#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

/// <summary>
/// ���Ԍo�߂�ݒ肷��
/// </summary>
/// <param name="i">�o�ߎ���(�b)</param>
void interval(double i)
{
	clock_t g;
	g = i * CLOCKS_PER_SEC + clock();
	while (g > clock());
}