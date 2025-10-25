# DeviceDriverPj
Got it ✅ — I’ll update the **README.md** for your Raspberry Pi 4 / UART-compatible **simple Linux character driver** project, including GPL license info and making it look professional for your GitHub repo.  

Here’s the improved **README.md**:

***

# Simple Linux Character Driver

## 📌 Overview
This project implements a **simple Linux character device driver** that allows user-space programs to write data into the driver and read it back.  
It uses a **dynamically allocated major number**, works without additional hardware, and can be tested on **Raspberry Pi 4 via UART** or on any Linux system.

This project is intended for **learning Linux kernel development** and showcasing driver skills in your **portfolio/resume**.

***

## ✨ Features
- Dynamic major number allocation (avoids conflicts)
- Implements `open`, `read`, `write`, and `release` operations
- Safe user-kernel data transfer using `copy_to_user` and `copy_from_user`
- Works on Raspberry Pi 4 (can use UART console for testing)
- Comes with a C test application for user-space interaction

***

## 📂 Project Structure
```
.
├── char_dynDriver.c  # Kernel module source code
├── Makefile          # For building the kernel module
├── test_driver.c     # User-space test program
└── README.md         # Project documentation
```

***

## 🔧 Building & Installing the Driver

1. **Compile the driver module**
   ```bash
   make
   ```

2. **Insert the module**
   ```bash
   sudo insmod char_driver.ko
   ```

3. **Check assigned major number**
   ```bash
   dmesg | tail
   ```

4. **Create a device file** (`` from previous step)
   ```bash
   sudo mknod /dev/simple_char c  0
   sudo chmod 666 /dev/simple_char
   ```

***

## 🖥 Testing the Driver

### **Option 1: Using Shell Commands**
```bash
echo "Hello from terminal!" > /dev/simple_char
cat /dev/simple_char
```

### **Option 2: Using Test Program**
1. **Compile the program**
   ```bash
   gcc test_driver.c -o test_driver
   ```

2. **Run it**
   ```bash
   ./test_driver
   ```

***

## 🛠 Testing via Raspberry Pi 4 UART
1. **Enable UART** in `/boot/config.txt`:
   ```
   enable_uart=1
   ```
   Then reboot:
   ```bash
   sudo reboot
   ```

2. **Use a USB-to-Serial adapter** to connect to Pi’s GPIO pins:
   - GPIO14 (TX) → Adapter RX  
   - GPIO15 (RX) → Adapter TX  
   - GND → Adapter GND  

3. **Open a serial terminal** (115200 baud, 8N1) on your PC.

4. **Login via UART** and run the above test commands/program.

***

## 📜 License
This project is licensed under the **GNU General Public License (GPL) v2**, the same license used by the Linux kernel.  
You are free to use, modify, and distribute this code, but derivatives must also remain open-source and GPL-licensed.

***

## 👤 Author
**Shrihari Vaidya**  
Bengaluru, Karnataka, India  
*GitHub:* [shrihari099]  

***

## 🚀 Notes
- This driver is **for educational purposes**.
- Works on **any Linux kernel with module support**.
- Testable in real hardware **or** in QEMU virtualized Raspberry Pi setups.

***
