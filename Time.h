// Header: 8051�ں˵�Ƭ��ͨ�ö�ʱ��T0 T1ͷ�ļ�
// File Name: Time.h
// Author: ����plus
// Date: 2019��4��6��
// Version: V1.0

#ifndef  __TIME_H_
#define  __TIME_H_


enum DelayState{Stop,Start,Wait,Ok};
//��ʱ����ʱ����
typedef struct
{
    unsigned int DelayMs;//�趨��ʱʱ��
    unsigned char State;
    unsigned int StartMs;//�ڲ�ʵ�� ��������ʱ��
    unsigned int EndMs;  //�ڲ�ʵ�� ��ʱ����ʱ��
} DelayTypedef;


#define T0_RUN(State) (TR0=State)
#define T1_RUN(State) (TR1=State)
#define T0_ClearFlag(State) (TF0=State)
#define T1_ClearFlag(State) (TF1=State)
#define T0_EnIT(State)  (ET0=State)
#define T1_EnIT(State)  (ET1=State)
//��ʱ����ʼ������ Reload ����Ƶ�� Ƶ�ʷ�ΧԼ(100~100000)
void TimeInit(unsigned int Reload);
//������ʱ����
void DelayNonBlocking(DelayTypedef* DelayStruct);
//��������ʱ����
void DelayBlocking(unsigned int Time);

#endif