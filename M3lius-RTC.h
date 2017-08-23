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
#ifndef URTCLIB
	#define URTCLIB
	#include "Arduino.h"
	#include "Wire.h"
	/*
	RTC I2C Address:
	DS3231 ROM 0x57
	DS3231 RTC 0x68
	*/
	#define URTCLIB_ADDRESS 0x68
	#define URTCLIB_EE_ADDRESS 0x57

	//Comment to disable RTC-setting function
	#define URTCLIB_SET

	//Comment to disable EEPROM functionality
	#define URTCLIB_EEPROM

	#ifdef _VARIANT_ARDUINO_STM32_
		#define URTCLIB_INIT_WIRE() if (_do_init) { _do_init = false; Wire.begin(); }
	#endif


	class M3liusRTC {
		public:
			M3liusRTC();
			byte second();
			byte minute();
			byte hour();
			byte day();
			byte month();
			byte year();
			byte seconds();
			byte dayOfWeek();
			void refresh();
			void set_rtc_address(int);

			#ifdef URTCLIB_SET
				void set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
			#endif

			#ifdef URTCLIB_EEPROM
				void set_ee_address(int);
				unsigned char eeprom_read(const unsigned int address);
				void eeprom_write(const unsigned int address, const unsigned char data);
			#endif

		private:
			int _rtc_address = URTCLIB_ADDRESS;
			#ifdef URTCLIB_EEPROM
				int _ee_address = URTCLIB_EE_ADDRESS;
			#endif
		
			byte _second = 0;
			byte _minute = 0;
			byte _hour = 0;
			byte _day = 0;
			byte _month = 0;
			byte _year = 0;
			byte _dayOfWeek = 0;
			#ifdef _VARIANT_ARDUINO_STM32_
				bool _do_init = true;
			#endif
            
            //Private Utility Functions
            
            // Converts normal decimal numbers to binary coded decimal
            byte decToBcd(byte val);
            
            // Convert binary coded decimal to normal decimal numbers
            byte bcdToDec(byte val);
	};
#endif
