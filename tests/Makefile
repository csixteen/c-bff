TARGETS := test_stack

SRC := ../src

define test_module
	@$(CC) -Wall -o $@ $^
	@./$@
	@echo $< passed!
endef

.PHONY : test
test : clean $(TARGETS)

test_stack: stack.c $(SRC)/stack.h $(SRC)/stack.c
	$(test_module)

.PHONY : clean
clean :
	@rm -rf $(TARGETS)
