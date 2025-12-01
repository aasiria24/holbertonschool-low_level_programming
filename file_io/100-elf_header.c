#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/* Print error and exit */
void print_error(const char *msg)
{
dprintf(STDERR_FILENO, "Error: %s\n", msg);
exit(98);
}

/* Print OS/ABI name */
const char *get_osabi(unsigned char osabi)
{
switch (osabi)
{
case ELFOSABI_SYSV: return "UNIX - System V";
case ELFOSABI_HPUX: return "HP-UX";
case ELFOSABI_NETBSD: return "UNIX - NetBSD";
case ELFOSABI_LINUX: return "UNIX - Linux";
case ELFOSABI_SOLARIS: return "UNIX - Solaris";
case ELFOSABI_IRIX: return "UNIX - IRIX";
case ELFOSABI_FREEBSD: return "UNIX - FreeBSD";
case ELFOSABI_TRU64: return "UNIX - TRU64";
case ELFOSABI_ARM: return "ARM";
case ELFOSABI_STANDALONE: return "Standalone App";
default:
{
static char buf[32];
snprintf(buf, sizeof(buf), "<unknown: %x>", osabi);
return buf;
}
}
}

/* Print ELF type */
const char *get_type(uint16_t type)
{
switch (type)
{
case ET_NONE: return "NONE (None)";
case ET_REL:  return "REL (Relocatable file)";
case ET_EXEC: return "EXEC (Executable file)";
case ET_DYN:  return "DYN (Shared object file)";
case ET_CORE: return "CORE (Core file)";
default:
{
static char buf[32];
snprintf(buf, sizeof(buf), "<unknown: %x>", type);
return buf;
}
}
}

int main(int ac, char **av)
{
int fd;
ssize_t rd;
Elf64_Ehdr hdr;

if (ac != 2)
print_error("Usage: elf_header elf_filename");

fd = open(av[1], O_RDONLY);
if (fd == -1)
print_error("Can't read file");

rd = read(fd, &hdr, sizeof(hdr));
if (rd != sizeof(hdr))
print_error("Can't read ELF header");

/* Check ELF magic */
if (hdr.e_ident[EI_MAG0] != ELFMAG0 ||
hdr.e_ident[EI_MAG1] != ELFMAG1 ||
hdr.e_ident[EI_MAG2] != ELFMAG2 ||
hdr.e_ident[EI_MAG3] != ELFMAG3)
{
print_error("Not an ELF file");
}

/* Print header */
printf("ELF Header:\n");
printf("  Magic:   ");
for (int i = 0; i < EI_NIDENT; i++)
printf("%02x%c", hdr.e_ident[i], i == EI_NIDENT - 1 ? '\n' : ' ');

printf("  Class:                             %s\n",
(hdr.e_ident[EI_CLASS] == ELFCLASS32) ? "ELF32" :
(hdr.e_ident[EI_CLASS] == ELFCLASS64) ? "ELF64" : "Invalid class");

printf("  Data:                              %s\n",
(hdr.e_ident[EI_DATA] == ELFDATA2LSB) ? "2's complement, little endian" :
(hdr.e_ident[EI_DATA] == ELFDATA2MSB) ? "2's complement, big endian" :
"Invalid data encoding");

printf("  Version:                           %d (current)\n",
hdr.e_ident[EI_VERSION]);

printf("  OS/ABI:                            %s\n",
get_osabi(hdr.e_ident[EI_OSABI]));

printf("  ABI Version:                       %d\n",
hdr.e_ident[EI_ABIVERSION]);

printf("  Type:                              %s\n", get_type(hdr.e_type));

printf("  Entry point address:               %#lx\n",
(unsigned long)hdr.e_entry);

close(fd);
return (0);
}

