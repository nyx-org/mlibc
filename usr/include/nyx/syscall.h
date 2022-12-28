#ifndef _LYRE__SYSCALL_H
#define _LYRE__SYSCALL_H

#include <stdint.h>

#define SYS_LOG 0
#define SYS_EXIT 1
#define SYS_MSG 2
#define SYS_ALLOC_PORT 3
#define SYS_GET_COMMON_PORT 4
#define SYS_REGISTER_COMMON_PORT 5
#define SYS_VM_CREATE 6
#define SYS_CREATE_TASK 7
#define SYS_START_TASK 8
#define SYS_VM_WRITE 9
#define SYS_VM_MAP 10
#define SYS_VM_REGISTER_DMA_REGION 11
#define SYS_FREE_PORT 12
#define SYS_YIELD 13
#define SYS_GETPID 14
#define SYS_GET_TASK 15

struct __syscall_ret {
  uint64_t ret;
  uint64_t errno;
};

#define __SYSCALL_EXPAND(...)                                                  \
  struct __syscall_ret ret;                                                    \
  asm volatile("mov %%rsp, %%r10\n\t"                                          \
               "lea 1f(%%rip), %%r11\n\t"                                      \
               "sysenter\n\t"                                                  \
               "1:"                                                            \
               : "=a"(ret.ret), "=b"(ret.errno)__VA_ARGS__ "r10", "r11",       \
                 "memory");                                                    \
  return ret

static inline struct __syscall_ret __syscall5(int number, uint64_t a,
                                              uint64_t b, uint64_t c,
                                              uint64_t d, uint64_t e) {
  register uint64_t r8 asm("%r8") = d;
  register uint64_t r9 asm("%r9") = e;
  __SYSCALL_EXPAND(, "+d"(b), "+c"(c)
                   : "D"(number), "S"(a), "r"(r8), "r"(r9)
                   :);
}

static inline struct __syscall_ret
__syscall4(int number, uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
  register uint64_t r8 asm("%r8") = d;
  __SYSCALL_EXPAND(, "+d"(b), "+c"(c) : "D"(number), "S"(a), "r"(r8) :);
}

static inline struct __syscall_ret __syscall3(int number, uint64_t a,
                                              uint64_t b, uint64_t c) {
  __SYSCALL_EXPAND(, "+d"(b), "+c"(c) : "D"(number), "S"(a) :);
}

static inline struct __syscall_ret __syscall2(int number, uint64_t a,
                                              uint64_t b) {
  __SYSCALL_EXPAND(, "+d"(b) : "D"(number), "S"(a) : "rcx", );
}

static inline struct __syscall_ret __syscall1(int number, uint64_t a) {
  __SYSCALL_EXPAND( : "D"(number), "S"(a) : "rcx", "rdx", );
}

static inline struct __syscall_ret __syscall0(int number) {
  __SYSCALL_EXPAND( : "D"(number) : "rcx", "rdx", );
}

#define __SYSCALL_NARGS_SEQ(_0, _1, _2, _3, _4, _5, _6, _7, N, ...) N
#define __SYSCALL_NARGS(...)                                                   \
  __SYSCALL_NARGS_SEQ(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)

#define __SYSCALL_CONCAT1(X, Y) X##Y
#define __SYSCALL_CONCAT(X, Y) __SYSCALL_CONCAT1(X, Y)

#define __syscall(...)                                                         \
  ({                                                                           \
    struct __syscall_ret (*__SYSCALL_f)(int, ...);                             \
    __SYSCALL_f = (struct __syscall_ret(*)(int, ...))__SYSCALL_CONCAT(         \
        __syscall, __SYSCALL_NARGS(__VA_ARGS__));                              \
    __SYSCALL_f(__VA_ARGS__);                                                  \
  })

#endif
