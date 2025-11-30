#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/**
* main - Copies the content of a file to another file
* @ac: Argument count
* @av: Argument vector
*
* Return: 0 on success, or exit with appropriate error code
*/
int main(int ac, char *av[])
{
int fd_from, fd_to;
ssize_t bytes_read, bytes_written;
char buffer[BUFFER_SIZE];
mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

/* Check argument count */
if (ac != 3)
{
dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
exit(97);
}

/* Open source file for reading */
fd_from = open(av[1], O_RDONLY);
if (fd_from == -1)
{
dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
exit(98);
}

/* Open destination file for writing - create if doesn't exist, truncate if exists */
fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, permissions);
if (fd_to == -1)
{
dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
close(fd_from);
exit(99);
}

/* Copy content in chunks of BUFFER_SIZE */
while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
{
bytes_written = write(fd_to, buffer, bytes_read);
if (bytes_written == -1 || bytes_written != bytes_read)
{
dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
close(fd_from);
close(fd_to);
exit(99);
}
}

/* Check if read failed */
if (bytes_read == -1)
{
dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
close(fd_from);
close(fd_to);
exit(98);
}

/* Close file descriptors and check for errors */
if (close(fd_from) == -1)
{
dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
close(fd_to);
exit(100);
}

if (close(fd_to) == -1)
{
dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
exit(100);
}

return (0);
}
