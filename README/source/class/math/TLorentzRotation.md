<!-- TLorentzRotation.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 10月 11 02:46:02 2018 (+0800)
;; Last-Updated: 三 9月 16 10:43:13 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TLorentzRotation*

**public TObject**

```
The TLorentzRotation class describes Lorentz transformations including
Lorentz boosts and rotations (see TRotation)

            | xx  xy  xz  xt |
            |                |
            | yx  yy  yz  yt |
   lambda = |                |
            | zx  zy  zz  zt |
            |                |
            | tx  ty  tz  tt |
```


## class

```cpp
public:

class TLorentzRotationRow {
public:
   inline TLorentzRotationRow(const TLorentzRotation &, int);
   inline Double_t operator [] (int) const;
private:
   const TLorentzRotation * fRR;
   int fII;
};
   // Helper class for implemention of C-style subscripting r[i][j]

   TLorentzRotation();
   // Default constructor. Gives a unit matrix.

   TLorentzRotation(const TRotation &);
   // Constructor for 3d rotations.

   TLorentzRotation(const TLorentzRotation &);
   // Copy constructor.

   TLorentzRotation(Double_t, Double_t, Double_t);
   TLorentzRotation(const TVector3 &);
   // Constructors giving a Lorenz-boost.

   inline Double_t XX() const;
   inline Double_t XY() const;
   inline Double_t XZ() const;
   inline Double_t XT() const;
   inline Double_t YX() const;
   inline Double_t YY() const;
   inline Double_t YZ() const;
   inline Double_t YT() const;
   inline Double_t ZX() const;
   inline Double_t ZY() const;
   inline Double_t ZZ() const;
   inline Double_t ZT() const;
   inline Double_t TX() const;
   inline Double_t TY() const;
   inline Double_t TZ() const;
   inline Double_t TT() const;
   // Elements of the matrix.

   inline TLorentzRotationRow operator [] (int) const;
   // Returns object of the helper class for C-style subscripting r[i][j]


   Double_t operator () (int, int) const;
   // Fortran-style subscriptimg: returns (i,j) element of the matrix.


   inline TLorentzRotation & operator = (const TLorentzRotation &);
   inline TLorentzRotation & operator = (const TRotation &);
   // Assignment.

   inline Bool_t operator == (const TLorentzRotation &) const;
   inline Bool_t operator != (const TLorentzRotation &) const;
   // Comparisons.

   inline Bool_t IsIdentity() const;
   // Returns true if the Identity matrix.

   inline TLorentzVector VectorMultiplication(const TLorentzVector&) const;
   inline TLorentzVector operator * (const TLorentzVector &) const;
   // Multiplication with a Lorentz vector.

   TLorentzRotation MatrixMultiplication(const TLorentzRotation &) const;
   inline TLorentzRotation operator * (const TLorentzRotation &) const;
   inline TLorentzRotation & operator *= (const TLorentzRotation &);
   inline TLorentzRotation & Transform(const TLorentzRotation &);
   inline TLorentzRotation & Transform(const TRotation &);
   // Matrix multiplication.
   // Note: a *= b; <=> a = a * b; while a.Transform(b); <=> a = b * a;

   inline TLorentzRotation Inverse() const;
   // Return the inverse.

   inline TLorentzRotation & Invert();
   // Inverts the LorentzRotation matrix.

   inline TLorentzRotation & Boost(Double_t, Double_t, Double_t);
   inline TLorentzRotation & Boost(const TVector3 &);
   // Lorenz boost.

   inline TLorentzRotation & RotateX(Double_t);
   // Rotation around x-axis.

   inline TLorentzRotation & RotateY(Double_t);
   // Rotation around y-axis.

   inline TLorentzRotation & RotateZ(Double_t);
   // Rotation around z-axis.

   inline TLorentzRotation & Rotate(Double_t, const TVector3 &);
   inline TLorentzRotation & Rotate(Double_t, const TVector3 *);
   // Rotation around specified vector.

protected:

   Double_t fxx, fxy, fxz, fxt,
            fyx, fyy, fyz, fyt,
            fzx, fzy, fzz, fzt,
            ftx, fty, ftz, ftt;
   // The matrix elements.

   void SetBoost(Double_t, Double_t, Double_t);
   // Set elements according to a boost vector.

   TLorentzRotation(Double_t, Double_t, Double_t, Double_t,
                    Double_t, Double_t, Double_t, Double_t,
                    Double_t, Double_t, Double_t, Double_t,
                    Double_t, Double_t, Double_t, Double_t);
   // Protected constructor.
```

## code

```cpp
// By default it is initialized to the identity matrix, but it may also be intialized by an other TLorentzRotation, by a pure TRotation or by a boost:

 TLorentzRotation l; // l is
 // initialized as identity
 TLorentzRotation m(l); // m = l
 TRotation r;
 TLorentzRotation lr(r);
 TLorentzRotation lb1(bx,by,bz);
 TVector3 b;
 TLorentzRotation lb2(b);

// The Matrix for a Lorentz boosts is:

//    | 1+gamma'*bx*bx  gamma'*bx*by   gamma'*bx*bz  gamma*bx |
//    |  gamma'*by*bx  1+gamma'*by*by  gamma'*by*bz  gamma*by |
//    |  gamma'*bz*bx   gamma'*bz*by  1+gamma'*bz*bz gamma*bz |
//    |    gamma*bx       gamma*by       gamma*bz     gamma   |

// with the boost vector b=(bx,by,bz) and gamma=1/Sqrt(1-beta*beta)
and gamma'=(gamma-1)/beta*beta.
```

```cpp
// Access to the matrix components/Comparisons
// Access to the matrix components is possible through the member functions
XX(), XY() .. TT(), through the operator (int,int):

 Double_t xx;
 TLorentzRotation l;
 xx = l.XX(); // gets the xx component
 xx = l(0,0); // gets the xx component

 if (l==m) {...} // test for equality
 if (l !=m) {...} // test for inequality
 if (l.IsIdentity()) {...} // test for identity
```


```cpp
// Compound transformations
// There are four possibilities to find the product of two TLorentzRotation
transformations:


 TLorentzRotation a,b,c;
 c = b*a;// product
 c = a.MatrixMultiplication(b); // a is unchanged
 a *= b;// Attention: a=a*b
 c = a.Transform(b)// a=b*a then c=a
```

```cpp
// Lorentz boosts

 Double_t bx, by, bz;
 TVector3 v(bx,by,bz);
 TLorentzRotation l;
 l.Boost(v);
 l.Boost(bx,by,bz);
```


```cpp
// Rotations
 TVector3 axis;
 l.RotateX(TMath::Pi()); // rotation around x-axis
 l.Rotate(.5,axis);// rotation around specified vector
```

```vpp
// Inverse transformation
// The matrix for the inverse transformation of a TLorentzRotatio
            | xx  yx  zx -tx |
            |                |
            | xy  yy  zy -ty |
            |                |
            | xz  yz  zz -tz |
            |                |
            |-xt -yt -zt  tt |
```

```cpp
// To return the inverse transformation keeping the current unchangednuse the member function Inverse().
//nInvert() inverts the current TLorentzRotation:


 l1 = l2.Inverse(); // l1 is inverse of l2, l2 unchanged
 l1 = l2.Invert(); // invert l2, then l1=l2
```cpp

// Transformation of a TLorentzVector
// To apply TLorentzRotation to TLorentzVector you can use either the VectorMultiplication() member function or the *operator. You can also use the Transform() function and the *=operator of the TLorentzVector class.:


 TLorentzVector v;
 ...
 v=l.VectorMultiplication(v);
 v = l * v;

 v.Transform(l);
 v *= l; // Attention v = l*v
```





<!-- TLorentzRotation.md ends here -->
