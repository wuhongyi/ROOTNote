<!-- TText.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 17:13:44 2016 (+0800)
;; Last-Updated: 二 9月 13 17:51:30 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TText

继承 TNamed, TAttText, TAttBBox2D

## class

```cpp
   TText();
   TText(Double_t x, Double_t y, const char *text);
   TText(Double_t x, Double_t y, const wchar_t *text);
   TText(const TText &text);
   virtual ~TText();
   void             Copy(TObject &text) const;
   virtual Int_t    DistancetoPrimitive(Int_t px, Int_t py);
   virtual TText   *DrawText(Double_t x, Double_t y, const char *text);
   virtual TText   *DrawText(Double_t x, Double_t y, const wchar_t *text);
   virtual TText   *DrawTextNDC(Double_t x, Double_t y, const char *text);
   virtual TText   *DrawTextNDC(Double_t x, Double_t y, const wchar_t *text);
   virtual void     ExecuteEvent(Int_t event, Int_t px, Int_t py);

   virtual void     GetControlBox(Int_t x, Int_t y, Double_t theta,
                                  Int_t cBoxX[4], Int_t cBoxY[4]);
   Double_t         GetX() const  { return fX; }
   virtual void     GetBoundingBox(UInt_t &w, UInt_t &h, Bool_t angle = kFALSE);
   virtual void     GetTextAscentDescent(UInt_t &a, UInt_t &d, const char *text) const;
   virtual void     GetTextAscentDescent(UInt_t &a, UInt_t &d, const wchar_t *text) const;
   virtual void     GetTextExtent(UInt_t &w, UInt_t &h, const char *text) const;
   virtual void     GetTextExtent(UInt_t &w, UInt_t &h, const wchar_t *text) const;
   virtual void     GetTextAdvance(UInt_t &a, const char *text, const Bool_t kern=kTRUE) const;
   const void *     GetWcsTitle(void) const;
   Double_t         GetY() const  { return fY; }

   virtual void     ls(Option_t *option="") const;
   virtual void     Paint(Option_t *option="");
   virtual void     PaintControlBox(Int_t x, Int_t y, Double_t theta);
   virtual void     PaintText(Double_t x, Double_t y, const char *text);
   virtual void     PaintText(Double_t x, Double_t y, const wchar_t *text);
   virtual void     PaintTextNDC(Double_t u, Double_t v, const char *text);
   virtual void     PaintTextNDC(Double_t u, Double_t v, const wchar_t *text);
   virtual void     Print(Option_t *option="") const;
   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual void     SetMbTitle(const wchar_t *title=L""); // *MENU*
   virtual void     SetNDC(Bool_t isNDC=kTRUE);
   virtual void     SetText(Double_t x, Double_t y, const char *text) {fX=x; fY=y; SetTitle(text);} // *MENU* *ARGS={x=>fX,y=>fY,text=>fTitle}
   virtual void     SetText(Double_t x, Double_t y, const wchar_t *text) {fX=x; fY=y; SetMbTitle(text);}
   virtual void     SetX(Double_t x) { fX = x; } // *MENU*
   virtual void     SetY(Double_t y) { fY = y; } // *MENU*

   virtual Rectangle_t  GetBBox();
   virtual TPoint       GetBBoxCenter();
   virtual void         SetBBoxCenter(const TPoint &p);
   virtual void         SetBBoxCenterX(const Int_t x);
   virtual void         SetBBoxCenterY(const Int_t y);
   virtual void         SetBBoxX1(const Int_t x); //Not Implemented
   virtual void         SetBBoxX2(const Int_t x); //Not Implemented
   virtual void         SetBBoxY1(const Int_t y); //Not Implemented
   virtual void         SetBBoxY2(const Int_t y); //Not Implemented
```

## code

```cpp
// By default, the text is drawn in the pad coordinates system. One can draw in NDC coordinates [0,1] if the function SetNDC is called for a TText object.
   TText *t = new TText(.5,.5,"Hello World !");
   t->SetTextAlign(22);
   t->SetTextColor(kRed+2);
   t->SetTextFont(43);
   t->SetTextSize(40);
   t->SetTextAngle(45);
   t->Draw();
```


## example





<!-- TText.md ends here -->
