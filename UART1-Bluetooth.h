// 蓝牙串口控制模块的接口API
//
#ifndef __UART1_BLUETOOTH_H_
#define __UART1_BLUETOOTH_H_


void Uart1Init_Bluetooth(void);
void UART1_SendData(unsigned char dat);
void UART1_SendString(char *s);

#endif 