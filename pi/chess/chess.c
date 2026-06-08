#include "fun.h"
void ret () {
	puts("\nNope!");
	sleep(1);
	s_x=-1, s_y=-1;
	moving=false;
}
int main () {
	srand(time(NULL));
	printf("\033[?25l");
	init_pieces(); init_algb_table(); init_posv_table();
	for (int x=0;x<TR;x++) {
		for (int y=0;y<TR;y++) {
			printf("%d ",posv_table[x*TR+y]);
		}
		putchar('\n');
	}
	getch();
	printable(table,true);
   	while (true) {
    	switch (tolower(getch())) {
			case 'r':
				init_pieces();
				break;
			case 'x':
				printf("\033[?25h%s",CLRS);
				exit(1);
				break;
			case 'w':
				if (d_x>0) d_x--;
				break;
			case 'a':
				if (d_y>0) d_y--;
				break;
			case 's':
				if (d_x<7) d_x++;
				break;
			case 'd':
				if (d_y<7) d_y++;
				break;
			case 'e':
				char c_turn=(n_turn==0) ? 'B' : 'W';
				int o_sled=table[d_x*TR+d_y];
				if (!moving) {
					if (o_sled-n_turn<0 || o_sled==N_EMPTY) {
						break;
					} else {
				 		s_x=d_x; s_y=d_y;
						moving=true;
						break;
					}
				}
				int c_sled=table[s_x*TR+s_y];
				if (!is_valid(table,s_x,s_y,d_x,d_y,c_sled)) {ret();break;}
				int tmp_table[TS*SOI];
				copy_table(tmp_table,table);
				chg_pos(tmp_table,s_x,s_y,d_x,d_y);
				if (!is_king_safe(tmp_table)) {ret();break;}
				bool capture=(table[d_x*TR+d_y]==N_EMPTY) ? 0 : 1;
				chg_pos(table,s_x,s_y,d_x,d_y);
				int king_color=(n_turn==18) ? 0 : 18; //getting info to call
				int king_x,king_y;                    //check_mate properly
				for (int x=0;x<TR;x++) {
					for (int y=0;y<TR;y++) {
						if (table[x*TR+y]-king_color==2) {
							king_x=x,king_y=y;
							break;
						}
					}
				}
				int status=0;
				int _threats=king_threats_check(table,king_color,
								king_x,king_y);
				while (_threats>0 && _threats<=2) {
					status++; _threats--;
				}
				write_play(c_sled,s_x,s_y,d_x,d_y,capture,status,0);
				printable(table,true);
				finish_play();
				moving=false;
				break;
			}
		printable(table,true);
		//print_plays_regs();
		printf("\n(%d,%d)",d_x,d_y);
    }
    return 0;
}
