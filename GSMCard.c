

#include "GSMCard.h"
#include "type.h"
#include "Command.h"
//�������ݻ���
RecBuff GSMBuff;
void GSM_Init()
{
  UART2Init_SIMCard();//��ʼ��GSM
	GSMBuff.begin=0;
	GSMBuff.end=0;
}