<!-- TGCommandPlugin.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 1月 27 21:45:34 2017 (+0800)
;; Last-Updated: 五 1月 27 21:48:35 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGCommandPlugin

TGCommandPlugin 继承 TGMainFrame


## class

```cpp
   TGCommandPlugin(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~TGCommandPlugin();

   void           CheckRemote(const char * /*str*/);
/// Check if actual ROOT session is a remote one or a local one.

   void           HandleCommand();

   virtual Bool_t HandleTimer(TTimer *t);
/// Handle timer event.
```

## code





<!-- TGCommandPlugin.md ends here -->
