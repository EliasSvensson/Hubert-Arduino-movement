#include <Arduino.h>
#include <Servo.h>

Servo servos[6]; // base, head/pan, head/tilt, shoulder, elbow, gripper

const int servo_pins[] = {3, 5, 6, 9, 10, 11};
const int pos_init[] = {1700, 1500, 2000, 2200, 1650, 1600};
const int pos_min[] = {560, 550, 950, 750, 550, 550};
const int pos_max[] = {2330, 2340, 2400, 2200, 2400, 2150};

int curr_pos[6];       // current servo position
int new_servo_val[6];  // servo position to move to

const int delta = 6;            // step size for servo
const int delaytime_short = 80;
const int delaytime_long = 160;  // delay time for servo 

int incomingByte = 0;           // for serial communication (via python)

void update_servo(const int servo_index, const int new_pos) {
  int inter_pos = curr_pos[servo_index];
  int diff = new_pos - inter_pos;
  int sign = (diff >= 0) - (diff < 0);
  int abs_diff = diff*sign;
  
  delay(delaytime_short);
  
  for (int i = 0; i < abs_diff; i += delta) {
    inter_pos += delta*abs_diff;
    servos[servo_index].writeMicroseconds(inter_pos);
    delay(delaytime_long);
  }
  curr_pos[servo_index] = inter_pos;
  delay(delaytime_short);
  
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(57600); // Starts the serial communication
  pinMode(LED_BUILTIN, OUTPUT); // enable the on-board led for feedback
  
  // attach servos and init arrays
  for(int i = 0; i < 6; i++) {
    servos[i].attach(servo_pins[i]);
    servos[i].writeMicroseconds(pos_init[i]);
    curr_pos[i] = pos_init[i];
    new_servo_val[i] = pos_init[i];
  }

  delay(2000);
}

void loop() {
  delay(4000);
  //update_servo(5, pos_max[5]-300);
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  }
  if (incomingByte > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}
