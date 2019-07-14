#include "DS1302.h"
#include<intrins.h>
#define Delay1us()   _nop_()

//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
unsigned  char  code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
unsigned  char  code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
unsigned  char  TIME[7] = {0, 0, 0x12, 0x01, 0x01, 0x02, 0x13};

void Ds1302Write (unsigned char  addr, unsigned  char  dat);
unsigned char Ds1302Read (unsigned  char  addr);

void Ds1302Init()
{
  unsigned  char  n;
  Ds1302Write (0x8E, 0X00);		 //��ֹд���������ǹر�д��������

  for (n = 0; n < 7; n++) //д��7���ֽڵ�ʱ���źţ�����ʱ��������
  {
    //Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);
  }

  Ds1302Write (0x8E, 0x80);		 //��д��������
}

char BCD2HEX (char BCD)
{
  char date;
  date = BCD & 0xf0 * 10 + BCD & 0x0f;
  return date;
}
char HEX2BCD (char HEX)
{
  char date;
  date =  HEX%10+(HEX/10%10)<<4;
  return date;
}
#define _BCD2HEX(BCD) BCD & 0xf0 * 10 + BCD & 0x0f
#define _HEX2BCD(HEX) HEX%10+(HEX/10%10)<<4;
void ReadTime (Ds1302_TypeDef* time)
{
  char tmp;
  /*��ȡ��*/
  tmp = Ds1302Read (READ_RTC_ADDR[0]);
  time->sec = BCD2HEX (tmp);
  /*��ȡ��*/
  tmp = Ds1302Read (READ_RTC_ADDR[1]);
  time->min = _BCD2HEX (tmp);
  /*��ȡʱ*/
  tmp = Ds1302Read (READ_RTC_ADDR[2]);

  if (tmp & 0x80)
  {
    time->mode = (tmp & 0x20)? PM: AM;
    time->hour = tmp & 0x10 * 10 + tmp & 0x0f;
  }
  else
  {
    time->mode = H24;
    time->hour = _BCD2HEX(tmp);
  }

  time->hour = BCD2HEX (tmp);
  /*��ȡ��*/
  tmp = Ds1302Read (READ_RTC_ADDR[3]);
  time->date = BCD2HEX (tmp);
  /*��ȡ��*/
  tmp = Ds1302Read (READ_RTC_ADDR[4]);
  time->mon = BCD2HEX (tmp);
  /*��ȡ��*/
  tmp = Ds1302Read (READ_RTC_ADDR[5]);
  time->day = BCD2HEX (tmp);
  /*��ȡ��*/
  tmp = Ds1302Read (READ_RTC_ADDR[6]);
  time->year = BCD2HEX (tmp);
}
void WriteTime(Ds1302_TypeDef* time)
{
  char tmp;
  /*д����*/
  tmp=time->sec;
  tmp=_HEX2BCD(tmp);
  Ds1302Write(WRITE_RTC_ADDR[0],tmp);
  /*д���*/
  tmp=time->min;
  tmp=_HEX2BCD(tmp);
  Ds1302Write(WRITE_RTC_ADDR[1],tmp);
  /*д��ʱ*/
  tmp=time->hour;
  tmp=_HEX2BCD(tmp);
  if(time->mode !=H24)tmp |=(time->mode =AM)?0 :0x20;
  Ds1302Write(WRITE_RTC_ADDR[2],tmp);
  /*д����*/
  tmp=time->date;
  tmp=_HEX2BCD(tmp);
  Ds1302Write(WRITE_RTC_ADDR[3],tmp);
  /*д����*/
  tmp=time->mon;
  tmp=_HEX2BCD(tmp);
  Ds1302Write(WRITE_RTC_ADDR[4],tmp);
  /*д����*/
  tmp=time->day;
  tmp=_HEX2BCD(tmp);
  Ds1302Write(WRITE_RTC_ADDR[5],tmp);
  /*д����*/
  tmp=time->year;
  tmp=_HEX2BCD(tmp);
  Ds1302Write(WRITE_RTC_ADDR[6],tmp);

}
void Ds1302Write (unsigned  char  addr, unsigned  char  dat)
{
  unsigned  char  n;
  CE = 0;
  Delay1us();

  SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
  Delay1us();
  CE = 1; //Ȼ��CE(CE)�øߵ�ƽ��
  Delay1us();

  for (n = 0; n < 8; n++) //��ʼ���Ͱ�λ��ַ����
  {
    DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
    addr >>= 1;
    SCLK = 1;//������������ʱ��DS1302��ȡ����
    Delay1us();
    SCLK = 0;
    Delay1us();
  }

  for (n = 0; n < 8; n++) //д��8λ����
  {
    DSIO = dat & 0x01;
    dat >>= 1;
    SCLK = 1;//������������ʱ��DS1302��ȡ����
    Delay1us();
    SCLK = 0;
    Delay1us();
  }

  CE = 0;//�������ݽ���
  Delay1us();
}


unsigned char Ds1302Read (unsigned  char  addr)
{
  unsigned  char  n, dat, dat1;
  CE = 0;
  Delay1us();

  SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
  Delay1us();
  CE = 1;//Ȼ��CE(CE)�øߵ�ƽ��
  Delay1us();

  for (n = 0; n < 8; n++) //��ʼ���Ͱ�λ��ַ����
  {
    DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
    addr >>= 1;
    SCLK = 1;//������������ʱ��DS1302��ȡ����
    Delay1us();
    SCLK = 0;//DS1302�½���ʱ����������
    Delay1us();
  }

  Delay1us();

  for (n = 0; n < 8; n++) //��ȡ8λ����
  {
    dat1 = DSIO;//�����λ��ʼ����
    dat = (dat >> 1) | (dat1 << 7);
    SCLK = 1;
    Delay1us();
    SCLK = 0;//DS1302�½���ʱ����������
    Delay1us();
  }

  CE = 0;
  Delay1us();	//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
  SCLK = 1;
  Delay1us();
  DSIO = 0;
  Delay1us();
  DSIO = 1;
  Delay1us();
  return dat;
}
