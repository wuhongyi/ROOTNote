<!-- TRandom2.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 8月 13 14:41:20 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.github.io -->

# TRandom2

## class

**继承 TRandom**

默认随机种子 1

TRandom2, is based on the Tausworthe generator of L'Ecuyer, and it has the advantage
of being fast and using only 3 words (of 32 bits) for the state. The period is 10**26.

```cpp
   virtual  Double_t Rndm(Int_t i=0);//Generate number in interval (0,1) : 0 and 1 are not included in the interval
   virtual  void     RndmArray(Int_t n, Float_t *array);
   virtual  void     RndmArray(Int_t n, Double_t *array);
   virtual  void     SetSeed(UInt_t seed=0);
```

<!-- TRandom2.md ends here -->
