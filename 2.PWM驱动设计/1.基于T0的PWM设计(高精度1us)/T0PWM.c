

#include "T0PWM.h"

#include <REGX52.H>

unsigned int PWMcycle = 20000 - 1-0x1A; //����
unsigned int PWMHTimes = 5000 - 1; //�ߵ�ƽʱ�� 20000us
unsigned int PWMLTimes = 15000 - 1; //�ߵ�ƽʱ�� 20000us


void T0_Init()
{
  TMOD = TMOD & 0xf0 | 0x01; //T0 16λ�ֶ�����
  TF0 = 0;
  TL0 = PWMHTimes;            //initial timer0 low byte
  TH0 = PWMHTimes >> 8;       //initial timer0 high byte
  TR0 = 1;                        //timer0 start running
  ET0 = 1;                        //enable timer0 interrupt
  EA = 1;                         //open global interrupt switch
}

//����վ�ձ���
void SetDutyCycle (float value)
{

  PWMHTimes = value * PWMcycle;
  PWMLTimes = PWMcycle - PWMHTimes;
}

void changPWMValue (unsigned int value)
{
  value = value > PWMcycle ? PWMcycle : value; //��ֹԽ��
  PWMHTimes = value;
  PWMLTimes = PWMcycle - PWMHTimes;
}


//����Ŀ��Ʒ�Χ 500us ~2500us ->0��~180��
void SetMotoangle (float angle)
{
  //    //��ֹԽ������˵��
  if (angle > 175) angle = 175;

  if (angle < 5) angle = 5;

  PWMHTimes = 500 + angle * 2000.0 / 180; //������ߵ�ƽʱ��
  PWMLTimes = PWMcycle - PWMHTimes;
}

/*****PWM����˵��************/
// 0xB1E0 = 65536-PWM����(20ms)
// PWMTimes Ϊ�ߵ�ƽ����ʱ��
/* Timer2 interrupt routine */
void tm0_isr() interrupt 1 using 1//PWM���ƶ�ʱ������
{
  T0_PWMout = ~T0_PWMout;

  if (T0_PWMout)
  {
    TL0 = (0 - PWMHTimes);
    TH0 = (0 - PWMHTimes) >> 8;

  }
  else
  {
    TL0 = (0 - PWMLTimes);
    TH0 = (0 - PWMLTimes) >> 8;
  }
}