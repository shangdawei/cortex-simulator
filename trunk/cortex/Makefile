decode:main.o fetch.o decode.o data_process_imm.o miscellaneous.o immediate_decode.o register.o memory.o
	gcc -o decode main.o fetch.o decode.o data_process_imm.o miscellaneous.o immediate_decode.o register.o memory.o
main.o:main.c fetch.h decode.h 
	gcc -c main.c
fetch.o:fetch.c fetch.h
	gcc -c fetch.c
decode.o:decode.c decode.h
	gcc -c decode.c
data_process_imm.o:data_process_imm.c instruction.h
	gcc -c data_process_imm.c
miscellaneous.o:miscellaneous.c instruction.h
	gcc -c miscellaneous.c
immediate_decode.o:immediate_decode.c instruction.h
	gcc -c immediate_decode.c
register.o:register.c register.h
	gcc -c register.c
memory.o:memory.c memory.h
	gcc -c memory.c
