<!-- TRotation.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 10月 11 08:49:38 2018 (+0800)
;; Last-Updated: 四 10月 11 08:50:34 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TRotation

**public TObject**


## class

```cpp
public:

class TRotationRow {
public:
   inline TRotationRow(const TRotation &, int);
   inline TRotationRow(const TRotationRow &);
   inline TRotationRow & operator=(const TRotationRow &);
   inline Double_t operator [] (int) const;
private:
   const TRotation * fRR;
   //    const TRotation & fRR;
   int fII;
};
   // Helper class for implemention of C-style subscripting r[i][j]

   TRotation();
   // Default constructor. Gives a unit matrix.

   TRotation(const TRotation &);
   TRotation(const TQuaternion &);
   // Copy constructor.

   virtual ~TRotation() {;};

   inline Double_t XX() const;
   inline Double_t XY() const;
   inline Double_t XZ() const;
   inline Double_t YX() const;
   inline Double_t YY() const;
   inline Double_t YZ() const;
   inline Double_t ZX() const;
   inline Double_t ZY() const;
   inline Double_t ZZ() const;
   // Elements of the rotation matrix (Geant4).

   inline TRotationRow operator [] (int) const;
   // Returns object of the helper class for C-style subscripting r[i][j]

   Double_t operator () (int, int) const;
   // Fortran-style subscripting: returns (i,j) element of the rotation matrix.

   inline TRotation & operator = (const TRotation &);
   // Assignment.

   inline Bool_t operator == (const TRotation &) const;
   inline Bool_t operator != (const TRotation &) const;
   // Comparisons (Geant4).

   inline Bool_t IsIdentity() const;
   // Returns true if the identity matrix (Geant4).

   inline TVector3 operator * (const TVector3 &) const;
   // Multiplication with a TVector3.

   TRotation operator * (const TRotation &) const;
   inline TRotation & operator *= (const TRotation &);
   inline TRotation & Transform(const TRotation &);
   // Matrix multiplication.
   // Note a *= b; <=> a = a * b; while a.transform(b); <=> a = b * a;

   inline TRotation Inverse() const;
   // Returns the inverse.

   inline TRotation & Invert();
   // Inverts the Rotation matrix.

   TRotation & RotateX(Double_t);
   // Rotation around the x-axis.

   TRotation & RotateY(Double_t);
   // Rotation around the y-axis.

   TRotation & RotateZ(Double_t);
   // Rotation around the z-axis.

   TRotation & Rotate(Double_t, const TVector3 &);
   inline TRotation & Rotate(Double_t, const TVector3 *);
   // Rotation around a specified vector.

   TRotation & RotateAxes(const TVector3 & newX,
                          const TVector3 & newY,
                          const TVector3 & newZ);
   // Rotation of local axes (Geant4).

   Double_t PhiX() const;
   Double_t PhiY() const;
   Double_t PhiZ() const;
   Double_t ThetaX() const;
   Double_t ThetaY() const;
   Double_t ThetaZ() const;
   // Return angles (RADS) made by rotated axes against original axes (Geant4).

   void AngleAxis(Double_t &, TVector3 &) const;
   // Returns the rotation angle and rotation axis (Geant4).

   inline TRotation & SetToIdentity();
   // Set equal to the identity rotation.

   TRotation & SetXEulerAngles(Double_t phi, Double_t theta, Double_t psi);
   void SetXPhi(Double_t);
   void SetXTheta(Double_t);
   void SetXPsi(Double_t);
   // Set the euler angles of the rotation.  The angles are defined using the
   // y-convention which rotates around the Z axis, around the new X axis, and
   // then around the new Z axis.  The x-convention is used Goldstein, Landau
   // and Lifshitz, and other common physics texts.  Contrast this with
   // SetYEulerAngles.

   TRotation & RotateXEulerAngles(Double_t phi, Double_t theta, Double_t psi);
   // Adds a rotation of the local axes defined by the Euler angle to the
   // current rotation.  See SetXEulerAngles for a note about conventions.

   Double_t GetXPhi(void) const;
   Double_t GetXTheta(void) const;
   Double_t GetXPsi(void) const;
   // Return the euler angles of the rotation.  See SetYEulerAngles for a
   // note about conventions.

   TRotation & SetYEulerAngles(Double_t phi, Double_t theta, Double_t psi);
   void SetYPhi(Double_t);
   void SetYTheta(Double_t);
   void SetYPsi(Double_t);
   // Set the euler angles of the rotation.  The angles are defined using the
   // y-convention which rotates around the Z axis, around the new Y axis, and
   // then around the new Z axis.  The x-convention is used Goldstein, Landau
   // and Lifshitz, and other common physics texts and is a rotation around the
   // Z axis, around the new X axis, and then around the new Z axis.

   TRotation & RotateYEulerAngles(Double_t phi, Double_t theta, Double_t psi);
   // Adds a rotation of the local axes defined by the Euler angle to the
   // current rotation.  See SetYEulerAngles for a note about conventions.

   Double_t GetYPhi(void) const;
   Double_t GetYTheta(void) const;
   Double_t GetYPsi(void) const;
   // Return the euler angles of the rotation.  See SetYEulerAngles for a
   // note about conventions.

   TRotation & SetXAxis(const TVector3& axis);
   TRotation & SetXAxis(const TVector3& axis, const TVector3& xyPlane);
   TRotation & SetYAxis(const TVector3& axis);
   TRotation & SetYAxis(const TVector3& axis, const TVector3& yzPlane);
   TRotation & SetZAxis(const TVector3& axis);
   TRotation & SetZAxis(const TVector3& axis, const TVector3& zxPlane);
   // Create a rotation with the axis vector parallel to the rotated coordinate
   // system.  If a second vector is provided it defines a plane passing
   // through the axis.

   void MakeBasis(TVector3& xAxis, TVector3& yAxis, TVector3& zAxis) const;
   // Take two input vectors (in xAxis, and zAxis) and turn them into an
   // orthogonal basis.  This is an internal helper function used to implement
   // the Set?Axis functions, but is exposed because the functionality is
   // often useful.

protected:

   TRotation(Double_t, Double_t, Double_t, Double_t, Double_t,
             Double_t, Double_t, Double_t, Double_t);
   // Protected constructor.

   Double_t fxx, fxy, fxz, fyx, fyy, fyz, fzx, fzy, fzz;
   // The matrix elements.
```

<!-- TRotation.md ends here -->
