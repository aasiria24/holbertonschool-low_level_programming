#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
* read_textfile - Reads a text file and prints it to stdout
* @filename: name of the file
* @letters: number of letters to read
*
* Return: number of letters printed, or 0 on failure
*/
ssize_t read_textfile(const char *filename, size_t letters)
{
int fd;
ssize_t r, w;
char *buf;

if (!filename)
return (0);

buf = malloc(letters);
if (!buf)
return (0);

fd = open(filename, O_RDONLY);
if (fd == -1)
{
free(buf);
return (0);
}

r = read(fd, buf, letters);
if (r == -1)
{
free(buf);
close(fd);
return (0);
}

w = write(STDOUT_FILENO, buf, r);

free(buf);
close(fd);

if (w == -1 || w != r)
return (0);

return (w);
}

