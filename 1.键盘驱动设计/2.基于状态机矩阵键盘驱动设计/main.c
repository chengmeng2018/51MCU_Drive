// Header:  From https://github.com/chengmeng2018/51MCU_Drive.git
// File Name: main
// Author: chengmeng2018
// Date: 2019-06-30
//version: v1.0
//Note: ��������Լ�����
#include <REGX52.H>
#include <stdio.h>
#include "keyBoard.h"

#define OutLED P2
void InitUART(void);//ʹ�ö�ʱ��1��Ϊ���ڲ����ʷ�����
void main()
{
    KeyStruct KeyNum;
    unsigned char KeyState;
    unsigned char str[32];
  InitUART();
    while(1)
    {
        KeyState = key_scan(&KeyNum);//�������
        if(KeyState==KeyFallEdge)
        {
            sprintf(str,"KeyState:%d Keynum:%d \r\n ",(unsigned int)KeyState,(unsigned int)(KeyNum.Value));
            printf(str);
          OutLED=KeyNum.Value;
        }
    }
}
//��дputchar����
char putchar(char c)
{
    ES=0;           //�ش����ж�
    SBUF=c;           
    while(TI!=1);   //�ȴ����ͳɹ�
    TI=0;           //��������жϱ�־
    ES=1;           //�������ж�
    return c;
}

void InitUART(void)//ʹ�ö�ʱ��1��Ϊ���ڲ����ʷ�����
{
    TH1 = 0xFD;	 //����11.0592mhz ��������Ϊ9600
    TL1 = TH1;
    TMOD |= 0x20;	 //��ʱ��1��ʽ2
    SCON = 0x50;	 //���ڽ���ʹ��
    ES = 1;			 //�����ж�ʹ��
    TR1 = 1;		 //��ʱ��1ʹ��
    TI = 1;			 //�����жϱ��λ����������
}