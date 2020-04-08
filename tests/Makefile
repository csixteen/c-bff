TARGETS := test_stack

SRC := ../src

define test_module
	@$(CC) -std=c99 -D_XOPEN_SOURCE=600 -Wall -o $@ $^
	@./$@
	@echo $< passed!
endef

.PHONY : test
test : clean $(TARGETS)

test_stack: stack.c $(SRC)/errors.c $(SRC)/stack.c
	$(test_module)

.PHONY : clean
clean :
	@rm -rf $(TARGETS)
