#include <Time.h>
#include "arduino_compiledate.h"


static uint32_t hash(unsigned char* str);
static uint8_t parseMonth(const char* str);

/**
 * @brief djb2 Hash algoritm, simple hashing algoritm.
 */
static uint32_t hash(unsigned char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
		
	return hash;
}

/**
 * @brief Convert 3 char month format. Example Jan, Feb, Nov, Dec.
 * @return Number between 0 and 11.
 */
uint8_t parseMonth(const char* str) {
	uint8_t sum = str[0] + str[1] + str[2];

	switch (sum) {
	case 0x19: return 0;
	case 0x0D: return 1;
	case 0x20: return 2;
	case 0x23: return 3;
	case 0x27: return 4;
	case 0x2D: return 5;
	case 0x2B: return 6;
	case 0x1D: return 7;
	case 0x28: return 8;
	case 0x26: return 9;
	case 0x33: return 10;
	case 0x0C: return 11;
	default: return 0;
	}
}


/**
 * @brief Parse Gcc __DATE__ and __TIME__ and fill in fm struct.
 * @note This does not fill year of day(tm_yday) or day of week(tm_wday).
 */
time_t CompileDate::parseGccDateTime(const __FlashStringHelper* f_date, const __FlashStringHelper* f_time, uint32_t offset) {
	struct tm result;

	char dstr[12];
	char tstr[9];

	memcpy_P(dstr, f_date, 12); //Jan DD YYYY
	memcpy_P(tstr, f_time, 9);  //12:12:12

	//Extract Date part
	dstr[3] = '\0';
	dstr[6] = '\0';
	dstr[11] = '\0';
	result.tm_mon = parseMonth(&dstr[0]);
	result.tm_mday = atoi(&dstr[4]);
	result.tm_year = atoi(&dstr[7]) - 1900;

	//Extract Time part.
	tstr[2] = '\0';
	tstr[5] = '\0';
	result.tm_hour = atoi(&tstr[0]);
	result.tm_min = atoi(&tstr[3]);
	result.tm_sec = atoi(&tstr[6]);
	
	//Clear not used fields.
	result.tm_isdst = 0;
	result.tm_wday = 0;
	result.tm_yday = 0;

	//Create arduino time_t
	return mktime(&result);
}


/**
 * @brief Perform simple hashing of __DATE__ and __TIME__
 */
uint32_t CompileDate::hashGccDateTime(const __FlashStringHelper* f_date, const __FlashStringHelper* f_time) {
	unsigned char dstr[12];
	unsigned char tstr[9];

	//copy from flash area.
	memcpy_P(dstr, f_date, 12); //Jan DD YYYY
	memcpy_P(tstr, f_time, 9);  //12:12:12

	//hash date and time
	return hash(dstr) ^ hash(tstr);
}
