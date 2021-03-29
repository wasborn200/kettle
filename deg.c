#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define DEG_5 5
#define MINDEG 10
#define TARGETDEG_98 98
#define TARGETDEG_90 90
#define TARGETDEG_70 70
#define ROW_DISPLAYDEG_NUMBER 5
#define ROW_TARGETDEG_NUMBER 11
#define ROW_STATUS_NUMBER 8
#define DISP_TARGETDEG_98 "�b�@�b���@�x�b�@�@�@�b�@\x1b[31m��\x1b[39m�@�Z�@�Z�@�b�@�@�@�b���@���b�@�@�b\n"
#define DISP_TARGETDEG_90 "�b�@�b���@�x�b�@�@�@�b�@�Z�@\x1b[31m��\x1b[39m�@�Z�@�b�@�@�@�b���@���b�@�@�b\n"
#define DISP_TARGETDEG_70 "�b�@�b���@�x�b�@�@�@�b�@�Z�@�Z�@\x1b[31m��\x1b[39m�@�b�@�@�@�b���@���b�@�@�b\n"
#define DISP_STATUS_HEATINGDEG "�b�@�@�@�@�@�@�@�@�@�b�@\x1b[31m��\x1b[39m�@�@�@�@�Z�b�@�@�@�@�@�@�@�@�@�@�b\n"
#define DISP_STATUS_KEEPINGDEG "�b�@�@�@�@�@�@�@�@�@�b�@�Z�@�@�@�@\x1b[31m��\x1b[39m�b�@�@�@�@�@�@�@�@�@�@�b\n"
#define DISP_DEG_BEFORE "�b�@�b�@�@�@�b�@�@�@�b�@�@ \x1b[31m\0"
#define DISP_DEG_AFTER "\x1b[39m�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n\0"
#define COUNTRESET 0

extern int nowDeg;
extern int targetDeg;

/// <summary>
/// �ۉ����x�܂Ő������M������
/// </summary>
void raiseDeg() {
	int diffDeg;
	int raiseDegCount = COUNTRESET;

	messageReset();
	printf("\r���M���J�n���܂��B");
	Sleep(2000);

	strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_HEATINGDEG);

	// 0.5�b����10�x�����M����
	while (nowDeg < targetDeg) {

		// h���́F�ۉ����x�ύX
		// q���́F�A�v���I��
		if (GetKeyState('T') & 0x8000) {
			changeTargetDeg();
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		Sleep(100);
		raiseDegCount++;

		// 0.5�b���ɉ��x��5�x�㏸������
		if (raiseDegCount == DEG_5) {
			if ((diffDeg = targetDeg - nowDeg) <= DEG_5) {
				nowDeg += diffDeg;
			}
			else {
				nowDeg += DEG_5;
			}
			reflectDeg();
			changeDisplay();
			raiseDegCount = COUNTRESET;
			printf("\r���M��");
		}
		
	}

	strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_KEEPINGDEG);
	changeDisplay();
	printf("\r�����������܂����B");
	Sleep(2000);
}

keepDeg(int* loc) {
	int dropDegCount = COUNTRESET;

	do {
		printf("\r�ۉ����B��������ꍇ�̓��b�N���������Ă�������(���͂k)�B");

		// r���́F���b�N���������ꂽ�Ƃ��̏���
		// h���́F�ۉ����x�ύX
		// q���́F�A�v���I��
		if (GetKeyState('L') & 0x8000) {
			lockOff(loc);
			break;
		}
		else if (GetKeyState('T') & 0x8000) {
			changeTargetDeg();
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		// 2�b���ɉ��x���P��������
		Sleep(50);
		dropDegCount++;
		if (dropDegCount == 40) {
			downDeg();
			dropDegCount = COUNTRESET;
		}


	} while (nowDeg >= targetDeg);
}

/// <summary>
/// ���Ԍo�߂ɂ�艷�x������������i�ۉ��ݒ艷�x�ȉ��ɂ͂Ȃ�Ȃ��j
/// </summary>
void downDeg() {

	if (nowDeg > targetDeg) {
		nowDeg--;
		reflectDeg();
		changeDisplay();
	}
}


/// <summary>
/// ���x�\��������ύX����
/// </summary>
void reflectDeg() {
	char deg[20];
	char temp[20];

	strcpy(display[ROW_DISPLAYDEG_NUMBER], "");

	// ���݂̉��x�𕶎��ɂ��āA�ԂɃX�y�[�X������
	// �Œቷ�x�̎���'-'�ŕ\������
	sprintf(temp, "%3d", nowDeg);
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		if (i % 2 == 0) {
			if (nowDeg == MINDEG)
			{
				deg[i] = '-';
			}
			else {
				deg[i] = temp[j];
			}
			j++;
		}
		else {
			deg[i] = ' ';
		}
	}
	deg[5] = '\0';

	strcat(display[ROW_DISPLAYDEG_NUMBER], DISP_DEG_BEFORE);
	strcat(display[ROW_DISPLAYDEG_NUMBER], deg);
	strcat(display[ROW_DISPLAYDEG_NUMBER], DISP_DEG_AFTER);
}

/// <summary>
/// �ۉ����x��ύX����
/// </summary>
void changeTargetDeg() {
	
	static int keepDegFlag = COUNTRESET;

	// �ۉ����x��98��90��70�̏��Ń��[�v����
	if (keepDegFlag != 2) {
		keepDegFlag++;
	}
	else {
		keepDegFlag = 0;
	}

	switch (keepDegFlag) {
	case 0:
		targetDeg = TARGETDEG_98;
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_98);
		break;
	case 1:
		targetDeg = TARGETDEG_90;
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_90);
		break;
	case 2:
		targetDeg = TARGETDEG_70;
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_70);
		break;
	}
	changeDisplay();
	Sleep(500);
}