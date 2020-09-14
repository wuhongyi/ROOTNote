<!-- TRandom2.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 5月  6 16:18:37 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->

# TRandom2

**继承 TRandom**

## class

默认随机种子 1

TRandom2, is based on the Tausworthe generator of L'Ecuyer, and it has the advantage
of being fast and using only 3 words (of 32 bits) for the state. The period is 10**26.

```cpp
   virtual  Double_t Rndm(Int_t i=0);//Generate number in interval (0,1) : 0 and 1 are not included in the interval
///  TausWorth generator from L'Ecuyer, uses as seed 3x32bits integers
///  Use a mask of 0xffffffffUL to make in work on 64 bit machines
///  Periodicity of about  10**26
///  Generate number in interval (0,1)  : 0 and 1 are not included in the interval

   virtual  void     RndmArray(Int_t n, Float_t *array);/// Return an array of n random numbers uniformly distributed in ]0,1]
   virtual  void     RndmArray(Int_t n, Double_t *array);/// Return an array of n random numbers uniformly distributed in ]0,1]
   virtual  void     SetSeed(UInt_t seed=0);
/// Set the generator seed.
/// If the seed given is zero, generate automatically seed values which
/// are different every time by using TRandom3  and TUUID
/// If a seed is given generate the other two needed for the generator state using
/// a linear congruential generator
/// The only condition, stated at the end of the 1999 L'Ecuyer paper is that the seeds
/// must be greater than 1,7 and 15.
```

<!-- TRandom2.md ends here -->
