#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define EI_NIDENT 16

/**
* Elf64_Ehdr - Structure for ELF64 header
*/
typedef struct
{
unsigned char e_ident[EI_NIDENT];
unsigned short e_type;
unsigned short e_machine;
unsigned int e_version;
unsigned long e_entry;
unsigned long e_phoff;
unsigned long e_shoff;
unsigned int e_flags;
unsigned short e_ehsize;
unsigned short e_phentsize;
unsigned short e_phnum;
unsigned short e_shentsize;
unsigned short e_shnum;
unsigned short e_shstrndx;
} Elf64_Ehdr;

/**
* Elf32_Ehdr - Structure for ELF32 header
*/
typedef struct
{
unsigned char e_ident[EI_NIDENT];
unsigned short e_type;
unsigned short e_machine;
unsigned int e_version;
unsigned int e_entry;
unsigned int e_phoff;
unsigned int e_shoff;
unsigned int e_flags;
unsigned short e_ehsize;
unsigned short e_phentsize;
unsigned short e_phnum;
unsigned short e_shentsize;
unsigned short e_shnum;
unsigned short e_shstrndx;
} Elf32_Ehdr;

/**
* print_error - Prints error message and exits with code 98
* @msg: Error message
*/
void print_error(const char *msg)
{
dprintf(STDERR_FILENO, "Error: %s\n", msg);
exit(98);
}

/**
* print_magic - Prints magic bytes
* @e_ident: ELF identification bytes
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
* @class: Class byte
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
* print_osabi - Prints OS/ABI
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
printf("NetBSD\n");
break;
case 3:
printf("Linux\n");
break;
case 6:
printf("Solaris\n");
break;
case 7:
printf("AIX\n");
break;
case 8:
printf("IRIX\n");
break;
case 9:
printf("FreeBSD\n");
break;
case 10:
printf("Tru64\n");
break;
case 11:
printf("Novell Modesto\n");
break;
case 12:
printf("OpenBSD\n");
break;
case 13:
printf("OpenVMS\n");
break;
case 14:
printf("NonStop Kernel\n");
break;
case 15:
printf("AROS\n");
break;
case 16:
printf("Fenix OS\n");
break;
case 17:
printf("CloudABI\n");
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
* @class: ELF class for byte order
*/
void print_type(unsigned int type, unsigned char class)
{
printf("  Type:                              ");

if (class == 1) /* ELF32 */
type = ((type >> 8) & 0xff) | ((type << 8) & 0xff00);

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
* print_entry - Prints entry point address
* @entry: Entry point
* @class: ELF class
*/
void print_entry(unsigned long entry, unsigned char class)
{
printf("  Entry point address:               ");

if (class == 1) /* ELF32 */
printf("0x%x\n", (unsigned int)entry);
else /* ELF64 */
printf("0x%lx\n", entry);
}

/**
* main - Displays ELF header
* @argc: Argument count
* @argv: Argument vector
* Return: 0 on success, 98 on error
*/
int main(int argc, char *argv[])
{
int fd;
unsigned char e_ident[EI_NIDENT];
Elf32_Ehdr header32;
Elf64_Ehdr header64;
ssize_t bytes;

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

/* Print ELF header */
printf("ELF Header:\n");
print_magic(e_ident);
print_class(e_ident[4]);
print_data(e_ident[5]);
print_version(e_ident[6]);
print_osabi(e_ident[7]);
print_abi_version(e_ident[8]);

/* Read the rest of the header based on class */
lseek(fd, 0, SEEK_SET);
if (e_ident[4] == 2) /* ELF64 */
{
bytes = read(fd, &header64, sizeof(header64));
if (bytes < (ssize_t)sizeof(header64))
print_error("Cannot read ELF64 header");
print_type(header64.e_type, e_ident[4]);
print_entry(header64.e_entry, e_ident[4]);
}
else /* ELF32 */
{
bytes = read(fd, &header32, sizeof(header32));
if (bytes < (ssize_t)sizeof(header32))
print_error("Cannot read ELF32 header");
print_type(header32.e_type, e_ident[4]);
print_entry(header32.e_entry, e_ident[4]);
}

close(fd);
return (0);
}
