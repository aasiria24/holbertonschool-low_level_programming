#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define EI_NIDENT 16

/**
* print_error - Prints error message to stderr and exits with code 98
* @msg: Error message to print
*/
void print_error(const char *msg)
{
dprintf(STDERR_FILENO, "Error: %s\n", msg);
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
* print_class - Prints ELF class
* @class: ELF class byte
*/
void print_class(unsigned char class)
{
printf("  Class:                             ");
switch (class)
{
case 0:
printf("none\n");
break;
case 1:
printf("ELF32\n");
break;
case 2:
printf("ELF64\n");
break;
default:
printf("<unknown: %d>\n", class);
}
}

/**
* print_data - Prints data encoding
* @data: Data encoding byte
*/
void print_data(unsigned char data)
{
printf("  Data:                              ");
switch (data)
{
case 0:
printf("none\n");
break;
case 1:
printf("2's complement, little endian\n");
break;
case 2:
printf("2's complement, big endian\n");
break;
default:
printf("<unknown: %d>\n", data);
}
}

/**
* print_version - Prints ELF version
* @version: Version byte
*/
void print_version(unsigned char version)
{
printf("  Version:                           %d", version);
if (version == 1)
printf(" (current)\n");
else
printf("\n");
}

/**
* print_osabi - Prints OS/ABI information
* @osabi: OS/ABI byte
*/
void print_osabi(unsigned char osabi)
{
printf("  OS/ABI:                            ");
switch (osabi)
{
case 0:
printf("UNIX - System V\n");
break;
case 1:
printf("HP-UX\n");
break;
case 2:
printf("UNIX - NetBSD\n");
break;
case 3:
printf("Linux\n");
break;
case 4:
printf("GNU Hurd\n");
break;
case 5:
printf("UNIX - Solaris\n");
break;
case 6:
printf("AIX\n");
break;
case 7:
printf("IRIX\n");
break;
case 8:
printf("FreeBSD\n");
break;
case 9:
printf("Tru64\n");
break;
case 10:
printf("Novell Modesto\n");
break;
case 11:
printf("OpenBSD\n");
break;
case 12:
printf("OpenVMS\n");
break;
case 13:
printf("NonStop Kernel\n");
break;
case 14:
printf("AROS\n");
break;
case 15:
printf("Fenix OS\n");
break;
case 16:
printf("CloudABI\n");
break;
case 97:
printf("ARM\n");
break;
default:
printf("<unknown: %d>\n", osabi);
}
}

/**
* print_abi_version - Prints ABI version
* @abi_version: ABI version byte
*/
void print_abi_version(unsigned char abi_version)
{
printf("  ABI Version:                       %d\n", abi_version);
}

/**
* print_type - Prints ELF type
* @type: Type value
* @data: Data encoding for byte order
*/
void print_type(unsigned int type, unsigned char data)
{
/* Adjust for byte order */
if (data == 1) /* Little endian */
{
if (type & 0xFF00)
type = ((type & 0xFF) << 8) | ((type >> 8) & 0xFF);
}

printf("  Type:                              ");
switch (type)
{
case 0:
printf("NONE (No file type)\n");
break;
case 1:
printf("REL (Relocatable file)\n");
break;
case 2:
printf("EXEC (Executable file)\n");
break;
case 3:
printf("DYN (Shared object file)\n");
break;
case 4:
printf("CORE (Core file)\n");
break;
default:
printf("<unknown: %d>\n", type);
}
}

/**
* get_uint16 - Reads a 16-bit value with proper byte order
* @ptr: Pointer to bytes
* @little_endian: 1 for little endian, 0 for big endian
* Return: 16-bit value
*/
unsigned short get_uint16(unsigned char *ptr, int little_endian)
{
if (little_endian)
return ptr[0] | (ptr[1] << 8);
else
return (ptr[0] << 8) | ptr[1];
}

/**
* get_uint32 - Reads a 32-bit value with proper byte order
* @ptr: Pointer to bytes
* @little_endian: 1 for little endian, 0 for big endian
* Return: 32-bit value
*/
unsigned int get_uint32(unsigned char *ptr, int little_endian)
{
if (little_endian)
return ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
else
return (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
}

/**
* get_uint64 - Reads a 64-bit value with proper byte order
* @ptr: Pointer to bytes
* @little_endian: 1 for little endian, 0 for big endian
* Return: 64-bit value
*/
unsigned long get_uint64(unsigned char *ptr, int little_endian)
{
unsigned long val = 0;

if (little_endian)
{
val = ptr[0];
val |= (unsigned long)ptr[1] << 8;
val |= (unsigned long)ptr[2] << 16;
val |= (unsigned long)ptr[3] << 24;
val |= (unsigned long)ptr[4] << 32;
val |= (unsigned long)ptr[5] << 40;
val |= (unsigned long)ptr[6] << 48;
val |= (unsigned long)ptr[7] << 56;
}
else
{
val = (unsigned long)ptr[0] << 56;
val |= (unsigned long)ptr[1] << 48;
val |= (unsigned long)ptr[2] << 40;
val |= (unsigned long)ptr[3] << 32;
val |= (unsigned long)ptr[4] << 24;
val |= (unsigned long)ptr[5] << 16;
val |= (unsigned long)ptr[6] << 8;
val |= ptr[7];
}

return val;
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
unsigned char e_ident[EI_NIDENT];
unsigned char header[64]; /* Enough for ELF32/ELF64 basic header */
ssize_t bytes;
unsigned char class, data;
int little_endian;
unsigned short type;
unsigned long entry;

if (argc != 2)
print_error("Usage: elf_header elf_filename");

fd = open(argv[1], O_RDONLY);
if (fd == -1)
print_error("Cannot open file");

/* Read ELF identification */
bytes = read(fd, e_ident, EI_NIDENT);
if (bytes != EI_NIDENT)
print_error("Cannot read ELF header");

/* Verify ELF magic */
if (e_ident[0] != 0x7f || e_ident[1] != 'E' || 
e_ident[2] != 'L' || e_ident[3] != 'F')
print_error("Not an ELF file");

class = e_ident[4];
data = e_ident[5];
little_endian = (data == 1);

/* Read rest of header (position 0, read 64 bytes) */
lseek(fd, 0, SEEK_SET);
bytes = read(fd, header, 64);
if (bytes < 64)
print_error("Cannot read full ELF header");

/* Extract type (offset 16, 2 bytes) */
type = get_uint16(header + 16, little_endian);

/* Extract entry point based on class */
if (class == 1) /* ELF32 */
entry = get_uint32(header + 24, little_endian);
else if (class == 2) /* ELF64 */
entry = get_uint64(header + 24, little_endian);
else
entry = 0;

/* Print ELF header */
printf("ELF Header:\n");
print_magic(e_ident);
print_class(class);
print_data(data);
print_version(e_ident[6]);
print_osabi(e_ident[7]);
print_abi_version(e_ident[8]);
print_type(type, data);
printf("  Entry point address:               0x%lx\n", entry);

close(fd);
return (0);
}
