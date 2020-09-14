<!-- TColor.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 5月  1 14:44:03 2018 (+0800)
;; Last-Updated: 二 5月  1 15:44:58 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TColor

TColor : public TNamed

## class

```cpp
namespace {
   static Bool_t& TColor__GrayScaleMode() {
      static Bool_t grayScaleMode;
      return grayScaleMode;
   }
   static TArrayI& TColor__Palette() {
      static TArrayI globalPalette(0);
      return globalPalette;
   }
   static TArrayD& TColor__PalettesList() {
      static TArrayD globalPalettesList(0);
      return globalPalettesList;
   }
}

static Int_t gHighestColorIndex = 0; ///< Highest color index defined

#define fgGrayscaleMode TColor__GrayScaleMode()
#define fgPalette TColor__Palette()
#define fgPalettesList TColor__PalettesList()

using std::floor;
```


```cpp
//class TColor : public TNamed

   TColor();/// Default constructor.
   TColor(Int_t color, Float_t r, Float_t g, Float_t b, const char *name="", Float_t a = 1);
/// Normal color constructor. Initialize a color structure.
/// Compute the RGB and HLS color components.

   TColor(Float_t r, Float_t g, Float_t b, Float_t a = 1);
/// Fast TColor constructor. It creates a color with an index just above the
/// current highest one. It does not name the color.
/// This is useful to create palettes.

   TColor(const TColor &color);/// Color copy constructor.
   virtual ~TColor();/// Color destructor.
   const char   *AsHexString() const;
/// Return color as hexadecimal string. This string can be directly passed
/// to, for example, TGClient::GetColorByName(). String will be reused so
/// copy immediately if needed.

   void          Copy(TObject &color) const;/// Copy this color to obj.
   static void   CreateColorWheel();
   static void   CreateColorsGray();
/// Create the Gray scale colors in the Color Wheel

   static void   CreateColorsCircle(Int_t offset, const char *name, UChar_t *rgb);
/// Create the "circle" colors in the color wheel.

   static void   CreateColorsRectangle(Int_t offset, const char *name, UChar_t *rgb);
/// Create the "rectangular" colors in the color wheel.

   static Int_t  CreateGradientColorTable(UInt_t Number, Double_t* Stops,
                    Double_t* Red, Double_t* Green, Double_t* Blue, UInt_t NColors, Float_t alpha=1.);
/// Static function creating a color table with several connected linear gradients.
///   - Number: The number of end point colors that will form the gradients.
///             Must be at least 2.
///   - Stops: Where in the whole table the end point colors should lie.
///            Each entry must be on [0, 1], each entry must be greater than
///            the previous entry.
///   - Red, Green, Blue: The end point color values.
///                       Each entry must be on [0, 1]
///   - NColors: Total number of colors in the table. Must be at least 1.
/// Returns a positive value on success and -1 on error.
/// The table is constructed by tracing lines between the given points in
/// RGB space.  Each color value may have a value between 0 and 1.  The
/// difference between consecutive "Stops" values gives the fraction of
/// space in the whole table that should be used for the interval between
/// the corresponding color values.
/// Normally the first element of Stops should be 0 and the last should be 1.
/// If this is not true, fewer than NColors will be used in proportion with
/// the total interval between the first and last elements of Stops.
/// This definition is similar to the povray-definition of gradient
/// color tables.
/// For instance:
/// ~~~ {.cpp}
/// UInt_t Number = 3;
/// Double_t Red[3]   = { 0.0, 1.0, 1.0 };
/// Double_t Green[3] = { 0.0, 0.0, 1.0 };
/// Double_t Blue[3]  = { 1.0, 0.0, 1.0 };
/// Double_t Stops[3] = { 0.0, 0.4, 1.0 };
/// ~~~
/// This defines a table in which there are three color end points:
/// RGB = {0, 0, 1}, {1, 0, 0}, and {1, 1, 1} = blue, red, white
/// The first 40% of the table is used to go linearly from blue to red.
/// The remaining 60% of the table is used to go linearly from red to white.
/// If you define a very short interval such that less than one color fits
/// in it, no colors at all will be allocated.  If this occurs for all
/// intervals, ROOT will revert to the default palette.
/// Original code by Andreas Zoglauer (zog@mpe.mpg.de)

   static Int_t  GetColorPalette(Int_t i);
/// Static function returning the color number i in current palette.

   static Int_t  GetNumberOfColors();
/// Static function returning number of colors in the color palette.

   virtual void  GetRGB(Float_t &r, Float_t &g, Float_t &b) const
                    { r=GetRed(); g=GetGreen(); b=GetBlue(); }
   virtual void  GetHLS(Float_t &h, Float_t &l, Float_t &s) const
                    { h=GetHue(); l=GetLight(); s=GetSaturation(); }
   Int_t         GetNumber() const { return fNumber; }
   ULong_t       GetPixel() const;
/// Return pixel value corresponding to this color. This pixel value can
/// be used in the GUI classes. This call does not work in batch mode since
/// it needs to communicate with the graphics system.

   Float_t       GetRed() const { return IsGrayscale() ? GetGrayscale() : fRed; }
   Float_t       GetGreen() const { return IsGrayscale() ? GetGrayscale() : fGreen; }
   Float_t       GetBlue() const { return IsGrayscale() ? GetGrayscale() : fBlue; }
   Float_t       GetHue() const { return fHue; }
   Float_t       GetLight() const { return fLight; }
   Float_t       GetSaturation() const { return IsGrayscale() ? 0 : fSaturation; }
   Float_t       GetAlpha() const { return fAlpha; }
   virtual Float_t GetGrayscale() const { /*ITU*/ return 0.299f*fRed + 0.587f*fGreen + 0.114f*fBlue; }
   virtual void  ls(Option_t *option="") const;/// List this color with its attributes.
   virtual void  Print(Option_t *option="") const;/// Dump this color with its attributes.
   virtual void  SetAlpha(Float_t a) { fAlpha = a; }
   virtual void  SetRGB(Float_t r, Float_t g, Float_t b);
/// Initialize this color and its associated colors.

   static void    InitializeColors();
/// Initialize colors used by the TCanvas based graphics (via TColor objects).
/// This method should be called before the ApplicationImp is created (which
/// initializes the GUI colors).

   static void    HLS2RGB(Float_t h, Float_t l, Float_t s, Float_t &r, Float_t &g, Float_t &b);
/// Static method to compute RGB from HLS. The l and s are between [0,1]
/// and h is between [0,360]. The returned r,g,b triplet is between [0,1].

   static void    HLS2RGB(Int_t h, Int_t l, Int_t s, Int_t &r, Int_t &g, Int_t &b);
/// Static method to compute RGB from HLS. The h,l,s are between [0,255].
/// The returned r,g,b triplet is between [0,255].

   static void    HLStoRGB(Float_t h, Float_t l, Float_t s, Float_t &r, Float_t &g, Float_t &b)
                     { TColor::HLS2RGB(h, l, s, r, g, b); } // backward compatible
   static void    HSV2RGB(Float_t h, Float_t s, Float_t v, Float_t &r, Float_t &g, Float_t &b);
/// Static method to compute RGB from HSV:
///  -  The hue value runs from 0 to 360.
///  -  The saturation is the degree of strength or purity and is from 0 to 1.
///     Purity is how much white is added to the color, so S=1 makes the purest
///     color (no white).
///  -  Brightness value also ranges from 0 to 1, where 0 is the black.
/// The returned r,g,b triplet is between [0,1].

   static void    RGB2HLS(Float_t r, Float_t g, Float_t b, Float_t &h, Float_t &l, Float_t &s);
/// Static method to compute HLS from RGB. The r,g,b triplet is between
/// [0,1], hue is between [0,360], light and satur are [0,1].

   static void    RGB2HLS(Int_t r, Int_t g, Int_t b, Int_t &h, Int_t &l, Int_t &s);
/// Static method to compute HLS from RGB. The r,g,b triplet is between
/// [0,255], hue, light and satur are between [0,255].

   static void    RGBtoHLS(Float_t r, Float_t g, Float_t b, Float_t &h, Float_t &l, Float_t &s)
                     { TColor::RGB2HLS(r, g, b, h, l, s); } // backward compatible
   static void    RGB2HSV(Float_t r, Float_t g, Float_t b, Float_t &h, Float_t &s, Float_t &v);
/// Static method to compute HSV from RGB.
///  -  The input values:
///    -  r,g,b triplet is between [0,1].
///  -  The returned values:
///    -  The hue value runs from 0 to 360.
///    -  The saturation is the degree of strength or purity and is from 0 to 1.
///       Purity is how much white is added to the color, so S=1 makes the purest
///       color (no white).
///    -  Brightness value also ranges from 0 to 1, where 0 is the black.

   static Int_t   GetColor(const char *hexcolor);
/// Static method returning color number for color specified by
/// hex color string of form: "#rrggbb", where rr, gg and bb are in
/// hex between [0,FF], e.g. "#c0c0c0".
/// If specified color does not exist it will be created with as
/// name "#rrggbb" with rr, gg and bb in hex between [0,FF].

   static Int_t   GetColor(Float_t r, Float_t g, Float_t b);
/// Static method returning color number for color specified by
/// r, g and b. The r,g,b should be in the range [0,1].
/// If specified color does not exist it will be created
/// with as name "#rrggbb" with rr, gg and bb in hex between
/// [0,FF].

   static Int_t   GetColor(Int_t r, Int_t g, Int_t b);
/// Static method returning color number for color specified by
/// r, g and b. The r,g,b should be in the range [0,255].
/// If the specified color does not exist it will be created
/// with as name "#rrggbb" with rr, gg and bb in hex between
/// [0,FF].

   static Int_t   GetColor(ULong_t pixel);
/// Static method returning color number for color specified by
/// system dependent pixel value. Pixel values can be obtained, e.g.,
/// from the GUI color picker.

   static Int_t   GetColorBright(Int_t color);
/// Static function: Returns the bright color number corresponding to n
/// If the TColor object does not exist, it is created.
/// The convention is that the bright color nb = n+150

   static Int_t   GetColorDark(Int_t color);
/// Static function: Returns the dark color number corresponding to n
/// If the TColor object does not exist, it is created.
/// The convention is that the dark color nd = n+100

   static Int_t   GetColorTransparent(Int_t color, Float_t a);
/// Static function: Returns the transparent color number corresponding to n.
/// The transparency level is given by the alpha value a.

   static Int_t   GetFreeColorIndex();
/// Static function: Returns a free color index which can be used to define
/// a user custom color.
/// ~~~ {.cpp}
///   Int_t ci = TColor::GetFreeColorIndex();
///   TColor *color = new TColor(ci, 0.1, 0.2, 0.3);
/// ~~~

   static ULong_t Number2Pixel(Int_t ci);
/// Static method that given a color index number, returns the corresponding
/// pixel value. This pixel value can be used in the GUI classes. This call
/// does not work in batch mode since it needs to communicate with the
/// graphics system.

   static ULong_t RGB2Pixel(Int_t r, Int_t g, Int_t b);
/// Convert r,g,b to graphics system dependent pixel value.
/// The r,g,b triplet must be [0,255].

   static ULong_t RGB2Pixel(Float_t r, Float_t g, Float_t b);
/// Convert r,g,b to graphics system dependent pixel value.
/// The r,g,b triplet must be [0,1].

   static void    Pixel2RGB(ULong_t pixel, Int_t &r, Int_t &g, Int_t &b);
/// Convert machine dependent pixel value (obtained via RGB2Pixel or
/// via Number2Pixel() or via TColor::GetPixel()) to r,g,b triplet.
/// The r,g,b triplet will be [0,255].

   static void    Pixel2RGB(ULong_t pixel, Float_t &r, Float_t &g, Float_t &b);
/// Convert machine dependent pixel value (obtained via RGB2Pixel or
/// via Number2Pixel() or via TColor::GetPixel()) to r,g,b triplet.
/// The r,g,b triplet will be [0,1].

   static const char *PixelAsHexString(ULong_t pixel);
/// Convert machine dependent pixel value (obtained via RGB2Pixel or
/// via Number2Pixel() or via TColor::GetPixel()) to a hexadecimal string.
/// This string can be directly passed to, for example,
/// TGClient::GetColorByName(). String will be reused so copy immediately
/// if needed.

   static void    SaveColor(std::ostream &out, Int_t ci);
/// Save a color with index > 228 as a C++ statement(s) on output stream out.

   static Bool_t  IsGrayscale();
/// Return whether all colors return grayscale values.

   static void    SetGrayscale(Bool_t set = kTRUE);
/// Set whether all colors should return grayscale values.
   
   static void    SetPalette(Int_t ncolors, Int_t *colors,Float_t alpha=1.);
/// Static function.
/// The color palette is used by the histogram classes
///  (see TH1::Draw options).
/// For example TH1::Draw("col") draws a 2-D histogram with cells
/// represented by a box filled with a color CI function of the cell content.
/// if the cell content is N, the color CI used will be the color number
/// in colors[N],etc. If the maximum cell content is > ncolors, all
/// cell contents are scaled to ncolors.
///
/// `if ncolors <= 0` a default palette (see below) of 50 colors is
/// defined. The colors defined in this palette are OK for coloring pads, labels.
///
/// ~~~ {.cpp}
/// index 0->9   : grey colors from light to dark grey
/// index 10->19 : "brown" colors
/// index 20->29 : "blueish" colors
/// index 30->39 : "redish" colors
/// index 40->49 : basic colors
/// ~~~
///
/// `if ncolors == 1 && colors == 0`, a Rainbow Color map is created
/// with 50 colors. It is kept for backward compatibility. Better palettes like
/// kBird are recommended.
///
/// High quality predefined palettes with 255 colors are available when `colors == 0`.
/// The following value of `ncolors` give access to:
///
/// ~~~ {.cpp}
/// if ncolors = 51 and colors=0, a Deep Sea palette is used.
/// if ncolors = 52 and colors=0, a Grey Scale palette is used.
/// if ncolors = 53 and colors=0, a Dark Body Radiator palette is used.
/// if ncolors = 54 and colors=0, a Two-Color Hue palette is used.(dark blue through neutral gray to bright yellow)
/// if ncolors = 55 and colors=0, a Rain Bow palette is used.
/// if ncolors = 56 and colors=0, an Inverted Dark Body Radiator palette is used.
/// if ncolors = 57 and colors=0, a monotonically increasing L value palette is used.
/// if ncolors = 58 and colors=0, a Cubehelix palette is used
///                                 (Cf. Dave Green's "cubehelix" colour scheme at http://www.mrao.cam.ac.uk/~dag/CUBEHELIX/)
/// if ncolors = 59 and colors=0, a Green Red Violet palette is used.
/// if ncolors = 60 and colors=0, a Blue Red Yellow palette is used.
/// if ncolors = 61 and colors=0, an Ocean palette is used.
/// if ncolors = 62 and colors=0, a Color Printable On Grey palette is used.
/// if ncolors = 63 and colors=0, an Alpine palette is used.
/// if ncolors = 64 and colors=0, an Aquamarine palette is used.
/// if ncolors = 65 and colors=0, an Army palette is used.
/// if ncolors = 66 and colors=0, an Atlantic palette is used.
/// if ncolors = 67 and colors=0, an Aurora palette is used.
/// if ncolors = 68 and colors=0, an Avocado palette is used.
/// if ncolors = 69 and colors=0, a Beach palette is used.
/// if ncolors = 70 and colors=0, a Black Body palette is used.
/// if ncolors = 71 and colors=0, a Blue Green Yellow palette is used.
/// if ncolors = 72 and colors=0, a Brown Cyan palette is used.
/// if ncolors = 73 and colors=0, a CMYK palette is used.
/// if ncolors = 74 and colors=0, a Candy palette is used.
/// if ncolors = 75 and colors=0, a Cherry palette is used.
/// if ncolors = 76 and colors=0, a Coffee palette is used.
/// if ncolors = 77 and colors=0, a Dark Rain Bow palette is used.
/// if ncolors = 78 and colors=0, a Dark Terrain palette is used.
/// if ncolors = 79 and colors=0, a Fall palette is used.
/// if ncolors = 80 and colors=0, a Fruit Punch palette is used.
/// if ncolors = 81 and colors=0, a Fuchsia palette is used.
/// if ncolors = 82 and colors=0, a Grey Yellow palette is used.
/// if ncolors = 83 and colors=0, a Green Brown Terrain palette is used.
/// if ncolors = 84 and colors=0, a Green Pink palette is used.
/// if ncolors = 85 and colors=0, an Island palette is used.
/// if ncolors = 86 and colors=0, a Lake palette is used.
/// if ncolors = 87 and colors=0, a Light Temperature palette is used.
/// if ncolors = 88 and colors=0, a Light Terrain palette is used.
/// if ncolors = 89 and colors=0, a Mint palette is used.
/// if ncolors = 90 and colors=0, a Neon palette is used.
/// if ncolors = 91 and colors=0, a Pastel palette is used.
/// if ncolors = 92 and colors=0, a Pearl palette is used.
/// if ncolors = 93 and colors=0, a Pigeon palette is used.
/// if ncolors = 94 and colors=0, a Plum palette is used.
/// if ncolors = 95 and colors=0, a Red Blue palette is used.
/// if ncolors = 96 and colors=0, a Rose palette is used.
/// if ncolors = 97 and colors=0, a Rust palette is used.
/// if ncolors = 98 and colors=0, a Sandy Terrain palette is used.
/// if ncolors = 99 and colors=0, a Sienna palette is used.
/// if ncolors = 100 and colors=0, a Solar palette is used.
/// if ncolors = 101 and colors=0, a South West palette is used.
/// if ncolors = 102 and colors=0, a Starry Night palette is used.
/// if ncolors = 103 and colors=0, a Sunset palette is used.
/// if ncolors = 104 and colors=0, a Temperature Map palette is used.
/// if ncolors = 105 and colors=0, a Thermometer palette is used.
/// if ncolors = 106 and colors=0, a Valentine palette is used.
/// if ncolors = 107 and colors=0, a Visible Spectrum palette is used.
/// if ncolors = 108 and colors=0, a Water Melon palette is used.
/// if ncolors = 109 and colors=0, a Cool palette is used.
/// if ncolors = 110 and colors=0, a Copper palette is used.
/// if ncolors = 111 and colors=0, a Gist Earth palette is used.
/// if ncolors = 112 and colors=0, a Viridis palette is used.
/// ~~~
/// These palettes can also be accessed by names:
/// ~~~ {.cpp}
/// kDeepSea=51,          kGreyScale=52,    kDarkBodyRadiator=53,
/// kBlueYellow= 54,      kRainBow=55,      kInvertedDarkBodyRadiator=56,
/// kBird=57,             kCubehelix=58,    kGreenRedViolet=59,
/// kBlueRedYellow=60,    kOcean=61,        kColorPrintableOnGrey=62,
/// kAlpine=63,           kAquamarine=64,   kArmy=65,
/// kAtlantic=66,         kAurora=67,       kAvocado=68,
/// kBeach=69,            kBlackBody=70,    kBlueGreenYellow=71,
/// kBrownCyan=72,        kCMYK=73,         kCandy=74,
/// kCherry=75,           kCoffee=76,       kDarkRainBow=77,
/// kDarkTerrain=78,      kFall=79,         kFruitPunch=80,
/// kFuchsia=81,          kGreyYellow=82,   kGreenBrownTerrain=83,
/// kGreenPink=84,        kIsland=85,       kLake=86,
/// kLightTemperature=87, kLightTerrain=88, kMint=89,
/// kNeon=90,             kPastel=91,       kPearl=92,
/// kPigeon=93,           kPlum=94,         kRedBlue=95,
/// kRose=96,             kRust=97,         kSandyTerrain=98,
/// kSienna=99,           kSolar=100,       kSouthWest=101,
/// kStarryNight=102,     kSunset=103,      kTemperatureMap=104,
/// kThermometer=105,     kValentine=106,   kVisibleSpectrum=107,
/// kWaterMelon=108,      kCool=109,        kCopper=110,
/// kGistEarth=111        kViridis=112
/// ~~~
/// For example:
/// ~~~ {.cpp}
/// gStyle->SetPalette(kBird);
/// ~~~
/// Set the current palette as "Bird" (number 57).
///
/// The color numbers specified in the palette can be viewed by selecting
/// the item "colors" in the "VIEW" menu of the canvas toolbar.
/// The color parameters can be changed via TColor::SetRGB.
///
/// Note that when drawing a 2D histogram `h2` with the option "COL" or
/// "COLZ" or with any "CONT" options using the color map, the number of colors
/// used is defined by the number of contours `n` specified with:
/// `h2->SetContour(n)`

```



```cpp
   enum EColorPalette {kDeepSea=51,          kGreyScale=52,    kDarkBodyRadiator=53,
                       kBlueYellow= 54,      kRainBow=55,      kInvertedDarkBodyRadiator=56,
                       kBird=57,             kCubehelix=58,    kGreenRedViolet=59,
                       kBlueRedYellow=60,    kOcean=61,        kColorPrintableOnGrey=62,
                       kAlpine=63,           kAquamarine=64,   kArmy=65,
                       kAtlantic=66,         kAurora=67,       kAvocado=68,
                       kBeach=69,            kBlackBody=70,    kBlueGreenYellow=71,
                       kBrownCyan=72,        kCMYK=73,         kCandy=74,
                       kCherry=75,           kCoffee=76,       kDarkRainBow=77,
                       kDarkTerrain=78,      kFall=79,         kFruitPunch=80,
                       kFuchsia=81,          kGreyYellow=82,   kGreenBrownTerrain=83,
                       kGreenPink=84,        kIsland=85,       kLake=86,
                       kLightTemperature=87, kLightTerrain=88, kMint=89,
                       kNeon=90,             kPastel=91,       kPearl=92,
                       kPigeon=93,           kPlum=94,         kRedBlue=95,
                       kRose=96,             kRust=97,         kSandyTerrain=98,
                       kSienna=99,           kSolar=100,       kSouthWest=101,
                       kStarryNight=102,     kSunset=103,      kTemperatureMap=104,
                       kThermometer=105,     kValentine=106,   kVisibleSpectrum=107,
                       kWaterMelon=108,      kCool=109,        kCopper=110,
                       kGistEarth=111,       kViridis=112};
```


## code

```cpp
// Colors are defined by their red, green and blue components, simply called the
// RGB components. The colors are also known by the hue, light and saturation
// components also known as the HLS components. When a new color is created the
// components of both color systems are computed.

// At initialization time, a table of colors is generated. An existing color can
// be retrieved by its index:

TColor *color = gROOT->GetColor(10);
```


```cpp
// Then it can be manipulated. For example its RGB components can be modified:

color->SetRGB(0.1, 0.2, 0.3);

// A new color can be created the following way:

Int_t ci = 1756; // color index
TColor *color = new TColor(ci, 0.1, 0.2, 0.3);
```


```cpp
// The following image displays the 50 basic colors.

{
   TCanvas *c = new TCanvas("c","Fill Area colors",0,0,500,200);
   c->DrawColorTable();
   return c;
}
```

```cpp
// The wheel contains the recommended 216 colors to be used in web applications.

// The colors in the color wheel are created by `TColor::CreateColorWheel`.

// Using this color set for your text, background or graphics will give your
yapplication a consistent appearance across different platforms and browsers.

// Colors are grouped by hue, the aspect most important in human perception.
// Touching color chips have the same hue, but with different brightness and
// vividness.

// Colors of slightly different hues clash. If you intend to display
// colors of the same hue together, you should pick them from the same group.

// Each color chip is identified by a mnemonic (e.g. kYellow) and a number.
// The keywords, kRed, kBlue, kYellow, kPink, etc are defined in the header file
// Rtypes.h that is included in all ROOT other header files. It is better
// to use these keywords in user code instead of hardcoded color numbers, e.g.:

myObject.SetFillColor(kRed);
myObject.SetFillColor(kYellow-10);
myLine.SetLineColor(kMagenta+2);


{
   TColorWheel *w = new TColorWheel();
   w->Draw();
   return w->GetCanvas();
}
```



```cpp
// The dark and bright color are used to give 3-D effects when drawing various
// boxes (see TWbox, TPave, TPaveText, TPaveLabel, etc).

//   - The dark colors have an index = color_index+100
//   - The bright colors have an index = color_index+150
//   - Two static functions return the bright and dark color number
//     corresponding to a color index. If the bright or dark color does not
//     exist, they are created:

Int_t dark   = TColor::GetColorDark(color_index);
Int_t bright = TColor::GetColorBright(color_index);
```


```cpp
// One can toggle between a grayscale preview and the regular colored mode using
// `TCanvas::SetGrayscale()`. Note that in grayscale mode, access via RGB
// will return grayscale values according to ITU standards (and close to b&w
// printer gray-scales), while access via HLS returns de-saturated gray-scales. The
// image below shows the ROOT color wheel in grayscale mode.

{
   TColorWheel *w = new TColorWheel();
   w->Draw();
   w->GetCanvas()->SetGrayscale();
   w->GetCanvas()->Modified();
   w->GetCanvas()->Update();
   return w->GetCanvas();
}
```



```cpp
// It is often very useful to represent a variable with a color map. The concept
// of "color palette" allows to do that. One color palette is active at any time.
// This "current palette" is set using:

gStyle->SetPalette(...);


// This function has two parameters: the number of colors in the palette and an
// array of containing the indices of colors in the palette. The following small
// example demonstrates how to define and use the color palette:
{
   TCanvas *c1  = new TCanvas("c1","c1",0,0,600,400);
   TF2 *f1 = new TF2("f1","0.1+(1-(x-2)*(x-2))*(1-(y-2)*(y-2))",1,3,1,3);
   Int_t palette[5];
   palette[0] = 15;
   palette[1] = 20;
   palette[2] = 23;
   palette[3] = 30;
   palette[4] = 32;
   gStyle->SetPalette(5,palette);
   f1->Draw("colz");
   return c1;
   }


//  To define more a complex palette with a continuous gradient of color, one
// should use the static function `TColor::CreateGradientColorTable()`.
// The following example demonstrates how to proceed:


{
   TCanvas *c2  = new TCanvas("c2","c2",0,0,600,400);
   TF2 *f2 = new TF2("f2","0.1+(1-(x-2)*(x-2))*(1-(y-2)*(y-2))",1,3,1,3);
   const Int_t Number = 3;
   Double_t Red[Number]    = { 1.00, 0.00, 0.00};
   Double_t Green[Number]  = { 0.00, 1.00, 0.00};
   Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
   Double_t Length[Number] = { 0.00, 0.50, 1.00 };
   Int_t nb=50;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
   f2->SetContour(nb);
   f2->SetLineWidth(1);
   f2->SetLineColor(kBlack);
   f2->Draw("surf1z");
   return c2;
}


// The function `TColor::CreateGradientColorTable()` automatically
// calls `gStyle->SetPalette()`, so there is not need to add one.

// After a call to `TColor::CreateGradientColorTable()` it is sometimes
// useful to store the newly create palette for further use. In particular, it is
// recommended to do if one wants to switch between several user define palettes.
// To store a palette in an array it is enough to do:

{
   Int_t MyPalette[100];
   Double_t Red[]    = {0., 0.0, 1.0, 1.0, 1.0};
   Double_t Green[]  = {0., 0.0, 0.0, 1.0, 1.0};
   Double_t Blue[]   = {0., 1.0, 0.0, 0.0, 1.0};
   Double_t Length[] = {0., .25, .50, .75, 1.0};
   Int_t FI = TColor::CreateGradientColorTable(5, Length, Red, Green, Blue, 100);
   for (int i=0;i<100;i++) MyPalette[i] = FI+i;
}

// Later on to reuse the palette `MyPalette` it will be enough to do

gStyle->SetPalette(100, MyPalette);

// As only one palette is active, one need to use `TExec` to be able to
// display plots using different palettes on the same pad.
// The following macro illustrate this feature.
```



```cpp
// \since **6.04:**
// 62 high quality palettes are predefined with 255 colors each.
// Despite the [disadvantages of the Rainbow color map](https://root.cern.ch/rainbow-color-map),
// it was kept in the list of predefined color maps.
// These palettes can be accessed "by name" with `gStyle->SetPalette(num)`.
// `num` can be taken within the following enum:

kDeepSea=51,          kGreyScale=52,    kDarkBodyRadiator=53,
kBlueYellow= 54,      kRainBow=55,      kInvertedDarkBodyRadiator=56,
kBird=57,             kCubehelix=58,    kGreenRedViolet=59,
kBlueRedYellow=60,    kOcean=61,        kColorPrintableOnGrey=62,
kAlpine=63,           kAquamarine=64,   kArmy=65,
kAtlantic=66,         kAurora=67,       kAvocado=68,
kBeach=69,            kBlackBody=70,    kBlueGreenYellow=71,
kBrownCyan=72,        kCMYK=73,         kCandy=74,
kCherry=75,           kCoffee=76,       kDarkRainBow=77,
kDarkTerrain=78,      kFall=79,         kFruitPunch=80,
kFuchsia=81,          kGreyYellow=82,   kGreenBrownTerrain=83,
kGreenPink=84,        kIsland=85,       kLake=86,
kLightTemperature=87, kLightTerrain=88, kMint=89,
kNeon=90,             kPastel=91,       kPearl=92,
kPigeon=93,           kPlum=94,         kRedBlue=95,
kRose=96,             kRust=97,         kSandyTerrain=98,
kSienna=99,           kSolar=100,       kSouthWest=101,
kStarryNight=102,     kSunset=103,      kTemperatureMap=104,
kThermometer=105,     kValentine=106,   kVisibleSpectrum=107,
kWaterMelon=108,      kCool=109,        kCopper=110,
kGistEarth=111,       kViridis=112

{
   c  = new TCanvas("c","c",0,0,300,300);
   TF2 *f2 = new TF2("f2","0.1+(1-(x-2)*(x-2))*(1-(y-2)*(y-2))",0.999,3.002,0.999,3.002);


   f2->SetContour(99); gStyle->SetPalette(kDeepSea);
   f2->Draw("surf2Z"); f2->SetTitle("kDeepSea");

   f2->SetContour(99); gStyle->SetPalette(kGreyScale);
   f2->Draw("surf2Z"); f2->SetTitle("kGreyScale");

// ...
}
```


```cpp
// To make a graphics object transparent it is enough to set its color to a
// transparent one. The color transparency is defined via its alpha component. The
// alpha value varies from `0.` (fully transparent) to `1.` (fully
// opaque). To set the alpha value of an existing color it is enough to do:


TColor *col26 = gROOT->GetColor(26);
col26->SetAlpha(0.01);


// A new color can be created transparent the following way:


Int_t ci = 1756;
TColor *color = new TColor(ci, 0.1, 0.2, 0.3, "", 0.5); // alpha = 0.5


// An example of transparency usage with parallel coordinates can be found
// in parallelcoordtrans.C.

// To ease the creation of a transparent color the static method
// `GetColorTransparent(Int_t color, Float_t a)` is provided.
// In the following example the `trans_red` color index point to
// a red color 30% transparent. The alpha value of the color index
// `kRed` is not modified.

Int_t trans_red = GetColorTransparent(kRed, 0.3);


// This function is also used in the methods
// `SetFillColorAlpha()`, `SetLineColorAlpha()`,
// `SetMarkerColorAlpha()` and `SetTextColorAlpha()`.
// In the following example the fill color of the histogram `histo`
// is set to blue with a transparency of 35%. The color `kBlue`
// itself remains fully opaque.

histo->SetFillColorAlpha(kBlue, 0.35);

// The transparency is available on all platforms when the flag `OpenGL.CanvasPreferGL` is set to `1`
// in `$ROOTSYS/etc/system.rootrc`, or on Mac with the Cocoa backend. On the file output
// it is visible with PDF, PNG, Gif, JPEG, SVG ... but not PostScript.
```




## example





<!-- TColor.md ends here -->
