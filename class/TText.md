<!-- TText.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 17:13:44 2016 (+0800)
;; Last-Updated: 一 10月 31 21:04:32 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TText

继承 TNamed, TAttText, TAttBBox2D

Base class for several text objects.

See TAttText for a list of text attributes or fonts,
and also for a discussion on text speed and font quality.

By default, the text is drawn in the pad coordinates system.
One can draw in NDC coordinates [0,1] if the function SetNDC
is called for a TText object.

## class

```cpp
   TText();
   TText(Double_t x, Double_t y, const char *text);
   TText(Double_t x, Double_t y, const wchar_t *text);
   TText(const TText &text);
   virtual ~TText();
   void             Copy(TObject &text) const;
/// Copy this text to text.

   virtual Int_t    DistancetoPrimitive(Int_t px, Int_t py);
/// Compute distance from point px,py to a string.
/// The rectangle surrounding this string is evaluated.
/// If the point (px,py) is in the rectangle, the distance is set to zero.

   virtual TText   *DrawText(Double_t x, Double_t y, const char *text);
/// Draw this text with new coordinates.

   virtual TText   *DrawText(Double_t x, Double_t y, const wchar_t *text);
/// Draw this text with new coordinates.

   virtual TText   *DrawTextNDC(Double_t x, Double_t y, const char *text);
/// Draw this text with new coordinates in NDC.

   virtual TText   *DrawTextNDC(Double_t x, Double_t y, const wchar_t *text);
/// Draw this text with new coordinates in NDC.

   virtual void     ExecuteEvent(Int_t event, Int_t px, Int_t py);
/// Execute action corresponding to one event.
///  This member function must be implemented to realize the action
///  corresponding to the mouse click on the object in the window

   virtual void     GetControlBox(Int_t x, Int_t y, Double_t theta,
                                  Int_t cBoxX[4], Int_t cBoxY[4]);
/// Return the text control box. The text position coordinates is (x,y) and
/// the text angle is theta. The control box coordinates are returned in cBoxX
/// and cBoxY.

   Double_t         GetX() const  { return fX; }
   virtual void     GetBoundingBox(UInt_t &w, UInt_t &h, Bool_t angle = kFALSE);
/// Return text size in pixels. By default the size returned does not take
/// into account the text angle (angle = kFALSE). If angle is set to kTRUE
/// w and h take the angle into account.

   virtual void     GetTextAscentDescent(UInt_t &a, UInt_t &d, const char *text) const;
/// Return text ascent and descent for string text
///  - in a return total text ascent
///  - in d return text descent

   virtual void     GetTextAscentDescent(UInt_t &a, UInt_t &d, const wchar_t *text) const;
/// Return text ascent and descent for string text
///  - in a return total text ascent
///  - in d return text descent

   virtual void     GetTextExtent(UInt_t &w, UInt_t &h, const char *text) const;
/// Return text extent for string text
///  - in w return total text width
///  - in h return text height

   virtual void     GetTextExtent(UInt_t &w, UInt_t &h, const wchar_t *text) const;
/// Return text extent for string text
///  - in w return total text width
///  - in h return text height

   virtual void     GetTextAdvance(UInt_t &a, const char *text, const Bool_t kern=kTRUE) const;
/// Return text advance for string text
/// if kern is true (default) kerning is taken into account. If it is false
/// the kerning is not taken into account.

   const void *     GetWcsTitle(void) const;
/// Returns the text as UNICODE.

   Double_t         GetY() const  { return fY; }

   virtual void     ls(Option_t *option="") const;
/// List this text with its attributes.

   virtual void     Paint(Option_t *option="");
/// Paint this text with its current attributes.

   virtual void     PaintControlBox(Int_t x, Int_t y, Double_t theta);
/// Paint the text control box. (x,y) are the coordinates where the control
/// box should be painted and theta is the angle of the box.

   virtual void     PaintText(Double_t x, Double_t y, const char *text);
/// Draw this text with new coordinates.

   virtual void     PaintText(Double_t x, Double_t y, const wchar_t *text);
/// Draw this text with new coordinates.

   virtual void     PaintTextNDC(Double_t u, Double_t v, const char *text);
/// Draw this text with new coordinates in NDC.

   virtual void     PaintTextNDC(Double_t u, Double_t v, const wchar_t *text);
/// Draw this text with new coordinates in NDC.

   virtual void     Print(Option_t *option="") const;
/// Dump this text with its attributes.

   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save primitive as a C++ statement(s) on output stream out

   virtual void     SetMbTitle(const wchar_t *title=L""); // *MENU*
/// Change (i.e. set) the title of the TNamed.

   virtual void     SetNDC(Bool_t isNDC=kTRUE);
/// Set NDC mode on if isNDC = kTRUE, off otherwise

   virtual void     SetText(Double_t x, Double_t y, const char *text) {fX=x; fY=y; SetTitle(text);} // *MENU* *ARGS={x=>fX,y=>fY,text=>fTitle}
   virtual void     SetText(Double_t x, Double_t y, const wchar_t *text) {fX=x; fY=y; SetMbTitle(text);}
   virtual void     SetX(Double_t x) { fX = x; } // *MENU*
   virtual void     SetY(Double_t y) { fY = y; } // *MENU*

   virtual Rectangle_t  GetBBox();
/// Return the "bounding Box" of the Box

   virtual TPoint       GetBBoxCenter();
/// Return the point given by Alignment as 'center'

   virtual void         SetBBoxCenter(const TPoint &p);
/// Set the point given by Alignment as 'center'

   virtual void         SetBBoxCenterX(const Int_t x);
/// Set X coordinate of the point given by Alignment as 'center'

   virtual void         SetBBoxCenterY(const Int_t y);
/// Set Y coordinate of the point given by Alignment as 'center'

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
