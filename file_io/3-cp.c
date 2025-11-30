#include "main.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
* main - Copies the content of a file to another file
* @ac: argument count
* @av: argument vector
*
* Return: 0 on success, exits with codes 97, 98, 99, 100 on errors
*/
int main(int ac, char **av)
{
int fd_from, fd_to;
ssize_t r, w;
char buffer[1024];

if (ac != 3)
{
dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
exit(97);
}

fd_from = open(av[1], O_RDONLY);
if (fd_from == -1)
{
dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
exit(98);
}

fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
if (fd_to == -1)
{
dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
close(fd_from);
exit(99);
}

while ((r = read(fd_from, buffer, 1024)) > 0)
{
w = write(fd_to, buffer, r);
if (w == -1 || w != r)
{
dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
close(fd_from);
close(fd_to);
exit(99);
}
}

if (r == -1)
{
dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
close(fd_from);
close(fd_to);
exit(98);
}

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

