/**
 * RTC Library for DS1307 and DS3231 based from uRTCLib by Naguissa
 *
 *
 * @copyright trettet
 * @author trettet
 * @email trettet@gmail.com
 * @version 0.1 alpha
 * @created 2015-05-07
 * @forked 2017-08-24
 */
#include <Arduino.h>
#include "M3liusRTC.h"

M3liusRTC::M3liusRTC() {
	#ifndef _VARIANT_ARDUINO_STM32_
	  Wire.begin();
	#endif
	//  refresh();
}


void M3liusRTC::refresh() {
	#ifdef _VARIANT_ARDUINO_STM32_
		URTCLIB_INIT_WIRE();
	#endif
	Wire.beginTransmission(_rtc_address);
	Wire.write(0); // set DS3231 register pointer to 00h
	Wire.endTransmission();
	Wire.requestFrom(_rtc_address, 7);
	// request seven uint8_ts of data starting from register 00h
	_second = Wire.read();
	_second = uRTCLIB_bcdToDec(_second);
	_minute = Wire.read();
	_minute = uRTCLIB_bcdToDec(_minute);
	_hour = Wire.read() & 0b111111;
	_hour = uRTCLIB_bcdToDec(_hour);
	_dayOfWeek = Wire.read();
	_dayOfWeek = uRTCLIB_bcdToDec(_dayOfWeek);
	_day = Wire.read();
	_day = uRTCLIB_bcdToDec(_day);
	_month = Wire.read();
	_month = uRTCLIB_bcdToDec(_month);
	_year = Wire.read();
	_year = uRTCLIB_bcdToDec(_year);
}


byte M3liusRTC::second() {
	return _second;
}

byte M3liusRTC::minute() {
	return _minute;
}

byte M3liusRTC::hour() {
	return _hour;
}

byte M3liusRTC::day() {
	return _day;
}

byte M3liusRTC::month() {
	return _month;
}

byte M3liusRTC::year() {
	return _year;
}

byte M3liusRTC::dayOfWeek() {
	return _dayOfWeek;
}

void M3liusRTC::set_rtc_address(int addr) {
	_rtc_address = addr;
}


#ifdef URTCLIB_SET
	void M3liusRTC::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
		#ifdef _VARIANT_ARDUINO_STM32_
			URTCLIB_INIT_WIRE();
		#endif
		Wire.beginTransmission(_rtc_address);
		Wire.write(0); // set next input to start at the seconds register
		Wire.write(uRTCLIB_decToBcd(second)); // set seconds
		Wire.write(uRTCLIB_decToBcd(minute)); // set minutes
		Wire.write(uRTCLIB_decToBcd(hour)); // set hours
		Wire.write(uRTCLIB_decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
		Wire.write(uRTCLIB_decToBcd(dayOfMonth)); // set date (1 to 31)
		Wire.write(uRTCLIB_decToBcd(month)); // set month
		Wire.write(uRTCLIB_decToBcd(year)); // set year (0 to 99)
		Wire.endTransmission();
	}
#endif


#ifdef URTCLIB_EEPROM
	void M3liusRTC::set_ee_address(int addr) {
		_ee_address = addr;
	}

	unsigned char M3liusRTC::eeprom_read(const unsigned int address) {
		unsigned int rdata = 0xFF;
		#ifdef _VARIANT_ARDUINO_STM32_
			URTCLIB_INIT_WIRE();
		#endif
		Wire.beginTransmission(_ee_address);
		Wire.write((int)(address >> 8)); // MSB
		Wire.write((int)(address & 0xFF)); // LSB
		Wire.endTransmission();
		Wire.requestFrom(_ee_address, 1);
		if (Wire.available()) {
			rdata = Wire.read();
		}
		return rdata;
	}

	void M3liusRTC::eeprom_write(const unsigned int address, const unsigned char data) {
		#ifdef _VARIANT_ARDUINO_STM32_
			URTCLIB_INIT_WIRE();
		#endif
		Wire.beginTransmission(_ee_address);
		Wire.write((int)(address >> 8)); // MSB
		Wire.write((int)(address & 0xFF)); // LSB
		Wire.write(data);
		delay(5); // Little delay to assure EEPROM is able to process data; if missing and inside for look meses some values
		Wire.endTransmission();
	}
#endif

// Private Utility Functions
byte M3liusRTC::decToBcd(byte val) {
	return ( (val/10*16) + (val%10) );
}

byte M3liusRTC::bcdToDec(byte val) {
	return ( (val/16*10) + (val%16) );
}


