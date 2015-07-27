#include "wiringBBB.hpp"


/*----- pinMode() -----*/
void pinMode(int pin, DIRECTION direction) {
    // INPUT
    if (direction == INPUT) {
        // export
        char pin_char[5];
        char export_path[] = "/sys/class/gpio/export";
        FILE *fp_export;
        sprintf(pin_char, "%d", pin);
        fp_export = fopen(export_path, "w");
        fputs(pin_char, fp_export);
        fclose(fp_export);
        // direction
        char in_char[] = "in";
        char direction_path[40];
        FILE *fp_pindirection;
        sprintf(direction_path, "/sys/class/gpio/gpio%d/direction", pin);
        fp_pindirection = fopen(direction_path, "w");
        fputs(in_char, fp_pindirection);
        fclose(fp_pindirection);
    }
    // OUTPUT
    if (direction == OUTPUT) {
        // export
        char pin_char[5];
        char export_path[] = "/sys/class/gpio/export";
        FILE *fp_export;
        sprintf(pin_char, "%d", pin);
        fp_export = fopen(export_path, "w");
        fputs(pin_char, fp_export);
        fclose(fp_export);
        // direction
        char out_char[] = "out";
        char direction_path[40];
        FILE *fp_pindirection;
        sprintf(direction_path, "/sys/class/gpio/gpio%d/direction", pin);
        fp_pindirection = fopen(direction_path, "w");
        fputs(out_char, fp_pindirection);
        fclose(fp_pindirection);
    }
    // ANALOG INPUT
    if (direction == AINPUT) {
        char analog_input_char[] = "cape-bone-iio";
        char slots_path[] = "/sys/devices/bone_capemgr.9/slots";
        FILE *fp_slots;
        fp_slots = fopen(slots_path, "w");
        fputs(analog_input_char, fp_slots);
        fclose(fp_slots);
    }
    // ANALOG OUTPUT
    if (direction == AOUTPUT) {
        char analog_output_char[] = "am33xx_pwm";
        char slots_path[] = "/sys/devices/bone_capemgr.9/slots";
        FILE *fp_slots;
        fp_slots = fopen(slots_path, "w");
        fputs(analog_output_char, fp_slots);
        fclose(fp_slots);

        char analog_output_pin_char[40];
        char pin_P[][6] = {
            "P8_13",
            "P9_21"
        };
        int pin_Pi[] = {
            23,
            3
        };
        int pin_Pi_usiro[] = {
            16,
            17
        };
        int pin_num = 0;
        for (int i = 0; i < 2; i++) {
            if (pin == pin_Pi[i]) {
                pin_num = i;
            }
        }
        sprintf(analog_output_pin_char, "bone_pwm_%s", pin_P[pin_num]);
        fp_slots = fopen(slots_path, "w");
        fputs(analog_output_pin_char, fp_slots);
        fclose(fp_slots);

        char period[] = "1000000";
        char pwm_period[50];
        char pwm_run[50];
        FILE *fp_period;
        FILE *fp_run;
        sprintf(pwm_period, "/sys/devices/ocp.3/pwm_test_%s.%d/period", pin_P[pin_num], pin_Pi_usiro[pin_num]);
        sprintf(pwm_run,    "/sys/devices/ocp.3/pwm_test_%s.%d/run"   , pin_P[pin_num], pin_Pi_usiro[pin_num]);
        fp_period = fopen(pwm_period, "w");
        fp_run = fopen(pwm_run, "w");
        fputs(period, fp_period);
        fputs("1", fp_run);
        fclose(fp_period);
        fclose(fp_run);
    }
}


/*----- digitalRead() -----*/
int digitalRead(int pin) {
    FILE *fp_value;
    char value_path[40];
    char digital_input_get_char[40];

    sprintf(value_path, "/sys/class/gpio/gpio%d/value", pin);
    fp_value = fopen(value_path, "r");
    fgets(digital_input_get_char, 40, fp_value);

    int value = atoi(digital_input_get_char);
    fclose(fp_value);
    return value;
}


/*----- digitalWrite() -----*/
void digitalWrite(int pin, STATE state) {
    FILE *fp_value;

    char value_path[40];

    sprintf(value_path, "/sys/class/gpio/gpio%d/value", pin);
    fp_value = fopen(value_path, "w");

    // LOW
    if (state == LOW) {
        fputs("0", fp_value);
    }
    // HIGH
    else if (state == HIGH) {
        fputs("1", fp_value);
    }

    fclose(fp_value);
}


/*----- analogRead() -----*/
int analogRead(int pin) {
    char analog_input_pin_path[40];
    char analog_input_get_char[40];
    FILE *fp_analog_pin;
    sprintf(analog_input_pin_path, "/sys/devices/ocp.3/helper.15/AIN%d", pin);
    fp_analog_pin = fopen(analog_input_pin_path, "r");
    fgets(analog_input_get_char, 40, fp_analog_pin);
    fclose(fp_analog_pin);
    int value = atoi(analog_input_get_char);
    return value;
}


/*----- analogWrite() -----*/
void analogWrite(int pin, int value) {
    char pin_P[][6] = {
        "P8_13",
        "P9_21"
    };
    int pin_Pi[] = {
        23,
        3
    };
    int pin_Pi_usiro[] = {
        16,
        17
    };
    int pin_num = 0;
    for (int i = 0; i < 2; i++) {
        if (pin == pin_Pi[i]) {
            pin_num = i;
        }
    }
    char pwm_duty[40];
    char pwm_duty_char[10];
    FILE *fp_pwm_duty;
    sprintf(pwm_duty, "/sys/devices/ocp.3/pwm_test_%s.%d/duty", pin_P[pin_num], pin_Pi_usiro[pin_num]);
    fp_pwm_duty = fopen(pwm_duty, "w");
    sprintf(pwm_duty_char, "%d", value);
    fputs(pwm_duty_char, fp_pwm_duty);
    fclose(fp_pwm_duty);
}
