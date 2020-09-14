<!-- TGIcon.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:00:50 2016 (+0800)
;; Last-Updated: 四 11月 10 21:04:38 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGIcon

TGIcon 继承 TGFrame

This class handles GUI icons.

## class

```cpp
   TGIcon(const TGWindow *p, const TGPicture *pic, UInt_t w, UInt_t h,
      UInt_t options = kChildFrame, Pixel_t back = GetDefaultFrameBackground()) :
         TGFrame(p, w, h, options, back), fPic(pic), fImage(0), fPath() { SetWindowName(); }

   TGIcon(const TGWindow *p = 0, const char *image = 0);/// Create icon.

   virtual ~TGIcon();/// Delete icon and free picture.

   virtual void Reset();         //*MENU*
/// Reset icon to original image. It can be used only via context menu.

   const TGPicture *GetPicture() const { return fPic; }
   TImage *GetImage() const { return fImage; }
   virtual void SetPicture(const TGPicture *pic);/// Set icon picture.
   virtual void SetImage(const char *img);/// Set icon image.
   virtual void SetImage(TImage *img);/// Change icon image.
   virtual void SetImagePath(const char *path);
/// Set directory where image is located

   virtual void Resize(UInt_t w = 0, UInt_t h = 0);/// Resize.
   virtual void Resize(TGDimension size) { Resize(size.fWidth, size.fHeight); }
   virtual void MoveResize(Int_t x, Int_t y, UInt_t w = 0, UInt_t h = 0);
/// Move icon to (x,y) and resize it to (w,h).

   virtual void ChangeBackgroundColor() { }

   virtual TGDimension GetDefaultSize() const;/// Return size of icon.
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save an icon widget as a C++ statement(s) on output stream out.   
```

## code


## example



<!-- TGIcon.md ends here -->
