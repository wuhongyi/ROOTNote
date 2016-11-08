<!-- TGComboBox.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 10:55:03 2016 (+0800)
;; Last-Updated: 二 11月  8 20:44:19 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGComboBox

TGComboBox 继承 TGCompositeFrame, TGWidget

A combobox (also known as a drop down listbox) allows the selection  
of one item out of a list of items. The selected item is visible in  
a little window. To view the list of possible items one has to click  
on a button on the right of the little window. This will drop down  
a listbox. After selecting an item from the listbox the box will    
disappear and the newly selected item will be shown in the little    
window.

```
Selecting an item in the combobox will generate the event:
kC_COMMAND, kCM_COMBOBOX, combobox id, item id.
```

TGLineStyleComboBox 继承 TGComboBox  
The TGLineStyleComboBox user callable and it creates a combobox for selecting the line style.

TGLineWidthComboBox 继承 TGComboBox  
The TGLineWidthComboBox user callable and it creates a combobox for selecting the line width.

TGFontTypeComboBox 继承 TGComboBox  
The TGFontTypeComboBox is user callable and it creates a combobox for selecting the font.



## class

**TGComboBox**

```cpp
   TGComboBox(const TGWindow *p = 0, Int_t id = -1,
              UInt_t options = kHorizontalFrame | kSunkenFrame | kDoubleBorder,
              Pixel_t back = GetWhitePixel());
   TGComboBox(const TGWindow *p, const char *text, Int_t id = -1,
              UInt_t options = kHorizontalFrame | kSunkenFrame | kDoubleBorder,
              Pixel_t back = GetWhitePixel());

   virtual ~TGComboBox();

   virtual void DrawBorder();
   virtual TGDimension GetDefaultSize() const { return TGDimension(fWidth, fHeight); }

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleDoubleClick(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual Bool_t HandleSelection(Event_t *event);
   virtual Bool_t HandleSelectionRequest(Event_t *event);
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);

   virtual void AddEntry(TGString *s, Int_t id)
                        { fListBox->AddEntry(s, id); Resize(); }
   virtual void AddEntry(const char *s, Int_t id)
                        { fListBox->AddEntry(s, id); Resize(); }
   virtual void AddEntry(TGLBEntry *lbe, TGLayoutHints *lhints)
                        { fListBox->AddEntry(lbe, lhints); Resize(); }
   virtual void InsertEntry(TGString *s, Int_t id, Int_t afterID)
                        { fListBox->InsertEntry(s, id, afterID); Resize(); }
   virtual void InsertEntry(const char *s, Int_t id, Int_t afterID)
                        { fListBox->InsertEntry(s, id, afterID); Resize(); }
   virtual void InsertEntry(TGLBEntry *lbe, TGLayoutHints *lhints, Int_t afterID)
                        { fListBox->InsertEntry(lbe, lhints, afterID); Resize(); }
   virtual void NewEntry(const char *s = "Entry")
                        { fListBox->NewEntry(s); Resize(); }       //*MENU*
   virtual void RemoveEntry(Int_t id = -1);                        //*MENU*
   virtual void RemoveAll();                                       //*MENU*
   virtual void Layout();
   virtual Bool_t IsTextInputEnabled() const { return (fTextEntry != 0); }
   virtual void EnableTextInput(Bool_t on);    //*TOGGLE* *GETTER=IsTextInputEnabled
   virtual void RemoveEntries(Int_t from_ID, Int_t to_ID)
                        { fListBox->RemoveEntries(from_ID, to_ID); }
   virtual Int_t GetNumberOfEntries() const
                        { return fListBox->GetNumberOfEntries(); }

   virtual TGListBox    *GetListBox() const { return fListBox; }
   virtual TGTextEntry  *GetTextEntry() const { return fTextEntry; }
   virtual TGLBEntry    *FindEntry(const char *s) const;
   virtual void  Select(Int_t id, Bool_t emit = kTRUE);
   virtual Int_t GetSelected() const { return fListBox->GetSelected(); }
   virtual TGLBEntry *GetSelectedEntry() const
                        { return fListBox->GetSelectedEntry(); }
   virtual void SetTopEntry(TGLBEntry *e, TGLayoutHints *lh);
   virtual void SetEnabled(Bool_t on = kTRUE);   //*TOGGLE* *GETTER=IsEnabled
   virtual Bool_t IsEnabled() const { return  fDDButton->IsEnabled(); }
   virtual void SortByName(Bool_t ascend = kTRUE)
                  { fListBox->SortByName(ascend); }            //*MENU*icon=bld_sortup.png*

   virtual void Selected(Int_t widgetId, Int_t id);                  // *SIGNAL*
   virtual void Selected(Int_t id) { Emit("Selected(Int_t)", id); }  // *SIGNAL*
   virtual void Selected(const char *txt) { Emit("Selected(char*)", txt); } // *SIGNAL*
   virtual void ReturnPressed();                                     // *SIGNAL*
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGLineStyleComboBox**

```cpp
   TGLineStyleComboBox(const TGWindow *p = 0, Int_t id = -1,
              UInt_t options = kHorizontalFrame | kSunkenFrame | kDoubleBorder,
              Pixel_t back = GetWhitePixel());

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGLineWidthComboBox**

```cpp
   TGLineWidthComboBox(const TGWindow *p = 0, Int_t id = -1,
              UInt_t options = kHorizontalFrame | kSunkenFrame | kDoubleBorder,
              Pixel_t back = GetWhitePixel(), Bool_t none=kFALSE);

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGFontTypeComboBox**

```cpp
   TGFontTypeComboBox(const TGWindow *p = 0, Int_t id = -1,
            UInt_t options = kHorizontalFrame | kSunkenFrame | kDoubleBorder,
            Pixel_t bask = GetWhitePixel());
   virtual ~TGFontTypeComboBox();
```


## code

```cpp
#include "TGComboBox.h"

// TGComboBox
// 下拉选项
TGComboBox *fMonthBox;
fMonthBox = new TGComboBox(frame);
frame->AddFrame(fMonthBox, new TGLayoutHints(kLHintsLeft, 5, 5, 2, 2));
fMonthBox->AddEntry("AAA", 1);
fMonthBox->AddEntry("BBB", 2);
fMonthBox->AddEntry("CCC", 3);
fMonthBox->Select(1);
// fMonthBox->Resize(100, /*fYearEntry*/->GetHeight());
```


## example




<!-- TGComboBox.md ends here -->
