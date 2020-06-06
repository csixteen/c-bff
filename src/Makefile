OBJECTS := main.o prog.o stack.o errors.o

c-bff : $(OBJECTS)
	@$(CC) -std=c99 -D_XOPEN_SOURCE=600 -Wall -o c-bff $(OBJECTS)

main.o : common.h prog.h errors.h

errors.o: common.h errors.h

prog.o : prog.h stack.h

stack.o: stack.h errors.h

.PHONY : clean
clean :
	@rm -f c-bff $(OBJECTS)
