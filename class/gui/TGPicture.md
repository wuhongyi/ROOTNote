<!-- TGPicture.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:03:34 2016 (+0800)
;; Last-Updated: 二 11月  8 20:57:52 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGPicture

TGPicture 继承 TObject, TRefCnt , friend TGPicturePool

TGSelectedPicture 继承 TGPicture

TGPicturePool 继承 TObject


## class

**TGPicture**

```cpp
   virtual ~TGPicture();

   const char *GetName() const { return fName; }
   UInt_t      GetWidth() const { return fAttributes.fWidth; }
   UInt_t      GetHeight() const { return fAttributes.fHeight; }
   Pixmap_t    GetPicture() const { return fPic; }
   Pixmap_t    GetMask() const { return fMask; }
   Bool_t      IsScaled() const { return fScaled; }
   ULong_t     Hash() const { return fName.Hash(); }
   static const char *HashName(const char *name, Int_t width, Int_t height);

   virtual void Draw(Handle_t id, GContext_t gc, Int_t x, Int_t y) const;
   void         Print(Option_t *option="") const;
```


**TGSelectedPicture**

```cpp
   TGSelectedPicture(const TGClient *client, const TGPicture *p);
   virtual ~TGSelectedPicture();
```


**TGPicturePool**

```cpp
   TGPicturePool(const TGClient *client, const char *path):
      fClient(client), fPath(path), fPicList(0) { }
   virtual ~TGPicturePool();

   const char      *GetPath() const { return fPath; }
   const TGPicture *GetPicture(const char *name);
   const TGPicture *GetPicture(const char *name, char **xpm);
   const TGPicture *GetPicture(const char *name, UInt_t new_width, UInt_t new_height);
   const TGPicture *GetPicture(const char *name, Pixmap_t pxmap, Pixmap_t mask =  0);
   void             FreePicture(const TGPicture *pic);

   void             Print(Option_t *option="") const;
```

## code

```cpp
#include "TGIcon.h"
#include "TGResourcePool.h"
#include "TGPicture.h"

// TGPicture TGPicturePool TGIcon
// 插入系统自带的小图片
const char * const icon1[] =
{
"16 16 8 1",
"    c None s None",
".   c #808080",
"X   c #FFFF00",
"o   c #c0c0c0",
"O   c black",
"+   c #00FFFF",
"@   c #00FF00",
"#   c white",
"     .....      ",
"   ..XXoooOO    ",
"  .+XXXoooooO   ",
" .@++XXoooo#oO  ",
" .@@+XXooo#ooO  ",
".oo@@+Xoo#ooooO ",
".ooo@+.O.oooooO ",
".oooo@O#OoooooO ",
".oooo#.O.+ooooO ",
".ooo#oo#@X+oooO ",
" .o#oooo@X++oO  ",
" .#ooooo@XX++O  ",
"  .ooooo@@XXO   ",
"   ..ooo@@OO    ",
"     ..OOO      ",
"                "
};
TString name = "myicon";
ULong_t yellow;
gClient->GetColorByName("yellow", yellow);
TGPicturePool *picpool = gClient->GetResourcePool()->GetPicturePool();
const TGPicture *iconpic = picpool->GetPicture(name.Data(),(char **)icon1);
TGIcon *icon = new TGIcon(frame, iconpic, 40, 40, kChildFrame, yellow);
frame->AddFrame(icon, new TGLayoutHints(kLHintsLeft, 1,15,1,1));
```

## example




<!-- TGPicture.md ends here -->
