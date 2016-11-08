<!-- TGListTree.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 19:09:08 2016 (+0800)
;; Last-Updated: 二 11月  8 19:14:42 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGListTree

A list tree is a widget that can contain a number of items           
arranged in a tree structure. The items are represented by small     
folder icons that can be either open or closed.                      
                                                                     
The TGListTree is user callable. The TGListTreeItem is a service     
class of the list tree.                                              

A list tree can generate the following events:                       
kC_LISTTREE, kCT_ITEMCLICK, which button, location (y<<16|x).        
kC_LISTTREE, kCT_ITEMDBLCLICK, which button, location (y<<16|x).


TGListTreeItem friend TGListTree  
Abstract base-class for items that go into a TGListTree container.

TGListTreeItemStd 继承 TGListTreeItem  
Item that goes into a TGListTree container

TGListTree 继承 TGContainer  
Show items in a tree structured list


## class

**TGListTreeItem**

```cpp
   TGListTreeItem(TGClient *client=gClient);
   virtual ~TGListTreeItem() {}

   TGListTreeItem *GetParent()      const { return fParent; }
   TGListTreeItem *GetFirstChild()  const { return fFirstchild; }
   TGListTreeItem *GetLastChild()   const { return fLastchild;  }
   TGListTreeItem *GetPrevSibling() const { return fPrevsibling; }
   TGListTreeItem *GetNextSibling() const { return fNextsibling; }

   virtual Bool_t          IsOpen()    const { return fOpen; }
   virtual void            SetOpen(Bool_t o) { fOpen = o; }

   virtual Bool_t          IsActive() const = 0;
   virtual Pixel_t         GetActiveColor() const = 0;
   virtual void            SetActive(Bool_t) {}

   void                    Rename(const char* new_name) { SetText(new_name); }
   virtual const char     *GetText() const = 0;
   virtual Int_t           GetTextLength() const = 0;
   virtual const char     *GetTipText() const = 0;
   virtual Int_t           GetTipTextLength() const = 0;
   virtual void            SetText(const char *) {}
   virtual void            SetTipText(const char *) {}

   virtual void            SetUserData(void *, Bool_t=kFALSE) {}
   virtual void           *GetUserData() const = 0;

   virtual const TGPicture*GetPicture() const = 0;
   virtual void            SetPictures(const TGPicture*, const TGPicture*) {}
   virtual const TGPicture*GetCheckBoxPicture() const = 0;
   virtual void            SetCheckBoxPictures(const TGPicture*, const TGPicture*) {}
   virtual UInt_t          GetPicWidth() const;

   virtual void            SetCheckBox(Bool_t=kTRUE) {}
   virtual Bool_t          HasCheckBox() const = 0;
   virtual void            CheckItem(Bool_t=kTRUE) = 0;
   virtual void            Toggle() { SetCheckBox( ! IsChecked()); }
   virtual Bool_t          IsChecked() const = 0;

   // Propagation of checked-state form children to parents.
   virtual void            CheckAllChildren(Bool_t=kTRUE) {}
   virtual void            CheckChildren(TGListTreeItem*, Bool_t) {}
   virtual Bool_t          HasCheckedChild(Bool_t=kFALSE)   { return kTRUE; } // !!!!
   virtual Bool_t          HasUnCheckedChild(Bool_t=kFALSE) { return kTRUE; } // !!!!
   virtual void            UpdateState() {}

   // Item coloration (underline + minibox)
   virtual Bool_t          HasColor() const = 0;
   virtual Color_t         GetColor() const = 0;
   virtual void            SetColor(Color_t) {}
   virtual void            ClearColor() {}

   // Drag and drop.
   void            SetDNDSource(Bool_t onoff)
                   { if (onoff) fDNDState |= kIsDNDSource; else fDNDState &= ~kIsDNDSource; }
   void            SetDNDTarget(Bool_t onoff)
                   { if (onoff) fDNDState |= kIsDNDTarget; else fDNDState &= ~kIsDNDTarget; }
   Bool_t          IsDNDSource() const { return fDNDState & kIsDNDSource; }
   Bool_t          IsDNDTarget() const { return fDNDState & kIsDNDTarget; }

   // Allow handling by the items themselves ... NOT USED in TGListTree yet !!!!
   virtual Bool_t  HandlesDragAndDrop() const { return kFALSE; }
   virtual void    HandleDrag() {}
   virtual void    HandleDrop() {}

   virtual void    SavePrimitive(std::ostream&, Option_t*, Int_t) {}
```


**TGListTreeItemStd**

```cpp
   TGListTreeItemStd(TGClient *fClient = gClient, const char *name = 0,
                     const TGPicture *opened = 0, const TGPicture *closed = 0,
                     Bool_t checkbox = kFALSE);
   virtual ~TGListTreeItemStd();

   virtual Pixel_t         GetActiveColor() const;
   virtual Bool_t          IsActive()       const { return fActive; }
   virtual void            SetActive(Bool_t a)    { fActive = a; }

   virtual const char     *GetText()             const { return fText.Data(); }
   virtual Int_t           GetTextLength()       const { return fText.Length(); }
   virtual const char     *GetTipText()          const { return fTipText.Data(); }
   virtual Int_t           GetTipTextLength()    const { return fTipText.Length(); }
   virtual void            SetText(const char *text)   { fText = text; }
   virtual void            SetTipText(const char *tip) { fTipText = tip; }

   virtual void            SetUserData(void *userData, Bool_t own=kFALSE) { fUserData = userData; fOwnsData=own; }
   virtual void           *GetUserData() const { return fUserData; }

   virtual const TGPicture*GetPicture()         const { return fOpen ? fOpenPic : fClosedPic; }
   virtual const TGPicture*GetCheckBoxPicture() const { return fCheckBox ? (fChecked ? fCheckedPic : fUncheckedPic) : 0; }
   virtual void            SetPictures(const TGPicture *opened, const TGPicture *closed);
   virtual void            SetCheckBoxPictures(const TGPicture *checked, const TGPicture *unchecked);

   virtual void            SetCheckBox(Bool_t on = kTRUE);
   virtual Bool_t          HasCheckBox() const { return fCheckBox; }
   virtual void            CheckItem(Bool_t checked = kTRUE) { fChecked = checked; }
   virtual void            Toggle() { fChecked = !fChecked; }
   virtual Bool_t          IsChecked() const { return fChecked; }

   virtual void            CheckAllChildren(Bool_t state = kTRUE);
   virtual void            CheckChildren(TGListTreeItem *item, Bool_t state);
   virtual Bool_t          HasCheckedChild(Bool_t first=kFALSE);
   virtual Bool_t          HasUnCheckedChild(Bool_t first=kFALSE);
   virtual void            UpdateState();

   virtual Bool_t          HasColor() const { return fHasColor; }
   virtual Color_t         GetColor() const { return fColor; }
   virtual void            SetColor(Color_t color) { fHasColor = true;fColor = color; }
   virtual void            ClearColor() { fHasColor = false; }

   virtual void            SavePrimitive(std::ostream &out, Option_t *option, Int_t n);
```


****

```cpp
   //---- color markup mode of tree items
   enum EColorMarkupMode {
      kDefault        = 0,
      kColorUnderline = BIT(0),
      kColorBox       = BIT(1)
   };
   enum ECheckMode {
      kSimple    = BIT(2),
      kRecursive = BIT(3)
   };

   TGListTree(TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
              UInt_t options = 0, Pixel_t back = GetWhitePixel());
   TGListTree(TGCanvas *p, UInt_t options, Pixel_t back = GetWhitePixel());

   virtual ~TGListTree();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleDoubleClick(Event_t *event);
   virtual Bool_t HandleCrossing(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual Bool_t HandleKey(Event_t *event);

   virtual void SetCanvas(TGCanvas *canvas) { fCanvas = canvas; }
   virtual void DrawRegion(Int_t x, Int_t y, UInt_t w, UInt_t h);

   virtual void DrawOutline(Handle_t id, TGListTreeItem *item, Pixel_t col=0xbbbbbb,
                            Bool_t clear=kFALSE);
   virtual void DrawActive(Handle_t id, TGListTreeItem *item);

   virtual TGDimension GetDefaultSize() const
            { return TGDimension(fDefw, fDefh); }

   void            AddItem(TGListTreeItem *parent, TGListTreeItem *item);
   TGListTreeItem *AddItem(TGListTreeItem *parent, const char *string,
                           const TGPicture *open = 0,
                           const TGPicture *closed = 0,
                           Bool_t checkbox = kFALSE);
   TGListTreeItem *AddItem(TGListTreeItem *parent, const char *string,
                           void *userData, const TGPicture *open = 0,
                           const TGPicture *closed = 0,
                           Bool_t checkbox = kFALSE);
   void  RenameItem(TGListTreeItem *item, const char *string);
   Int_t DeleteItem(TGListTreeItem *item);
   void  OpenItem(TGListTreeItem *item);
   void  CloseItem(TGListTreeItem *item);
   void  CheckItem(TGListTreeItem *item, Bool_t check = kTRUE);
   void  SetCheckBox(TGListTreeItem *item, Bool_t on = kTRUE);
   void  ToggleItem(TGListTreeItem *item);
   Int_t RecursiveDeleteItem(TGListTreeItem *item, void *userData);

   Int_t DeleteChildren(TGListTreeItem *item);
   Int_t Reparent(TGListTreeItem *item, TGListTreeItem *newparent);
   Int_t ReparentChildren(TGListTreeItem *item, TGListTreeItem *newparent);
   void  SetToolTipItem(TGListTreeItem *item, const char *string);
   void  SetAutoTips(Bool_t on = kTRUE) { fAutoTips = on; }
   void  SetAutoCheckBoxPic(Bool_t on) { fAutoCheckBoxPic = on; }
   void  SetSelected(TGListTreeItem *item) { fSelected = item; }
   void  AdjustPosition(TGListTreeItem *item);
   void  AdjustPosition() { TGContainer::AdjustPosition(); }

   // overwrite TGContainer's methods
   void Home(Bool_t select = kFALSE);
   void End(Bool_t select = kFALSE);
   void PageUp(Bool_t select = kFALSE);
   void PageDown(Bool_t select = kFALSE);
   void LineUp(Bool_t select = kFALSE);
   void LineDown(Bool_t select = kFALSE);
   void Search(Bool_t close = kTRUE);

   Int_t Sort(TGListTreeItem *item);
   Int_t SortSiblings(TGListTreeItem *item);
   Int_t SortChildren(TGListTreeItem *item);
   void  HighlightItem(TGListTreeItem *item);
   void  ClearHighlighted();
   void  GetPathnameFromItem(TGListTreeItem *item, char *path, Int_t depth = 0);
   void  UnselectAll(Bool_t draw);
   void  SetToolTipText(const char *text, Int_t x, Int_t y, Long_t delayms);
   void  HighlightItem(TGListTreeItem *item, Bool_t state, Bool_t draw);
   void  HighlightChildren(TGListTreeItem *item, Bool_t state, Bool_t draw);
   void  DisableOpen(Bool_t disable = kTRUE) { fDisableOpen = disable;}
   void  GetChecked(TList *checked);
   void  GetCheckedChildren(TList *checked, TGListTreeItem *item);
   void  CheckAllChildren(TGListTreeItem *item, Bool_t state);

   TGListTreeItem *GetFirstItem()  const { return fFirst; }
   TGListTreeItem *GetSelected()   const { return fSelected; }
   TGListTreeItem *GetCurrent()    const { return fCurrent; }
   TGListTreeItem *GetBelowMouse() const { return fBelowMouse; }
   TGListTreeItem *FindSiblingByName(TGListTreeItem *item, const char *name);
   TGListTreeItem *FindSiblingByData(TGListTreeItem *item, void *userData);
   TGListTreeItem *FindChildByName(TGListTreeItem *item, const char *name);
   TGListTreeItem *FindChildByData(TGListTreeItem *item, void *userData);
   TGListTreeItem *FindItemByPathname(const char *path);
   TGListTreeItem *FindItemByObj(TGListTreeItem *item, void *ptr);

   void  AddItem(const char *string) { AddItem(fSelected, string); } //*MENU*
   void  AddRoot(const char *string) { AddItem(0, string); } //*MENU*
   Int_t DeleteSelected() { return (fSelected ? DeleteItem(fSelected) : 0); } //*MENU*
   void  RenameSelected(const char *string) { if (fSelected) RenameItem(fSelected, string); } //*MENU*

   virtual void MouseOver(TGListTreeItem *entry);  //*SIGNAL*
   virtual void MouseOver(TGListTreeItem *entry, UInt_t mask);  //*SIGNAL*
   virtual void KeyPressed(TGListTreeItem *entry, UInt_t keysym, UInt_t mask);  //*SIGNAL*
   virtual void ReturnPressed(TGListTreeItem *entry);  //*SIGNAL*
   virtual void Clicked(TGListTreeItem *entry, Int_t btn);  //*SIGNAL*
   virtual void Clicked(TGListTreeItem *entry, Int_t btn, Int_t x, Int_t y);  //*SIGNAL*
   virtual void Clicked(TGListTreeItem *entry, Int_t btn, UInt_t mask, Int_t x, Int_t y);  //*SIGNAL*
   virtual void DoubleClicked(TGListTreeItem *entry, Int_t btn);  //*SIGNAL*
   virtual void DoubleClicked(TGListTreeItem *entry, Int_t btn, Int_t x, Int_t y);  //*SIGNAL*
   virtual void Checked(TObject *obj, Bool_t check);  //*SIGNAL*
   virtual void DataDropped(TGListTreeItem *item, TDNDData *data);  //*SIGNAL*

   // Utility functions
   Int_t        FontHeight();
   Int_t        FontAscent();
   Int_t        TextWidth(const char *c);

   static const TGPicture *GetOpenPic();
   static const TGPicture *GetClosedPic();
   static const TGPicture *GetCheckedPic();
   static const TGPicture *GetUncheckedPic();

   // User control
   void         SetUserControl(Bool_t ctrl=kTRUE) { fUserControlled = ctrl; }
   Bool_t       HasUserControl() const { return fUserControlled; }
   void         SetEventHandled(Bool_t eh=kTRUE) { fEventHandled = eh; }
   Bool_t       IsEventHandled() const { return fEventHandled; }

   Bool_t   HandleDNDDrop(TDNDData *data);
   Atom_t   HandleDNDPosition(Int_t x, Int_t y, Atom_t action,
                              Int_t xroot, Int_t yroot);
   Atom_t   HandleDNDEnter(Atom_t * typelist);
   Bool_t   HandleDNDLeave();

   virtual TDNDData *GetDNDData(Atom_t) {
      return &fDNDData;
   }

   EColorMarkupMode GetColorMode() const { return fColorMode; }
   void SetColorMode(EColorMarkupMode colorMode) { fColorMode = colorMode; }

   ECheckMode GetCheckMode() const { return fCheckMode; }
   void SetCheckMode(ECheckMode mode) { fCheckMode = mode; }

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


## code



## example





<!-- TGListTree.md ends here -->
