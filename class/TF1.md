<!-- TF1.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 三 10月  5 13:15:44 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 13
;; URL: http://wuhongyi.cn -->

# TF1

继承于 TNamed, TAttLine, TAttFill, TAttMarker

A TF1 object is a 1-Dim function defined between a lower and upper limit.   
The function may be a simple function based on a TFormula expression or a precompiled user function.   
The function may have associated parameters.   
TF1 graphics function is via the TH1 and TGraph drawing functions.

The following types of functions can be created:

1.  Expression using variable x and no parameters
2.  Expression using variable x with parameters
3.  Lambda Expression with variable x and parameters
4.  A general C function with parameters
5.  A general C++ function object (functor) with parameters
6.  A member function with parameters of a general C++ class

## class

```cpp
public:
    // TF1 status bits
    enum {
       kNotDraw     = BIT(9)  // don't draw the function when in a TH1
    };

   TF1();
   TF1(const char *name, const char *formula, Double_t xmin=0, Double_t xmax = 1);
   TF1(const char *name, Double_t xmin, Double_t xmax, Int_t npar,Int_t ndim = 1);
#ifndef __CINT__
   TF1(const char *name, Double_t (*fcn)(Double_t *, Double_t *), Double_t xmin=0, Double_t xmax=1, Int_t npar=0, Int_t ndim = 1); //fcn为自己定义的函数曲线，npar为调用的参数个数
   TF1(const char *name, Double_t (*fcn)(const Double_t *, const Double_t *), Double_t xmin=0, Double_t xmax=1, Int_t npar=0,Int_t ndim = 1);
#endif

   // Constructors using functors (compiled mode only)
   TF1(const char *name, ROOT::Math::ParamFunctor f, Double_t xmin = 0, Double_t xmax = 1, Int_t npar = 0,Int_t ndim = 1);

   // Template constructors from any  C++ callable object,  defining  the operator() (double * , double *)
   // and returning a double.
   // The class name is not needed when using compile code, while it is required when using
   // interpreted code via the specialized constructor with void *.
   // An instance of the C++ function class or its pointer can both be used. The former is reccomended when using
   // C++ compiled code, but if CINT compatibility is needed, then a pointer to the function class must be used.
   // xmin and xmax specify the plotting range,  npar is the number of parameters.
   // See the tutorial math/exampleFunctor.C for an example of using this constructor
   template <typename Func>
   TF1(const char *name, Func f, Double_t xmin, Double_t xmax, Int_t npar,Int_t ndim = 1 );
   
   // backward compatible interface
   template <typename Func>
   TF1(const char *name, Func f, Double_t xmin, Double_t xmax, Int_t npar, const char *   ) :
      TNamed(name,name), TAttLine(), TAttFill(), TAttMarker(),
      fXmin(xmin), fXmax(xmax),
      fNpar(npar), fNdim(1),
      fNpx(100), fType(1),
      fNpfits(0), fNDF(0), fChisquare(0),
      fMinimum(-1111), fMaximum(-1111),
      fParErrors(std::vector<Double_t>(npar)),
      fParMin(std::vector<Double_t>(npar)),
      fParMax(std::vector<Double_t>(npar)),
      fParent(0), fHistogram(0),
      fMethodCall(0),
      fNormalized(false), fNormIntegral(0),
      fFunctor(ROOT::Math::ParamFunctor(f)),
      fFormula(0),
      fParams(new TF1Parameters(npar) )
   {
      DoInitialize();
   }


   // Template constructors from a pointer to any C++ class of type PtrObj with a specific member function of type
   // MemFn.
   // The member function must have the signature of  (double * , double *) and returning a double.
   // The class name and the method name are not needed when using compile code
   // (the member function pointer is used in this case), while they are required when using interpreted
   // code via the specialized constructor with void *.
   // xmin and xmax specify the plotting range,  npar is the number of parameters.
   // See the tutorial math/exampleFunctor.C for an example of using this constructor
   template <class PtrObj, typename MemFn>
   TF1(const char *name, const  PtrObj& p, MemFn memFn, Double_t xmin, Double_t xmax, Int_t npar,Int_t ndim = 1) :
      TNamed(name,name), TAttLine(), TAttFill(), TAttMarker(),
      fXmin(xmin), fXmax(xmax),
      fNpar(npar), fNdim(ndim),
      fNpx(100), fType(1),
      fNpfits(0), fNDF(0), fChisquare(0),
      fMinimum(-1111), fMaximum(-1111),
      fParErrors(std::vector<Double_t>(npar)),
      fParMin(std::vector<Double_t>(npar)),
      fParMax(std::vector<Double_t>(npar)),
      fParent(0), fHistogram(0),
      fMethodCall(0),
      fNormalized(false), fNormIntegral(0),
      fFunctor   ( ROOT::Math::ParamFunctor(p,memFn) ),
      fFormula(0),
      fParams(new TF1Parameters(npar) )
   {
      DoInitialize();
   }
   // backward compatible interface
   template <class PtrObj, typename MemFn>
   TF1(const char *name, const  PtrObj& p, MemFn memFn, Double_t xmin, Double_t xmax, Int_t npar,const char * , const char * ) :
      TNamed(name,name), TAttLine(), TAttFill(), TAttMarker(),
      fXmin(xmin), fXmax(xmax),
      fNpar(npar), fNdim(1),
      fNpx(100), fType(1),
      fNpfits(0), fNDF(0), fChisquare(0),
      fMinimum(-1111), fMaximum(-1111),
      fParErrors(std::vector<Double_t>(npar)),
      fParMin(std::vector<Double_t>(npar)),
      fParMax(std::vector<Double_t>(npar)),
      fParent(0), fHistogram(0),
      fMethodCall(0),
      fNormalized(false), fNormIntegral(0),
      fFunctor   ( ROOT::Math::ParamFunctor(p,memFn) ),
      fFormula(0),
      fParams(new TF1Parameters(npar) )
   {
      DoInitialize();
   }

   TF1(const TF1 &f1);
   TF1& operator=(const TF1 &rhs);
   virtual   ~TF1();
   virtual void     AddParameter(const TString &name, Double_t value) { if (fFormula) fFormula->AddParameter(name,value); }
   // virtual void     AddParameters(const pair<TString,Double_t> *pairs, Int_t size) { fFormula->AddParameters(pairs,size); }
   // virtual void     AddVariable(const TString &name, Double_t value = 0) { if (fFormula) fFormula->AddVariable(name,value); }
   // virtual void     AddVariables(const TString *vars, Int_t size) { if (fFormula) fFormula->AddVariables(vars,size); }
   virtual Bool_t   AddToGlobalList(Bool_t on = kTRUE);
/// Add to global list of functions (gROOT->GetListOfFunctions() )
/// return previous status (true of functions was already in the list false if not)

   virtual void     Browse(TBrowser *b);
   virtual void     Copy(TObject &f1) const;
   virtual Double_t Derivative (Double_t x, Double_t *params=0, Double_t epsilon=0.001) const;
   virtual Double_t Derivative2(Double_t x, Double_t *params=0, Double_t epsilon=0.001) const;
   virtual Double_t Derivative3(Double_t x, Double_t *params=0, Double_t epsilon=0.001) const;
   static  Double_t DerivativeError();
   virtual Int_t    DistancetoPrimitive(Int_t px, Int_t py);
/// Compute distance from point px,py to a function.
/// Compute the closest distance of approach from point px,py to this
/// function. The distance is computed in pixels units.
/// Note that px is called with a negative value when the TF1 is in
/// TGraph or TH1 list of functions. In this case there is no point
/// looking at the histogram axis.

   virtual void     Draw(Option_t *option="");
/// Draw this function with its current attributes.
/// Possible option values are:
/// option | description
/// -------|----------------------------------------
/// "SAME" | superimpose on top of existing picture
/// "L"    | connect all computed points with a straight line
/// "C"    | connect all computed points with a smooth curve
/// "FC"   | draw a fill area below a smooth curve
/// Note that the default value is "L". Therefore to draw on top
/// of an existing picture, specify option "LSAME"
/// NB. You must use DrawCopy if you want to draw several times the same
///     function in the current canvas.

   virtual TF1     *DrawCopy(Option_t *option="") const;
/// Draw a copy of this function with its current attributes.
///  This function MUST be used instead of Draw when you want to draw
///  the same function with different parameters settings in the same canvas.
/// Possible option values are:
/// option | description
/// -------|----------------------------------------
/// "SAME" | superimpose on top of existing picture
/// "L"    | connect all computed points with a straight line
/// "C"    | connect all computed points with a smooth curve
/// "FC"   | draw a fill area below a smooth curve
/// Note that the default value is "L". Therefore to draw on top
/// of an existing picture, specify option "LSAME"

   virtual TObject *DrawDerivative(Option_t *option="al"); // *MENU*
   virtual TObject *DrawIntegral(Option_t *option="al");   // *MENU*
   virtual void     DrawF1(Double_t xmin, Double_t xmax, Option_t *option="");
   virtual Double_t Eval(Double_t x, Double_t y=0, Double_t z=0, Double_t t=0) const; //通过变量x获得其函数返回值
   virtual Double_t EvalPar(const Double_t *x, const Double_t *params=0);
   virtual Double_t operator()(Double_t x, Double_t y=0, Double_t z = 0, Double_t t = 0) const;
   virtual Double_t operator()(const Double_t *x, const Double_t *params=0);
   virtual void     ExecuteEvent(Int_t event, Int_t px, Int_t py);
   virtual void     FixParameter(Int_t ipar, Double_t value); /// Fix the value of a parameter. The specified value will be used in a fit operation
       Double_t     GetChisquare() const {return fChisquare;}
   virtual TH1     *GetHistogram() const; //将其转为TH1类型
   virtual TH1     *CreateHistogram() { return DoCreateHistogram(fXmin, fXmax); }
   virtual TFormula *GetFormula() { return fFormula;}
   virtual const TFormula *GetFormula() const { return fFormula;}
   virtual TString  GetExpFormula(Option_t *option="") const { return (fFormula) ? fFormula->GetExpFormula(option) : ""; }
   virtual const TObject *GetLinearPart(Int_t i) const { return (fFormula) ? fFormula->GetLinearPart(i) : nullptr;}
   virtual Double_t GetMaximum(Double_t xmin=0, Double_t xmax=0, Double_t epsilon = 1.E-10, Int_t maxiter = 100, Bool_t logx = false) const; /// Returns the maximum value of the function
///  First, the grid search is used to bracket the maximum
///  with the step size = (xmax-xmin)/fNpx.
///  This way, the step size can be controlled via the SetNpx() function.
///  If the function is unimodal or if its extrema are far apart, setting
///  the fNpx to a small value speeds the algorithm up many times.
///  Then, Brent's method is applied on the bracketed interval
///  epsilon (default = 1.E-10) controls the relative accuracy (if |x| > 1 )
///  and absolute (if |x| < 1)  and maxiter (default = 100) controls the maximum number
///  of iteration of the Brent algorithm
///  If the flag logx is set the grid search is done in log step size
///  This is done automatically if the log scale is set in the current Pad
/// NOTE: see also TF1::GetMaximumX and TF1::GetX

   virtual Double_t GetMinimum(Double_t xmin=0, Double_t xmax=0, Double_t epsilon = 1.E-10, Int_t maxiter = 100, Bool_t logx = false) const; /// Returns the minimum value of the function on the (xmin, xmax) interval
///  First, the grid search is used to bracket the maximum
///  with the step size = (xmax-xmin)/fNpx. This way, the step size
///  can be controlled via the SetNpx() function. If the function is
///  unimodal or if its extrema are far apart, setting the fNpx to
///  a small value speeds the algorithm up many times.
///  Then, Brent's method is applied on the bracketed interval
///  epsilon (default = 1.E-10) controls the relative accuracy (if |x| > 1 )
///  and absolute (if |x| < 1)  and maxiter (default = 100) controls the maximum number
///  of iteration of the Brent algorithm
///  If the flag logx is set the grid search is done in log step size
///  This is done automatically if the log scale is set in the current Pad
/// NOTE: see also TF1::GetMaximumX and TF1::GetX

   virtual Double_t GetMaximumX(Double_t xmin=0, Double_t xmax=0, Double_t epsilon = 1.E-10, Int_t maxiter = 100, Bool_t logx = false) const; /// Returns the X value corresponding to the maximum value of the function
   virtual Double_t GetMinimumX(Double_t xmin=0, Double_t xmax=0, Double_t epsilon = 1.E-10, Int_t maxiter = 100, Bool_t logx = false) const; /// Returns the X value corresponding to the minimum value of the function
   virtual Double_t GetMaximumStored() const {return fMaximum;}
   virtual Double_t GetMinimumStored() const {return fMinimum;}
   virtual Int_t    GetNpar() const { return fNpar;}
   virtual Int_t    GetNdim() const { return fNdim;}
   virtual Int_t    GetNDF() const;
/// Return the number of degrees of freedom in the fit
/// the fNDF parameter has been previously computed during a fit.
/// The number of degrees of freedom corresponds to the number of points
/// used in the fit minus the number of free parameters.

   virtual Int_t    GetNpx() const {return fNpx;} //获得区间分成份数
    TMethodCall    *GetMethodCall() const {return fMethodCall;}
   virtual Int_t    GetNumber() const { return (fFormula) ? fFormula->GetNumber() : 0;}
   virtual Int_t    GetNumberFreeParameters() const;
   virtual Int_t    GetNumberFitPoints() const {return fNpfits;}
   virtual char    *GetObjectInfo(Int_t px, Int_t py) const;
        TObject    *GetParent() const {return fParent;}
   virtual Double_t GetParameter(Int_t ipar) const {
      return (fFormula) ? fFormula->GetParameter(ipar) : fParams->GetParameter(ipar);
   }
   virtual Double_t GetParameter(const TString &name)  const {
      return (fFormula) ? fFormula->GetParameter(name) : fParams->GetParameter(name);
   }
   virtual Double_t *GetParameters() const {
      return (fFormula) ? fFormula->GetParameters() : const_cast<Double_t*>(fParams->GetParameters());
   }
   virtual void     GetParameters(Double_t *params) { if (fFormula) fFormula->GetParameters(params);
                                                      else std::copy(fParams->ParamsVec().begin(), fParams->ParamsVec().end(), params); }
   virtual const char *GetParName(Int_t ipar) const {
      return (fFormula) ? fFormula->GetParName(ipar) : fParams->GetParName(ipar);
   }
   virtual Int_t    GetParNumber(const char* name) const {
      return (fFormula) ? fFormula->GetParNumber(name) : fParams->GetParNumber(name);
   }
   virtual Double_t GetParError(Int_t ipar) const;
   virtual const Double_t *GetParErrors() const {return fParErrors.data();}
   virtual void     GetParLimits(Int_t ipar, Double_t &parmin, Double_t &parmax) const;
   virtual Double_t GetProb() const;
   virtual Int_t    GetQuantiles(Int_t nprobSum, Double_t *q, const Double_t *probSum);
   virtual Double_t GetRandom(); /// Return a random number following this function shape
/// The distribution contained in the function fname (TF1) is integrated
/// over the channel contents.
/// It is normalized to 1.
/// For each bin the integral is approximated by a parabola.
/// The parabola coefficients are stored as non persistent data members
/// Getting one random number implies:
///  - Generating a random number between 0 and 1 (say r1)
///  - Look in which bin in the normalized integral r1 corresponds to
///  - Evaluate the parabolic curve in the selected bin to find the corresponding X value.
/// If the ratio fXmax/fXmin > fNpx the integral is tabulated in log scale in x
/// The parabolic approximation is very good as soon as the number of bins is greater than 50.

   virtual Double_t GetRandom(Double_t xmin, Double_t xmax); /// Return a random number following this function shape in [xmin,xmax]
///   The distribution contained in the function fname (TF1) is integrated
///   over the channel contents.
///   It is normalized to 1.
///   For each bin the integral is approximated by a parabola.
///   The parabola coefficients are stored as non persistent data members
///   Getting one random number implies:
///     - Generating a random number between 0 and 1 (say r1)
///     - Look in which bin in the normalized integral r1 corresponds to
///     - Evaluate the parabolic curve in the selected bin to find
///       the corresponding X value.
///   The parabolic approximation is very good as soon as the number
///   of bins is greater than 50.
///  IMPORTANT NOTE
///  The integral of the function is computed at fNpx points. If the function
///  has sharp peaks, you should increase the number of points (SetNpx)
///  such that the peak is correctly tabulated at several points.

   virtual void     GetRange(Double_t &xmin, Double_t &xmax) const;
   virtual void     GetRange(Double_t &xmin, Double_t &ymin, Double_t &xmax, Double_t &ymax) const;
   virtual void     GetRange(Double_t &xmin, Double_t &ymin, Double_t &zmin, Double_t &xmax, Double_t &ymax, Double_t &zmax) const;
   virtual Double_t GetSave(const Double_t *x);
   virtual Double_t GetX(Double_t y, Double_t xmin=0, Double_t xmax=0, Double_t epsilon = 1.E-10, Int_t maxiter = 100, Bool_t logx = false) const;  //由y找x
/// Returns the X value corresponding to the function value fy for (xmin<x<xmax).
/// in other words it can find the roots of the function when fy=0 and successive calls
/// by changing the next call to [xmin+eps,xmax] where xmin is the previous root.
///  First, the grid search is used to bracket the maximum
///  with the step size = (xmax-xmin)/fNpx. This way, the step size
///  can be controlled via the SetNpx() function. If the function is
///  unimodal or if its extrema are far apart, setting the fNpx to
///  a small value speeds the algorithm up many times.
///  Then, Brent's method is applied on the bracketed interval
///  epsilon (default = 1.E-10) controls the relative accuracy (if |x| > 1 )
///  and absolute (if |x| < 1)  and maxiter (default = 100) controls the maximum number
///  of iteration of the Brent algorithm
///  If the flag logx is set the grid search is done in log step size
///  This is done automatically if the log scale is set in the current Pad
/// NOTE: see also TF1::GetMaximumX, TF1::GetMinimumX

   virtual Double_t GetXmin() const {return fXmin;}
   virtual Double_t GetXmax() const {return fXmax;}
   TAxis           *GetXaxis() const ;
   TAxis           *GetYaxis() const ;
   TAxis           *GetZaxis() const ;
   virtual Double_t GetVariable(const TString &name) { return (fFormula) ? fFormula->GetVariable(name) : 0;}
   virtual Double_t GradientPar(Int_t ipar, const Double_t *x, Double_t eps=0.01);
   virtual void     GradientPar(const Double_t *x, Double_t *grad, Double_t eps=0.01);
   virtual void     InitArgs(const Double_t *x, const Double_t *params);
   static  void     InitStandardFunctions();
   virtual Double_t Integral(Double_t a, Double_t b, Double_t epsrel=1.e-12);
   virtual Double_t IntegralOneDim(Double_t a, Double_t b, Double_t epsrel, Double_t epsabs, Double_t &err);
   virtual Double_t IntegralError(Double_t a, Double_t b, const Double_t *params=0, const Double_t *covmat=0, Double_t epsilon=1.E-2);
   virtual Double_t IntegralError(Int_t n, const Double_t * a, const Double_t * b, const Double_t *params=0, const Double_t *covmat=0, Double_t epsilon=1.E-2);
   // virtual Double_t IntegralFast(const TGraph *g, Double_t a, Double_t b, Double_t *params=0);
   virtual Double_t IntegralFast(Int_t num, Double_t *x, Double_t *w, Double_t a, Double_t b, Double_t *params=0, Double_t epsilon=1e-12);
   virtual Double_t IntegralMultiple(Int_t n, const Double_t *a, const Double_t *b, Int_t maxpts, Double_t epsrel, Double_t epsabs ,Double_t &relerr,Int_t &nfnevl, Int_t &ifail);
   virtual Double_t IntegralMultiple(Int_t n, const Double_t *a, const Double_t *b, Int_t /*minpts*/, Int_t maxpts, Double_t epsrel, Double_t &relerr,Int_t &nfnevl, Int_t &ifail) {
      return  IntegralMultiple(n,a,b,maxpts, epsrel, epsrel, relerr, nfnevl, ifail);
   }
   virtual Double_t IntegralMultiple(Int_t n, const Double_t *a, const Double_t *b, Double_t epsrel, Double_t &relerr);
   virtual Bool_t   IsEvalNormalized() const { return fNormalized; }
   /// return kTRUE if the point is inside the function range
   virtual Bool_t   IsInside(const Double_t *x) const { return !(  ( x[0] < fXmin) || ( x[0] > fXmax ) ); }
   virtual Bool_t   IsLinear() const { return (fFormula) ? fFormula->IsLinear() : false;}
   virtual Bool_t   IsValid() const;
   virtual void     Print(Option_t *option="") const;
   virtual void     Paint(Option_t *option="");
   virtual void     ReleaseParameter(Int_t ipar);
   virtual void     Save(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Double_t zmin, Double_t zmax);
   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual void     SetChisquare(Double_t chi2) {fChisquare = chi2;}
   virtual void     SetFitResult(const ROOT::Fit::FitResult & result, const Int_t * indpar = 0);
   template <class PtrObj, typename MemFn>
   void SetFunction( PtrObj& p, MemFn memFn );
   template <typename Func>
   void SetFunction( Func f );
   virtual void     SetMaximum(Double_t maximum=-1111); // *MENU*
   virtual void     SetMinimum(Double_t minimum=-1111); // *MENU*
   virtual void     SetNDF(Int_t ndf);
   virtual void     SetNumberFitPoints(Int_t npfits) {fNpfits = npfits;}
   virtual void     SetNormalized(Bool_t flag) { fNormalized = flag; Update(); }
   virtual void     SetNpx(Int_t npx=100); // *MENU* 如果取点太少（也就是bin太大），图上显示的就是折线图连成的曲线，效果不好。为了曲线光滑，需要将区间分成尽量多的份数。
   virtual void     SetParameter(Int_t param, Double_t value) {
      (fFormula) ? fFormula->SetParameter(param,value) : fParams->SetParameter(param,value);
      Update();
   }
   virtual void     SetParameter(const TString &name, Double_t value) {
      (fFormula) ? fFormula->SetParameter(name,value) : fParams->SetParameter(name,value);
      Update();
   }
   virtual void     SetParameters(const Double_t *params) {
      (fFormula) ? fFormula->SetParameters(params) : fParams->SetParameters(params);
      Update(); 
   }
   virtual void     SetParameters(Double_t p0,Double_t p1,Double_t p2=0,Double_t p3=0,Double_t p4=0,
                                     Double_t p5=0,Double_t p6=0,Double_t p7=0,Double_t p8=0,
                                     Double_t p9=0,Double_t p10=0) {
      if (fFormula) fFormula->SetParameters(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);
      else          fParams->SetParameters(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);
      Update();
   } // *MENU*
   virtual void     SetParName(Int_t ipar, const char *name);
   virtual void     SetParNames(const char *name0="p0",const char *name1="p1",const char *name2="p2",
                                const char *name3="p3",const char *name4="p4", const char *name5="p5",
                                const char *name6="p6",const char *name7="p7",const char *name8="p8",
                                const char *name9="p9",const char *name10="p10"); // *MENU*
   virtual void     SetParError(Int_t ipar, Double_t error);
   virtual void     SetParErrors(const Double_t *errors);
   virtual void     SetParLimits(Int_t ipar, Double_t parmin, Double_t parmax);
   virtual void     SetParent(TObject *p=0) {fParent = p;}
   virtual void     SetRange(Double_t xmin, Double_t xmax); // *MENU*
   virtual void     SetRange(Double_t xmin, Double_t ymin,  Double_t xmax, Double_t ymax);
   virtual void     SetRange(Double_t xmin, Double_t ymin, Double_t zmin,  Double_t xmax, Double_t ymax, Double_t zmax);
   virtual void     SetSavedPoint(Int_t point, Double_t value);
   virtual void     SetTitle(const char *title=""); // *MENU*
   virtual void     Update();

   static  TF1     *GetCurrent();
   static  void     AbsValue(Bool_t reject=kTRUE);
/// Static function: set the fgAbsValue flag.
/// By default TF1::Integral uses the original function value to compute the integral
/// However, TF1::Moment, CentralMoment require to compute the integral
/// using the absolute value of the function.

   static  void     RejectPoint(Bool_t reject=kTRUE);
   static  Bool_t   RejectedPoint();
   static  void     SetCurrent(TF1 *f1);

   //Moments
   virtual Double_t Moment(Double_t n, Double_t a, Double_t b, const Double_t *params=0, Double_t epsilon=0.000001);
   virtual Double_t CentralMoment(Double_t n, Double_t a, Double_t b, const Double_t *params=0, Double_t epsilon=0.000001);
   virtual Double_t Mean(Double_t a, Double_t b, const Double_t *params=0, Double_t epsilon=0.000001) {return Moment(1,a,b,params,epsilon);}
   virtual Double_t Variance(Double_t a, Double_t b, const Double_t *params=0, Double_t epsilon=0.000001) {return CentralMoment(2,a,b,params,epsilon);}

   //some useful static utility functions to compute sampling points for Integral
   //static  void     CalcGaussLegendreSamplingPoints(TGraph *g, Double_t eps=3.0e-11);
   //static  TGraph  *CalcGaussLegendreSamplingPoints(Int_t num=21, Double_t eps=3.0e-11);
   static  void     CalcGaussLegendreSamplingPoints(Int_t num, Double_t *x, Double_t *w, Double_t eps=3.0e-11);
```

一维直方图拟合参数选项：

```cpp
TFitResultPtr TH1::Fit(const char *fname ,Option_t *option ,Option_t *goption, Double_t xxmin, Double_t xxmax);
TFitResultPtr TH1::Fit(TF1 *f1 ,Option_t *option ,Option_t *goption, Double_t xxmin, Double_t xxmax);
//      The list of fit options is given in parameter option.
//         option = "W"  Set all weights to 1 for non empty bins; ignore error bars
//                = "WW" Set all weights to 1 including empty bins; ignore error bars
//                = "I"  Use integral of function in bin, normalized by the bin volume,
//                       instead of value at bin center
//                = "L"  Use Loglikelihood method (default is chisquare method)
//                = "WL" Use Loglikelihood method and bin contents are not integer,
//                       i.e. histogram is weighted (must have Sumw2() set)
//                = "U"  Use a User specified fitting algorithm (via SetFCN)
//                = "Q"  Quiet mode (minimum printing)
//                = "V"  Verbose mode (default is between Q and V)
//                = "E"  Perform better Errors estimation using Minos technique
//                = "B"  User defined parameter settings are used for predefined functions
//                       like "gaus", "expo", "poln", "landau".
//                       Use this option when you want to fix one or more parameters for these functions.
//                = "M"  More. Improve fit results.
//                       It uses the IMPROVE command of TMinuit (see TMinuit::mnimpr).
//                       This algorithm attempts to improve the found local minimum by searching for a
//                       better one.
//                = "R"  Use the Range specified in the function range
//                = "N"  Do not store the graphics function, do not draw
//                = "0"  Do not plot the result of the fit. By default the fitted function
//                       is drawn unless the option"N" above is specified.
//                = "+"  Add this new fitted function to the list of fitted functions
//                       (by default, any previous function is deleted)
//                = "C"  In case of linear fitting, don't calculate the chisquare
//                       (saves time)
//                = "F"  If fitting a polN, switch to minuit fitter
//                = "S"  The result of the fit is returned in the TFitResultPtr
//                       (see below Access to the Fit Result)
//
//      When the fit is drawn (by default), the parameter goption may be used
//      to specify a list of graphics options. See TH1::Draw for a complete
//      list of these options.
//
//      In order to use the Range option, one must first create a function
//      with the expression to be fitted. For example, if your histogram
//      has a defined range between -4 and 4 and you want to fit a gaussian
//      only in the interval 1 to 3, you can do:
//           TF1 *f1 = new TF1("f1", "gaus", 1, 3);
//           histo->Fit("f1", "R");
//
//      Setting initial conditions
//      ==========================
//      Parameters must be initialized before invoking the Fit function.
//      The setting of the parameter initial values is automatic for the
//      predefined functions : poln, expo, gaus, landau. One can however disable
//      this automatic computation by specifying the option "B".
//      Note that if a predefined function is defined with an argument,
//      eg, gaus(0), expo(1), you must specify the initial values for
//      the parameters.
//      You can specify boundary limits for some or all parameters via
//           f1->SetParLimits(p_number, parmin, parmax);
//      if parmin>=parmax, the parameter is fixed
//      Note that you are not forced to fix the limits for all parameters.
//      For example, if you fit a function with 6 parameters, you can do:
//        func->SetParameters(0, 3.1, 1.e-6, -8, 0, 100);
//        func->SetParLimits(3, -10, -4);
//        func->FixParameter(4, 0);
//        func->SetParLimits(5, 1, 1);
//      With this setup, parameters 0->2 can vary freely
//      Parameter 3 has boundaries [-10,-4] with initial value -8
//      Parameter 4 is fixed to 0
//      Parameter 5 is fixed to 100.
//      When the lower limit and upper limit are equal, the parameter is fixed.
//      However to fix a parameter to 0, one must call the FixParameter function.
//
//      Note that option "I" gives better results but is slower.
//
//
//     Changing the fitting objective function
//     =======================================
//     By default a chi square function is used for fitting. When option "L" (or "LL") is used
//     a Poisson likelihood function (see note below) is used.
//     The functions are defined in the header Fit/Chi2Func.h or Fit/PoissonLikelihoodFCN and they
//     are implemented using the routines FitUtil::EvaluateChi2 or FitUtil::EvaluatePoissonLogL in
//     the file math/mathcore/src/FitUtil.cxx.
//     To specify a User defined fitting function, specify option "U" and
//     call the following functions:
//       TVirtualFitter::Fitter(myhist)->SetFCN(MyFittingFunction)
//     where MyFittingFunction is of type:
//     extern void MyFittingFunction(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
//
//     Chi2 Fits
//     =========
//     By default a chi2 (least-square) fit is performed on the histogram. The so-called modified least-square method
//     is used where the residual for each bin is computed using as error the observed value (the bin error)
//
//     Chi2 = Sum{ ( y(i) - f (x(i) | p )/ e(i) )^2 }
//
//     where y(i) is the bin content for each bin i, x(i) is the bin center and e(i) is the bin error (sqrt(y(i) for
//     an un-weighted histogram. Bins with zero errors are excluded from the fit. See also later the note on the treatment of empty bins.
//     When using option "I" the residual is computed not using the function value at the bin center, f (x(i) | p), but the integral
//     of the function in the bin,   Integral{ f(x|p)dx } divided by the bin volume
//
//     Likelihood Fits
//     ===============
//     When using option "L" a likelihood fit is used instead of the default chi2 square fit.
//     The likelihood is built assuming a Poisson probability density function for each bin.
//     The negative log-likelihood to be minimized is
//      NLL = Sum{ log Poisson( y(i) |{ f(x(i) | p ) ) }
//     The exact likelihood used is the Poisson likelihood described in this paper:
//     S. Baker and R. D. Cousins, “Clarification of the use of chi-square and likelihood functions in fits to histograms,”
//     Nucl. Instrum. Meth. 221 (1984) 437.
//     This method can then be used only when the bin content represents counts (i.e. errors are sqrt(N) ).
//     The likelihood method has the advantage of treating correctly bins with low statistics. In case of high
//     statistics/bin the distribution of the bin content becomes a normal distribution and the likelihood and chi2 fit
//     give the same result.
//     The likelihood method, although a bit slower, it is therefore the recommended method in case of low
//     bin statistics, where the chi2 method may give incorrect results, in particular when there are
//     several empty bins (see also below).
//     In case of a weighted histogram, it is possible to perform a likelihood fit by using the
//     option "WL". Note a weighted histogram is an histogram which has been filled with weights and it
//     contains the sum of the weight square ( TH1::Sumw2() has been called). The bin error for a weighted
//     histogram is the square root of the sum of the weight square.
//
//     Treatment of Empty Bins
//     =======================
//
//     Empty bins, which have the content equal to zero AND error equal to zero,
//     are excluded by default from the chisquare fit, but they are considered in the likelihood fit.
//     since they affect the likelihood if the function value in these bins is not negligible.
//     When using option "WW" these bins will be considered in the chi2 fit with an error of 1.
//     Note that if the histogram is having bins with zero content and non zero-errors they are considered as
//     any other bins in the fit. Instead bins with zero error and non-zero content are excluded in the chi2 fit.
//     A likelihood fit should also not be peformed on such an histogram, since we are assuming a wrong pdf for each bin.
//     In general, one should not fit an histogram with non-empty bins and zero errors, apart if all the bins have zero errors.
//     In this case one could use the option "w", which gives a weight=1 for each bin (unweighted least-square fit).
//
//     Fitting a histogram of dimension N with a function of dimension N-1
//     ===================================================================
//     It is possible to fit a TH2 with a TF1 or a TH3 with a TF2.
//     In this case the option "Integral" is not allowed and each cell has
//     equal weight.
//
//     Associated functions
//     ====================
//     One or more object (typically a TF1*) can be added to the list
//     of functions (fFunctions) associated to each histogram.
//     When TH1::Fit is invoked, the fitted function is added to this list.
//     Given an histogram h, one can retrieve an associated function
//     with:  TF1 *myfunc = h->GetFunction("myfunc");
//
//     Access to the fit result
//     ========================
//     The function returns a TFitResultPtr which can hold a  pointer to a TFitResult object.
//     By default the TFitResultPtr contains only the status of the fit which is return by an
//     automatic conversion of the TFitResultPtr to an integer. One can write in this case directly:
//     Int_t fitStatus =  h->Fit(myFunc)
//
//     If the option "S" is instead used, TFitResultPtr contains the TFitResult and behaves as a smart
//     pointer to it. For example one can do:
//     TFitResultPtr r = h->Fit(myFunc,"S");
//     TMatrixDSym cov = r->GetCovarianceMatrix();  //  to access the covariance matrix
//     Double_t chi2   = r->Chi2(); // to retrieve the fit chi2
//     Double_t par0   = r->Parameter(0); // retrieve the value for the parameter 0
//     Double_t err0   = r->ParError(0); // retrieve the error for the parameter 0
//     r->Print("V");     // print full information of fit including covariance matrix
//     r->Write();        // store the result in a file
//
//     The fit parameters, error and chi2 (but not covariance matrix) can be retrieved also
//     from the fitted function.
//     If the histogram is made persistent, the list of
//     associated functions is also persistent. Given a pointer (see above)
//     to an associated function myfunc, one can retrieve the function/fit
//     parameters with calls such as:
//       Double_t chi2 = myfunc->GetChisquare();
//       Double_t par0 = myfunc->GetParameter(0); //value of 1st parameter
//       Double_t err0 = myfunc->GetParError(0);  //error on first parameter
//
//     Access to the fit status
//     ========================
//     The status of the fit can be obtained converting the TFitResultPtr to an integer
//     independently if the fit option "S" is used or not:
//     TFitResultPtr r = h->Fit(myFunc,opt);
//     Int_t fitStatus = r;
//
//     The fitStatus is 0 if the fit is OK (i.e no error occurred).
//     The value of the fit status code is negative in case of an error not connected with the
//     minimization procedure, for example  when a wrong function is used.
//     Otherwise the return value is the one returned from the minimization procedure.
//     When TMinuit (default case) or Minuit2 are used as minimizer the status returned is :
//     fitStatus =  migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult.
//     TMinuit will return 0 (for migrad, minos, hesse or improve) in case of success and 4 in
//     case of error (see the documentation of TMinuit::mnexcm). So for example, for an error
//     only in Minos but not in Migrad a fitStatus of 40 will be returned.
//     Minuit2 will return also 0 in case of success and different values in migrad minos or
//     hesse depending on the error. See in this case the documentation of
//     Minuit2Minimizer::Minimize for the migradResult, Minuit2Minimizer::GetMinosError for the
//     minosResult and Minuit2Minimizer::Hesse for the hesseResult.
//     If other minimizers are used see their specific documentation for the status code returned.
//     For example in the case of Fumili, for the status returned see TFumili::Minimize.
//
//     Excluding points
//     ================
//     Use TF1::RejectPoint inside your fitting function to exclude points
//     within a certain range from the fit. Example:
//     Double_t fline(Double_t *x, Double_t *par)
//     {
//         if (x[0] > 2.5 && x[0] < 3.5) {
//           TF1::RejectPoint();
//           return 0;
//        }
//        return par[0] + par[1]*x[0];
//     }
//
//     void exclude() {
//        TF1 *f1 = new TF1("f1", "[0] +[1]*x +gaus(2)", 0, 5);
//        f1->SetParameters(6, -1,5, 3, 0.2);
//        TH1F *h = new TH1F("h", "background + signal", 100, 0, 5);
//        h->FillRandom("f1", 2000);
//        TF1 *fline = new TF1("fline", fline, 0, 5, 2);
//        fline->SetParameters(2, -1);
//        h->Fit("fline", "l");
//     }
//
//     Warning when using the option "0"
//     =================================
//     When selecting the option "0", the fitted function is added to
//     the list of functions of the histogram, but it is not drawn.
//     You can undo what you disabled in the following way:
//       h.Fit("myFunction", "0"); // fit, store function but do not draw
//       h.Draw(); function is not drawn
//       const Int_t kNotDraw = 1<<9;
//       h.GetFunction("myFunction")->ResetBit(kNotDraw);
//       h.Draw();  // function is visible again
//
//     Access to the Minimizer information during fitting
//     ==================================================
//     This function calls, the ROOT::Fit::FitObject function implemented in HFitImpl.cxx
//     which uses the ROOT::Fit::Fitter class. The Fitter class creates the objective fuction
//     (e.g. chi2 or likelihood) and uses an implementation of the  Minimizer interface for minimizing
//     the function.
//     The default minimizer is Minuit (class TMinuitMinimizer which calls TMinuit).
//     The default  can be set in the resource file in etc/system.rootrc. For example
//     Root.Fitter:      Minuit2
//     A different fitter can also be set via ROOT::Math::MinimizerOptions::SetDefaultMinimizer
//     (or TVirtualFitter::SetDefaultFitter).
//     For example ROOT::Math::MinimizerOptions::SetDefaultMinimizer("GSLMultiMin","BFGS");
//     will set the usdage of the BFGS algorithm of the GSL multi-dimensional minimization
//     (implemented in libMathMore). ROOT::Math::MinimizerOptions can be used also to set other
//     default options, like maximum number of function calls, minimization tolerance or print
//     level. See the documentation of this class.
//
//     For fitting linear functions (containing the "++" sign" and polN functions,
//     the linear fitter is automatically initialized.
```


## code

```cpp
TF1 *f1=new TF1("aaaaa","f(x)",min,max);
TF2 *f2=new TF2("aaaaa","f(x,y)",x min,x max,y min,y max);
```

```cpp
// inline expression using standard C++ functions/operators
// inline expression using a ROOT function (e.g. from TMath) without parameters
TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10); 
fa1->Draw();

TF1 *fa2 = new TF1("fa2","TMath::DiLog(x)",0,10); 
fa2->Draw();
```

```cpp
// inline expression using a user defined CLING function by name
Double_t myFunc(x) { return x+sin(x); } 
// ....
TF1 *fa3 = new TF1("fa3","myFunc(x)",-3,5); 
fa3->Draw();
```

```cpp
TF1 *fa = new TF1("fa","[0]*x*sin([1]*x)",-3,3);
fa->SetParameter(0,value_first_parameter);
fa->SetParameter(1,value_second_parameter);
fa->SetParName(0,"Constant");// Parameters may be given a name:
```

```cpp
TCanvas *c = new TCanvas("c","c",0,0,500,300);
TF1 *fb2 = new TF1("fa3","TMath::Landau(x,[0],[1],0)",-5,10); 
fb2->SetParameters(0.2,1.3); fb2->Draw(); 
```

```cpp
// A lambda expression with variables and parameters **(NEW)**
// TF1 now supports using lambda expressions in the formula. This allows, by using a full C++ syntax the full power of lambda functions and still mantain the capability of storing the function in a file which cannot be done with funciton pointer or lambda written not as expression, but as code (see items belows). 
// Example on how using lambda to define a sum of two functions. Note that is necessary to provide the number of parameters
TF1 f1("f1","sin(x)",0,10);
TF1 f2("f2","cos(x)",0,10);
TF1 fsum("f1","[&](double *x, double *p){ return p[0]*f1(x) + p[1]*f2(x); }",0,10,2); 
```


## example

```cpp
   Double_t myfunction(Double_t *x, Double_t *par)
   {
      Float_t xx =x[0];
      Double_t f = TMath::Abs(par[0]*sin(par[1]*xx)/xx);
      return f;
   }
   void myfunc()
   {
      TF1 *f1 = new TF1("myfunc",myfunction,0,10,2);
      f1->SetParameters(2,1);
      f1->SetParNames("constant","coefficient");
      f1->Draw();
   }
   void myfit()
   {
      TH1F *h1=new TH1F("h1","test",100,0,10);
      h1->FillRandom("myfunc",20000);
      TF1 *f1=gROOT->GetFunction("myfunc");
      f1->SetParameters(800,1);
      h1->Fit("myfunc");
   }
```

```cpp
   void gint() {
      TF1 *g = new TF1("g","gaus",-5,5);
      g->SetParameters(1,0,1);
      //default gaus integration method uses 6 points
      //not suitable to integrate on a large domain
      double r1 = g->Integral(0,5);
      double r2 = g->Integral(0,1000);

      //try with user directives computing more points
      Int_t np = 1000;
      double *x=new double[np];
      double *w=new double[np];
      g->CalcGaussLegendreSamplingPoints(np,x,w,1e-15);
      double r3 = g->IntegralFast(np,x,w,0,5);
      double r4 = g->IntegralFast(np,x,w,0,1000);
      double r5 = g->IntegralFast(np,x,w,0,10000);
      double r6 = g->IntegralFast(np,x,w,0,100000);
      printf("g->Integral(0,5)               = %g\n",r1);
      printf("g->Integral(0,1000)            = %g\n",r2);
      printf("g->IntegralFast(n,x,w,0,5)     = %g\n",r3);
      printf("g->IntegralFast(n,x,w,0,1000)  = %g\n",r4);
      printf("g->IntegralFast(n,x,w,0,10000) = %g\n",r5);
      printf("g->IntegralFast(n,x,w,0,100000)= %g\n",r6);
      delete [] x;
      delete [] w;
   }
///   This example produces the following results:
///
///      g->Integral(0,5)               = 1.25331
///      g->Integral(0,1000)            = 1.25319
///      g->IntegralFast(n,x,w,0,5)     = 1.25331
///      g->IntegralFast(n,x,w,0,1000)  = 1.25331
///      g->IntegralFast(n,x,w,0,10000) = 1.25331
///      g->IntegralFast(n,x,w,0,100000)= 1.253
```




<!-- TF1.md ends here -->
