#define NUM_OF_PINS 4 //Number of lights

int SWITCH_IN = 2; //Connection of Reed Switch
int    pins[] = {4,  9,  10,  12}; //Pins for lights
double rpms[] = {9, 50, 110, 230}; //RPM for each light (must be low to high)

unsigned long lastTime = 0;
int level = 0;
boolean lastSw = false;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_IN, INPUT);
  
  for (int i = 0; i < NUM_OF_PINS; i++) {
    pinMode(pins[i], OUTPUT);
  }
  
}

double toRPM(double m) {
  return (60.0 * 1000.0) / m;
}

void loop() {
  unsigned long currTime = millis();
  
  double rpm = toRPM(currTime - lastTime);
  if (level >= 0 && rpm < rpms[level])
    level--;
  
  
  for (int i = 0; i < NUM_OF_PINS; i++)
    digitalWrite(pins[i], LOW);
  
  for (int i = 0; i <= level; i++) {
      digitalWrite(pins[i], HIGH);
  }
  
  boolean sw = digitalRead(SWITCH_IN);
  if (sw && (!lastSw) && (currTime - lastTime > 10)) {
    long diff = currTime - lastTime;
    lastTime = currTime;
    if ((level < NUM_OF_PINS - 1) && (toRPM(diff) > rpms[level+1]))
      level++;
    
  }
  lastSw = sw;
  
  Serial.println(rpm);
}
