#include "mlibc/ansi-sysdeps.hpp"
#include "mlibc/internal-sysdeps.hpp"
#include <abi-bits/fcntl.h>
#include <asm/ioctls.h>
#include <bits/ensure.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <frg/hash.hpp>
#include <frg/hash_map.hpp>
#include <limits.h>
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/allocator.hpp>
#include <mlibc/debug.hpp>
#include <nyx/syscall.h>
#include <stdlib.h>

#define STRINGIFY_(X) #X
#define STRINGIFY(X) STRINGIFY_(X)
#define STUB_ONLY                                                              \
  {                                                                            \
    sys_libc_log(                                                              \
        "STUB_ONLY function on line " STRINGIFY(__LINE__) " was called");      \
    sys_libc_panic();                                                          \
  }

int __mlibc_get_posix_port();
namespace mlibc {

void sys_libc_log(const char *message) { __syscall(SYS_LOG, message); }

void sys_libc_panic() {
  sys_libc_log("\nMLIBC PANIC\n");
  sys_exit(1);
  __builtin_unreachable();
}

void sys_exit(int status) {
  __syscall(SYS_EXIT, status);
  __builtin_unreachable();
}

int sys_tcb_set(void *pointer) {
  __syscall(SYS_SET_FS_BASE, pointer);
  return 0;
}

extern "C" int posix_open(int port, int pid, const char *path, mode_t mode);
extern "C" int posix_read(int port, int pid, int fd, void *buf, size_t count);
extern "C" int posix_write(int port, int pid, int fd, void *buf, size_t count);
extern "C" int posix_close(int port, int pid, int fd);
extern "C" int posix_seek(int port, int pid, int fd, off_t offset, int whence);
extern "C" int posix_mmap(int port, int32_t pid, int32_t fd, void *space,
                          void *hint, int64_t size, int32_t prot, int32_t flags,
                          int64_t offset, void *out, int64_t out_size);

int sys_open(const char *path, int flags, mode_t mode, int *fd) {
  (void)flags;
  *fd = posix_open(__mlibc_get_posix_port(), sys_getpid(), path, mode);
  return 0;
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
  posix_read(__mlibc_get_posix_port(), sys_getpid(), fd, buf, count);
  *bytes_read = count;
  return 0;
}

int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
  posix_write(__mlibc_get_posix_port(), sys_getpid(), fd, (void *)buf, count);
  *bytes_written = count;
  return 0;
}

int sys_close(int fd) {
  posix_close(__mlibc_get_posix_port(), sys_getpid(), fd);
  return 0;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
  *new_offset =
      posix_seek(__mlibc_get_posix_port(), sys_getpid(), fd, offset, whence);
  return 0;
}

int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd,
               off_t offset, void **window) {
  struct [[gnu::packed]] {
    void *space;
    size_t pid;
  } task;
  __syscall(SYS_GET_TASK, &task);
  return posix_mmap(__mlibc_get_posix_port(), sys_getpid(), fd, task.space,
                    hint, size, prot, flags, offset, (void *)window,
                    sizeof(void *));
}

int sys_anon_allocate(size_t size, void **pointer) {
  return sys_vm_map(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0,
                    pointer);
}

int sys_vm_unmap(void *pointer, size_t size) {
  (void)pointer;
  (void)size;
  return 0;
}

int sys_anon_free(void *pointer, size_t size) {
  (void)pointer;
  (void)size;
  // return sys_vm_unmap(pointer, size);
  return 0;
}

int sys_futex_wait(int *pointer, int expected, timespec const *time) {
  (void)pointer;
  (void)expected;
  (void)time;
  __ensure(!"sys_futex_wait function was called");
  __builtin_unreachable();
}
int sys_futex_wake(int *pointer) {
  (void)pointer;
  __ensure(!"sys_futex_wake function was called");
  __builtin_unreachable();
}

int sys_clock_get(int clock, time_t *secs, long *nanos) {
  (void)clock;
  (void)secs;
  (void)nanos;

  __ensure(!"sys_clock_get function was called");
  __builtin_unreachable();
}

} // namespace mlibc
