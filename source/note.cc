// note.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 12月  5 11:27:32 2014 (+0800)
// Last-Updated: 四 10月  8 18:15:44 2015 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 7
// URL: http://wuhongyi.github.io 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Char_t      //Signed Character 1 byte
UChar_t     //Unsigned Character 1 byte
hort_t      //Signed Short integer 2 bytes
UShort_t    //Unsigned Short integer 2 bytes
Int_t       //Signed integer 4 bytes
UInt_t      //Unsigned integer 4 bytes
Long64_t    //Portable signed long integer 8 bytes
ULong64_t   //Portable unsigned long integer 8 bytes
Float_t     //Float 4 bytes
Double_t    //Float 8 bytes
Double32_t  //Double 8 bytes in memory, written as a Float 4 bytes
Bool_t      //Boolean (0=false, 1=true)


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


//gRandom is a pointer to the current random number generator. By default, it points to a TRandom3 object, based on the “Mersenne-Twister” generator. This generator is very fast and has very good random proprieties (a very long period of 10600 ). Setting the seed to 0 implies that the seed will be uniquely generated using the TUUID. Any other value will be used as a constant. The following basic random distributions are provided: Rndm() or Uniform(min,max), Gaus(mean,sigma), Exp(tau), BreitWigner(mean,sigma), Landau(mean,sigma), Poisson(mean), Binomial(ntot,prob). You can customize your ROOT session by replacing the random number generator. You can delete gRandom and recreate it with your own. For example:
root[] delete gRandom;
root[] gRandom = new TRandom2(0); //seed=0
//TRandom2 is another generator, which is also very fast and uses only three words for its state.


//gFile is the pointer to the current opened file in the ROOT session.

//gDirectory is a pointer to the current directory. The concept and role of a directory is explained in the chapter “Input/Output”.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  





// 
// note.cc ends here
