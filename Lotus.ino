/*
   On : FC03EF00
Off : FD02EF00

Haut : FF00EF00
Bas : FE01EF00


Blanc : F807EF00

Rouge : FB04EF00
Orange : F708EF00
Orange + : F30CEF00
Orange ++ : EF10EF00
Jaune : EB14EF00

Vert foncé : FA05EF00
Vert : F609EF00
Cyan : F20DEF00
Cyanfoncé : EE11EF00
Cyanfoncé+ : EA15EF00


Bleu nuit : F906EF00
Bleu : F50AEF00
Mauve : F10EEF00
Violet : ED12EF00
Magenta : E916EF00
*/

#include <IRremote.hpp>
#include <FastLED.h>

const int pinIR = 2;

const int NLed = 23;
const int LedPin = 3;
CRGB Leds[NLed];
int R=0;
int G=0;
int B=0;
bool OnOff;

float ValeursCoeff[] = {0.00, 0.15, 0.30, 0.45, 0.60, 0.75, 0.90, 1.00};
int IndiceCoeff = 8;
int Coeff;

void setup()
{

  IrReceiver.begin(pinIR, ENABLE_LED_FEEDBACK); // Start the receiver
  FastLED.addLeds<WS2812B, LedPin, RGB>(Leds, NLed);
  Serial.begin(9600);

  for(int i=0; i<NLed; i++)
        {
        Leds[i] = CRGB(0,0,0);
        FastLED.show();
        delay(15);
        }
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data

      IrReceiver.resume(); // Enable receiving of the next value
      if(IrReceiver.decodedIRData.decodedRawData == 0xFB04EF00) {G=0; R=255; B=0;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xF708EF00) {G=72; R=140; B=0;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xF30CEF00) {G=96; R=190; B=0;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xEF10EF00) {G=128; R=255; B=0;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xEB14EF00) {G=150; R=255; B=0;}

      if(IrReceiver.decodedIRData.decodedRawData == 0xFA05EF00) {G=153; R=0; B=0;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xF609EF00) {G=255; R=0; B=0;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xF20DEF00) {G=255; R=0; B=255;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xEE11EF00) {G=204; R=0; B=204;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xEA15EF00) {G=153; R=0; B=153;}

      if(IrReceiver.decodedIRData.decodedRawData == 0xF906EF00) {G=0; R=0; B=153;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xF50AEF00) {G=0; R=0; B=255;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xF10EEF00) {G=0; R=102; B=102;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xED12EF00) {G=0; R=120; B=1200;}
      if(IrReceiver.decodedIRData.decodedRawData == 0xE916EF00) {G=0; R=255; B=255;}

      if(IrReceiver.decodedIRData.decodedRawData == 0xF807EF00) {G=80; R=80; B=80;}
      /*
       * Bleu nuit : F906EF00
Bleu : F50AEF00
Mauve : F10EEF00
Violet : ED12EF00
Magenta : E916EF00
       */

      
      if(IrReceiver.decodedIRData.decodedRawData == 0xFF00EF00 && IndiceCoeff != 8) IndiceCoeff++;
      if(IrReceiver.decodedIRData.decodedRawData == 0xFE01EF00 && IndiceCoeff != 0) IndiceCoeff--;
      
      if(IrReceiver.decodedIRData.decodedRawData == 0xFC03EF00) OnOff = true;
      if(IrReceiver.decodedIRData.decodedRawData == 0xFD02EF00) OnOff = false;
      
      if(OnOff){
        for(int i=0; i<NLed; i++)
        {
        Leds[i] = CRGB(G*ValeursCoeff[IndiceCoeff-1],R*ValeursCoeff[IndiceCoeff-1],B*ValeursCoeff[IndiceCoeff-1]);
        FastLED.show();
        delay(15);
        }
      }
      
      if(!OnOff)
      {
        for(int i=0; i<NLed; i++)
        {
        Leds[i] = CRGB(0,0,0);
        FastLED.show();
        delay(15);
        }
      }

        

      

      
      
      
  }
  Serial.println(OnOff);
}
