<!-- TGMenu.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 12:20:31 2016 (+0800)
;; Last-Updated: 三 9月 16 10:59:55 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TGMenu+

TGMenuEntry 继承 TObject , friend TGPopupMenu , TGMenuBar  
This class contains all information about a menu entry.  
It is a fully protected class used internally by TGPopupMenu.

TGPopupMenu 继承 TGFrame  ,friend TGMenuTitle , TGMenuBar , TGSplitButton
This class creates a popup menu object. Popup menu's are attached to TGMenuBar objects.

TGMenuTitle 继承 TGFrame  
This class creates a menu title. A menu title is a frame to which a popup menu can be attached. Menu titles are automatically created when adding a popup menu to a menubar.

TGMenuBar 继承 TGHorizontalFrame , friend TGPopupMenu
This class creates a menu bar.


## class

**TGMenuEntry**

```cpp
   TGMenuEntry(): fEntryId(0), fUserData(0), fType(), fStatus(0),
      fEx(0), fEy(0), fEw(0), fEh(0), fLabel(0), fShortcut(0), fPic(0), fPopup(0) { }
   virtual ~TGMenuEntry() { if (fLabel) delete fLabel; if (fShortcut) delete fShortcut; }

   Int_t          GetEntryId() const { return fEntryId; }
   const char    *GetName() const { return fLabel ? fLabel->GetString() : 0; }
   const char    *GetShortcutText() const { return fShortcut ? fShortcut->GetString() : 0; }
   virtual Int_t  GetStatus() const { return fStatus; }
   EMenuEntryType GetType() const { return fType; }
   TGPopupMenu   *GetPopup() const { return fPopup; }
   TGHotString   *GetLabel() const  { return fLabel; }
   TGString      *GetShortcut() const { return fShortcut; }
   Int_t          GetEx() const { return fEx; }
   Int_t          GetEy() const { return fEy; }
   UInt_t         GetEw() const { return fEw; }
   UInt_t         GetEh() const { return fEh; }
   const TGPicture *GetPic() const { return fPic; }
   void          *GetUserData() const { return fUserData; }
```


**TGPopupMenu**

```cpp
   TGPopupMenu(const TGWindow *p = 0, UInt_t w = 10, UInt_t h = 10,
               UInt_t options = 0);
   virtual ~TGPopupMenu();

   virtual void AddEntry(TGHotString *s, Int_t id, void *ud = 0,
                         const TGPicture *p = 0, TGMenuEntry *before = 0);
   virtual void AddEntry(const char *s, Int_t id, void *ud = 0,
                         const TGPicture *p = 0, TGMenuEntry *before = 0);
   virtual void AddSeparator(TGMenuEntry *before = 0);
   virtual void AddLabel(TGHotString *s, const TGPicture *p = 0,
                         TGMenuEntry *before = 0);
   virtual void AddLabel(const char *s, const TGPicture *p = 0,
                         TGMenuEntry *before = 0);
   virtual void AddPopup(TGHotString *s, TGPopupMenu *popup,
                         TGMenuEntry *before = 0, const TGPicture *p = 0);
   virtual void AddPopup(const char *s, TGPopupMenu *popup,
                         TGMenuEntry *before = 0, const TGPicture *p = 0);
   virtual void   EnableEntry(Int_t id);
   virtual void   DisableEntry(Int_t id);
   virtual Bool_t IsEntryEnabled(Int_t id);
   virtual void   HideEntry(Int_t id);
   virtual Bool_t IsEntryHidden(Int_t id);
   virtual void   DefaultEntry(Int_t id);
   virtual void   CheckEntry(Int_t id);
   virtual void   CheckEntryByData(void *user_data);
   virtual void   UnCheckEntry(Int_t id);
   virtual void   UnCheckEntryByData(void *user_data);
   virtual void   UnCheckEntries();
   virtual Bool_t IsEntryChecked(Int_t id);
   virtual void   RCheckEntry(Int_t id, Int_t IDfirst, Int_t IDlast);
   virtual Bool_t IsEntryRChecked(Int_t id);
   virtual void   PlaceMenu(Int_t x, Int_t y, Bool_t stick_mode,
                            Bool_t grab_pointer);
   virtual Int_t  EndMenu(void *&userData);
   virtual void   DeleteEntry(Int_t id);
   virtual void   DeleteEntry(TGMenuEntry *entry);
   virtual TGMenuEntry *GetEntry(Int_t id);
   virtual TGMenuEntry *GetCurrent() const { return fCurrent; }
   virtual TGMenuEntry *GetEntry(const char *s);
   const TList    *GetListOfEntries() const { return fEntryList; }
   virtual void    DrawBorder();
   virtual Bool_t  HandleButton(Event_t *event);
   virtual Bool_t  HandleMotion(Event_t *event);
   virtual Bool_t  HandleCrossing(Event_t *event);
   virtual Bool_t  HandleTimer(TTimer *t);
   virtual void    Associate(const TGWindow *w) { fMsgWindow = w; }
   virtual void    SetMenuBar(TGMenuBar *bar) { fMenuBar = bar; }
   TGMenuBar      *GetMenuBar() const { return fMenuBar; }
   virtual void    Activate(Bool_t) { }
   virtual void    Activate(TGMenuEntry *entry);
   virtual void    SavePrimitive(std::ostream &out, Option_t *option = "");

   UInt_t GetEntrySep()  const { return fEntrySep; }
   virtual void SetEntrySep(UInt_t sep)  { fEntrySep = sep; }

   virtual void PoppedUp() { Emit("PoppedUp()"); }                        // *SIGNAL*
   virtual void PoppedDown() { Emit("PoppedDown()"); }                    // *SIGNAL*
   virtual void Highlighted(Int_t id) { Emit("Highlighted(Int_t)", id); } // *SIGNAL*
   virtual void Activated(Int_t id) { Emit("Activated(Int_t)", id); }     // *SIGNAL*
```


**TGMenuTitle**

```cpp
   static FontStruct_t  GetDefaultFontStruct();
   static const TGGC   &GetDefaultSelectedGC();
   static const TGGC   &GetDefaultGC();

   TGMenuTitle(const TGWindow *p = 0, TGHotString *s = 0, TGPopupMenu *menu = 0,
               GContext_t norm = GetDefaultGC()(),
               FontStruct_t font = GetDefaultFontStruct(),
               UInt_t options = 0);
   virtual ~TGMenuTitle() { if (fLabel) delete fLabel; }

   Pixel_t      GetTextColor() const { return fTextColor; }
   void         SetTextColor(Pixel_t col) { fTextColor = col; }
   virtual void SetState(Bool_t state);
   Bool_t       GetState() const { return fState; }
   Int_t        GetHotKeyCode() const { return fHkeycode; }
   TGPopupMenu *GetMenu() const { return fMenu; }
   const char  *GetName() const { return fLabel ? fLabel->GetString() : 0; }
   virtual void DoSendMessage();
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```

**TGMenuBar**

```cpp
   TGMenuBar(const TGWindow *p = 0, UInt_t w = 60, UInt_t h = 20,
             UInt_t options = kHorizontalFrame | kRaisedFrame);
   virtual ~TGMenuBar();

   virtual void AddPopup(TGHotString *s, TGPopupMenu *menu, TGLayoutHints *l,
                         TGPopupMenu *before = 0);
   virtual void AddPopup(const char *s, TGPopupMenu *menu, TGLayoutHints *l,
                         TGPopupMenu *before = 0);
   virtual TGPopupMenu *AddPopup(const TString &s, Int_t padleft = 4, Int_t padright = 0,
                                 Int_t padtop = 0, Int_t padbottom = 0);
   virtual void AddTitle(TGMenuTitle *title, TGLayoutHints *l, TGPopupMenu *before = 0);

   virtual TGPopupMenu *GetPopup(const char *s);
   virtual TGPopupMenu *RemovePopup(const char *s);

   virtual TGMenuTitle *GetCurrent() const { return fCurrent; }
   virtual TList  *GetTitles() const { return fTitles; }
   virtual Bool_t  HandleButton(Event_t *event);
   virtual Bool_t  HandleMotion(Event_t *event);
   virtual Bool_t  HandleKey(Event_t *event);
   virtual void    SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual void    Layout();
           void    PopupConnection();
   TGFrameElement* GetLastOnLeft();
```




## code

```cpp
#include "TGMenu.h"
```

```cpp
// TGMenuBar
// 最上面那行弹出菜单的标签
TGMenuBar *fMenuBar;// main menu bar
fMenuBar = new TGMenuBar(this, 35, 50, kHorizontalFrame);
fMenuBar->AddPopup("&File", fMenuFile/*子菜单TGPopupMenu*/, new TGLayoutHints(kLHintsTop|kLHintsLeft, 0, 4, 0, 0));
fMenuBar->AddPopup("&Help", fMenuHelp, new TGLayoutHints(kLHintsTop|kLHintsRight));
AddFrame(fMenuBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5));
```

```cpp
// TGPopupMenu
// 最上面那行弹出菜单的子菜单
TGPopupMenu *fMenuFile;    // "File" popup menu entry
TGPopupMenu *fMenuHelp;    // "Help" popup menu entry
fMenuFile = new TGPopupMenu(gClient->GetRoot());
fMenuFile->AddEntry(" &Open...\tCtrl+O", IDs, 0,gClient->GetPicture("bld_open.png"));
fMenuFile->AddEntry(" &Browse...\tCtrl+B", IDs);
fMenuFile->AddEntry(" &New Canvas\tCtrl+N", IDs);
fMenuFile->AddEntry(" &Close Window\tCtrl+W", IDs);
fMenuFile->AddSeparator();//分割线
fMenuFile->AddEntry(" E&xit\tCtrl+Q", M_FILE_EXIT, 0,gClient->GetPicture("bld_exit.png"));
fMenuFile->Connect("Activated(Int_t)", "DNDMainFrame", this,"HandleMenu(Int_t)"/*deal IDs*/);
fMenuFile->DisableEntry(IDs);//显示灰色，无法按
fMenuFile->HideEntry(IDs);//隐藏，不显示
fMenuHelp = new TGPopupMenu(gClient->GetRoot());
fMenuHelp->AddEntry(" &About...", M_HELP_ABOUT, 0,gClient->GetPicture("about.xpm"));
fMenuHelp->Connect("Activated(Int_t)", "DNDMainFrame", this,"HandleMenu(Int_t)");
fMenuView = new TGPopupMenu(gClient->GetRoot());
fMenuView->AddEntry("&Dock", M_VIEW_DOCK);
fMenuView->DisableEntry(M_VIEW_DOCK);
fMenuView->AddEntry("&Undock", M_VIEW_UNDOCK);
fMenuView->AddSeparator();
fMenuView->AddEntry("Enable U&ndock", M_VIEW_ENBL_DOCK);
fMenuView->AddEntry("Enable &Hide", M_VIEW_ENBL_HIDE);
fMenuView->CheckEntry(M_VIEW_ENBL_DOCK);
fMenuView->CheckEntry(M_VIEW_ENBL_HIDE);
fMenuDock->Connect("Undocked()", "TestMainFrame", this, "HandleMenu(=M_VIEW_UNDOCK)");
```




## example






<!-- TGMenu.md ends here -->
