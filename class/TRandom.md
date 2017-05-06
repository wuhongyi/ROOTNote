<!-- TRandom.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:29:55 2014 (+0800)
;; Last-Updated: 六 5月  6 16:12:39 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 9
;; URL: http://wuhongyi.cn -->

# TRandom

**继承 TNamed**

```
This is the base class for the ROOT Random number generators. 
This class defines the ROOT Random number interface and it should not be instantiated directly but used via its derived classes (e.g. TRandom1, TRandom2 or TRandom3). 
Note that this class implements also a very simple generator (linear congruential) with periodicity = 10**9
which is known to have defects (the lower random bits are correlated) and therefore should NOT be used in any statistical study.
One should use instead TRandom1, TRandom2 or TRandom3.
TRandom3, is based on the "Mersenne Twister generator", and is the recommended one, since it has good random proprieties (period of about 10**6000 ) and it is fast.
TRandom1, based on the RANLUX algorithm, has mathematically proven random proprieties and a period of about 10**171. It is however slower than the others.
TRandom2, is based on the Tausworthe generator of L'Ecuyer, and it has the advantage of being fast and using only 3 words (of 32 bits) for the state. The period is 10**26.

The following table shows some timings (in nanoseconds/call) for the random numbers obtained using an Intel Pentium 3.0 GHz running Linux and using the gcc 3.2.3 compiler

-   TRandom           34   ns/call     (BAD Generator)
-   TRandom1          242  ns/call
-   TRandom2          37   ns/call
-   TRandom3          45   ns/call

Random numbers distributed according to 1-d, 2-d or 3-d distributions contained in TF1, TF2 or TF3 objects can also be generated. 
For example, to get a random number distributed following abs(sin(x)/x)*sqrt(x)
you can do :

  TF1 *f1 = new TF1("f1","abs(sin(x)/x)*sqrt(x)",0,10);
  double r = f1->GetRandom();

or you can use the UNURAN package. You need in this case to initialize UNURAN
to the function you would like to generate.

  TUnuran u;
  u.Init(TUnuranDistrCont(f1));
  double r = u.Sample();
```

## class

默认随机种子 65539

Simple Random number generator (periodicity = 10**9)

```cpp
virtual  Int_t    Binomial(Int_t ntot, Double_t prob);//二项分布
/// Generates a random integer N according to the binomial law.
/// Coded from Los Alamos report LA-5061-MS.
/// N is binomially distributed between 0 and ntot inclusive
/// with mean prob*ntot and prob is between 0 and 1.
/// Note: This function should not be used when ntot is large (say >100).
/// The normal approximation is then recommended instead
/// (with mean =*ntot+0.5 and standard deviation sqrt(ntot*prob*(1-prob)).

virtual  Double_t BreitWigner(Double_t mean=0, Double_t gamma=1);//Brei-Wigner分布
/// Return a number distributed following a BreitWigner function with mean and gamma.

virtual  void     Circle(Double_t &x, Double_t &y, Double_t r);
/// Generates random vectors, uniformly distributed over a circle of given radius.
///   Input : r = circle radius
///   Output: x,y a random 2-d vector of length r

virtual  Double_t Exp(Double_t tau);//指数分布
/// Returns an exponential deviate.
///          exp( -t/tau )

virtual  Double_t Gaus(Double_t mean=0, Double_t sigma=1);//高斯分布
/// Samples a random number from the standard Normal (Gaussian) Distribution
/// with the given mean and sigma.
/// Uses the Acceptance-complement ratio from W. Hoermann and G. Derflinger
/// This is one of the fastest existing method for generating normal random variables.
/// It is a factor 2/3 faster than the polar (Box-Muller) method used in the previous
/// version of TRandom::Gaus. The speed is comparable to the Ziggurat method (from Marsaglia)
/// implemented for example in GSL and available in the MathMore library.
/// REFERENCE:  - W. Hoermann and G. Derflinger (1990):
///              The ACR Method for generating normal random variables,
///              OR Spektrum 12 (1990), 181-185.
/// Implementation taken from
/// UNURAN (c) 2000  W. Hoermann & J. Leydold, Institut f. Statistik, WU Wien

virtual  UInt_t   GetSeed() const {return fSeed;}//获得随机种子
virtual  UInt_t   Integer(UInt_t imax);//（0，imax-1）随机整数
virtual  Double_t Landau(Double_t mean=0, Double_t sigma=1);//Landau分布
/// Generate a random number following a Landau distribution
/// with location parameter mu and scale parameter sigma:
///      Landau( (x-mu)/sigma )
/// Note that mu is not the mpv(most probable value) of the Landa distribution
/// and sigma is not the standard deviation of the distribution which is not defined.
/// For mu  =0 and sigma=1, the mpv = -0.22278
/// The Landau random number generation is implemented using the
/// function landau_quantile(x,sigma), which provides
/// the inverse of the landau cumulative distribution.
/// landau_quantile has been converted from CERNLIB ranlan(G110).

virtual  Int_t    Poisson(Double_t mean);//泊松分布（返回int）
/// Generates a random integer N according to a Poisson law.
/// Prob(N) = exp(-mean)*mean^N/Factorial(N)
/// Use a different procedure according to the mean value.
/// The algorithm is the same used by CLHEP.
/// For lower value (mean < 25) use the rejection method based on
/// the exponential.
/// For higher values use a rejection method comparing with a Lorentzian
/// distribution, as suggested by several authors.
/// This routine since is returning 32 bits integer will not work for values
/// larger than 2*10**9.
/// One should then use the Trandom::PoissonD for such large values.

virtual  Double_t PoissonD(Double_t mean);//泊松分布（返回double）
/// Generates a random number according to a Poisson law.
/// Prob(N) = exp(-mean)*mean^N/Factorial(N)
/// This function is a variant of TRandom::Poisson returning a double
/// instead of an integer.

virtual  void     Rannor(Float_t &a, Float_t &b);//Return 2 numbers distributed following a gaussian with mean=0 and sigma=1.
virtual  void     Rannor(Double_t &a, Double_t &b);//Return 2 numbers distributed following a gaussian with mean=0 and sigma=1.
virtual  void     ReadRandom(const char *filename);//从root文件中读取随机数产生器
/// Reads saved random generator status from filename.

virtual  void     SetSeed(UInt_t seed=0);//设置随机种子
/// Set the random generator seed. Note that default value is zero, which is
/// different than the default value used when constructing the class.
/// If the seed is zero the seed is set to a random value
/// which in case of TRandom depends on the lowest 4 bytes of TUUID
/// The UUID will be identical if SetSeed(0) is called with time smaller than 100 ns
/// Instead if a different generator implementation is used (TRandom1, 2 or 3)
/// the seed is generated using a 128 bit UUID. This results in different seeds
/// and then random sequence for every SetSeed(0) call.

virtual  Double_t Rndm(Int_t i=0);//（0，1]均匀分布
///  Machine independent random number generator.
///  Based on the BSD Unix (Rand) Linear congrential generator.
///  Produces uniformly-distributed floating points between 0 and 1.
///  Identical sequence on all machines of >= 32 bits.
///  Periodicity = 2**31, generates a number in (0,1).
///  Note that this is a generator which is known to have defects
///  (the lower random bits are correlated) and therefore should NOT be
///  used in any statistical study).

virtual  void     RndmArray(Int_t n, Float_t *array);/// Return an array of n random numbers uniformly distributed in ]0,1].
virtual  void     RndmArray(Int_t n, Double_t *array);/// Return an array of n random numbers uniformly distributed in ]0,1].
virtual  void     Sphere(Double_t &x, Double_t &y, Double_t &z, Double_t r);//获得各向同性的抽样
/// Generates random vectors, uniformly distributed over the surface
/// of a sphere of given radius.
///   Input : r = sphere radius
///   Output: x,y,z a random 3-d vector of length r
/// Method: (based on algorithm suggested by Knuth and attributed to Robert E Knop)
///         which uses less random numbers than the CERNLIB RN23DIM algorithm

virtual  Double_t Uniform(Double_t x1=1);/// Returns a uniform deviate on the interval  (0, x1).
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
