<!-- gui.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 09:27:16 2016 (+0800)
;; Last-Updated: 二 11月  8 21:17:40 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 21
;; URL: http://wuhongyi.cn -->

# TGFrame

//---- frame states

enum EFrameState {
   kIsVisible  = BIT(0),
   kIsMapped   = kIsVisible,
   kIsArranged = BIT(1)
};

//---- frame cleanup
enum EFrameCleanup {
   kNoCleanup    = 0,
   kLocalCleanup = 1,
   kDeepCleanup  = -1
};

//---- types of frames (and borders)

enum EFrameType {
   kChildFrame      = 0,
   kMainFrame       = BIT(0),
   kVerticalFrame   = BIT(1),
   kHorizontalFrame = BIT(2),
   kSunkenFrame     = BIT(3),
   kRaisedFrame     = BIT(4),
   kDoubleBorder    = BIT(5),
   kFitWidth        = BIT(6),
   kFixedWidth      = BIT(7),
   kFitHeight       = BIT(8),
   kFixedHeight     = BIT(9),
   kFixedSize       = (kFixedWidth | kFixedHeight),
   kOwnBackground   = BIT(10),
   kTransientFrame  = BIT(11),
   kTempFrame       = BIT(12),
   kMdiMainFrame    = BIT(13),
   kMdiFrame        = BIT(14)
};

//---- MWM hints stuff

enum EMWMHints {
   // functions
   kMWMFuncAll      = BIT(0),
   kMWMFuncResize   = BIT(1),
   kMWMFuncMove     = BIT(2),
   kMWMFuncMinimize = BIT(3),
   kMWMFuncMaximize = BIT(4),
   kMWMFuncClose    = BIT(5),

   // input mode
   kMWMInputModeless                = 0,
   kMWMInputPrimaryApplicationModal = 1,
   kMWMInputSystemModal             = 2,
   kMWMInputFullApplicationModal    = 3,

   // decorations
   kMWMDecorAll      = BIT(0),
   kMWMDecorBorder   = BIT(1),
   kMWMDecorResizeH  = BIT(2),
   kMWMDecorTitle    = BIT(3),
   kMWMDecorMenu     = BIT(4),
   kMWMDecorMinimize = BIT(5),
   kMWMDecorMaximize = BIT(6)
};

//---- drag and drop

enum EDNDFlags {
   kIsDNDSource = BIT(0),
   kIsDNDTarget = BIT(1)
};


This class subclasses TGWindow, used as base class for some simple widgets (buttons, labels, etc.).
It provides:
 - position & dimension fields
 - an 'options' attribute (see constant above)
 - a generic event handler
 - a generic layout mechanism
 - a generic border


TGCompositeFrame
This class is the base class for composite widgets (menu bars, list boxes, etc.).
It provides: 
 - a layout manager
 - a frame container (TList *)


TGVerticalFrame
Composite frame with vertical child layout

TGHorizontalFrame
Composite frame with horizontal child layout


TGMainFrame
This class defines top level windows that interact with the system Window Manager (WM or MWM for Motif Window Manager).


TGTransientFrame
This class defines transient windows that typically are used for dialogs.


TGGroupFrame
A group frame is a composite frame with a border and a title.
It is typically used to group a number of logically related widgets visually together.


TGHeaderFrame
Horizontal Frame used to contain header buttons and splitters in a list view. Used to have resizable column headers. 


-----

# TGButton

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


//--- Button states

enum EButtonState {
   kButtonUp,
   kButtonDown,
   kButtonEngaged,
   kButtonDisabled
};

----

# TGListBox

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
// TGListBox                                                            //
//                                                                      //
// A TGListBox widget.                                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGComboBox

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

----

# TGNumberEntry

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGNumberEntry, TGNumberEntryField and TGNumberFormat                 //
//                                                                      //
// TGNumberEntry is a number entry input widget with up/down buttons.   //
// TGNumberEntryField is a number entry input widget.                   //
// TGNumberFormat contains enum types to specify the numeric format .   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

class TGNumberFormat {
public:
   enum EStyle {             // Style of number entry field
      kNESInteger = 0,       // Integer
      kNESRealOne = 1,       // Fixed fraction real, one digit
      kNESRealTwo = 2,       // Fixed fraction real, two digit
      kNESRealThree = 3,     // Fixed fraction real, three digit
      kNESRealFour = 4,      // Fixed fraction real, four digit
      kNESReal = 5,          // Real number
      kNESDegree = 6,        // Degree
      kNESMinSec = 7,        // Minute:seconds
      kNESHourMin = 8,       // Hour:minutes
      kNESHourMinSec = 9,    // Hour:minute:seconds
      kNESDayMYear = 10,     // Day/month/year
      kNESMDayYear = 11,     // Month/day/year
      kNESHex = 12           // Hex
   };

   enum EAttribute {         // Attributes of number entry field
      kNEAAnyNumber = 0,     // Any number
      kNEANonNegative = 1,   // Non-negative number
      kNEAPositive = 2       // Positive number
   };

   enum ELimit {             // Limit selection of number entry field
      kNELNoLimits = 0,      // No limits
      kNELLimitMin = 1,      // Lower limit only
      kNELLimitMax = 2,      // Upper limit only
      kNELLimitMinMax = 3    // Both lower and upper limits
   };

   enum EStepSize {          // Step for number entry field increase
      kNSSSmall = 0,         // Small step
      kNSSMedium = 1,        // Medium step
      kNSSLarge = 2,         // Large step
      kNSSHuge = 3           // Huge step
   };

   virtual ~TGNumberFormat() { }
   ClassDef(TGNumberFormat,0)  // Class defining namespace for several enums used by TGNumberEntry
};

----

# TGMenu

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
// TGMenuEntry                                                          //
//                                                                      //
// This class contains all information about a menu entry.              //
// It is a fully protected class used internally by TGPopupMenu.        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGPopupMenu                                                          //
//                                                                      //
// This class creates a popup menu object. Popup menu's are attached    //
// to TGMenuBar objects.                                                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGMenuTitle                                                          //
//                                                                      //
// This class creates a menu title. A menu title is a frame             //
// to which a popup menu can be attached. Menu titles are automatically //
// created when adding a popup menu to a menubar.                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGMenuBar                                                            //
//                                                                      //
// This class creates a menu bar.                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//--- Menu entry status mask

enum EMenuEntryState {
   kMenuActiveMask     = BIT(0),
   kMenuEnableMask     = BIT(1),
   kMenuDefaultMask    = BIT(2),
   kMenuCheckedMask    = BIT(3),
   kMenuRadioMask      = BIT(4),
   kMenuHideMask       = BIT(5),
   kMenuRadioEntryMask = BIT(6)
};

//--- Menu entry types

enum EMenuEntryType {
   kMenuSeparator,
   kMenuLabel,
   kMenuEntry,
   kMenuPopup
};

----

# TGDoubleSlider

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

enum EDoubleSliderSize {
   //--- sizes for vert. and horz. sliders
   kDoubleSliderWidth  = 24,
   kDoubleSliderHeight = kDoubleSliderWidth
};


enum EDoubleSliderScale {
   //--- type of slider scale
   kDoubleScaleNo        = BIT(0),
   kDoubleScaleDownRight = BIT(1),
   kDoubleScaleBoth      = BIT(2)
};

----

# TripleSlider

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


----

# TRootEmbeddedCanvas

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TRootEmbeddedCanvas                                                  //
//                                                                      //
// This class creates a TGCanvas in which a TCanvas is created. Use     //
// GetCanvas() to get a pointer to the TCanvas.                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


----

# TGLabel

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGLabel                                                              //
//                                                                      //
// This class handles GUI labels.                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGTextEntry

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

----

# TGPicture

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGPicture, TGSelectdPicture & TGPicturePool                          //
//                                                                      //
// The TGPicture class implements pictures and icons used in the        //
// different GUI elements and widgets. The TGPicturePool class          //
// implements a TGPicture cache. TGPictures are created, managed and    //
// destroyed by the TGPicturePool.                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGSimpleTable

A simple table that owns it's interface.

----

# TGTable

A table used to visualize data from diffent sources.

----

# TGImageMap

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGImageMap (with TGRegion and TGRegionWithId help classes)           //
//                                                                      //
// A TGImageMap provides the functionality like a clickable image in    //
// a web browser with sensitive regions (MAP HTML tag).                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGTextViewStream

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGTextViewStream                                                     //
//                                                                      //
// A TGTextViewStream is a text viewer widget. It is a specialization   //
// of TGTextView and std::ostream, and it uses a TGTextViewStreamBuf,   //
// who inherits from std::streambuf, allowing to stream text directly   //
// to the text view in a cout-like fashion                              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGView

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


----

# TGTab

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


----

# TGSlider

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

//--- sizes for vert. and horz. sliders

enum ESliderSize {
   kSliderWidth  = 24,
   kSliderHeight = kSliderWidth
};


enum ESliderType {
   //--- slider types (type of slider picture)
   kSlider1        = BIT(0),
   kSlider2        = BIT(1),

   //--- scaling of slider
   kScaleNo        = BIT(2),
   kScaleDownRight = BIT(3),
   kScaleBoth      = BIT(4)
};


----

# TGScrollBar

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

//--- scrollbar types

enum EScrollBarMode {
   kSBHorizontal,
   kSBVertical
};


----

# TGListView

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

enum EListViewMode {
   kLVLargeIcons,
   kLVSmallIcons,
   kLVList,
   kLVDetails
};

----

# TGCanvas

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGCanvas and TGViewPort and TGContainer                              //
//                                                                      //
// A TGCanvas is a frame containing two scrollbars (horizontal and      //
// vertical) and a viewport. The viewport acts as the window through    //
// which we look at the contents of the container frame.                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGListTree

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


----

# TGColorSelect

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




----

# TGColorDialog

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


----

# TGClient

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGClient                                                             //
//                                                                      //
// Window client. In client server windowing systems, like X11 this     //
// class is used to make the initial connection to the window server.   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----

# TGLayout

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// A number of different layout classes (TGLayoutManager,               //
// TGVerticalLayout, TGHorizontalLayout, TGLayoutHints, etc.).          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//---- layout hints

enum ELayoutHints {
   kLHintsNoHints = 0,
   kLHintsLeft    = BIT(0),
   kLHintsCenterX = BIT(1),
   kLHintsRight   = BIT(2),
   kLHintsTop     = BIT(3),
   kLHintsCenterY = BIT(4),
   kLHintsBottom  = BIT(5),
   kLHintsExpandX = BIT(6),
   kLHintsExpandY = BIT(7),
   kLHintsNormal  = (kLHintsLeft | kLHintsTop)
   // bits 8-11 used by ETableLayoutHints
};


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGLayoutHints                                                        //
//                                                                      //
// This class describes layout hints used by the layout classes.        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGLayoutManager                                                      //
//                                                                      //
// Frame layout manager. This is an abstract class.                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGVerticalLayout and TGHorizontalLayout managers.                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGRowLayout and TGColumnLayout managers.                             //
//                                                                      //
// The follwing two layout managers do not make use of TGLayoutHints.   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGMatrixLayout manager.                                              //
//                                                                      //
// This layout managers does not make use of TGLayoutHints.             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGTileLayout, TGListLayout and TGListDetailsLayout managers.         //
//                                                                      //
// This are layout managers for the TGListView widget.                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

----


<!-- gui.md ends here -->
