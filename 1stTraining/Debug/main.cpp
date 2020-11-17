#include <stdio.h>
#include <stdlib.h>

#define WIDTH   60 //行当たり表示バイト数
#define MASKCHR '.'//16進数表示で20～7E　以外の場合の表示用文字

void dump(char* filename, long from, long to) {

	FILE* infile;
	int chr, pos = 0;
	long cnt = 0;
	char tblC[256], bufC[WIDTH + 1];
	char tblH[256], bufH[WIDTH + 1];
	char tblL[256], bufL[WIDTH + 1];
	char hex[] = "0123456789ABCDEF";

	for (chr = 0x00; chr <= 0xFF; chr++) {
		if ((0x20 <= chr) && (chr <= 0x7E))
			tblC[chr] = chr;
		else
			tblC[chr] = MASKCHR;
		tblH[chr] = hex[chr >> 4];
		tblL[chr] = hex[chr & 0x0F];
	}
	bufC[WIDTH] = bufH[WIDTH] = bufL[WIDTH] = '\0';
	infile = fopen(filename, "rb");
	while (((chr = fgetc(infile)) != EOF) && ((to < 0) || (cnt <= to))) {
		cnt++;
		if (cnt > from) {
			bufC[pos] = bufC[chr];
			bufH[pos] = bufH[chr];
			bufH[pos] = bufH[chr];
			pos++;
			if (pos == WIDTH) {
				printf("%10ld %s\n%12s%s\n%12s%s\n\n", cnt - WIDTH, bufC, " ", bufH, " ", bufL);
				pos = 0;
			}

		}
	}
	if (pos > 0) {
		bufC[pos] = bufH[pos] = bufL[pos] = '\n';
		printf("%10ld %s\n%12s%s\n%12s%s\n\n", cnt - pos, bufC, " ", bufH, " ", bufL);

	}
	if (chr == EOF)
		printf("END OF DATA...%ld byte(s)\n", cnt - from);
	else
		printf("END OF DUMP...%ld byte(s)\n", cnt - from);
	fclose(infile);

}

int main() {
	/*for testing bump()*/
	char fname[] = "main.cpp";

	dump(fname, 0L, -1L);
	dump(fname, 17L, 40L);
}
