/* This is the demo version of the RBDS decoder component of the FM/AM radio receiver.
 * The code is designed to take in a single group (104 bits) of encoded, synchronized RBDS data.
 * This data should be passed in as an array four 26-bit blocks.
 * It then outputs basic information of this group (PI code, PTY code, music info, etc...).
 * depending on the design of the receiver, a synchronizer program may be necessary.
 */ 
 
// TO COMPILE AND TEST THIS PROGRAM, TYPE IN TERMINAL: 
// cd "C:Users/dcoga/OneDrive/Documents/Notes F21/ECEN 403 904/Radio_Main/RBDS_Decoder/Demo_Ver"
// g++ -std=c++17 -o RBDS_Decoder_V1 RBDS_Decoder_V1.cpp
// ./RBDS_Decoder_V1
 
// iostream should NOT be included in the 404 version (no more interfacing with the terminal)
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/* ***TODO: MUST include a header file vith variable and function declarations to work with Arduino */
#include "RBDS_Decoder_V1.h"

#define PROGMEM
#define PGM_P const char *
#define __STDC_FORMAT_MACROS

// For bit logic and operations (currently unused)
/* #define lowByte(x) (uint8_t)((x) & 0xFF)
#define highByte(x) (uint8_t)(((x) >> 8) & 0xFF)
#define pgm_read_byte(x) (uint8_t)(*x)
#define pgm_read_word(x) (uint16_t)(*x)
#define pgm_read_ptr(x) (void *)(*x) */

using namespace std;

// Decode the 5-bit group type from block B. Defines the format and contents of blocks C & D
uint8_t get_group_type(unsigned int blockB) {
	
	// Need these bits: 00000011111000000000000000000000
	uint8_t group_type = (blockB & 0x03E00000) >> 21; // Of block bits 25-0, group_type is bits 25-21 (5 bits)
	cout << "Group type: " << unsigned(group_type) << endl;
	
	// Print the group type in correct format for demo purposes
	unsigned int gt_demo = 0;
	if (group_type % 2 == 0) {
		gt_demo = group_type / 2;
		cout << "Formatted group type: " << gt_demo << "A" << endl;
	}
	else {
		gt_demo = (group_type - 1) / 2;
		cout << "Formatted group type: " << gt_demo << "B" << endl;
	}
	
	return group_type;
}

// Retrieve the 1-bit TP (traffic program) code from block B 
bool get_TP(unsigned int blockB) {
	// Need this bit: 00000000000100000000000000000000
	bool TP_code = (blockB & 0x00100000) >> 20;
	cout << "TP = " << TP_code << endl;
	
	return TP_code;
}

// Decodes PTY (program type) code from 5 bits of block B
string get_PTY(unsigned int blockB) {
	// Need these bits: 00000000000011111000000000000000
	uint8_t PTY_bits = (blockB & 0x000F8000) >> 15;
	string PTY_code = "undef";
	bool length_16 = true; // false for 8-char display, true for 16-char display
	
	// Convert 5-bit code into 8- or 16-character string based on RBDS standard
	switch(unsigned(PTY_bits)) {
		case 0x1 : 
			PTY_code = "News";
			break;
		case 0x2 : 
			if (length_16) 
			PTY_code = "Information"; // <= 16-char version
			else PTY_code = "Inform"; // <= 8-char version
			break;
		case 0x3 : 
			PTY_code = "Sports";
			break;
		case 0x4 : 
			PTY_code = "Talk";
			break;
		case 0x5 : 
			PTY_code = "Rock";
			break;
		case 0x6 : 
			if (length_16) 
			PTY_code = "Classic_Rock";
			else PTY_code = "Cls_Rock";
			break;
		case 0x7 : 
			if (length_16) 
			PTY_code = "Adult_Hits";
			else PTY_code = "Adlt_Hit";
			break;
		case 0x8 : 
			if (length_16) 
			PTY_code = "Soft_Rock";
			else PTY_code = "Soft_Rck";
			break;
		case 0x9 : 
			PTY_code = "Top_40";
			break;
		case 0xA : 
			PTY_code = "Country";
			break;
		case 0xB : 
			PTY_code = "Oldies";
			break;
		case 0xC : 
			PTY_code = "Soft";
			break;
		case 0xD : 
			if (length_16) 
			PTY_code = "Nostalgia";
			else PTY_code = "Nostalga";
			break;
		case 0xE : 
			PTY_code = "Jazz";
			break;
		case 0xF : 
			if (length_16) 
			PTY_code = "Classical";
			else PTY_code = "Classicl";
			break;
		case 0x10 : 
			if (length_16) 
			PTY_code = "Rhythm_and_Blues";
			else PTY_code = "R_&_B";
			break;
		case 0x11 : 
			if (length_16) 
			PTY_code = "Soft_R_&_B";
			else PTY_code = "Soft_R&B";
			break;
		case 0x12 : 
			if (length_16) 
			PTY_code = "Foreign_Language";
			else PTY_code = "Language";
			break;
		case 0x13 : 
			if (length_16) 
			PTY_code = "Religious_Music";
			else PTY_code = "Rel_Musc";
			break;
		case 0x14 : 
			if (length_16) 
			PTY_code = "Religious_Talk";
			else PTY_code = "Rel_Talk";
			break;
		case 0x15 : 
			if (length_16) 
			PTY_code = "Personality";
			else PTY_code = "Persnlty";
			break;
		case 0x16 : 
			PTY_code = "Public";
			break;
		case 0x17 : 
			PTY_code = "College";
			break;
		case 0x18 : 
			if (length_16) 
			PTY_code = "Hablar_Espanol"; // Spanish talk
			else PTY_code = "Habl_Esp";
			break;
		case 0x19 : 
			if (length_16) 
			PTY_code = "Musica_Espanol"; // Spanish music
			else PTY_code = "Musc_Esp";
			break;
		case 0x1A : 
			PTY_code = "Hip_Hop";
			break;
		case 0x1B : 
			PTY_code = "Custom"; // Unassigned
			break;
		case 0x1C : 
			PTY_code = "Custom"; // Unassigned
			break;
		case 0x1D : 
			PTY_code = "Weather";
			break;
		case 0x1E : 
			if (length_16) 
			PTY_code = "Emergency_Test";
			else PTY_code = "Test";
			break;
		case 0x1F : 
			if (length_16) 
			PTY_code = "ALERT!_ALERT!"; // Emergency
			else PTY_code = "ALERT!";
			break;
		default :
			PTY_code = "None";
	}
	
	cout << "PTY code: " << unsigned(PTY_bits) << endl;
	cout << "Formatted PTY code: " << PTY_code << endl;
	
	return PTY_code;
}

// Decode the 16-bit PI (program identifier) code from block A
string get_PI(unsigned int blockA) {
	// Country code: A = America, C = Canada, F = Mexica, B/D/E = Coverage Area Code
	// Hexadecimal -> Decimal -> Do Math -> Base 26
	string PI_code;
	unsigned int Digit1; // First place 
	unsigned int Digit2; // First place and second place added 
	unsigned int Place2; // Second place
	unsigned int Place3; // Third place
	unsigned int Place4; // Fourth place
	
	unsigned int numMod;
	
	// Need bits 00000011111111111111110000000000
	unsigned int PI_num = (blockA & 0x03FFFC00) >> 10;
	char PI_b26letters[4]; 
	
	// Reserved codes: 0x0000 - 0x0FFF for 3-letter PI codes
	if (PI_num < 0x1000) {
		PI_b26letters[0] = '3';
		PI_b26letters[1] = 'L';
		PI_b26letters[2] = 'T';
		PI_b26letters[3] = 'R';
	}
	// 0x1000 (4096) - 0x54A7 (21671) for K--- PI codes
	else if (PI_num < 0x54A8) {
		PI_b26letters[0] = 'K';
		// Use unique conveersion calculations detailed in RBDS standard to convert hex to letters
		PI_num -= 4096;
		Digit2 = PI_num % 676;
		Digit1 = Digit2 % 26; // First spot
		Place2 = (Digit2 - Digit1) / 26;
		Place3 = (PI_num - Digit2) / 676;
		// Convert unsigned int to char
		PI_b26letters[3] = num2letter(Digit1);
		PI_b26letters[2] = num2letter(Place2);
		PI_b26letters[1] = num2letter(Place3);
	}
	// 0x54A8 (21672) - 0x994F (39247) for W--- PI codes
	else if (PI_num < 0x9950) {
		// Same as K--- codes, just subtract a different starting value
		PI_b26letters[0] = 'W';
		PI_num -= 21672;
		Digit2 = PI_num % 676;
		Digit1 = Digit2 % 26; // First spot
		Place2 = (Digit2 - Digit1) / 26;
		Place3 = (PI_num - Digit2) / 676;
		
		PI_b26letters[3] = num2letter(Digit1);
		PI_b26letters[2] = num2letter(Place2);
		PI_b26letters[1] = num2letter(Place3);
	}
	// 0xA100 to 0xA9FF for -0-- PI codes
	else if (PI_num < 0xAA00) {
		PI_b26letters[1] = '0';
		Place4 = (PI_num & 0x0F00) >> 8;
		Place2 = (PI_num & 0x00F0) >> 4;
		Digit1 = PI_num & 0x000F;
		
		PI_b26letters[3] = hex2letter(Digit1);
		PI_b26letters[2] = hex2letter(Place2);
		PI_b26letters[0] = hex2letter(Place4);
	}
	// 0xAFA1 to 0xAFAF for --00 PI codes
	else if (PI_num < 0xAFB0) {
		PI_b26letters[2] = '0';
		PI_b26letters[3] = '0';
		Place4 = (PI_num & 0x00F0) >> 4;
		Place3 = PI_num & 0x000F;
		
		PI_b26letters[1] = hex2letter(Place3);
		PI_b26letters[0] = hex2letter(Place4);
	}
	// 0xB-01 to 0xE-FF for unique PI codes
	else {
		Place4 = (PI_num & 0xF000) >> 12; // Should be B, D, or E
		Place3 = (PI_num & 0x0F00) >> 8;  // This place doesn't matter for these codes
		Place2 = (PI_num & 0x00F0) >> 4;
		Digit1 = PI_num & 0x000F;
		
		PI_b26letters[0] = hex2letter(Place4);
		PI_b26letters[1] = hex2letter(Place3);
		PI_b26letters[2] = hex2letter(Place2);
		PI_b26letters[3] = hex2letter(Digit1);
	}
	
	PI_code.push_back(PI_b26letters[0]);
	PI_code.push_back(PI_b26letters[1]);
	PI_code.push_back(PI_b26letters[2]);
	PI_code.push_back(PI_b26letters[3]);
	
	cout << "PI code: " << PI_code << endl;
	
	return PI_code;
}

// Convert a number to a letter (base 26)
char num2letter(unsigned int n) {
	string conv_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char conv_char = conv_table[n];
	return conv_char;
}

// Convert a hex value to a character
char hex2letter(unsigned int n) {
	string conv_table = "0123456789ABCDEF";
	char conv_char = conv_table[n];
	return conv_char;
}

// Decode an 8-bit char of a 32 (2B) or 64 (2A) char RadioText message. Text is in blocks C&D for 2A, and D only for 2B
// Placement of the chars in the message is determined by the TS (text segment) address 
char get_RadioText(unsigned int blockX, unsigned int blockB, bool check_char) {
	
	char RadioText_part;
	// cout << *RadioText_part << endl;
	// Need bits 00000011111111000000000000000000 and 00000000000000111111110000000000
	uint8_t RT_bits;
	if (check_char) {
		RT_bits = (blockX & 0x03FC0000) >> 18;
		// cout << "Bits: " << unsigned(RT_bits) << endl;
	}
	else {
		RT_bits = (blockX & 0x0003FC00) >> 10;
	}
	// RadioText_part[0] = (blockX & 0x03FC0000) >> 10;
	// RadioText_part[1] = (blockX & 0x0003FC00) >> 10;
	char RadioText_pt;
	
	// Convert bits to text according to table in annex E of nrsc-4 standard
	BCD_to_char(RT_bits, &RadioText_part);
	
	// Need bits 00000000000000000011110000000000
	uint8_t TS_addr = (blockB & 0x00003C00) >> 10;
	
	return RadioText_part;
	
}

// Convert two 8-bit values to characters (used for RadioText)
void BCD_to_char(uint8_t BCD, char *text) {
	/* uint8_t nibble = (BCD & 0xF0) >> 4;
    *text = (nibble == 0xA ? ' ' : nibble + '0');
    nibble = BCD & 0x0F;
    *text = (nibble == 0xA ? ' ' : nibble + '0'); */
	
	// Note: This is the same conversion order as ASCII. May need optimizing later.
	string switch_table = " !\"# %&'()*+'-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]-_|abcdefghijklmnopqrstuvwxyz{|}- ";
	if (unsigned(BCD) < 32) {
		*text = switch_table[0];
	}
	else if (unsigned(BCD) - 32 < switch_table.length()) {
		*text = switch_table[unsigned(BCD) - 32];
	}
	else {
		*text = switch_table[0];
	}
	/*switch(unsigned(BCD)) {
		case 32 :
			*text = ' ';
			break;
		case 33 :
			*text = '!';
			break;
		case 39 :
			*text = '\'';
			break;
		case 44 :
			*text = ',';
			break;
		case 45 :
			*text = '-';
			break;
		case 46 :
			*text = '.';
			break;
		case 47 :
			*text = '/';
			break;
		case 48 :
			*text = '0';
			break;
		case 49 :
			*text = '1';
			break;
		case 50 :
			*text = '2';
			break;
		case 51 :
			*text = '3';
			break;
		case 52 :
			*text = '4';
			break;
		case 53 :
			*text = '5';
			break;
		case 54 :
			*text = '6';
			break;
		case 55 :
			*text = '7';
			break;
		case 56 :
			*text = '8';
			break;
		case 57 :
			*text = '9';
			break;
		case 65 :
			*text = 'A';
			break;
		case 66 :
			*text = 'B';
			break;
		case 67 :
			*text = 'C';
			break;
		case 68 :
			*text = 'D';
			break;
		case 69 :
			*text = 'E';
			break;
		case 70 :
			*text = 'F';
			break;
		case 71 :
			*text = 'G';
			break;
		case 72 :
			*text = 'H';
			break;
		case 73 :
			*text = 'I';
			break;
		case 74 :
			*text = 'J';
			break;
		case 75 :
			*text = 'K';
			break;
		case 76 :
			*text = 'L';
			break;
		case 77 :
			*text = 'M';
			break;
		case 78 :
			*text = 'N';
			break;
		case 79 :
			*text = 'O';
			break;
		case 80 :
			*text = 'P';
			break;
		case 81 :
			*text = 'Q';
			break;
		case 82 :
			*text = 'R';
			break;
		case 83 :
			*text = 'S';
			break;
		case 84 :
			*text = 'T';
			break;
		case 85 :
			*text = 'U';
			break;
		case 86 :
			*text = 'V';
			break;
		case 87 :
			*text = 'W';
			break;
		case 88 :
			*text = 'X';
			break;
		case 89 :
			*text = 'Y';
			break;
		case 90 :
			*text = 'Z';
			break;
		case 97 :
			*text = 'a';
			break;
		default :
			*text = ' ';
	}*/
};



int main() {
	
	// Define the 4 blocks of the group. Though ints are 32 bits, each block only uses 26 bits (0x03FFFFFF)
	// In the final version of the program, the values of the blocks will be passed in from the Arduino
	unsigned int block[4]; // 4 parts of the whole 104-bit group 
	block[0] = 0x0152A400; // Block A 0x54A9 -> "WAAB"
	// block[0] = 0x01529B00; // Block A 0x5A47 -> "KZZY"
	// block[0] = 0x028A6800; // Block A 0xA29A -> "209A"
	// block[0] = 0x02BC8400; // Block A 0xAF21 -> "2100"
	block[1] = 0x00930000; // Block B GT 2A PTY 6 TP 1
	// block[1] = 0x02760000; // Block B GT 9B PTY 12 TP 1
	block[2] = 0x01848000; // Block C "a "
	block[3] = 0x01056800; // Block D "AZ"
	// block[2] = 0x00DCFC00; // Block C "7?"
	// block[3] = 0x01017000; // Block D "@\"
	// block[2] = 0x01519400; // Block C "Te"
	// block[3] = 0x01CDD000; // Block D "st"
	
	// Input 4 blocks of RBDS group. Format in decimal (hex/bin compatibility can be added). 
	// cout << "Input block A: ";
	// cin >> block[0];
	// cout << "Input block B: ";
	// cin >> block[1];
	// cout << "Input block C: ";
	// cin >> block[2];
	// cout << "Input block D: ";
	// cin >> block[3];
	
	if ((!block[0]) && (!block[1])) { // Check that blocks contain data
		cout << "ERROR: Input data is missing/incompatible!" << endl;
		return 1;
	}
	
	// Define variables that will be assigned through the PI code 
	/* string PI_country = "None";
	string PI_code = "undef"; */
	
	// Obtain the universal components common of all groups
	uint8_t group_type = get_group_type(block[1]);
	bool TP_code = get_TP(block[1]);
	string PTY_code = get_PTY(block[1]);
	string PI_code = get_PI(block[0]);
	
	// Obtain any group-specific components given group_type
	if (unsigned(group_type) == 4 || unsigned(group_type) == 5) { // Groups 2A or 2B
		// cout << "Group 2 branch called" << endl;
		// char RadioText_partD[2]; // A segment of 2 (2B) or 4 (2A) 8-bit characters
		// uint8_t TS_addr; // Text segment address code
		if (unsigned(group_type) == 4) {
			// cout << RadioText_full << endl;
			char RadioText_part[64];
			RadioText_part[0] = get_RadioText(block[2], block[1], true);
			RadioText_part[1] = get_RadioText(block[2], block[1], false);
			RadioText_part[2] = get_RadioText(block[3], block[1], true);
			RadioText_part[3] = get_RadioText(block[3], block[1], false);
			
			/* int charPlace = 0x4*TS_addr;
			RadioText_full[charPlace] = RadioText_partC[0];
			RadioText_full[charPlace + 1] = RadioText_partC[1];
			RadioText_full[charPlace + 2] = RadioText_partD[0];
			RadioText_full[charPlace + 3] = RadioText_partD[1]; */
			cout << "RadioText: " << RadioText_part[0] << RadioText_part[1] << RadioText_part[2] << RadioText_part[3] << endl;
		}
		else {
			char RadioText_part[32];
			
			RadioText_part[0] = get_RadioText(block[3], block[1], true);
			RadioText_part[1] = get_RadioText(block[3], block[1], false);
			
			/* int charPlace = 0x2*TS_addr;
			RadioText_full[charPlace] = RadioText_partD[0];
			RadioText_full[charPlace + 1] = RadioText_partD[1]; */
			cout << "RadioText: " << RadioText_part[0] << RadioText_part[1] << endl;
		}
		
	}
	
	return 0;
}