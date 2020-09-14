<!-- THttpWSHandler.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 6月  6 01:02:18 2018 (+0800)
;; Last-Updated: 三 6月  6 01:03:57 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# THttpWSHandler

THttpWSHandler : public TNamed  
friend class THttpServer


```cpp
/// Class for user-side handling of websocket with THttpServer
/// 1. Create derived from  THttpWSHandler class and implement
///     ProcessWS() method, where all web sockets request handled.
/// 2. Register instance of derived class to running THttpServer
///
///        TUserWSHandler *handler = new TUserWSHandler("name1","title");
///        THttpServer *server = new THttpServer("http:8090");
///        server->Register("/subfolder", handler)
///
/// 3. Now server can accept web socket connection from outside.
///    For instance, from JavaScirpt one can connect to it with code:
///
///        var ws = new WebSocket("ws://hostname:8090/subfolder/name1/root.websocket")
///
/// 4. In the ProcessWS(THttpCallArg *arg) method following code should be implemented:
///
///     if (arg->IsMethod("WS_CONNECT")) {
///         return true;  // to accept incoming request
///      }
///
///      if (arg->IsMethod("WS_READY")) {
///          fWSId = arg->GetWSId(); // fWSId should be member of the user class
///          return true; // connection established
///      }
///
///     if (arg->IsMethod("WS_CLOSE")) {
///         fWSId = 0;
///         return true; // confirm close of socket
///     }
///
///     if (arg->IsMethod("WS_DATA")) {
///         // received data stored as POST data
///         std::string str((const char *)arg->GetPostData(), arg->GetPostDataLength());
///         std::cout << "got string " << str << std::endl;
///         // immediately send data back using websocket id
///         SendCharStarWS(fWSId, "our reply");
///         return true;
///     }
```

## class

```cpp
   virtual ~THttpWSHandler();

   /// Provides content of default web page for registered web-socket handler
   /// Can be content of HTML page or file name, where content should be taken
   /// For instance, file:/home/user/test.htm or file:$jsrootsys/files/canvas.htm
   /// If not specified, default index.htm page will be shown
   /// Used by the webcanvas
   virtual TString GetDefaultPageContent() { return ""; }

   /// Return kTRUE if websocket with given ID exists
   Bool_t HasWS(UInt_t wsid) const { return FindEngine(wsid) != 0; }

   void CloseWS(UInt_t wsid);

   void SendWS(UInt_t wsid, const void *buf, int len);

   void SendCharStarWS(UInt_t wsid, const char *str);

   virtual Bool_t ProcessWS(THttpCallArg *arg) = 0;
```

<!-- THttpWSHandler.md ends here -->
