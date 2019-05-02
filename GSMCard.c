

#include "GSMCard.h"
#include "type.h"
#include "Command.h"
//接收数据缓存
RecBuff GSMBuff;
void GSM_Init()
{
  UART2Init_SIMCard();//初始化GSM
	GSMBuff.begin=0;
	GSMBuff.end=0;
}