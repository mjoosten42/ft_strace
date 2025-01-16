#include "syscall.h"

#include <stddef.h>

const t_syscall_prototype *syscall_get_prototype(int nr) {
	static const t_syscall_prototype syscalls[] = {
		{ 0, 3, "read", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 1, 3, "write", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 2, 3, "open", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%u", 4 } } },
		{ 3, 1, "close", { "%i", 4 }, { { "%i", 4 } } },
		{ 4, 2, "stat", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 5, 2, "fstat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 6, 2, "lstat", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 7, 3, "poll", { "%i", 4 }, { { "%p", 8 }, { "%lu", 8 }, { "%i", 4 } } },
		{ 8, 3, "lseek", { "%li", 8 }, { { "%i", 4 }, { "%li", 8 }, { "%i", 4 } } },
		{ 9,
		  6,
		  "mmap",
		  { "%p", 8 },
		  { { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%li", 8 } } },
		{ 10, 3, "mprotect", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 11, 2, "munmap", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 12, 1, "brk", { "%p", 8 }, { { "%p", 8 } } },
		{ 13, 4, "rt_sigaction", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 14, 4, "rt_sigprocmask", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 15, 0, "rt_sigreturn", { "%i", 4 }, {} },
		{ 16, 2, "ioctl", { "%i", 4 }, { { "%i", 4 }, { "%lu", 8 } } },
		{ 17, 4, "pread64", { "%li", 8 }, { { "%u", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 } } },
		{ 18, 4, "pwrite64", { "%li", 8 }, { { "%u", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 } } },
		{ 19, 3, "readv", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 20, 3, "writev", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 21, 2, "access", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 22, 1, "pipe", { "%i", 4 }, { { "%p", 8 } } },
		{ 23, 5, "select", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 24, 0, "sched_yield", { "%i", 4 }, {} },
		{ 25, 4, "mremap", { "%p", 8 }, { { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 26, 3, "msync", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 27, 3, "mincore", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 28, 3, "madvise", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 29, 3, "shmget", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 30, 3, "shmat", { "%p", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 31, 3, "shmctl", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 32, 1, "dup", { "%i", 4 }, { { "%i", 4 } } },
		{ 33, 2, "dup2", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 34, 0, "pause", { "%i", 4 }, {} },
		{ 35, 2, "nanosleep", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 36, 2, "getitimer", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 37, 1, "alarm", { "%u", 4 }, { { "%u", 4 } } },
		{ 38, 3, "setitimer", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 39, 0, "getpid", { "%i", 4 }, {} },
		{ 40, 4, "sendfile", { "%li", 8 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 41, 3, "socket", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 42, 3, "connect", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 43, 3, "accept", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 44,
		  6,
		  "sendto",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 45,
		  6,
		  "recvfrom",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 46, 3, "sendmsg", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 47, 3, "recvmsg", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 48, 2, "shutdown", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 49, 3, "bind", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 50, 2, "listen", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 51, 3, "getsockname", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 52, 3, "getpeername", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 53, 4, "socketpair", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 54, 5, "setsockopt", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 55, 5, "getsockopt", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 56, 4, "clone", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 57, 0, "fork", { "%i", 4 }, {} },
		{ 58, 0, "vfork", { "%i", 4 }, {} },
		{ 59, 3, "execve", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 60, 1, "exit", { "%i", -2 }, { { "%i", 4 } } },
		{ 61, 4, "wait4", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 62, 2, "kill", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 63, 1, "uname", { "%i", 4 }, { { "%p", 8 } } },
		{ 64, 3, "semget", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 65, 3, "semop", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 66, 3, "semctl", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 67, 1, "shmdt", { "%i", 4 }, { { "%p", 8 } } },
		{ 68, 2, "msgget", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 69, 4, "msgsnd", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 70, 5, "msgrcv", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 }, { "%i", 4 } } },
		{ 71, 3, "msgctl", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 72, 2, "fcntl", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 73, 2, "flock", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 74, 1, "fsync", { "%i", 4 }, { { "%i", 4 } } },
		{ 75, 1, "fdatasync", { "%i", 4 }, { { "%i", 4 } } },
		{ 76, 2, "truncate", { "%i", 4 }, { { "%p", 8 }, { "%li", 8 } } },
		{ 77, 2, "ftruncate", { "%i", 4 }, { { "%i", 4 }, { "%li", 8 } } },
		{ 78, 3, "getdents", { "%li", 8 }, { { "%u", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 79, 2, "getcwd", { "%p", 8 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 80, 1, "chdir", { "%i", 4 }, { { "%p", 8 } } },
		{ 81, 1, "fchdir", { "%i", 4 }, { { "%i", 4 } } },
		{ 82, 2, "rename", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 83, 2, "mkdir", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 } } },
		{ 84, 1, "rmdir", { "%i", 4 }, { { "%p", 8 } } },
		{ 85, 2, "creat", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 } } },
		{ 86, 2, "link", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 87, 1, "unlink", { "%i", 4 }, { { "%p", 8 } } },
		{ 88, 2, "symlink", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 89, 3, "readlink", { "%li", 8 }, { { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 90, 2, "chmod", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 } } },
		{ 91, 2, "fchmod", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 } } },
		{ 92, 3, "chown", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 }, { "%u", 4 } } },
		{ 93, 3, "fchown", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 }, { "%u", 4 } } },
		{ 94, 3, "lchown", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 }, { "%u", 4 } } },
		{ 95, 1, "umask", { "%u", 4 }, { { "%u", 4 } } },
		{ 96, 2, "gettimeofday", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 97, 2, "getrlimit", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 98, 2, "getrusage", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 99, 1, "sysinfo", { "%i", 4 }, { { "%p", 8 } } },
		{ 100, 1, "times", { "%li", 8 }, { { "%p", 8 } } },
		{ 101, 4, "ptrace", { "%li", 8 }, { { "%d", 8 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 102, 0, "getuid", { "%u", 4 }, {} },
		{ 103, 3, "syslog", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 104, 0, "getgid", { "%u", 4 }, {} },
		{ 105, 1, "setuid", { "%i", 4 }, { { "%u", 4 } } },
		{ 106, 1, "setgid", { "%i", 4 }, { { "%u", 4 } } },
		{ 107, 0, "geteuid", { "%u", 4 }, {} },
		{ 108, 0, "getegid", { "%u", 4 }, {} },
		{ 109, 2, "setpgid", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 110, 0, "getppid", { "%i", 4 }, {} },
		{ 111, 1, "getpgrp", { "%i", 4 }, { { "%i", 4 } } },
		{ 112, 0, "setsid", { "%i", 4 }, {} },
		{ 113, 2, "setreuid", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 } } },
		{ 114, 2, "setregid", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 } } },
		{ 115, 2, "getgroups", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 116, 2, "setgroups", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 117, 3, "setresuid", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 }, { "%u", 4 } } },
		{ 118, 3, "getresuid", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 119, 3, "setresgid", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 }, { "%u", 4 } } },
		{ 120, 3, "getresgid", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 121, 1, "getpgid", { "%i", 4 }, { { "%i", 4 } } },
		{ 122, 1, "setfsuid", { "%i", 4 }, { { "%u", 4 } } },
		{ 123, 1, "setfsgid", { "%i", 4 }, { { "%u", 4 } } },
		{ 124, 1, "getsid", { "%i", 4 }, { { "%i", 4 } } },
		{ 125, 2, "capget", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 126, 2, "capset", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 127, 2, "rt_sigpending", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 128, 4, "rt_sigtimedwait", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 129, 3, "rt_sigqueueinfo", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 130, 2, "rt_sigsuspend", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 131, 2, "sigaltstack", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 132, 2, "utime", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 133, 3, "mknod", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 }, { "%lu", 8 } } },
		{ 134, 1, "uselib", { "%i", 4 }, { { "%p", 8 } } },
		{ 135, 1, "personality", { "%i", 4 }, { { "%lu", 8 } } },
		{ 136, 2, "ustat", { "%i", 4 }, { { "%lu", 8 }, { "%p", 8 } } },
		{ 137, 2, "statfs", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 138, 2, "fstatfs", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 139, 3, "sysfs", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 }, { "%p", 8 } } },
		{ 140, 2, "getpriority", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 } } },
		{ 141, 3, "setpriority", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 }, { "%i", 4 } } },
		{ 142, 2, "sched_setparam", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 143, 2, "sched_getparam", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 144, 3, "sched_setscheduler", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 145, 1, "sched_getscheduler", { "%i", 4 }, { { "%i", 4 } } },
		{ 146, 1, "sched_get_priority_max", { "%i", 4 }, { { "%i", 4 } } },
		{ 147, 1, "sched_get_priority_min", { "%i", 4 }, { { "%i", 4 } } },
		{ 148, 2, "sched_rr_get_interval", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 149, 2, "mlock", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 150, 2, "munlock", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 151, 1, "mlockall", { "%i", 4 }, { { "%i", 4 } } },
		{ 152, 0, "munlockall", { "%i", 4 }, {} },
		{ 153, 0, "vhangup", { "%i", 4 }, {} },
		{ 154, 3, "modify_ldt", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%lu", 8 } } },
		{ 155, 2, "pivot_root", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 156, 1, "_sysctl", { "%i", 4 }, { { "%p", 8 } } },
		{ 157, 5, "prctl", { "%i", 4 }, { { "%i", 4 }, { "%lu", 8 }, { "%lu", 8 }, { "%lu", 8 }, { "%lu", 8 } } },
		{ 158, 2, "arch_prctl", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 159, 1, "adjtimex", { "%i", 4 }, { { "%p", 8 } } },
		{ 160, 2, "setrlimit", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 161, 1, "chroot", { "%i", 4 }, { { "%p", 8 } } },
		{ 162, 0, "sync", { "%i", -2 }, {} },
		{ 163, 1, "acct", { "%i", 4 }, { { "%p", 8 } } },
		{ 164, 2, "settimeofday", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 165, 5, "mount", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%lu", 8 }, { "%p", 8 } } },
		{ 166, 2, "umount2", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 167, 2, "swapon", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 168, 1, "swapoff", { "%i", 4 }, { { "%p", 8 } } },
		{ 169, 1, "reboot", { "%i", 4 }, { { "%i", 4 } } },
		{ 170, 2, "sethostname", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 171, 2, "setdomainname", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 172, 1, "iopl", { "%i", 4 }, { { "%i", 4 } } },
		{ 173, 3, "ioperm", { "%i", 4 }, { { "%lu", 8 }, { "%lu", 8 }, { "%i", 4 } } },
		{ 174, 2, "create_module", { "%p", 8 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 175, 3, "init_module", { "%i", 4 }, { { "%p", 8 }, { "%lu", 8 }, { "%p", 8 } } },
		{ 176, 2, "delete_module", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 177, 1, "get_kernel_syms", { "%i", 4 }, { { "%p", 8 } } },
		{ 178, 5, "query_module", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 179, 4, "quotactl", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 180, 3, "nfsservctl", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 181, 0, "getpmsg", { "%i", 4 }, {} },
		{ 182, 0, "putpmsg", { "%i", 4 }, {} },
		{ 183, 0, "afs_syscall", { "%i", 4 }, {} },
		{ 184, 0, "tuxcall", { "%i", 4 }, {} },
		{ 185, 0, "security", { "%i", 4 }, {} },
		{ 186, 0, "gettid", { "%i", 4 }, {} },
		{ 187, 3, "readahead", { "%li", 8 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 188, 5, "setxattr", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 189, 5, "lsetxattr", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 190, 5, "fsetxattr", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 191, 4, "getxattr", { "%li", 8 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 192, 4, "lgetxattr", { "%li", 8 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 193, 4, "fgetxattr", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 194, 3, "listxattr", { "%li", 8 }, { { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 195, 3, "llistxattr", { "%li", 8 }, { { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 196, 3, "flistxattr", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 197, 2, "removexattr", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 198, 2, "lremovexattr", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 199, 2, "fremovexattr", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 200, 2, "tkill", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 201, 1, "time", { "%li", 8 }, { { "%p", 8 } } },
		{ 202,
		  6,
		  "futex",
		  { "%li", 8 },
		  { { "%p", 8 }, { "%i", 4 }, { "%u", 4 }, { "%p", 8 }, { "%p", 8 }, { "%u", 4 } } },
		{ 203, 3, "sched_setaffinity", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 204, 3, "sched_getaffinity", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 205, 1, "set_thread_area", { "%i", 4 }, { { "%p", 8 } } },
		{ 206, 2, "io_setup", { "%li", 8 }, { { "%u", 4 }, { "%p", 8 } } },
		{ 207, 1, "io_destroy", { "%i", 4 }, { { "%lu", 8 } } },
		{ 208, 5, "io_getevents", { "%i", 4 }, { { "%lu", 8 }, { "%li", 8 }, { "%li", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 209, 3, "io_submit", { "%i", 4 }, { { "%lu", 8 }, { "%li", 8 }, { "%p", 8 } } },
		{ 210, 3, "io_cancel", { "%i", 4 }, { { "%lu", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 211, 1, "get_thread_area", { "%i", 4 }, { { "%p", 8 } } },
		{ 212, 3, "lookup_dcookie", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 213, 1, "epoll_create", { "%i", 4 }, { { "%i", 4 } } },
		{ 214, 3, "epoll_ctl_old", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 215, 3, "epoll_wait_old", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 216,
		  5,
		  "remap_file_pages",
		  { "%i", 4 },
		  { { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 217, 3, "getdents64", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 218, 1, "set_tid_address", { "%i", 4 }, { { "%p", 8 } } },
		{ 219, 0, "restart_syscall", { "%li", 8 }, {} },
		{ 220, 4, "semtimedop", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 221, 4, "fadvise64", { "%i", 4 }, { { "%i", 4 }, { "%li", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 222, 3, "timer_create", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 223, 4, "timer_settime", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 224, 2, "timer_gettime", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 } } },
		{ 225, 1, "timer_getoverrun", { "%i", 4 }, { { "%p", 8 } } },
		{ 226, 1, "timer_delete", { "%i", 4 }, { { "%p", 8 } } },
		{ 227, 2, "clock_settime", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 228, 2, "clock_gettime", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 229, 2, "clock_getres", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 230, 4, "clock_nanosleep", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 231, 1, "exit_group", { "%i", -2 }, { { "%i", 4 } } },
		{ 232, 4, "epoll_wait", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 233, 4, "epoll_ctl", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 234, 3, "tgkill", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 235, 2, "utimes", { "%i", 4 }, { { "%p", 8 }, { "%p", 32 } } },
		{ 236, 0, "vserver", { "%i", 4 }, {} },
		{ 237,
		  6,
		  "mbind",
		  { "%li", 8 },
		  { { "%p", 8 }, { "%lu", 8 }, { "%i", 4 }, { "%p", 8 }, { "%lu", 8 }, { "%u", 4 } } },
		{ 238, 3, "set_mempolicy", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%lu", 8 } } },
		{ 239,
		  5,
		  "get_mempolicy",
		  { "%li", 8 },
		  { { "%p", 8 }, { "%p", 8 }, { "%lu", 8 }, { "%p", 8 }, { "%lu", 8 } } },
		{ 240, 4, "mq_open", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%u", 4 }, { "%p", 8 } } },
		{ 241, 1, "mq_unlink", { "%i", 4 }, { { "%p", 8 } } },
		{ 242, 5, "mq_timedsend", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%u", 4 }, { "%p", 8 } } },
		{ 243,
		  5,
		  "mq_timedreceive",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 244, 2, "mq_notify", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 245, 3, "mq_getsetattr", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 246, 4, "kexec_load", { "%li", 8 }, { { "%lu", 8 }, { "%lu", 8 }, { "%p", 8 }, { "%lu", 8 } } },
		{ 247, 4, "waitid", { "%i", 4 }, { { "%d", 4 }, { "%u", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 248, 5, "add_key", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 249, 4, "request_key", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 250, 1, "keyctl", { "%li", 8 }, { { "%i", 4 } } },
		{ 251, 3, "ioprio_set", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 252, 2, "ioprio_get", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 253, 0, "inotify_init", { "%i", 4 }, {} },
		{ 254, 3, "inotify_add_watch", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 255, 2, "inotify_rm_watch", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 256, 4, "migrate_pages", { "%li", 8 }, { { "%i", 4 }, { "%lu", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 257, 4, "openat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%u", 4 } } },
		{ 258, 3, "mkdirat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 259, 4, "mknodat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 }, { "%lu", 8 } } },
		{ 260, 5, "fchownat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 }, { "%u", 4 }, { "%i", 4 } } },
		{ 261, 3, "futimesat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 32 } } },
		{ 262, 4, "newfstatat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 263, 3, "unlinkat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 264, 4, "renameat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 265, 5, "linkat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 266, 3, "symlinkat", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 267, 4, "readlinkat", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 268, 4, "fchmodat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 }, { "%i", 4 } } },
		{ 269, 4, "faccessat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 270,
		  6,
		  "pselect6",
		  { "%i", 4 },
		  { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 271, 4, "ppoll", { "%i", 4 }, { { "%p", 8 }, { "%lu", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 272, 1, "unshare", { "%i", 4 }, { { "%i", 4 } } },
		{ 273, 2, "set_robust_list", { "%li", 8 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 274, 3, "get_robust_list", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 275,
		  6,
		  "splice",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%u", 4 } } },
		{ 276, 4, "tee", { "%li", 8 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%u", 4 } } },
		{ 277, 4, "sync_file_range", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%u", 4 } } },
		{ 278, 4, "vmsplice", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%lu", 8 }, { "%u", 4 } } },
		{ 279,
		  6,
		  "move_pages",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%lu", 8 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 280, 4, "utimensat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 32 }, { "%i", 4 } } },
		{ 281, 5, "epoll_pwait", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 282, 3, "signalfd", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 283, 2, "timerfd_create", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 284, 2, "eventfd", { "%i", 4 }, { { "%u", 4 }, { "%i", 4 } } },
		{ 285, 4, "fallocate", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%li", 8 }, { "%li", 8 } } },
		{ 286, 4, "timerfd_settime", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 287, 2, "timerfd_gettime", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 288, 4, "accept4", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 289, 4, "signalfd4", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 290, 2, "eventfd2", { "%i", 4 }, { { "%u", 4 }, { "%i", 4 } } },
		{ 291, 1, "epoll_create1", { "%i", 4 }, { { "%i", 4 } } },
		{ 292, 3, "dup3", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 293, 2, "pipe2", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 294, 1, "inotify_init1", { "%i", 4 }, { { "%i", 4 } } },
		{ 295, 4, "preadv", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 } } },
		{ 296, 4, "pwritev", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 } } },
		{ 297, 4, "rt_tgsigqueueinfo", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 298,
		  5,
		  "perf_event_open",
		  { "%i", 4 },
		  { { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%lu", 8 } } },
		{ 299, 5, "recvmmsg", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 }, { "%i", 4 }, { "%p", 8 } } },
		{ 300, 2, "fanotify_init", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 } } },
		{ 301, 5, "fanotify_mark", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 }, { "%lu", 8 }, { "%i", 4 }, { "%p", 8 } } },
		{ 302, 4, "prlimit64", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 }, { "%p", 8 }, { "%p", 8 } } },
		{ 303,
		  5,
		  "name_to_handle_at",
		  { "%i", 4 },
		  { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 304, 3, "open_by_handle_at", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 305, 2, "clock_adjtime", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 } } },
		{ 306, 1, "syncfs", { "%i", 4 }, { { "%i", 4 } } },
		{ 307, 4, "sendmmsg", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 }, { "%i", 4 } } },
		{ 308, 2, "setns", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 } } },
		{ 309, 3, "getcpu", { "%i", 4 }, { { "%p", 8 }, { "%p", 8 }, { "%p", 8 } } },
		{ 310,
		  6,
		  "process_vm_readv",
		  { "%i", 4 },
		  { { "%i", 4 }, { "%p", 8 }, { "%lu", 8 }, { "%p", 8 }, { "%lu", 8 }, { "%lu", 8 } } },
		{ 311,
		  6,
		  "process_vm_writev",
		  { "%i", 4 },
		  { { "%i", 4 }, { "%p", 8 }, { "%lu", 8 }, { "%p", 8 }, { "%lu", 8 }, { "%lu", 8 } } },
		{ 312, 5, "kcmp", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%i", 4 }, { "%lu", 8 }, { "%lu", 8 } } },
		{ 313, 3, "finit_module", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 } } },
		{ 314, 3, "sched_setattr", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 315, 4, "sched_getattr", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 }, { "%u", 4 } } },
		{ 316, 5, "renameat2", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 317, 3, "seccomp", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 }, { "%p", 8 } } },
		{ 318, 3, "getrandom", { "%li", 8 }, { { "%p", 8 }, { "%i", 4 }, { "%u", 4 } } },
		{ 319, 2, "memfd_create", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 } } },
		{ 320,
		  5,
		  "kexec_file_load",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%i", 4 }, { "%lu", 8 }, { "%p", 8 }, { "%lu", 8 } } },
		{ 321, 3, "bpf", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 322, 5, "execveat", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 323, 1, "userfaultfd", { "%i", 4 }, { { "%i", 4 } } },
		{ 324, 3, "membarrier", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 }, { "%i", 4 } } },
		{ 325, 3, "mlock2", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
		{ 326,
		  6,
		  "copy_file_range",
		  { "%li", 8 },
		  { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%u", 4 } } },
		{ 327, 5, "preadv2", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 }, { "%i", 4 } } },
		{ 328, 5, "pwritev2", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%li", 8 }, { "%i", 4 } } },
		{ 329, 4, "pkey_mprotect", { "%i", 4 }, { { "%p", 8 }, { "%i", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 330, 2, "pkey_alloc", { "%i", 4 }, { { "%u", 4 }, { "%u", 4 } } },
		{ 331, 1, "pkey_free", { "%i", 4 }, { { "%i", 4 } } },
		{ 332, 5, "statx", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%u", 4 }, { "%p", 8 } } },
		{ 0 },
		{ 334, 4, "rseq", { "%i", 4 }, { { "%p", 8 }, { "%u", 4 }, { "%i", 4 }, { "%i", 4 } } },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 424, 4, "pidfd_send_signal", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%p", 8 }, { "%u", 4 } } },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 434, 2, "pidfd_open", { "%i", 4 }, { { "%i", 4 }, { "%u", 4 } } },
		{ 435, 2, "clone3", { "%li", 8 }, { { "%p", 8 }, { "%i", 4 } } },
		{ 0 },
		{ 437, 4, "openat2", { "%li", 8 }, { { "%i", 4 }, { "%p", 8 }, { "%p", 8 }, { "%i", 4 } } },
		{ 438, 3, "pidfd_getfd", { "%i", 4 }, { { "%i", 4 }, { "%i", 4 }, { "%u", 4 } } },
		{ 439, 4, "faccessat2", { "%i", 4 }, { { "%i", 4 }, { "%p", 8 }, { "%i", 4 }, { "%i", 4 } } },
	};

	return &syscalls[nr];
}

const size_t syscall_max = 440;
