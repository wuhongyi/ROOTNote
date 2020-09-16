<!-- TGListBox.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 10:37:30 2016 (+0800)
;; Last-Updated: 三 9月 16 10:59:23 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TGListBox+

TGListBox 继承 TGCompositeFrame, TGWidget

A TGListBox widget.

A listbox is a box, possibly with scrollbar, containing entries.  
Currently entries are simple text strings (TGTextLBEntry).  
A TGListBox looks a lot like a TGCanvas. It has a TGViewPort  
containing a TGLBContainer which contains the entries and it also  
has a vertical scrollbar which becomes visible if there are more  
items than fit in the visible part of the container.  

```
Selecting an item in the listbox will generate the event:
kC_COMMAND, kCM_LISTBOX, listbox id, item id.   
```

## class

```cpp
   TGListBox(const TGWindow *p = 0, Int_t id = -1,
             UInt_t options = kSunkenFrame | kDoubleBorder,
             Pixel_t back = GetWhitePixel());
   virtual ~TGListBox();

   virtual void AddEntry(TGString *s, Int_t id);
   virtual void AddEntry(const char *s, Int_t id);
   virtual void AddEntry(TGLBEntry *lbe, TGLayoutHints *lhints);
   virtual void AddEntrySort(TGString *s, Int_t id);
   virtual void AddEntrySort(const char *s, Int_t id);
   virtual void AddEntrySort(TGLBEntry *lbe, TGLayoutHints *lhints);
   virtual void InsertEntry(TGString *s, Int_t id, Int_t afterID);
   virtual void InsertEntry(const char *s , Int_t id, Int_t afterID);
   virtual void InsertEntry(TGLBEntry *lbe, TGLayoutHints *lhints, Int_t afterID);
   virtual void NewEntry(const char *s = "Entry");             //*MENU*
   virtual void RemoveEntry(Int_t id = -1);                    //*MENU*
   virtual void RemoveAll();                                   //*MENU*
   virtual void RemoveEntries(Int_t from_ID, Int_t to_ID);
   virtual void ChangeBackground(Pixel_t back);
   virtual void SetTopEntry(Int_t id = -1);
   virtual void SetMultipleSelections(Bool_t multi = kTRUE)
                  { fLbc->SetMultipleSelections(multi); }      //*TOGGLE* *GETTER=GetMultipleSelections
   virtual Bool_t GetMultipleSelections() const
                  { return fLbc->GetMultipleSelections(); }
   virtual Int_t  GetNumberOfEntries() const
                  { return fLbc->GetList()->GetSize(); }
   virtual TGLBEntry    *GetEntry(Int_t id) const;
   virtual TGLBEntry    *FindEntry(const char *s) const;
   virtual TGFrame      *GetContainer() const { return fVport->GetContainer(); }
   virtual TGViewPort   *GetViewPort() const { return fVport; }
   virtual TGScrollBar  *GetScrollBar() const { return fVScrollbar; }
   virtual TGVScrollBar *GetVScrollbar() const { return fVScrollbar; }

   virtual void DrawBorder();
   virtual void Resize(UInt_t w, UInt_t h);
   virtual void Resize(TGDimension size) { Resize(size.fWidth, size.fHeight); }
   virtual void MoveResize(Int_t x, Int_t y, UInt_t w, UInt_t h);
   virtual void Layout();
   virtual void SetLayoutManager(TGLayoutManager*) { }
   virtual void SortByName(Bool_t ascend = kTRUE);   //*MENU*icon=bld_sortup.png*
   virtual void IntegralHeight(Bool_t mode) { fIntegralHeight = mode; }
   virtual TGDimension GetDefaultSize() const;

   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);

   virtual TGLBEntry *Select(Int_t id, Bool_t sel = kTRUE)
                                       { return fLbc->Select(id, sel); }
   virtual Int_t GetSelected() const;
   virtual Bool_t GetSelection(Int_t id) { return fLbc->GetSelection(id); }
   virtual TGLBEntry *GetSelectedEntry() const { return fLbc->GetSelectedEntry(); }
   virtual void GetSelectedEntries(TList *selected);
   UInt_t  GetItemVsize() const { return fItemVsize; }

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");

   virtual void Selected(Int_t widgetId, Int_t id);   //*SIGNAL*
   virtual void Selected(Int_t id) { Emit("Selected(Int_t)", id); } //*SIGNAL*
   virtual void Selected(const char *txt) { Emit("Selected(char*)", txt); } //*SIGNAL
   virtual void DoubleClicked(Int_t widgetId, Int_t id);   //*SIGNAL*
   virtual void DoubleClicked(Int_t id) { Emit("DoubleClicked(Int_t)", id); } //*SIGNAL*
   virtual void DoubleClicked(const char *txt) { Emit("DoubleClicked(char*)", txt); } //*SIGNAL
   virtual void SelectionChanged() { Emit("SelectionChanged()"); } //*SIGNAL*

```

## code

```cpp
#include "TGListBox.h"
```

```cpp
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
```
 




## example



<!-- TGListBox.md ends here -->
