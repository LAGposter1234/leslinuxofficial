#include <stdlib.h>

void _start(void) {
// int main() {
    // set user to user
    //syscall(SYS_setuid, 1000);
    //syscall(SYS_setgid, 1000);
    char *env[] = {
        "PATH=/bin:/usr/bin",
        "HOME=/home/root",
        "TERM=linux",
        NULL
    };
    char *args[] = { "/bin/bash", NULL };
    exec("/bin/bash", args, env);

// return 0;
    syscall(SYS_exit, 0);
}