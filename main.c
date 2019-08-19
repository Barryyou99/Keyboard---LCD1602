#include <msp430.h> 
#include <LCD1602IIC.h>

/**
 * main.c
 */
char scanKey();

void keyboard_init(){

    //设置行管脚为输入
    P3DIR &= ~BIT6; //P3.6端口设为输入
    P3REN |= BIT6;  //使P3.6能上拉/下拉电阻
    P3OUT &= ~BIT6;  //置P3.6为上拉电阻模式
    P3SEL &= ~BIT6; //P3.6为I/O接口

    P7DIR &= ~BIT0; //P7.0端口设为输入
    P7REN |= BIT0;  //使P7.0能上拉/下拉电阻
    P7OUT &= ~BIT0;  //置P7.0为上拉电阻模式
    P7SEL &= ~BIT0; //P7.0为I/O接口

    P6DIR &= ~BIT4; //P6.4端口设为输入
    P6REN |= BIT4;  //使P6.4能上拉/下拉电阻
    P6OUT &= ~BIT4;  //置P6.4为上拉电阻模式
    P6SEL &= ~BIT4; //P6.4为I/O接口

    P6DIR &= ~BIT3; //P6.3端口设为输入
    P6REN |= BIT3;  //使6.3能上拉/下拉电阻
    P6OUT &= ~BIT3;  //置P6.3为上拉电阻模式
    P6SEL &= ~BIT3; //P6.3为I/O接口

    //设置列管脚为输出
    P6DIR |= BIT2+BIT1+BIT0; //P6.2,1,0端口设为输出
    P6OUT &=~(BIT2+BIT1+BIT0);

}
void main(void)
{
    int i=0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    keyboard_init();
    LCD_init(0x27,16,2);//初始化LCD1602
    LCD_Backlight_on();//打开背光灯
    LCD_clearAndprint("TEL:");//显示文字
    LCD_Cursor_on();



    while(1){
        LCD_printchar(scanKey());
        for(i=0;i<30;i++) __delay_cycles(10000);//消抖
    }

}

char scanKey(){
    //扫描列
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

    }while((key_value&0x0f)==0);//直到有行被按下

    switch(key_value){//返回按下的字符
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
