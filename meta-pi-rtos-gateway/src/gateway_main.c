/**
 * @file gateway_main.c
 * @brief Main Entry Point for Pi-RTOS Edge Gateway
 *
 * This module initializes and starts all core tasks of the Pi-RTOS Edge Gateway
 * on a Raspberry Pi 4B (ARM Cortex-A72). It simulates FreeRTOS SMP cores by
 * running four concurrent pthreads for sensor collection, cloud communication,
 * OTA updates, and security monitoring.
 *
 * Features (Implemented):
 *  - Starts four core tasks as threads
 *  - Graceful shutdown via Ctrl+C (SIGINT)
 *  - Basic console status output
 *
 * Limitations / TODOs:
 *  - Add configuration file parsing (JSON/YAML)
 *  - Setup proper logging framework instead of printf
 *  - Assign thread priorities and CPU affinity for real-time behavior
 *  - Add health-check API (REST/gRPC) for monitoring
 *
 * Usage:
 *  - Compile and run on Raspberry Pi 4B
 *  - Ensure that the other core task modules (sensor, cloud, OTA, security)
 *    are linked correctly
 *
 * Author: Shrihari Vaidya
 * Version: 1.0
 * Date: 2025-09-20
 *
 * License: MIT License (see LICENSE file in repository root)
 */

#include "gateway.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* -----------------------------------------------------------
   Global Running Flag
   ----------------------------------------------------------- */
volatile int system_running = 1;

/* -----------------------------------------------------------
   Thread Creation Helper
   ----------------------------------------------------------- */
/**
 * @brief Wrapper for pthread_create with logging
 *
 * @param thread Pointer to pthread handle
 * @param fn Function pointer to task
 * @param name Name of the task for logging
 * @return int 0 on success, -1 on failure
 */
static int create_task(thread_t* thread, task_fn_t fn, const char* name) {
    if (pthread_create(thread, NULL, fn, NULL) != 0) {
        printf("Error creating %s thread\n", name);
        return -1;
    }
    printf("   ✓ %s activated\n", name);
    return 0;
}

// Signal handler function for shutdown requests (e.g., SIGINT, SIGTERM)
void signal_handler(int sig) {
    // Print a message to notify that a shutdown signal was received
    printf("\n[SYSTEM] Shutdown signal received...\n");

    // Update the global 'running' flag to indicate program should terminate
    // This flag is typically checked by the main program loop to exit gracefully
    system_running = 0;
}

/* -----------------------------------------------------------
   Main Entry Point
   ----------------------------------------------------------- */
/**
 * @brief Program entry point
 *
 * Initializes and launches all core tasks, handles shutdown signals,
 * and waits for all threads to complete before exiting.
 *
 * @return int Exit code (0 = success, 1 = failure)
 */
int main() {
    printf("======================================================\n");
    printf("🚀 Pi-RTOS-Edge Gateway v1.0 (C Implementation)\n");
    printf("Multi-threaded C-based IoT Gateway\n");
    printf("Hardware: Raspberry Pi 4B (4-core ARM Cortex-A72)\n");
    printf("======================================================\n\n");

    // Register Ctrl+C signal handler for graceful shutdown
    signal(SIGINT, signal_handler);

    thread_t threads[4];

    // Launch tasks simulating FreeRTOS SMP cores
    if (create_task(&threads[0], sensor_task,   "Core 1: SensorCore")   < 0) return 1;
    if (create_task(&threads[1], cloud_task,    "Core 2: CloudCore")    < 0) return 1;
    if (create_task(&threads[2], ota_task,      "Core 3: OTACore")      < 0) return 1;
    if (create_task(&threads[3], security_task, "Core 4: SecurityCore") < 0) return 1;

    printf("\n🎯 All systems operational!\n");
    printf("📊 Real-time sensor monitoring active\n");
    printf("☁️  Cloud connectivity pipeline ready (stub)\n");
    printf("🔒 Security monitoring enabled (partial)\n");
    printf("🔄 OTA update system standby (stub)\n");
    printf("\nPress Ctrl+C to shutdown gracefully\n\n");

    // Idle loop until shutdown signal
    while (system_running) {
        sleep(1);
    }

    // Wait for all threads to finish
    printf("\n[SYSTEM] Waiting for all tasks to complete...\n");
    for (int i = 0; i < 4; i++) pthread_join(threads[i], NULL);

    printf("✅ [SYSTEM] Pi-RTOS-Edge Gateway stopped successfully\n");
    return 0;
}
