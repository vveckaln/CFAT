// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIWeightRecordDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/afs/cern.ch/work/v/vveckaln/private/CFAT/1.0.0/interface/WeightRecord.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_WeightRecord(void *p = 0);
   static void *newArray_WeightRecord(Long_t size, void *p);
   static void delete_WeightRecord(void *p);
   static void deleteArray_WeightRecord(void *p);
   static void destruct_WeightRecord(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WeightRecord*)
   {
      ::WeightRecord *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WeightRecord >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WeightRecord", ::WeightRecord::Class_Version(), "interface/WeightRecord.hh", 27,
                  typeid(::WeightRecord), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WeightRecord::Dictionary, isa_proxy, 4,
                  sizeof(::WeightRecord) );
      instance.SetNew(&new_WeightRecord);
      instance.SetNewArray(&newArray_WeightRecord);
      instance.SetDelete(&delete_WeightRecord);
      instance.SetDeleteArray(&deleteArray_WeightRecord);
      instance.SetDestructor(&destruct_WeightRecord);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WeightRecord*)
   {
      return GenerateInitInstanceLocal((::WeightRecord*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WeightRecord*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WeightMap(void *p = 0);
   static void *newArray_WeightMap(Long_t size, void *p);
   static void delete_WeightMap(void *p);
   static void deleteArray_WeightMap(void *p);
   static void destruct_WeightMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WeightMap*)
   {
      ::WeightMap *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WeightMap >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WeightMap", ::WeightMap::Class_Version(), "interface/WeightRecord.hh", 39,
                  typeid(::WeightMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WeightMap::Dictionary, isa_proxy, 4,
                  sizeof(::WeightMap) );
      instance.SetNew(&new_WeightMap);
      instance.SetNewArray(&newArray_WeightMap);
      instance.SetDelete(&delete_WeightMap);
      instance.SetDeleteArray(&deleteArray_WeightMap);
      instance.SetDestructor(&destruct_WeightMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WeightMap*)
   {
      return GenerateInitInstanceLocal((::WeightMap*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WeightMap*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr WeightRecord::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WeightRecord::Class_Name()
{
   return "WeightRecord";
}

//______________________________________________________________________________
const char *WeightRecord::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WeightRecord*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WeightRecord::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WeightRecord*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WeightRecord::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WeightRecord*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WeightRecord::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WeightRecord*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WeightMap::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WeightMap::Class_Name()
{
   return "WeightMap";
}

//______________________________________________________________________________
const char *WeightMap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WeightMap*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WeightMap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WeightMap*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WeightMap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WeightMap*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WeightMap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WeightMap*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void WeightRecord::Streamer(TBuffer &R__b)
{
   // Stream an object of class WeightRecord.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WeightRecord::Class(),this);
   } else {
      R__b.WriteClassBuffer(WeightRecord::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WeightRecord(void *p) {
      return  p ? new(p) ::WeightRecord : new ::WeightRecord;
   }
   static void *newArray_WeightRecord(Long_t nElements, void *p) {
      return p ? new(p) ::WeightRecord[nElements] : new ::WeightRecord[nElements];
   }
   // Wrapper around operator delete
   static void delete_WeightRecord(void *p) {
      delete ((::WeightRecord*)p);
   }
   static void deleteArray_WeightRecord(void *p) {
      delete [] ((::WeightRecord*)p);
   }
   static void destruct_WeightRecord(void *p) {
      typedef ::WeightRecord current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WeightRecord

//______________________________________________________________________________
void WeightMap::Streamer(TBuffer &R__b)
{
   // Stream an object of class WeightMap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WeightMap::Class(),this);
   } else {
      R__b.WriteClassBuffer(WeightMap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WeightMap(void *p) {
      return  p ? new(p) ::WeightMap : new ::WeightMap;
   }
   static void *newArray_WeightMap(Long_t nElements, void *p) {
      return p ? new(p) ::WeightMap[nElements] : new ::WeightMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_WeightMap(void *p) {
      delete ((::WeightMap*)p);
   }
   static void deleteArray_WeightMap(void *p) {
      delete [] ((::WeightMap*)p);
   }
   static void destruct_WeightMap(void *p) {
      typedef ::WeightMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WeightMap

namespace ROOT {
   static TClass *maplEWeightscOWeightRecordgR_Dictionary();
   static void maplEWeightscOWeightRecordgR_TClassManip(TClass*);
   static void *new_maplEWeightscOWeightRecordgR(void *p = 0);
   static void *newArray_maplEWeightscOWeightRecordgR(Long_t size, void *p);
   static void delete_maplEWeightscOWeightRecordgR(void *p);
   static void deleteArray_maplEWeightscOWeightRecordgR(void *p);
   static void destruct_maplEWeightscOWeightRecordgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<Weights,WeightRecord>*)
   {
      map<Weights,WeightRecord> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<Weights,WeightRecord>));
      static ::ROOT::TGenericClassInfo 
         instance("map<Weights,WeightRecord>", -2, "map", 96,
                  typeid(map<Weights,WeightRecord>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEWeightscOWeightRecordgR_Dictionary, isa_proxy, 0,
                  sizeof(map<Weights,WeightRecord>) );
      instance.SetNew(&new_maplEWeightscOWeightRecordgR);
      instance.SetNewArray(&newArray_maplEWeightscOWeightRecordgR);
      instance.SetDelete(&delete_maplEWeightscOWeightRecordgR);
      instance.SetDeleteArray(&deleteArray_maplEWeightscOWeightRecordgR);
      instance.SetDestructor(&destruct_maplEWeightscOWeightRecordgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<Weights,WeightRecord> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<Weights,WeightRecord>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEWeightscOWeightRecordgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<Weights,WeightRecord>*)0x0)->GetClass();
      maplEWeightscOWeightRecordgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEWeightscOWeightRecordgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEWeightscOWeightRecordgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<Weights,WeightRecord> : new map<Weights,WeightRecord>;
   }
   static void *newArray_maplEWeightscOWeightRecordgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<Weights,WeightRecord>[nElements] : new map<Weights,WeightRecord>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEWeightscOWeightRecordgR(void *p) {
      delete ((map<Weights,WeightRecord>*)p);
   }
   static void deleteArray_maplEWeightscOWeightRecordgR(void *p) {
      delete [] ((map<Weights,WeightRecord>*)p);
   }
   static void destruct_maplEWeightscOWeightRecordgR(void *p) {
      typedef map<Weights,WeightRecord> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<Weights,WeightRecord>

namespace ROOT {
   static TClass *maplEVaricOdoublegR_Dictionary();
   static void maplEVaricOdoublegR_TClassManip(TClass*);
   static void *new_maplEVaricOdoublegR(void *p = 0);
   static void *newArray_maplEVaricOdoublegR(Long_t size, void *p);
   static void delete_maplEVaricOdoublegR(void *p);
   static void deleteArray_maplEVaricOdoublegR(void *p);
   static void destruct_maplEVaricOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<Vari,double>*)
   {
      map<Vari,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<Vari,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<Vari,double>", -2, "map", 96,
                  typeid(map<Vari,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEVaricOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<Vari,double>) );
      instance.SetNew(&new_maplEVaricOdoublegR);
      instance.SetNewArray(&newArray_maplEVaricOdoublegR);
      instance.SetDelete(&delete_maplEVaricOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEVaricOdoublegR);
      instance.SetDestructor(&destruct_maplEVaricOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<Vari,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<Vari,double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEVaricOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<Vari,double>*)0x0)->GetClass();
      maplEVaricOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEVaricOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEVaricOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<Vari,double> : new map<Vari,double>;
   }
   static void *newArray_maplEVaricOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<Vari,double>[nElements] : new map<Vari,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEVaricOdoublegR(void *p) {
      delete ((map<Vari,double>*)p);
   }
   static void deleteArray_maplEVaricOdoublegR(void *p) {
      delete [] ((map<Vari,double>*)p);
   }
   static void destruct_maplEVaricOdoublegR(void *p) {
      typedef map<Vari,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<Vari,double>

namespace {
  void TriggerDictionaryInitialization_WeightRecordDict_Impl() {
    static const char* headers[] = {
"interface/WeightRecord.hh",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc630/lcg/root/6.10.08-fmblme2/include",
"/afs/cern.ch/work/v/vveckaln/private/CFAT/1.0.0/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "WeightRecordDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
struct __attribute__((annotate("$clingAutoload$interface/WeightRecord.hh")))  WeightRecord;
class __attribute__((annotate("$clingAutoload$interface/WeightRecord.hh")))  WeightMap;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "WeightRecordDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/afs/cern.ch/work/v/vveckaln/private/CFAT/1.0.0/interface/WeightRecord.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"WeightMap", payloadCode, "@",
"WeightRecord", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("WeightRecordDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_WeightRecordDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_WeightRecordDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_WeightRecordDict() {
  TriggerDictionaryInitialization_WeightRecordDict_Impl();
}
