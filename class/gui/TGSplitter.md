<!-- TGSplitter.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 14 20:33:11 2016 (+0800)
;; Last-Updated: 一 11月 14 20:44:11 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGSplitter

TGSplitter, TGVSplitter and TGHSplitter                              
                                                                
A splitter allows the frames left and right or above and below of    
it to be resized. The frame to be resized must have the kFixedWidth  
or kFixedHeight property set.


TGSplitter 继承 TGFrame

TGVSplitter 继承 TGSplitter

TGHSplitter 继承 TGSplitter

TGVFileSplitter 继承 TGVSplitter

## class

**TGSplitter**

```cpp
   TGSplitter(const TGWindow *p = 0, UInt_t w = 2, UInt_t h = 4,
              UInt_t options = kChildFrame,
              Pixel_t back = GetDefaultFrameBackground());/// Create a splitter.
   virtual ~TGSplitter() { }

   virtual void   SetFrame(TGFrame *frame, Bool_t prev) = 0;

   virtual Bool_t HandleButton(Event_t *event) = 0;
   virtual Bool_t HandleMotion(Event_t *event) = 0;
   virtual Bool_t HandleCrossing(Event_t *event) = 0;

   void DragStarted();      // *SIGNAL*  /// Emit DragStarted signal.
   void Moved(Int_t delta); // *SIGNAL*  /// Emit Moved signal.

   Bool_t GetExternalHandler() const { return fExternalHandler; }
   void SetExternalHandler(Bool_t x) { fExternalHandler = x; }
```


**TGVSplitter**

```cpp
   TGVSplitter(const TGWindow *p = 0, UInt_t w = 4, UInt_t h = 4,
               UInt_t options = kChildFrame,
               Pixel_t back = GetDefaultFrameBackground());/// Create a vertical splitter.
   TGVSplitter(const TGWindow *p, UInt_t w, UInt_t h, Bool_t external);/// Create a vertical splitter.
   virtual ~TGVSplitter();/// Delete vertical splitter widget.

   virtual void   DrawBorder();/// Draw vertical splitter.
   virtual void   SetFrame(TGFrame *frame, Bool_t left);
/// Set frame to be resized. If frame is on the left of the splitter
/// set left to true.

   const TGFrame *GetFrame() const { return fFrame; }
   Bool_t         GetLeft() const { return fLeft; }
   Bool_t         IsLeft() const { return fLeft; }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a splitter widget as a C++ statement(s) on output stream out.

   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button event in vertical splitter.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion event in vertical splitter.
   virtual Bool_t HandleCrossing(Event_t *event);/// Handle mouse motion event in vertical splitter.
```


**TGHSplitter**

```cpp
   TGHSplitter(const TGWindow *p = 0, UInt_t w = 4, UInt_t h = 4,
               UInt_t options = kChildFrame,
               Pixel_t back = GetDefaultFrameBackground());/// Create a horizontal splitter.
   TGHSplitter(const TGWindow *p, UInt_t w, UInt_t h, Bool_t external);/// Create a horizontal splitter.
   virtual ~TGHSplitter();/// Delete horizontal splitter widget.

   virtual void   DrawBorder();/// Draw horizontal splitter.
   virtual void   SetFrame(TGFrame *frame, Bool_t above);
/// Set frame to be resized. If frame is above the splitter
/// set above to true.

   const TGFrame *GetFrame() const { return fFrame; }
   Bool_t         GetAbove() const { return fAbove; }
   Bool_t         IsAbove() const { return fAbove; }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a splitter widget as a C++ statement(s) on output stream out.

   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button event in horizontal splitter.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion event in horizontal splitter.
   virtual Bool_t HandleCrossing(Event_t *event);/// Handle mouse motion event in horizontal splitter.
```


**TGVFileSplitter**

```cpp
   TGVFileSplitter(const TGWindow *p = 0, UInt_t w = 4, UInt_t h = 4,
               UInt_t options = kChildFrame,
               Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGVFileSplitter();

   virtual Bool_t HandleDoubleClick(Event_t *);/// Handle double click mouse event in splitter.
   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button event in vertical splitter.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion event in vertical splitter.
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a splitter widget as a C++ statement(s) on output stream out.

   void LayoutHeader(TGFrame *f);  //*SIGNAL*  /// Emit LayoutFeader() signal.
   void LayoutListView();  //*SIGNAL*  /// Emit LayoutListView() signal.
   void ButtonPressed();   //*SIGNAL*  /// Emit ButtonPressed() signal.
   void ButtonReleased();  //*SIGNAL*  /// Emit ButtonReleased() signal.
   void DoubleClicked(TGVFileSplitter* frame);  //*SIGNAL*  /// Emit DoubleClicked() signal.
```


## code



## example



<!-- TGSplitter.md ends here -->
