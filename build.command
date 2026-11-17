#!/bin/bash
# macOS: double-click in Finder, or run with bash from Terminal.
set -euo pipefail

ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
cd "$ROOT"
# Finder/Terminal may start without Homebrew's directory in PATH.
for tool_dir in /opt/homebrew/bin /usr/local/bin; do
  if [ -d "$tool_dir" ]; then PATH="$PATH:$tool_dir"; fi
done
export PATH
CHECK_ONLY=0
RESUME_RUN=''
scratch=''
case "${1:-}" in
  --check) CHECK_ONLY=1 ;;
  --resume)
    [[ "${2:-}" =~ ^[0-9]+$ ]] && [ "$#" -eq 2 ] || { echo '用法：bash build.command --resume 运行ID' >&2; exit 1; }
    RESUME_RUN=$2 ;;
  --help|-h)
    echo '用法：bash build.command [--check | --resume 运行ID]'
    echo '默认：提交并上传编译相关文件，触发 GitHub Actions，等待并下载结果。'
    echo '--check：只检查环境、登录、仓库权限和分支，不提交、不上传、不触发编译。'
    echo '--resume 运行ID：继续等待和下载已有任务，不提交、不推送、不创建新编译。'
    exit 0 ;;
  '') ;;
  *) echo "未知参数：$1" >&2; exit 1 ;;
esac

finish() {
  result=$?
  trap - EXIT
  if [ -n "$scratch" ]; then rm -rf -- "$scratch"; fi
  if [ "$result" -ne 0 ]; then
    echo
    echo '操作未完成，请查看上方错误信息。' >&2
  fi
  # Pause only on a regular interactive launch; --check remains automation friendly.
  if [ "$CHECK_ONLY" -eq 0 ] && [ -t 0 ]; then
    read -r -p '按回车关闭…' _ || true
  fi
  exit "$result"
}
trap finish EXIT

fail() { echo "错误：$*" >&2; exit 1; }

# Retry reads and downloads only. A dispatch request must never be retried here:
# GitHub may have accepted it even when the local connection was interrupted.
scratch=$(mktemp -d "${TMPDIR:-/tmp}/remote-build.XXXXXX")
gh_retry() {
  local attempt status=1
  for ((attempt=1; attempt<=3; attempt++)); do
    if gh "$@" > "$scratch/stdout" 2> "$scratch/stderr"; then
      cat "$scratch/stdout"
      return 0
    else
      status=$?
    fi
    if [ "$attempt" -lt 3 ]; then
      echo "GitHub 查询或下载暂时失败，正在重试（$attempt/3）…" >&2
      sleep "$((attempt * 2))"
    fi
  done
  cat "$scratch/stderr" >&2
  return "$status"
}

command -v git >/dev/null || fail '没有找到 Git，请先安装 Xcode Command Line Tools。'
if ! command -v gh >/dev/null; then
  if [ "$CHECK_ONLY" -eq 1 ]; then
    fail '未安装 GitHub CLI。可执行 brew install gh 后重试。'
  fi
  command -v brew >/dev/null || fail '请先安装 GitHub CLI：https://cli.github.com/，然后重新运行。'
  echo '正在安装 GitHub CLI…'
  brew install gh
fi

if ! gh auth status --hostname github.com >/dev/null 2>&1; then
  [ "$CHECK_ONLY" -eq 0 ] || fail '尚未登录 GitHub，请先执行 gh auth login。'
  echo '首次使用需要通过浏览器登录 GitHub。'
  gh auth login --hostname github.com --git-protocol https --web --scopes repo,workflow
fi

git rev-parse --is-inside-work-tree >/dev/null 2>&1 || fail '脚本必须放在 captain-cabin 仓库根目录。'
# Follow origin's push destination so changing the Git remote also changes the
# workflow, status queries and artifact downloads. Do not hard-code an owner.
remote=$(git remote get-url --push origin)
case "$remote" in
  https://github.com/*) repo=${remote#https://github.com/} ;;
  http://github.com/*) repo=${remote#http://github.com/} ;;
  git@github.com:*) repo=${remote#git@github.com:} ;;
  ssh://git@github.com/*) repo=${remote#ssh://git@github.com/} ;;
  *) fail "origin 不是可识别的 GitHub 地址：$remote" ;;
esac
repo=${repo%/}
repo=${repo%.git}
[[ "$repo" =~ ^[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+$ ]] || fail '无法识别 GitHub 仓库名称。'
repo_url="https://github.com/$repo"
echo "origin 推送地址：$remote"
echo "本次构建仓库：$repo_url"

if [ -z "$RESUME_RUN" ]; then
branch=$(git symbolic-ref --quiet --short HEAD) || fail '当前处于 detached HEAD，请先切换到默认分支。'
default_branch=$(gh_retry api "repos/$repo" --jq '.default_branch')
can_push=$(gh_retry api "repos/$repo" --jq '.permissions.push // false')
[ "$can_push" = true ] || fail "当前 GitHub 账号没有 $repo 的推送权限。"
[ "$branch" = "$default_branch" ] || fail "请先切换到默认分支 $default_branch；首次启用手动 workflow 需要上传到默认分支。"
git diff --cached --quiet || fail '暂存区已有其他修改。请先处理已有暂存内容，避免混入本次提交。'

for required in .github/workflows/remote-keil-test.yml scripts/prepare_remote_ci.py scripts/keil_ci.py 2_remote_test/rc_endu_test/Projects/MDK-ARM/CatchXBlack_Pro.uvprojx; do
  [ -f "$required" ] || fail "缺少文件：$required"
done

echo "GitHub 仓库：$repo"
echo "上传分支：$branch"
echo '将提交编译配置、操作说明、一键脚本和遥控器源码目录中的修改。'
if [ "$CHECK_ONLY" -eq 1 ]; then
  echo '检查通过。未提交、上传或启动编译。'
  exit 0
fi

# Authenticate this command via gh without changing the user's remote or global Git config.
github_git() {
  git -c credential.helper= -c 'credential.https://github.com.helper=!gh auth git-credential' "$@"
}
push_url="$repo_url.git"
github_git fetch "$push_url" "$branch"
git merge-base --is-ancestor FETCH_HEAD HEAD || fail '远端有本地尚未包含的提交，请先执行 git pull --ff-only 后重试。'

git add -- .gitignore .github/workflows/remote-keil-test.yml scripts/prepare_remote_ci.py scripts/keil_ci.py scripts/tests/ \
  2_remote_test/GITHUB_BUILD.md 2_remote_test/rc_endu_test 'build.command'
if ! git diff --cached --quiet; then
  git commit -m 'Add one-click GitHub build test for remote firmware'
fi
commit=$(git rev-parse HEAD)
echo '正在上传到 GitHub…'
github_git push "$push_url" "HEAD:refs/heads/$branch"

workflow=remote-keil-test.yml
echo '等待 GitHub 识别 workflow…'
available=0
for ((attempt=0; attempt<24; attempt++)); do
  if gh api "repos/$repo/actions/workflows/$workflow" --jq '.id' >/dev/null 2>&1; then
    available=1
    break
  fi
  sleep 5
done
[ "$available" -eq 1 ] || fail "workflow 暂未可用，请查看 $repo_url/actions，启用 Actions 后重新运行脚本。"

request_id="mac-$(date -u +%Y%m%dT%H%M%SZ)-$$-$RANDOM"
gh workflow run "$workflow" --repo "$repo" --ref "$branch" --raw-field "request_id=$request_id"
echo '已发起编译，正在查找本次运行…'
run_id=''
for ((attempt=0; attempt<36; attempt++)); do
  if candidate=$(gh run list --repo "$repo" --workflow "$workflow" --branch "$branch" \
    --event workflow_dispatch --limit 100 --json databaseId,displayTitle \
    --jq ".[] | select(.displayTitle == \"Remote firmware $request_id\") | .databaseId"); then
    run_id=$candidate
    [ -z "$run_id" ] || break
  fi
  sleep 5
done
[ -n "$run_id" ] || fail "未找到本次运行，请查看 $repo_url/actions。请勿连续重复触发。"
run_url="$repo_url/actions/runs/$run_id"
echo "运行页面：$run_url"
run_sha=$(gh_retry run view "$run_id" --repo "$repo" --json headSha --jq '.headSha')
[ "$run_sha" = "$commit" ] || fail '触发时远端分支发生变化，本次运行的提交与本地不同，请检查运行页面。'
else
  run_id=$RESUME_RUN
  run_url="$repo_url/actions/runs/$run_id"
  gh_retry run view "$run_id" --repo "$repo" --json databaseId --jq '.databaseId' >/dev/null
  echo "继续已有任务：$run_url"
fi

output="$ROOT/build-artifacts/remote/$run_id"
mkdir -p "$output"
printf '%s\n' "$run_url" > "$output/run-url.txt"
echo '等待云端编译完成，下载和安装工具链可能需要较长时间…'
last_state=''
completed=0
query_failures=0
wait_started=$SECONDS
while [ "$((SECONDS - wait_started))" -lt 2700 ]; do
  if state=$(gh run view "$run_id" --repo "$repo" --json status,conclusion \
    --jq '.status + " " + (.conclusion // "")' 2> "$output/status-query-error.txt"); then
    if [ "$query_failures" -gt 0 ]; then echo 'GitHub 状态查询已恢复。'; fi
    query_failures=0
    if [ "$state" != "$last_state" ]; then
      echo "状态：$state"
      last_state=$state
    fi
    case "$state" in
      completed*) completed=1; break ;;
    esac
  else
    query_failures=$((query_failures + 1))
    printf '\n[%s] 状态查询失败\n' "$(date '+%Y-%m-%d %H:%M:%S')" >> "$output/network-errors.log"
    cat "$output/status-query-error.txt" >> "$output/network-errors.log"
    if [ "$query_failures" -eq 1 ]; then
      echo '暂时无法查询 GitHub 状态；云端任务不受影响，脚本会自动重试。'
      echo "也可稍后继续：bash \"$ROOT/build.command\" --resume $run_id"
    fi
  fi
  sleep 10
done
[ "$completed" -eq 1 ] || fail "等待超时，云端任务可能仍在运行。可执行 bash \"$ROOT/build.command\" --resume $run_id 继续。运行页面：$run_url"

echo '正在下载运行日志和构建附件…'
gh_retry run view "$run_id" --repo "$repo" --log > "$output/github-run.log" 2> "$output/log-download-error.txt" || true
artifact_count=$(gh_retry api "repos/$repo/actions/runs/$run_id/artifacts?per_page=100" \
  --jq '[.artifacts[] | select(.expired == false)] | length')
download_ok=1
if [ "$artifact_count" -gt 0 ]; then
  download_ok=0
  # Download into a fresh directory on each attempt. A failed download may have
  # left partial files; gh refuses to overwrite those when retrying in place.
  for ((attempt=1; attempt<=3; attempt++)); do
    download_dir="$scratch/artifacts-$attempt"
    mkdir -p "$download_dir"
    if gh run download "$run_id" --repo "$repo" --dir "$download_dir" 2> "$output/artifact-download-error.txt"; then
      cp -R "$download_dir/." "$output/"
      download_ok=1
      break
    fi
    if [ "$attempt" -lt 3 ]; then
      echo "附件下载暂时失败，正在重试（$attempt/3）…"
      sleep "$((attempt * 2))"
    fi
  done
  if [ "$download_ok" -eq 0 ]; then cat "$output/artifact-download-error.txt" >&2; fi
else
  echo '本次运行没有生成附件，请查看 github-run.log 或运行页面。'
fi
echo "结果目录：$output"
if [ "$state" != 'completed success' ]; then
  reason_file="$output/remote-keil-diagnostics/ci-logs/failure.txt"
  if [ -f "$reason_file" ]; then
    echo '本次失败原因与解决方式：' >&2
    cat "$reason_file" >&2
  fi
  echo '云端编译未成功，请检查 remote-keil-diagnostics 内的日志。' >&2
  echo "运行页面：$run_url" >&2
  exit 1
fi
[ "$download_ok" -eq 1 ] || fail "编译成功但附件下载失败，可在 $run_url 手动下载。"
[ -d "$output/remote-firmware-app" ] || fail '运行成功但未下载到固件附件，请检查运行页面。'
echo "编译成功。固件保存在：$output/remote-firmware-app"
echo 'BIN 是应用镜像，起始地址为 0x08010000，不含 Bootloader。'
