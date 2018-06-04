#include "RTClib.h"
#include <Wire.h>

uint8_t time[2];

RTClib::RTClib(){
	Wire.begin();
}

void RTClib::set_time(int hour, int minutes, int seconds){

	byte b[8];

	b[0] = decToBcd(seconds);
	b[1] = decToBcd(minutes);
	b[2] = decToBcd(hour);


	// Turn off oscillator
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x00);
	Wire.write(0x00);

	// set the minutes
	Wire.write(b[1]);

	// set the hour
	Wire.write(b[2]);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.endTransmission();

	// set the seconds and turn on the oscillator
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x00);
	Wire.write(0x80 | b[0]);
	Wire.endTransmission();
}

byte* RTClib::get_time(){

	byte b[7];

	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();

	Wire.requestFrom(DEVICE_ADDRESS, 12);
	b[0] = Wire.read()& 0x7f; 
	b[1] = Wire.read()& 0x7f; 
	b[2] = Wire.read()& 0x6f; 
	b[3] = Wire.read()& 0x03; 
	b[4] = Wire.read()& 0x3f; 
	b[5] = Wire.read()& 0x1f; 
	b[6] = Wire.read()& 0xff;


	return b;
}

void RTClib::set_alarm(int time_offset){
	byte b[7];

	// get the current date/time
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();

	Wire.requestFrom(DEVICE_ADDRESS, 12);
	b[0] = Wire.read()& 0x7f; 
	b[1] = Wire.read()& 0x7f; 
	b[2] = Wire.read()& 0x6f; 
	b[3] = Wire.read()& 0x03; 
	b[4] = Wire.read()& 0x3f; 
	b[5] = Wire.read()& 0x1f; 
	b[6] = Wire.read()& 0xff;

	//set the alarm mask
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x0D);
	Wire.write(0x70);

	Wire.endTransmission();

	// TODO: catch the case where the seconds/minutes/hours rolls over at midnight
	// and therefore the alarm will not be reached


	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x0a);

	Wire.write(0x50);
	Wire.write(0x05);
	Wire.write(0x00);
	Wire.endTransmission();


	delay(10);
	//enable alarm ALM0
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x07);
	Wire.write(0x10);
	Wire.endTransmission();


}


uint8_t RTClib::decToBcd(uint8_t val)
{
  return ( (val/10*16) + (val%10) );
}

uint8_t RTClib::bcdToDec(uint8_t val)
{
  return ( (val/16*10) + (val%16) );
}