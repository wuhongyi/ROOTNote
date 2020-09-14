<!-- TSystem.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 3月 18 14:16:11 2016 (+0800)
;; Last-Updated: 六 5月  6 19:12:36 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 7
;; URL: http://wuhongyi.cn -->

# TSystem

继承TNamed

Abstract base class defining a generic interface to the underlying Operating System.

```cpp
R__EXTERN TSystem *gSystem;
R__EXTERN TFileHandler *gXDisplay;  // Display server (X11) input event handler
```


## class

```cpp
enum EAccessMode {
   kFileExists        = 0,
   kExecutePermission = 1,
   kWritePermission   = 2,
   kReadPermission    = 4
};

enum ELogOption {
   kLogPid            = 0x01,
   kLogCons           = 0x02
};

enum ELogLevel {
   kLogEmerg          = 0,
   kLogAlert          = 1,
   kLogCrit           = 2,
   kLogErr            = 3,
   kLogWarning        = 4,
   kLogNotice         = 5,
   kLogInfo           = 6,
   kLogDebug          = 7
};

enum ELogFacility {
   kLogLocal0,
   kLogLocal1,
   kLogLocal2,
   kLogLocal3,
   kLogLocal4,
   kLogLocal5,
   kLogLocal6,
   kLogLocal7
};

enum EFpeMask {
   kNoneMask         = 0x00,
   kInvalid          = 0x01,  // Invalid argument
   kDivByZero        = 0x02,  // Division by zero
   kOverflow         = 0x04,  // Overflow
   kUnderflow        = 0x08,  // Underflow
   kInexact          = 0x10,  // Inexact
   kDefaultMask      = 0x07,
   kAllMask          = 0x1F
};

enum EFileModeMask {
   kS_IFMT   = 0170000,   // bitmask for the file type bitfields
   kS_IFSOCK = 0140000,   // socket
   kS_IFLNK  = 0120000,   // symbolic link
   kS_IFOFF  = 0110000,   // offline file
   kS_IFREG  = 0100000,   // regular file
   kS_IFBLK  = 0060000,   // block device
   kS_IFDIR  = 0040000,   // directory
   kS_IFCHR  = 0020000,   // character device
   kS_IFIFO  = 0010000,   // fifo
   kS_ISUID  = 0004000,   // set UID bit
   kS_ISGID  = 0002000,   // set GID bit
   kS_ISVTX  = 0001000,   // sticky bit
   kS_IRWXU  = 00700,     // mask for file owner permissions
   kS_IRUSR  = 00400,     // owner has read permission
   kS_IWUSR  = 00200,     // owner has write permission
   kS_IXUSR  = 00100,     // owner has execute permission
   kS_IRWXG  = 00070,     // mask for group permissions
   kS_IRGRP  = 00040,     // group has read permission
   kS_IWGRP  = 00020,     // group has write permission
   kS_IXGRP  = 00010,     // group has execute permission
   kS_IRWXO  = 00007,     // mask for permissions for others (not in group)
   kS_IROTH  = 00004,     // others have read permission
   kS_IWOTH  = 00002,     // others have write permisson
   kS_IXOTH  = 00001      // others have execute permission
};

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
```
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

**TProcessEventTimer 继承 TTimer**

```cpp
// Asynchronous timer used for processing pending GUI and timer events  
// every delay ms. Call in a tight computing loop                       
// TProcessEventTimer::ProcessEvent(). If the timer did timeout this    
// call will process the pending events and return kTRUE if the         
// TROOT::IsInterrupted() flag is set (can be done by hitting key in    
// canvas or selecting canvas menu item View/Interrupt.                 

   TProcessEventTimer(Long_t delay);
/// Create async event processor timer. Delay is in milliseconds.

   Bool_t Notify() { return kTRUE; }
   Bool_t ProcessEvents();
/// Process events if timer did time out. Returns kTRUE if interrupt
/// flag is set (by hitting a key in the canvas or selecting the
/// Interrupt menu item in canvas or some other action).
```

**TSystem**
```cpp
TSystem(const char *name = "Generic", const char *title = "Generic System");/// Create a new OS interface.
virtual ~TSystem();/// Delete the OS interface.

//---- Misc
virtual Bool_t          Init();/// Initialize the OS interface.
virtual void            SetProgname(const char *name);
/// Set the application name (from command line, argv[0]) and copy it in
/// gProgName.

virtual void            SetDisplay();/// Set DISPLAY environment variable based on utmp entry. Only for UNIX.
void                    SetErrorStr(const char *errstr);/// Set the system error string. This string will be used by GetError().
/// To be used in case one does not want or can use the system error
/// string (e.g. because error is generated by a third party POSIX like
/// library that does not use standard errno).
const char             *GetErrorStr() const { return GetLastErrorString(); }
virtual const char     *GetError();/// Return system error string.
void                    RemoveOnExit(TObject *obj);/// Objects that should be deleted on exit of the OS interface.
virtual const char     *HostName();/// Return the system's host name.
virtual void            NotifyApplicationCreated();/// Hook to tell TSystem that the TApplication object has been created.

static Int_t            GetErrno();/// Static function returning system error number.
static void             ResetErrno();/// Static function resetting system error number.
void                    Beep(Int_t freq=-1, Int_t duration=-1, Bool_t setDefault=kFALSE);
void                    GetBeepDefaults(Int_t &freq, Int_t &duration) const { freq = fBeepFreq; duration = fBeepDuration; }
/// Beep for duration milliseconds with a tone of frequency freq.
/// Defaults to printing the `\a` character to stdout.
/// If freq or duration is <0 respectively, use default value.
/// If setDefault is set, only set the frequency and duration as
/// new defaults, but don't beep.
/// If default freq or duration is <0, never beep (silence)

//---- EventLoop
virtual void            Run();/// System event loop.
virtual Bool_t          ProcessEvents();
/// Process pending events (GUI, timers, sockets). Returns the result of
/// TROOT::IsInterrupted(). The interrupt flag (TROOT::SetInterrupt())
/// can be set during the handling of the events. This mechanism allows
/// macros running in tight calculating loops to be interrupted by some
/// GUI event (depending on the interval with which this method is
/// called). For example hitting ctrl-c in a canvas will set the
/// interrupt flag.

virtual void            DispatchOneEvent(Bool_t pendingOnly = kFALSE);/// Dispatch a single event.
virtual void            ExitLoop();/// Exit from event loop.
Bool_t                  InControl() const { return fInControl; }
virtual void            InnerLoop();/// Inner event loop.
virtual Int_t           Select(TList *active, Long_t timeout);/// Select on active file descriptors (called by TMonitor).
virtual Int_t           Select(TFileHandler *fh, Long_t timeout);/// Select on active file descriptors (called by TMonitor).

//---- Handling of system events
virtual void            AddSignalHandler(TSignalHandler *sh);
/// Add a signal handler to list of system signal handlers. Only adds
/// the handler if it is not already in the list of signal handlers.

virtual TSignalHandler *RemoveSignalHandler(TSignalHandler *sh);
/// Remove a file handler from the list of file handlers. Returns
/// the handler or 0 if the handler was not in the list of file handlers.

virtual void            ResetSignal(ESignals sig, Bool_t reset = kTRUE);
/// If reset is true reset the signal handler for the specified signal
/// to the default handler, else restore previous behaviour.

virtual void            ResetSignals();/// Reset signals handlers to previous behaviour.
virtual void            IgnoreSignal(ESignals sig, Bool_t ignore = kTRUE);
/// If ignore is true ignore the specified signal, else restore previous
/// behaviour.

virtual void            IgnoreInterrupt(Bool_t ignore = kTRUE);
/// If ignore is true ignore the interrupt signal, else restore previous
/// behaviour. Typically call ignore interrupt before writing to disk.

virtual TSeqCollection *GetListOfSignalHandlers() const { return fSignalHandler; }
virtual void            AddFileHandler(TFileHandler *fh);
/// Add a file handler to the list of system file handlers. Only adds
/// the handler if it is not already in the list of file handlers.

virtual TFileHandler   *RemoveFileHandler(TFileHandler *fh);
/// Remove a file handler from the list of file handlers. Returns
/// the handler or 0 if the handler was not in the list of file handlers.

virtual TSeqCollection *GetListOfFileHandlers() const { return fFileHandler; }
virtual void            AddStdExceptionHandler(TStdExceptionHandler *eh);
/// Add an exception handler to list of system exception handlers. Only adds
/// the handler if it is not already in the list of exception handlers.

virtual TStdExceptionHandler *RemoveStdExceptionHandler(TStdExceptionHandler *eh);
/// Remove an exception handler from list of exception handlers. Returns
/// the handler or 0 if the handler was not in the list of exception handlers.

virtual TSeqCollection *GetListOfStdExceptionHandlers() const { return fStdExceptionHandler; }

//---- Floating Point Exceptions Control
virtual Int_t           GetFPEMask();/// Return the bitmap of conditions that trigger a floating point exception.
virtual Int_t           SetFPEMask(Int_t mask = kDefaultMask);
/// Set which conditions trigger a floating point exception.
/// Return the previous set of conditions.

//---- Time & Date
virtual TTime           Now();/// Get current time in milliseconds since 0:00 Jan 1 1995.
virtual TSeqCollection *GetListOfTimers() const { return fTimers; }
virtual void            AddTimer(TTimer *t);/// Add timer to list of system timers.
virtual TTimer         *RemoveTimer(TTimer *t);
/// Remove timer from list of system timers. Returns removed timer or 0
/// if timer was not active.

virtual void            ResetTimer(TTimer *) { }
virtual Long_t          NextTimeOut(Bool_t mode);
/// Time when next timer of mode (synchronous=kTRUE or
/// asynchronous=kFALSE) will time-out (in ms).

virtual void            Sleep(UInt_t milliSec);//程序休眠   Sleep milliSec milli seconds.

//---- Processes
virtual Int_t           Exec(const char *shellcmd);//执行命令   Execute a command.
virtual FILE           *OpenPipe(const char *command, const char *mode);/// Open a pipe.
virtual int             ClosePipe(FILE *pipe);/// Close the pipe.
virtual TString         GetFromPipe(const char *command);/// Execute command and return output in TString.
virtual void            Exit(int code, Bool_t mode = kTRUE);//退出程序  Exit the application.
virtual void            Abort(int code = 0);/// Abort the application.
virtual int             GetPid();/// Get process id.
virtual void            StackTrace();/// Print a stack trace.

//---- Directories
virtual int             MakeDirectory(const char *name);//新建文件夹
/// Make a directory. Returns 0 in case of success and
/// -1 if the directory could not be created (either already exists or
/// illegal path name).

virtual void           *OpenDirectory(const char *name);//打开文件夹  Open a directory. Returns 0 if directory does not exist.
virtual void            FreeDirectory(void *dirp);/// Free a directory.
virtual const char     *GetDirEntry(void *dirp);/// Get a directory entry. Returns 0 if no more entries.
virtual void           *GetDirPtr() const { return 0; }
virtual Bool_t          ChangeDirectory(const char *path);//进入该目录   Change directory.
virtual const char     *WorkingDirectory();/// Return working directory.
virtual const char     *HomeDirectory(const char *userName = 0);/// Return the user's home directory.
virtual int             mkdir(const char *name, Bool_t recursive = kFALSE);
/// Make a file system directory. Returns 0 in case of success and
/// -1 if the directory could not be created (either already exists or
/// illegal path name).
/// If 'recursive' is true, makes parent directories as needed.

Bool_t                  cd(const char *path) { return ChangeDirectory(path); }//进入该目录
const char             *pwd() { return WorkingDirectory(); }//获得当前路径
virtual const char     *TempDirectory() const;
/// Return a user configured or systemwide directory to create
/// temporary files in.

virtual FILE           *TempFileName(TString &base, const char *dir = 0);
/// Create a secure temporary file by appending a unique
/// 6 letter string to base. The file will be created in
/// a standard (system) directory or in the directory
/// provided in dir. The full filename is returned in base
/// and a filepointer is returned for safely writing to the file
/// (this avoids certain security problems). Returns 0 in case
/// of error.

//---- Paths & Files
virtual const char     *BaseName(const char *pathname);/// Base name of a file name. Base name of /user/root is root.
virtual const char     *DirName(const char *pathname);
/// Return the directory name in pathname. DirName of /user/root is /user.
/// In case no dirname is specified "." is returned.

virtual char           *ConcatFileName(const char *dir, const char *name);/// Concatenate a directory and a file name. User must delete returned string.
virtual Bool_t          IsAbsoluteFileName(const char *dir);/// Return true if dir is an absolute pathname.
virtual Bool_t          IsFileInIncludePath(const char *name, char **fullpath = 0);
/// Return true if 'name' is a file that can be found in the ROOT include
/// path or the current directory.
/// If 'name' contains any ACLiC style information (e.g. trailing +[+][g|O]),
/// it will be striped off 'name'.
/// If fullpath is != 0, the full path to the file is returned in *fullpath,
/// which must be deleted by the caller.

virtual const char     *PrependPathName(const char *dir, TString& name);/// Concatenate a directory and a file name.
virtual Bool_t          ExpandPathName(TString &path);
/// Expand a pathname getting rid of special shell characters like ~.$, etc.
/// For Unix/Win32 compatibility use $(XXX) instead of $XXX when using
/// environment variables in a pathname. If compatibility is not an issue
/// you can use on Unix directly $XXX.

virtual char           *ExpandPathName(const char *path);
/// Expand a pathname getting rid of special shell characters like ~.$, etc.
/// For Unix/Win32 compatibility use $(XXX) instead of $XXX when using
/// environment variables in a pathname. If compatibility is not an issue
/// you can use on Unix directly $XXX. The user must delete returned string.

virtual Bool_t          AccessPathName(const char *path, EAccessMode mode = kFileExists);//判断该文件是否存在、是否可写、是否可读
/// Returns FALSE if one can access a file using the specified access mode.
/// The file name must not contain any special shell characters line ~ or $,
/// in those cases first call ExpandPathName().
/// Attention, bizarre convention of return value!!

virtual Bool_t          IsPathLocal(const char *path);
/// Returns TRUE if the url in 'path' points to the local file system.
/// This is used to avoid going through the NIC card for local operations.

virtual int             CopyFile(const char *from, const char *to, Bool_t overwrite = kFALSE);//复制文件
/// Copy a file. If overwrite is true and file already exists the
/// file will be overwritten. Returns 0 when successful, -1 in case
/// of file open failure, -2 in case the file already exists and overwrite
/// was false and -3 in case of error during copy.

virtual int             Rename(const char *from, const char *to);//文件、文件夹重命名  Rename a file.
virtual int             Link(const char *from, const char *to);/// Create a link from file1 to file2.
virtual int             Symlink(const char *from, const char *to);/// Create a symbolic link from file1 to file2.
virtual int             Unlink(const char *name);/// Unlink, i.e. remove, a file.
int                     GetPathInfo(const char *path, Long_t *id, Long_t *size, Long_t *flags, Long_t *modtime);
/// Get info about a file: id, size, flags, modification time.
///  - Id      is (statbuf.st_dev << 24) + statbuf.st_ino
///  - Size    is the file size
///  - Flags   is file type: 0 is regular file, bit 0 set executable,
///                          bit 1 set directory, bit 2 set special file
///                          (socket, fifo, pipe, etc.)
/// Modtime is modification time.
/// The function returns 0 in case of success and 1 if the file could
/// not be stat'ed.

int                     GetPathInfo(const char *path, Long_t *id, Long64_t *size, Long_t *flags, Long_t *modtime);
/// Get info about a file: id, size, flags, modification time.
///  - Id      is (statbuf.st_dev << 24) + statbuf.st_ino
///  - Size    is the file size
///  - Flags   is file type: 0 is regular file, bit 0 set executable,
///                          bit 1 set directory, bit 2 set special file
///                          (socket, fifo, pipe, etc.)
/// Modtime is modification time.
/// The function returns 0 in case of success and 1 if the file could
/// not be stat'ed.

virtual int             GetPathInfo(const char *path, FileStat_t &buf);//获取该文件信息
/// Get info about a file. Info is returned in the form of a FileStat_t
/// structure (see TSystem.h).
/// The function returns 0 in case of success and 1 if the file could
/// not be stat'ed.

virtual int             GetFsInfo(const char *path, Long_t *id, Long_t *bsize, Long_t *blocks, Long_t *bfree);
/// Get info about a file system: fs type, block size, number of blocks,
/// number of free blocks.

virtual int             Chmod(const char *file, UInt_t mode);/// Set the file permission bits. Returns -1 in case or error, 0 otherwise.
virtual int             Umask(Int_t mask);/// Set the process file creation mode mask.
virtual int             Utime(const char *file, Long_t modtime, Long_t actime);
/// Set the a files modification and access times. If actime = 0 it will be
/// set to the modtime. Returns 0 on success and -1 in case of error.

virtual const char     *UnixPathName(const char *unixpathname);//当前文件所在目录
/// Convert from a Unix pathname to a local pathname. E.g. from `/user/root` to `\user\root`.

virtual const char     *FindFile(const char *search, TString& file, EAccessMode mode = kFileExists);
/// Find location of file in a search path. Return value points to TString for
/// compatibility with Which(const char *, const char *, EAccessMode).
/// Returns 0 in case file is not found.

virtual char           *Which(const char *search, const char *file, EAccessMode mode = kFileExists);//寻找可执行文件所在位置
/// Find location of file in a search path. User must delete returned string.
/// Returns 0 in case file is not found.

virtual TList          *GetVolumes(Option_t *) const { return 0; }

//---- Users & Groups
virtual Int_t           GetUid(const char *user = 0);/// Returns the user's id. If user = 0, returns current user's id.
virtual Int_t           GetGid(const char *group = 0);/// Returns the group's id. If group = 0, returns current user's group.
virtual Int_t           GetEffectiveUid();
/// Returns the effective user id. The effective id corresponds to the
/// set id bit on the file being executed.

virtual Int_t           GetEffectiveGid();
/// Returns the effective group id. The effective group id corresponds
/// to the set id bit on the file being executed.

virtual UserGroup_t    *GetUserInfo(Int_t uid);
/// Returns all user info in the UserGroup_t structure. The returned
/// structure must be deleted by the user. In case of error 0 is returned.

virtual UserGroup_t    *GetUserInfo(const char *user = 0);
/// Returns all user info in the UserGroup_t structure. If user = 0, returns
/// current user's id info. The returned structure must be deleted by the
/// user. In case of error 0 is returned.

virtual UserGroup_t    *GetGroupInfo(Int_t gid);
/// Returns all group info in the UserGroup_t structure. The only active
/// fields in the UserGroup_t structure for this call are:
///  - fGid and fGroup
/// The returned structure must be deleted by the user. In case of
/// error 0 is returned.

virtual UserGroup_t    *GetGroupInfo(const char *group = 0);
/// Returns all group info in the UserGroup_t structure. The only active
/// fields in the UserGroup_t structure for this call are:
///  - fGid and fGroup
/// If group = 0, returns current user's group. The returned structure
/// must be deleted by the user. In case of error 0 is returned.

//---- Environment Manipulation
virtual void            Setenv(const char *name, const char *value);/// Set environment variable.
virtual void            Unsetenv(const char *name);/// Unset environment variable.
virtual const char     *Getenv(const char *env);//获取环境变量对应的路径
/// Get environment variable.

//---- System Logging
virtual void            Openlog(const char *name, Int_t options, ELogFacility facility);
/// Open connection to system log daemon. For the use of the options and
/// facility see the Unix openlog man page.

virtual void            Syslog(ELogLevel level, const char *mess);
/// Send mess to syslog daemon. Level is the logging level and mess the
/// message that will be written on the log.

virtual void            Closelog();/// Close connection to system log daemon.

//---- Standard Output redirection
virtual Int_t           RedirectOutput(const char *name, const char *mode = "a", RedirectHandle_t *h = 0);
/// Redirect standard output (stdout, stderr) to the specified file.
/// If the file argument is 0 the output is set again to stderr, stdout.
/// The second argument specifies whether the output should be added to the
/// file ("a", default) or the file be truncated before ("w").
/// The implementations of this function save internally the current state into
/// a static structure.
/// The call can be made reentrant by specifying the opaque structure pointed
/// by 'h', which is filled with the relevant information. The handle 'h'
/// obtained on the first call must then be used in any subsequent call,
/// included ShowOutput, to display the redirected output.
/// Returns 0 on success, -1 in case of error.

virtual void            ShowOutput(RedirectHandle_t *h);
/// Display the content associated with the redirection described by the
/// opaque handle 'h'.

//---- Dynamic Loading
virtual void            AddDynamicPath(const char *pathname);/// Add a new directory to the dynamic path.
virtual const char     *GetDynamicPath();/// Return the dynamic path (used to find shared libraries).
virtual void            SetDynamicPath(const char *pathname);
/// Set the dynamic path to a new value.
/// If the value of 'path' is zero, the dynamic path is reset to its
/// default value.

char                   *DynamicPathName(const char *lib, Bool_t quiet = kFALSE);
/// Find a dynamic library called lib using the system search paths.
/// Appends known extensions if needed. Returned string must be deleted
/// by the user!

virtual const char     *FindDynamicLibrary(TString& lib, Bool_t quiet = kFALSE);
/// Find a dynamic library using the system search paths. lib will be updated
/// to contain the absolute filename if found. Returns lib if found, or NULL
/// if a library called lib was not found.
/// This function does not open the library.

virtual Func_t          DynFindSymbol(const char *module, const char *entry);
/// Find specific entry point in specified library. Specify "*" for lib
/// to search in all libraries.

virtual int             Load(const char *module, const char *entry = "", Bool_t system = kFALSE);//加载文件、链接库等
/// Load a shared library. Returns 0 on successful loading, 1 in
/// case lib was already loaded, -1 in case lib does not exist
/// or in case of error and -2 in case of version mismatch.
/// When entry is specified the loaded lib is
/// searched for this entry point (return -1 when entry does not exist,
/// 0 otherwise). When the system flag is kTRUE, the library is considered
/// a permanent system library that should not be unloaded during the
/// course of the session.

virtual void            Unload(const char *module);/// Unload a shared library.
virtual void            ListSymbols(const char *module, const char *re = "");/// List symbols in a shared library.
virtual void            ListLibraries(const char *regexp = "");
/// List all loaded shared libraries. Regexp is a wildcard expression,
/// see TRegexp::MakeWildcard.

virtual const char     *GetLibraries(const char *regexp = "",
				     const char *option = "",
				     Bool_t isRegexp = kTRUE);
/// Return a space separated list of loaded shared libraries.
/// Regexp is a wildcard expression, see TRegexp::MakeWildcard.
/// This list is of a format suitable for a linker, i.e it may contain
/// -Lpathname and/or -lNameOfLib.
/// Option can be any of:
///  - S: shared libraries loaded at the start of the executable, because
///       they were specified on the link line.
///  - D: shared libraries dynamically loaded after the start of the program.
/// For MacOS only:
///  - L: list the .dylib rather than the .so (this is intended for linking)
///       This options is not the default


//---- RPC
virtual TInetAddress    GetHostByName(const char *server);/// Get Internet Protocol (IP) address of host.
virtual TInetAddress    GetPeerName(int sock);/// Get Internet Protocol (IP) address of remote host and port #.
virtual TInetAddress    GetSockName(int sock);/// Get Internet Protocol (IP) address of host and port #.
virtual int             GetServiceByName(const char *service);/// Get port # of internet service.
virtual char           *GetServiceByPort(int port);/// Get name of internet service.
virtual int             OpenConnection(const char *server, int port, int tcpwindowsize = -1, const char *protocol = "tcp");/// Open a connection to another host.
virtual int             AnnounceTcpService(int port, Bool_t reuse, int backlog, int tcpwindowsize = -1);/// Announce TCP/IP service.
virtual int             AnnounceUdpService(int port, int backlog);/// Announce UDP service.
virtual int             AnnounceUnixService(int port, int backlog);/// Announce unix domain service.
virtual int             AnnounceUnixService(const char *sockpath, int backlog);/// Announce unix domain service.
virtual int             AcceptConnection(int sock);/// Accept a connection.
virtual void            CloseConnection(int sock, Bool_t force = kFALSE);/// Close socket connection.
virtual int             RecvRaw(int sock, void *buffer, int length, int flag);
/// Receive exactly length bytes into buffer. Use opt to receive out-of-band
/// data or to have a peek at what is in the buffer (see TSocket).

virtual int             SendRaw(int sock, const void *buffer, int length, int flag);
/// Send exactly length bytes from buffer. Use opt to send out-of-band
/// data (see TSocket).

virtual int             RecvBuf(int sock, void *buffer, int length);/// Receive a buffer headed by a length indicator.
virtual int             SendBuf(int sock, const void *buffer, int length);/// Send a buffer headed by a length indicator.
virtual int             SetSockOpt(int sock, int kind, int val);/// Get socket option.
virtual int             GetSockOpt(int sock, int kind, int *val);/// Get socket option.

//---- System, CPU and Memory info
virtual int             GetSysInfo(SysInfo_t *info) const;
/// Returns static system info, like OS type, CPU type, number of CPUs
/// RAM size, etc into the SysInfo_t structure. Returns -1 in case of error,
/// 0 otherwise.

virtual int             GetCpuInfo(CpuInfo_t *info, Int_t sampleTime = 1000) const;//获取CPU信息
/// Returns cpu load average and load info into the CpuInfo_t structure.
/// Returns -1 in case of error, 0 otherwise. Use sampleTime to set the
/// interval over which the CPU load will be measured, in ms (default 1000).

virtual int             GetMemInfo(MemInfo_t *info) const;//获取内存使用情况信息
/// Returns ram and swap memory usage info into the MemInfo_t structure.
/// Returns -1 in case of error, 0 otherwise.

virtual int             GetProcInfo(ProcInfo_t *info) const;
/// Returns ram and swap memory usage info into the MemInfo_t structure.
/// Returns -1 in case of error, 0 otherwise.


//---- ACLiC (Automatic Compiler of Shared Library for CINT)
virtual void            AddIncludePath(const char *includePath);/// Add includePath to the already set include path.
virtual void            AddLinkedLibs(const char *linkedLib);/// Add linkedLib to already set linked libs.
virtual int             CompileMacro(const char *filename, Option_t *opt="", const char* library_name = "", const char* build_dir = "", UInt_t dirmode = 0);//执行宏文件？？？
/// This method compiles and loads a shared library containing
/// the code from the file "filename".
/// The return value is true (1) in case of success and false (0)
/// in case of error.
/// The possible options are:
///    - k : keep the shared library after the session end.
///    - f : force recompilation.
///    - g : compile with debug symbol
///    - O : optimized the code
///    - c : compile only, do not attempt to load the library.
///    - s : silence all informational output
///    - v : output all information output
///    - d : debug ACLiC, keep all the output files.
///    - - : if buildir is set, use a flat structure (see buildir below)
/// If library_specified is specified, CompileMacro generates the file
/// "library_specified".soext where soext is the shared library extension for
/// the current platform.
/// If build_dir is specified, it is used as an alternative 'root' for the
/// generation of the shared library.  The library is stored in a sub-directories
/// of 'build_dir' including the full pathname of the script unless a flat
/// directory structure is requested ('-' option).  With the '-' option the libraries
/// are created directly in the directory 'build_dir'; in particular this means that
/// 2 scripts with the same name in different source directory will over-write each
/// other's library.
/// See also TSystem::SetBuildDir.
/// If dirmode is not zero and we need to create the target directory, the
/// file mode bit will be change to 'dirmode' using chmod.
/// If library_specified is not specified, CompileMacro generate a default name
/// for library by taking the name of the file "filename" but replacing the
/// dot before the extension by an underscore and by adding the shared
/// library extension for the current platform.
/// For example on most platform, hsimple.cxx will generate hsimple_cxx.so
/// It uses the directive fMakeSharedLibs to create a shared library.
/// If loading the shared library fails, it tries to output a list of missing
/// symbols by creating an executable (on some platforms like OSF, this does
/// not HAVE to be an executable) containing the script. It uses the
/// directive fMakeExe to do so.
/// For both directives, before passing them to TSystem::Exec, it expands the
/// variables $SourceFiles, $SharedLib, $LibName, $IncludePath, $LinkedLibs,
/// $DepLibs, $ExeName and $ObjectFiles. See SetMakeSharedLib() for more
/// information on those variables.
/// This method is used to implement the following feature:
/// Synopsis:
/// The purpose of this addition is to allow the user to use an external
/// compiler to create a shared library from its C++ macro (scripts).
/// Currently in order to execute a script, a user has to type at the root
/// prompt
///  .X myfunc.C(arg1,arg2)
/// We allow them to type:
///  .X myfunc.C++(arg1,arg2)
/// or
///  .X myfunc.C+(arg1,arg2)
/// In which case an external compiler will be called to create a shared
/// library.  This shared library will then be loaded and the function
/// myfunc will be called with the two arguments.  With '++' the shared library
/// is always recompiled.  With '+' the shared library is recompiled only
/// if it does not exist yet or the macro file is newer than the shared
/// library.
/// Of course the + and ++ notation is supported in similar way for .x and .L.
/// Through the function TSystem::SetMakeSharedLib(), the user will be able to
/// indicate, with shell commands, how to build a shared library (a good
/// default will be provided). The most common change, namely where to find
/// header files, will be available through the function
/// TSystem::SetIncludePath().
/// A good default will be provided so that a typical user session should be at
/// most:
/// root[1] gSystem->SetIncludePath("-I$ROOTSYS/include -I$HOME/mypackage/include");
/// root[2] .x myfunc.C++(10,20);
/// The user may sometimes try to compile a script before it has loaded all the
/// needed shared libraries.  In this case we want to be helpfull and output a
/// list of the unresolved symbols. So if the loading of the created shared
/// library fails, we will try to build a executable that contains the
/// script. The linker should then output a list of missing symbols.
/// To support this we provide a TSystem::SetMakeExe() function, that sets the
/// directive telling how to create an executable. The loader will need
/// to be informed of all the libraries available. The information about
/// the libraries that has been loaded by .L and TSystem::Load() is accesible
/// to the script compiler. However, the information about
/// the libraries that have been selected at link time by the application
/// builder (like the root libraries for root.exe) are not available and need
/// to be explicitly listed in fLinkedLibs (either by default or by a call to
/// TSystem::SetLinkedLibs()).
/// To simplify customization we could also add to the .rootrc support for the
/// variables
/// Unix.*.Root.IncludePath:     -I$ROOTSYS/include
/// WinNT.*.Root.IncludePath:    -I%ROOTSYS%/include
/// Unix.*.Root.LinkedLibs:      -L$ROOTSYS/lib -lBase ....
/// WinNT.*.Root.LinkedLibs:     %ROOTSYS%/lib/*.lib msvcrt.lib ....
/// And also support for MakeSharedLibs() and MakeExe().
/// (the ... have to be replaced by the actual values and are here only to
/// shorten this comment).

virtual Int_t           GetAclicProperties() const;
/// Return the ACLiC properties field.   See EAclicProperties for details
/// on the semantic of each bit.

virtual const char     *GetBuildArch() const;/// Return the build architecture.
virtual const char     *GetBuildCompiler() const;/// Return the build compiler
virtual const char     *GetBuildCompilerVersion() const;/// Return the build compiler version
virtual const char     *GetBuildNode() const;/// Return the build node name.
virtual const char     *GetBuildDir() const;/// Return the path of the build directory.
virtual const char     *GetFlagsDebug() const;/// Return the debug flags.
virtual const char     *GetFlagsOpt() const;/// Return the optimization flags.
virtual const char     *GetIncludePath();/// Get the list of include path.
virtual const char     *GetLinkedLibs() const;
/// Return the list of library linked to this executable.
/// See TSystem::CompileMacro for more details.

virtual const char     *GetLinkdefSuffix() const;
/// Return the linkdef suffix chosen by the user for ACLiC.
/// See TSystem::CompileMacro for more details.

virtual EAclicMode      GetAclicMode() const;
/// AclicMode indicates whether the library should be built in
/// debug mode or optimized.  The values are:
///  - TSystem::kDefault : compile the same as the current ROOT
///  - TSystem::kDebug : compiled in debug mode
///  - TSystem::kOpt : optimized the library

virtual const char     *GetMakeExe() const;
/// Return the command line use to make an executable.
/// See TSystem::CompileMacro for more details.

virtual const char     *GetMakeSharedLib() const;
/// Return the command line use to make a shared library.
/// See TSystem::CompileMacro for more details.

virtual const char     *GetSoExt() const;/// Get the shared library extension.
virtual const char     *GetObjExt() const;/// Get the object file extension.
virtual void            SetBuildDir(const char* build_dir, Bool_t isflat = kFALSE);
/// Set the location where ACLiC will create libraries and use as
/// a scratch area.
/// If isflast is flase, then the libraries are actually stored in
/// sub-directories of 'build_dir' including the full pathname of the
/// script.  If the script is location at /full/path/name/macro.C
/// the library will be located at 'build_dir+/full/path/name/macro_C.so'
/// If 'isflat' is true, then no subdirectory is created and the library
/// is created directly in the directory 'build_dir'.  Note that in this
/// mode there is a risk than 2 script of the same in different source
/// directory will over-write each other.

virtual void            SetFlagsDebug(const char *);
// FlagsDebug should contain the options to pass to the C++ compiler
/// in order to compile the library in debug mode.

virtual void            SetFlagsOpt(const char *);
/// FlagsOpt should contain the options to pass to the C++ compiler
/// in order to compile the library in optimized mode.

virtual void            SetIncludePath(const char *includePath);
/// IncludePath should contain the list of compiler flags to indicate where
/// to find user defined header files. It is used to expand $IncludePath in
/// the directives given to SetMakeSharedLib() and SetMakeExe(),

virtual void            SetMakeExe(const char *directives);
/// Directives has the same syntax as the argument of SetMakeSharedLib but is
/// used to create an executable. This creation is used as a means to output
/// a list of unresolved symbols, when loading a shared library has failed.
/// The required variable is $ExeName rather than $SharedLib

virtual void            SetAclicMode(EAclicMode mode);
/// AclicMode indicates whether the library should be built in
/// debug mode or optimized.  The values are:
///  - TSystem::kDefault : compile the same as the current ROOT
///  - TSystem::kDebug : compiled in debug mode
///  - TSystem::kOpt : optimized the library

virtual void            SetMakeSharedLib(const char *directives);
/// Directives should contain the description on how to compile and link a
/// shared lib. This description can be any valid shell command, including
/// the use of ';' to separate several instructions. However, shell specific
/// construct should be avoided. In particular this description can contain
/// environment variables, like $ROOTSYS (or %ROOTSYS% on windows).
/// Five special variables will be expanded before execution:
///   Variable name       Expands to
///   -------------       ----------
///   $SourceFiles        Name of source files to be compiled
///   $SharedLib          Name of the shared library being created
///   $LibName            Name of shared library without extension
///   $BuildDir           Directory where the files will be created
///   $IncludePath        value of fIncludePath
///   $LinkedLibs         value of fLinkedLibs
///   $DepLibs            libraries on which this library depends on
///   $ObjectFiles        Name of source files to be compiler with
///                       their extension changed to .o or .obj
///   $Opt                location of the optimization/debug options
///                       set fFlagsDebug and fFlagsOpt

virtual void            SetLinkedLibs(const char *linkedLibs);
/// LinkedLibs should contain the library directory and list of libraries
/// needed to recreate the current executable. It is used to expand $LinkedLibs
/// in the directives given to SetMakeSharedLib() and SetMakeExe()
/// The default value on Unix is: `root-config --glibs`

virtual void            SetLinkdefSuffix(const char *suffix);
/// The 'suffix' will be appended to the name of a script loaded by ACLiC
/// and used to locate any eventual additional linkdef information that
/// ACLiC should used to produce the dictionary.
/// So by default, when doing .L MyScript.cxx, ACLiC will look
/// for a file name MyScript_linkdef and having one of the .h (.hpp,
/// etc.) extensions.  If such a file exist, it will be added to
/// the end of the linkdef file used to created the ACLiC dictionary.
/// This effectively enable the full customization of the creation
/// of the dictionary.  It should be noted that the file is intended
/// as a linkdef `fragment`, so usually you would not list the
/// typical:
///~~~ {.cpp}
///   #pragma link off ....
///~~~

virtual void            SetSoExt(const char *soExt);/// Set shared library extension, should be either .so, .sl, .a, .dll, etc.
virtual void            SetObjExt(const char *objExt);/// Set object files extension, should be either .o, .obj, etc.
virtual TString         SplitAclicMode(const char *filename, TString &mode, TString &args, TString &io) const;
/// This method split a filename of the form:
///  ~~~ {.cpp}
///   [path/]macro.C[+|++[k|f|g|O|c|s|d|v|-]][(args)].
///  ~~~
/// It stores the ACliC mode [+|++[options]] in 'mode',
/// the arguments (including parenthesis) in arg
/// and the I/O indirection in io

virtual void            CleanCompiledMacros();/// Remove the shared libs produced by the CompileMacro() function.
```

## code

```cpp
// virtual void            SetMakeSharedLib(const char *directives);

gSystem->SetMakeSharedLib(
"KCC -n32 --strict $IncludePath -K0 \$Opt $SourceFile
 --no_exceptions --signed_chars --display_error_number
 --diag_suppress 68 -o $SharedLib");

gSystem->setMakeSharedLib(
"Cxx $IncludePath -c $SourceFile;
 ld  -L/usr/lib/cmplrs/cxx -rpath /usr/lib/cmplrs/cxx -expect_unresolved
 \$Opt -shared /usr/lib/cmplrs/cc/crt0.o /usr/lib/cmplrs/cxx/_main.o
 -o $SharedLib $ObjectFile -lcxxstd -lcxx -lexc -lots -lc"

gSystem->SetMakeSharedLib(
"$HOME/mygcc/bin/g++ \$Opt -Wall -fPIC $IncludePath $SourceFile
 -shared -o $SharedLib");

gSystem->SetMakeSharedLib(
"cl -DWIN32  -D_WIN32 -D_MT -D_DLL -MD /O2 /G5 /MD -DWIN32
 -D_WINDOWS $IncludePath $SourceFile
 /link -PDB:NONE /NODEFAULTLIB /INCREMENTAL:NO /RELEASE /NOLOGO
 $LinkedLibs -entry:_DllMainCRTStartup@12 -dll /out:$SharedLib")
```

```cpp
// void SetMakeExe(const char *directives)

gSystem->SetMakeExe(
"g++ -Wall -fPIC $IncludePath $SourceFiles
 -o $ExeName $LinkedLibs -L/usr/X11R6/lib -lX11 -lm -ldl -rdynamic");
```

```cpp
// void            SetIncludePath(const char *includePath);

gSystem->SetInclude("-I$ROOTSYS/include -Imydirectory/include");

/// the default value of IncludePath on Unix is:
///    "-I$ROOTSYS/include "
/// and on Windows:
///    "/I%ROOTSYS%/include "
```

<!-- TSystem.md ends here -->
