//内置硬件头文件
#include <STC12C5A60S2.H>
#include "GSMCard.h"
#include "Bluetooth.h"
#include "Output_Control.h"


//主程序
void main()
{
	//外设初始化
  OutPut_Init();//初始化输出
  Bluetooth_Init();//初始化蓝牙
	GSM_Init();//GSM初始化
  while (1)
  {

  }

}