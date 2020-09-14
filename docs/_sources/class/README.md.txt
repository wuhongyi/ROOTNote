<!-- README.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:27:32 2014 (+0800)
;; Last-Updated: 一 10月 31 21:53:53 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 17
;; URL: http://wuhongyi.cn -->

# 类的使用

<!-- A B C D E F G H I J K L M N O P Q R S T U V W X Y Z -->

本章主要介绍常用类中的函数

包括：函数的使用、函数的参数设置、示例代码等

```cpp
Char_t      //Signed Character 1 byte
UChar_t     //Unsigned Character 1 byte
Short_t      //Signed Short integer 2 bytes
UShort_t    //Unsigned Short integer 2 bytes
Int_t       //Signed integer 4 bytes
UInt_t      //Unsigned integer 4 bytes
Long64_t    //Portable signed long integer 8 bytes
ULong64_t   //Portable unsigned long integer 8 bytes
Float_t     //Float 4 bytes
Double_t    //Float 8 bytes
Double32_t  //Double 8 bytes in memory, written as a Float 4 bytes
Bool_t      //Boolean (0=false, 1=true)
```

```
The symbols used for the type are:
C: a character string terminated by the 0 character
B: an 8 bit signed integer
b: an 8 bit unsigned integer
S: a 16 bit signed integer
s: a 16 bit unsigned integer
I: a 32 bit signed integer
i: a 32 bit unsigned integer
L: a 64 bit signed integer
l: a 64 bit unsigned integer
F: a 32 bit floating point
D: a 64 bit floating point
O: [the letter ‘o’, not a zero] a boolean (Bool_t)
```

```
The type of information shown in the histogram statistics box can be selected with:
      gStyle->SetOptStat(mode);

The "mode" has up to nine digits that can be set to on (1 or 2), off (0).

      mode = ksiourmen  (default = 000001111)
      k = 1;  kurtosis printed
      k = 2;  kurtosis and kurtosis error printed
      s = 1;  skewness printed
      s = 2;  skewness and skewness error printed
      i = 1;  integral of bins printed
      o = 1;  number of overflows printed
      u = 1;  number of underflows printed
      r = 1;  rms printed
      r = 2;  rms and rms error printed
      m = 1;  mean value printed
      m = 2;  mean and mean error values printed
      e = 1;  number of entries printed
      n = 1;  name of histogram is printed
```



```cpp
gROOT->GetListOfClasses()
gROOT->GetListOfColors()
gROOT->GetListOfTypes()
gROOT->GetListOfGlobals()
gROOT->GetListOfGlobalFunctions()
gROOT->GetListOfFiles()
gROOT->GetListOfMappedFiles()
gROOT->GetListOfSockets()
gROOT->GetListOfCanvases()
gROOT->GetListOfStyles()
gROOT->GetListOfFunctions()
gROOT->GetListOfSpecials()
gROOT->GetListOfGeometries()
gROOT->GetListOfBrowsers()
gROOT->GetListOfMessageHandlers()
//These methods return a TSeqCollection, meaning a collection of objects, and they can be used to do list operations such as finding an object, or traversing the list and calling a method for each of the members. See the TCollection class description for the full set of methods supported for a collection. For example, to find a canvas called c1you can do:
root[] gROOT->GetListOfCanvases()->FindObject("c1")
//This returns a pointer to a TObject, and before you can use it as a canvas you need to cast it to a TCanvas*.


//A graphic object is always drawn on the active pad. It is convenient to access the active pad, no matter what it is. For that, we have gPad that is always pointing to the active pad. For example, if you want to change the fill color of the active pad to blue, but you do not know its name, you can use gPad .
root[] gPad->SetFillColor(38)

// gRandom 默认调用 TRandom3

//gRandom is a pointer to the current random number generator. By default, it points to a TRandom3 object, based on the “Mersenne-Twister” generator. This generator is very fast and has very good random proprieties (a very long period of 10600 ). Setting the seed to 0 implies that the seed will be uniquely generated using the TUUID. Any other value will be used as a constant. The following basic random distributions are provided: Rndm() or Uniform(min,max), Gaus(mean,sigma), Exp(tau), BreitWigner(mean,sigma), Landau(mean,sigma), Poisson(mean), Binomial(ntot,prob). You can customize your ROOT session by replacing the random number generator. You can delete gRandom and recreate it with your own. For example:
root[] delete gRandom;
root[] gRandom = new TRandom2(0); //seed=0
//TRandom2 is another generator, which is also very fast and uses only three words for its state.


//gFile is the pointer to the current opened file in the ROOT session.

//gDirectory is a pointer to the current directory. The concept and role of a directory is explained in the chapter “Input/Output”.
```

## 画图参数

```
//Fitting Histograms

• *fname:The name of the fitted function (the model) is passed as the first parameter. This name may be one of ROOT pre-defined function names or a user-defined function. The functions below are predefined, and can be used with the TH1::Fit method:
• “gaus” Gaussian function with 3 parameters: f(x) = p0*exp(-0.5*((x-p1)/p2)ˆ2)
• “expo”An Exponential with 2 parameters: f(x) = exp(p0+p1*x)
• “polN ” A polynomial of degree N : f(x) = p0 + p1*x + p2*x2 +...
• “landau” Landau function with mean and sigma. This function has been adaptedfrom the CERNLIB routine G110 denlan.
• *option:The second parameter is the fitting option. Here is the list of fitting options:
• “W” Set all weights to 1 for non empty bins; ignore error bars
• “WW” Set all weights to 1 including empty bins; ignore error bars
• “I” Use integral of function in bin instead of value at bin center
• “L” Use log likelihood method (default is chi-square method)
• “U” Use a user specified fitting algorithm
• “Q” Quiet mode (minimum printing)
• “V” Verbose mode (default is between Q and V)
• “E” Perform better errors estimation using the Minos technique
• “M” Improve fit results
• “R” Use the range specified in the function range
• “N” Do not store the graphics function, do not draw
• “0” Do not plot the result of the fit. By default the fitted function is drawn unless the option “N” above is specified.
• “+” Add this new fitted function to the list of fitted functions (by default, the previous function is deleted and only the last one is kept)
• “B”Use this option when you want to fix one or more parameters and the fitting function is like polN, expo, landau, gaus.
• “LL”An improved Log Likelihood fit in case of very low statistics and when bincontentsare not integers. Do not use this option if bin contents are large (greater than 100).
• “C”In case of linear fitting, don’t calculate the chisquare (saves time).
• “F”If fitting a polN, switch to Minuit fitter (by default, polN functions are fitted by the linear fitter).
• *goption:The third parameter is the graphics option that is the same as in the TH1::Draw (see the chapter Draw Options).
• xxmin, xxmax:Thee fourth and fifth parameters specify the range over which to apply the fit.
```


```
//Graph Draw Options
The various drawing options for a graph are explained in TGraph::PaintGraph. They are:
• “L” A simple poly-line between every points is drawn   //折线图,将每个bin用线连接
• “F” A fill area is drawn
• “F1” Idem as “F” but fill area is no more repartee around X=0 or Y=0
• “F2” draw a fill area poly line connecting the center of bins
• “A” Axis are drawn around the graph
• “C” A smooth curve is drawn  //将每个bin用一条光滑的曲线连接起来
• “*” A star is plotted at each point//每个点用*表示
• “P” The current marker of the graph is plotted at each point
• “B” A bar chart is drawn at each point
• “[]” Only the end vertical/horizontal lines of the error bars are drawn. This option only applies to the TGraphAsymmErrors.
• “1” ylow = rwymin

The TGraphPolar drawing options are:
“O” Polar labels are paint orthogonally to the polargram radius.
“P” Polymarker are paint at each point position.
“E” Paint error bars.
“F” Paint fill area (closed polygon).
“A”Force axis redrawing even if a polagram already exists.
```


```
//Draw Options                   //eg. h->Draw("E1SAME"); 或 h->SetOption("lego");h->Draw();
The following draw options are supported on all histogram classes:
• “AXIS”: Draw only the axis.
• “HIST”: When a histogram has errors, it is visualized by default with error bars. To visualize it without errors use HIST together with the required option (e.g. “HIST SAME C”).
• “SAME”: Superimpose on previous picture in the same pad.
• “CYL”: Use cylindrical coordinates.
• “POL”: Use polar coordinates.
• “SPH”: Use spherical coordinates.
• “PSR”: Use pseudo-rapidity/phi coordinates.  //通常的二维直方图
• “LEGO”: Draw a lego plot with hidden line removal.
• “LEGO1”: Draw a lego plot with hidden surface removal.
• “LEGO2”: Draw a lego plot using colors to show the cell contents.
• “SURF”: Draw a surface plot with hidden line removal.
• “SURF1”: Draw a surface plot with hidden surface removal.
• “SURF2”: Draw a surface plot using colors to show the cell contents.
• “SURF3”: Same as SURF with a contour view on the top.
• “SURF4”: Draw a surface plot using Gouraud shading.
• “SURF5”: Same as SURF3 but only the colored contour is drawn. Used with option CYL , SPH or PSR it allows to draw colored contours on a sphere, a cylinder or in a pseudo rapidly space. In Cartesian or polar coordinates,option SURF3 is used.

The following options are supported for 1-D histogram classes:
• “AH”: Draw the histogram, but not the axis labels and tick marks
• “B”: Draw a bar chart
• “C”: Draw a smooth curve through the histogram bins  //将每个bin用一条光滑的曲线连接起来
• “E”: Draw the error bars    //“E0”- “E4” 与误差有关的参数
• “E0”: Draw the error bars including bins with 0 contents
• “E1”: Draw the error bars with perpendicular lines at the edges  //垂直方向的误差棒
• “E2”: Draw the error bars with rectangles
• “E3”: Draw a fill area through the end points of the vertical error bars
• “E4”: Draw a smoothed filled area through the end points of the error bars
• “L”: Draw a line through the bin contents  //将每个bin用线连接
• “P”: Draw a (poly)marker at each bin using the histogram’s current marker style
• “P0”: Draw current marker at each bin including empty bins
• “PIE”: Draw a Pie Chart
• “*H”: Draw histogram with a * at each bin
• “LF2”: Draw histogram as with option “L” but with a fill area. Note that “L” also draws a fill area if the histogram fill color is set but the fill area corresponds to the histogram contour.
• “9”: Force histogram to be drawn in high resolution mode. By default, the histogram is drawn in low resolution in case the number of bins is greater than the number of pixels in the current pad
• “][”: Draw histogram without the vertical lines for the first and the last bin. Use it when superposing many histograms on the same picture.

The following options are supported for 2-D histogram classes:
• “ARR”: Arrow mode. Shows gradient between adjacent cells
• “BOX”: Draw a box for each cell with surface proportional to contents  //每个单元画一BOX，Box面积正比于bin contents
• “BOX1”: A sunken button is drawn for negative values, a raised one for positive values
• “COL”: Draw a box for each cell with a color scale varying with contents  //每个单元画一个box，颜色与 bin contents相关
• “COLZ”: Same as “COL” with a drawn color palette  //同col，但是画一个条显示颜色与内容对应关系
• “CONT”: Draw a contour plot (same as CONT0 )  //画轮廓图
• “CONTZ”: Same as “CONT” with a drawn color palette
• “CONT0”: Draw a contour plot using surface colors to distinguish contours
• “CONT1”: Draw a contour plot using line styles to distinguish contours
• “CONT2”: Draw a contour plot using the same line style for all contours
• “CONT3”: Draw a contour plot using fill area colors
• “CONT4”: Draw a contour plot using surface colors (SURF2 option at theta = 0)
• "CONT5": Use Delaunay triangles to compute the contours
• “LIST”: Generate a list of TGraph objects for each contour
• “FB”: To be used with LEGO or SURFACE , suppress the Front-Box
• “BB”: To be used with LEGO or SURFACE , suppress the Back-Box
• “A”: To be used with LEGO or SURFACE , suppress the axis
• “SCAT”: Draw a scatter-plot (default)  //绘制散点图
• “SPEC”: Use TSpectrum2Painter tool for drawing
• “TEXT”: Draw bin contents as text (format set via gStyle->SetPaintTextFormat) .
• “TEXTnn”: Draw bin contents as text at angle nn ( 0<nn<90 ).
• “[cutg]”: Draw only the sub-range selected by the TCutG name “cutg”.
• “Z”: The “Z” option can be specified with the options: BOX, COL, CONT, SURF, and LEGO to display the color palette with an axis indicating the value of the corresponding color on the right side ofthe picture.

The following options are supported for 3-D histogram classes:
• " " : Draw a 3D scatter plot.
• “BOX”: Draw a box for each cell with volume proportional to contents
• “LEGO”: Same as “BOX”
• “ISO”: Draw an iso surface
• “FB”: Suppress the Front-Box
• “BB”: Suppress the Back-Box
• “A”: Suppress the axis
```
       

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

```cpp
TH3D *h3 = new TH3D("h3", "h3", 20, -2, 2, 20, -2, 2, 20, 0, 4);
Double_t x,y,z;
for (Int_t i=0; i<10000; i++) {
gRandom->Rannor(x,y);     
z=x*x+y*y;
h3->Fill(x,y,z);
}
h3->Draw("iso");

TF3 *fun3 = new TF3("fun3","sin(x*x+y*y+z*z-36)",-2,2,-2,2,-2,2);
fun3->Draw();
```


```cpp
//进度滑动条
TCanvas *c1 = new TCanvas("c1","The HSUM example",200,10,600,400);
c1->SetGrid();
gBenchmark->Start("hsum");
// Create some histograms.
auto total  = new TH1F("total","This is the total distribution",100,-4,4);
auto main   = new TH1F("main","Main contributor",100,-4,4);
auto s1     = new TH1F("s1","This is the first signal",100,-4,4);
auto s2     = new TH1F("s2","This is the second signal",100,-4,4);
total->Sumw2();  // store the sum of squares of weights
total->SetMarkerStyle(21);
total->SetMarkerSize(0.7);
main->SetFillColor(16);
s1->SetFillColor(42);
s2->SetFillColor(46);
TSlider *slider = 0;////////滑动条

// Fill histograms randomly
gRandom->SetSeed();
const Int_t kUPDATE = 500;
Float_t xs1, xs2, xmain;
for ( Int_t i=0; i<10000; i++) {
  xmain = gRandom->Gaus(-1,1.5);
  xs1   = gRandom->Gaus(-0.5,0.5);
  xs2   = gRandom->Landau(1,0.15);
  main->Fill(xmain);
  s1->Fill(xs1,0.3);
  s2->Fill(xs2,0.2);
  total->Fill(xmain);
  total->Fill(xs1,0.3);
  total->Fill(xs2,0.2);
  if (i && (i%kUPDATE) == 0) {
    if (i == kUPDATE) {
      total->Draw("e1p");
      main->Draw("same");
      s1->Draw("same");
      s2->Draw("same");
      c1->Update();
      slider = new TSlider("slider",
			   "test",4.2,0,4.6,total->GetMaximum(),38);
      slider->SetFillColor(46);
    }
    if (slider) slider->SetRange(0,Float_t(i)/10000.);
    c1->Modified();
    c1->Update();
  }
 }
slider->SetRange(0,1);
total->Draw("sameaxis"); // to redraw axis hidden by the fill area
c1->Modified();
gBenchmark->Show("hsum");
```



```cpp
TPaveLabel pl;

//basic 2-d options
Float_t xMin=0.67, yMin=0.875, xMax=0.85, yMax=0.95;
Int_t cancolor = 17;
TCanvas c2h("c2h","2-d options",10,10,800,600);
c2h.Divide(2,2);
c2h.SetFillColor(cancolor);
c2h.cd(1);
h2.Draw();       pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"SCAT","brNDC");
c2h.cd(2);
h2.Draw("box");  pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"BOX","brNDC");
c2h.cd(3);
h2.Draw("arr");  pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"ARR","brNDC");
c2h.cd(4);
h2.Draw("colz"); pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"COLZ","brNDC");
c2h.Update();

//text option
TCanvas ctext("ctext","text option",50,50,800,600);
gPad->SetGrid();
ctext.SetFillColor(cancolor);
ctext.SetGrid();
h2.Draw("text"); pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"TEXT","brNDC");
ctext.Update();

//contour options
TCanvas cont("contours","contours",100,100,800,600);
cont.Divide(2,2);
gPad->SetGrid();
cont.SetFillColor(cancolor);
cont.cd(1);
h2.Draw("contz"); pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"CONTZ","brNDC");
cont.cd(2);
gPad->SetGrid();
h2.Draw("cont1"); pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"CONT1","brNDC");
cont.cd(3);
gPad->SetGrid();
h2.Draw("cont2"); pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"CONT2","brNDC");
cont.cd(4);
gPad->SetGrid();
h2.Draw("cont3"); pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"CONT3","brNDC");
cont.Update();

//lego options
TCanvas lego("lego","lego options",150,150,800,600);
lego.Divide(2,2);
lego.SetFillColor(cancolor);
lego.cd(1);
h2.Draw("lego");     pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"LEGO","brNDC");
lego.cd(2);
h2.Draw("lego1");    pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"LEGO1","brNDC");
lego.cd(3);
gPad->SetTheta(61); gPad->SetPhi(-82);
h2.Draw("surf1pol"); pl.DrawPaveLabel(xMin,yMin,xMax+0.05,yMax,"SURF1POL","brNDC");
lego.cd(4);
gPad->SetTheta(21); gPad->SetPhi(-90);
h2.Draw("surf1cyl"); pl.DrawPaveLabel(xMin,yMin,xMax+0.05,yMax,"SURF1CYL","brNDC");
lego.Update();

//surface options
TCanvas surf("surfopt","surface options",200,200,800,600);
surf.Divide(2,2);
surf.SetFillColor(cancolor);
surf.cd(1);
h2.Draw("surf1");   pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"SURF1","brNDC");
surf.cd(2);
h2.Draw("surf2z");  pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"SURF2Z","brNDC");
surf.cd(3);
h2.Draw("surf3");   pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"SURF3","brNDC");
surf.cd(4);
h2.Draw("surf4");   pl.DrawPaveLabel(xMin,yMin,xMax,yMax,"SURF4","brNDC");
surf.Update();
```







<!-- README.md ends here -->
