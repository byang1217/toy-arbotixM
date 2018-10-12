#include <ax12.h>

#define SERVO_MAX 4

// Pin 0 maps to the USER LED on the ArbotiX Robocontroller.
int led = 0;
int loop_count = 0;

void CheckVoltage(){  
	// wait, then check the voltage (LiPO safety)
	float voltage = (ax12GetRegister (1, AX_PRESENT_VOLTAGE, 1)) / 10.0;
	Serial.println("###########################");   
	Serial.print ("System Voltage: ");
	Serial.print (voltage);
	Serial.println (" volts.");
	if (voltage < 10.0){
		Serial.println("Voltage levels below 10v, please charge battery.");
//		while(1);
	}  
	if (voltage > 10.0){
		Serial.println("Voltage levels nominal.");
	}
	Serial.println("###########################"); 
}

void ScanServo(){
	int id;
	int pos;

	Serial.println("###########################");
	Serial.println("Starting Servo Scanning Test.");
	Serial.println("###########################");

	for (id = 1; id < SERVO_MAX; id ++) {
		pos =  ax12GetRegister(id, 36, 2);
		Serial.print("Servo ID: ");
		Serial.println(id);
		Serial.print("Servo Position: ");
		Serial.println(pos);

		if (pos <= 0){
			Serial.println("###########################");
			Serial.print("ERROR! Servo ID: ");
			Serial.print(id);
			Serial.println(" not found. Please check connection and verify correct ID is set.");
			Serial.println("###########################"); 
		}

		delay(50);
	}
}

void RelaxServos(){
	int id;

	Serial.println("###########################");
	Serial.println("Relaxing Servos.");
	Serial.println("###########################");    

	for (id = 1; id < SERVO_MAX; id ++) {
		Relax(id);
		delay(50);
	}
}

void LEDTest(){
	int id;

	Serial.println("###########################");
	Serial.println("Running LED Test");
	Serial.println("###########################");    

	for (id = 1; id < SERVO_MAX; id ++) {
		ax12SetRegister(id, 25, 1);
		Serial.print("LED ON - Servo ID: ");
		Serial.println(id);
		delay(1000);
		ax12SetRegister(id, 25, 0);  
		Serial.print("LED OFF - Servo ID: ");
		Serial.println(id);    
		delay(1000);    
		id = id++;
	}
}

// the setup routine runs once when you press reset:
void setup() {                
	// initialize the digital pin as an output.
	pinMode(led, OUTPUT);     
	Serial.begin(115200);
	CheckVoltage();
	ScanServo();
	LEDTest();
}

// the loop routine runs over and over again forever:
void loop() {
	int inByte = Serial.read();

	loop_count ++;
	Serial.print("loop count: ");
	Serial.println(loop_count);
	Serial.print("input: ");
	Serial.println((char)inByte);
	if (loop_count % 2)
		digitalWrite(led, HIGH);
	else
		digitalWrite(led, LOW);

	

	delay(10); // wait for 10 ms
}
