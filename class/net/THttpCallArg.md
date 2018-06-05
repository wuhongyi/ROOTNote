<!-- THttpCallArg.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 6月  5 23:53:08 2018 (+0800)
;; Last-Updated: 二 6月  5 23:58:56 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# THttpCallArg

THttpCallArg : public TObject

Contains arguments for single HTTP call   
Must be used in THttpEngine to process incoming http requests


## class

```cpp
   THttpCallArg();
   ~THttpCallArg();

   // these methods used to set http request arguments

   /** set request method kind like GET or POST */
   void SetMethod(const char *method) { fMethod = method; }

   /** set engine-specific top-name */
   void SetTopName(const char *topname) { fTopName = topname; }

   void SetPathAndFileName(const char *fullpath);
/// set complete path of requested http element
/// For instance, it could be "/folder/subfolder/get.bin"
/// Here "/folder/subfolder/" is element path and "get.bin" requested file.
/// One could set path and file name separately

   /** set request path name */
   void SetPathName(const char *p) { fPathName = p; }

   /** set request file name */
   void SetFileName(const char *f) { fFileName = f; }

   /** set name of authenticated user */
   void SetUserName(const char *n) { fUserName = n; }

   /** set request query */
   void SetQuery(const char *q) { fQuery = q; }

   void SetPostData(void *data, Long_t length, Bool_t make_copy = kFALSE);
/// set data, posted with the request
/// buffer should be allocated with malloc(length+1) call,
/// while last byte will be set to 0
/// Than one could use post data as null-terminated string

   void SetWSHandle(TNamed *handle);
/// assign websocket handle with HTTP call

   TNamed *TakeWSHandle();
/// takeout websocket handle with HTTP call
/// can be done only once

   /** set web-socket id */
   void SetWSId(UInt_t id) { fWSId = id; }

   /** get web-socket id */
   UInt_t GetWSId() const { return fWSId; }

   /** set full set of request header */
   void SetRequestHeader(const char *h) { fRequestHeader = h ? h : ""; }

   /** returns number of fields in request header */
   Int_t NumRequestHeader() const { return CountHeader(fRequestHeader).Atoi(); }

   /** returns field name in request header */
   TString GetRequestHeaderName(Int_t number) const { return CountHeader(fRequestHeader, number); }

   /** get named field from request header */
   TString GetRequestHeader(const char *name) { return AccessHeader(fRequestHeader, name); }

   /** returns engine-specific top-name */
   const char *GetTopName() const { return fTopName.Data(); }

   /** returns request method like GET or POST */
   const char *GetMethod() const { return fMethod.Data(); }

   /** returns kTRUE if post method is used */
   Bool_t IsMethod(const char *name) const { return fMethod.CompareTo(name) == 0; }

   /** returns kTRUE if post method is used */
   Bool_t IsPostMethod() const { return IsMethod("POST"); }

   /** return pointer on posted with request data */
   void *GetPostData() const { return fPostData; }

   /** return length of posted with request data */
   Long_t GetPostDataLength() const { return fPostDataLength; }

   /** returns post data as TString */
   TString GetPostDataAsString() const { return TString((const char *) GetPostData(), GetPostDataLength()); }

   /** returns path name from request URL */
   const char *GetPathName() const { return fPathName.Data(); }

   /** returns file name from request URL */
   const char *GetFileName() const { return fFileName.Data(); }

   /** return authenticated user name (0 - when no authentication) */
   const char *GetUserName() const { return fUserName.Length() > 0 ? fUserName.Data() : 0; }

   /** returns request query (string after ? in request URL) */
   const char *GetQuery() const { return fQuery.Data(); }

   // these methods used in THttpServer to set results of request processing

   /** set content type like "text/xml" or "application/json" */
   void SetContentType(const char *typ) { fContentType = typ; }

   /** mark reply as 404 error - page/request not exists or refused */
   void Set404() { SetContentType("_404_"); }

   /** mark reply as postponed - submitting thread will not be inform */
   void SetPostponed() { SetContentType("_postponed_"); }

   /** indicate that http request should response with file content */
   void SetFile(const char *filename = 0)
   {
      SetContentType("_file_");
      if (filename != 0)
         fContent = filename;
   }

   /** set content type as XML */
   void SetXml() { SetContentType("text/xml"); }

   /** set content type as JSON */
   void SetJson() { SetContentType("application/json"); }

   void AddHeader(const char *name, const char *value);
/// Set name: value pair to reply header
/// Content-Type field handled separately - one should use SetContentType() method
/// Content-Length field cannot be set at all;

   /** returns number of fields in header */
   Int_t NumHeader() const { return CountHeader(fHeader).Atoi(); }

   /** returns field name in header */
   TString GetHeaderName(Int_t number) const { return CountHeader(fHeader, number); }

   TString GetHeader(const char *name);/// return specified header

   /** Set Content-Encoding header like gzip */
   void SetEncoding(const char *typ) { AccessHeader(fHeader, "Content-Encoding", typ, kTRUE); }

   /** Set content directly */
   void SetContent(const char *c) { fContent = c; }

   Bool_t CompressWithGzip();/// compress reply data with gzip compression

   /** Set kind of content zipping
     * 0 - none
     * 1 - only when supported in request header
     * 2 - if supported and content size bigger than 10K
     * 3 - always */
   void SetZipping(Int_t kind) { fZipping = kind; }

   /** return kind of content zipping */
   Int_t GetZipping() const { return fZipping; }

   /** add extra http header value to the reply */
   void SetExtraHeader(const char *name, const char *value) { AddHeader(name, value); }

   // Fill http header
   void FillHttpHeader(TString &buf, const char *header = 0);

   // these methods used to return results of http request processing

   Bool_t IsContentType(const char *typ) const { return fContentType == typ; }
   Bool_t Is404() const { return IsContentType("_404_"); }
   Bool_t IsFile() const { return IsContentType("_file_"); }
   Bool_t IsPostponed() const { return IsContentType("_postponed_"); }
   const char *GetContentType() const { return fContentType.Data(); }

   void SetBinData(void *data, Long_t length);
/// set binary data, which will be returned as reply body

   Long_t GetContentLength() const { return IsBinData() ? fBinDataLength : fContent.Length(); }

   const void *GetContent() const { return IsBinData() ? fBinData : fContent.Data(); }

   void NotifyCondition();
/// method used to notify condition which waiting when operation will complete
/// Condition notified only if not-postponed state is set

   virtual void HttpReplied();
/// virtual method to inform object that http request is processed
/// Normally condition is notified and waiting thread will be awaked
/// One could reimplement this method in sub-class
```


<!-- THttpCallArg.md ends here -->
