// some C++ header definition
#ifdef __MAKECINT__
// turns off dictionary generation for all

/* #pragma link off all globals; */
/* #pragma link off all classes; */
/* #pragma link off all functions; */
/* #pragma link off all namespaces; */
/* #pragma link off all enums; */

#pragma link C++ class Vari+;
#pragma link C++ class Weights+;
#pragma link C++ class Categories+;
/* #pragma link C++ const std::map<Vari, TString> varititles; */
/* #pragma link C++ const std::map<unsigned char, pair<Weights, Vari>> windmap; */
/* #pragma link C++ const std::map<Weights, TString> weightstitles; */
/* #pragma link C++ const std::map<Weights, Categories> wcats; */
/* #pragma link C++ const std::map<Categories, TString> cattitles; */
/* #pragma link C++ const std::map<Vari, TString> varititles; */


#pragma link C++ std::map<Vari, double>+;
#pragma link C++ class WeightRecord+;

#pragma link C++ std::map<Weights, WeightRecord>+;
#pragma link C++ class WeightMap+;


#endif
