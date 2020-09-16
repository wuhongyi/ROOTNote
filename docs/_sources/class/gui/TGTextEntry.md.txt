<!-- TGTextEntry.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 13:52:02 2016 (+0800)
;; Last-Updated: 三 9月 16 11:16:44 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->

# TGTextEntry*

```cpp
// A TGTextEntry is a one line text input widget.                       
//                                                                      
// Changing text in the text entry widget will generate the event:      
// kC_TEXTENTRY, kTE_TEXTCHANGED, widget id, 0.                         
// Hitting the enter key will generate:                                 
// kC_TEXTENTRY, kTE_ENTER, widget id, 0.                               
// Hitting the tab key will generate:                                   
// kC_TEXTENTRY, kTE_TAB, widget id, 0.                                 
```


TGTextEntry 继承 TGFrame, TGWidget


## class

```cpp
   enum   EEchoMode { kNormal, kNoEcho, kPassword };
   enum   EInsertMode { kInsert, kReplace };

   static FontStruct_t  GetDefaultFontStruct();/// Return default font structure in use.
   static const TGGC   &GetDefaultGC();/// Return default graphics context.

   TGTextEntry(const TGWindow *p, TGTextBuffer *text, Int_t id = -1,
               GContext_t norm = GetDefaultGC()(),
               FontStruct_t font = GetDefaultFontStruct(),
               UInt_t option = kSunkenFrame | kDoubleBorder,
               Pixel_t back = GetWhitePixel());
/// Create a text entry widget. It will adopt the TGTextBuffer object
/// (i.e. the text buffer will be deleted by the text entry widget).

   TGTextEntry(const TGWindow *parent = 0, const char *text = 0, Int_t id = -1);/// Simple text entry constructor.
   TGTextEntry(const TString &contents, const TGWindow *parent, Int_t id = -1);
/// Simple test entry constructor. Notice TString argument comes before the
/// parent argument (to make this ctor different from the first one taking a
/// const char*).

   virtual ~TGTextEntry();

   virtual  TGDimension GetDefaultSize() const;/// Return the default / minimal size of the widget.
   virtual  void        SetDefaultSize(UInt_t w, UInt_t h);
/// Set the default / minimal size of the widget.

   virtual  void        AppendText(const char *text);
/// Appends text to the end of text entry, clears the selection
/// and moves the cursor to the end of the line.
/// If necessary the text is truncated to fit MaxLength().
/// See also GetText(), InsertText(), SetText(), RemoveText().

            void        Backspace();
/// Deletes the character on the left side of the text cursor and moves the
/// cursor one position to the left. If a text has been marked by the user
/// (e.g. by clicking and dragging) the cursor will be put at the beginning
/// of the marked text and the marked text will be removed.
/// See also  Del().

            void        Clear(Option_t *option="");/// Clears up the text entry.
            void        CursorLeft(Bool_t mark = kFALSE , Int_t steps = 1);
/// Moves the cursor leftwards one or more characters.
/// See also CursorRight().

            void        CursorRight(Bool_t mark = kFALSE , Int_t steps = 1);
/// Moves the cursor rightwards one or more characters.
/// See also CursorLeft().

            void        CursorWordForward(Bool_t mark = kFALSE);
/// Moves the cursor one word to the right.  If mark is kTRUE, the text
/// is marked. See also CursorWordBackward().

            void        CursorWordBackward(Bool_t mark = kFALSE);
/// Moves the cursor one word to the left.  If mark is kTRUE, the text
/// is marked. See also CursorWordForward().

            void        Cut();
/// Copies the marked text to the clipboard and deletes it, if there is any.
/// See also CopyText() Paste().

            void        Del();
/// Deletes the character on the right side of the text cursor. If a text
/// has been marked by the user (e.g. by clicking and dragging) the cursor
/// will be put at the beginning of the marked text and the marked text will
/// be removed.
/// See also Backspace().

            void        Deselect();
/// Deselects all text (i.e. removes marking) and leaves the cursor at the current position.
   virtual  void        DrawBorder();/// Draw the border of the text entry widget.
            void        End(Bool_t mark = kFALSE);
/// Moves the text cursor to the right end of the line. If mark is kTRUE text
/// will be marked towards the last position, if not any marked text will
/// be unmarked if the cursor is moved.
/// See also Home().

   ETextJustification   GetAlignment() const       { return fAlignment; }//获得文本的对齐方式
   TGTextBuffer        *GetBuffer() const { return fText; }
            Int_t       GetCursorPosition() const  { return fCursorIX; }
            TString     GetDisplayText() const;
/// Returns the text that's currently displayed.  This is normally
/// the same as GetText(), but can be e.g.
/// "*****" if EEchoMode is kPassword or
/// ""      if it is kNoEcho.

   EEchoMode            GetEchoMode() const        { return fEchoMode; }
   EInsertMode          GetInsertMode() const      { return fInsertMode; }
            TString     GetMarkedText() const;
/// Returns the text marked by the user (e.g. by clicking and
/// dragging), or zero if no text is marked. See also HasMarkedText().

            Int_t       GetMaxLength() const    { return fMaxLen; }
   const    char       *GetText() const { return fText->GetString(); }
   virtual TGToolTip   *GetToolTip() const { return fTip; }
   virtual const char  *GetTitle() const { return GetText(); }
            Bool_t      HasMarkedText() const  { return fSelectionOn && (fStartIX != fEndIX); }
            Pixel_t     GetTextColor() const { return fNormGC.GetForeground(); }
           FontStruct_t GetFontStruct() const { return fFontStruct; }
            void        Home(Bool_t mark = kFALSE);
/// Moves the text cursor to the left end of the line. If mark is kTRUE text
/// will be marked towards the first position, if not any marked text will
/// be unmarked if the cursor is moved.
/// See also End().

   virtual  void        Insert(const char *);
/// Removes any currently selected text, inserts newText,
/// sets it as the new contents of the text entry.

   virtual  void        InsertText(const char *text, Int_t pos);
/// Inserts text at position pos, clears the selection and moves
/// the cursor to the end of the line.
/// If necessary the text is truncated to fit MaxLength().
/// See also GetText(), SetText(), AppendText(), RemoveText().

            Bool_t      IsFrameDrawn() const       { return fFrameDrawn; }
            Bool_t      IsEdited() const           { return fEdited; }
   virtual  void        Layout() { UpdateOffset(); }
            void        MarkWord(Int_t pos);
/// Marks the word nearest to cursor position. See also HandleDoubleClick().

            Int_t       MaxMark() const { return fStartIX > fEndIX ? fStartIX : fEndIX; }
            Int_t       MinMark() const { return fStartIX < fEndIX ? fStartIX : fEndIX; }
            void        NewMark(Int_t pos);
/// New character mark at position pos. See also SetCursorPosition().

            void        Remove();
/// Deletes all characters on the right side of the cursor.
/// See also Del() Backspace().

   virtual  void        RemoveText(Int_t start, Int_t end);
/// Removes text at the range, clears the selection and moves
/// the cursor to the end of the line.
/// See also GetText(), InsertText(), SetText(), AppendText().

   virtual  void        SetFont(TGFont *font, Bool_t local = kTRUE);
/// Changes text font specified by pointer to TGFont object. If local is kTRUE font is changed locally.

   virtual  void        SetFont(FontStruct_t font, Bool_t local = kTRUE);
/// Changes text font. If local is kTRUE font is changed locally.

   virtual  void        SetFont(const char *fontName, Bool_t local = kTRUE);
/// Changes text font specified by name. If local is kTRUE font is changed locally.

   virtual  void        SetTextColor(Pixel_t color, Bool_t local = kTRUE);
/// Changes text color. If local is true color is changed locally.

   virtual  void        SetTextColor(TColor *color, Bool_t local = kTRUE);
/// Changes text color. If local is true color is changed locally.

   virtual  void        SetText(const char *text, Bool_t emit = kTRUE);          //*MENU*
/// Sets text entry to text, clears the selection and moves
/// the cursor to the end of the line.
/// If necessary the text is truncated to fit MaxLength().
/// See also  GetText().

   virtual  void        SetToolTipText(const char *text, Long_t delayms = 500);  //*MENU* 设置鼠标放上去将会出现的提醒文字
/// Set tool tip text associated with this text entry. The delay is in
/// milliseconds (minimum 250). To remove tool tip call method with text = 0.

   virtual  void        SetMaxLength(Int_t maxlen);                              //*MENU*
/// Set the maximum length of the text in the editor.  If the text is
/// currently too long, it is chopped off at the limit. Any marked text will
/// be unmarked.  The cursor position is set to 0 and the first part of the
/// string is shown.
/// See  also GetMaxLength().

   virtual  void        SelectAll();
/// Selects all text (i.e. marks it) and moves the cursor to the
/// end. Useful when a default value has been inserted. If the user
/// types before clicking on the widget the selected text will be
/// erased.

   virtual  void        SetAlignment(ETextJustification mode = kTextLeft);       //*SUBMENU*
// 设置文本对齐方式
/// Sets the alignment of the text entry.
/// Possible values are kTextLeft(default), kTextRight, kTextCenterX.
/// See also GetAlignment().

   virtual  void        SetInsertMode(EInsertMode mode = kInsert);               //*SUBMENU*
/// Sets the mode how characters are entered to the text entry.

   virtual  void        SetEchoMode(EEchoMode mode = kNormal);                   //*SUBMENU*
/// The echo modes available are:
///  kNormal   - display characters as they are entered.  This is the default.
///  kNoEcho   - do not display anything.
///  kPassword - display asterisks instead of the characters actually entered.
/// It is always possible to cut and paste any marked text;  only the widget's own
/// display is affected.
/// See also GetEchoMode(), GetDisplayText().

            void        SetEnabled(Bool_t flag = kTRUE) { SetState( flag ); }    //*TOGGLE* *GETTER=IsEnabled
   virtual  void        SetCursorPosition(Int_t pos);
/// Set the cursor position to newPos. See also NewMark().

            void        SetEdited(Bool_t flag = kTRUE) { fEdited = flag; }
   virtual  void        SetFocus();/// Set focus to this text entry.
   virtual  void        SetFrameDrawn(Bool_t flag = kTRUE);
/// Sets the text entry to draw itself inside a two-pixel frame if
/// enable is kTRUE, and to draw itself without any frame if enable is
/// kFALSE. The default is kTRUE.

   virtual  void        SetState(Bool_t state);/// Set state of widget. If kTRUE=enabled, kFALSE=disabled.
   virtual  void        SetTitle(const char *label) { SetText(label); }
   virtual  void        SetForegroundColor(Pixel_t fore) { SetTextColor(fore, kFALSE); }
   Pixel_t              GetForeground() const { return fNormGC.GetForeground(); }
   Bool_t               HasOwnFont() const { return fHasOwnFont; }

   virtual  void        SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a text entry widget as a C++ statement(s) on output stream out.

   virtual  Bool_t      HandleButton(Event_t *event);/// Handle mouse button event in text entry widget.
   virtual  Bool_t      HandleDoubleClick(Event_t *event);/// Handle mouse double click event in the text entry widget.
   virtual  Bool_t      HandleCrossing(Event_t *event);/// Handle mouse crossing event.
   virtual  Bool_t      HandleMotion(Event_t *event);/// Handle mouse motion event in the text entry widget.
   virtual  Bool_t      HandleKey(Event_t *event);
/// The key press event handler converts a key press to some line editor
/// action. Here are the default key bindings:
///   Left Arrow
///          Move the cursor one character leftwards.
///          Scroll the text when  cursor is out of frame.
///   Right Arrow
///          Move the cursor one character rightwards
///          Scroll the text when  cursor is out of frame.
///   Backspace
///          Deletes the character on the left side of the text cursor and moves the
///          cursor one position to the left. If a text has been marked by the user
///          (e.g. by clicking and dragging) the cursor will be put at the beginning
///          of the marked text and the marked text will be removed.
///   Home
///          Moves the text cursor to the left end of the line. If mark is TRUE text
///          will be marked towards the first position, if not any marked text will
///          be unmarked if the cursor is moved.
///   End
///          Moves the text cursor to the right end of the line. If mark is TRUE text
///          will be marked towards the last position, if not any marked text will
///          be unmarked if the cursor is moved.
///   Delete
///          Deletes the character on the right side of the text cursor. If a text
///          has been marked by the user (e.g. by clicking and dragging) the cursor
///          will be put at the beginning of the marked text and the marked text will
///          be removed.
///   Insert
///          Switches character insert mode.
///   Shift - Left Arrow
///          Mark text one character leftwards
///   Shift - Right Arrow
///          Mark text one character rightwards
///   Control - Left Arrow
///          Move the cursor one word leftwards
///   Control - Right Arrow
///          Move the cursor one word rightwards.
///   Control - Shift - Left Arrow
///          Mark text one word leftwards
///   Control - Shift - Right Arrow
///          Mark text one word rightwards
///   Control-A
///          Move the cursor to the beginning of the line
///   Control-B
///          Move the cursor one character leftwards
///   Control-C
///          Copy the marked text to the clipboard.
///   Control-D
///          Delete the character to the right of the cursor
///   Control-E
///          Move the cursor to the end of the line
///   Control-F
///          Move the cursor one character rightwards
///   Control-H
///          Delete the character to the left of the cursor
///   Control-K
///          Delete marked text if any or delete all
///          characters to the right of the cursor
///   Control-U
///          Delete all characters on the line
///   Control-V
///          Paste the clipboard text into line edit.
///   Control-X
///          Cut the marked text, copy to clipboard.
///   Control-Y
///          Paste the clipboard text into line edit.
///  All other keys with valid ASCII codes insert themselves into the line.

   virtual  Bool_t      HandleFocusChange(Event_t *event);/// Handle focus change event in text entry widget.
   virtual  Bool_t      HandleSelection(Event_t *event);/// Handle text selection event.
   virtual  Bool_t      HandleSelectionClear(Event_t *event);/// Handle selection clear event.
   virtual  Bool_t      HandleSelectionRequest(Event_t *event);
/// Handle request to send current clipboard contents to requestor window.

   virtual  Bool_t      HandleTimer(TTimer *t);/// Handle cursor blink timer.
   virtual  Bool_t      HandleConfigureNotify(Event_t *event);/// Handles resize events for this widget.

   virtual  void        TextChanged(const char *text = 0);      //*SIGNAL*
/// This signal is emitted every time the text has changed.

   virtual  void        ReturnPressed();                        //*SIGNAL*
/// This signal is emitted when the return or enter key is pressed.

   virtual  void        TabPressed();                           //*SIGNAL*
/// This signal is emitted when the <TAB> key is pressed.

   virtual  void        ShiftTabPressed();                      //*SIGNAL*
/// This signal is emitted when <SHIFT> and <TAB> keys are pressed.   
   
   virtual  void        CursorOutLeft();                        //*SIGNAL*
/// This signal is emitted when cursor is going out of left side.

   virtual  void        CursorOutRight();                       //*SIGNAL*
/// This signal is emitted when cursor is going out of right side.

   virtual  void        CursorOutUp();                          //*SIGNAL*
/// This signal is emitted when cursor is going out of upper side.

   virtual  void        CursorOutDown();                        //*SIGNAL*
/// This signal is emitted when cursor is going out of bottom side.

   virtual  void        DoubleClicked();                        //*SIGNAL*
/// This signal is emitted when widget is double clicked.   
```

## code

```cpp
// TGTextEntry
// 单个文本框
TGTextEntry *fTestText = new TGTextEntry(frame, new TGTextBuffer(100));
fTestText->SetToolTipText("This is a text entry widget");
fTestText->Resize(300, fTestText->GetDefaultHeight());
frame->AddFrame(fTestText, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 2, 2, 2));
// fTestText->Clear();//清除内容
std::string command = fTestText->GetText();
```


## example



<!-- TGTextEntry.md ends here -->
