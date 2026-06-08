#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "def.h"
#include "get_sizes.h"
#include "tokenizer.h"
#include "lexer.h"
#include "bug.h"
bool debug=true;
int main () {
	char cd[CD_MAX_S];
	while (true) {
		int np_s[2*sizeof(int)];
		printf("\033[0;92m]\033[0m\033[3 q");
		fgets(cd,CD_MAX_S,stdin);
		cd[CD_MAX_S-1]='\0';
		int cd_s=get_cd_s(cd);
		if (*cd=='q') {
			puts("\033[2 q");
			exit(0);
		}
		get_np_s(cd,cd_s,np_s);
		char num[*np_s][NUM_MAX_S], op[np_s[1]];
		tokenizer(num,op,cd,cd_s,*np_s);
		if (!lexer(cd,num,op,cd_s,*np_s,np_s[1]))
			continue;
		if (debug)
			bug(np_s,num,op);
	}
	return 0;
}
