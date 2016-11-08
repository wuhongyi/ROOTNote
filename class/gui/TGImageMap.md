<!-- TGImageMap.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:43:14 2016 (+0800)
;; Last-Updated: 二 11月  8 20:58:47 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGImageMap

TGRegion 继承 TObject  
Describes a region

TGRegionWithId 继承 TGRegion  
Region with id, tooltip text and popup menu


TGImageMap 继承 TGPictureButton  
Clickable image (like MAP in HTML)


## class

**TGRegion**

```cpp
   enum ERegionType { kRectangle, kEllipse };

   TGRegion();
   TGRegion(Int_t x, Int_t y, UInt_t w, UInt_t h, ERegionType = kRectangle);
   TGRegion(Int_t n, TPoint *points, Bool_t winding = kFALSE);
   TGRegion(Int_t n, Int_t *x, Int_t *y, Bool_t winding = kFALSE);
   TGRegion(const TArrayS &x, const TArrayS &y, Bool_t winding = kFALSE);
   TGRegion(const TGRegion &reg);
   virtual ~TGRegion();

   Bool_t      Contains(const TPoint &p) const;
   Bool_t      Contains(Int_t x, Int_t y) const;
   TGRegion    Unite(const TGRegion &r) const;
   TGRegion    Intersect(const TGRegion &r) const;
   TGRegion    Subtract(const TGRegion &r) const;
   TGRegion    Eor(const TGRegion &r) const;
   TGDimension GetDimension() const;
   TGPosition  GetPosition() const;
   Bool_t      IsNull() const;
   Bool_t      IsEmpty() const;

   TGRegion operator|(const TGRegion &r) const { return Unite(r); }
   TGRegion operator+(const TGRegion &r) const { return Unite(r); }
   TGRegion operator&(const TGRegion &r) const { return Intersect(r); }
   TGRegion operator-(const TGRegion &r) const { return Subtract(r); }
   TGRegion operator^(const TGRegion &r) const { return Eor(r); }
   TGRegion& operator|=(const TGRegion &r) { return *this = *this | r; }
   TGRegion& operator+=(const TGRegion &r) { return *this = *this + r; }
   TGRegion& operator&=(const TGRegion &r) { return *this = *this & r; }
   TGRegion& operator-=(const TGRegion &r) { return *this = *this - r; }
   TGRegion& operator^=(const TGRegion &r) { return *this = *this ^ r; }
   Bool_t operator==(const TGRegion &r)  const;
   Bool_t operator!=(const TGRegion &r) const { return !(operator==(r)); }
   TGRegion &operator=(const TGRegion &r);
```


**TGRegionWithId**

```cpp
   TGRegionWithId();
   TGRegionWithId(Int_t id, Int_t x, Int_t y, UInt_t w, UInt_t h,
                  ERegionType = kRectangle);
   TGRegionWithId(Int_t id, Int_t n, TPoint *points, Bool_t winding = kFALSE);
   TGRegionWithId(const TGRegionWithId &reg);
   TGRegionWithId(const TGRegion &reg, Int_t id);
   virtual ~TGRegionWithId();

   Int_t        GetId() const { return fId; }
   TGToolTip   *GetToolTipText() const { return fTip; }
   void         SetToolTipText(const char *text, Long_t delayms,
                               const TGFrame *frame);
   TGPopupMenu *GetPopup() const { return fPopup; }
   void         SetPopup(TGPopupMenu *popup) { fPopup = popup; }
   void         DisplayPopup();
```


**TGImageMap**

```cpp
   enum ENavMode { kNavRegions, kNavGrid };

   TGImageMap(const TGWindow *p = 0, const TGPicture *pic = 0);
   TGImageMap(const TGWindow *p, const TString &pic);
   virtual ~TGImageMap();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleDoubleClick(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);

   ENavMode       GetNavMode() { return fNavMode; }
   void           AddRegion(const TGRegion &region, Int_t id);
   TGPopupMenu   *CreatePopup(Int_t id);
   TGPopupMenu   *GetPopup(Int_t id);

   void SetToolTipText(const char *text, Long_t delayms = 300);
   void SetToolTipText(Int_t id, const char *text, Long_t delayms = 300);
   void SetCursor(ECursor cursor = kHand) { fCursorMouseOver = cursor; }
   void SetPicture(const TGPicture * /*new_pic*/) { } // disabled

   virtual void RegionClicked(Int_t id); // *SIGNAL*
   virtual void DoubleClicked(Int_t id); // *SIGNAL*
   virtual void DoubleClicked();         // *SIGNAL*
   virtual void OnMouseOver(Int_t id);   // *SIGNAL*
   virtual void OnMouseOut(Int_t id);    // *SIGNAL*
```


## code

```cpp
#include "TGImageMap.h"		 
// TGImageMap
// 插入图片
TGImageMap* fImageMap;
fImageMap = new TGImageMap(frame, "picture.jpg");
frame->AddFrame(fImageMap);
fImageMap->Connect("RegionClicked(Int_t)", "WorldMap", this,"PrintCode(Int_t)");
```

## example




<!-- TGImageMap.md ends here -->
