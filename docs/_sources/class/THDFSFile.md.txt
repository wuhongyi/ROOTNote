<!-- THDFSFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 15:24:06 2019 (+0800)
;; Last-Updated: 三 9月 16 10:33:38 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# THDFSFile*

```
Reads and writes its data via the HDFS protocols

A THDFSFile is like a normal TFile except that it reads and writes
its data via the HDFS protocols. For more information on HDFS, see
http://hadoop.apache.org/hdfs/.
This implementation interfaces with libhdfs, which is a JNI-based
library (i.e., it will start a Java JVM internally the first time
it is called). At a minimum, you will need your environment's
$CLASSPATH variable set up properly to use. Here's an example of
one way to properly set your classpath, assuming you use the OSG
distribution of Hadoop:
    $ source $HADOOP_CONF_DIR/hadoop-env.sh
    $ export CLASSPATH=$HADOOP_CLASSPATH
Additionally, you will need a valid libjvm in your $LD_LIBRARY_PATH
This is usually found in either:
    $JAVA_HOME/jre/lib/i386/server
or
    $JAVA_HOME/jre/lib/amd64/server
This file can only be used if hdfs support is compiled into ROOT.
The HDFS URLs follow the Hadoop notation and should be of the form:
    hdfs://[host:port]/absolute/path/to/file/in/HDFS.root
Any host or port information will be ignored; this is taken from the
node's HDFS configuration files.

Example HDFS URLs:

    hdfs:///user/username/dir1/file2.root
    hdfs://localhost/user/username/dir1/file2.root
```


```cpp
class THDFSFile : public TFile

THDFSSystem : public TSystem
```

## class

**THDFSFile**

```cpp
private:
   void     *fHdfsFH;    ///< HDFS file handle
   void     *fFS;        ///< HDFS user handle
   Long64_t  fSize;      ///< File size
   Long64_t  fSysOffset; ///< Seek offset in file
   TUrl      fUrl;       ///< HDFS url
   TString   fPath;      ///< HDFS path

   Int_t    SysOpen(const char *pathname, Int_t flags, UInt_t mode);/// Open a file in HDFS.
   Int_t    SysClose(Int_t fd);/// Close the file in HDFS.
   Int_t    SysRead(Int_t fd, void *buf, Int_t len);
/// Read specified number of bytes from current offset into the buffer.
/// See documentation for TFile::SysRead().   
   
   Int_t    SysWrite(Int_t fd, const void *buf, Int_t len);
/// Write a buffer into the file; this is not supported currently.   
   
   Long64_t SysSeek(Int_t fd, Long64_t offset, Int_t whence);
/// Seek to a specified position in the file.  See TFile::SysSeek().
/// Note that THDFSFile does not support seeks when the file is open for write.   
   
   Int_t    SysStat(Int_t fd, Long_t *id, Long64_t *size, Long_t *flags, Long_t *modtime);
/// Perform a stat on the HDFS file; see TFile::SysStat().

   Int_t    SysSync(Int_t fd);

public:
   THDFSFile(const char *path, Option_t *option="",
             const char *ftitle="", Int_t compress=1);/// Usual Constructor.  See the TFile constructor for details.
   virtual ~THDFSFile();

   void ResetErrno() const;
```

----

**THDFSSystem**

```cpp
private:
   void  *fFH;           ///< HDFS filesystem handle.
   void  *fDirp;         ///< Pointer to the array of file information.
   TUrl  *fUrlp;         ///< Pointer to the array of directory content URLs.
   Int_t  fDirEntries;   ///< The number of entries in the fDirp array.
   Int_t  fDirCtr;       ///< The current position in the fDirp array.

public:
    THDFSSystem();
    virtual ~THDFSSystem() { }

    Int_t       MakeDirectory(const char *name);/// Make a directory.
    void       *OpenDirectory(const char *name);
/// Open a directory via hdfs. Returns an opaque pointer to a dir
/// structure. Returns 0 in case of error.	
	
    void        FreeDirectory(void *dirp);
    const char *GetDirEntry(void *dirp);
    Int_t       GetPathInfo(const char *path, FileStat_t &buf);
/// Get info about a file. Info is returned in the form of a FileStat_t
/// structure (see TSystem.h).
/// The function returns 0 in case of success and 1 if the file could
/// not be stat'ed.	
	
    Bool_t      AccessPathName(const char *path, EAccessMode mode);
/// Returns FALSE if one can access a file using the specified access mode.
/// Mode is the same as for the Unix access(2) function.
/// Attention, bizarre convention of return value!!	
	
    Int_t       Unlink(const char *path);
/// Unlink, i.e. remove, a file or directory. Returns 0 when successful,
/// -1 in case of failure.	
```



<!-- THDFSFile.md ends here -->
