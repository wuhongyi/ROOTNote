<!-- TMinuitMinimizer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 15:17:21 2016 (+0800)
;; Last-Updated: 一 11月 28 15:27:52 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TMinuitMinimizer

TMinuitMinimizer class implementing the ROOT::Math::Minimizer interface using TMinuit.  
This class is normally instantiates using the plug-in manager(plug-in with name Minuit or TMinuit)
In addition the user can choose the minimizer algorithm: Migrad (the default one), Simplex, or Minimize (combined Migrad + Simplex)

TMinuitMinimizer 继承 ROOT::Math::Minimizer

## class

```cpp
   /**
      Default constructor
   */
   TMinuitMinimizer ( ROOT::Minuit::EMinimizerType type = ROOT::Minuit::kMigrad, unsigned int ndim = 0);

   /**
      Constructor from a char * (used by PM)
   */
   TMinuitMinimizer ( const char * type , unsigned int ndim = 0);

   /**
      Destructor (no operations)
   */
   ~TMinuitMinimizer ();


   /// set the function to minimize
   virtual void SetFunction(const ROOT::Math::IMultiGenFunction & func);
   // Set the objective function to be minimized, by passing a function object implement the
   // basic multi-dim Function interface. In this case the derivatives will be
   // calculated by Minuit
   // Here a TMinuit instance is created since only at this point we know the number of parameters

   /// set the function to minimize
   virtual void SetFunction(const ROOT::Math::IMultiGradFunction & func);
   // Set the objective function to be minimized, by passing a function object implement the
   // multi-dim gradient Function interface. In this case the function derivatives are provided
   // by the user via this interface and there not calculated by Minuit.

   /// set free variable
   virtual bool SetVariable(unsigned int ivar, const std::string & name, double val, double step);

   /// set upper/lower limited variable (override if minimizer supports them )
   virtual bool SetLimitedVariable(unsigned int ivar , const std::string & name , double val , double step , double /* lower */, double /* upper */);

   /// set lower limit variable  (override if minimizer supports them )
   virtual bool SetLowerLimitedVariable(unsigned int  ivar , const std::string & name , double val , double step , double lower );

   /// set upper limit variable (override if minimizer supports them )
   virtual bool SetUpperLimitedVariable(unsigned int ivar , const std::string & name , double val , double step , double upper );

   /// set fixed variable (override if minimizer supports them )
   virtual bool SetFixedVariable(unsigned int /* ivar */, const std::string & /* name */, double /* val */);

   /// set the value of an existing variable
   virtual bool SetVariableValue(unsigned int , double );

   /// set the step size of an existing variable
   virtual bool SetVariableStepSize(unsigned int , double );
   /// set the lower-limit of an existing variable
   virtual bool SetVariableLowerLimit(unsigned int , double );
   /// set the upper-limit of an existing variable
   virtual bool SetVariableUpperLimit(unsigned int , double );
   /// set the limits of an existing variable
   virtual bool SetVariableLimits(unsigned int ivar, double lower, double upper);
   /// fix an existing variable
   virtual bool FixVariable(unsigned int);
   /// release an existing variable
   virtual bool ReleaseVariable(unsigned int);
   /// query if an existing variable is fixed (i.e. considered constant in the minimization)
   /// note that by default all variables are not fixed
   virtual bool IsFixedVariable(unsigned int) const;
   /// get variable settings in a variable object (like ROOT::Fit::ParamsSettings)
   virtual bool GetVariableSettings(unsigned int, ROOT::Fit::ParameterSettings & ) const;


   /// method to perform the minimization
   virtual  bool Minimize();
   // perform the minimization using the algorithm chosen previously by the user
   // By default Migrad is used.
   // Return true if the found minimum is valid and update internal chached values of
   // minimum values, errors and covariance matrix.
   // Status of minimizer is set to:
   // migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult

   /// return minimum function value
   virtual double MinValue() const;

   /// return expected distance reached from the minimum
   virtual double Edm() const;

   /// return  pointer to X values at the minimum
   virtual const double *  X() const { return &fParams.front(); }

   /// return pointer to gradient values at the minimum
   virtual const double *  MinGradient() const { return 0; } // not available in Minuit2

   /// number of function calls to reach the minimum
   virtual unsigned int NCalls() const;

   /// this is <= Function().NDim() which is the total
   /// number of variables (free+ constrained ones)
   virtual unsigned int NDim() const { return fDim; }

   /// number of free variables (real dimension of the problem)
   /// this is <= Function().NDim() which is the total
   virtual unsigned int NFree() const;// return number of free parameters

   /// minimizer provides error and error matrix
   virtual bool ProvidesError() const { return true; }

   /// return errors at the minimum
   virtual const double * Errors() const { return  &fErrors.front(); }

   /** return covariance matrices elements
       if the variable is fixed the matrix is zero
       The ordering of the variables is the same as in errors
   */
   virtual double CovMatrix(unsigned int i, unsigned int j) const {
      return ( fCovar.size() > (i + fDim* j) ) ? fCovar[i + fDim* j] : 0;
   }

   /**
       Fill the passed array with the  covariance matrix elements
       if the variable is fixed or const the value is zero.
       The array will be filled as cov[i *ndim + j]
       The ordering of the variables is the same as in errors and parameter value.
       This is different from the direct interface of Minuit2 or TMinuit where the
       values were obtained only to variable parameters
   */
   virtual bool GetCovMatrix(double * cov) const;// get covariance matrix

   /**
       Fill the passed array with the Hessian matrix elements
       The Hessian matrix is the matrix of the second derivatives
       and is the inverse of the covariance matrix
       If the variable is fixed or const the values for that variables are zero.
       The array will be filled as h[i *ndim + j]
   */
   virtual bool GetHessianMatrix(double * h) const;
   // get Hessian - inverse of covariance matrix
   // just invert it
   // but need to get the compact form to avoid the zero for the fixed parameters

   ///return status of covariance matrix
   virtual int CovMatrixStatus() const;
   // return status of covariance matrix
   //           status:  0= not calculated at all
   //                    1= approximation only, not accurate
   //                    2= full matrix, but forced positive-definite
   //                    3= full accurate covariance matrix

   ///global correlation coefficient for variable i
   virtual double GlobalCC(unsigned int ) const;

   /// minos error for variable i, return false if Minos failed
   virtual bool GetMinosError(unsigned int i, double & errLow, double & errUp, int = 0);// global correlation coefficient for parameter i

   /**
      perform a full calculation of the Hessian matrix for error calculation
    */
   virtual bool Hesse();   // perform calculation of Hessian

   /**
      scan a parameter i around the minimum. A minimization must have been done before,
      return false if it is not the case
    */
   virtual bool Scan(unsigned int i, unsigned int &nstep, double * x, double * y, double xmin = 0, double xmax = 0);
   // scan a parameter (variable) around the minimum value
   // the parameters must have been set before
   // if xmin=0 && xmax == 0  by default scan around 2 sigma of the error
   // if the errors  are also zero then scan from min and max of parameter range
   // (if parameters are limited Minuit scan from min and max instead of 2 sigma by default)
   // (force in that case to use errors)

   /**
      find the contour points (xi,xj) of the function for parameter i and j around the minimum
      The contour will be find for value of the function = Min + ErrorUp();
    */
   virtual bool Contour(unsigned int i, unsigned int j, unsigned int & npoints, double *xi, double *xj);// contour plot for parameter i and j


   virtual void PrintResults();

   /// return reference to the objective function
   ///virtual const ROOT::Math::IGenFunction & Function() const;

   /// get name of variables (override if minimizer support storing of variable names)
   virtual std::string VariableName(unsigned int ivar) const;

   /// get index of variable given a variable given a name
   /// return always -1 . (It is Not implemented)
   virtual int VariableIndex(const std::string & name) const;

   /// static function to switch on/off usage of static global TMinuit instance (gMinuit)
   /// By default it is used (i.e. is on). Method returns the previous state
   bool static UseStaticMinuit(bool on = true);

   /// suppress the minuit warnings (if called with false will enable them)
   /// By default they are suppressed only when the printlevel is <= 0
   void SuppressMinuitWarnings(bool nowarn=true);

```


## code




## example




<!-- TMinuitMinimizer.md ends here -->
