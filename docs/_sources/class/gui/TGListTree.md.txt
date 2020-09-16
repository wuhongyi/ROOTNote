<!-- TGListTree.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 19:09:08 2016 (+0800)
;; Last-Updated: 三 9月 16 10:59:37 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TGListTree*

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
   virtual UInt_t          GetPicWidth() const;/// Return width of item's icon.

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
                     Bool_t checkbox = kFALSE);/// Create list tree item.
   virtual ~TGListTreeItemStd();/// Delete list tree item.

   virtual Pixel_t         GetActiveColor() const;/// Return color for marking items that are active or selected.
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
   virtual void            SetPictures(const TGPicture *opened, const TGPicture *closed);/// Change list tree item icons.
   virtual void            SetCheckBoxPictures(const TGPicture *checked, const TGPicture *unchecked);/// Change list tree check item icons.

   virtual void            SetCheckBox(Bool_t on = kTRUE);/// Set a check box on the tree node.
   virtual Bool_t          HasCheckBox() const { return fCheckBox; }
   virtual void            CheckItem(Bool_t checked = kTRUE) { fChecked = checked; }
   virtual void            Toggle() { fChecked = !fChecked; }
   virtual Bool_t          IsChecked() const { return fChecked; }

   virtual void            CheckAllChildren(Bool_t state = kTRUE);
/// Set all child items of this one checked if state=kTRUE,
/// unchecked if state=kFALSE.

   virtual void            CheckChildren(TGListTreeItem *item, Bool_t state);
/// Set all child items of 'item' checked if state=kTRUE;
/// unchecked if state=kFALSE.

   virtual Bool_t          HasCheckedChild(Bool_t first=kFALSE);/// Add all child items of 'item' into the list 'checked'.
   virtual Bool_t          HasUnCheckedChild(Bool_t first=kFALSE);/// Add all child items of 'item' into the list 'checked'.
   virtual void            UpdateState();/// Update the state of the node 'item' according to the children states.

   virtual Bool_t          HasColor() const { return fHasColor; }
   virtual Color_t         GetColor() const { return fColor; }
   virtual void            SetColor(Color_t color) { fHasColor = true;fColor = color; }
   virtual void            ClearColor() { fHasColor = false; }

   virtual void            SavePrimitive(std::ostream &out, Option_t *option, Int_t n);
/// Save a list tree item attributes as a C++ statements on output stream.
```


**TGListTree**

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
              UInt_t options = 0, Pixel_t back = GetWhitePixel());/// Create a list tree widget.
   TGListTree(TGCanvas *p, UInt_t options, Pixel_t back = GetWhitePixel());/// Create a list tree widget.

   virtual ~TGListTree();/// Delete list tree widget.

   virtual Bool_t HandleButton(Event_t *event);/// Handle button events in the list tree.
   virtual Bool_t HandleDoubleClick(Event_t *event);/// Handle double click event in the list tree (only for kButton1).
   virtual Bool_t HandleCrossing(Event_t *event);/// Handle mouse crossing event.
   virtual Bool_t HandleMotion(Event_t *event);
/// Handle mouse motion event. Used to set tool tip, to emit
/// MouseOver() signal and for DND handling.

   virtual Bool_t HandleKey(Event_t *event);/// The key press event handler converts a key press to some line editor action.

   virtual void SetCanvas(TGCanvas *canvas) { fCanvas = canvas; }
   virtual void DrawRegion(Int_t x, Int_t y, UInt_t w, UInt_t h);/// Redraw list tree.

   virtual void DrawOutline(Handle_t id, TGListTreeItem *item, Pixel_t col=0xbbbbbb,
                            Bool_t clear=kFALSE);/// Draw a outline of color 'col' around an item.
   virtual void DrawActive(Handle_t id, TGListTreeItem *item);/// Draw active item with its active color.

   virtual TGDimension GetDefaultSize() const
            { return TGDimension(fDefw, fDefh); }

   void            AddItem(TGListTreeItem *parent, TGListTreeItem *item);/// Add given item to list tree.
   TGListTreeItem *AddItem(TGListTreeItem *parent, const char *string,
                           const TGPicture *open = 0,
                           const TGPicture *closed = 0,
                           Bool_t checkbox = kFALSE);/// Add item to list tree. Returns new item.
   TGListTreeItem *AddItem(TGListTreeItem *parent, const char *string,
                           void *userData, const TGPicture *open = 0,
                           const TGPicture *closed = 0,
                           Bool_t checkbox = kFALSE);
/// Add item to list tree. If item with same userData already exists
/// don't add it. Returns new item.

   void  RenameItem(TGListTreeItem *item, const char *string);/// Rename item in list tree.
   Int_t DeleteItem(TGListTreeItem *item);/// Delete item from list tree.
   void  OpenItem(TGListTreeItem *item);/// Open item in list tree (i.e. show child items).
   void  CloseItem(TGListTreeItem *item);/// Close item in list tree (i.e. hide child items).
   void  CheckItem(TGListTreeItem *item, Bool_t check = kTRUE);/// Set check button state for the node 'item'.
   void  SetCheckBox(TGListTreeItem *item, Bool_t on = kTRUE);/// Set check button state for the node 'item'.
   void  ToggleItem(TGListTreeItem *item);/// Toggle check button state of the node 'item'.
   Int_t RecursiveDeleteItem(TGListTreeItem *item, void *userData);
/// Delete item with fUserData == ptr. Search tree downwards starting at item.

   Int_t DeleteChildren(TGListTreeItem *item);/// Delete children of item from list.
   Int_t Reparent(TGListTreeItem *item, TGListTreeItem *newparent);/// Make newparent the new parent of item.
   Int_t ReparentChildren(TGListTreeItem *item, TGListTreeItem *newparent);/// Make newparent the new parent of the children of item.
   void  SetToolTipItem(TGListTreeItem *item, const char *string);
/// Set tooltip text for this item. By default an item for which the
/// userData is a pointer to an TObject the TObject::GetTitle() will
/// be used to get the tip text.

   void  SetAutoTips(Bool_t on = kTRUE) { fAutoTips = on; }
   void  SetAutoCheckBoxPic(Bool_t on) { fAutoCheckBoxPic = on; }
   void  SetSelected(TGListTreeItem *item) { fSelected = item; }
   void  AdjustPosition(TGListTreeItem *item);
/// Move content to position of item. If item is 0, move to position
/// of currently selected item.

   void  AdjustPosition() { TGContainer::AdjustPosition(); }

   // overwrite TGContainer's methods
   void Home(Bool_t select = kFALSE);/// Move content to the top.
   void End(Bool_t select = kFALSE);/// Move content to the bottom.
   void PageUp(Bool_t select = kFALSE);/// Move content one page up.
   void PageDown(Bool_t select = kFALSE);/// Move content one page down.
   void LineUp(Bool_t select = kFALSE);/// Move content one item-size up.
   void LineDown(Bool_t select = kFALSE);/// Move content one item-size down.
   void Search(Bool_t close = kTRUE);/// Invokes search dialog. Looks for item with the entered name.

   Int_t Sort(TGListTreeItem *item);/// Sort items starting with item.
   Int_t SortSiblings(TGListTreeItem *item);/// Sort siblings of item.
   Int_t SortChildren(TGListTreeItem *item);/// Sort siblings of item.
   void  HighlightItem(TGListTreeItem *item);/// Highlight item.
   void  ClearHighlighted();/// Un highlight items.
   void  GetPathnameFromItem(TGListTreeItem *item, char *path, Int_t depth = 0);
/// Get pathname from item. Use depth to limit path name to last
/// depth levels. By default depth is not limited.

   void  UnselectAll(Bool_t draw);/// Unselect all items.
   void  SetToolTipText(const char *text, Int_t x, Int_t y, Long_t delayms);
/// Set tool tip text associated with this item. The delay is in
/// milliseconds (minimum 250). To remove tool tip call method with
/// delayms = 0. To change delayms you first have to call this method
/// with delayms=0.

   void  HighlightItem(TGListTreeItem *item, Bool_t state, Bool_t draw);/// Highlight tree item.
   void  HighlightChildren(TGListTreeItem *item, Bool_t state, Bool_t draw);/// Higlight item children.
   void  DisableOpen(Bool_t disable = kTRUE) { fDisableOpen = disable;}
   void  GetChecked(TList *checked);
/// Add all checked list tree items of this list tree into
/// the list 'checked'. This list is not adopted and must
/// be deleted by the user later.

   void  GetCheckedChildren(TList *checked, TGListTreeItem *item);
/// Add all child items of 'item' into the list 'checked'.

   void  CheckAllChildren(TGListTreeItem *item, Bool_t state);
/// Check all child items of 'item' and 'item' itself according
/// to the state value: kTRUE means check all, kFALSE - uncheck all.

   TGListTreeItem *GetFirstItem()  const { return fFirst; }
   TGListTreeItem *GetSelected()   const { return fSelected; }
   TGListTreeItem *GetCurrent()    const { return fCurrent; }
   TGListTreeItem *GetBelowMouse() const { return fBelowMouse; }
   TGListTreeItem *FindSiblingByName(TGListTreeItem *item, const char *name);/// Find sibling of item by name.
   TGListTreeItem *FindSiblingByData(TGListTreeItem *item, void *userData);/// Find sibling of item by userData.
   TGListTreeItem *FindChildByName(TGListTreeItem *item, const char *name);/// Find child of item by name.
   TGListTreeItem *FindChildByData(TGListTreeItem *item, void *userData);/// Find child of item by userData.
   TGListTreeItem *FindItemByPathname(const char *path);
/// Find item by pathname. Pathname is in the form of /xx/yy/zz. If zz
/// in path /xx/yy is found it returns item, 0 otherwise.

   TGListTreeItem *FindItemByObj(TGListTreeItem *item, void *ptr);
/// Find item with fUserData == ptr. Search tree downwards starting at item.

   void  AddItem(const char *string) { AddItem(fSelected, string); } //*MENU*
   void  AddRoot(const char *string) { AddItem(0, string); } //*MENU*
   Int_t DeleteSelected() { return (fSelected ? DeleteItem(fSelected) : 0); } //*MENU*
   void  RenameSelected(const char *string) { if (fSelected) RenameItem(fSelected, string); } //*MENU*

   virtual void MouseOver(TGListTreeItem *entry);  //*SIGNAL*    /// Signal emitted when pointer is over entry.
   virtual void MouseOver(TGListTreeItem *entry, UInt_t mask);  //*SIGNAL*    /// Signal emitted when pointer is over entry.
   virtual void KeyPressed(TGListTreeItem *entry, UInt_t keysym, UInt_t mask);  //*SIGNAL*
/// Signal emitted when keyboard key pressed
/// entry - selected item
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

   virtual void ReturnPressed(TGListTreeItem *entry);  //*SIGNAL*    /// Emit ReturnPressed() signal.
   virtual void Clicked(TGListTreeItem *entry, Int_t btn);  //*SIGNAL*    /// Emit Clicked() signal.
   virtual void Clicked(TGListTreeItem *entry, Int_t btn, Int_t x, Int_t y);  //*SIGNAL*    /// Emit Clicked() signal.
   virtual void Clicked(TGListTreeItem *entry, Int_t btn, UInt_t mask, Int_t x, Int_t y);  //*SIGNAL*    /// Emit Clicked() signal.
   virtual void DoubleClicked(TGListTreeItem *entry, Int_t btn);  //*SIGNAL*    /// Emit DoubleClicked() signal.
   virtual void DoubleClicked(TGListTreeItem *entry, Int_t btn, Int_t x, Int_t y);  //*SIGNAL*    /// Emit DoubleClicked() signal.   
   virtual void Checked(TObject *obj, Bool_t check);  //*SIGNAL*
   virtual void DataDropped(TGListTreeItem *item, TDNDData *data);  //*SIGNAL*    /// Emit DataDropped() signal.

   // Utility functions
   Int_t        FontHeight();/// Returns height of currently used font.
   Int_t        FontAscent();/// Returns ascent of currently used font.
   Int_t        TextWidth(const char *c);/// Returns text width relative to currently used font.

   static const TGPicture *GetOpenPic();/// Returns the icon used by items in open state.
   static const TGPicture *GetClosedPic();/// Returns the icon used by items in closed state.
   static const TGPicture *GetCheckedPic();/// Returns the icon used for checked checkbox.
   static const TGPicture *GetUncheckedPic();/// Returns the icon used for unchecked checkbox.

   // User control
   void         SetUserControl(Bool_t ctrl=kTRUE) { fUserControlled = ctrl; }
   Bool_t       HasUserControl() const { return fUserControlled; }
   void         SetEventHandled(Bool_t eh=kTRUE) { fEventHandled = eh; }
   Bool_t       IsEventHandled() const { return fEventHandled; }

   Bool_t   HandleDNDDrop(TDNDData *data);/// Handle drop events.
   Atom_t   HandleDNDPosition(Int_t x, Int_t y, Atom_t action,
                              Int_t xroot, Int_t yroot);/// Handle dragging position events.
   Atom_t   HandleDNDEnter(Atom_t * typelist);/// Handle drag enter events.
   Bool_t   HandleDNDLeave();/// Handle drag leave events.

   virtual TDNDData *GetDNDData(Atom_t) {
      return &fDNDData;
   }

   EColorMarkupMode GetColorMode() const { return fColorMode; }
   void SetColorMode(EColorMarkupMode colorMode) { fColorMode = colorMode; }

   ECheckMode GetCheckMode() const { return fCheckMode; }
   void SetCheckMode(ECheckMode mode) { fCheckMode = mode; }

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a list tree widget as a C++ statements on output stream out.
```


## code



## example





<!-- TGListTree.md ends here -->
