<!-- TSystem.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 3月 18 14:16:11 2016 (+0800)
;; Last-Updated: 六 8月 13 16:56:12 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->

# TSystem

## class

继承TNamed

```cpp
struct FileStat_t {
   Long_t   fDev;          // device id
   Long_t   fIno;          // inode
   Int_t    fMode;         // protection (combination of EFileModeMask bits)
   Int_t    fUid;          // user id of owner
   Int_t    fGid;          // group id of owner
   Long64_t fSize;         // total size in bytes
   Long_t   fMtime;        // modification date
   Bool_t   fIsLink;       // symbolic link
   TString  fUrl;          // end point url of file
   FileStat_t() : fDev(0), fIno(0), fMode(0), fUid(0), fGid(0), fSize(0),
                  fMtime(0), fIsLink(kFALSE), fUrl("") { }
};

struct UserGroup_t {
   Int_t    fUid;          // user id
   Int_t    fGid;          // group id
   TString  fUser;         // user name
   TString  fGroup;        // group name
   TString  fPasswd;       // password
   TString  fRealName;     // user full name
   TString  fShell;        // user preferred shell
   UserGroup_t() : fUid(0), fGid(0), fUser(), fGroup(), fPasswd(),
                   fRealName (), fShell() { }
};

struct SysInfo_t {
   TString   fOS;          // OS
   TString   fModel;       // computer model
   TString   fCpuType;     // type of cpu
   Int_t     fCpus;        // number of cpus
   Int_t     fCpuSpeed;    // cpu speed in MHz
   Int_t     fBusSpeed;    // bus speed in MHz
   Int_t     fL2Cache;     // level 2 cache size in KB
   Int_t     fPhysRam;     // physical RAM in MB
   SysInfo_t() : fOS(), fModel(), fCpuType(), fCpus(0), fCpuSpeed(0),
                 fBusSpeed(0), fL2Cache(0), fPhysRam(0) { }
   virtual ~SysInfo_t() { }
   ClassDef(SysInfo_t, 1); // System information - OS, CPU, RAM.
};

struct CpuInfo_t {
   Float_t   fLoad1m;      // cpu load average over 1 m
   Float_t   fLoad5m;      // cpu load average over 5 m
   Float_t   fLoad15m;     // cpu load average over 15 m
   Float_t   fUser;        // cpu user load in percentage
   Float_t   fSys;         // cpu sys load in percentage
   Float_t   fTotal;       // cpu user+sys load in percentage
   Float_t   fIdle;        // cpu idle percentage
   CpuInfo_t() : fLoad1m(0), fLoad5m(0), fLoad15m(0),
                 fUser(0), fSys(0), fTotal(0), fIdle(0) { }
   virtual ~CpuInfo_t() { }
   ClassDef(CpuInfo_t, 1); // CPU load information.
};

struct MemInfo_t {
   Int_t     fMemTotal;    // total RAM in MB
   Int_t     fMemUsed;     // used RAM in MB
   Int_t     fMemFree;     // free RAM in MB
   Int_t     fSwapTotal;   // total swap in MB
   Int_t     fSwapUsed;    // used swap in MB
   Int_t     fSwapFree;    // free swap in MB
   MemInfo_t() : fMemTotal(0), fMemUsed(0), fMemFree(0),
                 fSwapTotal(0), fSwapUsed(0), fSwapFree(0) { }
   virtual ~MemInfo_t() { }
   ClassDef(MemInfo_t, 1); // Memory utilization information.
};

struct ProcInfo_t {
   Float_t   fCpuUser;     // user time used by this process in seconds
   Float_t   fCpuSys;      // system time used by this process in seconds
   Long_t    fMemResident; // resident memory used by this process in KB
   Long_t    fMemVirtual;  // virtual memory used by this process in KB
   ProcInfo_t() : fCpuUser(0), fCpuSys(0), fMemResident(0),
                  fMemVirtual(0) { }
   virtual ~ProcInfo_t() { }
   ClassDef(ProcInfo_t, 1);// System resource usage of given process.
};

struct RedirectHandle_t {
   TString   fFile;        // File where the output was redirected
   TString   fStdOutTty;   // tty associated with stdout, if any (e.g. from ttyname(...))
   TString   fStdErrTty;   // tty associated with stderr, if any (e.g. from ttyname(...))
   Int_t     fStdOutDup;   // Duplicated descriptor for stdout
   Int_t     fStdErrDup;   // Duplicated descriptor for stderr
   Int_t     fReadOffSet;  // Offset where to start reading the file (used by ShowOutput(...))
   RedirectHandle_t(const char *n = 0) : fFile(n), fStdOutTty(), fStdErrTty(), fStdOutDup(-1),
                                         fStdErrDup(-1), fReadOffSet(-1) { }
   void Reset() { fFile = ""; fStdOutTty = ""; fStdErrTty = "";
                  fStdOutDup = -1; fStdErrDup = -1; fReadOffSet = -1; }
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TSystem(const char *name = "Generic", const char *title = "Generic System");
virtual ~TSystem();

//---- Misc
virtual Bool_t          Init();
virtual void            SetProgname(const char *name);
virtual void            SetDisplay();
void                    SetErrorStr(const char *errstr);
const char             *GetErrorStr() const { return GetLastErrorString(); }
virtual const char     *GetError();
void                    RemoveOnExit(TObject *obj);
virtual const char     *HostName();
virtual void            NotifyApplicationCreated();

static Int_t            GetErrno();
static void             ResetErrno();
void                    Beep(Int_t freq=-1, Int_t duration=-1, Bool_t setDefault=kFALSE);
void                    GetBeepDefaults(Int_t &freq, Int_t &duration) const { freq = fBeepFreq; duration = fBeepDuration; }

//---- EventLoop
virtual void            Run();
virtual Bool_t          ProcessEvents();
virtual void            DispatchOneEvent(Bool_t pendingOnly = kFALSE);
virtual void            ExitLoop();
Bool_t                  InControl() const { return fInControl; }
virtual void            InnerLoop();
virtual Int_t           Select(TList *active, Long_t timeout);
virtual Int_t           Select(TFileHandler *fh, Long_t timeout);

//---- Handling of system events
virtual void            AddSignalHandler(TSignalHandler *sh);
virtual TSignalHandler *RemoveSignalHandler(TSignalHandler *sh);
virtual void            ResetSignal(ESignals sig, Bool_t reset = kTRUE);
virtual void            ResetSignals();
virtual void            IgnoreSignal(ESignals sig, Bool_t ignore = kTRUE);
virtual void            IgnoreInterrupt(Bool_t ignore = kTRUE);
virtual TSeqCollection *GetListOfSignalHandlers() const { return fSignalHandler; }
virtual void            AddFileHandler(TFileHandler *fh);
virtual TFileHandler   *RemoveFileHandler(TFileHandler *fh);
virtual TSeqCollection *GetListOfFileHandlers() const { return fFileHandler; }
virtual void            AddStdExceptionHandler(TStdExceptionHandler *eh);
virtual TStdExceptionHandler *RemoveStdExceptionHandler(TStdExceptionHandler *eh);
virtual TSeqCollection *GetListOfStdExceptionHandlers() const { return fStdExceptionHandler; }

//---- Floating Point Exceptions Control
virtual Int_t           GetFPEMask();
virtual Int_t           SetFPEMask(Int_t mask = kDefaultMask);

//---- Time & Date
virtual TTime           Now();
virtual TSeqCollection *GetListOfTimers() const { return fTimers; }
virtual void            AddTimer(TTimer *t);
virtual TTimer         *RemoveTimer(TTimer *t);
virtual void            ResetTimer(TTimer *) { }
virtual Long_t          NextTimeOut(Bool_t mode);
virtual void            Sleep(UInt_t milliSec);//程序休眠

//---- Processes
virtual Int_t           Exec(const char *shellcmd);//执行命令
virtual FILE           *OpenPipe(const char *command, const char *mode);
virtual int             ClosePipe(FILE *pipe);
virtual TString         GetFromPipe(const char *command);
virtual void            Exit(int code, Bool_t mode = kTRUE);//退出程序
virtual void            Abort(int code = 0);
virtual int             GetPid();
virtual void            StackTrace();

//---- Directories
virtual int             MakeDirectory(const char *name);//新建文件夹
virtual void           *OpenDirectory(const char *name);//打开文件夹
virtual void            FreeDirectory(void *dirp);
virtual const char     *GetDirEntry(void *dirp);
virtual void           *GetDirPtr() const { return 0; }
virtual Bool_t          ChangeDirectory(const char *path);//进入该目录
virtual const char     *WorkingDirectory();
virtual const char     *HomeDirectory(const char *userName = 0);
virtual int             mkdir(const char *name, Bool_t recursive = kFALSE);
Bool_t                  cd(const char *path) { return ChangeDirectory(path); }//进入该目录
const char             *pwd() { return WorkingDirectory(); }//获得当前路径
virtual const char     *TempDirectory() const;
virtual FILE           *TempFileName(TString &base, const char *dir = 0);

//---- Paths & Files
virtual const char     *BaseName(const char *pathname);
virtual const char     *DirName(const char *pathname);
virtual char           *ConcatFileName(const char *dir, const char *name);
virtual Bool_t          IsAbsoluteFileName(const char *dir);
virtual Bool_t          IsFileInIncludePath(const char *name, char **fullpath = 0);
virtual const char     *PrependPathName(const char *dir, TString& name);
virtual Bool_t          ExpandPathName(TString &path);
virtual char           *ExpandPathName(const char *path);
virtual Bool_t          AccessPathName(const char *path, EAccessMode mode = kFileExists);//判断该文件是否存在、是否可写、是否可读
virtual Bool_t          IsPathLocal(const char *path);
virtual int             CopyFile(const char *from, const char *to, Bool_t overwrite = kFALSE);//复制文件
virtual int             Rename(const char *from, const char *to);//文件、文件夹重命名
virtual int             Link(const char *from, const char *to);
virtual int             Symlink(const char *from, const char *to);
virtual int             Unlink(const char *name);
int                     GetPathInfo(const char *path, Long_t *id, Long_t *size, Long_t *flags, Long_t *modtime);
int                     GetPathInfo(const char *path, Long_t *id, Long64_t *size, Long_t *flags, Long_t *modtime);
virtual int             GetPathInfo(const char *path, FileStat_t &buf);//获取该文件信息
virtual int             GetFsInfo(const char *path, Long_t *id, Long_t *bsize, Long_t *blocks, Long_t *bfree);
virtual int             Chmod(const char *file, UInt_t mode);
virtual int             Umask(Int_t mask);
virtual int             Utime(const char *file, Long_t modtime, Long_t actime);
virtual const char     *UnixPathName(const char *unixpathname);//当前文件所在目录
virtual const char     *FindFile(const char *search, TString& file, EAccessMode mode = kFileExists);
virtual char           *Which(const char *search, const char *file, EAccessMode mode = kFileExists);//寻找可执行文件所在位置
virtual TList          *GetVolumes(Option_t *) const { return 0; }

//---- Users & Groups
virtual Int_t           GetUid(const char *user = 0);
virtual Int_t           GetGid(const char *group = 0);
virtual Int_t           GetEffectiveUid();
virtual Int_t           GetEffectiveGid();
virtual UserGroup_t    *GetUserInfo(Int_t uid);
virtual UserGroup_t    *GetUserInfo(const char *user = 0);
virtual UserGroup_t    *GetGroupInfo(Int_t gid);
virtual UserGroup_t    *GetGroupInfo(const char *group = 0);

//---- Environment Manipulation
virtual void            Setenv(const char *name, const char *value);
virtual void            Unsetenv(const char *name);
virtual const char     *Getenv(const char *env);//获取环境变量对应的路径

//---- System Logging
virtual void            Openlog(const char *name, Int_t options, ELogFacility facility);
virtual void            Syslog(ELogLevel level, const char *mess);
virtual void            Closelog();

//---- Standard Output redirection
virtual Int_t           RedirectOutput(const char *name, const char *mode = "a", RedirectHandle_t *h = 0);
virtual void            ShowOutput(RedirectHandle_t *h);

//---- Dynamic Loading
virtual void            AddDynamicPath(const char *pathname);
virtual const char     *GetDynamicPath();
virtual void            SetDynamicPath(const char *pathname);
char                   *DynamicPathName(const char *lib, Bool_t quiet = kFALSE);
virtual const char     *FindDynamicLibrary(TString& lib, Bool_t quiet = kFALSE);
virtual Func_t          DynFindSymbol(const char *module, const char *entry);
virtual int             Load(const char *module, const char *entry = "", Bool_t system = kFALSE);//加载文件、链接库等
virtual void            Unload(const char *module);
virtual void            ListSymbols(const char *module, const char *re = "");
virtual void            ListLibraries(const char *regexp = "");
virtual const char     *GetLibraries(const char *regexp = "",
				     const char *option = "",
				     Bool_t isRegexp = kTRUE);

//---- RPC
virtual TInetAddress    GetHostByName(const char *server);
virtual TInetAddress    GetPeerName(int sock);
virtual TInetAddress    GetSockName(int sock);
virtual int             GetServiceByName(const char *service);
virtual char           *GetServiceByPort(int port);
virtual int             OpenConnection(const char *server, int port, int tcpwindowsize = -1, const char *protocol = "tcp");
virtual int             AnnounceTcpService(int port, Bool_t reuse, int backlog, int tcpwindowsize = -1);
virtual int             AnnounceUdpService(int port, int backlog);
virtual int             AnnounceUnixService(int port, int backlog);
virtual int             AnnounceUnixService(const char *sockpath, int backlog);
virtual int             AcceptConnection(int sock);
virtual void            CloseConnection(int sock, Bool_t force = kFALSE);
virtual int             RecvRaw(int sock, void *buffer, int length, int flag);
virtual int             SendRaw(int sock, const void *buffer, int length, int flag);
virtual int             RecvBuf(int sock, void *buffer, int length);
virtual int             SendBuf(int sock, const void *buffer, int length);
virtual int             SetSockOpt(int sock, int kind, int val);
virtual int             GetSockOpt(int sock, int kind, int *val);

//---- System, CPU and Memory info
virtual int             GetSysInfo(SysInfo_t *info) const;
virtual int             GetCpuInfo(CpuInfo_t *info, Int_t sampleTime = 1000) const;//获取CPU信息
virtual int             GetMemInfo(MemInfo_t *info) const;//获取内存使用情况信息
virtual int             GetProcInfo(ProcInfo_t *info) const;

//---- ACLiC (Automatic Compiler of Shared Library for CINT)
virtual void            AddIncludePath(const char *includePath);
virtual void            AddLinkedLibs(const char *linkedLib);
virtual int             CompileMacro(const char *filename, Option_t *opt="", const char* library_name = "", const char* build_dir = "", UInt_t dirmode = 0);//执行宏文件？？？
virtual Int_t           GetAclicProperties() const;
virtual const char     *GetBuildArch() const;
virtual const char     *GetBuildCompiler() const;
virtual const char     *GetBuildCompilerVersion() const;
virtual const char     *GetBuildNode() const;
virtual const char     *GetBuildDir() const;
virtual const char     *GetFlagsDebug() const;
virtual const char     *GetFlagsOpt() const;
virtual const char     *GetIncludePath();
virtual const char     *GetLinkedLibs() const;
virtual const char     *GetLinkdefSuffix() const;
virtual EAclicMode      GetAclicMode() const;
virtual const char     *GetMakeExe() const;
virtual const char     *GetMakeSharedLib() const;
virtual const char     *GetSoExt() const;
virtual const char     *GetObjExt() const;
virtual void            SetBuildDir(const char* build_dir, Bool_t isflat = kFALSE);
virtual void            SetFlagsDebug(const char *);
virtual void            SetFlagsOpt(const char *);
virtual void            SetIncludePath(const char *includePath);
virtual void            SetMakeExe(const char *directives);
virtual void            SetAclicMode(EAclicMode mode);
virtual void            SetMakeSharedLib(const char *directives);
virtual void            SetLinkedLibs(const char *linkedLibs);
virtual void            SetLinkdefSuffix(const char *suffix);
virtual void            SetSoExt(const char *soExt);
virtual void            SetObjExt(const char *objExt);
virtual TString         SplitAclicMode(const char *filename, TString &mode, TString &args, TString &io) const;
virtual void            CleanCompiledMacros();
```

## code



<!-- TSystem.md ends here -->
