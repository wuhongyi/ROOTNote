<!-- TGTableContainer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:25:24 2016 (+0800)
;; Last-Updated: 三 9月 16 11:15:46 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGTableContainer-

TGTableFrame contains a composite frame that uses a TGMatrixLayout  
 to Layout the frames it contains.

TGTableHeaderFrame implements a frame used to display TGTableHeaders  
in a TGTable.                                                        
                                                                     
Both classes are for internal use in TGTable only. 


TGTableFrame 继承 TQObject

TGTableHeaderFrame 继承 TGCompositeFrame


## class

**TGTableFrame**

```cpp
   TGTableFrame(const TGWindow *p, UInt_t nrows, UInt_t ncolumns);
/// Create the container used to view TGTableCells. p.

   virtual ~TGTableFrame() { delete fFrame; }

   TGFrame *GetFrame() const { return fFrame; }

   void SetCanvas(TGCanvas *canvas) { fCanvas = canvas; }
   void HandleMouseWheel(Event_t *event);/// Handle mouse wheel to scroll.
   virtual void DrawRegion(Int_t x, Int_t y, UInt_t w, UInt_t h);/// Draw a region of container in viewport.
```


**TGTableHeaderFrame**

```cpp
   TGTableHeaderFrame(const TGWindow *p, TGTable *table = 0, UInt_t w = 1,
                      UInt_t h = 1, EHeaderType type = kColumnHeader,
                      UInt_t option = 0);
   ~TGTableHeaderFrame() {}

   virtual void DrawRegion(Int_t x, Int_t y, UInt_t w, UInt_t h);/// Draw a region of container in viewport.
```








<!-- TGTableContainer.md ends here -->
