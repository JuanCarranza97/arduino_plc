#define SDA     2
#define SCL     3

void setup() {
  Serial.begin(115200);
  pinMode(SDA,OUTPUT);
  pinMode(SCL,OUTPUT);

  digitalWrite(SDA,HIGH);
  digitalWrite(SCL,HIGH);
}

void loop() {
  if(Serial.available()){
    int output = Serial.parseInt();
    int value = Serial.parseInt();
    int data = (output<<7) | (value);
    Serial.println("Mandando");
    Serial.print("  Out: "+String(output)+", Val: "+String(value)+" -->0x");
    Serial.print(data,HEX);
    Serial.print(",0b");
    Serial.print(data,BIN);
    Serial.println(" a el PLC... ");
    delay(500);
    send_data(data);
    Serial.println("DONE");
  }
}

void send_data(int x){
  digitalWrite(SDA,LOW);
  delay(500);
  digitalWrite(SCL,LOW);
  delay(500);
  for(int i=0;i<10;i++){
    digitalWrite(SDA,(x&(1<<i))>>i);
    delay(250);
    digitalWrite(SCL,HIGH);
    delay(250);
    digitalWrite(SCL,LOW);
    delay(250);
    digitalWrite(SDA,LOW);
    delay(250);
  }
  digitalWrite(SCL,HIGH);
  delay(250);
  digitalWrite(SDA,HIGH);
  delay(250);
  
}
