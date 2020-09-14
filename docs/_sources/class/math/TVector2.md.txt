<!-- TVector2.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 10月 11 08:50:53 2018 (+0800)
;; Last-Updated: 四 10月 11 08:51:26 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TVector2

**public TObject**

## class

```cpp
//------------------------------------------------------------------------------
//  data members
//------------------------------------------------------------------------------
protected:

   Double_t    fX;    // components of the vector
   Double_t    fY;
//------------------------------------------------------------------------------
//  function members
//------------------------------------------------------------------------------
public:

   typedef Double_t Scalar;   // to be able to use it with the ROOT::Math::VectorUtil functions

   TVector2 ();
   TVector2 (Double_t *s);
   TVector2 (Double_t x0, Double_t y0);
   virtual ~TVector2();
                                        // ****** unary operators

   TVector2&       operator  = (TVector2 const & v);
   TVector2&       operator += (TVector2 const & v);
   TVector2&       operator -= (TVector2 const & v);
   Double_t        operator *= (TVector2 const & v);
   TVector2&       operator *= (Double_t s);
   TVector2&       operator /= (Double_t s);

                                        // ****** binary operators

   friend TVector2       operator + (const TVector2&, const TVector2&);
   friend TVector2       operator + (const TVector2&, Double_t  );
   friend TVector2       operator + (Double_t  , const TVector2&);
   friend TVector2       operator - (const TVector2&, const TVector2&);
   friend TVector2       operator - (const TVector2&, Double_t  );
   friend Double_t       operator * (const TVector2&, const TVector2&);
   friend TVector2       operator * (const TVector2&, Double_t  );
   friend TVector2       operator * (Double_t  , const TVector2&);
   friend TVector2       operator / (const TVector2&, Double_t  );
   friend Double_t       operator ^ (const TVector2&, const TVector2&);

                                        // ****** setters
   void Set(const TVector2& v);
   void Set(Double_t x0, Double_t y0);
   void Set(float  x0, float  y0);
   void SetX(Double_t x0);
   void SetY(Double_t y0);
                                        // ****** other member functions

   Double_t Mod2() const { return fX*fX+fY*fY; };
   Double_t Mod () const;

   Double_t Px()   const { return fX; };
   Double_t Py()   const { return fY; };
   Double_t X ()   const { return fX; };
   Double_t Y ()   const { return fY; };

                                        // phi() is defined in [0,TWOPI]

   Double_t Phi           () const;
   Double_t DeltaPhi(const TVector2& v) const;
   void     SetMagPhi(Double_t mag, Double_t phi);

                                        // unit vector in the direction of *this

   TVector2 Unit() const;
   TVector2 Ort () const;

                                        // projection of *this to the direction
                                        // of TVector2 vector `v'

   TVector2 Proj(const TVector2& v) const;

                                        // component of *this normal to `v'

   TVector2 Norm(const TVector2& v) const;

                                        // rotates 2-vector by phi radians
   TVector2 Rotate (Double_t phi) const;

                                        // returns phi angle in the interval [0,2*PI)
   static Double_t Phi_0_2pi(Double_t x);

                                        // returns phi angle in the interval [-PI,PI)
   static Double_t Phi_mpi_pi(Double_t x);


   void Print(Option_t* option="") const;
```

<!-- TVector2.md ends here -->
