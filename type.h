
//通用数据类型

#ifndef __TYPE_H_
#define __TYPE_H_


#define _BuffLengh 32
typedef struct
{
	char begin;
	char end;
	char state;
	char strBuff[_BuffLengh];
}RecBuff;

enum RecState{NEWMes,WAITMes,RECMes};

#endif