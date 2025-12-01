#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
* print_error - Prints error message to stderr and exits
* @msg: Error message to print
*/
void print_error(const char *msg)
{
dprintf(STDERR_FILENO, "%s\n", msg);
exit(98);
}

/**
* print_magic - Prints the magic bytes
* @e_ident: Pointer to ELF identification bytes
*/
void print_magic(unsigned char *e_ident)
{
int i;

printf("  Magic:   ");
for (i = 0; i < 16; i++)
printf("%02x%c", e_ident[i], i == 15 ? '\n' : ' ');
}

/**
* get_class - Returns the class string
* @class: ELF class byte
* Return: Class string
*/
const char *get_class(unsigned char class)
{
switch (class)
{
case 0: return "none";
case 1: return "ELF32";
case 2: return "ELF64";
default: return "<unknown>";
}
}

/**
* get_data - Returns the data encoding string
* @data: ELF data encoding byte
* Return: Data encoding string
*/
const char *get_data(unsigned char data)
{
switch (data)
{
case 0: return "none";
case 1: return "2's complement, little endian";
case 2: return "2's complement, big endian";
default: return "<unknown>";
}
}

/**
* get_osabi - Returns the OS/ABI string
* @osabi: OS/ABI byte
* Return: OS/ABI string
*/
const char *get_osabi(unsigned char osabi)
{
switch (osabi)
{
case 0: return "UNIX - System V";
case 1: return "HP-UX";
case 2: return "NetBSD";
case 3: return "Linux";
case 4: return "GNU Hurd";
case 5: return "Solaris";
case 6: return "AIX";
case 7: return "IRIX";
case 8: return "FreeBSD";
case 9: return "Tru64";
case 10: return "Novell Modesto";
case 11: return "OpenBSD";
case 12: return "OpenVMS";
case 13: return "NonStop Kernel";
case 14: return "AROS";
case 15: return "Fenix OS";
case 16: return "CloudABI";
case 97: return "ARM";
default: 
{
static char buf[30];
sprintf(buf, "<unknown: %d>", osabi);
return buf;
}
}
}

/**
* get_type - Returns the type string
* @type: ELF type
* @class: ELF class for proper byte order
* Return: Type string
*/
const char *get_type(unsigned int type, unsigned char class)
{
if (class == 1) /* ELF32 */
type >>= 8;

switch (type)
{
case 0: return "NONE (No file type)";
case 1: return "REL (Relocatable file)";
case 2: return "EXEC (Executable file)";
case 3: return "DYN (Shared object file)";
case 4: return "CORE (Core file)";
default:
{
static char buf[30];
sprintf(buf, "<unknown: %d>", type);
return buf;
}
}
}

/**
* get_entry - Returns the entry point address
* @entry: Entry point bytes
* @class: ELF class
* @data: Data encoding for byte order
* Return: Entry point as unsigned long
*/
unsigned long get_entry(unsigned char *entry, unsigned char class, unsigned char data)
{
unsigned long addr = 0;
int i;

if (class == 1) /* ELF32 */
{
if (data == 1) /* Little endian */
{
for (i = 3; i >= 0; i--)
addr = (addr << 8) | entry[i];
}
else /* Big endian */
{
for (i = 0; i < 4; i++)
addr = (addr << 8) | entry[i];
}
}
else /* ELF64 */
{
if (data == 1) /* Little endian */
{
for (i = 7; i >= 0; i--)
addr = (addr << 8) | entry[i];
}
else /* Big endian */
{
for (i = 0; i < 8; i++)
addr = (addr << 8) | entry[i];
}
}
return addr;
}

/**
* main - Displays ELF header information
* @argc: Argument count
* @argv: Argument vector
* Return: 0 on success, 98 on error
*/
int main(int argc, char *argv[])
{
int fd;
unsigned char header[64];
ssize_t bytes;

if (argc != 2)
print_error("Usage: elf_header elf_filename");

fd = open(argv[1], O_RDONLY);
if (fd == -1)
print_error("Error: Cannot open file");

/* Read ELF header (first 64 bytes) */
bytes = read(fd, header, 64);
if (bytes < 64)
print_error("Error: Cannot read ELF header");

/* Check ELF magic */
if (header[0] != 0x7f || header[1] != 'E' || 
header[2] != 'L' || header[3] != 'F')
print_error("Error: Not an ELF file");

/* Print ELF header information */
printf("ELF Header:\n");
print_magic(header);
printf("  Class:                             %s\n", get_class(header[4]));
printf("  Data:                              %s\n", get_data(header[5]));
printf("  Version:                           %d (current)\n", header[6]);
printf("  OS/ABI:                            %s\n", get_osabi(header[7]));
printf("  ABI Version:                       %d\n", header[8]);
printf("  Type:                              %s\n", 
get_type(*(unsigned int *)(header + 16), header[4]));
printf("  Entry point address:               0x%lx\n",
get_entry(header + 24, header[4], header[5]));

close(fd);
return (0);
}
