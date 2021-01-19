#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define _WIN32_IE	            0x0500
#define MAX_RECENT_COUNT            10
#define MAX_TAB_COUNT               16
#define MAX_RESULT_COUNT            32
#define MAX_TEXT_LENGTH          32000
#define MAX_TOOLTIP_LENGTH        1024
#define MAX_REFCOLUMN_COUNT        128
#define MAX_CHART_COLOR_COUNT        9

#define DLG_OK                      1
#define DLG_CANCEL                 -1
#define DLG_DELETE                  2

#define ACTION_SETDEFFONT           1
#define ACTION_DESTROY              2
#define ACTION_RESIZETAB            3
#define ACTION_UPDATETAB            4

#define ROW_VIEW                    0
#define ROW_EDIT                    1
#define ROW_ADD                     2

#define TABLE                       1
#define VIEW                        2
#define INDEX                       3
#define TRIGGER                     4
#define COLUMN                      5

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <shlwapi.h>
#include <stdio.h>
#include <tchar.h>
#include <ctime>
#include <sys/stat.h>
#include <locale.h>
#include <math.h>

#include "missing.h"
#include "sqlite3.h"

extern sqlite3 *db;
extern HWND  hMainWnd, hTreeWnd, hEditorWnd, hTabWnd, hSortingResultWnd, hTooltipWnd;

extern HTREEITEM treeItems[5]; // 0 - current
extern TCHAR editTableData16[255]; // filled on DataEdit Dialog
extern TCHAR searchString[255];

extern const char *TYPES8[5];
extern const TCHAR *TYPES16[5];
extern const TCHAR *TYPES16u[5];
extern const TCHAR *TYPES16p[5];

extern HFONT hDefFont;
extern WNDPROC cbOldListView;
LRESULT CALLBACK cbNewListView(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool CALLBACK cbEnumChildren (HWND hWnd, LPARAM action);
int CALLBACK cbListComparator(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

struct ListViewCell {
	HWND hListWnd;
	int iItem;
	int iSubItem;
};
extern ListViewCell currCell;

extern HMENU hEditDataMenu, hResultMenu, hBlobMenu, hEditorMenu;

void setEditorFont(HWND hWnd);
void setTreeFont(HWND hWnd);

void processHightlight(HWND hEditorWnd, bool isRequireHighligth, bool isRequireParenthesisHighligth);
bool processEditorEvents(MSGFILTER* pF);
bool processAutoComplete(HWND hParent, int key, bool isKeyDown);
TCHAR* getWordFromCursor(HWND hWnd, bool isTable, int pos = -1);

bool executeCommandQuery(const TCHAR* query);
int ListView_SetData(HWND hListWnd, sqlite3_stmt *stmt, bool isRef = false);
int ListView_ShowRef(HWND hListWnd, int rowNo, int colNo);
int ListView_Sort(HWND hListWnd, int colNo);
int ListView_Reset(HWND hListWnd);
int Header_GetItemText(HWND hWnd, int i, TCHAR* pszText, int cchTextMax);
LRESULT onListViewMenu(int cmd, bool ignoreLastColumn = false);
TCHAR* getDbValue(const TCHAR* query16);
TCHAR* getDDL(TCHAR* name16, int type, bool withDrop = false);
bool isQueryValid(const char* query);
bool showDbError(HWND hWnd);

#endif
