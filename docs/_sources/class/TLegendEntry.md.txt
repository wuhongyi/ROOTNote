<!-- TLegendEntry.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 10月 31 23:32:48 2016 (+0800)
;; Last-Updated: 二 11月  1 12:35:35 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TLegendEntry

继承 TObject, TAttText, TAttLine, TAttFill, TAttMarker

Storage class for one entry of a TLegend

## class

```cpp
   TLegendEntry();
   TLegendEntry(const TObject *obj, const char *label = 0, Option_t *option="lpf" );
/// TLegendEntry normal constructor for one entry in a TLegend.
/// obj is the object this entry will represent. If obj has
/// line/fill/marker attributes, then the TLegendEntry will display
/// these attributes.
/// label is the text that will describe the entry, it is displayed using
/// TLatex, so may have a complex format.
/// option may have values
///  - L draw line associated w/ TAttLine if obj inherits from TAttLine
///  - P draw polymarker assoc. w/ TAttMarker if obj inherits from TAttMarker
///  - F draw a box with fill associated w/ TAttFill if obj inherits TAttFill
///    default is object = "LPF"

   TLegendEntry( const TLegendEntry &entry );
   virtual ~TLegendEntry();
   virtual void          Copy( TObject &obj ) const;/// copy this TLegendEntry into obj
   virtual const char   *GetLabel() const { return fLabel.Data(); }
   virtual TObject      *GetObject() const { return fObject; }
   virtual Option_t     *GetOption() const { return fOption.Data(); }
   virtual void          Print( Option_t *option = "" ) const;/// dump this TLegendEntry to std::cout
   virtual void          SaveEntry( std::ostream &out, const char *name );
/// Save this TLegendEntry as C++ statements on output stream out
///  to be used with the SaveAs .C option

   virtual void          SetLabel( const char *label = "" ) { fLabel = label; } // *MENU*
   virtual void          SetObject(TObject* obj );/// (re)set the obj pointed to by this entry
   virtual void          SetObject( const char *objectName );  // *MENU* /// (re)set the obj pointed to by this entry
   virtual void          SetOption( Option_t *option="lpf" ) { fOption = option; } // *MENU*
```

## code




## example




<!-- TLegendEntry.md ends here -->
