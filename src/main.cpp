#include <Arduino.h>
#include <plane.cpp>
#include <controller.cpp>
#include <EnableInterrupt.h>

#define outPin 3
int out = 0;

Controller controller;

void calcCH1(){controller.getChannel(1).calcInput();}
void calcCH2(){controller.getSettings().CH2.calcInput();}
void calcCH3(){controller.getSettings().CH3.calcInput();}
void calcCH4(){controller.getSettings().CH4.calcInput();}
void calcCH5(){controller.getSettings().CH5.calcInput();}
void calcCH6(){controller.getSettings().CH6.calcInput();}

void setup()
{
	Serial.begin(9600);
	controller = Controller();

	enableInterrupt(controller.getSettings().CH1.getPin(), calcCH1, CHANGE);
	enableInterrupt(controller.getSettings().CH2.getPin(), calcCH2, CHANGE);
	enableInterrupt(controller.getSettings().CH3.getPin(), calcCH3, CHANGE);
	enableInterrupt(controller.getSettings().CH4.getPin(), calcCH4, CHANGE);
	enableInterrupt(controller.getSettings().CH5.getPin(), calcCH5, CHANGE);
	enableInterrupt(controller.getSettings().CH6.getPin(), calcCH6, CHANGE);

	pinMode(outPin, OUTPUT);
}

void loop()
{
	if(!controller.isAllStarted()){
		Serial.println("connect controller!!");
	}

	if(!controller.isAllAlive()){
		Serial.println("connect controller!!");
	}

	if(controller.allNewDataAvalible()){
	Serial.print(controller.getSettings().CH1.getValue());
	Serial.print("\t");
	Serial.print(controller.getSettings().CH2.getValue());
	Serial.print("\t");
	Serial.print(controller.getSettings().CH3.getValue());
	Serial.print("\t");
	Serial.print(controller.getSettings().CH4.getValue());
	Serial.print("\t");
	Serial.print(controller.getSettings().CH5.getValue());
	Serial.print("\t");
	Serial.println(controller.getSettings().CH6.getValue());
	}

	delay(100);
}