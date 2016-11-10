<!-- TGButton.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 10:18:00 2016 (+0800)
;; Last-Updated: 四 11月 10 21:39:55 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGButton

```cpp
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGButton, TGTextButton, TGPictureButton, TGCheckButton,              //
// TGRadioButton and TGSplitButton                                      //
//                                                                      //
// This header defines all GUI button widgets.                          //
//                                                                      //
// TGButton is a button abstract base class. It defines general button  //
// behaviour.                                                           //
//                                                                      //
// TGTextButton and TGPictureButton yield an action as soon as they are //
// clicked. These buttons usually provide fast access to frequently     //
// used or critical commands. They may appear alone or placed in a      //
// group.                                                               //
//                                                                      //
// The action they perform can be inscribed with a meaningful tooltip   //
// set by SetToolTipText(const char* text, Long_t delayms=400).         //
//                                                                      //
// The text button has a label indicating the action to be taken when   //
// the button is pressed. The text can be a hot string ("&Exit") that   //
// defines the label "Exit" and keyboard mnemonics Alt+E for button     //
// selection. A button label can be changed by SetText(new_label).      //
//                                                                      //
// Selecting a text or picture button will generate the event:          //
// kC_COMMAND, kCM_BUTTON, button id, user data.                        //
//                                                                      //
// The purpose of TGCheckButton and TGRadioButton is for selecting      //
// different options. Like text buttons, they have text or hot string   //
// as a label.                                                          //
//                                                                      //
// Radio buttons are grouped usually in logical sets of two or more     //
// buttons to present mutually exclusive choices.                       //
//                                                                      //
// Selecting a check button will generate the event:                    //
// kC_COMMAND, kCM_CHECKBUTTON, button id, user data.                   //
//                                                                      //
// Selecting a radio button will generate the event:                    //
// kC_COMMAND, kCM_RADIOBUTTON, button id, user data.                   //
//                                                                      //
// If a command string has been specified (via SetCommand()) then this  //
// command string will be executed via the interpreter whenever a       //
// button is selected. A command string can contain the macros:         //
// $MSG   -- kC_COMMAND, kCM[CHECK|RADIO]BUTTON packed message          //
//           (use GET_MSG() and GET_SUBMSG() to unpack)                 //
// $PARM1 -- button id                                                  //
// $PARM2 -- user data pointer                                          //
// Before executing these macros are expanded into the respective       //
// Long_t's                                                             //
//                                                                      //
// TGSplitButton implements a button with added menu functionality.     //
// There are 2 modes of operation available.                            //
//                                                                      //
// If the button is split, a menu will popup when the menu area of the  //
// button is clicked. Activating a menu item changes the functionality  //
// of the button by having it emit a additional signal when it is       //
// clicked. The signal emitted when the button is clicked, is the       //
// ItemClicked(Int_t) signal with a different fixed value for the       //
// Int_t that corresponds to the id of the activated menu entry.        //
//                                                                      //
// If the button is not split, clicking it will popup the menu and the  //
// ItemClicked(Int_t) signal will be emitted when a menu entry is       //
// acitvated. The value of the Int_t is again equal to the value of     //
// the id of the activated menu entry.                                  //
//                                                                      //
// The mode of operation of a SplitButton can be changed on the fly     //
// by calling the SetSplit(Bool_t) method.                              //
//////////////////////////////////////////////////////////////////////////
```

TGButton 继承 TGFrame, TGWidget ， friend TGButtonGroup  

TGTextButton 继承 TGButton

TGPictureButton 继承 TGButton

TGCheckButton 继承 TGButton

TGRadioButton 继承 TGButton

TGSplitButton 继承 TGTextButton


## class

**TGButton**

```cpp
   static const TGGC   &GetDefaultGC();
   static const TGGC   &GetHibckgndGC();

   TGButton(const TGWindow *p = 0, Int_t id = -1, GContext_t norm = GetDefaultGC()(),
            UInt_t option = kRaisedFrame | kDoubleBorder);
   virtual ~TGButton();

   virtual Bool_t       HandleButton(Event_t *event);
   virtual Bool_t       HandleCrossing(Event_t *event);
   virtual void         SetUserData(void *userData) { fUserData = userData; }
   virtual void        *GetUserData() const { return fUserData; }
   virtual void         SetToolTipText(const char *text, Long_t delayms = 400);  //*MENU*
   virtual TGToolTip   *GetToolTip() const { return fTip; }
   virtual void         SetState(EButtonState state, Bool_t emit = kFALSE);
   virtual EButtonState GetState() const { return fState; }
   virtual void         AllowStayDown(Bool_t a) { fStayDown = a; }
   virtual void         SetGroup(TGButtonGroup *gr);
   TGButtonGroup       *GetGroup() const { return fGroup; }

   virtual Bool_t       IsDown() const;// { return !(fOptions & kRaisedFrame); }
   virtual void         SetDown(Bool_t on = kTRUE, Bool_t emit = kFALSE);
   virtual Bool_t       IsOn() const { return IsDown(); }
   virtual void         SetOn(Bool_t on = kTRUE,  Bool_t emit = kFALSE) { SetDown(on, emit); }
   virtual Bool_t       IsToggleButton() const { return kFALSE; }
   virtual Bool_t       IsExclusiveToggle() const { return kFALSE; }
   virtual void         Toggle(Bool_t emit = kFALSE) { SetDown(IsDown() ? kFALSE : kTRUE, emit); }
   virtual void         SetEnabled(Bool_t e = kTRUE); //*TOGGLE* *GETTER=IsEnabled
   virtual UInt_t       GetStyle() const { return fStyle; }
   virtual void         SetStyle(UInt_t newstyle);
   virtual void         SetStyle(const char *style);

   virtual void         SavePrimitive(std::ostream &out, Option_t *option = "");

   GContext_t GetNormGC() const { return fNormGC; }

   virtual void Pressed()  { Emit("Pressed()"); }   // *SIGNAL*
   virtual void Released() { Emit("Released()"); }  // *SIGNAL*
   virtual void Clicked()  { Emit("Clicked()"); }   // *SIGNAL*
   virtual void Toggled(Bool_t on) { Emit("Toggled(Bool_t)", on); }  // *SIGNAL*
```


**TGTextButton**

```cpp
   static FontStruct_t GetDefaultFontStruct();

   TGTextButton(const TGWindow *p, TGHotString *s, Int_t id = -1,
                GContext_t norm = GetDefaultGC()(),
                FontStruct_t font = GetDefaultFontStruct(),
                UInt_t option = kRaisedFrame | kDoubleBorder);
   TGTextButton(const TGWindow *p = 0, const char *s = 0, Int_t id = -1,
                GContext_t norm = GetDefaultGC()(),
                FontStruct_t font = GetDefaultFontStruct(),
                UInt_t option = kRaisedFrame | kDoubleBorder);
   TGTextButton(const TGWindow *p, const char *s, const char *cmd,
                Int_t id = -1, GContext_t norm = GetDefaultGC()(),
                FontStruct_t font = GetDefaultFontStruct(),
                UInt_t option = kRaisedFrame | kDoubleBorder);

   virtual ~TGTextButton();

   virtual TGDimension GetDefaultSize() const;

   virtual Bool_t     HandleKey(Event_t *event);
   const TGHotString *GetText() const { return fLabel; }
   virtual const char *GetTitle() const { return fLabel->Data(); }
   TString            GetString() const { return TString(fLabel->GetString()); }
   virtual void       SetTextJustify(Int_t tmode);
   Int_t GetTextJustify() const { return fTMode; }
   virtual void       SetText(TGHotString *new_label);
   virtual void       SetText(const TString &new_label);
   virtual void       SetTitle(const char *label) { SetText(label); }
   virtual void       SetFont(FontStruct_t font, Bool_t global = kFALSE);
   virtual void       SetFont(const char *fontName, Bool_t global = kFALSE);
   virtual void       SetTextColor(Pixel_t color, Bool_t global = kFALSE);
   virtual void       SetForegroundColor(Pixel_t fore) { SetTextColor(fore); }
   Bool_t             HasOwnFont() const;
   void               SetWrapLength(Int_t wl) { fWrapLength = wl; Layout(); }
   Int_t              GetWrapLength() const { return fWrapLength; }
   void               SetMargins(Int_t left=0, Int_t right=0, Int_t top=0, Int_t bottom=0)
                        { fMLeft = left; fMRight = right; fMTop = top; fMBottom = bottom; }

   virtual void       SetLeftMargin(Int_t val)   { fMLeft = val; }
   virtual void       SetRightMargin(Int_t val)  { fMRight = val; }
   virtual void       SetTopMargin(Int_t val)    { fMTop = val; }
   virtual void       SetBottomMargin(Int_t val) { fMBottom = val; }

   Int_t              GetLeftMargin() const { return fMLeft; }
   Int_t              GetRightMargin() const { return fMRight; }
   Int_t              GetTopMargin() const { return fMTop; }
   Int_t              GetBottomMargin() const { return fMBottom; }

   void               ChangeText(const char *title)  { SetTitle(title); } //*MENU*icon=bld_rename.png*

   FontStruct_t GetFontStruct() const { return fFontStruct; }

   virtual void       Layout();
   virtual void       SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGPictureButton**

```cpp
   TGPictureButton(const TGWindow *p, const TGPicture *pic, Int_t id = -1,
                   GContext_t norm = GetDefaultGC()(),
                   UInt_t option = kRaisedFrame | kDoubleBorder);
   TGPictureButton(const TGWindow *p, const TGPicture *pic, const char *cmd,
                   Int_t id = -1, GContext_t norm = GetDefaultGC()(),
                   UInt_t option = kRaisedFrame | kDoubleBorder);
   TGPictureButton(const TGWindow *p = 0, const char* pic = 0, Int_t id = -1,
                   GContext_t norm = GetDefaultGC()(),
                   UInt_t option = kRaisedFrame | kDoubleBorder);
   virtual ~TGPictureButton();

   virtual void     SetPicture(const TGPicture *new_pic);
   virtual void     SetDisabledPicture(const TGPicture *pic);
   const TGPicture *GetPicture() const { return fPic; };
   const TGPicture *GetDisabledPicture() const { return fPicD; };
   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGCheckButton**

```cpp
   static FontStruct_t  GetDefaultFontStruct();
   static const TGGC   &GetDefaultGC();

   TGCheckButton(const TGWindow *p, TGHotString *s, Int_t id = -1,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   TGCheckButton(const TGWindow *p = 0, const char *s = 0, Int_t id = -1,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   TGCheckButton(const TGWindow *p, const char *s, const char *cmd, Int_t id = -1,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   virtual ~TGCheckButton();

   virtual TGDimension GetDefaultSize() const;

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleKey(Event_t *event);
   virtual Bool_t HandleCrossing(Event_t *event);
   virtual Bool_t IsToggleButton() const { return kTRUE; }
   virtual Bool_t IsOn() const { return fState == kButtonDown; }
   virtual Bool_t IsDown() const { return fState == kButtonDown; }
   virtual Bool_t IsDisabledAndSelected() const { return ((fState == kButtonDisabled) && fStateOn); }
   virtual void   SetDisabledAndSelected(Bool_t);
   virtual void   SetState(EButtonState state, Bool_t emit = kFALSE);
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGRadioButton**

```cpp
   static FontStruct_t  GetDefaultFontStruct();
   static const TGGC   &GetDefaultGC();

   TGRadioButton(const TGWindow *p, TGHotString *s, Int_t id = -1,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   TGRadioButton(const TGWindow *p = 0, const char *s = 0, Int_t id = -1,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   TGRadioButton(const TGWindow *p, const char *s, const char *cmd, Int_t id = -1,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   virtual ~TGRadioButton();

   virtual TGDimension GetDefaultSize() const;

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleKey(Event_t *event);
   virtual Bool_t HandleCrossing(Event_t *event);
   virtual void   SetState(EButtonState state, Bool_t emit = kFALSE);
   virtual void   SetDisabledAndSelected(Bool_t);
   virtual Bool_t IsToggleButton() const { return kTRUE; }
   virtual Bool_t IsExclusiveToggle() const { return kTRUE; }
   virtual Bool_t IsOn() const { return fStateOn; }
   virtual Bool_t IsDown() const { return fStateOn; }
   virtual Bool_t IsDisabledAndSelected() const { return ((fState == kButtonDisabled) && fStateOn); }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGSplitButton**

```cpp
   TGSplitButton(const TGWindow *p, TGHotString *menulabel,
                TGPopupMenu *popmenu, Bool_t split = kTRUE,
                Int_t id = -1, GContext_t norm = GetDefaultGC()(),
                FontStruct_t fontstruct = GetDefaultFontStruct(),
                UInt_t option = kRaisedFrame | kDoubleBorder);

   virtual ~TGSplitButton();

   virtual TGDimension GetDefaultSize() const ;

   virtual void   SetText(TGHotString *new_label);
   virtual void   SetText(const TString &new_label);
   virtual void   SetFont(FontStruct_t font, Bool_t global = kFALSE);
   virtual void   SetFont(const char *fontName, Bool_t global = kFALSE);
   virtual void   SetMBState(EButtonState state);
   virtual void   SetSplit(Bool_t split);
   Bool_t         IsSplit() { return fSplit; }
   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleCrossing(Event_t *event);
   virtual Bool_t HandleKey(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual void   Layout();

   virtual void MBPressed()  { Emit("MBPressed()"); }   // *SIGNAL*
   virtual void MBReleased() { Emit("MBReleased()"); }  // *SIGNAL*
   virtual void MBClicked()  { Emit("MBClicked()"); }   // *SIGNAL*
   virtual void ItemClicked(Int_t id) { Emit("ItemClicked(Int_t)", id); } // *SIGNAL*

   // Slots
   void HandleMenu(Int_t id) ;/// Handle a menu item activation.
```


## code

```cpp
// Button
#include "TGClient.h"
#include "TGButton.h"
```

```cpp
// TGTextButton
// 按钮，按钮上有字，字可改变
TGTextButton     *fStart;
fStart = new TGTextButton(frame, "&Start");
// fStart = new TGTextButton(frame, "&Start the \n software""and go it");
// fStart->Resize(300, 200);//设置大小
// fStart->ChangeOptions(fStart->GetOptions() | kFixedSize);
ULong_t yellow;
gClient->GetColorByName("yellow", yellow);
fStart->ChangeBackground(yellow);//button background will be set to yellow
fStart->Connect("Clicked()", "MyMainFrame", this, "ChangeStartLabel()");
frame->AddFrame(fStart, new TGLayoutHints(kLHintsTop | kLHintsExpandX,3, 2, 2, 2));
fStart->SetToolTipText("Click to toggle the button label (Start/Stop)");//鼠标放上去显示的信息
void ChangeStartLabel()
{
  fStart->SetState(kButtonDown);
  if (!start) {
     fStart->SetText("&Stop");
     start = kTRUE;
  } else {
     fStart->SetText("&Start");
     start = kFALSE;
  }
  fStart->SetState(kButtonUp);
}
```

```cpp
// TGCheckButton
// 多选按钮
TGVButtonGroup *fButtonGroup;  // Button group
fButtonGroup = new TGVButtonGroup(frame, "My Button Group");
fButtonGroup->SetTitlePos(TGGroupFrame::kCenter);
frame->AddFrame(fButtonGroup, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,1, 1, 1, 1));
// TGGroupFrame *fButtonGroup = new TGGroupFrame(frame, "Enable/Disable");
// fButtonGroup->SetTitlePos(TGGroupFrame::kCenter);
// frame->AddFrame(fButtonGroup, new TGLayoutHints(kLHintsExpandX ));
TGCheckButton *fCheckb[4];
fCheckb[0] = new TGCheckButton(fButtonGroup, new TGHotString("CB 1"),IDs);//Widget IDs ，每个的唯一编号，0，1，2，3……
fCheckb[1] = new TGCheckButton(fButtonGroup, new TGHotString("CB 2"),IDs);
fCheckb[2] = new TGCheckButton(fButtonGroup, new TGHotString("CB 3"),IDs);
fCheckb[3] = new TGCheckButton(fButtonGroup, new TGHotString("CB 4"),IDs);
fCheckb[0]->SetOn();//Default state
// fCheckb[0]->->SetState(kButtonDown);//设置状态为选上
fCheckb[0]->GetState();//获得当前状态，0、1
// fCheckb[0]->Connect("Toggled(Bool_t)", "MyButtonTest", this, "SetGroupEnabled(Bool_t)");
fButtonGroup->Show();
fButtonGroup->SetState(kTRUE);//是否开启，开启才可以选，不开启是灰色的
```

```cpp
// TGRadioButton
// 单选按钮
TGVButtonGroup      *fButtonGroup;  // Button group
TGRadioButton *fRadiob[2];
fButtonGroup = new TGVButtonGroup(frame, "My Button Group");
fButtonGroup->SetTitlePos(TGGroupFrame::kCenter);
fRadiob[0] = new TGRadioButton(fButtonGroup, new TGHotString("RB 1"),IDs);
fRadiob[1] = new TGRadioButton(fButtonGroup, new TGHotString("RB 2"),IDs);
fRadiob[1]->SetOn();//Default state
fButtonGroup->Show();
fButtonGroup->SetState(kTRUE);//是否开启，开启才可以选，不开启是灰色的
fButtonGroup->SetRadioButtonExclusive(kTRUE);//???
frame->AddFrame(fButtonGroup, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,1, 1, 1, 1));
```


```cpp
// TGPictureButton
// 按钮是图片


```

```cpp
// TGSplitButton
//


```


## example




<!-- TGButton.md ends here -->
