# Pi-RTOS Edge Gateway - TODO List

## Core 1: Sensor Task
- [x] Generate fake sensor readings
- [x] Write readings to UART (/dev/ttyAMA0)
- [ ] Replace with real I2C/SPI sensor driver
- [ ] Buffer UART output for efficiency

## Core 2: Cloud Task
- [ ] Add MQTT client (paho.mqtt.c / mosquitto)
- [ ] TLS connection to Google Cloud IoT Core
- [ ] JWT-based authentication
- [ ] Retry/reconnect logic for network failures

## Core 3: OTA Task
- [ ] Integrate RAUC/swupdate for A/B updates
- [ ] Secure firmware with signatures
- [ ] Rollback support

## Core 4: Security Task
- [x] Monitor system load average
- [ ] Monitor CPU temp, memory, disk usage
- [ ] Verify secure boot state
- [ ] Validate cloud certificates

## General
- [ ] Replace printf with structured logging
- [ ] Add configuration file parsing (JSON/YAML)
- [ ] Implement message queues between tasks
- [ ] Add unit tests
