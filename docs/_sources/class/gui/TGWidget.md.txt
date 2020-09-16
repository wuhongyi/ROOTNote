<!-- TGWidget.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:09:34 2016 (+0800)
;; Last-Updated: 三 9月 16 11:17:16 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGWidget*

The widget base class. It is light weight (all inline service        
methods) and is typically used as mixin class (via multiple          
inheritance), see for example TGButton.



## class

```cpp
//--- Text justification modes

enum ETextJustification {
   kTextLeft    = BIT(0),
   kTextRight   = BIT(1),
   kTextCenterX = BIT(2),
   kTextTop     = BIT(3),
   kTextBottom  = BIT(4),
   kTextCenterY = BIT(5)
};


//--- Widget status

enum EWidgetStatus {
   kWidgetWantFocus = BIT(0),
   kWidgetHasFocus  = BIT(1),
   kWidgetIsEnabled = BIT(2)
};
```


**TGWidget**

```cpp
   TGWidget():
     fWidgetId(-1), fWidgetFlags(0), fMsgWindow(0), fCommand() { }
   TGWidget(Int_t id):
     fWidgetId(id), fWidgetFlags(0), fMsgWindow(0), fCommand() { }
   virtual ~TGWidget() { }

   Int_t         WidgetId() const { return fWidgetId; }
   Bool_t        IsEnabled() const { return (Bool_t)((fWidgetFlags & kWidgetIsEnabled) != 0); }
   Bool_t        HasFocus() const { return (Bool_t)((fWidgetFlags & kWidgetHasFocus) != 0); }
   Bool_t        WantFocus() const { return (Bool_t)((fWidgetFlags & kWidgetWantFocus) != 0); }
   virtual void  Associate(const TGWindow *w) { fMsgWindow = w; }
   virtual void  SetCommand(const char *command) { fCommand = command; }
   const char   *GetCommand() const { return fCommand.Data(); }
```


## code




## example



<!-- TGWidget.md ends here -->
