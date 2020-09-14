<!-- TSpline.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 10月  5 10:40:31 2016 (+0800)
;; Last-Updated: 三 10月  5 10:54:57 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TSpline

直接使用的插值类：TSpline3、TSpline5

TSpline3 继承于 TSpline
TSpline5 继承于 TSpline

抽象基类 TSpline 继承于 TNamed, TAttLine, TAttFill, TAttMarker

TSplinePoly 继承于 TObject
TSplinePoly3 继承于 TSplinePoly
TSplinePoly5 继承于 TSplinePoly

## class

### TSpline3

```cpp
public:
   TSpline3() : TSpline() , fPoly(0), fValBeg(0), fValEnd(0),
      fBegCond(-1), fEndCond(-1) {}
   TSpline3(const char *title,
            Double_t x[], Double_t y[], Int_t n, const char *opt=0,
            Double_t valbeg=0, Double_t valend=0);
   TSpline3(const char *title,
            Double_t xmin, Double_t xmax,
            Double_t y[], Int_t n, const char *opt=0,
            Double_t valbeg=0, Double_t valend=0);
   TSpline3(const char *title,
            Double_t x[], const TF1 *func, Int_t n, const char *opt=0,
            Double_t valbeg=0, Double_t valend=0);
   TSpline3(const char *title,
            Double_t xmin, Double_t xmax,
            const TF1 *func, Int_t n, const char *opt=0,
            Double_t valbeg=0, Double_t valend=0);
   TSpline3(const char *title,
            const TGraph *g, const char *opt=0,
            Double_t valbeg=0, Double_t valend=0);
   TSpline3(const TH1 *h, const char *opt=0,
            Double_t valbeg=0, Double_t valend=0);
   TSpline3(const TSpline3&);
   TSpline3& operator=(const TSpline3&);
   Int_t    FindX(Double_t x) const;
   Double_t Eval(Double_t x) const;
   Double_t Derivative(Double_t x) const;
   virtual ~TSpline3() {if (fPoly) delete [] fPoly;}
   void GetCoeff(Int_t i, Double_t &x, Double_t &y, Double_t &b,
                 Double_t &c, Double_t &d) {x=fPoly[i].X();y=fPoly[i].Y();
                  b=fPoly[i].B();c=fPoly[i].C();d=fPoly[i].D();}
   void GetKnot(Int_t i, Double_t &x, Double_t &y) const
      {x=fPoly[i].X(); y=fPoly[i].Y();}
   virtual  void     SaveAs(const char *filename,Option_t *option="") const;
   virtual  void     SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual  void     SetPoint(Int_t i, Double_t x, Double_t y);
   virtual  void     SetPointCoeff(Int_t i, Double_t b, Double_t c, Double_t d);
   static void Test();
```

### TSpline5

```cpp
public:
   TSpline5() : TSpline() , fPoly(0) {}
   TSpline5(const char *title,
            Double_t x[], Double_t y[], Int_t n,
            const char *opt=0, Double_t b1=0, Double_t e1=0,
            Double_t b2=0, Double_t e2=0);
   TSpline5(const char *title,
            Double_t xmin, Double_t xmax,
            Double_t y[], Int_t n,
            const char *opt=0, Double_t b1=0, Double_t e1=0,
            Double_t b2=0, Double_t e2=0);
   TSpline5(const char *title,
            Double_t x[], const TF1 *func, Int_t n,
            const char *opt=0, Double_t b1=0, Double_t e1=0,
            Double_t b2=0, Double_t e2=0);
   TSpline5(const char *title,
            Double_t xmin, Double_t xmax,
            const TF1 *func, Int_t n,
            const char *opt=0, Double_t b1=0, Double_t e1=0,
            Double_t b2=0, Double_t e2=0);
   TSpline5(const char *title,
            const TGraph *g,
            const char *opt=0, Double_t b1=0, Double_t e1=0,
            Double_t b2=0, Double_t e2=0);
   TSpline5(const TH1 *h,
            const char *opt=0, Double_t b1=0, Double_t e1=0,
            Double_t b2=0, Double_t e2=0);
   TSpline5(const TSpline5&);
   TSpline5& operator=(const TSpline5&);
   Int_t    FindX(Double_t x) const;
   Double_t Eval(Double_t x) const;
   Double_t Derivative(Double_t x) const;
   virtual ~TSpline5() {if (fPoly) delete [] fPoly;}
   void GetCoeff(Int_t i, Double_t &x, Double_t &y, Double_t &b,
                 Double_t &c, Double_t &d, Double_t &e, Double_t &f)
      {x=fPoly[i].X();y=fPoly[i].Y();b=fPoly[i].B();
      c=fPoly[i].C();d=fPoly[i].D();
      e=fPoly[i].E();f=fPoly[i].F();}
   void GetKnot(Int_t i, Double_t &x, Double_t &y) const
      {x=fPoly[i].X(); y=fPoly[i].Y();}
   virtual  void     SaveAs(const char *filename,Option_t *option="") const;
   virtual  void     SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual  void     SetPoint(Int_t i, Double_t x, Double_t y);
   virtual  void     SetPointCoeff(Int_t i, Double_t b, Double_t c, Double_t d,
                                   Double_t e, Double_t f);
   static void Test();
```

### TSpline

```cpp
public:
   TSpline() : fDelta(-1), fXmin(0), fXmax(0),
      fNp(0), fKstep(kFALSE), fHistogram(0), fGraph(0), fNpx(100) {}
   TSpline(const char *title, Double_t delta, Double_t xmin,
      Double_t xmax, Int_t np, Bool_t step) :
      TNamed("Spline",title), TAttFill(0,1),
      fDelta(delta), fXmin(xmin),
      fXmax(xmax), fNp(np), fKstep(step),
      fHistogram(0), fGraph(0), fNpx(100) {}
   virtual ~TSpline();

   virtual void     GetKnot(Int_t i, Double_t &x, Double_t &y) const =0;
   virtual Int_t    DistancetoPrimitive(Int_t px, Int_t py);
   virtual void     Draw(Option_t *option="");
   virtual void     ExecuteEvent(Int_t event, Int_t px, Int_t py);
   virtual Double_t GetDelta() const {return fDelta;}
   TH1F            *GetHistogram() const {return fHistogram;}
   virtual Int_t    GetNp()    const {return fNp;}
   virtual Int_t    GetNpx()   const {return fNpx;}
   virtual Double_t GetXmin()  const {return fXmin;}
   virtual Double_t GetXmax()  const {return fXmax;}
   virtual void     Paint(Option_t *option="");
   virtual Double_t Eval(Double_t x) const=0;
   virtual void     SaveAs(const char * /*filename*/,Option_t * /*option*/) const {;}
   void             SetNpx(Int_t n) {fNpx=n;}
```

### TSplinePoly

```cpp
public:
   TSplinePoly() :
      fX(0), fY(0) {}
   TSplinePoly(Double_t x, Double_t y) :
      fX(x), fY(y) {}
   TSplinePoly(TSplinePoly const &other);
   TSplinePoly &operator=(TSplinePoly const &other);

   Double_t &X() {return fX;}
   Double_t &Y() {return fY;}
   void GetKnot(Double_t &x, Double_t &y) const {x=fX; y=fY;}

   virtual Double_t Eval(Double_t) const {return fY;}
```

### TSplinePoly3

```cpp
public:
   TSplinePoly3() :
      fB(0), fC(0), fD(0) {}
   TSplinePoly3(Double_t x, Double_t y, Double_t b, Double_t c, Double_t d) :
      TSplinePoly(x,y), fB(b), fC(c), fD(d) {}
   TSplinePoly3(TSplinePoly3 const &other);
   TSplinePoly3 &operator=(TSplinePoly3 const &other);

   Double_t &B() {return fB;}
   Double_t &C() {return fC;}
   Double_t &D() {return fD;}
   Double_t Eval(Double_t x) const {
      Double_t dx=x-fX;
      return (fY+dx*(fB+dx*(fC+dx*fD)));
   }
   Double_t Derivative(Double_t x) const {
      Double_t dx=x-fX;
      return (fB+dx*(2*fC+3*fD*dx));      
   }
```

### TSplinePoly5

```cpp
public:
   TSplinePoly5() :
      fB(0), fC(0), fD(0), fE(0), fF(0) {}
   TSplinePoly5(Double_t x, Double_t y, Double_t b, Double_t c,
      Double_t d, Double_t e, Double_t f) :
      TSplinePoly(x,y), fB(b), fC(c), fD(d), fE(e), fF(f) {}
   TSplinePoly5(TSplinePoly5 const &other);
   TSplinePoly5 &operator=(TSplinePoly5 const &other);

   Double_t &B() {return fB;}
   Double_t &C() {return fC;}
   Double_t &D() {return fD;}
   Double_t &E() {return fE;}
   Double_t &F() {return fF;}
   Double_t Eval(Double_t x) const {
      Double_t dx=x-fX;
      return (fY+dx*(fB+dx*(fC+dx*(fD+dx*(fE+dx*fF)))));
   }
   Double_t Derivative(Double_t x) const{
      Double_t dx=x-fX;
      return (fB+dx*(2*fC+dx*(3*fD+dx*(4*fE+dx*(5*fF)))));
   }
```


## code



## example



<!-- TSpline.md ends here -->
