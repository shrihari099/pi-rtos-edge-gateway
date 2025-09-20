/**
 * @file core2_cloud.c
 * @brief Core 2 - Cloud Communication Task for Pi-RTOS Edge Gateway
 *
 * This module implements the cloud communication task for the Raspberry Pi 4B
 * (ARM Cortex-A72). It is responsible for preparing sensor data and sending it
 * to a cloud IoT platform (e.g., Google Cloud IoT Core) via MQTT over TLS.
 * Currently, it simulates cloud communication with placeholder console output.
 *
 * Features (Implemented):
 *  - Prints sensor data processing messages to console
 *
 * Limitations / TODOs:
 *  - Integrate MQTT client library (paho.mqtt.c or mosquitto)
 *  - Establish secure TLS connection to cloud endpoint
 *  - Authenticate with JWT tokens
 *  - Publish sensor readings periodically
 *  - Implement retry/reconnect logic in case of network failures
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
#include <unistd.h>


/**
 * @brief Core 2 Task - Cloud communication.
 *
 * @param arg Unused
 * @return NULL Always returns NULL
 */
void* cloud_task(void* arg) {
    printf("[CLOUD-CORE] Started\n");

    while (system_running) {
        printf("[CLOUD] Processing sensor data for cloud...\n");
        printf("[CLOUD] TODO: Implement MQTT/TLS\n");
        sleep(5);  // Placeholder loop
    }

    printf("[CLOUD-CORE] Stopped\n");
    return NULL;
}
