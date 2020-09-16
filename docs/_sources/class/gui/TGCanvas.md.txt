<!-- TGCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 18:30:40 2016 (+0800)
;; Last-Updated: 三 9月 16 10:57:17 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGCanvas*

A TGCanvas is a frame containing two scrollbars (horizontal and      
vertical) and a viewport. The viewport acts as the window through    
which we look at the contents of the container frame. 

A TGContainer frame manages a content area. It can display and       
control a hierarchy of multi-column items, and provides the ability  
to add new items at any time. By default it doesn't map subwindows   
which are items of the container. In this case subwindow must        
provide DrawCopy method, see for example TGLVEntry class.            
It is also possible to use option which allow to map subwindows.     
This option has much slower drawing speed in case of more than 1000  
items placed in container. To activate this option the fMapSubwindows  
data member must be set to kTRUE (for example TTVLVContainer class)  
                                                                     
The TGContainer class can handle the keys:     
-  F7, Ctnrl-F - activate search dialog                           
-  F3, Ctnrl-G - continue search                                  
-  End - go to the last item in container                         
-  Home - go to the first item in container                       
-  PageUp,PageDown,arrow keys - navigate inside container         
-  Return/Enter - equivalent to double click of the mouse button  
-  Contrl-A - select/activate all items.                          
-  Space - invert selection.                                      



TGContainer 继承 TGCompositeFrame , friend TGViewPort , TGCanvas , TGContainerKeyboardTimer , TGContainerScrollTimer , TGListView


TGViewPort 继承 TGCompositeFrame

TGCanvas 继承 TGFrame


## class

**TGContainer**

```cpp
   TGContainer(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
               UInt_t options = kSunkenFrame,
               Pixel_t back = GetDefaultFrameBackground());
/// Create a canvas container. This is the (large) frame that contains
/// all the list items. It will be shown through a TGViewPort (which is
/// created by the TGCanvas).

   TGContainer(TGCanvas *p,UInt_t options = kSunkenFrame,
               Pixel_t back = GetDefaultFrameBackground());
/// Create a canvas container. This is the (large) frame that contains
/// all the list items. It will be shown through a TGViewPort (which is
/// created by the TGCanvas).

   virtual ~TGContainer();/// Delete canvas container.

   virtual void DrawRegion(Int_t x, Int_t y, UInt_t w, UInt_t h);
/// Draw a region of container in viewport.
/// x, y, w, h are position and dimension of area to be
/// redrawn in viewport coordinates.

   virtual void ClearViewPort();/// Clear view port and redraw full content
   virtual void Associate(const TGWindow *w) { fMsgWindow = w; }
   virtual void AdjustPosition();/// Move content to position of highlighted/activated frame.
   virtual void SetPagePosition(const TGPosition& pos);/// Set page position.
   virtual void SetPagePosition(Int_t x, Int_t y);/// Set page position.
   virtual void SetPageDimension(const TGDimension& dim);/// Set page dimension.
   virtual void SetPageDimension(UInt_t w, UInt_t h);/// Set page dimension.
   virtual void RemoveAll();/// Remove all items from the container.
   virtual void RemoveItem(TGFrame *item);/// Remove item from container.
   virtual void Layout();/// Layout container entries.

   TGCanvas         *GetCanvas() const { return fCanvas; }
   const TGWindow   *GetMessageWindow() const { return fMsgWindow; }
   virtual TGPosition   GetPagePosition() const;/// Returns page position.
   virtual TGDimension  GetPageDimension() const;/// Returns page dimension.

   virtual Int_t  NumSelected() const { return fSelected; }
   virtual Int_t  NumItems() const { return fTotal; }
   virtual TGFrameElement *FindFrame(Int_t x,Int_t y,Bool_t exclude=kTRUE);
/// Find frame located int container at position x,y.

   virtual TGFrame        *FindFrameByName(const char *name);/// Find frame by name.
   virtual TGHScrollBar *GetHScrollbar() const;/// returns pointer to hor. scroll bar
   virtual TGVScrollBar *GetVScrollbar() const;/// returns pointer to vert. scroll bar
   virtual void SetHsbPosition(Int_t newPos);/// set new hor. position
   virtual void SetVsbPosition(Int_t newPos);/// Set position of vertical scrollbar.
   virtual void LineUp(Bool_t select = kFALSE);/// Make current position first line in window by scrolling up.
   virtual void LineDown(Bool_t select = kFALSE);/// Move one line down.
   virtual void LineLeft(Bool_t select = kFALSE);/// Move current position one column left.
   virtual void LineRight(Bool_t select = kFALSE);/// Move current position one column right.
   virtual void PageUp(Bool_t select = kFALSE);/// Move  position one page up.
   virtual void PageDown(Bool_t select = kFALSE);/// Move position one page down.
   virtual void Home(Bool_t select = kFALSE);/// Move to upper-left corner of container.
   virtual void End(Bool_t select = kFALSE);/// Move to the bottom-right corner of container.
   virtual void Search(Bool_t close = kTRUE);/// Invokes search dialog. Looks for item with the entered name.
   virtual void *FindItem(const TString& name,
                          Bool_t direction = kTRUE,
                          Bool_t caseSensitive = kTRUE,
                          Bool_t subString = kFALSE);

   virtual const TGFrame *GetNextSelected(void **current);
/// Return the next selected item. If the "current" pointer is 0, the first
/// selected item will be returned.

   virtual TGFrame *GetLastActive() const { return fLastActiveEl ? fLastActiveEl->fFrame : 0; }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a canvas container as a C++ statement(s) on output stream out.

   virtual Bool_t HandleDNDFinished() { fBdown = kFALSE; return kTRUE; }
   virtual Bool_t HandleExpose(Event_t *event);/// Handle expose events. Do not use double buffer.
   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button event in container.
   virtual Bool_t HandleDoubleClick(Event_t *event);/// Handle double click mouse event.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion events.
   virtual Bool_t HandleKey(Event_t *event);/// The key press event handler converts a key press to some line editor action.

   const TGPicture *GetObjPicture(TGFrame *f);
/// Retrieve icons associated with class "name". Association is made
/// via the user's ~/.root.mimes file or via $ROOTSYS/etc/root.mimes.

   virtual void SetDragPixmap(const TGPicture *pic);/// Set drag window pixmaps and hotpoint.

   virtual void SelectAll();                    //*SIGNAL*
/// Select all items in the container.
/// SelectAll() signal emitted.

   virtual void UnSelectAll();                  //*SIGNAL*  /// Unselect all items in the container.
   virtual void InvertSelection();              //*SIGNAL*
/// Invert the selection, all selected items become unselected and vice versa.

   virtual void ReturnPressed(TGFrame*);        //*SIGNAL*
/// Signal emitted when Return/Enter key pressed.
/// It's equivalent to "double click" of mouse button.

   virtual void SpacePressed(TGFrame*);         //*SIGNAL*
/// Signal emitted when space key pressed.
/// Pressing space key inverts selection.

   virtual void KeyPressed(TGFrame*, UInt_t keysym, UInt_t mask); //*SIGNAL*
/// Signal emitted when keyboard key pressed
/// frame - activated frame
/// keysym - defined in "KeySymbols.h"
/// mask - modifier key mask, defined in "GuiTypes.h"
/// const Mask_t kKeyShiftMask   = BIT(0);
/// const Mask_t kKeyLockMask    = BIT(1);
/// const Mask_t kKeyControlMask = BIT(2);
/// const Mask_t kKeyMod1Mask    = BIT(3);   // typically the Alt key
/// const Mask_t kButton1Mask    = BIT(8);
/// const Mask_t kButton2Mask    = BIT(9);
/// const Mask_t kButton3Mask    = BIT(10);
/// const Mask_t kButton4Mask    = BIT(11);
/// const Mask_t kButton5Mask    = BIT(12);
/// const Mask_t kAnyModifier    = BIT(15);

   virtual void OnMouseOver(TGFrame*);          //*SIGNAL*  /// Signal emitted when pointer is over entry.
   virtual void CurrentChanged(Int_t x,Int_t y);//*SIGNAL*  /// Emit signal when current position changed.
   virtual void CurrentChanged(TGFrame* f);     //*SIGNAL*  /// Emit signal when current selected frame changed.
   virtual void Clicked(TGFrame *f, Int_t btn); //*SIGNAL*  /// Emit Clicked() signal.
   virtual void DoubleClicked(TGFrame *f, Int_t btn);  //*SIGNAL*  /// Emit DoubleClicked() signal.
   virtual void DoubleClicked(TGFrame *f, Int_t btn, Int_t x, Int_t y); //*SIGNAL*  /// Emit DoubleClicked() signal.
   virtual void Clicked(TGFrame *f, Int_t btn, Int_t x, Int_t y);       //*SIGNAL*  /// Emit Clicked() signal.
```


**TGViewPort**

```cpp
   TGViewPort(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
              UInt_t options = kChildFrame,
              Pixel_t back = GetDefaultFrameBackground());/// Create a viewport object.

   TGFrame *GetContainer() const { return fContainer; }
   void SetContainer(TGFrame *f);
/// Add container frame to the viewport. We must make sure that the added
/// container is at least a TGCompositeFrame (TGCanvas::AddFrame depends
/// on it).

   virtual void DrawBorder() { };
   virtual void Layout() { }
   virtual TGDimension GetDefaultSize() const { return TGDimension(fWidth, fHeight); }

   virtual void SetHPos(Int_t xpos);/// Moves content of container frame in horizontal direction.
   virtual void SetVPos(Int_t ypos);/// Moves content of container frame in vertical direction.
   void SetPos(Int_t xpos, Int_t ypos);/// Goto new position.

   Int_t GetHPos() const { return fX0; }
   Int_t GetVPos() const { return fY0; }
   virtual Bool_t HandleConfigureNotify(Event_t *event);/// Handle resize events.
```


**TGCanvas**

```cpp
   enum { kCanvasNoScroll         = 0,
          kCanvasScrollHorizontal = BIT(0),
          kCanvasScrollVertical   = BIT(1),
          kCanvasScrollBoth       = (kCanvasScrollHorizontal | kCanvasScrollVertical)
   };

   TGCanvas(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
            UInt_t options = kSunkenFrame | kDoubleBorder,
            Pixel_t back = GetDefaultFrameBackground());/// Create a canvas object.

   virtual ~TGCanvas();/// Delete canvas.

   TGFrame      *GetContainer() const { return fVport->GetContainer(); }
   TGViewPort   *GetViewPort() const { return fVport; }
   TGHScrollBar *GetHScrollbar() const { return fHScrollbar; }
   TGVScrollBar *GetVScrollbar() const { return fVScrollbar; }

   virtual void  AddFrame(TGFrame *f, TGLayoutHints *l = 0);
/// Adding a frame to a canvas is actually adding the frame to the
/// viewport container. The viewport container must be at least a
/// TGCompositeFrame for this method to succeed.

   virtual void  SetContainer(TGFrame *f) { fVport->SetContainer(f); }
   virtual void  MapSubwindows();
   virtual void  DrawBorder();/// Draw canvas border.
   virtual void  Layout();
/// Create layout for canvas. Depending on the size of the container
/// we need to add the scrollbars.

   virtual void  ClearViewPort();/// Clear view port and redraw content.
   virtual Int_t GetHsbPosition() const;/// Set position of horizontal scrollbar.
   virtual Int_t GetVsbPosition() const;/// Get position of vertical scrollbar.
   virtual void  SetHsbPosition(Int_t newPos);/// Get position of horizontal scrollbar.
   virtual void  SetVsbPosition(Int_t newPos);/// Set position of vertical scrollbar.
   void          SetScrolling(Int_t scrolling);
/// Set scrolling policy. Use values defined by the enum: kCanvasNoScroll,
/// kCanvasScrollHorizontal, kCanvasScrollVertical, kCanvasScrollBoth.

   Int_t         GetScrolling() const { return fScrolling; }

   virtual TGDimension GetDefaultSize() const { return TGDimension(fWidth, fHeight); }
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);/// Handle message generated by the canvas scrollbars.

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a canvas widget as a C++ statement(s) on output stream out.
```





## code




## example




<!-- TGCanvas.md ends here -->
