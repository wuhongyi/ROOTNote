<!-- TGraphPolar.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:52:37 2014 (+0800)
;; Last-Updated: 六 8月 13 12:33:42 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.github.io -->

# TGraphPolar

## class



## code



## example

```cpp
TCanvas *CPol = new TCanvas("CPol","TGraphPolar Examples",700,700);
Double_t rmin=0;
Double_t rmax=TMath::Pi()*2;
Double_t r[1000];
Double_t theta[1000];
TF1 * fp1 = new TF1("fplot","cos(x)",rmin,rmax);
for (Int_t ipt = 0; ipt < 1000; ipt++) {
r[ipt] = ipt*(rmax-rmin)/1000+rmin;
theta[ipt] = fp1->Eval(r[ipt]);}
TGraphPolar * grP1 = new TGraphPolar(1000,r,theta);
grP1->SetLineColor(2);
grP1->Draw("AOL");
```


<!-- TGraphPolar.md ends here -->
