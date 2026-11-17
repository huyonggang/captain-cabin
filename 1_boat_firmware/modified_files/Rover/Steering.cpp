#include "Rover.h"

/*****************************************
    Set the flight control servos based on the current calculated values
*****************************************/
void Rover::set_servos(void)
{
    water_detector.update();
    // send output signals to motors
    if (motor_test) {
        motor_test_output();
    } else if (control_mode == &mode_endurance && arming.is_armed()) {
        // TEST-ONLY: endurance test drives the two throttles directly
        mode_endurance.output_motors();
    } else {
        // get ground speed
        float speed;
        if (!g2.attitude_control.get_forward_speed(speed)) {
            speed = 0.0f;
        }

        g2.motors.output(arming.is_armed(), speed, G_Dt);
    }
}
