<!-- TBackCompFitter.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 13:12:27 2016 (+0800)
;; Last-Updated: 一 11月 28 13:47:39 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TBackCompFitter

Backward compatible implementation of TVirtualFitter using the
class ROOT::Fit::Fitter. This class is created after fitting an
histogram (TH1), TGraph or TTree and provides in addition to the
methods of the TVirtualFitter hooks to access the fit result class
(ROOT::Fit::FitResult), the fit configuration
(ROOT::Fit::FitConfig) or the fit data (ROOT::Fit::FitData) using

Methods for getting the confidence level or contours are also
provided. Note that after a new calls to TH1::Fit (or similar) the
class will be deleted and all reference to the FitResult, FitConfig
or minimizer will be invalid. One could eventually copying the
class before issuing a new fit to avoid deleting this information.


TBackCompFitter 继承 TVirtualFitter

## class

```cpp
   TBackCompFitter();
/// Constructor needed by TVirtualFitter interface. Same behavior as default constructor.
/// initialize setting name and the global pointer

   //TBackCompFitter(ROOT::Fit::Fitter & fitter, ROOT::Fit::FitData * );
   TBackCompFitter( const std::shared_ptr<ROOT::Fit::Fitter> & fitter, const std::shared_ptr<ROOT::Fit::FitData> & data  );
/// Constructor used after having fit using directly ROOT::Fit::Fitter
/// will create a dummy fitter copying configuration and parameter settings

   virtual ~TBackCompFitter();/// Destructor - delete the managed objects


   enum {
      kCanDeleteLast = BIT(9)  // object can be deleted before creating a new one
   };

   // inherited interface
   virtual Double_t  Chisquare(Int_t npar, Double_t *params) const;
/// Do chisquare calculations in case of likelihood fits
/// Do evaluation a the minimum only

   virtual void      Clear(Option_t *option="");
   virtual Int_t     ExecuteCommand(const char *command, Double_t *args, Int_t nargs);
/// Execute the command (Fortran Minuit compatible interface)

   virtual void      FixParameter(Int_t ipar);/// Fix the parameter

   virtual void      GetConfidenceIntervals(Int_t n, Int_t ndim, const Double_t *x, Double_t *ci, Double_t cl=0.95);
/// Computes point-by-point confidence intervals for the fitted function.
/// \param n    number of points
/// \param ndim dimensions of points
/// \param x    points, at which to compute the intervals, for ndim > 1
///             should be in order: (x0,y0, x1, y1, ... xn, yn)
/// \param ci   computed intervals are returned in this array
/// \param cl   confidence level, default=0.95
/// NOTE, that the intervals are approximate for nonlinear(in parameters) models

   virtual void      GetConfidenceIntervals(TObject *obj, Double_t cl=0.95);
/// Computes confidence intervals at level cl. Default is 0.95
/// The TObject parameter can be a TGraphErrors, a TGraph2DErrors or a TH1,2,3.
/// For Graphs, confidence intervals are computed for each point,
/// the value of the graph at that point is set to the function value at that
/// point, and the graph y-errors (or z-errors) are set to the value of
/// the confidence interval at that point.
/// For Histograms, confidence intervals are computed for each bin center
/// The bin content of this bin is then set to the function value at the bin
/// center, and the bin error is set to the confidence interval value.
/// NOTE: confidence intervals are approximate for nonlinear models!
/// Allowed combinations:
/// Fitted object             | Passed object
/// --------------------------|------------------
/// TGraph                    | TGraphErrors, TH1
/// TGraphErrors, AsymmErrors | TGraphErrors, TH1
/// TH1                       | TGraphErrors, TH1
/// TGraph2D                  | TGraph2DErrors, TH2
/// TGraph2DErrors            | TGraph2DErrors, TH2
/// TH2                       | TGraph2DErrors, TH2
/// TH3                       | TH3

   virtual Double_t *GetCovarianceMatrix() const;
/// Get the error matrix in a pointer to a NxN array.
/// excluding the fixed parameters

   virtual Double_t  GetCovarianceMatrixElement(Int_t i, Int_t j) const;
/// Get error matrix element (return all zero if matrix is not available)

   virtual Int_t     GetErrors(Int_t ipar,Double_t &eplus, Double_t &eminus, Double_t &eparab, Double_t &globcc) const;/// Get fit errors
   virtual Int_t     GetNumberTotalParameters() const;/// Number of total parameters
   virtual Int_t     GetNumberFreeParameters() const;

   virtual Double_t  GetParError(Int_t ipar) const;/// Parameter error
   virtual Double_t  GetParameter(Int_t ipar) const;/// Parameter value
   virtual Int_t     GetParameter(Int_t ipar,char *name,Double_t &value,Double_t &verr,Double_t &vlow, Double_t &vhigh) const;/// Get all parameter info (name, value, errors)
   virtual const char *GetParName(Int_t ipar) const;/// Return name of parameter ipar
   virtual Int_t     GetStats(Double_t &amin, Double_t &edm, Double_t &errdef, Int_t &nvpar, Int_t &nparx) const;/// Get fit statistical information
   virtual Double_t  GetSumLog(Int_t i);/// Sum of log (un-needed)

   virtual Bool_t    IsFixed(Int_t ipar) const ;/// Query if parameter ipar is fixed

   virtual void      PrintResults(Int_t level, Double_t amin) const;
/// Print the fit result.
/// Use PrintResults function in case of Minuit for old -style printing

   virtual void      ReleaseParameter(Int_t ipar);/// Release a fit parameter
   virtual void      SetFitMethod(const char *name);
/// Set fit method (chi2 or likelihood).
/// According to the method the appropriate FCN function will be created

   virtual Int_t     SetParameter(Int_t ipar,const char *parname,Double_t value,Double_t verr,Double_t vlow, Double_t vhigh);
/// Set (add) a new fit parameter passing initial value, step size (verr) and parameter limits
/// if vlow > vhigh the parameter is unbounded
/// if the stepsize (verr) == 0 the parameter is treated as fixed

   virtual void      SetFCN(void (*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t) );
/// Override setFCN to use the Adapter to Minuit2 FCN interface
/// To set the address of the minimization function

   // this for CINT (interactive functions)
   virtual void      SetFCN(void * );
/// Set the address of the minimization function
/// this function is called by CINT instead of the function above

   // for using interpreted function passed by the user
   virtual void SetMethodCall(TMethodCall * m) { fMethodCall = m; }

   // get reference to Fit configuration (NOTE: it will be invalid when class is deleted)
   ROOT::Fit::FitConfig & GetFitConfig()  { return fFitter->Config(); }

   // get reference to Fit Result object (NOTE: it will be invalid when class is deleted)
   const ROOT::Fit::FitResult & GetFitResult() const { return fFitter->Result(); }

   // get a copy of the Fit result returning directly a new  TFitResult
   TFitResult * GetTFitResult() const;
/// Return a new copy of the TFitResult object which needs to be deleted later by the user

   // get reference to Fit Data object (NOTE: it will be invalid when class is deleted)
   const ROOT::Fit::FitData & GetFitData() const { return *fFitData; }

   // return pointer to last used minimizer
   ROOT::Math::Minimizer * GetMinimizer() const;
/// Return a pointer to the minimizer.
/// the return pointer will be valid after fitting and as long a new fit will not be done.
/// For keeping a minimizer pointer the method ReCreateMinimizer() could eventually be used

   // return pointer to last used objective function
   ROOT::Math::IMultiGenFunction * GetObjFunction() const;
/// Return a pointer to the objective function (FCN)
/// If fitting directly using TBackCompFitter the pointer is managed by the class,
/// which has been set previously when calling SetObjFunction or SetFCN
/// Otherwise if the class is used in the backward compatible mode (e.g. after having fitted a TH1)
/// the return pointer will be valid after fitting and as long a new fit will not be done.

   // scan likelihood value of  parameter and fill the given graph.
   bool  Scan(unsigned int ipar, TGraph * gr, double xmin = 0, double xmax = 0);
///  Scan parameter ipar between value of xmin and xmax
///  A graph must be given which will be on return filled with the scan resul
///  If the graph size is zero, a default size n = 40 will be used

   //    scan likelihood value for two  parameters and fill the given graph.
   //    bool  Scan2D(unsigned int ipar, unsigned int jpar, TGraph2D * gr,
   //                         double xmin = 0, double xmax = 0, double ymin = 0, double ymax = 0);

   // create contour of two parameters around the minimum
   // pass as option confidence level:  default is a value of 0.683
   bool  Contour(unsigned int ipar, unsigned int jpar, TGraph * gr , double confLevel = 0.683);
/// Create a 2D contour around the minimum for the parameter ipar and jpar
/// if a minimum does not exist or is invalid it will return false
/// on exit a TGraph is filled with the contour points
/// the number of contur points is determined by the size of the TGraph.
/// if the size is zero a default number of points = 20 is used
/// pass optionally the confidence level, default is 0.683
/// it is assumed that ErrorDef() defines the right error definition
/// (i.e 1 sigma error for one parameter). If not the confidence level are scaled to new level

   // set FCN using new interface
   virtual void SetObjFunction(  ROOT::Math::IMultiGenFunction * f);
/// Set the objective function for fitting
/// Needed if fitting directly using TBackCompFitter class
/// The class clones a copy of the function and manages it

   // recreate minimizer and FCN for TMinuit fits and standard printout
   void ReCreateMinimizer();
/// Recreate a minimizer instance using the function and data
/// set objective function in minimizers function to re-create FCN from stored data object and fit options
```

## code

```cpp
TBackCompFitter * fitter = (TBackCompFitter *) TVirtualFitter::GetFitter();
ROOT::Fit::FitResult & result = fitter->GetFitResult();
result.Print(std::cout);
```

## example




<!-- TBackCompFitter.md ends here -->
