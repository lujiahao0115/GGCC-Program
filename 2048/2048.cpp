#include<graphics.h>
#include<bits/stdc++.h>
#include<conio.h>
SYSTEMTIME sys;
using namespace std;
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
void color(int x, int y)
{
	int num = a[x][y];
	if (num == 2)setbkcolor(RGB(190, 24, 93)), setfillcolor(RGB(190, 24, 93));
	else if (num == 4)setbkcolor(RGB(162, 28, 175)), setfillcolor(RGB(162, 28, 175));
	else if (num == 8)setbkcolor(RGB(126, 34, 206)), setfillcolor(RGB(126, 34, 206));
	else if (num == 16)setbkcolor(RGB(67, 56, 202)), setfillcolor(RGB(67, 56, 202));
	else if (num == 32)setbkcolor(RGB(29, 78, 216)), setfillcolor(RGB(29, 78, 216));
	else if (num == 64)setbkcolor(RGB(3, 105, 161)), setfillcolor(RGB(3, 105, 161));
	else if (num == 128)setbkcolor(RGB(15, 118, 110)), setfillcolor(RGB(15, 118, 110));
	else if (num == 256)setbkcolor(RGB(21, 128, 61)), setfillcolor(RGB(21, 128, 61));
	else if (num == 512)setbkcolor(RGB(77, 124, 15)), setfillcolor(RGB(77, 124, 15));
	else if (num == 1024)setbkcolor(RGB(161, 98, 7)), setfillcolor(RGB(161, 98, 7));
	else if (num == 2048)setbkcolor(RGB(194, 65, 12)), setfillcolor(RGB(194, 65, 12));
	else if(IsDarkMode)setfillcolor(RGB(32, 32, 32));
	else setfillcolor(RGB(224,224,224));
}
void print()
{
	settextstyle(24, 0, _T("微软雅黑"));
	if (IsDarkMode) {
		setbkcolor(RGB(16, 16, 16));
		settextcolor(RGB(255, 255, 255));
		setfillcolor(RGB(32, 32, 32));
	}
	else {
		setbkcolor(RGB(240, 240, 240));
		settextcolor(RGB(0, 0, 0));
		setfillcolor(RGB(224,224,224));
	}
	cleardevice();
	if (IsDarkMode)setbkcolor(RGB(32, 32, 32));
	else setbkcolor(RGB(224, 224, 224));
	solidroundrect(70, 15, 190, 80, 5, 5);
	solidroundrect(210, 15, 330, 80, 5, 5);
	outtextxy(94, 25, _T("当前得分"));
	itoa(score, s, 10);
	outtextxy(234, 25, _T("最大数字"));
	RECT r1 = { 70, 44, 190, 80 };
	drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	itoa(Maxn, s, 10);
	RECT r2 = { 210, 44, 330, 80 };
	drawtext(s, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(24, 0, _T("微软雅黑"));
	if (IsDarkMode)setbkcolor(RGB(16, 16, 16));
	else setbkcolor(RGB(240, 240, 240));
	RECT r3 = { 0, 420, 400, 500 };
	drawtext(_T("按空格键切换主题"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(32, 0, _T("微软雅黑"));
	settextcolor(RGB(255, 255, 255));
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j) {
			int x01 = 30 + (i - 1) * 80 + i * 4, y01 = 90 + (j - 1) * 80 + j * 4;
			int x02 = 110 + (i - 1) * 80 + i * 4, y02 = 170 + (j - 1) * 80 + j * 4;
			color(i, j);
			solidroundrect(x01, y01, x02, y02, 10, 10);
			if (a[i][j] == 0)continue;
			itoa(a[i][j], s, 10);
			RECT r = { x01,y01,x02,y02 };
			drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
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
	memset(mv, false, sizeof(mv));
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j)
			b[i][j] = a[i][j];
	if (cz == 'w')
		for (int j = 1; j <= 4; j++)
			for (int i = 2; i <= 4; i++) {
				if (!a[i][j])continue;
				int k = i;
				while (!a[k - 1][j] && k >= 2)
					a[k - 1][j] = a[k][j], a[k][j] = 0, k--;
				if (a[k][j] == a[k - 1][j] && !mv[k - 1][j])
					a[k - 1][j] = 2 * a[k][j], a[k][j] = 0, mv[k - 1][j] = true, score += a[k - 1][j];
			}
	else if (cz == 'a')
		for (int i = 1; i <= 4; i++)
			for (int j = 2; j <= 4; j++) {
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k - 1] && k >= 2)
					a[i][k - 1] = a[i][k], a[i][k] = 0, k--;
				if (a[i][k] == a[i][k - 1] && !mv[i][k - 1])
					a[i][k - 1] = 2 * a[i][k], a[i][k] = 0, mv[i][k - 1] = true, score += a[i][k - 1];
			}
	else if (cz == 's')
		for (int j = 1; j <= 4; j++)
			for (int i = 3; i >= 1; i--) {
				if (!a[i][j])continue;
				int k = i;
				while (!a[k + 1][j] && k <= 3)a[k + 1][j] = a[k][j], a[k][j] = 0, k++;
				if (a[k][j] == a[k + 1][j] && !mv[k + 1][j])
					a[k + 1][j] = 2 * a[k][j], a[k][j] = 0, mv[k + 1][j] = true, score += a[k + 1][j];
			}
	else if (cz == 'd')
		for (int i = 1; i <= 4; i++)
			for (int j = 3; j >= 1; j--) {
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k + 1] && k <= 3)
					a[i][k + 1] = a[i][k], a[i][k] = 0, k++;
				if (a[i][k] == a[i][k + 1] && !mv[i][k + 1])
					a[i][k + 1] = 2 * a[i][k], a[i][k] = 0, mv[i][k + 1] = true, score += a[i][k + 1];
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
} 
int main()
{
	initgraph(400, 500);
	if (sys.wHour >= 18 || sys.wHour <= 6)IsDarkMode = 1;
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
		cz = _getch();
		if (cz == -32)cz = -_getch();
		if (cz == 's')cz = 'd';
		else if (cz == 'd')cz = 's';
		else if (cz == 'w')cz = 'a';
		else if (cz == 'a')cz = 'w';
		else if (cz == ' ')IsDarkMode = (IsDarkMode + 1) % 2;
		move(cz);
		print();
		if (space == 0 && check()) {
			if (IDNO == MessageBox(GetHWnd(), "你失败了，游戏结束。", _T("2048"), MB_OK)) break;
			return 0;
		}
		if (Maxn == 2048) {
			if (IDNO == MessageBox(GetHWnd(), "恭喜你，成功了。", _T("2048"), MB_OK)) break;
			return 0;
		}
	}
	_getch();
	closegraph();
}