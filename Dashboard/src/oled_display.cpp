#include <U8g2lib.h>
#include <Wire.h>

// Fonction générique pour afficher de la data int
// void displayDataInt(U8G2_SH1106_128X64_NONAME_F_HW_I2C display, int data, const char * texte, const char * unite, int scale,  int y, int l, int w, const uint8_t* font) {
//   char buffer[15];
//   display.setFont(font); // Petite police pour plus de contenu   
//   // Conversion du nombre en chaîne de caractères
//   sprintf(buffer, "%s:%d%s",texte, data, unite);
//   display.drawStr(0, y, buffer);
//   // Barre de progression
//   display.drawFrame(0, y+5, l, w);            // Cadre de la barre
//   display.drawBox(0, y+5, (data * l) / scale, w);  // Remplissage en fonction de "data"
// }
void displayDataInt(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, int data, const char *texte, const char *unite, int scale, int y, int l, int w, const uint8_t *font) {
  char buffer[30]; // Augmenter la taille du buffer pour éviter les dépassements

  // Configuration de la police
  display.setFont(font);

  // Créer la chaîne formatée pour l'affichage
  snprintf(buffer, sizeof(buffer), "%s: %d%s", texte, data, unite);
  
  // Afficher le texte
  display.drawStr(0, y, buffer);

  // Limiter "data" à la plage [0, scale] pour éviter les dépassements
  if (data > scale) {
    data = scale;
  } else if (data < 0) {
    data = 0;
  }

  // Dessiner la barre de progression
  display.drawFrame(0, y + 5, l, w);                     // Dessiner le cadre
  int barWidth = (data * l) / scale;                    // Calculer la largeur de la barre
  display.drawBox(1, y + 6, barWidth - 1, w - 2);       // Dessiner la barre (1 pixel de marge)
}

// Fonction générique pour afficher de la data float
void displayDataFloat(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float data, const char * texte, const char * unite, int scale,  int y, int l, int w, const uint8_t* font) {
  char buffer[30]; // Augmenter la taille du buffer pour éviter les dépassements

  // Configuration de la police
  display.setFont(font);

  // Créer la chaîne formatée pour l'affichage
  snprintf(buffer, sizeof(buffer), "%s: %.2f%s", texte, data, unite);
  
  // Afficher le texte
  display.drawStr(0, y, buffer);

  // Limiter "data" à la plage [0, scale] pour éviter les dépassements
  if (data > scale) {
    data = scale;
  } else if (data < 0) {
    data = 0;
  }

  // Dessiner la barre de progression
  display.drawFrame(0, y + 5, l, w);                     // Dessiner le cadre
  int barWidth = (data * l) / scale;                    // Calculer la largeur de la barre
  display.drawBox(1, y + 6, barWidth - 1, w - 2);       // Dessiner la barre (1 pixel de marge)
  // char buffer[20];
  // display.setFont(font); // Petite police pour plus de contenu   
  // // Conversion du nombre en chaîne de caractères
  // sprintf(buffer, "%s:%.2f%s",texte, data, unite);
  // display.drawStr(0, y, buffer);
  // // Barre de progression
  // display.drawFrame(0, y+5, l, w);            // Cadre de la barre
  // display.drawBox(0, y+5, (data * l) / scale, w);  // Remplissage en fonction de "data"
}

void initTCA9548() {
  // Réinitialiser tous les canaux à désactivé (0x00)
  Wire.beginTransmission(0x70);
  Wire.write(0x00);  // Désactive tous les canaux
  Wire.endTransmission();
  delay(5);
}

// Fonctions pour activer un canal sur le TCA9548A
void tcaSelect(uint8_t channel) { 
  //initTCA9548();
  if (channel > 7) return;
  Wire.beginTransmission(0x70);
  Wire.write(1 << channel);
  Wire.endTransmission();
  delay(50); // Temps pour stabiliser le canal (augmenter si nécessaire)
  // Serial.print("Switching to channel: ");
  // Wire.beginTransmission(0x70);
  // Wire.write(channel); 
  // Wire.endTransmission();
}

void scanTCAChannels() {
  for (uint8_t channel = 0; channel < 8; channel++) {
    tcaSelect(channel);
    Serial.print("Scanning channel: ");
    Serial.println(channel);
    for (uint8_t address = 1; address < 127; address++) {
      Wire.beginTransmission(address);
      if (Wire.endTransmission() == 0) {
        Serial.print("Device found at 0x");
        Serial.println(address, HEX);
      }
    }
  }
}

