#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* print_error - prints error message and exits
* @msg: error message to print
*/
void print_error(char *msg)
{
fprintf(stderr, "%s\n", msg);
exit(98);
}

/**
* print_magic - prints ELF magic bytes
* @e_ident: ELF identification array
*/
void print_magic(unsigned char *e_ident)
{
int i;

printf("  Magic:   ");
for (i = 0; i < EI_NIDENT; i++)
{
printf("%02x", e_ident[i]);
if (i == EI_NIDENT - 1)
printf("\n");
else
printf(" ");
}
}

/**
* print_class - prints ELF class
* @e_ident: ELF identification array
*/
void print_class(unsigned char *e_ident)
{
printf("  Class:                             ");
switch (e_ident[EI_CLASS])
{
case ELFCLASSNONE:
printf("none\n");
break;
case ELFCLASS32:
printf("ELF32\n");
break;
case ELFCLASS64:
printf("ELF64\n");
break;
default:
printf("<unknown: %x>\n", e_ident[EI_CLASS]);
break;
}
}

/**
* print_data - prints data encoding
* @e_ident: ELF identification array
*/
void print_data(unsigned char *e_ident)
{
printf("  Data:                              ");
switch (e_ident[EI_DATA])
{
case ELFDATANONE:
printf("none\n");
break;
case ELFDATA2LSB:
printf("2's complement, little endian\n");
break;
case ELFDATA2MSB:
printf("2's complement, big endian\n");
break;
default:
printf("<unknown: %x>\n", e_ident[EI_DATA]);
break;
}
}

/**
* print_version - prints ELF version
* @e_ident: ELF identification array
*/
void print_version(unsigned char *e_ident)
{
printf("  Version:                           ");

if (e_ident[EI_VERSION] == EV_NONE)
printf("0 (invalid)\n");
else if (e_ident[EI_VERSION] == EV_CURRENT)
printf("1 (current)\n");
else
printf("%d\n", e_ident[EI_VERSION]);
}

/**
* print_osabi - prints OS/ABI
* @e_ident: ELF identification array
*/
void print_osabi(unsigned char *e_ident)
{
printf("  OS/ABI:                            ");
switch (e_ident[EI_OSABI])
{
case ELFOSABI_SYSV:
printf("UNIX - System V\n");
break;
case ELFOSABI_HPUX:
printf("HP-UX\n");
break;
case ELFOSABI_NETBSD:
printf("UNIX - NetBSD\n");
break;
case ELFOSABI_LINUX:
printf("UNIX - GNU\n");
break;
case ELFOSABI_SOLARIS:
printf("UNIX - Solaris\n");
break;
case ELFOSABI_IRIX:
printf("UNIX - IRIX\n");
break;
case ELFOSABI_FREEBSD:
printf("UNIX - FreeBSD\n");
break;
case ELFOSABI_TRU64:
printf("UNIX - TRU64\n");
break;
case ELFOSABI_ARM:
printf("ARM\n");
break;
case ELFOSABI_STANDALONE:
printf("Stand-alone App\n");
break;
default:
printf("<unknown: %x>\n", e_ident[EI_OSABI]);
break;
}
}

/**
* print_abiversion - prints ABI version
* @e_ident: ELF identification array
*/
void print_abiversion(unsigned char *e_ident)
{
printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

/**
* print_type - prints ELF type
* @e_type: ELF type
* @e_ident: ELF identification array
*/
void print_type(uint16_t e_type, unsigned char *e_ident)
{
printf("  Type:                              ");

/* Handle endianness for e_type */
if (e_ident[EI_DATA] == ELFDATA2MSB)
{
e_type = ((e_type >> 8) & 0x00FF) | ((e_type << 8) & 0xFF00);
}

switch (e_type)
{
case ET_NONE:
printf("NONE (None)\n");
break;
case ET_REL:
printf("REL (Relocatable file)\n");
break;
case ET_EXEC:
printf("EXEC (Executable file)\n");
break;
case ET_DYN:
printf("DYN (Shared object file)\n");
break;
case ET_CORE:
printf("CORE (Core file)\n");
break;
default:
printf("<unknown: %x>\n", e_type);
break;
}
}

/**
* print_entry - prints entry point address
* @e_entry: entry point address
* @e_ident: ELF identification array
*/
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
printf("  Entry point address:               ");

/* Handle big endian addresses */
if (e_ident[EI_DATA] == ELFDATA2MSB)
{
e_entry = ((e_entry << 8) & 0xFF00FF00) |
((e_entry >> 8) & 0xFF00FF);
e_entry = (e_entry << 16) | (e_entry >> 16);
}

/* Print based on class */
if (e_ident[EI_CLASS] == ELFCLASS32)
printf("0x%x\n", (unsigned int)e_entry);
else
printf("0x%lx\n", e_entry);
}

/**
* read_elf_header - reads ELF header based on class
* @fd: file descriptor
* @e_ident: ELF identification array
* @e_type: pointer to store e_type
* @e_entry: pointer to store e_entry
*/
void read_elf_header(int fd, unsigned char *e_ident,
uint16_t *e_type, unsigned long int *e_entry)
{
ssize_t read_bytes;

/* Return to beginning and read full header based on class */
lseek(fd, 0, SEEK_SET);

if (e_ident[EI_CLASS] == ELFCLASS32)
{
Elf32_Ehdr header32;

read_bytes = read(fd, &header32, sizeof(header32));
if (read_bytes != sizeof(header32))
print_error("Error: Cannot read ELF header");

*e_type = header32.e_type;
*e_entry = header32.e_entry;
}
else if (e_ident[EI_CLASS] == ELFCLASS64)
{
Elf64_Ehdr header64;

read_bytes = read(fd, &header64, sizeof(header64));
if (read_bytes != sizeof(header64))
print_error("Error: Cannot read ELF header");

*e_type = header64.e_type;
*e_entry = header64.e_entry;
}
else
{
print_error("Error: Unknown ELF class");
}
}

/**
* validate_elf_file - validates if file is ELF
* @fd: file descriptor
* @e_ident: buffer to store ELF identification
*/
void validate_elf_file(int fd, unsigned char *e_ident)
{
ssize_t read_bytes;

/* Read ELF identification */
read_bytes = read(fd, e_ident, EI_NIDENT);
if (read_bytes != EI_NIDENT)
print_error("Error: Cannot read ELF identification");

/* Check ELF magic */
if (e_ident[EI_MAG0] != ELFMAG0 ||
e_ident[EI_MAG1] != ELFMAG1 ||
e_ident[EI_MAG2] != ELFMAG2 ||
e_ident[EI_MAG3] != ELFMAG3)
print_error("Error: Not an ELF file");
}

/**
* print_elf_header - prints all ELF header information
* @e_ident: ELF identification array
* @e_type: ELF type
* @e_entry: entry point address
*/
void print_elf_header(unsigned char *e_ident,
uint16_t e_type, unsigned long int e_entry)
{
printf("ELF Header:\n");
print_magic(e_ident);
print_class(e_ident);
print_data(e_ident);
print_version(e_ident);
print_osabi(e_ident);
print_abiversion(e_ident);
print_type(e_type, e_ident);
print_entry(e_entry, e_ident);
}

/**
* main - main function
* @argc: argument count
* @argv: argument array
* Return: 0 on success, 98 on error
*/
int main(int argc, char **argv)
{
int fd;
unsigned char e_ident[EI_NIDENT];
uint16_t e_type;
unsigned long int e_entry;

if (argc != 2)
print_error("Usage: elf_header elf_filename");

fd = open(argv[1], O_RDONLY);
if (fd == -1)
print_error("Error: Cannot open file");

validate_elf_file(fd, e_ident);
read_elf_header(fd, e_ident, &e_type, &e_entry);
print_elf_header(e_ident, e_type, e_entry);

if (close(fd) == -1)
print_error("Error: Cannot close file descriptor");

return (0);
}
