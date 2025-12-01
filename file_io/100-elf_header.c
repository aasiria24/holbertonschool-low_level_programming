#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
* exit_error - Prints a custom error message to stderr and exits with status 98.
* @msg: The custom error message to print.
*/
void exit_error(const char *msg)
{
dprintf(STDERR_FILENO, "Error: %s\n", msg);
exit(98);
}

/**
* check_elf - Checks if the file is a valid ELF file.
* @e_ident: A pointer to the ELF identification bytes.
*/
void check_elf(unsigned char *e_ident)
{
/* The first four bytes of the magic number must be 0x7f, 'E', 'L', 'F' */
if (e_ident[EI_MAG0] != ELFMAG0 ||
e_ident[EI_MAG1] != ELFMAG1 ||
e_ident[EI_MAG2] != ELFMAG2 ||
e_ident[EI_MAG3] != ELFMAG3)
{
exit_error("File is not a valid ELF file.");
}
}

/**
* print_magic - Prints the Magic numbers (e_ident[EI_MAG0] through e_ident[EI_NIDENT - 1]).
* @e_ident: A pointer to the ELF identification bytes.
*/
void print_magic(unsigned char *e_ident)
{
int i;

printf("  Magic:   ");
for (i = 0; i < EI_NIDENT; i++)
{
printf("%02x", e_ident[i]);
if (i < EI_NIDENT - 1)
printf(" ");
}
printf("\n");
}

/**
* print_class - Prints the architecture class of the ELF file.
* @e_ident: A pointer to the ELF identification bytes.
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
}
}

/**
* print_data - Prints the data encoding scheme of the ELF file.
* @e_ident: A pointer to the ELF identification bytes.
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
}
}

/**
* print_version - Prints the version of the ELF file.
* @e_ident: A pointer to the ELF identification bytes.
*/
void print_version(unsigned char *e_ident)
{
printf("  Version:                           %d", e_ident[EI_VERSION]);

switch (e_ident[EI_VERSION])
{
case EV_CURRENT:
printf(" (current)\n");
break;
default:
printf("\n");
break;
}
}

/**
* print_osabi - Prints the OS/ABI field of the ELF header.
* @e_ident: A pointer to the ELF identification bytes.
*/
void print_osabi(unsigned char *e_ident)
{
printf("  OS/ABI:                            ");

switch (e_ident[EI_OSABI])
{
case ELFOSABI_NONE:
printf("UNIX - System V\n");
break;
case ELFOSABI_HPUX:
printf("UNIX - HP-UX\n");
break;
case ELFOSABI_NETBSD:
printf("UNIX - NetBSD\n");
break;
case ELFOSABI_LINUX:
printf("UNIX - Linux\n");
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
printf("Standalone App\n");
break;
default:
printf("<unknown: %x>\n", e_ident[EI_OSABI]);
}
}

/**
* print_abi - Prints the ABI Version field of the ELF header.
* @e_ident: A pointer to the ELF identification bytes.
*/
void print_abi(unsigned char *e_ident)
{
printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

/**
* print_type - Prints the file type from the ELF header.
* @e_type: The file type (e_type).
* @e_ident: A pointer to the ELF identification bytes.
*/
void print_type(unsigned int e_type, unsigned char *e_ident)
{
/* Adjust e_type for big endian architecture if necessary,
* though readelf 2.26.1 output for big endian seems to show the
* type correctly without explicit swapping for standard types.
* We rely on the system handling the structure reading correctly
* IF we were reading the full structure. Since we are reading byte by byte,
* we stick to the basic types for simplicity based on the example output.
*/
if (e_ident[EI_DATA] == ELFDATA2MSB)
e_type >>= 8;

printf("  Type:                              ");

switch (e_type)
{
case ET_NONE:
printf("NONE (No file type)\n");
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
}
}

/**
* print_entry - Prints the entry point address.
* @e_entry: The address of the entry point (e_entry).
* @e_ident: A pointer to the ELF identification bytes.
*/
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
printf("  Entry point address:               %#lx\n", e_entry);
}

/**
* print_header_info - Displays the required information from the ELF header.
* @header: A pointer to the 64-bit ELF header structure (which covers both 32/64-bit formats).
*/
void print_header_info(const void *header)
{
/* The first 16 bytes are the e_ident array, common to both 32/64 bit */
const unsigned char *e_ident = (const unsigned char *)header;

printf("ELF Header:\n");
print_magic((unsigned char *)e_ident);
print_class((unsigned char *)e_ident);
print_data((unsigned char *)e_ident);
print_version((unsigned char *)e_ident);
print_osabi((unsigned char *)e_ident);
print_abi((unsigned char *)e_ident);

/* Depending on class, cast to the appropriate ELF structure to access
* the e_type and e_entry fields correctly, which are located after e_ident.
* Since the task constraints prevent reading the file twice, we must read
* the maximum possible header size (for ELF64) in the first read call.
* The header buffer is large enough for Elf64_Ehdr, but we access the fields
* based on the EI_CLASS byte.
*/
if (e_ident[EI_CLASS] == ELFCLASS64)
{
const Elf64_Ehdr *h64 = (const Elf64_Ehdr *)header;
print_type(h64->e_type, (unsigned char *)e_ident);
print_entry(h64->e_entry, (unsigned char *)e_ident);
}
else if (e_ident[EI_CLASS] == ELFCLASS32)
{
const Elf32_Ehdr *h32 = (const Elf32_Ehdr *)header;
print_type(h32->e_type, (unsigned char *)e_ident);
print_entry(h32->e_entry, (unsigned char *)e_ident);
}
else
{
/* Handle unknown class gracefully, though check_elf should handle invalid. */
exit_error("Invalid ELF Class for parsing.");
}
}

/**
* main - Displays the information contained in the ELF header of a file.
* @ac: The number of arguments supplied to the program.
* @av: An array of pointers to the arguments.
*
* Return: 0 on success.
*
* Constraints applied:
* - lseek allowed once (used to rewind after reading magic number if needed, but not used here).
* - read allowed maximum of 2 times at runtime (used 1 time to read the whole header).
* - exit with status 98 and display comprehensive error message on error.
*/
int main(int ac, char *av[])
{
int fd;
/* Elf64_Ehdr is 64 bytes, Elf32_Ehdr is 52 bytes. We read the larger size (64 bytes)
* in a single read call to satisfy the constraint (read max 2 times).
*/
Elf64_Ehdr header;
ssize_t r;

if (ac != 2)
{
dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
exit(98);
}

fd = open(av[1], O_RDONLY);
if (fd == -1)
{
dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
exit(98);
}

/* Read the entire header in one go (64 bytes for Elf64_Ehdr) */
r = read(fd, &header, sizeof(Elf64_Ehdr));
if (r == -1)
{
close(fd);
exit_error("Failed to read ELF header.");
}
/* Check if the file is too small to contain a header (at least the identification bytes) */
if (r < (ssize_t)EI_NIDENT)
{
close(fd);
exit_error("File is too small to be a valid ELF file.");
}

/* 1. Check for ELF magic numbers */
check_elf(header.e_ident);

/* 2. Print the required information */
print_header_info(&header);

if (close(fd) == -1)
{
/* File descriptor closure error (highly unlikely but required for robust code) */
exit_error("Failed to close file descriptor.");
}

return (0);
}
