

#include "Bluetooth.h"
#include "type.h"
#include "Command.h"
//�������ݻ���
RecBuff BTBuff;
void Bluetooth_Init()
{
  Uart1Init_Bluetooth();
	BTBuff.begin=0;
	BTBuff.end=0;
}
char checkMessage()
{
	
	return 0;
}