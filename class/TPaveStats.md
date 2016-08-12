<!-- TPaveStats.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 五 8月 12 22:31:52 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.github.io -->

# TPaveStats

## class

<!-- ```cpp -->

<!-- ``` -->

## code

```cpp
//设置TPave参数
TPaveStats *ps2 = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
ps2->SetX1NDC(0.65); ps2->SetX2NDC(0.85);//设置位置
ps2->SetTextColor(kRed);//设置颜色
```

<!-- TPaveStats.md ends here -->
