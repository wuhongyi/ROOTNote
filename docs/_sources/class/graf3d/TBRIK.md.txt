<!-- TBRIK.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 1月 13 16:03:32 2018 (+0800)
;; Last-Updated: 三 9月 16 10:44:52 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TBRIK*

继承 TShape



## class

```cpp
public:
   TBRIK();

/*
A box with faces perpendicular to the axes.
It has 6 parameters:
  - name:       name of the shape
  - title:      shape's title
  - material:  (see TMaterial)
  - dx:         half-length of the box along the x-axis
  - dy:         half-length of the box along the y-axis
  - dz:         half-length of the box along the z-axis
*/
   TBRIK(const char *name, const char *title, const char *material, Float_t dx, Float_t dy, Float_t dz);
   virtual ~TBRIK();

/// Compute distance from point px,py to a BRIK
/// Compute the closest distance of approach from point px,py to each corner
/// point of the BRIK.
   virtual Int_t   DistancetoPrimitive(Int_t px, Int_t py);
   virtual const TBuffer3D &GetBuffer3D(Int_t reqSections) const;/// Get buffer 3D
   Float_t         GetDx() const {return fDx;}
   Float_t         GetDy() const {return fDy;}
   Float_t         GetDz() const {return fDz;}

/// Return total X3D needed by TNode::ls (when called with option "x")
   virtual void    Sizeof3D() const;

```


<!-- TBRIK.md ends here -->
