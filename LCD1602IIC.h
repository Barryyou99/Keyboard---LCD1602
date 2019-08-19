/*
 * LCD1602IIC.h
 *
 *
 *  Created on: 2019年7月30日
 *      Author: HITsz - Barry
 */

/*************************使用说明*******************************
 *
 * 这是LCD1620 IIC协议支持库,适用于MSP430F552X系列单片机,由官方自带支持库移植得到。
 *
 * IIC通信会占用单片机两个I/O端口，它们分别为P3.0和P3.1（无法更改），使用时请避免占用。
 *
 * LCD1602的型号不同，其通信地址也不同，详情请查阅datasheet
 *
 * 本模块会调用MSP430F552X的driverlib.h及C标准库string.h、stdint.h,
 * 若报错，请检查这些文件是否已添加到工程中。
 *
 * 下面是MSP430552X与LCD1602的连接方式
 *
 * LCD1602  -  MSP430F552X
 *   GND    -       GND
 *   VCC    -       5V
 *   SDA    -       P3.0
 *   SCL    -       P3.1
 *   VO     -       P6.5
 *
 *   VO（在LCD1602的正面）可以接到P6.5(单片机的拨码电位器）调节对比度
 *
 * Barry
 * 2019.7.30
 *
 ***************************************************************/


#include <stdint.h>
#ifndef LCD1602IIC_H_
#define LCD1602IIC_H_

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for LCD_backlight control
#define LCD_backlight 0x08
#define LCD_NObacklight 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit



uint8_t _Addr;
uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;
uint8_t _numlines;
uint8_t _cols;
uint8_t _rows;
uint8_t _backlightval;

/*************************库自用函数*******************************/
void I2C_init(uint8_t Slave_Addr);
void LCD_begin(uint8_t cols, uint8_t lines, uint8_t dotsize);
void LCD_printchar(char value);
void LCD_expanderWrite(uint8_t _data);
void LCD_write4bits(uint8_t value);
void LCD_pulseEnable(uint8_t _data);
void LCD_printfIIC(uint8_t data);
void LCD_command(uint8_t value);
void set_zero(char *str, int x, int y);
void LCD_send(uint8_t value,uint8_t mode);
/****************************************************************/


/*************************用户函数*******************************/


/***************************************************************
	函数名:     LCD_init
	目的:       初始化LCD1602模块
	参数:		
					1 lcd_Addr [uint8_t]
						LCD1602的地址
					2 lcd_cols [uint8_t]
						LCD1602每行的字数(列数)
					3 lcd_row [uint8_t]
						LCD1602显示屏的行数                        

	返回值:     无
****************************************************************/
void LCD_init(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);

/***************************************************************
	函数名:     LCD_setCursor
	目的:       设置光标位置
	参数:		
					1 col [uint8_t]
						列
					2 row [uint8_t]
						列         

	返回值:     无
****************************************************************/
void LCD_setCursor(uint8_t col, uint8_t row);

/***************************************************************
	函数名:     LCD_Display_off
	目的:       关闭屏幕显示
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Display_off(void);

/***************************************************************
	函数名:     LCD_Display_on
	目的:       开启屏幕显示
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Display_on(void);

/***************************************************************
	函数名:     LCD_Cursor_off
	目的:       关闭光标显示
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Cursor_off(void);

/***************************************************************
	函数名:     LCD_Cursor_on
	目的:       开启光标显示
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Cursor_on(void);

/***************************************************************
	函数名:     LCD_Blink_off
	目的:       关闭闪烁
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Blink_off(void);

/***************************************************************
	函数名:     LCD_Blink_on
	目的:       开启闪烁
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Blink_on(void);

/***************************************************************
	函数名:     LCD_ScrollDisplayLeft
	目的:       屏幕整体向左滚动一列
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_ScrollDisplayLeft(void);

/***************************************************************
	函数名:     LCD_ScrollDisplayRight
	目的:       屏幕整体向右滚动一列
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_ScrollDisplayRight(void);

/***************************************************************
	函数名:     LCD_LeftToRight
	目的:       设置文字从左到右显示
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_LeftToRight(void);

/***************************************************************
	函数名:     LCD_RightToLeft
	目的:       设置文字从右到左显示
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_RightToLeft(void);

/***************************************************************
	函数名:     LCD_Autoscroll_on
	目的:       开启自动滚动
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Autoscroll_on(void);

/***************************************************************
	函数名:     LCD_Autoscroll_off
	目的:       关闭自动滚动
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Autoscroll_off(void);

/***************************************************************
	函数名:     LCD_Backlight_off
	目的:       关闭背光
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Backlight_off(void);

/***************************************************************
	函数名:     LCD_Backlight_on
	目的:       开启背光
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_Backlight_on(void);

/***************************************************************
	函数名:     LCD_clear
	目的:       清空屏幕
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_clear(void);

/***************************************************************
	函数名:     LCD_home
	目的:       回到第一个字符 (第一行第一列)
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_home(void);

/***************************************************************
	函数名:     LCD_print
	目的:       从光标当前位置开始显示字符串(不会自动换行)
	参数:		
					1 str [char*]
						要显示的字符串                      
	返回值:     无
****************************************************************/
void LCD_print(char *str);

/***************************************************************
	函数名:     LCD_selectRow1
	目的:       选择第一行(第一列)
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_selectRow1(void);

/***************************************************************
	函数名:     LCD_selectRow2
	目的:       选择第二行(第一列)
	参数:		无                                      
	返回值:     无
****************************************************************/
void LCD_selectRow2(void);

/***************************************************************
	函数名:     LCD_clearAndprint
	目的:       清空屏幕并显示字符串(会自动换行)
	参数:		
					1 str [char*]
						要显示的字符串                      
	返回值:     无
****************************************************************/
void LCD_clearAndprint(char *str);

/***************************************************************
	函数名:     Int2String
	目的:       整数(32位)转字符串
	参数:		
					1 num [long]
						长整数，支持负数
                    2 str [char*]
                        转换后字符串的地址                     
	返回值:     转换后字符串的地址
****************************************************************/
char *Int2String(long num, char *str);

/***************************************************************
	函数名:     Frac2String
	目的:       小数(双精度)转字符串
	参数:		
					1 num [double]
						双精度小数，支持负数
                    2 str [char*]
                        转换后字符串的地址                     
	返回值:     转换后字符串的地址
****************************************************************/
char *Frac2String(double num,int x, char *str);


#endif /* LCD1602IIC_H_ */
