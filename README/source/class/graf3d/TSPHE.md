<!-- TSPHE.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 1月 13 16:17:58 2018 (+0800)
;; Last-Updated: 三 9月 16 10:44:19 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TSPHE*

继承 TShape



## class

```cpp
   TSPHE();

/*
It has 9 parameters:
  - name:       name of the shape
  - title:      shape's title
  - material:  (see TMaterial)
  - rmin:       minimum radius
  - rmax:       maximum radius
  - themin:     theta min
  - themax:     theta max
  - phimin:     phi min
  - phimax:     phi max
ROOT color indx = max(i-i0,j-j0);
*/
   TSPHE(const char *name, const char *title, const char *material, Float_t rmin, Float_t rmax, Float_t themin,
         Float_t themax, Float_t phimin, Float_t phimax);/// SPHE shape normal constructor

/// SPHE shape "simplified" constructor
   TSPHE(const char *name, const char *title, const char *material, Float_t rmax);
   virtual ~TSPHE();

/// Compute distance from point px,py to a PSPHE
/// Compute the closest distance of approach from point px,py to each
/// computed outline point of the PSPHE (stolen from PCON).
   virtual Int_t   DistancetoPrimitive(Int_t px, Int_t py);
   virtual const TBuffer3D &GetBuffer3D(Int_t reqSections) const;/// Get buffer 3d.
   virtual Float_t GetRmin() const {return fRmin;}
   virtual Float_t GetRmax() const {return fRmax;}
   virtual Float_t GetThemin() const {return fThemin;}
   virtual Float_t GetThemax() const {return fThemax;}
   virtual Float_t GetPhimin() const {return fPhimin;}
   virtual Float_t GetPhimax() const {return fPhimax;}
   virtual Float_t GetAspectRatio() const { return fAspectRatio;}
   virtual Int_t   GetNumberOfDivisions () const {return fNdiv;}
   virtual void    SetAspectRatio(Float_t factor=1.0){ fAspectRatio = factor; MakeTableOfCoSin();}
   virtual void    SetEllipse(const Float_t *factors);/// Set ellipse.

/// Set number of divisions.
   virtual void    SetNumberOfDivisions (Int_t p);

/// Return total X3D needed by TNode::ls (when called with option "x")
   virtual void    Sizeof3D() const;
```


<!-- TSPHE.md ends here -->
