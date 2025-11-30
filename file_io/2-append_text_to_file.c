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
* append_text_to_file - Appends text at the end of a file
* @filename: Name of the file
* @text_content: NULL terminated string to add at the end of the file
*
* Return: 1 on success, -1 on failure
*/
int append_text_to_file(const char *filename, char *text_content)
{
int fd;
ssize_t bytes_written;
size_t len = 0;

if (filename == NULL)
return (-1);
/* Open file for appending (don't create if it doesn't exist) */
fd = open(filename, O_WRONLY | O_APPEND);
if (fd == -1)
return (-1);

/* If text_content is not NULL, append it to the file */
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
