<!-- TGTab.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 15:46:55 2016 (+0800)
;; Last-Updated: 三 12月  7 19:16:36 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
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
   TGTabLayout(TGTab *main);/// Create a tab layout manager.

   virtual void Layout();/// Layout the tab widget.
   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGTab**

```cpp
   static FontStruct_t  GetDefaultFontStruct();/// Return default font structure in use.
   static const TGGC   &GetDefaultGC();/// Return default graphics context in use.

   TGTab(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
         GContext_t norm = GetDefaultGC()(),
         FontStruct_t font = GetDefaultFontStruct(),
         UInt_t options = kChildFrame,
         Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGTab();
/// Delete tab widget. This deletes the tab windows and the containers.
/// The tab string is deleted by the TGTabElement dtor.

   virtual TGCompositeFrame *AddTab(TGString *text);
/// Add a tab to the tab widget. Returns the new container, which
/// is owned by the tab widget. The text is adopted by the tab widget.

   virtual TGCompositeFrame *AddTab(const char *text);
/// Add a tab to the tab widget. Returns the new container. The container
/// is owned by the tab widget.

   virtual void              AddTab(const char *text, TGCompositeFrame *cf);
/// Add a tab to the tab widget and fill it with given TGCompositeFrame.

   virtual void              AddTab(TGString *text, TGCompositeFrame *cf);
/// Add a tab to the tab widget and fill it with given TGCompositeFrame.

   virtual void              NewTab(const char *text = "tab");   // *MENU*icon=bld_newtab.png*
/// Create new tab. Used in context menu.

   virtual void              RemoveTab(Int_t tabIndex = -1,
                                       Bool_t storeRemoved = kTRUE); // *MENU*icon=bld_removetab.png*
/// Remove container and tab of tab with index tabIndex.
/// Does NOT remove the container contents!

   virtual Bool_t            SetTab(Int_t tabIndex, Bool_t emit = kTRUE);
/// Brings the composite frame with the index tabIndex to the
/// front and generate the following event if the front tab has changed:
/// kC_COMMAND, kCM_TAB, tab id, 0.
/// Returns kFALSE if tabIndex is a not valid index

   virtual Bool_t            SetTab(const char *name, Bool_t emit = kTRUE);
/// Brings the composite frame with the name to the
/// front and generate the following event if the front tab has changed:
/// kC_COMMAND, kCM_TAB, tab id, 0.
/// Returns kFALSE if tab with name does not exist.

   virtual void              DrawBorder() { }

   TGCompositeFrame *GetContainer() const { return fContainer; }
   Int_t             GetCurrent() const { return fCurrent; }
   TGCompositeFrame *GetTabContainer(Int_t tabIndex) const;
/// Return container of tab with index tabIndex.
/// Return 0 in case tabIndex is out of range.

   TGCompositeFrame *GetTabContainer(const char *name) const;
/// Return the tab container of tab with string name.
/// Returns 0 in case name is not found.

   TGTabElement     *GetTabTab(Int_t tabIndex) const;
/// Return the tab element of tab with index tabIndex.
/// Returns 0 in case tabIndex is out of range.

   TGTabElement     *GetTabTab(const char *name) const;
/// Return the tab element of tab with string name.
/// Returns 0 in case name is not found.

   TGCompositeFrame *GetCurrentContainer() const { return GetTabContainer(fCurrent); }
   TGTabElement     *GetCurrentTab() const { return GetTabTab(fCurrent); }
   UInt_t            GetTabHeight() const { return fTabh; }
   Int_t             GetNumberOfTabs() const;/// Return number of tabs.
   virtual void      SetEnabled(Int_t tabIndex, Bool_t on = kTRUE);  //*MENU*
/// Enable or disable tab.

   virtual void      SetText(const char *text = "tab");              //*MENU*icon=bld_rename.png*
/// Set text to current tab.

   Bool_t            IsEnabled(Int_t tabIndex) const;/// Returns true if tab is enabled.

   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a tab widget as a C++ statement(s) on output stream out.

   virtual void CloseTab(Int_t id) { Emit("CloseTab(Int_t)", id); }  //*SIGNAL*
   virtual void Removed(Int_t id) { Emit("Removed(Int_t)", id); }    //*SIGNAL*
   virtual void Selected(Int_t id) { Emit("Selected(Int_t)", id); }  //*SIGNAL*
   virtual TGLayoutManager *GetLayoutManager() const;/// Return layout manager.
```


**TGTabElement**

```cpp
   TGTabElement(const TGWindow *p = 0, TGString *text = 0, UInt_t w = 1, UInt_t h = 1,
                GContext_t norm = TGTab::GetDefaultGC()(),
                FontStruct_t font = TGTab::GetDefaultFontStruct(),
                UInt_t options = kRaisedFrame,
                Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGTabElement();

   virtual void        DrawBorder();/// Draw little tab element.
   virtual TGDimension GetDefaultSize() const;/// Get default size of tab widget.
   const TGString     *GetText() const { return fText; }
   const char         *GetString() const { return fText->GetString(); }
   virtual Bool_t      HandleButton(Event_t *event);
/// Handle button event in the tab widget. Basically we only handle
/// button events in the small tabs.

   void                SetText(TGString *text);/// Set new tab text.
   virtual void        SetEnabled(Bool_t on = kTRUE) { fEnabled = on; }
   Bool_t              IsEnabled() const { return fEnabled; }
   virtual void        SetEditDisabled(UInt_t) {}
   virtual void        ShowClose(Bool_t on = kTRUE);
/// Show/hide close icon on the tab element, then apply layout
/// to compute correct elements size.

   Bool_t              IsCloseShown() const { return fShowClose; }
   virtual void        SetActive(Bool_t on = kTRUE) { fActive = on; }
   Bool_t              IsActive() const { return fActive; }
```


## code



## example





<!-- TGTab.md ends here -->
