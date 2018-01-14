<!-- TH2Poly.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月 14 13:53:25 2018 (+0800)
;; Last-Updated: 日 1月 14 14:13:56 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TH2Poly

继承 public TH2

2D Histogram with Polygonal Bins

```cpp
`TH2Poly` is a 2D Histogram class (TH2) allowing to define polygonal
bins of arbitrary shape.

Each bin in the `TH2Poly` histogram is a `TH2PolyBin` object.
`TH2PolyBin` is a very simple class containing the vertices (stored
as `TGraph`s or `TMultiGraph`s ) and contents of the polygonal
bin as well as several related functions.

Essentially, a `TH2Poly` is a TList of `TH2PolyBin` objects
with methods to manipulate them.

Bins are defined using one of the `AddBin()` methods. The bin definition
should be done before filling.

The histogram can be filled with `Fill(Double_t x, Double_t y, Double_t w)
`. `w` is the weight.
If no weight is specified, it is assumed to be 1.

Not all histogram's area need to be binned. Filling an area without bins,
will falls into the overflows. Adding a bin is not retroactive; it doesn't
affect previous fillings. A `Fill()` call, that
was previously ignored due to the lack of a bin at the specified location, is
not reconsidered when that location is binned later.

If there are two overlapping bins, the first one in the list will be incremented
by `Fill()`.

The histogram may automatically extends its limits if a bin outside the
histogram limits is added. This is done when the default constructor (with no
arguments) is used. It generates a histogram with no limits along the X and Y
axis. Adding bins to it will extend it up to a proper size.

`TH2Poly` implements a partitioning algorithm to speed up bins' filling.
The partitioning algorithm divides the histogram into regions called cells.
The bins that each cell intersects are recorded in an array of `TList`s.
When a coordinate in the histogram is to be filled; the method (quickly) finds
which cell the coordinate belongs.  It then only loops over the bins
intersecting that cell to find the bin the input coordinate corresponds to.
The partitioning of the histogram is updated continuously as each bin is added.
The default number of cells on each axis is 25. This number could be set to
another value in the constructor or adjusted later by calling the
`ChangePartition(Int_t, Int_t)` method. The partitioning algorithm is
considerably faster than the brute force algorithm (i.e. checking if each bin
contains the input coordinates), especially if the histogram is to be filled
many times.


## Partitioning Algorithm
The partitioning algorithm forms an essential part of the `TH2Poly`
class. It is implemented to speed up the filling of bins.

With the brute force approach, the filling is done in the following way:  An
iterator loops over all bins in the `TH2Poly` and invokes the
method `IsInside()` for each of them.
This method checks if the input location is in that bin. If the filling
coordinate is inside, the bin is filled. Looping over all the bin is
very slow.

The alternative is to divide the histogram into virtual rectangular regions
called "cells". Each cell stores the pointers of the bins intersecting it.
When a coordinate is to be filled, the method finds which cell the coordinate
falls into. Since the cells are rectangular, this can be done very quickly.
It then only loops over the bins associated with that cell.

The addition of bins to the appropriate cells is done when the bin is added
to the histogram. To do this, `AddBin()` calls the
`AddBinToPartition()` method.
This method adds the input bin to the partitioning matrix.

The number of partition cells per axis can be specified in the constructor.
If it is not specified, the default value of 25 along each axis will be
assigned. This value was chosen because it is small enough to avoid slowing
down AddBin(), while being large enough to enhance Fill() by a considerable
amount. Regardless of how it is initialized at construction time, it can be
changed later with the `ChangePartition()` method.
`ChangePartition()` deletes the
old partition matrix and generates a new one with the specified number of cells
on each axis.

The optimum number of partition cells per axis changes with the number of
times `Fill()` will be called.  Although partitioning greatly speeds up
filling, it also adds a constant time delay into the code. When `Fill()`
is to be called many times, it is more efficient to divide the histogram into
a large number cells. However, if the histogram is to be filled only a few
times, it is better to divide into a small number of cells.
```

## class

```cpp
// class TH2Poly : public TH2

public:
   TH2Poly();
   TH2Poly(const char *name,const char *title, Double_t xlow, Double_t xup, Double_t ylow, Double_t yup);
   TH2Poly(const char *name,const char *title, Int_t nX, Double_t xlow, Double_t xup,  Int_t nY, Double_t ylow, Double_t yup);
   virtual ~TH2Poly();

/// Adds a new bin to the histogram. It can be any object having the method
/// IsInside(). It returns the bin number in the histogram. It returns 0 if
/// it failed to add. To allow the histogram limits to expand when a bin
/// outside the limits is added, call SetFloat() before adding the bin.
   Int_t        AddBin(TObject *poly);

/// Adds a new bin to the histogram. The number of vertices and their (x,y)
/// coordinates are required as input. It returns the bin number in the
/// histogram.
   Int_t        AddBin(Int_t n, const Double_t *x, const Double_t *y);

/// Add a new bin to the histogram. The bin shape is a rectangle.
/// It returns the bin number of the bin in the histogram.
   Int_t        AddBin(Double_t x1, Double_t y1, Double_t x2, Double_t  y2);

/// Performs the operation: this = this + c1*h1.
   virtual Bool_t Add(const TH1 *h1, Double_t c1);

/// Replace contents of this histogram by the addition of h1 and h2.
   virtual Bool_t Add(const TH1 *h1, const TH1 *h2, Double_t c1=1, Double_t c2=1);

/// Performs the operation: this = this + c1*f1.
   virtual Bool_t Add(TF1 *h1, Double_t c1=1, Option_t *option="");

/// Clears the contents of all bins in the histogram.
   void         ClearBinContents();                 // Clears the content of all bins

/// Make a complete copy of the underlying object.  If 'newname' is set,
/// the copy's name will be set to that name.
   TObject     *Clone(const char* newname = "") const;

/// Changes the number of partition cells in the histogram.
/// Deletes the old partition and constructs a new one.
   void         ChangePartition(Int_t n, Int_t m);  // Sets the number of partition cells to another value

/// Increment the bin containing (x,y) by 1.
/// Uses the partitioning algorithm.
   Int_t        Fill(Double_t x,Double_t y);

/// Increment the bin containing (x,y) by w.
/// Uses the partitioning algorithm.
   Int_t        Fill(Double_t x,Double_t y, Double_t w);

/// Increment the bin named "name" by w.
   Int_t        Fill(const char* name, Double_t w);

/// Fills a 2-D histogram with an array of values and weights.
///
/// \param [in] ntimes:  number of entries in arrays x and w
///                      (array size must be ntimes*stride)
/// \param [in] x:       array of x values to be histogrammed
/// \param [in] y:       array of y values to be histogrammed
/// \param [in] w:       array of weights
/// \param [in] stride:  step size through arrays x, y and w
   void         FillN(Int_t ntimes, const Double_t* x, const Double_t* y, const Double_t* w, Int_t stride = 1);
   Int_t        Fill(Double_t){return -1;}                              //MayNotUse
   Int_t        Fill(Double_t , const char *, Double_t){return -1;}     //MayNotUse
   Int_t        Fill(const char *, Double_t , Double_t ){return -1;}    //MayNotUse
   Int_t        Fill(const char *, const char *, Double_t ){return -1;} //MayNotUse
   void         FillN(Int_t, const Double_t*, const Double_t*, Int_t){return;}  //MayNotUse

/// Returns the bin number of the bin at the given coordinate. -1 to -9 are
/// the overflow and underflow bins.  overflow bin -5 is the unbinned areas in
/// the histogram (also called "the sea"). The third parameter can be left
/// blank.
/// The overflow/underflow bins are:
///~~~ {.cpp}
/// -1 | -2 | -3
/// -------------
/// -4 | -5 | -6
/// -------------
/// -7 | -8 | -9
///~~~
/// where -5 means is the "sea" bin (i.e. unbinned areas)
   Int_t        FindBin(Double_t x, Double_t y, Double_t z = 0);
   TList       *GetBins(){return fBins;}                                // Returns the TList of all bins in the histogram

/// Returns the content of the input bin
/// For the overflow/underflow/sea bins:
///~~~ {.cpp}
/// -1 | -2 | -3
/// ---+----+----
/// -4 | -5 | -6
/// ---+----+----
/// -7 | -8 | -9
///~~~
/// where -5 is the "sea" bin (i.e. unbinned areas)
   Double_t     GetBinContent(Int_t bin) const;
   Double_t     GetBinContent(Int_t, Int_t) const {return 0;}           //MayNotUse
   Double_t     GetBinContent(Int_t, Int_t, Int_t) const {return 0;}    //MayNotUse
   Bool_t       GetBinContentChanged() const{return fBinContentChanged;}

/// Returns the value of error associated to bin number bin.
/// If the sum of squares of weights has been defined (via Sumw2),
/// this function returns the sqrt(sum of w2).
/// otherwise it returns the sqrt(contents) for this bin.
   Double_t     GetBinError(Int_t bin) const;
   Double_t     GetBinError(Int_t , Int_t) const {return 0;}            //MayNotUse
   Double_t     GetBinError(Int_t , Int_t , Int_t) const {return 0;}    //MayNotUse
   const char  *GetBinName(Int_t bin) const;/// Returns the bin name.
   const char  *GetBinTitle(Int_t bin) const;/// Returns the bin title.
   Bool_t       GetFloat(){return fFloat;}

/// Returns the maximum value of the histogram.
   Double_t     GetMaximum() const;

/// Returns the maximum value of the histogram that is less than maxval.
   Double_t     GetMaximum(Double_t maxval) const;

/// Returns the minimum value of the histogram.
   Double_t     GetMinimum() const;

/// Returns the minimum value of the histogram that is greater than minval.
   Double_t     GetMinimum(Double_t minval) const;
   Bool_t       GetNewBinAdded() const{return fNewBinAdded;}
   Int_t        GetNumberOfBins() const{return fNcells;}

/// Bins the histogram using a honeycomb structure
   void         Honeycomb(Double_t xstart, Double_t ystart, Double_t a, Int_t k, Int_t s);   // Bins the histogram using a honeycomb structure

/// Returns the integral of bin contents.
/// By default the integral is computed as the sum of bin contents.
/// If option "width" or "area" is specified, the integral is the sum of
/// the bin contents multiplied by the area of the bin.
   Double_t     Integral(Option_t* option = "") const;
   Double_t     Integral(Int_t, Int_t, const Option_t*) const{return 0;}                             //MayNotUse
   Double_t     Integral(Int_t, Int_t, Int_t, Int_t, const Option_t*) const{return 0;}               //MayNotUse
   Double_t     Integral(Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, const Option_t*) const{return 0;} //MayNotUse
   Long64_t     Merge(TCollection *);/// TH2Poly cannot be merged.
   void         Reset(Option_t *option);/// Reset this histogram: contents, errors, etc.

/// Save primitive as a C++ statement(s) on output stream out
   void         SavePrimitive(std::ostream& out, Option_t* option = "");

/// Multiply this histogram by a constant c1.
   virtual void Scale(Double_t c1 = 1, Option_t* option = "");

/// Sets the contents of the input bin to the input content
/// Negative values between -1 and -9 are for the overflows and the sea
   void         SetBinContent(Int_t bin, Double_t content);
   void         SetBinContent(Int_t, Int_t, Double_t){return;}           //MayNotUse
   void         SetBinContent(Int_t, Int_t, Int_t, Double_t){return;}    //MayNotUse
   void         SetBinContentChanged(Bool_t flag){fBinContentChanged = flag;}

/// When set to kTRUE, allows the histogram to expand if a bin outside the
/// limits is added.
   void         SetFloat(Bool_t flag = true);
   void         SetNewBinAdded(Bool_t flag){fNewBinAdded = flag;}
```


```cpp
// class TH2PolyBin: public TObject

public:
   TH2PolyBin();
   TH2PolyBin(TObject *poly, Int_t bin_number);
   virtual ~TH2PolyBin();

   void      ClearContent(){fContent = 0;}
   void      Fill(Double_t w) {fContent = fContent+w; SetChanged(true);}
   Double_t  GetArea();/// Returns the area of the bin.
   Double_t  GetContent() const{return fContent;}
   Bool_t    GetChanged() const{return fChanged;}
   Int_t     GetBinNumber() const {return fNumber;}
   TObject  *GetPolygon() const {return fPoly;}

/// Returns the maximum value for the x coordinates of the bin.
   Double_t  GetXMax();

/// Returns the minimum value for the x coordinates of the bin.
   Double_t  GetXMin();

/// Returns the maximum value for the y coordinates of the bin.
   Double_t  GetYMax();

/// Returns the minimum value for the y coordinates of the bin.
   Double_t  GetYMin();

/// Return "true" if the point (x,y) is inside the bin.
   Bool_t    IsInside(Double_t x, Double_t y) const;
   void      SetChanged(Bool_t flag){fChanged = flag;}
   void      SetContent(Double_t content){fContent = content; SetChanged(true);}
```

## code


```cpp
{
// The following very simple macro shows how to build and fill a `TH2Poly`:
    TH2Poly *h2p = new TH2Poly();

    Double_t x1[] = {0, 5, 6};
    Double_t y1[] = {0, 0, 5};
    Double_t x2[] = {0, -1, -1, 0};
    Double_t y2[] = {0, 0, -1, 3};
    Double_t x3[] = {4, 3, 0, 1, 2.4};
    Double_t y3[] = {4, 3.7, 1, 3.7, 2.5};

    h2p->AddBin(3, x1, y1);
    h2p->AddBin(4, x2, y2);
    h2p->AddBin(5, x3, y3);

    h2p->Fill(0.1, 0.01, 3);
    h2p->Fill(-0.5, -0.5, 7);
    h2p->Fill(-0.7, -0.5, 1);
    h2p->Fill(1, 3, 1.5);
}
```


## example



<!-- TH2Poly.md ends here -->
