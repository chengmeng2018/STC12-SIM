

#include "Bluetooth.h"

#include "Command.h"
#include <STC12C5A60S2.H>

//�������ݻ���
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


    //���ݴ�����Ϻ�ʼ�µĽ���
    ES = 1;                 //Enable UART interrupt
  }

  return 0;
}
