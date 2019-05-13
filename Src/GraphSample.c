#include "DIALOG.h"
#include "stdlib.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0        (GUI_ID_USER + 0x00)
#define ID_GRAPH_0         (GUI_ID_USER + 0x01)
#define ID_GRAPH_1         (GUI_ID_USER + 0x02)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window",          ID_WINDOW_0,   0, 0, 320, 240, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph",            ID_GRAPH_0,   0, 0, 320, 240, 0, 0x0, 0 }
};

static GRAPH_DATA_Handle _hDataYT1;
extern volatile int uinti;
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_BLACK);
    //
    // Graph YT
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);

    _hDataYT1 = GRAPH_DATA_YT_Create(GUI_ORANGE, 320, NULL, 0);

    GRAPH_AttachData(hItem, _hDataYT1);
    GRAPH_SetGridVis(hItem, 1);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _ChangeDataXY
*/
/*********************************************************************
*
*       _ChangeDataYT
*/
static void _ChangeDataYT(GRAPH_DATA_Handle hData, int Offset) {
  //
  // Add a value to the given handle
  //
  GRAPH_DATA_YT_AddValue(hData, (I16)rand() % 120 + Offset);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask3(void) {
  GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  while (1) {
    GUI_Delay(50);
    _ChangeDataYT(_hDataYT1, 120);
    GUI_Exec();
  }
}
