#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "header.h"
#include "control.c"
#include "water.c"
#include "deg.c"

#define MINDEG 10
#define TARGETDEG_98 98
#define LACKWATER 0
#define COUNTRESET 0
#define ROW_MAX_NUMBER 21
#define COLUMN_NUMBER 80
#define LOCK_ON 0
#define LOCK_OFF 1
#define DISP_LOCKON "�b�@�@�[�[�[�@�@�@�@�@�[�[�[�[�[�[�[�@�@�@�@�b�@�Z�@�b�@�@�b\n"
#define DISP_LOCKOFF "�b�@�@�[�[�[�@�@�@�@�@�[�[�[�[�[�[�[�@�@�@�@�b�@\x1b[31m��\x1b[39m�@�b�@�@�b\n"


int nowDeg = MINDEG;
int targetDeg = TARGETDEG_98;
int nowWater = LACKWATER;
int keepDegFlag = COUNTRESET;
int lock = LOCK_ON;

// ������ʕ\��

char display[ROW_MAX_NUMBER][COLUMN_NUMBER] = {
	" �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n",   // 0
	"�b�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�b\n",  // 1
	"�b�@�@�[�[�[�@�@�@�@�@�[�[�[�[�[�[�[�@�@�@�@�@�[�[�[�@�@�@�b\n",  // 2
	"�b�@�b�@�@�@�b�@�@�@�b�@�@���@�x�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n",  // 3
	"�b�@�b���@�M�b�@�@�@�b�@�@�@�@�@�@�@�b�@�@�@�b���@���b�@�@�b\n",  // 4
	"�b�@�b�@�@�@�b�@�@�@�b�@�@ \x1b[31m- - -\x1b[39m�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n",  // 5
	"�b�@�@�[�[�[�@�@    �b�@�@�@�@�@�@�@�b�@�@�@�@�[�[�[�@�@�@�b\n",  // 6
	"�b�@�@���͂g�@�@�@�@�b���M�@�@�@�ۉ��b�@�@�@�@���͂`�@�@�@�b\n",  // 7
	"�b�@�@�@�@�@�@�@�@�@�b�@�Z�@�@�@�@�Z�b�@�@�@�@�@�@�@�@�@�@�b\n",  // 8
	"�b�@�@�[�[�[�@�@�@�@�b�@�@�@�@�@�@�@�b�@�@�@�@�[�[�[�@�@�@�b\n",  // 9
	"�b�@�b�ہ@���b�@�@�@�b�@98�@90�@70�@�b�@�@�@�b���b�N�b�@�@�b\n",  // 10
	"�b�@�b���@�x�b�@�@�@�b�@\x1b[31m��\x1b[39m�@�Z�@�Z�@�b�@�@�@�b���@���b�@�@�b\n",  // 11
	"�b�@�b�ρ@�X�b�@�@�@�b�@�@�@�@�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n",  // 12
	"�b�@�@�[�[�[�@�@�@�@�@�[�[�[�[�[�[�[�@�@�@�@�b�@�Z�@�b�@�@�b\n",  // 13
	"�b�@�@���͂s�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�b�@�@�@�b�@�@�b\n",  // 14
	"�b�@�@�@�@�@�@�@�@�@�@���@�@�@�@�@�@�@�@�@�@�@�[�[�[�@�@�@�b\n",  // 15
	"�b�@�@�[�[�[�@�@���ʁF���������������������@�@���͂k�@�@�@�b\n",  // 16
	"�b�@�b���@���b�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�b\n",  // 17
	"�b�@�@�[�[�[�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�b\n",  // 18
	"�b�@�@���͂v�@�@�@�@�@�@�@�@�@�@�@�y�A�v���I���@���́F�p�z�b\n",  // 19
	" �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n"    // 20
};

int main(void)
{
	changeDisplay();
	printf("�����|�b�g�A�v���J�n");
	Sleep(2000);

	while(1) {
		
		// �������[�h(�����������)
		if (nowWater == LACKWATER && nowDeg == MINDEG) {
			addWater();
		}

		// ���M���[�h(��������A�ۉ����x�ȉ��̏��)
		if (nowWater > LACKWATER && nowDeg < targetDeg) {
			raiseDeg();
		}

		// ��������A�����������Ă�����
		if (nowWater > LACKWATER && nowDeg >= targetDeg) {
			if(lock == LOCK_ON){
				// �ۉ����[�h(���b�N������)
				keepDeg();
			}
			else {
				// �������[�h(���b�N�����ς�)
				drainWater();
			}
		}

	}

	return 0;
}