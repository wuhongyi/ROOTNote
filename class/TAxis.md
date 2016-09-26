<!-- TAxis.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 二 9月 13 18:14:12 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 11
;; URL: http://wuhongyi.github.io -->

# TAxis

继承 TNamed, TAttAxis

## class

```cpp
   TAxis();
   TAxis(Int_t nbins, Double_t xmin, Double_t xmax);
   TAxis(Int_t nbins, const Double_t *xbins);
   TAxis(const TAxis &axis);
   virtual ~TAxis();
   TAxis& operator=(const TAxis&);

   Bool_t     CanExtend() const { return (fBits2 & kCanExtend);  }
   void       SetCanExtend(Bool_t canExtend) { fBits2 = canExtend ? (fBits2 | kCanExtend) : (fBits2 & ~kCanExtend); }
   void       SetNoAlphanumeric(Bool_t noalpha = kTRUE) {
      fBits2 = noalpha ? (fBits2 | kNotAlpha) : (fBits2 & ~kNotAlpha);
      if (IsAlphanumeric() ) {
         SetCanExtend(kFALSE);
         SetAlphanumeric(kFALSE);
      }
   }
   void               CenterLabels(Bool_t center=kTRUE);
   void               CenterTitle(Bool_t center=kTRUE);
   
/// Choose a reasonable time format from the coordinates in the active pad and the number of divisions in this axis
/// If orientation = "X", the horizontal axis of the pad will be used for ref.
/// If orientation = "Y", the vertical axis of the pad will be used for ref.   
   const char        *ChooseTimeFormat(Double_t axislength=0);
   virtual void       Copy(TObject &axis) const;
   virtual void       Delete(Option_t * /*option*/ ="") { }
   virtual Int_t      DistancetoPrimitive(Int_t px, Int_t py);
   virtual TObject   *DrawClone(Option_t * /*option*/ ="") const {return 0;}
   
/// Execute action corresponding to one event
///  This member function is called when an axis is clicked with the locator.
///  The axis range is set between the position where the mouse is pressed and the position where it is released.
///  If the mouse position is outside the current axis range when it is released the axis is unzoomed with the corresponding proportions.
///  Note that the mouse does not need to be in the pad or even canvas when it is released.   
   virtual void       ExecuteEvent(Int_t event, Int_t px, Int_t py);

/// Find bin number corresponding to abscissa x. NOTE: this method does not work with alphanumeric bins !!!
/// If x is underflow or overflow, attempt to extend the axis if TAxis::kCanExtend is true. Otherwise, return 0 or fNbins+1.
   virtual Int_t      FindBin(Double_t x);
   virtual Int_t      FindBin(Double_t x) const { return FindFixBin(x); }

/// Find bin number with label.
/// If the List of labels does not exist create it and make the axis alphanumeric
/// If one wants just to add a single label- just call TAxis::SetBinLabel
/// If label is not in the list of labels do the following depending on the
/// bit TAxis::kCanExtend; of the axis.
///   - if the bit is set add the new label and if the number of labels exceeds
///      the number of bins, double the number of bins via TH1::LabelsInflate
///   - if the bit is not set and the histogram has labels in each bin
///        set the bit automatically and consider the histogram as alphanumeric
///     if histogram has only some bins with labels then the histogram is not
///     consider alphanumeric and return -1
/// -1 is returned only when the Axis has no parent histogram
   virtual Int_t      FindBin(const char *label);

/// Find bin number corresponding to abscissa x
/// Identical to TAxis::FindBin except that if x is an underflow/overflow no attempt is made to extend the axis.
   virtual Int_t      FindFixBin(Double_t x) const;

/// Find bin number with label.
/// If the List of labels does not exist or the label doe not exist just return -1 .
/// Do not attempt to modify the axis. This is different than FindBin
   virtual Int_t      FindFixBin(const char *label) const;
   virtual Double_t   GetBinCenter(Int_t bin) const;
   virtual Double_t   GetBinCenterLog(Int_t bin) const;
   const char        *GetBinLabel(Int_t bin) const;
   virtual Double_t   GetBinLowEdge(Int_t bin) const;
   virtual Double_t   GetBinUpEdge(Int_t bin) const;
   virtual Double_t   GetBinWidth(Int_t bin) const;
   virtual void       GetCenter(Double_t *center) const;
           Bool_t     GetCenterLabels() const { return TestBit(kCenterLabels); }
           Bool_t     GetCenterTitle() const { return TestBit(kCenterTitle); }
           Bool_t     GetDecimals() const { return TestBit(kDecimals); }
   THashList         *GetLabels() const { return fLabels; }
   virtual void       GetLowEdge(Double_t *edge) const;
           Bool_t     GetMoreLogLabels() const { return TestBit(kMoreLogLabels); }
           Int_t      GetNbins() const { return fNbins; }
           Bool_t     GetNoExponent() const { return TestBit(kNoExponent); }
   virtual TObject   *GetParent() const {return fParent;}
           Bool_t     GetRotateTitle() const { return TestBit(kRotateTitle); }
   virtual const char *GetTicks() const;
   virtual Bool_t     GetTimeDisplay() const {return fTimeDisplay;}
   virtual const char *GetTimeFormat() const {return fTimeFormat.Data();}
   virtual const char *GetTimeFormatOnly() const;
   const char        *GetTitle() const {return fTitle.Data();}
   const TArrayD     *GetXbins() const {return &fXbins;}
           Int_t      GetFirst() const;
           Int_t      GetLast() const;
           Double_t   GetXmin() const {return fXmin;}
           Double_t   GetXmax() const {return fXmax;}
   virtual void       ImportAttributes(const TAxis *axis);
   Bool_t             IsVariableBinSize() const {
                         // true if axis has variable bin sizes, false otherwise
                         return (fXbins.GetSize() != 0);
                      }

///  Set option(s) to draw axis with labels
///  option = "a" sort by alphabetic order
///         = ">" sort by decreasing values
///         = "<" sort by increasing values
///         = "h" draw labels horizonthal
///         = "v" draw labels vertical
///         = "u" draw labels up (end of label right adjusted)
///         = "d" draw labels down (start of label left adjusted)
   virtual void       LabelsOption(Option_t *option="h");  // *MENU*
           void       RotateTitle(Bool_t rotate=kTRUE); // *TOGGLE* *GETTER=GetRotateTitle
   virtual void       SaveAttributes(std::ostream &out, const char *name, const char *subname);
   virtual void       Set(Int_t nbins, Double_t xmin, Double_t xmax);
   virtual void       Set(Int_t nbins, const Float_t *xbins);
   virtual void       Set(Int_t nbins, const Double_t *xbins);
   virtual void       SetBinLabel(Int_t bin, const char *label);//设置bin名称
           void       SetDecimals(Bool_t dot = kTRUE); // *TOGGLE* *GETTER=GetDecimals
   virtual void       SetDefaults();
   virtual void       SetDrawOption(Option_t * /*option*/ ="") { }
   virtual void       SetLimits(Double_t xmin, Double_t xmax) { /* set axis limits */ fXmin = xmin; fXmax = xmax; }
           void       SetMoreLogLabels(Bool_t more=kTRUE);  // *TOGGLE* *GETTER=GetMoreLogLabels
           void       SetNoExponent(Bool_t noExponent=kTRUE);  // *TOGGLE* *GETTER=GetNoExponent
   virtual void       SetParent(TObject *obj) {fParent = obj;}
   virtual void       SetRange(Int_t first=0, Int_t last=0);  // *MENU*
   virtual void       SetRangeUser(Double_t ufirst, Double_t ulast);  // *MENU* 人为设置坐标范围！

///  Set ticks orientation.
///  option = "+"  ticks drawn on the "positive side" (default)
///  option = "-"  ticks drawn on the "negative side"
///  option = "+-" ticks drawn on both sides
   virtual void       SetTicks(Option_t *option="+"); // *MENU*  //  option = "+"  ticks drawn on the "positive side" (default) ; option = "-"  ticks drawn on the "negative side" ; option = "+-" ticks drawn on both sides
   virtual void       SetTimeDisplay(Int_t value) {fTimeDisplay = (value != 0);} // *TOGGLE*
   virtual void       SetTimeFormat(const char *format="");  // *MENU*
   virtual void       SetTimeOffset(Double_t toffset, Option_t *option="local");
   virtual void       UnZoom();  // *MENU*
   virtual void       ZoomOut(Double_t factor=0, Double_t offset=0);  // *MENU*
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

```cpp
/// Change the format used for time plotting
///
/// The format string for date and time use the same options as the one used
/// in the standard strftime C function, i.e. :
/// for date :
///
///          %a abbreviated weekday name
///          %b abbreviated month name
///          %d day of the month (01-31)
///          %m month (01-12)
///          %y year without century
///
/// for time :
///
///          %H hour (24-hour clock)
///          %I hour (12-hour clock)
///          %p local equivalent of AM or PM
///          %M minute (00-59)
///          %S seconds (00-61)
///          %% %
///
/// This function allows also to define the time offset. It is done via %F
/// which should be appended at the end of the format string. The time
/// offset has the following format: 'yyyy-mm-dd hh:mm:ss'
/// Example:
///
h = new TH1F("Test","h",3000,0.,200000.);
h->GetXaxis()->SetTimeDisplay(1);
h->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2000-02-28 13:00:01");
///
/// This defines the time format being "dd/mm/yy" and the time offset as the
/// February 28th 2003 at 13:00:01
///
/// If %F is not specified, the time offset used will be the one defined by:
/// gStyle->SetTimeOffset. For example like that:
///
TDatime da(2003,02,28,12,00,00);
gStyle->SetTimeOffset(da.Convert());
```


## example



<!-- TAxis.md ends here -->
