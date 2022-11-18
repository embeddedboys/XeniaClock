#include "i2c/native_i2c.h"
#include "native_rtc.h"
#include "src/widgets/lv_label.h"
#include <stdint.h>

#define DS3231_I2C_ADDR 0x68

#define DS3231_REG_CTL  0x0e
#define DS3231_REG_STAT 0x0f
#define DS3231_REG_AGING_OFFSET     0x10
#define DS3231_REG_TEMP_UB  0x11
#define DS3231_REG_TEMP_LB  0x12

enum {
    DS1307_REG_SECONDS = 0x00,
    DS1307_REG_MINUTES = 0x01,
    DS1307_REG_HOURS = 0x02,
    DS1307_REG_DAY = 0x03,
    DS1307_REG_DATE = 0x04,
    DS1307_REG_MONTH = 0x05,
    DS1307_REG_YEAR = 0x06,
    DS1307_REG_CONTROL = 0x07,
    //RAM 56 Bytes
    DS1307_REG_RAM_00 = 0x08,
    DS1307_REG_RAM_55 = 0x3F,
};

extern lv_obj_t *ui_LabelTest;

static void ds3231_init()
{
    int rc;
    uint8_t val;

    /* enable clock, write zero into CH bit */
#if DEFAULT_RTC_DEVICE == RTC_DEVICE_DS1307
    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS);
    i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS, val & 0x7f);
#elif DEFAULT_RTC_DEVICE == RTC_DEVICE_DS3231
    val = i2c_read_reg(DS3231_I2C_ADDR, DS3231_REG_CTL);
    i2c_write_reg(DS3231_I2C_ADDR, DS3231_REG_CTL, val & 0x7f);
#else
    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS);
    i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS, val & 0x7f);
#endif

    /* set hour mode, 24-hour mode, when this bit changed,
     * a new value re-enterd is required
     */
    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS);
    i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS, val & 0x7f);
    
    /* 12-hour mode */
    // i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS, val | 0x40);
}

void rtc_ds3231_set_time(datetime_t t)
{

}

/* TODO: The read ops from DS3231 should be brust
 * and fast (in 1 seconds), read all bytes in one time
 */
datetime_t rtc_ds3231_get_time()
{
    uint8_t val = 0;
    int rc;
    uint8_t hour = 0, minute = 0, second = 0;
    datetime_t ds3231_time;

    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS);
    ds3231_time.hour = val & 0x3f;

    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_MINUTES);
    ds3231_time.min = ((val & 0x7f) >> 4) * 10 + (val & 0x0f);

    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS);
    ds3231_time.sec = ((val & 0x7f) >> 4) * 10 + (val & 0x0f);

    return ds3231_time;
}

void rtc_device_init()
{
    ds3231_init();

    p_rtc_device_set_time = rtc_ds3231_set_time;
    p_rtc_device_get_time = rtc_ds3231_get_time;
}
