#include "lcd_init.h"
#include "delay.h"
#include "spi.h"

void LCD_GPIO_Init(void)
{
	GPIO_Config_T gpio_init_struct;
	gpio_init_struct.pin = GPIO_PIN_4 | GPIO_PIN_6;
	gpio_init_struct.mode = GPIO_MODE_OUT;
	gpio_init_struct.speed = GPIO_SPEED_100MHz;
	gpio_init_struct.otype = GPIO_OTYPE_PP;
	gpio_init_struct.pupd = GPIO_PUPD_NOPULL;
	GPIO_Config(GPIOA, &gpio_init_struct);

	gpio_init_struct.pin = GPIO_PIN_4;
	GPIO_Config(GPIOC, &gpio_init_struct);
}

void delay(int t)
{
	while (t--)
		;
}

/******************************************************************************
	  函数说明：LCD串行数据写入函数
	  入口数据：dat  要写入的串行数据
	  返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat)
{
	LCD_CS_Clr();

	while (!(SPI1_SPI->STS & SPI_FLAG_TXBE))
	{
		/* 等待发送缓冲器为空 */
	}
	SPI1_SPI->DATA = dat;
	// while (!(SPI1_SPI->STS & SPI_FLAG_RXBNE))
	// {
	// 	/* 等待接收缓冲非空 */
	// }
	// SPI1_SPI->DATA; /* 接收一字节数据 */
	SPI1_SPI->STS & SPI_FLAG_RXBNE;
	while (SPI1_SPI->STS & SPI_FLAG_BSY)
	{
	}

	LCD_CS_Set();
}

/******************************************************************************
	  函数说明：LCD写入数据
	  入口数据：dat 写入的数据
	  返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}

/******************************************************************************
	  函数说明：LCD写入数据
	  入口数据：dat 写入的数据
	  返回值：  无
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}

/******************************************************************************
	  函数说明：LCD写入命令
	  入口数据：dat 写入的命令
	  返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr(); // 写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set(); // 写数据
}

/******************************************************************************
	  函数说明：设置起始和结束地址
	  入口数据：x1,x2 设置列的起始和结束地址
				y1,y2 设置行的起始和结束地址
	  返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (USE_HORIZONTAL == 0)
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_DATA(x1 + 34);
		LCD_WR_DATA(x2 + 34);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c); // 储存器写
	}
	else if (USE_HORIZONTAL == 1)
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_DATA(x1 + 34);
		LCD_WR_DATA(x2 + 34);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c); // 储存器写
	}
	else if (USE_HORIZONTAL == 2)
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_DATA(y1 + 34);
		LCD_WR_DATA(y2 + 34);
		LCD_WR_REG(0x2c); // 储存器写
	}
	else
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_DATA(y1 + 34);
		LCD_WR_DATA(y2 + 34);
		LCD_WR_REG(0x2c); // 储存器写
	}
}

void LCD_Init(void)
{
	LCD_GPIO_Init(); // 初始化GPIO
	spi1_init();	 // 初始化SPI1

	LCD_RES_Clr(); // 复位
	delay_ms(10);
	LCD_RES_Set();
	delay_ms(10);
	LCD_BLK_Set(); // 打开背光
	delay_ms(10);

	LCD_WR_REG(0xfe);
	LCD_WR_REG(0xef);

	LCD_WR_REG(0x36);
	// LCD_WR_DATA8(0xE8);		//横屏一个方向
	LCD_WR_DATA8(0x28); // 横屏另一个方向，转180度
	LCD_WR_REG(0x3a);
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0x85);
	LCD_WR_DATA8(0xc0);
	LCD_WR_REG(0x86);
	LCD_WR_DATA8(0x98);
	LCD_WR_REG(0x87);
	LCD_WR_DATA8(0x28);
	LCD_WR_REG(0x89);
	LCD_WR_DATA8(0x33);
	LCD_WR_REG(0x8B);
	LCD_WR_DATA8(0x84);
	LCD_WR_REG(0x8D);
	LCD_WR_DATA8(0x3B);
	LCD_WR_REG(0x8E);
	LCD_WR_DATA8(0x0f);
	LCD_WR_REG(0x8F);
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0xe8);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x17);

	LCD_WR_REG(0xec);
	LCD_WR_DATA8(0x57);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0xff);

	LCD_WR_REG(0xed);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x09);

	// LCD_WR_REG(0xc3);
	// LCD_WR_DATA8(0x29);
	// LCD_WR_REG(0xc4);
	// LCD_WR_DATA8(0x45);  ///vcom 烧录了
	LCD_WR_REG(0xc9);
	LCD_WR_DATA8(0x10);

	LCD_WR_REG(0xff);
	LCD_WR_DATA8(0x61);

	LCD_WR_REG(0x99);
	LCD_WR_DATA8(0x3A);
	LCD_WR_REG(0x9d);
	LCD_WR_DATA8(0x43);
	LCD_WR_REG(0x98);
	LCD_WR_DATA8(0x3e);
	LCD_WR_REG(0x9c);
	LCD_WR_DATA8(0x4b);

	LCD_WR_REG(0xF0);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x1d);

	LCD_WR_REG(0xF2);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xF1);
	LCD_WR_DATA8(0x3b);
	LCD_WR_DATA8(0x68);
	LCD_WR_DATA8(0x66);
	LCD_WR_DATA8(0x36);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x2f);

	LCD_WR_REG(0xF3);
	LCD_WR_DATA8(0x37);
	LCD_WR_DATA8(0x6a);
	LCD_WR_DATA8(0x66);
	LCD_WR_DATA8(0x37);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xFA);
	LCD_WR_DATA8(0x80);
	LCD_WR_DATA8(0x0f);

	LCD_WR_REG(0xBE);
	LCD_WR_DATA8(0x11); // source bias

	LCD_WR_REG(0xCB);
	LCD_WR_DATA8(0x02);

	LCD_WR_REG(0xCD);
	LCD_WR_DATA8(0x22);

	LCD_WR_REG(0x9B);
	LCD_WR_DATA8(0xFF);

	LCD_WR_REG(0x35);
	LCD_WR_DATA8(0x00);

	LCD_WR_REG(0x44);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x0a);

	LCD_WR_REG(0x11);
	delay_ms(200);
	LCD_WR_REG(0x29);

	LCD_WR_REG(0x2c);

#if 0
	LCD_RES_Clr(); // 复位
	delay_ms(30);
	LCD_RES_Set();
	delay_ms(100);
	LCD_BLK_Set(); // 打开背光
	delay_ms(100);
	//
	LCD_WR_REG(0x11);
	//	delay_ms(120);
	LCD_WR_REG(0x36);
	// LCD_WR_DATA8(0xE8);		//横屏一个方向
	LCD_WR_DATA8(0x28); // 横屏另一个方向，转180度

	// if (USE_HORIZONTAL == 0)
	// 	LCD_WR_DATA8(0x00);
	// else if (USE_HORIZONTAL == 1)
	// 	LCD_WR_DATA8(0xC0);
	// else if (USE_HORIZONTAL == 2)
	// 	LCD_WR_DATA8(0x70);
	// else
	// 	LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33);

	LCD_WR_REG(0xB7);
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x13);

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);

	LCD_WR_REG(0xC6);
	LCD_WR_DATA8(0x0F);

	LCD_WR_REG(0xD0);
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xD6);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xF0);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x29);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x3E);
	LCD_WR_DATA8(0x38);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x30);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xF0);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x3E);
	LCD_WR_DATA8(0x36);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x29);
	LCD_WR_DATA8(0x32);

	// 	LCD_WR_REG(0x2A);
	//	LCD_WR_DATA8(0x00);
	//	LCD_WR_DATA8(0x22);
	//	LCD_WR_DATA8(0x00);
	//	LCD_WR_DATA8(0xCD);
	//	LCD_WR_DATA8(0x2B);
	//	LCD_WR_DATA8(0x00);
	//	LCD_WR_DATA8(0x00);
	//	LCD_WR_DATA8(0x01);
	//	LCD_WR_DATA8(0x3F);
	//	LCD_WR_REG(0x2C);
	LCD_WR_REG(0x21);

	LCD_WR_REG(0x11);
	delay_ms(120);
	LCD_WR_REG(0x29);
#endif
}
