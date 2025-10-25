#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char write_buf[100] = "Hello from user space!";
    char read_buf[100];

    fd = open("/dev/simple_char", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return 1;
    }

    write(fd, write_buf, sizeof(write_buf));
    read(fd, read_buf, sizeof(read_buf));

    printf("Data read from device: %s\n", read_buf);

    close(fd);
    return 0;
}

