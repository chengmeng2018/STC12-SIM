

#include "Bluetooth.h"

#include "Command.h"
#include <STC12C5A60S2.H>

//接收数据缓存
RecBuff BTBuff;
void Bluetooth_Init()
{
  Uart1Init_Bluetooth();
  BTBuff.begin = 0;
  BTBuff.end = 0;
}
char checkMessage()
{
  if (BTBuff.state == NEWMes)
  {
		//findStr(BTBuff.strBuff,);


    //数据处理完毕后开始新的接收
    ES = 1;                 //Enable UART interrupt
  }

  return 0;
}
