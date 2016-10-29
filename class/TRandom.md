<!-- TRandom.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 8月 13 14:24:43 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 8
;; URL: http://wuhongyi.cn -->

# TRandom

## class

**继承 TNamed**

默认随机种子 65539

Simple Random number generator (periodicity = 10**9)

```cpp
virtual  Int_t    Binomial(Int_t ntot, Double_t prob);//二项分布
virtual  Double_t BreitWigner(Double_t mean=0, Double_t gamma=1);//Brei-Wigner分布
virtual  void     Circle(Double_t &x, Double_t &y, Double_t r);
virtual  Double_t Exp(Double_t tau);//指数分布
virtual  Double_t Gaus(Double_t mean=0, Double_t sigma=1);//高斯分布
virtual  UInt_t   GetSeed() const {return fSeed;}//获得随机种子
virtual  UInt_t   Integer(UInt_t imax);//（0，imax-1）随机整数
virtual  Double_t Landau(Double_t mean=0, Double_t sigma=1);//Landau分布
virtual  Int_t    Poisson(Double_t mean);//泊松分布（返回int）
virtual  Double_t PoissonD(Double_t mean);//泊松分布（返回double）
virtual  void     Rannor(Float_t &a, Float_t &b);//Return 2 numbers distributed following a gaussian with mean=0 and sigma=1.
virtual  void     Rannor(Double_t &a, Double_t &b);//Return 2 numbers distributed following a gaussian with mean=0 and sigma=1.
virtual  void     ReadRandom(const char *filename);//从root文件中读取随机数产生器
virtual  void     SetSeed(UInt_t seed=0);//设置随机种子
virtual  Double_t Rndm(Int_t i=0);//（0，1]均匀分布
virtual  void     RndmArray(Int_t n, Float_t *array);
virtual  void     RndmArray(Int_t n, Double_t *array);
virtual  void     Sphere(Double_t &x, Double_t &y, Double_t &z, Double_t r);//获得各向同性的抽样
virtual  Double_t Uniform(Double_t x1=1);
virtual  Double_t Uniform(Double_t x1, Double_t x2);//（x1，x2]均匀分布
virtual  void     WriteRandom(const char *filename);//将该随机数产生器存为root文件 Writes random generator status to filename.
```

## code

```cpp
#include "TRandom.h"
TRandom r;
r.Rndm();
r.Gaus();
r.Gaus(10,3);
```

```cpp
// A TRandom object may be written to a Root file : as part of another object or with its own key 
gRandom->Write("Random");
```


## example

```cpp

```


<!-- TRandom.md ends here -->
