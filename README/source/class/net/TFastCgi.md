<!-- TFastCgi.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 6月  5 23:50:42 2018 (+0800)
;; Last-Updated: 二 6月  5 23:52:42 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TFastCgi

TFastCgi : public THttpEngine

```cpp
// http engine implementation, based on fastcgi package                 //
// Allows to redirect http requests from normal web server like         //
// Apache or lighttpd                                                   //
//                                                                      //
// Configuration example for lighttpd                                   //
//                                                                      //
// server.modules += ( "mod_fastcgi" )                                  //
// fastcgi.server = (                                                   //
//   "/remote_scripts/" =>                                              //
//     (( "host" => "192.168.1.11",                                     //
//        "port" => 9000,                                               //
//        "check-local" => "disable",                                   //
//        "docroot" => "/"                                              //
//     ))                                                               //
// )                                                                    //
//                                                                      //
// When creating THttpServer, one should specify:                       //
//                                                                      //
//  THttpServer* serv = new THttpServer("fastcgi:9000");                //
//                                                                      //
// In this case, requests to lighttpd server will be                    //
// redirected to ROOT session. Like:                                    //
//    http://lighttpdhost/remote_scripts/root.cgi/                      //
//                                                                      //
// Following additional options can be specified                        //
//    top=foldername - name of top folder, seen in the browser          //
//    debug=1 - run fastcgi server in debug mode                        //
// Example:                                                             //
//    serv->CreateEngine("fastcgi:9000?top=fastcgiserver");             //
```

## class

```cpp
   TFastCgi();
   virtual ~TFastCgi();

   Int_t GetSocket() const { return fSocket; }

   virtual Bool_t Create(const char *args);
/// initializes fastcgi variables and start thread,
/// which will process incoming http requests

   static void *run_func(void *);
```

<!-- TFastCgi.md ends here -->
