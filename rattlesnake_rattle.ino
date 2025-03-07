int motorPin = 3; // PWM-capable pin

void setup() {
    pinMode(motorPin, OUTPUT);
}

void loop() {
    accel_decel1(); // Run acceleration-deceleration sequence
    delay(100);    // Wait 0.1 seconds

    accel_decel2(); // Run abrupt ON/OFF sequence
    delay(750);    // Wait 0.75 seconds

    accel_decel3(); // Run smooth acceleration to 80% and deceleration
}

// Function to turn motor ON with percentage-based power (0-100%)
void on(int percentage) {
    if (percentage < 0) percentage = 0;     // Clamp minimum at 0%
    if (percentage > 100) percentage = 100; // Clamp maximum at 100%

    int pwmValue = (percentage * 255) / 100; // Convert percentage to PWM (0-255)
    analogWrite(motorPin, pwmValue);
}

// Function to turn motor OFF
void off() {
    analogWrite(motorPin, 0);
}

// Function to gradually accelerate to 100% in 0.5s, hold for 4s, then decelerate
void accel_decel1() {
    int stepDelay = 25; // Delay per step (milliseconds)
    int steps = 500 / stepDelay; // Number of steps in 0.5 seconds (500ms)

    // Accelerate from 0% to 100% in 0.5s
    for (int power = 0; power <= 100; power += (100 / steps)) {
        on(power);
        delay(stepDelay);
    }

    delay(4000); // Hold full speed for 4 seconds

    // Decelerate from 100% to 0% in 0.5s
    for (int power = 100; power >= 0; power -= (100 / steps)) {
        on(power);
        delay(stepDelay);
    }

    off(); // Ensure motor is completely off
}

// Function to turn motor ON for 1 second, OFF for 0.1 second, repeat 3 times
void accel_decel2() {
    for (int i = 0; i < 3; i++) {
        on(100);  // Turn motor ON at 100% power instantly
        delay(1000);  // Keep it ON for 1 second

        off();  // Turn motor OFF
        delay(100);  // Keep it OFF for 0.1 second
    }
}

// Function to accelerate from 0% to 80% in 2s, then decelerate from 80% to 0% in 2s
void accel_decel3() {
    int stepDelay = 50; // Delay per step (milliseconds)
    int steps = 2000 / stepDelay; // Number of steps in 2 seconds (2000ms)
    int maxPower = 80; // Target power is 80%

    // Accelerate from 0% to 80% in 2 seconds
    for (int power = 0; power <= maxPower; power += (maxPower / steps)) {
        on(power);
        delay(stepDelay);
    }

    // Decelerate from 80% to 0% in 2 seconds
    for (int power = maxPower; power >= 0; power -= (maxPower / steps)) {
        on(power);
        delay(stepDelay);
    }

    off(); // Ensure motor is completely off
}
