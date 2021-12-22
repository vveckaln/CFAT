// some C++ header definition
#ifdef __MAKECINT__
// turns off dictionary generation for all

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all namespaces;
#pragma link C++ enum Vari;
#pragma link C++ const std::map<Vari, TString> varititles;
#pragma link C++ std::map<Vari, double>+;
#pragma link C++ class WeightRecord+;
#pragma link C++ enum Weights;
#pragma link C++ const std::map<Weights, TString> weightstitles;
#pragma link C++ const std::map<Weights, Categories> wcats;
#pragma link C++ const std::map<Categories, TString> cattitles;
#pragma link C++ std::map<Definitions::Weights, WeightRecord>+;
#pragma link C++ const std::map<unsigned char, pair<Weights, Vari>> windmap;
#pragma link C++ class WeightMap+;


#endif
