#include "elf_loader.h"

bool load_elf(char *p)
{
	int ret;
	int a=100;
	int sizeof_prog_headers;
	int memory_entry;
	int i,j,k;
	int buffer_num;
	int elf_prot;
	int buffer_size;
	int buffer_flag;
	char* segment;
	char* p_memory;
	Elf32_Ehdr file_header;// = (Elf32_Ehdr)malloc(sizeof(Elf32_Ehdr))
	Elf32_Phdr *prog_headers;
	Elf32_Phdr *elf_phdr;
	FILE *input;
	p_memory = (char *)memory;
	(char *)memory;
	input = fopen(p,"r");
//	printf("%d\n",sizeof(Elf32_Ehdr));
	if(input==NULL)
	{
		printf("\nerror on open elf file!");
		getch();
		exit(1);
	}
	ret = fread( (char *)(&file_header), sizeof(Elf32_Ehdr), 1, input );
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

////				XTInt32	ret;
////				XTInt32	sizeof_prog_headers;
////				Elf32_Phdr *prog_headers;
////
////
////				mi_entry = file_header.e_entry;
////				sizeof_prog_headers = file_header.e_phentsize * file_header.e_phnum;
////				prog_headers = new Elf32_Phdr[file_header.e_phnum]; 
////				//need to replace with our function

//				SYSCALL::XTLseek(mi_file, file_header.e_phoff, SEEK_SET);
//
//				ret = SYSCALL::XTRead(mi_file, (void*)prog_headers, sizeof_prog_headers);
//				if( -1 == ret )
//				{
//								UTIL::XTLOG("Read Prog Header Error!");
//								SYSCALL::XTExit(-1);
//				} 
	//	read the elf file programheaders to the prog_headers array
	ret = fread(prog_headers,file_header.e_phentsize,file_header.e_phnum,input);
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
		//if(feof(input))
		//{
		//	printf("end of file[before read] \n");
		//}
		fseek(input,elf_phdr->p_offset,SEEK_SET);
		buffer_size = elf_phdr->p_filesz;
		p_memory += elf_phdr->p_paddr;
		buffer_flag = elf_phdr->p_offset;
		buffer_num=1;
		while(!fread(p_memory,buffer_size,1,input))				//一次读取过大filesize可能出错，buffer_size/=2直到成功读取,
		{														//则该buffer_size为合理读取大小
				fseek(input,elf_phdr->p_offset,SEEK_SET);
				buffer_size = buffer_size/2;					
				buffer_num = buffer_num*2;						//buffer_size*buffer_num则大约为原来读取块的大小elf_phdr->p_filesz
		}
		p_memory = (char *)memory+elf_phdr->p_paddr+buffer_size;//循环结束后已经成功读取了一块，应该把内存指针指向加上一块buffer_size
		k = buffer_num - 1;										//还有buffer_num-1块buffer_size大小的块需要读取
		fseek(input,elf_phdr->p_offset+buffer_size,SEEK_SET);
		if(feof(input))
		{
			printf("read the end of file before while(k)\n");
			exit(1);
		}
		while(k)												
		{
			fread( p_memory + (buffer_num-k)*buffer_size , buffer_size , 1 , input );
			if(feof(input))
			{
				printf("read the end of file during while(k = %d)\n",k);
			}
			k--;
		}
		if(feof(input))
		{
			printf("read the end of file after while(k)\n");
		}
		else
		{
			fseek(input, elf_phdr->p_offset+buffer_size*buffer_num,SEEK_SET);
			if(!fread( p_memory + buffer_num*buffer_size,elf_phdr->p_filesz-(buffer_size*buffer_num),1,input))
			{
				printf("余数处理error!\n");
			}
		}
		//ret = fread(p_memory+(elf_phdr->p_paddr),1,elf_phdr->p_filesz,input);
		if(feof(input))
		{
			printf("end of file \n");
		}
		if(ret != 1)
		{
			printf("segment %d loading error!",i);
		}
	}
//
//				Elf32_Phdr *elf_phdr;
//				XTInt32 elf_prot;
//				XTInt32 elf_flags;
//				XTInt32 page_offset;
//				XTInt32 i;
//
//				XTMemAddr highest_addr = 0x0;
//				XTUint32  highest_file_size = 0;	
//				XTUint32  highest_mem_size = 0;	
//
//				for( i = 0, elf_phdr = (Elf32_Phdr*)(prog_headers); i < file_header.e_phnum; i++, elf_phdr++ )
//				{
//								if( elf_phdr->p_type != PT_LOAD )
//												continue;
//
//								if( elf_phdr->p_flags & PF_R )
//												elf_prot |= PROT_READ;
//								if( elf_phdr->p_flags & PF_W )
//												elf_prot |= PROT_WRITE;
//								if( elf_phdr->p_flags & PF_X )
//												elf_prot |= PROT_EXEC;
//
//								//elf_flags = MAP_ANON|MAP_PRIVATE|MAP_DENYWRITE|MAP_EXECUTABLE|MAP_FIXED;
//								elf_flags = MAP_PRIVATE | MAP_FIXED;
//
//								page_offset = PAGEOFFSET(elf_phdr->p_vaddr);
//
//								if( MAP_FAILED == SYSCALL::XTMmap((void *)PAGESTART(elf_phdr->p_vaddr), elf_phdr->p_filesz + page_offset, elf_prot, elf_flags, mi_file, elf_phdr->p_offset - page_offset) )
//								{
//												UTIL::XTLOG("mmap error!\n");
//												SYSCALL::XTExit(-1);
//								}
//
//#if 0
//								XTUint8 *tmp_buf = new XTUint8[elf_phdr->p_filesz+1];
//								//need TODO
//								SYSCALL::XTLseek(mi_file, elf_phdr->p_offset, SEEK_SET);
//								SYSCALL::XTRead(mi_file, tmp_buf, elf_phdr->p_filesz);
//								UTIL::XTMemcpy((void *)elf_phdr->p_vaddr, tmp_buf, elf_phdr->p_filesz);
//#endif
//
//								if( elf_phdr->p_vaddr > highest_addr )
//								{
//												highest_addr = PAGESTART(elf_phdr->p_vaddr);
//												highest_file_size = elf_phdr->p_filesz + page_offset;
//												highest_mem_size = elf_phdr->p_memsz + page_offset;
//								}
//				}
//				delete[] prog_headers;
//
//				//Special deal with bss segment.
//				elf_prot = PROT_READ | PROT_WRITE;
//				elf_flags = MAP_ANON | MAP_PRIVATE | MAP_FIXED;
//				if( MAP_FAILED == SYSCALL::XTMmap((void *)PAGEALIGN(highest_addr + highest_file_size), (highest_mem_size - highest_file_size), elf_prot, elf_flags, 0, 0) )
//				{
//								UTIL::XTLOG("mmap error!\n");
//								SYSCALL::XTExit(-1);
//				}
//				UTIL::XTMemset((void *)(highest_addr + highest_file_size), 0, (highest_mem_size-highest_file_size));
//
////				mi_brk = PAGEALIGN(highest_addr + highest_file_size) + PAGEALIGN(highest_mem_size - highest_file_size);
//				mi_brk = PAGEALIGN(highest_addr + highest_mem_size);
//				SYSCALL::sys_brk = mi_brk;
//				//SYSCALL::sys_brk = 0x10017000;
//				
//				//map memory for heap & stack
//				elf_prot = PROT_READ | PROT_WRITE;
//				elf_flags = MAP_ANON | MAP_PRIVATE | MAP_FIXED;
//				if( MAP_FAILED == SYSCALL::XTMmap((void *)PAGESTART(mi_brk), GLOBAL::STACK_BASE - mi_brk, elf_prot, elf_flags, 0, 0) )
//				{
//								UTIL::XTLOG("mmap error!\n");
//								SYSCALL::XTExit(-1);
//				}

	return true;
}