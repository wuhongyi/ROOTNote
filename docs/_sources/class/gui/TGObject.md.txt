<!-- TGObject.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 14:18:24 2016 (+0800)
;; Last-Updated: 三 11月  9 14:53:33 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGObject

This class is the baseclass for all ROOT GUI widgets.                
The ROOT GUI components emulate the Win95 look and feel and the code  
is based on the XClass'95 code (see Copyleft in source). 


TGObject 继承 TObject

## class

```cpp
   TGObject(): fId(0), fClient(0) { }
   TGObject(const TGObject& tgo): TObject(tgo), fId(tgo.fId), fClient(tgo.fClient) { }
   virtual ~TGObject() { }

   Handle_t  GetId() const { return fId; }
   TGClient *GetClient() const { return fClient; }
   ULong_t   Hash() const { return (ULong_t) fId >> 0; }
   Bool_t    IsEqual(const TObject *obj) const;
/// Equal comparison (TGObjects are equal if they have the same
/// window identifier). If the TGObjects have not been created by
/// the Window manager (e.g. a TGLVEntry), then fall back to the
/// default TObject equal comparison

   virtual void SaveAs(const char* filename = "", Option_t* option = "") const;
/// Write this TGObject to a file using TImage, if filename's extension signals
/// a valid TImage::EImageFileType, as defined by TImage::GetImageFileTypeFromFilename().
/// Otherwise forward to TObject::SaveAs().
```

## code



## example




<!-- TGObject.md ends here -->
