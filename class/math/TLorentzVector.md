<!-- TLorentzVector.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 10月 11 08:43:08 2018 (+0800)
;; Last-Updated: 四 10月 11 08:44:48 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TLorentzVector

**public TObject**

Place holder for real lorentz vector class.

## class

```cpp
private:

   TVector3 fP;  // 3 vector component
   Double_t fE;  // time or energy of (x,y,z,t) or (px,py,pz,e)

public:

   typedef Double_t Scalar;   // to be able to use it with the ROOT::Math::VectorUtil functions

   enum { kX=0, kY=1, kZ=2, kT=3, kNUM_COORDINATES=4, kSIZE=kNUM_COORDINATES };
   // Safe indexing of the coordinates when using with matrices, arrays, etc.

   TLorentzVector();

   TLorentzVector(Double_t x, Double_t y, Double_t z, Double_t t);
   // Constructor giving the components x, y, z, t.

   TLorentzVector(const Double_t * carray);
   TLorentzVector(const Float_t * carray);
   // Constructor from an array, not checked!

   TLorentzVector(const TVector3 & vector3, Double_t t);
   // Constructor giving a 3-Vector and a time component.

   TLorentzVector(const TLorentzVector & lorentzvector);
   // Copy constructor.

   virtual ~TLorentzVector(){};
   // Destructor

   // inline operator TVector3 () const;
   // inline operator TVector3 & ();
   // Conversion (cast) to TVector3.

   inline Double_t X() const;
   inline Double_t Y() const;
   inline Double_t Z() const;
   inline Double_t T() const;
   // Get position and time.

   inline void SetX(Double_t a);
   inline void SetY(Double_t a);
   inline void SetZ(Double_t a);
   inline void SetT(Double_t a);
   // Set position and time.

   inline Double_t Px() const;
   inline Double_t Py() const;
   inline Double_t Pz() const;
   inline Double_t P()  const;
   inline Double_t E()  const;
   inline Double_t Energy() const;
   // Get momentum and energy.

   inline void SetPx(Double_t a);
   inline void SetPy(Double_t a);
   inline void SetPz(Double_t a);
   inline void SetE(Double_t a);
   // Set momentum and energy.

   inline TVector3 Vect() const ;
   // Get spatial component.

   inline void SetVect(const TVector3 & vect3);
   // Set spatial component.

   inline Double_t Theta() const;
   inline Double_t CosTheta() const;
   inline Double_t Phi() const; //returns phi from -pi to pi
   inline Double_t Rho() const;
   // Get spatial vector components in spherical coordinate system.

   inline void SetTheta(Double_t theta);
   inline void SetPhi(Double_t phi);
   inline void SetRho(Double_t rho);
   // Set spatial vector components in spherical coordinate system.

   inline void SetPxPyPzE(Double_t px, Double_t py, Double_t pz, Double_t e);
   inline void SetXYZT(Double_t  x, Double_t  y, Double_t  z, Double_t t);
   inline void SetXYZM(Double_t  x, Double_t  y, Double_t  z, Double_t m);
   inline void SetPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m);
   inline void SetPtEtaPhiE(Double_t pt, Double_t eta, Double_t phi, Double_t e);
   // Setters to provide the functionality (but a more meanigful name) of
   // the previous version eg SetV4... PsetV4...

   inline void GetXYZT(Double_t *carray) const;
   inline void GetXYZT(Float_t *carray) const;
   // Getters into an arry
   // no checking!

   Double_t operator () (int i) const;
   inline Double_t operator [] (int i) const;
   // Get components by index.

   Double_t & operator () (int i);
   inline Double_t & operator [] (int i);
   // Set components by index.

   inline TLorentzVector & operator = (const TLorentzVector &);
   // Assignment.

   inline TLorentzVector   operator +  (const TLorentzVector &) const;
   inline TLorentzVector & operator += (const TLorentzVector &);
   // Additions.

   inline TLorentzVector   operator -  (const TLorentzVector &) const;
   inline TLorentzVector & operator -= (const TLorentzVector &);
   // Subtractions.

   inline TLorentzVector operator - () const;
   // Unary minus.

   inline TLorentzVector operator * (Double_t a) const;
   inline TLorentzVector & operator *= (Double_t a);
   // Scaling with real numbers.

   inline Bool_t operator == (const TLorentzVector &) const;
   inline Bool_t operator != (const TLorentzVector &) const;
   // Comparisons.

   inline Double_t Perp2() const;
   // Transverse component of the spatial vector squared.

   inline Double_t Pt() const;
   inline Double_t Perp() const;
   // Transverse component of the spatial vector (R in cylindrical system).

   inline void SetPerp(Double_t);
   // Set the transverse component of the spatial vector.

   inline Double_t Perp2(const TVector3 & v) const;
   // Transverse component of the spatial vector w.r.t. given axis squared.

   inline Double_t Pt(const TVector3 & v) const;
   inline Double_t Perp(const TVector3 & v) const;
   // Transverse component of the spatial vector w.r.t. given axis.

   inline Double_t Et2() const;
   // Transverse energy squared.

   inline Double_t Et() const;
   // Transverse energy.

   inline Double_t Et2(const TVector3 &) const;
   // Transverse energy w.r.t. given axis squared.

   inline Double_t Et(const TVector3 &) const;
   // Transverse energy w.r.t. given axis.

   inline Double_t DeltaPhi(const TLorentzVector &) const;
   inline Double_t DeltaR(const TLorentzVector &) const;
   inline Double_t DrEtaPhi(const TLorentzVector &) const;
   inline TVector2 EtaPhiVector();

   inline Double_t Angle(const TVector3 & v) const;
   // Angle wrt. another vector.

   inline Double_t Mag2() const;
   inline Double_t M2() const;
   // Invariant mass squared.

   inline Double_t Mag() const;
   inline Double_t M() const;
   // Invariant mass. If mag2() is negative then -sqrt(-mag2()) is returned.

   inline Double_t Mt2() const;
   // Transverse mass squared.

   inline Double_t Mt() const;
   // Transverse mass.

   inline Double_t Beta() const;
   inline Double_t Gamma() const;

   inline Double_t Dot(const TLorentzVector &) const;
   inline Double_t operator * (const TLorentzVector &) const;
   // Scalar product.

   inline void SetVectMag(const TVector3 & spatial, Double_t magnitude);
   inline void SetVectM(const TVector3 & spatial, Double_t mass);
   // Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)

   inline Double_t Plus() const;
   inline Double_t Minus() const;
   // Returns t +/- z.
   // Related to the positive/negative light-cone component,
   // which some define this way and others define as (t +/- z)/sqrt(2)

   inline TVector3 BoostVector() const ;
   // Returns the spatial components divided by the time component.

   void Boost(Double_t, Double_t, Double_t);
   inline void Boost(const TVector3 &);
   // Lorentz boost.

   Double_t Rapidity() const;
   // Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))

   inline Double_t Eta() const;
   inline Double_t PseudoRapidity() const;
   // Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))

   inline void RotateX(Double_t angle);
   // Rotate the spatial component around the x-axis.

   inline void RotateY(Double_t angle);
   // Rotate the spatial component around the y-axis.

   inline void RotateZ(Double_t angle);
   // Rotate the spatial component around the z-axis.

   inline void RotateUz(TVector3 & newUzVector);
   // Rotates the reference frame from Uz to newUz (unit vector).

   inline void Rotate(Double_t, const TVector3 &);
   // Rotate the spatial component around specified axis.

   inline TLorentzVector & operator *= (const TRotation &);
   inline TLorentzVector & Transform(const TRotation &);
   // Transformation with HepRotation.

   TLorentzVector & operator *= (const TLorentzRotation &);
   TLorentzVector & Transform(const TLorentzRotation &);
   // Transformation with HepLorenzRotation.

   virtual void        Print(Option_t *option="") const;
```



<!-- TLorentzVector.md ends here -->
