<!-- TGTextViewStream.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 15:24:36 2016 (+0800)
;; Last-Updated: 三 9月 16 11:16:51 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGTextViewStream*

TGTextViewStreamBuf 继承 std::streambuf

TGTextViewostream 继承 TGTextView, std::ostream

A TGTextViewStream is a text viewer widget. It is a specialization   
of TGTextView and std::ostream, and it uses a TGTextViewStreamBuf,   
who inherits from std::streambuf, allowing to stream text directly   
to the text view in a cout-like fashion

## class

**TGTextViewStreamBuf**

```cpp
   TGTextViewStreamBuf(TGTextView *textview);
   virtual ~TGTextViewStreamBuf() { }
```


**TGTextViewostream**

```cpp
   TGTextViewostream(const TGWindow* parent = 0, UInt_t w = 1, UInt_t h = 1,
                     Int_t id = -1, UInt_t sboptions = 0,
                     Pixel_t back = TGTextView::GetWhitePixel());
   TGTextViewostream(const TGWindow *parent, UInt_t w, UInt_t h,
                     TGText *text, Int_t id, UInt_t sboptions, ULong_t back);
   TGTextViewostream(const TGWindow *parent, UInt_t w, UInt_t h,
                     const char *string, Int_t id, UInt_t sboptions,
                     ULong_t back);
   virtual ~TGTextViewostream() { }
```


## code

```cpp
#include "TGTextViewStream.h"		 
		 
// TGTextViewStream
// 数据流输出框
TGTextViewostream *fTextView;
TGTextEntry       *fCommand;
fTextView = new TGTextViewostream(frame1, 500, 300);
frame1->AddFrame(fTextView, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 0));
fCommand = new TGTextEntry(frame2, (const char *)"", 20);
fCommand->Connect("ReturnPressed()", "TextViewMainFrame", this, "HandleReturn()");
frame2->AddFrame(fCommand, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
void HandleReturn()
{
   std::string line;
   std::string command = fCommand->GetText();
   *fTextView << gSystem->GetFromPipe(command.c_str()).Data() << std::endl;
   fTextView->ShowBottom();
   fCommand->Clear();
}
```

## example




<!-- TGTextViewStream.md ends here -->
