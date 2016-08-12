# 类的使用

<!-- A B C D E F G H I J K L M N O P Q R S T U V W X Y Z -->

本章主要介绍常用类中的函数

包括：函数的使用、函数的参数设置、示例代码等


## 未分类

```cpp
//支持中文显示
"\\hbox{RHIC スピン物理 Нью-Йорк}"
```

```cpp
//直方图上不要TPave
gStyle->SetOptStat(0);
```

```cpp
char name[10], title[20];
TObjArray Hlist(0);
TH1F* h;
for (Int_t i = 0; i < 15; i++) {
sprintf(name,"h%d",i);   //把格式化的数据写入字符串中
sprintf(title,"histo nr:%d",i);
h = new TH1F(name,title,100,-4,4);
Hlist.Add(h);
h->FillRandom("gaus",1000);}
TFile f("demo.root","recreate");
Hlist->Write();
f.Close();
```
