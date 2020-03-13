#ifndef DRAW_FUNCTIONS
#define DRAW_FUNCTIONS

#include <WiFi.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include "../config/enums.h"
#include "../config/config.h"

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern DisplayValues gDisplayValues;
extern unsigned char measureIndex;

void drawTime(){
  u8g2.setFont(u8g2_font_6x13_tf); //u8g2.setTextSize(1);
  u8g2.setCursor(0, 0);
  u8g2.print(gDisplayValues.time);
}

void drawSignalStrength(){
  const byte X = 51;
  const byte X_SPACING = 2;

  // Draw the four base rectangles
  u8g2.drawBox(X, 8-2, 1, 2);  //Bar 1
  u8g2.drawBox(X + X_SPACING, 8-2, 1, 2); // Bar 2
  u8g2.drawBox(X + X_SPACING*2, 8-2, 1, 2); // Bar 3
  u8g2.drawBox(X + X_SPACING*3, 8-2, 1, 2); // Bar 4
  //u8g2.fillRect(X, 8-2, 1, 2, WHITE); // Bar 1
  //u8g2.fillRect(X + X_SPACING, 8-2, 1, 2, WHITE); // Bar 2
  //u8g2.fillRect(X + X_SPACING*2, 8-2, 1, 2, WHITE); // Bar 3
  //u8g2.fillRect(X + X_SPACING*3, 8-2, 1, 2, WHITE); // Bar 4

  // Draw bar 2
  if(gDisplayValues.wifi_strength > -70){
    u8g2.drawBox(X+X_SPACING, 8-4, 1, 4);
    //u8g2.fillRect(X+X_SPACING, 8-4, 1, 4, WHITE);
  }

  // Draw bar 3
  if(gDisplayValues.wifi_strength > -60){
    u8g2.drawBox(X+X_SPACING*2, 8-6, 1, 6);
    //u8g2.fillRect(X+X_SPACING*2, 8-6, 1, 6, WHITE);
  }

  // Draw bar 4
  if(gDisplayValues.wifi_strength >= -50){
    u8g2.drawBox(X+X_SPACING*3, 8-8, 1, 8);
    //u8g2.fillRect(X+X_SPACING*3, 8-8, 1, 8, WHITE);
  }
}

void drawMeasurementProgress(){
  const byte Y = SCREEN_WIDTH - 20;
  u8g2.drawBox(0, Y, measureIndex*2, 2);
  //u8g2.drawRect(0, Y, measureIndex*2, 2, WHITE);
}

/**
 * The screen that is displayed when the ESP has just booted
 * and is connecting to WiFi & AWS.
 */
void drawBootscreen(){
  byte X = 14;
  byte Y = 70;
  byte WIDTH = 6;
  byte MAX_HEIGHT = 35;
  byte HEIGHT_STEP = 10;
  byte X_SPACING = 10;

  u8g2.drawBox(X,Y,WIDTH,MAX_HEIGHT - HEIGHT_STEP*3);
  u8g2.drawBox(X + X_SPACING,Y - HEIGHT_STEP,WIDTH,MAX_HEIGHT - HEIGHT_STEP*2);
  u8g2.drawBox(X + X_SPACING*2,Y - HEIGHT_STEP*2,WIDTH,MAX_HEIGHT - HEIGHT_STEP);
  u8g2.drawBox(X + X_SPACING*3,Y - HEIGHT_STEP*3,WIDTH,MAX_HEIGHT);

  //u8g2.fillRect(X              , Y, WIDTH, MAX_HEIGHT - HEIGHT_STEP*3, WHITE);
  //u8g2.fillRect(X + X_SPACING  , Y - HEIGHT_STEP, WIDTH, MAX_HEIGHT - HEIGHT_STEP*2, WHITE);
  //u8g2.fillRect(X + X_SPACING*2, Y - HEIGHT_STEP*2, WIDTH, MAX_HEIGHT - HEIGHT_STEP, WHITE);
  //u8g2.fillRect(X + X_SPACING*3, Y - HEIGHT_STEP*3, WIDTH, MAX_HEIGHT, WHITE);

  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setCursor(0, Y + MAX_HEIGHT / 2);
  u8g2.println("Connecting");

  if(gDisplayValues.currentState == CONNECTING_WIFI){
    u8g2.println("   WiFi");
  }

  if(gDisplayValues.currentState == CONNECTING_AWS){
    u8g2.println("   AWS");
  }
}

/**
 * Draw the current amps & watts in the middle of the u8g2.
 */
void drawAmpsWatts(){

  String watts = String(gDisplayValues.watt, 0);
  String amps = String(gDisplayValues.amps, 2);
  
  String lblWatts = "Watt";
  String lblAmps = "Amps";

  const int startY = 30;

  // Calculate how wide (pixels) the text will be once rendered.
  // Each character = 6 pixels, with font size 2, that is 12 pixels.
  // -1 because of the spacing between letters (last one doesn't)
  int widthAmps = (amps.length() * 12) -1;
  int widthLblAmps = lblAmps.length() * 6 - 1;

  int widthWatts = watts.length() * 12 - 1;
  int widthLblWatts = lblWatts.length() * 6 -1;

  u8g2.setFont(u8g2_font_ncenR12_tf);
  u8g2.setCursor((SCREEN_HEIGHT - widthAmps) / 2, startY);
  u8g2.print(amps);

  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setCursor((SCREEN_HEIGHT - widthLblAmps) / 2, startY + 15);
  u8g2.print(lblAmps);

  u8g2.setFont(u8g2_font_ncenR12_tf);
  u8g2.setCursor((SCREEN_HEIGHT - widthWatts) / 2, startY + 40);
  u8g2.print(watts);

  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setCursor((SCREEN_HEIGHT - widthLblWatts) / 2, startY + 60);
  u8g2.print(lblWatts);
}

#endif