#include<graphics.h>
#include<bits/stdc++.h>
#include<conio.h>
#define key_down(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
SYSTEMTIME sys;
LOGFONT f;
RECT r;
MOUSEMSG m;
using namespace std;
int clrtb[15][3] = { {190,24,93},{162,28,175},{126,34,206},{67,56,202},{29,78,216},{3,105,161},
					 {15,118,110},{21,128,61},{77,124,15},{161,98,7},{194,65,12} };
int a[6][6] = { 0 }, b[6][6] = { 0 };
bool mv[6][6] = { 0 }, IsDarkMode = 0;
int x, y, score = 0, space = 14, Maxn = 2, t;
char cz, s[25];
void init()
{
	memset(a, 0, sizeof(a));
	do x = rand() % 4 + 1, y = rand() % 4 + 1;
	while (a[x][y] != 0);
	t = rand() % 6;
	if (t == 0)a[x][y] = 4;
	else a[x][y] = 2;
	do x = rand() % 4 + 1, y = rand() % 4 + 1;
	while (a[x][y] != 0);
	t = rand() % 6;
	if (t == 0)a[x][y] = 4;
	else a[x][y] = 2;
}
int check() {
	int flag = 0;
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j)
			if (!a[i][j] || a[i][j] == a[i + 1][j] || a[i][j] == a[i - 1][j]
				|| a[i][j] == a[i][j + 1] || a[i][j] == a[i][j - 1])return 0;
}
void print()
{
	if (IsDarkMode) {
		setbkcolor(RGB(16, 16, 16));
		settextcolor(RGB(255, 255, 255));
		setfillcolor(RGB(32,32,32));
	}
	else {
		setbkcolor(RGB(240, 240, 240));
		settextcolor(RGB(0, 0, 0));
		setfillcolor(RGB(255,255,255));
	}
	cleardevice();
	if (IsDarkMode)setbkcolor(RGB(32,32,32));
	else setbkcolor(RGB(255,255,255));
	solidroundrect(430, 350, 520, 395, 40, 40);
	settextstyle(26, 0, _T("Segoe Fluent Icons"));
	if (IsDarkMode) {
		r = { 465,350,520,395 };
		settextcolor(RGB(0, 120, 215));
		drawtext(_T(""), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		r = { 430,350,485,395 };
		settextcolor(RGB(255, 255, 255));
		drawtext(_T(""), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		r = { 440,355,475,390 };
		settextcolor(RGB(0, 120, 215));
		drawtext(_T(""), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		r = { 475,355,510,390 };
		settextcolor(RGB(0, 0, 0));
		drawtext(_T(""), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	settextstyle(26, 0, _T("微软雅黑"));
	solidroundrect(415,19, 540, 159, 6, 6);
	outtextxy(440, 35, _T("当前得分"));
	itoa(score, s, 10);
	outtextxy(440, 95, _T("最大数字"));
	r = { 440, 60, 515, 90 };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	itoa(Maxn, s, 10);
	r = { 440, 120, 515, 150 };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(36, 0, _T("微软雅黑"));
	settextcolor(RGB(255, 255, 255));
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j) {
			int num = a[i][j], r, g, b;
			int x01 = 9 + (i - 1) * 90 + i * 6, y01 = 12 + (j - 1) * 90 + j * 6;
			int x02 = 99 + (i - 1) * 90 + i * 6, y02 = 102 + (j - 1) * 90 + j * 6;
			if (num) {
				for (int k = 1; k <= 11; ++k)
					if (num == (1 << k)) {
						r = clrtb[k - 1][0], g = clrtb[k - 1][1], b = clrtb[k - 1][2];
						setbkcolor(RGB(r, g, b));
						setlinecolor(RGB(r * 5 / 6, g * 5 / 6, b * 5 / 6));
						setfillcolor(RGB(r, g, b));
						fillroundrect(x01, y01, x02, y02, 6, 6);
						break;
					}
			}
			else {
				if (IsDarkMode) {
					setfillcolor(RGB(32, 32, 32));
					setlinecolor(RGB(0, 0, 0));
				}
				else {
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(224, 224, 224));
				}
				fillroundrect(x01, y01, x02, y02, 6, 6);
			}
			if (a[i][j] == 0)continue;
			itoa(a[i][j], s, 10);
			RECT R = { x01,y01,x02,y02 };
			drawtext(s, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	Sleep(200);
}
int same()
{
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j)
			if (a[i][j] != b[i][j])return 0;
	return 1;
}
void move(char cz)
{
	int flag = 0;
	memset(mv, false, sizeof(mv));
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j)
			b[i][j] = a[i][j];
	if (key_down(VK_LEFT)) {
		for (int j = 1; j <= 4; j++)
			for (int i = 2; i <= 4; i++) {
				if (!a[i][j])continue;
				int k = i;
				while (!a[k - 1][j] && k >= 2)
					a[k - 1][j] = a[k][j], a[k][j] = 0, k--;
				if (a[k][j] == a[k - 1][j] && !mv[k - 1][j])
					a[k - 1][j] = 2 * a[k][j], a[k][j] = 0, mv[k - 1][j] = true, score += a[k - 1][j];
			}
		flag = 1;
	}
	else if (key_down(VK_UP)) {
		for (int i = 1; i <= 4; i++)
			for (int j = 2; j <= 4; j++) {
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k - 1] && k >= 2)
					a[i][k - 1] = a[i][k], a[i][k] = 0, k--;
				if (a[i][k] == a[i][k - 1] && !mv[i][k - 1])
					a[i][k - 1] = 2 * a[i][k], a[i][k] = 0, mv[i][k - 1] = true, score += a[i][k - 1];
			}
		flag = 1;
	}
	else if (key_down(VK_RIGHT)) {
		for (int j = 1; j <= 4; j++)
			for (int i = 3; i >= 1; i--) {
				if (!a[i][j])continue;
				int k = i;
				while (!a[k + 1][j] && k <= 3)a[k + 1][j] = a[k][j], a[k][j] = 0, k++;
				if (a[k][j] == a[k + 1][j] && !mv[k + 1][j])
					a[k + 1][j] = 2 * a[k][j], a[k][j] = 0, mv[k + 1][j] = true, score += a[k + 1][j];
			}
		flag = 1;
	}
	else if (key_down(VK_DOWN)) {
		for (int i = 1; i <= 4; i++)
			for (int j = 3; j >= 1; j--) {
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k + 1] && k <= 3)
					a[i][k + 1] = a[i][k], a[i][k] = 0, k++;
				if (a[i][k] == a[i][k + 1] && !mv[i][k + 1])
					a[i][k + 1] = 2 * a[i][k], a[i][k] = 0, mv[i][k + 1] = true, score += a[i][k + 1];
			}
		flag = 1;
	}
	else return;
	if (same() && check() == 0)return;
	space = 0;
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j) {
			if (a[i][j] == 0)space++;
			Maxn = max(Maxn, a[i][j]);
		}
	if (space == 0)return;
	do x = rand() % 4 + 1, y = rand() % 4 + 1;
	while (a[x][y] != 0);
	t = rand() % 6;
	if (t == 0)a[x][y] = 4;
	else a[x][y] = 2;
	space++;
	if (flag)print();
} 
int main()
{
	initgraph(560,420);
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	GetLocalTime(&sys);
	if (sys.wHour >= 18 || sys.wHour <= 5)IsDarkMode = 1;
	else IsDarkMode = 0;
	if (IsDarkMode) {
		setbkcolor(RGB(16, 16, 16));
		settextcolor(RGB(255, 255, 255));
	}
	else {
		setbkcolor(RGB(240, 240, 240));
		settextcolor(RGB(0, 0, 0));
	}
	cleardevice();
	srand((unsigned)time(NULL));
	init();
	print();
	while (1) {
		//m = GetMouseMsg();
		if (key_down(VK_SPACE)) {
			IsDarkMode = (IsDarkMode + 1) % 2;
			print();
		}
		move(cz);
		if (space == 0 && check()) {
			if (Maxn >= 2048) {
				if (IDNO == MessageBox(GetHWnd(), "恭喜你，成功了。", _T("2048"), MB_OK)) break;
				return 0;
			}
			else {
				if (IDNO == MessageBox(GetHWnd(), "你失败了，游戏结束。", _T("2048"), MB_OK)) break;
				return 0;
			}
		}
	}
	_getch();
	closegraph();
}