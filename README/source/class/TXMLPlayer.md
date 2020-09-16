<!-- TXMLPlayer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 15:44:42 2019 (+0800)
;; Last-Updated: 三 9月 16 10:40:50 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TXMLPlayer-

```cpp
// Class for xml code generation
// It should be used for generation of xml steramers, which could be used outside root
// environment. This means, that with help of such streamers user can read and write
// objects from/to xml file, which later can be accepted by ROOT.
//
// At the moment supported only classes, which are not inherited from TObject
// and which not contains any TObject members.
//
// To generate xml code:
//
// 1. ROOT library with required classes should be created.
//    In general, without such library non of user objects can be stored and
//    retrived from any ROOT file
//
// 2. Generate xml streamers by root script like:
//
//    void generate() {
//      gSystem->Load("libRXML.so");   // load ROOT xml library
//      gSystem->Load("libuser.so");   // load user ROOT library
//
//      TList lst;
//      lst.Add(TClass::GetClass("TUserClass1"));
//      lst.Add(TClass::GetClass("TUserClass2"));
//      ...
//      TXMLPlayer player;
//      player.ProduceCode(&lst, "streamers");    // create xml streamers
//    }
//
//  3. Copy "streamers.h", "streamers.cxx", "TXmlFile.h", "TXmlFile.cxx" files
//     to user project and compile them. TXmlFile class implementation can be taken
//     from http://www-linux.gsi.de/~linev/xmlfile.tar.gz
//
// TXMLPlayer class generates one function per class, which called class streamer.
// Name of such function for class TExample will be TExample_streamer.
//
// Following data members for streamed classes are supported:
//  - simple data types (int, double, float)
//  - array of simple types (int[5], double[5][6])
//  - dynamic array of simple types (int* with comment field // [fSize])
//  - const char*
//  - object of any nonROOT class
//  - pointer on object
//  - array of objects
//  - array of pointers on objects
//  - stl string
//  - stl vector, list, deque, set, multiset, map, multimap
//  - allowed arguments for stl containers are: simple data types, string, object, pointer on object
//  Any other data member can not be (yet) read from xml file and write to xml file.
//
// If data member of class is private or protected, it can not be accessed via
// member name. Two alternative way is supported. First, if for class member fValue
// exists function GetValue(), it will be used to get value from the class, and if
// exists SetValue(), it will be used to set apropriate data member. Names of setter
// and getter methods can be specified in comments filed like:
//
//     int  fValue;   // *OPTION={GetMethod="GetV";SetMethod="SetV"}
//
// If getter or setter methods does not available, address to data member will be
// calculated as predefined offeset to object start address. In that case generated code
// should be used only on the same platform (OS + compiler), where it was generated.
//
// Generated streamers resolve inheritance tree for given class. This allows to have
// array (or vector) of object pointers on some basic class, while objects of derived
// class(es) are used.
```


```cpp
class TXMLPlayer : public TObject
```

## class

```cpp
public:
   TXMLPlayer();
   virtual ~TXMLPlayer();

   Bool_t ProduceCode(TList *cllist, const char *filename);

protected:
   TString GetStreamerName(TClass *cl);

   const char *ElementGetter(TClass *cl, const char *membername, int specials = 0);
   const char *ElementSetter(TClass *cl, const char *membername, char *endch);

   TString GetMemberTypeName(TDataMember *member);
   TString GetBasicTypeName(TStreamerElement *el);
   TString GetBasicTypeReaderMethodName(Int_t type, const char *realname);
   void ProduceStreamerSource(std::ostream &fs, TClass *cl, TList *cllist);

   void ReadSTLarg(std::ostream &fs, TString &argname, int argtyp, Bool_t isargptr, TClass *argcl, TString &tname,
                   TString &ifcond);
   void WriteSTLarg(std::ostream &fs, const char *accname, int argtyp, Bool_t isargptr, TClass *argcl);
   Bool_t ProduceSTLstreamer(std::ostream &fs, TClass *cl, TStreamerSTL *el, Bool_t isWriting);

   TString fGetterName; //!  buffer for name of getter method
   TString fSetterName; //!  buffer for name of setter method
   TXMLSetup fXmlSetup; //!  buffer for xml names conversion
```

## code

```cpp
// To access data from xml files, user should use TXmlFile class, which is different from
// ROOT TXMLFile, but provides very similar functionality. For example, to read
// object from xml file:

TXmlFile file("test.xml");             // open xml file
file.ls();                             // show list of keys in file
TExample* ex1 = (TExample*) file.Get("ex1", TExample_streamer); // get object
file.Close();

// To write object to file:

TXmlFile outfile("test2.xml", "recreate");    // create xml file
TExample* ex1 = new TExample;
outfile.Write(ex1, "ex1", TExample_streamer);   // write object to file
outfile.Close();
```

<!-- TXMLPlayer.md ends here -->
