
#include <REGX52.H>
#include "keyBoard.h"


void delay2ms (void)  //��ʱ����
{
  unsigned char i, j;

  for (i = 133; i > 0; i--)
    for (j = 6; j > 0; j--);
}


unsigned char IndependentKeyboard()
{
  unsigned char keyValue = 0xff;
  keyValue &= ~((!(char)Key0)<<0);
  keyValue &= ~((!(char)Key1)<<1);
  keyValue &= ~((!(char)Key2)<<2);
  keyValue &= ~((!(char)Key3)<<3);
  keyValue &= ~((!(char)Key4)<<4);
  keyValue &= ~((!(char)Key5)<<5);
  keyValue &= ~((!(char)Key6)<<6);
  keyValue &= ~((!(char)Key7)<<7);

  return keyValue;
}
//�������
unsigned char key_scan (KeyStruct* KeyNum)
{
  unsigned char keyValue = 0;
  unsigned char State = KeyNum->State;
  unsigned char KeyTemp = KeyNum->Value;
  /*******������̶�ȡ����******/
  keyValue =	IndependentKeyboard();//�����������

  switch (State)
  {
  case CheckKey://����Ƿ��а�������
    if (keyValue == 0xff)
    {
      break;
    }

    KeyTemp = keyValue;
    State = DelayKey;

  case DelayKey://����ʱ������
    delay2ms();
    State = KeyTemp == keyValue ? KeyFallEdge : CheckKey;
    break;

  case KeyFallEdge://�����½����ź�(��һ��)
    State = KeyDown;
    break;

  case KeyDown://���ذ���״̬(����)
    if (KeyTemp != keyValue)
    {
      State = KeyRisEdge;
      KeyNum->lastValue = KeyTemp;
    }

    break;

  case KeyRisEdge://�����������ź�(һ��)
    State = CheckKey;
    break;

  default:
    break;
  }

  KeyNum->State = State;
  KeyNum->Value = keyValue;
  return State;
}
