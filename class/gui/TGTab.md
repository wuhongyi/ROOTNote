<!-- TGTab.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 15:46:55 2016 (+0800)
;; Last-Updated: 二 11月  8 15:55:13 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGTab

The TGTab is user callable. The TGTabElement and TGTabLayout are     
is a service classes of the tab widget.                              


TGTabLayout 继承 TGLayoutManager


TGTab 继承 TGCompositeFrame, TGWidget

A tab widget contains a set of composite frames each with a little   
tab with a name (like a set of folders with tabs).                   

```
Clicking on a tab will bring the associated composite frame to the  
front and generate the following event:                             
kC_COMMAND, kCM_TAB, tab id, 0.
```


TGTabElement 继承 TGFrame



## class

**TGTabLayout**

```cpp
   TGTabLayout(TGTab *main);

   virtual void Layout();
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGTab**

```cpp
   static FontStruct_t  GetDefaultFontStruct();
   static const TGGC   &GetDefaultGC();

   TGTab(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
         GContext_t norm = GetDefaultGC()(),
         FontStruct_t font = GetDefaultFontStruct(),
         UInt_t options = kChildFrame,
         Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGTab();

   virtual TGCompositeFrame *AddTab(TGString *text);
   virtual TGCompositeFrame *AddTab(const char *text);
   virtual void              AddTab(const char *text, TGCompositeFrame *cf);
   virtual void              AddTab(TGString *text, TGCompositeFrame *cf);

   virtual void              NewTab(const char *text = "tab");   // *MENU*icon=bld_newtab.png*
   virtual void              RemoveTab(Int_t tabIndex = -1,
                                       Bool_t storeRemoved = kTRUE); // *MENU*icon=bld_removetab.png*
   virtual Bool_t            SetTab(Int_t tabIndex, Bool_t emit = kTRUE);
   virtual Bool_t            SetTab(const char *name, Bool_t emit = kTRUE);
   virtual void              DrawBorder() { }

   TGCompositeFrame *GetContainer() const { return fContainer; }
   Int_t             GetCurrent() const { return fCurrent; }
   TGCompositeFrame *GetTabContainer(Int_t tabIndex) const;
   TGCompositeFrame *GetTabContainer(const char *name) const;
   TGTabElement     *GetTabTab(Int_t tabIndex) const;
   TGTabElement     *GetTabTab(const char *name) const;
   TGCompositeFrame *GetCurrentContainer() const { return GetTabContainer(fCurrent); }
   TGTabElement     *GetCurrentTab() const { return GetTabTab(fCurrent); }
   UInt_t            GetTabHeight() const { return fTabh; }
   Int_t             GetNumberOfTabs() const;
   virtual void      SetEnabled(Int_t tabIndex, Bool_t on = kTRUE);  //*MENU*
   virtual void      SetText(const char *text = "tab");              //*MENU*icon=bld_rename.png*
   Bool_t            IsEnabled(Int_t tabIndex) const;

   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");

   virtual void CloseTab(Int_t id) { Emit("CloseTab(Int_t)", id); }  //*SIGNAL*
   virtual void Removed(Int_t id) { Emit("Removed(Int_t)", id); }    //*SIGNAL*
   virtual void Selected(Int_t id) { Emit("Selected(Int_t)", id); }  //*SIGNAL*
   virtual TGLayoutManager *GetLayoutManager() const;
```


**TGTabElement**

```cpp
   TGTabElement(const TGWindow *p = 0, TGString *text = 0, UInt_t w = 1, UInt_t h = 1,
                GContext_t norm = TGTab::GetDefaultGC()(),
                FontStruct_t font = TGTab::GetDefaultFontStruct(),
                UInt_t options = kRaisedFrame,
                Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGTabElement();

   virtual void        DrawBorder();
   virtual TGDimension GetDefaultSize() const;
   const TGString     *GetText() const { return fText; }
   const char         *GetString() const { return fText->GetString(); }
   virtual Bool_t      HandleButton(Event_t *event);
   void                SetText(TGString *text);
   virtual void        SetEnabled(Bool_t on = kTRUE) { fEnabled = on; }
   Bool_t              IsEnabled() const { return fEnabled; }
   virtual void        SetEditDisabled(UInt_t) {}
   virtual void        ShowClose(Bool_t on = kTRUE);
   Bool_t              IsCloseShown() const { return fShowClose; }
   virtual void        SetActive(Bool_t on = kTRUE) { fActive = on; }
   Bool_t              IsActive() const { return fActive; }
```


## code



## example





<!-- TGTab.md ends here -->
