// note.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 12月  5 11:31:46 2014 (+0800)
// Last-Updated: 五 12月 26 16:46:06 2014 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 5
// URL: http://wuhongyi.github.io 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TStopwatch.h"//计时类
   void        Start(Bool_t reset = kTRUE);
   void        Stop();
   void        Continue();
   Int_t       Counter() const { return fCounter; }
   Double_t    RealTime();
   void        Reset() { ResetCpuTime(); ResetRealTime(); }
   void        ResetCpuTime(Double_t time = 0) { Stop();  fTotalCpuTime = time; }
   void        ResetRealTime(Double_t time = 0) { Stop(); fTotalRealTime = time; }
   Double_t    CpuTime();
   void        Print(Option_t *option="") const;


  TStopwatch sw;
  sw.Start();
  printf("CPU: %8.3f\n",sw.CpuTime());


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TBenchmark.h"//系统自带计时： 
   Int_t              GetBench(const char *name) const;
   Float_t            GetCpuTime(const char *name);
   Float_t            GetRealTime(const char *name);
   virtual void       Print(Option_t *name="") const;
   virtual void       Reset();
   virtual void       Show(const char *name);
   virtual void       Start(const char *name);
   virtual void       Stop(const char *name);
   virtual void       Summary(Float_t &rt, Float_t &cp);
   R__EXTERN TBenchmark  *gBenchmark;


gBenchmark->Start("tree");
gBenchmark->Show("tree");
//输出格式如下：tree      : Real Time =   0.55 seconds Cpu Time =   0.17 seconds
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// demo of Timers
Int_t i;
Float_t ratio;
TSlider *slider;
TCanvas *c1;
void hsumTimer(Int_t nfill=100000)
{
// Simple example illustrating how to use the C++ interpreter
// to fill histograms in a loop and show the graphics results
// This program is a variant of the tutorial "hsum".
// It illustrates the use of Timers.
  c1 = new TCanvas("c1","The HSUM example",200,10,600,400);
  c1->SetGrid();

// Create some histograms.
  total  = new TH1F("total","This is the total distribution",100,-4,4);
  main   = new TH1F("main","Main contributor",100,-4,4);
  s1     = new TH1F("s1","This is the first signal",100,-4,4);
  s2     = new TH1F("s2","This is the second signal",100,-4,4);
  total->Sumw2();   // store the sum of squares of weights
  total->SetMarkerStyle(21);
  total->SetMarkerSize(0.7);
  main->SetFillColor(16);
  s1->SetFillColor(42);
  s2->SetFillColor(46);
  total->SetMaximum(nfill/20.);
  total->Draw("e1p");
  main->Draw("same");
  s1->Draw("same");
  s2->Draw("same");
  c1->Update();slider = new TSlider("slider",
     "test",4.2,0,4.6,0.8*total->GetMaximum(),38);
  slider->SetFillColor(46);

// Create a TTimer (hsumUpdate called every 30 msec)
  TTimer timer("hsumUpdate()",30); 
  timer.TurnOn();

 // Fill histograms randomly
  Float_t xs1, xs2, xmain;
  gRandom->SetSeed();
  for (Int_t i=0; i<nfill; i++) {
     ratio = Float_t(i)/Float_t(nfill);
     if (gSystem->ProcessEvents()) break;
     xmain = gRandom->Gaus(-1,1.5);
     xs1   = gRandom->Gaus(-0.5,0.5);
     xs2   = gRandom->Landau(1,0.15);
     main->Fill(xmain);
     s1->Fill(xs1,0.3);
     s2->Fill(xs2,0.2);
     total->Fill(xmain);
     total->Fill(xs1,0.3);
     total->Fill(xs2,0.2);
  }
  timer.TurnOff();
  hsumUpdate();
}

void hsumUpdate()
{
// called when Timer times out
   if (slider) slider->SetRange(0,ratio);
   c1->Modified();
   c1->Update();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......





// 
// note.cc ends here
