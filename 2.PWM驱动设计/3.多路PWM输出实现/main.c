/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 -----------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/*---------------------------------------------------------------------*/


/*************  ����˵��    **************

ʹ��Timer0ģ��16ͨ��PWM��������

���Ϊ P1.0 ~ P1.7, P2.0 ~ P2.7, ��Ӧ PWM0 ~ PWM15.

��ʱ���ж�Ƶ��һ�㲻Ҫ����100KHZ, ���㹻��ʱ�����ĳ�������.

������ʹ��11.0592MHZʱ��, 25K���ж�Ƶ��, 250��PWM, ����Ϊ10ms.

�ж��ﴦ���ʱ�䲻����6us, ռCPUʱ���ԼΪ15%.

******************************************/

#include    <reg52.h>

#define MAIN_Fosc       12000000UL  //������ʱ��
#define Timer0_Rate     2500       //�ж�Ƶ��


typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

#define Timer0_Reload   (65536UL -(MAIN_Fosc/12 / Timer0_Rate))        //Timer 0 ��װֵ

//************** PWM8 �����ͳ����Լ�IO�ڶ��� ***************
//********************  8ͨ��8 bit ��PWM    ********************

#define     PWM_DUTY_MAX    250 // 0~255    PWM����, ���255
#define     PWM_ON          1   // ����ռ�ձȵĵ�ƽ, 1 �� 0

#define     PWM_OFF         (!PWM_ON)
#define     PWM_ALL_ON      (0xff * PWM_ON)

u8 bdata PWM_temp1,PWM_temp2;       //Ӱ��һ��RAM����λѰַ�����ʱͬ��ˢ��
sbit    P_PWM0  =   PWM_temp1^0;    //  ����Ӱ��RAMÿλ��Ӧ��IO
sbit    P_PWM1  =   PWM_temp1^1;
sbit    P_PWM2  =   PWM_temp1^2;
sbit    P_PWM3  =   PWM_temp1^3;
sbit    P_PWM4  =   PWM_temp1^4;
sbit    P_PWM5  =   PWM_temp1^5;
sbit    P_PWM6  =   PWM_temp1^6;
sbit    P_PWM7  =   PWM_temp1^7;
sbit    P_PWM8  =   PWM_temp2^0;
sbit    P_PWM9  =   PWM_temp2^1;
sbit    P_PWM10 =   PWM_temp2^2;
sbit    P_PWM11 =   PWM_temp2^3;
sbit    P_PWM12 =   PWM_temp2^4;
sbit    P_PWM13 =   PWM_temp2^5;
sbit    P_PWM14 =   PWM_temp2^6;
sbit    P_PWM15 =   PWM_temp2^7;

u8  pwm_duty;       //���ڼ���ֵ
u8  pwm[16];        //pwm0~pwm15 Ϊ0��15·PWM�Ŀ��ֵ

bit     B_1ms;
u8      cnt_1ms;
u8      cnt_20ms;

/**********************************************/
void main(void)
{
    u8  i;
    TMOD &= ~(1<<2);    // Timer0 set as Timer
    TMOD = TMOD&0x0f0|0x01;      // Timer0 set as 16 bits 
    TH0 = Timer0_Reload / 256;  //Timer0 Load
    TL0 = Timer0_Reload % 256;
    ET0 = 1;        //Timer0 Interrupt Enable
    PT0 = 1;        //�����ȼ�
    TR0 = 1;        //Timer0 Run
    EA = 1;         //�����ж�

    cnt_1ms = Timer0_Rate / 1000;   //1ms����
    cnt_20ms = 20;
    
    for(i=0; i<16; i++)     pwm[i] = i * 15 + 15;   //��PWMһ����ֵ
    
    while(1)
    {
        if(B_1ms)   //1ms��
        {
            B_1ms = 0;
            if(--cnt_20ms == 0) //PWM 20ms�ı�һ��
            {
                cnt_20ms = 20;
                for(i=0; i<16; i++) pwm[i]++;
            }
        }
    }
} 


/********************** Timer0 1ms�жϺ��� ************************/
void timer0 (void) interrupt 1
{
    TH0 = Timer0_Reload / 256;  //Timer0 Load
    TL0 = Timer0_Reload % 256;
    P1 = PWM_temp1;         //Ӱ��RAM�����ʵ�ʵ�PWM�˿�
    P2 = PWM_temp2;
        
    if(++pwm_duty == PWM_DUTY_MAX)      //PWM���ڽ��������¿�ʼ�µ�����
    {
        pwm_duty = 0;
        PWM_temp1 = PWM_ALL_ON; 
        PWM_temp2 = PWM_ALL_ON; 
    }
    ACC = pwm_duty;
    if(ACC == pwm[0])       P_PWM0  = PWM_OFF;  //�ж�PWMռ�ձ��Ƿ����
    if(ACC == pwm[1])       P_PWM1  = PWM_OFF;
    if(ACC == pwm[2])       P_PWM2  = PWM_OFF;
    if(ACC == pwm[3])       P_PWM3  = PWM_OFF;
    if(ACC == pwm[4])       P_PWM4  = PWM_OFF;
    if(ACC == pwm[5])       P_PWM5  = PWM_OFF;
    if(ACC == pwm[6])       P_PWM6  = PWM_OFF;
    if(ACC == pwm[7])       P_PWM7  = PWM_OFF;
    if(ACC == pwm[8])       P_PWM8  = PWM_OFF;
    if(ACC == pwm[9])       P_PWM9  = PWM_OFF;
    if(ACC == pwm[10])      P_PWM10 = PWM_OFF;
    if(ACC == pwm[11])      P_PWM11 = PWM_OFF;
    if(ACC == pwm[12])      P_PWM12 = PWM_OFF;
    if(ACC == pwm[13])      P_PWM13 = PWM_OFF;
    if(ACC == pwm[14])      P_PWM14 = PWM_OFF;
    if(ACC == pwm[15])      P_PWM15 = PWM_OFF;

    if(--cnt_1ms == 0)
    {
        cnt_1ms = Timer0_Rate / 1000;
        B_1ms = 1;      // 1ms��־
    }
}

