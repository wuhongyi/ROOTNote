<!-- Buttons.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 1月  5 12:18:12 2019 (+0800)
;; Last-Updated: 六 1月  5 12:18:41 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# Buttons

```cpp
enum EEventType {
   kNoEvent       =  0,
   kButton1Down   =  1, kButton2Down   =  2, kButton3Down   =  3, kKeyDown  =  4,
   kWheelUp       =  5, kWheelDown     =  6, kButton1Shift  =  7, kButton1ShiftMotion  =  8,
   kButton1Up     = 11, kButton2Up     = 12, kButton3Up     = 13, kKeyUp    = 14,
   kButton1Motion = 21, kButton2Motion = 22, kButton3Motion = 23, kKeyPress = 24,
   kArrowKeyPress = 25, kArrowKeyRelease = 26,
   kButton1Locate = 41, kButton2Locate = 42, kButton3Locate = 43, kESC      = 27,
   kMouseMotion   = 51, kMouseEnter    = 52, kMouseLeave    = 53,
   kButton1Double = 61, kButton2Double = 62, kButton3Double = 63
};

enum EEditMode {
   kPolyLine  = 1,  kSPolyLine = 2,  kPolyGone  = 3,
   kSPolyGone = 4,  kBox       = 5,  kDelete    = 6,
   kPad       = 7,  kText      = 8,  kEditor    = 9,
   kExit      = 10, kPave      = 11, kPaveLabel = 12,
   kPaveText  = 13, kPavesText = 14, kEllipse   = 15,
   kArc       = 16, kLine      = 17, kArrow     = 18,
   kGraph     = 19, kMarker    = 20, kPolyMarker= 21,
   kPolyLine3D= 22, kWbox      = 23, kGaxis     = 24,
   kF1        = 25, kF2        = 26, kF3        = 27,
   kDiamond   = 28, kPolyMarker3D = 29, kButton = 101,
   kCutG      =100, kCurlyLine =200, kCurlyArc  = 201
};
```

<!-- Buttons.md ends here -->
