


#include "Command.h"
//����ָ��ʾ��
// OPEN RED LED
// CLOSE RED LED
// OPEN RED LED 3MIN LATER
// CLOSE RED LED 3MIN LATER

char *Control[] = {"OPEN", "CLOSE"};
char *Device[] = {"LED1", "LED2", "LED3"};
char *Time[]   = {"Sec", "Min", "Hour"};
//char

char GetMessage (RecBuff* RecTemp,char Buff)
{
  switch (RecTemp->state)
  {
  case WAITMes:
			RecTemp->state = RECMes;
  case RECMes:
    //�ж�ʱ����յ���β
    RecTemp->strBuff[RecTemp->end] = Buff;          //ѭ����������

    if (RecTemp->strBuff[RecTemp->end] == '\r')
    {
      RecTemp->state =	NEWMes;
    }
    else
    {
      RecTemp->end = (RecTemp->end + 1) % _BuffLengh;
    }
  case NEWMes://�Ѿ������յ����� ����������׼������
    RecTemp->state = WAITMes;
    RecTemp->end = 0;

  default:
    break;
  }
	return RecTemp->state;
}

