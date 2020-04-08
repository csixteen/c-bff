OBJECTS := c_bff.o prog.o stack.o errors.o

c-bff : $(OBJECTS)
	@$(CC) -Wall -o c-bff $(OBJECTS)

c_bff.o : c_bff.h prog.h errors.h

errors.o: c_bff.h errors.h

prog.o : prog.h stack.h

stack.o: stack.h errors.h

.PHONY : clean
clean :
	rm c-bff $(OBJECTS)
