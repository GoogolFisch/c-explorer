
OPT = -g3 -O0 -Wall

ifeq ($(OS), Windows_NT)
        EXEC=exe
else
        EXEC=out
endif

main: main.c _includes
	$(CC) $(OPT) main.c -o cxpl.$(EXEC)
	@echo DONE

_includes: filer.h parser.h


help:
	@echo main
	@echo help
