<!-- TCivetweb.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 6月  5 23:47:26 2018 (+0800)
;; Last-Updated: 二 6月  5 23:50:26 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TCivetweb

TCivetweb : public THttpEngine

```cpp
// http server implementation, based on civetweb embedded server        //
// It is default kind of engine, created for THttpServer                //
// Currently v1.8 from https://github.com/civetweb/civetweb is used     //
//                                                                      //
// Following additional options can be specified:                       //
//    top=foldername - name of top folder, seen in the browser          //
//    thrds=N - use N threads to run civetweb server (default 5)        //
//    auth_file - global authentication file                            //
//    auth_domain - domain name, used for authentication                //
//                                                                      //
// Example:                                                             //
//    new THttpServer("http:8080?top=MyApp&thrds=3");                   //
//                                                                      //
// Authentication:                                                      //
//    When auth_file and auth_domain parameters are specified, access   //
//    to running http server will be possible only after user           //
//    authentication, using so-call digest method. To generate          //
//    authentication file, htdigest routine should be used:             //
//                                                                      //
//        [shell] htdigest -c .htdigest domain_name user                //
//                                                                      //
//    When creating server, parameters should be:                       //
//                                                                      //
//       new THttpServer("http:8080?auth_file=.htdigets&auth_domain=domain_name");  //
//  
```



## class

```cpp
   TCivetweb();
   virtual ~TCivetweb();

   virtual Bool_t Create(const char *args);
/// Creates embedded civetweb server
/// As main argument, http port should be specified like "8090".
/// Or one can provide combination of ipaddress and portnumber like 127.0.0.1:8090
/// Extra parameters like in URL string could be specified after '?' mark:
///    thrds=N   - there N is number of threads used by the civetweb (default is 5)
///    top=name  - configure top name, visible in the web browser
///    auth_file=filename  - authentication file name, created with htdigets utility
///    auth_domain=domain   - authentication domain
///    websocket_timeout=tm  - set web sockets timeout in seconds (default 300)
///    loopback  - bind specified port to loopback 127.0.0.1 address
///    debug   - enable debug mode, server always returns html page with request info
///    log=filename  - configure civetweb log file

   const char *GetTopName() const { return fTopName.Data(); }

   Bool_t IsDebugMode() const { return fDebug; }

   Int_t ProcessLog(const char *message);
```





<!-- TCivetweb.md ends here -->
