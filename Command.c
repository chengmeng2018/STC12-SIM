


#include "Command.h"
#include "string.h"
#include "Output_Control.h"
//����ָ��ʾ��
// OPEN RED LED
// CLOSE RED LED
// OPEN RED LED 3MIN LATER
// CLOSE RED LED 3MIN LATER

char *Control[] = {"OPEN", "CLOSE"};
char *Device[] = {"LED1", "LED2", "LED3"};
char *Time[]   = {"Sec", "Min", "Hour"};
//char

//
char LEDxCheck(char* str)
{
 char i;
	
return 0;
}

//����Ƿ�Ϊ��������
char OpORclosCheck (char* str)
{
  char i;

  //����Ƿ�Ϊopen
  for (i = 0; i < 4; i++)
  {
    if (str[i] != Control[0][i])
      break;
  }

  if (i == 4)
  {
    return 1;
  }

  //����Ƿ�Ϊclose
  for (i = 0; i < 5; i++)
  {
    if (str[i] != Control[1][i])
      break;
  }

  if (i == 5)
  {
    return 2;
  }

  return 0;

}
void ControlLED (DelayTypedef* LEDDelay)
{
  char i;

  for (i = 0; i < 3; i++)
  {
    DelayNonBlocking (&LEDDelay[i]);

    if (LEDDelay[i].State == Stop)
    {
      LEDx_Write (i, LEDOff);
    }
    else if (LEDDelay[i].State == Ok)
    {
      LEDx_Write (i, LEDOn);
    }
  }

}
char findSpace (char* str, Messinfo* info)
{
  char strlength ;
  strlength = strlen (str) - info->begin;
  str = str + info->begin;
//ȥ����ͷ�Ŀո�
  while ((*str) == ' ')
  {
    str++;
    strlength--;
  }
//Ѱ����һ���ո�λ��
  for ( info->length = 0; info->length < strlength; info->length++)
  {
    if (str[info->length] == ' ' || str[info->length] == '\r')
    {
      info->end = info->begin + info->length;
      return 1;
    }
  }

  return 0;
}
char GetMessage (RecBuff* RecTemp, char Buff)
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

