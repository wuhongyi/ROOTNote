<!-- Factory.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 22:03:02 2016 (+0800)
;; Last-Updated: 一 11月 28 22:31:44 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# Factory

This is the main MVA steering class: it creates all MVA methods,   
and guides them through the training, testing and evaluation phases

Factory 继承 Configurable

**namespace TMVA**

## class

```cpp
      typedef std::vector<IMethod*> MVector;

      // no default  constructor
      Factory( TString theJobName, TFile* theTargetFile, TString theOption = "" );

      // default destructor
      virtual ~Factory();

      virtual const char*  GetName() const { return "Factory"; }

      // add events to training and testing trees
      void AddSignalTrainingEvent    ( const std::vector<Double_t>& event, Double_t weight = 1.0 );
      void AddBackgroundTrainingEvent( const std::vector<Double_t>& event, Double_t weight = 1.0 );
      void AddSignalTestEvent        ( const std::vector<Double_t>& event, Double_t weight = 1.0 );
      void AddBackgroundTestEvent    ( const std::vector<Double_t>& event, Double_t weight = 1.0 );
      void AddTrainingEvent( const TString& className, const std::vector<Double_t>& event, Double_t weight );
      void AddTestEvent    ( const TString& className, const std::vector<Double_t>& event, Double_t weight );
      void AddEvent        ( const TString& className, Types::ETreeType tt, const std::vector<Double_t>& event, Double_t weight );
      Bool_t UserAssignEvents(UInt_t clIndex);
      TTree* CreateEventAssignTrees( const TString& name );

      DataSetInfo& AddDataSet( DataSetInfo& );
      DataSetInfo& AddDataSet( const TString&  );

      // special case: signal/background

      // Data input related
      void SetInputTrees( const TString& signalFileName, const TString& backgroundFileName, 
                          Double_t signalWeight=1.0, Double_t backgroundWeight=1.0 );
/// define the input trees for signal and background; no cuts are applied

      void SetInputTrees( TTree* inputTree, const TCut& SigCut, const TCut& BgCut );
      // Set input trees  at once
      void SetInputTrees( TTree* signal, TTree* background, 
                          Double_t signalWeight=1.0, Double_t backgroundWeight=1.0) ;
/// define the input trees for signal and background from single input tree,
/// containing both signal and background events distinguished by the type 
/// identifiers: SigCut and BgCut

      void AddSignalTree( TTree* signal,    Double_t weight=1.0, Types::ETreeType treetype = Types::kMaxTreeType );
      void AddSignalTree( TString datFileS, Double_t weight=1.0, Types::ETreeType treetype = Types::kMaxTreeType );
      void AddSignalTree( TTree* signal, Double_t weight, const TString& treetype );      

      // ... depreciated, kept for backwards compatibility
      void SetSignalTree( TTree* signal, Double_t weight=1.0);

      void AddBackgroundTree( TTree* background, Double_t weight=1.0, Types::ETreeType treetype = Types::kMaxTreeType );
      void AddBackgroundTree( TString datFileB,  Double_t weight=1.0, Types::ETreeType treetype = Types::kMaxTreeType );
      void AddBackgroundTree( TTree* background, Double_t weight, const TString & treetype );

      // ... depreciated, kept for backwards compatibility
      void SetBackgroundTree( TTree* background, Double_t weight=1.0 );

      void SetSignalWeightExpression( const TString& variable );
      void SetBackgroundWeightExpression( const TString& variable );

      // special case: regression
      void AddRegressionTree( TTree* tree, Double_t weight = 1.0,  
                              Types::ETreeType treetype = Types::kMaxTreeType ) { 
         AddTree( tree, "Regression", weight, "", treetype ); 
      }

      // general

      // Data input related
      void SetTree( TTree* tree, const TString& className, Double_t weight ); // depreciated
      void AddTree( TTree* tree, const TString& className, Double_t weight=1.0,
                    const TCut& cut = "",
                    Types::ETreeType tt = Types::kMaxTreeType );
      void AddTree( TTree* tree, const TString& className, Double_t weight, const TCut& cut, const TString& treeType );

      // set input variable
      void SetInputVariables  ( std::vector<TString>* theVariables ); // depreciated
      void AddVariable        ( const TString& expression, const TString& title, const TString& unit,
                                char type='F', Double_t min = 0, Double_t max = 0 );/// user inserts discriminating variable in data set info
      void AddVariable        ( const TString& expression, char type='F',
                                Double_t min = 0, Double_t max = 0 );// user inserts discriminating variable in data set info
      void AddTarget          ( const TString& expression, const TString& title = "", const TString& unit = "",
                                Double_t min = 0, Double_t max = 0 );/// user inserts target in data set info
      void AddRegressionTarget( const TString& expression, const TString& title = "", const TString& unit = "",
                                Double_t min = 0, Double_t max = 0 )
      {
         AddTarget( expression, title, unit, min, max );
      }
      void AddSpectator         ( const TString& expression, const TString& title = "", const TString& unit = "",
                                Double_t min = 0, Double_t max = 0 );
/// user inserts target in data set info

      // set weight for class
      void SetWeightExpression( const TString& variable, const TString& className = "" );

      // set cut for class
      void SetCut( const TString& cut, const TString& className = "" );
      void SetCut( const TCut& cut, const TString& className = "" );
      void AddCut( const TString& cut, const TString& className = "" );
      void AddCut( const TCut& cut, const TString& className = "" );


      //  prepare input tree for training
      void PrepareTrainingAndTestTree( const TCut& cut, const TString& splitOpt );
/// prepare the training and test trees
/// -> same cuts for signal and background

      void PrepareTrainingAndTestTree( TCut sigcut, TCut bkgcut, const TString& splitOpt );
/// prepare the training and test trees

      // ... deprecated, kept for backwards compatibility 
      void PrepareTrainingAndTestTree( const TCut& cut, Int_t Ntrain, Int_t Ntest = -1 );
/// prepare the training and test trees 
/// kept for backward compatibility

      void PrepareTrainingAndTestTree( const TCut& cut, Int_t NsigTrain, Int_t NbkgTrain, Int_t NsigTest, Int_t NbkgTest, 
                                       const TString& otherOpt="SplitMode=Random:!V" );
/// prepare the training and test trees

      MethodBase* BookMethod( TString theMethodName, TString methodTitle, TString theOption = "" );
/// Book a classifier or regression method

      MethodBase* BookMethod( Types::EMVA theMethod,  TString methodTitle, TString theOption = "" );
/// books MVA method; the option configuration string is custom for each MVA
/// the TString field "theNameAppendix" serves to define (and distinguish)
/// several instances of a given MVA, eg, when one wants to compare the
/// performance of various configurations

      MethodBase* BookMethod( TMVA::Types::EMVA /*theMethod*/, 
                              TString /*methodTitle*/, 
                              TString /*methodOption*/, 
                              TMVA::Types::EMVA /*theComposite*/, 
                              TString /*compositeOption = ""*/ ) { return 0; } 

      // optimize all booked methods (well, if desired by the method)
      void OptimizeAllMethods                 (TString fomType="ROCIntegral", TString fitType="FitGA");
/// iterates through all booked methods and sees if they use parameter tuning and if so..
/// does just that  i.e. calls "Method::Train()" for different parameter setttings and
/// keeps in mind the "optimal one"... and that's the one that will later on be used
/// in the main training loop.

      void OptimizeAllMethodsForClassification(TString fomType="ROCIntegral", TString fitType="FitGA") { OptimizeAllMethods(fomType,fitType); }
      void OptimizeAllMethodsForRegression    (TString fomType="ROCIntegral", TString fitType="FitGA") { OptimizeAllMethods(fomType,fitType); }

      // training for all booked methods
      void TrainAllMethods                 ();
      void TrainAllMethodsForClassification( void ) { TrainAllMethods(); }
      void TrainAllMethodsForRegression    ( void ) { TrainAllMethods(); }

      // testing
      void TestAllMethods();

      // performance evaluation
      void EvaluateAllMethods( void );
/// iterates over all MVAs that have been booked, and calls their evaluation methods

      void EvaluateAllVariables( TString options = "" ); 
/// iterates over all MVA input varables and evaluates them

      // delete all methods and reset the method vector
      void DeleteAllMethods( void );

      // accessors
      IMethod* GetMethod( const TString& title ) const;
/// returns pointer to MVA that corresponds to given method title

      Bool_t Verbose( void ) const { return fVerbose; }
      void SetVerbose( Bool_t v=kTRUE );

      // make ROOT-independent C++ class for classifier response 
      // (classifier-specific implementation)
      // If no classifier name is given, help messages for all booked 
      // classifiers are printed
      virtual void MakeClass( const TString& methodTitle = "" ) const;

      // prints classifier-specific hepl messages, dedicated to 
      // help with the optimisation and configuration options tuning.
      // If no classifier name is given, help messages for all booked 
      // classifiers are printed
      void PrintHelpMessage( const TString& methodTitle = "" ) const;
/// Print predefined help message of classifier
/// iterate over methods and test

      static TDirectory* RootBaseDir() { return (TDirectory*)fgTargetFile; }
```

## code



## example



<!-- Factory.md ends here -->
