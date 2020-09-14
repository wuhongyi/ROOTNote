<!-- TPaveStats.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 一 10月 31 22:02:19 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TPaveStats

继承 TPaveText

## class

```cpp
   TPaveStats();
   TPaveStats(Double_t x1, Double_t y1,Double_t x2 ,Double_t y2, Option_t *option="br");/// TPaveStats normal constructor.
   virtual ~TPaveStats();
   virtual TBox    *AddBox(Double_t , Double_t , Double_t , Double_t) {return 0;}
   virtual TLine   *AddLine(Double_t , Double_t , Double_t, Double_t) {return 0;}
   virtual void     DeleteText() { }
   virtual void     EditText() { }
   virtual const char  *GetFitFormat()  const {return fFitFormat.Data();}
   virtual const char  *GetStatFormat() const {return fStatFormat.Data();}
   Int_t            GetOptFit() const;/// Return the fit option.
   Int_t            GetOptStat() const;/// Return the stat option.
   TObject         *GetParent() const {return fParent;}
   virtual void     Paint(Option_t *option="");/// Paint the pave stat.
   virtual void     InsertText(const char *) { }
   virtual void     InsertLine() { }
   virtual void     ReadFile(const char *, Option_t *, Int_t, Int_t) { }
   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save primitive as a C++ statement(s) on output stream out.

   virtual void     SaveStyle(); // *MENU*
/// Save This TPaveStats options in current style.

   virtual void     SetAllWith(const char *, Option_t *, Double_t) { }
   virtual void     SetMargin(Float_t) { }
   virtual void     SetFitFormat(const char *format="5.4g");    // *MENU*
/// Change (i.e. set) the format for printing fit parameters in statistics box.

   virtual void     SetStatFormat(const char *format="6.4g");   // *MENU*
/// Change (i.e. set) the format for printing statistics.

   void             SetOptFit(Int_t fit=1);                     // *MENU*
/// Set the fit option.

   void             SetOptStat(Int_t stat=1);                   // *MENU*
/// Set the stat option.

   void             SetParent(TObject*obj) {fParent = obj;}
   virtual void     UseCurrentStyle();
/// Replace current attributes by current style.
```

## code

```cpp
//设置TPave参数
TPaveStats *ps2 = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
ps2->SetX1NDC(0.65); ps2->SetX2NDC(0.85);//设置位置
ps2->SetTextColor(kRed);//设置颜色
```

```cpp
// When a histogram is painted, a TPaveStats object is created and added
// to the list of functions of the histogram. If a TPaveStats object
// already exists in the histogram list of functions, the existing object is just
// updated with the current histogram parameters.

// Once a histogram is painted, the statistics box can be accessed using
// h->FindObject("stats"). In the command line it is enough to do:

Root > h->Draw()
Root > TPaveStats *st = (TPaveStats*)h->FindObject("stats")

// because after h->Draw() the histogram is automatically painted. But
// in a script file the painting should be forced using gPad->Update()
// in order to make sure the statistics box is created:

h->Draw();
gPad->Update();
TPaveStats *st = (TPaveStats*)h->FindObject("stats");

// Without gPad->Update() the line h->FindObject("stats")
// returns a null pointer.

// When a histogram is drawn with the option "SAME", the statistics box
// is not drawn. To force the statistics box drawing with the option
// "SAME", the option "SAMES" must be used.
// If the new statistics box hides the previous statistics box, one can change
// its position with these lines ("h" being the pointer to the histogram):

Root > TPaveStats *st = (TPaveStats*)h->FindObject("stats")
Root > st->SetX1NDC(newx1); //new x start position
Root > st->SetX2NDC(newx2); //new x end position

// To change the type of information for an histogram with an existing
// TPaveStats one should do:

st->SetOptStat(mode);

// Where "mode" has the same meaning than when calling
// gStyle->SetOptStat(mode)` (see above).

// One can delete the statistics box for a histogram TH1* h with:

h->SetStats(0)

// and activate it again with:

h->SetStats(1).

// The type of information about fit parameters printed in the histogram statistics
// box can be selected via the parameter mode. The parameter mode can be
// = pcev  (default = 0111)

//      p = 1;  print Probability
//      c = 1;  print Chisquare/Number of degrees of freedom
//      e = 1;  print errors (if e=1, v must be 1)
//      v = 1;  print name/values of parameters

gStyle->SetOptFit(1011);

// print fit probability, parameter names/values and errors.

//  1. When "v" = 1 is specified, only the non-fixed parameters are shown.
//  2. When "v" = 2 all parameters are shown.

// Note: gStyle->SetOptFit(1) means "default value", so it is equivalent
// to gStyle->SetOptFit(111)
```

## example




<!-- TPaveStats.md ends here -->
