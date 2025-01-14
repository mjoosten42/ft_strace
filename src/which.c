#include "strace.h"

#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

const char *which(const char *filename) {
	if (strchr(filename, '/')) {
		return filename;
	}

	size_t		cap		= PATH_MAX;
	const char *paths	= getenv("PATH");
	char		 *path	= calloc(cap, sizeof(char));
	int			filelen = strlen(filename);
	struct stat buf		= { 0 };

	if (!path) {
		return NULL;
	}

	char *colon = strchr(paths, ':');

	while (colon) {
		size_t dirlen = colon - paths;
		size_t len	  = dirlen + 1 + filelen;

		if (len + 1 > cap) {
			cap *= 2;
			path = realloc(path, cap);

			if (!path) {
				return NULL;
			}
		}

		strncpy(path, paths, dirlen);
		path[dirlen] = '/';
		strcpy(path + dirlen + 1, filename);

		if (!stat(path, &buf) && S_ISREG(buf.st_mode) && (buf.st_mode & 0111)) {
			return path;
		}

		paths = colon + 1;
		colon = strchr(paths, ':');
	}

	return NULL;
}
