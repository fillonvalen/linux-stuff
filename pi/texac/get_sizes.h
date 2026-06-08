int get_cd_s (char *cd) {
	int s=0;
	for (int i=0;i<CD_MAX_S;i++)
		if (cd[i]!='\0') s++;
		else break;
	return s;
}
void get_np_s (char *cd, int cd_s, int *np_s) {
	int m=0, n=0, p=0;
	for (int i=0;i<cd_s-1;i++) {
		if (isdigit(cd[i])) {
			if (m==0) {
				n++; m++;
			}
			continue;
		}
		if (cd[i]!='.') {
			if (*cd=='-' && (i==0 || (i>0 && !isdigit(cd[i-1])))) {
				n++; p++;
			}
			p++;
			m=0;
		}
	}
	*np_s=n, np_s[1]=p; 
}
