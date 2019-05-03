


#include "Command.h"
#include "string.h"
#include "Output_Control.h"
//控制指令示例
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

//检查是否为开关命令
char OpORclosCheck (char* str)
{
  char i;

  //检测是否为open
  for (i = 0; i < 4; i++)
  {
    if (str[i] != Control[0][i])
      break;
  }

  if (i == 4)
  {
    return 1;
  }

  //检测是否为close
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
//去除开头的空格
  while ((*str) == ' ')
  {
    str++;
    strlength--;
  }
//寻找下一个空格位置
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
    //判断时候接收到结尾
    RecTemp->strBuff[RecTemp->end] = Buff;          //循环接收数据

    if (RecTemp->strBuff[RecTemp->end] == '\r')
    {
      RecTemp->state =	NEWMes;
    }
    else
    {
      RecTemp->end = (RecTemp->end + 1) % _BuffLengh;
    }

  case NEWMes://已经完整收到数据 这里做清理准备操作
    RecTemp->state = WAITMes;
    RecTemp->end = 0;

  default:
    break;
  }

  return RecTemp->state;
}

