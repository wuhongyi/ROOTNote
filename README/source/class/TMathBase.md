<!-- TMathBase.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 11月 27 21:31:45 2016 (+0800)
;; Last-Updated: 日 11月 27 21:37:00 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TMathBase

Define the functions Min, Max, Abs, Sign, Range for all types.
NB: These functions are unfortunately not available in a portable
way in std::.

More functions are defined in TMath.h. TMathBase.h is designed to be
a stable file and used in place of TMath.h in the ROOT miniCore.

**namespace TMath**

## namespace

```cpp
   // Abs
   inline Short_t  Abs(Short_t d);
   inline Int_t    Abs(Int_t d);
   inline Long_t   Abs(Long_t d);
   inline Long64_t Abs(Long64_t d);
   inline Float_t  Abs(Float_t d);
   inline Double_t Abs(Double_t d);
   inline LongDouble_t Abs(LongDouble_t d);

   // Even/Odd
   inline Bool_t   Even(Long_t a);
   inline Bool_t   Odd(Long_t a);

   // SignBit
   template<typename Integer>
   inline Bool_t SignBit(Integer a);
   inline Bool_t SignBit(Float_t a);
   inline Bool_t SignBit(Double_t a);
   inline Bool_t SignBit(LongDouble_t a);

   // Sign
   template<typename T1, typename T2>
   inline T1 Sign( T1 a, T2 b);
   inline Float_t  Sign(Float_t a, Float_t b);
   inline Double_t Sign(Double_t a, Double_t b);
   inline LongDouble_t Sign(LongDouble_t a, LongDouble_t b);
   
   // Min, Max of two scalars
   inline Short_t   Min(Short_t a, Short_t b);
   inline UShort_t  Min(UShort_t a, UShort_t b);
   inline Int_t     Min(Int_t a, Int_t b);
   inline UInt_t    Min(UInt_t a, UInt_t b);
   inline Long_t    Min(Long_t a, Long_t b);
   inline ULong_t   Min(ULong_t a, ULong_t b);
   inline Long64_t  Min(Long64_t a, Long64_t b);
   inline ULong64_t Min(ULong64_t a, ULong64_t b);
   inline Float_t   Min(Float_t a, Float_t b);
   inline Double_t  Min(Double_t a, Double_t b);

   inline Short_t   Max(Short_t a, Short_t b);
   inline UShort_t  Max(UShort_t a, UShort_t b);
   inline Int_t     Max(Int_t a, Int_t b);
   inline UInt_t    Max(UInt_t a, UInt_t b);
   inline Long_t    Max(Long_t a, Long_t b);
   inline ULong_t   Max(ULong_t a, ULong_t b);
   inline Long64_t  Max(Long64_t a, Long64_t b);
   inline ULong64_t Max(ULong64_t a, ULong64_t b);
   inline Float_t   Max(Float_t a, Float_t b);
   inline Double_t  Max(Double_t a, Double_t b);

   // Range
   inline Short_t   Range(Short_t lb, Short_t ub, Short_t x);
   inline Int_t     Range(Int_t lb, Int_t ub, Int_t x);
   inline Long_t    Range(Long_t lb, Long_t ub, Long_t x);
   inline ULong_t   Range(ULong_t lb, ULong_t ub, ULong_t x);
   inline Double_t  Range(Double_t lb, Double_t ub, Double_t x);

   //NextPrime is used by the Core classes.
   Long_t   NextPrime(Long_t x);   // Least prime number greater than x
/// Return next prime number after x, unless x is a prime in which case
/// x is returned.   
```

## code


## example




<!-- TMathBase.md ends here -->
