#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <pcolors.h>
#define CAL_WIDTH 21
void print_pctg (int Y_d, int Y_);
void print_cal (int Y_, int M_, int M_d, int M_fst_d, int max_Md);
int rd (double dn);
bool leap (int Y);
int fst_day_i (int Y_);
char curr_day_i (int year_day, int fst_day_i);
int max_month_days (int M_, int Y_);
int day_of_year (int M_, int Y_, int month_day);
int main () {
	time_t now=time(NULL);
	struct tm *t=localtime(&now);
	int Y=t->tm_year+1900, M=t->tm_mon,
	    Md=t->tm_mday, Yd=day_of_year(M+1,Y,Md),
		Wd=curr_day_i(Yd,fst_day_i(Y)),
		max_Md=max_month_days(M,Y),
		M_fst_d=curr_day_i(Yd-(Md-1),fst_day_i(Y));
		print_cal(Y,M,Md,M_fst_d,max_Md);
		return 0;	
}
void print_pctg (int Y_d, int Y_) {
	int mY_d=(leap(Y_)) ? 366 : 365,
	    pctg=rd((double)Y_d/mY_d*100),
		topctg=rd((double)pctg/4.761904762);
	for (int i=0;i<CAL_WIDTH;i++)
		if (i<=topctg)
			printf("▓");
		else
			printf("░");
	putchar('\n');
}
void print_cal (int Y_, int M_, int M_d, int M_fst_d, int max_Md) {
	char S_d[7][3]={"Su","Mo","Tu","We","Th","Fr","Sa"},
		 S_M[12][4]={"Jan","Feb","Mar","Apr","May","Jun",
				 "Jul","Aug","Sep","Oct","Nov","Dec"};
	printf("%4d",Y_);
	for (int i=0;i<CAL_WIDTH-7;i++)
		putchar(' ');
	printf("%s\n%s%s",S_M[M_],BLCK,B_WHT);
	for (int d=0;d<7;d++)
		printf("%s ",S_d[d]);
	puts(CLRC);
	int w=0;
	for (;w<M_fst_d;w++) printf("   ");
	for (int d=0;d<max_Md;d++) {
		if (w++>=7) {
			putchar('\n');
			w=1;
		}
		if (d+1==M_d) printf("%s%s",BLCK,B_WHT);
		printf("%2d%s ",d+1,CLRC);
	}
	putchar('\n');
}
int rd (double dn) {
	if ((dn-(int)dn)>=.5F)
		return (int)++dn;
	return (int)dn;
}
bool leap (int Y) {
	return ((Y%100!=0 && Y%4==0) || (Y%100==0 && Y%400==0));
}
char curr_day_i (int Y_d, int fd_i) {
	return fd_i+(Y_d-7*rd(Y_d*.1428F)-1);
}
int fst_day_i (int Y_) {
	int Nday_i=(Y_-2023);
	for (int y=2023;y<Y_;y++)
		if (leap(y)) Nday_i++;
	if (Nday_i>6)
		Nday_i-=7*rd(Nday_i*.14F);
	if (Nday_i==7) Nday_i=0;
	return Nday_i;
}
int max_month_days (int M_, int Y_) {
	if ((M_<7 && M_%2==0) || (M_>=7 && M_%2!=0) && M_!=1)
		return 31;
	if (M_==1)
		return (leap(Y_)) ? 29: 28;
	return 30;
}
int day_of_year (int M_, int Y_, int month_day) {
	if (M_==0)
		return month_day;
	int days=0, d=0;
	if (M_>1) M_--;
	while (d<M_)
		days+=max_month_days(d++,Y_);
	return days+month_day;
}
