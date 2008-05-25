decode:main.o fetch.o decode.o shift_rotate.o calculate.o data_process_imm.o miscellaneous.o immediate_decode.o register.o memory.o
	gcc -o decode main.o fetch.o decode.o shift_rotate.o calculate.o data_process_imm.o miscellaneous.o immediate_decode.o register.o memory.o -g
main.o:main.c fetch.h decode.h 
	gcc -c main.c -g
fetch.o:fetch.c fetch.h
	gcc -c fetch.c -g
decode.o:decode.c decode.h
	gcc -c decode.c -g
shift_rotate.o:shift_rotate.c instruction.h
	gcc -c shift_rotate.c -g
calculate.o:calculate.c instruction.h
	gcc -c calculate.c -g
data_process_imm.o:data_process_imm.c instruction.h
	gcc -c data_process_imm.c -g
miscellaneous.o:miscellaneous.c instruction.h
	gcc -c miscellaneous.c -g
immediate_decode.o:immediate_decode.c instruction.h
	gcc -c immediate_decode.c -g
register.o:register.c register.h
	gcc -c register.c -g
memory.o:memory.c memory.h
	gcc -c memory.c -g
