#pragma once

#include <stdint.h>

#include <GCS_MAVLink/GCS_MAVLink.h>
#include <AP_Math/AP_Math.h>
#include <AP_Mission/AP_Mission.h>
#include <AR_WPNav/AR_WPNav.h>

#include "defines.h"

// pre-define ModeRTL so Auto can appear higher in this file
class ModeRTL;

class Mode
{
public:

    // Auto Pilot modes
    // ----------------
    enum Number : uint8_t {
        MANUAL       = 0,
        ACRO         = 1,
        STEERING     = 3,
        HOLD         = 4,
        LOITER       = 5,
        FOLLOW       = 6,
        SIMPLE       = 7,
        AUTO         = 10,
        RTL          = 11,
        SMART_RTL    = 12,
        GUIDED       = 15,
        ENDURANCE    = 30,   // TEST-ONLY: motor endurance bench test
        INITIALISING = 16
    };

    // Constructor
    Mode();

    // do not allow copying
    Mode(const Mode &other) = delete;
    Mode &operator=(const Mode&) = delete;

    // enter this mode, returns false if we failed to enter
    bool enter();

    // perform any cleanups required:
    void exit();

    // returns a unique number specific to this mode
    virtual uint32_t mode_number() const = 0;

    // returns short text name (up to 4 bytes)
    virtual const char *name4() const = 0;

    //
    // methods that sub classes should override to affect movement of the vehicle in this mode
    //

    // convert user input to targets, implement high level control for this mode
    virtual void update() = 0;

    //
    // attributes of the mode
    //

    // return if in non-manual mode : Auto, Guided, RTL, SmartRTL
    virtual bool is_autopilot_mode() const { return false; }

    // return if external control is allowed in this mode (Guided or Guided-within-Auto)
    virtual bool in_guided_mode() const { return false; }

    // returns true if vehicle can be armed or disarmed from the transmitter in this mode
    virtual bool allows_arming_from_transmitter() { return !is_autopilot_mode(); }

    // returns false if vehicle cannot be armed in this mode
    virtual bool allows_arming() const { return true; }

    bool allows_stick_mixing() const { return is_autopilot_mode(); }

    //
    // attributes for mavlink system status reporting
    //

    // returns true if any RC input is used
    virtual bool has_manual_input() const { return false; }

    // true if heading is controlled
    virtual bool attitude_stabilized() const { return true; }

    // true if mode requires position and/or velocity estimate
    virtual bool requires_position() const { return true; }
    virtual bool requires_velocity() const { return true; }

    // return heading (in degrees) and cross track error (in meters) for reporting to ground station (NAV_CONTROLLER_OUTPUT message)
    virtual float wp_bearing() const;
    virtual float nav_bearing() const;
    virtual float crosstrack_error() const;
    virtual float get_desired_lat_accel() const;

    // get speed error in m/s, not currently supported
    float speed_error() const { return 0.0f; }

    //
    // navigation methods
    //

    // return distance (in meters) to destination
    virtual float get_distance_to_destination() const { return 0.0f; }

    // return desired location (used in Guided, Auto, RTL, etc)
    // return true on success, false if there is no valid destination
    virtual bool get_desired_location(Location& destination) const WARN_IF_UNUSED { return false; }

    // set desired location (used in Guided, Auto)
    //   next_leg_bearing_cd should be heading to the following waypoint (used to slow the vehicle in order to make the turn)
    virtual bool set_desired_location(const struct Location& destination, float next_leg_bearing_cd = AR_WPNAV_HEADING_UNKNOWN) WARN_IF_UNUSED;

    // true if vehicle has reached desired location. defaults to true because this is normally used by missions and we do not want the mission to become stuck
    virtual bool reached_destination() const { return true; }

    // get default speed for this mode (held in CRUISE_SPEED, WP_SPEED or RTL_SPEED)
    // rtl argument should be true if called from RTL or SmartRTL modes (handled here to avoid duplication)
    float get_speed_default(bool rtl = false) const;

    // set desired speed in m/s
    virtual bool set_desired_speed(float speed) { return false; }

    // execute the mission in reverse (i.e. backing up)
    void set_reversed(bool value);

    // handle tacking request (from auxiliary switch) in sailboats
    virtual void handle_tack_request();

protected:

    // subclasses override this to perform checks before entering the mode
    virtual bool _enter() { return true; }

    // subclasses override this to perform any required cleanup when exiting the mode
    virtual void _exit() { return; }

    // decode pilot steering and throttle inputs and return in steer_out and throttle_out arguments
    // steering_out is in the range -4500 ~ +4500 with positive numbers meaning rotate clockwise
    // throttle_out is in the range -100 ~ +100
    void get_pilot_desired_steering_and_throttle(float &steering_out, float &throttle_out);

    // decode pilot input steering and return steering_out and speed_out (in m/s)
    void get_pilot_desired_steering_and_speed(float &steering_out, float &speed_out);

    // decode pilot lateral movement input and return in lateral_out argument
    void get_pilot_desired_lateral(float &lateral_out);

    // decode pilot's input and return heading_out (in cd) and speed_out (in m/s)
    void get_pilot_desired_heading_and_speed(float &heading_out, float &speed_out);

    // decode pilot roll and pitch inputs and return in roll_out and pitch_out arguments
    // outputs are in the range -1 to +1
    void get_pilot_desired_roll_and_pitch(float &roll_out, float &pitch_out);

    // decode pilot height inputs and return in height_out arguments
    // outputs are in the range -1 to +1
    void get_pilot_desired_walking_height(float &walking_height_out);

    // high level call to navigate to waypoint
    void navigate_to_waypoint();

    // calculate steering output given a turn rate
    // desired turn rate in radians/sec. Positive to the right.
    void calc_steering_from_turn_rate(float turn_rate);

    // calculate steering angle given a desired lateral acceleration
    void calc_steering_from_lateral_acceleration(float lat_accel, bool reversed = false);

    // calculate steering output to drive towards desired heading
    // rate_max is a maximum turn rate in deg/s.  set to zero to use default turn rate limits
    void calc_steering_to_heading(float desired_heading_cd, float rate_max_degs = 0.0f);

    // calculates the amount of throttle that should be output based
    // on things like proximity to corners and current speed
    virtual void calc_throttle(float target_speed, bool avoidance_enabled);

    // performs a controlled stop. returns true once vehicle has stopped
    bool stop_vehicle();

    // estimate maximum vehicle speed (in m/s)
    // cruise_speed is in m/s, cruise_throttle should be in the range -1 to +1
    float calc_speed_max(float cruise_speed, float cruise_throttle) const;

    // calculate pilot input to nudge speed up or down
    //  target_speed should be in meters/sec
    //  reversed should be true if the vehicle is intentionally backing up which allows the pilot to increase the backing up speed by pulling the throttle stick down
    float calc_speed_nudge(float target_speed, bool reversed);

protected:

    // decode pilot steering and throttle inputs and return in steer_out and throttle_out arguments
    // steering_out is in the range -4500 ~ +4500 with positive numbers meaning rotate clockwise
    // throttle_out is in the range -100 ~ +100
    void get_pilot_input(float &steering_out, float &throttle_out);
    void set_steering(float steering_value);

    // references to avoid code churn:
    class AP_AHRS &ahrs;
    class Parameters &g;
    class ParametersG2 &g2;
    class RC_Channel *&channel_steer;
    class RC_Channel *&channel_throttle;
    class RC_Channel *&channel_lateral;
    class RC_Channel *&channel_roll;
    class RC_Channel *&channel_pitch;
    class RC_Channel *&channel_walking_height;
    class AR_AttitudeControl &attitude_control;

    // private members for waypoint navigation
    float _distance_to_destination; // distance from vehicle to final destination in meters
    bool _reached_destination;  // true once the vehicle has reached the destination
    float _desired_yaw_cd;      // desired yaw in centi-degrees.  used in Auto, Guided and Loiter
    float _prev_steering;
};


class ModeAcro : public Mode
{
public:

    uint32_t mode_number() const override { return ACRO; }
    const char *name4() const override { return "ACRO"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes for mavlink system status reporting
    bool has_manual_input() const override { return true; }

    // acro mode requires a velocity estimate for non skid-steer rovers
    bool requires_position() const override { return false; }
    bool requires_velocity() const override;

    // sailboats in acro mode support user manually initiating tacking from transmitter
    void handle_tack_request() override;
};


class ModeAuto : public Mode
{
public:

    uint32_t mode_number() const override { return AUTO; }
    const char *name4() const override { return "AUTO"; }

    bool is_loiter_submode() const { return _submode == Auto_Loiter; }
    bool is_rtl_submode() const { return _submode == Auto_RTL; }

    // methods that affect movement of the vehicle in this mode
    void update() override;
    void calc_throttle(float target_speed, bool avoidance_enabled) override;

    // attributes of the mode
    bool is_autopilot_mode() const override { return true; }

    // return if external control is allowed in this mode (Guided or Guided-within-Auto)
    bool in_guided_mode() const override { return _submode == Auto_Guided || _submode == Auto_NavScriptTime; }

    // return distance (in meters) to destination
    float get_distance_to_destination() const override;

    // get or set desired location
    bool get_desired_location(Location& destination) const override WARN_IF_UNUSED;
    bool set_desired_location(const struct Location& destination, float next_leg_bearing_cd = AR_WPNAV_HEADING_UNKNOWN) override WARN_IF_UNUSED;
    bool reached_destination() const override;

    // set desired speed in m/s
    bool set_desired_speed(float speed) override;

    // start RTL (within auto)
    void start_RTL();

    // lua accessors for nav script time support
    bool nav_script_time(uint16_t &id, uint8_t &cmd, float &arg1, float &arg2);
    void nav_script_time_done(uint16_t id);

    AP_Mission mission{
        FUNCTOR_BIND_MEMBER(&ModeAuto::start_command, bool, const AP_Mission::Mission_Command&),
        FUNCTOR_BIND_MEMBER(&ModeAuto::verify_command_callback, bool, const AP_Mission::Mission_Command&),
        FUNCTOR_BIND_MEMBER(&ModeAuto::exit_mission, void)};

    enum Mis_Done_Behave {
        MIS_DONE_BEHAVE_HOLD      = 0,
        MIS_DONE_BEHAVE_LOITER    = 1,
        MIS_DONE_BEHAVE_ACRO      = 2,
        MIS_DONE_BEHAVE_MANUAL    = 3
    };

protected:

    bool _enter() override;
    void _exit() override;

    enum AutoSubMode {
        Auto_WP,                // drive to a given location
        Auto_HeadingAndSpeed,   // turn to a given heading
        Auto_RTL,               // perform RTL within auto mode
        Auto_Loiter,            // perform Loiter within auto mode
        Auto_Guided,            // handover control to external navigation system from within auto mode
        Auto_Stop,              // stop the vehicle as quickly as possible
        Auto_NavScriptTime,     // accept targets from lua scripts while NAV_SCRIPT_TIME commands are executing
        Auto_Manual,            // Manual control during a auto waypoint
    } _submode;

    enum AutoSubMode prev_submode;  // previous submode

private:

    bool check_trigger(void);
    bool start_loiter(bool loiter_at_last_dest = false);
    void start_guided(const Location& target_loc);
    void start_stop();
    void send_guided_position_target();

    bool start_command(const AP_Mission::Mission_Command& cmd);
    void exit_mission();
    bool verify_command_callback(const AP_Mission::Mission_Command& cmd);

    bool verify_command(const AP_Mission::Mission_Command& cmd);
    void do_RTL(void);
    bool do_nav_wp(const AP_Mission::Mission_Command& cmd, bool always_stop_at_destination);
    void do_nav_guided_enable(const AP_Mission::Mission_Command& cmd);
    void do_nav_set_yaw_speed(const AP_Mission::Mission_Command& cmd);
    void do_nav_delay(const AP_Mission::Mission_Command& cmd);
    bool verify_nav_delay(const AP_Mission::Mission_Command& cmd);
    bool verify_nav_wp(const AP_Mission::Mission_Command& cmd);
    bool verify_RTL() const;
    bool verify_loiter_unlimited(const AP_Mission::Mission_Command& cmd);
    bool verify_loiter_time(const AP_Mission::Mission_Command& cmd);
    bool verify_nav_guided_enable(const AP_Mission::Mission_Command& cmd);
    bool verify_nav_set_yaw_speed();
    void do_wait_delay(const AP_Mission::Mission_Command& cmd);
    void do_within_distance(const AP_Mission::Mission_Command& cmd);
    bool verify_wait_delay();
    bool verify_within_distance();
    void do_change_speed(const AP_Mission::Mission_Command& cmd);
    void do_set_home(const AP_Mission::Mission_Command& cmd);
    void do_set_reverse(const AP_Mission::Mission_Command& cmd);
    void do_guided_limits(const AP_Mission::Mission_Command& cmd);
#if AP_SCRIPTING_ENABLED
    void do_nav_script_time(const AP_Mission::Mission_Command& cmd);
    bool verify_nav_script_time();
#endif

    // added for catchx mini.
    // the request is to control the vehicle by manual in auto mode
    // if there is valid rc input in stree or throttle channel for 0.5 second
    // the vehicle will be in manual control.
    // if there is no valid rc input in stree or throttle channel for 0.5 second
    // the vehicle will be in auto mode.
    // we use a flag to determine whether we are in manual mode.
    // also a counter to count the time of valid rc input.
    bool in_manual_mode;
    uint16_t valid_rc_input_time;
    // @brief check if there is valid rc input in stree or throttle channel
    // @return true if there is valid rc input and mode is need to changed
    bool RC_change_mode();

    bool waiting_to_start;  // true if waiting for EKF origin before starting mission
    bool auto_triggered;        // true when auto has been triggered to start

    // HeadingAndSpeed sub mode variables
    float _desired_speed;   // desired speed in HeadingAndSpeed submode
    bool _reached_heading;  // true when vehicle has reached desired heading in TurnToHeading sub mode

    // Loiter control
    uint16_t loiter_duration;       // How long we should loiter at the nav_waypoint (time in seconds)
    uint32_t loiter_start_time;     // How long have we been loitering - The start time in millis
    bool previously_reached_wp;     // set to true if we have EVER reached the waypoint

    // Guided-within-Auto variables
    struct {
        Location loc;           // location target sent to external navigation
        bool valid;             // true if loc is valid
        uint32_t last_sent_ms;  // system time that target was last sent to offboard navigation
    } guided_target;

    // Conditional command
    // A value used in condition commands (eg delay, change alt, etc.)
    // For example in a change altitude command, it is the altitude to change to.
    int32_t condition_value;
    // A starting value used to check the status of a conditional command.
    // For example in a delay command the condition_start records that start time for the delay
    int32_t condition_start;

    // Delay the next navigation command
    uint32_t nav_delay_time_max_ms;  // used for delaying the navigation commands
    uint32_t nav_delay_time_start_ms;

#if AP_SCRIPTING_ENABLED
    // nav_script_time command variables
    struct {
        bool done;          // true once lua script indicates it has completed
        uint16_t id;        // unique id to avoid race conditions between commands and lua scripts
        uint32_t start_ms;  // system time nav_script_time command was received (used for timeout)
        uint8_t command;    // command number provided by mission command
        uint8_t timeout_s;  // timeout (in seconds) provided by mission command
        float arg1;         // 1st argument provided by mission command
        float arg2;         // 2nd argument provided by mission command
    } nav_scripting;
#endif
};


class ModeGuided : public Mode
{
public:

    uint32_t mode_number() const override { return GUIDED; }
    const char *name4() const override { return "GUID"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes of the mode
    bool is_autopilot_mode() const override { return true; }

    // return if external control is allowed in this mode (Guided or Guided-within-Auto)
    bool in_guided_mode() const override { return true; }

    // return distance (in meters) to destination
    float get_distance_to_destination() const override;

    // return true if vehicle has reached destination
    bool reached_destination() const override;

    // set desired speed in m/s
    bool set_desired_speed(float speed) override;

    // get or set desired location
    bool get_desired_location(Location& destination) const override WARN_IF_UNUSED;
    bool set_desired_location(const struct Location& destination, float next_leg_bearing_cd = AR_WPNAV_HEADING_UNKNOWN) override WARN_IF_UNUSED;

    // set desired heading and speed
    void set_desired_heading_and_speed(float yaw_angle_cd, float target_speed);

    // set desired heading-delta, turn-rate and speed
    void set_desired_heading_delta_and_speed(float yaw_delta_cd, float target_speed);
    void set_desired_turn_rate_and_speed(float turn_rate_cds, float target_speed);

    // set steering and throttle (-1 to +1).  Only called from scripts
    void set_steering_and_throttle(float steering, float throttle);

    // vehicle start loiter
    bool start_loiter();

    // start stopping
    void start_stop();

    // guided limits
    void limit_set(uint32_t timeout_ms, float horiz_max);
    void limit_clear();
    void limit_init_time_and_location();
    bool limit_breached() const;

protected:

    enum GuidedMode {
        Guided_WP,
        Guided_HeadingAndSpeed,
        Guided_TurnRateAndSpeed,
        Guided_Loiter,
        Guided_SteeringAndThrottle,
        Guided_Stop
    };

    bool _enter() override;

    GuidedMode _guided_mode;    // stores which GUIDED mode the vehicle is in

    // attitude control
    bool have_attitude_target;  // true if we have a valid attitude target
    uint32_t _des_att_time_ms;  // system time last call to set_desired_attitude was made (used for timeout)
    float _desired_yaw_rate_cds;// target turn rate centi-degrees per second
    bool send_notification;     // used to send one time notification to ground station
    float _desired_speed;       // desired speed used only in HeadingAndSpeed submode

    // direct steering and throttle control
    bool _have_strthr;          // true if we have a valid direct steering and throttle inputs
    uint32_t _strthr_time_ms;   // system time last call to set_steering_and_throttle was made (used for timeout)
    float _strthr_steering;     // direct steering input in the range -1 to +1
    float _strthr_throttle;     // direct throttle input in the range -1 to +1

    // limits
    struct {
        uint32_t timeout_ms;// timeout from the time that guided is invoked
        float horiz_max;    // horizontal position limit in meters from where guided mode was initiated (0 = no limit)
        uint32_t start_time_ms; // system time in milliseconds that control was handed to the external computer
        Location start_loc; // starting location for checking horiz_max limit
    } limit;
};


class ModeHold : public Mode
{
public:

    uint32_t mode_number() const override { return HOLD; }
    const char *name4() const override { return "HOLD"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes for mavlink system status reporting
    bool attitude_stabilized() const override { return false; }

    // hold mode does not require position or velocity estimate
    bool requires_position() const override { return false; }
    bool requires_velocity() const override { return false; }
};

class ModeLoiter : public Mode
{
public:

    uint32_t mode_number() const override { return LOITER; }
    const char *name4() const override { return "LOIT"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes of the mode
    bool is_autopilot_mode() const override { return true; }

    // return desired heading (in degrees) and cross track error (in meters) for reporting to ground station (NAV_CONTROLLER_OUTPUT message)
    float wp_bearing() const override { return _desired_yaw_cd * 0.01f; }
    float nav_bearing() const override { return _desired_yaw_cd * 0.01f; }
    float crosstrack_error() const override { return 0.0f; }

    // return desired location
    bool get_desired_location(Location& destination) const override WARN_IF_UNUSED;

    // return distance (in meters) to destination
    float get_distance_to_destination() const override { return _distance_to_destination; }

    void set_enter_from_auto_wp_ending(bool b) { _enter_from_auto_wp_ending = b;}
protected:

    bool _enter() override;
    bool _enter_from_auto_wp_ending;
    Location _destination;      // target location to hold position around
    float _desired_speed;       // desired speed (ramped down from initial speed to zero)
};

class ModeManual : public Mode
{
public:

    uint32_t mode_number() const override { return MANUAL; }
    const char *name4() const override { return "MANU"; }

    bool is_cruising() const { return heading_hold_mode == cruise_hold; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes for mavlink system status reporting
    bool has_manual_input() const override { return true; }
    bool attitude_stabilized() const override { return false; }

    // manual mode does not require position or velocity estimate
    bool requires_position() const override { return false; }
    bool requires_velocity() const override { return false; }

    // let rover into cruise status in manual mode
    bool set_desired_speed(float speed) override;

protected:
    enum
    {
        heading_hold_manual,
        heading_hold,
        cruise_hold,
    } heading_hold_mode;
    bool prev_auto_steering;
    float heading_cd;
    float cruise_speed;
    void _exit() override;
    bool _enter() override;
private:
    void _set_heading(void);
};


class ModeRTL : public Mode
{
public:

    uint32_t mode_number() const override { return RTL; }
    const char *name4() const override { return "RTL"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes of the mode
    bool is_autopilot_mode() const override { return true; }

    // do not allow arming from this mode
    bool allows_arming() const override { return false; }

    // return desired location
    bool get_desired_location(Location& destination) const override WARN_IF_UNUSED;

    // return distance (in meters) to destination
    float get_distance_to_destination() const override { return _distance_to_destination; }
    bool reached_destination() const override;

    // set desired speed in m/s
    bool set_desired_speed(float speed) override;

protected:

    bool _enter() override;
    void _exit() override;

    bool send_notification; // used to send one time notification to ground station
    bool _loitering;        // true if loitering at end of RTL

};

class ModeSmartRTL : public Mode
{
public:

    uint32_t mode_number() const override { return SMART_RTL; }
    const char *name4() const override { return "SRTL"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes of the mode
    bool is_autopilot_mode() const override { return true; }

    // do not allow arming from this mode
    bool allows_arming() const override { return false; }

    // return desired location
    bool get_desired_location(Location& destination) const override WARN_IF_UNUSED;

    // return distance (in meters) to destination
    float get_distance_to_destination() const override { return _distance_to_destination; }
    bool reached_destination() const override { return smart_rtl_state == SmartRTL_StopAtHome; }

    // set desired speed in m/s
    bool set_desired_speed(float speed) override;

    // save current position for use by the smart_rtl flight mode
    void save_position();

protected:

    // Safe RTL states
    enum SmartRTLState {
        SmartRTL_WaitForPathCleanup,
        SmartRTL_PathFollow,
        SmartRTL_StopAtHome,
        SmartRTL_Failure
    } smart_rtl_state;

    bool _enter() override;
    bool _load_point;
    bool _loitering;        // true if loitering at end of SRTL
};

   

class ModeSteering : public Mode
{
public:

    uint32_t mode_number() const override { return STEERING; }
    const char *name4() const override { return "STER"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes for mavlink system status reporting
    bool has_manual_input() const override { return true; }

    // steering requires velocity but not position
    bool requires_position() const override { return false; }
    bool requires_velocity() const override { return true; }

    // return desired lateral acceleration
    float get_desired_lat_accel() const override { return _desired_lat_accel; }

private:

    float _desired_lat_accel;   // desired lateral acceleration calculated from pilot steering input
};

class ModeInitializing : public Mode
{
public:

    uint32_t mode_number() const override { return INITIALISING; }
    const char *name4() const override { return "INIT"; }

    // methods that affect movement of the vehicle in this mode
    void update() override { }

    // do not allow arming from this mode
    bool allows_arming() const override { return false; }

    // attributes for mavlink system status reporting
    bool has_manual_input() const override { return true; }
    bool attitude_stabilized() const override { return false; }
protected:
    bool _enter() override { return false; };
};

class ModeFollow : public Mode
{
public:

    uint32_t mode_number() const override { return FOLLOW; }
    const char *name4() const override { return "FOLL"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;

    // attributes of the mode
    bool is_autopilot_mode() const override { return true; }

    // return desired heading (in degrees) and cross track error (in meters) for reporting to ground station (NAV_CONTROLLER_OUTPUT message)
    float wp_bearing() const override;
    float nav_bearing() const override { return wp_bearing(); }
    float crosstrack_error() const override { return 0.0f; }

    // return desired location
    bool get_desired_location(Location& destination) const override WARN_IF_UNUSED { return false; }

    // return distance (in meters) to destination
    float get_distance_to_destination() const override;

    // set desired speed in m/s
    bool set_desired_speed(float speed) override;

protected:

    bool _enter() override;
    void _exit() override;

    float _desired_speed;       // desired speed in m/s
};

class ModeSimple : public Mode
{
public:

    uint32_t mode_number() const override { return SIMPLE; }
    const char *name4() const override { return "SMPL"; }

    // methods that affect movement of the vehicle in this mode
    void update() override;
    void init_heading();

    // simple type enum used for SIMPLE_TYPE parameter
    enum simple_type {
        Simple_InitialHeading = 0,
        Simple_CardinalDirections = 1,
    };

private:

    float _initial_heading_cd;  // vehicle heading (in centi-degrees) at moment vehicle was armed
    float _desired_heading_cd;  // latest desired heading (in centi-degrees) from pilot
};

// ---------------------------------------------------------------------------
// TEST-ONLY build: motor endurance bench/tank test mode (not for production)
//   Mode 1 (AUTO)    : firmware runs the configured cycle on its own (ET_* params),
//                      the phone may disconnect at any time.
//   Mode 2 (REALTIME): the App sends live throttle commands (MAV_CMD_USER_2);
//                      motors stop if no command arrives within ET_RT_TMO ms.
// ---------------------------------------------------------------------------
class ModeEndurance : public Mode
{
public:
    enum class State : uint8_t { IDLE=0, AUTO_RUN=1, AUTO_PAUSED=2, REALTIME=3, RT_LINK_LOST=4, DONE=5, FAULT=6 };
    enum class Phase : uint8_t { NONE=0, FWD=1, STOP1=2, REV=3, STOP2=4, BURST_ON=5, BURST_OFF=6, DAILY_REST=7 };

    uint32_t mode_number() const override { return ENDURANCE; }
    const char *name4() const override { return "ENDU"; }
    void update() override;
    bool attitude_stabilized() const override { return false; }
    bool requires_position() const override { return false; }
    bool requires_velocity() const override { return false; }

    // App commands (MAV_CMD_USER_1 / MAV_CMD_USER_2)
    MAV_RESULT handle_control(uint8_t action, bool reset_counters);
    MAV_RESULT handle_realtime(float left_pct, float right_pct, float hold_ms);

    // called from Rover::set_servos() instead of the normal mixer when active
    void output_motors();
    bool active() const;
    void send_status();   // 1Hz named-value telemetry + ETST log
    uint16_t pct_to_pwm(float pct, uint16_t trim) const;

    // v0.3 source gating: only the App link may enter / leave / command the test
    void set_msg_src(int8_t c, uint8_t sysid) { _msg_chan = c; _msg_sysid = sysid; }
    bool from_app() const;
    bool allow_mode_change(const Mode &new_mode, ModeReason reason);
    void deny_text(const char *what);

protected:
    bool _enter() override;
    void _exit() override;

private:
    void auto_step(uint32_t dt_ms);
    void next_phase();
    void start_phase(Phase p, uint32_t duration_ms, float target_pct);
    void fault(const char *why);
    void safety_checks(uint32_t dt_ms);

    State    _state = State::IDLE;
    int8_t   _msg_chan = -1;
    uint8_t  _msg_sysid;       // MAVLink channel of the message being handled (-1 = not from MAVLink)
    uint32_t _deny_text_ms;
    Phase    _phase = Phase::NONE;
    uint32_t _last_ms;
    uint32_t _phase_elapsed_ms;
    uint32_t _phase_dur_ms;
    float    _target_pct;        // signed: + forward, - reverse
    float    _out_l, _out_r;     // ramped output, percent
    float    _rt_l, _rt_r;       // realtime targets
    uint32_t _rt_last_ms;
    uint32_t _rt_hold_ms;
    uint32_t _cycles;            // completed FWD/REV cycles
    uint16_t _burst_done;
    uint32_t _bursts;            // completed burst blocks
    uint64_t _cum_run_ms;        // motor-on time
    uint64_t _since_burst_ms;    // motor-on time since last burst block
    uint64_t _active_ms;         // wall time since start / last daily rest
    uint32_t _last_save_ms;
    uint32_t _vlow_ms, _ihigh_ms;
    uint16_t _pwm_l = 1500, _pwm_r = 1500;
};

