bool err (int type) {
	printf("\033[0;31m");
	switch (type) {
		case 0:
			puts("what?");
			break;
		case 1:
			puts("invalid operator");
			break;
	}
	printf("\033[0m");
	return 0;
}
bool lexer (char *cd, char (*num)[NUM_MAX_S], char *op, 
			int cd_s, int n_s, int p_s) {
	cd_s--;
	for (int l=0;l<cd_s;l++) {   
		int not_valid=0;
		for (int p=0;p<OP_S-1;p++) 
			if (!isdigit(cd[l]) && cd[l]!=OP[p] && cd[l]!='.') 
				not_valid++;
		if (not_valid==OP_S-1) return err(1);
	}
	return 1;
}
