
#ifndef __MULDIGITALTUBE_H__
#define __MULDIGITALTUBE_H__

#define MulDigData P0
#define MulDigCmd  P2


void MulDigInit();//��ʼ������
void MulDigPlay();//��̬ˢ����ʾ

void DigSetBData (char ID, char Num); //����һλ
void DigSetDData (char ID, char Num); //������λ

#endif