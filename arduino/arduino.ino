#define SDA     2
#define SCL     3

bool receiving_data = false;
int data,bit_counter;
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
  if(digitalRead(SCL) == HIGH){
    if(digitalRead(SDA) == LOW && receiving_data == false) {
      Serial.print("Iniciando comunicacion ... ");
      data=0;
      bit_counter=0;
      receiving_data = true;
    }else{
      Serial.println("Terminando comunicacion, DATA: "+String(data));
      data_completion(data);
      receiving_data=false;
    }
  }

}

void clock_falling(void){
  if(receiving_data){
    if(bit_counter != 0){
      bool bit_value=digitalRead(SDA);
      Serial.println("Adding "+String(bit_value));
      data+=(bit_value<<(bit_counter-1));
    }else{
      Serial.println("DONE");
    }
    bit_counter++;
  }
}

void data_completion(int x){
  Serial.print("===== Data completion: 0x");
  Serial.print(x,HEX);
  Serial.print(", 0b");
  Serial.print(x,BIN);
  Serial.println(" =====");
  int output= (x&(0x380))>>7;
  int value = x&(0x7F);
  Serial.println("  Output: "+String(output));
  Serial.println("   Value: "+String(value));
  
}
