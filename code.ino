const int THROTTLE_PIN = 2; //Adjust according to your receiver 
const int STEER_PIN    = 3; //Adjust according to your receiver 

const int ENA = 5, IN1 = 7, IN2 = 8;
const int ENB = 6, IN3 = 9, IN4 = 10;

// Adjust these values to change the steering direction 
const int STEER_GAIN  = -1; 
const int MOTOR_A_DIR =  1;
const int MOTOR_B_DIR = -1;


const int CENTER = 1500;
const int DEADBAND = 30;

int toSpeed(long us) {
  long d = us - CENTER;
  if (abs(d) < DEADBAND) return 0;
  int s = map(us, 1000, 2000, -255, 255);
  return constrain(s, -255, 255);
}

void drive(int en, int a, int b, int speed) {
  speed = constrain(speed, -255, 255);
  digitalWrite(a, speed > 0);
  digitalWrite(b, speed < 0);
  analogWrite(en, abs(speed));
}

void setup() {
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEER_PIN, INPUT);
}

void loop() {
  long th = pulseIn(THROTTLE_PIN, HIGH);
  long st = pulseIn(STEER_PIN, HIGH);

  int throttle = toSpeed(th);
  int steer    = toSpeed(st) * STEER_GAIN;

  int left  = throttle + steer;
  int right = throttle - steer;

  drive(ENA, IN1, IN2, left  * MOTOR_A_DIR);
  drive(ENB, IN3, IN4, right * MOTOR_B_DIR);
}