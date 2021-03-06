#include <stdio.h>
#include <stdlib.h>

#define ROWNUM 26	/*ΐΘΜρ*/
#define CLSNUM  5	/*ΐΘνΚ*/

//\’ΜΜιΎ
typedef struct {
	char seat_class;	/*ΐΘνΚ*/
	int  reserved;		/*\ρσΤ*/
}SEAT;
typedef struct {
	char seat_row;	/*ΐΘΜρΌ*/
	int  seat_no;		/*ΐΘΜΤ*/
}POSITION;

static char row_s[] = "ABCDEFGHIJKMNOPQRSTUVWXYZ";
static char class_s[CLSNUM] = "SABC";

void check_service(char, int, SEAT* [ROWNUM], int);
void check_seats(char, int, SEAT* [ROWNUM], POSITION*);	/*Φchek_seats(ΐΘmF)Μvg^CvιΎ*/
void print_seats(char, int,  POSITION*);

void main() {
	check_service('A', 2, SEAT, POSITION);
}

//ΐΘmFΜΦ
//Class σ]ΜΐΘνΚ num σ]ΐΘ hall ΐΘ\ pos mFΚ
void check_seats(char Class,int num,SEAT *hall[ROWNUM],POSITION *pos) {
	int cnt, found = 0, no, row;
	//row ΐΘΜρΌ
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