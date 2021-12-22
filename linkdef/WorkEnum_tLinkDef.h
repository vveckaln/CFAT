// some C++ header definition
#ifdef __MAKECINT__
// turns off dictionary generation for all

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all namespaces;
#pragma link C++ namespace Definitions;
#pragma link C++ enum Definitions::WorkEnum_t;
#pragma link C++ const std::map<Definitions::WorkEnum_t, const char *>         Definitions::tag_levels_types_;
/* #pragma link C++ std::map<Definitions::WorkEnum_t, const char *>         Definitions::tag_levels_types_; */
/* #pragma link C++ std::map<Definitions::WorkEnum_t, TString>         Definitions::tag_levels_types_; */
#pragma link C++ function testfunc();
#endif
