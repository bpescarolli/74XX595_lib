/* Biblioteca utilização do shiftregisters de expansão de saidas com CI 74XX595
   Desenvolvido por: Bruno Pescarolli 
   16-05-2022
*/
#include "Arduino.h"
#include "output_expand74XX595.h"

// constructor
output_expand74XX595::output_expand74XX595(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin, int OE)
{
    // determina os parâmetros
    _numberOfShiftRegisters = numberOfShiftRegisters;
    
    _clockPin = clockPin;
    _serialDataPin = serialDataPin;
    _latchPin = latchPin;
    _OE = OE;
    
    // define os pinos como saida
    pinMode(clockPin, OUTPUT);
    pinMode(serialDataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(OE, OUTPUT);
    
    // incialemente todos em nivel baixo
    digitalWrite(clockPin, LOW);
    digitalWrite(serialDataPin, LOW);
    digitalWrite(latchPin, LOW);
    digitalWrite(OE, LOW);
    
    // aloca quantas saidas terei de acordo com o numero de shift-registers informado
    _digitalValues = (uint8_t *)malloc(numberOfShiftRegisters * sizeof(uint8_t));
    memset(_digitalValues, 0, numberOfShiftRegisters * sizeof(uint8_t));
    
    setAll(_digitalValues); // seta todas as saidas enumeradas.
}


void output_expand74XX595::setAll(uint8_t * digitalValues) {
    int byte;
    
    for (byte = _numberOfShiftRegisters - 1; byte >= 0; byte--) {
        shiftOut(_serialDataPin, _clockPin, LSBFIRST, digitalValues[byte]);
    }
    
    _digitalValues = digitalValues; 
    
    digitalWrite(_latchPin, HIGH); 
    digitalWrite(_latchPin, LOW); 
}

//obtem o estado de todas as saida.
uint8_t * output_expand74XX595::getAll() {
    return _digitalValues; 
}

//determino qual saida irei acionar em qual estado deixarei(LOW ou HIGH)
void output_expand74XX595::set(int pin, uint8_t value) {
  pin--;
    if (value == 1)
        _digitalValues[pin / 8] |= 1 << (pin % 8);
    else
        _digitalValues[pin / 8] &= ~(1 << (pin % 8));
                                     
    setAll(_digitalValues);
}

//obtem o estado de uma determinada saida especifica
uint8_t output_expand74XX595::get(int pin) {
  pin--;
    return (_digitalValues[pin / 8] << (pin % 8)) & 1;
}

//liga todas a saidas enumeradas
void output_expand74XX595::setAllHigh() {
    int i; 
    for (i = 0; i < _numberOfShiftRegisters; i++)
        _digitalValues[i] = 255;
    setAll(_digitalValues); 
}

//desliga todas as saidas enumeradas
void output_expand74XX595::setAllLow() {
    int i; 
    for (i = 0; i < _numberOfShiftRegisters; i++)
        _digitalValues[i] = 0; 
    setAll(_digitalValues); 
}

//aciona uma determinada saida de forma individual
void output_expand74XX595::setPin(int pin){
  setAllLow();
  set(pin, HIGH);
  }
  
//lamp test
void output_expand74XX595::startup(){
  setAllHigh();
  delay(1000);
  setAllLow();
}
