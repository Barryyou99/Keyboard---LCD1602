/*
 * LCD1602IIC.h
 *
 *
 *  Created on: 2019��7��30��
 *      Author: HITsz - Barry
 */

/*************************ʹ��˵��*******************************
 *
 * ����LCD1620 IICЭ��֧�ֿ�,������MSP430F552Xϵ�е�Ƭ��,�ɹٷ��Դ�֧�ֿ���ֲ�õ���
 *
 * IICͨ�Ż�ռ�õ�Ƭ������I/O�˿ڣ����Ƿֱ�ΪP3.0��P3.1���޷����ģ���ʹ��ʱ�����ռ�á�
 *
 * LCD1602���ͺŲ�ͬ����ͨ�ŵ�ַҲ��ͬ�����������datasheet
 *
 * ��ģ������MSP430F552X��driverlib.h��C��׼��string.h��stdint.h,
 * ������������Щ�ļ��Ƿ�����ӵ������С�
 *
 * ������MSP430552X��LCD1602�����ӷ�ʽ
 *
 * LCD1602  -  MSP430F552X
 *   GND    -       GND
 *   VCC    -       5V
 *   SDA    -       P3.0
 *   SCL    -       P3.1
 *   VO     -       P6.5
 *
 *   VO����LCD1602�����棩���Խӵ�P6.5(��Ƭ���Ĳ����λ�������ڶԱȶ�
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

/*************************�����ú���*******************************/
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


/*************************�û�����*******************************/


/***************************************************************
	������:     LCD_init
	Ŀ��:       ��ʼ��LCD1602ģ��
	����:		
					1 lcd_Addr [uint8_t]
						LCD1602�ĵ�ַ
					2 lcd_cols [uint8_t]
						LCD1602ÿ�е�����(����)
					3 lcd_row [uint8_t]
						LCD1602��ʾ��������                        

	����ֵ:     ��
****************************************************************/
void LCD_init(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);

/***************************************************************
	������:     LCD_setCursor
	Ŀ��:       ���ù��λ��
	����:		
					1 col [uint8_t]
						��
					2 row [uint8_t]
						��         

	����ֵ:     ��
****************************************************************/
void LCD_setCursor(uint8_t col, uint8_t row);

/***************************************************************
	������:     LCD_Display_off
	Ŀ��:       �ر���Ļ��ʾ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Display_off(void);

/***************************************************************
	������:     LCD_Display_on
	Ŀ��:       ������Ļ��ʾ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Display_on(void);

/***************************************************************
	������:     LCD_Cursor_off
	Ŀ��:       �رչ����ʾ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Cursor_off(void);

/***************************************************************
	������:     LCD_Cursor_on
	Ŀ��:       ���������ʾ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Cursor_on(void);

/***************************************************************
	������:     LCD_Blink_off
	Ŀ��:       �ر���˸
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Blink_off(void);

/***************************************************************
	������:     LCD_Blink_on
	Ŀ��:       ������˸
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Blink_on(void);

/***************************************************************
	������:     LCD_ScrollDisplayLeft
	Ŀ��:       ��Ļ�����������һ��
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_ScrollDisplayLeft(void);

/***************************************************************
	������:     LCD_ScrollDisplayRight
	Ŀ��:       ��Ļ�������ҹ���һ��
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_ScrollDisplayRight(void);

/***************************************************************
	������:     LCD_LeftToRight
	Ŀ��:       �������ִ�������ʾ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_LeftToRight(void);

/***************************************************************
	������:     LCD_RightToLeft
	Ŀ��:       �������ִ��ҵ�����ʾ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_RightToLeft(void);

/***************************************************************
	������:     LCD_Autoscroll_on
	Ŀ��:       �����Զ�����
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Autoscroll_on(void);

/***************************************************************
	������:     LCD_Autoscroll_off
	Ŀ��:       �ر��Զ�����
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Autoscroll_off(void);

/***************************************************************
	������:     LCD_Backlight_off
	Ŀ��:       �رձ���
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Backlight_off(void);

/***************************************************************
	������:     LCD_Backlight_on
	Ŀ��:       ��������
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_Backlight_on(void);

/***************************************************************
	������:     LCD_clear
	Ŀ��:       �����Ļ
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_clear(void);

/***************************************************************
	������:     LCD_home
	Ŀ��:       �ص���һ���ַ� (��һ�е�һ��)
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_home(void);

/***************************************************************
	������:     LCD_print
	Ŀ��:       �ӹ�굱ǰλ�ÿ�ʼ��ʾ�ַ���(�����Զ�����)
	����:		
					1 str [char*]
						Ҫ��ʾ���ַ���                      
	����ֵ:     ��
****************************************************************/
void LCD_print(char *str);

/***************************************************************
	������:     LCD_selectRow1
	Ŀ��:       ѡ���һ��(��һ��)
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_selectRow1(void);

/***************************************************************
	������:     LCD_selectRow2
	Ŀ��:       ѡ��ڶ���(��һ��)
	����:		��                                      
	����ֵ:     ��
****************************************************************/
void LCD_selectRow2(void);

/***************************************************************
	������:     LCD_clearAndprint
	Ŀ��:       �����Ļ����ʾ�ַ���(���Զ�����)
	����:		
					1 str [char*]
						Ҫ��ʾ���ַ���                      
	����ֵ:     ��
****************************************************************/
void LCD_clearAndprint(char *str);

/***************************************************************
	������:     Int2String
	Ŀ��:       ����(32λ)ת�ַ���
	����:		
					1 num [long]
						��������֧�ָ���
                    2 str [char*]
                        ת�����ַ����ĵ�ַ                     
	����ֵ:     ת�����ַ����ĵ�ַ
****************************************************************/
char *Int2String(long num, char *str);

/***************************************************************
	������:     Frac2String
	Ŀ��:       С��(˫����)ת�ַ���
	����:		
					1 num [double]
						˫����С����֧�ָ���
                    2 str [char*]
                        ת�����ַ����ĵ�ַ                     
	����ֵ:     ת�����ַ����ĵ�ַ
****************************************************************/
char *Frac2String(double num,int x, char *str);


#endif /* LCD1602IIC_H_ */
