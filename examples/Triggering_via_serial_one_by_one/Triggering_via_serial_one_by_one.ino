/* Programa de exemplo de aplicação da biblioteca output_expand74XX595.
   Desenvolvido por: Bruno Pescarolli 
   16-05-2022
*/

#define NUMBER_OF_REGISTERS 4 // numero de chips 
#include "output_expand74XX595.h"
int outputs_calculed = (NUMBER_OF_REGISTERS * 8); // calcula o numero de saidas
//Parametrização feita da seguinte sequecia --> N° Registradores, pino DATA, pino Clock, pino latch, pino OE// 
output_expand74XX595 output(NUMBER_OF_REGISTERS,13,12,11,10);

void setup(){
Serial.begin(9600);
Serial.println("Inciando...");
output.startup();//lamp test ligo faço um blink com ligando todas as saidas
Serial.print("Numero de saidas ... ");
Serial.println(outputs_calculed);
Serial.println("");
}

void loop(){
//Digite qualquer saida do CI via serial monitor que será acionado de forma individual.
while(Serial.available() >0){
    int data = Serial.parseInt();
    if (data > outputs_calculed){
        Serial.println("Esta saida nao existe");
        } else if(Serial.read() > 0){
        Serial.print("Acionando a saida ");
        Serial.print(data);
        Serial.println("");
        output.setPin(data);
    }
    Serial.println(output.get(30));
}
  
}
