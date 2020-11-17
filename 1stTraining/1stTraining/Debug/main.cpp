#include <stdio.h>
#include <stdlib.h>

#define WIDTH   60 //行当たり表示バイト数
#define MASKCHR '.'//16進数表示で20～7E　以外の場合の表示用文字

void dump(char* filename/*入力ファイルのファイル名*/, long from/*表示を開始するバイト位置*/, long to/*表示を終了するバイト位置(値が負の場合はファイルの末尾)*/) {

	FILE* infile;//ファイル構造体のポインタを作成
	int chr, pos = 0;
	long cnt = 0;
	char tblC[256]/*キャラ型1行目の表示文字*/, bufC[WIDTH + 1];//行当たり表示バイト数+1のchar型の配列
	char tblH[256]/*ハイ　　2行目の表示文字*/, bufH[WIDTH + 1];//行当たり表示バイト数+1のchar型の配列
	char tblL[256]/*ロー　　3行目の表示文字*/, bufL[WIDTH + 1];//行当たり表示バイト数+1のchar型の配列
	char hex[] = "0123456789ABCDEF";//0123456789ABCDEFをchar型の配列に代入

	for (int num=0;num<256;num++)
	{
		tblC[num] = ' ';
		tblH[num] = ' ';
		tblL[num] = ' ';
	}
	for (int num = 0; num < WIDTH+1; num++)
	{
		bufC[num] = ' ';
		bufH[num] = ' ';
		bufL[num] = ' ';
	}

	//chrに初期値として16進数の0を入れる。chrが16進数のFF以下の間繰り返す。chrを1づつ増やす
	for (chr = 0x00; chr <= 0xFF; chr++) {
		if ((0x20 <= chr) && (chr <= 0x7E))//chrが16進数の20以上かつchrが16進数の7E以下である
		{
			tblC[chr] = chr;//tblC[ ]のchr番目にchrを代入
		}
		else//chrが16進数の20以上かつchrが16進数の7E以下ではない
		{
			tblC[chr] = MASKCHR;//tblC[ ]のchr番目に16進数表示で20～7E　以外の場合の表示用文字 MASKCHR を代入
		}
		tblH[chr] = hex[chr >> 4];//tblH[ ]のchr番目にhex[]のchrを4つ右シフトしたもの番目を代入
		tblL[chr] = hex[chr & 0x0F];//tblL[]のchr番目にhex[]のchrを16進数の0fでビットANDしたもの番目を代入
	}
	bufC[WIDTH] = bufH[WIDTH] = bufL[WIDTH] = '\0';//bufC[ ],bufH[ ],bufL[ ]の最後にnullを入れる
	infile = fopen(filename, "rb");//ポインタにバイナリファイルを読み取り代入、ファイルがないときエラー

	//chrに代入したinfileの文字がファイルの最後ではない かつ 表示を終了するバイト位置ではない 間続ける
	while (((chr = fgetc(infile)/*infileから一文字読み込みintで返す*/) != EOF) && ((to < 0) || (cnt <= to))) {
		
		cnt++;//cntをインクリメント
		if (cnt > from) {//表示を開始するバイト位置よりcntが大きい
			bufC[pos] = bufC[chr];//bufC[]のpos番目に bufC[]のchr番目を代入
			bufH[pos] = bufH[chr];//bufH[]のpos番目に bufH[]のchr番目を代入
			bufL[pos] = bufL[chr];//bufL[]のpos番目に bufL[]のchr番目を代入
			pos++;//posをインクリメント
			if (pos == WIDTH) {//posが行当たり表示バイト数と一致
				printf("%10ld %s \n %12s %s \n %12s %s \n \n ", cnt - WIDTH, bufC, " ", bufH, " ", bufL);
				//書き出し long型cnt - WIDTHを10進で10文字空けて出力　文字列 bufC を出力 改行　文字列 " " を12文字空けて出力 文字列 bufH を出力　文字列 " " を12文字空けて出力 文字列 bufL を出力 改行 改行
				pos = 0;//posを0に
			}

		}
	}
	if (pos > 0) {//posが0より大きい
		bufC[pos] = bufH[pos] = bufL[pos] = '\n';//bufC[ ],bufH[ ],bufL[ ]のposに'\n'を入れる
		printf("%10ld %s \n %12s %s \n %12s %s \n \n ", cnt - pos, bufC, " ", bufH, " ", bufL);
		//書き出し long型cnt - posを10進で10文字空けて出力　文字列 bufC を出力 改行　文字列 " " を12文字空けて出力 文字列 bufH を出力　文字列 " " を12文字空けて出力 文字列 bufL を出力 改行 改行
	}
	if (chr == EOF) //chrがEOFと一致
	{
		printf("END OF DATA...%ld byte(s)\n", cnt - from);
		//書き出し END OF DATA...long型cnt - 表示を開始するバイト位置 バイト数 改行
	}
	else 
	{
		printf("END OF DUMP...%ld byte(s)\n", cnt - from);
		//書き出し END OF DATA...long型cnt - 表示を開始するバイト位置 バイト数 改行
	}
		
	fclose(infile);//ファイルを閉じる

}

int main() {
	/*for testing bump()*/
	char fname[] = "main.cpp";

	dump(fname/*入力ファイルのファイル名*/, 0L/*表示を開始するバイト位置*/, -1L/*表示を終了するバイト位置(値が負の場合はファイルの末尾)*/);
	dump(fname/*入力ファイルのファイル名*/, 17L/*表示を開始するバイト位置*/, 40L/*表示を終了するバイト位置(値が負の場合はファイルの末尾)*/);
}
