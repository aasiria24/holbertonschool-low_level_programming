#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <stddef.h>
/**
 * read_textfile - Reads a text file and prints it to stdout
 * @filename: pointer to file name
 * @letters: number of letters to read and print
 *
 * Return: number of letters printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters);
int _putchar(char c);
int create_file(const char *filename, char *text_content);
int append_text_to_file(const char *filename, char *text_content);

#endif /* MAIN_H */
