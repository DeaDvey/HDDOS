/*
https://files.waveshare.com/wiki/common/ST7796S_Datasheet.pdf
*/
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdint.h>
#include <stdbool.h>

#include "character_set/character.h"

#define MOSI	 11
#define SCLK	 10
#define LCD_CS 9
#define LCD_DC 14
#define LCD_RST 13
#define LCD_BL 15
#define SLCK_SPEED 60*1000*1000
#define SPI_DEVICE spi1

const int SCREEN_HEIGHT = 320;
const int SCREEN_WIDTH = 480;

void initialise_pins(void)
{
	gpio_init(LCD_CS);
	gpio_set_dir(LCD_CS, GPIO_OUT);
	gpio_put(LCD_CS, 1);

	gpio_init(LCD_DC);
	gpio_set_dir(LCD_DC, GPIO_OUT);

	gpio_init(LCD_RST);
	gpio_set_dir(LCD_RST, GPIO_OUT);

	gpio_init(LCD_BL);
	gpio_set_dir(LCD_BL, GPIO_OUT);

	spi_init(SPI_DEVICE, SLCK_SPEED);

	spi_set_format(
		SPI_DEVICE,
		8,
		SPI_CPOL_0,
		SPI_CPHA_0,
		SPI_MSB_FIRST
	);

	gpio_set_function(MOSI, GPIO_FUNC_SPI);
	gpio_set_function(SCLK, GPIO_FUNC_SPI);
}

void backlight(bool state)
{
	gpio_put(LCD_BL, state);
}

void hardware_reset(void)
{
	gpio_put(LCD_RST, 0);
	sleep_ms(20);
	gpio_put(LCD_RST, 1);
	sleep_ms(120);
}

void send_command(uint8_t cmd, const uint8_t data[], size_t length)
{
	gpio_put(LCD_CS, 0);

	gpio_put(LCD_DC, 0);
	spi_write_blocking(SPI_DEVICE, &cmd, 1);

	if (length > 0 && data != NULL) {
		gpio_put(LCD_DC, 1);
		spi_write_blocking(SPI_DEVICE, data, length);
	}
	gpio_put(LCD_CS, 0); // Always ends with LCD_CS pushing 0
}

void set_coords(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{
	// high and low bytes
	uint8_t x[] = {
			(uint8_t)(x1 >> 8), (uint8_t)x1,
			(uint8_t)(x2 >> 8), (uint8_t)x2
	};

	uint8_t y[] = {
			(uint8_t)(y1 >> 8), (uint8_t)y1,
			(uint8_t)(y2 >> 8), (uint8_t)y2
	};

	send_command(0x2A, x, sizeof(x)); // column set
	send_command(0x2B, y, sizeof(y)); // row set
}

void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{
	set_coords(x1, x2, y1, y2);

	// convert tobig endian byte order
	uint8_t pixel[2] = {
		(uint8_t)(colour >> 8),
		(uint8_t)(colour & 0xFF)
	};

	// memory write command 2Ch
	uint8_t cmd = 0x2C;
	send_command(cmd,NULL,0);

	// pull CS back to 0
	gpio_put(LCD_CS, 0);
	gpio_put(LCD_DC, 1);

	uint32_t width  = (uint32_t)x2 - x1 + 1;
	uint32_t height = (uint32_t)y2 - y1 + 1;
	uint32_t count  = width * height;

	for (uint32_t i = 0; i < count; i++) {
		spi_write_blocking(SPI_DEVICE, pixel, 2);
	}

	gpio_put(LCD_CS, 1);
}
void draw_pixel(uint16_t x, uint16_t y, uint16_t colour)
{
	set_coords(x, x+1, y, y+1);

	// convert tobig endian byte order
	uint8_t pixel[2] = {
		(uint8_t)(colour >> 8),
		(uint8_t)(colour & 0xFF)
	};

	// memory write command 2Ch
	uint8_t cmd = 0x2C;
	send_command(cmd,NULL,0);

	// pull CS back to 0
	gpio_put(LCD_CS, 0);
	gpio_put(LCD_DC, 1);

	uint32_t width  = (uint32_t)x - x + 1;
	uint32_t height = (uint32_t)y - y + 1;
	uint32_t count  = width * height;

	for (uint32_t i = 0; i < count; i++) {
		spi_write_blocking(SPI_DEVICE, pixel, 2);
	}

	gpio_put(LCD_CS, 1);
}

void draw_character(const Character* c, uint16_t fg, uint16_t bg, uint8_t pos_x, uint8_t pos_y)
{
	uint16_t left_x_coord = (pos_x * CHAR_WIDTH);
	uint16_t upper_y_coord = SCREEN_HEIGHT-(pos_y * CHAR_HEIGHT)-1;

	// draw bg
	// TODO in theory, this is more efficient, but can't get it to work
	//draw_rect( left_x_coord,left_x_coord+CHAR_WIDTH, upper_y_coord-CHAR_HEIGHT, upper_y_coord, bg);

	// draw character
	// c is a bitmap of the character
	for (int i=0; i<CHAR_HEIGHT; i++) {
		for (int j=0; j<CHAR_WIDTH; j++) {
			if ((c->map[i] >> (CHAR_WIDTH-j-1)) & 1ULL) { // bit = 1
				draw_pixel(upper_y_coord-i, left_x_coord+j, fg);
			}
			else draw_pixel(upper_y_coord-i, left_x_coord+j, bg);
		}
	}
}

void init_lcd(void)
{
	initialise_pins();
	backlight(true);
	hardware_reset();

	// software reset
	send_command(0x01, NULL, 0);
	sleep_ms(120);

	// stop sleeping
	send_command(0x11, NULL, 0);
	sleep_ms(120);

	// for some reason we do memory data access control
	uint8_t madctl = 0x48;
	send_command(0x36, &madctl, 1);

	// rgb pixel format
	uint8_t pixel_format = 0x55;
	send_command(0x3A, &pixel_format, 1);

	//display on
	send_command(0x29, NULL, 0);
	sleep_ms(20);

	//fill_rect(50,100,149,199,0xF800);
	//fill_rect(0, 0, 319, 479, 0xF800);
	draw_rect(0, 0, 319, 479, 0xffff);
}
