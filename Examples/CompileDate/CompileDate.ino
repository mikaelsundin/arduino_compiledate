/*
 Name:		CompileDate.ino
 Created:	2021-01-03 15:35
 Author:	Mikael Sundin
*/
#include <time.h>
#include <EEPROM.h>
#include <arduino_compiledate.h>

/**
 * @Brief Code for updating a RTC based on compiletime.
 * @Note This takes 4 bytes in eeprom to save last timestamp.
 *   The compileTime should match the compiletime to get a accurate timing.
 */
void checkCompileTime(uint32_t eeAdr = 2, uint32_t compileTime = 5) {
  time_t timestamp = CompileDate::parseGccDateTime(F(__DATE__), F(__TIME__), compileTime);
	time_t lastTimestamp;

	//Use simple hash to see if we have recompiled the sketch.
	EEPROM.get(eeAdr, lastTimestamp);
	if (lastTimestamp != timestamp) {
		EEPROM.put(eeAdr, timestamp);
		Serial.println("Compile time changed");

    //convert to YYYY MM DD HH MM SS struct.
		tm* rtc = gmtime(&compileTime);

		//Run code here to setup a RTC.
		//Update RTC here settings

	}
	else 
	{
		Serial.println("Compile time unchanged.");

	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
}


//Test library, try both compile and upload and reset button on the arduino board.
void loop() {
	delay(1000);
	checkCompileTime(0x002);
}
