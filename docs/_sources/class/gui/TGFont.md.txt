<!-- TGFont.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:30:31 2016 (+0800)
;; Last-Updated: 三 9月 16 10:58:30 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGFont*

TGFont and TGFontPool                                                
                                                                     
Encapsulate fonts used in the GUI system.                            
TGFontPool provides a pool of fonts.
TGTextLayout is used to keep track of string  measurement            
information when  using the text layout facilities.                  
It can be displayed with respect to any origin.


TGTextLayout 继承 TObject , friend TGFont

TGFont 继承 TNamed, TRefCnt ,friend TGFontPool, TGTextLayout;

TGFontPool 继承 TGObject

## class

```cpp
// Flags passed to TGFont::MeasureChars and TGFont::ComputeTextLayout

enum ETextLayoutFlags {
   kTextWholeWords = BIT(0),
   kTextAtLeastOne = BIT(1),
   kTextPartialOK  = BIT(2),
   kTextIgnoreTabs = BIT(3),
   kTextIgnoreNewlines = BIT(4)
};

enum EFontWeight {
   kFontWeightNormal = 0,
   kFontWeightMedium = 0,
   kFontWeightBold = 1,
   kFontWeightLight = 2,
   kFontWeightDemibold = 3,
   kFontWeightBlack = 4,
   kFontWeightUnknown = -1
};

enum EFontSlant {
   kFontSlantRoman = 0,
   kFontSlantItalic = 1,
   kFontSlantOblique = 2,
   kFontSlantUnknown = -1
};


struct FontMetrics_t {
   Int_t   fAscent;          // from baseline to top of font
   Int_t   fDescent;         // from baseline to bottom of font
   Int_t   fLinespace;       // the sum of the ascent and descent
   Int_t   fMaxWidth;        // width of widest character in font
   Bool_t  fFixed;           // true if monospace, false otherwise
};


struct FontAttributes_t {

   const char *fFamily; // Font family. The most important field.
   Int_t fPointsize;    // Pointsize of font, 0 for default size, or negative number meaning pixel size.
   Int_t fWeight;       // Weight flag; see below for def'n.
   Int_t fSlant;        // Slant flag; see below for def'n.
   Int_t fUnderline;    // Non-zero for underline font.
   Int_t fOverstrike;   // Non-zero for overstrike font.

   FontAttributes_t():  // default constructor
      fFamily    (0),
      fPointsize (0),
      fWeight    (kFontWeightNormal),
      fSlant     (kFontSlantRoman),
      fUnderline (0),
      fOverstrike(0) { }

   FontAttributes_t(const FontAttributes_t& f): // copy constructor
      fFamily    (f.fFamily),
      fPointsize (f.fPointsize),
      fWeight    (f.fWeight),
      fSlant     (f.fSlant),
      fUnderline (f.fUnderline),
      fOverstrike(f.fOverstrike) { }

   FontAttributes_t& operator=(const FontAttributes_t& f) // assignment operator
   {
      if (this != &f) {
         fFamily     = f.fFamily;
         fPointsize  = f.fPointsize;
         fWeight     = f.fWeight;
         fSlant      = f.fSlant;
         fUnderline  = f.fUnderline;
         fOverstrike = f.fOverstrike;
      }
      return *this;
   }

};
```


**TGTextLayout**

```cpp
   TGTextLayout(): fFont(NULL), fString(""), fWidth(0), fNumChunks(0), fChunks(NULL) {}
   virtual ~TGTextLayout();/// destructor

   void   DrawText(Drawable_t dst, GContext_t gc, Int_t x, Int_t y,
                   Int_t firstChar, Int_t lastChar) const;
/// Use the information in the TGTextLayout object to display a multi-line,
/// justified string of text.
/// This procedure is useful for simple widgets that need to display
/// single-font, multi-line text and want TGFont to handle the details.
/// dst       -- Window or pixmap in which to draw.
/// gc        -- Graphics context to use for drawing text.
/// x, y      -- Upper-left hand corner of rectangle in which to draw
///              (pixels).
/// firstChar -- The index of the first character to draw from the given
///              text item. 0 specfies the beginning.
/// lastChar  -- The index just after the last character to draw from the
///              given text item. A number < 0 means to draw all characters.

   void   UnderlineChar(Drawable_t dst, GContext_t gc,
                        Int_t x, Int_t y, Int_t underline) const;
/// Use the information in the TGTextLayout object to display an underline
/// below an individual character. This procedure does not draw the text,
/// just the underline.
/// This procedure is useful for simple widgets that need to display
/// single-font, multi-line text with an individual character underlined
/// and want TGFont to handle the details. To display larger amounts of
/// underlined text, construct and use an underlined font.
/// dst       -- Window or pixmap in which to draw.
/// gc        -- Graphics context to use for drawing text.
/// x, y      -- Upper-left hand corner of rectangle in which to draw
///              (pixels).
/// underline -- Index of the single character to underline, or -1 for
///              no underline.

   Int_t  PointToChar(Int_t x, Int_t y) const;
/// Use the information in the TGTextLayout token to determine the character
/// closest to the given point. The point must be specified with respect to
/// the upper-left hand corner of the text layout, which is considered to be
/// located at (0, 0).
/// Any point whose y-value is less that 0 will be considered closest to the
/// first character in the text layout; any point whose y-value is greater
/// than the height of the text layout will be considered closest to the last
/// character in the text layout.
/// Any point whose x-value is less than 0 will be considered closest to the
/// first character on that line; any point whose x-value is greater than the
/// width of the text layout will be considered closest to the last character
/// on that line.
/// The return value is the index of the character that was closest to the
/// point. Given a text layout with no characters, the value 0 will always
/// be returned, referring to a hypothetical zero-width placeholder character.

   Int_t  CharBbox(Int_t index, Int_t *x, Int_t *y, Int_t *w, Int_t *h) const;
/// Use the information in the TGTextLayout token to return the bounding box
/// for the character specified by index.
/// The width of the bounding box is the advance width of the character, and
/// does not include and left- or right-bearing. Any character that extends
/// partially outside of the text layout is considered to be truncated at the
/// edge. Any character which is located completely outside of the text
/// layout is considered to be zero-width and pegged against the edge.
/// The height of the bounding box is the line height for this font,
/// extending from the top of the ascent to the bottom of the descent.
/// Information about the actual height of the individual letter is not
/// available.
/// A text layout that contains no characters is considered to contain a
/// single zero-width placeholder character.
/// The return value is 0 if the index did not specify a character in the
/// text layout, or non-zero otherwise. In that case, *bbox is filled with
/// the bounding box of the character.
/// layout -- Layout information, from a previous call to ComputeTextLayout().
/// index  -- The index of the character whose bbox is desired.
/// x, y   -- Filled with the upper-left hand corner, in pixels, of the
///           bounding box for the character specified by index, if non-NULL.
/// w, h   -- Filled with the width and height of the bounding box for the
///           character specified by index, if non-NULL.

   Int_t  DistanceToText(Int_t x, Int_t y) const;
/// Computes the distance in pixels from the given point to the given
/// text layout. Non-displaying space characters that occur at the end of
/// individual lines in the text layout are ignored for hit detection
/// purposes.
/// The return value is 0 if the point (x, y) is inside the text layout.
/// If the point isn't inside the text layout then the return value is the
/// distance in pixels from the point to the text item.
/// x, y -- Coordinates of point to check, with respect to the upper-left
///         corner of the text layout (in pixels).

   Int_t  IntersectText(Int_t x, Int_t y, Int_t w, Int_t h) const;
/// Determines whether a text layout lies entirely inside, entirely outside,
/// or overlaps a given rectangle. Non-displaying space characters that occur
/// at the end of individual lines in the text layout are ignored for
/// intersection calculations.
/// The return value is -1 if the text layout is entirely outside of the
/// rectangle, 0 if it overlaps, and 1 if it is entirely inside of the
/// rectangle.
/// x, y -- Upper-left hand corner, in pixels, of rectangular area to compare
///         with text layout. Coordinates are with respect to the upper-left
///         hand corner of the text layout itself.
/// w, h -- The width and height of the above rectangular area, in pixels.

   void   ToPostscript(TString *dst) const;
/// Outputs the contents of a text layout in Postscript format. The set of
/// lines in the text layout will be rendered by the user supplied Postscript
/// function. The function should be of the form:
///     justify x y string  function  --
/// Justify is -1, 0, or 1, depending on whether the following string should
/// be left, center, or right justified, x and y is the location for the
/// origin of the string, string is the sequence of characters to be printed,
/// and function is the name of the caller-provided function; the function
/// should leave nothing on the stack.
/// The meaning of the origin of the string (x and y) depends on the
/// justification. For left justification, x is where the left edge of the
/// string should appear. For center justification, x is where the center of
/// the string should appear. And for right justification, x is where the
/// right edge of the string should appear. This behavior is necessary
/// because, for example, right justified text on the screen is justified
/// with screen metrics. The same string needs to be justified with printer
/// metrics on the printer to appear in the correct place with respect to
/// other similarly justified strings. In all circumstances, y is the
/// location of the baseline for the string.
/// result is modified to hold the Postscript code that will render the text
/// layout.
```


**TGFont**

```cpp
   virtual ~TGFont();/// Delete font.

   FontH_t      GetFontHandle() const { return fFontH; }
   FontStruct_t GetFontStruct() const { return fFontStruct; }
   FontStruct_t operator()() const;
   void         GetFontMetrics(FontMetrics_t *m) const;/// Get font metrics.
   FontAttributes_t GetFontAttributes() const { return fFA; }

   Int_t  PostscriptFontName(TString *dst) const;
/// Return the name of the corresponding Postscript font for this TGFont.
/// The return value is the pointsize of the TGFont. The name of the
/// Postscript font is appended to ds.
/// If the font does not exist on the printer, the print job will fail at
/// print time. Given a "reasonable" Postscript printer, the following
/// TGFont font families should print correctly:
///     Avant Garde, Arial, Bookman, Courier, Courier New, Geneva,
///     Helvetica, Monaco, New Century Schoolbook, New York,
///     Palatino, Symbol, Times, Times New Roman, Zapf Chancery,
///     and Zapf Dingbats.
/// Any other TGFont font families may not print correctly because the
/// computed Postscript font name may be incorrect.
/// dst -- Pointer to an initialized TString object to which the name of the
///        Postscript font that corresponds to the font will be appended.

   Int_t  TextWidth(const char *string, Int_t numChars = -1) const;
/// A wrapper function for the more complicated interface of MeasureChars.
/// Computes how much space the given simple string needs.
/// The return value is the width (in pixels) of the given string.
/// string   -- String whose width will be computed.
/// numChars -- Number of characters to consider from string, or < 0 for
///             strlen().

   Int_t  XTextWidth(const char *string, Int_t numChars = -1) const;/// Return text widht in pixels
   Int_t  TextHeight() const { return fFM.fLinespace; }
   void   UnderlineChars(Drawable_t dst, GContext_t gc,
                        const char *string, Int_t x, Int_t y,
                        Int_t firstChar, Int_t lastChar) const;
/// This procedure draws an underline for a given range of characters in a
/// given string. It doesn't draw the characters (which are assumed to have
/// been displayed previously); it just draws the underline. This procedure
/// would mainly be used to quickly underline a few characters without having
/// to construct an underlined font. To produce properly underlined text, the
/// appropriate underlined font should be constructed and used.
/// dst       -- Window or pixmap in which to draw.
/// gc        -- Graphics context for actually drawing line.
/// string    -- String containing characters to be underlined or overstruck.
/// x, y      -- Coordinates at which first character of string is drawn.
/// firstChar -- Index of first character.
/// lastChar  -- Index of one after the last character.

   TGTextLayout *ComputeTextLayout(const char *string, Int_t numChars,
                                  Int_t wrapLength, Int_t justify, Int_t flags,
                                  UInt_t *width, UInt_t *height) const;
/// Computes the amount of screen space needed to display a multi-line,
/// justified string of text. Records all the measurements that were done
/// to determine to size and positioning of the individual lines of text;
/// this information can be used by the TGTextLayout::DrawText() procedure
/// to display the text quickly (without remeasuring it).
/// This procedure is useful for simple widgets that want to display
/// single-font, multi-line text and want TGFont to handle the details.
/// The return value is a TGTextLayout token that holds the measurement
/// information for the given string. The token is only valid for the given
/// string. If the string is freed, the token is no longer valid and must
/// also be deleted.
/// The dimensions of the screen area needed to display the text are stored
/// in *width and *height.
/// string     -- String whose dimensions are to be computed.
/// numChars   -- Number of characters to consider from string, or < 0 for
///               strlen().
/// wrapLength -- Longest permissible line length, in pixels. <= 0 means no
///               automatic wrapping: just let lines get as long as needed.
/// justify    -- How to justify lines.
/// flags      -- Flag bits OR-ed together. kTextIgnoreTabs means that tab
///               characters should not be expanded. kTextIgnoreNewlines
///               means that newline characters should not cause a line break.
/// width      -- Filled with width of string.
/// height     -- Filled with height of string.

   Int_t  MeasureChars(const char *source, Int_t numChars, Int_t maxLength,
                      Int_t flags, Int_t *length) const;
/// Determine the number of characters from the string that will fit in the
/// given horizontal span. The measurement is done under the assumption that
/// DrawChars() will be used to actually display the characters.
/// The return value is the number of characters from source that fit into
/// the span that extends from 0 to maxLength. *length is filled with the
/// x-coordinate of the right edge of the last character that did fit.
/// source    -- Characters to be displayed. Need not be '\0' terminated.
/// numChars  -- Maximum number of characters to consider from source string.
/// maxLength -- If > 0, maxLength specifies the longest permissible line
///              length; don't consider any character that would cross this
///              x-position. If <= 0, then line length is unbounded and the
///              flags argument is ignored.
/// flags     -- Various flag bits OR-ed together:
///              TEXT_PARTIAL_OK means include the last char which only
///              partially fit on this line.
///              TEXT_WHOLE_WORDS means stop on a word boundary, if possible.
///              TEXT_AT_LEAST_ONE means return at least one character even
///              if no characters fit.
/// *length   -- Filled with x-location just after the terminating character.

   void   DrawCharsExp(Drawable_t dst, GContext_t gc, const char *source,
                      Int_t numChars, Int_t x, Int_t y) const;
/// Draw a string of characters on the screen. DrawCharsExp() expands
/// control characters that occur in the string to \X or \xXX sequences.
/// DrawChars() just draws the strings.
/// dst      -- Window or pixmap in which to draw.
/// gc       -- Graphics context for drawing characters.
/// source   -- Characters to be displayed. Need not be'\0' terminated.
///             For DrawChars(), all meta-characters (tabs, control
///             characters, and newlines) should be stripped out of the
///             string that is passed to this function. If they are not
///             stripped out, they will be displayed as regular printing
///             characters.
/// numChars -- Number of characters in string.
/// x, y     -- Coordinates at which to place origin of string when drawing.

   void   DrawChars(Drawable_t dst, GContext_t gc, const char *source,
                   Int_t numChars, Int_t x, Int_t y) const;
/// Perform a quick sanity check to ensure we won't overflow the X
/// coordinate space.

   void  Print(Option_t *option="") const;/// Print font info.
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
/// Save the used font as a C++ statement(s) on output stream out.
```


**TGFontPool**

```cpp
   TGFontPool(TGClient *client);/// Create a font pool.
   virtual ~TGFontPool();/// Cleanup font pool.

   TGFont  *GetFont(const char *font, Bool_t fixedDefault = kTRUE);
/// Get the specified font.
/// The font can be one of the following forms:
///        XLFD (see X documentation)
///        "Family [size [style] [style ...]]"
/// Returns 0 if error or no font can be found.
/// If fixedDefault is false the "fixed" font will not be substituted
/// as fallback when the asked for font does not exist.

   TGFont  *GetFont(const TGFont *font);
/// Use font, i.e. increases ref count of specified font. Returns 0
/// if font is not found.

   TGFont  *GetFont(FontStruct_t font);/// Use font, i.e. increases ref count of specified font.
   TGFont  *GetFont(const char *family, Int_t ptsize, Int_t weight, Int_t slant);
/// Returns font specified bay family, pixel/point size, weight and slant
///  negative value of ptsize means size in pixels
///  positive value of ptsize means size in points

   void     FreeFont(const TGFont *font);/// Free font. If ref count is 0 delete font.
   TGFont  *FindFont(FontStruct_t font) const;
/// Find font based on its font struct. Returns 0 if font is not found.

   TGFont  *FindFontByHandle(FontH_t font) const;
/// Find font based on its font handle. Returns 0 if font is not found.

   char   **GetAttributeInfo(const FontAttributes_t *fa);
/// Return information about the font attributes as an array of strings.
/// An array of FONT_NUMFIELDS strings is returned holding the value of the
/// font attributes in the following order:
/// family size weight slant underline overstrike

   void     FreeAttributeInfo(char **info);/// Free attributes info.
   char   **GetFontFamilies();
/// Return information about the font families that are available on the
/// current display.
/// An array of strings is returned holding a list of all the available font
/// families. The array is terminated with a NULL pointer.

   void     FreeFontFamilies(char **f);/// Delete an array of families allocated GetFontFamilies() method
   Bool_t   ParseFontName(const char *string, FontAttributes_t *fa);
/// Converts a string into a set of font attributes that can be used to
/// construct a font.
/// The string can be one of the following forms:
///        XLFD (see X documentation)
///        "Family [size [style] [style ...]]"
/// The return value is kFALSE if the object was syntactically
/// invalid. Otherwise, fills the font attribute buffer with the values
/// parsed from the string and returns kTRUE. The structure must already be
/// properly initialized.

   const char *NameOfFont(TGFont *font);/// Given a font, return a textual string identifying it.

   void     Print(Option_t *option="") const;/// List all fonts in the pool.
```

## code

```cpp
TGFont *font = fpool->GetFont("helvetica", -9, kFontWeightNormal, kFontSlantRoman);
font->Print();
```

## example




<!-- TGFont.md ends here -->
