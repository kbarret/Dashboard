#include <U8g2lib.h>
#include <Wire.h>
#include "oled_display.h"

// Configuration pour le multiplexeur I2C TCA9548A
#define TCA9548A_ADDRESS 0x70

// Canaux du TCA9548 (bitmask)
#define CHANNEL_0 0x01  // Canal 0
#define CHANNEL_1 0x02  // Canal 1
#define CHANNEL_2 0x04  // Canal 2
#define CHANNEL_3 0x08  // Canal 3
#define CHANNEL_4 0x10  // Canal 4
#define CHANNEL_5 0x20  // Canal 5
#define CHANNEL_6 0x40  // Canal 6
#define CHANNEL_7 0x80  // Canal 7

// Initialisation de l'écran OLED SH1106 en mode I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C display1(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_HW_I2C display2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_HW_I2C display3(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_HW_I2C display4(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int clt = 24;  
int egt = 58;          
int pressure = 200;
int iat = 15;
float lambda = 1.00;
float lambdaTarget = 0.98;
float pressureHuile = 3.00;
int tempHuile = 100;

void valueTest(){
  clt++;
  if(clt >= 115){
    clt = 0;
  }
  egt = egt + 10;   
  if(egt >= 900){
    egt = 0;
  }
  iat++;
  if(iat >= 115){
    iat = 0;
  }
  pressure = pressure + 10;   
  if(pressure >= 400){
    pressure = 0;
  }
  lambda = lambda + 0.05;   
  if(lambda >= 1.15){
    lambda = 0.55;
  }
  pressureHuile = pressureHuile + 0.5;   
  if(pressureHuile >= 7.00){
    pressureHuile = 1.50;
  }
  tempHuile = tempHuile + 10;   
  if(tempHuile >= 150){
    tempHuile = 0;
  }
}

void setup() {
  Serial.begin(115200);

  // Initialisation de l'écran
  Wire.begin(21, 22);
  
  // Définir la fréquence I2C à 400 kHz
  Wire.setClock(400000); // Fréquence en Hertz (par exemple 400000 pour 400 kHz)
  tcaSelect(0);
  display1.begin();
  tcaSelect(1);
  display2.begin();
  tcaSelect(2);
  display3.begin();
  tcaSelect(3);
  display4.begin();
  initTCA9548();
  //Scan TCA
  scanTCAChannels();
}

void loop() {
  valueTest();

  //ecran 1
  tcaSelect(0);
  display1.firstPage();
  do {
    displayDataInt(display1,clt,"CLT","degC",120,15,128,10,u8g2_font_10x20_me); 
    displayDataInt(display1,egt,"EGT","degC",1200,48,128,10,u8g2_font_10x20_me);
  } while (display1.nextPage());
  
  // //ecran 2
  tcaSelect(1);
  display2.firstPage();
  do {
    displayDataInt(display2,pressure,"MAP","Kpa",400,15,128,10,u8g2_font_10x20_me); 
    displayDataInt(display2,iat,"IAT","degC",120,48,128,10,u8g2_font_10x20_me);
  } while (display2.nextPage());
  
  
  // //ecran 3
  tcaSelect(2);
  display3.firstPage();
  do {
  displayDataFloat(display3,lambda,"Lambda"," ",2,15,128,10,u8g2_font_10x20_me); 
  displayDataFloat(display3,lambdaTarget,"target"," ",2,48,128,10,u8g2_font_10x20_me);
  } while (display3.nextPage());
  
  //ecran 4
  tcaSelect(3);
  display4.firstPage();
  do {
  displayDataFloat(display4,pressureHuile,"Oil","Bar",7,15,128,10,u8g2_font_10x20_me); 
  displayDataInt(display4,tempHuile,"Oil","degC",150,48,128,10,u8g2_font_10x20_me); 
  } while (display4.nextPage());
}



// #include <U8g2lib.h>
// #include "oled_display.h"

// // Initialisation de l'écran SH1106 en utilisant I2C
// // Remplacez U8G2_R0 par une autre rotation si nécessaire (R0 = normale, R1 = 90°, etc.)
// U8G2_SH1106_128X64_NONAME_F_HW_I2C display1(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// //variable
// float egt = 750.2;

// void setup() {
//   // Initialisation de l'écran
//   display1.begin();
//   display1.clearBuffer();

//   // Définir la police
//   display1.setFont(u8g2_font_ncenB08_tr); 
//   display1.drawStr(0, 15, "EGT:");
//   display1.sendBuffer();
//   // Optionnel : Réglage de la luminosité (si le module le supporte via logiciel)
//   display1.setContrast(0); // Entre 0 et 255

//   // Affichage d'un texte de bienvenue au démarrage
// }

// void loop() {

//   displayData(display1, egt, 1000, 0, 20, 128, 10, u8g2_font_10x20_me);
//   // Exemple d'affichage dynamique
//   // for (int i = 0; i <= 1000; i++) {
//   //   display1.firstPage();
//   //   do {
//   //     display1.setFont(u8g2_font_10x20_me); // Petite police pour plus de contenu
//   //     //display1.drawStr(0, 10, "Progression:");
      
//   //     // Conversion du nombre en chaîne de caractères
//   //     char buffer[10];
//   //     sprintf(buffer, "EGT: %d\xB0""C", i);
//   //     display1.drawStr(0, 15, buffer);

//   //     // Barre de progression EGT
//   //     display1.drawFrame(0, 20, 128, 10);            // Cadre de la barre
//   //     display1.drawBox(0, 20, (i * 128) / 1000, 10);  // Remplissage en fonction de "i"

//   //     sprintf(buffer, "CLT: %d\xB0""C", i/10);
//   //     display1.drawStr(0, 49, buffer);

//   //     // Barre de progression CLT
//   //     display1.drawFrame(0, 54, 128, 10);            // Cadre de la barre
//   //     display1.drawBox(0, 54, (i * 128) / 1000, 10);  // Remplissage en fonction de "i"

//   //   } while (display1.nextPage());

//     //delay(100); // Pause entre chaque mise à jour
//   //}
// }



  // Démarre un nouveau cycle de mise à jour
  // display.firstPage();
  // do {
  //   // Afficher les éléments fixes (pas de besoin de les redessiner à chaque cycle)
  //   display.drawStr(0, 20, "Temperature");
  //   display.drawStr(0, 40, "Humidity");

  //   // Effacer uniquement les zones dynamiques avant de redessiner
  //   //display.drawBox(0, 60, 128, 24);  // Effacer la zone de la température
  //   //display.drawBox(0, 50, 128, 24);  // Effacer la zone de l'humidité

  //   // Afficher les nouvelles valeurs
  //   char tempBuffer[20];
  //   sprintf(tempBuffer, "%.2f C", temperature);
  //   display.drawStr(0, 60, tempBuffer);  // Affiche la température à la position (0, 60)

  //   char humBuffer[20];
  //   sprintf(humBuffer, "%d%%", humidity);
  //   display.drawStr(0, 50, humBuffer);  // Affiche l'humidité à la position (0, 50)

  // } while (display.nextPage());  // Envoie les nouvelles données à l'écran

 