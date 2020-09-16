<!-- TString.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 20:33:51 2016 (+0800)
;; Last-Updated: 三 9月 16 10:28:57 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TString+

Cannot be stored in a TCollection... use TObjString instead.

The underlying string is stored as a char* that can be accessed via TString::Data().  
TString provides Short String Optimization (SSO) so that short strings (<15 on 64-bit and <11 on 32-bit) are contained in the TString internal data structure without the need for mallocing the required space.

## class

```cpp
   enum EStripType   { kLeading = 0x1, kTrailing = 0x2, kBoth = 0x3 };
   enum ECaseCompare { kExact, kIgnoreCase };
   static const Ssiz_t kNPOS = ::kNPOS;

   TString();                           // Null string
   explicit TString(Ssiz_t ic);         // Suggested capacity
   TString(const TString &s);           // Copy constructor
   TString(TString &&s);                // Move constructor
   TString(const char *s);              // Copy to embedded null
   TString(const char *s, Ssiz_t n);    // Copy past any embedded nulls
   TString(const std::string &s);
   TString(char c);
   TString(char c, Ssiz_t s);
   TString(const std::string_view &sub);
   TString(const TSubString &sub);

   virtual ~TString();

   // ROOT I/O interface
   virtual void     FillBuffer(char *&buffer) const;
   virtual void     ReadBuffer(char *&buffer);
   virtual Int_t    Sizeof() const;

   static TString  *ReadString(TBuffer &b, const TClass *clReq);
   static void      WriteString(TBuffer &b, const TString *a);

   friend TBuffer &operator<<(TBuffer &b, const TString *obj);

   // C I/O interface
   Bool_t   Gets(FILE *fp, Bool_t chop=kTRUE);
   void     Puts(FILE *fp);

   // Type conversion
   operator const char*() const { return GetPointer(); }
   operator std::string_view() const { return std::string_view(GetPointer(),Length()); }

   // Assignment
   TString    &operator=(char s);                // Replace string
   TString    &operator=(const char *s);
   TString    &operator=(const TString &s);
   TString    &operator=(const std::string &s);
   TString    &operator=(const std::string_view &s);
   TString    &operator=(const TSubString &s);
   TString    &operator+=(const char *s);        // Append string
   TString    &operator+=(const TString &s);
   TString    &operator+=(char c);
   TString    &operator+=(Short_t i);
   TString    &operator+=(UShort_t i);
   TString    &operator+=(Int_t i);
   TString    &operator+=(UInt_t i);
   TString    &operator+=(Long_t i);
   TString    &operator+=(ULong_t i);
   TString    &operator+=(Float_t f);
   TString    &operator+=(Double_t f);
   TString    &operator+=(Long64_t i);
   TString    &operator+=(ULong64_t i);

   // Indexing operators
   char         &operator[](Ssiz_t i);         // Indexing with bounds checking
   char         &operator()(Ssiz_t i);         // Indexing with optional bounds checking
   char          operator[](Ssiz_t i) const;
   char          operator()(Ssiz_t i) const;
   TSubString    operator()(Ssiz_t start, Ssiz_t len) const;   // Sub-string operator
   TSubString    operator()(const TRegexp &re) const;          // Match the RE
   TSubString    operator()(const TRegexp &re, Ssiz_t start) const;
   TSubString    operator()(TPRegexp &re) const;               // Match the Perl compatible Regular Expression
   TSubString    operator()(TPRegexp &re, Ssiz_t start) const;
   TSubString    SubString(const char *pat, Ssiz_t start = 0,
                           ECaseCompare cmp = kExact) const;

   // Non-static member functions
   TString     &Append(const char *cs);
   TString     &Append(const char *cs, Ssiz_t n);
   TString     &Append(const TString &s);
   TString     &Append(const TString &s, Ssiz_t n);
   TString     &Append(char c, Ssiz_t rep = 1);   // Append c rep times
   Int_t        Atoi() const;
   Long64_t     Atoll() const;
   Double_t     Atof() const;
   Bool_t       BeginsWith(const char *s,      ECaseCompare cmp = kExact) const;
   Bool_t       BeginsWith(const TString &pat, ECaseCompare cmp = kExact) const;
   Ssiz_t       Capacity() const { return (IsLong() ? GetLongCap() : kMinCap) - 1; }
   Ssiz_t       Capacity(Ssiz_t n);
   TString     &Chop();
   void         Clear();
   int          CompareTo(const char *cs,    ECaseCompare cmp = kExact) const;
   int          CompareTo(const TString &st, ECaseCompare cmp = kExact) const;
   Bool_t       Contains(const char *pat,    ECaseCompare cmp = kExact) const;
   Bool_t       Contains(const TString &pat, ECaseCompare cmp = kExact) const;
   Bool_t       Contains(const TRegexp &pat) const;
   Bool_t       Contains(TPRegexp &pat) const;
   Int_t        CountChar(Int_t c) const;
   TString      Copy() const;
   const char  *Data() const { return GetPointer(); }
   Bool_t       EndsWith(const char *pat, ECaseCompare cmp = kExact) const;
   Bool_t       EqualTo(const char *cs,    ECaseCompare cmp = kExact) const;
   Bool_t       EqualTo(const TString &st, ECaseCompare cmp = kExact) const;
   Ssiz_t       First(char c) const;
   Ssiz_t       First(const char *cs) const;
   void         Form(const char *fmt, ...)
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 2, 3)))   /* 1 is the this pointer */
#endif
   ;
   UInt_t       Hash(ECaseCompare cmp = kExact) const;
   Ssiz_t       Index(const char *pat, Ssiz_t i = 0,
                      ECaseCompare cmp = kExact) const;
   Ssiz_t       Index(const TString &s, Ssiz_t i = 0,
                      ECaseCompare cmp = kExact) const;
   Ssiz_t       Index(const char *pat, Ssiz_t patlen, Ssiz_t i,
                      ECaseCompare cmp) const;
   Ssiz_t       Index(const TString &s, Ssiz_t patlen, Ssiz_t i,
                      ECaseCompare cmp) const;
   Ssiz_t       Index(const TRegexp &pat, Ssiz_t i = 0) const;
   Ssiz_t       Index(const TRegexp &pat, Ssiz_t *ext, Ssiz_t i = 0) const;
   Ssiz_t       Index(TPRegexp &pat, Ssiz_t i = 0) const;
   Ssiz_t       Index(TPRegexp &pat, Ssiz_t *ext, Ssiz_t i = 0) const;
   TString     &Insert(Ssiz_t pos, const char *s);
   TString     &Insert(Ssiz_t pos, const char *s, Ssiz_t extent);
   TString     &Insert(Ssiz_t pos, const TString &s);
   TString     &Insert(Ssiz_t pos, const TString &s, Ssiz_t extent);
   Bool_t       IsAscii() const;
   Bool_t       IsAlpha() const;
   Bool_t       IsAlnum() const;
   Bool_t       IsDigit() const;
   Bool_t       IsFloat() const;
   Bool_t       IsHex() const;
   Bool_t       IsBin() const;
   Bool_t       IsOct() const;
   Bool_t       IsDec() const;
   Bool_t       IsInBaseN(Int_t base) const;
   Bool_t       IsNull() const         { return Length() == 0; }
   Bool_t       IsWhitespace() const   { return (Length() == CountChar(' ')); }
   Ssiz_t       Last(char c) const;
   Ssiz_t       Length() const         { return IsLong() ? GetLongSize() : GetShortSize(); }
   Bool_t       MaybeRegexp() const;
   Bool_t       MaybeWildcard() const;
   TString      MD5() const;
   TString     &Prepend(const char *cs);     // Prepend a character string
   TString     &Prepend(const char *cs, Ssiz_t n);
   TString     &Prepend(const TString &s);
   TString     &Prepend(const TString &s, Ssiz_t n);
   TString     &Prepend(char c, Ssiz_t rep = 1);  // Prepend c rep times
   std::istream     &ReadFile(std::istream &str);      // Read to EOF or null character
   std::istream     &ReadLine(std::istream &str,
                         Bool_t skipWhite = kTRUE);   // Read to EOF or newline
   std::istream     &ReadString(std::istream &str);             // Read to EOF or null character
   std::istream     &ReadToDelim(std::istream &str, char delim = '\n'); // Read to EOF or delimitor
   std::istream     &ReadToken(std::istream &str);                // Read separated by white space
   TString     &Remove(Ssiz_t pos);                     // Remove pos to end of string
   TString     &Remove(Ssiz_t pos, Ssiz_t n);           // Remove n chars starting at pos
   TString     &Remove(EStripType s, char c);           // Like Strip() but changing string directly
   TString     &Replace(Ssiz_t pos, Ssiz_t n, const char *s);
   TString     &Replace(Ssiz_t pos, Ssiz_t n, const char *s, Ssiz_t ns);
   TString     &Replace(Ssiz_t pos, Ssiz_t n, const TString &s);
   TString     &Replace(Ssiz_t pos, Ssiz_t n1, const TString &s, Ssiz_t n2);
   TString     &ReplaceAll(const TString &s1, const TString &s2); // Find&Replace all s1 with s2 if any
   TString     &ReplaceAll(const TString &s1, const char *s2);    // Find&Replace all s1 with s2 if any
   TString     &ReplaceAll(const    char *s1, const TString &s2); // Find&Replace all s1 with s2 if any
   TString     &ReplaceAll(const char *s1, const char *s2);       // Find&Replace all s1 with s2 if any
   TString     &ReplaceAll(const char *s1, Ssiz_t ls1, const char *s2, Ssiz_t ls2);  // Find&Replace all s1 with s2 if any
   void         Resize(Ssiz_t n);                       // Truncate or add blanks as necessary
   TSubString   Strip(EStripType s = kTrailing, char c = ' ') const;
   TString     &Swap(TString &other); // Swap the contents of this and other without reallocation
   void         ToLower();                              // Change self to lower-case
   void         ToUpper();                              // Change self to upper-case
   TObjArray   *Tokenize(const TString &delim) const;
   Bool_t       Tokenize(TString &tok, Ssiz_t &from, const char *delim = " ") const;

   // Static member functions
   static UInt_t  Hash(const void *txt, Int_t ntxt);    // Calculates hash index from any char string.
   static Ssiz_t  InitialCapacity(Ssiz_t ic = 15);      // Initial allocation capacity
   static Ssiz_t  MaxWaste(Ssiz_t mw = 15);             // Max empty space before reclaim
   static Ssiz_t  ResizeIncrement(Ssiz_t ri = 16);      // Resizing increment
   static Ssiz_t  GetInitialCapacity();
   static Ssiz_t  GetResizeIncrement();
   static Ssiz_t  GetMaxWaste();
   static TString Itoa   (    Int_t value, Int_t base);  // Converts int to string with respect to the base specified (2-36)
   static TString UItoa  (   UInt_t value, Int_t base);
   static TString LLtoa  ( Long64_t value, Int_t base);
   static TString ULLtoa (ULong64_t value, Int_t base);
   static TString BaseConvert(const TString& s_in, Int_t base_in, Int_t base_out);  // Converts string from base base_in to base base_out (supported bases 2-36)
   static TString Format(const char *fmt, ...)
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 1, 2)))
#endif
   ;
```

----

## code

```cpp
// Substring operations are provided by the TSubString class, which
// holds a reference to the original string and its data, along with
// the offset and length of the substring. To retrieve the substring
// as a TString, construct a TString from it, eg:
root [0] TString s("hello world")
root [1] TString s2( s(0,5) )
root [2] s2
(class TString)"hello"
```

## example



<!-- TString.md ends here -->
