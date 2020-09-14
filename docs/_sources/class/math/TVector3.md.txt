<!-- TVector3.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 3月 21 21:17:15 2018 (+0800)
;; Last-Updated: 三 3月 21 21:39:11 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TVector3

继承 public TObject


TVector3 is a general three vector class, which can be used for the description of different vectors in 3D.

## class

```cpp
   typedef Double_t Scalar;   // to be able to use it with the ROOT::Math::VectorUtil functions

   TVector3();

   TVector3(Double_t x, Double_t y, Double_t z);
   // The constructor.

   TVector3(const Double_t *);
   TVector3(const Float_t *);
   // Constructors from an array

   TVector3(const TVector3 &);
   // The copy constructor.

   virtual ~TVector3();
   // Destructor

   Double_t operator () (int) const;
   inline Double_t operator [] (int) const;
   // Get components by index (Geant4).

   Double_t & operator () (int);
   inline Double_t & operator [] (int);
   // Set components by index.

   inline Double_t x()  const;
   inline Double_t y()  const;
   inline Double_t z()  const;
   inline Double_t X()  const;
   inline Double_t Y()  const;
   inline Double_t Z()  const;
   inline Double_t Px() const;
   inline Double_t Py() const;
   inline Double_t Pz() const;
   // The components in cartesian coordinate system.

   inline void SetX(Double_t);
   inline void SetY(Double_t);
   inline void SetZ(Double_t);
   inline void SetXYZ(Double_t x, Double_t y, Double_t z);
   void        SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi);
   void        SetPtThetaPhi(Double_t pt, Double_t theta, Double_t phi);

   inline void GetXYZ(Double_t *carray) const;
   inline void GetXYZ(Float_t *carray) const;
   // Get the components into an array
   // not checked!

   Double_t Phi() const;
   // The azimuth angle. returns phi from -pi to pi

   Double_t Theta() const;
   // The polar angle.

   inline Double_t CosTheta() const;
   // Cosine of the polar angle.

   inline Double_t Mag2() const;
   // The magnitude squared (rho^2 in spherical coordinate system).

   Double_t Mag() const;
   // The magnitude (rho in spherical coordinate system).

   void SetPhi(Double_t);
   // Set phi keeping mag and theta constant (BaBar).

   void SetTheta(Double_t);
   // Set theta keeping mag and phi constant (BaBar).

   inline void SetMag(Double_t);
   // Set magnitude keeping theta and phi constant (BaBar).

   inline Double_t Perp2() const;
   // The transverse component squared (R^2 in cylindrical coordinate system).

   inline Double_t Pt() const;
   Double_t Perp() const;
   // The transverse component (R in cylindrical coordinate system).

   inline void SetPerp(Double_t);
   // Set the transverse component keeping phi and z constant.

   inline Double_t Perp2(const TVector3 &) const;
   // The transverse component w.r.t. given axis squared.

   inline Double_t Pt(const TVector3 &) const;
   Double_t Perp(const TVector3 &) const;
   // The transverse component w.r.t. given axis.

   inline Double_t DeltaPhi(const TVector3 &) const;
   Double_t DeltaR(const TVector3 &) const;///return deltaR with respect to v
   inline Double_t DrEtaPhi(const TVector3 &) const;
   inline TVector2 EtaPhiVector() const;
   void SetMagThetaPhi(Double_t mag, Double_t theta, Double_t phi);///setter with mag, theta, phi

   inline TVector3 & operator = (const TVector3 &);
   // Assignment.

   inline Bool_t operator == (const TVector3 &) const;
   inline Bool_t operator != (const TVector3 &) const;
   // Comparisons (Geant4).

   inline TVector3 & operator += (const TVector3 &);
   // Addition.

   inline TVector3 & operator -= (const TVector3 &);
   // Subtraction.

   inline TVector3 operator - () const;
   // Unary minus.

   inline TVector3 & operator *= (Double_t);
   // Scaling with real numbers.

   TVector3 Unit() const;
   // Unit vector parallel to this.

   inline TVector3 Orthogonal() const;
   // Vector orthogonal to this (Geant4).

   inline Double_t Dot(const TVector3 &) const;
   // Scalar product.

   inline TVector3 Cross(const TVector3 &) const;
   // Cross product.

   Double_t Angle(const TVector3 &) const;
   // The angle w.r.t. another 3-vector.

   Double_t PseudoRapidity() const;
   // Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))

   inline Double_t Eta() const;

   void RotateX(Double_t);
   // Rotates the Hep3Vector around the x-axis.

   void RotateY(Double_t);
   // Rotates the Hep3Vector around the y-axis.

   void RotateZ(Double_t);
   // Rotates the Hep3Vector around the z-axis.

   void RotateUz(const TVector3&);
   // Rotates reference frame from Uz to newUz (unit vector) (Geant4).

   void Rotate(Double_t, const TVector3 &);
   // Rotates around the axis specified by another Hep3Vector.

   TVector3 & operator *= (const TRotation &);
   TVector3 & Transform(const TRotation &);
   // Transformation with a Rotation matrix.

   inline TVector2 XYvector() const;

   void Print(Option_t* option="") const;//print vector parameters

```

## code

```cpp
// TVector3 has been implemented as a vector of three Double_t
// variables, representing the cartesian coordinates. By default all components
// are initialized to zero:

TVector3 v1;
v1 = (0,0,0)
TVector3 v3(1,2,3); // v3 = (1,2,3)
TVector3 v4(v2);// v4 = v2

// It is also possible (but not recommended) to initialize a TVector3
// with a Double_t or Float_t C array.

// You can get the basic components either by name or by index using operator():

xx = v1.X(); xx =v1(0);
yy = v1.Y();
yy = v1(1);
zz = v1.Z();
zz = v1(2);

// The memberfunctions SetX(), SetY(), SetZ()
// and SetXYZ() allow to set the components:

 v1.SetX(1.); v1.SetY(2.); v1.SetZ(3.);
 v1.SetXYZ(1.,2.,3.);


// Noncartesian coordinates
// To get information on the TVector3 in spherical (rho,phi,theta)
// or cylindrical (z,r,theta) coordinates, the
// the member functions Mag() (=magnitude=rho in spherical coordinates),
// Mag2(), Theta(), CosTheta(), Phi(),
// Perp() (the transverse component=r in cylindrical coordinates),Perp2() can be used:

 Double_t m = v.Mag(); // get magnitudeb (=rho=Sqrt(x*x+y*y+z*z)))
 Double_t m2 = v.Mag2(); // get magnitude squared
 Double_t t = v.Theta(); // get polar angle
 Double_t ct = v.CosTheta();// get cos of theta
 Double_t p = v.Phi(); // get azimuth angle
 Double_t pp = v.Perp(); // get transverse component
 Double_t pp2= v.Perp2(); // get transvers component squared

// It is also possible to get the transverse component with respect to another vector:

 Double_t ppv1 = v.Perp(v1);
 Double_t pp2v1 = v.Perp2(v1);

// The pseudo-rapidity ( eta=-ln (tan (theta/2)) ) can be obtained by Eta() or PseudoRapidity():

 Double_t eta = v.PseudoRapidity();

// There are set functions to change one of the noncartesian coordinates:

 v.SetTheta(.5); // keeping rho and phi
 v.SetPhi(.8); // keeping rho and theta
 v.SetMag(10.); // keeping theta and phi
 v.SetPerp(3.); // keeping z and phi


// Arithmetic / Comparison
// The TVector3 class provides the operators to add, subtract, scale and compare vectors:

 v3 = -v1;
 v1 = v2+v3;
 v1 += v3;
 v1 = v1 - v3
 v1 -= v3;
 v1 *= 10;
 v1 = 5*v2;

 if(v1==v2) {...}
 if(v1!=v2) {...}


// Related Vectors
 v2 = v1.Unit(); // get unit
// vector parallel to v1
 v2 = v1.Orthogonal(); // get vector orthogonal to v1

// Scalar and vector products
 s = v1.Dot(v2); // scalar product
 s = v1 * v2; // scalar product
 v = v1.Cross(v2); // vector product

// Angle between two vectors
 Double_t a = v1.Angle(v2);

// Rotations


// Rotation around axes
 v.RotateX(.5);
 v.RotateY(TMath::Pi());
 v.RotateZ(angle);

// Rotation around a vector
 v1.Rotate(TMath::Pi()/4, v2); // rotation around v2

// Rotation by TRotation
// TVector3 objects can be rotated by objects of the TRotation
// class using the Transform() member functions,
// the operator *= or the operator * of the TRotation class:

 TRotation m;
 // ...
 v1.transform(m);
 v1 = m*v1;
 v1 *= m; // Attention v1 = m*v1

// Transformation from rotated frame
 TVector3 direction = v.Unit();
 v1.RotateUz(direction); // direction must be TVector3 of unit length

// transforms v1 from the rotated frame (z' parallel to direction, x' in
// the theta plane and y' in the xy plane as well as perpendicular to the
// theta plane) to the (x,y,z) frame.
```



## example






<!-- TVector3.md ends here -->
