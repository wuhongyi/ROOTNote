<!-- TGFrame.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 09:42:03 2016 (+0800)
;; Last-Updated: 三 11月  9 11:09:28 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->

# TGFrame

```
This source is based on Xclass95, a Win95-looking GUI toolkit.
Copyright (C) 1996, 1997 David Barth, Ricky Ralston, Hector Peraza.

Xclass95 is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
```

The frame classes describe the different "dressed" GUI windows.      
                                                                     
The TGFrame class is a subclasses of TGWindow, and is used as base   
class for some simple widgets (buttons, labels, etc.).              
It provides:                                                         
 - position & dimension fields                                       
 - an 'options' attribute (see constant above)                       
 - a generic event handler                                           
 - a generic layout mechanism                                        
 - a generic border                                                  
                                                                     
The TGCompositeFrame class is the base class for composite widgets   
(menu bars, list boxes, etc.).                                       
It provides:                                                         
 - a layout manager                                                  
 - a frame container (TList *)                                       
                                                                 
The TGVerticalFrame and TGHorizontalFrame are composite frame that   
layout their children in vertical or horizontal way.                 
                                                                     
The TGMainFrame class defines top level windows that interact with   
the system Window Manager.                                           
                                                                     
The TGTransientFrame class defines transient windows that typically  
are used for dialogs windows.                                        

The TGGroupFrame is a composite frame with a border and a title.     
It is typically used to group a number of logically related widgets  
visually together.



TGFrame 继承 TGWindow, TQObject  
This class subclasses TGWindow, used as base class for some simple widgets (buttons, labels, etc.).  
It provides:  
 - position & dimension fields
 - an 'options' attribute (see constant above)
 - a generic event handler
 - a generic layout mechanism
 - a generic border
 
TGCompositeFrame 继承 TGFrame  
This class is the base class for composite widgets (menu bars, list boxes, etc.).  
It provides:   
 - a layout manager 
 - a frame container (TList *)


TGVerticalFrame 继承 TGCompositeFrame  
Composite frame with vertical child layout


TGHorizontalFrame 继承 TGCompositeFrame  
Composite frame with horizontal child layout


TGMainFrame 继承 TGCompositeFrame  
This class defines top level windows that interact with the system Window Manager (WM or MWM for Motif Window Manager).


TGTransientFrame 继承 TGMainFrame  
This class defines transient windows that typically are used for dialogs.


TGGroupFrame 继承 TGCompositeFrame  
A group frame is a composite frame with a border and a title.
It is typically used to group a number of logically related widgets visually together.


TGHeaderFrame 继承 TGHorizontalFrame  
Horizontal Frame used to contain header buttons and splitters in a list view. Used to have resizable column headers. 


## class

```cpp
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
```


**TGFrame**

```cpp
   // Default colors and graphics contexts
   static Pixel_t     GetDefaultFrameBackground();/// Get default frame background.
   static Pixel_t     GetDefaultSelectedBackground();/// Get default selected frame background.
   static Pixel_t     GetWhitePixel();/// Get white pixel value.
   static Pixel_t     GetBlackPixel();/// Get black pixel value.
   static const TGGC &GetBlackGC();/// Get black graphics context.
   static const TGGC &GetWhiteGC();/// Get white graphics context.
   static const TGGC &GetHilightGC();/// Get highlight color graphics context.
   static const TGGC &GetShadowGC();/// Get shadow color graphics context.
   static const TGGC &GetBckgndGC();/// Get background color graphics context.

   TGFrame(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
           UInt_t options = 0, Pixel_t back = GetDefaultFrameBackground());
/// Create a TGFrame object. Options is an OR of the EFrameTypes.

   TGFrame(TGClient *c, Window_t id, const TGWindow *parent = 0);
/// Create a frame using an externally created window. For example
/// to register the root window (called by TGClient), or a window
/// created via TVirtualX::InitWindow() (id is obtained with
/// TVirtualX::GetWindowID()).

   virtual ~TGFrame();

   virtual void DeleteWindow();
/// Delete window. Use single shot timer to call final delete method.
/// We use this indirect way since deleting the window in its own
/// execution "thread" can cause side effects because frame methods
/// can still be called while the window object has already been deleted.

   virtual void ReallyDelete() { delete this; }

   UInt_t GetEventMask() const { return fEventMask; }
   void   AddInput(UInt_t emask);
/// Add events specified in the emask to the events the frame should handle.

   void   RemoveInput(UInt_t emask);
/// Remove events specified in emask from the events the frame should handle.

   virtual Bool_t HandleEvent(Event_t *event);
/// Handle all frame events. Events are dispatched to the specific
/// event handlers.
   virtual Bool_t HandleConfigureNotify(Event_t *event);
/// This event is generated when the frame is resized.
   
   virtual Bool_t HandleButton(Event_t *) { return kFALSE; }
   virtual Bool_t HandleDoubleClick(Event_t *) { return kFALSE; }
   virtual Bool_t HandleCrossing(Event_t *) { return kFALSE; }
   virtual Bool_t HandleMotion(Event_t *) { return kFALSE; }
   virtual Bool_t HandleKey(Event_t *) { return kFALSE; }
   virtual Bool_t HandleFocusChange(Event_t *) { return kFALSE; }
   virtual Bool_t HandleClientMessage(Event_t *event);
/// Handle a client message. Client messages are the ones sent via
/// TGFrame::SendMessage (typically by widgets).

   virtual Bool_t HandleSelection(Event_t *) { return kFALSE; }
   virtual Bool_t HandleSelectionRequest(Event_t *) { return kFALSE; }
   virtual Bool_t HandleSelectionClear(Event_t *) { return kFALSE; }
   virtual Bool_t HandleColormapChange(Event_t *) { return kFALSE; }
   virtual Bool_t HandleDragEnter(TGFrame *) { return kFALSE; }
   virtual Bool_t HandleDragLeave(TGFrame *) { return kFALSE; }
   virtual Bool_t HandleDragMotion(TGFrame *) { return kFALSE; }
   virtual Bool_t HandleDragDrop(TGFrame *, Int_t /*x*/, Int_t /*y*/, TGLayoutHints*)
                     { return kFALSE; }
   virtual void   ProcessedConfigure(Event_t *event)
                     { Emit("ProcessedConfigure(Event_t*)", (Long_t)event); } //*SIGNAL*
   virtual void   ProcessedEvent(Event_t *event)
                     { Emit("ProcessedEvent(Event_t*)", (Long_t)event); } //*SIGNAL*

   virtual void   SendMessage(const TGWindow *w, Long_t msg, Long_t parm1, Long_t parm2);
/// Send message (i.e. event) to window w. Message is encoded in one long
/// as message type and up to two long parameters.

   virtual Bool_t ProcessMessage(Long_t, Long_t, Long_t) { return kFALSE; }

   virtual TGDimension GetDefaultSize() const ;
   virtual void    Move(Int_t x, Int_t y); /// Move frame.
   virtual void    Resize(UInt_t w = 0, UInt_t h = 0);
/// Resize the frame.
/// If w=0 && h=0 - Resize to default size

   virtual void    Resize(TGDimension size);/// Resize the frame.
   virtual void    MoveResize(Int_t x, Int_t y, UInt_t w = 0, UInt_t h = 0);
/// Move and/or resize the frame.
/// If w=0 && h=0 - Resize to default size

   virtual UInt_t  GetDefaultWidth() const { return GetDefaultSize().fWidth; }
   virtual UInt_t  GetDefaultHeight() const { return GetDefaultSize().fHeight; }
   virtual Pixel_t GetBackground() const { return fBackground; }
   virtual void    ChangeBackground(Pixel_t back); /// Change frame background color.
   virtual void    SetBackgroundColor(Pixel_t back);
/// Set background color (override from TGWindow base class).
/// Same effect as ChangeBackground().

   virtual Pixel_t GetForeground() const; /// Return frame foreground color.
   virtual void    SetForegroundColor(Pixel_t /*fore*/) { }
   virtual UInt_t  GetOptions() const { return fOptions; }
   virtual void    ChangeOptions(UInt_t options); /// Change frame options. Options is an OR of the EFrameTypes.
   virtual void    Layout() { }
   virtual void    MapSubwindows() { }  // Simple frames do not have subwindows
                                        // Redefine this in TGCompositeFrame!
   virtual void    ReparentWindow(const TGWindow *p, Int_t x = 0, Int_t y = 0)
                     { TGWindow::ReparentWindow(p, x, y); Move(x, y); }
   virtual void    MapWindow() { TGWindow::MapWindow(); if (fFE) fFE->fState |= kIsVisible; }
   virtual void    MapRaised() { TGWindow::MapRaised(); if (fFE) fFE->fState |= kIsVisible; }
   virtual void    UnmapWindow() { TGWindow::UnmapWindow(); if (fFE) fFE->fState &= ~kIsVisible; }

   virtual void    DrawBorder(); /// Draw frame border.
   virtual void    DrawCopy(Handle_t /*id*/, Int_t /*x*/, Int_t /*y*/) { }
   virtual void    Activate(Bool_t) { }
   virtual Bool_t  IsActive() const { return kFALSE; }
   virtual Bool_t  IsComposite() const { return kFALSE; }
   virtual Bool_t  IsEditable() const { return kFALSE; }
   virtual void    SetEditable(Bool_t) {}
   virtual void    SetLayoutBroken(Bool_t = kTRUE) {}
   virtual Bool_t  IsLayoutBroken() const { return kFALSE; }
   virtual void    SetCleanup(Int_t = kLocalCleanup) { /* backward compatebility */ }

   virtual void    SetDragType(Int_t type);
   virtual void    SetDropType(Int_t type);
   virtual Int_t   GetDragType() const;
/// Returns drag source type.
/// If frame is not "draggable" - return zero

   virtual Int_t   GetDropType() const;
/// Returns drop target type.
/// If frame cannot accept drop - return zero

   UInt_t GetWidth() const { return fWidth; }
   UInt_t GetHeight() const { return fHeight; }
   UInt_t GetMinWidth() const { return fMinWidth; }
   UInt_t GetMinHeight() const { return fMinHeight; }
   UInt_t GetMaxWidth() const { return fMaxWidth; }
   UInt_t GetMaxHeight() const { return fMaxHeight; }
   TGDimension GetSize() const { return TGDimension(fWidth, fHeight); }
   Int_t  GetX() const { return fX; }
   Int_t  GetY() const { return fY; }
   Int_t  GetBorderWidth() const { return fBorderWidth; }

   TGFrameElement *GetFrameElement() const { return fFE; }
   void SetFrameElement(TGFrameElement *fe) { fFE = fe; }

   Bool_t Contains(Int_t x, Int_t y) const
      { return ((x >= 0) && (x < (Int_t)fWidth) && (y >= 0) && (y < (Int_t)fHeight)); }
   virtual TGFrame *GetFrameFromPoint(Int_t x, Int_t y)
      { return (Contains(x, y) ? this : 0); }

   // Modifiers (without graphic update)
   virtual void SetX(Int_t x) { fX = x; }
   virtual void SetY(Int_t y) { fY = y; }
   virtual void SetWidth(UInt_t w) { fWidth = w; }
   virtual void SetHeight(UInt_t h) { fHeight = h; }
   virtual void SetMinWidth(UInt_t w) { fMinWidth = w; }
   virtual void SetMinHeight(UInt_t h) { fMinHeight = h; }
   virtual void SetMaxWidth(UInt_t w) { fMaxWidth = w; }
   virtual void SetMaxHeight(UInt_t h) { fMaxHeight = h; }
   virtual void SetSize(const TGDimension &s) { fWidth = s.fWidth; fHeight = s.fHeight; }

   // Printing and saving
   virtual void Print(Option_t *option="") const;/// Print window id.
   void SaveUserColor(std::ostream &out, Option_t *);/// Save a user color in a C++ macro file - used in SavePrimitive().
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a frame widget as a C++ statement(s) on output stream out.

   // dummy to remove from context menu
   virtual void        Delete(Option_t * /*option*/ ="") { }
   virtual TObject    *DrawClone(Option_t * /*option */="") const { return 0; }
   virtual void        DrawClass() const { }
   virtual void        Dump() const { }
   virtual void        Inspect() const { }
   virtual void        SetDrawOption(Option_t * /*option*/="") { }

   // drag and drop...
   void                SetDNDSource(Bool_t onoff)
                       { if (onoff) fDNDState |= kIsDNDSource; else fDNDState &= ~kIsDNDSource; }
   void                SetDNDTarget(Bool_t onoff)
                       { if (onoff) fDNDState |= kIsDNDTarget; else fDNDState &= ~kIsDNDTarget; }
   Bool_t              IsDNDSource() const { return fDNDState & kIsDNDSource; }
   Bool_t              IsDNDTarget() const { return fDNDState & kIsDNDTarget; }

   virtual TDNDData   *GetDNDData(Atom_t /*dataType*/) { return 0; }
   virtual Bool_t      HandleDNDDrop(TDNDData * /*DNDData*/) { return kFALSE; }
   virtual Atom_t      HandleDNDPosition(Int_t /*x*/, Int_t /*y*/, Atom_t /*action*/,
                                         Int_t /*xroot*/, Int_t /*yroot*/) { return kNone; }
   virtual Atom_t      HandleDNDEnter(Atom_t * /*typelist*/) { return kNone; }
   virtual Bool_t      HandleDNDLeave() { return kFALSE; }
   virtual Bool_t      HandleDNDFinished() { return kFALSE; }
```

**TGCompositeFrame**

```cpp
   TGCompositeFrame(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
                    UInt_t options = 0,
                    Pixel_t back = GetDefaultFrameBackground());
/// Create a composite frame. A composite frame has in addition to a TGFrame
/// also a layout manager and a list of child frames.

   TGCompositeFrame(TGClient *c, Window_t id, const TGWindow *parent = 0);
/// Create a frame using an externally created window. For example
/// to register the root window (called by TGClient), or a window
/// created via TVirtualX::InitWindow() (id is obtained with TVirtualX::GetWindowID()).


   virtual ~TGCompositeFrame();/// Delete a composite frame.

   virtual TList *GetList() const { return fList; }

   virtual UInt_t GetDefaultWidth() const
                     { return GetDefaultSize().fWidth; }
   virtual UInt_t GetDefaultHeight() const
                     { return GetDefaultSize().fHeight; }
   virtual TGDimension GetDefaultSize() const
                     { return (IsLayoutBroken() ? TGDimension(fWidth, fHeight) :
                               fLayoutManager->GetDefaultSize()); }
   virtual TGFrame *GetFrameFromPoint(Int_t x, Int_t y);/// Get frame located at specified point.
   virtual Bool_t TranslateCoordinates(TGFrame *child, Int_t x, Int_t y,
                                       Int_t &fx, Int_t &fy);
/// Translate coordinates to child frame.

   virtual void   MapSubwindows();
/// Map all sub windows that are part of the composite frame.

   virtual void   Layout();/// Layout the elements of the composite frame.
   virtual Bool_t HandleButton(Event_t *) { return kFALSE; }
   virtual Bool_t HandleDoubleClick(Event_t *) { return kFALSE; }
   virtual Bool_t HandleCrossing(Event_t *) { return kFALSE; }
   virtual Bool_t HandleMotion(Event_t *) { return kFALSE; }
   virtual Bool_t HandleKey(Event_t *) { return kFALSE; }
   virtual Bool_t HandleFocusChange(Event_t *) { return kFALSE; }
   virtual Bool_t HandleSelection(Event_t *) { return kFALSE; }
   virtual Bool_t HandleDragEnter(TGFrame *);/// Handle drag enter event.
   virtual Bool_t HandleDragLeave(TGFrame *);/// Handle drag leave event.
   virtual Bool_t HandleDragMotion(TGFrame *);/// Handle drag motion event.
   virtual Bool_t HandleDragDrop(TGFrame *frame, Int_t x, Int_t y, TGLayoutHints *lo);/// Handle drop event.
   virtual void   ChangeOptions(UInt_t options);
/// Change composite frame options. Options is an OR of the EFrameTypes.

   virtual Bool_t ProcessMessage(Long_t, Long_t, Long_t) { return kFALSE; }

   virtual TGLayoutManager *GetLayoutManager() const { return fLayoutManager; }
   virtual void SetLayoutManager(TGLayoutManager *l);
/// Set the layout manager for the composite frame.
/// The layout manager is adopted by the frame and will be deleted
/// by the frame.

   virtual TGFrameElement* FindFrameElement(TGFrame *f) const;/// Find frame-element holding frame f.

   virtual void   AddFrame(TGFrame *f, TGLayoutHints *l = 0);
/// Add frame to the composite frame using the specified layout hints.
/// If no hints are specified default hints TGLayoutHints(kLHintsNormal,0,0,0,0)
/// will be used. Most of the time, however, you will want to provide
/// specific hints. User specified hints can be reused many times
/// and need to be destroyed by the user. The added frames cannot not be
/// added to different composite frames but still need to be deleted by
/// the user.

   virtual void   RemoveAll(); /// Remove all frames from composite frame.
   virtual void   RemoveFrame(TGFrame *f); /// Remove frame from composite frame.
   virtual void   ShowFrame(TGFrame *f);/// Show sub frame.
   virtual void   HideFrame(TGFrame *f);/// Hide sub frame.
   Int_t          GetState(TGFrame *f) const;/// Get state of sub frame.
   Bool_t         IsVisible(TGFrame *f) const;/// Get state of sub frame.
   Bool_t         IsVisible(TGFrameElement *ptr) const { return (ptr->fState & kIsVisible); }
   Bool_t         IsArranged(TGFrame *f) const;/// Get state of sub frame.
   Bool_t         IsArranged(TGFrameElement *ptr) const { return (ptr->fState & kIsArranged); }
   Bool_t         IsComposite() const { return kTRUE; }
   virtual Bool_t IsEditable() const; /// Return kTRUE if frame is being edited.
   virtual void   SetEditable(Bool_t on = kTRUE);
/// Switch ON/OFF edit mode.
/// If edit mode is ON it is possible:
///  1. embed other ROOT GUI application (a la ActiveX)

   virtual void   SetLayoutBroken(Bool_t on = kTRUE); /// Set broken layout. No Layout method is called.
   virtual Bool_t IsLayoutBroken() const
                  { return fLayoutBroken || !fLayoutManager; }
   virtual void   SetEditDisabled(UInt_t on = 1);
/// Set edit disable flag for this frame and subframes
///  - if (on & kEditDisable) - disable edit for this frame and all subframes.

   virtual void   SetCleanup(Int_t mode = kLocalCleanup);
/// Turn on automatic cleanup of child frames in dtor.
/// if mode = kNoCleanup    - no automatic cleanup
/// if mode = kLocalCleanup - automatic cleanup in this composite frame only
/// if mode = kDeepCleanup  - automatic deep cleanup in this composite frame
///                           and all child composite frames (hierarchical)
/// Attention!
///    Hierarchical cleaning is dangerous and must be used with caution.
///    There are many GUI components (in ROOT and in user code) which do not
///    use Clean method in destructor ("custom deallocation").
///    Adding such component to GUI container which is using hierarchical
///    cleaning will produce seg. violation when container is deleted.
///    The reason is double deletion: first whem Clean method is invoked,
///    then at "custom deallocation".
///    We are going to correct all ROOT code to make it to be
///    consitent with hierarchical cleaning scheeme.

   virtual Int_t  MustCleanup() const { return fMustCleanup; }
   virtual void   Cleanup();
/// Cleanup and delete all objects contained in this composite frame.
/// This will delete all objects added via AddFrame().
/// CAUTION: all objects (frames and layout hints) must be unique, i.e.
/// cannot be shared.

   virtual void   SetMapSubwindows(Bool_t on) {  fMapSubwindows = on; }
   virtual Bool_t IsMapSubwindows() const { return fMapSubwindows; }

   virtual void   Print(Option_t *option="") const;/// Print all frames in this composite frame.
   virtual void   ChangeSubframesBackground(Pixel_t back);
/// Change background color for this frame and all subframes.

   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a composite frame widget as a C++ statement(s) on output stream out.

   virtual void   SavePrimitiveSubframes(std::ostream &out, Option_t *option = "");
/// Auxilary protected method  used to save subframes.
```

**TGVerticalFrame**

```cpp
   TGVerticalFrame(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
                   UInt_t options = kChildFrame,
                   Pixel_t back = GetDefaultFrameBackground()) :
      TGCompositeFrame(p, w, h, options | kVerticalFrame, back) { SetWindowName(); }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a vertical frame widget as a C++ statement(s) on output stream out.
```

**TGHorizontalFrame**

```cpp
   TGHorizontalFrame(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
                     UInt_t options = kChildFrame,
                     Pixel_t back = GetDefaultFrameBackground()) :
      TGCompositeFrame(p, w, h, options | kHorizontalFrame, back) { SetWindowName(); }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a horizontal frame widget as a C++ statement(s) on output stream out.
```

**TGMainFrame**

```cpp
   TGMainFrame(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
               UInt_t options = kVerticalFrame);
/// Create a top level main frame. A main frame interacts
/// with the window manager.

   virtual ~TGMainFrame();/// TGMainFrame destructor.

   virtual Bool_t HandleKey(Event_t *event);/// Handle keyboard events.
   virtual Bool_t HandleClientMessage(Event_t *event);/// Handle client messages sent to this frame.
   virtual Bool_t HandleSelection(Event_t *event);/// Handle primary selection event.
   virtual Bool_t HandleSelectionRequest(Event_t *event);/// Handle selection request event.
   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button events.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion events.
   virtual Bool_t SaveFrameAsCodeOrImage();
/// Opens dialog window allowing user to save the frame contents
/// as a ROOT macro or as an image.
/// Returns kTRUE if something was saved.
/// This is bound to Ctrl-S by default.

   virtual void   SendCloseMessage();
/// Send close message to self. This method should be called from
/// a button to close this window.

   virtual void   CloseWindow();   //*SIGNAL*
/// Close and delete main frame. We get here in response to ALT+F4 or
/// a window manager close command. To terminate the application when this
/// happens override this method and call gApplication->Terminate(0) or
/// make a connection to this signal (if after the slot this method
/// should not be called call DontCallClose() in the slot).
/// By default the window will be deleted.

   void DontCallClose();
/// Typically call this method in the slot connected to the CloseWindow()
/// signal to prevent the calling of the default or any derived CloseWindow()
/// methods to prevent premature or double deletion of this window.

   void SetWindowName(const char *name = 0);
/// Set window name. This is typically done via the window manager.

   void SetIconName(const char *name);
/// Set window icon name. This is typically done via the window manager.

   const TGPicture *SetIconPixmap(const char *iconName);
/// Set window icon pixmap by name. This is typically done via the window
/// manager. Icon can be in any image format supported by TImage, e.g.
/// GIF, XPM, PNG, JPG .. or even PS, PDF (see EImageFileTypes in TImage.h
/// for the full list of supported formats).

   void SetIconPixmap(char **xpm_array);
/// Set window icon by xpm array. That allows to have icons
/// builtin to the source code.

   void SetClassHints(const char *className, const char *resourceName);
/// Set the windows class and resource name. Used to get the right
/// resources from the resource database. However, ROOT applications
/// will typically use the .rootrc file for this.

   void SetMWMHints(UInt_t value, UInt_t funcs, UInt_t input);
/// Set decoration style for MWM-compatible wm (mwm, ncdwm, fvwm?).

   void SetWMPosition(Int_t x, Int_t y);/// Give the window manager a window position hint.
   void SetWMSize(UInt_t w, UInt_t h);/// Give the window manager a window size hint.
   void SetWMSizeHints(UInt_t wmin, UInt_t hmin, UInt_t wmax, UInt_t hmax,
                       UInt_t winc, UInt_t hinc);
/// Give the window manager minimum and maximum size hints. Also
/// specify via winc and hinc the resize increments.

   void SetWMState(EInitialState state);/// Set the initial state of the window. Either kNormalState or kIconicState.

   virtual Bool_t BindKey(const TGWindow *w, Int_t keycode, Int_t modifier) const;/// Bind key to a window.
   virtual void   RemoveBind(const TGWindow *w, Int_t keycode, Int_t modifier) const;/// Remove key binding.
   TList *GetBindList() const { return fBindList; }

   const char *GetWindowName() const { return fWindowName; }
   const char *GetIconName() const { return fIconName; }
   const char *GetIconPixmap() const { return fIconPixmap; }
   void GetClassHints(const char *&className, const char *&resourceName) const
      { className = fClassName.Data(); resourceName = fResourceName.Data(); }
   void GetMWMHints(UInt_t &value, UInt_t &funcs, UInt_t &input) const
      { value = fMWMValue; funcs = fMWMFuncs; input = fMWMInput; }
   void GetWMPosition(Int_t &x, Int_t &y) const { x = fWMX; y = fWMY; }
   void GetWMSize(UInt_t &w, UInt_t &h) const { w = fWMWidth; h = fWMHeight; }
   void GetWMSizeHints(UInt_t &wmin, UInt_t &hmin, UInt_t &wmax, UInt_t &hmax,
                       UInt_t &winc, UInt_t &hinc) const
      { wmin = fWMMinWidth; hmin = fWMMinHeight; wmax = fWMMaxWidth;
        hmax = fWMMaxHeight; winc = fWMWidthInc; hinc = fWMHeightInc; }
   EInitialState GetWMState() const { return fWMInitState; }

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a main frame widget as a C++ statement(s) on output stream out.

   virtual void SaveSource(const char *filename = "Rootappl.C", Option_t *option = ""); // *MENU*icon=bld_save.png*
/// Save the GUI main frame widget in a C++ macro file.   
```

**TGTransientFrame**

```cpp
   TGTransientFrame(const TGWindow *p = 0, const TGWindow *main = 0, UInt_t w = 1, UInt_t h = 1,
                    UInt_t options = kVerticalFrame);
/// Create a transient window. A transient window is typically used for
/// dialog boxes.

   enum EPlacement { kCenter, kLeft, kRight, kTop, kBottom, kTopLeft, kTopRight,
                     kBottomLeft, kBottomRight };
   virtual void    CenterOnParent(Bool_t croot = kTRUE, EPlacement pos = kCenter);
/// Position transient frame centered relative to the parent frame.
/// If fMain is 0 (i.e. TGTransientFrame is acting just like a
/// TGMainFrame) and croot is true, the window will be centered on
/// the root window, otherwise no action is taken and the default
/// wm placement will be used.

   const TGWindow *GetMain() const { return fMain; }
   virtual void    SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a transient frame widget as a C++ statement(s) on output stream out.

   virtual void    SaveSource(const char *filename = "Rootdlog.C", Option_t *option = ""); // *MENU*icon=bld_save.png*
/// Save the GUI tranzient frame widget in a C++ macro file.
```

**TGGroupFrame**

```cpp
   enum ETitlePos { kLeft = -1, kCenter = 0, kRight = 1 };

   static FontStruct_t  GetDefaultFontStruct();/// Return default font structure in use.
   static const TGGC   &GetDefaultGC();/// Return default graphics context in use.

   TGGroupFrame(const TGWindow *p, TGString *title,
                UInt_t options = kVerticalFrame,
                GContext_t norm = GetDefaultGC()(),
                FontStruct_t font = GetDefaultFontStruct(),
                Pixel_t back = GetDefaultFrameBackground());
/// Create a group frame. The title will be adopted and deleted by the
/// group frame.

   TGGroupFrame(const TGWindow *p = 0, const char *title = 0,
                UInt_t options = kVerticalFrame,
                GContext_t norm = GetDefaultGC()(),
                FontStruct_t font = GetDefaultFontStruct(),
                Pixel_t back = GetDefaultFrameBackground());
/// Create a group frame.

   virtual ~TGGroupFrame();/// Delete a group frame.

   virtual TGDimension GetDefaultSize() const;/// Returns default size.
   virtual void  DrawBorder();
/// Draw border of around the group frame.
/// if frame is kRaisedFrame  - a frame border is of "wall style",
/// otherwise of "groove style".

   virtual void  SetTitle(TGString *title);
/// Set or change title of the group frame. Titlte TGString is adopted
/// by the TGGroupFrame.

   virtual void  SetTitle(const char *title);/// Set or change title of the group frame.

   virtual void  Rename(const char *title)  { SetTitle(title); } //*MENU*icon=bld_rename.png*
           Int_t GetTitlePos() const { return fTitlePos; }
   virtual void  SetTitlePos(ETitlePos pos = kLeft) { fTitlePos = pos; }  //*SUBMENU*
   virtual void  SetTextColor(Pixel_t color, Bool_t local = kTRUE);
/// Changes text color.
/// If local is true color is changed locally, otherwise - globally.

   virtual void  SetTextFont(const char *fontName, Bool_t local = kTRUE);
/// Changes text font specified by name.
/// If local is true font is changed locally - otherwise globally.

   virtual void  SetTextFont(FontStruct_t font, Bool_t local = kTRUE);
/// Changes text font.
/// If local is true font is changed locally - otherwise globally.


   GContext_t GetNormGC() const { return fNormGC; }
   FontStruct_t GetFontStruct() const { return fFontStruct; }

   virtual const char *GetTitle() const { return fText->GetString(); }
   Bool_t HasOwnFont() const;
/// Returns kTRUE if text attributes are unique,
/// returns kFALSE if text attributes are shared (global).

   virtual void  SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a group frame widget as a C++ statement(s) on output stream out.
```

**TGHeaderFrame**

```cpp
   TGHeaderFrame(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
                 UInt_t options = kChildFrame,
                 Pixel_t back = GetDefaultFrameBackground());/// Header Frame constructor.

   virtual Bool_t HandleButton(Event_t* event);/// Handle mouse button event in header frame.
   virtual Bool_t HandleMotion(Event_t* event);/// Handle mouse motion events in header frame.
   virtual Bool_t HandleDoubleClick(Event_t *event);/// Handle double click mouse event in header frame.

   void SetColumnsInfo(Int_t nColumns, TGTextButton  **colHeader, TGVFileSplitter  **splitHeader);
/// Set columns information in the header frame.
```


## code

```cpp
// TGCompositeFrame::SetEditable(Bool_t on)

TGMainFrame *m = new TGMainFrame(gClient->GetRoot(), 500, 500);
m->SetEditable();
gSystem->Load("$ROOTSYS/test/Aclock"); // load Aclock demo
Aclock a;
gROOT->Macro("$ROOTSYS/tutorials/gui/guitest.C");
m->SetEditable(0);
m->MapWindow();
```

```cpp
// TGPicture *TGMainFrame::SetIconPixmap(const char *iconName)

main_frame->SetIconPixmap("/home/root/icons/bld_rgb.png");


// void TGMainFrame::SetIconPixmap(char **xpm_array)

#include "/home/root/icons/bld_rgb.xpm"
//bld_rgb.xpm contains char *bld_rgb[] array
main_frame->SetIconPixmap(bld_rgb);
```





## example





<!-- TGFrame.md ends here -->
