<!-- TGFontDialog.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:30:11 2016 (+0800)
;; Last-Updated: 三 9月 16 10:58:35 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGFontDialog*

The TGFontDialog allows easy font and font attribute selection.

TGFontDialog 继承 TGTransientFrame

## class

```cpp
   struct FontProp_t {
      TString     fName;               // font name
      Int_t       fSize;               // font size
      UInt_t      fAlign;              // text alignment
      Pixel_t     fColor;              // text color
      Bool_t      fBold;               // bold flag
      Bool_t      fItalic;             // italic flag
   };

   TGFontDialog(const TGWindow *parent = 0, const TGWindow *t = 0,
                FontProp_t *fontProp = 0, const TString &sample = "",
                char **fontList = 0, Bool_t wait = kTRUE);
/// Create font dialog. When closed via OK button fontProp is set to
/// the newly selected font. If closed via Cancel button or WM close box
/// fontProp->fName == "".

   virtual ~TGFontDialog();

   virtual void SetFont(TGFont *font);
   virtual void SetColor(Pixel_t color);
   virtual void SetAlign(Int_t align);
   virtual void EnableAlign(Bool_t on = kTRUE);/// Enable/disable align combobox
   virtual void UpdateStyleSize(const char *family);/// Build font style and size list boxes

   virtual void FontSelected(char *font)
            { Emit("FontSelected(char*)", font); }  //*SIGNAL*
   virtual void AlignSelected(Int_t a)
            { Emit("AlignSelected(Int_t)", a); }   //*SIGNAL*
   virtual void ColorSelected(Pixel_t c)
            { Emit("ColorSelected(Pixel_t)", c); }  //*SIGNAL*

```

<!-- TGFontDialog.md ends here -->
