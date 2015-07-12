#import "user32.dll"
  int PostMessageA( int hWnd, int Msg, int wParam, int lParam );
  int SendMessageA(int hWnd,int Msg,int wParam,int lParam);
  int GetAncestor( int hWnd, int gaFlags );
  int GetLastActivePopup( int hWnd );
  int GetDlgItem( int hDlg, int nIDDlgItem );
  int GetWindowText(int hDlg, int buffer, int nMaxCount); 
#import

#import "kernel32.dll"
  int  FindFirstFileA( string Path, int& Answer[] );
  bool FindNextFileA( int handle, int& Answer[] );
  bool FindClose( int handle );
#import

#include <WinUser32.mqh>

#define WM_COMMAND 0x0111
#define WM_KEYDOWN 0x0100
#define VK_DOWN 0x28
#define BM_CLICK 0x00F5
#define GA_ROOT 2
#define PAUSE 100

string BuffToString( int& Buffer[] )
{
  string Str = "";
  int Pos = 11;

  while (Pos < 75)
  {
    while (Buffer[Pos] != 0)
    {
      Str = Str + CharToStr(Buffer[Pos] & 0xFF);

      Buffer[Pos] /= 0x100;
    }
    Pos++;
  }

  return(Str);
}

int GetChartPos( string FileName )
{
  int Buffer[79];
  int Pos = 0;
  int handle = FindFirstFileA(TerminalPath() + "\history\\"  + AccountServer() + "\\*.hst", Buffer);

  if (BuffToString(Buffer) != FileName)
  {
    Pos++;

    while (FindNextFileA(handle, Buffer))
    {
      if (BuffToString(Buffer) == FileName)
        break;

      Pos++;
    }
  }

  if (handle > 0)
    FindClose(handle);

  return(Pos);
}

int OpenOfflineList()
{
  int hwnd = WindowHandle(Symbol(), Period());

  hwnd = GetAncestor(hwnd, GA_ROOT);

  SendMessageA(hwnd, WM_COMMAND, 33053, 0);
  Sleep(PAUSE);

  hwnd = GetLastActivePopup(hwnd);
  hwnd = GetForegroundWindow(); Sleep(PAUSE);
  return(hwnd);
}

void OpenOfflineChartbyNum( int ChartPos )
{
  char buffer[100];
  int hwnd1 = OpenOfflineList();
  int hwnd2 = GetDlgItem(hwnd1, 1);

  GetWindowText(hwnd1, buffer, 30);

  Print("The window handle is ", hwnd1, "title is ", buffer);
  hwnd1 = GetDlgItem(hwnd1, 0x487);

  while (ChartPos >= 0)
  {
    //SendMessageA(hwnd1, WM_KEYDOWN, VK_DOWN, 0);
    PostMessageA(hwnd1, WM_COMMAND,0x33197,0); 
    ChartPos--;
  }

  Sleep(PAUSE);
  SendMessageA(hwnd2, BM_CLICK, 0, 0);

  return;
}

void OpenOfflineChart( string Symb, int period )
{
  OpenOfflineChartbyNum(GetChartPos(Symb + period + ".hst"));

  return;
}

int init()
{
  OpenOfflineChart("AUDCAD", 45);
  return;
}