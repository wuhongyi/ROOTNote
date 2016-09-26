<!-- TBenchmark.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:31:46 2014 (+0800)
;; Last-Updated: 二 9月 13 18:16:24 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 6
;; URL: http://wuhongyi.github.io -->

# TBenchmark

系统自带计时

继承 TNamed

## class

```cpp
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
```

## code

```cpp
gBenchmark->Start("tree");
gBenchmark->Show("tree");
//输出格式如下：tree      : Real Time =   0.55 seconds Cpu Time =   0.17 seconds
```


<!-- TBenchmark.md ends here -->
