<!-- TMultiGraph.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:52:37 2014 (+0800)
;; Last-Updated: 六 8月 13 12:35:54 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.github.io -->

# TMultiGraph

## class


## code


## example

```cpp
//Draw three graphs with an exclusion zone.一个画板上画出多个Graph。
   
TCanvas *c1 = new TCanvas("c1","Exclusion graphs examples",200,10,600,400);
c1->SetGrid();

TMultiGraph *mg = new TMultiGraph();
mg->SetTitle("Exclusion graphs");

const Int_t n = 35;
Double_t x1[n], x2[n], x3[n], y1[n], y2[n], y3[n];
for (Int_t i=0;i<n;i++) {
  x1[i]  = i*0.1;
  x2[i]  = x1[i];
  x3[i]  = x1[i]+.5;
  y1[i] = 10*sin(x1[i]);
  y2[i] = 10*cos(x1[i]);
  y3[i] = 10*sin(x1[i])-2;
 }

TGraph *gr1 = new TGraph(n,x1,y1);
gr1->SetLineColor(2);
gr1->SetLineWidth(1504);
gr1->SetFillStyle(3005);

TGraph *gr2 = new TGraph(n,x2,y2);
gr2->SetLineColor(4);
gr2->SetLineWidth(-2002);
gr2->SetFillStyle(3004);
gr2->SetFillColor(9);

TGraph *gr3 = new TGraph(n,x3,y3);
gr3->SetLineColor(5);
gr3->SetLineWidth(-802);
gr3->SetFillStyle(3002);
gr3->SetFillColor(2);

mg->Add(gr1);
mg->Add(gr2);
mg->Add(gr3);
mg->Draw("AC");
```


<!-- TMultiGraph.md ends here -->
