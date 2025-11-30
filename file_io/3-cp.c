#include "main.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/**
* main - Copies content of a file to another file
* @ac: Argument count
* @av: Argument vector
*
* Return: 0 on success, error code on failure
*/
int main(int ac, char *av[])
{
int fd_from, fd_to;
ssize_t r, w;
char buf[BUFFER_SIZE];
mode_t perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

if (ac != 3)
dprintf(2, "Usage: cp file_from file_to\n"), exit(97);

fd_from = open(av[1], O_RDONLY);
if (fd_from == -1)
dprintf(2, "Error: Can't read from file %s\n", av[1]), exit(98);

fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, perm);
if (fd_to == -1)
dprintf(2, "Error: Can't write to %s\n", av[2]), close(fd_from), exit(99);

while ((r = read(fd_from, buf, BUFFER_SIZE)) > 0)
{
w = write(fd_to, buf, r);
if (w != r)
dprintf(2, "Error: Can't write to %s\n", av[2]), close(fd_from), close(fd_to), exit(99);
}

if (r == -1)
dprintf(2, "Error: Can't read from file %s\n", av[1]), close(fd_from), close(fd_to), exit(98);

if (close(fd_from) == -1)
dprintf(2, "Error: Can't close fd %d\n", fd_from), close(fd_to), exit(100);

if (close(fd_to) == -1)
dprintf(2, "Error: Can't close fd %d\n", fd_to), exit(100);

return (0);
}
