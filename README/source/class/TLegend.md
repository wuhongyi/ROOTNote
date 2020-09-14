<!-- TLegend.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 二 11月  1 12:59:22 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 12
;; URL: http://wuhongyi.cn -->

# TLegend

继承 TPave , TAttText

This class displays a legend box (TPaveText) containing several legend entries.

Each legend entry is made of a reference to a ROOT object, a text label and an
option specifying which graphical attributes (marker/line/fill) should be
displayed.

The legend contains a histogram, a function and a graph. The histogram is put in
the legend using its reference pointer whereas the graph and the function are added
using their names. Note that, because TGraph constructors do not have the
TGraph name as parameter, the graph name should be specified using the
SetName method.

TLegend inherits from TAttText therefore changing any text attributes (text alignment,
font, color...) on a legend will changed the text attributes on each line.


Note that the TPad class has a method to build automatically a legend
for all objects in the pad. It is called TPad::BuildLegend().

Each item in the legend is added using the AddEntry method. This
method defines the object to be added (by reference or name), the label
associated to this object and an option which a combination of:  
  - L: draw line associated with TAttLine if obj inherits from TAttLine
  - P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
  - F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
  - E: draw vertical error bar


## class

```cpp
   TLegend();
   TLegend( Double_t x1, Double_t y1, Double_t x2, Double_t y2,
            const char* header = "", Option_t* option="brNDC" );
/// Normal constructor.
/// A TLegend is a Pave with several TLegendEntry(s).
/// x1,y1,x2,y2 are the coordinates of the Legend in the current pad
/// (in normalised coordinates by default)
/// "header" is the title that will be displayed at the top of the legend
/// it is treated like a regular entry and supports TLatex. The default
/// is no header (header = 0).
/// The options are the same as for TPave Default = "brNDC"

   virtual ~TLegend();
   TLegend( const TLegend &legend );

   TLegendEntry   *AddEntry(const TObject* obj, const char* label = "", Option_t* option = "lpf" );
/// Add a new entry to this legend. "obj" is the object to be represented.
/// "label" is the text you wish to associate with obj in the legend.
/// If "label" is null or empty, the title of the object will be used.
/// Options are:
///  - L: draw line associated with TAttLine if obj inherits from TAttLine
///  - P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
///  - F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
///  - E: draw vertical error bar if option "L" is also specified

   TLegendEntry   *AddEntry(const char *name, const char* label = "", Option_t* option = "lpf" );
/// Add a new entry to this legend. "name" is the name of an object in the pad to
/// be represented label is the text you wish to associate with obj in the legend
/// if label is null or empty, the title of the object will be used.
/// Options are:
///  - L: draw line associated with TAttLine if obj inherits from TAttLine
///  - P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
///  - F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
///  - E: draw vertical error bar if option "L" is also specified

   virtual void    Clear( Option_t* option = "" ); // *MENU* /// Clear all entries in this legend, including the header.
   virtual void    Copy( TObject &obj ) const; /// Copy this legend into "obj".
   virtual void    DeleteEntry(); // *MENU* /// Delete entry at the mouse position.
   virtual void    Draw( Option_t* option = "" );/// Draw this legend with its current attributes.
   virtual void    EditEntryAttFill();/// Edit the fill attributes for the entry pointed by the mouse.
   virtual void    EditEntryAttLine();/// Edit the line attributes for the entry pointed by the mouse.
   virtual void    EditEntryAttMarker();/// Edit the marker attributes for the entry pointed by the mouse.
   virtual void    EditEntryAttText();/// Edit the text attributes for the entry pointed by the mouse.
   Float_t         GetColumnSeparation() const { return fColumnSeparation; }
   TLegendEntry   *GetEntry() const;
/// Get entry pointed to by the mouse.
/// This method is mostly a tool for other methods inside this class.

   Float_t         GetEntrySeparation() const { return fEntrySeparation; }
   virtual const char *GetHeader() const;
/// Returns the header, which is the title that appears at the top
/// of the legend.

   TList          *GetListOfPrimitives() const {return fPrimitives;}
   Float_t         GetMargin() const { return fMargin; }
   Int_t           GetNColumns() const { return fNColumns; }
   Int_t           GetNRows() const;/// Get the number of rows.
   virtual void    InsertEntry( const char* objectName = "",const char* label = "",
	                           Option_t* option = "lpf" ); // *MENU*
/// Add a new entry before the entry at the mouse position.

   virtual void    Paint( Option_t* option = "" );/// Paint this legend with its current attributes.
   virtual void    PaintPrimitives();/// Paint the entries (list of primitives) for this legend.
   virtual void    Print( Option_t* option = "" ) const;/// Paint this legend with its current attributes.
   
/// Dump this TLegend and its contents.

   virtual void    RecursiveRemove(TObject *obj);
/// Reset the legend entries pointing to "obj".

   virtual void    SavePrimitive(std::ostream &out, Option_t *option  = "");
/// Save this legend as C++ statements on output stream out
/// to be used with the SaveAs .C option.

   void            SetDefaults() { fEntrySeparation = 0.1f; fMargin = 0.25f; fNColumns = 1; fColumnSeparation = 0.0f; }
   void            SetColumnSeparation( Float_t columnSeparation )
                     { fColumnSeparation = columnSeparation; } // *MENU*
   virtual void    SetEntryLabel( const char* label ); // *MENU*
/// Edit the label of the entry pointed to by the mouse.

   virtual void    SetEntryOption( Option_t* option ); // *MENU*
/// Edit the option of the entry pointed to by the mouse.

   void            SetEntrySeparation( Float_t entryseparation )
                     { fEntrySeparation = entryseparation; } // *MENU*
   virtual void    SetHeader( const char *header = "" );  // *MENU*
/// Sets the header, which is the "title" that appears at the top of the legend.

   void            SetMargin( Float_t margin ) { fMargin = margin; } // *MENU*
   void            SetNColumns( Int_t nColumns ); // *MENU*
/// Set the number of columns for the legend. The header, if set, is given
/// its own row. After that, every nColumns entries are inserted into the
/// same row. For example, if one calls legend.SetNColumns(2), and there
/// is no header, then the first two TObjects added to the legend will be
/// in the first row, the next two will appear in the second row, and so on.
```



## code

```cpp
// In particular it can be interesting to change the text alignement that way. In
// order to have a base-line vertical alignment instead of a centered one simply do:

   leg->SetTextAlign(13);

// or

   leg->SetTextAlign(11);
```

```cpp
The default value of some TLegend attributes can be changed using
gStyle. The default settings are:

   SetLegendBorderSize(1);
   SetLegendFillColor(0);
   SetLegendFont(42);
   SetLegendTextSize(0.);

// The global attributes change the default values for the next created legends.

// Text attributes can be also changed individually on each legend entry:

   TLegendEntry *le = leg->AddEntry(h1,"Histogram filled with random numbers","f");
   le->SetTextColor(kBlue);;
```


```cpp
// When an object is added by name, a scan is performed on the list of objects
// contained in the current pad (gPad) and also in the possible TMultiGraph and
// THStack present in the pad. If a matching name is found, the corresponding
// object is added in the legend using its pointer.

   TCanvas *c1 = new TCanvas("c1","c1",600,500);
   gStyle->SetOptStat(0);

   TH1F *h1 = new TH1F("h1","TLegend Example",200,-10,10);
   h1->FillRandom("gaus",30000);
   h1->SetFillColor(kGreen);
   h1->SetFillStyle(3003);
   h1->Draw();

   TF1 *f1=new TF1("f1","1000*TMath::Abs(sin(x)/x)",-10,10);
   f1->SetLineColor(kBlue);
   f1->SetLineWidth(4);
   f1->Draw("same");

   const Int_t n = 20;
   Double_t x[n], y[n], ex[n], ey[n];
   for (Int_t i=0;i<n;i++) {
      x[i]  = i*0.1;
      y[i]  = 1000*sin(x[i]+0.2);
      x[i]  = 17.8*x[i]-8.9;
      ex[i] = 1.0;
      ey[i] = 10.*i;
   }
   TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetName("gr");
   gr->SetLineColor(kRed);
   gr->SetLineWidth(2);
   gr->SetMarkerStyle(21);
   gr->SetMarkerSize(1.3);
   gr->SetMarkerColor(7);
   gr->Draw("P");

   leg = new TLegend(0.1,0.7,0.48,0.9);
   leg->SetHeader("The Legend Title");
   leg->AddEntry(h1,"Histogram filled with random numbers","f");
   leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
   leg->AddEntry("gr","Graph with error bars","lep");
   leg->Draw();

   return c1;
```



```cpp
It is possible to draw the legend entries over several columns using
the method SetNColumns() like in the following example.

   TCanvas *c3 = new TCanvas("c2","c2",500,300);

   TLegend* leg = new TLegend(0.2, 0.2, .8, .8);
   TH1* h = new TH1F("", "", 1, 0, 1);

   leg-> SetNColumns(2);

   leg->AddEntry(h, "Column 1 line 1", "l");
   leg->AddEntry(h, "Column 2 line 1", "l");
   leg->AddEntry(h, "Column 1 line 2", "l");
   leg->AddEntry(h, "Column 2 line 2", "l");

   leg->Draw();
   return c3;
```


```cpp
TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
legend->SetHeader("The Legend Title");
legend->SetTextSize(0.05);
legend->SetBorderSize(0);
legend->AddEntry(h1,"All nations","");
legend->AddEntry(h2,"French only","");
legend->Draw();
```

## example



<!-- TLegend.md ends here -->
