// This program decodes a sample RBDS input

// Includes and defines for SSD1306 display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Other includes and defines
#include <String.h>

#include <RBDS_Decoder_V1.h>

// ***Put example RBDS inputs here. Format is as follows:*** 
// Group type XX, PI code, PTY code, TP ID code
// Then any other features specific to the group type, such as Radio Text

// Group...
// unsigned long long int myRBDS;


// Define parts of RBDS signal for convenience
unsigned int block[4];
// const unsigned int blockA = 0x0152A400; // Split RBDS into 4 blocks
// const unsigned int blockB = 0x00930000;
// const unsigned int blockC = 0x01848000;
// const unsigned int blockD = 0x01056800;

uint8_t group_type;
String PTY_code;
String radiotext;
// bool grouptype[5], PIcode[x], PTYcode[x], TPID[x]; // Data that is always in RBDS signal

void setup() {
  unsigned long blockA = 0x0152A400; // Split RBDS into 4 blocks
  unsigned long blockB = 0x00930000;
  unsigned long blockC = 0x01848000;
  unsigned long blockD = 0x01056800;
  Serial.begin(9600);
  
  // block[0] = 0x0152A400; // Block A 0x54A9 -> "WAAB"
  // block[0] = 0x01529B00; // Block A 0x5A47 -> "KZZY"
  // block[0] = 0x028A6800; // Block A 0xA29A -> "209A"
  // block[1] = 9633792;
  // block[1] = 0x00930000; // Block B GT 2A PTY 6 TP 1
  // block[1] = 0x02760000; // Block B GT 9B PTY 12 TP 1
  // block[2] = 0x01848000; // Block C "a "
  // block[3] = 0x01056800; // Block D "AZ"
  
  group_type = get_group_type(blockB);
  PTY_code = get_PTY(blockB);
  radiotext = get_RadioText(block
  Serial.print("Block B value: ");
  Serial.println(blockB);
  Serial.print("Group type: ");
  Serial.println(group_type);
  Serial.print("PTY code: ");
  Serial.println(PTY_code);
}

void loop() {
  

}
