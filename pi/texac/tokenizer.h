void tokenizer (char (*num)[NUM_MAX_S], char *op, char *cd,  
				int cd_s, int n_s) {
	int d_c=0, o_c=0, c=0;
	bool is_neg=false;
	for (int i=0;i<cd_s;i++) { 
		char digits[NUM_MAX_S];
		if (isdigit(cd[i]) || cd[i]=='.') {
			digits[c++]=cd[i];
			continue;
		} 
		op[o_c]=cd[i];
		switch (c) {
			case 0:
				if (cd[i]=='-' && (i==0 || (i>0 && !isdigit(cd[i-1])))) {
					op[o_c++]='*';
					op[o_c++]='-';
					*num[d_c+1]='1';
					num[d_c+1][1]='\0';
					is_neg=true;
					continue;
				}
				break;
			case 1:
				if (n_s==1) {
					**num=*digits;
					continue;
				}
				*num[d_c]=*digits;
				num[d_c++][1]='\0';
				break;

			default:
				memcpy(num[d_c],digits,c);
				num[d_c++][c]='\0';
		}
		if (is_neg) {
			d_c++;
			!is_neg;
		}
		c=0; 
		o_c++;
	}
}

