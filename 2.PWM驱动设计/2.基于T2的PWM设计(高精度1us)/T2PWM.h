
#ifndef __T2PWM_H__
#define __T2PWM_H__

#define T2_PWMout P2_0  //PWM�������


void T2_Init();

//����վ�ձ���
void SetDutyCycle (float value);
//����ռ�ձ�
void changPWMValue (unsigned int value);
//�趨����Ƕ�
void SetMotoangle (float angle);
#endif