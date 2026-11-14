#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * print_magic_class_data - prints magic numbers, class and data encoding
 * @e: pointer to array of ELF magic numbers
 */
void print_magic_class_data(unsigned char *e)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x%s", e[i], i == EI_NIDENT - 1 ? "\n" : " ");

	printf("  Class:                             ");
	if (e[EI_CLASS] == ELFCLASS32)
		printf("ELF32\n");
	else if (e[EI_CLASS] == ELFCLASS64)
		printf("ELF64\n");
	else if (e[EI_CLASS] == ELFCLASSNONE)
		printf("none\n");
	else
		printf("<unknown: %x>\n", e[EI_CLASS]);

	printf("  Data:                              ");
	if (e[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (e[EI_DATA] == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else if (e[EI_DATA] == ELFDATANONE)
		printf("none\n");
	else
		printf("<unknown: %x>\n", e[EI_DATA]);
}

/**
 * print_osabi - prints the version, OS/ABI and ABI version
 * @e: pointer to array of ELF magic numbers
 */
void print_osabi(unsigned char *e)
{
	int i;
	char *names[] = {
		"UNIX - System V", "UNIX - HP-UX", "UNIX - NetBSD",
		"UNIX - Linux", "UNIX - Solaris", "UNIX - AIX",
		"UNIX - IRIX", "UNIX - FreeBSD", "UNIX - TRU64",
		"Novell - Modesto", "UNIX - OpenBSD", "ARM",
		"Standalone App"
	};
	unsigned char ids[] = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 97, 255};

	printf("  Version:                           %d%s", e[EI_VERSION],
	       e[EI_VERSION] == EV_CURRENT ? " (current)\n" : "\n");
	printf("  OS/ABI:                            ");
	for (i = 0; i < 13; i++)
	{
		if (ids[i] == e[EI_OSABI])
		{
			printf("%s\n", names[i]);
			break;
		}
	}
	if (i == 13)
		printf("<unknown: %x>\n", e[EI_OSABI]);
	printf("  ABI Version:                       %d\n", e[EI_ABIVERSION]);
}

/**
 * print_type - prints ELF type
 * @type: ELF type
 * @e_ident: pointer to array of ELF magic numbers
 */
void print_type(unsigned int type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		type = ((type & 0xFF00) >> 8) | ((type & 0x00FF) << 8);

	printf("  Type:                              ");
	if (type == ET_NONE)
		printf("NONE (None)\n");
	else if (type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (type == ET_CORE)
		printf("CORE (Core file)\n");
	else
		printf("<unknown: %x>\n", type);
}

/**
 * print_entry - prints entry point address
 * @h: pointer to Elf64_Ehdr
 */
void print_entry(Elf64_Ehdr *h)
{
	unsigned long int entry = h->e_entry;

	printf("  Entry point address:               ");
	if (h->e_ident[EI_CLASS] == ELFCLASS32)
	{
		Elf32_Ehdr *h32 = (Elf32_Ehdr *)h;
		unsigned int e32 = h32->e_entry;

		if (h->e_ident[EI_DATA] == ELFDATA2MSB)
			e32 = ((e32 & 0xFF000000) >> 24) |
			      ((e32 & 0x00FF0000) >> 8)  |
			      ((e32 & 0x0000FF00) << 8)  |
			      ((e32 & 0x000000FF) << 24);
		printf("0x%x\n", e32);
	}
	else
	{
		if (h->e_ident[EI_DATA] == ELFDATA2MSB)
		{
			unsigned char *p = (unsigned char *)&entry;
			unsigned char t;
			int i;

			for (i = 0; i < 4; i++)
			{
				t = p[i];
				p[i] = p[7 - i];
				p[7 - i] = t;
			}
		}
		printf("0x%lx\n", entry);
	}
}

/**
 * main - displays the information contained in the ELF header at the start
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	Elf64_Ehdr h;
	int fd;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
		exit(98);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	if (read(fd, h.e_ident, 16) != 16 || h.e_ident[0] != 0x7f ||
	    h.e_ident[1] != 'E' || h.e_ident[2] != 'L' || h.e_ident[3] != 'F')
	{
		close(fd);
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		exit(98);
	}
	if (lseek(fd, 0, SEEK_SET) == -1 ||
	    read(fd, &h, sizeof(h)) < (ssize_t)sizeof(Elf32_Ehdr))
	{
		close(fd);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	printf("ELF Header:\n");
	print_magic_class_data(h.e_ident);
	print_osabi(h.e_ident);
	print_type(h.e_type, h.e_ident);
	print_entry(&h);
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(98);
	}
	return (0);
}
