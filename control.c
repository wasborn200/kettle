#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

extern char str[13][80];

/// <summary>
/// ��ʕ\���̃��Z�b�g�y�эĕ\��
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < 13; i++)
	{
		printf(str[i]);
	}
}

/// <summary>
/// ���b�Z�[�W�̃��Z�b�g
/// </summary>
void messageReset() {
	printf("\r�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
}



/// <summary>
/// ���Ԍo�߂�ݒ肷��
/// </summary>
/// <param name="i">�o�ߎ���(�b)</param>
//void interval(double i)
//{
//	clock_t g;
//	g = i * CLOCKS_PER_SEC + clock();
//	while (g > clock());
//}
