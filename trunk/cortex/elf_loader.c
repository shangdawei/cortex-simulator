#include "elf_loader.h"

bool load_elf(char *p)
{
	int ret;
	int a=100;
	int sizeof_prog_headers;
	int memory_entry;
	int i;
//	int buffer_num;
	int elf_prot;
	int buffer_size;
	int buffer_flag;
//	char* segment;
	char* p_memory;

	Elf32_Ehdr file_header;// = (Elf32_Ehdr)malloc(sizeof(Elf32_Ehdr))
	Elf32_Phdr *prog_headers;
	Elf32_Phdr *elf_phdr;
	FILE *input;

	input = fopen(p,"rb");
	if(input==NULL)
	{
		printf("\nerror on open elf file!");
		getchar();
		exit(1);
	}
	ret = (int)fread( (char *)(&file_header), sizeof(Elf32_Ehdr), 1, input );
	if (!(	(file_header.e_ident[0] == 0x7F) &&
	(file_header.e_ident[1] == 'E') &&
	(file_header.e_ident[2] == 'L') &&
	(file_header.e_ident[3] == 'F')	)) 
	{
		printf("Read ELFMemoryImage Header Error!");
		return false;
	}
	if(file_header.e_type != ET_EXEC)
	{
		printf("Not Executable Image");
	}
	memory_entry = file_header.e_entry;
	sizeof_prog_headers = file_header.e_phentsize * file_header.e_phnum;
	prog_headers = (Elf32_Phdr *)malloc(sizeof(Elf32_Phdr)*file_header.e_phnum);
	//printf("elf file size = %d\n",file_header.
	fseek(input,file_header.e_phoff,SEEK_SET);

	//	read the elf file programheaders to the prog_headers array
	ret = (int)fread(prog_headers,file_header.e_phentsize,file_header.e_phnum,input);
	if(ret == -1)
	{
		printf("Read Program Header Error!");
		exit(1);
	}
	//	put every segment(except the last segment including .bss section,
	//	for it mapped to virtual address) in elf file into our memory[];
	for( i = 0, elf_phdr = (Elf32_Phdr*)(prog_headers); i < file_header.e_phnum; i++, elf_phdr++)
	{
		if(elf_phdr->p_type != PT_LOAD)
			continue;
		if(elf_phdr->p_flags & PF_R)
		{
			elf_prot |= PROT_READ;
		}
		if( elf_phdr->p_flags & PF_W )
		{
			elf_prot |= PROT_WRITE;
		}
		if( elf_phdr->p_flags & PF_X )
		{
			elf_prot |= PROT_EXEC;
		}

		fseek(input,elf_phdr->p_offset,SEEK_SET);
		buffer_size = elf_phdr->p_filesz;
		//load the segments into different spaces
		if( elf_phdr->p_paddr >= FLASH_BEGIN && elf_phdr->p_paddr <= FLASH_END)
			p_memory = (char*)(flash + elf_phdr->p_paddr);
		else if ( elf_phdr->p_paddr >= SRAM_BEGIN && elf_phdr->p_paddr <= SRAM_END )
			p_memory = (char*)(sram + elf_phdr->p_paddr - SRAM_BEGIN);
		buffer_flag = elf_phdr->p_offset;
		ret = (int)fread(p_memory, buffer_size, 1, input);

		if(ret != 1 && buffer_size !=0)
		{
			printf("segment %d loading error!",i);
		}
	}
	initial_entry(file_header.e_entry);
	return true;
}

void initial_entry(int entry)
{
	set_pc(entry);
}