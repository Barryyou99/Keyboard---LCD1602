#include <msp430.h> 
#include <LCD1602IIC.h>

/**
 * main.c
 */
char scanKey();

void keyboard_init(){

    //�����йܽ�Ϊ����
    P3DIR &= ~BIT6; //P3.6�˿���Ϊ����
    P3REN |= BIT6;  //ʹP3.6������/��������
    P3OUT &= ~BIT6;  //��P3.6Ϊ��������ģʽ
    P3SEL &= ~BIT6; //P3.6ΪI/O�ӿ�

    P7DIR &= ~BIT0; //P7.0�˿���Ϊ����
    P7REN |= BIT0;  //ʹP7.0������/��������
    P7OUT &= ~BIT0;  //��P7.0Ϊ��������ģʽ
    P7SEL &= ~BIT0; //P7.0ΪI/O�ӿ�

    P6DIR &= ~BIT4; //P6.4�˿���Ϊ����
    P6REN |= BIT4;  //ʹP6.4������/��������
    P6OUT &= ~BIT4;  //��P6.4Ϊ��������ģʽ
    P6SEL &= ~BIT4; //P6.4ΪI/O�ӿ�

    P6DIR &= ~BIT3; //P6.3�˿���Ϊ����
    P6REN |= BIT3;  //ʹ6.3������/��������
    P6OUT &= ~BIT3;  //��P6.3Ϊ��������ģʽ
    P6SEL &= ~BIT3; //P6.3ΪI/O�ӿ�

    //�����йܽ�Ϊ���
    P6DIR |= BIT2+BIT1+BIT0; //P6.2,1,0�˿���Ϊ���
    P6OUT &=~(BIT2+BIT1+BIT0);

}
void main(void)
{
    int i=0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    keyboard_init();
    LCD_init(0x27,16,2);//��ʼ��LCD1602
    LCD_Backlight_on();//�򿪱����
    LCD_clearAndprint("TEL:");//��ʾ����
    LCD_Cursor_on();



    while(1){
        LCD_printchar(scanKey());
        for(i=0;i<30;i++) __delay_cycles(10000);//����
    }

}

char scanKey(){
    //ɨ����
    char key_value=0;
    unsigned char state=0;
    do{
        key_value=0;
        if(state==0){

            P6OUT |= BIT0;
            P6OUT &=~ (BIT1+BIT2);

        }else if(state==1){

            P6OUT |= BIT1;
            P6OUT &=~ (BIT0+BIT2);

        }else if(state==2){

            P6OUT |= BIT2;
            P6OUT &=~ (BIT0+BIT1);

        }

        if(++state==3) state=0;


        if(P6OUT & BIT0)
            key_value = BIT5;

        if(P6OUT & BIT1)
            key_value = BIT6;

        if(P6OUT & BIT2)
            key_value = BIT7;

        if(P3IN & BIT6) key_value |= BIT0;
        else key_value &= ~BIT0;

        if(P7IN & BIT0) key_value |= BIT1;
        else key_value &= ~BIT1;

        if(P6IN & BIT4) key_value |= BIT2;
        else key_value &= ~BIT2;

        if(P6IN & BIT3) key_value |= BIT3;
        else key_value &= ~BIT3;

    }while((key_value&0x0f)==0);//ֱ�����б�����

    switch(key_value){//���ذ��µ��ַ�
        case 129: return '1';
        case 65: return '2';
        case 33: return '3';
        case 130: return '4';
        case 66: return '5';
        case 34: return '6';
        case 132: return '7';
        case 68: return '8';
        case 36: return '9';
        case 136: return '*';
        case 72: return '0';
        case 40: return '#';
        default: return 0;
    }
}
