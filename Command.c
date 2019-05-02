


#include "Command.h"
//控制指令示例
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

