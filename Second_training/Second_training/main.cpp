#include <stdio.h>
#include <stdlib.h>

#define ROWNUM 26	/*���Ȃ̗�*/
#define CLSNUM  5	/*���Ȏ�ʐ�*/

//�\���̂̐錾
typedef struct {
	char seat_class;	/*���Ȏ��*/
	int  reserved;		/*�\����*/
}SEAT;
typedef struct {
	char seat_row;	/*���Ȃ̗�*/
	int  seat_no;		/*���Ȃ̔�*/
}POSITION;

static char row_s[] = "ABCDEFGHIJKMNOPQRSTUVWXYZ";
static char class_s[CLSNUM] = "SABC";

void check_service(char, int, SEAT* [ROWNUM], int);
void check_seats(char, int, SEAT* [ROWNUM], POSITION*);	/*�֐�chek_seats(���Ȋm�F)�̃v���g�^�C�v�錾*/
void print_seats(char, int,  POSITION*);

void main() {
	check_service('A', 2, SEAT, POSITION);
}

//���Ȋm�F�̊֐�
//Class ��]�̍��Ȏ�� num ��]���Ȑ� hall ���ȕ\ pos �m�F����
void check_seats(char Class,int num,SEAT *hall[ROWNUM],POSITION *pos) {
	int cnt, found = 0, no, row;
	//row ���Ȃ̗�
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