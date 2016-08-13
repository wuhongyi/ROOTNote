<!-- TRandom1.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 8月 13 14:35:16 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.github.io -->

# TRandom1

## class

**继承 TRandom**

Ranlux random number generator class (periodicity > 10**14) 



```cpp
   TRandom1();
   TRandom1(UInt_t seed, Int_t lux = 3 );
   TRandom1(Int_t rowIndex, Int_t colIndex, Int_t lux );
   virtual ~TRandom1();
   
   virtual  Int_t    GetLuxury() const {return fLuxury;}
                    // Get the current seed (first element of the table)
   virtual  UInt_t   GetSeed() const { return  UInt_t ( fFloatSeedTable[0] /  fMantissaBit24 ) ; }
                    // Gets the current seed.
   const UInt_t     *GetTheSeeds() const {return fTheSeeds;}
                     // Gets the current array of seeds.
   static   void     GetTableSeeds(UInt_t* seeds, Int_t index);
                     // Gets back seed values stored in the table, given the index.
   virtual  Double_t Rndm(Int_t i=0);//（0，1]均匀分布
   virtual  void     RndmArray(Int_t size, Float_t *vect);
   virtual  void     RndmArray(Int_t size, Double_t *vect);
   virtual  void     SetSeed2(UInt_t seed, Int_t lux=3);
                     // Sets the state of the algorithm according to seed.
   virtual  void     SetSeeds(const UInt_t * seeds, Int_t lux=3);
                     // Sets the state of the algorithm according to the zero terminated
                     // array of seeds. Only the first seed is used.
   virtual  void     SetSeed(UInt_t seed);
```


<!-- TRandom1.md ends here -->
