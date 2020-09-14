<!-- TGClient.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 20:20:22 2016 (+0800)
;; Last-Updated: 六 11月 19 15:01:40 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGClient

TGClient 继承 TObject, TQObject , friend TGCocoa

Window client. In client server windowing systems, like X11 this     
class is used to make the initial connection to the window server.

## class

```cpp
   TGClient(const char *dpyName = 0);
/// Create a connection with the display sever on host dpyName and setup
/// the complete GUI system, i.e., graphics contexts, fonts, etc. for all
/// widgets.

   virtual ~TGClient();/// Closing down client: cleanup and close X connection.

   const TGWindow *GetRoot() const;
/// Returns current root (i.e. base) window. By changing the root
/// window one can change the window hierarchy, e.g. a top level
/// frame (TGMainFrame) can be embedded in another window.

   const TGWindow *GetDefaultRoot() const;
/// Returns the root (i.e. desktop) window. Should only be used as parent
/// for frames that will never be embedded, like popups, message boxes,
/// etc. (like TGToolTips, TGMessageBox, etc.).

   void            SetRoot(TGWindow *root = 0);
/// Sets the current root (i.e. base) window. By changing the root
/// window one can change the window hierarchy, e.g. a top level
/// frame (TGMainFrame) can be embedded in another window.

   TGWindow       *GetWindowById(Window_t sw) const;
/// Find a TGWindow via its handle. If window is not found return 0.

   TGWindow       *GetWindowByName(const char *name) const;
/// Find a TGWindow via its name (unique name used in TGWindow::SavePrimitive).
/// If window is not found return 0.

   UInt_t       GetDisplayWidth() const;/// Get display width.
   UInt_t       GetDisplayHeight() const;/// Get display height.

   Bool_t       IsEditable() const { return fRoot != fDefaultRoot; }
   Bool_t       IsEditDisabled() const;/// Returns kTRUE if edit/guibuilding is forbidden.
   void         SetEditDisabled(Bool_t on = kTRUE);/// If on is kTRUE editting/guibuilding is forbidden.

   FontStruct_t GetFontByName(const char *name, Bool_t fixedDefault = kTRUE) const;
/// Get a font by name. If font is not found, fixed font is returned,
/// if fixed font also does not exist return 0 and print error.
/// The loaded font needs to be freed using TVirtualX::DeleteFont().
/// If fixedDefault is false the "fixed" font will not be substituted
/// as fallback when the asked for font does not exist.

   Bool_t       GetColorByName(const char *name, Pixel_t &pixel) const;
/// Get a color by name. If color is found return kTRUE and pixel is
/// set to the color's pixel value, kFALSE otherwise.

   Pixel_t      GetHilite(Pixel_t base_color) const;/// Return pixel value of hilite color based on base_color.
   Pixel_t      GetShadow(Pixel_t base_color) const;
/// Return pixel value of shadow color based on base_color.
/// Shadow is 60% of base_color intensity.

   void         FreeColor(Pixel_t color) const;/// Free color.
   void         ForceRedraw() { fForceRedraw = kTRUE; }
   void         NeedRedraw(TGWindow *w, Bool_t force = kFALSE);/// Set redraw flags.
   void         CancelRedraw(TGWindow *w);
   void         RegisterWindow(TGWindow *w);/// Add a TGWindow to the clients list of windows.
   void         UnregisterWindow(TGWindow *w);/// Remove a TGWindow from the list of windows.
   void         RegisterPopup(TGWindow *w);
/// Add a popup menu to the list of popups. This list is used to pass
/// events to popup menus that are popped up over a transient window which
/// is waited for (see WaitFor()).

   void         UnregisterPopup(TGWindow *w);/// Remove a popup menu from the list of popups.
   void         AddUnknownWindowHandler(TGUnknownWindowHandler *h);
/// Add handler for unknown (i.e. unregistered) windows.

   void         RemoveUnknownWindowHandler(TGUnknownWindowHandler *h);
/// Remove handler for unknown (i.e. unregistered) windows.

   void         AddIdleHandler(TGIdleHandler *h);/// Add handler for idle events.
   void         RemoveIdleHandler(TGIdleHandler *h);/// Remove handler for idle events.
   Bool_t       HandleInput();
/// Handles input from the display server. Returns kTRUE if one or more
/// events have been processed, kFALSE otherwise.

   void         ProcessLine(TString cmd, Long_t msg, Long_t parm1, Long_t parm2);
/// Execute string "cmd" via the interpreter. Before executing replace
/// in the command string the token $MSG, $PARM1 and $PARM2 by msg,
/// parm1 and parm2, respectively. The function in cmd string must accept
/// these as longs.

   void         WaitFor(TGWindow *w);/// Wait for window to be destroyed.
   void         WaitForUnmap(TGWindow *w);/// Wait for window to be unmapped.
   void         ResetWaitFor(TGWindow *w);/// reset waiting
   EGEventType  GetWaitForEvent() const  { return fWaitForEvent;}
   Window_t     GetWaitForWindow() const { return fWaitForWindow; }
   void         SetWaitForWindow(Window_t wid) {fWaitForWindow = wid;}
   Bool_t       ProcessEventsFor(TGWindow *w);
/// Like gSystem->ProcessEvents() but then only allow events for w to
/// be processed. For example to interrupt the processing and destroy
/// the window, call gROOT->SetInterrupt() before destroying the window.

   Bool_t       HandleEvent(Event_t *event);/// Handle a GUI event.
   Bool_t       HandleMaskEvent(Event_t *event, Window_t wid);
/// Handle masked events only if window wid is the window for which the
/// event was reported or if wid is a parent of the event window. The not
/// masked event are handled directly. The masked events are:
/// kButtonPress, kButtonRelease, kKeyPress, kKeyRelease, kEnterNotify,
/// kLeaveNotify, kMotionNotify.

   void         RegisteredWindow(Window_t w);      //*SIGNAL*
/// Emits a signal when a Window has been registered in TGClient.
/// Used in TRecorder.

   void         ProcessedEvent(Event_t *event, Window_t wid);   //*SIGNAL*
/// Emits a signal when an event has been processed.
/// Used in TRecorder.

   const TGResourcePool *GetResourcePool() const { return fResourcePool; }

   TGPicturePool   *GetPicturePool() const { return fPicturePool; }
   const TGPicture *GetPicture(const char *name);
/// Get picture from the picture pool. Picture must be freed using
/// TGClient::FreePicture(). If picture is not found 0 is returned.

   const TGPicture *GetPicture(const char *name, UInt_t new_width, UInt_t new_height);
/// Get picture with specified size from pool (picture will be scaled if
/// necessary). Picture must be freed using TGClient::FreePicture(). If
/// picture is not found 0 is returned.

   void             FreePicture(const TGPicture *pic);/// Free picture resource.

   TGGCPool        *GetGCPool() const { return fGCPool; }
   TGGC            *GetGC(GCValues_t *values, Bool_t rw = kFALSE);
/// Get graphics context from the gc pool. Context must be freed via
/// TGClient::FreeGC(). If rw is true a new read/write-able GC
/// is returned, otherwise a shared read-only context is returned.
/// For historical reasons it is also possible to create directly a
/// TGGC object, but it is advised to use this new interface only.

   void             FreeGC(const TGGC *gc);/// Free a graphics context.
   void             FreeGC(GContext_t gc);/// Free a graphics context.

   TGFontPool      *GetFontPool() const { return fFontPool; }
   TGFont          *GetFont(const char *font, Bool_t fixedDefault = kTRUE);
/// Get a font from the font pool. Fonts must be freed via
/// TGClient::FreeFont(). Returns 0 in case of error or if font
/// does not exist. If fixedDefault is false the "fixed" font
/// will not be substituted as fallback when the asked for font
/// does not exist.

   TGFont          *GetFont(const TGFont *font);/// Get again specified font. Will increase its usage count.
   void             FreeFont(const TGFont *font);/// Free a font.

   UInt_t           GetStyle() const { return fStyle; }
   void             SetStyle(UInt_t newstyle) { fStyle = newstyle; }
   void             SetStyle(const char *style);/// Set the button style (modern or classic).

   Colormap_t       GetDefaultColormap() const { return fDefaultColormap; }
   TGMimeTypes     *GetMimeTypeList() const { return fMimeTypeList; }

   THashList       *GetListOfWindows() const { return fWlist; }
   TList           *GetListOfPopups() const { return fPlist; }

   static TGClient *Instance();/// Returns global gClient (initialize graphics first, if not already done)
```

```cpp
#ifndef __CINT__
#define gClient (TGClient::Instance())
#endif
```


## code



## example

<!-- TGClient.md ends here -->
