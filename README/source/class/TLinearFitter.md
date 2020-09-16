<!-- TLinearFitter.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 14:25:40 2016 (+0800)
;; Last-Updated: 三 9月 16 12:47:00 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TLinearFitter*

The Linear Fitter - fitting functions that are LINEAR IN PARAMETERS

```cpp
// Linear fitter is used to fit a set of data points with a linear
// combination of specified functions. Note, that "linear" in the name
// stands only for the model dependency on parameters, the specified
// functions can be nonlinear.
// The general form of this kind of model is
//
//          y(x) = a[0] + a[1]*f[1](x)+...a[n]*f[n](x)
//
// Functions f are fixed functions of x. For example, fitting with a
// polynomial is linear fitting in this sense.
//
//                         The fitting method
//
// The fit is performed using the Normal Equations method with Cholesky
// decomposition.
//
//                         Why should it be used?
//
// The linear fitter is considerably faster than general non-linear
// fitters and doesn't require to set the initial values of parameters.
//
//                          Using the fitter:
//
// 1.Adding the data points:
//  1.1 To store or not to store the input data?
//      - There are 2 options in the constructor - to store or not
//        store the input data. The advantages of storing the data
//        are that you'll be able to reset the fitting model without
//        adding all the points again, and that for very large sets
//        of points the chisquare is calculated more precisely.
//        The obvious disadvantage is the amount of memory used to
//        keep all the points.
//      - Before you start adding the points, you can change the
//        store/not store option by StoreData() method.
//  1.2 The data can be added:
//      - simply point by point - AddPoint() method
//      - an array of points at once:
//        If the data is already stored in some arrays, this data
//        can be assigned to the linear fitter without physically
//        coping bytes, thanks to the Use() method of
//        TVector and TMatrix classes - AssignData() method
//
// 2.Setting the formula
//  2.1 The linear formula syntax:
//      -Additive parts are separated by 2 plus signes "++"
//       --for example "1 ++ x" - for fitting a straight line
//      -All standard functions, undrestood by TFormula, can be used
//       as additive parts
//       --TMath functions can be used too
//      -Functions, used as additive parts, shouldn't have any parameters,
//       even if those parameters are set.
//       --for example, if normalizing a sum of a gaus(0, 1) and a
//         gaus(0, 2), don't use the built-in "gaus" of TFormula,
//         because it has parameters, take TMath::Gaus(x, 0, 1) instead.
//      -Polynomials can be used like "pol3", .."polN"
//      -If fitting a more than 3-dimensional formula, variables should
//       be numbered as follows:
//       -- x0, x1, x2... For example, to fit  "1 ++ x0 ++ x1 ++ x2 ++ x3*x3"
//  2.2 Setting the formula:
//    2.2.1 If fitting a 1-2-3-dimensional formula, one can create a
//          TF123 based on a linear expression and pass this function
//          to the fitter:
//          --Example:
//            TLinearFitter *lf = new TLinearFitter();
//            TF2 *f2 = new TF2("f2", "x ++ y ++ x*x*y*y", -2, 2, -2, 2);
//            lf->SetFormula(f2);
//          --The results of the fit are then stored in the function,
//            just like when the TH1::Fit or TGraph::Fit is used
//          --A linear function of this kind is by no means different
//            from any other function, it can be drawn, evaluated, etc.
//    2.2.2 There is no need to create the function if you don't want to,
//          the formula can be set by expression:
//          --Example:
//            // 2 is the number of dimensions
//            TLinearFitter *lf = new TLinearFitter(2);
//            lf->SetFormula("x ++ y ++ x*x*y*y");
//          --That's the only way to go, if you want to fit in more
//            than 3 dimensions
//    2.2.3 The fastest functions to compute are polynomials and hyperplanes.
//          --Polynomials are set the usual way: "pol1", "pol2",...
//          --Hyperplanes are set by expression "hyp3", "hyp4", ...
//          ---The "hypN" expressions only work when the linear fitter
//             is used directly, not through TH1::Fit or TGraph::Fit.
//             To fit a graph or a histogram with a hyperplane, define
//             the function as "1++x++y".
//          ---A constant term is assumed for a hyperplane, when using
//             the "hypN" expression, so "hyp3" is in fact fitting with
//             "1++x++y++z" function.
//          --Fitting hyperplanes is much faster than fitting other
//            expressions so if performance is vital, calculate the
//            function values beforehand and give them to the fitter
//            as variables
//          --Example:
//            You want to fit "sin(x)|cos(2*x)" very fast. Calculate
//            sin(x) and cos(2*x) beforehand and store them in array *data.
//            Then:
//            TLinearFitter *lf=new TLinearFitter(2, "hyp2");
//            lf->AssignData(npoint, 2, data, y);
//
//  2.3 Resetting the formula
//    2.3.1 If the input data is stored (or added via AssignData() function),
//          the fitting formula can be reset without re-adding all the points.
//          --Example:
//            TLinearFitter *lf=new TLinearFitter("1++x++x*x");
//            lf->AssignData(n, 1, x, y, e);
//            lf->Eval()
//            //looking at the parameter significance, you see,
//            // that maybe the fit will improve, if you take out
//            // the constant term
//            lf->SetFormula("x++x*x");
//            lf->Eval();
//            ...
//    2.3.2 If the input data is not stored, the fitter will have to be
//          cleared and the data will have to be added again to try a
//          different formula.
//
// 3.Accessing the fit results
//  3.1 There are methods in the fitter to access all relevant information:
//      --GetParameters, GetCovarianceMatrix, etc
//      --the t-values of parameters and their significance can be reached by
//        GetParTValue() and GetParSignificance() methods
//  3.2 If fitting with a pre-defined TF123, the fit results are also
//      written into this function.
```

TLinearFitter 继承 TVirtualFitter

## class

```cpp
   TLinearFitter();
///default c-tor, input data is stored
///If you don't want to store the input data,
///run the function StoreData(kFALSE) after constructor

   TLinearFitter(Int_t ndim, const char *formula, Option_t *opt="D");
///First parameter stands for number of dimensions in the fitting formula
///Second parameter is the fitting formula: see class description for formula syntax
///Options:
///The option is to store or not to store the data
///If you don't want to store the data, choose "" for the option, or run
///StoreData(kFalse) member function after the constructor

   TLinearFitter(Int_t ndim);
///The parameter stands for number of dimensions in the fitting formula
///The input data is stored. If you don't want to store the input data,
///run the function StoreData(kFALSE) after constructor

   TLinearFitter(TFormula *function, Option_t *opt="D");
///This constructor uses a linear function. How to create it?
///TFormula now accepts formulas of the following kind:
///TFormula("f", "x++y++z++x*x") or
///TFormula("f", "x[0]++x[1]++x[2]*x[2]");
///Other than the look, it's in no
///way different from the regular formula, it can be evaluated,
///drawn, etc.
///The option is to store or not to store the data
///If you don't want to store the data, choose "" for the option, or run
///StoreData(kFalse) member function after the constructor

   TLinearFitter(const TLinearFitter& tlf);
   virtual ~TLinearFitter();

   TLinearFitter& operator=(const TLinearFitter& tlf);
   virtual void       Add(TLinearFitter *tlf);
///Add another linear fitter to this linear fitter. Points and Design matrices
///are added, but the previos fitting results (if any) are deleted.
///Fitters must have same formulas (this is not checked). Fixed parameters are not changed

   virtual void       AddPoint(Double_t *x, Double_t y, Double_t e=1);
///Adds 1 point to the fitter.
///First parameter stands for the coordinates of the point, where the function is measured
///Second parameter - the value being fitted
///Third parameter - weight(measurement error) of this point (=1 by default)

   virtual void       AddTempMatrices();
   virtual void       AssignData(Int_t npoints, Int_t xncols, Double_t *x, Double_t *y, Double_t *e=0);
///This function is to use when you already have all the data in arrays
///and don't want to copy them into the fitter. In this function, the Use() method
///of TVectorD and TMatrixD is used, so no bytes are physically moved around.
///First parameter - number of points to fit
///Second parameter - number of variables in the model
///Third parameter - the variables of the model, stored in the following way:
///(x0(0), x1(0), x2(0), x3(0), x0(1), x1(1), x2(1), x3(1),...

   virtual void       Clear(Option_t *option="");///Clears everything. Used in TH1::Fit and TGraph::Fit().
   virtual void       ClearPoints();///To be used when different sets of points are fitted with the same formula.
   virtual void       Chisquare();///Calculates the chisquare.
   virtual Int_t      Eval();
/// Perform the fit and evaluate the parameters
/// Returns 0 if the fit is ok, 1 if there are errors

   virtual Int_t      EvalRobust(Double_t h=-1);
///Finds the parameters of the fitted function in case data contains
///outliers.
///Parameter h stands for the minimal fraction of good points in the
///dataset (h < 1, i.e. for 70% of good points take h=0.7).
///The default value of h*Npoints is  (Npoints + Nparameters+1)/2
///If the user provides a value of h smaller than above, default is taken
///See class description for the algorithm details

   virtual Int_t      ExecuteCommand(const char *command, Double_t *args, Int_t nargs);
///To use in TGraph::Fit and TH1::Fit().

   virtual void       FixParameter(Int_t ipar);///Fixes paramter #ipar at its current value.
   virtual void       FixParameter(Int_t ipar, Double_t parvalue);///Fixes parameter #ipar at value parvalue.
   virtual void       GetAtbVector(TVectorD &v);///Get the Atb vector - a vector, used for internal computations
   virtual Double_t   GetChisquare();/// Get the Chisquare.
   virtual void       GetConfidenceIntervals(Int_t n, Int_t ndim, const Double_t *x, Double_t *ci, Double_t cl=0.95);
///Computes point-by-point confidence intervals for the fitted function
///Parameters:
///n - number of points
///ndim - dimensions of points
///x - points, at which to compute the intervals, for ndim > 1
///    should be in order: (x0,y0, x1, y1, ... xn, yn)
///ci - computed intervals are returned in this array
///cl - confidence level, default=0.95
///
///NOTE, that this method can only be used when the fitting function inherits from a TF1,
///so it's not possible when the fitting function was set as a string or as a pure TFormula

   virtual void       GetConfidenceIntervals(TObject *obj, Double_t cl=0.95);
///Computes confidence intervals at level cl. Default is 0.95
///The TObject parameter can be a TGraphErrors, a TGraph2DErrors or a TH123.
///For Graphs, confidence intervals are computed for each point,
///the value of the graph at that point is set to the function value at that
///point, and the graph y-errors (or z-errors) are set to the value of
///the confidence interval at that point
///For Histograms, confidence intervals are computed for each bin center
///The bin content of this bin is then set to the function value at the bin
///center, and the bin error is set to the confidence interval value.
///Allowed combinations:
///Fitted object               Passed object
///TGraph                      TGraphErrors, TH1
///TGraphErrors, AsymmErrors   TGraphErrors, TH1
///TH1                         TGraphErrors, TH1
///TGraph2D                    TGraph2DErrors, TH2
///TGraph2DErrors              TGraph2DErrors, TH2
///TH2                         TGraph2DErrors, TH2
///TH3                         TH3

   virtual Double_t*  GetCovarianceMatrix() const;///Returns covariance matrix
   virtual void       GetCovarianceMatrix(TMatrixD &matr);///Returns covariance matrix
   virtual Double_t   GetCovarianceMatrixElement(Int_t i, Int_t j) const {return fParCovar(i, j);}
   virtual void       GetDesignMatrix(TMatrixD &matr);///Returns the internal design matrix
   virtual void       GetErrors(TVectorD &vpar);///Returns parameter errors
   virtual Int_t      GetNumberTotalParameters() const {return fNfunctions;}
   virtual Int_t      GetNumberFreeParameters() const {return fNfunctions-fNfixed;}
   virtual Int_t      GetNpoints() { return fNpoints; }
   virtual void       GetParameters(TVectorD &vpar);///Returns parameter values
   virtual Double_t   GetParameter(Int_t ipar) const {return fParams(ipar);}
   virtual Int_t      GetParameter(Int_t ipar,char* name,Double_t& value,Double_t& /*verr*/,Double_t& /*vlow*/, Double_t& /*vhigh*/) const;
///Returns the value and the name of the parameter #ipar
///NB: In the calling function the argument name must be set large enough

   virtual const char *GetParName(Int_t ipar) const;///Returns name of parameter #ipar
   virtual Double_t   GetParError(Int_t ipar) const;///Returns the error of parameter #ipar
   virtual Double_t   GetParTValue(Int_t ipar);///Returns the t-value for parameter #ipar
   virtual Double_t   GetParSignificance(Int_t ipar);///Returns the significance of parameter #ipar
   virtual void       GetFitSample(TBits& bits);
///For robust lts fitting, returns the sample, on which the best fit was based

   virtual Double_t   GetY2() const {return fY2;}
   virtual Bool_t     IsFixed(Int_t ipar) const {return fFixedParams[ipar];}
   virtual Int_t      Merge(TCollection *list);///Merge objects in list
   virtual void       PrintResults(Int_t level, Double_t amin=0) const;
   virtual void       ReleaseParameter(Int_t ipar);///Releases parameter #ipar.
   virtual void       SetBasisFunctions(TObjArray * functions);
///set the basis functions in case the fitting function is not
/// set directly
/// The TLinearFitter will manage and delete the functions contained in the list

   virtual void       SetDim(Int_t n);
///set the number of dimensions

   virtual void       SetFormula(const char* formula);
///Additive parts should be separated by "++".
///Examples (ai are parameters to fit):
///1.fitting function: a0*x0 + a1*x1 + a2*x2
///  input formula "x[0]++x[1]++x[2]"
///2.TMath functions can be used:
///  fitting function: a0*TMath::Gaus(x, 0, 1) + a1*y
///  input formula:    "TMath::Gaus(x, 0, 1)++y"
///fills the array of functions

   virtual void       SetFormula(TFormula *function);///Set the fitting function.
   virtual void       StoreData(Bool_t store) {fStoreData=store;}

   virtual Bool_t     UpdateMatrix();///Update the design matrix after the formula has been changed.

   //dummy functions for TVirtualFitter:
   virtual Double_t  Chisquare(Int_t /*npar*/, Double_t * /*params*/) const {return 0;}
   virtual Int_t     GetErrors(Int_t /*ipar*/,Double_t & /*eplus*/, Double_t & /*eminus*/, Double_t & /*eparab*/, Double_t & /*globcc*/) const {return 0;}

   virtual Int_t     GetStats(Double_t& /*amin*/, Double_t& /*edm*/, Double_t& /*errdef*/, Int_t& /*nvpar*/, Int_t& /*nparx*/) const {return 0;}
   virtual Double_t  GetSumLog(Int_t /*i*/) {return 0;}
   virtual void      SetFitMethod(const char * /*name*/) {;}
   virtual Int_t     SetParameter(Int_t /*ipar*/,const char * /*parname*/,Double_t /*value*/,Double_t /*verr*/,Double_t /*vlow*/, Double_t /*vhigh*/) {return 0;}
```

## code



## class




<!-- TLinearFitter.md ends here -->
