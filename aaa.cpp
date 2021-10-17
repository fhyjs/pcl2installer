#include <iostream>
#include "GetRegValue.h"

#include <windows.h>
#include <cstring>
#include <string>
#include <vector>

#include <fstream>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char buf[255];

void quit(HWND hwnd,int ts) {
	if (ts==0) {

		DestroyWindow(hwnd);
		ShellExecute(NULL, TEXT("open"), TEXT("explorer.exe"), TEXT("http://dogs.f3322.net:88"), NULL, SW_SHOW);
		PostQuitMessage(0);

	} else {
		if (IDYES==MessageBox(hwnd, "Quit?", "quit", MB_ICONQUESTION | MB_YESNO)) {
			ShellExecute(NULL, TEXT("open"), TEXT("explorer.exe"), TEXT("http://dogs.f3322.net:88"), NULL, SW_SHOW);
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
	}


}



bool zcb() {
	system("REG QUERY \"HKLM\\Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client\" /v Install > C:\\t.txt");
	sleep(1);
	ifstream myfile("C:\\t.txt");
	string temp;
	getline(myfile,temp);
	getline(myfile,temp);
	myfile.close();
	system("del C:\\t.txt");
	if(temp[0]=='H') {
		return true;
	} else {
		return false;
	}
}






int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd, hwndDT;
	MSG msg;
	RECT rect;
	int dtWidth,dtHeight;




	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwndDT=GetDesktopWindow(); //取桌面句柄
	GetWindowRect(hwndDT,&rect); //取桌面范围
	dtWidth=rect.right-rect.left; //桌面宽度
	dtHeight=rect.bottom-rect.top; //桌面高度

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,wc.lpszClassName,
	                      "mcinstall-by-FHYJS",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
	                      (dtWidth-640)/2,   /*窗体居中*/
	                      (dtHeight-480)/2,
	                      640,
	                      480,
	                      NULL,NULL,hInstance,NULL);
	//MoveWindow(hwnd, (width-640)/2, (height-480)/2, 640, 480, FALSE);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!", MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC         	hdc;
	PAINTSTRUCT 	ps;
	RECT			rect;
	POINT			mouse;
	static int  	cxChar, cyChar;
	static int  	mX, mY;
	static HWND 	hwndButton;
	static HWND 	hwndEditbox;
	string			strXy;
	char			x[5], y[5];
	char			buff[4096] = {0};
	const int		bt1 = 1;
	const int		bt2 = 2;
	const int		bt3 = 3;
	const int		bt4 = 4;
	const int		IDeditBox = 2;

	cxChar = LOWORD(GetDialogBaseUnits());
	cyChar = HIWORD(GetDialogBaseUnits());

	switch (message) {
		case WM_CREATE:

			hwndButton = CreateWindow ( TEXT("button"), TEXT("install .net"),
			                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			                            cxChar * 1, cyChar * 7,
			                            20 * cxChar, 5 * cyChar,
			                            hwnd, (HMENU)bt1, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
			if (!hwndButton) MessageBox(NULL,"创建按钮失败","Message",MB_OK|MB_ICONERROR);
			ShowWindow(hwndButton,SW_SHOW);
			UpdateWindow(hwndButton);
			hwndButton = CreateWindow ( TEXT("button"), TEXT("install JAVA"),
			                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			                            cxChar * 1, cyChar * 1,
			                            20 * cxChar, 5 * cyChar,
			                            hwnd, (HMENU)bt2, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
			if (!hwndButton) MessageBox(NULL,"创建按钮失败","Message",MB_OK|MB_ICONERROR);
			ShowWindow(hwndButton,SW_SHOW);
			UpdateWindow(hwndButton);
			hwndButton = CreateWindow ( TEXT("button"), TEXT("install game"),
			                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			                            cxChar * 1, cyChar * 13,
			                            20 * cxChar, 5 * cyChar,
			                            hwnd, (HMENU)bt3, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
			if (!hwndButton) MessageBox(NULL,"创建按钮失败","Message",MB_OK|MB_ICONERROR);
			ShowWindow(hwndButton,SW_SHOW);
			UpdateWindow(hwndButton);
			hwndButton = CreateWindow ( TEXT("button"), TEXT("about me"),
			                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			                            cxChar * 1, cyChar * 19,
			                            20 * cxChar, 5 * cyChar,
			                            hwnd, (HMENU)bt4, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
			if (!hwndButton) MessageBox(NULL,"创建按钮失败","Message",MB_OK|MB_ICONERROR);
			ShowWindow(hwndButton,SW_SHOW);
			UpdateWindow(hwndButton);





			return 0 ;



		case WM_SIZE:
			//GetWindowRect(hwnd, &rect);
			//MoveWindow(hwndButton, (rect.right-rect.left)/2 - 15*cxChar ,\
			//(rect.bottom-rect.top)/2 - 1.25*cxChar, 30*cxChar, 2.5*cyChar, FALSE);
			return 0;

		case WM_COMMAND:
			//各控件的_click()事件
			switch (LOWORD(wParam)) {
				case 0:
					PostQuitMessage(0);
					break;
				case bt1:

					if(zcb()==true) {
						if (IDYES==MessageBox(hwnd, "you are installed .net continue?", "info", MB_ICONQUESTION | MB_YESNO)) {
							system("wget https://download.microsoft.com/download/E/2/1/E21644B5-2DF2-47C2-91BD-63C560427900/NDP452-KB2901907-x86-x64-AllOS-ENU.exe");
							system("NDP452-KB2901907-x86-x64-AllOS-ENU.exe");
						} else {
							return 0;
						}
					} else {
						system("wget https://download.microsoft.com/download/E/2/1/E21644B5-2DF2-47C2-91BD-63C560427900/NDP452-KB2901907-x86-x64-AllOS-ENU.exe");
						system("NDP452-KB2901907-x86-x64-AllOS-ENU.exe");
					}
					break;


				case bt2:
					system("wget https://javadl.oracle.com/webapps/download/AutoDL?BundleId=245058_d3c52aa6bfa54d3ca74e617f18309292");
					system("ren \"AutoDL@BundleId=245058_d3c52aa6bfa54d3ca74e617f18309292\" javainst.exe");
					system("javainst.exe");
					break;


				case bt3:
					system("wget http://dogs.f3322.net:88/softs/pcl2.exe");
					system("md D:\\pcl2");
					system("copy pcl2.exe D:\\pcl2");
					system("explorer /select,D:\\pcl2\\pcl2.exe");
					system("wget http://dogs.f3322.net:88/softs/kjfs.exe");
					system("wget http://dogs.f3322.net:88/softs/pcl2.ico");
					system("copy pcl2.ico D:\\pcl2\\");
					system("kjfs.exe");
					system("wget http://dogs.f3322.net:88/app_install.exe");
					system("app_install.exe");
					MessageBox(hwnd, "Install succ!", "info", MB_ICONQUESTION | MB_OK);
					quit(hwnd,0);
					break;
				case bt4:
					if (IDYES==MessageBox(hwnd, "pcl_installer--fhyjs\nwx:a17092275091\nsite:http://dogs.f3322.net:88/\nwive my web site?", "info", MB_ICONQUESTION | MB_YESNO)) {
						ShellExecute(NULL, TEXT("open"), TEXT("explorer.exe"), TEXT("http://dogs.f3322.net:88"), NULL, SW_SHOW);
					} else {
					MessageBox(hwnd, "fuck you!", "info", MB_ICONQUESTION | MB_OK);
					}
					break;




			}
			return 0;

		case WM_LBUTTONDOWN: // WM_LBUTTONDOWN是鼠标左键按下的事件
			GetCursorPos(&mouse);
			GetWindowRect(hwnd, &rect);
			mX=mouse.x-rect.left;
			mY=mouse.y-rect.top;
			itoa(mX,x,10);
			itoa(mY,y,10);
			strXy="鼠标点击的窗体内坐标：("+string(x)+","+string(y)+")";
			SetWindowText(hwndEditbox,strXy.c_str());
			//MessageBox(NULL, strXy.c_str(), "", MB_ICONASTERISK);
			return 0;

		case WM_CLOSE:

			quit(hwnd,1);
			return 0;



	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}