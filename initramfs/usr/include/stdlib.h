#pragma once

#include <syscall.h>

long strlen(const char *s) {
    long len = 0;
    while (*s++) len++;
    return len;
}

void puts(const char *s) {
    syscall(SYS_write, 1, s, strlen(s));
}

void gets(char *s, long maxlen) {
    long n = syscall(SYS_read, 0, s, maxlen - 1);
    if (n > 0) {
        s[n] = '\0';
    } else {
        s[0] = '\0';
    }
}

void putchar(char c) {
    syscall(SYS_write, 1, &c, 1);
}

int exec(const char *path, char *const argv[], char *const envp[]) {
    return syscall(SYS_execve, path, argv, envp);
}

long filesize(const char *path) {
    int fd = syscall(SYS_open, path, O_RDONLY);
    if (fd < 0)
        return -1;

    long size = syscall(SYS_lseek, fd, 0, SEEK_END);

    syscall(SYS_close, fd);
    return size;
}

long getfilecont(const char *path, char *buf) {
    long size = filesize(path);
    int fd = syscall(SYS_open, path, O_RDONLY);
    if (fd < 0)
        return -1;

    long n = syscall(SYS_read, fd, buf, size - 1);
    syscall(SYS_close, fd);

    if (n < 0)
        return -1;

    buf[n] = '\0';
    return n;
}

void outfilecont(const char *path, const char *buf, long len) {
    int fd = syscall(SYS_open, path, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0) {
        return;
    }
    syscall(SYS_write, fd, buf, len);
    syscall(SYS_close, fd);
}

void exit(int code) {
    syscall(SYS_exit, code);
}