
OPT = -g3 -O0

ifeq ($(OS), Windows_NT)
        EXEC=exe
else
        EXEC=out
endif

main: main.c _includes
	$(CC) $(OPT) main.c -o run.$(EXEC)
	@echo DONE

_includes: filer.h perser.h


help:
	@echo main
	@echo help
