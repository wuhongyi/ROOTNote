// note.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 3月 14 09:17:11 2015 (+0800)
// Last-Updated: 日 3月 27 20:49:46 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 5
// URL: http://wuhongyi.github.io 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TF1.h

TF1(const char *name, void *fcn, Double_t xmin, Double_t xmax, Int_t npar);//fcn为自己定义的函数曲线，npar为调用的参数个数

virtual Double_t Eval(Double_t x, Double_t y=0, Double_t z=0, Double_t t=0) const;//通过变量x获得其函数返回值

TH1     *GetHistogram() const;//将其转为TH1类型

virtual Int_t    GetNpx() const {return fNpx;}//获得区间分成份数

virtual Double_t GetX(Double_t y, Double_t xmin=0, Double_t xmax=0, Double_t epsilon = 1.E-10, Int_t maxiter = 100, Bool_t logx = false) const;//由y找x

virtual void     SetNpx(Int_t npx=100); // *MENU* 如果取点太少（也就是bin太大），图上显示的就是折线图连成的曲线，效果不好。为了曲线光滑，需要将区间分成尽量多的份数。

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


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TGraph.h

virtual Int_t         IsInside(Double_t x, Double_t y) const;//判断（x，y）是否在TCut选定的范围

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1.h

virtual Bool_t   Add(const TH1 *h, const TH1 *h2, Double_t c1=1, Double_t c2=1); // *MENU* 两个TH1相加

virtual void     Draw(Option_t *option="");//画图

virtual Int_t    Fill(Double_t x);//将数据填充进直方图
virtual Int_t    Fill(Double_t x, Double_t w);
virtual Int_t    Fill(const char *name, Double_t w);
virtual void     FillN(Int_t ntimes, const Double_t *x, const Double_t *w, Int_t stride=1);
virtual void     FillN(Int_t, const Double_t *, const Double_t *, const Double_t *, Int_t) {;}
virtual void     FillRandom(const char *fname, Int_t ntimes=5000);
virtual void     FillRandom(TH1 *h, Int_t ntimes=5000);
virtual Int_t    FindBin(Double_t x, Double_t y=0, Double_t z=0);

virtual void     Reset(Option_t *option="");//将其清除重置

virtual void     Scale(Double_t c1=1, Option_t *option="");//比例缩放

virtual Int_t    GetNbinsX() const {return fXaxis.GetNbins();}//获取轴bin值
virtual Int_t    GetNbinsY() const {return fYaxis.GetNbins();}
virtual Int_t    GetNbinsZ() const {return fZaxis.GetNbins();}


//ROOT 6
virtual Double_t *GetIntegral();//TH1积分，当前bin值为前面所有bin的累积，然后归一化（最大值为1），返回该数组

TH1             *GetCumulative(Bool_t forward = kTRUE, const char* suffix = "_cumulative") const;//TH1积分，当前bin值为前面所有bin的累积。

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 
// note.hh ends here
