<!-- TRootEmbeddedCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 13:30:41 2016 (+0800)
;; Last-Updated: 三 9月 16 11:17:35 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TRootEmbeddedCanvas*


TRootEmbeddedCanvas 继承 TGCanvas , friend TRootEmbeddedContainer

This class creates a TGCanvas in which a TCanvas is created. Use  
 GetCanvas() to get a pointer to the TCanvas.

## class

```cpp
   TRootEmbeddedCanvas(const char *name = 0, const TGWindow *p = 0, UInt_t w = 10,
            UInt_t h = 10, UInt_t options = kSunkenFrame | kDoubleBorder,
            Pixel_t back = GetDefaultFrameBackground());
/// Create an TCanvas embedded in a TGFrame. A pointer to the TCanvas can
/// be obtained via the GetCanvas() member function. To embed a canvas
/// derived from a TCanvas do the following:
/// TRootEmbeddedCanvas *embedded = new TRootEmbeddedCanvas(0, p, w, h);
///      [note name must be 0, not null string ""]
/// Int_t wid = embedded->GetCanvasWindowId();
/// TMyCanvas *myc = new TMyCanvas("myname", 10, 10, wid);
/// embedded->AdoptCanvas(myc);
///      [ the MyCanvas is adopted by the embedded canvas and will be
///        destroyed by it ]

   virtual ~TRootEmbeddedCanvas();/// Delete embedded ROOT canvas.

   void       AdoptCanvas(TCanvas *c);/// Canvas c is adopted from this embedded canvas.
   TCanvas   *GetCanvas() const { return fCanvas; }
   Int_t      GetCanvasWindowId() const { return fCWinId; }
   Bool_t     GetAutoFit() const { return fAutoFit; }
   void       SetAutoFit(Bool_t fit = kTRUE) { fAutoFit = fit; }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
// Save an embedded canvas as a C++ statement(s) on output stream out.

   virtual Bool_t HandleDNDDrop(TDNDData *data);/// Handle drop events.
   virtual Atom_t HandleDNDPosition(Int_t /*x*/, Int_t /*y*/, Atom_t action,
                                    Int_t /*xroot*/, Int_t /*yroot*/);
/// Handle dragging position events.

   virtual Atom_t HandleDNDEnter(Atom_t * typelist);/// Handle drag enter events.
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
