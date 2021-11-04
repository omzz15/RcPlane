#include <Arduino.h>
#include <plane.cpp>
#include <controller.cpp>
#include <EnableInterrupt.h>

#define outPin 3
int out = 0;

Controller controller;

void calcCH1(){controller.CH1.calcInput();}
void calcCH2(){controller.CH2.calcInput();}
void calcCH3(){controller.CH3.calcInput();}
void calcCH4(){controller.CH4.calcInput();}
void calcCH5(){controller.CH5.calcInput();}
void calcCH6(){controller.CH6.calcInput();}

void setup()
{
	Serial.begin(9600);
	controller = Controller();

	enableInterrupt(controller.CH1.getPin(), calcCH1, CHANGE);
	enableInterrupt(controller.CH2.getPin(), calcCH2, CHANGE);
	enableInterrupt(controller.CH3.getPin(), calcCH3, CHANGE);
	enableInterrupt(controller.CH4.getPin(), calcCH4, CHANGE);
	enableInterrupt(controller.CH5.getPin(), calcCH5, CHANGE);
	enableInterrupt(controller.CH6.getPin(), calcCH6, CHANGE);

	pinMode(outPin, OUTPUT);
}



void loop()
{
	if(!controller.isAllStarted()){
		out = 0;
		analogWrite(outPin, out);
	while(!controller.isAllStarted()){
		Serial.println("connect controller!!");
		delay(100);
	}
	}

	if(!controller.isAllAlive()){
		out = 0;
		analogWrite(outPin, out);
	while(!controller.isAllAlive()){
		Serial.println("connect controller!!");
		delay(100);
	}
	}

	if(controller.CH3.hasNewData()){
		out = constrain((controller.CH3.getValue() + 0.95) * 135, 0, 255);
		Serial.print("output: ");
		Serial.println(out);
	}

	analogWrite(outPin, out);

/*
	if(controller.allNewDataAvalible()){
	Serial.print(controller.CH1.getValue());
	Serial.print("\t");
	Serial.print(controller.CH2.getValue());
	Serial.print("\t");
	Serial.print(controller.CH3.getValue());
	Serial.print("\t");
	Serial.print(controller.CH4.getValue());
	Serial.print("\t");
	Serial.print(controller.CH5.getValue());
	Serial.print("\t");
	Serial.println(controller.CH6.getValue());
	}

	delay(100);
*/
}