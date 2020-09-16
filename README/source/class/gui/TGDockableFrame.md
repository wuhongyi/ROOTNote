<!-- TGDockableFrame.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 1月 27 22:13:25 2017 (+0800)
;; Last-Updated: 三 9月 16 10:58:15 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGDockableFrame*

A TGDockableFrame is a frame with handles that allow it to be        
undocked (i.e. put in a transient frame of its own) and to be docked  
again or hidden and shown again. It uses the TGDockButton, which is  
a button with two vertical bars (||) and TGDockHideButton, which is  
a button with a small triangle. The TGUndockedFrame is a transient   
frame that on closure will put the frame back in the dock.

TGDockButton : public TGButton  
TGDockHideButton : public TGDockButton  
TGUndockedFrame : public TGTransientFrame  
TGDockableFrame : public TGCompositeFrame, public TGWidget  friend class TGUndockedFrame



## class

**TGDockButton**

```cpp
   TGDockButton(const TGCompositeFrame *p = 0, Int_t id = 1);/// Create a dock button (i.e. button with two vertical bars).
   virtual ~TGDockButton();/// Delete dock button.

   virtual Bool_t HandleCrossing(Event_t *event);/// Handle dock button crossing events.
```
   

**TGDockHideButton**

```cpp
   TGDockHideButton(const TGCompositeFrame *p = 0);/// Create a dock hide button (i.e. button with small triangle).

   void SetAspectRatio(Int_t a) { fAspectRatio = a; DoRedraw(); }
```


**TGUndockedFrame**

```cpp
   TGUndockedFrame(const TGWindow *p = 0, TGDockableFrame *dockable = 0);/// Create the undocked (transient) frame.
   virtual ~TGUndockedFrame();/// Delete undocked frame. Puts back dockable frame in its original container.

   void FixSize();/// Fix the size of the undocked frame so it cannot be changed via the WM.
   void CloseWindow();/// Close undocked frame (called via WM close button).
```


**TGDockableFrame**

```cpp
   TGDockableFrame(const TGWindow *p = 0, Int_t id = -1,
                   UInt_t options = kHorizontalFrame);/// Create a dockable frame widget.
   virtual ~TGDockableFrame();/// Cleanup dockable frame.

   virtual void AddFrame(TGFrame *f, TGLayoutHints *hints);/// Add frame to dockable frame container. Frame and hints are NOT adopted.

   virtual Bool_t ProcessMessage(Long_t, Long_t, Long_t);/// Process dockable frame messages.
   virtual void Docked() { Emit("Docked()"); }        //*SIGNAL*
   virtual void Undocked() { Emit("Undocked()"); }    //*SIGNAL*

   void UndockContainer();/// Undock container.
   void DockContainer(Int_t del = kTRUE);/// Dock container back to TGDockableFrame.

   void HideContainer();/// Hide dock container.
   void ShowContainer();/// Show dock container.

   void   EnableUndock(Bool_t onoff);/// Enable undocking.
   Bool_t EnableUndock() const { return fEnableUndock; }
   void   EnableHide(Bool_t onoff);/// Enable hiding.
   Bool_t EnableHide() const { return fEnableHide; }

   void SetWindowName(const char *name);/// Set window name so it appear as title of the undock window.

   Bool_t IsUndocked() const { return (fFrame != 0); }
   Bool_t IsHidden() const { return fHidden; }

   Bool_t IsFixedSize() const { return  fFixedSize; }
   void   SetFixedSize(Bool_t fixed) { fFixedSize = fixed; }

   TGCompositeFrame *GetContainer() const { return fContainer; }
   TGUndockedFrame  *GetUndocked() const { return fFrame; }

   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a dockable frame widget as a C++ statement(s) on output stream out.
```

## code



<!-- TGDockableFrame.md ends here -->
