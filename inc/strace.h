#ifndef STRACE_H
#define STRACE_H

#include "arch.h"
#include "syscall.h"

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/user.h>
#include <unistd.h>

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

#define CHECK_SYSCALL(call)                           \
	do {                                              \
		if ((call) == -1) {                           \
			eprintf(#call ": %s\n", strerror(errno)); \
			kill(0, SIGKILL);                         \
		}                                             \
	} while (0)

#define ONCE(call)           \
	do {                     \
		static int flag = 1; \
                             \
		if (flag) {          \
			(call);          \
			flag = 0;        \
		}                    \
	} while (0)

int trace(pid_t pid_t);

void on_syscall_start(t_syscall_info *info, const u_regs *regs);
void on_syscall_end(t_syscall_info *info, const u_regs *regs);

const char *strerrorname(int error);
const char *strerrordesc(int error);
const char *syscall_name(int number);

const char *which(const char *filename);

#endif
