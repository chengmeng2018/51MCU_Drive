#include <REGX52.H>
#include "T2PWM.h"

void main()
{
  /*���������ʼ��*/
  T2_Init();
  
  SetDutyCycle(0.5);//ռ�ձ� �ٷֱ��趨
  changPWMValue(10000);
  SetMotoangle(90);
  /*ѭ��ִ�й���*/
  while(1)
  {
  
  }

}