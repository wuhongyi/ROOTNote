// note.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 3月 14 09:45:05 2015 (+0800)
// Last-Updated: 六 4月  2 16:01:46 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 7
// URL: http://wuhongyi.github.io 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TSpectrum();
TSpectrum(Int_t maxpositions, Double_t resolution=1);
virtual ~TSpectrum();
virtual TH1        *Background(const TH1 *hist,Int_t niter=20, Option_t *option="");
TH1                *GetHistogram() const {return fHistogram;}//暂未实施
Int_t               GetNPeaks() const {return fNPeaks;}
Double_t            *GetPositionX() const {return fPositionX;}
Double_t            *GetPositionY() const {return fPositionY;}
virtual void        Print(Option_t *option="") const;
virtual Int_t       Search(const TH1 *hist, Double_t sigma=2, Option_t *option="", Double_t threshold=0.05);//option 可选
static void         SetAverageWindow(Int_t w=3);   //set average window
static void         SetDeconIterations(Int_t n=3); //set max number of decon iterations
void                SetResolution(Double_t resolution=1);

//new functions January 2006
const char         *Background(Double_t *spectrum, Int_t ssize,Int_t numberIterations,Int_t direction, Int_t filterOrder,bool smoothing,Int_t smoothWindow,bool compton);//实际计算background函数
const char         *SmoothMarkov(Double_t *source, Int_t ssize, Int_t averWindow);
const char         *Deconvolution(Double_t *source, const Double_t *response,Int_t ssize, Int_t numberIterations,Int_t numberRepetitions, Double_t boost );
const char         *DeconvolutionRL(Double_t *source, const Double_t *response,Int_t ssize, Int_t numberIterations,Int_t numberRepetitions, Double_t boost );
const char         *Unfolding(Double_t *source,const Double_t **respMatrix,Int_t ssizex, Int_t ssizey,Int_t numberIterations,Int_t numberRepetitions, Double_t boost);
Int_t               SearchHighRes(Double_t *source,Double_t *destVector, Int_t ssize,Double_t sigma, Double_t threshold,bool backgroundRemove,Int_t deconIterations,bool markov, Int_t averWindow);//实际寻峰函数
Int_t               Search1HighRes(Double_t *source,Double_t *destVector, Int_t ssize,Double_t sigma, Double_t threshold,bool backgroundRemove,Int_t deconIterations,bool markov, Int_t averWindow);

static Int_t        StaticSearch(const TH1 *hist, Double_t sigma=2, Option_t *option="goff", Double_t threshold=0.05);
static TH1         *StaticBackground(const TH1 *hist,Int_t niter=20, Option_t *option="");


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Int_t npeaks=10;
TH1F *h = new TH1F("h","test",500,0,1000);
TSpectrum *s = new TSpectrum(2*npeaks);
Int_t nfound = s->Search(h,2,"",0.1);
double *number=s->GetPositionX();
for (int i = 0; i<nfound; ++i)
  {
    cout<<number[i]<<endl;
  }
cout<<"!!!:"<<s->GetNPeaks()<<endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

virtual TH1        *Background(const TH1 *hist,Int_t niter=20, Option_t *option="");

enum {
  kBackOrder2 =0,
  kBackOrder4 =1,
  kBackOrder6 =2,
  kBackOrder8 =3,
  kBackIncreasingWindow =0,
  kBackDecreasingWindow =1,
  kBackSmoothing3 =3,
  kBackSmoothing5 =5,
  kBackSmoothing7 =7,
  kBackSmoothing9 =9,
  kBackSmoothing11 =11,
  kBackSmoothing13 =13,
  kBackSmoothing15 =15
};

// One-dimensional background estimation function.
// This function calculates the background spectrum in the input histogram h.The background is returned as a histogram.

// Function parameters:

// h: input 1-d histogram
// numberIterations, (default value = 20).Increasing numberIterations make the result smoother and lower.
// option: may contain one of the following options:

// to set the direction parameter
// "BackIncreasingWindow". By default the direction is BackDecreasingWindow
// filterOrder-order of clipping filter,  (default "BackOrder2")
// -possible values= "BackOrder4"
// "BackOrder6"
// "BackOrder8"
// "nosmoothing"- if selected, the background is not smoothed
// By default the background is smoothed.
// smoothWindow-width of smoothing window, (default is "BackSmoothing3")
// -possible values= "BackSmoothing5"
// "BackSmoothing7"
// "BackSmoothing9"
// "BackSmoothing11"
// "BackSmoothing13"
// "BackSmoothing15"
// "Compton" if selected the estimation of Compton edge
// will be included.
// "same" : if this option is specified, the resulting background
// histogram is superimposed on the picture in the current pad.

// NOTE that the background is only evaluated in the current range of h.
// ie, if h has a bin range (set via h->GetXaxis()->SetRange(binmin,binmax),
// the returned histogram will be created with the same number of bins
// as the input histogram h, but only bins from binmin to binmax will be filled
// with the estimated background.


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

virtual Int_t       Search(const TH1 *hist, Double_t sigma=2, Option_t *option="", Double_t threshold=0.05);

// One-dimensional peak search function
// This function searches for peaks in source spectrum in hin.The number of found peaks and their positions are written into the members fNpeaks and fPositionX. The search is performed in the current histogram range.

// Function parameters:
// hin:       pointer to the histogram of source spectrum
// sigma:   sigma of searched peaks, for details we refer to manual
// threshold: (default=0.05)  peaks with amplitude less than
// threshold*highest_peak are discarded.  0<threshold<1

// By default, the background is removed before deconvolution.
// Specify the option "nobackground" to not remove the background.

// By default the "Markov" chain algorithm is used.
// Specify the option "noMarkov" to disable this algorithm
// Note that by default the source spectrum is replaced by a new spectrum

// By default a polymarker object is created and added to the list of
// functions of the histogram. The histogram is drawn with the specified
// option and the polymarker object drawn on top of the histogram.
// The polymarker coordinates correspond to the npeaks peaks found in
// the histogram.

// A pointer to the polymarker object can be retrieved later via:

// TList *functions = hin->GetListOfFunctions();
// TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");

// Specify the option "goff" to disable the storage and drawing of the
// polymarker.
// To disable the final drawing of the histogram with the search results (in case
// you want to draw it yourself) specify "nodraw" in the options parameter.


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const char         *Background(Double_t *spectrum, Int_t ssize,Int_t numberIterations,Int_t direction, Int_t filterOrder,bool smoothing,Int_t smoothWindow,bool compton);

This function calculates background spectrum from source spectrum.
The result is placed in the vector pointed by spe1945ctrum pointer.
The goal is to separate the useful information (peaks) from useless
information (background).

method is based on Sensitive Nonlinear Iterative Peak (SNIP) clipping algorithm.
new value in the channel "i" is calculated

where p = 1, 2, ..., numberIterations. In fact it represents second order
difference filter (-1,2,-1).

One can also change the
direction of the change of the clipping window, the order of the clipping
filter, to include smoothing, to set width of smoothing window and to include
the estimation of Compton edges. On successful completion it returns 0. On
error it returns pointer to the string describing error.

Parameters:
spectrum: pointer to the vector of source spectrum
ssize: length of the spectrum vector
numberIterations: maximal width of clipping window,
direction:  direction of change of clipping window.Possible values: kBackIncreasingWindow, kBackDecreasingWindow
filterOrder: order of clipping filter.Possible values: kBackOrder2, kBackOrder4, kBackOrder6, kBackOrder8
smoothing: logical variable whether the smoothing operation in the estimation of background will be included.Possible values: kFALSE, kTRUE
smoothWindow: width of smoothing window.Possible values: kBackSmoothing3, kBackSmoothing5, kBackSmoothing7,kBackSmoothing9, kBackSmoothing11, kBackSmoothing13, kBackSmoothing15.
compton: logical variable whether the estimation of Compton edge will be included. Possible values: kFALSE, kTRUE.


Example 1 script Background_incr.c:
#include <TSpectrum>
void Background_incr() {
   Int_t i;
   Double_t nbins = 256;
   Double_t xmin  = 0;
   Double_t xmax  = nbins;
   Double_t * source = new Double_t[nbins];
   TH1F *back = new TH1F("back","",nbins,xmin,xmax);
   TH1F *d = new TH1F("d","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   back=(TH1F*) f->Get("back1;1");
   TCanvas *Background = gROOT->GetListOfCanvases()->FindObject("Background");
   if (!Background) Background =
     new TCanvas("Background",
                 "Estimation of background with increasing window",
                 10,10,1000,700);
   back->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=back->GetBinContent(i + 1);
   s->Background(source,nbins,6,kBackIncreasingWindow,kBackOrder2,kFALSE,
                 kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d->SetBinContent(i + 1,source[i]);
   d->SetLineColor(kRed);
   d->Draw("SAME L");
}

Example 2 script Background_decr.c:
#include <TSpectrum>
void Background_decr() {
   Int_t i;
   Double_t nbins = 256;
   Double_t xmin  = 0;
   Double_t xmax  = nbins;
   Double_t * source = new Double_t[nbins];
   TH1F *back = new TH1F("back","",nbins,xmin,xmax);
   TH1F *d = new TH1F("d","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   back=(TH1F*) f->Get("back1;1");
   TCanvas *Background = gROOT->GetListOfCanvases()->FindObject("Background");
   if (!Background) Background =
     new TCanvas("Background","Estimation of background with decreasing window",
                 10,10,1000,700);
   back->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=back->GetBinContent(i + 1);
   s->Background(source,nbins,6,kBackDecreasingWindow,kBackOrder2,kFALSE,
                 kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d->SetBinContent(i + 1,source[i]);
   d->SetLineColor(kRed);
   d->Draw("SAME L");
}

Example 3 script Background_width.c:
#include <TSpectrum>
void Background_width() {
   Int_t i;
   Double_t nbins = 256;
   Double_t xmin  = 0;
   Double_t xmax  = nbins;
   Double_t * source = new Double_t[nbins];
   TH1F *h = new TH1F("h","",nbins,xmin,xmax);
   TH1F *d1 = new TH1F("d1","",nbins,xmin,xmax);
   TH1F *d2 = new TH1F("d2","",nbins,xmin,xmax);
   TH1F *d3 = new TH1F("d3","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   h=(TH1F*) f->Get("back1;1");
   TCanvas *background = gROOT->GetListOfCanvases()->FindObject("background");
   if (!background) background = new TCanvas("background",
   "Influence of clipping window width on the estimated background",
   10,10,1000,700);
   h->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,4,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);
   d1->SetLineColor(kRed);
   d1->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,6,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d2->SetBinContent(i + 1,source[i]);
   d2->SetLineColor(kBlue);
   d2->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,8,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d3->SetBinContent(i + 1,source[i]);
   d3->SetLineColor(kGreen);
   d3->Draw("SAME L");
}

Example 4 script Background_width2.c:
#include <TSpectrum>
void Background_width2() {
   Int_t i;
   Double_t nbins = 4096;
   Double_t xmin  = 0;
   Double_t xmax  = 4096;
   Double_t * source = new Double_t[nbins];
   TH1F *h = new TH1F("h","",nbins,xmin,xmax);
   TH1F *d1 = new TH1F("d1","",nbins,xmin,xmax);
   TH1F *d2 = new TH1F("d2","",nbins,xmin,xmax);
   TH1F *d3 = new TH1F("d3","",nbins,xmin,xmax);
   TH1F *d4 = new TH1F("d4","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   h=(TH1F*) f->Get("back2;1");
   TCanvas *background = gROOT->GetListOfCanvases()->FindObject("background");
   if (!background) background = new TCanvas("background",
   "Influence of clipping window width on the estimated background",
   10,10,1000,700);
   h->SetAxisRange(0,1000);
   h->SetMaximum(20000);
   h->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,10,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);
   d1->SetLineColor(kRed);
   d1->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,20,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d2->SetBinContent(i + 1,source[i]);
   d2->SetLineColor(kBlue);
   d2->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,30,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d3->SetBinContent(i + 1,source[i]);
   d3->SetLineColor(kGreen);
   d3->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,10,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d4->SetBinContent(i + 1,source[i]);
   d4->SetLineColor(kMagenta);
   d4->Draw("SAME L");
}

Example 5 script Background_order.c:
#include <TSpectrum>
void Background_order() {
   Int_t i;
   Double_t nbins = 4096;
   Double_t xmin  = 0;
   Double_t xmax  = 4096;
   Double_t * source = new Double_t[nbins];
   TH1F *h = new TH1F("h","",nbins,xmin,xmax);
   TH1F *d1 = new TH1F("d1","",nbins,xmin,xmax);
   TH1F *d2 = new TH1F("d2","",nbins,xmin,xmax);
   TH1F *d3 = new TH1F("d3","",nbins,xmin,xmax);
   TH1F *d4 = new TH1F("d4","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   h=(TH1F*) f->Get("back2;1");
   TCanvas *background = gROOT->GetListOfCanvases()->FindObject("background");
   if (!background) background = new TCanvas("background",
   "Influence of clipping filter difference order on the estimated background",
   10,10,1000,700);
   h->SetAxisRange(1220,1460);
   h->SetMaximum(11000);
   h->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,40,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);
   d1->SetLineColor(kRed);
   d1->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,40,kBackDecreasingWindow,kBackOrder4,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d2->SetBinContent(i + 1,source[i]);
   d2->SetLineColor(kBlue);
   d2->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,40,kBackDecreasingWindow,kBackOrder6,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d3->SetBinContent(i + 1,source[i]);
   d3->SetLineColor(kGreen);
   d3->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,40,kBackDecreasingWindow,kBackOrder8,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d4->SetBinContent(i + 1,source[i]);
   d4->SetLineColor(kMagenta);
   d4->Draw("SAME L");
}

Example 6 script Background_smooth.c:
#include <TSpectrum>
void Background_smooth() {
   Int_t i;
   Double_t nbins = 4096;
   Double_t xmin  = 0;
   Double_t xmax  = nbins;
   Double_t * source = new Double_t[nbins];
   TH1F *h = new TH1F("h","",nbins,xmin,xmax);
   TH1F *d1 = new TH1F("d1","",nbins,xmin,xmax);
   TH1F *d2 = new TH1F("d2","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   h=(TH1F*) f->Get("back4;1");
   TCanvas *background = gROOT->GetListOfCanvases()->FindObject("background");
   if (!background) background = new TCanvas("background",
   "Estimation of background with noise",10,10,1000,700);
   h->SetAxisRange(3460,3830);
   h->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,6,kBackDecreasingWindow,kBackOrder2,kFALSE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);
   d1->SetLineColor(kRed);
   d1->Draw("SAME L");
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,6,kBackDecreasingWindow,kBackOrder2,kTRUE,
   kBackSmoothing3,kFALSE);
   for (i = 0; i < nbins; i++) d2->SetBinContent(i + 1,source[i]);
   d2->SetLineColor(kBlue);
   d2->Draw("SAME L");
}

Example 8 script Background_compton.c:
#include <TSpectrum>
void Background_compton() {
   Int_t i;
   Double_t nbins = 512;
   Double_t xmin  = 0;
   Double_t xmax  = nbins;
   Double_t * source = new Double_t[nbins];
   TH1F *h = new TH1F("h","",nbins,xmin,xmax);
   TH1F *d1 = new TH1F("d1","",nbins,xmin,xmax);
   TFile *f = new TFile("spectra\\TSpectrum.root");
   h=(TH1F*) f->Get("back3;1");
   TCanvas *background = gROOT->GetListOfCanvases()->FindObject("background");
   if (!background) background = new TCanvas("background",
   "Estimation of background with Compton edges under peaks",10,10,1000,700);
   h->Draw("L");
   TSpectrum *s = new TSpectrum();
   for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
   s->Background(source,nbins,10,kBackDecreasingWindow,kBackOrder8,kTRUE,
   kBackSmoothing5,,kTRUE);
   for (i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);
   d1->SetLineColor(kRed);
   d1->Draw("SAME L");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......





// 
// note.cc ends here








