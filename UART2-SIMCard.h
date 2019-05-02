// SIMCard串口控制模块的接口API
//
#ifndef __UART1_SIMCARD_H_
#define __UART1_SIMCARD_H_


void UART2Init_SIMCard();
void UART2_SendData(unsigned char  dat);
void UART2_SendString(char *s);


#endif 