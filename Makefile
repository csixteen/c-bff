.PHONY : bin
bin:
	@cd src && $(MAKE)
	@mkdir -p bin
	@cp src/c-bff bin/

clean:
	@cd src && $(MAKE) clean

test:
	@cd tests && $(MAKE)
