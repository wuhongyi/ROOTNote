<!-- TPaveText.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 三 9月 16 12:48:26 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TPaveText*

继承 public TPave, TAttText

A Pave with several lines of text.

## class

```cpp
   TPaveText();
   TPaveText(Double_t x1, Double_t y1,Double_t x2 ,Double_t y2, Option_t *option="br");
   // PaveText normal constructor.
   // A PaveText is a Pave with several lines of text
   //  option = "TR" Top and Right shadows are drawn.
   //  option = "TL" Top and Left shadows are drawn.
   //  option = "BR" Bottom and Right shadows are drawn.
   //  option = "BL" Bottom and Left shadows are drawn.
   //  If none of these four above options is specified the default the
   //  option "BR" will be used to draw the border. To produces a pave
   //  without any border it is enough to specify the option "NB" (no border).
   //  option = "NDC" x1,y1,x2,y2 are given in NDC
   //  option = "ARC" corners are rounded
   // In case of option "ARC", the corner radius is specified
   // via TPave::SetCornerRadius(rad) where rad is given in percent
   // of the pave height (default value is 0.2).
   // The individual text items are entered via AddText
   // By default, text items inherits from the default pavetext AttText.
   // A title can be added later to this pavetext via TPaveText::SetLabel.

   TPaveText(const TPaveText &pavetext);
// pavetext copy constructor.

   virtual ~TPaveText();
   TPaveText& operator=(const TPaveText&);

   virtual TBox    *AddBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2);
// Add a new graphics box to this pavetext.

   virtual TLine   *AddLine(Double_t x1=0, Double_t y1=0, Double_t x2=0, Double_t y2=0);
// Add a new graphics line to this pavetext.

   virtual TText   *AddText(Double_t x1, Double_t y1, const char *label);
// Add a new Text line to this pavetext at given coordinates.

   virtual TText   *AddText(const char *label);
// Add a new Text line to this pavetext.

   virtual void     Clear(Option_t *option="");  // *MENU*
// Clear all lines in this pavetext.

   virtual void     DeleteText(); // *MENU*
// Delete text at the mouse position.

   virtual void     Draw(Option_t *option="");
// Draw this pavetext with its current attributes.

   virtual void     DrawFile(const char *filename, Option_t *option="");
// Draw lines in filename in this pavetext.

   virtual void     EditText(); // *MENU*
// Edit text at the mouse position.

   const char      *GetLabel() const {return fLabel.Data();}
   virtual TText   *GetLine(Int_t number) const;
// Get Pointer to line number in this pavetext.

   virtual TText   *GetLineWith(const char *text) const;
// Get Pointer to first containing string text in this pavetext.

   virtual TList   *GetListOfLines() const {return fLines;}
   Float_t          GetMargin() const {return fMargin;}
   virtual TObject *GetObject(Double_t &ymouse, Double_t &yobj) const;
// Get object pointed by the mouse in this pavetext.

   virtual Int_t    GetSize() const;
//  return number of text lines (ignoring Tlines, etc)

   virtual void     InsertLine(); // *MENU*
// Add a new lineine at the mouse position.

   virtual void     InsertText(const char *label); // *MENU*
// Add a new Text line at the mouse position.

   virtual void     Paint(Option_t *option="");
// Paint this pavetext with its current attributes.

   virtual void     PaintPrimitives(Int_t mode);
// Paint list of primitives in this pavetext.

   virtual void     Print(Option_t *option="") const;
   virtual void     ReadFile(const char *filename, Option_t *option="", Int_t nlines=50, Int_t fromline=0); // *MENU*
   // Read lines of filename in this pavetext.
   //  Read from line number fromline a total of nlines
   //  Note that this function changes the default text alignment to left/center

   virtual void     SaveLines(std::ostream &out, const char *name);
// Save lines of this pavetext as C++ statements on output stream out

   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
// Save primitive as a C++ statement(s) on output stream out

   virtual void     SetAllWith(const char *text, Option_t *option, Double_t value); // *MENU*
   // Set attribute option for all lines containing string text.
   // Possible options are all the AttText attributes
   //       Align, Color, Font, Size and Angle

   virtual void     SetLabel(const char *label) {fLabel = label;} // *MENU*
   virtual void     SetMargin(Float_t margin=0.05) {fMargin=margin;} // *MENU*
   virtual void     UseCurrentStyle();
```

## code


## example

```cpp
TPaveText *pt = new TPaveText(0.6,0.85,0.98,0.98,"brNDC");//添加图片的注释。
pt->SetFillColor(18);
pt->SetTextAlign(12);
pt->AddText("Use the axis Context Menu LabelsOption");
pt->AddText(" \"a\"   to sort by alphabetic order");
pt->AddText(" \">\"   to sort by decreasing vakues");
pt->AddText(" \"<\"   to sort by increasing vakues");
pt->Draw();
```





<!-- TPaveText.md ends here -->
