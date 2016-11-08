<!-- TRootEmbeddedCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 13:30:41 2016 (+0800)
;; Last-Updated: 二 11月  8 20:55:00 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TRootEmbeddedCanvas


TRootEmbeddedCanvas 继承 TGCanvas , friend TRootEmbeddedContainer

This class creates a TGCanvas in which a TCanvas is created. Use  
 GetCanvas() to get a pointer to the TCanvas.

## class

```cpp
   TRootEmbeddedCanvas(const char *name = 0, const TGWindow *p = 0, UInt_t w = 10,
            UInt_t h = 10, UInt_t options = kSunkenFrame | kDoubleBorder,
            Pixel_t back = GetDefaultFrameBackground());
   virtual ~TRootEmbeddedCanvas();

   void       AdoptCanvas(TCanvas *c);
   TCanvas   *GetCanvas() const { return fCanvas; }
   Int_t      GetCanvasWindowId() const { return fCWinId; }
   Bool_t     GetAutoFit() const { return fAutoFit; }
   void       SetAutoFit(Bool_t fit = kTRUE) { fAutoFit = fit; }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");

   virtual Bool_t HandleDNDDrop(TDNDData *data);
   virtual Atom_t HandleDNDPosition(Int_t /*x*/, Int_t /*y*/, Atom_t action,
                                    Int_t /*xroot*/, Int_t /*yroot*/);
   virtual Atom_t HandleDNDEnter(Atom_t * typelist);
   virtual Bool_t HandleDNDLeave();
```

## code

```cpp
#include "TRootEmbeddedCanvas.h"

// TRootEmbeddedCanvas
// 画板
TRootEmbeddedCanvas *fCanvas= new TRootEmbeddedCanvas("Canvas", frame, 600, 400);
TGLayoutHints *fLcan = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10, 10, 10, 10);
frame->AddFrame(fCanvas, fLcan);
fCanvas->GetCanvas()->SetFillColor(33);
fCanvas->GetCanvas()->SetFrameFillColor(41);
fCanvas->GetCanvas()->SetBorderMode(0);
fCanvas->GetCanvas()->SetGrid();
fCanvas->GetCanvas()->SetLogy();
fCanvas->GetCanvas()->Modified();
fCanvas->GetCanvas()->Update();
```

## example




<!-- TRootEmbeddedCanvas.md ends here -->
