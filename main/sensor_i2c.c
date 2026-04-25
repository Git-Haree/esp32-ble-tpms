#include "sensor_i2c.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <stdlib.h>

static const char *TAG = "I2C_SENSOR";

esp_err_t sensor_i2c_init(void) {
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode          = I2C_MODE_MASTER,
        .sda_io_num    = I2C_MASTER_SDA_IO,
        .scl_io_num    = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);
    ESP_LOGI(TAG, "I2C master on SDA:%d SCL:%d", I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
    return i2c_driver_install(i2c_master_port, conf.mode,
                              I2C_MASTER_RX_BUF_DISABLE,
                              I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t sensor_i2c_read_data(float *temperature, float *pressure) {
    *temperature = 25.0 + ((rand() % 100) / 100.0) * 5.0;
    *pressure    = 2200.0 + ((rand() % 200) - 100.0);
    return ESP_OK;
}
