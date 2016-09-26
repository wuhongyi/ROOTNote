<!-- TTime.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 18:18:45 2016 (+0800)
;; Last-Updated: 二 9月 13 18:20:22 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.github.io -->

# TTime

Basic time type with millisecond precision.

## class

```cpp
   TTime(): fMilliSec(0) { }
   TTime(Long64_t msec): fMilliSec(msec) { }
   TTime(const TTime &t): fMilliSec(t.fMilliSec) { }
   virtual ~TTime() { }

   TTime& operator=(const TTime &t);

   TTime operator+=(const TTime &t);
   TTime operator-=(const TTime &t);
   TTime operator*=(const TTime &t);
   TTime operator/=(const TTime &t);

   friend TTime operator+(const TTime &t1, const TTime &t2);
   friend TTime operator-(const TTime &t1, const TTime &t2);
   friend TTime operator*(const TTime &t1, const TTime &t2);
   friend TTime operator/(const TTime &t1, const TTime &t2);

   friend Bool_t operator== (const TTime &t1, const TTime &t2);
   friend Bool_t operator!= (const TTime &t1, const TTime &t2);
   friend Bool_t operator<  (const TTime &t1, const TTime &t2);
   friend Bool_t operator<= (const TTime &t1, const TTime &t2);
   friend Bool_t operator>  (const TTime &t1, const TTime &t2);
   friend Bool_t operator>= (const TTime &t1, const TTime &t2);

   operator long() const;
   operator unsigned long() const;
   operator long long() const;
   operator unsigned long long() const;
   const char *AsString() const;
```


## code




## example




<!-- TTime.md ends here -->
