#include <stdio.h>
#include <stdlib.h>

#define WIDTH   60 //�s������\���o�C�g��
#define MASKCHR '.'//16�i���\����20�`7E�@�ȊO�̏ꍇ�̕\���p����

void dump(char* filename/*���̓t�@�C���̃t�@�C����*/, long from/*�\�����J�n����o�C�g�ʒu*/, long to/*�\�����I������o�C�g�ʒu(�l�����̏ꍇ�̓t�@�C���̖���)*/) {

	FILE* infile;//�t�@�C���\���̂̃|�C���^���쐬
	int chr, pos = 0;
	long cnt = 0;
	char tblC[256]/*�L�����^1�s�ڂ̕\������*/, bufC[WIDTH + 1];//�s������\���o�C�g��+1��char�^�̔z��
	char tblH[256]/*�n�C�@�@2�s�ڂ̕\������*/, bufH[WIDTH + 1];//�s������\���o�C�g��+1��char�^�̔z��
	char tblL[256]/*���[�@�@3�s�ڂ̕\������*/, bufL[WIDTH + 1];//�s������\���o�C�g��+1��char�^�̔z��
	char hex[] = "0123456789ABCDEF";//0123456789ABCDEF��char�^�̔z��ɑ��

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

	//chr�ɏ����l�Ƃ���16�i����0������Bchr��16�i����FF�ȉ��̊ԌJ��Ԃ��Bchr��1�Â��₷
	for (chr = 0x00; chr <= 0xFF; chr++) {
		if ((0x20 <= chr) && (chr <= 0x7E))//chr��16�i����20�ȏォ��chr��16�i����7E�ȉ��ł���
		{
			tblC[chr] = chr;//tblC[ ]��chr�Ԗڂ�chr����
		}
		else//chr��16�i����20�ȏォ��chr��16�i����7E�ȉ��ł͂Ȃ�
		{
			tblC[chr] = MASKCHR;//tblC[ ]��chr�Ԗڂ�16�i���\����20�`7E�@�ȊO�̏ꍇ�̕\���p���� MASKCHR ����
		}
		tblH[chr] = hex[chr >> 4];//tblH[ ]��chr�Ԗڂ�hex[]��chr��4�E�V�t�g�������̔Ԗڂ���
		tblL[chr] = hex[chr & 0x0F];//tblL[]��chr�Ԗڂ�hex[]��chr��16�i����0f�Ńr�b�gAND�������̔Ԗڂ���
	}
	bufC[WIDTH] = bufH[WIDTH] = bufL[WIDTH] = '\0';//bufC[ ],bufH[ ],bufL[ ]�̍Ō��null������
	infile = fopen(filename, "rb");//�|�C���^�Ƀo�C�i���t�@�C����ǂݎ�����A�t�@�C�����Ȃ��Ƃ��G���[

	//chr�ɑ������infile�̕������t�@�C���̍Ō�ł͂Ȃ� ���� �\�����I������o�C�g�ʒu�ł͂Ȃ� �ԑ�����
	while (((chr = fgetc(infile)/*infile����ꕶ���ǂݍ���int�ŕԂ�*/) != EOF) && ((to < 0) || (cnt <= to))) {
		
		cnt++;//cnt���C���N�������g
		if (cnt > from) {//�\�����J�n����o�C�g�ʒu���cnt���傫��
			bufC[pos] = bufC[chr];//bufC[]��pos�Ԗڂ� bufC[]��chr�Ԗڂ���
			bufH[pos] = bufH[chr];//bufH[]��pos�Ԗڂ� bufH[]��chr�Ԗڂ���
			bufL[pos] = bufL[chr];//bufL[]��pos�Ԗڂ� bufL[]��chr�Ԗڂ���
			pos++;//pos���C���N�������g
			if (pos == WIDTH) {//pos���s������\���o�C�g���ƈ�v
				printf("%10ld %s \n %12s %s \n %12s %s \n \n ", cnt - WIDTH, bufC, " ", bufH, " ", bufL);
				//�����o�� long�^cnt - WIDTH��10�i��10�����󂯂ďo�́@������ bufC ���o�� ���s�@������ " " ��12�����󂯂ďo�� ������ bufH ���o�́@������ " " ��12�����󂯂ďo�� ������ bufL ���o�� ���s ���s
				pos = 0;//pos��0��
			}

		}
	}
	if (pos > 0) {//pos��0���傫��
		bufC[pos] = bufH[pos] = bufL[pos] = '\n';//bufC[ ],bufH[ ],bufL[ ]��pos��'\n'������
		printf("%10ld %s \n %12s %s \n %12s %s \n \n ", cnt - pos, bufC, " ", bufH, " ", bufL);
		//�����o�� long�^cnt - pos��10�i��10�����󂯂ďo�́@������ bufC ���o�� ���s�@������ " " ��12�����󂯂ďo�� ������ bufH ���o�́@������ " " ��12�����󂯂ďo�� ������ bufL ���o�� ���s ���s
	}
	if (chr == EOF) //chr��EOF�ƈ�v
	{
		printf("END OF DATA...%ld byte(s)\n", cnt - from);
		//�����o�� END OF DATA...long�^cnt - �\�����J�n����o�C�g�ʒu �o�C�g�� ���s
	}
	else 
	{
		printf("END OF DUMP...%ld byte(s)\n", cnt - from);
		//�����o�� END OF DATA...long�^cnt - �\�����J�n����o�C�g�ʒu �o�C�g�� ���s
	}
		
	fclose(infile);//�t�@�C�������

}

int main() {
	/*for testing bump()*/
	char fname[] = "main.cpp";

	dump(fname/*���̓t�@�C���̃t�@�C����*/, 0L/*�\�����J�n����o�C�g�ʒu*/, -1L/*�\�����I������o�C�g�ʒu(�l�����̏ꍇ�̓t�@�C���̖���)*/);
	dump(fname/*���̓t�@�C���̃t�@�C����*/, 17L/*�\�����J�n����o�C�g�ʒu*/, 40L/*�\�����I������o�C�g�ʒu(�l�����̏ꍇ�̓t�@�C���̖���)*/);
}
