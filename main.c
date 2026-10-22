/*
https://files.waveshare.com/wiki/common/ST7796S_Datasheet.pdf
*/
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdint.h>
#include <stdbool.h>

#define MOSI	 11
#define SCLK	 10
#define LCD_CS 9
#define LCD_DC 14
#define LCD_RST 13
#define LCD_BL 15

void initialise_pins(void);
void backlight(bool state);
void hardware_reset(void);
void send_command(uint8_t cmd, const uint8_t data[], size_t length);
void init_lcd(void);
void set_coords(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);
void send_pixel(uint16_t color);


int main(void)
{
	const uint LED_PIN = PICO_DEFAULT_LED_PIN;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);

	initialise_pins();
	backlight(true);
	init_lcd();

	while (true) {
		tight_loop_contents();
	}
}

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

	spi_init(spi1, 10 * 1000 * 1000);

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
	spi_write_blocking(spi1, &cmd, 1);

	if (length > 0 && data != NULL) {
		gpio_put(LCD_DC, 1);
		spi_write_blocking(spi1, data, length);
	}

	gpio_put(LCD_CS, 1);
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

void send_pixel(uint16_t color)
{
	//high and low bytes
	uint8_t pixel[] = {
			(uint8_t)(color >> 8),
			(uint8_t)color
	};

	//memory write
	send_command(0x2C, pixel, sizeof(pixel));
}

void init_lcd(void)
{
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

	// writecontent
	uint8_t pixel_format = 0x55;
	send_command(0x3A, &pixel_format, 1);

	//display on
	send_command(0x29, NULL, 0);
	sleep_ms(20);

	set_coords(50, 50, 100, 100);
	send_pixel(0xF800); // red in RGB565
}
