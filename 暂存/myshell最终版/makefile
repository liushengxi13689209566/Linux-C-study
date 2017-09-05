cc = gcc
OBJ = shell
all:
	$(cc) -c ./myshell_1.c
	$(cc) -o $(OBJ) ./*.o /lib64/libreadline.so.6 -I -lreadlin -lncurses -g
	rm *.o 
clean:
	rm *.o
