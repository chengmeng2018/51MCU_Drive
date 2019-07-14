#ifndef __DS1302_H__
#define __DS1302_H__

#include <REGX52.H>
//---����ds1302ʹ�õ�IO��---//
sbit DSIO = P3^4;
sbit CE = P3^5;
sbit SCLK = P3^6;

enum Ds1302_MODE{H24,AM,PM};
typedef struct
{
  char sec;
  char min;
  char hour;
  char date;
  char mon;
  char day;
  char year;
  char mode;
}Ds1302_TypeDef;

void Ds1302Init();//DS1302��ʼ��
void ReadTime(Ds1302_TypeDef* time);
void WriteTime(Ds1302_TypeDef* time);

#endif