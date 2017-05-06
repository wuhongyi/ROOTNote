<!-- TRandom1.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 5月  6 16:16:51 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TRandom1

**继承 TRandom**



## class

Ranlux random number generator class (periodicity > 10**14) 



```cpp
/// Luxury level is set in the same way as the original FORTRAN routine.
///  level 0  (p=24): equivalent to the original RCARRY of Marsaglia
///           and Zaman, very long period, but fails many tests.
///  level 1  (p=48): considerable improvement in quality over level 0,
///           now passes the gap test, but still fails spectral test.
///  level 2  (p=97): passes all known tests, but theoretically still
///           defective.
///  level 3  (p=223): DEFAULT VALUE.  Any theoretically possible
///           correlations have very small chance of being observed.
///  level 4  (p=389): highest possible luxury, all 24 bits chaotic.

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
   static   void     GetTableSeeds(UInt_t* seeds, Int_t index);///static function returning the table of seeds
                     // Gets back seed values stored in the table, given the index.
   virtual  Double_t Rndm(Int_t i=0);//（0，1]均匀分布
   virtual  void     RndmArray(Int_t size, Float_t *vect);///return an array of random numbers in ]0,1]
   virtual  void     RndmArray(Int_t size, Double_t *vect);///return an array of random numbers in ]0,1[
   virtual  void     SetSeed2(UInt_t seed, Int_t lux=3);
/// The initialisation is carried out using a Multiplicative
/// Congruential generator using formula constants of L'Ecuyer
/// as described in "A review of pseudorandom number generators"
/// (Fred James) published in Computer Physics Communications 60 (1990)
/// pages 329-344
/// modified for the case of seed = 0. In that case a random 64 bits seed based on
/// TUUID (using TRandom3(0) ) is generated in order to have a unique seed

                     // Sets the state of the algorithm according to seed.
					 virtual  void     SetSeeds(const UInt_t * seeds, Int_t lux=3);


                     // Sets the state of the algorithm according to the zero terminated
                     // array of seeds. Only the first seed is used.
   virtual  void     SetSeed(UInt_t seed);
```


<!-- TRandom1.md ends here -->
