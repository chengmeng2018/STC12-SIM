// Header: 8051�ں˵�Ƭ��ͨ�ö�ʱ��T0 T1ͷ�ļ�
// File Name: Time.h
// Author: ����plus
// Date: 2019��4��6��
// Version: V1.1

#include "Time.h"

//#message "Time.h��ʹ��REGX52.Hͷ�ļ�"
#include <STC12C5A60S2.H>


#define FOSC 12000000L      //System frequency
//#message Time.h�趨�ľ���Ƶ��Ϊ 12000000L
//---TMOD��������---//
#define  T0NoReload13B 0x00
#define  T0NoReload16B 0x01
#define  T0Reload8B    0x10
#define  T0dual8B      0x11
#define  T0Count       0x04
#define  T0GATE        0x08

#define  T1NoReload13B 0x00
#define  T1NoReload16B 0x01
#define  T1Reload8B    0x10
#define  T1UnUsed8B    0x11
#define  T1Count       0x40
#define  T1GATE        0x80

//---TCON��������---//

//��ʱ������ֵ
unsigned int T0Reload,T1Reload;

//ȫ��ϵͳʱ��
unsigned int SystemTick =0;

/****************************
//Function Name:  ��ʱ��
//Input : FOSC ����Ƶ��
          Reload ����Ƶ�� Ƶ�ʷ�Χ(100~100000)
//Output: void
//Description:  ��ʱ����ʼ���������ö�ʱ��
//
//***************************/
void TimeInit(unsigned int Reload)
{
    T0_RUN(0);//�ض�ʱ��
    //�趨����ģʽ
    TMOD &=0xf0;
    TMOD |= T0NoReload16B;
    TMOD &= ~T0Count;
    //��ʼֵ�趨
    T0Reload=(65536-FOSC/12/Reload)+9; //��������ֵ ���Զ����ز���9
    TH0=T0Reload>>8;
    TL0=T0Reload;
    EA=1;//�����ж�
    T0_EnIT(1);//����ʱ��0�ж�
		T0_RUN(1);//�ض�ʱ��
}
/****************************
//Function Name:  ��������ʱ����
//Input : void
//Output: ��ʱʱ���Ƿ���
//Description: ��ʱʱ�䲻��������������
//
//***************************/
void DelayNonBlocking(DelayTypedef* DelayStruct)
{
    switch(DelayStruct->State)
    {
    case Stop:
        return;
        break;
    case Start:
        DelayStruct->StartMs=SystemTick;
        DelayStruct->EndMs = DelayStruct->StartMs+DelayStruct->DelayMs;
        DelayStruct->State=Wait;
        break;
    case Wait:
        if( DelayStruct->EndMs > DelayStruct->StartMs)
        {
            if( SystemTick > DelayStruct->EndMs)
            {
                DelayStruct->State=Ok;
            }
            else
            {
                DelayStruct->State=Wait;
            }
        }
        else
        {
            if( SystemTick<DelayStruct->StartMs && SystemTick > DelayStruct->EndMs)
            {
                DelayStruct->State=Ok;
            }
            else
            {
                DelayStruct->State=Wait;
            }
        }
        break;
    case Ok:
        //DelayStruct->State =Stop;
        break;
    }
}
/****************************
//Function Name:  ms����ʱ����
//Input : ��ʱʱ��
//Output: ��ʱ����˳�
//Description:
//
//***************************/
void DelayBlocking(unsigned int Time)
{
    unsigned int CurrentTime=SystemTick;
    while(Time)
    {
        if(CurrentTime!=SystemTick)
        {
            CurrentTime=SystemTick;
            Time--;
        }
    }
}
/****************************
//Function Name:  ��ʱ��0�жϺ���
//Input : void
//Output: void
//Description:
//
//***************************/
void Time0(void) interrupt 1
{
    TH0=T0Reload>>8;
    TL0=T0Reload;
    T0_ClearFlag(0);
    SystemTick++;

}
/****************************
//Function Name:  ��ʱ��1�жϺ���
//Input : void
//Output: void
//Description:
//
//***************************/
void Time1(void) interrupt 3
{

}