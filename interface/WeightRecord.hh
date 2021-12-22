#ifndef _weightrecord_hh_
#define _weightrecord_hh_
#include "Definitions.hh"
#include "WorkEnum_t.hh"
#include <map>
#include "TString.h"
//#include "TObject.h"

using namespace std;
using namespace Definitions;
enum class Vari { NOMINAL = 0, DOWN = 1, UP = 2 };
enum class Weights {NORM, PU, GENERATOR, TRIGSF, SELSF, L1PREFIREPROB, BOWLERLUNDBFRAG, PETERSONFRAG, SEMILEPBR, TOPPTSF, 
    MUR1P0MUF2P0, MUR1P0MUF0P5, MUR2P0MUF1P0, MUR2P0MUF2P0, MUR0P5MUF1P0, MUR0P5MUF0P5,
    CTEQ_TEA_PDF, MMHT_PDF};

enum class Categories {CNORM, CPU, CGENERATOR, CTRIGSF, CSELSF, CL1PREFIREPROB, CBLFRAG, CPETERSONFRAG, CSEMILEPBR, CTOPPTSF, 
    CQCD,
    CPDF};


extern const map<unsigned char, pair<Weights, Vari>> windmap;
extern const map<Weights, TString> weightstitles;
extern const map<Weights, Categories> wcats;
extern const map<Categories, TString> cattitles;
extern const map<Vari, TString> varititles;

struct WeightRecord: public TObject
{
  WeightRecord();
  ~WeightRecord();
  map<Vari, double> _weights;
  double & operator[] (Vari);
  double GetWeight(Vari);
  //void Do();
  void ls();
  ClassDef(WeightRecord, 1);
};

class WeightMap: public TObject
{
  map<Weights, WeightRecord> _weightmap;
public:
  WeightMap();
  ~WeightMap();
  map<Weights, WeightRecord> * operator -> ();
  WeightRecord & operator[](Weights);
  double GetWeight(Weights, Vari, WorkEnum_t);
  double GetWeight0(WorkEnum_t);
  void Reset();
  void Do();
  void ls();
  ClassDef(WeightMap, 1);
};
#endif
