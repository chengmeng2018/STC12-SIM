

#include "Bluetooth.h"
#include "type.h"
#include "Command.h"
//接收数据缓存
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