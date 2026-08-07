#include <stdlib.h>

/*
* LesLinux INIT system
* NO rights reseved
* EVIL microsoft (open source)
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
    syscall(SYS_mount,
        "devtmpfs",
        "/dev",
        "devtmpfs",
        0,
        NULL);

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