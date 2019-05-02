
/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC12C5Axx Series MCU UART2 (8-bit/9-bit)Demo ---------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

#include "reg51.h"
#include "intrins.h"
#include "UART2-SIMCard.h"


#define FOSC 11059200L      //System frequency
#define BAUD 115200         //UART baudrate

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT EVEN_PARITY   //Testing even parity

/*Declare SFR associated with the UART2 */
sfr AUXR  = 0x8e;           //Auxiliary register
sfr S2CON = 0x9a;           //UART2 control register
sfr S2BUF = 0x9b;           //UART2 data buffer
sfr BRT   = 0x9c;           //Baudrate generator
sfr IE2   = 0xaf;           //Interrupt control 2

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3

bit UART2_busy;

void UART2_SendData (unsigned char  dat);
void UART2_SendString (char *s);

void UART2Init_SIMCard()
{
#if (PARITYBIT == NONE_PARITY)
  S2CON = 0x50;           //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
  S2CON = 0xda;           //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
  S2CON = 0xd2;           //9-bit variable UART, parity bit initial to 0
#endif

  BRT = - (FOSC / 32 / BAUD); //Set auto-reload vaule of baudrate generator
  AUXR = 0x14;            //Baudrate generator work in 1T mode
  IE2 = 0x01;             //Enable UART2 interrupt
  EA = 1;                 //Open master interrupt switch

}

/*----------------------------
UART2 interrupt service routine
----------------------------*/
void Uart2() interrupt 8
{
  if (S2CON & S2RI)
  {
    S2CON &= ~S2RI;     //Clear receive interrupt flag
    P0 = S2BUF;         //P0 show UART data
    P2 = (S2CON & S2RB8);//P2.2 show parity bit
  }

  if (S2CON & S2TI)
  {
    S2CON &= ~S2TI;     //Clear transmit interrupt flag
    UART2_busy = 0;           //Clear transmit busy flag
  }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void UART2_SendData (unsigned char  dat)
{
  while (UART2_busy);           //Wait for the completion of the previous data is sent

  ACC = dat;              //Calculate the even parity bit P (PSW.0)

  if (P)                  //Set the parity bit according to P
  {
#if (PARITYBIT == ODD_PARITY)
    S2CON &= ~S2TB8;    //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
    S2CON |= S2TB8;     //Set parity bit to 1
#endif
  }
  else
  {
#if (PARITYBIT == ODD_PARITY)
    S2CON |= S2TB8;     //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
    S2CON &= ~S2TB8;    //Set parity bit to 0
#endif
  }

  UART2_busy = 1;
  S2BUF = ACC;            //Send data to UART2 buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void UART2_SendString (char *s)
{
  while (*s)              //Check the end of the string
  {
    UART2_SendData (*s++);    //Send current char and increment string ptr
  }
}

