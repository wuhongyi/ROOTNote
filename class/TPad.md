<!-- TPad.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 五 8月 12 21:50:35 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 22
;; URL: http://wuhongyi.github.io -->

# TPad

## class

```cpp
void              Modified(Bool_t flag=1);//  Set to true when pad is modified

```


## code

```cpp
//图片修饰
gPad->SetTickx(1);//上边框有刻度
gPad->SetTicky(1);//右边框有刻度
gPad->SetTickx(2);//上边框有刻度和数值
gPad->SetTicky(2);//右边框有刻度和数值



TPad* pad1 = new TPad("pad1","pad1",0.03,0.62,0.50,0.92,32);//x起点，y起点，x终点，y终点，颜色
pad1->Draw();
pad1->cd();
pad1->SetLogy();//y轴 对数坐标
pad1->SetGridy();//y轴 网格
pad2->SetLogx();
pad2->SetGridx();


```


<!-- TPad.md ends here -->
