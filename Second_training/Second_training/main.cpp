#include <stdio.h>
#include <stdlib.h>

#define ROWNUM 26	/*座席の列数*/
#define CLSNUM  5	/*座席種別数*/

//構造体の宣言
typedef struct {
	char seat_class;	/*座席種別*/
	int  reserved;		/*予約状態*/
}SEAT;
typedef struct {
	char seat_row;	/*座席の列名*/
	int  seat_no;		/*座席の番*/
}POSITION;

static char row_s[] = "ABCDEFGHIJKMNOPQRSTUVWXYZ";
static char class_s[CLSNUM] = "SABC";

void check_service(char, int, SEAT* [ROWNUM], int);
void check_seats(char, int, SEAT* [ROWNUM], POSITION*);	/*関数chek_seats(座席確認)のプロトタイプ宣言*/
void print_seats(char, int,  POSITION*);

void main() {
	check_service('A', 2, SEAT, POSITION);
}

//座席確認の関数
//Class 希望の座席種別 num 希望座席数 hall 座席表 pos 確認結果
void check_seats(char Class,int num,SEAT *hall[ROWNUM],POSITION *pos) {
	int cnt, found = 0, no, row;
	//row 座席の列名
	for (row = 0; row < ROWNUM; row++) {
		cnt = 0;
		for (no = 0; hall[row][no].seat_class != '\0'; no++) {
			if ((hall[row][no].seat_class == Class) && (hall[row][no].reserved == 0)) {
				if (++cnt >= num) {
					found = 1;
						break;
				}
			}
			else {
				cnt = 0;
			}
		}
		if (found != 0) {
			break;
		}
	}
	if (found != 0) {
		pos->seat_row = row_s[row];
		pos->seat_no  = row_s[row + 1];
	}
	else {
		pos->seat_row = '\0';
	}
}

void check_service(char Class, int num, SEAT* hall[ROWNUM], int opt) {
	int i;
	char c;
	POSITION pos;

	check_seats(Class, num, hall, &pos);
	print_seats(Class, num,  &pos);
	if (pos.seat_row=='\0') {
		for (i = 0; i < CLSNUM; i++) {
			if (opt == 0) {
				c = class_s[i];
			}
			else {
				c = class_s[CLSNUM-i-1];
			}
			if (Class != c) {
				check_seats(Class, num, hall, &pos);
				print_seats(Class, num, &pos);
			}
		}
	}

}

void  print_seats(char Class, int num, POSITION* pos) {

}