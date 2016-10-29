<!-- TLegend.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 六 10月 29 21:45:32 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 11
;; URL: http://wuhongyi.cn -->

# TLegend

继承 TPave , TAttText

## class

```cpp
   TLegend();
   TLegend( Double_t x1, Double_t y1, Double_t x2, Double_t y2,
            const char* header = "", Option_t* option="brNDC" );
   virtual ~TLegend();
   TLegend( const TLegend &legend );

   TLegendEntry   *AddEntry(const TObject* obj, const char* label = "", Option_t* option = "lpf" );
   TLegendEntry   *AddEntry(const char *name, const char* label = "", Option_t* option = "lpf" );
   virtual void    Clear( Option_t* option = "" ); // *MENU*
   virtual void    Copy( TObject &obj ) const;
   virtual void    DeleteEntry(); // *MENU*
   virtual void    Draw( Option_t* option = "" );
   virtual void    EditEntryAttFill();
   virtual void    EditEntryAttLine();
   virtual void    EditEntryAttMarker();
   virtual void    EditEntryAttText();
   Float_t         GetColumnSeparation() const { return fColumnSeparation; }
   TLegendEntry   *GetEntry() const;
   Float_t         GetEntrySeparation() const { return fEntrySeparation; }
   virtual const char *GetHeader() const;
   TList          *GetListOfPrimitives() const {return fPrimitives;}
   Float_t         GetMargin() const { return fMargin; }
   Int_t           GetNColumns() const { return fNColumns; }
   Int_t           GetNRows() const;
   virtual void    InsertEntry( const char* objectName = "",const char* label = "",
                             Option_t* option = "lpf" ); // *MENU*
   virtual void    Paint( Option_t* option = "" );
   virtual void    PaintPrimitives();
   virtual void    Print( Option_t* option = "" ) const;
   virtual void    RecursiveRemove(TObject *obj);
   virtual void    SavePrimitive(std::ostream &out, Option_t *option  = "");
   void            SetDefaults() { fEntrySeparation = 0.1f; fMargin = 0.25f; fNColumns = 1; fColumnSeparation = 0.0f; }
   void            SetColumnSeparation( Float_t columnSeparation )
                     { fColumnSeparation = columnSeparation; } // *MENU*
   virtual void    SetEntryLabel( const char* label ); // *MENU*
   virtual void    SetEntryOption( Option_t* option ); // *MENU*
   void            SetEntrySeparation( Float_t entryseparation )
                     { fEntrySeparation = entryseparation; } // *MENU*
   virtual void    SetHeader( const char *header = "" );  // *MENU*
   void            SetMargin( Float_t margin ) { fMargin = margin; } // *MENU*
   void            SetNColumns( Int_t nColumns ); // *MENU*
```



## code


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
