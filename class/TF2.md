<!-- TF2.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:52:37 2014 (+0800)
;; Last-Updated: 六 8月 13 12:37:44 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TF2

## class


## code


## example

```cpp
//由 TF2 函数填充 TH2
gROOT->Reset();
gStyle->SetOptStat(0);
gStyle->SetPalette(1);
gStyle->SetCanvasColor(33);
gStyle->SetFrameFillColor(18);
TF2 *f2 = new TF2("f2","xygaus + xygaus(5) + xylandau(10)",-4,4,-4,4);
Double_t params[] = {130,-1.4,1.8,1.5,1, 150,2,0.5,-2,0.5, 3600,-2,0.7,-3,0.3};
f2->SetParameters(params);
TH2F h2("h2","xygaus + xygaus(5) + xylandau(10)",20,-4,4,20,-4,4);
h2.SetFillColor(46);
h2.FillRandom("f2",40000);
```

<!-- TF2.md ends here -->
