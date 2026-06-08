#include <pcolors.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <psym.h>
#define BK_ID      7
#define BP_ID      8 
#define BB_ID      9 
#define BR_ID     10
#define BN_ID     11
#define BQ_ID     12
#define N_EMPTY    0
#define CHECK      1
#define DCHECK     2
#define CMATE      3
#define PPROM      4
#define TR         8
#define TS        64
#define SC         4 
#define PLAY_S     6
#define MPV      131
#define MRC      135  
#define SOI sizeof(int)
int algb_table[TS*SOI],                // table with algrebraic coordinates
	posv_table[TS*SOI],                // valuable positions table
    table[TS*SOI],                     // pieces table
    n_turn=18,                         // 18 (white) or 0 (black)  
    reg_black_plays[2000][PLAY_S*SOI], // register black plays
    reg_white_plays[2000][PLAY_S*SOI], // register white plays
    attacked=-1,                       // color that is being checked
    d_x=0,d_y=0,                       // destination coordinates
    s_x=0,s_y=0,                       // old coordinates
    w_plays=0,                         // number of white plays
    b_plays=0;                         // same but black plays instead
bool moving=false,
	 debug=true;
int swap_player (bool asign) {
	if (!asign) {
		n_turn=(n_turn==18) ? 0 : 18;
		return 0;
	}
	return (n_turn==18) ? 0 : 18;
}
int get_color_id (int piece_id) {
	return (piece_id-18<0) ? 0 : 18;
}
bool is_box_bussy (int *_table, int x,int y) {
	return _table[x*TR+y]!=N_EMPTY;
}
void get_algb_coor (int *dest_c, int n_play_x)  {
	char L[8]="abcdefgh";
	dest_c[0]=L[n_play_x%10-1],
	dest_c[1]=(int)(.1F*(n_play_x-(n_play_x%10)));
}
void trans_play (int *n_play) {
	char inits[7]="K BRNQ";
	if (n_play[0]!=BP_ID && n_play[0]!=BP_ID+11) {
		int e_p=(n_play[0]>=18) ? 11 : 0;
		(void)putchar(inits[n_play[0]-e_p]);
	}
	int dest_coor[2*SOI];
	get_algb_coor(dest_coor,n_play[1]);
	printf("%c%d",dest_coor[1],dest_coor[0]);
	putchar((n_play[2]==0) ? '-':'x');
	get_algb_coor(dest_coor,n_play[3]);
	printf("%c%d",dest_coor[0],dest_coor[1]);
	switch (n_play[4]) {
		case 1:
			putchar('+');
			break;
		case 2:
			printf("++");
			break;
		case 3:
			putchar('#');
			break;
		case 4:
			putchar('=');
	}
	putchar((n_play[5]!=0) ? n_play[5]+'0':'!');
}
void print_piece (char color, char init) {
	if (color=='w') {
		switch (init) {
			case 'b':
				printf(WBISHOP);
				break;		
			case 'k':
				printf(WKING);
				break;
			case 'n':
				printf(WKNIGHT);
				break;
			case 'p':
				printf(WPAWN);
				break;
			case 'q':
				printf(WQUEEN);
				break;
			case 'r':
				printf(WROOK);
		}
		return;
	}
	switch (init) {
		case 'b':
			printf(BBISHOP);
			break; 	
		case 'k':
			printf(BKING);
			break;
		case 'n':
			printf(BKNIGHT);
			break;
		case 'p':
			printf(BPAWN);
			break;
		case 'q':
			printf(BQUEEN);
			break;
		case 'r':
			printf(BROOK);
	}
}
void trans_piece_id (char *c_piece, int piece_id, bool print) {
	char initials[7]="kpbrnq";
	piece_id-=18;
	c_piece[0]=(piece_id<0) ? 'b' : 'w';
	piece_id+=(piece_id<0) ? 11 : 0;
	c_piece[1]=initials[piece_id];
	if (print)
		print_piece(c_piece[0],c_piece[1]);
}
bool is_my_piece (int *_table, int x, int y) {
	return ((_table[x*TR+y]-18<0 && n_turn==0) ||
	        (_table[x*TR+y]-18>=0 && n_turn==18) &&
	         _table[x*TR+y]!=N_EMPTY);
}
bool is_s_piece (int *_table,char piece_initial, int x, int y) {
	char cont[3];
	trans_piece_id(cont,_table[x*TR+y],false);
	return (cont[1]==piece_initial);
}
bool range_bishop (int *_table,int sx,int sy,int dx,int dy) { 
	(sx<dx) ? sx++ : sx--; 
	(sy<dy) ? sy++ : sy--; 
	int tmp_x=sx, tmp_y=sy;
	if (sx>dx) { // U
		if (sy>dy) {// UL
			while (tmp_x!=dx || tmp_y!=dy) {
				if (is_box_bussy(_table,tmp_x--,tmp_y--)) 
					return 1;
				}
		}
		while (tmp_x!=dx || tmp_y!=dy) {//UR
			if (is_box_bussy(_table,tmp_x--,tmp_y++)) 
				return 1;
		}
		return 0;
	} 
	if (sy>dy) { //D
		while (tmp_x!=dx || tmp_y!=dy)  //DL
			if (is_box_bussy(_table,tmp_x++,tmp_y--)) 
				return 1;
	}
	while (tmp_x!=dx || tmp_y!=dy)  //DR
		if (is_box_bussy(_table,tmp_x++,tmp_y++)) 
			return 1;
	return 0;
}
bool range_pawn (int *_table,int sx,int sy,int dx,int dy,int color) {
	return ((color==0 && _table[(sx-1)*TR+dy]!=N_EMPTY) ||
	 	    (color==18 && _table[(sx+1)*TR+dy]!=N_EMPTY));
}
bool range_rook (int *_table,int sx,int sy,int dx,int dy) {
	(sx==dx) ? (sy>dy ? sy-- : sy++):
			     (sx>dx ? sx-- : sx++);
	if (sx==dx) { //L or R
		if (sy>dy) {//L
			for (int n=sy;n>dy;n--) 
				if (is_box_bussy(_table,sx,n)) return 1;
	}
		for (int n=sy;n<dy;n++) //R
			if (is_box_bussy(_table,sx,n)) return 1;
	}
	if (sx>dx) {//U
		for (int m=sx;m>dx;m--)
			if (is_box_bussy(_table,m,sy)) return 1;
	}
	for (int m=sx;m<dx;m++) //D
		if (is_box_bussy(_table,m,sy)) return 1;
	return 0;
}
bool range_queen (int *_table,int sx,int sy,int dx,int dy) {
	if (sx==dx || sy==dy) 
		return (range_rook(_table,sx,sy,dx,dy));
	else
		return (range_bishop(_table,sx,sy,dx,dy));
}
bool range_disrupted (int *_table,int sx,int sy,int dx,int dy,int piece_id) {
	int color_id=get_color_id(piece_id);
	piece_id-=(piece_id==BP_ID && color_id==18) ? 11 : 0;
	switch (piece_id) {
		case BB_ID:
			if (range_bishop(_table,sx,sy,dx,dy))
				return 1;			
			break;
		case BP_ID:
			if (range_pawn(_table,sx,sy,dx,dy,color_id))
				return 1;
			break;
		case BQ_ID:
			if (range_queen(_table,sx,sy,dx,dy))
				return 1;		
			break;
		case BR_ID:
			if (range_rook(_table,sx,sy,dx,dy))
				return 1;
	}
	return 0;
}
bool king_threatened (int x2comp,int y2comp, char pieces_inits[],int opp_color) {
	if (x2comp<0 || x2comp>7 || y2comp<0 || y2comp>7)
		return 0;
	if (table[x2comp*TR+y2comp]!=N_EMPTY &&
	    ((table[x2comp*TR+y2comp]-18<0 && opp_color==0) ||
		(table[x2comp*TR+y2comp]-18>=0 && opp_color==18)) &&
	    ((is_s_piece(table,pieces_inits[0],x2comp,y2comp) ||
 		 is_s_piece(table,pieces_inits[1],x2comp,y2comp))))
		return 1;
	return 0;
}
int king_threats_check (int *_table,int turn,int K_x,int K_y) {
	int opp_color=(turn==18) ? 0 : 18,
	    threats=0, var_K_x=K_x,var_K_y=K_y;
	while (var_K_x>0 && var_K_y<7) {
		var_K_x--; var_K_y++;
		if (king_threatened(var_K_x,var_K_y,"bq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,var_K_x,var_K_y,BB_ID)) {
			threats++;
			break;
		}
	}
	var_K_x=K_x,var_K_y=K_y;
	while (var_K_x<7 && var_K_y<7) {
		var_K_x++; var_K_y++;
		if (king_threatened(var_K_x,var_K_y,"bq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,var_K_x,var_K_y,BB_ID)) {
			threats++;
			break;
		}
	}
	var_K_x=K_x,var_K_y=K_y;
	while (var_K_x>0 && var_K_y>0) {
		var_K_x--; var_K_y--;
		if (king_threatened(var_K_x,var_K_y,"bq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,var_K_x,var_K_y,BB_ID)) {
			threats++;
			break;
		}
	}
	var_K_x=K_x,var_K_y=K_y;
	while (var_K_x<7 && var_K_y>0) {
		var_K_x++; var_K_y--;
		if (king_threatened(var_K_x,var_K_y,"bq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,var_K_x,var_K_y,BB_ID)) {
			threats++;	
			break;
		}
	}
	var_K_x=K_x;
	while (var_K_x<7) {
		var_K_x++;
		if (king_threatened(var_K_x,K_y,"rq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,var_K_x,K_y,BR_ID)) {
			threats++;	
			break;
		}
	}
	var_K_x=K_x;
	while (var_K_x>0) {
		var_K_x--;
		if (king_threatened(var_K_x,K_y,"rq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,var_K_x,K_y,BR_ID)) {
			threats++;	
			break;
		}
	}
	var_K_y=K_y;
	while (var_K_y>0) {
		var_K_y--;
		if (king_threatened(K_x,var_K_y,"rq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,K_x,var_K_y,BR_ID)) {
			threats++;	
			break;
		}
	}
	var_K_y=K_y;
	while (var_K_y<7) {
		var_K_y++;
		if (king_threatened(var_K_x,var_K_y,"rq",opp_color) &&
			!range_disrupted(_table,K_x,K_y,K_x,var_K_y,BR_ID)) {
			threats++;	
			break;
		}
	}
	if (king_threatened(K_x-2,K_y-1,"nn",opp_color) ||
		king_threatened(K_x-2,K_y+1,"nn",opp_color) ||
		king_threatened(K_x-1,K_y+2,"nn",opp_color) ||
		king_threatened(K_x-1,K_y-2,"nn",opp_color) ||
		king_threatened(K_x+1,K_y-2,"nn",opp_color) ||
		king_threatened(K_x+1,K_y+2,"nn",opp_color) ||
		king_threatened(K_x+2,K_y-1,"nn",opp_color) ||
		king_threatened(K_x+2,K_y+1,"nn",opp_color))
			threats++;
	if (king_threatened(K_x-1,K_y-1,"pp",opp_color) ||
	    king_threatened(K_x-1,K_y+1,"pp",opp_color) ||
	    king_threatened(K_x+1,K_y-1,"pp",opp_color) ||
	    king_threatened(K_x+1,K_y+1,"pp",opp_color))
			threats++;
	return threats;                   
}
void chg_pos (int *_table, int sx, int sy, int dx, int dy) {
	_table[dx*TR+dy]=_table[sx*TR+sy];
	_table[sx*TR+sy]=N_EMPTY;
}
bool is_king_safe (int *_table) {
	int K_x=0,K_y=0;
	for (int x=0;x<TR;x++) {
		for (int y=0;y<TR;y++) {
			if (is_my_piece(_table,x,y) && is_s_piece(_table,'k',x,y)) {
				K_x=x,K_y=y;
				break;
			}
		}
	}
	//printf("\n[%d]\n",n_turn);getch();
	if (king_threats_check(_table,n_turn,K_x,K_y)>0)
		return false;
	return true;
}
bool iv_bishop (int sx, int sy, int dx, int dy, int *_table) {
	if (((sx-dx==sy-dy)       ||
	    (abs(sx-dx)==(sy-dy))  ||
	    ((sx-dx)==abs(sy-dy))) &&
	    !range_disrupted(_table,sx,sy,dx,dy,BB_ID))
		return true;
	return false;
}
bool iv_king (int sx, int sy, int dx, int dy) {
	if ((sx-dx==1 || sx-dx==-1 || sx-dx==0) &&
		(sy-dy==1 || sy-dy==-1 ||
		(sx-dx!=0 && sy-dy==0)))
		return true;
	return false;
}
bool iv_knight (int sx, int sy, int dx, int dy) {
	if ((dx==sx-2 && dy==sy-1) ||
		(dx==sx-2 && dy==sy+1) ||
		(dx==sx-1 && dy==sy-2) ||
		(dx==sx-1 && dy==sy+2) ||
		(dx==sx+1 && dy==sy-2) ||
		(dx==sx+1 && dy==sy+2) ||
		(dx==sx+2 && dy==sy-1) ||
		(dx==sx+2 && dy==sy+1))
		return true;
	return false;
}
bool iv_b_pawn (int sx, int sy, int dx, int dy,
				int piece_id, int end_id, int *_table) {
	if ((sx==1 && dy==sy && (dx==sx+1 || dx==sx+2) &&
		range_disrupted(_table,sx,sy,dx,dy,piece_id) &&
		end_id==N_EMPTY) ||
		(end_id==N_EMPTY && sx!=1 && (dx==sx+1 && dy==sy)) ||
		(end_id!=N_EMPTY && dx==sx+1 && dy==sy+1) || 
	    (end_id!=N_EMPTY && dx==sx+1 && dy==sy-1))
		return true;
	return false;
}
bool iv_w_pawn (int sx, int sy, int dx, int dy,
				int piece_id, int end_id, int *_table) {
	if ((sx==6 && dy==sy && (dx==sx-1 || dx==sx-2) &&
		!range_disrupted(_table,sx,sy,dx,dy,piece_id)) || 
		(end_id==N_EMPTY && sx!=6 && (dx==sx-1 && dy==sy)) ||
		(end_id!=N_EMPTY && (dx==sx-1 && dy==sy+1)) ||
		(end_id!=N_EMPTY && (dx==sx-1 && dy==sy-1)))
		return true;
	return false;
}
bool iv_queen (int sx, int sy, int dx, int dy, int *_table) {
	if (((sx-dx==0 || sy-dy==0) ||
		((sx-dx==sy-dy) ||
		(abs(sx-dx)==(sy-dy))  ||
		((sx-dx)==abs(sy-dy)))) &&
		!range_disrupted(_table,sx,sy,dx,dy,BQ_ID))
		return true;
	return false;
}
bool iv_rook (int sx, int sy, int dx, int dy, int *_table) {
	if ((sx-dx==0 || sy-dy==0) &&
	    !range_disrupted(_table,sx,sy,dx,dy,BR_ID))
		return true;
	return false;
}
bool is_valid (int *_table,int sx,int sy,int dx,int dy,
				int piece_id) {
	int piece_color_id=get_color_id(piece_id);
	int end_id=_table[dx*TR+dy];
	if (piece_id==N_EMPTY ||
		piece_color_id!=n_turn ||
	   (((piece_id-18<0 && end_id-18<0) ||
	   (piece_id-18>=0 && end_id-18>=0)) &&
		piece_id!=N_EMPTY && end_id!=N_EMPTY) )
		return 0;         
	switch (piece_id) {
		case BP_ID:
			if (iv_b_pawn(sx,sy,dx,dy,piece_id,end_id,_table)) return 1;
			break;
		case BP_ID+11:
			if (iv_w_pawn(sx,sy,dx,dy,piece_id,end_id,_table)) return 1;
			break;
		case BR_ID:
		case BR_ID+11:
			if (iv_rook(sx,sy,dx,dy,_table)) return 1;
			break;
		case BN_ID:
		case BN_ID+11:
			if (iv_knight(sx,sy,dx,dy)) return 1;
			break;
		case BB_ID:
		case BB_ID+11: 
			if (iv_bishop(sx,sy,dx,dy,_table)) return 1;
			break;
		case BQ_ID:
		case BQ_ID+11: 
			if (iv_queen(sx,sy,dx,dy,_table)) return 1;
			break;
		case BK_ID:
		case BK_ID+11: 
			if (iv_king(sx,sy,dx,dy)) return 1;
			break;
	}
	return 0;
}
void printable (int *_table,bool cursor) {
	char lrs[9]="abcdefgh";
	printf("%s  ",CLRS);
	for (int y=0;y<TR;y++)
		printf("%c  ",lrs[algb_table[y]-81]);
	printf("\n%s",P_DR);
	for (int i=0;i<TR-1;i++)
		printf("%s%s%s",P_B,P_B,P_DH);
	printf("%s%s%s\n",P_B,P_B,P_DL);
	for (int x=0;x<TR;x++) {
		printf(P_V);
		for (int y=0;y<TR;y++) {
			if (cursor) 
				if (d_x==x && d_y==y) {
					printf(BLCK);
					(moving) ? printf(B_BLUE) :
					(debug)  ? printf(B_RED)  : printf(B_WHT);
				}
			if (_table[x*TR+y]!=N_EMPTY) {
				char cont[3];
				trans_piece_id(cont,_table[x*TR+y],true);
			} else {
				printf(EMPTY);
			}
			printf("%s%s",CLRC,P_V);
		}
		printf(" %d\n",(int)((algb_table[x*8])*.1F));
		if (x<TR-1)
			printf(P_RV);
		else
			printf(P_RU);
		if (x<TR-1) {
			for (int i=0;i<TR-1;i++)
				printf("%s%s%s",P_B,P_B,P_VH);
			printf("%s%s%s",P_B,P_B,P_LV);
		} else {
			for (int i=0;i<TR-1;i++)
				printf("%s%s%s",P_B,P_B,P_HU);
			printf("%s%s%s",P_B,P_B,P_LU);
		}
		putchar('\n');
	}
	printf(CLRC);
}
void print_plays(int *_plays, int s) {
	for (int i=0;i<s;i++) {
		if (i%4==0)
			printf("(%d) ",(int)(i*.25F)+1);
		printf("%d ",_plays[i]);
		if ((i+1)%4==0)
			putchar('\n');
	}
	putchar('\n');
}
void get_table_values (int *_vals_table, int *_table, int color) {
	for (int x=0;x<TR;x++) {
		for (int y=0;y<TR;y++) {
			int piece_id=_table[x*TR+y];
			_vals_table[x*TR+y]=0;
			if (piece_id!=N_EMPTY && ((piece_id-18<0 && color==0) ||
				(piece_id-18>=0 && color==18))) {
				_vals_table[x*TR+y]=piece_id;
				if (piece_id==BK_ID || piece_id==BK_ID+11)
					_vals_table[x*TR+y]=100;
				else if (piece_id!=N_EMPTY)
					_vals_table[x*TR+y]-=(color==0) ? 7 : 18;
			}
		}
	}
}
void copy_table (int *dest, int *table) {
	for (int x=0;x<TR;x++) 
		for (int y=0;y<TR;y++) 
			dest[x*TR+y]=table[x*TR+y];
}
void get_values (int *my_plays, int *values, int _plays_no, int *_table,
					bool posv_case) {
	int p=3;
	_plays_no*=4;
	int color=(n_turn==0) ? 18 : 0;
	while (p<=_plays_no) { 
		int tmp_table[TS*SOI],
		    t_vals_table[TS*SOI],
			ox=my_plays[p-3], oy=my_plays[p-2],
			dx=my_plays[p-1], dy=my_plays[p],
			t_val=0;
		copy_table(tmp_table,_table);
		chg_pos(tmp_table,ox,oy,dx,dy);
		get_table_values(t_vals_table,tmp_table,color);
		for (int x=0;x<TR;x++)
			for (int y=0;y<TR;y++)
					t_val+=t_vals_table[x*TR+y];
		t_val-=(posv_case) ? posv_table[dx*TR+dy] : 0;
		values[(int)(p*.25f)]=t_val;
		p+=4;
	}
}
int possible_plays (int *_table) {
	int plays_s=0;
	for (int x=0;x<TR;x++) {
		for (int y=0;y<TR;y++) {
			for (int a=0;a<TR;a++) {
				for (int b=0;b<TR;b++) {
					int tmp_table[TS*SOI],
					    piece_id=table[x*TR+y];
					copy_table(tmp_table,_table);
					if (is_valid(_table,x,y,a,b,piece_id)) {
						chg_pos(tmp_table,x,y,a,b);
						if (is_king_safe(tmp_table)) 
							plays_s++;
					}
				}
			}
		}
	}
	return plays_s;
}
void get_plays (int *_my_plays,int *_table) {
	int i=3;
	for (int x=0;x<TR;x++) {
		for (int y=0;y<TR;y++) {
			for (int a=0;a<TR;a++) {
				for (int b=0;b<TR;b++) {
					int tmp_table[TS*SOI],
					    piece_id=table[x*TR+y];
					copy_table(tmp_table,_table);
					if (is_valid(_table,x,y,a,b,piece_id)) {
						chg_pos(tmp_table,x,y,a,b);
						if (is_king_safe(tmp_table)) {
							_my_plays[i]=b,   _my_plays[i-1]=a,
							_my_plays[i-2]=y, _my_plays[i-3]=x;
							i+=4;
						}
					}
				}
			}
		}
	}
}
int best_move_i (int *_values, int *_plays, size_t vals_s) {
	int i_winner=0, reps=0;
	for (int i=0;i<vals_s-1;i++)  
		if (_values[i+1]<_values[i_winner])
			i_winner=i+1;
	for (int i=0;i<vals_s;i++)  
		if (_values[i]==_values[i_winner] && i!=i_winner)
			reps++;
	if (reps>0) {
		int i_l[reps*SOI], il_i=0;
		for (int d=0;d<vals_s;d++) 
			if (_values[d]==_values[i_winner])
				i_l[il_i++]=d;
		i_winner=i_l[rand()%reps];
	}
	return i_winner;
}
int theorical_play (int _plays_no, int *_values, int *_table, int o_turn) {
    int _plays[_plays_no*4*SOI];
	get_plays(_plays,_table);
	get_values(_plays,_values,_plays_no,_table,false);
	int i_winner=best_move_i(_values,_plays,_plays_no);
	int sx=_plays[i_winner*4],   sy=_plays[(i_winner*4)+1],
	    dx=_plays[(i_winner*4)+2], dy=_plays[(i_winner*4)+3];
	chg_pos(_table,sx,sy,dx,dy);
	if (!debug) {
		printf("\n\033[0;32m[%d]\033[m\n",n_turn);
		for (int i=0;i<_plays_no;i++) {
			printf("%2d) %d",i,_values[i]);
			putchar((i+1)%9==0 && i!=_plays_no-1 ? '\n':'\t');
		}
		printf("\n\033[0;31m[Worst: %d]\033[0m",_values[i_winner]);
		getch();
	}
	return i_winner;
}
int win_or_lose (int *_table, int o_turn) {
	int plays_no=possible_plays(_table);	
	int values[plays_no*SOI];
	int i_winner=(plays_no!=0) ? 
		theorical_play(plays_no,values,_table,o_turn) : 0;
	(void)swap_player(false);
	return (plays_no!=0) ? values[i_winner] : 0;
}
void ok_choose_play (int *best_play, int *_plays, int *_values,
                     int *diffs, int _plays_no) {
	int i_winner=0, reps=0;
	for (int d=0;d<_plays_no-1;d++) 
		if (diffs[d+1]>diffs[i_winner])
			i_winner=d+1;
	for (int d=0;d<_plays_no;d++) 
		if (diffs[d]==diffs[i_winner] && d!=i_winner)
			reps++;
	if (reps>0) {
		int i_l[reps*SOI], il_i=0;
		for (int d=0;d<_plays_no;d++) 
			if (diffs[d]==diffs[i_winner])
				i_l[il_i++]=d;
		i_winner=i_l[rand()%reps];
	}
	i_winner*=4;
	for (int i=0;i<4;i++)
		best_play[i]=_plays[i_winner+i];
}
void ok_eval (int *best_play, int *_my_plays, int *_values,int _plays_no,int *_table) {
	_plays_no*=4;
	int p=3,
	    diffs_i=0,
	    diffs[(int)(_plays_no*.25F)*SOI],
	    o_turn=n_turn;
	while (p<=_plays_no) {
		int sx=_my_plays[p-3], sy=_my_plays[p-2],
		    dx=_my_plays[p-1], dy=_my_plays[p],
		    tmp_table[TS*SOI];
		copy_table(tmp_table,_table);
		chg_pos(tmp_table,sx,sy,dx,dy);
		(void)swap_player(false);
		int i_w=MPV-_values[(int)(p*.25F)],
		    i_l=MPV-win_or_lose(tmp_table,o_turn),
		    cat_i_w=MPV-win_or_lose(tmp_table,o_turn), // i_l -> i lose 
		    cat_i_l=MPV-win_or_lose(tmp_table,o_turn), // i_w -> i win
		    dog_i_w=MPV-win_or_lose(tmp_table,o_turn),
		    dog_i_l=MPV-win_or_lose(tmp_table,o_turn);
		if (debug) {
			printf("\n(%d, %d -> %d, %d)",sx,sy,dx,dy);
			printf("\033[0;34m%d-%d+%d-%d=%d\033[0m\n",
			    i_w,i_l,cat_i_w,cat_i_l,
			    i_w-i_l+cat_i_w-cat_i_l);getch();
		}
		diffs[diffs_i++]=i_w-i_l+cat_i_w-cat_i_l;
		p+=4;	
	}
	ok_choose_play(best_play,_my_plays,_values,diffs,(int)(_plays_no*.25F));
}
void ok_computer () {
	int plays_no=possible_plays(table),
	    my_plays[plays_no*4*SOI],
		best_play[4*SOI],
		values[plays_no],
		ok_s_x=0, ok_s_y=0,
		ok_d_x=0, ok_d_y=0,
	 	s_xy_buff[2*SOI],
		d_xy_buff[2*SOI];
	if (plays_no==0) {
		puts("[Check mate]");sleep(1);
		return;
	}
	get_plays(my_plays,table);
	get_values(my_plays,values,plays_no,table,false);
	ok_eval(best_play,my_plays,values,plays_no,table);
	ok_s_x=best_play[0], ok_s_y=best_play[1],
	ok_d_x=best_play[2], ok_d_y=best_play[3],
	get_algb_coor(s_xy_buff,algb_table[ok_s_x*TR+ok_s_y]);
	get_algb_coor(d_xy_buff,algb_table[ok_d_x*TR+ok_d_y]);
	table[ok_d_x*TR+ok_d_y]=table[ok_s_x*TR+ok_s_y];
	table[ok_s_x*TR+ok_s_y]=N_EMPTY;
	n_turn=18;
}
void write_play(int piece_id, int s_x, int s_y, int d_x, int d_y,
				bool capture, int status, int pp_id) {
	int play[PLAY_S*SOI];
	*play=piece_id;
	play[1]=algb_table[s_x*TR+s_y];
	play[2]=capture;
	play[3]=algb_table[d_x*TR+d_y];
	play[4]=status; play[5]=pp_id;
	trans_play(play);
	for (int i=0;i<PLAY_S;i++) 
		reg_white_plays[w_plays][i]=play[i];
}
void finish_play () {
	(n_turn==18) ? w_plays++ : b_plays++;
	(void)swap_player(false);
	if (n_turn==0)
		ok_computer();
}
void init_algb_table () {
    for (int i=8;i>=1;i--) {
		for (int j=1;j<9;j++) {
	    	char num[3];
			num[0]=i+'0'; num[1]=j+'0';
            algb_table[TR*(TR-i)+j-1]=atoi(num);
        }
    }
}
void init_posv_table () {
	for (int x=0;x<TR;x++) {
		for (int y=0;y<TR;y++) {
			switch (x) {
				case 3:
				case 4:
					if (y>2 && y<5)
						posv_table[x*TR+y]=4;
					else
						posv_table[x*TR+y]=3;
					break;
				case 2:
				case 5:
					posv_table[x*TR+y]=3;
					break;
				case 1:
				case 6:
					posv_table[x*TR+y]=2;
					break;
				case 0:
				case 7:
					posv_table[x*TR+y]=1;
			}
		}
	}
}
void init_pawns () {
	for (int i=0;i<TR;i++) {
		table[8+i]=BP_ID;
		table[48+i]=BP_ID+11;
    }
}
void init_bishops () {
	table[2]=BB_ID;
	table[5]=BB_ID;
	table[58]=BB_ID+11;
	table[61]=BB_ID+11;
}
void init_kings () {
	table[4]=BK_ID;
	table[60]=BK_ID+11;
}
void init_knights () {
	table[1]=BN_ID;
	table[6]=BN_ID;
	table[57]=BN_ID+11;
	table[62]=BN_ID+11;
}
void init_rooks () {
	table[0]=BR_ID;
	table[7]=BR_ID;
	table[56]=BR_ID+11;
	table[63]=BR_ID+11;
}
void init_queens () {
	table[3]=BQ_ID;
	table[59]=BQ_ID+11;
}
void init_pieces () {
	for (int w=0;w<TR;w++) 
		for (int h=0;h<TR;h++)
			table[w*TR+h]=N_EMPTY;	
	init_bishops();
	init_kings();
	init_knights();
	init_pawns();
	init_queens();
	init_rooks();
}
void print_plays_regs () {
	for (int r=0;r<w_plays;r++) {
		for (int p=0;p<PLAY_S;p++) 
			printf("%d ",reg_white_plays[r][p]);
		printf("\t%s%s",BLCK,B_WHT);
		for (int p=0;p<PLAY_S;p++) 		
			printf("%d ",reg_black_plays[r][p]);
		printf("%s\n",CLRC);
	}
}
