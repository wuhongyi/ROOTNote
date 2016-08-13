<!-- TH1.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 六 8月 13 11:16:28 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 8
;; URL: http://wuhongyi.github.io -->

# TH1

## class

```cpp
virtual Bool_t   Add(const TH1 *h, const TH1 *h2, Double_t c1=1, Double_t c2=1); // *MENU* 两个TH1相加

virtual void     Draw(Option_t *option="");//画图

virtual Int_t    Fill(Double_t x);//将数据填充进直方图
virtual Int_t    Fill(Double_t x, Double_t w);
virtual Int_t    Fill(const char *name, Double_t w);
virtual void     FillN(Int_t ntimes, const Double_t *x, const Double_t *w, Int_t stride=1);
virtual void     FillN(Int_t, const Double_t *, const Double_t *, const Double_t *, Int_t) {;}
virtual void     FillRandom(const char *fname, Int_t ntimes=5000);
virtual void     FillRandom(TH1 *h, Int_t ntimes=5000);
virtual Int_t    FindBin(Double_t x, Double_t y=0, Double_t z=0);

virtual void     Reset(Option_t *option="");//将其清除重置

virtual void     Scale(Double_t c1=1, Option_t *option="");//比例缩放

virtual Int_t    GetNbinsX() const {return fXaxis.GetNbins();}//获取轴bin值
virtual Int_t    GetNbinsY() const {return fYaxis.GetNbins();}
virtual Int_t    GetNbinsZ() const {return fZaxis.GetNbins();}


//ROOT 6
virtual Double_t *GetIntegral();//TH1积分，当前bin值为前面所有bin的累积，然后归一化（最大值为1），返回该数组

TH1             *GetCumulative(Bool_t forward = kTRUE, const char* suffix = "_cumulative") const;//TH1积分，当前bin值为前面所有bin的累积。
```


## code

```cpp
TH1F *h1=new TH1F("stats name","title name",number of bins,min,max);
TH1F *h1=new TH1F("stats name","title name;X axis;Y axis",number of bins,min,max);
 float x=gRandom->Uniform(-5.,5.);
 h1->Fill(x);                       //均匀分布
h1->FillRandom("gaus",50000);       //
h1->Draw();
```

```cpp
//循环创建图片
TH1D  h[16];
char Stringtemp[256];
for(int i=0;i<16;i++){ 
  sprintf(Stringtemp,"h[%d]",i);//这样创建数组名不好，直接 "h%d"这样好
  h[i]=new TH1D(Stringtemp,"",4096,0,4096);
} 
```


## example

```cpp

```

<!-- TH1.md ends here -->
