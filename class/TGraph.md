<!-- TGraph.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 一 11月  7 21:50:42 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 15
;; URL: http://wuhongyi.cn -->

# TGraph

继承 TNamed, TAttLine, TAttFill, TAttMarker 

## class

```cpp
   // TGraph status bits
   enum {
      kClipFrame     = BIT(10),  // clip to the frame boundary
      kNotEditable   = BIT(18)   // bit set if graph is non editable
   };

   TGraph();/// Graph default constructor.
   TGraph(Int_t n);
/// Constructor with only the number of points set
/// the arrays x and y will be set later

   TGraph(Int_t n, const Int_t *x, const Int_t *y);/// Graph normal constructor with ints.
   TGraph(Int_t n, const Float_t *x, const Float_t *y);/// Graph normal constructor with floats.
   TGraph(Int_t n, const Double_t *x, const Double_t *y);/// Graph normal constructor with doubles.
   TGraph(const TGraph &gr);/// Copy constructor for this graph
   TGraph& operator=(const TGraph&);/// Equal operator for this graph
   TGraph(const TVectorF &vx, const TVectorF &vy);
/// Graph constructor with two vectors of floats in input
/// A graph is build with the X coordinates taken from vx and Y coord from vy
/// The number of points in the graph is the minimum of number of points
/// in vx and vy.

   TGraph(const TVectorD &vx, const TVectorD &vy);
/// Graph constructor with two vectors of doubles in input
/// A graph is build with the X coordinates taken from vx and Y coord from vy
/// The number of points in the graph is the minimum of number of points
/// in vx and vy.

   TGraph(const TH1 *h);/// Graph constructor importing its parameters from the TH1 object passed as argument
   TGraph(const TF1 *f, Option_t *option="");
/// Graph constructor importing its parameters from the TF1 object passed as argument
/// - if option =="" (default), a TGraph is created with points computed
///                at the fNpx points of f.
/// - if option =="d", a TGraph is created with points computed with the derivatives
///                at the fNpx points of f.
/// - if option =="i", a TGraph is created with points computed with the integral
///                at the fNpx points of f.
/// - if option =="I", a TGraph is created with points computed with the integral
///                at the fNpx+1 points of f and the integral is normalized to 1.

   TGraph(const char *filename, const char *format="%lg %lg", Option_t *option="");
/// Graph constructor reading input from filename.
/// filename is assumed to contain at least two columns of numbers.
/// the string format is by default "%lg %lg".
/// this is a standard c formatting for scanf. If columns of numbers should be
/// skipped, a "%*lg" or "%*s" for each column can be added,
/// e.g. "%lg %*lg %lg" would read x-values from the first and y-values from
/// the third column.
/// For files separated by a specific delimiter different from ' ' and '\t' (e.g. ';' in csv files)
/// you can avoid using %*s to bypass this delimiter by explicitly specify the "option" argument,
/// e.g. option=" \t,;" for columns of figures separated by any of these characters (' ', '\t', ',', ';')
/// used once (e.g. "1;1") or in a combined way (" 1;,;;  1").
/// Note in that case, the instantiation is about 2 times slower.

   virtual ~TGraph();/// Graph default destructor.

   virtual void          Apply(TF1 *f);
/// Apply function f to all the data points
/// f may be a 1-D function TF1 or 2-d function TF2
/// The Y values of the graph are replaced by the new values computed
/// using the function

   virtual void          Browse(TBrowser *b);/// Browse
   virtual Double_t      Chisquare(TF1 *f1, Option_t *option="") const;
/// Return the chisquare of this graph with respect to f1.
/// The chisquare is computed as the sum of the quantity below at each point:
/// \f[
///   \frac{(y-f1(x))^{2}}{ey^{2}+(\frac{1}{2}(exl+exh)f1'(x))^{2}}
/// \f]
/// where x and y are the graph point coordinates and f1'(x) is the derivative of function f1(x).
/// This method to approximate the uncertainty in y because of the errors in x, is called
/// "effective variance" method.
/// In case of a pure TGraph, the denominator is 1.
/// In case of a TGraphErrors or TGraphAsymmErrors the errors are taken
/// into account.
/// By default the range of the graph is used whatever function range.
/// Use option "R" to use the function range

   static Bool_t         CompareArg(const TGraph* gr, Int_t left, Int_t right);
/// Return kTRUE if point number "left"'s argument (angle with respect to positive
/// x-axis) is bigger than that of point number "right". Can be used by Sort.

   static Bool_t         CompareX(const TGraph* gr, Int_t left, Int_t right);/// Return kTRUE if fX[left] > fX[right]. Can be used by Sort.
   static Bool_t         CompareY(const TGraph* gr, Int_t left, Int_t right);/// Return kTRUE if fY[left] > fY[right]. Can be used by Sort.
   static Bool_t         CompareRadius(const TGraph* gr, Int_t left, Int_t right);
/// Return kTRUE if point number "left"'s distance to origin is bigger than
/// that of point number "right". Can be used by Sort.

   virtual void          ComputeRange(Double_t &xmin, Double_t &ymin, Double_t &xmax, Double_t &ymax) const; /// Compute the x/y range of the points in this graph
   virtual Int_t         DistancetoPrimitive(Int_t px, Int_t py);
/// Compute distance from point px,py to a graph.
///  Compute the closest distance of approach from point px,py to this line.
///  The distance is computed in pixels units.

   virtual void          Draw(Option_t *chopt="");
/// Draw this graph with its current attributes.
/// The options to draw a graph are described in TGraphPainter class.

   virtual void          DrawGraph(Int_t n, const Int_t *x, const Int_t *y, Option_t *option="");/// Draw this graph with new attributes.
   virtual void          DrawGraph(Int_t n, const Float_t *x, const Float_t *y, Option_t *option="");/// Draw this graph with new attributes.
   virtual void          DrawGraph(Int_t n, const Double_t *x=0, const Double_t *y=0, Option_t *option="");/// Draw this graph with new attributes.
   virtual void          DrawPanel(); // *MENU* /// Display a panel with all graph drawing options.
   virtual Double_t      Eval(Double_t x, TSpline *spline=0, Option_t *option="") const; //通过 x 插值找 y 值，提供多种插值算法：线性插值、光滑插值等
/// Interpolate points in this graph at x using a TSpline
///  -if spline==0 and option="" a linear interpolation between the two points
///   close to x is computed. If x is outside the graph range, a linear
///   extrapolation is computed.
///  -if spline==0 and option="S" a TSpline3 object is created using this graph
///   and the interpolated value from the spline is returned.
///   the internally created spline is deleted on return.
///  -if spline is specified, it is used to return the interpolated value.

   virtual void          ExecuteEvent(Int_t event, Int_t px, Int_t py);
/// Execute action corresponding to one event.
///  This member function is called when a graph is clicked with the locator
///  If Left button clicked on one of the line end points, this point
///     follows the cursor until button is released.
///  if Middle button clicked, the line is moved parallel to itself
///     until the button is released.

   virtual void          Expand(Int_t newsize);/// If array sizes <= newsize, expand storage to 2*newsize.
   virtual void          Expand(Int_t newsize, Int_t step);
/// If graph capacity is less than newsize points then make array sizes
/// equal to least multiple of step to contain newsize points.
/// Returns kTRUE if size was altered

   virtual TObject      *FindObject(const char *name) const;/// Search object named name in the list of functions
   virtual TObject      *FindObject(const TObject *obj) const;/// Search object obj in the list of functions

   virtual TFitResultPtr Fit(const char *formula ,Option_t *option="" ,Option_t *goption="", Axis_t xmin=0, Axis_t xmax=0); // *MENU*   返回0表示拟合正常
/// Fit this graph with function with name fname.
/// interface to TGraph::Fit(TF1 *f1...
/// fname is the name of an already predefined function created by TF1 or TF2
/// Predefined functions such as gaus, expo and poln are automatically
/// created by ROOT.
/// fname can also be a formula, accepted by the linear fitter (linear parts divided
/// by "++" sign), for example "x++sin(x)" for fitting "[0]*x+[1]*sin(x)"

   virtual TFitResultPtr Fit(TF1 *f1 ,Option_t *option="" ,Option_t *goption="", Axis_t xmin=0, Axis_t xmax=0);
////////////////////////////////////////////////////////////////////////////////
/// Fit this graph with function f1.
///
/// f1 is an already predefined function created by TF1.
/// Predefined functions such as gaus, expo and poln are automatically
/// created by ROOT.
///
/// The list of fit options is given in parameter option.
///
/// option | description
/// -------|------------
/// "W" | Set all weights to 1; ignore error bars
/// "U" | Use a User specified fitting algorithm (via SetFCN)
/// "Q" | Quiet mode (minimum printing)
/// "V" | Verbose mode (default is between Q and V)
/// "E" | Perform better Errors estimation using Minos technique
/// "B" | User defined parameter settings are used for predefined functions like "gaus", "expo", "poln", "landau". Use this option when you want to fix one or more parameters for these functions.
/// "M" | More. Improve fit results. It uses the IMPROVE command of TMinuit (see TMinuit::mnimpr). This algorithm attempts to improve the found local minimum by searching for a better one.
/// "R" | Use the Range specified in the function range
/// "N" | Do not store the graphics function, do not draw
/// "0" | Do not plot the result of the fit. By default the fitted function is drawn unless the option "N" above is specified.
/// "+" | Add this new fitted function to the list of fitted functions (by default, any previous function is deleted)
/// "C" | In case of linear fitting, do not calculate the chisquare (saves time)
/// "F" | If fitting a polN, use the minuit fitter
/// "EX0" | When fitting a TGraphErrors or TGraphAsymErrors do not consider errors in the coordinate
/// "ROB" | In case of linear fitting, compute the LTS regression coefficients (robust (resistant) regression), using the default fraction of good points "ROB=0.x" - compute the LTS regression coefficients, using 0.x as a fraction of good points
/// "S" |  The result of the fit is returned in the TFitResultPtr (see below Access to the Fit Result)
///
/// When the fit is drawn (by default), the parameter goption may be used
/// to specify a list of graphics options. See TGraphPainter for a complete
/// list of these options.
///
/// In order to use the Range option, one must first create a function
/// with the expression to be fitted. For example, if your graph
/// has a defined range between -4 and 4 and you want to fit a gaussian
/// only in the interval 1 to 3, you can do:
///
///        TF1 *f1 = new TF1("f1","gaus",1,3);
///        graph->Fit("f1","R");
///
/// Who is calling this function:
///
/// Note that this function is called when calling TGraphErrors::Fit
/// or TGraphAsymmErrors::Fit ot TGraphBentErrors::Fit
/// See the discussion below on error calculation.
///
/// ## Linear fitting:
///   When the fitting function is linear (contains the "++" sign) or the fitting
///   function is a polynomial, a linear fitter is initialised.
///   To create a linear function, use the following syntax: linear parts
///   separated by "++" sign.
///   Example: to fit the parameters of "[0]*x + [1]*sin(x)", create a
///    TF1 *f1=new TF1("f1", "x++sin(x)", xmin, xmax);
///   For such a TF1 you don't have to set the initial conditions.
///   Going via the linear fitter for functions, linear in parameters, gives a
///   considerable advantage in speed.
///
/// ## Setting initial conditions:
///
///   Parameters must be initialized before invoking the Fit function.
///   The setting of the parameter initial values is automatic for the
///   predefined functions : poln, expo, gaus, landau. One can however disable
///   this automatic computation by specifying the option "B".
///   You can specify boundary limits for some or all parameters via
///
///        f1->SetParLimits(p_number, parmin, parmax);
///   If parmin>=parmax, the parameter is fixed
///   Note that you are not forced to fix the limits for all parameters.
///   For example, if you fit a function with 6 parameters, you can do:
///
///     func->SetParameters(0,3.1,1.e-6,0.1,-8,100);
///     func->SetParLimits(4,-10,-4);
///     func->SetParLimits(5, 1,1);
///   With this setup, parameters 0->3 can vary freely.
///   Parameter 4 has boundaries [-10,-4] with initial value -8.
///   Parameter 5 is fixed to 100.
///
/// ## Fit range:
///
///   The fit range can be specified in two ways:
///     - specify rxmax > rxmin (default is rxmin=rxmax=0)
///     - specify the option "R". In this case, the function will be taken
///       instead of the full graph range.
/// ## Changing the fitting function:
///   By default a chi2 fitting function is used for fitting a TGraph.
///   The function is implemented in FitUtil::EvaluateChi2.
///   In case of TGraphErrors an effective chi2 is used (see below TGraphErrors fit)
///   To specify a User defined fitting function, specify option "U" and
///   call the following functions:
///      TVirtualFitter::Fitter(mygraph)->SetFCN(MyFittingFunction)
///   where MyFittingFunction is of type:
///   extern void MyFittingFunction(Int_t &npar, Double_t *gin, Double_t &f,
///                                 Double_t *u, Int_t flag);
/// ## TGraphErrors fit:
///   In case of a TGraphErrors object, when x errors are present, the error along x,
///   is projected along the y-direction by calculating the function at the points x-exlow and
///   x+exhigh. The chisquare is then computed as the sum of the quantity below at each point:
///
/// \f[
///   \frac{(y-f(x))^{2}}{ey^{2}+(\frac{1}{2}(exl+exh)f'(x))^{2}}
/// \f]
///
///   where x and y are the point coordinates, and f'(x) is the derivative of the
///   function f(x).
///
///   In case the function lies below (above) the data point, ey is ey_low (ey_high).
///
///   thanks to Andy Haas (haas@yahoo.com) for adding the case with TGraphAsymmErrors
///             University of Washington
///
///   The approach used to approximate the uncertainty in y because of the
///   errors in x is to make it equal the error in x times the slope of the line.
///   The improvement, compared to the first method (f(x+ exhigh) - f(x-exlow))/2
///   is of (error of x)**2 order. This approach is called "effective variance method".
///   This improvement has been made in version 4.00/08 by Anna Kreshuk.
///   The implementation is provided in the function FitUtil::EvaluateChi2Effective
///
/// NOTE:
/// 1. By using the "effective variance" method a simple linear regression
///    becomes a non-linear case, which takes several iterations
///    instead of 0 as in the linear case.
/// 2. The effective variance technique assumes that there is no correlation
///    between the x and y coordinate.
/// 3. The standard chi2 (least square) method without error in the coordinates (x) can
///    be forced by using option "EX0"
/// 4. The linear fitter doesn't take into account the errors in x. When fitting a
///    TGraphErrors with a linear functions the errors in x will not be considered.
///    If errors in x are important, go through minuit (use option "F" for polynomial fitting).
/// 5. When fitting a TGraph (i.e. no errors associated with each point),
///    a correction is applied to the errors on the parameters with the following
///    formula: errorp *= sqrt(chisquare/(ndf-1))
///
///  ## Access to the fit result
///  The function returns a TFitResultPtr which can hold a  pointer to a TFitResult object.
///  By default the TFitResultPtr contains only the status of the fit which is return by an
///  automatic conversion of the TFitResultPtr to an integer. One can write in this case
///  directly:
///
///      Int_t fitStatus =  h->Fit(myFunc)
///
///  If the option "S" is instead used, TFitResultPtr contains the TFitResult and behaves
///  as a smart pointer to it. For example one can do:
///
///      TFitResultPtr r = h->Fit(myFunc,"S");
///      TMatrixDSym cov = r->GetCovarianceMatrix();  //  to access the covariance matrix
///      Double_t chi2   = r->Chi2(); // to retrieve the fit chi2
///      Double_t par0   = r->Value(0); // retrieve the value for the parameter 0
///      Double_t err0   = r->ParError(0); // retrieve the error for the parameter 0
///      r->Print("V");     // print full information of fit including covariance matrix
///      r->Write();        // store the result in a file
///  The fit parameters, error and chi2 (but not covariance matrix) can be retrieved also
///  from the fitted function.
///  If the histogram is made persistent, the list of
///  associated functions is also persistent. Given a pointer (see above)
///  to an associated function myfunc, one can retrieve the function/fit
///  parameters with calls such as:
///      Double_t chi2 = myfunc->GetChisquare();
///      Double_t par0 = myfunc->GetParameter(0); //value of 1st parameter
///      Double_t err0 = myfunc->GetParError(0);  //error on first parameter
/// ## Access to the fit status
///  The status of the fit can be obtained converting the TFitResultPtr to an integer
///  independently if the fit option "S" is used or not:
///       TFitResultPtr r = h->Fit(myFunc,opt);
///       Int_t fitStatus = r;
///  The fitStatus is 0 if the fit is OK (i.e. no error occurred).
///  The value of the fit status code is negative in case of an error not connected with the
///  minimization procedure, for example when a wrong function is used.
///  Otherwise the return value is the one returned from the minimization procedure.
///  When TMinuit (default case) or Minuit2 are used as minimizer the status returned is :
///  fitStatus =  migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult.
///  TMinuit will return 0 (for migrad, minos, hesse or improve) in case of success and 4 in
///  case of error (see the documentation of TMinuit::mnexcm). So for example, for an error
///  only in Minos but not in Migrad a fitStatus of 40 will be returned.
///  Minuit2 will return also 0 in case of success and different values in migrad, minos or
///  hesse depending on the error.   See in this case the documentation of
///  Minuit2Minimizer::Minimize for the migradResult, Minuit2Minimizer::GetMinosError for the
///  minosResult and Minuit2Minimizer::Hesse for the hesseResult.
///  If other minimizers are used see their specific documentation for the status code
///  returned. For example in the case of Fumili, for the status returned see TFumili::Minimize.
///
/// ## Associated functions:
///   One or more object (typically a TF1*) can be added to the list
///   of functions (fFunctions) associated with each graph.
///   When TGraph::Fit is invoked, the fitted function is added to this list.
///   Given a graph gr, one can retrieve an associated function
///   with:  TF1 *myfunc = gr->GetFunction("myfunc");
///
///   If the graph is made persistent, the list of associated functions is also
///   persistent. Given a pointer (see above) to an associated function myfunc,
///   one can retrieve the function/fit parameters with calls such as:
///
///       Double_t chi2 = myfunc->GetChisquare();
///       Double_t par0 = myfunc->GetParameter(0); //value of 1st parameter
///       Double_t err0 = myfunc->GetParError(0);  //error on first parameter
///
/// ## Fit Statistics
///   You can change the statistics box to display the fit parameters with
///   the TStyle::SetOptFit(mode) method. This mode has four digits.
///   mode = pcev  (default = 0111)
///
///       v = 1;  print name/values of parameters
///       e = 1;  print errors (if e=1, v must be 1)
///       c = 1;  print Chisquare/Number of degrees of freedom
///       p = 1;  print Probability
///
///   For example: gStyle->SetOptFit(1011);
///   prints the fit probability, parameter names/values, and errors.
///   You can change the position of the statistics box with these lines
///   (where g is a pointer to the TGraph):
///       Root > TPaveStats *st = (TPaveStats*)g->GetListOfFunctions()->FindObject("stats")
///       Root > st->SetX1NDC(newx1); //new x start position
///       Root > st->SetX2NDC(newx2); //new x end position

   virtual void          FitPanel(); // *MENU*
/// Display a GUI panel with all graph fit options.
/// See class TFitEditor for example

   Bool_t                GetEditable() const; /// Return kTRUE if kNotEditable bit is not set, kFALSE otherwise.
   TF1                  *GetFunction(const char *name) const;//获得拟合函数，由拟合函数可得到拟合参数
/// Return pointer to function with name.
/// Functions such as TGraph::Fit store the fitted function in the list of
/// functions of this graph.

   TH1F                 *GetHistogram() const;
/// Returns a pointer to the histogram used to draw the axis
/// Takes into account the two following cases.
///  1. option 'A' was specified in TGraph::Draw. Return fHistogram
///  2. user had called TPad::DrawFrame. return pointer to hframe histogram

   TList                *GetListOfFunctions() const { return fFunctions; }
   virtual Double_t      GetCorrelationFactor() const;/// Return graph correlation factor
   virtual Double_t      GetCovariance() const;/// Return covariance of vectors x,y
   virtual Double_t      GetMean(Int_t axis=1) const;/// Return mean value of X (axis=1)  or Y (axis=2)
   virtual Double_t      GetRMS(Int_t axis=1) const; /// Return RMS of X (axis=1)  or Y (axis=2)
   Int_t                 GetMaxSize() const {return fMaxSize;}
   Int_t                 GetN() const {return fNpoints;}//获得填充点个数
   virtual Double_t      GetErrorX(Int_t bin) const;
/// This function is called by GraphFitChisquare.
/// It always returns a negative value. Real implementation in TGraphErrors

   virtual Double_t      GetErrorY(Int_t bin) const;
/// This function is called by GraphFitChisquare.
/// It always returns a negative value. Real implementation in TGraphErrors

   virtual Double_t      GetErrorXhigh(Int_t bin) const;
/// This function is called by GraphFitChisquare.
/// It always returns a negative value. Real implementation in TGraphErrors
/// and TGraphAsymmErrors

   virtual Double_t      GetErrorXlow(Int_t bin)  const;
/// This function is called by GraphFitChisquare.
/// It always returns a negative value. Real implementation in TGraphErrors
/// and TGraphAsymmErrors

   virtual Double_t      GetErrorYhigh(Int_t bin) const;
/// This function is called by GraphFitChisquare.
/// It always returns a negative value. Real implementation in TGraphErrors
/// and TGraphAsymmErrors

   virtual Double_t      GetErrorYlow(Int_t bin)  const;
/// This function is called by GraphFitChisquare.
/// It always returns a negative value. Real implementation in TGraphErrors
/// and TGraphAsymmErrors

   Double_t             *GetX()  const {return fX;}
   Double_t             *GetY()  const {return fY;}
   virtual Double_t     *GetEX() const {return 0;}
   virtual Double_t     *GetEY() const {return 0;}
   virtual Double_t     *GetEXhigh() const {return 0;}
   virtual Double_t     *GetEXlow()  const {return 0;}
   virtual Double_t     *GetEYhigh() const {return 0;}
   virtual Double_t     *GetEYlow()  const {return 0;}
   virtual Double_t     *GetEXlowd()  const {return 0;}
   virtual Double_t     *GetEXhighd() const {return 0;}
   virtual Double_t     *GetEYlowd()  const {return 0;}
   virtual Double_t     *GetEYhighd() const {return 0;}
   Double_t              GetMaximum()  const {return fMaximum;}
   Double_t              GetMinimum()  const {return fMinimum;}
   TAxis                *GetXaxis() const ; /// Get x axis of the graph.
   TAxis                *GetYaxis() const ; /// Get y axis of the graph.
   virtual Int_t         GetPoint(Int_t i, Double_t &x, Double_t &y) const;
/// Get x and y values for point number i.
/// The function returns -1 in case of an invalid request or the point number otherwise

   virtual void          InitExpo(Double_t xmin=0, Double_t xmax=0); /// Compute Initial values of parameters for an exponential.
   virtual void          InitGaus(Double_t xmin=0, Double_t xmax=0); /// Compute Initial values of parameters for a gaussian.
   virtual void          InitPolynom(Double_t xmin=0, Double_t xmax=0); /// Compute Initial values of parameters for a polynom.
   virtual Int_t         InsertPoint(); // *MENU* /// Insert a new point at the mouse position
   virtual Double_t      Integral(Int_t first=0, Int_t last=-1) const;
/// Integrate the TGraph data within a given (index) range.
/// Note that this function computes the area of the polygon enclosed by the points of the TGraph.
/// The polygon segments, which are defined by the points of the TGraph, do not need to form a closed polygon,
/// since the last polygon segment, which closes the polygon, is taken as the line connecting the last TGraph point
/// with the first one. It is clear that the order of the point is essential in defining the polygon.
/// Also note that the segments should not intersect.
/// NB:
///  - if last=-1 (default) last is set to the last point.
///  - if (first <0) the first point (0) is taken.
/// ### Method:
/// There are many ways to calculate the surface of a polygon. It all depends on what kind of data
/// you have to deal with. The most evident solution would be to divide the polygon in triangles and
/// calculate the surface of them. But this can quickly become complicated as you will have to test
/// every segments of every triangles and check if they are intersecting with a current polygon's
/// segment or if it goes outside the polygon. Many calculations that would lead to many problems...
/// ### The solution (implemented by R.Brun)
/// Fortunately for us, there is a simple way to solve this problem, as long as the polygon's
/// segments don't intersect.
/// It takes the x coordinate of the current vertex and multiply it by the y coordinate of the next
/// vertex. Then it subtracts from it the result of the y coordinate of the current vertex multiplied
/// by the x coordinate of the next vertex. Then divide the result by 2 to get the surface/area.
/// ### Sources
///  - http://forums.wolfram.com/mathgroup/archive/1998/Mar/msg00462.html
///  - http://stackoverflow.com/questions/451426/how-do-i-calculate-the-surface-area-of-a-2d-polygon


   virtual Bool_t        IsEditable() const {return !TestBit(kNotEditable);}
   virtual Int_t         IsInside(Double_t x, Double_t y) const;//判断（x，y）是否在TCut选定的范围
/// Return 1 if the point (x,y) is inside the polygon defined by
/// the graph vertices 0 otherwise.
/// Algorithm:
/// The loop is executed with the end-point coordinates of a line segment
/// (X1,Y1)-(X2,Y2) and the Y-coordinate of a horizontal line.
/// The counter inter is incremented if the line (X1,Y1)-(X2,Y2) intersects
/// the horizontal line. In this case XINT is set to the X-coordinate of the
/// intersection point. If inter is an odd number, then the point x,y is within
/// the polygon.

   virtual void          LeastSquareFit(Int_t m, Double_t *a, Double_t xmin=0, Double_t xmax=0);
/// Least squares polynomial fitting without weights.
/// \param [in] m     number of parameters
/// \param [in] ma     array of parameters
/// \param [in] mfirst 1st point number to fit (default =0)
/// \param [in] mlast  last point number to fit (default=fNpoints-1)
/// based on CERNLIB routine LSQ: Translated to C++ by Rene Brun

   virtual void          LeastSquareLinearFit(Int_t n, Double_t &a0, Double_t &a1, Int_t &ifail, Double_t xmin=0, Double_t xmax=0);
/// Least square linear fit without weights.
///  Fit a straight line (a0 + a1*x) to the data in this graph.
/// \param [in] ndata        if ndata<0, fits the logarithm of the graph (used in InitExpo() to set
///                          the initial parameter values for a fit with exponential function.
/// \param [in] a0           constant
/// \param [in] a1           slope
/// \param [in] ifail        return parameter indicating the status of the fit (ifail=0, fit is OK)
/// \param [in] xmin, xmax   fitting range
///  extracted from CERNLIB LLSQ: Translated to C++ by Rene Brun

   virtual Int_t         Merge(TCollection* list);
/// Adds all graphs from the collection to this graph.
/// Returns the total number of poins in the result or -1 in case of an error.   

   virtual void          Paint(Option_t *chopt="");/// Draw this graph with its current attributes.
   void                  PaintGraph(Int_t npoints, const Double_t *x, const Double_t *y, Option_t *chopt);/// Draw the (x,y) as a graph.
   void                  PaintGrapHist(Int_t npoints, const Double_t *x, const Double_t *y, Option_t *chopt);/// Draw the (x,y) as a histogram.
   virtual void          PaintStats(TF1 *fit);/// Draw the stats
   virtual void          Print(Option_t *chopt="") const;/// Print graph values.
   virtual void          RecursiveRemove(TObject *obj); /// Recursively remove object from the list of functions
   virtual Int_t         RemovePoint(); // *MENU* /// Delete point close to the mouse position
   virtual Int_t         RemovePoint(Int_t ipoint); /// Delete point number ipoint
   virtual void          SavePrimitive(std::ostream &out, Option_t *option = ""); /// Save primitive as a C++ statement(s) on output stream out
   virtual void          SetEditable(Bool_t editable=kTRUE); // *TOGGLE* *GETTER=GetEditable
/// if editable=kFALSE, the graph cannot be modified with the mouse
///  by default a TGraph is editable

   virtual void          SetHistogram(TH1F *h) {fHistogram = h;}
   virtual void          SetMaximum(Double_t maximum=-1111); // *MENU* /// Set the maximum of the graph.
   virtual void          SetMinimum(Double_t minimum=-1111); // *MENU* /// Set the minimum of the graph.
   virtual void          Set(Int_t n);
/// Set number of points in the graph
/// Existing coordinates are preserved
/// New coordinates above fNpoints are preset to 0.

   virtual void          SetPoint(Int_t i, Double_t x, Double_t y);/// Set x and y values for point number i. 逐个点填充，i从0开始
   virtual void          SetTitle(const char *title="");    // *MENU* /// Set graph title.
   virtual void          Sort(Bool_t (*greater)(const TGraph*, Int_t, Int_t)=&TGraph::CompareX,
                              Bool_t ascending=kTRUE, Int_t low=0, Int_t high=-1111);
/// Sorts the points of this TGraph using in-place quicksort (see e.g. older glibc).
/// To compare two points the function parameter greaterfunc is used (see TGraph::CompareX for an
/// example of such a method, which is also the default comparison function for Sort). After
/// the sort, greaterfunc(this, i, j) will return kTRUE for all i>j if ascending == kTRUE, and
/// kFALSE otherwise.
/// The last two parameters are used for the recursive quick sort, stating the range to be sorted

   virtual void          UseCurrentStyle();
/// Set current style settings in this graph
/// This function is called when either TCanvas::UseCurrentStyle
/// or TROOT::ForceStyle have been invoked.

   void                  Zero(Int_t &k,Double_t AZ,Double_t BZ,Double_t E2,Double_t &X,Double_t &Y,Int_t maxiterations);
/// Find zero of a continuous function.
/// This function finds a real zero of the continuous real
/// function Y(X) in a given interval (A,B). See accompanying
/// notes for details of the argument list and calling sequence
```

## code

```cpp
// sort points along x axis
graph->Sort();
// sort points along their distance to origin
graph->Sort(&TGraph::CompareRadius);

Bool_t CompareErrors(const TGraph* gr, Int_t i, Int_t j) {
  const TGraphErrors* ge=(const TGraphErrors*)gr;
  return (ge->GetEY()[i]>ge->GetEY()[j]); }
// sort using the above comparison function, largest errors first
graph->Sort(&CompareErrors, kFALSE);
```




## example

```cpp
const Int_t n = 20;
Double_t x[n], y[n];
for (Int_t i=0;i<n;i++) {
x[i] = i*0.1;
y[i] = 10*sin(x[i]+0.2);}
// create graph
TGraph *gr = new TGraph(n,x,y);
TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,600,400);
// draw the graph with axis, continuous line, and put a * at each point
gr->Draw("AC*");
```

```cpp
//Draw a graph with text attached to each point.

const Int_t n = 10;
TGraph *gr = new TGraph(n);
gr->SetTitle("A Simple Graph Example with Text");
gr->SetMarkerStyle(20);
TExec *ex = new TExec("ex","drawtext();");
gr->GetListOfFunctions()->Add(ex);
…………

//然后加上以下代码：
void drawtext()
{
   Int_t i,n;
   Double_t x,y;
   TLatex *l;

   TGraph *g = (TGraph*)gPad->GetListOfPrimitives()->FindObject("Graph");
   n = g->GetN();
   for (i=1; i<n; i++) {
      g->GetPoint(i,x,y);
      l = new TLatex(x,y+0.2,Form("%4.2f",y));
      l->SetTextSize(0.025);
      l->SetTextFont(42);
      l->SetTextAlign(21);
      l->Paint();
   }
}
```


```cpp
//Draw a simple graph。
   
TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
c1->SetFillColor(42);
c1->SetGrid();

const Int_t n = 20;
Double_t x[n], y[n];
for (Int_t i=0;i<n;i++) {
  x[i] = i*0.1;
  y[i] = 10*sin(x[i]+0.2);
  printf(" i %i %f %f \n",i,x[i],y[i]);
 }
gr = new TGraph(n,x,y);
gr->SetLineColor(2);
gr->SetLineWidth(4);
gr->SetMarkerColor(4);
gr->SetMarkerStyle(21);
gr->SetTitle("a simple graph");//设置标题
gr->GetXaxis()->SetTitle("X title");//设置横坐标
gr->GetYaxis()->SetTitle("Y title");//设置纵坐标
gr->Draw("ACP");
```

```cpp
//Draw several graphs with an exclusion zones.一个画板上画出多个Graph，图片上加注释。
   
TCanvas *c = new TCanvas("c","Charged Higgs L300 Contour",0,0,700,700);
c->SetTickx();
c->SetTicky();
c->SetGridx();
c->SetGridy();

TH1 *frame = new TH1F("frame","",1000,50,500);
frame->SetMinimum(1);
frame->SetMaximum(50);
frame->SetDirectory(0);
frame->SetStats(0);
frame->GetXaxis()->SetTitle("m_{A} (GeV)");
frame->GetXaxis()->SetTickLength(0.02);
frame->GetXaxis()->SetLabelSize(0.03);
frame->GetYaxis()->SetTitle("tan#beta");
frame->GetYaxis()->SetMoreLogLabels();
frame->GetYaxis()->SetLabelSize(0.03);
frame->Draw(" ");
c->SetLogy();

TGraph *gr1 = new TGraph(10);
gr1->SetFillColor(6);
gr1->SetFillStyle(3005);
gr1->SetLineColor(6);
gr1->SetLineWidth(603);
gr1->SetPoint(0,140,0.5);
gr1->SetPoint(1,130,2.9);
gr1->SetPoint(2,124.677,3.83726);
gr1->SetPoint(3,113.362,6.06903);
gr1->SetPoint(4,108.513,8.00221);
gr1->SetPoint(5,111.746,10.0272);
gr1->SetPoint(6,119.828,12.8419);
gr1->SetPoint(7,135.991,30.0872);
gr1->SetPoint(8,140,40);
gr1->SetPoint(9,135,60);
gr1->Draw("C");
TLatex *tex = new TLatex(140.841,37.9762,
			 "#leftarrow t #rightarrow bH^{+}, H^{+} #rightarrow #tau#nu");
tex->SetTextColor(6);
tex->Draw();

TGraph *gr2 = new TGraph(15);
gr2->SetName("Graph");
gr2->SetTitle("Graph");
gr2->SetFillColor(1);
gr2->SetFillStyle(3005);
gr2->SetLineWidth(3);
gr2->SetPoint(0,499.192,3.02622);
gr2->SetPoint(1,427.748,3.06233);
gr2->SetPoint(2,358.244,3.10722);
gr2->SetPoint(3,305.711,3.24589);
gr2->SetPoint(4,244.289,3.36617);
gr2->SetPoint(5,206.304,3.7544);
gr2->SetPoint(6,178.017,4.50347);
gr2->SetPoint(7,148.114,6.20297);
gr2->SetPoint(8,131.142,8.00221);
gr2->SetPoint(9,111.746,8.48188);
gr2->SetPoint(10,102.047,9.52921);
gr2->SetPoint(11,96.3901,13.2212);
gr2->SetPoint(12,92.3491,19.0232);
gr2->SetPoint(13,90.7328,26.3935);
gr2->SetPoint(14,93.1573,50.4385);
gr2->Draw("L");
tex = new TLatex(346.929,6.62281,"ATLAS");
tex->SetLineWidth(2);
tex->Draw();
tex = new TLatex(328.341,5.24703,"#intLdt = 300 fb^{-1}");
tex->SetTextSize(0.0297619);
tex->SetLineWidth(2);
tex->Draw();
tex = new TLatex(340.463,4.1874,"Maximal mixing");
tex->SetTextSize(0.0297619);
tex->SetLineWidth(2);
tex->Draw();
tex = new TLatex(413.2,2.51608,"LEP 2000");
tex->SetTextSize(0.0297619);
tex->SetLineWidth(2);
tex->Draw();

TGraph *gr3 = new TGraph(10);
gr3->SetName("Graph");
gr3->SetTitle("Graph");
gr3->SetFillColor(2);
gr3->SetFillStyle(3004);
gr3->SetLineColor(2);
gr3->SetLineWidth(603);
gr3->SetPoint(0,176.84,10.7499);
gr3->SetPoint(1,190.575,11.9912);
gr3->SetPoint(2,211.58,12.7108);
gr3->SetPoint(3,243.088,12.3457);
gr3->SetPoint(4,279.443,12.6185);
gr3->SetPoint(5,302.065,12.9916);
gr3->SetPoint(6,331.957,13.7713);
gr3->SetPoint(7,369.928,14.2821);
gr3->SetPoint(8,425.673,16.1651);
gr3->SetPoint(9,499.192,18.1635);
gr3->Draw("C");
tex = new TLatex(188.151,9.36035,
		 "gb #rightarrow tH^{+}, H^{+} #rightarrow #tau#nu");
tex->SetTextColor(2);
tex->Draw();

TGraph *gr4 = new TGraph(10);
gr4->SetName("Graph");
gr4->SetTitle("Graph");
gr4->SetFillColor(4);
gr4->SetFillStyle(3004);
gr4->SetLineColor(4);
gr4->SetLineWidth(-603);
gr4->SetPoint(0,178.456,2.91797);
gr4->SetPoint(1,200.269,3.40033);
gr4->SetPoint(2,229.354,3.96243);
gr4->SetPoint(3,249.551,4.07959);
gr4->SetPoint(4,269.749,3.71097);
gr4->SetPoint(5,298.025,3.09308);
gr4->SetPoint(6,341.652,2.89679);
gr4->SetPoint(7,378.007,2.57808);
gr4->SetPoint(8,441.023,2.16454);
gr4->SetPoint(9,499.677,1.76145);
gr4->Draw("C");
tex = new TLatex(165.,1.15498,
		 "gb #rightarrow tH^{+}, H^{+} #rightarrow tb");
tex->SetTextColor(4);
tex->Draw();

TGraph *gr5 = new TGraph(10);
gr5->SetName("Graph");
gr5->SetTitle("Graph");
gr5->SetFillColor(4);
gr5->SetFillStyle(3004);
gr5->SetLineColor(4);
gr5->SetLineWidth(603);
gr5->SetPoint(0,152.603,23.0996);
gr5->SetPoint(1,188.151,18.8373);
gr5->SetPoint(2,239.048,15.2499);
gr5->SetPoint(3,264.901,15.8156);
gr5->SetPoint(4,299.641,18.8373);
gr5->SetPoint(5,334.381,20.7085);
gr5->SetPoint(6,360.233,22.4362);
gr5->SetPoint(7,396.589,24.4859);
gr5->SetPoint(8,433.752,25.7669);
gr5->SetPoint(9,499.192,27.3132);
gr5->Draw("C");
```



<!-- TGraph.md ends here -->
