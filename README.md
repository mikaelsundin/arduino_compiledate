# arduino_compiledate
A simple Arduino library for converting compile date and time to be used to setup a RTC timer.

# Usage Example
#include <time.h>
#include "CompileDate.h"

void checkCompileTime(uint32_t eeAdr = 2, uint32_t compileTime = 5) {
	uint32_t lastHash;
	uint32_t hash = CompileDate::parseGccDateTime(F(__DATE__), F(__TIME__));

	//Use simple hash to see if we have recompiled the sketch.
	EEPROM.get(eeAdr, lastHash);
	if (lastHash != hash) {
		EEPROM.put(eeAdr, hash);
		Serial.println("Compile time changed");

		time_t compileTime = CompileDate::parseGccDateTime(F(__DATE__), F(__TIME__), compileTime);
		tm* rtc = gmtime(&compileTime);

		//Run code here to setup a RTC.
		//Update RTC here settings

	}
	else 
	{
		Serial.println("Compile time unchanged.");

	}
}

void setup(){
    checkCompileTime();
}

void loop(){

}