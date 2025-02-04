#define _GNU_SOURCE

#include "strace.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>

int main(int argc, char **argv) {
	pid_t pid	  = 0;
	int	  i		  = 1;
	int	  summary = 0;

	if (argc >= 2 && !strncmp(argv[1], "-c", 2)) {
		summary = 1;
		i++;
	}

	if (argc < i + 1) {
		eprintf("%s: must have PROG [ARGS]\n", argv[0]);
		return EXIT_FAILURE;
	}

	const char *path = which(argv[i]);

	if (!path) {
		eprintf("%s: Can't stat '%s': %s\n", basename(argv[0]), argv[i], strerror(errno));
		return EXIT_FAILURE;
	}

	CHECK_SYSCALL(pid = fork());

	if (!pid) {
		CHECK_SYSCALL(raise(SIGSTOP));
		CHECK_SYSCALL(execv(path, argv + i));
	}

	// eprintf("parent: %d\n", getpid());
	// eprintf("child:  %d\n", pid);

	CHECK_SYSCALL(ptrace(PTRACE_SEIZE, pid, NULL, PTRACE_O_TRACESYSGOOD));

	return event_loop(pid, summary ? count : trace);
}
