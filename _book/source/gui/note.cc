// note.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 6月 25 16:11:28 2016 (+0800)
// Last-Updated: 六 10月  8 21:04:38 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 45
// URL: http://wuhongyi.cn 

// WidgetMessageTypes
enum EWidgetMessageTypes {
   kC_COMMAND          = 1,
      kCM_MENU            = 1,
      kCM_MENUSELECT      = 2,
      kCM_BUTTON          = 3,
      kCM_CHECKBUTTON     = 4,
      kCM_RADIOBUTTON     = 5,
      kCM_LISTBOX         = 6,
      kCM_COMBOBOX        = 7,
      kCM_TAB             = 8,
   kC_HSCROLL          = 2,
   kC_VSCROLL          = 3,
      kSB_LINEUP          = 1,
      kSB_LINEDOWN        = 2,
      kSB_PAGEUP          = 3,
      kSB_PAGEDOWN        = 4,
      kSB_SLIDERTRACK     = 5,
      kSB_SLIDERPOS       = 6,
   kC_TEXTENTRY        = 4,
      kTE_TEXTCHANGED     = 1,
      kTE_ENTER           = 2,
      kTE_TAB             = 3,
      kTE_KEY             = 4,
   kC_CONTAINER        = 5,
      kCT_ITEMCLICK       = 1,
      kCT_ITEMDBLCLICK    = 2,
      kCT_SELCHANGED      = 3,
      kCT_KEY             = 4,
   kC_HSLIDER          = 6,
   kC_VSLIDER          = 7,
      kSL_POS             = 1,
      kSL_TRACK           = 2,
      kSL_PRESS           = 3,
      kSL_RELEASE         = 4,
      kSL_POINTER         = 5,
   kC_LISTTREE         = 8,
   kC_TEXTVIEW         = 9,
      kTXT_ISMARKED       = 1,
      kTXT_DATACHANGE     = 2,
      kTXT_CLICK2         = 3,
      kTXT_CLICK3         = 4,
      kTXT_F3             = 5,
      kTXT_OPEN           = 6,
      kTXT_CLOSE          = 7,
      kTXT_SAVE           = 8,
   kC_COLORSEL         = 10,
      kCOL_CLICK          = 1,
      kCOL_SELCHANGED     = 2,
   kC_PATTERNSEL       = 11,
      kPAT_CLICK          = 1,
      kPAT_SELCHANGED     = 2,
   kC_MARKERSEL        = 12,
      kMAR_CLICK          = 1,
      kMAR_SELCHANGED     = 2,
   kC_POPUP            = 13,
      kPOP_HIDE           = 1,
   kC_DOCK             = 14,
      kDOCK_DOCK          = 1,
      kDOCK_UNDOCK        = 2,
      kDOCK_SHOW          = 3,
      kDOCK_HIDE          = 4,
   kC_MDI              = 15,
      kMDI_CURRENT        = 1,
      kMDI_CREATE         = 2,
      kMDI_CLOSE          = 4,
      kMDI_RESTORE        = 8,
      kMDI_MOVE           = 16,
      kMDI_SIZE           = 32,
      kMDI_MINIMIZE       = 64,
      kMDI_MAXIMIZE       = 128,
      kMDI_HELP           = 256,
      kMDI_MENU           = 512,
   kC_USER             = 1001,
   kC_MSGMAX           = 10000
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// TGCheckButton
// TGComboBox

// TGGroupFrame
// TGIcon
// TGLabel
// TGListBox
// TGMenuBar
// TGNumberEntry
// TGPicture
// TGPicturePool
// TGPopupMenu
// TGRadioButton
// TGSplitButton
// TGTextEntry
// TGTripleSlider
// TGVButtonGroup
// TGTextButton


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGButton, TGTextButton, TGPictureButton, TGCheckButton TGRadioButton //
// and TGSplitButton                                                    //
//                                                                      //
// This header defines all GUI button widgets.                          //
//                                                                      //
// TGButton is a button abstract base class. It defines general button  //
// behaviour.                                                           //
//                                                                      //
// Selecting a text or picture button will generate the event:          //
// kC_COMMAND, kCM_BUTTON, button id, user data.                        //
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
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGColorPalette, TGColorPick and TGColorDialog.                       //
//                                                                      //
// The TGColorPalette is a widget showing an matrix of color cells. The //
// colors can be set and selected.                                      //
//                                                                      //
// The TGColorPick is a widget which allows a color to be picked from   //
// HLS space. It consists of two elements: a color map window from      //
// where the user can select the hue and saturation level of a color,   //
// and a slider to select color's lightness.                            //
//                                                                      //
// Selecting a color in these two widgets will generate the event:      //
// kC_COLORSEL, kCOL_CLICK, widget id, 0.                               //
// and the signal:                                                      //
// ColorSelected(Pixel_t color)                                         //
//                                                                      //
// The TGColorDialog presents a full featured color selection dialog.   //
// It uses 2 TGColorPalette's and the TGColorPick widgets.              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGColorFrame, TG16ColorSelector, TGColorPopup and TGColorSelect.     //
//                                                                      //
// The TGColorFrame is a small frame with border showing a specific     //
// color.                                                               //
//                                                                      //
// The TG16ColorSelector is a composite frame with 16 TGColorFrames.    //
//                                                                      //
// The TGColorPopup is a popup containing a TG16ColorSelector and a     //
// "More..." button which popups up a TGColorDialog allowing custom     //
// color selection.                                                     //
//                                                                      //
// The TGColorSelect widget is like a checkbutton but instead of the    //
// check mark there is color area with a little down arrow. When        //
// clicked on the arrow the TGColorPopup pops up.                       //
//                                                                      //
// Selecting a color in this widget will generate the event:            //
// kC_COLORSEL, kCOL_SELCHANGED, widget id, pixel.                      //
// and the signal:                                                      //
// ColorSelected(Pixel_t pixel)                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGComboBox, TGComboBoxPopup                                          //
//                                                                      //
// A combobox (also known as a drop down listbox) allows the selection  //
// of one item out of a list of items. The selected item is visible in  //
// a little window. To view the list of possible items one has to click //
// on a button on the right of the little window. This will drop down   //
// a listbox. After selecting an item from the listbox the box will     //
// disappear and the newly selected item will be shown in the little    //
// window.                                                              //
//                                                                      //
// The TGComboBox is user callable. The TGComboBoxPopup is a service    //
// class of the combobox.                                               //
//                                                                      //
// Selecting an item in the combobox will generate the event:           //
// kC_COMMAND, kCM_COMBOBOX, combobox id, item id.                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGDoubleSlider, TGDoubleVSlider and TGDoubleHSlider                  //
//                                                                      //
// DoubleSlider widgets allow easy selection of a min and a max value   //
// out of a range.                                                      //
// DoubleSliders can be either horizontal or vertical oriented and      //
// there is a choice of three different types of tick marks.            //
//                                                                      //
// To change the min value press the mouse near to the left / bottom    //
// edge of the slider.                                                  //
// To change the max value press the mouse near to the right / top      //
// edge of the slider.                                                  //
// To change both values simultaneously press the mouse near to the     //
// center of the slider.                                                //
//                                                                      //
// TGDoubleSlider is an abstract base class. Use the concrete           //
// TGDoubleVSlider and TGDoubleHSlider.                                 //
//                                                                      //
// Dragging the slider will generate the event:                         //
// kC_VSLIDER, kSL_POS, slider id, 0  (for vertical slider)             //
// kC_HSLIDER, kSL_POS, slider id, 0  (for horizontal slider)           //
//                                                                      //
// Pressing the mouse will generate the event:                          //
// kC_VSLIDER, kSL_PRESS, slider id, 0  (for vertical slider)           //
// kC_HSLIDER, kSL_PRESS, slider id, 0  (for horizontal slider)         //
//                                                                      //
// Releasing the mouse will generate the event:                         //
// kC_VSLIDER, kSL_RELEASE, slider id, 0  (for vertical slider)         //
// kC_HSLIDER, kSL_RELEASE, slider id, 0  (for horizontal slider)       //
//                                                                      //
// Use the functions GetMinPosition(), GetMaxPosition() and             //
// GetPosition() to retrieve the position of the slider.                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGListBox, TGLBContainer, TGLBEntry and TGTextLBEntry                //
//                                                                      //
// A listbox is a box, possibly with scrollbar, containing entries.     //
// Currently entries are simple text strings (TGTextLBEntry).           //
// A TGListBox looks a lot like a TGCanvas. It has a TGViewPort         //
// containing a TGLBContainer which contains the entries and it also    //
// has a vertical scrollbar which becomes visible if there are more     //
// items than fit in the visible part of the container.                 //
//                                                                      //
// The TGListBox is user callable. The other classes are service        //
// classes of the listbox.                                              //
//                                                                      //
// Selecting an item in the listbox will generate the event:            //
// kC_COMMAND, kCM_LISTBOX, listbox id, item id.                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGListTree and TGListTreeItem                                        //
//                                                                      //
// A list tree is a widget that can contain a number of items           //
// arranged in a tree structure. The items are represented by small     //
// folder icons that can be either open or closed.                      //
//                                                                      //
// The TGListTree is user callable. The TGListTreeItem is a service     //
// class of the list tree.                                              //
//                                                                      //
// A list tree can generate the following events:                       //
// kC_LISTTREE, kCT_ITEMCLICK, which button, location (y<<16|x).        //
// kC_LISTTREE, kCT_ITEMDBLCLICK, which button, location (y<<16|x).     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGListView, TGLVContainer and TGLVEntry                              //
//                                                                      //
// A list view is a widget that can contain a number of items           //
// arranged in a grid or list. The items can be represented either      //
// by a string or by an icon.                                           //
//                                                                      //
// The TGListView is user callable. The other classes are service       //
// classes of the list view.                                            //
//                                                                      //
// A list view can generate the following events:                       //
// kC_CONTAINER, kCT_SELCHANGED, total items, selected items.           //
// kC_CONTAINER, kCT_ITEMCLICK, which button, location (y<<16|x).       //
// kC_CONTAINER, kCT_ITEMDBLCLICK, which button, location (y<<16|x).    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGMenuBar, TGPopupMenu, TGMenuTitle and TGMenuEntry                  //
//                                                                      //
// This header contains all different menu classes.                     //
//                                                                      //
// Selecting a menu item will generate the event:                       //
// kC_COMMAND, kCM_MENU, menu id, user data.                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGScrollBar and TGScrollBarElement                                   //
//                                                                      //
// The classes in this file implement scrollbars. Scrollbars can be     //
// either placed horizontal or vertical. A scrollbar contains three     //
// TGScrollBarElements: The "head", "tail" and "slider". The head and   //
// tail are fixed at either end and have the typical arrows in them.    //
//                                                                      //
// The TGHScrollBar will generate the following event messages:         //
// kC_HSCROLL, kSB_SLIDERPOS, position, 0                               //
// kC_HSCROLL, kSB_SLIDERTRACK, position, 0                             //
//                                                                      //
// The TGVScrollBar will generate the following event messages:         //
// kC_VSCROLL, kSB_SLIDERPOS, position, 0                               //
// kC_VSCROLL, kSB_SLIDERTRACK, position, 0                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGSlider, TGVSlider and TGHSlider                                    //
//                                                                      //
// Slider widgets allow easy selection of a range.                      //
// Sliders can be either horizontal or vertical oriented and there is   //
// a choice of two different slider types and three different types     //
// of tick marks.                                                       //
//                                                                      //
// TGSlider is an abstract base class. Use the concrete TGVSlider and   //
// TGHSlider.                                                           //
//                                                                      //
// Dragging the slider will generate the event:                         //
// kC_VSLIDER, kSL_POS, slider id, position  (for vertical slider)      //
// kC_HSLIDER, kSL_POS, slider id, position  (for horizontal slider)    //
//                                                                      //
// Pressing the mouse will generate the event:                          //
// kC_VSLIDER, kSL_PRESS, slider id, 0  (for vertical slider)           //
// kC_HSLIDER, kSL_PRESS, slider id, 0  (for horizontal slider)         //
//                                                                      //
// Releasing the mouse will generate the event:                         //
// kC_VSLIDER, kSL_RELEASE, slider id, 0  (for vertical slider)         //
// kC_HSLIDER, kSL_RELEASE, slider id, 0  (for horizontal slider)       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGTab, TGTabElement, TGTabLayout                                     //
//                                                                      //
// A tab widget contains a set of composite frames each with a little   //
// tab with a name (like a set of folders with tabs).                   //
//                                                                      //
// The TGTab is user callable. The TGTabElement and TGTabLayout are     //
// is a service classes of the tab widget.                              //
//                                                                      //
// Clicking on a tab will bring the associated composite frame to the   //
// front and generate the following event:                              //
// kC_COMMAND, kCM_TAB, tab id, 0.                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGTextEntry                                                          //
//                                                                      //
// A TGTextEntry is a one line text input widget.                       //
//                                                                      //
// Changing text in the text entry widget will generate the event:      //
// kC_TEXTENTRY, kTE_TEXTCHANGED, widget id, 0.                         //
// Hitting the enter key will generate:                                 //
// kC_TEXTENTRY, kTE_ENTER, widget id, 0.                               //
// Hitting the tab key will generate:                                   //
// kC_TEXTENTRY, kTE_TAB, widget id, 0.                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGTripleVSlider and TGTripleHSlider                                  //
//                                                                      //
// TripleSlider inherit from DoubleSlider widgets and allow easy        //
// selection of a min, max and pointer value out of a range.            //
// The pointer position can be constrained to edges of slider and / or  //
// can be relative to the slider position.                              //
//                                                                      //
// To change the min value press the mouse near to the left / bottom    //
// edge of the slider.                                                  //
// To change the max value press the mouse near to the right / top      //
// edge of the slider.                                                  //
// To change both values simultaneously press the mouse near to the     //
// center of the slider.                                                //
// To change pointer value press the mouse on the pointer and drag it   //
// to the desired position                                              //
//                                                                      //
// Dragging the slider will generate the event:                         //
// kC_VSLIDER, kSL_POS, slider id, 0  (for vertical slider)             //
// kC_HSLIDER, kSL_POS, slider id, 0  (for horizontal slider)           //
//                                                                      //
// Pressing the mouse will generate the event:                          //
// kC_VSLIDER, kSL_PRESS, slider id, 0  (for vertical slider)           //
// kC_HSLIDER, kSL_PRESS, slider id, 0  (for horizontal slider)         //
//                                                                      //
// Releasing the mouse will generate the event:                         //
// kC_VSLIDER, kSL_RELEASE, slider id, 0  (for vertical slider)         //
// kC_HSLIDER, kSL_RELEASE, slider id, 0  (for horizontal slider)       //
//                                                                      //
// Moving the pointer will generate the event:                          //
// kC_VSLIDER, kSL_POINTER, slider id, 0  (for vertical slider)         //
// kC_HSLIDER, kSL_POINTER, slider id, 0  (for horizontal slider)       //
//                                                                      //
// Use the functions GetMinPosition(), GetMaxPosition() and             //
// GetPosition() to retrieve the position of the slider.                //
// Use the function GetPointerPosition() to retrieve the position of    //
// the pointer                                                          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGView                                                               //
//                                                                      //
// A TGView provides the infrastructure for text viewer and editor      //
// widgets. It provides a canvas (TGViewFrame) and (optionally) a       //
// vertical and horizontal scrollbar and methods for marking and        //
// scrolling.                                                           //
//                                                                      //
// The TGView (and derivatives) will generate the following             //
// event messages:                                                      //
// kC_TEXTVIEW, kTXT_ISMARKED, widget id, [true|false]                  //
// kC_TEXTVIEW, kTXT_DATACHANGE, widget id, 0                           //
// kC_TEXTVIEW, kTXT_CLICK2, widget id, position (y << 16) | x)         //
// kC_TEXTVIEW, kTXT_CLICK3, widget id, position (y << 16) | x)         //
// kC_TEXTVIEW, kTXT_F3, widget id, true                                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


// =============================================================================

// Button
#include "TGClient.h"
#include "TGButton.h"

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


// TGPictureButton
// 按钮是图片



// TGSplitButton
//




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGListBox.h"

// TGListBox
// 可选择列表，可单选、多选
TGListBox           *fListBox;
TList               *fSelected;
fListBox = new TGListBox(frame, 89);
fSelected = new TList;
char tmp[20];
for (int i = 0; i < 20; ++i) {
  sprintf(tmp, "Entry %i", i+1);
  fListBox->AddEntry(tmp, i+1/*IDs*/);
}
fListBox->Resize(100,150);
frame->AddFrame(fListBox, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 5));
fListBox->SetMultipleSelections(0/*0  1*/);//设置是否可多选
fSelected->Clear();// Writes selected entries in TList if multiselection.
if (fListBox->GetMultipleSelections()) {
  Printf("Selected entries are:\n");
  fListBox->GetSelectedEntries(fSelected);
  fSelected->ls();
 } else {
  Printf("Selected entries is: %d\n", fListBox->GetSelected());
 }
if (fSelected) {//不用之后
  fSelected->Delete();
  delete fSelected;
 }

// TGLBContainer
//


// TGLBEntry
//



// TGTextLBEntry
//


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#include "TGComboBox.h"

// TGComboBox
// 下拉选项
TGComboBox *fMonthBox;
fMonthBox = new TGComboBox(frame);
frame->AddFrame(fMonthBox, new TGLayoutHints(kLHintsLeft, 5, 5, 2, 2));
fMonthBox->AddEntry("AAA", 1);
fMonthBox->AddEntry("BBB", 2);
fMonthBox->AddEntry("CCC", 3);
fMonthBox->Select(1);
// fMonthBox->Resize(100, /*fYearEntry*/->GetHeight());

// TGComboBoxPopup
// 


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGNumberEntry.h"

// TGNumberEntry
TGNumberEntry *fYearEntry = new TGNumberEntry(frame, 2016/*初始值*/, 5/*能容纳位数*/, IDs,TGNumberFormat::kNESInteger,TGNumberFormat::kNEAPositive,TGNumberFormat::kNELLimitMin, 1995/*min*/,2020/*max*/);
frame->AddFrame(fYearEntry, new TGLayoutHints(kLHintsLeft, 5, 5, 2, 2));
// fYearEntry->Connect("ValueSet(Long_t)", "MyMainFrame", this, "DoSetlabel()");
// (fYearEntry->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,"DoSetlabel()");

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGMenu.h"

// TGMenuBar
// 最上面那行弹出菜单的标签
TGMenuBar *fMenuBar;// main menu bar
fMenuBar = new TGMenuBar(this, 35, 50, kHorizontalFrame);
fMenuBar->AddPopup("&File", fMenuFile/*子菜单TGPopupMenu*/, new TGLayoutHints(kLHintsTop|kLHintsLeft, 0, 4, 0, 0));
fMenuBar->AddPopup("&Help", fMenuHelp, new TGLayoutHints(kLHintsTop|kLHintsRight));
AddFrame(fMenuBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5));

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

// TGMenuTitle
//




// TGMenuEntry
//


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGTripleSlider.h"

// TGTripleSlider
// 可调节范围，左右边界外加一个中间值
TGTripleHSlider *fHslider1;
fHslider1 = new TGTripleHSlider(frame, 190, kDoubleScaleBoth, IDs,
				kHorizontalFrame,
				GetDefaultFrameBackground(),
				kFALSE, kFALSE, kFALSE, kFALSE);
fHslider1->Connect("PointerPositionChanged()", "TTripleSliderDemo", this, "DoSlider()");
fHslider1->Connect("PositionChanged()", "TTripleSliderDemo", this, "DoSlider()");
fHslider1->SetRange(0.05,5.0);
frame->AddFrame(fHslider1, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
fHslider1->GetMinPosition();//Float_t
fHslider1->GetPointerPosition();//Float_t
fHslider1->GetMaxPosition());//Float_t
fHslider1->SetPointerPosition(atof("1.23"));
fHslider1->SetPosition(atof("5.0"), fHslider1->GetMaxPosition());
fHslider1->SetPosition(fHslider1->GetMinPosition(), atof("0.1");
fHslider1->SetConstrained(kTRUE);
fHslider1->SetRelative(kTRUE);		       
		       
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TRootEmbeddedCanvas.h"

// TRootEmbeddedCanvas
// 画板
TRootEmbeddedCanvas *fCanvas= new TRootEmbeddedCanvas("Canvas", frame, 600, 400);
TGLayoutHints *fLcan = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10, 10, 10, 10);
frame->AddFrame(fCanvas, fLcan);
fCanvas->GetCanvas()->SetFillColor(33);
fCanvas->GetCanvas()->SetFrameFillColor(41);
fCanvas->GetCanvas()->SetBorderMode(0);
fCanvas->GetCanvas()->SetGrid();
fCanvas->GetCanvas()->SetLogy();
fCanvas->GetCanvas()->Modified();
fCanvas->GetCanvas()->Update();


///////////////////////////////////////////////////////////

#include "TGLabel.h"

// TGLabel
const char gReadyMsg[] = "Ready. You can drag list tree items to any \
pad in the canvas, or to the \"Base\" folder of the list tree itself...";
TGLabel *fStatus = new TGLabel(frame, new TGHotString(gReadyMsg));
fStatus->SetTextJustify(kTextLeft);
fStatus->SetTextColor(0x0000ff);
fStatus->Enable();
// fStatus->Disable();
// if (fStatus->IsDisabled()) ;
// fStatus->SetText("XXX");
// fStatus->SetText(125);
// fStatus->SetFont("XXX");
fStatus->SetText(Form("abc%ld",100);
frame->AddFrame(fStatus, new TGLayoutHints(kLHintsExpandX | kLHintsCenterY,10, 10, 10, 10));


TGGC *fTextGC;
const TGFont *font = gClient->GetFont("-*-times-bold-r-*-*-18-*-*-*-*-*-*-*");
if (!font) font = gClient->GetResourcePool()->GetDefaultFont();
FontStruct_t labelfont = font->GetFontStruct();
GCValues_t   gval;
gval.fMask = kGCBackground | kGCFont | kGCForeground;
gval.fFont = font->GetFontHandle();
gClient->GetColorByName("yellow", gval.fBackground);
fTextGC = gClient->GetGC(&gval, kTRUE);
ULong_t bcolor, ycolor;
gClient->GetColorByName("yellow", ycolor);
gClient->GetColorByName("blue", bcolor);
fStatus = new TGLabel(frame, "OwnFont & Bck/ForgrColor", fTextGC->GetGC(), labelfont, kChildFrame, bcolor);//
fStatus->SetTextColor(ycolor);
// fStatus->ChangeOptions(fStatus->GetOptions() | kFixedSize);
// fStatus->Resize(350, 80);
frame->AddFrame(fStatus, new TGLayoutHints(kLHintsNormal, 5, 5, 3, 4));


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// TGTextEntry
// 单个文本框
TGTextEntry *fTestText = new TGTextEntry(frame, new TGTextBuffer(100));
fTestText->SetToolTipText("This is a text entry widget");
fTestText->Resize(300, fTestText->GetDefaultHeight());
frame->AddFrame(fTestText, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 2, 2, 2));
// fTestText->Clear();//清除内容
std::string command = fTestText->GetText();



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGIcon.h"
#include "TGResourcePool.h"
#include "TGPicture.h"

// TGPicture TGPicturePool TGIcon
// 插入系统自带的小图片
const char * const icon1[] =
{
"16 16 8 1",
"    c None s None",
".   c #808080",
"X   c #FFFF00",
"o   c #c0c0c0",
"O   c black",
"+   c #00FFFF",
"@   c #00FF00",
"#   c white",
"     .....      ",
"   ..XXoooOO    ",
"  .+XXXoooooO   ",
" .@++XXoooo#oO  ",
" .@@+XXooo#ooO  ",
".oo@@+Xoo#ooooO ",
".ooo@+.O.oooooO ",
".oooo@O#OoooooO ",
".oooo#.O.+ooooO ",
".ooo#oo#@X+oooO ",
" .o#oooo@X++oO  ",
" .#ooooo@XX++O  ",
"  .ooooo@@XXO   ",
"   ..ooo@@OO    ",
"     ..OOO      ",
"                "
};
TString name = "myicon";
ULong_t yellow;
gClient->GetColorByName("yellow", yellow);
TGPicturePool *picpool = gClient->GetResourcePool()->GetPicturePool();
const TGPicture *iconpic = picpool->GetPicture(name.Data(),(char **)icon1);
TGIcon *icon = new TGIcon(frame, iconpic, 40, 40, kChildFrame, yellow);
frame->AddFrame(icon, new TGLayoutHints(kLHintsLeft, 1,15,1,1));


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGSimpleTable.h"

// TGSimpleTable
// 简单数据表格
Double_t     **fData;
UInt_t         fNDataRows;
UInt_t         fNDataColumns;
UInt_t         fNTableRows;
UInt_t         fNTableColumns;
TGSimpleTable *fSimpleTable;
Int_t i = 0, j = 0;
fData = new Double_t*[fNDataRows];// Create the needed data.
for (i = 0; i < (Int_t)fNDataRows; i++) {
   fData[i] = new Double_t[fNDataColumns];
   for (j = 0; j < (Int_t)fNDataColumns; j++) {
      fData[i][j] = 10 * i + j;
   }
}
fSimpleTable = new TGSimpleTable(frame, IDs, fData, fNTableRows, fNTableColumns);
frame->AddFrame(fSimpleTable, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGImageMap.h"		 
// TGImageMap
// 插入图片
TGImageMap* fImageMap;
fImageMap = new TGImageMap(frame, "picture.jpg");
frame->AddFrame(fImageMap);
fImageMap->Connect("RegionClicked(Int_t)", "WorldMap", this,"PrintCode(Int_t)");



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TGTextViewStream.h"		 
		 
// TGTextViewStream
// 数据流输出框
TGTextViewostream *fTextView;
TGTextEntry       *fCommand;
fTextView = new TGTextViewostream(frame1, 500, 300);
frame1->AddFrame(fTextView, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 0));
fCommand = new TGTextEntry(frame2, (const char *)"", 20);
fCommand->Connect("ReturnPressed()", "TextViewMainFrame", this, "HandleReturn()");
frame2->AddFrame(fCommand, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
void HandleReturn()
{
   std::string line;
   std::string command = fCommand->GetText();
   *fTextView << gSystem->GetFromPipe(command.c_str()).Data() << std::endl;
   fTextView->ShowBottom();
   fCommand->Clear();
}

		 
// 
// note.cc ends here










