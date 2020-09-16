<!-- TGButtonGroup.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:21:17 2016 (+0800)
;; Last-Updated: 三 9月 16 10:57:04 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGButtonGroup*

TGButtonGroup, TGVButtonGroup and TGHButtonGroup  
This header defines button group frames.

The TGButtonGroup widget organizes TGButton widgets in a group.

A button group widget makes it easier to deal with groups of buttons.  
A button in a button group is associated with a unique identifier.   
The button group emits a Clicked() signal with this identifier when  
the button is clicked. Thus, a button group is an ideal solution     
when you have several similar buttons and want to connect all their  
Clicked() signals, for example, to one slot.                         

An exclusive button group switches off all toggle buttons except     
the one that was clicked. A button group is by default non-exclusive.  
All radio buttons that are inserted, will be mutually exclusive even   
if the button group is non-exclusive.                                
                                                                      
                                                                     
There are two ways of using a button group:                          
                                                                     
   The button group is a parent widget of a number of buttons,       
   i.e. the button group is the parent argument in the button        
   constructor. The buttons are assigned identifiers 1, 2, 3 etc.    
   in the order they are created or you can specify button id in     
   the button constructor. A TGButtonGroup can display a frame and   
   a title because it inherits from TGGroupFrame.                    

NOTE: there is no need to call AddFrame() since the buttons are      
automatically added with a default layout hint to their parent,      
i.e. the buttongroup. To override the default layout hints use the   
SetLayoutHints() method.                                             

```
 ButtonGroup Signals:                                                
                                                                     
   Pressed(Int_t id)  -->  is emitted when a button in the group is  
                           pressed down. The id argument is the      
                           button's identifier.                      
   Released(Int_t id) -->  is emitted when a button in the group is  
                           released. The id argument is the button's 
                           identifier.                               
   Clicked(Int_t id)  -->  is emitted when a button in the group is  
                           clicked. The id argument is the button's  
                           identifier.                               
```

The TGHButtonGroup widget organizes TGButton widgets in a group      
with one horizontal row. TGHButtonGroup is a convenience class that  
offers a thin layer on top of TGButtonGroup. It inherits from        
TGButtonGroup.                                                       
                                                                      
The TGVButtonGroup widget organizes TGButton widgets in a group      
with one vertical column. TGVButtonGroup is a convenience class that   
offers a thin layer on top of TGButtonGroup. It inherits from        
TGButtonGroup.                                                       


TGButtonGroup 继承 TGGroupFrame , friend TGButton

TGVButtonGroup 继承 TGButtonGroup

TGHButtonGroup 继承 TGButtonGroup

## class

**TGButtonGroup**

```cpp
   TGButtonGroup(const TGWindow *parent = 0,
                 const TString &title = "",
                 UInt_t options = kChildFrame | kVerticalFrame,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 Pixel_t back = GetDefaultFrameBackground());
/// Constructor. Layout 1 row or 1 column.

   TGButtonGroup(const TGWindow *parent,
                 UInt_t r, UInt_t c, Int_t s = 0, Int_t h = 0 ,
                 const TString &title = "",
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 Pixel_t back = GetDefaultFrameBackground());
/// Constructor. Layout defined by TGMatrixLayout:
///    r = number of rows
///    c = number of columns
///    s = interval between frames
///    h = layout hints

   virtual ~TGButtonGroup();/// Destructor, we do not delete the buttons.

   virtual void Pressed(Int_t id)  { Emit("Pressed(Int_t)",id); }   //*SIGNAL*
   virtual void Released(Int_t id) { Emit("Released(Int_t)",id);}   //*SIGNAL*
   virtual void Clicked(Int_t id)  { Emit("Clicked(Int_t)",id); }   //*SIGNAL*

   virtual void ButtonPressed();
/// This slot is activated when one of the buttons in the group emits the
/// Pressed() signal.

   virtual void ButtonReleased();
/// This slot is activated when one of the buttons in the group emits the
/// Released() signal.

   virtual void ButtonClicked();
/// This slot is activated when one of the buttons in the group emits the
/// Clicked() signal.

   virtual void ReleaseButtons();
/// This slot is activated when one of the buttons in the
/// exclusive group emits the Pressed() signal.

   Bool_t IsEnabled() const { return fState; }
   Bool_t IsExclusive() const { return fExclGroup; }
   Bool_t IsRadioButtonExclusive() const  { return fRadioExcl; }
   Bool_t IsBorderDrawn() const { return fDrawBorder; }
   Int_t  GetCount() const { return fMapOfButtons->GetSize(); }
   Int_t  GetId(TGButton *button) const;
/// Finds and returns the id of the button.
/// Returns -1 if the button is not a member of this group.

   virtual void SetExclusive(Bool_t flag = kTRUE);
/// Sets the button group to be exclusive if enable is kTRUE,
/// or to be non-exclusive if enable is kFALSE.
/// An exclusive button group switches off all other toggle buttons when
/// one is switched on. This is ideal for groups of radio-buttons
/// A non-exclusive group allow many buttons to be switched on at the same
/// time. The default setting is kFALSE.

   virtual void SetRadioButtonExclusive(Bool_t flag = kTRUE);
/// If enable is kTRUE, this button group will treat radio buttons as
/// mutually exclusive, and other buttons according to IsExclusive().
/// This function is called automatically whenever a TGRadioButton
/// is inserted, so you should normally never have to call it.

   virtual void SetState(Bool_t state = kTRUE);
/// Sets the state of all the buttons in the group to enable or disable.

   virtual void SetBorderDrawn(Bool_t enable = kTRUE);/// Makes border to be visible/invisible.
   virtual void SetButton(Int_t id, Bool_t down = kTRUE);
/// Sets the button with id to be on/down, and if this is an
/// exclusive group, all other button in the group to be off/up.

   virtual void SetTitle(TGString *title);/// Set or change title.
   virtual void SetTitle(const char *title);/// Set or change title.

   virtual Int_t     Insert(TGButton *button, int id = -1);
/// Inserts a button with the identifier id into the button group.
/// Returns the button identifier.
/// It is not necessary to manually insert buttons that have this button
/// group as their parent widget. An exception is when you want custom
/// identifiers instead of the default 1, 2, 3 etc.
/// The button is assigned the identifier id or an automatically
/// generated identifier.  It works as follows: If id > 0, this
/// identifier is assigned.  If id == -1 (default), the identifier is
/// equal to the number of buttons in the group+1.  If id is any other
/// negative integer, for instance -2, a unique identifier (negative
/// integer <= -2) is generated.
/// Inserting several buttons with id = -1 assigns the identifiers 1,
/// 2, 3, etc.

   virtual void      Remove(TGButton *button);/// Removes a button from the button group.
   virtual TGButton *Find(Int_t id) const;
/// Finds and returns a pointer to the button with the specified
/// identifier id. Returns null if the button was not found.

   virtual TGButton *GetButton(Int_t id) const { return Find(id); }
   virtual void      Show();/// Show group of buttons.
   virtual void      Hide();/// Hide group of buttons.
   virtual void      DrawBorder();
/// Draw border of around the group frame.
/// if frame is kRaisedFrame  - a frame border is of "wall style",
/// otherwise of "groove style".

   virtual void      SetLayoutHints(TGLayoutHints *l, TGButton *button = 0);
/// Set layout hints for the specified button or if button=0 for all
/// buttons.

   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a button group widget as a C++ statement(s) on output stream out.
```


**TGVButtonGroup**

```cpp
   TGVButtonGroup(const TGWindow *parent,
                  const TString &title = "",
                  GContext_t norm = GetDefaultGC()(),
                  FontStruct_t font = GetDefaultFontStruct(),
                  Pixel_t back = GetDefaultFrameBackground()) :
      TGButtonGroup(parent, title, kChildFrame | kVerticalFrame,
                    norm, font, back) { }

   virtual ~TGVButtonGroup() { }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a button group widget as a C++ statement(s) on output stream out.
```


**TGHButtonGroup**

```cpp
   TGHButtonGroup(const TGWindow *parent,
                  const TString &title = "",
                  GContext_t norm = GetDefaultGC()(),
                  FontStruct_t font = GetDefaultFontStruct(),
                  Pixel_t back = GetDefaultFrameBackground()) :
      TGButtonGroup(parent, title, kChildFrame | kHorizontalFrame,
                    norm, font, back) { }

   virtual ~TGHButtonGroup() { }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a button group widget as a C++ statement(s) on output stream out.   
```


## code

// Example:                                                             //
//                                                                      //
//    // vertical frame without border and title                        //
//    TGVButtonGroup *bg = new TGVButtonGroup(main_frame);              //
//                                                                      //
//    // create text button with id=1                                   //
//    TGTextButton *button1 = new TGTextButton(bg,"some text");         //
//                                                                      //
//    // create another text button with id=2                           //
//    TGTextButton *button2 = new TGTextButton(bg,"another text");      //
//                                                                      //
//    // map all buttons                                                //
//    bg->Show();                                                       //

## example



<!-- TGButtonGroup.md ends here -->
