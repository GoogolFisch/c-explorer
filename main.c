
#include<stdio.h>
#include<stdbool.h>
#include"filer.h"
#include"parser.h"

/*show help*/
int printHelp(char *name){
	printf("%s [Files]\n",name);
	printf("add as many files as you want!\n");
	printf("Format:\n");
	printf("//Comments\n");
	printf("Line\tcontent of line or segment\n");
	printf("Options: (combine them!)\n");
	printf("-l print line number of function\n");
	printf("-p also print prepocessor\n");
	return 0;
}

int main(int argc,char **argv){
	if(argc < 2)
		return printHelp(argv[0]);


	bool doPrintLn = false;
	bool usePrep = false;

	for(int aOver = 1;aOver < argc;aOver++){
		if(argv[aOver][0] == '-'){
			for(int i = 1;argv[aOver][i] != 0;i++){
				if(argv[aOver][i] == 'l')
					doPrintLn = true;
				else if(argv[aOver][i] == 'p')
					usePrep = true;
			}
			// do not use as a file!
			argv[aOver][0] = 0;
			//break;
		}
	}

	for(int fOver = 1;fOver < argc;fOver++){
		char *lookAtFile = argv[fOver];
		int mainSize;
		char *mainCont = f_readFile(lookAtFile,&mainSize);
		if(mainCont == NULL)continue;
		printf("// =============== %s",lookAtFile);
		p_printfo(mainCont,mainSize,doPrintLn,usePrep);

		free(mainCont);
		printf("\n");
	}
	return 0;
}
