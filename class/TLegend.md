<!-- TLegend.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 五 8月 12 22:31:34 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 10
;; URL: http://wuhongyi.cn -->

# TLegend

## class

<!-- ```cpp -->

<!-- ``` -->

```cpp
// `TLegend` inherits from `TAttText` therefore changing any
// text attributes (text alignment, font, color...) on a legend will changed the
// text attributes on each line.

// In particular it can be interesting to change the text alignement that way. In
// order to have a base-line vertical alignment instead of a centered one simply do:
// ~~~ {.cpp}
//    leg->SetTextAlign(13);
// ~~~
// or
// ~~~ {.cpp}
//    leg->SetTextAlign(11);
// ~~~
// The default value of some `TLegend` attributes can be changed using
// `gStyle`. The default settings are:
// ~~~ {.cpp}
//    SetLegendBorderSize(1);
//    SetLegendFillColor(0);
//    SetLegendFont(42);
//    SetLegendTextSize(0.);
// ~~~
// The global attributes change the default values for the next created legends.

// Text attributes can be also changed individually on each legend entry:
// ~~~ {.cpp}
//    TLegendEntry *le = leg->AddEntry(h1,"Histogram filled with random numbers","f");
//    le->SetTextColor(kBlue);;
// ~~~

// Note that the `TPad` class has a method to build automatically a legend
// for all objects in the pad. It is called `TPad::BuildLegend()`.

// Each item in the legend is added using the `AddEntry` method. This
// method defines the object to be added (by reference or name), the label
// associated to this object and an option which a combination of:

//   - L: draw line associated with TAttLine if obj inherits from TAttLine
//   - P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
//   - F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
//   - E: draw vertical error bar

```

## code

```cpp

```

## example

```cpp
TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
legend->SetHeader("The Legend Title");
legend->SetTextSize(0.05);
legend->SetBorderSize(0);
legend->AddEntry(h1,"All nations","");
legend->AddEntry(h2,"French only","");
legend->Draw();
```

<!-- TLegend.md ends here -->
