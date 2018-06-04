/*
	Library for the control of the MCP7940M chip
*/


#ifndef RTClib_h

#define RTClib_h
#include "Arduino.h"
#include "Wire.h"

// start code = 1101
// next 3 bits are 111
// last bit = 0 for write and 1 for read


/*
	Device Address
*/

#define DEVICE_ADDRESS 0x6F

/*
	Register Addresses
*/

#define CONTROL 0x07

// Timekeeping
#define RTCSEC 0x00
#define RTCMIN 0x01
#define RTCHOUR 0x2
#define RTCWDAY 0x03
#define RTCDATE 0x04
#define RTCMTH 0x05
#define RTCYEAR 0x06

//Alarms
#define ALM0SEC 0x0A
#define ALM0MIN 0x0B
#define ALM0HOUR 0x0C
#define ALM0WKDAY 0x0D
#define ALM0DATE 0x0E
#define ALM0MTH 0x0F

#define ALM1SEC 0x11
#define ALM1MIN 0x12
#define ALM1HOUR 0x13
#define ALM1WKDAY 0x14
#define ALM1DATE 0x15
#define ALM1MTH 0x16

class RTClib{
	public:
		RTClib::RTClib();

		/*
			set the current time
			args: year, month, day, hour(in 24 hours), minutes, seconds
		*/

		void RTClib::set_time(int hour, int minutes, int seconds);

		byte* RTClib::get_time();

		/*
			set an alarm from a set amount of seconds from the current time.
			argument is the time in the future in seconds
		*/

		void RTClib::set_alarm(int time_offset);

	private:
		uint8_t RTClib::decToBcd(uint8_t val);
		uint8_t RTClib::bcdToDec(uint8_t val);

};

#endif