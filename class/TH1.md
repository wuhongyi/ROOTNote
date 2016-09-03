<!-- TH1.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 12:32:36 2014 (+0800)
;; Last-Updated: 四 9月  1 23:05:30 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 17
;; URL: http://wuhongyi.github.io -->

# TH1

- TH1C : histograms with one byte per channel.   Maximum bin content = 127
- TH1S : histograms with one short per channel.  Maximum bin content = 32767
- TH1I : histograms with one int per channel.    Maximum bin content = 2147483647
- TH1F : histograms with one float per channel.  Maximum precision 7 digits
- TH1D : histograms with one double per channel. Maximum precision 14 digits

```
The TH*C classes also inherit from the array class TArrayC.
The TH*S classes also inherit from the array class TArrayS.
The TH*I classes also inherit from the array class TArrayI.
The TH*F classes also inherit from the array class TArrayF.
The TH*D classes also inherit from the array class TArrayD.
```

When an histogram is created, a reference to it is automatically added to the list of in-memory objects for the current file or directory. This default behaviour can be changed by:

```cpp
h->SetDirectory(0);          // for the current histogram h
TH1::AddDirectory(kFALSE);   // sets a global switch disabling the reference
```

When the histogram is deleted, the reference to it is removed from the list of objects in memory. When a file is closed, all histograms in memory associated with this file are automatically deleted.

----

All histogram types support either fix or variable bin sizes. 2-D histograms may have fix size bins along X and variable size bins along Y or vice-versa. The functions to fill, manipulate, draw or access histograms are identical in both cases.


Convention for numbering bins

For all histogram types: nbins, xlow, xup

```
bin = 0;       underflow bin
bin = 1;       first bin with low-edge xlow INCLUDED
bin = nbins;   last bin with upper-edge xup EXCLUDED
bin = nbins+1; overflow bin
```


## class

```cpp
protected:
   TH1();
   TH1(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup);
   TH1(const char *name,const char *title,Int_t nbinsx,const Float_t *xbins);
   TH1(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins);
   virtual Int_t    BufferFill(Double_t x, Double_t w);
   virtual Bool_t   FindNewAxisLimits(const TAxis* axis, const Double_t point, Double_t& newMin, Double_t &newMax);
   virtual void     SavePrimitiveHelp(std::ostream &out, const char *hname, Option_t *option = "");
   static Bool_t    RecomputeAxisLimits(TAxis& destAxis, const TAxis& anAxis);
   static Bool_t    SameLimitsAndNBins(const TAxis& axis1, const TAxis& axis2);

   virtual Double_t DoIntegral(Int_t ix1, Int_t ix2, Int_t iy1, Int_t iy2, Int_t iz1, Int_t iz2, Double_t & err,
                               Option_t * opt, Bool_t doerr = kFALSE) const;

   virtual void     DoFillN(Int_t ntimes, const Double_t *x, const Double_t *w, Int_t stride=1);

   static bool CheckAxisLimits(const TAxis* a1, const TAxis* a2);
   static bool CheckBinLimits(const TAxis* a1, const TAxis* a2);
   static bool CheckBinLabels(const TAxis* a1, const TAxis* a2);
   static bool CheckEqualAxes(const TAxis* a1, const TAxis* a2);
   static bool CheckConsistentSubAxes(const TAxis *a1, Int_t firstBin1, Int_t lastBin1, const TAxis *a2, Int_t firstBin2=0, Int_t lastBin2=0);
   static bool CheckConsistency(const TH1* h1, const TH1* h2);

public:
   // TH1 status bits
   enum {
      kNoStats     = BIT(9),  // don't draw stats box
      kUserContour = BIT(10), // user specified contour levels
      //kCanRebin    = BIT(11), // FIXME DEPRECATED - to be removed, replaced by SetCanExtend / CanExtendAllAxes
      kLogX        = BIT(15), // X-axis in log scale
      kIsZoomed    = BIT(16), // bit set when zooming on Y axis
      kNoTitle     = BIT(17), // don't draw the histogram title
      kIsAverage   = BIT(18), // Bin contents are average (used by Add)
      kIsNotW      = BIT(19)  // Histogram is forced to be not weighted even when the histogram is filled with weighted different than 1.
   };
   // size of statistics data (size of  array used in GetStats()/ PutStats )
   // s[0]  = sumw       s[1]  = sumw2
   // s[2]  = sumwx      s[3]  = sumwx2
   // s[4]  = sumwy      s[5]  = sumwy2   s[6]  = sumwxy
   // s[7]  = sumwz      s[8]  = sumwz2   s[9]  = sumwxz   s[10]  = sumwyz
   // s[11] = sumwt      s[12] = sumwt2                 (11 and 12 used only by TProfile3D)
   enum {
      kNstat       = 13  // size of statistics data (up to TProfile3D)
   };


   virtual ~TH1();

   virtual Bool_t   Add(TF1 *h1, Double_t c1=1, Option_t *option="");
   virtual Bool_t   Add(const TH1 *h1, Double_t c1=1);//该函数是将h1直方图进行c1倍的放大或缩小后加到当前直方图中。
   virtual Bool_t   Add(const TH1 *h, const TH1 *h2, Double_t c1=1, Double_t c2=1); // *MENU* 将 h1 放大或缩小 c1 倍加上 h2 放大或缩小 c2 倍相加赋给 h。
   virtual void     AddBinContent(Int_t bin);//在第 bin 个 bin 上计数加一。
   virtual void     AddBinContent(Int_t bin, Double_t w);
   static  void     AddDirectory(Bool_t add=kTRUE);
   static  Bool_t   AddDirectoryStatus();
   virtual void     Browse(TBrowser *b);
   virtual Bool_t   CanExtendAllAxes() const;
   virtual Double_t Chi2Test(const TH1* h2, Option_t *option = "UU", Double_t *res = 0) const;
   virtual Double_t Chi2TestX(const TH1* h2, Double_t &chi2, Int_t &ndf, Int_t &igood,Option_t *option = "UU",  Double_t *res = 0) const;
   virtual Double_t Chisquare(TF1 * f1, Option_t *option = "") const;
   virtual void     ClearUnderflowAndOverflow();
   virtual Double_t ComputeIntegral(Bool_t onlyPositive = false);
   TObject*         Clone(const char* newname=0) const;//克隆直方图，这里的 Close 是新开辟一块内存空间存储新直方图的，克隆之后，原始直方图的修改或删除对克隆的直方图没有影响。而TH1D *hnew =h;这个只是将新建的对象指向 h 的地址。
   virtual void     Copy(TObject &hnew) const;
   virtual void     DirectoryAutoAdd(TDirectory *);
   virtual Int_t    DistancetoPrimitive(Int_t px, Int_t py);
   virtual Bool_t   Divide(TF1 *f1, Double_t c1=1);
   virtual Bool_t   Divide(const TH1 *h1);
   virtual Bool_t   Divide(const TH1 *h1, const TH1 *h2, Double_t c1=1, Double_t c2=1, Option_t *option=""); // *MENU*
   virtual void     Draw(Option_t *option="");//画图
   virtual TH1     *DrawCopy(Option_t *option="", const char * name_postfix = "_copy") const;
   virtual TH1     *DrawNormalized(Option_t *option="", Double_t norm=1) const;
   virtual void     DrawPanel(); // *MENU*
   virtual Int_t    BufferEmpty(Int_t action=0);
   virtual void     Eval(TF1 *f1, Option_t *option="");
   virtual void     ExecuteEvent(Int_t event, Int_t px, Int_t py);
   virtual void     ExtendAxis(Double_t x, TAxis *axis);
   virtual TH1     *FFT(TH1* h_output, Option_t *option);
   virtual Int_t    Fill(Double_t x);//将数据填充进直方图
   virtual Int_t    Fill(Double_t x, Double_t w);
   virtual Int_t    Fill(const char *name, Double_t w);
   virtual void     FillN(Int_t ntimes, const Double_t *x, const Double_t *w, Int_t stride=1);
   virtual void     FillN(Int_t, const Double_t *, const Double_t *, const Double_t *, Int_t) {;}
   virtual void     FillRandom(const char *fname, Int_t ntimes=5000);
   virtual void     FillRandom(TH1 *h, Int_t ntimes=5000);
   virtual Int_t    FindBin(Double_t x, Double_t y=0, Double_t z=0);//寻找x值对应的bin数 对一维直方图，返回 x 值所在 bin，若为二维直方图，返回 （x，y） 所在 bin，三维同理。
   virtual Int_t    FindFixBin(Double_t x, Double_t y=0, Double_t z=0) const;
   virtual Int_t    FindFirstBinAbove(Double_t threshold=0, Int_t axis=1) const;
   virtual Int_t    FindLastBinAbove (Double_t threshold=0, Int_t axis=1) const;
   virtual TObject *FindObject(const char *name) const;
   virtual TObject *FindObject(const TObject *obj) const;
   virtual TFitResultPtr    Fit(const char *formula ,Option_t *option="" ,Option_t *goption="", Double_t xmin=0, Double_t xmax=0); // *MENU*
   virtual TFitResultPtr    Fit(TF1 *f1 ,Option_t *option="" ,Option_t *goption="", Double_t xmin=0, Double_t xmax=0);
   virtual void     FitPanel(); // *MENU*
   TH1             *GetAsymmetry(TH1* h2, Double_t c2=1, Double_t dc2=0);
   Int_t            GetBufferLength() const {return fBuffer ? (Int_t)fBuffer[0] : 0;}
   Int_t            GetBufferSize  () const {return fBufferSize;}
   const   Double_t *GetBuffer() const {return fBuffer;}
   static  Int_t    GetDefaultBufferSize();
   virtual Double_t *GetIntegral();//ROOT 6  //TH1积分，当前bin值为前面所有bin的累积，然后归一化（最大值为1），返回该数组
   TH1             *GetCumulative(Bool_t forward = kTRUE, const char* suffix = "_cumulative") const;//ROOT 6 //TH1积分，当前bin值为前面所有bin的累积。

   TList           *GetListOfFunctions() const { return fFunctions; }

   virtual Int_t    GetNdivisions(Option_t *axis="X") const;
   virtual Color_t  GetAxisColor(Option_t *axis="X") const;
   virtual Color_t  GetLabelColor(Option_t *axis="X") const;
   virtual Style_t  GetLabelFont(Option_t *axis="X") const;
   virtual Float_t  GetLabelOffset(Option_t *axis="X") const;
   virtual Float_t  GetLabelSize(Option_t *axis="X") const;
   virtual Style_t  GetTitleFont(Option_t *axis="X") const;
   virtual Float_t  GetTitleOffset(Option_t *axis="X") const;
   virtual Float_t  GetTitleSize(Option_t *axis="X") const;
   virtual Float_t  GetTickLength(Option_t *axis="X") const;
   virtual Float_t  GetBarOffset() const {return Float_t(0.001*Float_t(fBarOffset));}
   virtual Float_t  GetBarWidth() const  {return Float_t(0.001*Float_t(fBarWidth));}
   virtual Int_t    GetContour(Double_t *levels=0);
   virtual Double_t GetContourLevel(Int_t level) const;
   virtual Double_t GetContourLevelPad(Int_t level) const;

   virtual Int_t    GetBin(Int_t binx, Int_t biny=0, Int_t binz=0) const;
   virtual void     GetBinXYZ(Int_t binglobal, Int_t &binx, Int_t &biny, Int_t &binz) const;
   virtual Double_t GetBinCenter(Int_t bin) const;//返回该bin的中点坐标。
   virtual Double_t GetBinContent(Int_t bin) const;//返回该bin的计数.
   virtual Double_t GetBinContent(Int_t bin, Int_t) const { return GetBinContent(bin); }
   virtual Double_t GetBinContent(Int_t bin, Int_t, Int_t) const { return GetBinContent(bin); }
   virtual Double_t GetBinError(Int_t bin) const;//Return value of error associated to bin number bin. if the sum of squares of weights has been defined (via Sumw2),this function returns the sqrt(sum of w2). otherwise it returns the sqrt(contents) for this bin.
   virtual Double_t GetBinError(Int_t binx, Int_t biny) const { return GetBinError(GetBin(binx, biny)); } // for 2D histograms only
   virtual Double_t GetBinError(Int_t binx, Int_t biny, Int_t binz) const { return GetBinError(GetBin(binx, biny, binz)); } // for 3D histograms only
   virtual Double_t GetBinErrorLow(Int_t bin) const;//Return lower error associated to bin number bin. The error will depend on the statistic option used will return the binContent - lower interval value
   virtual Double_t GetBinErrorUp(Int_t bin) const;//Return upper error associated to bin number bin. The error will depend on the statistic option used will return the binContent - upper interval value
   virtual EBinErrorOpt  GetBinErrorOption() const { return fBinStatErrOpt; }
   virtual Double_t GetBinLowEdge(Int_t bin) const;//return bin lower edge for 1D historam
   virtual Double_t GetBinWidth(Int_t bin) const;//返回bin的宽度。
   virtual Double_t GetBinWithContent(Double_t c, Int_t &binx, Int_t firstx=0, Int_t lastx=0,Double_t maxdiff=0) const;
   virtual void     GetCenter(Double_t *center) const;
   static  Bool_t   GetDefaultSumw2();
   TDirectory      *GetDirectory() const {return fDirectory;}
   virtual Double_t GetEntries() const;  //returns the number of entries
   virtual Double_t GetEffectiveEntries() const;
   virtual TF1     *GetFunction(const char *name) const;
   virtual Int_t    GetDimension() const { return fDimension; }
   virtual Double_t GetKurtosis(Int_t axis=1) const;//For axis =1, 2 or 3 returns kurtosis of the histogram along x, y or z axis.Kurtosis(gaussian(0, 1)) = 0. For axis =11, 12 or 13 returns the approximate standard error of kurtosis of the histogram along x, y or z axis. Note, that since third and fourth moment are not calculated at the fill time, kurtosis and its standard error are computed bin by bin
   virtual void     GetLowEdge(Double_t *edge) const;
   virtual Double_t GetMaximum(Double_t maxval=FLT_MAX) const;
   virtual Int_t    GetMaximumBin() const;
   virtual Int_t    GetMaximumBin(Int_t &locmax, Int_t &locmay, Int_t &locmaz) const;
   virtual Double_t GetMaximumStored() const {return fMaximum;}
   virtual Double_t GetMinimum(Double_t minval=-FLT_MAX) const;
   virtual Int_t    GetMinimumBin() const;
   virtual Int_t    GetMinimumBin(Int_t &locmix, Int_t &locmiy, Int_t &locmiz) const;
   virtual Double_t GetMinimumStored() const {return fMinimum;}
   virtual Double_t GetMean(Int_t axis=1) const;//returns the mean value along axis. For axis = 1,2 or 3 returns the mean value of the histogram along X,Y or Z axis. For axis = 11, 12, 13 returns the standard error of the mean value of the histogram along X, Y or Z axis. Note that the mean value/RMS is computed using the bins in the currently defined range (see TAxis::SetRange). By default the range includes all bins from 1 to nbins included, excluding underflows and overflows. To force the underflows and overflows in the computation, one must call the static function TH1::StatOverflows(kTRUE) before filling the histogram.
   virtual Double_t GetMeanError(Int_t axis=1) const;//Return standard error of mean of this histogram along the X axis.  Note that the mean value/RMS is computed using the bins in the currently defined range (see TAxis::SetRange). By default the range includes  all bins from 1 to nbins included, excluding underflows and overflows. To force the underflows and overflows in the computation, one must call the static function TH1::StatOverflows(kTRUE) before filling the histogram.  Also note, that although the definition of standard error doesn't include the assumption of normality, many uses of this feature implicitly assume it.
   virtual Int_t    GetNbinsX() const {return fXaxis.GetNbins();}//获取该轴bin值
   virtual Int_t    GetNbinsY() const {return fYaxis.GetNbins();}
   virtual Int_t    GetNbinsZ() const {return fZaxis.GetNbins();}
   virtual Int_t    GetNcells() const {return fNcells; }//number of bins(1D), cells (2D) +U/Overflows
   virtual Double_t GetNormFactor() const {return fNormFactor;}//如果没有设置将会返回0。这个因子是将直方图面积设为该因子。设置该因子参考 SetNormFactor(Double_t factor=1)。
   virtual char    *GetObjectInfo(Int_t px, Int_t py) const;
   Option_t        *GetOption() const {return fOption.Data();}

   TVirtualHistPainter *GetPainter(Option_t *option="");

   virtual Int_t    GetQuantiles(Int_t nprobSum, Double_t *q, const Double_t *probSum=0);
   virtual Double_t GetRandom() const;//return a random number distributed according the histogram bin contents.  This function checks if the bins integral exists. If not, the integral is evaluated, normalized to one. The integral is automatically recomputed if the number of entries is not the same then when the integral was computed. NB Only valid for 1-d histograms. Use GetRandom2 or 3 otherwise. If the histogram has a bin with negative content a NaN is returned
   virtual void     GetStats(Double_t *stats) const;
// fill the array stats from the contents of this histogram
// The array stats must be correctly dimensioned in the calling program.
// stats[0] = sumw
// stats[1] = sumw2
// stats[2] = sumwx
// stats[3] = sumwx2
// If no axis-subrange is specified (via TAxis::SetRange), the array stats is simply a copy of the statistics quantities computed at filling time.If a sub-range is specified, the function recomputes these quantities from the bin contents in the current axis range.
// Note that the mean value/RMS is computed using the bins in the currently defined range (see TAxis::SetRange). By default the range includes all bins from 1 to nbins included, excluding underflows and overflows. To force the underflows and overflows in the computation, one must call the static function TH1::StatOverflows(kTRUE) before filling the histogram.
   virtual Double_t GetStdDev(Int_t axis=1) const;//returns the sigma distribution along axis
   virtual Double_t GetStdDevError(Int_t axis=1) const;
   virtual Double_t GetSumOfWeights() const;//Return the sum of weights excluding under/overflows.
   virtual TArrayD *GetSumw2() {return &fSumw2;}
   virtual const TArrayD *GetSumw2() const {return &fSumw2;}
   virtual Int_t    GetSumw2N() const {return fSumw2.fN;}
           Double_t GetRMS(Int_t axis=1) const { return GetStdDev(axis); }
// For axis = 1,2 or 3 returns the Sigma value of the histogram along X, Y or Z axis. For axis = 11, 12 or 13 returns the error of RMS estimation along X, Y or Z axis for Normal distribution.
// Note that the mean value/sigma is computed using the bins in the currently defined range (see TAxis::SetRange). By default the range includes all bins from 1 to nbins included, excluding underflows and overflows. To force the underflows and overflows in the computation, one must  call the static function TH1::StatOverflows(kTRUE) before filling  the histogram.
// Note that this function returns the Standard Deviation (Sigma) of the distribution (not RMS). The Sigma estimate is computed as Sqrt((1/N)*(Sum(x_i-x_mean)^2)). The name "RMS" was introduced many years ago (Hbook/PAW times). 
           Double_t GetRMSError(Int_t axis=1) const { return GetStdDevError(axis); }
// Return error of RMS estimation for Normal distribution.
// Note that the mean value/RMS is computed using the bins in the currently defined range (see TAxis::SetRange). By default the range includes all bins from 1 to nbins included, excluding underflows and overflows.  To force the underflows and overflows in the computation, one must call the static function TH1::StatOverflows(kTRUE) before filling the histogram.
// Value returned is standard deviation of sample standard deviation.
Note that it is an approximated value which is valid only in the case that the original data distribution is Normal. The correct one would require the 4-th momentum value, which cannot be accurately estimated from an histogram since the x-information for all entries is not kept.
   virtual Double_t GetSkewness(Int_t axis=1) const;
           TAxis*   GetXaxis()  { return &fXaxis; }//返回指向该坐标轴 TAxis* 的指针，可对该轴进行设置。具体参考TAxis类的使用。
           TAxis*   GetYaxis()  { return &fYaxis; }//返回指向该坐标轴 TAxis* 的指针，可对该轴进行设置。具体参考TAxis类的使用。
           TAxis*   GetZaxis()  { return &fZaxis; }//返回指向该坐标轴 TAxis* 的指针，可对该轴进行设置。具体参考TAxis类的使用。
     const TAxis*   GetXaxis() const { return &fXaxis; }
     const TAxis*   GetYaxis() const { return &fYaxis; }
     const TAxis*   GetZaxis() const { return &fZaxis; }
   virtual Double_t Integral(Option_t *option="") const;//Return integral of bin contents. Only bins in the bins range are considered. By default the integral is computed as the sum of bin contents in the range.  if option "width" is specified, the integral is the sum of the bin contents multiplied by the bin width in x.
   virtual Double_t Integral(Int_t binx1, Int_t binx2, Option_t *option="") const;//returns the integral of bin contents in a given bin range
   virtual Double_t IntegralAndError(Int_t binx1, Int_t binx2, Double_t & err, Option_t *option="") const;
   virtual Double_t Interpolate(Double_t x);//Given a point x, approximates the value via linear interpolation based on the two nearest bin centers. 获取x的y值。其值为最近两个bin线性插值。
   virtual Double_t Interpolate(Double_t x, Double_t y);
   virtual Double_t Interpolate(Double_t x, Double_t y, Double_t z);
           Bool_t   IsBinOverflow(Int_t bin) const;//Return true if the bin is overflow.
           Bool_t   IsBinUnderflow(Int_t bin) const;//Return true if the bin is overflow.
   virtual Double_t AndersonDarlingTest(const TH1 *h2, Option_t *option="") const;
   virtual Double_t AndersonDarlingTest(const TH1 *h2, Double_t &advalue) const;
   virtual Double_t KolmogorovTest(const TH1 *h2, Option_t *option="") const;// statistical test of compatibility in shape between two histograms
   virtual void     LabelsDeflate(Option_t *axis="X");// Reduce the number of bins for the axis passed in the option to the number of bins having a label. The method will remove only the extra bins existing after the last "labeled" bin. Note that if there are "un-labeled" bins present between "labeled" bins they will not be removed.
   virtual void     LabelsInflate(Option_t *axis="X");//Double the number of bins for axis.Refill histogram. This function is called by TAxis::FindBin(const char *label).
   virtual void     LabelsOption(Option_t *option="h", Option_t *axis="X");
   virtual Long64_t Merge(TCollection *list);
   virtual Bool_t   Multiply(TF1 *h1, Double_t c1=1);//Performs the operation: this = this*c1*f1. if errors are defined (see TH1::Sumw2), errors are also recalculated.  Only bins inside the function range are recomputed. IMPORTANT NOTE: If you intend to use the errors of this histogram later you should call Sumw2 before making this operation. This is particularly important if you fit the histogram after TH1::Multiply The function return kFALSE if the Multiply operation failed.
   virtual Bool_t   Multiply(const TH1 *h1);// Multiply this histogram by h1.  this = this*h1   If errors of this are available (TH1::Sumw2), errors are recalculated.  Note that if h1 has Sumw2 set, Sumw2 is automatically called for this if not already set.   IMPORTANT NOTE: If you intend to use the errors of this histogram later you should call Sumw2 before making this operation. This is particularly important if you fit the histogram after TH1::Multiply. The function return kFALSE if the Multiply operation failed
   virtual Bool_t   Multiply(const TH1 *h1, const TH1 *h2, Double_t c1=1, Double_t c2=1, Option_t *option=""); // *MENU*  Replace contents of this histogram by multiplication of h1 by h2. this = (c1*h1)*(c2*h2)   If errors of this are available (TH1::Sumw2), errors are recalculated. Note that if h1 or h2 have Sumw2 set, Sumw2 is automatically called for this if not already set.   IMPORTANT NOTE: If you intend to use the errors of this histogram later you should call Sumw2 before making this operation. This is particularly important if you fit the histogram after TH1::Multiply. The function return kFALSE if the Multiply operation failed.
   virtual void     Paint(Option_t *option="");//Control routine to paint any kind of histograms.  This function is automatically called by TCanvas::Update.(see TH1::Draw for the list of options)
   virtual void     Print(Option_t *option="") const;//Print some global quantities for this histogram. If option "base" is given, number of bins and ranges are also printed.  If option "range" is given, bin contents and errors are also printed for all bins in the current range (default 1-->nbins).  If option "all" is given, bin contents and errors are also printed for all bins including under and overflows.
   virtual void     PutStats(Double_t *stats);
   virtual TH1     *Rebin(Int_t ngroup=2, const char*newname="", const Double_t *xbins=0);  // *MENU*
   virtual TH1     *RebinX(Int_t ngroup=2, const char*newname="") { return Rebin(ngroup,newname, (Double_t*) 0); }
   virtual void     Rebuild(Option_t *option="");
   virtual void     RecursiveRemove(TObject *obj);
   virtual void     Reset(Option_t *option="");//将其清除重置
// Reset this histogram: contents, errors, etc.
// if option "ICE" is specified, resets only Integral, Contents and Errors.  
// if option "ICES" is specified, resets only Integral, Contents , Errors and Statistics  
// if option "M"   is specified, resets also Minimum and Maximum  
// The option "ICE" is used when extending the histogram (in ExtendAxis, LabelInflate, etc..)  
// The option "ICES is used in combination with the buffer (see BufferEmpty and BufferFill)  
   virtual void     ResetStats();//Reset the statistics including the number of entries and replace with values calculates from bin content. The number of entries is set to the total bin content or (in case of weighted histogram) to number of effective entries.
   virtual void     SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual void     Scale(Double_t c1=1, Option_t *option="");//比例缩放
   virtual void     SetAxisColor(Color_t color=1, Option_t *axis="X");
   virtual void     SetAxisRange(Double_t xmin, Double_t xmax, Option_t *axis="X");
   virtual void     SetBarOffset(Float_t offset=0.25) {fBarOffset = Short_t(1000*offset);}
   virtual void     SetBarWidth(Float_t width=0.5) {fBarWidth = Short_t(1000*width);}
   virtual void     SetBinContent(Int_t bin, Double_t content);
   virtual void     SetBinContent(Int_t bin, Int_t, Double_t content) { SetBinContent(bin, content); }
   virtual void     SetBinContent(Int_t bin, Int_t, Int_t, Double_t content) { SetBinContent(bin, content); }
   virtual void     SetBinError(Int_t bin, Double_t error);
   virtual void     SetBinError(Int_t binx, Int_t biny, Double_t error);
   virtual void     SetBinError(Int_t binx, Int_t biny, Int_t binz, Double_t error);
   virtual void     SetBins(Int_t nx, Double_t xmin, Double_t xmax);
   virtual void     SetBins(Int_t nx, const Double_t *xBins);
   virtual void     SetBins(Int_t nx, Double_t xmin, Double_t xmax, Int_t ny, Double_t ymin, Double_t ymax);
   virtual void     SetBins(Int_t nx, const Double_t *xBins, Int_t ny, const Double_t *yBins);
   virtual void     SetBins(Int_t nx, Double_t xmin, Double_t xmax, Int_t ny, Double_t ymin, Double_t ymax,
                            Int_t nz, Double_t zmin, Double_t zmax);
   virtual void     SetBins(Int_t nx, const Double_t *xBins, Int_t ny, const Double_t * yBins, Int_t nz,
                            const Double_t *zBins);
   virtual void     SetBinsLength(Int_t = -1) { } //redefined in derived classes
   virtual void     SetBinErrorOption(EBinErrorOpt type) { fBinStatErrOpt = type; }
   virtual void     SetBuffer(Int_t buffersize, Option_t *option="");
   virtual UInt_t   SetCanExtend(UInt_t extendBitMask);
   virtual void     SetContent(const Double_t *content);
   virtual void     SetContour(Int_t nlevels, const Double_t *levels=0);
   virtual void     SetContourLevel(Int_t level, Double_t value);
   static  void     SetDefaultBufferSize(Int_t buffersize=1000);
   static  void     SetDefaultSumw2(Bool_t sumw2=kTRUE);
   virtual void     SetDirectory(TDirectory *dir);
   virtual void     SetEntries(Double_t n) {fEntries = n;};
   virtual void     SetError(const Double_t *error);
   virtual void     SetLabelColor(Color_t color=1, Option_t *axis="X");
   virtual void     SetLabelFont(Style_t font=62, Option_t *axis="X");
   virtual void     SetLabelOffset(Float_t offset=0.005, Option_t *axis="X");
   virtual void     SetLabelSize(Float_t size=0.02, Option_t *axis="X");

   /*
    * Set the minimum / maximum value for the Y axis (1-D histograms) or Z axis (2-D histograms)
    *   By default the maximum / minimum value used in drawing is the maximum / minimum value of the histogram
    * plus a margin of 10%. If these functions are called, the values are used without any extra margin.
    */
   virtual void     SetMaximum(Double_t maximum = -1111) { fMaximum = maximum; }; // *MENU*  Set the minimum / maximum value for the Y axis (1-D histograms) or Z axis (2-D histograms). By default the maximum / minimum value used in drawing is the maximum / minimum value of the histogram plus a margin of 10\%. If these functions are called, the values are used without any extra margin.
   virtual void     SetMinimum(Double_t minimum = -1111) { fMinimum = minimum; }; // *MENU*

   virtual void     SetName(const char *name); // *MENU*  Change the name of this histogram. Histograms are named objects in a THashList. We must update the hashlist if we change the name. We protect this operation
   virtual void     SetNameTitle(const char *name, const char *title);//Change the name and title of this histogram. Histograms are named objects in a THashList. We must update the hashlist if we change the name
   virtual void     SetNdivisions(Int_t n=510, Option_t *axis="X");
   virtual void     SetNormFactor(Double_t factor=1) {fNormFactor = factor;}
   virtual void     SetStats(Bool_t stats=kTRUE); // *MENU*
   virtual void     SetOption(Option_t *option=" ") {fOption = option;}
   virtual void     SetTickLength(Float_t length=0.02, Option_t *axis="X");
   virtual void     SetTitleFont(Style_t font=62, Option_t *axis="X");
   virtual void     SetTitleOffset(Float_t offset=1, Option_t *axis="X");
   virtual void     SetTitleSize(Float_t size=0.02, Option_t *axis="X");
   virtual void     SetTitle(const char *title);  // *MENU*  Change (i.e. set) the title. if title is in the form "stringt;stringx;stringy;stringz" the histogram title is set to stringt, the x axis title to stringx, the y axis title to stringy, and the z axis title to stringz. To insert the character ";" in one of the titles, one should use "\#;" or "\#semicolon".
   virtual void     SetXTitle(const char *title) {fXaxis.SetTitle(title);}
   virtual void     SetYTitle(const char *title) {fYaxis.SetTitle(title);}
   virtual void     SetZTitle(const char *title) {fZaxis.SetTitle(title);}
   virtual TH1     *ShowBackground(Int_t niter=20, Option_t *option="same"); // *MENU*
   virtual Int_t    ShowPeaks(Double_t sigma=2, Option_t *option="", Double_t threshold=0.05); // *MENU*
   virtual void     Smooth(Int_t ntimes=1, Option_t *option=""); // *MENU* Smooth bin contents of this histogram. if option contains "R" smoothing is applied only to the bins defined in the X axis range (default is to smooth all bins). Bin contents are replaced by their smooth values. Errors (if any) are not modified. the smoothing procedure is repeated ntimes (default=1)
   static  void     SmoothArray(Int_t NN, Double_t *XX, Int_t ntimes=1);//smooth array xx, translation of Hbook routine hsmoof.F    based on algorithm 353QH twice presented by J. Friedman in Proc.of the 1974 CERN School of Computing, Norway, 11-24 August, 1974.
   static  void     StatOverflows(Bool_t flag=kTRUE);
   virtual void     Sumw2(Bool_t flag = kTRUE);
   void             UseCurrentStyle();
   static  TH1     *TransformHisto(TVirtualFFT *fft, TH1* h_output,  Option_t *option);


   // TODO: Remove obsolete methods in v6-04
   virtual Double_t GetCellContent(Int_t binx, Int_t biny) const
                        { Obsolete("GetCellContent", "v6-00", "v6-04"); return GetBinContent(GetBin(binx, biny)); }
   virtual Double_t GetCellError(Int_t binx, Int_t biny) const
                        { Obsolete("GetCellError", "v6-00", "v6-04"); return GetBinError(binx, biny); }
   virtual void     RebinAxis(Double_t x, TAxis *axis)
                        { Obsolete("RebinAxis", "v6-00", "v6-04"); ExtendAxis(x, axis); }
   virtual void     SetCellContent(Int_t binx, Int_t biny, Double_t content)
                        { Obsolete("SetCellContent", "v6-00", "v6-04"); SetBinContent(GetBin(binx, biny), content); }
   virtual void     SetCellError(Int_t binx, Int_t biny, Double_t content)
                        { Obsolete("SetCellError", "v6-00", "v6-04"); SetBinError(binx, biny, content); }
```


## code

```cpp
TH1F *h1=new TH1F("stats name","title name",number of bins,min,max);
TH1F *h1=new TH1F("stats name","title name;X axis;Y axis",number of bins,min,max);
 float x=gRandom->Uniform(-5.,5.);
 h1->Fill(x);                       //均匀分布
h1->FillRandom("gaus",50000);       //
h1->Draw();
```

```cpp
//循环创建图片
TH1D  h[16];
char Stringtemp[256];
for(int i=0;i<16;i++){ 
  sprintf(Stringtemp,"h[%d]",i);//这样创建数组名不好，直接 "h%d"这样好
  h[i]=new TH1D(Stringtemp,"",4096,0,4096);
} 
```

```cpp
//默认情况下，Draw 将会清空当 前Pad 再画当前直方图，如想要一个图上多个直方图，将第二个及之后的直方图 Option_t 设为 "same"。
  TH1D *h=new TH1D("h","the title",60,-3.0,3.0);
  TH1D *h1=new TH1D("h1","",60,-3.0,3.0);
  TRandom *r =new TRandom();
  for (int i = 0; i<1000; ++i)
  {
    h->Fill(r->Gaus());
    h1->Fill(r->Gaus(1,1));
  }
  h->Draw();
  // h1->Draw();
  h1->Draw("same");
```

```cpp
//Double_t   *GetIntegral();
//Return a pointer to the array of bins integral.
//返回一个指向数组的指针，当前值为 bin 从 0到当前 bin 面积所占的比例。
  int bin=60;
  TH1D *h=new TH1D("h","the title",bin,-3.0,3.0);
  TRandom *r =new TRandom();
  for (int i = 0; i<1000; ++i)
    {
      h->Fill(r->Gaus());
    }
  double *Integral;
  Integral=h->GetIntegral();
  for (int i = 0; i<bin; ++i)
    {
      std::cout<<i<<"  "<<Integral[i]<<std::endl;
    }
  h->Draw();
```


```cpp
//克隆直方图，这里的 Close 是新开辟一块内存空间存储新直方图的，克隆之后，原始直方图的修改或删除对克隆的直方图没有影响。而TH1D *hnew =h;这个只是将新建的对象指向 h 的地址。
TH1D *h=new TH1D("h","the title",60,-3.0,3.0);
TRandom *r =new TRandom();
for (int i = 0; i<1000; ++i)
{
  h->Fill(r->Gaus());
}
TH1D *hnew = (TH1D*)h->Clone("hnew");
// TH1D *hnew =h;
h->Reset();
hnew->Draw();
```

## example

<!-- ```cpp -->

<!-- ``` -->



<!-- TH1.md ends here -->
