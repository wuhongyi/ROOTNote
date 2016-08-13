<!-- TPaveText.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 六 8月 13 12:39:17 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.github.io -->

# TPaveText

## class


## code


## example

```cpp
TPaveText *pt = new TPaveText(0.6,0.85,0.98,0.98,"brNDC");//添加图片的注释。
pt->SetFillColor(18);
pt->SetTextAlign(12);
pt->AddText("Use the axis Context Menu LabelsOption");
pt->AddText(" \"a\"   to sort by alphabetic order");
pt->AddText(" \">\"   to sort by decreasing vakues");
pt->AddText(" \"<\"   to sort by increasing vakues");
pt->Draw();
```





<!-- TPaveText.md ends here -->
