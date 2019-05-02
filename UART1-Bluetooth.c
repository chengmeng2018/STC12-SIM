

#include "reg51.h"
#include "intrins.h"
#include "UART1-Bluetooth.h"
#include "Command.h"
#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT NONE_PARITY   //Testing even parity
bit Uart1_busy;

void UART1_SendData (unsigned char  dat);
void UART1_SendString (char *s);

void Uart1Init_Bluetooth()
{
#if (PARITYBIT == NONE_PARITY)
  SCON = 0x50;            //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
  SCON = 0xda;            //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
  SCON = 0xd2;            //9-bit variable UART, parity bit initial to 0
#endif
  TMOD &= 0x0f;
  TMOD |= 0x20;            //Set Timer1 as 8-bit auto reload mode
  TH1 = TL1 = - (FOSC / 12 / 32 / BAUD); //Set auto-reload vaule
  TR1 = 1;                //Timer1 start run
  ES = 1;                 //Enable UART interrupt
  EA = 1;                 //Open master interrupt switch

}

/*----------------------------
UART interrupt service routine
----------------------------*/
extern  RecBuff BTBuff;
void Uart_Isr() interrupt 4
{
  if (RI)
  {
    RI = 0;             //Clear receive interrupt flag
    //接收数据
		if( GetMessage (&BTBuff, SBUF)==NEWMes)
		{
			ES=0;//关串口等待书处理
		}
  }

  if (TI)
  {
    TI = 0;             //Clear transmit interrupt flag
    Uart1_busy = 0;           //Clear transmit busy flag
  }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void UART1_SendData (unsigned char  dat)
{
  while (Uart1_busy);           //Wait for the completion of the previous data is sent

  ACC = dat;              //Calculate the even parity bit P (PSW.0)

  if (P)                  //Set the parity bit according to P
  {
#if (PARITYBIT == ODD_PARITY)
    TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
    TB8 = 1;            //Set parity bit to 1
#endif
  }
  else
  {
#if (PARITYBIT == ODD_PARITY)
    TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
    TB8 = 0;            //Set parity bit to 0
#endif
  }

  Uart1_busy = 1;
  SBUF = ACC;             //Send data to UART buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void UART1_SendString (char *s)
{
  while (*s)              //Check the end of the string
  {
    UART1_SendData (*s++);    //Send current char and increment string ptr
  }
}

