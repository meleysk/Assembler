#possible suffixes
.SUFFIXES: .c .o

#gcc will be used to compile the source file
CC = gcc

CFLAGS= -g

#rule how the executable should be created from the source file
.c.o:
	$(CC) $(CFLAGS) -c $<
	
#dependency rule for the default target
p4: main.o functions.o	helpers.o	
	gcc main.o functions.o	helpers.o -o p4
	
#dependency rule for other targets
main.o:  constants.h		structdef.h  globals.h  prototypes.h
functions.o:  constants.h structdef.h externs.h  prototypes.h
helpers.o:  constants.h structdef.h externs.h  prototypes.h


#target for removing unnecessary files
clean:
	rm -f *.o core
