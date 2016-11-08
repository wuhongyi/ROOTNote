<!-- TGClient.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 20:20:22 2016 (+0800)
;; Last-Updated: 二 11月  8 20:24:13 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGClient

TGClient 继承 TObject, TQObject , friend TGCocoa

Window client. In client server windowing systems, like X11 this     
class is used to make the initial connection to the window server.

## class

```cpp
   TGClient(const char *dpyName = 0);
   virtual ~TGClient();

   const TGWindow *GetRoot() const;
   const TGWindow *GetDefaultRoot() const;
   void            SetRoot(TGWindow *root = 0);
   TGWindow       *GetWindowById(Window_t sw) const;
   TGWindow       *GetWindowByName(const char *name) const;

   UInt_t       GetDisplayWidth() const;
   UInt_t       GetDisplayHeight() const;

   Bool_t       IsEditable() const { return fRoot != fDefaultRoot; }
   Bool_t       IsEditDisabled() const;
   void         SetEditDisabled(Bool_t on = kTRUE);

   FontStruct_t GetFontByName(const char *name, Bool_t fixedDefault = kTRUE) const;
   Bool_t       GetColorByName(const char *name, Pixel_t &pixel) const;
   Pixel_t      GetHilite(Pixel_t base_color) const;
   Pixel_t      GetShadow(Pixel_t base_color) const;
   void         FreeColor(Pixel_t color) const;
   void         ForceRedraw() { fForceRedraw = kTRUE; }
   void         NeedRedraw(TGWindow *w, Bool_t force = kFALSE);
   void         CancelRedraw(TGWindow *w);
   void         RegisterWindow(TGWindow *w);
   void         UnregisterWindow(TGWindow *w);
   void         RegisterPopup(TGWindow *w);
   void         UnregisterPopup(TGWindow *w);
   void         AddUnknownWindowHandler(TGUnknownWindowHandler *h);
   void         RemoveUnknownWindowHandler(TGUnknownWindowHandler *h);
   void         AddIdleHandler(TGIdleHandler *h);
   void         RemoveIdleHandler(TGIdleHandler *h);
   Bool_t       HandleInput();
   void         ProcessLine(TString cmd, Long_t msg, Long_t parm1, Long_t parm2);
   void         WaitFor(TGWindow *w);
   void         WaitForUnmap(TGWindow *w);
   void         ResetWaitFor(TGWindow *w);
   EGEventType  GetWaitForEvent() const  { return fWaitForEvent;}
   Window_t     GetWaitForWindow() const { return fWaitForWindow; }
   void         SetWaitForWindow(Window_t wid) {fWaitForWindow = wid;}
   Bool_t       ProcessEventsFor(TGWindow *w);

   Bool_t       HandleEvent(Event_t *event);
   Bool_t       HandleMaskEvent(Event_t *event, Window_t wid);
   void         RegisteredWindow(Window_t w);      //*SIGNAL*
   void         ProcessedEvent(Event_t *event, Window_t wid);   //*SIGNAL*

   const TGResourcePool *GetResourcePool() const { return fResourcePool; }

   TGPicturePool   *GetPicturePool() const { return fPicturePool; }
   const TGPicture *GetPicture(const char *name);
   const TGPicture *GetPicture(const char *name, UInt_t new_width, UInt_t new_height);
   void             FreePicture(const TGPicture *pic);

   TGGCPool        *GetGCPool() const { return fGCPool; }
   TGGC            *GetGC(GCValues_t *values, Bool_t rw = kFALSE);
   void             FreeGC(const TGGC *gc);
   void             FreeGC(GContext_t gc);

   TGFontPool      *GetFontPool() const { return fFontPool; }
   TGFont          *GetFont(const char *font, Bool_t fixedDefault = kTRUE);
   TGFont          *GetFont(const TGFont *font);
   void             FreeFont(const TGFont *font);

   UInt_t           GetStyle() const { return fStyle; }
   void             SetStyle(UInt_t newstyle) { fStyle = newstyle; }
   void             SetStyle(const char *style);

   Colormap_t       GetDefaultColormap() const { return fDefaultColormap; }
   TGMimeTypes     *GetMimeTypeList() const { return fMimeTypeList; }

   THashList       *GetListOfWindows() const { return fWlist; }
   TList           *GetListOfPopups() const { return fPlist; }

   static TGClient *Instance();
```

```cpp
#ifndef __CINT__
#define gClient (TGClient::Instance())
#endif
```


## code



## example

<!-- TGClient.md ends here -->
