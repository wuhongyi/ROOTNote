<!-- THttpEngine.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 6月  6 00:44:58 2018 (+0800)
;; Last-Updated: 三 6月  6 00:46:18 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# THttpEngine

THttpEngine : public TNamed

Abstract class for implementing http protocol for THttpServer

## class

```cpp
   virtual ~THttpEngine();

   /** Method to create all components of engine. Called once from by the server */
   virtual Bool_t Create(const char *) { return kFALSE; }

   /** Returns pointer to THttpServer associated with engine */
   THttpServer *GetServer() const { return fServer; }
```

<!-- THttpEngine.md ends here -->
