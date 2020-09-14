<!-- TVirtualFitter.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 21:31:47 2016 (+0800)
;; Last-Updated: 六 1月  5 12:02:15 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TVirtualFitter


Abstract base class for fitting

TVirtualFitter 继承 TNamed

## class

```cpp
   TVirtualFitter();
   virtual ~TVirtualFitter();
   virtual Double_t  Chisquare(Int_t npar, Double_t *params) const  = 0;

   virtual void      Clear(Option_t *option="") = 0;
   virtual Int_t     ExecuteCommand(const char *command, Double_t *args, Int_t nargs) = 0;
   virtual void      FixParameter(Int_t ipar) = 0;
   virtual void      GetConfidenceIntervals(Int_t n, Int_t ndim, const Double_t *x, Double_t *ci, Double_t cl=0.95);
///return confidence intervals in array x of dimension ndim
///implemented in TFitter and TLinearFitter

   virtual void      GetConfidenceIntervals(TObject *obj, Double_t cl=0.95);
///return confidence intervals in TObject obj
///implemented in TFitter and TLinearFitter

   virtual Double_t *GetCovarianceMatrix() const = 0;
   virtual Double_t  GetCovarianceMatrixElement(Int_t i, Int_t j) const = 0;
   virtual Int_t     GetErrors(Int_t ipar,Double_t &eplus, Double_t &eminus, Double_t &eparab, Double_t &globcc) const = 0;
   typedef void   (* FCNFunc_t )(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
   virtual FCNFunc_t GetFCN() { return fFCN; }
   virtual Foption_t GetFitOption() const {return fOption;}
   TMethodCall      *GetMethodCall() const {return fMethodCall;}
   virtual Int_t     GetNumberTotalParameters() const = 0;
   virtual Int_t     GetNumberFreeParameters() const = 0;
   virtual TObject  *GetObjectFit() const {return fObjectFit;}
   virtual Double_t  GetParError(Int_t ipar) const = 0;
   virtual Double_t  GetParameter(Int_t ipar) const = 0;
   virtual Int_t     GetParameter(Int_t ipar,char *name,Double_t &value,Double_t &verr,Double_t &vlow, Double_t &vhigh) const  = 0;
   virtual const char *GetParName(Int_t ipar) const = 0;
   virtual Int_t     GetStats(Double_t &amin, Double_t &edm, Double_t &errdef, Int_t &nvpar, Int_t &nparx) const  = 0;
   virtual Double_t  GetSumLog(Int_t i) = 0;
   virtual TObject  *GetUserFunc() const {return fUserFunc;}
   virtual Int_t     GetXfirst() const {return fXfirst;}
   virtual Int_t     GetXlast()  const {return fXlast;}
   virtual Int_t     GetYfirst() const {return fYfirst;}
   virtual Int_t     GetYlast()  const {return fYlast;}
   virtual Int_t     GetZfirst() const {return fZfirst;}
   virtual Int_t     GetZlast()  const {return fZlast;}
   virtual Bool_t    IsFixed(Int_t ipar) const = 0;
   virtual void      PrintResults(Int_t level, Double_t amin) const = 0;
   virtual void      ReleaseParameter(Int_t ipar) = 0;
   virtual Double_t *SetCache(Int_t npoints, Int_t psize);
/// Initialize the cache array
/// npoints is the number of points to be stored (or already stored) in the cache
/// psize is the number of elements per point
/// if (npoints*psize > fCacheSize) the existing cache is deleted
/// and a new array is created.
/// The function returns a pointer to the cache

   virtual void      SetFCN(void *fcn);
///  To set the address of the minimization objective function
///     this function is called by CINT instead of the function above

   virtual void      SetFCN(void (*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t));
/// To set the address of the minimization objective function
/// called by the native compiler (see function below when called by CINT)

   virtual void      SetFitMethod(const char *name) = 0;
   virtual void      SetFitOption(Foption_t option) {fOption = option;}
   virtual void      SetObjectFit(TObject *obj) {fObjectFit = obj;}
   virtual Int_t     SetParameter(Int_t ipar,const char *parname,Double_t value,Double_t verr,Double_t vlow, Double_t vhigh) = 0;
   virtual void      SetUserFunc(TObject *userfunc) {fUserFunc = userfunc;}
   virtual void      SetXfirst(Int_t first) {fXfirst = first;}
   virtual void      SetXlast (Int_t last)  {fXlast  = last;}
   virtual void      SetYfirst(Int_t first) {fYfirst = first;}
   virtual void      SetYlast (Int_t last)  {fYlast  = last;}
   virtual void      SetZfirst(Int_t first) {fZfirst = first;}
   virtual void      SetZlast (Int_t last)  {fZlast  = last;}

   static  TVirtualFitter *GetFitter();/// static: return the current Fitter
   static  TVirtualFitter *Fitter(TObject *obj, Int_t maxpar = 25);
/// Static function returning a pointer to the current fitter.
/// If the fitter does not exist, the default TFitter is created.
/// Don't delete the returned fitter object, it will be re-used.

   static const char *GetDefaultFitter();/// static: return the name of the default fitter
   static Int_t     GetMaxIterations();
/// static: Return the maximum number of iterations
/// actually max number of function calls

   static Double_t  GetErrorDef();/// static: Return the Error Definition
   static Double_t  GetPrecision();/// static: Return the fit relative precision
   static void      SetDefaultFitter(const char* name = "");/// static: set name of default fitter
   static void      SetFitter(TVirtualFitter *fitter, Int_t maxpar = 25);/// Static function to set an alternative fitter
   static void      SetMaxIterations(Int_t niter=5000);
/// static: Set the maximum number of function calls for the minimization algorithm
/// For example for MIGRAD this is the maxcalls value passed as first argument
/// (see http://wwwasdoc.web.cern.ch/wwwasdoc/minuit/node18.html )

   static void      SetErrorDef(Double_t errdef=1);
/// static: Set the Error Definition (default=1)
/// For Minuit this is the value passed with the "SET ERR" command
/// (see http://wwwasdoc.web.cern.ch/wwwasdoc/minuit/node18.html)

   static void      SetPrecision(Double_t prec=1e-6);
/// static: Set the tolerance used in the minimization algorithm
/// For example for MIGRAD this is tolerance value passed as second argument
/// (see http://wwwasdoc.web.cern.ch/wwwasdoc/minuit/node18.html )
```

----

## code



## example




<!-- TVirtualFitter.md ends here -->
