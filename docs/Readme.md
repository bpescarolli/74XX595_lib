## Descrição
È um projeto de exemplo de utilização da biblioteca "output_expand74XX595" , com objetivo de montar interfaces de expansão de saida para o arduino de forma escalonada de acordo com a necessidade de projeto.

## Exemplo de aplicação
Aqui temos um exemplo de aplicação do uso da biblioteca para um projeto onde temos uma interface de expansão de saida com 4 chips 74XX595 ligados em cascata tento ao todo 32 saidas.

Neste exemplo   iremos acionar estas saidas via serial de forma individual.

Observação: se chama 74XX595 , onde pode ser aplicado a qualquer familia de Ci´s 74 ... por exemplo 74LS595, 74HC595 seja PTH ou SMD.

![](https://raw.githubusercontent.com/bpescarolli/74XX595_lib/master/circuit.jpg)

## Utilizando a biblioteca
Declarando a biblioteca e parametrizando ...
```
#define NUMBER_OF_REGISTERS 4 // numero de chips 
#include "output_expand74XX595.h"
int outputs_calculed = (NUMBER_OF_REGISTERS * 8); 
/* Parametrização feita da seguinte sequecia:
N° Registradores, 
pino DATA,digital 13 do arduino
pino Clock,digital 12 do arduino
pino latch,digital 11 do arduino
pino OE digital 10 do arduino */ 
output_expand74XX595 output(NUMBER_OF_REGISTERS,13,12,11,10);
```
Acionando via serial de forma individual ...
```
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
}
  
}
```
## Demais comandos presentes nesta biblioteca.
Em breve. 😉