class ImuSettings{
	
};

class Imu{

};


/*
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu;
#define loopDelay 10
bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
unsigned long time;

Quaternion q;
VectorFloat gravity;
float euler[3];
float ypr[3];

volatile bool mpuInterrupt = false;

void dmpDataReady() {	
	mpuInterrupt = true;
}

void giroRefresh() {
	mpuIntStatus = mpu.getIntStatus();
	// get current FIFO count
	fifoCount = mpu.getFIFOCount();
	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		Serial.println(F("FIFO overflow!, giro descompensat!!"));
		Serial.print("&");
		// otherwise, check for DMP data ready interrupt (this should happen frequently)
	}
	else if (mpuIntStatus & 0x02) {
		Serial.print("%");
		// wait for correct available data length, should be a VERY short wait
		time = millis();
		while ((fifoCount < packetSize) && ((millis() - time) < 2)) {
			Serial.println("|" + (String)((millis() - time) < 2));
			Serial.println((String)(fifoCount < packetSize));
			fifoCount = mpu.getFIFOCount();
		}
		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);

		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;

		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

	}
	mpuInterrupt = false;
}

void giroPrint() {
	Serial.print("ypr\t");
	Serial.print(ypr[0] * 180 / M_PI);
	Serial.print("\t");
	Serial.print(ypr[1] * 180 / M_PI);
	Serial.print("\t");
	Serial.println(ypr[2] * 180 / M_PI);
}
void giroinit() {
	Wire.begin();
	TWBR = 24;
	Serial.println(F("Initializing I2C devices..."));
	mpu.initialize();

	Serial.println(F("Testing device connections..."));
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

	Serial.println(F("Initializing DMP..."));
	devStatus = mpu.dmpInitialize();

	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

	if (devStatus == 0) {
		Serial.println(F("Enabling DMP..."));
		mpu.setDMPEnabled(true);
		Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		attachInterrupt(0, dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		Serial.println(F("DMP ready! Waiting for first interrupt..."));
		dmpReady = true;

		packetSize = mpu.dmpGetFIFOPacketSize();
	}
	else {
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}
}

void setup() {

	Serial.begin(115200);

	giroinit();

}

void loop() {
	//delay(loopDelay);

	if (mpuInterrupt) {
		giroRefresh();
		giroPrint();
	}

}
This code doesn’t:

#include <Arduino.h>//crashes
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu;
#define loopDelay 10
bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
unsigned long time;
// orientation/motion vars
Quaternion q;
VectorFloat gravity;
float euler[3];
float ypr[3];

void dmpDataReady() {	
	giroRefresh();
}
*/