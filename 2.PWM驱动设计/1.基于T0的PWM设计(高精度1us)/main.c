#include <REGX52.H>
#include "T0PWM.h"

void main()
{
  /*���������ʼ��*/
  T0_Init();
  
  SetDutyCycle(0.5);//ռ�ձ� �ٷֱ��趨
  changPWMValue(10000);
  //SetMotoangle(90);
  /*ѭ��ִ�й���*/
  while(1)
  {
  
  }

}