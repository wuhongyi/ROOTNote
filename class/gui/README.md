<!-- README.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 6月 25 16:11:28 2016 (+0800)
;; Last-Updated: 一 9月  4 15:32:54 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 55
;; URL: http://wuhongyi.cn -->

# README

```cpp
// System predefined widget message types. Message types are constants  
// that indicate which widget sent the message and by which widget      
// function (sub-message). Make sure your own message types don't clash  
// whith the ones defined in this file. ROOT reserves all message ids   
// between 0 - 1000. User defined messages should be in the range       
// 1001 - 10000. Sub-messages must always be in the range 1-255.        
// To use MK_MSG() just cast your message id's to an EWidgetMessageType.

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
```


```cpp
//Buttons.h
enum EEventType {
   kNoEvent       =  0,
   kButton1Down   =  1, kButton2Down   =  2, kButton3Down   =  3, kKeyDown  =  4,
   kWheelUp       =  5, kWheelDown     =  6, kButton1Shift  =  7, kButton1ShiftMotion  =  8,
   kButton1Up     = 11, kButton2Up     = 12, kButton3Up     = 13, kKeyUp    = 14,
   kButton1Motion = 21, kButton2Motion = 22, kButton3Motion = 23, kKeyPress = 24,
   kArrowKeyPress = 25, kArrowKeyRelease = 26,
   kButton1Locate = 41, kButton2Locate = 42, kButton3Locate = 43, kESC      = 27,
   kMouseMotion   = 51, kMouseEnter    = 52, kMouseLeave    = 53,
   kButton1Double = 61, kButton2Double = 62, kButton3Double = 63
};

enum EEditMode {
   kPolyLine  = 1,  kSPolyLine = 2,  kPolyGone  = 3,
   kSPolyGone = 4,  kBox       = 5,  kDelete    = 6,
   kPad       = 7,  kText      = 8,  kEditor    = 9,
   kExit      = 10, kPave      = 11, kPaveLabel = 12,
   kPaveText  = 13, kPavesText = 14, kEllipse   = 15,
   kArc       = 16, kLine      = 17, kArrow     = 18,
   kGraph     = 19, kMarker    = 20, kPolyMarker= 21,
   kPolyLine3D= 22, kWbox      = 23, kGaxis     = 24,
   kF1        = 25, kF2        = 26, kF3        = 27,
   kDiamond   = 28, kPolyMarker3D = 29, kButton = 101,
   kCutG      =100, kCurlyLine =200, kCurlyArc  = 201
};
```




  - TGCheckButton
  - TGComboBox
  - TGGroupFrame
  - TGIcon
  - TGLabel
  - TGListBox
  - TGMenuBar
  - TGNumberEntry
  - TGPicture
  - TGPicturePool
  - TGPopupMenu
  - TGRadioButton
  - TGSplitButton
  - TGTextEntry
  - TGTripleSlider
  - TGVButtonGroup
  - TGTextButton


```cpp
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
```



```cpp
static const char *gFonts[][2] = {    //   unix name,     name
   { "",                                           ""                         }, //not used
   { "-*-times-medium-i-*-*-12-*-*-*-*-*-*-*",     "1. times italic"          },
   { "-*-times-bold-r-*-*-12-*-*-*-*-*-*-*",       "2. times bold"            },
   { "-*-times-bold-i-*-*-12-*-*-*-*-*-*-*",       "3. times bold italic"     },
   { "-*-helvetica-medium-r-*-*-12-*-*-*-*-*-*-*", "4. helvetica"             },
   { "-*-helvetica-medium-o-*-*-12-*-*-*-*-*-*-*", "5. helvetica italic"      },
   { "-*-helvetica-bold-r-*-*-12-*-*-*-*-*-*-*",   "6. helvetica bold"        },
   { "-*-helvetica-bold-o-*-*-12-*-*-*-*-*-*-*",   "7. helvetica bold italic" },
   { "-*-courier-medium-r-*-*-12-*-*-*-*-*-*-*",   "8. courier"               },
   { "-*-courier-medium-o-*-*-12-*-*-*-*-*-*-*",   "9. courier italic"        },
   { "-*-courier-bold-r-*-*-12-*-*-*-*-*-*-*",     "10. courier bold"         },
   { "-*-courier-bold-o-*-*-12-*-*-*-*-*-*-*",     "11. courier bold italic"  },
   { "-*-symbol-medium-r-*-*-12-*-*-*-*-*-*-*",    "12. symbol"               },
   { "-*-times-medium-r-*-*-12-*-*-*-*-*-*-*",     "13. times"                },
   { 0, 0}
};
```





```cpp

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
```


<!-- README.md ends here -->
