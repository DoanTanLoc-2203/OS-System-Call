all : test.o
	gcc -o test test.o -lget_proc_info
test.o: test.c 
	gcc -c test.c
clean:
	rm -f test *.o
