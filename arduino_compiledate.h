#ifndef ARDUINO_COMPILEDATE_H
#define ARDUINO_COMPILEDATE_H

#include "arduino.h"
#include "time.h"

class CompileDate {
public:
    static time_t parseGccDateTime(const __FlashStringHelper* f_date, const __FlashStringHelper* f_time, uint32_t offset=0);
    static uint32_t hashGccDateTime(const __FlashStringHelper* f_date, const __FlashStringHelper* f_time);
};


#endif