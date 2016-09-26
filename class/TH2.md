<!-- TH2.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 二 9月 13 16:50:16 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 9
;; URL: http://wuhongyi.github.io -->

# TH2

继承 TH1


## class

```cpp
   virtual ~TH2();
   virtual Int_t    BufferEmpty(Int_t action=0);
   virtual void     Copy(TObject &hnew) const;
   virtual Int_t    Fill(Double_t x, Double_t y);
   virtual Int_t    Fill(Double_t x, Double_t y, Double_t w);
   virtual Int_t    Fill(Double_t x, const char *namey, Double_t w);
   virtual Int_t    Fill(const char *namex, Double_t y, Double_t w);
   virtual Int_t    Fill(const char *namex, const char *namey, Double_t w);
   virtual void     FillN(Int_t, const Double_t *, const Double_t *, Int_t) {;} //MayNotUse
   virtual void     FillN(Int_t ntimes, const Double_t *x, const Double_t *y, const Double_t *w, Int_t stride=1);
   virtual void     FillRandom(const char *fname, Int_t ntimes=5000);
   virtual void     FillRandom(TH1 *h, Int_t ntimes=5000);
   virtual Int_t    FindFirstBinAbove(Double_t threshold=0, Int_t axis=1) const;
   virtual Int_t    FindLastBinAbove (Double_t threshold=0, Int_t axis=1) const;
   virtual void     FitSlicesX(TF1 *f1=0,Int_t firstybin=0, Int_t lastybin=-1, Int_t cut=0, Option_t *option="QNR", TObjArray* arr = 0); // *MENU*
   virtual void     FitSlicesY(TF1 *f1=0,Int_t firstxbin=0, Int_t lastxbin=-1, Int_t cut=0, Option_t *option="QNR", TObjArray* arr = 0); // *MENU*
   virtual Int_t    GetBin(Int_t binx, Int_t biny, Int_t binz = 0) const;
   virtual Double_t GetBinWithContent2(Double_t c, Int_t &binx, Int_t &biny, Int_t firstxbin=1, Int_t lastxbin=-1,Int_t firstybin=1, Int_t lastybin=-1, Double_t maxdiff=0) const;
   virtual Double_t GetBinContent(Int_t bin) const { return TH1::GetBinContent(bin); }
   virtual Double_t GetBinContent(Int_t binx, Int_t biny) const { return TH1::GetBinContent( GetBin(binx, biny) ); }
   virtual Double_t GetBinContent(Int_t binx, Int_t biny, Int_t) const { return TH1::GetBinContent( GetBin(binx, biny) ); }
   using TH1::GetBinErrorLow;
   using TH1::GetBinErrorUp;
   virtual Double_t GetBinErrorLow(Int_t binx, Int_t biny) { return TH1::GetBinErrorLow( GetBin(binx, biny) ); }
   virtual Double_t GetBinErrorUp(Int_t binx, Int_t biny) { return TH1::GetBinErrorUp( GetBin(binx, biny) ); }
   virtual Double_t GetCorrelationFactor(Int_t axis1=1,Int_t axis2=2) const;
   virtual Double_t GetCovariance(Int_t axis1=1,Int_t axis2=2) const;
   virtual void     GetRandom2(Double_t &x, Double_t &y);//返回满足二维分布的x,y随机数
   virtual void     GetStats(Double_t *stats) const;
   virtual Double_t Integral(Option_t *option="") const;
   //virtual Double_t Integral(Int_t, Int_t, Option_t * ="") const {return 0;}
   using TH1::Integral;
   virtual Double_t Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t *option="") const;
   virtual Double_t Integral(Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Option_t * ="") const {return 0;}
   using TH1::IntegralAndError;
   virtual Double_t IntegralAndError(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Double_t & err, Option_t *option="") const;
   virtual Double_t Interpolate(Double_t x);
   virtual Double_t Interpolate(Double_t x, Double_t y);
   virtual Double_t Interpolate(Double_t x, Double_t y, Double_t z);
   virtual Double_t KolmogorovTest(const TH1 *h2, Option_t *option="") const;
   virtual Long64_t Merge(TCollection *list);
   virtual TH2     *RebinX(Int_t ngroup=2, const char *newname="");//合bin，几个合成一个
   virtual TH2     *RebinY(Int_t ngroup=2, const char *newname="");//合bin，几个合成一个
   virtual TH2     *Rebin2D(Int_t nxgroup=2, Int_t nygroup=2, const char *newname="");//合bin，几个合成一个
      TProfile     *ProfileX(const char *name="_pfx", Int_t firstybin=1, Int_t lastybin=-1, Option_t *option="") const;   // *MENU*
      TProfile     *ProfileY(const char *name="_pfy", Int_t firstxbin=1, Int_t lastxbin=-1, Option_t *option="") const;   // *MENU*
         TH1D      *ProjectionX(const char *name="_px", Int_t firstybin=0, Int_t lastybin=-1, Option_t *option="") const; // *MENU*
         TH1D      *ProjectionY(const char *name="_py", Int_t firstxbin=0, Int_t lastxbin=-1, Option_t *option="") const; // *MENU*
   virtual void     PutStats(Double_t *stats);
   TH1D            *QuantilesX(Double_t prob = 0.5, const char * name = "_qx" ) const;
   TH1D            *QuantilesY(Double_t prob = 0.5, const char * name = "_qy" ) const;
   virtual void     Reset(Option_t *option="");
   virtual void     SetBinContent(Int_t bin, Double_t content);
   virtual void     SetBinContent(Int_t binx, Int_t biny, Double_t content) { SetBinContent(GetBin(binx, biny), content); }
   virtual void     SetBinContent(Int_t binx, Int_t biny, Int_t, Double_t content) { SetBinContent(GetBin(binx, biny), content); }
   virtual void     SetShowProjectionX(Int_t nbins=1);  // *MENU*
   virtual void     SetShowProjectionY(Int_t nbins=1);  // *MENU*
   virtual TH1     *ShowBackground(Int_t niter=20, Option_t *option="same");
   virtual Int_t    ShowPeaks(Double_t sigma=2, Option_t *option="", Double_t threshold=0.05); // *MENU*
   virtual void     Smooth(Int_t ntimes=1, Option_t *option=""); // *MENU*
```

## code

```cpp
TH2* h = new TH2D(/* name */ "h2",/* title */ "Hist with constant bin width",/* X-dimension */ 100, 0.0, 4.0,/* Y-dimension */ 200, -3.0, 1.5);
```


```cpp
const Int_t XBINS = 5; const Int_t YBINS = 5;
Double_t xEdges[XBINS + 1] = {0.0, 0.2, 0.3, 0.6, 0.8, 1.0};
Double_t yEdges[YBINS + 1] = {-1.0, -0.4, -0.2, 0.5, 0.7, 1.0};
TH2* h = new TH2D("h2", "h2", XBINS, xEdges, YBINS, yEdges);
TAxis* xAxis = h->GetXaxis(); TAxis* yAxis = h->GetYaxis();
cout << "Third bin on Y-dimension: " << endl; // corresponds to [-0.2, 0.5]
cout << "\tLower edge: " << yAxis->GetBinLowEdge(3) << endl;
cout << "\tCenter: " << yAxis->GetBinCenter(3) << endl;
cout << "\tUpper edge: " << yAxis->GetBinUpEdge(3) << endl;
```


## example

```cpp
//直方图的bin标签设置

const Int_t nx = 12;
const Int_t ny = 20;
char *month[nx]  = {"January","February","March","April","May","June","July","August","September","October","November","December"};
char *people[ny] = {"Jean","Pierre","Marie","Odile","Sebastien","Fons","Rene","Nicolas","Xavier","Greg","Bjarne","Anton","Otto","Eddy","Peter","Pasha","Philippe","Suzanne","Jeff","Valery"};
TCanvas *c1 = new TCanvas("c1","demo bin labels",10,10,800,800);
c1->SetGrid();
c1->SetLeftMargin(0.15);
c1->SetBottomMargin(0.15);
TH2F *h = new TH2F("h","test",nx,0,nx,ny,0,ny);
for (Int_t i=0;i<5000;i++) {
  h->Fill(gRandom->Gaus(0.5*nx,0.2*nx), gRandom->Gaus(0.5*ny,0.2*ny));
 }
h->SetStats(0);
for (i=1;i<=nx;i++) h->GetXaxis()->SetBinLabel(i,month[i-1]);//直方图每个bin设置标签名字。
for (i=1;i<=ny;i++) h->GetYaxis()->SetBinLabel(i,people[i-1]);//一维二维一样的添加方式。
h->Draw("text");
```


<!-- TH2.md ends here -->
