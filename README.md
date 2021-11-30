# Capstone
Project containing all code for ECEN 403 and ECEN 404 senior project classes.
By: Daniel Cogan, Texas A&M University

INCLUDED FILES: 
Currently, code is split into separate files for demo and testing purposes. 
It is configured to run on an Arudino Uno R3.

Audio_Proc.ino - Handles audio processing of an audio signal from AM/FM receivers. 

Display_Tests.ino - Controls the Adafruit OLED 128x64 display. Frequency, volume, and mode are monitored. A custom team logo is also implemented.

RBDS_Decoder.ino - Takes in and decodes an RDS/RBDS bitstream (radio channel information). Uses a custom C++ library.
RBDS_Decoder_Ard.cpp - The C++ code of the custom library. 
RBDS_Decoder_V1_Ard.h - The header file connecting the C++ file to the Arduino code. RENAME THIS FILE TO RBDS_Decoder_V1.h FOR IT TO WORK

RBDS_Decoder_V1.cpp - The original version of the C++ custom library which can be run through a terminal on Windows. Directions to compile are near the beginning of the program
RBDS_Decoder_V1.h - The header file of RBDS_Decoder_V1.cpp

