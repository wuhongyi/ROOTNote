<!-- TGLabel.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 13:39:02 2016 (+0800)
;; Last-Updated: 三 9月 16 10:59:11 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TGLabel*

TGLabel 继承 TGFrame

## class

```cpp
   static FontStruct_t  GetDefaultFontStruct();/// Static returning label default font struct.
   static const TGGC   &GetDefaultGC();/// Static returning label default graphics context.

   TGLabel(const TGWindow *p, TGString *text,
           GContext_t norm = GetDefaultGC()(),
           FontStruct_t font = GetDefaultFontStruct(),
           UInt_t options = kChildFrame,
           Pixel_t back = GetDefaultFrameBackground());
/// Create a label GUI object. TGLabel will become the owner of the
/// text and will delete it in its dtor.

   TGLabel(const TGWindow *p = 0, const char *text = 0,
           GContext_t norm = GetDefaultGC()(),
           FontStruct_t font = GetDefaultFontStruct(),
           UInt_t options = kChildFrame,
           Pixel_t back = GetDefaultFrameBackground());
/// Create a label GUI object.

   virtual ~TGLabel();/// Delete label.

   virtual TGDimension GetDefaultSize() const;/// Return default size.

   const TGString *GetText() const { return fText; }
   virtual const char *GetTitle() const { return fText->Data(); }
   virtual void SetText(TGString *newText);
/// Set new text in label. After calling this method one needs to call
/// the parents frame's Layout() method to force updating of the label size.
/// The new_text is adopted by the TGLabel and will be properly deleted.

   void SetText(const char *newText) { SetText(new TGString(newText)); }
   virtual void ChangeText(const char *newText) { SetText(newText); } //*MENU*icon=bld_rename.png*
   virtual void SetTitle(const char *label) { SetText(label); }
   void  SetText(Int_t number) { SetText(new TGString(number)); }
   void  SetTextJustify(Int_t tmode);
/// Set text justification. Mode is an OR of the bits:
/// kTextTop, kTextBottom, kTextLeft, kTextRight, kTextCenterX and
/// kTextCenterY.

   Int_t GetTextJustify() const { return fTMode; }
   virtual void SetTextFont(TGFont *font, Bool_t global = kFALSE);
/// Changes text font specified by pointer to TGFont object.
/// If global is true font is changed globally - otherwise locally.

   virtual void SetTextFont(FontStruct_t font, Bool_t global = kFALSE);
/// Changes text font.
/// If global is true font is changed globally - otherwise locally.

   virtual void SetTextFont(const char *fontName, Bool_t global = kFALSE);
/// Changes text font specified by name.
/// If global is true font is changed globally - otherwise locally.

   virtual void SetTextColor(Pixel_t color, Bool_t global = kFALSE);
/// Changes text color.
/// If global is true color is changed globally - otherwise locally.

   virtual void SetTextColor(TColor *color, Bool_t global = kFALSE);
/// Changes text color.
/// If global is true color is changed globally - otherwise locally.

   virtual void SetForegroundColor(Pixel_t fore) { SetTextColor(fore); }
   virtual void Disable(Bool_t on = kTRUE)
               { fDisabled = on; fClient->NeedRedraw(this); } //*TOGGLE* *GETTER=IsDisabled
   virtual void Enable() { fDisabled = kFALSE; fClient->NeedRedraw(this); }
   Bool_t IsDisabled() const { return fDisabled; }
   Bool_t HasOwnFont() const;
/// Returns kTRUE if text attributes are unique.
/// Returns kFALSE if text attributes are shared (global).

   void  SetWrapLength(Int_t wl) { fWrapLength = wl; Layout(); }
   Int_t GetWrapLength() const { return fWrapLength; }

   void  Set3DStyle(Int_t style) { f3DStyle = style; fClient->NeedRedraw(this); }
   Int_t Get3DStyle() const { return f3DStyle; }

   void SetMargins(Int_t left=0, Int_t right=0, Int_t top=0, Int_t bottom=0)
      { fMLeft = left; fMRight = right; fMTop = top; fMBottom = bottom; }
   Int_t GetLeftMargin() const { return fMLeft; }
   Int_t GetRightMargin() const { return fMRight; }
   Int_t GetTopMargin() const { return fMTop; }
   Int_t GetBottomMargin() const { return fMBottom; }

   GContext_t GetNormGC() const { return fNormGC; }
   FontStruct_t GetFontStruct() const { return fFont->GetFontStruct(); }
   TGFont      *GetFont() const  { return fFont; }

   virtual void Layout();
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a label widget as a C++ statement(s) on output stream out.
```

## code

```cpp
#include "TGLabel.h"

// TGLabel
const char gReadyMsg[] = "Ready. You can drag list tree items to any \
pad in the canvas, or to the \"Base\" folder of the list tree itself...";
TGLabel *fStatus = new TGLabel(frame, new TGHotString(gReadyMsg));
fStatus->SetTextJustify(kTextLeft);
fStatus->SetTextColor(0x0000ff);
fStatus->Enable();
// fStatus->Disable();
// if (fStatus->IsDisabled()) ;
// fStatus->SetText("XXX");
// fStatus->SetText(125);
// fStatus->SetFont("XXX");
fStatus->SetText(Form("abc%ld",100);
frame->AddFrame(fStatus, new TGLayoutHints(kLHintsExpandX | kLHintsCenterY,10, 10, 10, 10));
```

## example



<!-- TGLabel.md ends here -->
