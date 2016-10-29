<!-- TCut.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 10月 29 20:56:42 2016 (+0800)
;; Last-Updated: 六 10月 29 21:00:25 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TCut

继承 TNamed

A specialized string object used in TTree selections.


## class

```cpp
   TCut();
   TCut(const char *title);
   TCut(const char *name, const char *title);
   TCut(const TCut &cut);
   virtual ~TCut();

   // Assignment
   TCut&    operator=(const char *rhs);
   TCut&    operator=(const TCut &rhs);
   TCut&    operator+=(const char *rhs);
   TCut&    operator+=(const TCut &rhs);
   TCut&    operator*=(const char *rhs);
   TCut&    operator*=(const TCut &rhs);

   // Comparison
   Bool_t   operator==(const char *rhs) const;
   Bool_t   operator==(const TCut &rhs) const;
   Bool_t   operator!=(const char *rhs) const;
   Bool_t   operator!=(const TCut &rhs) const;

   friend TCut operator+(const TCut &lhs, const char *rhs);
   friend TCut operator+(const char *lhs, const TCut &rhs);
   friend TCut operator+(const TCut &lhs, const TCut &rhs);
   friend TCut operator*(const TCut &lhs, const char *rhs);
   friend TCut operator*(const char *lhs, const TCut &rhs);
   friend TCut operator*(const TCut &lhs, const TCut &rhs);
// Preventing warnings with -Weffc++ in GCC since the overloading of the && and || operators was a design choice.
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40600
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif
   friend TCut operator&&(const TCut &lhs, const char *rhs);
   friend TCut operator&&(const char *lhs, const TCut &rhs);
   friend TCut operator&&(const TCut &lhs, const TCut &rhs);
   friend TCut operator||(const TCut &lhs, const char *rhs);
   friend TCut operator||(const char *lhs, const TCut &rhs);
   friend TCut operator||(const TCut &lhs, const TCut &rhs);
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40600
#pragma GCC diagnostic pop
#endif
   friend TCut operator!(const TCut &rhs);

   // Type conversion
   operator const char*() const { return GetTitle(); }
```

## code

```cpp
// A specialized string object used for TTree selections.
// A TCut object has a name and a title. It does not add any data
// members compared to a TNamed. It only add a set of operators to
// facilitate logical string concatenation. 
// Operators =, +=, +, *, !, &&, || overloaded.

    Root > TCut c1 = "x<1"
    Root > TCut c2 = "y<0"
    Root > TCut c3 = c1&&c2
    Root > ntuple.Draw("x", c1)
    Root > ntuple.Draw("x", c1||"x>0")
    Root > ntuple.Draw("x", c1&&c2)
    Root > ntuple.Draw("x", "(x+y)"*(c1&&c2))
```

## example



<!-- TCut.md ends here -->
