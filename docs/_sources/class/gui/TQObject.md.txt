<!-- TQObject.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 14:12:31 2016 (+0800)
;; Last-Updated: 三 9月 16 11:17:29 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TQObject*

This is the ROOT implementation of the Qt object communication       
mechanism (see also http:www.troll.no/qt/metaobjects.html)         
                                                                     
Signals and slots are used for communication between objects.        
When an object has changed in some way that might be interesting     
for the outside world, it emits a signal to tell whoever is          
listening. All slots that are connected to this signal will be       
activated (called).  It is even possible to connect a signal         
directly to  another signal (this will emit the second signal        
immediately whenever the first is emitted.) There is no limitation   
on the number of slots that can be connected to a signal.            
The slots will be activated in the order they were connected         
to the signal. This mechanism allows objects to be easily reused,    
because the object that emits a signal does not need to know         
to what the signals are connected to.                                
Together, signals and slots make up a powerfull component            
programming mechanism.                                               
                                                                     

TQObject friend  TQConnection

TQObjSender 继承 TQObject


## class

**TQObject**

```cpp
   TQObject();
/// TQObject Constructor.
/// Comment:
///  - In order to minimize memory allocation fListOfSignals and
///    fListOfConnections are allocated only if it is neccesary
///  - When fListOfSignals/fListOfConnections are empty they will
///    be deleted

   virtual ~TQObject();
/// TQObject Destructor.
///    - delete all connections and signal list

   TList   *GetListOfClassSignals() const;/// Returns pointer to list of signals of this class.
   TList   *GetListOfSignals() const { return fListOfSignals; }
   TList   *GetListOfConnections() const { return fListOfConnections; }

   Bool_t   AreSignalsBlocked() const { return fSignalsBlocked; }
   Bool_t   BlockSignals(Bool_t b)
            { Bool_t ret = fSignalsBlocked; fSignalsBlocked = b; return ret; }

   void  CollectClassSignalLists(TList& list, TClass* cls);
/// Collect class signal lists from class cls and all its
/// base-classes.
/// The recursive traversal is not performed for classes not
/// deriving from TQClass.

   template <typename... T> void EmitVA(const char *signal_name, Int_t /* nargs */, const T&... params);
   // void  EmitVA(const char *signal, Int_t nargs, ...);
   void  EmitVA(const char *signal, Int_t nargs, va_list va) = delete;
   void  Emit(const char *signal);
/// Acitvate signal without args.

   void  Emit(const char *signal, Long_t *paramArr);
/// Emit a signal with a varying number of arguments,
/// paramArr is an array of the parameters.
/// Note: any parameter should be converted to long type.

   void  Emit(const char *signal, const char *params);
/// Activate signal with parameter text string.

   void  Emit(const char *signal, Double_t param);
/// Activate signal with single parameter.

   void  Emit(const char *signal, Long_t param);
/// Activate signal with single parameter.

   void  Emit(const char *signal, Long64_t param);
/// Activate signal with single parameter.

   void  Emit(const char *signal, Bool_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, Char_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, UChar_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, Short_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, UShort_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, Int_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, UInt_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, ULong_t param)
         { Emit(signal, (Long_t)param); }
   void  Emit(const char *signal, ULong64_t param)
         { Emit(signal, (Long64_t) param); }
   void  Emit(const char *signal, Float_t param)
         { Emit(signal, (Double_t)param); }

   Bool_t Connect(const char *signal,
                  const char *receiver_class,
                  void *receiver,
                  const char *slot);
/// Non-static method is used to connect from the signal
/// of this object to the receiver slot.
/// Warning! No check on consistency of sender/receiver
/// classes/methods.
/// This method makes possible to have connection/signals from
/// interpreted class. See also RQ_OBJECT.h.

   Bool_t Disconnect(const char *signal = 0,
                     void *receiver = 0,
                     const char *slot = 0);
/// Disconnects signal of this object from slot of receiver.
/// Equivalent to Disconnect(this, signal, receiver, slot)

   virtual void   HighPriority(const char *signal_name,
                               const char *slot_name = 0);
/// 1. If slot_name = 0 => makes signal defined by the signal_name
///    to be the first in the fListOfSignals, this decreases
///    the time for lookup.
/// 2. If slot_name != 0 => makes slot defined by the slot_name
///    to be executed first when signal_name is emitted.
/// Signal name is not compressed.

   virtual void   LowPriority(const char *signal_name,
                              const char *slot_name = 0);
/// 1. If slot_name = 0 => makes signal defined by the signal_name
///    to be the last in the fListOfSignals, this increase the time
///    for lookup.
/// 2. If slot_name != 0 => makes slot defined by the slot_name
///    to  be executed last when signal_name is emitted.
/// Signal name is not compressed.

   virtual Bool_t HasConnection(const char *signal_name) const;
/// Return true if there is any object connected to this signal.
/// Only checks for object signals.

   virtual Int_t  NumberOfSignals() const;
/// Return number of signals for this object.
/// Only checks for object signals.

   virtual Int_t  NumberOfConnections() const;/// Return number of connections for this object.
   virtual void   Connected(const char * /*signal_name*/) { }
   virtual void   Disconnected(const char * /*signal_name*/) { }

   virtual void   Destroyed()
                  { Emit("Destroyed()"); }                 // *SIGNAL*
   virtual void   ChangedBy(const char *method)
                  { Emit("ChangedBy(char*)", method); }    // *SIGNAL*
   virtual void   Message(const char *msg)
                  { Emit("Message(char*)", msg); }         // *SIGNAL*

   static Bool_t  Connect(TQObject *sender,
                          const char *signal,
                          const char *receiver_class,
                          void *receiver,
                          const char *slot);
/// Create connection between sender and receiver.
/// Signal and slot string must have a form:
///    "Draw(char*, Option_t* ,Int_t)"
/// All blanks and "const" words will be removed,
/// Warning:
///  If receiver is class not derived from TQObject and going to be
///  deleted, disconnect all connections to this receiver.
///  In case of class derived from TQObject it is done automatically.


   static Bool_t  Connect(const char *sender_class,
                          const char *signal,
                          const char *receiver_class,
                          void *receiver,
                          const char *slot);
/// This method allows to make a connection from any object
/// of the same class to a single slot.
/// Signal and slot string must have a form:
///    "Draw(char*, Option_t* ,Int_t)"
/// All blanks and "const" words will be removed,
/// Warning:
///  If receiver class not derived from TQObject and going to be
///  deleted, disconnect all connections to this receiver.
///  In case of class derived from TQObject it is done automatically.

   static Bool_t  Disconnect(TQObject *sender,
                             const char *signal = 0,
                             void *receiver = 0,
                             const char *slot = 0);
/// Disconnects signal in object sender from slot_method in
/// object receiver. For objects derived from TQObject signal-slot
/// connection is removed when either of the objects involved
/// are destroyed.
/// Disconnect() is typically used in three ways, as the following
/// examples shows:
///  - Disconnect everything connected to an object's signals:
///       Disconnect(myObject);
///  - Disconnect everything connected to a signal:
///       Disconnect(myObject, "mySignal()");
///  - Disconnect a specific receiver:
///       Disconnect(myObject, 0, myReceiver, 0);
/// 0 may be used as a wildcard in three of the four arguments,
/// meaning "any signal", "any receiving object" or
/// "any slot in the receiving object", respectively.
/// The sender has no default and may never be 0
/// (you cannot disconnect signals from more than one object).
/// If signal is 0, it disconnects receiver and slot_method
/// from any signal. If not, only the specified signal is
/// disconnected.
/// If  receiver is 0, it disconnects anything connected to signal.
/// If not, slots in objects other than receiver are not
/// disconnected
/// If slot_method is 0, it disconnects anything that is connected
/// to receiver.  If not, only slots named slot_method will be
/// disconnected, and all other slots are left alone.
/// The slot_method must be 0 if receiver is left out, so you
/// cannot disconnect a specifically-named slot on all objects.

   static Bool_t  Disconnect(const char *class_name,
                             const char *signal,
                             void *receiver = 0,
                             const char *slot = 0);
/// Disconnects "class signal". The class is defined by class_name.
/// See also Connect(class_name,signal,receiver,slot).

   static Bool_t  AreAllSignalsBlocked();/// Returns true if all signals are blocked.
   static Bool_t  BlockAllSignals(Bool_t b);
/// Block or unblock all signals. Returns the previous block status.   
```


**TQObjSender**

```cpp
   TQObjSender() : TQObject(), fSender(0), fSenderClass() { }
   virtual ~TQObjSender() { Disconnect(); }

   virtual void SetSender(void *sender) { fSender = sender; }
   void SetSenderClassName(const char *sclass = "") { fSenderClass = sclass; }
```


## code

```cpp
// void TQObject::Emit(const char *signal_name)

theButton->Emit("Clicked()");
```

```cpp
// void TQObject::Emit(const char *signal_name, Long_t param)

theButton->Emit("Clicked(int)",id)
```

```cpp
// void TQObject::Emit(const char *signal_name, Long64_t param)

theButton->Emit("Progress(Long64_t)",processed)
```

```cpp
// void TQObject::Emit(const char *signal_name, Double_t param)

theButton->Emit("Scale(float)",factor)
```

```cpp
// void TQObject::Emit(const char *signal_name, const char *params)

myObject->Emit("Error(char*)","Fatal error");
```


```cpp
// void TQObject::Emit(const char *signal_name, Long_t *paramArr)

TQObject *processor; // data processor
TH1F     *hist;      // filled with processor results

processor->Connect("Evaluated(Float_t,Float_t)",
                   "TH1F",hist,"Fill12(Axis_t,Axis_t)");

Long_t args[2];
args[0] = (Long_t)processor->GetValue(1);
args[1] = (Long_t)processor->GetValue(2);

processor->Emit("Evaluated(Float_t,Float_t)",args);
```

```cpp
// Bool_t TQObject::Connect(TQObject *sender,
//                          const char *signal,
//                          const char *cl,
//                          void *receiver,
//                          const char *slot)

/// cl != 0 - class name, it can be class with or
///           without dictionary, e.g interpreted class.
TGButton *myButton;
TH2F     *myHist;
TQObject::Connect(myButton,"Clicked()",
                  "TH2F", myHist,"Draw(Option_t*)");

/// cl == 0 - corresponds to function (interpereted or global)
///           the name of the function is defined by the slot string,
///           parameter receiver should be 0.
TGButton *myButton;
TH2F     *myHist;
TQObject::Connect(myButton,"Clicked()",
                  0, 0,"hsimple()");
```


```cpp
// Bool_t TQObject::Connect(const char *class_name,
//                          const char *signal,
//                          const char *cl,
//                          void *receiver,
//                          const char *slot)

/// cl != 0 - class name, it can be class with or
///           without dictionary, e.g interpreted class.

TGButton *myButton;
TH2F     *myHist;

TQObject::Connect("TGButton", "Clicked()",
                   "TH2F", myHist, "Draw(Option_t*)");

/// cl == 0 - corresponds to function (interpereted or global)
///           the name of the function is defined by the slot string,
///           parameter receiver should be 0.

TGButton *myButton;
TH2F     *myHist;
TQObject::Connect("TGButton", "Clicked()",
                   0, 0, "hsimple()");
```



## example




<!-- TQObject.md ends here -->
