void bug (int *np_s, char (*num)[CD_MAX_S], char *op) {
	for (int i=0;i<29;i++) 
		putchar('-');
	printf("\nNumbers %2d\tOperators %2d\n", *np_s,np_s[1]);
	for (int i=0;i<np_s[1];i++) {
		printf("'%c'",op[i]);
		if (i!=np_s[1]-1)
			printf(", ");
	}
	putchar('\n');
	for (int i=0;i<*np_s;i++) {
		printf("%s",num[i]);
		if (i!=*np_s-1)
		printf(", ");
	}
	putchar('\n');
	for (int i=0;i<29;i++) 
		putchar('-');
	putchar('\n');
}

