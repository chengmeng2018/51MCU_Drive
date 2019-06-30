
#include <REGX52.H>
#include "keyBoard.h"


void delay2ms (void)  //��ʱ����
{
  unsigned char i, j;

  for (i = 133; i > 0; i--)
    for (j = 6; j > 0; j--);
}
unsigned char 	GetMatrixKeyboard()
{
  unsigned char KeyValue = 0x00;
  //������Ŷ�ȡ���ļ�ֵ
  MatrixKeyboard = 0X0F;
  delay2ms();
  KeyValue |= MatrixKeyboard & 0x0F;
  //������
  MatrixKeyboard = 0XF0;
  delay2ms();
  KeyValue |= MatrixKeyboard &0xF0;
  return KeyValue;
}

//�������
unsigned char key_scan (KeyStruct* KeyNum)
{
  unsigned char keyValue = 0;
  unsigned char State = KeyNum->State;
  unsigned char KeyTemp = KeyNum->Value;

  /*******������̶�ȡ����****/
  keyValue = GetMatrixKeyboard();

  switch (State)
  {
  case CheckKey:
    if (keyValue == 0xFF)
    {
      break;
    }

    KeyTemp = keyValue;
    State = DelayKey;

  case DelayKey:
    delay2ms();
    State = KeyTemp == keyValue ? KeyFallEdge : CheckKey;
    break;

  case KeyFallEdge:
    State = KeyDown;
    break;

  case KeyDown:
    if (KeyTemp != keyValue)
    {
      State = KeyRisEdge;
      KeyNum->lastValue = KeyTemp;
    }

    break;

  case KeyRisEdge:
    State = CheckKey;
    break;

  default:
    break;
  }

  KeyNum->State = State;
  KeyNum->Value = keyValue;
  return State;
}
