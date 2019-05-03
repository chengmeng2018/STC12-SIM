
#include "Output_Control.h"
#include <STC12C5A60S2.H>


//Êä³öÒý½Å¿ØÖÆ
sbit LED0 = P1 ^ 0;
sbit LED1 = P1 ^ 1;
sbit LED2 = P1 ^ 2;

void OutPut_Init()
{
  LED0 = LEDOff;
  LED1 = LEDOff;
  LED2 = LEDOff;
}
void LEDx_Write (char LEDx, char state)
{
  switch (LEDx)
  {
  case 0:
    LED0 = state;
    break;

  case 1:
    LED1 = state;
    break;

  case 2:
    LED2 = state;
    break;

  default:
    break;
  }

}