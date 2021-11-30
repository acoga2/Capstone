/* This is the demo version of the header file for RBDS_Decoder_V1.cpp.
 * In order for the decoder to be included in Arduino as a custom library, 
 * a header file containing declarations and definitions of all necessary
 * functions and variables is necessary. 
 */
 
// The Arduino versions of both the header and .cpp files are located in .../Documents/Arduino/libraries/RBDS_Decoder

#ifndef _RDSDECODER_H_INCLUDED // Don't redefine this header if it's already defined
#define _RDSDECODER_H_INCLUDED

#if defined(__GNUC__)
# if defined(__AVR__)

#  define __STDC_FORMAT_MACROS
#  define __STDC_LIMIT_MACROS

#  if defined(ARDUINO) && ARDUINO >= 100 // If program is run through Arduino
#   include <Arduino.h>
// #   define string String // In Arduino, the std::string variable is instead defined as String
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

// Functions are declared here
uint8_t get_group_type(unsigned int blockB);
bool get_TP(unsigned int blockB);
std::string get_PTY(unsigned int blockB);
std::string get_PI(unsigned int blockA);
char num2letter(unsigned int n);
char hex2letter(unsigned int n);
char get_RadioText(unsigned int blockX, unsigned int blockB, bool check_char);
void BCD_to_char(uint8_t BCD, char *text);

#endif