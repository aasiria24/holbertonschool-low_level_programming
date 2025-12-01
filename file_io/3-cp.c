#include "main.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

/**
* main - Copies content of a file to another file
* @ac: Argument count
* @av: Argument vector
*
* Return: 0 on success, error code on failure
*/
int main(int ac, char *av[])
{
int f1, f2;
ssize_t n;
char buf[BUF_SIZE];

if (ac != 3)
dprintf(2, "Usage: cp file_from file_to\n"), exit(97);

f1 = open(av[1], O_RDONLY);
if (f1 == -1)
dprintf(2, "Error: Can't read from file %s\n", av[1]), exit(98);

f2 = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
if (f2 == -1)
dprintf(2, "Error: Can't write to %s\n", av[2]), close(f1), exit(99);

while ((n = read(f1, buf, BUF_SIZE)) > 0)
if (write(f2, buf, n) != n)
{
dprintf(2, "Error: Can't write to %s\n", av[2]);
close(f1), close(f2), exit(99);
}

if (n == -1)
dprintf(2, "Error: Can't read from file %s\n", av[1]),
close(f1), close(f2), exit(98);

if (close(f1) == -1)
dprintf(2, "Error: Can't close fd %d\n", f1),
close(f2), exit(100);

if (close(f2) == -1)
dprintf(2, "Error: Can't close fd %d\n", f2), exit(100);

return (0);
}
