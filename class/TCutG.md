<!-- TCutG.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:48:25 2014 (+0800)
;; Last-Updated: 五 8月 12 22:30:42 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 6
;; URL: http://wuhongyi.cn -->

# TCutG

## class

<!-- ```cpp -->

<!-- ``` -->

## code

<!-- ```cpp -->

<!-- ``` -->


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
