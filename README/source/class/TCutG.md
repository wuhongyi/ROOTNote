<!-- TCutG.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:48:25 2014 (+0800)
;; Last-Updated: 三 9月 16 12:51:00 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 8
;; URL: http://wuhongyi.cn -->

# TCutG*

继承 TGraph

A Graphical cut.

A TCutG object is a closed polygon defining a closed region in a x,y plot.
It can be created via the graphics editor option "CutG" or directly by
invoking its constructor. The first and last points should be the same.

To create a TCutG via the graphics editor, use the left button to select the
points building the contour of the cut. Click on the right button to close the
TCutG. When it is created via the graphics editor, the TCutG object is named
"CUTG". It is recommended to immediately change the name by using the context
menu item "SetName". When the graphics editor is used, the names of the
variables X,Y are automatically taken from the current pad title.

A Graphical cut may be drawn via TGraph::Draw. It can be edited like a normal
TGraph.

A Graphical cut may be saved to a file via TCutG::Write.

## class

```cpp
   TCutG();/// TCutG default constructor.
   TCutG(const TCutG &cutg);/// TCutG copy constructor
   TCutG(const char *name, Int_t n);/// TCutG normal constructor.
   TCutG(const char *name, Int_t n, const Float_t *x, const Float_t *y);/// TCutG normal constructor.
   TCutG(const char *name, Int_t n, const Double_t *x, const Double_t *y);/// TCutG normal constructor.
   virtual ~TCutG();

   TCutG &operator=(const TCutG &);
   virtual Double_t Area() const;
/// Compute the area inside this TCutG
/// The algorithm uses Stoke's theorem over the border of the closed polygon.
/// Just as a reminder: Stoke's theorem reduces a surface integral
/// to a line integral over the border of the surface integral.

   virtual void     Center(Double_t &cx, Double_t &cy) const;
/// Compute the center x,y of this TCutG
/// The algorithm uses Stoke's theorem over the border of the closed polygon.
/// Just as a reminder: Stoke's theorem reduces a surface integral
/// to a line integral over the border of the surface integral.

   TObject         *GetObjectX() const {return fObjectX;}
   TObject         *GetObjectY() const {return fObjectY;}
   const char      *GetVarX() const {return fVarX.Data();}
   const char      *GetVarY() const {return fVarY.Data();}
   virtual Double_t IntegralHist(TH2 *h, Option_t *option="") const;
/// Compute the integral of 2-d histogram h for all bins inside the cut
/// if option "width" is specified, the integral is the sum of
/// the bin contents multiplied by the bin width in x and in y.

   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");/// Save primitive as a C++ statement(s) on output stream out.
   virtual void     SetObjectX(TObject *obj);/// Set the X object (and delete the previous one if any).
   virtual void     SetObjectY(TObject *obj);/// Set the Y object (and delete the previous one if any).
   virtual void     SetVarX(const char *varx); // *MENU* /// Set X variable.
   virtual void     SetVarY(const char *vary); // *MENU* /// Set Y variable.
```

## code

```cpp
// Assume a TTree object T and:

Root > T.Draw("abs(fMomemtum)%fEtot")

// the TCutG members fVarX, fVary will be set to:

fVarx = fEtot
fVary = abs(fMomemtum)

// A graphical cut can be used in a TTree selection expression:

Root > T.Draw("fEtot","cutg1")

// where "cutg1" is the name of an existing graphical cut.

// Note that, as shown in the example above, a graphical cut may be used in a
// selection expression when drawing TTrees expressions of 1-d, 2-d or
// 3-dimensions. The expressions used in TTree::Draw can reference the variables in
// the fVarX, fVarY of the graphical cut plus other variables.
```

```cpp
// When the TCutG object is created by TTree::Draw, it is added to the list of special objects in
// the main TROOT object pointed by gROOT. To retrieve a pointer to this object
// from the code or command line, do:

    TCutG *mycutg;
    mycutg = (TCutG*)gROOT->GetListOfSpecials()->FindObject("CUTG")
    mycutg->SetName("mycutg");

// When the TCutG is not created via TTree::Draw, one must set the variable names
// corresponding to x,y if one wants to use the cut as input to TTree::Draw,eg

    TCutG *cutg = new TCutG("mycut",5);
    cutg->SetVarX("y");
    cutg->SetVarY("x");
    cutg->SetPoint(0,-0.3586207,1.509534);
    cutg->SetPoint(1,-1.894181,-0.529661);
    cutg->SetPoint(2,0.07780173,-1.21822);
    cutg->SetPoint(3,-1.0375,-0.07944915);
    cutg->SetPoint(4,0.756681,0.1853814);
    cutg->SetPoint(5,-0.3586207,1.509534);

// Example of use of a TCutG in TTree::Draw:

    tree.Draw("x:y","mycutg && z>0 %% sqrt(x)>1")
```



## example

```cpp
//图像上数据筛选  曲线拟合
#include "TF2.h"
#include "TH2.h"
#include "TCutG.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
//+ Fitting a 2-D histogram (a variant)
// This tutorial illustrates :
//  - how to create a 2-d function
//  - fill a 2-d histogram randomly from this function
//  - fit the histogram
//  - display the fitted function on top of the histogram (lego-plot)
//    using a surface plot in a sub-range of the histogram.
//      图像上数据筛选  曲线拟合
Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}   
Double_t fun2(Double_t *x, Double_t *par) {
   Double_t *p1 = &par[0];
   Double_t *p2 = &par[5];
   Double_t *p3 = &par[10];
   Double_t result = g2(x,p1) + g2(x,p2) + g2(x,p3);
   return result;
}

TCanvas *fit2a() {
   TCanvas *c = new TCanvas();
   gStyle->SetOptStat(kTRUE); 
   gStyle->SetPalette(1); 
   const Int_t npar = 15;
   Double_t f2params[npar] = {100,-3,3,-3,3,160,0,0.8,0,0.9,40,4,0.7,4,0.7};
   TF2 *f2 = new TF2("f2",fun2,-10,10,-10,10, npar);
   f2->SetParameters(f2params);

   //Create an histogram and fill it randomly with f2
   TH2F *h2 = new TH2F("h2","From f2",40,-10,10,40,-10,10);
   Int_t nentries = 100000;
   h2->FillRandom("f2",nentries);
   //Fit h2 with original function f2
   Float_t ratio = 4*nentries/100000;
   f2params[ 0] *= ratio;
   f2params[ 5] *= ratio;
   f2params[10] *= ratio;
   f2->SetParameters(f2params);
   h2->Fit("f2","N");
   TCutG *cutg = new TCutG("cutg",5);//设置数据区域
   cutg->SetPoint(0,-7,-7);
   cutg->SetPoint(1, 2,-7);
   cutg->SetPoint(2, 2, 2);
   cutg->SetPoint(3,-7, 2);
   cutg->SetPoint(4,-7,-7);
   h2->Draw("lego2 0");
   h2->SetFillColor(38);
   f2->SetNpx(80);
   f2->SetNpy(80);
   f2->Draw("surf1 same bb [cutg]");
   return c;
}
```


```cpp
// 图像上数据筛选
void fit2d()
{
   //example illustrating how to fit a 2-d histogram of type y=f(x)
   // generate a 2-d histogram using a TCutG 图像上数据筛选
   const Int_t n = 6;
   Float_t x[n] = {0.092,0.83,0.94,0.81,0.12,0.1};
   Float_t y[n] = {0.71,9.4,9,8,0.3,0.71};
   TCutG *cut = new TCutG("cut",n,x,y);//设置数据区域
   TH2F *h2 = new TH2F("h2","h2",40,0,1,40,0,10);
   Float_t u,v;
   for (Int_t i=0;i<100000;i++) {
      u = gRandom->Rndm();
      v = 10*gRandom->Rndm();
      if (cut->IsInside(u,v)) h2->Fill(u,v);//筛选数据
   }
   TCanvas *c1 = new TCanvas("c1","show profile",600,900);
   c1->Divide(1,2);
   c1->cd(1);
   h2->Draw();
   c1->cd(2);
   
   //use a TProfile to convert the 2-d to 1-d problem
   TProfile *prof = h2->ProfileX();
   prof->Fit("pol1");
}
```


```cpp
// make a contour plot and get the first contour in a TPolyMarker
void FirstContour()
{
   //this macro generates a color contour plot by selecting entries from an ntuple file.
   //The TGraph object corresponding to the first contour line is accessed and displayed into a separate canvas.
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("FirstContour.C","../hsimple.C");
   dir.ReplaceAll("/./","/");
   if (!gInterpreter->IsLoaded(dir.Data())) gInterpreter->LoadMacro(dir.Data());
   TFile *file = (TFile*)gROOT->ProcessLineFast("hsimple(1)");
   if (!file) return;
   TTree *ntuple = (TTree*)file->Get("ntuple");
   
   TCanvas *c1 = new TCanvas("c1","Contours",10,10,800,600);
   gStyle->SetPalette(1);
   ntuple->Draw("py:px","px*px+py*py < 20", "contz,list");
   
   //we must call Update to force the canvas to be painted.  When 
   //painting the contour plot, the list of contours is generated
   //and a reference to it added to the Root list of special objects
   c1->Update();
      
   TCanvas *c2 = new TCanvas("c2","First contour",100,100,800,600);
   
   
   TObjArray *contours = 
      (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
   if (!contours) return;
   TList *lcontour1 = (TList*)contours->At(0);
   if (!lcontour1) return;
   TGraph *gc1 = (TGraph*)lcontour1->First();
   if (!gc1) return;
   if (gc1->GetN() < 10) return;
   gc1->SetMarkerStyle(21);
   gc1->Draw("alp");
   
   //We make a TCutG object with the array obtained from this graph
   TCutG *cutg = new TCutG("cutg",gc1->GetN(),gc1->GetX(),gc1->GetY());
   
   //We create a polymarker object with npmax points.
   const Int_t npmax = 50000;
   TPolyMarker *pm = new TPolyMarker(npmax);
   Int_t np = 0;
   while(1) {
      Double_t x = -4 +8*gRandom->Rndm();
      Double_t y = -4 +8*gRandom->Rndm();
      if (cutg->IsInside(x,y)) {
         pm->SetPoint(np,x,y);
         np++;
         if (np == npmax) break;
      }
   }
   pm->Draw();
}
```

<!-- TCutG.md ends here -->
