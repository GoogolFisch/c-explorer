
#ifndef PARSER_H_
#define PARSER_H_

#include"includer.h"

// do the half parsing, as well as printing
void p_printfo(char *data,int size){
	int functionDepth = 0;
	int curlBeginn = -1;
	int lineNumber = 0;
	char ch,pch = 0;
	char replch;
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
			if(ch == '\'' && pch != '\\')
				isSingStr = 0;
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
			if(ch == ';' && pch == '}' && functionDepth == 0){
				replch = data[over];
				data[over] = 0;
				printf("\n%s",data + curlBeginn);
				data[over] = replch;
			}
			else if((ch == ';' || ch == '{') && functionDepth == 0){
				printf("\n\n");
				if(prevComment != -1){
					replch = data[endComment];
					data[endComment] = 0;
					printf("%s\n",data + prevComment);
					data[endComment] = replch;
				}
				replch = data[over];
				data[over] = 0;
				printf("%d\t%s",lineNumber,data + nlBeginns);
				data[over] = replch;
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

			if((isComment || isMlComment) && functionDepth < 1){
				prevComment = over - 1;
			}
		}
	}
}


#endif
