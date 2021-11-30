/* This is the Arduino version of the header file for RBDS_Decoder_V1.cpp.
 * In order for the decoder to be included in Arduino as a custom library, 
 * a header file containing declarations and definitions of all necessary
 * functions and variables is necessary. 
 */

#ifndef _RDSDECODER_H_INCLUDED // Don't redefine this header if it's already defined
#define _RDSDECODER_H_INCLUDED

#if defined(__GNUC__)
# if defined(__AVR__)

#  define __STDC_FORMAT_MACROS
#  define __STDC_LIMIT_MACROS

#  if defined(ARDUINO) && ARDUINO >= 100 // If program is run through Arduino
#   include <Arduino.h>
#  else
#   include <WProgram.h>
#  endif

# elif defined(__i386__) || defined(__x86_64__) // If program is run through Windows terminal
#  include <stdint.h>
#  include <stddef.h>
#  include <stdbool.h>
#  define word uint16_t
#  define byte uint8_t
# endif

#else
# warning Unsupported compiler detected! // If this message displays, something is very wrong
#endif

// Any external variables are defined here
// DO NOT define main/function-specific vars in the header file
/* unsigned int block[4];
String PI_country;
String PI_code;
uint8_t group_type;
bool TP_code;
String PTY_code;
String RadioText_part;
uint8_t TS_addr; */

// Functions are declared here
uint8_t get_group_type(unsigned long blockB);
bool get_TP(unsigned long blockB);
String get_PTY(unsigned long blockB);
String get_PI(unsigned long blockA);
char num2letter(unsigned long n);
char hex2letter(unsigned long n);
char get_RadioText(unsigned long blockX, unsigned long blockB, bool check_char);
void BCD_to_char(uint8_t BCD, char *text);

#endif
