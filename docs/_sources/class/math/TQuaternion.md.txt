<!-- TQuaternion.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 10月 11 08:45:21 2018 (+0800)
;; Last-Updated: 三 9月 16 10:42:51 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TQuaternion*

**public TObject**


## class

```cpp
public:

   TQuaternion(Double_t real = 0, Double_t X = 0, Double_t Y = 0, Double_t Z = 0);
   TQuaternion(const TVector3 & vector, Double_t real = 0);
   TQuaternion(const Double_t *);
   TQuaternion(const Float_t *);
   // Constructors from an array : 0 to 2 = vector part, 3 = real part

   TQuaternion(const TQuaternion &);
   // The copy constructor.

   virtual ~TQuaternion();
   // Destructor

   Double_t operator () (int) const;
   inline Double_t operator [] (int) const;
   // Get components by index. 0 to 2 = vector part, 3 = real part

   Double_t & operator () (int);
   inline Double_t & operator [] (int);
   // Set components by index. 0 to 2 = vector part, 3 = real part

   inline TQuaternion& SetRXYZ(Double_t r,Double_t x,Double_t y,Double_t z);
   inline TQuaternion& SetRV(Double_t r, TVector3& vect);
   // Sets components
   TQuaternion& SetAxisQAngle(TVector3& v,Double_t QAngle);
   // Set from vector direction and quaternion angle
   Double_t GetQAngle() const;
   TQuaternion& SetQAngle(Double_t angle);
   // set and get quaternion angle

   inline void GetRXYZ(Double_t *carray) const;
   inline void GetRXYZ(Float_t *carray) const;
   // Get the components into an array : 0 to 2 vector part, 3 real part
   // not checked!

   // ---------------  real to quaternion algebra
   inline TQuaternion& operator=(Double_t r);
   inline Bool_t operator == (Double_t r) const;
   inline Bool_t operator != (Double_t r) const;
   inline TQuaternion& operator+=(Double_t real);
   inline TQuaternion& operator-=(Double_t real);
   inline TQuaternion& operator*=(Double_t real);
   inline TQuaternion& operator/=(Double_t real);
   TQuaternion operator*(Double_t real) const;
   TQuaternion operator+(Double_t real) const;
   TQuaternion operator-(Double_t real) const;
   TQuaternion operator/(Double_t real) const;

   // ---------------- vector to quaternion algebra
   inline TQuaternion& operator=(const TVector3& );
   inline Bool_t operator == (const TVector3&) const;
   inline Bool_t operator != (const TVector3&) const;
   inline TQuaternion& operator+=(const TVector3 &vector);
   inline TQuaternion& operator-=(const TVector3 &vector);
   TQuaternion& MultiplyLeft(const TVector3 &vector);
   TQuaternion& operator*=(const TVector3 &vector);
   TQuaternion& DivideLeft(const TVector3 &vector);
   TQuaternion& operator/=(const TVector3 &vector);
   TQuaternion operator+(const TVector3 &vector) const;
   TQuaternion operator-(const TVector3 &vector) const;
   TQuaternion LeftProduct(const TVector3 &vector) const;
   TQuaternion operator*(const TVector3 &vector) const;
   TQuaternion LeftQuotient(const TVector3 &vector) const;
   TQuaternion operator/(const TVector3 &vector) const;

   // ----------------- quaternion algebra
   inline TQuaternion& operator=(const TQuaternion& );
   inline Bool_t operator == (const TQuaternion&) const;
   inline Bool_t operator != (const TQuaternion&) const;
   inline TQuaternion& operator+=(const TQuaternion &quaternion);
   inline TQuaternion& operator-=(const TQuaternion &quaternion);
   TQuaternion& MultiplyLeft(const TQuaternion &quaternion);
   TQuaternion& operator*=(const TQuaternion &quaternion);
   TQuaternion& DivideLeft(const TQuaternion &quaternion);
   TQuaternion& operator/=(const TQuaternion &quaternion);
   TQuaternion operator+(const TQuaternion &quaternion) const;
   TQuaternion operator-(const TQuaternion &quaternion) const;
   TQuaternion LeftProduct(const TQuaternion &quaternion) const;
   TQuaternion operator*(const TQuaternion &quaternion) const;
   TQuaternion LeftQuotient(const TQuaternion &quaternion) const;
   TQuaternion operator/(const TQuaternion &quaternion) const;

   // ------------------ general algebra
   inline Double_t Norm() const; // quaternion magnitude
   inline Double_t Norm2() const; // quaternion squared magnitude
   Double_t QMag() const { return Norm(); } // quaternion magnitude
   Double_t QMag2() const { return Norm2(); } // quaternion squared magnitude
   inline TQuaternion& Normalize();  // normalize quaternion
   inline TQuaternion operator - () const; // Unary minus.
   inline TQuaternion Conjugate() const;
   TQuaternion Invert() const;
   void Rotate(TVector3& vect) const;
   TVector3 Rotation(const TVector3& vect) const;

   void Print(Option_t* option="") const;

   Double_t fRealPart;          // Real part
   TVector3 fVectorPart; // vector part
```








<!-- TQuaternion.md ends here -->
