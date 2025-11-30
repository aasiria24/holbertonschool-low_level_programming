#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
* _strlen - Calculates the length of a string
* @str: The string to measure
*
* Return: The length of the string
*/
size_t _strlen(char *str)
{
size_t len = 0;

while (str && str[len])
len++;

return (len);
}

/**
* create_file - Creates a file with specified content
* @filename: Name of the file to create
* @text_content: NULL terminated string to write to the file
*
* Return: 1 on success, -1 on failure
*/
int create_file(const char *filename, char *text_content)
{
int fd;
ssize_t bytes_written;
size_t len = 0;

if (filename == NULL)
return (-1);

/* Open file with required permissions: rw------- (600) */
fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
if (fd == -1)
return (-1);

/* If text_content is not NULL, write it to the file */
if (text_content != NULL)
{
len = _strlen(text_content);
bytes_written = write(fd, text_content, len);
if (bytes_written == -1 || (size_t)bytes_written != len)
{
close(fd);
return (-1);
}
}

close(fd);
return (1);
}
