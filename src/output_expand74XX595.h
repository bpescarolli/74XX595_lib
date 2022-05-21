/* Biblioteca utilização do shiftregisters de expansão de saidas com CI 74XX595
   Desenvolvido por: Bruno Pescarolli 
   16-05-2022
*/
#ifndef output_expand74XX595_h
#define output_expand74XX595_h

#include "Arduino.h"

class output_expand74XX595{
  public:
    output_expand74XX595(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin, int OE);
    void startup(); //blink de inicialização
    void setAll(uint8_t * digitalValues);
    uint8_t * getAll(); 
    void set(int pin, uint8_t value);
    void setPin(int pin);
    void setAllLow();
    void setAllHigh(); 
    uint8_t get(int pin);
  private:
    int _numberOfShiftRegisters;
    int _clockPin;
    int _serialDataPin;
    int _latchPin;
    int _OE;
    uint8_t * _digitalValues;
};
#endif
