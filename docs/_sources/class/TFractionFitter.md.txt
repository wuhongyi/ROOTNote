<!-- TFractionFitter.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 13:57:41 2016 (+0800)
;; Last-Updated: 三 9月 16 12:46:54 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TFractionFitter*

The virtue of this fit is that it takes into account both data and Monte Carlo
statistical uncertainties. The way in which this is done is through a standard
likelihood fit using Poisson statistics; however, the template (MC) predictions
are also varied within statistics, leading to additional contributions to the
overall likelihood. This leads to many more fit parameters (one per bin per
template), but the minimisation with respect to these additional parameters is
done analytically rather than introducing them as formal fit parameters. Some
special care needs to be taken in the case of bins with zero content. For more
details please see the original publication cited above.

TFractionFitter 继承 TObject

## class

```cpp
   TFractionFitter();
   TFractionFitter(TH1* data, TObjArray *MCs, Option_t *option="");
/// TFractionFitter constructor. Does a complete initialisation (including
/// consistency checks, default fit range as the whole histogram but without
/// under- and overflows, and declaration of the fit parameters). Note that
/// the histograms are not copied, only references are used.
/// \param[in] data histogram to be fitted
/// \param[in] MCs  array of TH1* corresponding template distributions
/// \param[in] option   can be used to control the print level of the minimization algorithm
///            - option = "Q"  : quite - no message is printed
///            - option = "V"  : verbose - max print out
///            - option = ""   : default: print initial fraction values and result

   virtual ~TFractionFitter();

   //TVirtualFitter* GetFitter() const;
   ROOT::Fit::Fitter* GetFitter() const;
/// Give direct access to the underlying fitter class. This can be
/// used e.g. to modify parameter values or step sizes.

   void ErrorAnalysis(Double_t UP);
/// Set UP to the given value (see class TMinuit), and perform a MINOS minimisation.

   void SetRangeX(Int_t low, Int_t high);
/// Set the X range of the histogram to be used in the fit.
/// Use ReleaseRangeX() to go back to fitting the full histogram.
/// The consistency check ensures that no empty fit range occurs (and also
/// recomputes the bin content integrals).
/// \param[in] low lower X bin number
/// \param[in] high upper X bin number

   void ReleaseRangeX();/// Release restrictions on the X range of the histogram to be used in the fit.
   void SetRangeY(Int_t low, Int_t high);
/// Set the Y range of the histogram to be used in the fit (2D or 3D histograms only).
/// Use ReleaseRangeY() to go back to fitting the full histogram.
/// The consistency check ensures that no empty fit range occurs (and also
/// recomputes the bin content integrals).
/// \param[in] low lower X bin number
/// \param[in] high upper X bin number

   void ReleaseRangeY();/// Release restrictions on the Y range of the histogram to be used in the fit.
   void SetRangeZ(Int_t low, Int_t high);
/// Set the Z range of the histogram to be used in the fit (3D histograms only).
/// Use ReleaseRangeY() to go back to fitting the full histogram.
/// The consistency check ensures that no empty fit range occurs (and also
/// recomputes the bin content integrals).
/// \param[in] low lower X bin number
/// \param[in] high upper X bin number

   void ReleaseRangeZ();/// Release restrictions on the Z range of the histogram to be used in the fit.
   void ExcludeBin(Int_t bin);
/// Exclude the given bin from the fit. The bin numbering to be used is that
/// of TH1::GetBin().

   void IncludeBin(Int_t bin);
/// Include the given bin in the fit, if it was excluded before using ExcludeBin().
/// The bin numbering to be used is that of TH1::GetBin().

   void Constrain(Int_t parm, Double_t low, Double_t high);
/// Constrain the values of parameter number <parm> (the parameter numbering
/// follows that of the input template vector).
/// Use UnConstrain() to remove this constraint.

   void UnConstrain(Int_t parm);/// Remove the constraints on the possible values of parameter <parm>.
   void SetData(TH1 *data);
/// Change the histogram to be fitted to. Notes:
/// - Parameter constraints and settings are retained from a possible previous fit.
/// - Modifying the dimension or number of bins results in an error (in this case
///   rather instantiate a new TFractionFitter object)

   void SetMC(Int_t parm, TH1 *MC);
/// Change the histogram for template number <parm>. Notes:
/// - Parameter constraints and settings are retained from a possible previous fit.
/// - Modifying the dimension or number of bins results in an error (in this case
///   rather instantiate a new TFractionFitter object)

   void SetWeight(Int_t parm, TH1* weight);
/// Set bin by bin weights for template number <parm> (the parameter numbering
/// follows that of the input template vector).
/// Weights can be "unset" by passing a null pointer.
/// Consistency of the weights histogram with the data histogram is checked at
/// this point, and an error in case of problems.

   TFitResultPtr Fit();
/// Perform the fit with the default UP value.
/// The value returned is the minimisation status.

   void GetResult(Int_t parm, Double_t& value, Double_t& error) const;
/// Obtain the fit result for parameter <parm> (the parameter numbering
/// follows that of the input template vector).

   TH1* GetPlot();
/// Return the "template prediction" corresponding to the fit result (this is not
/// the same as the weighted sum of template distributions, as template statistical
/// uncertainties are taken into account).
/// Note that the name of this histogram will simply be the same as that of the
/// "data" histogram, prefixed with the string "Fraction fit to hist: ".
/// Note also that the histogram is managed by the TFractionFitter class, so the returned pointer will be invalid if 
/// the class is deleted 

   // This global function needs access to computeFCN()
   //friend void TFractionFitFCN(Int_t& npar, Double_t* gin, Double_t& f, Double_t* par, Int_t flag);

   // Goodness of fit
   Double_t GetChisquare() const;
/// Return the likelihood ratio Chi-squared (chi2) for the fit.
/// The value is computed when the fit is executed successfully.
/// Chi2 calculation is based on the "likelihood ratio" lambda,
/// lambda = L(y;n) / L(m;n),
/// where L(y;n) is the likelihood of the fit result <y> describing the data <n>
/// and L(m;n) is the likelihood of an unknown "true" underlying distribution
/// <m> describing the data <n>. Since <m> is unknown, the data distribution is
/// used instead,
/// lambda = L(y;n) / L(n;n).
/// Note that this ratio is 1 if the fit is perfect. The chi2 value is then
/// computed according to
/// chi2 = -2*ln(lambda).
/// This parameter can be shown to follow a Chi-square distribution. See for
/// example S. Baker and R. Cousins, "Clarification of the use of chi-square
/// and likelihood functions in fits to histograms", Nucl. Instr. Meth. A221,
/// pp. 437-442 (1984)

   Int_t GetNDF() const;
/// return the number of degrees of freedom in the fit
/// the fNDF parameter has been previously computed during a fit.
/// The number of degrees of freedom corresponds to the number of points
/// used in the fit minus the number of templates.

   Double_t GetProb() const;/// return the fit probability

   // MC predictions (smeared templates)
   TH1* GetMCPrediction(Int_t parm) const;
/// Return the adjusted MC template (Aji) for template (parm).
/// Note that the (Aji) times fractions only sum to the total prediction
/// of the fit if all weights are 1.
/// Note also that the histogram is managed by the TFractionFitter class, so the returned pointer will be invalid if 
/// the class is deleted 

   // FCN evaluation
   Double_t EvaluateFCN(const Double_t * par) {
      Double_t f = 0;
      ComputeFCN(f, par, 0);
      return f;
   }
```

## code

```cpp
{
  TH1F *data;                              //data histogram
  TH1F *mc0;                               // first MC histogram
  TH1F *mc1;                               // second MC histogram
  TH1F *mc2;                               // third MC histogram
  ....                                     // retrieve histograms
   TObjArray *mc = new TObjArray(3);        // MC histograms are put in this array
   mc->Add(mc0);
   mc->Add(mc1);
   mc->Add(mc2);
   TFractionFitter* fit = new TFractionFitter(data, mc); // initialise
   fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
   fit->SetRangeX(1,15);                    // use only the first 15 bins in the fit
   Int_t status = fit->Fit();               // perform the fit
   std::cout << "fit status: " << status << std::endl;
   if (status == 0) {                       // check on fit status
     TH1F* result = (TH1F*) fit->GetPlot();
     data->Draw("Ep");
     result->Draw("same");
   }
}
```


```cpp
/*
## Assumptions
A few assumptions need to be made for the fit procedure to be carried out:
 1 The total number of events in each template is not too small
    (so that its Poisson uncertainty can be neglected).
 2 The number of events in each bin is much smaller than the total
    number of events in each template (so that multinomial
    uncertainties can be replaced with Poisson uncertainties).

Biased fit uncertainties may result if these conditions are not fulfilled
(see e.g. arXiv:0803.2711).

## Instantiation
A fit object is instantiated through
    TFractionFitter* fit = new TFractionFitter(data, mc);
A number of basic checks (intended to ensure that the template histograms
represent the same "kind" of distribution as the data one) are carried out.
The TVirtualFitter object is then addressed and all fit parameters (the
template fractions) declared (initially unbounded).

## Applying constraints
Fit parameters can be constrained through

 fit->Constrain(parameter #, lower bound, upper bound);

Setting lower bound = upper bound = 0 removes the constraint (a la Minuit);
however, a function

    fit->Unconstrain(parameter #)

is also provided to simplify this.

## Setting parameter values
The function

    TVirtualFitter* vFit = fit->GetFitter();

is provided for direct access to the TVirtualFitter object. This allows to
set and fix parameter values, and set step sizes directly.

## Restricting the fit range
The fit range can be restricted through

    fit->SetRangeX(first bin #, last bin #);
and freed using

    fit->ReleaseRangeX();
For 2D histograms the Y range can be similarly restricted using

    fit->SetRangeY(first bin #, last bin #);
    fit->ReleaseRangeY();
and for 3D histograms also

    fit->SetRangeZ(first bin #, last bin #);
    fit->ReleaseRangeZ();
It is also possible to exclude individual bins from the fit through

    fit->ExcludeBin(bin #);
where the given bin number is assumed to follow the TH1::GetBin() numbering.
Any bins excluded in this way can be included again using the corresponding

    fit->IncludeBin(bin #);

## Weights histograms
Weights histograms (for a motivation see the above publication) can be specified
for the individual MC sources through

    fit->SetWeight(parameter #, pointer to weights histogram);
and unset by specifying a null pointer.

## Obtaining fit results
The fit is carried out through

    Int_t status = fit->Fit();
where  status  is the code returned from the "MINIMIZE" command. For fits
that converged, parameter values and errors can be obtained through

    fit->GetResult(parameter #, value, error);
and the histogram corresponding to the total Monte Carlo prediction (which
is not the same as a simple weighted sum of the input Monte Carlo distributions)
can be obtained by

    TH1* result = fit->GetPlot();
## Using different histograms
It is possible to change the histogram being fitted through

    fit->SetData(TH1* data);
and to change the template histogram for a given parameter number through

    fit->SetMC(parameter #, TH1* MC);
This can speed up code in case of multiple data or template histograms;
however, it should be done with care as any settings are taken over from
the previous fit. In addition, neither the dimensionality nor the numbers of
bins of the histograms should change (in that case it is better to instantiate
a new TFractionFitter object).
*/
```





## example




<!-- TFractionFitter.md ends here -->
