
#define SDA     2
#define SCL     3

void setup() {
  Serial.begin(115200);
  pinMode(SDA,INPUT);
  pinMode(SCL,INPUT);
  pinMode(13,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SDA),data_change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SCL),clock_falling, FALLING);
}

void loop() {
  digitalWrite(13,digitalRead(SDA));
}

void data_change(void){
  Serial.println("Data change");

}

void clock_falling(void){
  delay(1);
  Serial.println("Clock falling -->"+String(digitalRead(SCL)));
}
