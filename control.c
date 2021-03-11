#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

/// <summary>
/// ŠÔŒo‰ß‚ğİ’è‚·‚é
/// </summary>
/// <param name="i">Œo‰ßŠÔ(•b)</param>
void interval(double i)
{
	clock_t g;
	g = i * CLOCKS_PER_SEC + clock();
	while (g > clock());
}