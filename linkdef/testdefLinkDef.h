// some C++ header definition
#ifdef __MAKECINT__
// turns off dictionary generation for all

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all namespaces;
//#pragma link C++ const int testdef::testi; 
#pragma link C++ function someDo();
#pragma link C++ namespace testdef;
#pragma link C++ function testdef::testDo();
#endif
