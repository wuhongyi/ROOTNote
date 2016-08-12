<!-- TCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 五 8月 12 21:55:38 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 11
;; URL: http://wuhongyi.github.io -->

# TCanvas

## class

```cpp
virtual void      Update();//刷新画板

void              Clear(Option_t *option="");
// Remove all primitives from the canvas.
// If option "D" is specified, direct subpads are cleared but not deleted.
// This option is not recursive, i.e. pads in direct subpads are deleted.


TCanvas(const char *name, const char *title="", Int_t form=1);
TCanvas(const char *name, const char *title, Int_t ww, Int_t wh);
TCanvas(const char *name, const char *title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh);
TCanvas(const char *name, Int_t ww, Int_t wh, Int_t winid);


void SaveSource(const char *filename, Option_t *option)
// Save primitives in this canvas as a C++ macro file.
// This function loops on all the canvas primitives and for each primitive
// calls the object SavePrimitive function.
// When outputing floating point numbers, the default precision is 7 digits.
// The precision can be changed (via system.rootrc) by changing the value
// of the environment variable "Canvas.SavePrecision"

  void SavePrimitive(std::ostream &out, Option_t *option /*= ""*/)
// Save primitives in this canvas in C++ macro file with GUI.

```

## code

```cpp
TCanvas *MyC = new TCanvas("MyC","Test canvas",1)     //新建画板
MyC->SetFillColor(42);                                //设置画板背景颜色
MyC->Divide(2,2);                                     //将画板分成2*2四个区域
MyC->cd(1);                                           //指向第一个区域
f1->Draw();                                           //在第一个区域画图f1

MyC->SaveAs("");

TH1* hc = (TH1*)f1->Clone();                          //克隆直方图

//设置画板
TCanvas *c1 = new TCanvas("c1","画板标题在这",200,10,700,700);	
TCanvas *c1 = new TCanvas("c1","画板标题在这",900,700);

c1->Divide(2,2);//将画板分成四份，2*2	
c1->SetFillColor(40);//设置画板背景颜色


TCanvas *canv = new TCanvas("image", "ccc");
canv->ToggleEventStatus();
canv->SetRightMargin(0.2);
canv->SetLeftMargin(0.01);
canv->SetTopMargin(0.01);
canv->SetBottomMargin(0.01);
```

## example

```cpp
Canvas *statsEditing() {
//    - how to remove a stat element from the stat box 
//    - how to add a new one
//如何除去图上右上角box中的信息已经添加信息

   // Create and plot a test histogram with stats
   TCanvas *se = new TCanvas;
   TH1F *h = new TH1F("h","test",100,-3,3);
   h->FillRandom("gaus",3000);
   gStyle->SetOptStat();
   h->Draw();
   se->Update();

   // Retrieve the stat box
   TPaveStats *ps = (TPaveStats*)se->GetPrimitive("stats");
   ps->SetName("mystats");
   TList *list = ps->GetListOfLines();

   // Remove the RMS line
   TText *tconst = ps->GetLineWith("RMS");
   list->Remove(tconst);

   // Add a new line in the stat box.
   // Note that "=" is a control character
   TLatex *myt = new TLatex(0,0,"Test = 10");
   myt ->SetTextFont(42);
   myt ->SetTextSize(0.04);
   myt ->SetTextColor(kRed);
   list->Add(myt);

   // the following line is needed to avoid that the automatic redrawing of stats
   h->SetStats(0);

   se->Modified();
   return se;
}

```


<!-- TCanvas.md ends here -->
