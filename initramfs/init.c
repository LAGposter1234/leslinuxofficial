#include <stdlib.h>

/*
* Install media INIT
* The installer will replace this
* with the other init that mounts
* the drive at / instead of /mnt/persist
* But thats the only difference smh
*/

int _start(void) {
    // check PID
    if (syscall(SYS_getpid) != 1) {
        syscall(SYS_write, 1, "INIT must be started as PID 1\n", 32);
        syscall(SYS_exit, 1);
    }
    // clear screen
    puts("\033[2J\033[H");
    puts("\033[32m[ OK ]\033[0m INIT started as PID 1\n");
    puts("\033[33m[ TASK ]\033[0m Mount persistant storage\n");
    puts("\033[34m[ SUBTASK ]\033[0m Mount devtmpfs as /dev\n");
    syscall(SYS_mount,
        "devtmpfs",
        "/dev",
        "devtmpfs",
        0,
        NULL);
    // also secretly set up the secretly secret /proc and /sys filesystems
    syscall(SYS_mount, "proc", "/proc", "proc", 0, NULL);
    syscall(SYS_mount, "sysfs", "/sys", "sysfs", 0, NULL);
    // mount /dev/sda as /mnt/persist using mount syscall
    if (syscall(SYS_mount, "/dev/sda", "/home/", "ext4", 0, NULL) != 0) {
        // failed is red
        puts("\033[31m[ FAILED ]\033[0m Mount persistant storage\n");
    } else {
        puts("\032[33m[ OK ]\033[0m Mount persistant storage\n");
    }
    puts("\033[33m[ TASK ]\033[0m Start shell (Shouldnt return)\n");
    // check for sh
    if (syscall(SYS_access, "/bin/bash", X_OK) != 0) {
        puts("\033[31m[ FAILED ]\033[0m Start shell (bash not found)\n");
        while(1) {
            int i = 0;
            i++;
            // Code so that the c compiler dosent optimize this out

        }
    }
    puts("\032[33m[ OK ]\033[0m bash found\n");

    puts("\033[33m[ TASK ]\033[0m Set hostname\n");
    // set hostname to contents of /etc/hostname
    char hostname[256];
    int fd = syscall(SYS_open, "/etc/hostname", O_RDONLY);
    if (fd < 0) {
        puts("\033[31m[ FAILED ]\033[0m Set hostname (Could not open /etc/hostname)\n");
    } else {
        int n = syscall(SYS_read, fd, hostname, sizeof(hostname) - 1);
        if (n < 0) {
            puts("\033[31m[ FAILED ]\033[0m Set hostname (Could not read /etc/hostname)\n");
        } else {
            hostname[n] = '\0'; // null terminate
            // remove newline if present
            if (hostname[n - 1] == '\n') {
                hostname[n - 1] = '\0';
            }
            syscall(SYS_sethostname, hostname, strlen(hostname));
            puts("\033[32m[ OK ]\033[0m Set hostname to ");
            puts(hostname);
            puts("\n");
        }
        syscall(SYS_close, fd);
    }

    puts("Welcome to Lesbian's Linux!\n");
puts("\033[41m              \033[0m\n"); // Red
puts("\033[103m              \033[0m\n"); // Bright yellow
puts("\033[47m              \033[0m\n"); // White
puts("\033[105m              \033[0m\n"); // Bright magenta
puts("\033[45m              \033[0m\n"); // Magenta
    
    // start shell
    char *env[] = {
        "PATH=/bin",
        "HOME=/home/root",
        "TERM=linux",
        NULL
    };
    char *args[] = { "/bin/bash", "/root/init.sh", NULL };
    while(1) {
        //syscall(SYS_execve, args[0], args, env);
        exec(args[0], args, env);
    }
    return 0;
}