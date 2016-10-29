<!-- TLatex.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 16:52:31 2016 (+0800)
;; Last-Updated: 二 9月 13 17:51:30 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TLatex

继承 TText, TAttLine


## class

```cpp
      TLatex();
      TLatex(Double_t x, Double_t y, const char *text);
      TLatex(const TLatex &text);
      virtual ~TLatex();
      void             Copy(TObject &text) const;

      TLatex          *DrawLatex(Double_t x, Double_t y, const char *text);
      TLatex          *DrawLatexNDC(Double_t x, Double_t y, const char *text);

      Double_t         GetHeight() const;
      Double_t         GetXsize();
      Double_t         GetYsize();
      void             GetBoundingBox(UInt_t &w, UInt_t &h, Bool_t angle = kFALSE);
      virtual void     Paint(Option_t *option="");
      virtual void     PaintLatex(Double_t x, Double_t y, Double_t angle, Double_t size, const char *text);

      virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
      virtual void     SetIndiceSize(Double_t factorSize);
      virtual void     SetLimitIndiceSize(Int_t limitFactorSize);
```


## code

```cpp
   TCanvas *cl = new TCanvas("cl","cl",10,10,700,500);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Double_t dy = 1./7.;
   Tl.DrawText(.1, dy,   "x^{2y} :");    Tl.DrawLatex(.5, dy,   "x^{2y}");
   Tl.DrawText(.1, 2*dy, "x_{2y} :");    Tl.DrawLatex(.5, 2*dy, "x_{2y}");
   Tl.DrawText(.1, 3*dy, "x^{y^{2}} :"); Tl.DrawLatex(.5, 3*dy, "x^{y^{2}}");
   Tl.DrawText(.1, 4*dy, "x^{y_{1}} :"); Tl.DrawLatex(.5, 4*dy, "x^{y_{1}}");
   Tl.DrawText(.1, 5*dy, "x^{y}_{1} :"); Tl.DrawLatex(.5, 5*dy, "x^{y}_{1}");
   Tl.DrawText(.1, 6*dy, "x_{1}^{y} :"); Tl.DrawLatex(.5, 6*dy, "x_{1}^{y}");
```


上下角标
```cpp
   TCanvas *cl = new TCanvas("cl","cl",10,10,700,100);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Tl.DrawText(.1, .5,   "{}^{40}_{20}Ca :"); Tl.DrawLatex(.5, .5, "{}^{40}_{20}Ca");
```

```cpp
   TCanvas *cl = new TCanvas("cl","cl",10,10,700,100);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Tl.DrawText(.1, .5,   "x = #frac{y+z/2}{y^{2}+1} :"); Tl.DrawLatex(.5, .5, "x = #frac{y+z/2}{y^{2}+1}");
```   


```cpp
   TCanvas *cl = new TCanvas("cl","cl",10,10,700,100);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Tl.DrawText(.1, .5,   "#sqrt{10} #sqrt[3]{10} :"); Tl.DrawLatex(.5, .5, "#sqrt{10} #sqrt[3]{10}");
```

```cpp
// One can change the font, the text color, or the text size at any time using :  #font[font-number]{...}, #color[color-number]{...} and #scale[scale-factor]{...}
   TCanvas *cl = new TCanvas("cl","cl",10,10,900,300);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Double_t dy = 1./4.;
   Tl.DrawText(.01, dy,   "#font[12]{Times Italic} and #font[22]{Times bold} :");    Tl.DrawLatex(.7, dy,   "#font[12]{Times Italic} and #font[22]{Times bold}");
   Tl.DrawText(.01, 2*dy, "#color[2]{Red} and #color[4]{Blue} :");    Tl.DrawLatex(.7, 2*dy, "#color[2]{Red} and #color[4]{Blue}");
   Tl.DrawText(.01, 3*dy, "#scale[1.2]{Bigger} and #scale[0.8]{Smaller} :"); Tl.DrawLatex(.7, 3*dy, "#scale[1.2]{Bigger} and #scale[0.8]{Smaller}");
```


## example






<!-- TLatex.md ends here -->
