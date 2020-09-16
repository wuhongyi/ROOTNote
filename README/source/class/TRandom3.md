<!-- TRandom3.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 三 9月 16 12:58:30 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->


# TRandom3*

**继承 TRandom**

## class

默认随机种子 4357


```cpp
// get the current seed (only first element of the seed table)
virtual  UInt_t    GetSeed() const { return fMt[0];}
virtual  Double_t  Rndm(Int_t i=0);//（0，1]均匀分布
///  Machine independent random number generator.
///  Produces uniformly-distributed floating points in (0,1)
///  Method: Mersenne Twister

virtual  void      RndmArray(Int_t n, Float_t *array);/// Return an array of n random numbers uniformly distributed in ]0,1]
virtual  void      RndmArray(Int_t n, Double_t *array);/// Return an array of n random numbers uniformly distributed in ]0,1]
virtual  void      SetSeed(UInt_t seed=0);
///  Set the random generator sequence
/// if seed is 0 (default value) a TUUID is generated and used to fill
/// the first 8 integers of the seed array.
/// In this case the seed is guaranteed to be unique in space and time.
/// Use upgraded seeding procedure to fix a known problem when seeding with values
/// with many zero in the bit pattern (like 2**28).
/// see http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
```

## code

```cpp
#include "TRandom1.h"          TRandom3 r(111);
#include "TRandom2.h"          TRandom3 r(0);
#include "TRandom3.h"          TRandom3 r(0);
```


## example



<!-- TRandom3.md ends here -->
