<!-- TTimer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:31:46 2014 (+0800)
;; Last-Updated: 二 9月 13 19:52:39 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 7
;; URL: http://wuhongyi.cn -->

# TTimer

继承 TSysEvtHandler

可用于图形界面

Handles synchronous and a-synchronous timer events. You can use  this class in one of the following ways:   
- Sub-class TTimer and override the Notify() method.
- Re-implement the TObject::HandleTimer() method in your class and pass a pointer to this object to timer, see the SetObject() method.
- Pass an interpreter command to timer, see SetCommand() method.
- Create a TTimer, connect its Timeout() signal to the appropriate methods. Then when the time is up it will emit a Timeout() signal and call connected slots.

Minimum timeout interval is defined in TSystem::ESysConstants as kItimerResolution (currently 10 ms). 


## class

```cpp
   TTimer(Long_t milliSec = 0, Bool_t mode = kTRUE);
   TTimer(TObject *obj, Long_t milliSec, Bool_t mode = kTRUE);
   TTimer(const char *command, Long_t milliSec, Bool_t mode = kTRUE);
   virtual ~TTimer() { Remove(); }

   Bool_t         CheckTimer(const TTime &now);
   const char    *GetCommand() const { return fCommand.Data(); }
   TObject       *GetObject() { return fObject; }
   TTime          GetTime() const { return fTime; }
   UInt_t         GetTimerID() { return fTimeID;}
   TTime          GetAbsTime() const { return fAbsTime; }
   Bool_t         HasTimedOut() const { return fTimeout; }
   Bool_t         IsSync() const { return fSync; }
   Bool_t         IsAsync() const { return !fSync; }
   Bool_t         IsInterruptingSyscalls() const { return fIntSyscalls; }
   virtual Bool_t Notify();
   void           Add() { TurnOn(); }
   void           Remove() { TurnOff(); }
   void           Reset();
   void           SetCommand(const char *command);
   void           SetObject(TObject *object);
   void           SetInterruptSyscalls(Bool_t set = kTRUE);
   void           SetTime(Long_t milliSec) { fTime = milliSec; }
   void           SetTimerID(UInt_t id = 0) { fTimeID = id; }
   virtual void   Start(Long_t milliSec = -1, Bool_t singleShot = kFALSE);
   virtual void   Stop() { TurnOff(); }
   virtual void   TurnOn();                         //*SIGNAL*
   virtual void   TurnOff();                        //*SIGNAL*
   virtual void   Timeout() { Emit("Timeout()"); }  //*SIGNAL*

   static void    SingleShot(Int_t milliSec, const char *receiver_class,
                             void *receiver, const char *method);
```

## code

```cpp
//  Signal/slots example: 
TTimer *timer = new TTimer();
timer->Connect("Timeout()", "myObjectClassName", myObject, "TimerDone()");
timer->Start(2000, kTRUE);   // 2 seconds single-shot

// Timeout signal is emitted repeadetly with minimum timeout
// timer->Start(0, kFALSE);
```


## example

```cpp
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
```


<!-- TTimer.md ends here -->
