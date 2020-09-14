<!-- THttpServer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 6月  6 00:46:38 2018 (+0800)
;; Last-Updated: 三 6月  6 01:00:02 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# THttpServer

THttpServer : public TNamed

Emulation of websocket with long poll requests                       
Allows to send data from server to client without explicit request


```cpp
// Online http server for arbitrary ROOT application                    //
//                                                                      //
// Idea of THttpServer - provide remote http access to running          //
// ROOT application and enable HTML/JavaScript user interface.          //
// Any registered object can be requested and displayed in the browser. //
// There are many benefits of such approach:                            //
//     * standard http interface to ROOT application                    //
//     * no any temporary ROOT files when access data                   //
//     * user interface running in all browsers                         //
//                                                                      //
// Starting HTTP server                                                 //
//                                                                      //
// To start http server, at any time  create instance                   //
// of the THttpServer class like:                                       //
//    serv = new THttpServer("http:8080");                              //
//                                                                      //
// This will starts civetweb-based http server with http port 8080.     //
// Than one should be able to open address "http://localhost:8080"      //
// in any modern browser (IE, Firefox, Chrome) and browse objects,      //
// created in application. By default, server can access files,         //
// canvases and histograms via gROOT pointer. All such objects          //
// can be displayed with JSROOT graphics.                               //
//                                                                      //
// At any time one could register other objects with the command:       //
//                                                                      //
// TGraph* gr = new TGraph(10);                                         //
// gr->SetName("gr1");                                                  //
// serv->Register("graphs/subfolder", gr);                              //
//                                                                      //
// If objects content is changing in the application, one could         //
// enable monitoring flag in the browser - than objects view            //
// will be regularly updated.                                           //
//                                                                      //
// More information: https://root.cern/root/htmldoc/guides/HttpServer/HttpServer.html  //

```

## class


```cpp
   THttpServer(const char *engine = "civetweb:8080");
/// As argument, one specifies engine kind which should be
/// created like "http:8080". One could specify several engines
/// at once, separating them with semicolon (";"). Following engines are supported:
///
///       http - TCivetweb, civetweb-based implementation of http protocol
///       fastcgi - TFastCgi, special protocol for communicating with web servers
///
/// For each created engine one should provide socket port number like "http:8080" or "fastcgi:9000".
/// Additional engine-specific options can be supplied with URL syntax like "http:8080?thrds=10".
/// Full list of supported options should be checked in engines docu.
///
/// One also can configure following options, separated by semicolon:
///
///     readonly, ro   - set read-only mode (default)
///     readwrite, rw  - allows methods execution of registered objects
///     global         - scans global ROOT lists for existing objects (default)
///     noglobal       - disable scan of global lists
///     cors           - enable CORS header with origin="*"
///     cors=domain    - enable CORS header with origin="domain"
///
/// For example, create http server, which allows cors headers and disable scan of global lists,
/// one should provide "http:8080;cors;noglobal" as parameter
///
/// THttpServer uses JavaScript ROOT (https://root.cern/js) to implement web clients UI.
/// Normally JSROOT sources are used from $ROOTSYS/etc/http directory,
/// but one could set JSROOTSYS shell variable to specify alternative location

   virtual ~THttpServer();

   Bool_t CreateEngine(const char *engine);
/// factory method to create different http engines
/// At the moment two engine kinds are supported:
///   civetweb (default) and fastcgi
/// Examples:
///   "http:8080" or "civetweb:8080" or ":8080"  - creates civetweb web server with http port 8080
///   "fastcgi:9000" - creates fastcgi server with port 9000
/// One could apply additional parameters, using URL syntax:
///    "http:8080?thrds=10"

   Bool_t IsAnyEngine() const { return fEngines.GetSize() > 0; }

   /** returns pointer on objects sniffer */
   TRootSniffer *GetSniffer() const { return fSniffer; }

   void SetSniffer(TRootSniffer *sniff);
/// Set TRootSniffer to the server
/// Server takes ownership over sniffer

   Bool_t IsReadOnly() const;/// returns read-only mode

   void SetReadOnly(Bool_t readonly);
/// Set read-only mode for the server (default on)
/// In read-only server is not allowed to change any ROOT object, registered to the server
/// Server also cannot execute objects method via exe.json request

   /** Enable CORS header to ProcessRequests() responses
    * Specified location (typically "*") add as "Access-Control-Allow-Origin" header */
   void SetCors(const char *domain = "*") { fCors = domain; }

   /** Returns kTRUE if CORS was configured */
   Bool_t IsCors() const { return fCors.Length() > 0; }

   /** Returns specified CORS domain */
   const char *GetCors() const { return fCors.Data(); }

   /** set name of top item in objects hierarchy */
   void SetTopName(const char *top) { fTopName = top; }

   /** returns name of top item in objects hierarchy */
   const char *GetTopName() const { return fTopName.Data(); }

   void SetJSROOT(const char *location);
/// Set location of JSROOT to use with the server
/// One could specify address like:
///   https://root.cern.ch/js/3.3/
///   http://web-docs.gsi.de/~linev/js/3.3/
/// This allows to get new JSROOT features with old server,
/// reduce load on THttpServer instance, also startup time can be improved
/// When empty string specified (default), local copy of JSROOT is used (distributed with ROOT)

   void AddLocation(const char *prefix, const char *path);
/// add files location, which could be used in the server
/// one could map some system folder to the server like AddLocation("mydir/","/home/user/specials");
/// Than files from this directory could be addressed via server like
/// http://localhost:8080/mydir/myfile.root

   void SetDefaultPage(const char *filename);
/// Set file name of HTML page, delivered by the server when
/// http address is opened in the browser.
/// By default, $ROOTSYS/etc/http/files/online.htm page is used
/// When empty filename is specified, default page will be used

   void SetDrawPage(const char *filename);
/// Set file name of HTML page, delivered by the server when
/// objects drawing page is requested from the browser
/// By default, $ROOTSYS/etc/http/files/draw.htm page is used
/// When empty filename is specified, default page will be used

   void SetTimer(Long_t milliSec = 100, Bool_t mode = kTRUE);
/// create timer which will invoke ProcessRequests() function periodically
/// Timer is required to perform all actions in main ROOT thread
/// Method arguments are the same as for TTimer constructor
/// By default, sync timer with 100 ms period is created
///
/// It is recommended to always use sync timer mode and only change period to
/// adjust server reaction time. Use of async timer requires, that application regularly
/// calls gSystem->ProcessEvents(). It happens automatically in ROOT interactive shell.
/// If milliSec == 0, no timer will be created.
/// In this case application should regularly call ProcessRequests() method.
///
/// Async timer allows to use THttpServer in applications, which does not have explicit
/// gSystem->ProcessEvents() calls. But be aware, that such timer can interrupt any system call
/// (lise malloc) and can lead to dead locks, especially in multi-threaded applications.

   /** Check if file is requested, thread safe */
   Bool_t IsFileRequested(const char *uri, TString &res) const;
/// Verifies that request is just file name
/// File names typically contains prefix like "jsrootsys/"
/// If true, method returns real name of the file,
/// which should be delivered to the client
/// Method is thread safe and can be called from any thread

   /** Execute HTTP request */
   Bool_t ExecuteHttp(THttpCallArg *arg);
/// Executes http request, specified in THttpCallArg structure
/// Method can be called from any thread
/// Actual execution will be done in main ROOT thread, where analysis code is running.

   /** Submit HTTP request */
   Bool_t SubmitHttp(THttpCallArg *arg, Bool_t can_run_immediately = kFALSE);
/// Submit http request, specified in THttpCallArg structure
/// Contrary to ExecuteHttp, it will not block calling thread.
/// User should reimplement THttpCallArg::HttpReplied() method
/// to react when HTTP request is executed.
/// Method can be called from any thread
/// Actual execution will be done in main ROOT thread, where analysis code is running.
/// When called from main thread and can_run_immediately==kTRUE, will be
/// executed immediately. Returns kTRUE when was executed.

   /** Process submitted requests, must be called from main thread */
   void ProcessRequests();
/// Process requests, submitted for execution
/// Regularly invoked by THttpTimer, when somewhere in the code
/// gSystem->ProcessEvents() is called.
/// User can call serv->ProcessRequests() directly, but only from main analysis thread.

   /** Register object in subfolder */
   Bool_t Register(const char *subfolder, TObject *obj);
/// Register object in folders hierarchy
/// See TRootSniffer::RegisterObject() for more details

   /** Unregister object */
   Bool_t Unregister(TObject *obj);
/// Unregister object in folders hierarchy
/// See TRootSniffer::UnregisterObject() for more details

   /** Restrict access to specified object */
   void Restrict(const char *path, const char *options);
/// Restrict access to specified object
/// See TRootSniffer::Restrict() for more details

   Bool_t RegisterCommand(const char *cmdname, const char *method, const char *icon = 0);
/// Register command which can be executed from web interface
///
/// As method one typically specifies string, which is executed with
/// gROOT->ProcessLine() method. For instance
///    serv->RegisterCommand("Invoke","InvokeFunction()");
///
/// Or one could specify any method of the object which is already registered
/// to the server. For instance:
///     serv->Register("/", hpx);
///     serv->RegisterCommand("/ResetHPX", "/hpx/->Reset()");
/// Here symbols '/->' separates item name from method to be executed
///
/// One could specify additional arguments in the command with
/// syntax like %arg1%, %arg2% and so on. For example:
///     serv->RegisterCommand("/ResetHPX", "/hpx/->SetTitle(\"%arg1%\")");
///     serv->RegisterCommand("/RebinHPXPY", "/hpxpy/->Rebin2D(%arg1%,%arg2%)");
/// Such parameter(s) will be requested when command clicked in the browser.
///
/// Once command is registered, one could specify icon which will appear in the browser:
///     serv->SetIcon("/ResetHPX", "rootsys/icons/ed_execute.png");
///
/// One also can set extra property '_fastcmd', that command appear as
/// tool button on the top of the browser tree:
///     serv->SetItemField("/ResetHPX", "_fastcmd", "true");
/// Or it is equivalent to specifying extra argument when register command:
///     serv->RegisterCommand("/ResetHPX", "/hpx/->Reset()", "button;rootsys/icons/ed_delete.png");


   Bool_t Hide(const char *fullname, Bool_t hide = kTRUE);
/// hides folder or element from web gui

   Bool_t SetIcon(const char *fullname, const char *iconname);
/// set name of icon, used in browser together with the item
/// One could use images from $ROOTSYS directory like:
///    serv->SetIcon("/ResetHPX","/rootsys/icons/ed_execute.png");

   Bool_t CreateItem(const char *fullname, const char *title);

   Bool_t SetItemField(const char *fullname, const char *name, const char *value);

   const char *GetItemField(const char *fullname, const char *name);

   /** Guess mime type base on file extension */
   static const char *GetMimeType(const char *path);

   /** Reads content of file from the disk */
   static char *ReadFileContent(const char *filename, Int_t &len);
```


<!-- THttpServer.md ends here -->
