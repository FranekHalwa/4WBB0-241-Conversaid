#define volumePin 3
#define trigPin 8
#define echoPin 9

long volume;
long duration;
long distance;
int threshold_distance = 150;

String msg;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(volumePin, INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Conversaid Test Serial Data");
  msg = "";
}

void loop() {
  // put your main code here, to run repeatedly:
  // send a pulse from the US sensor to measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // calculate distance from duration of pulse and speed of sounds wave through air
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2.0;

  // read volume level
  volume = digitalRead(volumePin);

  // Detect if any BlueTooth command is sent
  if (Serial1.available() > 0) {
    msg = Serial1.readString();
    Serial.println("Android command: " + msg);
    if (msg=="LOW") {
      threshold_distance = 75; 
    }
    if (msg=="HIGH") {
      threshold_distance = 150;
    }
    Serial.println(threshold_distance + "!");
    
  }
  if(distance<threshold_distance) {
    Serial1.println("distance breach\n");
    Serial.print("distance breach, ");
    Serial.println(threshold_distance);
  }
  if(volume==HIGH) {
      Serial1.println("volume breach\n");
      Serial.println("volume breach");
    }

   delay(200);
}
