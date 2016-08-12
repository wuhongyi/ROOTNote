<!-- TFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:38:01 2014 (+0800)
;; Last-Updated: 五 8月 12 22:31:34 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 8
;; URL: http://wuhongyi.github.io -->

# TFile

## class

<!-- ```cpp -->
<!-- // -->
<!-- ``` -->

## code

```cpp
//打开文件
TFile f("demo.root");
if (f.IsZombie()) {
cout << "Error opening file" << endl;
exit(-1);} 
else {
 .....
 }
 ```


```cpp
//多个cycle时候读取某一部分数据
TTree *tt;
gFile->GetObject("NameOfTree;1",tt)

```

```cpp
//Saving/Reading Histograms to/from a File
//The following statements create a ROOT file and store a histogram on the file. Because TH1 derives from TNamed , the key identifier on the file is the histogram name:
TFile f("histos.root","new");
TH1F h1("hgaus","histo from a gaussian",100,-3,3);
h1.FillRandom("gaus",10000);
h1->Write();
//To read this histogram in another ROOT session, do:
TFile f("histos.root");
TH1F *h = (TH1F*)f.Get("hgaus");
One can save all histograms in memory to the file by:
file->Write();
For a more detailed explanation, see “Input/Output”.


TTree *fChain = (TTree*)gFile->Get("t");
Long64_t nentries = fChain->GetEntriesFast(); 
```



## example

```cpp
//文本读取数据存ROOT文件：
#include "Riostream.h"
void basic() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   std::cout<<dir<<std::endl;
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");std::cout<<dir<<std::endl;//当前目录路径

   ifstream in;
   in.open(Form("%sbasic.dat",dir.Data()));

   Float_t x,y,z;
   Int_t nlines = 0;
   TFile *f = new TFile("basic.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");

   while (1) {
      in >> x >> y >> z;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
      h1->Fill(x);
      ntuple->Fill(x,y,z);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

void basic2() {
//   example of macro to create can ntuple reading data from an ascii file.
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic2.C","");
   dir.ReplaceAll("/./","/");
   
   TFile *f = new TFile("basic2.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TTree *T = new TTree("ntuple","data from ascii file");
   Long64_t nlines = T->ReadFile(Form("%sbasic.dat",dir.Data()),"x:y:z");
   printf(" found %lld points\n",nlines);
   T->Draw("x","z>2");
   T->Write();
}
```

<!-- TFile.md ends here -->
