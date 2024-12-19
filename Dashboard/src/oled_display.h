#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <U8g2lib.h>

// Déclarez les fonctions ici
//void displayDataInt(U8G2_SH1106_128X64_NONAME_F_HW_I2C display, int data, const char * texte, const char * unite, int scale, int y, int l, int w, const uint8_t* font);
void displayDataInt(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, int data, const char *texte, const char *unite, int scale, int y, int l, int w, const uint8_t *font);
void displayDataFloat(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float data, const char * texte, const char * unite, int scale,  int y, int l, int w, const uint8_t* font);
void initTCA9548();
void tcaSelect(uint8_t channel);
void scanTCAChannels();

#endif