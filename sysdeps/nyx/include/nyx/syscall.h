#ifndef _NYX_SYSCALL_H
#define _NYX_SYSCALL_H

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
#define SYS_SET_FS_BASE 16

struct __syscall_ret {
  uint64_t ret;
  uint64_t errno;
};

static inline struct __syscall_ret __syscall0(int syscall) {
  struct __syscall_ret ret;

  __asm__ volatile("int $0x42"
                   : "=b"(ret.errno), "=a"(ret.ret)
                   : "a"(syscall)
                   : "r10", "r11", "memory");
  return ret;
}

static inline struct __syscall_ret __syscall1(int syscall, uint64_t param1) {
  struct __syscall_ret ret;

  __asm__ volatile("int $0x42"
                   : "=b"(ret.errno), "=a"(ret.ret)
                   : "a"(syscall), "D"(param1)
                   : "r10", "r11", "memory");

  return ret;
}

static inline struct __syscall_ret __syscall2(int syscall, uint64_t param1,
                                              uint64_t param2) {
  struct __syscall_ret ret;

  __asm__ volatile("int $0x42"
                   : "=b"(ret.errno), "=a"(ret.ret)
                   : "a"(syscall), "D"(param1), "S"(param2)
                   : "r10", "r11", "memory");

  return ret;
}

static inline struct __syscall_ret
__syscall3(int syscall, uint64_t param1, uint64_t param2, uint64_t param3) {
  struct __syscall_ret ret;

  __asm__ volatile("int $0x42"
                   : "=b"(ret.errno), "=a"(ret.ret)
                   : "a"(syscall), "D"(param1), "S"(param2), "d"(param3)
                   : "r10", "r11", "memory");

  return ret;
}

static inline struct __syscall_ret __syscall4(int syscall, uint64_t param1,
                                              uint64_t param2, uint64_t param3,
                                              uint64_t param4) {
  struct __syscall_ret ret;

  __asm__ volatile("int $0x42"
                   : "=b"(ret.errno), "=a"(ret.ret)
                   : "a"(syscall), "D"(param1), "S"(param2), "d"(param3),
                     "c"(param4)
                   : "r10", "r11", "memory");

  return ret;
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
