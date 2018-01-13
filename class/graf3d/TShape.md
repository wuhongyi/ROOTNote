<!-- TShape.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 1月 13 16:23:57 2018 (+0800)
;; Last-Updated: 六 1月 13 16:27:59 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TShape

继承 public TNamed, public TAttLine, public TAttFill, public TAtt3D



This is the base class for all geometry shapes.  
The list of shapes currently supported correspond to the shapes in Geant version 3:

```cpp
   TBRIK,TCONE,TCONS,TGTRA,TPARA,TPCON,TPGON
   TTRAP,TTRD1,TTRD2,THYPE, TTUBE and TTUBS.
```

## class


```cpp
public:
   TShape();
   TShape(const char *name, const char *title, const char *material);
   TShape(const TShape&);
   TShape& operator=(const TShape&);
   virtual         ~TShape();

/// Stub to avoid forcing implementation at this stage
   virtual const   TBuffer3D &GetBuffer3D(Int_t reqSections) const;
   TMaterial      *GetMaterial()  const {return fMaterial;}
   virtual Int_t   GetNumber()     const {return fNumber;}
   Int_t           GetVisibility() const {return fVisibility;}

/// This method is used only when a shape is painted outside a TNode.
   virtual void    Paint(Option_t *option="");
   virtual void    SetName(const char *name);

/// Set points.
   virtual void    SetPoints(Double_t *points) const ;
   virtual void    SetVisibility(Int_t vis) {fVisibility = vis;} // *MENU*

/// Transform points (LocalToMaster)
   void            TransformPoints(Double_t *points, UInt_t NbPnts) const;
```

<!-- TShape.md ends here -->
