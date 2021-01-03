# arduino_compiledate
A simple Arduino library for converting compile date and time to be used to setup a RTC timer.

# Usage Example
<pre><code>
#include <time.h>
#include "CompileDate.h"

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

void setup(){
    checkCompileTime();
}

void loop(){

}
</code></pre>
