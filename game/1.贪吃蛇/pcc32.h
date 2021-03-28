#ifndef PCC32_H_INCLUDED
#define PCC32_H_INCLUDED
#include <stdlib.h>
#include <windows.h>
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
/* 按键定义 */
#define JK_FUNC_KEY  0x00
#define JK_CTRL_KEY  0xE0
#define JK_ESC       0x001B
#define JK_ENTER     0x000D
#define JK_SPACE     0x0020
#define JK_BKSPACE   0x0008
#define JK_TAB       0x0009
#define JK_CTRL_Z    0x001A
#define JK_CTRL_X    0x0018
#define JK_CTRL_C    0x0003
#define JK_CTRL_A    0x0001
#define JK_CTRL_S    0x0013
#define JK_CTRL_D    0x0004
#define JK_LEFT      0xE04B
#define JK_RIGHT     0xE04D
#define JK_UP        0xE048
#define JK_DOWN      0xE050
#define JK_INSERT    0xE052
#define JK_HOME      0xE047
#define JK_PGUP      0xE049
#define JK_DELETE    0xE053
#define JK_END       0xE04F
#define JK_PGDW      0xE051
#define JK_F1        0xFF3B
#define JK_F2        0xFF3C
#define JK_F3        0xFF3D
#define JK_F4        0xFF3E
#define JK_F5        0xFF3F
#define JK_F6        0xFF40
#define JK_F7        0xFF41
#define JK_F8        0xFF42
#define JK_F9        0xFF43
#define JK_F10       0xFF44
#define JK_F11       0xE085
#define JK_F12       0xE086
/* 控制台尺寸定义 */
#define MIN_CONSOLE_WIDTH   14
#define MIN_CONSOLE_HEIGHT  1
/* 颜色定义 */
typedef enum _PCCOLOR
{
  BLACK        = 0,
  BLUE         = 1,
  DARK_GREEN   = 2,
  LIGHT_BLUE   = 3,
  RED          = 4,
  PURPLE       = 5,
  ORANGE       = 6,
  GREY         = 7,
  DARKER_GREY  = 8,
  MEDIUM_BLUE  = 9,
  LIGHT_GREEN  = 10,
  TEAL         = 11,
  RED_ORANGE   = 12,
  LIGHT_PURPLE = 13,
  YELLOW       = 14,
  WHITE        = 15
}PCCOLOR;
#ifdef __cplusplus
extern "C" {
#endif
/* 延时,以毫秒计 */
void delayMS(uint32 d);
/* 清除文字 */
void clearText(void);
/* 发出简单的响铃声(阻塞,慎用) */
int simpleRing(uint16 freq, uint16 len);
/* 设置文本颜色,0~15 */
int setTextColor(uint8 fColor);
/* 获取文本颜色,0~15 */
PCCOLOR getTextColor(void);
/* 设置文本背景颜色,0~15 */
int setBackColor(uint8 bColor);
/* 获取文本背景颜色,0~15 */
PCCOLOR getBackColor(void);
/* 设置文本及其背景颜色,0~15 */
int setColors(uint8 fColor, uint8 bColor);
/* 设置/取消前/背景颜色的交换解析 */
int setSwapColors(int b);
/* 设定/取消文字的下划线 */
int setUnderLine(int b);
/* 获取控制台文本行的最大长度[默认为80] */
uint8 getLineWidth(void);
/* 获取控制台文本行的最大行数 */
uint8 getLineNum(void);
/* 获取光标的横坐标[列数] */
uint8 getCursorX(void);
/* 获取光标的纵坐标[行数] */
uint8 getCursorY(void);
/* 屏幕光标定位,x为列(横),y为行(纵) */
int gotoTextPos(uint8 x, uint8 y);
/* 设置光标的可见性 */
int setCursorVisible(int b);
/* 设置光标的(厚度)尺寸,1-100 */
int setCursorSize(uint8 s);
/* 获取控制台的标题字符串 */
int getConsoleTitle(char *title, uint8 len);
/* 设置控制台的标题字符串 */
int setConsoleTitle(char *title);
/* 设置一个没有滚动条的控制台窗口尺寸 */
int fixConsoleSize(uint16 width, uint16 height);
/* 输出控制台的相关信息(仅作调试用) */
int showConsoleInfo();
/* 获取控制台的键输入 */
uint16 jkGetKey(void);
/* 判断控制台是否有键按下 */
int jkHasKey(void);
#ifdef __cplusplus
}
#endif
#endif // PCC32_H_INCLUDED
void delayMS(uint32 d)
{
   Sleep(d);
   return ;
}
void clearText(void)
{
   system("cls");
   return ;
}
int setTextColor(uint8 fColor)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(hd, &csbInfo);
   return SetConsoleTextAttribute(hd, fColor | (csbInfo.wAttributes&~0x0F));
}
PCCOLOR getTextColor(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
   return (PCCOLOR)(csbInfo.wAttributes&0x0F);
}
int setBackColor(uint8 bColor)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(hd, &csbInfo);
   return SetConsoleTextAttribute(hd, (bColor << 4) | (csbInfo.wAttributes&~0xF0));
}
PCCOLOR getBackColor(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
   return (PCCOLOR)((csbInfo.wAttributes&0xF0) >> 4);
}
int setColors(uint8 fColor, uint8 bColor)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(hd, &csbInfo);
   return SetConsoleTextAttribute(hd, fColor | (bColor << 4) | (csbInfo.wAttributes&~0xFF));
}
int setSwapColors(int b)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(hd, &csbInfo);
   if (!!b)
      return SetConsoleTextAttribute(hd, csbInfo.wAttributes | 0x4000);
   else
      return SetConsoleTextAttribute(hd, csbInfo.wAttributes & ~0x4000);
}
int setUnderLine(int b)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(hd, &csbInfo);
   if (!!b)
      return SetConsoleTextAttribute(hd, csbInfo.wAttributes | 0x8000);
   else
      return SetConsoleTextAttribute(hd, csbInfo.wAttributes & ~0x8000);
}
uint8 getLineWidth(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
   return csbInfo.dwSize.X;
}
uint8 getLineNum(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
   return csbInfo.dwSize.Y;
}
uint8 getCursorX(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
   return csbInfo.dwCursorPosition.X;
}
uint8 getCursorY(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbInfo;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
   return csbInfo.dwCursorPosition.Y;
}
int gotoTextPos(uint8 x, uint8 y)
{
   COORD cd;
   cd.X = x;
   cd.Y = y;
   return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}
int setCursorVisible(int b)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO ccInfo;
   GetConsoleCursorInfo(hd, &ccInfo);
   ccInfo.bVisible = !!b;
   return SetConsoleCursorInfo(hd, &ccInfo);
}
int setCursorSize(uint8 s)
{
   HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO ccInfo;
   GetConsoleCursorInfo(hd, &ccInfo);
   ccInfo.dwSize = s;
   return SetConsoleCursorInfo(hd, &ccInfo);
}
int getConsoleTitle(char *title, uint8 len)
{
   return GetConsoleTitle(title, len);
}
int setConsoleTitle(char *title)
{
   return SetConsoleTitle(title);
}
int fixConsoleSize(uint16 width, uint16 height)
{
   int ret = 0;
   int fixX = 0, fixY = 0;
   COORD cd;
   SMALL_RECT srctWindow;
   CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
   HANDLE hWin = GetStdHandle(STD_OUTPUT_HANDLE);
   if (!hWin)
      return 0;
   // 调整最小范围
   fixX = (width < MIN_CONSOLE_WIDTH) ? MIN_CONSOLE_WIDTH : width;
   fixY = (height < MIN_CONSOLE_HEIGHT) ? MIN_CONSOLE_HEIGHT : height;
   // 先将BUF尺寸扩大到最大
   cd.X = 512;
   cd.Y = 512;
   ret = SetConsoleScreenBufferSize(hWin, cd);
   if (!ret)
      return ret;
   //puts("Set Max Buf Error.");
   // 测试屏幕允许的最大尺寸
   GetConsoleScreenBufferInfo(hWin, &csbiInfo);
   cd = csbiInfo.dwMaximumWindowSize;
   //printf("Max Win Size[%d, %d].\n", cd.X, cd.Y);
   fixX = (fixX > cd.X) ? cd.X : fixX;
   fixY = (fixY > cd.Y) ? cd.Y : fixY;
   //printf("Fix Win Size[%d, %d].\n", fixX, fixY);
   // 确定适当的窗口尺寸
   srctWindow.Left = 0;
   srctWindow.Right = fixX - 1;
   srctWindow.Top = 0;
   srctWindow.Bottom = fixY - 1;
   ret = SetConsoleWindowInfo(hWin, 1, &srctWindow);
   if (!ret)
      return ret;
   //puts("Set Size Error.");
   // 确定适当的BUF尺寸
   cd.X = fixX;
   cd.Y = fixY;
   ret = SetConsoleScreenBufferSize(hWin, cd);
   if (!ret)
      return ret;
   //puts("Set Buff Error.");
   //printf("Fix Win Size[%d, %d]: %d.\n", fixX, fixY, ret);
   return ret;
}
int showConsoleInfo()
{
   int ret;
   HANDLE hWin = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
   ret = GetConsoleScreenBufferInfo(hWin, &csbiInfo);
   if (ret)
   {
      printf("Buffer Size: [X]%d - [Y]%d\n", csbiInfo.dwSize.X, csbiInfo.dwSize.Y);
      printf("Cursor Pos : [X]%d - [Y]%d\n", csbiInfo.dwCursorPosition.X, csbiInfo.dwCursorPosition.Y);
      printf("Attributes : %d\n", csbiInfo.wAttributes);
      printf("Current Win: [L]%d - [R]%d - [T]%d - [B]%d\n", \
             csbiInfo.srWindow.Left, csbiInfo.srWindow.Right, csbiInfo.srWindow.Top, csbiInfo.srWindow.Bottom);
      printf("Maximum Win: [X]%d - [Y]%d\n", csbiInfo.dwMaximumWindowSize.X, csbiInfo.dwMaximumWindowSize.Y);
      puts("Over.");
   }
   return ret;
}
int simpleRing(uint16 freq, uint16 len)
{
   return Beep(freq, len);
}
uint16 jkGetKey(void)
{
   uint16 rk = 0;
   uint8 k = getch();
   if (k == JK_FUNC_KEY)
   {
      k = getch();
      rk = 0xFF00 | k;
      return rk;
   }
   if (k == JK_CTRL_KEY)
   {
      k = getch();
      rk = 0xE000 | k;
      return rk;
   }
   rk = 0x0000 | k;
   return rk;
}
int jkHasKey(void)
{
   return (kbhit());
}
//End of pcc32.c




