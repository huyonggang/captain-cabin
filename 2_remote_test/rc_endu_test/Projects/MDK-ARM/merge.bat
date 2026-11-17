@echo off
@REM 设置输入文件的路径
set boot="../../../CatchXBlackPro_BootLoader/Output/boot.hex"
set app="../../Output/apm32f407.hex"

srec_cat.exe %boot% -intel -fill 0xff 0x08000000 0x08010000 %app% -intel -o "../../Output/BIN/%1(boot+app).hex" -intel

exit
