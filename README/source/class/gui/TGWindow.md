<!-- TGWindow.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:00:20 2016 (+0800)
;; Last-Updated: 三 9月 16 11:17:21 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGWindow*

TGWindow 继承 TGObject , friend TGClient  
ROOT GUI Window base class.

TGUnknownWindowHandler 继承 TObject

Handle events for windows that are not part of the native ROOT GUI.  
Typically windows created by Xt or Motif.

## class

**TGWindow**

```cpp
   enum  EEditMode {
      kEditEnable        = 0,          // allow edit of this window
      kEditDisable       = BIT(0),     // disable edit of this window
      kEditDisableEvents = BIT(1),     // window events cannot be editted
      kEditDisableGrab   = BIT(2),     // window grab cannot be editted
      kEditDisableLayout = BIT(3),     // window layout cannot be editted
      kEditDisableResize = BIT(4),     // window size cannot be editted
      kEditDisableHeight = BIT(5),     // window height cannot be editted
      kEditDisableWidth  = BIT(6),     // window width cannot be editted
      kEditDisableBtnEnable = BIT(7),  // window can handle mouse button events
      kEditDisableKeyEnable = BIT(8)   // window can handle keyboard events
   };

   TGWindow(const TGWindow *p = 0, Int_t x = 0, Int_t y = 0,
            UInt_t w = 0, UInt_t h = 0, UInt_t border = 0,
            Int_t depth = 0,
            UInt_t clss = 0,
            void *visual = 0,
            SetWindowAttributes_t *attr = 0,
            UInt_t wtype = 0);
/// Create a new window. Parent p must exist otherwise the root window
/// is taken as parent. No arguments specified results in values from
/// parent to be taken (or defaults).

   TGWindow(TGClient *c, Window_t id, const TGWindow *parent = 0);/// Create a copy of a window.

   virtual ~TGWindow();/// Window destructor. Unregisters the window.

   const TGWindow *GetParent() const { return fParent; }
   virtual const TGWindow *GetMainFrame() const;/// Returns top level main frame.

   virtual void MapWindow() { gVirtualX->MapWindow(fId); }
   virtual void MapSubwindows() { gVirtualX->MapSubwindows(fId); }
   virtual void MapRaised() { gVirtualX->MapRaised(fId); }
   virtual void UnmapWindow() { gVirtualX->UnmapWindow(fId); }
   virtual void DestroyWindow() { gVirtualX->DestroyWindow(fId); }
   virtual void DestroySubwindows() { gVirtualX->DestroySubwindows(fId); }
   virtual void RaiseWindow() { gVirtualX->RaiseWindow(fId); }
   virtual void LowerWindow() { gVirtualX->LowerWindow(fId); }
   virtual void IconifyWindow() { gVirtualX->IconifyWindow(fId); }
   virtual void ReparentWindow(const TGWindow *p, Int_t x = 0, Int_t y = 0);
/// Reparent window, make p the new parent and position the window at
/// position (x,y) in new parent.

   virtual void RequestFocus() { gVirtualX->SetInputFocus(fId); }

   virtual void SetBackgroundColor(Pixel_t color)
                  { gVirtualX->SetWindowBackground(fId, color); }
   virtual void SetBackgroundPixmap(Pixmap_t pixmap)
                  { gVirtualX->SetWindowBackgroundPixmap(fId, pixmap); }

   virtual Bool_t HandleExpose(Event_t *event)
                  { if (event->fCount == 0) fClient->NeedRedraw(this); return kTRUE; }
   virtual Bool_t HandleEvent(Event_t *) { return kFALSE; }
   virtual Bool_t HandleTimer(TTimer *) { return kFALSE; }
   virtual Bool_t HandleIdleEvent(TGIdleHandler *) { return kFALSE; }

   virtual void   Move(Int_t x, Int_t y);/// Move the window.
   virtual void   Resize(UInt_t w, UInt_t h);/// Resize the window.
   virtual void   MoveResize(Int_t x, Int_t y, UInt_t w, UInt_t h);/// Move and resize the window.
   virtual Bool_t IsMapped();/// Returns kTRUE if window is mapped on screen, kFALSE otherwise.
   virtual Bool_t IsEditable() const { return (fClient->GetRoot() == this); }
   virtual UInt_t GetEditDisabled() const { return fEditDisabled; }
   virtual void   SetEditDisabled(UInt_t on = kEditDisable) { fEditDisabled = on; }
   virtual void   SetEditable(Bool_t on = kTRUE)
                  { if (!(fEditDisabled & kEditDisable)) fClient->SetRoot(on ? this : 0); }
   virtual Int_t  MustCleanup() const { return 0; }
   virtual void   Print(Option_t *option="") const;
/// Print window id.
/// If option is "tree" - print all parent windows tree

   virtual void        SetWindowName(const char *name = 0);/// Set window name.
   virtual const char *GetName() const;/// Return unique name, used in SavePrimitive methods.
   virtual void        SetName(const char *name) { fName = name; }

   virtual void   SetMapSubwindows(Bool_t /*on*/) {  }
   virtual Bool_t IsMapSubwindows() const { return kTRUE; }

   static Int_t        GetCounter();
/// Return global window counter (total number of created windows).
```


****

```cpp
   TGUnknownWindowHandler() { }
   virtual ~TGUnknownWindowHandler() { }

   virtual Bool_t HandleEvent(Event_t *) = 0;
```

## code



## example




<!-- TGWindow.md ends here -->
