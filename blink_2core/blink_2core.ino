#define LED_0  2
#define LED_1  3

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_0,OUTPUT);

}

void setup1() {
  // put your setup code here, to run once:
  pinMode(LED_1,OUTPUT);

}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_0,LOW);
  delay(500);
  digitalWrite(LED_0,HIGH);
  delay(500);
}

void loop1() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_1,LOW);
  delay(100);
  digitalWrite(LED_1,HIGH);
  delay(100);
}
