<!-- TFitter.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 13:48:37 2016 (+0800)
;; Last-Updated: 一 11月 28 13:56:29 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TFitter

The ROOT standard fitter based on TMinuit

TFitter 继承 TVirtualFitter

## class

```cpp
   TFitter(Int_t maxpar = 25);
   virtual ~TFitter();
   virtual Double_t   Chisquare(Int_t npar, Double_t *params) const ;/// return a chisquare equivalent
   virtual void       Clear(Option_t *option="");/// reset the fitter environment
   virtual Int_t      ExecuteCommand(const char *command, Double_t *args, Int_t nargs);
/// Execute a fitter command;
///   command : command string
///   args    : list of nargs command arguments

   virtual void       FitChisquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
///  Minimization function for H1s using a Chisquare method
///  Default method (function evaluated at center of bin)
///  for each point the cache contains the following info
///    -1D : bc,e, xc  (bin content, error, x of center of bin)
///    -2D : bc,e, xc,yc
///    -3D : bc,e, xc,yc,zc

   virtual void       FitChisquareI(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
///  Minimization function for H1s using a Chisquare method
///  The "I"ntegral method is used
///  for each point the cache contains the following info
///    -1D : bc,e, xc,xw  (bin content, error, x of center of bin, x bin width of bin)
///    -2D : bc,e, xc,xw,yc,yw
///    -3D : bc,e, xc,xw,yc,yw,zc,zw

   virtual void       FitLikelihood(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
///  Minimization function for H1s using a Likelihood method*-*-*-*-*-*
///     Basically, it forms the likelihood by determining the Poisson
///     probability that given a number of entries in a particular bin,
///     the fit would predict it's value.  This is then done for each bin,
///     and the sum of the logs is taken as the likelihood.
///  Default method (function evaluated at center of bin)
///  for each point the cache contains the following info
///    -1D : bc,e, xc  (bin content, error, x of center of bin)
///    -2D : bc,e, xc,yc
///    -3D : bc,e, xc,yc,zc

   virtual void       FitLikelihoodI(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
///  Minimization function for H1s using a Likelihood method*-*-*-*-*-*
///     Basically, it forms the likelihood by determining the Poisson
///     probability that given a number of entries in a particular bin,
///     the fit would predict it's value.  This is then done for each bin,
///     and the sum of the logs is taken as the likelihood.
///  The "I"ntegral method is used
///  for each point the cache contains the following info
///    -1D : bc,e, xc,xw  (bin content, error, x of center of bin, x bin width of bin)
///    -2D : bc,e, xc,xw,yc,yw
///    -3D : bc,e, xc,xw,yc,yw,zc,zw

   virtual void       FixParameter(Int_t ipar);/// Fix parameter ipar.
   virtual void       GetConfidenceIntervals(Int_t n, Int_t ndim, const Double_t *x, Double_t *ci, Double_t cl=0.95);
///Computes point-by-point confidence intervals for the fitted function
///Parameters:
///n - number of points
///ndim - dimensions of points
///x - points, at which to compute the intervals, for ndim > 1
///    should be in order: (x0,y0, x1, y1, ... xn, yn)
///ci - computed intervals are returned in this array
///cl - confidence level, default=0.95
///NOTE, that the intervals are approximate for nonlinear(in parameters) models

   virtual void       GetConfidenceIntervals(TObject *obj, Double_t cl=0.95);
///Computes confidence intervals at level cl. Default is 0.95
///The TObject parameter can be a TGraphErrors, a TGraph2DErrors or a TH1,2,3.
///For Graphs, confidence intervals are computed for each point,
///the value of the graph at that point is set to the function value at that
///point, and the graph y-errors (or z-errors) are set to the value of
///the confidence interval at that point.
///For Histograms, confidence intervals are computed for each bin center
///The bin content of this bin is then set to the function value at the bin
///center, and the bin error is set to the confidence interval value.
///NOTE: confidence intervals are approximate for nonlinear models!
///Allowed combinations:
///Fitted object               Passed object
///TGraph                      TGraphErrors, TH1
///TGraphErrors, AsymmErrors   TGraphErrors, TH1
///TH1                         TGraphErrors, TH1
///TGraph2D                    TGraph2DErrors, TH2
///TGraph2DErrors              TGraph2DErrors, TH2
///TH2                         TGraph2DErrors, TH2
///TH3                         TH3

   virtual Double_t  *GetCovarianceMatrix() const;/// return a pointer to the covariance matrix
   virtual Double_t   GetCovarianceMatrixElement(Int_t i, Int_t j) const;
/// return element i,j from the covariance matrix

   virtual Int_t      GetErrors(Int_t ipar,Double_t &eplus, Double_t &eminus, Double_t &eparab, Double_t &globcc) const;
/// return current errors for a parameter
///   ipar     : parameter number
///   eplus    : upper error
///   eminus   : lower error
///   eparab   : parabolic error
///   globcc   : global correlation coefficient

   TMinuit           *GetMinuit() const {return fMinuit;}
   virtual Int_t      GetNumberTotalParameters() const;/// return the total number of parameters (free + fixed)
   virtual Int_t      GetNumberFreeParameters() const;/// return the number of free parameters
   virtual Double_t   GetParError(Int_t ipar) const;/// return error of parameter ipar
   virtual Double_t   GetParameter(Int_t ipar) const;
/// return current value of parameter ipar

   virtual Int_t      GetParameter(Int_t ipar,char *name,Double_t &value,Double_t &verr,Double_t &vlow, Double_t &vhigh) const;
/// return current values for a parameter
///   ipar     : parameter number
///   parname  : parameter name
///   value    : initial parameter value
///   verr     : initial error for this parameter
///   vlow     : lower value for the parameter
///   vhigh    : upper value for the parameter
///  WARNING! parname must be suitably dimensionned in the calling function.

   virtual const char *GetParName(Int_t ipar) const;/// return name of parameter ipar
   virtual Int_t      GetStats(Double_t &amin, Double_t &edm, Double_t &errdef, Int_t &nvpar, Int_t &nparx) const;
/// return global fit parameters
///   amin     : chisquare
///   edm      : estimated distance to minimum
///   errdef
///   nvpar    : number of variable parameters
///   nparx    : total number of parameters

   virtual Double_t   GetSumLog(Int_t i);
/// return Sum(log(i) i=0,n
/// used by log likelihood fits

   virtual Bool_t     IsFixed(Int_t ipar) const;///return kTRUE if parameter ipar is fixed, kFALSE othersise)
   virtual void       PrintResults(Int_t level, Double_t amin) const;/// Print fit results
   virtual void       ReleaseParameter(Int_t ipar);/// Release parameter ipar.
   virtual void       SetFCN(void *fcn);
/// Specify the address of the fitting algorithm (from the interpreter)

   virtual void       SetFCN(void (*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t));
/// Specify the address of the fitting algorithm

   virtual void       SetFitMethod(const char *name);/// ret fit method (chisquare or loglikelihood)
   virtual Int_t      SetParameter(Int_t ipar,const char *parname,Double_t value,Double_t verr,Double_t vlow, Double_t vhigh);
/// set initial values for a parameter
///   ipar     : parameter number
///   parname  : parameter name
///   value    : initial parameter value
///   verr     : initial error for this parameter
///   vlow     : lower value for the parameter
///   vhigh    : upper value for the parameter
```

## code


## example



<!-- TFitter.md ends here -->
