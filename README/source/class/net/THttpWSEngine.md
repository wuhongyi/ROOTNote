<!-- THttpWSEngine.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 6月  6 01:00:31 2018 (+0800)
;; Last-Updated: 三 6月  6 01:01:37 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# THttpWSEngine

THttpWSEngine : public TNamed

Internal instance used to exchange WS functionality between          
THttpServer and THttpWSHandler. Normally should not be used directly

## class

```cpp
   virtual ~THttpWSEngine();

   virtual UInt_t GetId() const = 0;

   virtual void ClearHandle() = 0;

   virtual void Send(const void *buf, int len) = 0;

   virtual void SendCharStar(const char *str);
/// Envelope for sending string via the websocket

   virtual Bool_t PreviewData(THttpCallArg *) { return kFALSE; }
```


<!-- THttpWSEngine.md ends here -->
