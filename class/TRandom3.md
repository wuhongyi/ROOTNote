<!-- TRandom3.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 8月 13 14:35:16 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.github.io -->


# TRandom3

## class

**继承 TRandom**

默认随机种子 4357


```cpp
// get the current seed (only first element of the seed table)
virtual  UInt_t    GetSeed() const { return fMt[0];}
virtual  Double_t  Rndm(Int_t i=0);//（0，1]均匀分布
virtual  void      RndmArray(Int_t n, Float_t *array);
virtual  void      RndmArray(Int_t n, Double_t *array);
virtual  void      SetSeed(UInt_t seed=0);
```

## code

```cpp
#include "TRandom1.h"          TRandom3 r(111);
#include "TRandom2.h"          TRandom3 r(0);
#include "TRandom3.h"          TRandom3 r(0);
```


## example



<!-- TRandom3.md ends here -->
