#include <Arduino.h>
#include <plane.cpp>
#include <controller.cpp>
#include <EnableInterrupt.h>

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
}



void loop()
{
	while(!controller.controllerConnected()){
		Serial.println("connect controller!!");
		delay(1000);
	}

	while(controller.controllerDead()){
		Serial.println("reconnect controller!!");
		delay(500);
	}

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
}