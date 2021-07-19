int led = 2;
int n = 3;
int dly =15; void setup(){ // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(led,HIGH);
if (n==1){
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,LOW);
  delay(dly);
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,LOW);
  delay(dly);
}
if (n==2){
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,LOW);
  delay(dly);
  digitalWrite(led,LOW);
  delay(dly);
}
if (n==3){
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,HIGH);
  delay(dly);
  digitalWrite(led,LOW);
  delay(dly);
}
}
