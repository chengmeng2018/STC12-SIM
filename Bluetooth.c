

#include "Bluetooth.h"

#include "Command.h"
#include <STC12C5A60S2.H>

//�������ݻ���
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
    //����ҵ��˿ո�
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
    //����ҵ��˿ո�
    if (findSpace (&(BTBuff.strBuff[info.begin]), & info) == 1)
    {
      recTemp = LEDxCheck (&(BTBuff.strBuff[info.begin]));
    }
    else
    {

    }

    //���ݴ�����Ϻ�ʼ�µĽ���
    ES = 1;                 //Enable UART interrupt
  }

  return 0;
}
