<!-- TGImageMap.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:43:14 2016 (+0800)
;; Last-Updated: 三 12月  7 21:08:19 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TGImageMap

A TGImageMap provides the functionality like a clickable image in    
a web browser with sensitive regions (MAP HTML tag).

TGImageMap (with TGRegion and TGRegionWithId help classes)


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
   TGRegion(Int_t x, Int_t y, UInt_t w, UInt_t h, ERegionType = kRectangle);/// Create and initialize a region with a rectangle.
   TGRegion(Int_t n, TPoint *points, Bool_t winding = kFALSE);/// Create and intialize a region with a polygon.
   TGRegion(Int_t n, Int_t *x, Int_t *y, Bool_t winding = kFALSE);/// Create and initialize a region with an X and Y array of points.
   TGRegion(const TArrayS &x, const TArrayS &y, Bool_t winding = kFALSE);/// Create and initialize a region with an X and a Y array of points.
   TGRegion(const TGRegion &reg);
   virtual ~TGRegion();

   Bool_t      Contains(const TPoint &p) const;/// Return true if point p is contained in the region.
   Bool_t      Contains(Int_t x, Int_t y) const;/// Return true if point (x,y) is contained in the region.
   TGRegion    Unite(const TGRegion &r) const;/// Return the union of this region with r.
   TGRegion    Intersect(const TGRegion &r) const;/// Returns a region which is the intersection of this region and r.
   TGRegion    Subtract(const TGRegion &r) const;/// Returns a region which is r subtracted from this region.
   TGRegion    Eor(const TGRegion &r) const;
/// Returns a region which is the difference between the union and
/// intersection this region and r.

   TGDimension GetDimension() const;/// Return dimension of region (widht, height).
   TGPosition  GetPosition() const;/// Return position of region (x, y).
   Bool_t      IsNull() const;/// Return true if region is not set.
   Bool_t      IsEmpty() const;/// Return true if region is empty.

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
   TGRegionWithId();/// Create GUI region (with id and possible tooltip).
   TGRegionWithId(Int_t id, Int_t x, Int_t y, UInt_t w, UInt_t h,
                  ERegionType = kRectangle);
/// Create GUI region (with id and possible tooltip).

   TGRegionWithId(Int_t id, Int_t n, TPoint *points, Bool_t winding = kFALSE);/// Create GUI region (with id and possible tooltip).
   TGRegionWithId(const TGRegionWithId &reg);/// Copy constructor.
   TGRegionWithId(const TGRegion &reg, Int_t id);/// Copy ctor which allows setting of new id.
   virtual ~TGRegionWithId();

   Int_t        GetId() const { return fId; }
   TGToolTip   *GetToolTipText() const { return fTip; }
   void         SetToolTipText(const char *text, Long_t delayms,
                               const TGFrame *frame);
/// Set tool tip text associated with this region. The delay is in
/// milliseconds (minimum 250). To remove tool tip call method with
/// text = 0.

   TGPopupMenu *GetPopup() const { return fPopup; }
   void         SetPopup(TGPopupMenu *popup) { fPopup = popup; }
   void         DisplayPopup();/// Display popup menu associated with this region.
```


**TGImageMap**

```cpp
   enum ENavMode { kNavRegions, kNavGrid };

   TGImageMap(const TGWindow *p = 0, const TGPicture *pic = 0);/// Create an image map widget.
   TGImageMap(const TGWindow *p, const TString &pic);/// Create an image map widget.
   virtual ~TGImageMap();/// Cleanup image map widget.

   virtual Bool_t HandleButton(Event_t *event);/// Handle button events.
   virtual Bool_t HandleDoubleClick(Event_t *event);/// Handle double click events.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion events.

   ENavMode       GetNavMode() { return fNavMode; }
   void           AddRegion(const TGRegion &region, Int_t id);/// Add a region to the image map.
   TGPopupMenu   *CreatePopup(Int_t id);/// Create popoup menu or returns existing for regions with specified id.
   TGPopupMenu   *GetPopup(Int_t id);/// Return popup for regions with specified id.

   void SetToolTipText(const char *text, Long_t delayms = 300);
/// Set tooltip text for main region.

   void SetToolTipText(Int_t id, const char *text, Long_t delayms = 300);
/// Set tooltip text for regions with specified id.

   void SetCursor(ECursor cursor = kHand) { fCursorMouseOver = cursor; }
   void SetPicture(const TGPicture * /*new_pic*/) { } // disabled

   virtual void RegionClicked(Int_t id); // *SIGNAL*
/// Handle when mouse was clicked on region id. Emits signal
/// RegionClicked(Int_t).


   virtual void DoubleClicked(Int_t id); // *SIGNAL*
/// Handle when mouse is double clicked on region id. Emits signal
/// DoubleClicked(Int_t).

   virtual void DoubleClicked();         // *SIGNAL*
/// Handle when mouse is double clicked on main map. Emits signal
/// DoubleClicked().

   virtual void OnMouseOver(Int_t id);   // *SIGNAL*
/// Handle when mouse moves over region id. Emits signal
/// OnMouseOver(Int_t).

   virtual void OnMouseOut(Int_t id);    // *SIGNAL*
/// Handle when mouse moves from region id. Emits signal
/// OnMouseOut(Int_t).   
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
