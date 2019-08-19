/*
 * LCD1602IIC.c
 *
 *
 *  Created on: 2019年7月30日
 *      Author: HITsz - Barry
 */

#include "LCD1602IIC.h"
#include "driverlib.h"
#include "string.h"
// LCD_commands


void I2C_init(uint8_t Slave_Addr){
    //Assign I2C pins to USCI_B0
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN1
        );
    //Initialize Master
    USCI_B_I2C_initMasterParam param = {0};
    param.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK;
    param.i2cClk = UCS_getSMCLK();
    param.dataRate = USCI_B_I2C_SET_DATA_RATE_400KBPS;
    USCI_B_I2C_initMaster(USCI_B0_BASE, &param);
    //Specify slave address
    USCI_B_I2C_setSlaveAddress(USCI_B0_BASE,
        Slave_Addr
        );
    //Set in transmit mode
    USCI_B_I2C_setMode(USCI_B0_BASE,
        USCI_B_I2C_TRANSMIT_MODE
        );
    //Enable I2C Module to start operations
    USCI_B_I2C_enable(USCI_B0_BASE);
}

void LCD_init(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows){
  _Addr = lcd_Addr;
  _cols = lcd_cols;
  _rows = lcd_rows;
  _backlightval = LCD_NObacklight;
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  I2C_init(_Addr);
  LCD_begin(_cols, _rows,LCD_5x10DOTS);
}

void LCD_begin(uint8_t cols, uint8_t lines, uint8_t dotsize){
    if (lines > 1) {
    _displayfunction |= LCD_2LINE;
    }
    _numlines = lines;

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != 0) && (lines == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before LCD_sending LCD_commands. Arduino can turn on way befer 4.5V so we'll wait 50
    _delay_cycles(50);

    // Now we pull both RS and R/W low to begin LCD_commands
    LCD_expanderWrite(_backlightval);   // reset expanderand turn LCD_backlight off (Bit 8 =1)
    _delay_cycles(1000);

    //put the LCD into 4 bit mode
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

      // we start in 8bit mode, try to set 4 bit mode
   LCD_write4bits(0x03 << 4);
   _delay_cycles(4500); // wait min 4.1ms

   // second try
   LCD_write4bits(0x03 << 4);
   _delay_cycles(4500); // wait min 4.1ms

   // third go!
   LCD_write4bits(0x03 << 4);
   _delay_cycles(150);

   // finally, set to 4-bit interface
   LCD_write4bits(0x02 << 4);


    // set # lines, font size, etc.
    LCD_command(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    LCD_Display_on();

    // clear it off
    LCD_clear();

    // Initialize to default text direction (for roman languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    // set the entry mode
    LCD_command(LCD_ENTRYMODESET | _displaymode);

    LCD_home();

}

void LCD_setCursor(uint8_t col, uint8_t row){
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if ( row > _numlines ) {
        row = _numlines-1;    // we count rows starting w/0
    }
    LCD_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_Display_off() {
    _displaycontrol &= ~LCD_DISPLAYON;
    LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCD_Display_on() {
    _displaycontrol |= LCD_DISPLAYON;
    LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCD_Cursor_off() {
    _displaycontrol &= ~LCD_CURSORON;
    LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCD_Cursor_on() {
    _displaycontrol |= LCD_CURSORON;
    LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCD_Blink_off() {
    _displaycontrol &= ~LCD_BLINKON;
    LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCD_Blink_on() {
    _displaycontrol |= LCD_BLINKON;
    LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCD_ScrollDisplayLeft(void) {
    LCD_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_ScrollDisplayRight(void) {
    LCD_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCD_LeftToRight(void) {
    _displaymode |= LCD_ENTRYLEFT;
    LCD_command(LCD_ENTRYMODESET | _displaymode);
}

void LCD_RightToLeft(void) {
    _displaymode &= ~LCD_ENTRYLEFT;
    LCD_command(LCD_ENTRYMODESET | _displaymode);
}

void LCD_Autoscroll_on(void) {
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    LCD_command(LCD_ENTRYMODESET | _displaymode);
}

void LCD_Autoscroll_off(void) {
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    LCD_command(LCD_ENTRYMODESET | _displaymode);
}


void LCD_Backlight_off(void) {
    _backlightval=LCD_NObacklight;
    LCD_expanderWrite(0);
}

void LCD_Backlight_on(void) {
    _backlightval=LCD_backlight;
    LCD_expanderWrite(0);
}


void LCD_send(uint8_t value,uint8_t mode){

    uint8_t highnib=value&0xf0;
    uint8_t lownib=(value<<4)&0xf0;
    LCD_write4bits((highnib)|mode);
    LCD_write4bits((lownib)|mode);
}

void LCD_printchar(char value){
    LCD_send(value,1);
}
void LCD_home(){
    LCD_command(LCD_RETURNHOME);  // set cursor position to zero
    _delay_cycles(2000);  // this LCD_command takes a long time!
}

void LCD_clear(){
    LCD_command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
    _delay_cycles(2000);  // this LCD_command takes a long time!
}

void LCD_expanderWrite(uint8_t _data){
    LCD_printfIIC((int)(_data) | _backlightval);
}

void LCD_write4bits(uint8_t value){
    LCD_expanderWrite(value);
    LCD_pulseEnable(value);
}

void LCD_pulseEnable(uint8_t _data){
        LCD_expanderWrite(_data | En);  // En high
        __delay_cycles(1);      // enable pulse must be >450ns

        LCD_expanderWrite(_data & ~En); // En low
        __delay_cycles(50);     // LCD_commands need > 37us to settle
}

void LCD_printfIIC(uint8_t data){

        USCI_B_I2C_masterSendSingleByte(USCI_B0_BASE,data);

        //Delay until transmission completes
        while (USCI_B_I2C_isBusBusy(USCI_B0_BASE)) ;

        //Delay between each transaction
        __delay_cycles(50);

}


void LCD_command(uint8_t value){
    LCD_send(value, 0);
}

void LCD_print(char *str){
    while(*str) LCD_printchar(*str++);
}

void LCD_clearAndprint(char *str){
    int i=0;
    LCD_clear();

    LCD_selectRow1();
    while(*str){
        i++;
        if(i==17){
            LCD_selectRow2();
            if(*str==' '){
                str++;
                continue; //如果第二行首个为空格 则跳过
            }
        }
        LCD_printchar(*str++);
    }
}

void LCD_selectRow1(){
    LCD_setCursor(0,0);
}

void LCD_selectRow2(){
    LCD_setCursor(0,1);
}

char *Int2String(long num, char *str) //10进制
{
    int i = 0;   //指示填充str
    if (num < 0) //如果num为负数，将num变正
    {
        num = -num;
        str[i++] = '-';
    }

    //转换
    do
    {
        str[i++] = num % 10 + 48; //取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0'
        num /= 10; //去掉最低位
    } while (num); //num不为0继续循环
    str[i] = '\0';//确定开始调整的位置

    int j = 0;
    if (str[0] == '-')
    //如果有负号，负号不用调整
    {
        j = 1; //从第二位开始调整
        ++i; //由于有负号，所以交换的对称轴也要后移1位
    }

    //对称交换
    for (; j < i / 2; j++)
    {
        //对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b;
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }
    return str; //返回转换后的值
}

char *Frac2String(double num,int x, char *str)     //10进制
    {
    char c_temp[20],c_temp2[20],c_temp3[20];
    long temp;
    int i;
    long j=1;
    for(i=0;i<x;i++){
        j*=10;
    }
    strcpy(str,"");
    temp=(long)num;//取整数部分
    Int2String(temp,c_temp);
    if(num<0){
        num *= -1;
        temp *= -1;
    }
    temp=(long)((num-temp)*j+j);
    Int2String(temp,c_temp2);
    for(i=0;i<19;i++){
        c_temp3[i]=c_temp2[i+1];
    }
    set_zero(c_temp3,x+1,20);
    strcat(str,c_temp);
    strcat(str,".");
    strcat(str,c_temp3);
    return str;
    }

void set_zero(char *str, int x, int y)
{
    int i;
    for (i = x - 1; i < y; i++)
    {
        str[i] = 0;
    }
}
