<!-- TGSpeedo.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 14 20:47:06 2016 (+0800)
;; Last-Updated: 三 9月 16 11:15:00 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGSpeedo*

TGSpeedo is a widget looking like a speedometer, with a needle,      
a counter and a small odometer window.                               
                                                                     
Three thresholds are configurable, with their glowing color          
A peak mark can be enabled, allowing to keep track of the highest    
value displayed. The mark can be reset by right-clicking on the      
widget.                                                              
Two signals are available:                                           
 - OdoClicked(): when user click on the small odometer window        
 - LedClicked(): when user click on the small led near the counter


TGSpeedo 继承 TGFrame, TGWidget


## class

```cpp
   enum EGlowColor { kNoglow, kGreen, kOrange, kRed };

   TGSpeedo(const TGWindow *p = 0, int id = -1);/// TGSpeedo widget constructor.
   TGSpeedo(const TGWindow *p, Float_t smin, Float_t smax,
            const char *lbl1 = "", const char *lbl2 = "",
            const char *dsp1 = "", const char *dsp2 = "", int id = -1);/// TGSpeedo widget constructor.
   virtual ~TGSpeedo();/// TGSpeedo widget Destructor.

   virtual TGDimension  GetDefaultSize() const;/// Return default dimension of the widget.
   virtual Bool_t       HandleButton(Event_t *event);/// Handle mouse button event.

   const TGPicture     *GetPicture() const { return fBase; }
   TImage              *GetImage() const { return fImage; }
   Float_t              GetPeakVal() const { return fPeakVal; }
   Float_t              GetScaleMin() const { return fScaleMin; }
   Float_t              GetScaleMax() const { return fScaleMax; }
   Bool_t               IsThresholdActive() { return fThresholdActive; }

   void Build();/// Build TGSpeedo widget.
   void Glow(EGlowColor col = kGreen);/// Make speedo glowing.
   void StepScale(Float_t step);/// Increment/decrement scale (needle position) of "step" value.
   void SetScaleValue(Float_t val);/// Set actual scale (needle position) value.
   void SetScaleValue(Float_t val, Int_t damping);/// Set actual scale (needle position) value.
   void SetOdoValue(Int_t val);/// Set actual value of odo meter.
   void SetDisplayText(const char *text1, const char *text2 = "");
/// Set small display text (two lines).

   void SetLabelText(const char *text1, const char *text2 = "");
/// Set main label text (two lines).

   void SetMinMaxScale(Float_t min, Float_t max);/// Set min and max scale values.
   void SetThresholds(Float_t th1 = 0.0, Float_t th2 = 0.0, Float_t th3 = 0.0)
             { fThreshold[0] = th1; fThreshold[1] = th2; fThreshold[2] = th3; }
   void SetThresholdColors(EGlowColor col1, EGlowColor col2, EGlowColor col3)
             { fThresholdColor[0] = col1; fThresholdColor[1] = col2; fThresholdColor[2] = col3; }
   void EnableThreshold() { fThresholdActive = kTRUE; }
   void DisableThreshold() { fThresholdActive = kFALSE; Glow(kNoglow); fClient->NeedRedraw(this);}
   void EnablePeakMark() { fPeakMark = kTRUE; }
   void DisablePeakMark() { fPeakMark = kFALSE; }
   void EnableMeanMark() { fMeanMark = kTRUE; }
   void DisableMeanMark() { fMeanMark = kFALSE; }
   void ResetPeakVal() { fPeakVal = fValue; fClient->NeedRedraw(this); }
   void SetMeanValue(Float_t mean) { fMeanVal = mean; fClient->NeedRedraw(this); }

   void OdoClicked() { Emit("OdoClicked()"); }   // *SIGNAL*
   void LedClicked() { Emit("LedClicked()"); }   // *SIGNAL*
```

## code



## example



<!-- TGSpeedo.md ends here -->
