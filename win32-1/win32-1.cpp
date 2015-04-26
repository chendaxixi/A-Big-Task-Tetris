/*
* Copyright 2014.215B������
* All rights reserved.
*
* �ļ����ƣ�win32-1.cpp
* ժ	Ҫ������˹����
*
* ��ǰ�汾��1.0
* ��	��: chendaxixi/���ٱ�
* ������ڣ�2014��1��10��
*
* ȡ���汾��1.0
* ԭ����  ��chendaxixi/���ٱ�
* ������ڣ�2014��1��10��
*/
// win32-1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MAX_LOADSTRING 100
#define GRID 30           // ����߳�
#define nGameWidth 15     // ��������
#define nGameHeight 20    // ��������
#define nWidth 24         // ���ڿ�
#define nHeight 22        // ���ڸ�

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

RECT workRegion;        // ����������
bool autoFlag = false;  // true��ʾ�Զ�ģʽ��false��ʾ�ֶ�ģʽ

int flag[nGameWidth + 2][nGameHeight + 1];	//	��¼�������ķ���
int now, next;	//now,next�ֱ��ʾ��ǰ���顢��һ�����������
int sum, sum_max = 0;	//sum,sum_max�ֱ��ʾ��ǰ�ܵ÷֣���ǰ��¼
int picture_num = 0;	//��ʾ��ǰͼƬ�ļǺ�
int	timer;	//��ʱ���
char key[10000] = "";	//�������
int key_len = 0;	//������볤��
int come = -1;	//��¼��Ϊ����ָ������
int come_times = 0;		//��¼��Ϊ����ָ������ĸ���
int mode = 1;	//ģʽ
int timer_0 = 300;	//����ģʽ�µĻ���ʱ����
int timer_turn = -1;		//����ģʽ�б��ٵļ��
int timer_tnow;	//����ģʽ�йر���
int timer_now = 0;	//�����ۼ�ʱ��
int timer_all = 0;	//�ܼ�ʱ��
int tool = -2;	//�������-2��ʾδ������-1��ʾ�ѿ���������
int tool_pre = -2;	//��һ������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int					colour_turn(HDC *, HBRUSH *, HPEN *, int, int);	//�л���ɫ���л��ɹ�����1�����ɹ�����0
int					colour_delete(HBRUSH *, HPEN *);	//�ͷ���Դ���ͷųɹ�����1�����ɹ�����0
int					point_(int, int, int);	//���õ����ꣻ���óɹ�����1�����ɹ�����0
int					initpoint(int);		//��ʼ�������ꣻ��ʼ���ɹ�����1�����ɹ�����0
int					remove();	//���������·������ɹ�����1�����ɹ�����0
int					flag_1();	//�ж��ƶ��Ƿ�Ϸ����Ϸ�����1�����Ϸ�����0
int					init_1();	//����ֹͣ��ĸ��£����³ɹ�����1�����ɹ�����0
int					init_2();	//�����������ɹ�����1�����ɹ�����0
int					get(struct Point *, struct Point *);	//��b�ݴ���a���ݴ�ɹ�����1�����ɹ�����0
int					init_0(HWND *);	//�¿�һ�ֵĳ�ʼ������ʼ���ɹ�����1�����ɹ�����0
int					revolve();	//��ת�� ��ת�ɹ�����1�����ɹ�����0
int					revolve_(int);	//����type����ת����ת�ɹ�����1�����ɹ�����0
int					flag_revolve();	//�ж���ת�Ƿ�Ϸ����Ϸ�����1�����Ϸ�����0
int					picture_turn(HDC *);	//�л�ͼƬ���л��ɹ�����1�����ɹ�����0
int					move(int);	//�ƶ����ƶ��ɹ�����1�����ɹ�����0
int					check(HWND *);	//������룻����Ӧ��Ϊ����1�����򷵻�0
int					equals(char *s1);	//�ж��ַ����Ƿ���ȣ���ȷ���1������ȷ���0
int					answer_1();	//��һ��������Ϊ����������;�ɹ�����1�����ɹ�����0
int					answer_2(int i, int j);	//�ڶ���������Ϊ��ʹ�ض��������N��;�ɹ�����1�����ɹ�����0
int					answer_3(int n);	//������������Ϊ��������N�У��ɹ�����1�����ɹ�����0
int					answer_4(HWND *hWnd);	//������������Ϊ���ָ����٣��ɹ�����1�����ɹ�����0
int					add(WPARAM c);	//�������룻��ӳɹ�����1����Ч����0
int					init_3();	//֮�󷽿���޸ģ��޸ĸ��ʵȣ����޸ĳɹ�����1�����ɹ�����0
int					init_tool(int n);	//������ߣ��е��߷���1,�޷���0
int					work_tool(HWND *hWnd);	//������Ч����ʱ��Ч����1�����򷵻�0
int					printf_tool(HDC *hdc);	//����������ƣ���������1��δ��������0
int					printf_mode(HDC *hdc);	//���״̬���ɹ�����1�����ɹ�����0



//�����
struct Point{
	int x;
	int y;
} ;

struct Point point[4], point1[4], point2[4], move_[3] = {{0, 1}, {-1, 0}, {1, 0}};	//point1,point2������ʱ����point,move_������/������

//���巽�����ɫ
struct Colour{
	int x;
	int y;
	int z;
};

struct Colour colour[9] = {	
//	{0, 0, 0},	{0, 0, 50}, {0, 100, 0}, {200, 0, 0},	{0, 100, 50},	
//	{200, 100, 0},	{200, 0 ,50},	{200, 100, 50},		{250, 250, 250}	
	{0, 0, 0},	{253, 249, 70}, {255, 15, 15}, {0, 255, 255},	{0, 0, 155},	
	{255, 0, 128},	{75, 75, 75},	{0, 128, 255},	{255, 255, 255}	
	};


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN321, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN321));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN321));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.hbrBackground	= CreateSolidBrush(RGB(75, 248, 114));
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN321);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, TEXT("����˹����"), WS_SYSMENU,
      400, 100, GRID * nWidth, GRID * nHeight - 10, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent, len, num, tt;
	PAINTSTRUCT ps;
	HDC hdc, hhdc;
	HBRUSH hBrush;
	HPEN hPen;
	TCHAR str[100];
	HDC hbuf;
	HBITMAP bmp;
	HBITMAP bmpMem;

	switch (message)
	{
	case WM_CREATE:
		// ��ʼ��
		init_0(&hWnd);

		// ���ù�����
		workRegion.left		= 0;
		workRegion.bottom	= 0;
		workRegion.right	= nWidth * GRID;
		workRegion.top		= nHeight * GRID;
		break;

	case WM_TIMER:
		if(autoFlag) {
			if (tool > -2)
				timer_now += timer;

			timer_all += timer;

			//�����������
			if (timer_now > 60000){
				tool = -1;
				tt = rand() % 27;
				if (tt < 16)
					tt = rand() % 27;
				init_tool(tt);
				tool_pre = tool;
				work_tool(&hWnd);
				timer_now = 0;
			}	

			if ((tool > 6) && (tool < 12)){
				if (tool == 7){
					if (timer_now > 30000){
						tool = -1;
						timer = timer_0;
						KillTimer(hWnd,	1);
						SetTimer(hWnd, 1, timer, NULL);
					}
				}
				else {
					if (timer_now > 15000){
						if (tool == 8)
							timer_turn = -1;
						else if (tool == 9){
							timer = timer_0;
							KillTimer(hWnd,	1);
							SetTimer(hWnd, 1, timer, NULL);
						}
						else if (tool == 10){
							timer_0 = 300;
							timer = timer_0;
							KillTimer(hWnd,	1);
							SetTimer(hWnd, 1, timer, NULL);
							mode = 1;
							timer_turn = -1;
						}
						tool = -1;
					}
				}
			}

			//����ģʽ���趨
			if (timer_turn > 0)
				timer_turn--;
			else if (timer_turn == 0){
				timer_turn = 5;
				if (timer_tnow){
					tt = rand() % (timer_0 / 2);
					if (rand() % 2)
						timer = timer_0 + tt;
					else timer = timer_0 - tt;
					KillTimer(hWnd,	1);
					SetTimer(hWnd, 1, timer, NULL);
				}
				else{
					tt = rand() % (timer_0 / 2);
					timer = 20 + tt;
					KillTimer(hWnd,	1);
					SetTimer(hWnd, 1, timer, NULL);
				}
				timer_tnow = !timer_tnow;
			}

			if (!flag_1())	//�ж���Ϸ����
			{
				autoFlag = !autoFlag;
				len = wsprintf(str,TEXT("��Ϸ������\n�����ĵ÷��ǣ�%d"), sum);
				MessageBox(hWnd, str, TEXT("Game Over"), MB_OK);
				init_0(&hWnd);
			}
			else if (!move(0))	//�жϷ���ֹͣ����
				init_1();
			InvalidateRect(hWnd, &workRegion, TRUE);
		}
		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	//	MessageBox(hWnd, TEXT("�Բ���û��Ϊ��갴��������Ϊ��"), TEXT("�������"), MB_OK);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_LEFT:
			if (autoFlag)	//�ж��Ƿ���ͣ
			{
				if (tool != 11)
					move(1);
				else 
					move(2);
				InvalidateRect(hWnd, &workRegion, TRUE);
			}
			break;

		case VK_RIGHT:
			if (autoFlag)
			{
				if (tool != 11)
					move(2);
				else
					move(1);
				InvalidateRect(hWnd, &workRegion, TRUE);
			}
			break;

		case VK_UP:
			if (autoFlag)
			{	
				revolve();
				InvalidateRect(hWnd, &workRegion, TRUE);
			}
			break;

		case VK_DOWN:
			if (autoFlag)
			{
				move(0);
				InvalidateRect(hWnd, &workRegion, TRUE);
			}
			break;

		case VK_F2:
			autoFlag = !autoFlag;
			break;
		
		//����ģʽ
		case VK_F3:
			if (!((tool > 6) && (tool < 12)))
				if (mode < 3){
					if (timer_turn > 0)
						timer_turn = -1;
					else{
						timer_turn = 5;
						timer_tnow = 1;
					}
				}
			break;

		//��ģʽ
		case VK_F4:
			if (!((tool > 6) && (tool < 12))){
				timer_0 = 500;
				timer = timer_0;
				KillTimer(hWnd,	1);
				SetTimer(hWnd, 1, timer, NULL);
				mode = 0;
			}
			break;

		//����ģʽ
		case VK_F5:
			if (!((tool > 6) && (tool < 12))){
				timer_0 = 300;
				timer = timer_0;
				KillTimer(hWnd,	1);
				SetTimer(hWnd, 1, timer, NULL);
				mode = 1;
				timer_turn = -1;
			}
			break;

		//����ģʽ
		case VK_F6:
			if (!((tool > 6) && (tool < 12))){
				timer_0 = 180;
				timer = timer_0;
				KillTimer(hWnd,	1);
				SetTimer(hWnd, 1, timer, NULL);
				mode = 2;
			}
			break;

		//���ģʽ
		case VK_F7:
			if (!((tool > 6) && (tool < 12))){
				timer_turn = 5;
				timer_tnow = 1;

				timer_0 = 120;
				timer = timer_0;
				KillTimer(hWnd,	1);
				SetTimer(hWnd, 1, timer, NULL);
				mode = 3;
			}
			break;

		//����ģʽ
		case VK_F8:
			if (tool == -1)
				tool = -2;
			else if (tool == -2){
				tool = -1;
				tool_pre = -2;
				timer_now = 0;
			}
			break;

		//����Esc�˳�
		case VK_ESCAPE:		
			PostQuitMessage(0);
			break;

		//�������������������
		case VK_SPACE:
			if (autoFlag)
			{
				init_2();
				if (timer > 30)
					timer -= 30;
				KillTimer(hWnd,	1);
				SetTimer(hWnd, 1, timer, NULL);
			}
			break;

		case VK_RETURN:
			check(&hWnd);
			key_len = 0;
			key[0] = 0;
			InvalidateRect(hWnd, &workRegion, TRUE);
			break;

		default:
			add(wParam);
			break;
		}
		return 0;

	case WM_PAINT:
		hhdc = BeginPaint(hWnd, &ps);
		hdc = CreateCompatibleDC(hhdc);
		bmpMem = CreateCompatibleBitmap(hhdc, nWidth * GRID, nHeight * GRID);
		SelectObject(hdc, bmpMem);

		hBrush = CreateSolidBrush(RGB(192, 192, 192)); 
		SelectObject(hdc, hBrush); 
		hPen = CreatePen(PS_SOLID, 0, RGB(192, 192, 192));
		SelectObject(hdc, hPen);
		Rectangle(hdc, 0, 0, nGameWidth * GRID,nGameHeight * GRID); 
		DeleteObject(hBrush);
		DeleteObject(hPen);

		hBrush = CreateSolidBrush(RGB(32, 202, 2)); 
		SelectObject(hdc, hBrush); 
		hPen = CreatePen(PS_SOLID, 0, RGB(32, 202, 2));
		SelectObject(hdc, hPen);
		Rectangle(hdc, nGameWidth * GRID, 0, nWidth * GRID, nHeight * GRID); 
		DeleteObject(hBrush);
		DeleteObject(hPen);

		// ����
		if (remove())
		{
			num = picture_num;
			while (picture_num == num)
				picture_num = rand() % 12;
		};

		//����ǰ����
		colour_turn(&hdc, &hBrush, &hPen, now, 0);
		for (int i = 0;i < 4;i++)
			Rectangle(hdc, point[i].x * GRID, point[i].y * GRID, (point[i].x + 1) * GRID, (point[i].y + 1) * GRID);
		colour_delete(&hBrush, &hPen);

		//��ԭʼ����
		for (int i = 0;i < nGameWidth;i++)
			for (int j = 0;j < nGameHeight;j++)
				if (flag[i + 1][j])
				{
					colour_turn(&hdc, &hBrush, &hPen, flag[i + 1][j], 0);
					Rectangle(hdc, i * GRID, j * GRID, (i + 1) * GRID, (j + 1) * GRID);
					colour_delete(&hBrush, &hPen);
				}

		//����һ������
		colour_turn(&hdc, &hBrush, &hPen, next, 0);
		get(point1, point);
		initpoint(next);
		for (int  i = 0;i < 4;i++)
			Rectangle(hdc, (point[i].x + 11) * GRID + 15, (point[i].y + 1) * GRID, (point[i].x + 12) * GRID + 15, (point[i].y + 2) * GRID);
		get(point, point1);
		colour_delete(&hBrush, &hPen);

		// ���߿�
		colour_turn(&hdc, &hBrush, &hPen, 8, 3);
		MoveToEx(hdc, nGameWidth * GRID, 0, NULL);
		LineTo(hdc, nGameWidth * GRID, nGameHeight * GRID);
		MoveToEx(hdc, 0, nGameHeight * GRID, NULL);
		LineTo(hdc, nGameWidth * GRID, nGameHeight * GRID);


		// �����Ϸ˵��
		TextOut(hdc, (nGameWidth) * GRID + 5, 5 * GRID, TEXT("����:"), 3);
		if (tool_pre > -2){
			wsprintf(str,TEXT("tool_%c.bmp"), 'a' + tool_pre);
			hbuf = CreateCompatibleDC(NULL);
			bmp = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
			SelectObject(hbuf, bmp);
			BitBlt(hdc, (nGameWidth) * GRID + 5, 6 * GRID, 100, 100, hbuf, 0, 0, SRCCOPY);
		}
		printf_tool(&hdc);
		if (tool > -2){
			len = wsprintf(str,TEXT("����ߵ����� 00:%.2d"), (60000 - timer_now) / 1000);
			TextOut(hdc, nGameWidth * GRID + 5, 11 * GRID, str, len);
		}
		else{
			TextOut(hdc, (nGameWidth) * GRID + 5, 11 * GRID, TEXT("����ߵ���:��"), 7);
		}

		TextOut(hdc, (nGameWidth) * GRID + 5, 12 * GRID, TEXT("��ǰ״̬:"), 5);

		//���״̬
		printf_mode(&hdc);
		TextOut(hdc, (nGameWidth) * GRID + 5, 14 * GRID, TEXT("����ģʽ:F8"), 7);

		TextOut(hdc, (nGameWidth) * GRID + 5, 0 * GRID, TEXT("��һ��:"), 4);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 0 * GRID, TEXT("�÷֣�"), 3);
		len = wsprintf(str,TEXT("%d"), sum);	//һ��GRID����ԼΪ2
		TextOut(hdc, (nGameWidth + 5) * GRID + 35, 0 * GRID, str, len);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 1 * GRID, TEXT("��ǰ��¼��"), 5);
		len = wsprintf(str,TEXT("%d"), sum_max);
		TextOut(hdc, (nGameWidth + 6) * GRID + 35, 1 * GRID, str, len);
		len = wsprintf(str,TEXT("�Ѻ�ʱ�� %.2d:%.2d"), timer_all / 60000, (timer_all % 60000) / 1000);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 2 * GRID, str, len);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 3 * GRID, TEXT("��Ϸ˵��:"), 5);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 4 * GRID, TEXT("��ʼ/��ͣ��F2"), 8);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 5 * GRID, TEXT("����ģʽ��F3"), 7);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 6 * GRID, TEXT("��ģʽ��F4"), 7);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 7 * GRID, TEXT("����ģʽ��F5"), 7);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 8 * GRID, TEXT("����ģʽ��F6"), 7);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 9 * GRID, TEXT("Crazyģʽ��F7"), 10);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 10 * GRID, TEXT("���󣺡�"), 4);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 11 * GRID, TEXT("���ң���"), 4);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 12 * GRID, TEXT("��ת����"), 4);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 13 * GRID, TEXT("���£���"), 4);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 14 * GRID, TEXT("������Space"), 8);
		TextOut(hdc, (nGameWidth + 4) * GRID + 25, 15 * GRID, TEXT("�˳���Esc"), 6);


		// ����ͼƬ
		picture_turn(&hdc);

		// �ͷ���Դ
		colour_delete(&hBrush, &hPen);
		BitBlt(hhdc, 0, 0, nWidth * GRID, nHeight * GRID, hdc, 0, 0, SRCCOPY); 
		ReleaseDC(hWnd, hhdc);
		DeleteObject(bmpMem); 
		DeleteObject(hdc);  

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//���״̬���ɹ�����1�����ɹ�����0
int printf_mode(HDC *hdc){
	switch (mode){
	case 0:
		switch (tool){
		case 7:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣����٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣�����"), 5);
			break;
		case 8:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣�����"), 5);
			break;
		case 9:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣����٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣�����"), 5);
			break;
		case 10:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 11:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣����٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣�����"), 5);
			break;
		default:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("�򵥣�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��"), 2);
		}
		break;
	case 1:
		switch (tool){
		case 7:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���������٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����������"), 5);
			break;
		case 8:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����������"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����������"), 5);
			break;
		case 9:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���������٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����������"), 5);
			break;
		case 10:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 11:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���������٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����������"), 5);
			break;
		default:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����������"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����"), 2);
		}
		break;
	case 2:
		switch (tool){
		case 7:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ����٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 8:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 9:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ����٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 10:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 11:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ����٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		default:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("����"), 2);
		}
		break;
	case 3:
		switch (tool){
		case 7:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬱��٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬼���"), 5);
			break;
		case 8:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬱���"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬱���"), 5);
			break;
		case 9:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬱��٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬼���"), 5);
			break;
		case 10:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���ѣ�����"), 5);
			break;
		case 11:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬱��٣�����"), 8);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬵���"), 5);
			break;
		default:
			if (timer_turn > -1)
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("��񣬱���"), 5);
			else
				TextOut(*hdc, (nGameWidth) * GRID + 5, 13 * GRID, TEXT("���"), 2);
		}
		break;
	}
	return 1;
}

//����������ƣ���������1��δ��������0
int printf_tool(HDC *hdc){
	if (tool == -2){
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����δ����"), 5);
		return 0;
	}
	switch(tool_pre){
	case -1:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("�޵���"), 3);
		break;
	case 0:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����1��"), 4);
		break;
	case 1:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����2��"), 4);
		break;
	case 2:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����3��"), 4);
		break;
	case 3:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("+100��"), 5);
		break;
	case 4:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("+200��"), 5);
		break;
	case 5:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("+400��"), 6);
		break;
	case 6:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("˫������"), 4);
		break;
	case 7:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����30��"), 5);
		break;
	case 8:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����15��"), 5);
		break;
	case 9:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����15��"), 5);
		break;
	case 10:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("���ѱ���ģʽ15��"), 9);
		break;
	case 11:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����15��"), 5);
		break;
	case 12:
		TextOut(*hdc, (nGameWidth) * GRID + 5, 10 * GRID, TEXT("����"), 2);
		break;
	}
	return 1;
}

//������Ч����ʱ��Ч����1�����򷵻�0
int work_tool(HWND *hWnd){
	TCHAR str[100];
	int len;
	switch (tool){
	case 0:
		for (int j = 0;j < 1;j++){
			for (int k = nGameHeight -1;k > 0;k--)
				for (int i = 1;i <= nGameWidth;i++)
					flag[i][k] = flag[i][k-1];
			for (int i = 1;i <= nGameWidth;i++)
				flag[i][0] = 0;
		}
		break;
	case 1:
		for (int j = 0;j < 2;j++){
			for (int k = nGameHeight -1;k > 0;k--)
				for (int i = 1;i <= nGameWidth;i++)
					flag[i][k] = flag[i][k-1];
			for (int i = 1;i <= nGameWidth;i++)
				flag[i][0] = 0;
		}
		break;
	case 2:
		for (int j = 0;j < 3;j++){
			for (int k = nGameHeight -1;k > 0;k--)
				for (int i = 1;i <= nGameWidth;i++)
					flag[i][k] = flag[i][k-1];
			for (int i = 1;i <= nGameWidth;i++)
				flag[i][0] = 0;
		}
		break;
	case 3:
		sum += 100;
		break;
	case 4:
		sum += 200;
		break;
	case 5:
		sum += 400;
		break;
	case 7:
		timer += timer / 2;
		KillTimer(*hWnd,	1);
		SetTimer(*hWnd, 1, timer, NULL);
		break;
	case 8:
		timer_turn = 5;
		timer_tnow = 1;
		break;
	case 9:
		timer /= 2;
		KillTimer(*hWnd,	1);
		SetTimer(*hWnd, 1, timer, NULL);
		break;
	case 10:
		timer_turn = 5;
		timer_tnow = 1;
		timer_0 = 180;
		timer = timer_0;
		KillTimer(*hWnd,	1);
		SetTimer(*hWnd, 1, timer, NULL);
		break;
	case 12:
		InvalidateRect(*hWnd, &workRegion, TRUE);
		autoFlag = !autoFlag;
		len = wsprintf(str,TEXT("��Ϸ������\n�����ĵ÷��ǣ�%d"), sum);
		MessageBox(*hWnd, str, TEXT("Game Over"), MB_OK);
		init_0(hWnd);
		break;
	default:
		return 0;
	}
	if (tool < 6)
		tool = -1;
	return 1;
}

//������ߣ��е��߷���1,�޷���0
int init_tool(int n){
	switch(n){
	case 0:
	case 1:
	case 2:
		tool = 0;
		break;
	case 3:
	case 4:
		tool = 1;
		break;
	case 5:
		tool = 2;
		break;
	case 6:
	case 7:
	case 8:
		tool = 3;
		break;
	case 9:
	case 10:
		tool = 4;
		break;
	case 11:
		tool = 5;
		break;
	case 12:
	case 13:
		tool = 6;
		break;
	case 14:
	case 15:
		tool = 7;
		break;
	case 16:
	case 17:
		tool = 8;
		break;
	case 18:
	case 19:
		tool = 9;
		break;
	case 20:
	case 21:
		tool = 10;
		break;
	case 22:
	case 23:
		tool = 11;
		break;
	case 24:
		tool = 12;
		break;
	default:
		return 0;
	}

	return 1;
}

//������룻����Ӧ��Ϊ����1�����򷵻�0
int check(HWND *hWnd){
	if (equals("CR")){
		answer_1();
		return 1;
	}

	char tempstr1[100] = "COME";
	for (int i = 1;i < 8;i++)
		for (int j = 1;j < 10;j++){
			tempstr1[4] = '0' + i;
			tempstr1[5] = '0' + j;
			tempstr1[6] = 0;
			if (equals(tempstr1)){
				answer_2(i, j);
				return 1;
			}
		}

	char tempstr2[100] = "WP";
	for (int i = 1;i < 10;i++){
		tempstr2[2] = '0' + i;
		tempstr2[3] = 0;
		if (equals(tempstr2)){
			answer_3(i);
			return 1;
		}
	}

	if (equals("STOP")){
		answer_4(hWnd);
		return 1;
	}

	return 0;
}

//�ж��ַ����Ƿ���ȣ���ȷ���1������ȷ���0
int equals(char *s1){
	char *s2 = key;
	while ((*s2 != 0) && (*s1 == *s2)){
		s1++;s2++;
	}
	if (*s2 != 0) return 0;
	if (*s1 != 0) return 0;
	return 1;
}

//��һ��������Ϊ����������;�ɹ�����1�����ɹ�����0
int answer_1(){
	init_2();
	return 1;
}

//�ڶ���������Ϊ��ʹ�ض��������N��;�ɹ�����1�����ɹ�����0
int answer_2(int i, int j){
	come = i;
	come_times = j;
	next = come;
	return 1;
}

//������������Ϊ��������N�У��ɹ�����1�����ɹ�����0
int answer_3(int n){
	for (int j = 0;j < n;j++){
		for (int k = nGameHeight -1;k > 0;k--)
			for (int i = 1;i <= nGameWidth;i++)
				flag[i][k] = flag[i][k-1];
		for (int i = 1;i <= nGameWidth;i++)
			flag[i][0] = 0;
	}
	return 1;
}

//������������Ϊ���ָ����٣��ɹ�����1�����ɹ�����0
int answer_4(HWND *hWnd){
	timer = timer_0;
	KillTimer(*hWnd,	1);
	SetTimer(*hWnd, 1, timer, NULL);

	return 1;
}

//�������룻��ӳɹ�����1����Ч����0
int add(WPARAM c){
	if ( ((c >= 'A') && (c <='Z')) || ((c >='0') && (c <= '9')) ){
		key[key_len] = c;
		key_len++;
		key[key_len] = 0;
		return 1;
	}
	return 0;
}

//�л�ͼƬ���л��ɹ�����1�����ɹ�����0
int picture_turn(HDC *hdc)
{
	HDC hbuf;
	HBITMAP bmp;
	TCHAR str[100];
	wsprintf(str,TEXT("%c.bmp"), 'a' + picture_num);
	hbuf = CreateCompatibleDC(NULL);
	bmp = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	SelectObject(hbuf, bmp);
	BitBlt(*hdc, (nGameWidth + 1) * GRID, (nGameHeight - 4) * GRID, 100, 100, hbuf, 0, 0, SRCCOPY);

	return 1;
}

//�л���ɫ���л��ɹ�����1�����ɹ�����0
int colour_turn(HDC *hdc, HBRUSH *hBrush, HPEN *hPen, int type, int wide)
{
	*hBrush = CreateSolidBrush(RGB(colour[type].x, colour[type].y, colour[type].z));
	if (wide == 0)
		*hPen = CreatePen(PS_SOLID, wide, RGB(250, 250, 250));
	else
		*hPen = CreatePen(PS_SOLID, wide, RGB(0, 0, 0));
	SelectObject(*hdc, *hBrush);
	SelectObject(*hdc, *hPen);

	return 1;
}

//�ͷ���Դ���ͷųɹ�����1�����ɹ�����0
int colour_delete(HBRUSH *hBrush, HPEN *hPen)
{
	DeleteObject(*hBrush);
	DeleteObject(*hPen);

	return 1;
}

//���õ����ꣻ���óɹ�����1�����ɹ�����0
int point_(int i, int a, int b)
{
	point[i].x = a;
	point[i].y = b;

	return 1;
}

//��ʼ�������ꣻ��ʼ���ɹ�����1�����ɹ�����0
int initpoint(int type)
{
	switch (type)
	{
	case 1:	
		for (int i = 0;i < 4;i++)
			point_(i, 5, i);
		break;
	case 2:
		for (int i = 0;i < 3;i++)
			point_(i, 5, i);
		point_(3, 4, 2);
		break;
	case 3:
		for (int i = 0;i < 3;i++)
			point_(i, 5, i);
		point_(3, 6, 2);
		break;
	case 4:
		point_(0, 5, 0);
		point_(1, 5, 1);
		point_(2, 6, 0);
		point_(3, 6, 1);
		break;
	case 5:
		point_(0, 5, 0);
		point_(1, 4, 0);
		point_(2, 5, 1);
		point_(3, 6, 1);
		break;
	case 6:
		point_(0, 5, 0);
		point_(1, 6, 0);
		point_(2, 5, 1);
		point_(3, 4, 1);
		break;
	case 7:
		point_(0, 5, 0);
		point_(1, 6, 0);
		point_(2, 7, 0);
		point_(3, 6, 1);
		break;
	}

	return 1;
}

//���������·������ɹ�����1�����ɹ�����0
int remove()
{
	int times, flag2;
	times = 0;
	for (int j = nGameHeight -1;j >= 0;j--)
	{
		flag2 = 1;
		for (int i = 1;i <= nGameWidth;i++)
			if (!flag[i][j])
			{
				flag2 = 0;
				break;
			}
			if (flag2)
			{
				times++;
				for (int k = j;k > 0;k--)
					for (int i = 1;i <= nGameWidth;i++)
						flag[i][k] = flag[i][k-1];
				for (int i = 1;i <= nGameWidth;i++)
					flag[i][0] = 0;
				j++;
			}
	}

	switch (times)
	{
	case 0:
		return 0;
	case 1:
		if (tool != 6)
			sum += 100;
		else 
			sum += 200;
		break;
	case 2:
		if (tool != 6)
			sum += 200;
		else
			sum += 400;
		break;
	case 3:
		if (tool != 6)
			sum += 400;
		else
			sum += 800;
		break;
	case 4:
		if (tool != 6)
			sum += 800;
		else
			sum += 1600;
		break;
	}

	return 1;
}

//�ж��ƶ��Ƿ�Ϸ����Ϸ�����1�����Ϸ�����0
int flag_1()
{
	for (int i = 0;i < 4;i++)
		if (flag[point[i].x + 1][point[i].y])
			return 0;
	return 1;
}

//����ֹͣ��ĸ��£����³ɹ�����1�����ɹ�����0
int init_1()
{
	for (int i = 0;i < 4;i++)
		flag[point[i].x + 1][point[i].y] = now;

	initpoint(next);

	if (come_times > 0)
		come_times--;

	if (come_times == 0)
		come = -1;

	now = next;
	init_3();

	return 1;
}

//��b�ݴ���a���ݴ�ɹ�����1�����ɹ�����0
int get(struct Point *a, struct Point *b)
{
	for (int i = 0;i < 4;i++)
		a[i] = b[i];

	return 1;
}

//�����������ɹ�����1�����ɹ�����0
int init_2()
{
	for (int i = 0;i < nGameWidth;i++)
		for (int j = 0;j < nGameHeight;j++)
			flag[i + 1][j] = 0;

	for (int i = 0;i <= nGameHeight;i++)
	{
		flag[0][i] = 1;
		flag[nGameWidth + 1][i] = 1;
	}

	for (int i = 0;i < nGameWidth;i++)
		flag[i + 1][nGameHeight] = 1;

	if (next > 0)
		initpoint(next);

	now = next;
	init_3();

	return 1;
}

//֮�󷽿���޸ģ��޸ĸ��ʵȣ����޸ĳɹ�����1�����ɹ�����0
int init_3(){
	int n;
	if (come > 0)
		next = come;

	else if (mode == 0){
		n = rand() % 21 + 1;
		switch (n){
		case	1:
		case	2:
		case	3:
		case	13:	
			next = 1;
			break;
		case	4:
		case	5:
		case	6:	
			next = 2;
			break;
		case	7:
		case	8:
		case	9:	
			next = 3;
			break;
		case	10:
		case	11:
		case	12:
		case	16:	
			next = 4;
			break;
		case	14:
		case	15:
			next = 5;
			break;
		case	17:
		case	18:
			next = 6;
			break;
		case	19:
		case	20:
		case	21:
			next = 7;
			break;	
		}
	}

	else if (mode == 1){
		n = rand() % 21 + 1;
		switch (n){
		case	1:
		case	2:
		case	3:
			next = 1;
			break;
		case	4:
		case	5:
		case	6:	
			next = 2;
			break;
		case	7:
		case	8:
		case	9:	
			next = 3;
			break;
		case	10:
		case	11:
		case	12:	
			next = 4;
			break;
		case	13:
		case	14:
		case	15:
			next = 5;
			break;
		case	16:
		case	17:
		case	18:	
			next = 6;
			break;
		case	19:
		case	20:
		case	21:	
			next = 7;
			break;
		}
	}

	else if (mode == 2){
		n = rand() % 21 + 1;
		switch (n){
		case	1:
		case	2:
			next = 1;
			break;
		case	4:
		case	5:
		case	6:	
			next = 2;
			break;
		case	7:
		case	8:
		case	9:	
			next = 3;
			break;
		case	11:
		case	12:	
			next = 4;
			break;
		case	3:
		case	13:
		case	14:
		case	15:
			next = 5;
			break;
		case	10:
		case	16:
		case	17:
		case	18:	
			next = 6;
			break;
		case	19:
		case	20:
		case	21:	
			next = 7;
			break;
		}
	}

	else if (mode == 3){
		n = rand() % 21 + 1;
		switch (n){
		case	1:
			next = 1;
			break;
		case	6:	
		case	7:
			next = 2;
			break;
		case	5:
		case	9:	
			next = 3;
			break;
		case	12:	
			next = 4;
			break;
		case	8:
		case	2:
		case	3:
		case	13:
		case	14:
		case	15:
			next = 5;
			break;
		case	4:
		case	11:
		case	10:
		case	16:
		case	17:
		case	18:	
			next = 6;
			break;
		case	19:
		case	20:
		case	21:	
			next = 7;
			break;
		}
	}

	return 1;
}

//�¿�һ�ֵĳ�ʼ������ʼ���ɹ�����1�����ɹ�����0
int init_0(HWND *hWnd)
{
	srand((unsigned)time(NULL));
	next = -1;

	init_2();
	now = 1;

	initpoint(1);

	if (sum > sum_max)
		sum_max = sum;
	sum = 0;
	timer_0 = 300;
	key_len = 0;
	key[0] = 0;
	come = -1;	
	come_times = 0;		
	mode = 1;	
	timer_turn = -1;		
	timer_now = 0;	
	timer_all = 0;	
	tool = -2;	
	tool_pre = -2;	
	timer = timer_0;
	SetTimer(*hWnd, 1, timer, NULL);

	return 1;
}

//�ж���ת�Ƿ�Ϸ����Ϸ�����1�����Ϸ�����0
int flag_revolve()
{
	for (int i = 0;i < 4;i++)
		if ((point[i].x < 0) || (point[i].x >= nGameWidth) || (point[i].y < 0) || (point[i].y >= nGameHeight) 
			||	(flag[point[i].x + 1][point[i].y]))
			return 0;
	return 1;
}

//����type����ת����ת�ɹ�����1�����ɹ�����0
int revolve_(int type)
{
	for (int i = 0;i < 4;i++)
	{
		point[i].x = point2[type].x - (point2[i].y - point2[type].y);
		point[i].y = point2[type].y + (point2[i].x - point2[type].x);
	}
	
	return 1;
}

//�ƶ����ƶ��ɹ�����1�����ɹ�����0
int move(int type)
{
	get(point1, point);

	for (int i = 0;i < 4;i++)
	{
		point[i].x += move_[type].x;
		point[i].y += move_[type].y;
	}

	if (!flag_1())
	{
		get(point, point1);
		return 0;
	}
	return 1;
}

//��ת�� ��ת�ɹ�����1�����ɹ�����0
int revolve()
{
	int type;
	switch (now)
	{
	case 1:
		type = 2;
		break;
	case 2:
		type = 1;
		break;
	case 3:
		type = 1;
		break;
	case 4:
		return 1;
	case 5:
		type = 0;
		break;
	case 6:
		type = 0;
		break;
	case 7:
		type = 1;
		break;
	}
	get(point1, point);
	for (int i = 0;i < 3;i += 2)
	{
		for (int j = 0;j <= i;j++)
		{
			get(point2, point);
			revolve_(type);
		}
		if (flag_revolve())
			return 1;
		get(point, point1);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
