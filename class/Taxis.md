<!-- Taxis.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 五 8月 12 21:55:37 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 9
;; URL: http://wuhongyi.github.io -->

# Taxis

## class

```cpp
virtual void       SetBinLabel(Int_t bin, const char *label);//设置bin名称

virtual void       SetRangeUser(Double_t ufirst, Double_t ulast);  // *MENU* 人为设置坐标范围！
virtual void       SetTicks(Option_t *option="+"); // *MENU*    //  option = "+"  ticks drawn on the "positive side" (default) ; option = "-"  ticks drawn on the "negative side" ; option = "+-" ticks drawn on both sides
```


## code

```cpp
//设置坐标范围
TAxis *axis=h1->GetXaxis();
axis->SetRangeUser(950,1300);
TAxis *axisy=h1->GetYaxis();
axisy->SetRangeUser(0,100);


//直方图坐标设置 TAttAxis.h
h3->SetTitle("");
h3->GetXaxis()->SetNdivisions(611);//坐标刻度设置，n = n1 + 100*n2 + 10000*n3 ，Where n1 is the number of primary divisions, n2 is the number of second order divisions and n3 is the number of third order divisions.
h3->GetXaxis()->SetTitleSize(20);
h3->GetXaxis()->SetTitleFont(43);
h3->GetXaxis()->SetTitleOffset(3.);//调节title与坐标轴的距离
h3->GetXaxis()->SetLabelFont(44);
h3->GetXaxis()->SetLabelSize(20);
h3->GetYaxis()->SetTitle("ratio h1/h2 ");
h3->GetYaxis()->SetNdivisions(505);
h3->GetYaxis()->SetTitleSize(20);
h3->GetYaxis()->SetTitleFont(43);
h3->GetYaxis()->SetTitleOffset(1.55);//调节title与坐标轴的距离
h3->GetYaxis()->SetLabelFont(43);
h3->GetYaxis()->SetLabelSize(15);


h1->SetLineColor(1);
//1 black;2 red;3 green;4 blue;5yellow;6 magenta;……
h1->SetLogx();   //设置x轴为对数坐标轴
h1->GetXaxis()->SetTitle("x");
h->GetXaxis()->SetTitle("X axis title");
h->GetYaxis()->SetTitle("Y axis title");
h->GetZaxis()->SetTitle("Z axis title");
h1->SetTitle("title name;X axis;Y axis");
h->GetXaxis()->CenterTitle();
h->GetYaxis()->CenterTitle();

h1->SetFrameFillColor(33);    //设置图片背景颜色

```

<!-- Taxis.md ends here -->
