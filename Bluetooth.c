

#include "Bluetooth.h"

#include "Command.h"
#include <STC12C5A60S2.H>

//接收数据缓存
RecBuff BTBuff;
char BTSBUF[32];
void Bluetooth_Init()
{
  Uart1Init_Bluetooth();
  BTBuff.begin = 0;
  BTBuff.end = 0;
}
char checkBluetoothMessage (DelayTypedef* LEDDelay)
{
  Messinfo info = {0, 0, 0};
  DelayTypedef LEDTemp;
  char recTemp;

  if (BTBuff.state == NEWMes)
  {
    //如果找到了空格
    if (findSpace (&(BTBuff.strBuff[info.begin]), & info) == 1)
    {
      recTemp = OpORclosCheck (&(BTBuff.strBuff[info.begin]));

      if (recTemp)
      {
        LEDTemp.State = recTemp == 1 ? Start : Stop;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
		info.begin=info.end;
    //如果找到了空格
    if (findSpace (&(BTBuff.strBuff[info.begin]), & info) == 1)
    {
      recTemp = LEDxCheck (&(BTBuff.strBuff[info.begin]));
    }
    else
    {

    }

    //数据处理完毕后开始新的接收
    ES = 1;                 //Enable UART interrupt
  }

  return 0;
}
