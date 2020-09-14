<!-- TGDNDManager.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 1月 27 21:54:09 2017 (+0800)
;; Last-Updated: 五 1月 27 22:12:57 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGDNDManager


TGDragWindow 继承 TGFrame  
TDNDData 继承 TObject  
TGDNDManager 继承 TObject


TGDragWindow  
Window used as drag icon during drag and drop operations.



```cpp
R__EXTERN TGDNDManager *gDNDManager; // global drag and drop manager
```


## class

**TGDragWindow**

```cpp
   TGDragWindow(const TGWindow *p, Pixmap_t pic, Pixmap_t mask,
                UInt_t options = kChildFrame, Pixel_t back = GetWhitePixel());
   virtual ~TGDragWindow();

   virtual TGDimension GetDefaultSize() const { return TGDimension(fPw, fPh); }

   virtual void MapWindow();/// Map and Raise TGDragWindow.
   virtual void UnmapWindow();/// Unmap TGDragWindow.
   virtual void RaiseWindow();/// Raise TGDragWindow.
   virtual void LowerWindow();/// Lower TGDragWindow.
   virtual void MapRaised();/// Map TGDragWindow.

   virtual void Layout();/// Layout TGDragWindow.

   Window_t GetInputId() const { return fInput; }
   Bool_t HasWindow(Window_t w) const { return (w == fId || w == fInput); }
```


**TDNDData**

```cpp
   TDNDData(Atom_t dt = kNone, void *d = 0, Int_t len = 0, Atom_t act = kNone) :
      fDataType(dt), fAction(act), fData(d), fDataLength(len) {}
   ~TDNDData() {}

   Atom_t    fDataType;       // Data type description
   Atom_t    fAction;         // Action description
   void     *fData;           // Actual data
   Int_t     fDataLength;     // Length of data
```


**TGDNDManager**

```cpp
   TGDNDManager(TGFrame *toplevel, Atom_t *typelist);
   virtual ~TGDNDManager();

   Bool_t         HandleClientMessage(Event_t *event);/// Handle DND related client messages.
   Bool_t         HandleSelectionRequest(Event_t *event);/// Handle selection request event.
   Bool_t         HandleSelection(Event_t *event);/// Handle selection event.

   Bool_t         HandleTimer(TTimer *t);/// Handle Drop timeout.

  //--- called by widgets

   TGFrame       *GetMainFrame() const { return fMain; }
   void           SetMainFrame(TGFrame *main) { fMain = main; }
   void           SetDragPixmap(Pixmap_t pic, Pixmap_t mask, Int_t hot_x, Int_t hot_y);/// Set drag window pixmaps and hotpoint.
   Bool_t         SetRootProxy();/// Set root window proxy.
   Bool_t         RemoveRootProxy();/// Remove root window proxy.

   Bool_t         StartDrag(TGFrame *src, Int_t x_root, Int_t y_root,
                            Window_t grabWin = kNone);/// Start dragging.
   Bool_t         Drag(Int_t x_root, Int_t y_root, Atom_t action, Time_t timestamp);/// Process drag event.
   Bool_t         Drop();/// Drop.
   Bool_t         EndDrag();/// End dragging.

   Bool_t         IsDragging() const { return fDragging; }
   Window_t       GetSource() const { return fSource; }
   Window_t       GetTarget() const { return fTarget; }
   Atom_t        *GetTypeList() const { return fTypelist; }

   static Atom_t  GetDNDAware();
   static Atom_t  GetDNDSelection();
   static Atom_t  GetDNDProxy();
   static Atom_t  GetDNDEnter();
   static Atom_t  GetDNDLeave();
   static Atom_t  GetDNDPosition();
   static Atom_t  GetDNDStatus();
   static Atom_t  GetDNDDrop();
   static Atom_t  GetDNDFinished();
   static Atom_t  GetDNDVersion();
   static Atom_t  GetDNDActionCopy();
   static Atom_t  GetDNDActionMove();
   static Atom_t  GetDNDActionLink();
   static Atom_t  GetDNDActionAsk();
   static Atom_t  GetDNDActionPrivate();
   static Atom_t  GetDNDTypeList();
   static Atom_t  GetDNDActionList();
   static Atom_t  GetDNDActionDescrip();
   static Atom_t  GetXCDNDData();
```



## code




<!-- TGDNDManager.md ends here -->
