//����Ӳ��ͷ�ļ�
#include <STC12C5A60S2.H>
#include "GSMCard.h"
#include "Bluetooth.h"
#include "Output_Control.h"


//������
void main()
{
	//�����ʼ��
  OutPut_Init();//��ʼ�����
  Bluetooth_Init();//��ʼ������
	GSM_Init();//GSM��ʼ��
  while (1)
  {

  }

}