/**
 * @file gateway.h
 * @brief Public API for Pi-RTOS Edge Gateway
 *
 * This header exposes the public interfaces, task prototypes,
 * and data types for the IoT gateway running on Raspberry Pi.
 *
 * Version: v1.0
 * Author : Shrihari Vaidya
 * License: MIT
 */

#ifndef GATEWAY_H
#define GATEWAY_H

#include <pthread.h>
#include <time.h>

/* -----------------------------------------------------------
   Thread Typedefs
   ----------------------------------------------------------- */
typedef pthread_t thread_t;
typedef void* (*task_fn_t)(void*);

/* -----------------------------------------------------------
   Global Variables
   ----------------------------------------------------------- */

// Shared global running flag
extern volatile int system_running;


/* -----------------------------------------------------------
   Sensor Data Structure
   ----------------------------------------------------------- */
typedef struct {
    int sensor_id;
    float temperature;
    float humidity;
    time_t timestamp;
} sensor_data_t;

/* -----------------------------------------------------------
   Tasks (function prototypes)
   ----------------------------------------------------------- */
void* sensor_task(void* arg);
void* cloud_task(void* arg);
void* ota_task(void* arg);
void* security_task(void* arg);

/* -----------------------------------------------------------
   Signal Handler
   ----------------------------------------------------------- */
   /*Handles SIGINT (Ctrl+C) for graceful shutdown.
   Note:
   - Declare in header if used in multiple .c files.
   - Define in a single .c file (gateway_main.c) to avoid
     linker errors and ensure only one global instance.
   - Do NOT mark as inline; signal() requires a unique function
     address.
*/
void signal_handler(int sig);

#endif // GATEWAY_H

