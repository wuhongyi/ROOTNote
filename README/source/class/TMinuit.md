<!-- TMinuit.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 14:42:33 2016 (+0800)
;; Last-Updated: 三 9月 16 12:58:02 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TMinuit*

The MINUIT minimisation package (base class)

TMinuit 继承 TNamed

## class

```cpp

R__EXTERN TMinuit  *gMinuit;
```


```cpp
   TMinuit();
   TMinuit(Int_t maxpar);///  maxpar is the maximum number of parameters used with this TMinuit object.
   virtual       ~TMinuit();
   virtual void   BuildArrays(Int_t maxpar=15);///*-*-*-*-*-*-*Create internal Minuit arrays for the maxpar parameters*-*-*-*
   virtual TObject *Clone(const char *newname="") const;   //Clone-Method to copy the function-pointer fFCN
/// Make a clone of an object using the Streamer facility.
/// Function pointer is copied to Clone

   virtual Int_t  Command(const char *command);
/// execute a Minuit command
///     Equivalent to MNEXCM except that the command is given as a
///     character string.
/// See TMinuit::mnhelp for the full list of available commands
/// See also http://wwwasdoc.web.cern.ch/wwwasdoc/minuit/node18.html for
///  a complete documentation of all the available commands
/// Returns the status of the execution:
///   = 0: command executed normally
///     1: command is blank, ignored
///     2: command line unreadable, ignored
///     3: unknown command, ignored
///     4: abnormal termination (e.g., MIGRAD not converged)
///     5: command is a request to read PARAMETER definitions
///     6: 'SET INPUT' command
///     7: 'SET TITLE' command
///     8: 'SET COVAR' command
///     9: reserved
///    10: END command
///    11: EXIT or STOP command
///    12: RETURN command

   virtual TObject *Contour(Int_t npoints=10, Int_t pa1=0, Int_t pa2=1);
/// Creates a TGraph object describing the n-sigma contour of a
/// TMinuit fit. The contour of the parameters pa1 and pa2 is calculated
/// unsing npoints (>=4) points. The TMinuit status will be
///  0   on success and
/// -1   if errors in the calling sequence (pa1, pa2 not variable)
///  1   if less than four points can be found
///  2   if npoints<4
///  n>3 if only n points can be found (n < npoints)
/// The status can be obtained via TMinuit::GetStatus().
/// To get the n-sigma contour the ERRDEF parameter in Minuit has to set
/// to n^2. The fcn function has to be set before the routine is called.
/// The TGraph object is created via the interpreter. The user must cast it
/// to a TGraph*. Note that the TGraph is created with npoints+1 in order to
/// close the contour (setting last point equal to first point).
/// You can find an example in $ROOTSYS/tutorials/fit/fitcont.C

   virtual Int_t  DefineParameter( Int_t parNo, const char *name, Double_t initVal, Double_t initErr, Double_t lowerLimit, Double_t upperLimit );/// Define a parameter
   virtual void   DeleteArrays();///*-*-*-*-*-*-*-*-*-*-*-*Delete internal Minuit arrays*-*-*-*-*-*-*-*-*
   virtual Int_t  Eval(Int_t npar, Double_t *grad, Double_t &fval, Double_t *par, Int_t flag);
/// Evaluate the minimisation function
///  Input parameters:
///    npar:    number of currently variable parameters
///    par:     array of (constant and variable) parameters
///    flag:    Indicates what is to be calculated (see example below)
///    grad:    array of gradients
///  Output parameters:
///    fval:    The calculated function value.
///    grad:    The (optional) vector of first derivatives).
/// The meaning of the parameters par is of course defined by the user,
/// who uses the values of those parameters to calculate their function value.
/// The starting values must be specified by the user.
/// Later values are determined by Minuit as it searches for the minimum
/// or performs whatever analysis is requested by the user.
///
/// Note that this virtual function may be redefined in a class derived from TMinuit.
/// The default function calls the function specified in SetFCN

   virtual Int_t  FixParameter( Int_t parNo );/// fix a parameter
   TMethodCall   *GetMethodCall() const {return fMethodCall;}
   TObject       *GetObjectFit() const {return fObjectFit;}
   Int_t          GetMaxIterations() const {return fMaxIterations;}
   virtual Int_t  GetNumFixedPars() const;/// returns the number of currently fixed parameters


   virtual Int_t  GetNumFreePars() const;/// returns the number of currently free parameters
   virtual Int_t  GetNumPars() const;
/// returns the total number of parameters that have been defined
/// as fixed or free. The constant parameters are not counted.

   virtual Int_t  GetParameter( Int_t parNo, Double_t &currentValue, Double_t &currentError ) const;
/// return parameter value and error

   virtual TObject *GetPlot() const {return fPlot;}
   Int_t          GetStatus() const {return fStatus;}
   virtual Int_t  Migrad();/// invokes the MIGRAD minimizer
   virtual void   mnamin();
///*-*-*-*-*-*-*-*-*-*-*-*-*Initialize AMIN*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*C        Called  from many places.  Initializes the value of AMIN by
///*-*C        calling the user function. Prints out the function value and
///*-*C        parameter values if Print Flag value is high enough.

   virtual void   mnbins(Double_t a1, Double_t a2, Int_t naa, Double_t &bl, Double_t &bh, Int_t &nb, Double_t &bwid);
///*-*-*-*-*-*-*-*-*-*-*Compute reasonable histogram intervals*-*-*-*-*-*-*-*-*
///*-*        Function TO DETERMINE REASONABLE HISTOGRAM INTERVALS
///*-*        GIVEN ABSOLUTE UPPER AND LOWER BOUNDS  A1 AND A2
///*-*        AND DESIRED MAXIMUM NUMBER OF BINS NAA
///*-*        PROGRAM MAKES REASONABLE BINNING FROM BL TO BH OF WIDTH BWID
///*-*        F. JAMES,   AUGUST, 1974 , stolen for Minuit, 1988

   virtual void   mncalf(Double_t *pvec, Double_t &ycalf);
///*-*-*-*-*-*-*-*-*-*Transform FCN to find further minima*-*-*-*-*-*-*-*-*-*
///*-*        Called only from MNIMPR.  Transforms the function FCN
///*-*        by dividing out the quadratic part in order to find further
///*-*        minima.    Calculates  ycalf = (f-fmin)/(x-xmin)*v*(x-xmin)

   virtual void   mncler();
///*-*-*-*-*-*-*-*-*-*-*Resets the parameter list to UNDEFINED*-*-*-*-*-*-*-*
///*-*        Called from MINUIT and by option from MNEXCM

   virtual void   mncntr(Int_t ke1, Int_t ke2, Int_t &ierrf);
///*-*-*-*-*Print function contours in two variables, on line printer*-*-*-*-*
///*-*                input arguments: parx, pary, devs, ngrid

   virtual void   mncomd(const char *crdbin, Int_t &icondn);
///*-*-*-*-*-*-*-*-*-*-*Reads a command string and executes*-*-*-*-*-*-*-*-*-*
///*-*        Called by user.  'Reads' a command string and executes.
///*-*     Equivalent to MNEXCM except that the command is given as a
///*-*          character string.
///*-*     ICONDN = 0: command executed normally
///*-*              1: command is blank, ignored
///*-*              2: command line unreadable, ignored
///*-*              3: unknown command, ignored
///*-*              4: abnormal termination (e.g., MIGRAD not converged)
///*-*              5: command is a request to read PARAMETER definitions
///*-*              6: 'SET INPUT' command
///*-*              7: 'SET TITLE' command
///*-*              8: 'SET COVAR' command
///*-*              9: reserved
///*-*             10: END command
///*-*             11: EXIT or STOP command
///*-*             12: RETURN command

   virtual void   mncont(Int_t ke1, Int_t ke2, Int_t nptu, Double_t *xptu, Double_t *yptu, Int_t &ierrf);
///*-*-*-*-*-*-*Find points along a contour where FCN is minimum*-*-*-*-*-*-*
///*-*       Find NPTU points along a contour where the function
///*-*             FMIN (X(KE1),X(KE2)) =  AMIN+UP
///*-*       where FMIN is the minimum of FCN with respect to all
///*-*       the other NPAR-2 variable parameters (if any).
///*-*   IERRF on return will be equal to the number of points found:
///*-*     NPTU if normal termination with NPTU points found
///*-*     -1   if errors in the calling sequence (KE1, KE2 not variable)
///*-*      0   if less than four points can be found (using MNMNOT)
///*-*     n>3  if only n points can be found (n < NPTU)
///*-*                 input arguments: parx, pary, devs, ngrid

   virtual void   mncrck(TString crdbuf, Int_t maxcwd, TString &comand, Int_t &lnc
                    ,  Int_t mxp, Double_t *plist, Int_t &llist, Int_t &ierr, Int_t isyswr);
///*-*-*-*-*-*-*-*-*-*-*-*Cracks the free-format input*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*       Cracks the free-format input, expecting zero or more
///*-*         alphanumeric fields (which it joins into COMAND(1:LNC))
///*-*         followed by one or more numeric fields separated by
///*-*         blanks and/or one comma.  The numeric fields are put into
///*-*         the LLIST (but at most MXP) elements of PLIST.
///*-*      IERR = 0 if no errors,
///*-*           = 1 if error(s).

   virtual void   mncros(Double_t &aopt, Int_t &iercr);
///*-*-*-*-*-*-*-*-*-*-*Find point where MNEVAL=AMIN+UP*-*-*-*-*-*-*-*-*-*-*-*
///*-*       Find point where MNEVAL=AMIN+UP, along the line through
///*-*       XMIDCR,YMIDCR with direction XDIRCR,YDIRCR,   where X and Y
///*-*       are parameters KE1CR and KE2CR.  If KE2CR=0 (from MINOS),
///*-*       only KE1CR is varied.  From MNCONT, both are varied.
///*-*       Crossing point is at
///*-*        (U(KE1),U(KE2)) = (XMID,YMID) + AOPT*(XDIR,YDIR)

   virtual void   mncuve();
///*-*-*-*-*-*-*-*Makes sure that the current point is a local minimum*-*-*-*-*
///*-*        Makes sure that the current point is a local
///*-*        minimum and that the error matrix exists,
///*-*        or at least something good enough for MINOS and MNCONT

   virtual void   mnderi();
///*-*-*-*-*-*-*-*Calculates the first derivatives of FCN (GRD)*-*-*-*-*-*-*-*
///*-*        Calculates the first derivatives of FCN (GRD),
///*-*        either by finite differences or by transforming the user-
///*-*        supplied derivatives to internal coordinates,
///*-*        according to whether fISW[2] is zero or one.

   virtual void   mndxdi(Double_t pint, Int_t ipar, Double_t &dxdi);
///*-*-*-*Calculates the transformation factor between ext/internal values*-*
///*-*        calculates the transformation factor between external and
///*-*        internal parameter values.     this factor is one for
///*-*        parameters which are not limited.     called from MNEMAT.

   virtual void   mneig(Double_t *a, Int_t ndima, Int_t n, Int_t mits, Double_t *work, Double_t precis, Int_t &ifault);
///*-*-*-*-*-*-*-*-*-*-*-*Compute matrix eigen values*-*-*-*-*-*-*-*-*-*-*-*-*

   virtual void   mnemat(Double_t *emat, Int_t ndim);
/// Calculates the external error matrix from the internal matrix
/// Note that if the matrix is declared like Double_t matrix[5][5]
/// in the calling program, one has to call mnemat with, eg
///     gMinuit->mnemat(&matrix[0][0],5);

   virtual void   mnerrs(Int_t number, Double_t &eplus, Double_t &eminus, Double_t &eparab, Double_t &gcc);
///*-*-*-*-*-*-*-*-*-*Utility routine to get MINOS errors*-*-*-*-*-*-*-*-*-*-*
///*-*    Called by user.
///*-*    NUMBER is the parameter number
///*-*    values returned by MNERRS:
///*-*       EPLUS, EMINUS are MINOS errors of parameter NUMBER,
///*-*       EPARAB is 'parabolic' error (from error matrix).
///*-*                 (Errors not calculated are set = 0)
///*-*       GCC is global correlation coefficient from error matrix

   virtual void   mneval(Double_t anext, Double_t &fnext, Int_t &ierev);
///*-*-*-*-*-*-*Evaluates the function being analyzed by MNCROS*-*-*-*-*-*-*-*
///*-*      Evaluates the function being analyzed by MNCROS, which is
///*-*      generally the minimum of FCN with respect to all remaining
///*-*      variable parameters.  The class data members contains the
///*-*      data necessary to know the values of U(KE1CR) and U(KE2CR)
///*-*      to be used, namely     U(KE1CR) = XMIDCR + ANEXT*XDIRCR
///*-*      and (if KE2CR .NE. 0)  U(KE2CR) = YMIDCR + ANEXT*YDIRCR

   virtual void   mnexcm(const char *comand, Double_t *plist, Int_t llist, Int_t &ierflg) ;
///*-*-*-*-*-*Interprets a command and takes appropriate action*-*-*-*-*-*-*-*
///*-*        either directly by skipping to the corresponding code in
///*-*        MNEXCM, or by setting up a call to a function
///*-*  recognized MINUIT commands:
///*-*  obsolete commands:
///*-*      IERFLG is now (94.5) defined the same as ICONDN in MNCOMD
///*-*            = 0: command executed normally
///*-*              1: command is blank, ignored
///*-*              2: command line unreadable, ignored
///*-*              3: unknown command, ignored
///*-*              4: abnormal termination (e.g., MIGRAD not converged)
///*-*              9: reserved
///*-*             10: END command
///*-*             11: EXIT or STOP command
///*-*             12: RETURN command
///*-*     see also http://wwwasdoc.web.cern.ch/wwwasdoc/minuit/node18.html for the possible list
///*-*     of all Minuit commands

   virtual void   mnexin(Double_t *pint);
///*-*-*-*-*Transforms the external parameter values U to internal values*-*-*
///*-*        Transforms the external parameter values U to internal
///*-*        values in the dense array PINT.

   virtual void   mnfixp(Int_t iint, Int_t &ierr);
///*-*-*-*-*-*-*Removes parameter IINT from the internal parameter list*-*-*
///*-*        and arranges the rest of the list to fill the hole.

   virtual void   mnfree(Int_t k);
///*-*-*-*Restores one or more fixed parameter(s) to variable status*-*-*-*-*-*
///*-*        Restores one or more fixed parameter(s) to variable status
///*-*        by inserting it into the internal parameter list at the
///*-*        appropriate place.
///*-*        K = 0 means restore all parameters
///*-*        K = 1 means restore the last parameter fixed
///*-*        K = -I means restore external parameter I (if possible)
///*-*        IQ = fix-location where internal parameters were stored
///*-*        IR = external number of parameter being restored
///*-*        IS = internal number of parameter being restored

   virtual void   mngrad();
///*-*-*-*-*-*-*-*-*-*Interprets the SET GRAD command*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*       Called from MNSET
///*-*       Interprets the SET GRAD command, which informs MINUIT whether
///*-*       the first derivatives of FCN will be calculated by the user
///*-*       inside FCN.  It can check the user derivative calculation
///*-*       by comparing it with a finite difference approximation.

   virtual void   mnhelp(TString comd);
//*-*  Global HELP: Summary of all commands

   virtual void   mnhelp(const char *command="");
///interface to Minuit help

   virtual void   mnhess();
///*-*-*-*-*-*Calculates the full second-derivative matrix of FCN*-*-*-*-*-*-*-*
///*-*        by taking finite differences. When calculating diagonal
///*-*        elements, it may iterate so that step size is nearly that
///*-*        which gives function change= UP/10. The first derivatives
///*-*        of course come as a free side effect, but with a smaller
///*-*        step size in order to obtain a known accuracy.

   virtual void   mnhes1();
///*-*-*-*Calculate first derivatives (GRD) and uncertainties (DGRD)*-*-*-*-*-*
///*-*         and appropriate step sizes GSTEP
///*-*      Called from MNHESS and MNGRAD

   virtual void   mnimpr();
///*-*-*-*-*-*-*Attempts to improve on a good local minimum*-*-*-*-*-*-*-*-*-*
///*-*        Attempts to improve on a good local minimum by finding a
///*-*        better one.   The quadratic part of FCN is removed by MNCALF
///*-*        and this transformed function is minimized using the simplex
///*-*        method from several random starting points.
///*-*        ref. -- Goldstein and Price, Math.Comp. 25, 569 (1971)

   virtual void   mninex(Double_t *pint);
///*-*-*-*-*Transforms from internal coordinates (PINT) to external (U)*-*-*-*
///*-*        The minimizing routines which work in
///*-*        internal coordinates call this routine before calling FCN.

   virtual void   mninit(Int_t i1, Int_t i2, Int_t i3);
///*-*-*-*-*-*Main initialization member function for MINUIT*-*-*-*-*-*-*-*-*
///*-*     It initializes some constants
///*-*                (including the logical I/O unit nos.),

   virtual void   mnlims();
///*-*-*-*Interprets the SET LIM command, to reset the parameter limits*-*-*-*
///*-*       Called from MNSET

   virtual void   mnline(Double_t *start, Double_t fstart, Double_t *step, Double_t slope, Double_t toler);
///*-*-*-*-*-*-*-*-*-*Perform a line search from position START*-*-*-*-*-*-*-*
///*-*        along direction STEP, where the length of vector STEP
///*-*                   gives the expected position of minimum.
///*-*        FSTART is value of function at START
///*-*        SLOPE (if non-zero) is df/dx along STEP at START
///*-*        TOLER is initial tolerance of minimum in direction STEP
///*-* SLAMBG and ALPHA control the maximum individual steps allowed.
///*-* The first step is always =1. The max length of second step is SLAMBG.
///*-* The max size of subsequent steps is the maximum previous successful
///*-*   step multiplied by ALPHA + the size of most recent successful step,
///*-*   but cannot be smaller than SLAMBG.

   virtual void   mnmatu(Int_t kode);
///*-*-*-*-*-*-*-*Prints the covariance matrix v when KODE=1*-*-*-*-*-*-*-*-*
///*-*        always prints the global correlations, and
///*-*        calculates and prints the individual correlation coefficients

   virtual void   mnmigr();
///*-*-*-*-*-*-*-*-*Performs a local function minimization*-*-*-*-*-*-*-*-*-*
///*-*        Performs a local function minimization using basically the
///*-*        method of Davidon-Fletcher-Powell as modified by Fletcher
///*-*        ref. -- Fletcher, Comp.J. 13,317 (1970)   "switching method"

   virtual void   mnmnos();
///*-*-*-*-*-*-*-*-*-*-*Performs a MINOS error analysis*-*-*-*-*-*-*-*-*-*-*-*
///*-*        Performs a MINOS error analysis on those parameters for
///*-*        which it is requested on the MINOS command by calling
///*-*        MNMNOT for each parameter requested.

   virtual void   mnmnot(Int_t ilax, Int_t ilax2, Double_t &val2pl, Double_t &val2mi);
///*-*-*-*-*-*Performs a MINOS error analysis on one parameter*-*-*-*-*-*-*-*-*
///*-*        The parameter ILAX is varied, and the minimum of the
///*-*        function with respect to the other parameters is followed
///*-*        until it crosses the value FMIN+UP.

   virtual void   mnparm(Int_t k, TString cnamj, Double_t uk, Double_t wk, Double_t a, Double_t b, Int_t &ierflg);
///*-*-*-*-*-*-*-*-*Implements one parameter definition*-*-*-*-*-*-*-*-*-*-*-*
///*-*        Called from MNPARS and user-callable
///*-*    Implements one parameter definition, that is:
///*-*          K     (external) parameter number
///*-*          CNAMK parameter name
///*-*          UK    starting value
///*-*          WK    starting step size or uncertainty
///*-*          A, B  lower and upper physical parameter limits
///*-*    and sets up (updates) the parameter lists.
///*-*    Output: IERFLG=0 if no problems
///*-*                  >0 if MNPARM unable to implement definition

   virtual void   mnpars(TString &crdbuf, Int_t &icondn);
///*-*-*-*-*-*-*-*Implements one parameter definition*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*        Called from MNREAD and user-callable
///*-*    Implements one parameter definition, that is:
///*-*       parses the string CRDBUF and calls MNPARM
///*-* output conditions:
///*-*        ICONDN = 0    all OK
///*-*        ICONDN = 1    error, attempt to define parameter is ignored
///*-*        ICONDN = 2    end of parameter definitions

   virtual void   mnpfit(Double_t *parx2p, Double_t *pary2p, Int_t npar2p, Double_t *coef2p, Double_t &sdev2p);
///*-*-*-*-*-*-*-*-*-*To fit a parabola to npar2p points*-*-*-*-*-*-*-*-*-*-*
///*-*   npar2p   no. of points
///*-*   parx2p(i)   x value of point i
///*-*   pary2p(i)   y value of point i
///*-*
///*-*   coef2p(1...3)  coefficients of the fitted parabola
///*-*   y=coef2p(1) + coef2p(2)*x + coef2p(3)*x**2
///*-*   sdev2p= variance
///*-*   method : chi**2 = min equation solved explicitly

   virtual void   mnpint(Double_t &pexti, Int_t i, Double_t &pinti);
///*-*-*-*-*-*-*Calculates the internal parameter value PINTI*-*-*-*-*-*-*-*
///*-*        corresponding  to the external value PEXTI for parameter I.

   virtual void   mnplot(Double_t *xpt, Double_t *ypt, char *chpt, Int_t nxypt, Int_t npagwd, Int_t npagln);
///*-*-*-*Plots points in array xypt onto one page with labelled axes*-*-*-*-*
///*-*        NXYPT is the number of points to be plotted
///*-*        XPT(I) = x-coord. of ith point
///*-*        YPT(I) = y-coord. of ith point
///*-*        CHPT(I) = character to be plotted at this position
///*-*        the input point arrays XPT, YPT, CHPT are destroyed.
///*-*   If fGraphicsmode is true (default), a TGraph object is produced
///*-*   via the Plug-in handler. To get the plot, you can do:
///*-*       TGraph *gr = (TGraph*)gMinuit->GetPlot();
///*-*       gr->Draw("al");

   virtual void   mnpout(Int_t iuext, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const;
///*-*-*-*Provides the user with information concerning the current status*-*-*
///*-*          of parameter number IUEXT. Namely, it returns:
///*-*        CHNAM: the name of the parameter
///*-*        VAL: the current (external) value of the parameter
///*-*        ERR: the current estimate of the parameter uncertainty
///*-*        XLOLIM: the lower bound (or zero if no limits)
///*-*        XUPLIM: the upper bound (or zero if no limits)
///*-*        IUINT: the internal parameter number (or zero if not variable,
///*-*           or negative if undefined).
///*-*  Note also:  If IUEXT is negative, then it is -internal parameter
///*-*           number, and IUINT is returned as the EXTERNAL number.
///*-*     Except for IUINT, this is exactly the inverse of MNPARM
///*-*     User-called

   virtual void   mnprin(Int_t inkode, Double_t fval);
///*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
///*-*        also prints other relevant information such as function value,
///*-*        estimated distance to minimum, parameter errors, step sizes.
///*-*
///*-*         According to the value of IKODE, the printout is:/
///*-*    IKODE=INKODE= 0    only info about function value
///*-*                  1    parameter values, errors, limits
///*-*                  2    values, errors, step sizes, internal values
///*-*                  3    values, errors, step sizes, first derivs.
///*-*                  4    values, parabolic errors, MINOS errors
///*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to fISW[1]

   virtual void   mnpsdf();
///*-*-*-*-*-*Calculates the eigenvalues of v to see if positive-def*-*-*-*-*
///*-*        if not, adds constant along diagonal to make positive.

   virtual void   mnrazz(Double_t ynew, Double_t *pnew, Double_t *y, Int_t &jh, Int_t &jl);
///*-*-*-*-*Called only by MNSIMP (and MNIMPR) to add a new point*-*-*-*-*-*-*
///*-*        and remove an old one from the current simplex, and get the
///*-*        estimated distance to minimum.

   virtual void   mnrn15(Double_t &val, Int_t &inseed);
///*-*-*-*-*-*-*This is a super-portable random number generator*-*-*-*-*-*-*
///*-*         It should not overflow on any 32-bit machine.
///*-*         The cycle is only ~10**9, so use with care!
///*-*         Note especially that VAL must not be undefined on input.
///*-*                    Set Default Starting Seed

   virtual void   mnrset(Int_t iopt);
///*-*-*-*-*-*-*-*Resets function value and errors to UNDEFINED*-*-*-*-*-*-*-*
///*-*    If IOPT=1,
///*-*    If IOPT=0, sets only MINOS errors to undefined
///*-*        Called from MNCLER and whenever problem changes, for example
///*-*        after SET LIMITS, SET PARAM, CALL FCN 6

   virtual void   mnsave();
   virtual void   mnscan();
///*-*-*-*-*Scans the values of FCN as a function of one parameter*-*-*-*-*-*
///*-*        and plots the resulting values as a curve using MNPLOT.
///*-*        It may be called to scan one parameter or all parameters.
///*-*        retains the best function and parameter values found.

   virtual void   mnseek();
///*-*-*-*Performs a rough (but global) minimization by monte carlo search*-*
///*-*        Each time a new minimum is found, the search area is shifted
///*-*        to be centered at the best value.  Random points are chosen
///*-*        uniformly over a hypercube determined by current step sizes.
///*-*   The Metropolis algorithm accepts a worse point with probability
///*-*      exp(-d/UP), where d is the degradation.  Improved points
///*-*      are of course always accepted.  Actual steps are random
///*-*      multiples of the nominal steps (DIRIN).

   virtual void   mnset();
///*-*-*-*-*Interprets the commands that start with SET and SHOW*-*-*-*-*-*-*
///*-*        Called from MNEXCM
///*-*        file characteristics for SET INPUT
///*-*       'SET ' or 'SHOW',  'ON ' or 'OFF', 'SUPPRESSED' or 'REPORTED  '
///*-*        explanation of print level numbers -1:3  and strategies 0:2
///*-*        identification of debug options
///*-*        things that can be set or shown
///*-*        options not intended for normal users

   virtual void   mnsimp();
///*-*-*-*-*Minimization using the simplex method of Nelder and Mead*-*-*-*-*

   virtual void   mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat);
///*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
///*-*       User-called
///*-*          Namely, it returns:
///*-*        FMIN: the best function value found so far
///*-*        FEDM: the estimated vertical distance remaining to minimum
///*-*        ERRDEF: the value of UP defining parameter uncertainties
///*-*        NPARI: the number of currently variable parameters
///*-*        NPARX: the highest (external) parameter number defined by user
///*-*        ISTAT: a status integer indicating how good is the covariance
///*-*           matrix:  0= not calculated at all
///*-*                    1= approximation only, not accurate
///*-*                    2= full matrix, but forced positive-definite
///*-*                    3= full accurate covariance matrix

   virtual void   mntiny(volatile Double_t epsp1, Double_t &epsbak);
///*-*-*-*-*-*-*-*To find the machine precision*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*        Compares its argument with the value 1.0, and returns
///*-*        the value .TRUE. if they are equal.  To find EPSMAC
///*-*        safely by foiling the Fortran optimizer

   Bool_t         mnunpt(TString &cfname);
///*-*-*-*-*-*Returns .TRUE. if CFNAME contains unprintable characters*-*-*-*

   virtual void   mnvert(Double_t *a, Int_t l, Int_t m, Int_t n, Int_t &ifail);
///*-*-*-*-*-*-*-*-*-*-*-*Inverts a symmetric matrix*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*        inverts a symmetric matrix.   matrix is first scaled to
///*-*        have all ones on the diagonal (equivalent to change of units)
///*-*        but no pivoting is done since matrix is positive-definite.

   virtual void   mnwarn(const char *copt, const char *corg, const char *cmes);
///*-*-*-*-*-*-*-*-*-*-*-*Prints Warning messages*-*-*-*-*-*-*-*-*-*-*-*-*-*
///*-*     If COPT='W', CMES is a WARning message from CORG.
///*-*     If COPT='D', CMES is a DEBug message from CORG.
///*-*         If SET WARnings is in effect (the default), this routine
///*-*             prints the warning message CMES coming from CORG.
///*-*         If SET NOWarnings is in effect, the warning message is
///*-*             stored in a circular buffer of length kMAXMES.
///*-*         If called with CORG=CMES='SHO', it prints the messages in
///*-*             the circular buffer, FIFO, and empties the buffer.

   virtual void   mnwerr();
///*-*-*-*-*-*-*-*Calculates the WERR, external parameter errors*-*-*-*-*-*-*
///*-*      and the global correlation coefficients, to be called
///*-*      whenever a new covariance matrix is available.

   virtual Int_t  Release( Int_t parNo );/// release a parameter
   virtual Int_t  SetErrorDef( Double_t up );
/// To get the n-sigma contour the error def parameter "up" has to set to n^2.

   virtual void   SetFCN(void *fcn);
///*-*-*-*-*-*-*To set the address of the minimization function*-*-*-*-*-*-*-*
///     this function is called by CINT instead of the function above

   virtual void   SetFCN(void (*fcn)(Int_t &, Double_t *, Double_t &f, Double_t *, Int_t));
///*-*-*-*-*-*-*To set the address of the minimization function*-*-*-*-*-*-*-*

   virtual void   SetGraphicsMode(Bool_t mode=kTRUE) {fGraphicsMode = mode;}
   virtual void   SetMaxIterations(Int_t maxiter=500) {fMaxIterations = maxiter;}
   virtual void   SetObjectFit(TObject *obj) {fObjectFit=obj;}
   virtual Int_t  SetPrintLevel( Int_t printLevel=0 );
///set Minuit print level
/// printlevel = -1  quiet (also suppresse all warnings)
///            =  0  normal
///            =  1  verbose
```

## code



## example




<!-- TMinuit.md ends here -->
