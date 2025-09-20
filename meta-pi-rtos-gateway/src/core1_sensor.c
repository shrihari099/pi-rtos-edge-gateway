/**
 * @file core1_sensor.c
 * @brief Core 1 - Sensor Data Collection Task for Pi-RTOS Edge Gateway
 *
 * This module implements the sensor task responsible for collecting
 * temperature and humidity readings on the Raspberry Pi 4B (ARM Cortex-A72)
 * and transmitting them via UART (/dev/ttyAMA0). It simulates sensor data
 * for testing purposes and demonstrates the multi-threaded design of the
 * Pi-RTOS Edge Gateway.
 *
 * Features:
 *  - Generates simulated sensor readings (temperature/humidity)
 *  - Writes data to UART for downstream tasks or logging
 *  - Prints readings to console for real-time monitoring
 *
 * Limitations / TODOs:
 *  - Replace simulated readings with real I2C/SPI sensor integration
 *  - Buffer UART output to avoid opening/closing device each time
 *  - Allow configurable UART device via external configuration file
 *
 * Usage:
 *  - This task is intended to run as a pthread from gateway_main.c
 *  - Continuously runs until the global `system_running` flag is cleared
 *
 * Author: Shrihari Vaidya
 * Version: 1.0
 * Date: 2025-09-20
 *
 * License: MIT License (see LICENSE file in repository root)
 */


#include "gateway.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int sensor_count = 0;

/**
 * @brief Core 1 Task - Collects sensor data periodically.
 *
 * ✅ Implemented:
 *  - Simulated temperature/humidity readings
 *  - Writes to UART (/dev/ttyAMA0)
 *
 * 🚧 TODO:
 *  - Replace with real I2C/SPI sensor
 *  - Buffer UART output instead of reopening each time
 *  - Add configurable UART device via config file
 */
void* sensor_task(void* arg) {
    printf("[SENSOR-CORE] Started\n");

    while (system_running) {
        sensor_count++;
        sensor_data_t data = {
            .sensor_id = 1,
            .temperature = 20.0 + (sensor_count % 20),
            .humidity = 30.0 + (sensor_count % 40),
            .timestamp = time(NULL)
        };

        // Console output
        printf("[SENSOR] Reading #%d T:%.1f°C H:%.1f%% @ %ld\n",
               sensor_count, data.temperature, data.humidity, data.timestamp);

        // UART output
        int uart_fd = open("/dev/ttyAMA0", O_WRONLY | O_NOCTTY);
        if (uart_fd > 0) {
            char msg[128];
            snprintf(msg, sizeof(msg), "SENSOR:%d,%.1f,%.1f,%ld\r\n",
                     data.sensor_id, data.temperature, data.humidity, data.timestamp);
            write(uart_fd, msg, strlen(msg));
            close(uart_fd);
        }

        sleep(2);  // Run every 2 seconds
    }

    printf("[SENSOR-CORE] Stopped\n");
    return NULL;
}
