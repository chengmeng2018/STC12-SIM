//����Ӳ��ͷ�ļ�
#include <STC12C5A60S2.H>
#include "GSMCard.h"
#include "Bluetooth.h"
#include "Output_Control.h"
#include "Time.h"
#include "Command.h"
//������
void main()
{
	DelayTypedef LEDDelay[3];
	
	//�����ʼ��
	TimeInit(1000);//��ʼ����ʱ��
  OutPut_Init();//��ʼ�����
  Bluetooth_Init();//��ʼ������
	GSM_Init();//GSM��ʼ��
	DelayBlocking(15000);//��ʱ15s �ȴ�GSM��������
  while (1)
  {
		checkBluetoothMessage(&LEDDelay);
		ControlLED(&LEDDelay);
  }

}