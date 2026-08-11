#include <stdlib.h>

extern int main(int argc, char **argv);

__attribute__((noreturn))
void _start(void) {
    int argc;
    char **argv;

    __asm__(
        "mov (%%rsp), %0\n"
        "lea 8(%%rsp), %1\n"
        : "=r"(argc), "=r"(argv)
    );

    syscall(SYS_exit, main(argc, argv));
    __builtin_unreachable();
}