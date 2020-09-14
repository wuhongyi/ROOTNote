<!-- TStopwatch.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:31:46 2014 (+0800)
;; Last-Updated: 六 8月 13 13:18:24 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->

# TStopwatch

```cpp
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
```


## code

```cpp
TStopwatch sw;
sw.Start();
printf("CPU: %8.3f\n",sw.CpuTime());
```



<!-- TStopwatch.md ends here -->
