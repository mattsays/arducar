#define IR_SENSOR_LEFT 8
#define IR_SENSOR_RIGHT 8

#define IR_STOP 21
#define IR_FORWARD 17
#define IR_BACK 25
#define IR_LEFT 20
#define IR_RIGHT 22

#define RB_MOTOR_A 1
#define RB_MOTOR_B 0

#define RB_MOTOR 0

#define LB_MOTOR_A 2
#define LB_MOTOR_B 3

#define LB_MOTOR 1

#define LF_MOTOR_A 4
#define LF_MOTOR_B 5

#define LF_MOTOR 2

#define RF_MOTOR_A 6
#define RF_MOTOR_B 7

#define RF_MOTOR 3

#define STOP 0
#define FORWARD 1
#define BACK 2
#define TURN_LEFT 3
#define TURN_RIGHT 4

// This functions handles the single motor behaviour by applying voltage to one pin or another 
// accordingly to the motor direction
void motor_control(int motor, int movement) {

  int motor_a = 0;
  int motor_b = 0;

  if(movement == FORWARD) {
    motor_a = 0;
    motor_b = 1;
  } else if(movement == BACK) {
    motor_a = 1;
    motor_b = 0;
  } else if(movement == STOP) {
    motor_a = 0;
    motor_b = 0;
  }

  switch(motor) {
    case RB_MOTOR:
      digitalWrite(RB_MOTOR_A, motor_a);
      digitalWrite(RB_MOTOR_B, motor_b);
      break;
      
    case LB_MOTOR:
      digitalWrite(LB_MOTOR_A, motor_a);
      digitalWrite(LB_MOTOR_B, motor_b);
      break;
      
    case RF_MOTOR:
      digitalWrite(RF_MOTOR_A, motor_a);
      digitalWrite(RF_MOTOR_B, motor_b);
      break;
      
    case LF_MOTOR:
      digitalWrite(LF_MOTOR_A, motor_a);
      digitalWrite(LF_MOTOR_B, motor_b);
      break;
  }
  
}

// Cool function to handle better the movement of the car without using redundant lines of code
void car_move(int movement) {
  switch(movement) {
    case STOP:
      motor_control(LF_MOTOR, STOP);
      motor_control(RF_MOTOR, STOP);
      motor_control(LB_MOTOR, STOP);
      motor_control(RB_MOTOR, STOP);
      break;
    case FORWARD:
      motor_control(LF_MOTOR, FORWARD);
      motor_control(RF_MOTOR, FORWARD);
      motor_control(LB_MOTOR, FORWARD);
      motor_control(RB_MOTOR, FORWARD);
      break;
    case BACK:
      motor_control(LF_MOTOR, BACK);
      motor_control(RF_MOTOR, BACK);
      motor_control(LB_MOTOR, BACK);
      motor_control(RB_MOTOR, BACK);
      break;
    case TURN_LEFT:
      motor_control(LF_MOTOR, BACK);
      motor_control(LB_MOTOR, BACK);
      motor_control(RF_MOTOR, FORWARD);
      motor_control(RB_MOTOR, FORWARD);
      break;
    case TURN_RIGHT:
      motor_control(LF_MOTOR, FORWARD);
      motor_control(LB_MOTOR, FORWARD);
      motor_control(RF_MOTOR, BACK);
      motor_control(RB_MOTOR, BACK);
      break;
  }
  
}

// Registering all pins with all their functions
void setup() {
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
    
    pinMode(RB_MOTOR_A, OUTPUT);
    pinMode(RB_MOTOR_B, OUTPUT);
    digitalWrite(1, 1);

    pinMode(RF_MOTOR_A, OUTPUT);
    pinMode(RF_MOTOR_B, OUTPUT);

    pinMode(LB_MOTOR_A, OUTPUT);
    pinMode(LB_MOTOR_B, OUTPUT);

    pinMode(LF_MOTOR_A, OUTPUT);
    pinMode(LF_MOTOR_B, OUTPUT);

    pinMode(IR_SENSOR_LEFT, INPUT);
    pinMode(IR_SENSOR_RIGHT, INPUT);
    delay(5000);
    digitalWrite(13, 0);
}

bool sensor_left = 0;
bool sensor_right = 0;


// In this function sensors data is readed and inverted because we need to know when the sensors are on the black tape.
void loop() {
    sensor_left = !digitalRead(IR_SENSOR_LEFT);
    sensor_right = !digitalRead(IR_SENSOR_RIGHT);

    // If both sensors are on black tape it means that arducar is on final part of the track, 
    // otherwise it is moved accordingly to the sensor data
    if(sensor_left && sensor_right) {
        car_move(STOP);
    } else {
        if(sensor_left) {
            car_move(TURN_RIGHT);
        } else if(sensor_right) {
            car_move(TURN_LEFT);
        } else {
            car_move(FORWARD);
        }
    }
}
