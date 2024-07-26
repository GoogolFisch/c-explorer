
#ifndef PARSER_H_
#define PARSER_H_

#include<stdio.h>
#include<stdbool.h>

void p_print(char *data,int start,int end){
	if(end >= 0){
		char save = data[end];
		data[end] = 0;
		printf("%s",data + start);
		data[end] = save;
	}
	else{
		printf("%s",data + start);
	}
}

//#define PI 3.1415

// do the half parsing, as well as printing
void p_printfo(char *data,int size, bool printLn,bool usePrep){
	int functionDepth = 0;
	int curlBeginn = -1;
	int lineNumber = 0;

	bool isPrep = false;
	char ch,pch = 0;
	char isString,isSingStr,isStrEsc,isComment,isMlComment;
	int prevComment,endComment,nlBeginns;
	isString = isSingStr = isStrEsc = isComment = isMlComment = 0;
	prevComment = endComment = nlBeginns = -1;
	for(int over = 0;over < size;over++){
		pch = ch;
		ch = data[over];
		if(ch == '\n'){
			lineNumber++;
		}/**/

		if(isString){
			if(isStrEsc)isStrEsc = 0;
			else{
				if(ch == '\"')
					isString = 0;
				else if(ch == '\\')
					isStrEsc = 1;
			}
		}
		else if(isSingStr){
			isSingStr++;
			if(isStrEsc)isStrEsc = 0;
			else if(ch == '\'')
				isSingStr = 0;
			else if(ch == '\\')
				isStrEsc = 1;
			else if(isSingStr > 2)
				printf("E");
		}
		else if(isComment){
			if(ch == '\n' && pch != '\\'){
				isComment = 0;
				endComment = over;
				nlBeginns = over + 1;
			}
		}
		else if(isMlComment){
			if(ch == '/' && pch == '*'){
				endComment = over + 1;
				isMlComment = 0;
			}
		}
		else{
			// print info
			if(ch == '\n' && pch != '\\' && isPrep & usePrep){
				//printf("@");
				isPrep = false;
				p_print(data,nlBeginns - 1,over);
			}
			else if(ch == ';' && pch == '}' && functionDepth == 0){
				p_print(data,curlBeginn,over + 1);
			}
			else if((ch == ';' || ch == '{') && functionDepth == 0){
				printf("\n\n");
				if(prevComment != -1){
					p_print(data,prevComment,endComment + 1);
				}
				if(printLn)
					printf("%d\t",lineNumber);
				p_print(data,nlBeginns,over);
				printf(";\b");
				if(ch == '{')
					curlBeginn = over;
			}
			// doing the regulating stuff!
			if(ch == '{')
				functionDepth++;
			else if(ch == '}'){
				functionDepth--;
				prevComment = -1;
			}
			else if(ch == '"')
				isString = 1;
			else if(ch == '\'')
				isSingStr = 1;
			else if(ch == '/' && pch == '/')
				isComment = 1;
			else if(ch == '*' && pch == '/')
				isMlComment = 1;
			else if(ch == '\n' && pch != '\\')
				nlBeginns = over + 1;
			else if(ch == '#' && functionDepth == 0){
				isPrep = true;
			}

			if((isComment || isMlComment) && functionDepth < 1){
				prevComment = over - 1;
			}
		}
	}
	if(isPrep && usePrep){
		p_print(data,nlBeginns - 1,-1);
	}
}

#endif
