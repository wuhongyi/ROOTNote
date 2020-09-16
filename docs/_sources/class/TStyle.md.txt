<!-- TStyle.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 19:01:37 2016 (+0800)
;; Last-Updated: 三 9月 16 10:28:22 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TStyle+

继承 TNamed, TAttLine, TAttFill, TAttMarker, TAttText

## class

```cpp
   virtual void     Browse(TBrowser *b);
   static  void     BuildStyles();
   virtual void     Copy(TObject &style) const;
   virtual void     cd();

   virtual Int_t    DistancetoPrimitive(Int_t px, Int_t py);
   Int_t            GetNdivisions(Option_t *axis="X") const;
   TAttText        *GetAttDate() {return &fAttDate;}
   Color_t          GetAxisColor(Option_t *axis="X") const;
   Color_t          GetLabelColor(Option_t *axis="X") const;
   Style_t          GetLabelFont(Option_t *axis="X") const;
   Float_t          GetLabelOffset(Option_t *axis="X") const;
   Float_t          GetLabelSize(Option_t *axis="X") const;
   Color_t          GetTitleColor(Option_t *axis="X") const;  //return axis title color of pad title color
   Style_t          GetTitleFont(Option_t *axis="X") const;   //return axis title font of pad title font
   Float_t          GetTitleOffset(Option_t *axis="X") const; //return axis title offset
   Float_t          GetTitleSize(Option_t *axis="X") const;   //return axis title size
   Float_t          GetTickLength(Option_t *axis="X") const;

   Float_t          GetBarOffset() const {return fBarOffset;}
   Float_t          GetBarWidth() const {return fBarWidth;}
   Int_t            GetDrawBorder() const {return fDrawBorder;}
   Float_t          GetEndErrorSize() const {return fEndErrorSize;}
   Float_t          GetErrorX() const {return fErrorX;}
   Bool_t           GetCanvasPreferGL() const {return fCanvasPreferGL;}
   Color_t          GetCanvasColor() const {return fCanvasColor;}
   Width_t          GetCanvasBorderSize() const {return fCanvasBorderSize;}
   Int_t            GetCanvasBorderMode() const {return fCanvasBorderMode;}
   Int_t            GetCanvasDefH() const      {return fCanvasDefH;}
   Int_t            GetCanvasDefW() const      {return fCanvasDefW;}
   Int_t            GetCanvasDefX() const      {return fCanvasDefX;}
   Int_t            GetCanvasDefY() const      {return fCanvasDefY;}
   Int_t            GetColorPalette(Int_t i) const;
   Int_t            GetColorModelPS() const    {return fColorModelPS;}
   Float_t          GetDateX()  const          {return fDateX;}
   Float_t          GetDateY() const           {return fDateY;}
   const char      *GetFitFormat()       const {return fFitFormat.Data();}
   Int_t            GetHatchesLineWidth() const {return fHatchesLineWidth;}
   Double_t         GetHatchesSpacing() const  {return fHatchesSpacing;}
   Width_t          GetLegendBorderSize() const   {return fLegendBorderSize;}
   Color_t          GetLegendFillColor() const {return fLegendFillColor;}
   Style_t          GetLegendFont() const {return fLegendFont;}
   Double_t         GetLegendTextSize() const {return fLegendTextSize;}
   Int_t            GetNumberOfColors() const;
   Color_t          GetPadColor() const        {return fPadColor;}
   Width_t          GetPadBorderSize() const   {return fPadBorderSize;}
   Int_t            GetPadBorderMode() const   {return fPadBorderMode;}
   Float_t          GetPadBottomMargin() const {return fPadBottomMargin;}
   Float_t          GetPadTopMargin() const    {return fPadTopMargin;}
   Float_t          GetPadLeftMargin() const   {return fPadLeftMargin;}
   Float_t          GetPadRightMargin() const  {return fPadRightMargin;}
   Bool_t           GetPadGridX() const        {return fPadGridX;}
   Bool_t           GetPadGridY() const        {return fPadGridY;}
   Int_t            GetPadTickX() const        {return fPadTickX;}
   Int_t            GetPadTickY() const        {return fPadTickY;}
   Color_t          GetFuncColor() const       {return fFuncColor;}
   Style_t          GetFuncStyle() const       {return fFuncStyle;}
   Width_t          GetFuncWidth() const       {return fFuncWidth;}
   Color_t          GetGridColor() const       {return fGridColor;}
   Style_t          GetGridStyle() const       {return fGridStyle;}
   Width_t          GetGridWidth() const       {return fGridWidth;}
   Color_t          GetFrameFillColor()  const {return fFrameFillColor;}
   Color_t          GetFrameLineColor()  const {return fFrameLineColor;}
   Style_t          GetFrameFillStyle()  const {return fFrameFillStyle;}
   Style_t          GetFrameLineStyle()  const {return fFrameLineStyle;}
   Width_t          GetFrameLineWidth()  const {return fFrameLineWidth;}
   Width_t          GetFrameBorderSize() const {return fFrameBorderSize;}
   Int_t            GetFrameBorderMode() const {return fFrameBorderMode;}
   Color_t          GetHistFillColor()   const {return fHistFillColor;}
   Color_t          GetHistLineColor()   const {return fHistLineColor;}
   Style_t          GetHistFillStyle()   const {return fHistFillStyle;}
   Style_t          GetHistLineStyle()   const {return fHistLineStyle;}
   Width_t          GetHistLineWidth()   const {return fHistLineWidth;}
   Bool_t           GetHistMinimumZero() const {return fHistMinimumZero;}
   Double_t         GetHistTopMargin()   const {return fHistTopMargin;}
   Float_t          GetLegoInnerR() const {return fLegoInnerR;}
   Int_t            GetNumberContours() const {return fNumberContours;}
   Int_t            GetOptDate() const {return fOptDate;}
   Int_t            GetOptFile() const {return fOptFile;}
   Int_t            GetOptFit() const {return fOptFit;}
   Int_t            GetOptStat() const {return fOptStat;}
   Int_t            GetOptTitle() const {return fOptTitle;}
   Int_t            GetOptLogx() const {return fOptLogx;}
   Int_t            GetOptLogy() const {return fOptLogy;}
   Int_t            GetOptLogz() const {return fOptLogz;}
   const char      *GetPaintTextFormat() const {return fPaintTextFormat.Data();}
   void             GetPaperSize(Float_t &xsize, Float_t &ysize) const;
   Int_t            GetShowEventStatus() const {return fShowEventStatus;}
   Int_t            GetShowEditor() const {return fShowEditor;}
   Int_t            GetShowToolBar() const {return fShowToolBar;}

   Float_t          GetScreenFactor() const {return fScreenFactor;}
   Color_t          GetStatColor() const {return fStatColor;}
   Color_t          GetStatTextColor() const {return fStatTextColor;}
   Width_t          GetStatBorderSize() const {return fStatBorderSize;}
   Style_t          GetStatFont() const  {return fStatFont;}
   Float_t          GetStatFontSize() const  {return fStatFontSize;}
   Style_t          GetStatStyle() const  {return fStatStyle;}
   const char      *GetStatFormat() const {return fStatFormat.Data();}
   Float_t          GetStatX() const     {return fStatX;}
   Float_t          GetStatY() const     {return fStatY;}
   Float_t          GetStatW() const     {return fStatW;}
   Float_t          GetStatH() const     {return fStatH;}
   Int_t            GetStripDecimals() const {return fStripDecimals;}
   Double_t         GetTimeOffset() const {return fTimeOffset;} //return axis time offset
   Int_t            GetTitleAlign() {return fTitleAlign;} // return the histogram title TPaveLabel alignment
   Color_t          GetTitleFillColor() const {return fTitleColor;}  //return histogram title fill area color
   Color_t          GetTitleTextColor() const {return fTitleTextColor;}  //return histogram title text color
   Style_t          GetTitleStyle() const  {return fTitleStyle;}
   Float_t          GetTitleFontSize() const  {return fTitleFontSize;} //return histogram title font size
   Width_t          GetTitleBorderSize() const {return fTitleBorderSize;} //return border size of histogram title TPaveLabel
   Float_t          GetTitleXOffset() const {return GetTitleOffset("X");} //return X axis title offset
   Float_t          GetTitleXSize() const   {return GetTitleSize("X");}   //return X axis title size
   Float_t          GetTitleYOffset() const {return GetTitleOffset("Y");} //return Y axis title offset
   Float_t          GetTitleYSize() const   {return GetTitleSize("Y");}   //return Y axis title size
   Float_t          GetTitleX() const     {return fTitleX;}  //return left X position of histogram title TPavelabel
   Float_t          GetTitleY() const     {return fTitleY;}  //return left bottom position of histogram title TPavelabel
   Float_t          GetTitleW() const     {return fTitleW;}  //return width of histogram title TPaveLabel
   Float_t          GetTitleH() const     {return fTitleH;}  //return height of histogram title TPavelabel
   const char      *GetHeaderPS() const {return fHeaderPS.Data();}
   const char      *GetTitlePS()  const {return fTitlePS.Data();}
   const char      *GetLineStyleString(Int_t i=1) const;
   Float_t          GetLineScalePS() const {return fLineScalePS;}
   Bool_t           IsReading() const {return fIsReading;}
   virtual void     Paint(Option_t *option="");
   virtual void     Reset(Option_t *option="");

   void             SetColorModelPS(Int_t c=0);
   void             SetFitFormat(const char *format="5.4g") {fFitFormat = format;}
   void             SetHeaderPS(const char *header);
   void             SetHatchesLineWidth(Int_t l) {fHatchesLineWidth = l;}
   void             SetHatchesSpacing(Double_t h) {fHatchesSpacing = TMath::Max(0.1,h);}
   void             SetTitlePS(const char *pstitle);
   void             SetLineScalePS(Float_t scale=3) {fLineScalePS=scale;}
   void             SetLineStyleString(Int_t i, const char *text);
   void             SetNdivisions(Int_t n=510, Option_t *axis="X");
   void             SetAxisColor(Color_t color=1, Option_t *axis="X");
   void             SetLabelColor(Color_t color=1, Option_t *axis="X");
   void             SetLabelFont(Style_t font=62, Option_t *axis="X");
   void             SetLabelOffset(Float_t offset=0.005, Option_t *axis="X");
   void             SetLabelSize(Float_t size=0.04, Option_t *axis="X");
   void             SetLegoInnerR(Float_t rad=0.5) {fLegoInnerR = rad;}
   void             SetScreenFactor(Float_t factor=1) {fScreenFactor = factor;}
   void             SetTickLength(Float_t length=0.03, Option_t *axis="X");
   void             SetTitleColor(Color_t color=1, Option_t *axis="X"); //set axis title color or pad title color
   void             SetTitleFont(Style_t font=62, Option_t *axis="X"); //set axis title font or pad title font
   void             SetTitleOffset(Float_t offset=1, Option_t *axis="X"); //set axis title offset
   void             SetTitleSize(Float_t size=0.02, Option_t *axis="X");  //set axis title size or pad title size
   void             SetNumberContours(Int_t number=20);
   void             SetOptDate(Int_t datefl=1);
   void             SetOptFile(Int_t file=1) {fOptFile = file;}
   void             SetOptFit(Int_t fit=1);
   void             SetOptLogx(Int_t logx=1) {fOptLogx = logx;}
   void             SetOptLogy(Int_t logy=1) {fOptLogy = logy;}
   void             SetOptLogz(Int_t logz=1) {fOptLogz = logz;}
   void             SetOptStat(Int_t stat=1);
   void             SetOptStat(Option_t *stat);
   void             SetOptTitle(Int_t tit=1) {fOptTitle = tit;}
   void             SetBarOffset(Float_t baroff=0.5) {fBarOffset = baroff;}
   void             SetBarWidth(Float_t barwidth=0.5) {fBarWidth = barwidth;}
   void             SetDateX(Float_t x=0.01) {fDateX = x;}
   void             SetDateY(Float_t y=0.01) {fDateY = y;}
   void             SetEndErrorSize(Float_t np=2);
   void             SetErrorX(Float_t errorx=0.5) {fErrorX = errorx;}
   void             SetCanvasPreferGL(Bool_t prefer = kTRUE) {fCanvasPreferGL=prefer;}
   void             SetDrawBorder(Int_t drawborder=1) {fDrawBorder = drawborder;}
   void             SetCanvasColor(Color_t color=19) {fCanvasColor = color;}
   void             SetCanvasBorderSize(Width_t size=1) {fCanvasBorderSize = size;}
   void             SetCanvasBorderMode(Int_t mode=1) {fCanvasBorderMode = mode;}
   void             SetCanvasDefH(Int_t h=500) {fCanvasDefH = h;}
   void             SetCanvasDefW(Int_t w=700) {fCanvasDefW = w;}
   void             SetCanvasDefX(Int_t topx=10) {fCanvasDefX = topx;}
   void             SetCanvasDefY(Int_t topy=10) {fCanvasDefY = topy;}
   void             SetLegendBorderSize(Width_t size=4) {fLegendBorderSize = size;}
   void             SetLegendFillColor(Color_t color=0) {fLegendFillColor = color;}
   void             SetLegendFont(Style_t font=62) {fLegendFont = font;}
   void             SetLegendTextSize(Double_t size=0.) {fLegendTextSize = size;}
   void             SetPadColor(Color_t color=19) {fPadColor = color;}
   void             SetPadBorderSize(Width_t size=1) {fPadBorderSize = size;}
   void             SetPadBorderMode(Int_t mode=1) {fPadBorderMode = mode;}
   void             SetPadBottomMargin(Float_t margin=0.1) {fPadBottomMargin=margin;}
   void             SetPadTopMargin(Float_t margin=0.1)    {fPadTopMargin=margin;}
   void             SetPadLeftMargin(Float_t margin=0.1)   {fPadLeftMargin=margin;}
   void             SetPadRightMargin(Float_t margin=0.1)  {fPadRightMargin=margin;}
   void             SetPadGridX(Bool_t gridx) {fPadGridX = gridx;}
   void             SetPadGridY(Bool_t gridy) {fPadGridY = gridy;}
   void             SetPadTickX(Int_t tickx)  {fPadTickX = tickx;}
   void             SetPadTickY(Int_t ticky)  {fPadTickY = ticky;}
   void             SetFuncStyle(Style_t style=1) {fFuncStyle = style;}
   void             SetFuncColor(Color_t color=1) {fFuncColor = color;}
   void             SetFuncWidth(Width_t width=4) {fFuncWidth = width;}
   void             SetGridStyle(Style_t style=3) {fGridStyle = style;}
   void             SetGridColor(Color_t color=0) {fGridColor = color;}
   void             SetGridWidth(Width_t width=1) {fGridWidth = width;}
   void             SetFrameFillColor(Color_t color=1) {fFrameFillColor = color;}
   void             SetFrameLineColor(Color_t color=1) {fFrameLineColor = color;}
   void             SetFrameFillStyle(Style_t styl=0)  {fFrameFillStyle = styl;}
   void             SetFrameLineStyle(Style_t styl=0)  {fFrameLineStyle = styl;}
   void             SetFrameLineWidth(Width_t width=1) {fFrameLineWidth = width;}
   void             SetFrameBorderSize(Width_t size=1) {fFrameBorderSize = size;}
   void             SetFrameBorderMode(Int_t mode=1) {fFrameBorderMode = mode;}
   void             SetHistFillColor(Color_t color=1) {fHistFillColor = color;}
   void             SetHistLineColor(Color_t color=1) {fHistLineColor = color;}
   void             SetHistFillStyle(Style_t styl=0)  {fHistFillStyle = styl;}
   void             SetHistLineStyle(Style_t styl=0)  {fHistLineStyle = styl;}
   void             SetHistLineWidth(Width_t width=1) {fHistLineWidth = width;}
   void             SetHistMinimumZero(Bool_t zero=kTRUE);
   void             SetHistTopMargin(Double_t hmax=0.05) {fHistTopMargin = hmax;}
   void             SetPaintTextFormat(const char *format="g") {fPaintTextFormat = format;}
   void             SetPaperSize(EPaperSize size);
   void             SetPaperSize(Float_t xsize=20, Float_t ysize=26);
   void             SetStatColor(Color_t color=19) {fStatColor=color;}
   void             SetStatTextColor(Color_t color=1) {fStatTextColor=color;}
   void             SetStatStyle(Style_t style=1001) {fStatStyle=style;}
   void             SetStatBorderSize(Width_t size=2) {fStatBorderSize=size;}
   void             SetStatFont(Style_t font=62) {fStatFont=font;}
   void             SetStatFontSize(Float_t size=0)  {fStatFontSize=size;}
   void             SetStatFormat(const char *format="6.4g") {fStatFormat = format;}
   void             SetStatX(Float_t x=0)    {fStatX=x;}
   void             SetStatY(Float_t y=0)    {fStatY=y;}
   void             SetStatW(Float_t w=0.19) {fStatW=w;}
   void             SetStatH(Float_t h=0.1)  {fStatH=h;}
   void             SetStripDecimals(Bool_t strip=kTRUE);
   void             SetTimeOffset(Double_t toffset);
   void             SetTitleAlign(Int_t a=13) {fTitleAlign=a;}
   void             SetTitleFillColor(Color_t color=1)   {fTitleColor=color;}
   void             SetTitleTextColor(Color_t color=1)   {fTitleTextColor=color;}
   void             SetTitleStyle(Style_t style=1001)  {fTitleStyle=style;}
   void             SetTitleFontSize(Float_t size=0)   {fTitleFontSize=size;}
   void             SetTitleBorderSize(Width_t size=2) {fTitleBorderSize=size;}
   void             SetTitleXOffset(Float_t offset=1)  {SetTitleOffset(offset,"X");}
   void             SetTitleXSize(Float_t size=0.02)   {SetTitleSize(size,"X");}
   void             SetTitleYOffset(Float_t offset=1)  {SetTitleOffset(offset,"Y");}
   void             SetTitleYSize(Float_t size=0.02)   {SetTitleSize(size,"Y");}
   void             SetTitleX(Float_t x=0)     {fTitleX=x;}
   void             SetTitleY(Float_t y=0.985) {fTitleY=y;}
   void             SetTitleW(Float_t w=0)     {fTitleW=w;}
   void             SetTitleH(Float_t h=0)     {fTitleH=h;}
   void             ToggleEventStatus() { fShowEventStatus = fShowEventStatus ? 0 : 1; }
   void             ToggleEditor() { fShowEditor = fShowEditor ? 0 : 1; }
   void             ToggleToolBar() { fShowToolBar = fShowToolBar ? 0 : 1; }
   void             SetIsReading(Bool_t reading=kTRUE);
   void             SetPalette(Int_t ncolors=kBird, Int_t *colors=0, Float_t alpha=1.);
   void             SavePrimitive(std::ostream &out, Option_t * = "");
   void             SaveSource(const char *filename, Option_t *option=0);
```


<!-- TStyle.md ends here -->
