
#ifndef FILER_H_
#define FILER_H_

#include<stdlib.h>

/*
 * safly read a file and store all of it contens
 * returns the data and safePointer for the size*/
char *f_readFile(char *fileName,int *safePointer){
	FILE *fptr = fopen(fileName,"r");
	if(fptr == NULL)return NULL;

	fseek(fptr,0L,SEEK_END);
	int size = ftell(fptr);
	*safePointer = size;
	fseek(fptr,0L,SEEK_SET);

	char *data = malloc(sizeof(char) * size);
	if(data != NULL)
		fread(data,sizeof(char),size,fptr);
	fclose(fptr);
	return data;
}


#endif
