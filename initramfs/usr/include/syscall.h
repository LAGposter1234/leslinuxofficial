#include <stdarg.h>
#define SYS_write 1
#define SYS_exit 60
#define SYS_fork 57
#define SYS_execve 59
#define SYS_wait4 61
#define SYS_getpid 39
#define SYS_getppid 110
#define SYS_access 21
#define SYS_open 2
#define SYS_close 3
#define SYS_read 0
#define SYS_lseek 8
#define SYS_brk 12
#define SYS_mmap 9
#define SYS_munmap 11
#define SYS_chdir 80
#define SYS_getcwd 79
#define SYS_dup 32
#define SYS_dup2 33
#define X_OK 1
#define F_OK 0
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 64
#define O_TRUNC 512
#define O_APPEND 1024
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define MAP_PRIVATE 2
#define MAP_ANONYMOUS 32
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
#define PROT_NONE 0
#define MAP_FAILED ((void *)-1)
#define NULL ((void *)0)
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define SYS_clone 56
#define SYS_kill 62
#define SYS_uname 63
#define SYS_stat 4
#define SYS_fstat 5
#define SYS_lstat 6
#define SYS_getdents64 217
#define SYS_mkdir 83
#define SYS_unlink 87
#define SYS_rename 82
#define SYS_mount 165
#define SYS_ioctl 16
#define SYS_mprotect 10
#define SYS_exit_group 231
#define O_DIRECTORY 65536
#define O_CLOEXEC 524288
#define MAP_SHARED 1
#define MAP_FIXED 16
#define SYS_mount 165
#define SYS_sethostname 170
#define SYS_openat 288
#define SYS_setuid 105
#define SYS_setgid 106

typedef unsigned long size_t;
typedef long ssize_t;

typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;

void *memset(void *s, int c, size_t n){
    unsigned char *p = s;
    while (n--)
        *p++ = c;
    return s;
}

/*
* I literally have no idea why memset is required
* tcc is complaining about it
* even when i put -nostdlib
* like bro SYFM 💔💔💔
*/

long syscall(long number, ...)
{
    va_list args;
    va_start(args, number);

    long a1 = va_arg(args, long);
    long a2 = va_arg(args, long);
    long a3 = va_arg(args, long);
    register long a4 asm("r10") = va_arg(args, long);
    register long a5 asm("r8")  = va_arg(args, long);
    register long a6 asm("r9")  = va_arg(args, long);

    va_end(args);

    long ret;

    asm volatile(
        "syscall"
        : "=a"(ret)
        : "a"(number),
          "D"(a1),
          "S"(a2),
          "d"(a3),
          "r"(a4),
          "r"(a5),
          "r"(a6)
        : "rcx", "r11", "memory"
    );

    return ret;
}