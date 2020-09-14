<!-- TGLayout.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 21:14:31 2016 (+0800)
;; Last-Updated: 二 11月  8 21:27:11 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGLayout

A number of different layout classes (TGLayoutManager,               
TGVerticalLayout, TGHorizontalLayout, TGLayoutHints, etc.).

TGLayoutHints : public TObject, TRefCnt , friend TGFrameElement , TGCompositeFrame
This class describes layout hints used by the layout classes.

TGFrameElement : public TObject  
Base class used in GUI containers

TGLayoutManager : public TObject  
Frame layout manager. This is an abstract class. 

TGVerticalLayout : public TGLayoutManager  
TGVerticalLayout and TGHorizontalLayout managers.

TGHorizontalLayout : public TGVerticalLayout

TGRowLayout : public TGVerticalLayout  
The follwing two layout managers do not make use of TGLayoutHints.

TGColumnLayout : public TGRowLayout

TGMatrixLayout : public TGLayoutManager  
This layout managers does not make use of TGLayoutHints.

TGTileLayout : public TGLayoutManager  
This are layout managers for the TGListView widget. 

TGListLayout : public TGTileLayout

TGListDetailsLayout : public TGTileLayout

## class

```cpp
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
```

**TGLayoutHints**

```cpp
   TGLayoutHints(ULong_t hints = kLHintsNormal,
                 Int_t padleft = 0, Int_t padright = 0,
                 Int_t padtop = 0, Int_t padbottom = 0):
     fFE(0), fPrev(0), fLayoutHints(hints), fPadtop(padtop), fPadbottom(padbottom),
     fPadleft(padleft), fPadright(padright)
     { SetRefCount(0); }

   TGLayoutHints(const TGLayoutHints &lh);

   virtual ~TGLayoutHints();

   ULong_t GetLayoutHints() const { return fLayoutHints; }
   Int_t   GetPadTop() const { return fPadtop; }
   Int_t   GetPadBottom() const { return fPadbottom; }
   Int_t   GetPadLeft() const { return fPadleft; }
   Int_t   GetPadRight() const { return fPadright; }

   virtual void SetLayoutHints(ULong_t lh) { fLayoutHints = lh; }
   virtual void SetPadTop(Int_t v)  {  fPadtop = v; }
   virtual void SetPadBottom(Int_t v)  {  fPadbottom = v; }
   virtual void SetPadLeft(Int_t v)  {  fPadleft = v; }
   virtual void SetPadRight(Int_t v)  {  fPadright = v; }

   void Print(Option_t* option = "") const;
   void ls(Option_t* option = "") const { Print(option); }

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGFrameElement**

```cpp

   TGFrame        *fFrame;    // frame used in layout
   Int_t           fState;    // EFrameState defined in TGFrame.h
   TGLayoutHints  *fLayout;   // layout hints used in layout

   TGFrameElement() : fFrame(0), fState(0), fLayout(0) { }
   TGFrameElement(TGFrame *f, TGLayoutHints *l);
   ~TGFrameElement();

   void Print(Option_t* option = "") const;
   void ls(Option_t* option = "") const { Print(option); }
```


**TGLayoutManager**

```cpp
   TGLayoutManager() : fModified(kTRUE) {}

   virtual void Layout() = 0;
   virtual TGDimension GetDefaultSize() const = 0;
   virtual void SetDefaultWidth(UInt_t /* w */) {}
   virtual void SetDefaultHeight(UInt_t /* h */) {}
   virtual Bool_t IsModified() const { return fModified; }
   virtual void   SetModified(Bool_t flag = kTRUE) { fModified = flag; }
```


**TGVerticalLayout**

```cpp
   TGVerticalLayout(TGCompositeFrame *main);

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGHorizontalLayout**

```cpp
   TGHorizontalLayout(TGCompositeFrame *main) : TGVerticalLayout(main) { }

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGRowLayout**

```cpp
   Int_t   fSep;             // interval between frames

   TGRowLayout(TGCompositeFrame *main, Int_t s = 0) :
      TGVerticalLayout(main), fSep(s) { }

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGColumnLayout**

```cpp
   TGColumnLayout(TGCompositeFrame *main, Int_t s = 0) : TGRowLayout(main, s) { }

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGMatrixLayout**

```cpp
   Int_t   fSep;                      // interval between frames
   Int_t   fHints;                    // layout hints (currently not used)
   UInt_t  fRows;                     // number of rows
   UInt_t  fColumns;                  // number of columns

   TGMatrixLayout(TGCompositeFrame *main, UInt_t r, UInt_t c, Int_t s=0, Int_t h=0);

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGTileLayout**

```cpp
   TGTileLayout(TGCompositeFrame *main, Int_t sep = 0);

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual Bool_t IsModified() const { return fModified; }
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGListLayout**

```cpp
   TGListLayout(TGCompositeFrame *main, Int_t sep = 0) :
      TGTileLayout(main, sep) { }

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


**TGListDetailsLayout**

```cpp
   TGListDetailsLayout(TGCompositeFrame *main, Int_t sep = 0, UInt_t w = 0) :
      TGTileLayout(main, sep), fWidth(w) { }

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SetDefaultWidth(UInt_t w) { fWidth = w; }
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


## code



## example



<!-- TGLayout.md ends here -->
