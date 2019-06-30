

#include "T2PWM.h"

#include <REGX52.H>

unsigned int PWMcycle = 20000 - 1; //����
unsigned int PWMHTimes = 5000 - 1; //�ߵ�ƽʱ�� 20000us
unsigned int PWMLTimes = 15000 - 1; //�ߵ�ƽʱ�� 20000us


void T2_Init()
{
  // unsigned int time=65536-20000;
  CP_RL2 = 0;
  TCLK = 0;
  RCLK = 0;
  C_T2 = 0;
  TF2 = 0;
  RCAP2L = TL2 = PWMHTimes;            //initial timer2 low byte
  RCAP2H = TH2 = PWMHTimes >> 8;       //initial timer2 high byte
  TR2 = 1;                        //timer2 start running
  ET2 = 1;                        //enable timer2 interrupt
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
void tm2_isr() interrupt 5 using 1//PWM���ƶ�ʱ������
{
  T2_PWMout = ~T2_PWMout;
  TF2 = 0;//��־λ����

  if (T2_PWMout)
  {
    RCAP2L = (0 - PWMLTimes);
    RCAP2H = (0 - PWMLTimes) >> 8;
  }
  else
  {
    RCAP2L = (0 - PWMHTimes);
    RCAP2H = (0 - PWMHTimes) >> 8;
  }
}