#include "AdaptUGC.h"
#include "eglib.h"
#include <eglib/display/st7789.h>
#include <eglib/hal/four_wire_spi/esp32/esp32_ili9341.h>
#include "sensor.h"
#include "logdef.h"

#define HSPI 2

static eglib_t myeglib;

uint8_t ucg_font_9x15B_mf[] = { UCG_FONT_9x15B_MF };
uint8_t ucg_font_ncenR14_hr[] = { UCG_FONT_NCENR14_HR };
uint8_t ucg_font_fub11_tr[] = { UCG_FONT_FUB11_TR };
uint8_t ucg_font_fub11_hr[] = { UCG_FONT_FUB11_HR };
uint8_t ucg_font_fub14_hn[] = { UCG_FONT_FUB14_HN };
uint8_t ucg_font_fub14_hr[] = { UCG_FONT_FUB14_HR };
uint8_t ucg_font_fub14_hf[] = { UCG_FONT_FUB14_HF };
uint8_t ucg_font_fur14_hf[] = { UCG_FONT_FUR14_HF };
uint8_t ucg_font_fub17_hf[] = { UCG_FONT_FUB17_HF };
uint8_t ucg_font_fub20_hn[] = { UCG_FONT_FUB20_HN };
uint8_t ucg_font_fub20_hr[] = { UCG_FONT_FUB20_HR };
uint8_t ucg_font_fub20_hf[] = { UCG_FONT_FUB20_HF };
uint8_t ucg_font_fur20_hf[] = { UCG_FONT_FUR20_HF };
uint8_t ucg_font_fub25_hr[] = { UCG_FONT_FUB25_HR };
uint8_t ucg_font_fub25_hf[] = { UCG_FONT_FUB25_HF };
uint8_t ucg_font_fur25_hf[] = { UCG_FONT_FUR25_HF };
uint8_t ucg_font_fub35_hn[] = { UCG_FONT_FUB35_HN };
uint8_t ucg_font_fub35_hr[] = { UCG_FONT_FUB35_HR };

uint8_t ucg_font_profont22_mr[] = {  UCG_FONT_PROFONT22_MR };
uint8_t ucg_font_fub25_hn[] = { UCG_FONT_FUB25_HN };
uint8_t ucg_font_fub11_hn[] = { UCG_FONT_FUB11_HN };


void  AdaptUGC::begin() {
	eglib = &myeglib;
	st7789_config_t st7789_config = {
			.width = 240,
			.height = 320,
			.color = ST7789_COLOR_18_BIT,
			.page_address = ST7789_PAGE_ADDRESS_TOP_TO_BOTTOM,
			.colum_address = ST7789_COLUMN_ADDRESS_LEFT_TO_RIGHT,
			.page_column_order = ST7789_PAGE_COLUMN_ORDER_NORMAL,
			.vertical_refresh = ST7789_VERTICAL_REFRESH_TOP_TO_BOTTOM,
			.horizontal_refresh = ST7789_HORIZONTAL_REFRESH_LEFT_TO_RIGHT,
	};

	esp32_hal_config_t esp32_ili9341_config = {
			.spi_num = 	VSPI,
			.freq = 	13111111*3,  // max 40 MHz
			.dataMode = SPI_MODE0,
			.bitOrder = MSBFIRST,
			.gpio_scl = SPI_SCLK,
			.gpio_sda = SPI_MOSI,
			.gpio_sdi = SPI_MISO,
			.gpio_cs  = CS_Display,
			.gpio_dc  = SPI_DC,
			.gpio_rs  = RESET_Display,
	};

	ESP_LOGI(FNAME, "eglib_Send() &eglib:%x  hal-driv:%x config:%x\n", (unsigned int)eglib, (unsigned int)&esp32_ili9341, (unsigned int)&esp32_ili9341_config );

	eglib_Init( &myeglib, &esp32_ili9341, &esp32_ili9341_config, &st7789, &st7789_config );

};


