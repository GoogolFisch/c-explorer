
#include"includer.h"
#include"console.h"
#include"filer.h"
#include"parser.h"

/*show help*/
int printHelp(char *name){
	printf("%s [Files]\n",name);
	printf("add as many files as you want!\n");
	printf("Format:\n");
	printf("//Comments\n")
	printf("Line\tcontent of line or segment\n")
	return 0;
}

int main(int argc,char **argv){
	if(argc < 2)
		return printHelp(argv[0]);
	for(int fOver = 1;fOver < argc;fOver++){
		char *lookAtFile = argv[fOver];
		int mainSize;
		char *mainCont = f_readFile(lookAtFile,&mainSize);
		if(mainCont == NULL)continue;
		printf("// ========== File: %s",lookAtFile);
		p_printfo(mainCont,mainSize);

		free(mainCont);
		printf("\n");
	}
	return 0;
}
