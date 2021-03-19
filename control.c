#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define LINE_LOCK_NUMBER 6
#define LINE_MAX_NUMBER 18
#define COLUMN_NUMBER 80
#define DISP_LOCKON "�b�@�b�@�Z�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n"
#define DISP_LOCKOFF "�b�@�b�@\x1b[31m��\x1b[39m�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n"

extern char display[LINE_MAX_NUMBER][COLUMN_NUMBER];

/// <summary>
/// ��ʕ\���̃��Z�b�g�y�эĕ\��
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < LINE_MAX_NUMBER; i++)
	{
		printf(display[i]);
	}
}

/// <summary>
/// ���b�Z�[�W�̃��Z�b�g
/// </summary>
void messageReset() {
	printf("\r�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
}

void lockOn() {
	strcpy(display[LINE_LOCK_NUMBER], DISP_LOCKON);
	changeDisplay();
	printf("\r���������b�N����܂����B");
	Sleep(1000);
}

void lockOff() {
	strcpy(display[LINE_LOCK_NUMBER], DISP_LOCKOFF);
	changeDisplay();
	printf("\r�������b�N����������܂����B");
	Sleep(1000);
}