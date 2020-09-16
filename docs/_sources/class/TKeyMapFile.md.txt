<!-- TKeyMapFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 15:04:12 2019 (+0800)
;; Last-Updated: 三 9月 16 10:32:01 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TKeyMapFile*

```
 Utility class for browsing TMapFile objects.

 When the browser is invoked for a TMapFile, a TKeyMapFile object
 is created for each object in the mapped file.
 When a TKeyMapFile object is clicked in the browser, a new copy
 of this object is copied into the local directory and the action
 corresponding to object->Browse is executed (typically Draw).
```

```cpp
class TKeyMapFile : public TNamed
```

## class

```cpp
private:
   TKeyMapFile(const TKeyMapFile&);            // TKeyMapFile objects are not copiable.
   TKeyMapFile& operator=(const TKeyMapFile&); // TKeyMapFile objects are not copiable.

   TMapFile      *fMapFile;       ///< Pointer to map file

public:
   TKeyMapFile();
   TKeyMapFile(const char *name, const char *classname, TMapFile *mapfile);
   virtual ~TKeyMapFile() {;}
   virtual void      Browse(TBrowser *b);
```

<!-- TKeyMapFile.md ends here -->
