<!-- TGIcon.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:00:50 2016 (+0800)
;; Last-Updated: 二 11月  8 14:02:01 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGIcon

TGIcon 继承 TGFrame

This class handles GUI icons.

## class

```cpp
   TGIcon(const TGWindow *p, const TGPicture *pic, UInt_t w, UInt_t h,
      UInt_t options = kChildFrame, Pixel_t back = GetDefaultFrameBackground()) :
         TGFrame(p, w, h, options, back), fPic(pic), fImage(0), fPath() { SetWindowName(); }

   TGIcon(const TGWindow *p = 0, const char *image = 0);

   virtual ~TGIcon();

   virtual void Reset();         //*MENU*
   const TGPicture *GetPicture() const { return fPic; }
   TImage *GetImage() const { return fImage; }
   virtual void SetPicture(const TGPicture *pic);
   virtual void SetImage(const char *img);
   virtual void SetImage(TImage *img);
   virtual void SetImagePath(const char *path);

   virtual void Resize(UInt_t w = 0, UInt_t h = 0);
   virtual void Resize(TGDimension size) { Resize(size.fWidth, size.fHeight); }
   virtual void MoveResize(Int_t x, Int_t y, UInt_t w = 0, UInt_t h = 0);
   virtual void ChangeBackgroundColor() { }

   virtual TGDimension GetDefaultSize() const;
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```

## code


## example



<!-- TGIcon.md ends here -->
