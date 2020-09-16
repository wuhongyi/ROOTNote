<!-- TLatex.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 16:52:31 2016 (+0800)
;; Last-Updated: 三 9月 16 12:49:00 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TLatex*

继承 TText, TAttLine

To draw Mathematical Formula.

TLatex's purpose is to write mathematical equations. The syntax is very similar
to the Latex's one. 

When the font precision (see TAttText) is low (0 or 1), TLatex is
painted as a normal TText, the control characters are not interpreted.


Subscripts and superscripts are made with the `_` and `^`
commands. These commands can be combined to make complicated subscript and
superscript expressions. You may adjust the display of subscripts and
superscripts by using the two functions SetIndiceSize(Double_t),
which set relative size of subscripts and superscripts, and
SetLimitIndiceSize(Int_t), which set limits for text resizing of
subscripts and superscripts.

```
TLatex can display dozens of special mathematical symbols. A few of them, such
as + and > , are produced by typing the corresponding
keyboard character.

TLatex provides 4 kinds of proportional delimiters:

    #[]{....} or "a la" Latex #left[.....#right] : big square brackets
    #{}{....} or              #left{.....#right} : big curly brackets
    #||{....} or              #left|.....#right| : big absolute value symbols
    #(){....} or              #left(.....#right) : big parentheses


The command to produce a lowercase Greek letter is obtained by adding a
# to the name of the letter. For an uppercase Greek letter, just
capitalize the first letter of the command name. Some letters have two
representations. The name of the second one (the "variation") starts with "var".

Several kind of accents are available:

   #hat    = Begin_Latex #hat{a} End_Latex
   #check  = Begin_Latex #check{a} End_Latex
   #acute  = Begin_Latex #acute{a} End_Latex
   #grave  = Begin_Latex #grave{a} End_Latex
   #dot    = Begin_Latex #dot{a} End_Latex
   #ddot   = Begin_Latex #ddot{a} End_Latex
   #tilde  = Begin_Latex #tilde{a} End_Latex
```


The class TMathText is a TeX math formulae interpreter. It uses plain
TeX syntax and uses "\" as control instead of "#". If a piece of text containing
"\" is given to TLatex then TMathText is automatically invoked.
Therefore, as histograms' titles, axis titles, labels etc ... are drawn using
TLatex, the TMathText syntax can be used for them also.




## class

```cpp
      TLatex();
      TLatex(Double_t x, Double_t y, const char *text);
      TLatex(const TLatex &text);
      virtual ~TLatex();
      void             Copy(TObject &text) const;

      TLatex          *DrawLatex(Double_t x, Double_t y, const char *text);
/// Make a copy of this object with the new parameters
/// And copy object attributes

      TLatex          *DrawLatexNDC(Double_t x, Double_t y, const char *text);/// Draw this TLatex with new coordinates in NDC.

      Double_t         GetHeight() const;/// Return height of current pad in pixels
      Double_t         GetXsize();/// Return size of the formula along X in pad coordinates
      Double_t         GetYsize();/// Return size of the formula along Y in pad coordinates
      void             GetBoundingBox(UInt_t &w, UInt_t &h, Bool_t angle = kFALSE);/// Return text size in pixels
      virtual void     Paint(Option_t *option="");/// Paint.
      virtual void     PaintLatex(Double_t x, Double_t y, Double_t angle, Double_t size, const char *text);
/// Main drawing function
/// Warning: Unlike most others "XYZ::PaintXYZ" methods, PaintLatex modifies
///          the TLatex data members.

      virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");/// Save primitive as a C++ statement(s) on output stream out
      virtual void     SetIndiceSize(Double_t factorSize);/// Set relative size of subscripts and superscripts
      virtual void     SetLimitIndiceSize(Int_t limitFactorSize);/// Set limit for text resizing of subscripts and superscripts
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
// The best way to put the subscripts and superscripts before the character and not
// after, is to use an empty character:
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
// The #sqrt command produces the square root of its argument; it has
// an optional first argument for other roots.

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

```cpp
// Text can be split in two lines via the command #splitline.

   TCanvas *cl = new TCanvas("cl","cl",10,10,700,100);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Tl.DrawText(.1, .5,   "#splitline{21 April 2003}{14:02:30} :"); Tl.DrawLatex(.6, .5, "#splitline{21 April 2003}{14:02:30}");
```

```cpp
// The special sign: #slash draws a slash on top of the text between brackets:

   TCanvas *cl = new TCanvas("cl","cl",10,10,700,100);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Tl.DrawText(.1, .5,   "#slash{E}_{T} :"); Tl.DrawLatex(.5, .5, "#slash{E}_{T}");
```

```cpp
// Bar and vectors sign are done the following way:

   TCanvas *cl = new TCanvas("cl","cl",10,10,700,100);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Tl.DrawText(.1, .5,   "#bar{a} and #vec{a} :"); Tl.DrawLatex(.5, .5, "#bar{a} and #vec{a}");
```

```cpp
// One can change the font, the text color, or the text size at any time using :
// #font[font-number]{...}, #color[color-number]{...}
// and #scale[scale-factor]{...}

   TCanvas *cl = new TCanvas("cl","cl",10,10,900,300);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Double_t dy = 1./4.;
   Tl.DrawText(.01, dy,   "#font[12]{Times Italic} and #font[22]{Times bold} :");    Tl.DrawLatex(.7, dy,   "#font[12]{Times Italic} and #font[22]{Times bold}");
   Tl.DrawText(.01, 2*dy, "#color[2]{Red} and #color[4]{Blue} :");    Tl.DrawLatex(.7, 2*dy, "#color[2]{Red} and #color[4]{Blue}");
   Tl.DrawText(.01, 3*dy, "#scale[1.2]{Bigger} and #scale[0.8]{Smaller} :"); Tl.DrawLatex(.7, 3*dy, "#scale[1.2]{Bigger} and #scale[0.8]{Smaller}");
```

```cpp
// The two commands #kern and #lower enable a better control
// over character placement. The command #kern[(Float_t)dx]{text} moves
// the output string horizontally by the fraction dx of its length.
// Similarly, #lower[(Float_t)dy]{text} shifts the text up or down by
// the fraction dy of its height.

   TCanvas *cl = new TCanvas("cl","cl",10,10,900,300);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   TLatex Tt; Tt.SetTextFont(43); Tt.SetTextSize(12);
   Double_t dy = 1./7.;
   Tl.DrawLatex(.5,   dy, "Positive k#kern[0.3]{e}#kern[0.3]{r}#kern[0.3]{n}#kern[0.3]{i}#kern[0.3]{n}#kern[0.3]{g}");
   Tt.DrawText(.01, 2*dy, "Positive k#kern[0.3]{e}#kern[0.3]{r}#kern[0.3]{n}#kern[0.3]{i}#kern[0.3]{n}#kern[0.3]{g} :");
   Tl.DrawLatex(.5, 3*dy, "Negative k#kern[-0.3]{e}#kern[-0.3]{r}#kern[-0.3]{n}#kern[-0.3]{i}#kern[-0.3]{n}#kern[-0.3]{g}");
   Tt.DrawText(.01, 4*dy, "Negative k#kern[-0.3]{e}#kern[-0.3]{r}#kern[-0.3]{n}#kern[-0.3]{i}#kern[-0.3]{n}#kern[-0.3]{g} :");
   Tl.DrawLatex(.5, 5*dy, "Vertical a#lower[0.2]{d}#lower[0.4]{j}#lower[0.1]{u}#lower[-0.1]{s}#lower[-0.3]{t}#lower[-0.4]{m}#lower[-0.2]{e}#lower[0.1]{n}t");
   Tt.DrawText(.01, 6*dy, "Vertical a#lower[0.2]{d}#lower[0.4]{j}#lower[0.1]{u}#lower[-0.1]{s}#lower[-0.3]{t}#lower[-0.4]{m}#lower[-0.2]{e}#lower[0.1]{n}t :");
```

```cpp
// Text can be turned italic or boldface using the commands #it and #bf.

   TCanvas *cl = new TCanvas("cl","cl",10,10,900,300);
   TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(20);
   Double_t dy = 1./3.;
   Tl.DrawText(.01, dy,   "abc#alpha#beta#gamma, #it{abc#alpha#beta#gamma} :");    Tl.DrawLatex(.7, dy,   "abc#alpha#beta#gamma, #it{abc#alpha#beta#gamma}");
   Tl.DrawText(.01, 2*dy, "#bf{bold}, #it{italic}, #bf{#it{bold italic}}, #bf{#bf{unbold}}} :");    Tl.DrawLatex(.7, 2*dy, "#bf{bold}, #it{italic}, #bf{#it{bold italic}}, #bf{#bf{unbold}}}");
```


## example

```cpp
// The TText alignment rules apply to the TLatex objects with one exception
// concerning the vertical alignment:

// - if the vertical alignment = 1 , subscripts are not taken into account
// - if the vertical alignment = 0 , the text is aligned to the box surrounding
                                     the full text with sub and superscripts
// This is illustrated by the following example:

   TCanvas Tlva("Tlva","Tlva",500,500);
   Tlva.SetGrid();
   Tlva.DrawFrame(0,0,1,1);
   const char *longstring = "K_{S}... K^{*0}... #frac{2s}{#pi#alpha^{2}} #frac{d#sigma}{dcos#theta} (e^{+}e^{-} #rightarrow f#bar{f} ) = #left| #frac{1}{1 - #Delta#alpha} #right|^{2} (1+cos^{2}#theta)";

   TLatex latex;
   latex.SetTextSize(0.025);
   latex.SetTextAlign(13);  //align at top
   latex.DrawLatex(.2,.9,"K_{S}");
   latex.DrawLatex(.3,.9,"K^{*0}");
   latex.DrawLatex(.2,.8,longstring);

   latex.SetTextAlign(12);  //centered
   latex.DrawLatex(.2,.6,"K_{S}");
   latex.DrawLatex(.3,.6,"K^{*0}");
   latex.DrawLatex(.2,.5,longstring);

   latex.SetTextAlign(11);  //default bottom alignment
   latex.DrawLatex(.2,.4,"K_{S}");
   latex.DrawLatex(.3,.4,"K^{*0}");
   latex.DrawLatex(.2,.3,longstring);

   latex.SetTextAlign(10);  //special bottom alignment
   latex.DrawLatex(.2,.2,"K_{S}");
   latex.DrawLatex(.3,.2,"K^{*0}");
   latex.DrawLatex(.2,.1,longstring);

   latex.SetTextAlign(12);
   latex.SetTextFont(72);
   latex.DrawLatex(.1,.80,"13");
   latex.DrawLatex(.1,.55,"12");
   latex.DrawLatex(.1,.35,"11");
   latex.DrawLatex(.1,.18,"10");
   return Tlva;
```


```cpp
   TCanvas ex1("ex1","Latex",500,600);
   TLatex Tl;
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.8,"1)   C(x) = d #sqrt{#frac{2}{#lambdaD}}  #int^{x}_{0}cos(#frac{#pi}{2}t^{2})dt");
   Tl.DrawLatex(0.1,0.6,"2)   C(x) = d #sqrt{#frac{2}{#lambdaD}}  #int^{x}cos(#frac{#pi}{2}t^{2})dt");
   Tl.DrawLatex(0.1,0.4,"3)   R = |A|^{2} = #frac{1}{2}(#[]{#frac{1}{2}+C(V)}^{2}+#[]{#frac{1}{2}+S(V)}^{2})");
   Tl.DrawLatex(0.1,0.2,"4)   F(t) = #sum_{i=-#infty}^{#infty}A(i)cos#[]{#frac{i}{t+i}}");
   return ex1;
```


```cpp
   TCanvas ex2("ex2","Latex",500,300);
   TLatex Tl;
   Tl.SetTextAlign(23);
   Tl.SetTextSize(0.08);
   Tl.DrawLatex(0.5,0.95,"e^{+}e^{-}#rightarrowZ^{0}#rightarrowI#bar{I}, q#bar{q}");
   Tl.DrawLatex(0.5,0.75,"|#vec{a}#bullet#vec{b}|=#Sigmaa^{i}_{jk}+b^{bj}_{i}");
   Tl.DrawLatex(0.5,0.5,"i(#partial_{#mu}#bar{#psi}#gamma^{#mu}+m#bar{#psi}=0#Leftrightarrow(#Box+m^{2})#psi=0");
   Tl.DrawLatex(0.5,0.3,"L_{em}=eJ^{#mu}_{em}A_{#mu} , J^{#mu}_{em}=#bar{I}#gamma_{#mu}I , M^{j}_{i}=#SigmaA_{#alpha}#tau^{#alphaj}_{i}");
   return ex2;
```


```cpp
   TCanvas ex3("ex3","Latex",500,300);
   TPaveText pt(.1,.1,.9,.9);
   pt.AddText("#frac{2s}{#pi#alpha^{2}}  #frac{d#sigma}{dcos#theta} (e^{+}e^{-} #rightarrow f#bar{f} ) = ");
   pt.AddText("#left| #frac{1}{1 - #Delta#alpha} #right|^{2} (1+cos^{2}#theta");
   pt.AddText("+ 4 Re #left{ #frac{2}{1 - #Delta#alpha} #chi(s) #[]{#hat{g}_{#nu}^{e}#hat{g}_{#nu}^{f} (1 + cos^{2}#theta) + 2 #hat{g}_{a}^{e}#hat{g}_{a}^{f} cos#theta) } #right}");
   pt.SetLabel("Born equation");
   pt.Draw();
   return ex3;
```


<!-- TLatex.md ends here -->
