//内置硬件头文件
#include <STC12C5A60S2.H>
#include "GSMCard.h"
#include "Bluetooth.h"
#include "Output_Control.h"
#include "Time.h"
#include "Command.h"
//主程序
void main()
{
	DelayTypedef LEDDelay[3];
	
	//外设初始化
	TimeInit(1000);//初始化定时器
  OutPut_Init();//初始化输出
  Bluetooth_Init();//初始化蓝牙
	GSM_Init();//GSM初始化
	DelayBlocking(15000);//延时15s 等待GSM启动联网
  while (1)
  {
		checkBluetoothMessage(&LEDDelay);
		ControlLED(&LEDDelay);
  }

}