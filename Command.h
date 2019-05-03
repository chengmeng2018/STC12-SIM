
//øÿ÷∆÷∏¡Ó

#ifndef __COMMAND_H_
#define __COMMAND_H_

#include "type.h"
#include "Time.h"
typedef struct
{
  char begin;
  char end;
  char length;

} Messinfo;


char GetMessage (RecBuff* RecTemp, char Buff);
char findSpace(char* str,Messinfo* info);
void ControlLED(DelayTypedef* LEDDelay);
char OpORclosCheck(char* str);
char LEDxCheck(char* str);
#endif