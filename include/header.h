#ifndef _EPAPER_CALENDAR_
#define _EPAPER_CALENDAR_

// Display Library example for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: the e-paper panels require 3.3V supply AND data lines!
//
// Display Library based on Demo Example from Good Display: http://www.e-paper-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

// GxEPD2_WS_ESP32_Driver : GxEPD2_Example variant for Universal e-Paper Raw Panel Driver Board, ESP32 WiFi / Bluetooth Wireless
// https://www.waveshare.com/product/e-paper-esp32-driver-board.htm

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Display ePaper for Arduino: https://forum.arduino.cc/index.php?topic=436411.0

// mapping of Waveshare ESP32 Driver Board
// BUSY -> 25, RST -> 26, DC -> 27, CS-> 15, CLK -> 13, DIN -> 14

// NOTE: this board uses "unusual" SPI pins and requires re-mapping of HW SPI to these pins in SPIClass
//       this example shows how this can be done easily

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
// Note: if you use this with ENABLE_GxEPD2_GFX 1:
//       uncomment it in GxEPD2_GFX.h too, or add #include <GFX.h> before any #include <GxEPD2_GFX.h>

#include <SPI.h>
#include <Wire.h>
#include <GxEPD2_BW.h>
// #include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// select the display class (only one), matching the kind of display panel
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
//#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
//#define GxEPD2_DISPLAY_CLASS GxEPD2_7C

// select the display driver class (only one) for your  panel
//#define GxEPD2_DRIVER_CLASS GxEPD2_154     // GDEP015OC1  200x200, no longer available
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_D67 // GDEH0154D67 200x200
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_T8  // GDEW0154T8  152x152
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_M09 // GDEW0154M09 200x200
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_M10 // GDEW0154M10 152x152
//#define GxEPD2_DRIVER_CLASS GxEPD2_213     // GDE0213B1   128x250, phased out
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_B72 // GDEH0213B72 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_B73 // GDEH0213B73 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_flex // GDEW0213I5F 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_M21 // GDEW0213M21 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_290     // GDEH029A1   128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_T5  // GDEW029T5   128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_T94 // GDEM029T94  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_M06 // GDEW029M06  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_260     // GDEW026T0   152x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_260_M01 // GDEW026M01  152x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_270     // GDEW027W3   176x264
//#define GxEPD2_DRIVER_CLASS GxEPD2_371     // GDEW0371W7  240x416
#define GxEPD2_DRIVER_CLASS GxEPD2_420 // GDEW042T2   400x300
// #define GxEPD2_DRIVER_CLASS GxEPD2_420_M01 // GDEW042M01  400x300
//#define GxEPD2_DRIVER_CLASS GxEPD2_583     // GDEW0583T7  600x448
//#define GxEPD2_DRIVER_CLASS GxEPD2_583_T8  // GDEW0583T8  648x480
//#define GxEPD2_DRIVER_CLASS GxEPD2_750     // GDEW075T8   640x384
//#define GxEPD2_DRIVER_CLASS GxEPD2_750_T7  // GDEW075T7   800x480
// 3-color e-papers
//#define GxEPD2_DRIVER_CLASS GxEPD2_154c     // GDEW0154Z04 200x200, no longer available
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_Z90c // GDEH0154Z90 200x200
//#define GxEPD2_DRIVER_CLASS GxEPD2_213c     // GDEW0213Z16 104x212
//#define GxEPD2_DRIVER_CLASS GxEPD2_290c     // GDEW029Z10  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_C90c // GDEM029C90  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_270c     // GDEW027C44  176x264
//#define GxEPD2_DRIVER_CLASS GxEPD2_420c     // GDEW042Z15  400x300
//#define GxEPD2_DRIVER_CLASS GxEPD2_583c     // GDEW0583Z21 600x448
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c     // GDEW075Z09  600x384
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z08 // GDEW075Z08  800x480
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z90 // GDEH075Z90  880x528
//#define GxEPD2_DRIVER_CLASS GxEPD2_1248     // GDEW1248T3  1303x984
// 7-color e-paper
//#define GxEPD2_DRIVER_CLASS GxEPD2_565c // Waveshare 5.65" 7-color (3C graphics)

// somehow there should be an easier way to do this
#define GxEPD2_BW_IS_GxEPD2_BW true
#define GxEPD2_3C_IS_GxEPD2_3C false
#define GxEPD2_7C_IS_GxEPD2_7C false
#define GxEPD2_1248_IS_GxEPD2_1248 false
#define IS_GxEPD(c, x) (c##x)
#define IS_GxEPD2_BW(x) IS_GxEPD(GxEPD2_BW_IS_, x)
#define IS_GxEPD2_3C(x) IS_GxEPD(GxEPD2_3C_IS_, x)
#define IS_GxEPD2_7C(x) IS_GxEPD(GxEPD2_7C_IS_, x)
#define IS_GxEPD2_1248(x) IS_GxEPD(GxEPD2_1248_IS_, x)

#if defined(ESP32)
#define MAX_DISPLAY_BUFFER_SIZE 65536ul // e.g.
#if IS_GxEPD2_BW(GxEPD2_DISPLAY_CLASS)
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
#elif IS_GxEPD2_3C(GxEPD2_DISPLAY_CLASS)
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
#elif IS_GxEPD2_7C(GxEPD2_DISPLAY_CLASS)
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2))
#endif

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=*/15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));
#endif

#endif