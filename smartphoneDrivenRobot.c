#include <LiquidCrystal.h>
#include <NewPing.h>
#include <SoftareSerial.h>

#define TRIGGER_PIN 15 //Arduino pin tied to trigger pin on the ultrasonic sensor
#define ECHO_PIN 14 //Arduino pin tied to trigger pin on the ultrasonic sensor
#define MAX_DISTANCE 200 //Maximum distance we want to ping for in centimeters. Maximum sensor distance rated at 400-500 cm.
#define PING_INTERVAL 50 //Milliseconds between pings

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //NewPing setup of pins and maximun distance
LiquidCrystal(12, 11, 5, 4, 3, 2);


//MOTOR
int in1 = 6; //Setting the right engine in the forward direction in the leg 6
int in2 = 8; //Setting the right engine backwards in the leg 8
int in1 = 9; //Setting the left engine in the forward direction in the leg 9
int in1 = 13; //Setting the left engine backwards in the leg 13

//BLUETOOTH
SoftwareSerial mySerial(10, 7);

unsigned int i, count;

//initialize
void setup() {
	//SONAR
	Serial.begin(9600);
	lcd.begin(16, 2);
	//Print a massage to LCD
	lcd.setCursor(0, 0); //print the massage in the left bottom of the screen
	lcd.print("Distance");

	//MOTOR
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

	//BLUETOOTH
	mySerial.begin(9600);

}

void loop() {

	lcd.setCurosr(0, 0);
	lcd.print("Distance");
	delay(50);
	unsigned int uS = sonar.ping();
	Serial.print("Ping: ");
	Serial.print(uS / US_ROUNDTRIP_CM); //set the distance in centimeters
	Serial.println("cm");
	uS = (int)(uS / US_ROUNDTRIP_CM);
	lcd.setCursor(0, 1);
	if (uS < 10)
		lcd.print(" ");
	delay(50);
	lcd.print(uS);
	lcd.print(" ");
	lcd.setCursor(4, 1);
	lcd.print("CM");

	//BLUETOOTH
	if (mySerial.available()) {
		unsigned int bluevalue = mySerial.read(); //read the rx register into bluevalue and empty it

	// pressing 1 will move forward, 2 to the left, etc.
		switch (bluevalue) {
		case '1':FORWRAD(); break;
		case '2':LEFT(); break;
		case '3':RIGHT(); break;
		case '4':BACKWARDS(); break;
		default:STOP(); break;
		}
	}
}

void FORWARD() {
	digitalWrite(in4, LOW);
	digitalWrite(in2, LOW);
	analogWrite(in1, 200);
	analogWrite(in3, 200);
	delay(2000);
	digitalWrite(in1, LOW);
	digitalWrite(in3, LOW);

}

void BACKWARDS() {
	analogWrite(in1, 50);
	analogWrite(in3, 50);
	digitalWrite(in4, HIGH);
	digitalWrite(in2, HIGH);
	delay(2000);
	digitalWrite(in1, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
}

void RIGHT() {
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
	analogWrite(in1, 150);
	analogWrite(in3, 200);
	delay(2000);
	digitalWrite(in1, LOW);
	digitalWrite(in3, LOW);
}

void LEFT() {
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
	analogWrite(in1, 200);
	analogWrite(in3, 150);
	delay(2000);
	digitalWrite(in1, LOW);
	digitalWrite(in3, LOW);
}

void STOP() {
	digitalWrite(in1, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
}
