int __mlibc_posix_port = 0;

extern "C" int bootstrap_look_up(const char *name);
int __mlibc_get_posix_port() {
  if (__mlibc_posix_port == 0)
    __mlibc_posix_port = bootstrap_look_up(("org.nyx.posix"));
  return __mlibc_posix_port;
}