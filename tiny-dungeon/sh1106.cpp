// Thanks, Technoblogy
// - http://www.technoblogy.com/show?23OS

// heavily modified to support ATtiny84 and add some new features,
// as well as optimize the hell out of anything already here

#include <Wire.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <Arduino.h>
#include "monochrome-spritesheet.hh"

/* Tiny Graphics Library v3 - see http://www.technoblogy.com/show?23OS

   David Johnson-Davies - www.technoblogy.com - 23rd September 2018
   ATtiny85 @ 8 MHz (internal oscillator; BOD disabled)

   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license:
   http://creativecommons.org/licenses/by/4.0/
*/


// Pins
int const sda = 6;
int const scl = 4;

// Constants
int const address = 60;
int const commands = 0x00;
int const onecommand = 0x80;
int const data = 0x40;
int const onedata = 0xC0;

// OLED display **********************************************

// Character set for text - stored in program memory
// 6 columns of 8
const uint8_t CharMap[96][6] PROGMEM = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 },
  { 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 },
  { 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 },
  { 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 },
  { 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 },
  { 0x36, 0x49, 0x56, 0x20, 0x50, 0x00 },
  { 0x00, 0x08, 0x07, 0x03, 0x00, 0x00 },
  { 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 },
  { 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 },
  { 0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x00 },
  { 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 },
  { 0x00, 0x80, 0x70, 0x30, 0x00, 0x00 },
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },
  { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },
  { 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 },
  { 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 },
  { 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 },
  { 0x72, 0x49, 0x49, 0x49, 0x46, 0x00 },
  { 0x21, 0x41, 0x49, 0x4D, 0x33, 0x00 },
  { 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 },
  { 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 },
  { 0x3C, 0x4A, 0x49, 0x49, 0x31, 0x00 },
  { 0x41, 0x21, 0x11, 0x09, 0x07, 0x00 },
  { 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 },
  { 0x46, 0x49, 0x49, 0x29, 0x1E, 0x00 },
  { 0x00, 0x00, 0x14, 0x00, 0x00, 0x00 },
  { 0x00, 0x40, 0x34, 0x00, 0x00, 0x00 },
  { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },
  { 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 },
  { 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 },
  { 0x02, 0x01, 0x59, 0x09, 0x06, 0x00 },
  { 0x3E, 0x41, 0x5D, 0x59, 0x4E, 0x00 },
  { 0x7C, 0x12, 0x11, 0x12, 0x7C, 0x00 },
  { 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 },
  { 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 },
  { 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 },
  { 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 },
  { 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 },
  { 0x3E, 0x41, 0x41, 0x51, 0x73, 0x00 },
  { 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 },
  { 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 },
  { 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 },
  { 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 },
  { 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 },
  { 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x00 },
  { 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 },
  { 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 },
  { 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 },
  { 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 },
  { 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 },
  { 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 },
  { 0x03, 0x01, 0x7F, 0x01, 0x03, 0x00 },
  { 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 },
  { 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 },
  { 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 },
  { 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 },
  { 0x03, 0x04, 0x78, 0x04, 0x03, 0x00 },
  { 0x61, 0x59, 0x49, 0x4D, 0x43, 0x00 },
  { 0x00, 0x7F, 0x41, 0x41, 0x41, 0x00 },
  { 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 },
  { 0x00, 0x41, 0x41, 0x41, 0x7F, 0x00 },
  { 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 },
  { 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 },
  { 0x00, 0x03, 0x07, 0x08, 0x00, 0x00 },
  { 0x20, 0x54, 0x54, 0x78, 0x40, 0x00 },
  { 0x7F, 0x28, 0x44, 0x44, 0x38, 0x00 },
  { 0x38, 0x44, 0x44, 0x44, 0x28, 0x00 },
  { 0x38, 0x44, 0x44, 0x28, 0x7F, 0x00 },
  { 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 },
  { 0x00, 0x08, 0x7E, 0x09, 0x02, 0x00 },
  { 0x18, 0xA4, 0xA4, 0x9C, 0x78, 0x00 },
  { 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 },
  { 0x00, 0x44, 0x7D, 0x40, 0x00, 0x00 },
  { 0x20, 0x40, 0x40, 0x3D, 0x00, 0x00 },
  { 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 },
  { 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 },
  { 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00 },
  { 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 },
  { 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 },
  { 0xFC, 0x18, 0x24, 0x24, 0x18, 0x00 },
  { 0x18, 0x24, 0x24, 0x18, 0xFC, 0x00 },
  { 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 },
  { 0x48, 0x54, 0x54, 0x54, 0x24, 0x00 },
  { 0x04, 0x04, 0x3F, 0x44, 0x24, 0x00 },
  { 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 },
  { 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 },
  { 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 },
  { 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 },
  { 0x4C, 0x90, 0x90, 0x90, 0x7C, 0x00 },
  { 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 },
  { 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 },
  { 0x00, 0x00, 0x77, 0x00, 0x00, 0x00 },
  { 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 },
  { 0x00, 0x06, 0x09, 0x06, 0x00, 0x00 },  // degree symbol = '~'
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 }

};

// Current plot position
int x0;
int y0;

// Send a single command
void Single(uint8_t x) {
  Wire.write(onecommand);
  Wire.write(x);
}

void InitI2C(){
  Wire.begin();
}

void InitDisplay() {
  Wire.beginTransmission(address);
  Wire.write(commands);
  Wire.write(0xA1);  // Flip horizontal
  Wire.write(0xAF);  // Display on
  Wire.endTransmission();
}

void ClearDisplay() {
  for (int p = 0; p < 8; p++) {
    Wire.beginTransmission(address);
    Single(0xB0 + p);
    Wire.endTransmission();
    for (int q = 0; q < 8; q++) {
      Wire.beginTransmission(address);
      Wire.write(data);
      for (int i = 0; i < 20; i++) Wire.write(0);
      Wire.endTransmission();
    }
  }
}

void setupDisplay(){
    InitI2C();
    ClearDisplay();
    InitDisplay();
}

// Move current plot position to x,y
void MoveTo(int x, int y) {
  x0 = x;
  y0 = y;
}

uint8_t ReverseByte(uint8_t x) {
  x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
  x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
  x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
  return x;
}

// private method - plot a char at the current position, and also assumes caller already placed display in ReadModifyWrite mode
PlotCharInRMW(int c) {
  for (int col = 0; col < 6; col++) {
    Wire.write(onedata);
    Wire.write(
      ReverseByte( // i'd rather reverse the sprite maps instead
          pgm_read_byte(&CharMap[c - 32][col])
          )
      );
  }
}

// Plot an ASCII character with bottom left corner at x,y
// only supports y divisible by 8, hence page instead of y
void PlotChar(int c, int x, int page) {
  Wire.beginTransmission(address);
  Single(0xB0 + page);
  // column is automatically incremented on display memory accessses so no need to keep re-setting it
  Single(0x00 + ((x + 2) & 0x0F));  // initial Column low nibble
  Single(0x10 + ((x + 2) >> 4));    // initial Column high nibble
  Single(0xE0);                           // Read modify write
  PlotCharInRMW(c);
  Single(0xEE);  // Cancel read modify write
  Wire.endTransmission();
}

// Plot text starting at the current plot position - really really fast, a full screen in 0.2 seconds
void PlotText(PGM_P s) {
  int p = (int) s;
  Wire.beginTransmission(address);
  Single(0xB0 + (y0 >> 3));
  // column is automatically incremented on display memory writes so no need to keep re-setting it!
  Single(0x00 + ((x0 + 2) & 0x0F));  // initial Column low nibble
  Single(0x10 + ((x0 + 2) >> 4));    // initial Column high nibble
  Single(0xE0); // Read modify write
  while (1) {
    char c = pgm_read_byte(p++);
    if (c == 0) break;
    Wire.endTransmission(); // really small i2c buffer! so call this per character
    Wire.beginTransmission(address);
    PlotCharInRMW(c);
  }
  Single(0xEE);  // end read modify write
  Wire.endTransmission();
} // 11 column limit? might be wire buffer?

void invert(){
  Wire.beginTransmission(address);
  Single(0xA7); // inverse display output
  Wire.endTransmission();
}

void unInvert(){
  Wire.beginTransmission(address);
  Single(0xA6);
  Wire.endTransmission();
}

// the above 2 in a row
void blink(){
  invert();
  delay(100);
  unInvert();
}


// these disregard the "invert" state
void forceDisplayAllOff(){
  Wire.beginTransmission(address);
  Single(0xAE); // turn display off - overrides any other command effect
  Wire.endTransmission();
}

void forceDisplayAllOn(){
  Wire.beginTransmission(address);
  Single(0xA5); // force all segments on
  Wire.endTransmission();
}

void resetForceDisplay(){
  Wire.beginTransmission(address);
  Single(0xA4); // undo force all segments on
  Single(0xAF); // turn display back on
  Wire.endTransmission();
}
// contrast but for OLEDs
// default is 1 << 7
void setBrightness(uint8_t brightness){ 
  Wire.beginTransmission(address);
  Single(0x81); // enable contrast control mode
  Single(brightness); // send it, and exit contrast control mode
  Wire.endTransmission();
}

void resetBrightness(){
  setBrightness(1 << 7);
}

// max lines = 63 !!
// loops the display ram across the display with this offset
void setScroll(uint8_t lines){
  Wire.beginTransmission(address);
  Single(0x40 | (lines & 0x3F));
  Wire.endTransmission();
}

void resetScroll(){
  setScroll(0);
}