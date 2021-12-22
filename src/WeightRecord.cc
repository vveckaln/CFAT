#include "WeightRecord.hh"
ClassImp(WeightRecord)
ClassImp(WeightMap)

const map<unsigned char, pair<Weights, Vari>> windmap =
  {
    make_pair(1, make_pair(Weights::TRIGSF, Vari::UP)),
    make_pair(2, make_pair(Weights::TRIGSF, Vari::DOWN)),
    make_pair(3, make_pair(Weights::SELSF, Vari::UP)),
    make_pair(4, make_pair(Weights::SELSF, Vari::DOWN)),
    make_pair(5, make_pair(Weights::L1PREFIREPROB, Vari::NOMINAL)),
    make_pair(6, make_pair(Weights::BOWLERLUNDBFRAG, Vari::UP)),
    make_pair(7, make_pair(Weights::BOWLERLUNDBFRAG, Vari::DOWN)),
    make_pair(8, make_pair(Weights::PETERSONFRAG, Vari::NOMINAL)),
    make_pair(9, make_pair(Weights::SEMILEPBR, Vari::UP)),
    make_pair(10, make_pair(Weights::SEMILEPBR, Vari::DOWN)),
    make_pair(11, make_pair(Weights::TOPPTSF, Vari::NOMINAL)),
    make_pair(12, make_pair(Weights::MUR1P0MUF2P0, Vari::NOMINAL)),
    make_pair(13, make_pair(Weights::MUR1P0MUF0P5, Vari::NOMINAL)),
    make_pair(14, make_pair(Weights::MUR2P0MUF1P0, Vari::NOMINAL)),
    make_pair(15, make_pair(Weights::MUR2P0MUF2P0, Vari::NOMINAL)),
    make_pair(16, make_pair(Weights::MUR0P5MUF1P0, Vari::NOMINAL)),
    make_pair(17, make_pair(Weights::MUR0P5MUF0P5, Vari::NOMINAL)),
    make_pair(18, make_pair(Weights::CTEQ_TEA_PDF, Vari::NOMINAL)),
    make_pair(19, make_pair(Weights::MMHT_PDF, Vari::NOMINAL))

  };

// enum class Weights {NORM, PU, GENERATOR, TRIGSF, SELSF, L1PREFIREPROB, BOWLERLUNDBFRAG, PETERSONFRAG, SEMILEPBR, TOPPTSF, 
//     MUR1P0MUF2P0, MUR1P0MUF0P5, MUR2P0MUF1P0, MUR2P0MUF2P0, MUR0P5MUF1P0, MUR0P5MUF0P5,
//     CTEQ_TEA_PDF, MMHT_PDF};

const map<Weights, TString> weightstitles =
  {
    make_pair(Weights::NORM, "normalisation"),
    make_pair(Weights::GENERATOR, "generator"),
    make_pair(Weights::PU, "pileup"),
    make_pair(Weights::TRIGSF, "trig. efficiency correction"),
    make_pair(Weights::SELSF, "sel. efficiency correction"),
    make_pair(Weights::L1PREFIREPROB, "L1 prefire"),
    make_pair(Weights::BOWLERLUNDBFRAG, "BL b fragmentation"),
    make_pair(Weights::PETERSONFRAG, "Peterson frag."),
    make_pair(Weights::SEMILEPBR, "semilep BR"),
    make_pair(Weights::TOPPTSF, "top $p_{T}$"),
    make_pair(Weights::MUR1P0MUF2P0, "$#mu_{R}=1.0$ $#mu_{F}=2.0$"),
    make_pair(Weights::MUR1P0MUF0P5, "$#mu_{R}=1.0$ $#mu_{F}=0.5$"),
    make_pair(Weights::MUR2P0MUF1P0, "$#mu_{R}=2.0$ $#mu_{F}=1.0$"),
    make_pair(Weights::MUR2P0MUF2P0, "$#mu_{R}=2.0$ $#mu_{F}=2.0$"),
    make_pair(Weights::MUR0P5MUF1P0, "$#mu_{R}=0.5$ $#mu_{F}=1.0$"),
    make_pair(Weights::MUR0P5MUF0P5, "$#mu_{R}=0.5$ $#mu_{F}=0.5$"),
    make_pair(Weights::CTEQ_TEA_PDF, "CTEQ TEA"),
    make_pair(Weights::MMHT_PDF, "MHT")
  };


const map<Weights, Categories> wcats =
  {
    make_pair(Weights::NORM, Categories::CNORM),
    make_pair(Weights::GENERATOR, Categories::CGENERATOR),
    make_pair(Weights::PU, Categories::CPU),
    make_pair(Weights::TRIGSF, Categories::CTRIGSF),
    make_pair(Weights::SELSF, Categories::CSELSF),
    make_pair(Weights::L1PREFIREPROB, Categories::CL1PREFIREPROB),
    make_pair(Weights::BOWLERLUNDBFRAG, Categories::CBLFRAG),
    make_pair(Weights::PETERSONFRAG, Categories::CPETERSONFRAG),
    make_pair(Weights::SEMILEPBR, Categories::CSEMILEPBR),
    make_pair(Weights::TOPPTSF, Categories::CTOPPTSF),
    make_pair(Weights::MUR1P0MUF2P0, Categories::CQCD),
    make_pair(Weights::MUR1P0MUF0P5, Categories::CQCD),
    make_pair(Weights::MUR2P0MUF1P0, Categories::CQCD),
    make_pair(Weights::MUR2P0MUF2P0, Categories::CQCD),
    make_pair(Weights::MUR0P5MUF1P0, Categories::CQCD),
    make_pair(Weights::MUR0P5MUF0P5, Categories::CQCD),
    make_pair(Weights::CTEQ_TEA_PDF, Categories::CPDF),
    make_pair(Weights::MMHT_PDF, Categories::CPDF)
  };


const map<Categories, TString> cattitles =
  {
    make_pair(Categories::CNORM,          "Normalisation"),
    make_pair(Categories::CPU,            "Pileup"),
    make_pair(Categories::CGENERATOR,     "Generator"),
    make_pair(Categories::CTRIGSF,        "Trigger efficiency"),
    make_pair(Categories::CSELSF,         "Selection efficiency"),
    make_pair(Categories::CL1PREFIREPROB, "L1 prefire prob"),
    make_pair(Categories::CBLFRAG,        "BL fragmentation"),
    make_pair(Categories::CPETERSONFRAG,  "Peterson frag"),
    make_pair(Categories::CSEMILEPBR,     "Semilepton branching rations"),
    make_pair(Categories::CTOPPTSF,       "top $p_{T}$"),
    make_pair(Categories::CQCD,           "QCD scales"),
    make_pair(Categories::CPDF,           "PDF")
  };

const map<Vari, TString> varititles =
  {
    make_pair(Vari::NOMINAL, "nom."),
    make_pair(Vari::DOWN,    "down"),
    make_pair(Vari::UP,      "up")
  };


WeightRecord::WeightRecord()
{
}

WeightRecord::~WeightRecord()
{
  _weights.clear();
}

double & WeightRecord::operator[] (Vari var)
{
  return _weights[var];
}

double WeightRecord::GetWeight(Vari var)
{
  map<Vari, double>::iterator it = _weights.find(var);
  if (it == _weights.end())
    {
      return 1.0;
    }
  return operator [](var);
}

void WeightRecord::ls()
{
  for(map<Vari, double>::iterator it = _weights.begin(); it != _weights.end(); it ++)
    {
      printf("\t%s %f*1E6\n", varititles.at(it -> first).Data(), it -> second * 1E6);
    }
}

WeightMap::WeightMap()
{

}

WeightMap::~WeightMap()
{
  _weightmap.clear();
}

map<Weights, WeightRecord> * WeightMap::operator -> ()
{
  return & _weightmap;
}

WeightRecord & WeightMap::operator[] (Weights weight)
{
  return _weightmap[weight];
}

double WeightMap::GetWeight(Weights wgt, Vari vari, WorkEnum_t workmode)
{
  if (workmode == WorkEnum_t::GEN and not (wgt == Weights::NORM or wgt == Weights::GENERATOR))
    {
      return 1.0;
    }
  map<Weights, WeightRecord>::iterator it = _weightmap.find(wgt);
  if (it == _weightmap.end())
    {
      return 1.0;
    }
  WeightRecord weightrec = _weightmap[wgt];
  
  return weightrec.GetWeight(vari);
}

double WeightMap::GetWeight0(WorkEnum_t wmode)
{
  return GetWeight(Weights::NORM, Vari::NOMINAL, wmode) * 
    GetWeight(Weights::PU,              Vari::NOMINAL, wmode) * 
    GetWeight(Weights::TRIGSF,          Vari::NOMINAL, wmode) * 
    GetWeight(Weights::SELSF,           Vari::NOMINAL, wmode) *
    GetWeight(Weights::L1PREFIREPROB,   Vari::NOMINAL, wmode) *
    GetWeight(Weights::BOWLERLUNDBFRAG, Vari::NOMINAL, wmode) * 
    GetWeight(Weights::GENERATOR,       Vari::NOMINAL, wmode);
}

void WeightMap::Reset()
{
  _weightmap.clear();

}

void WeightMap::ls()
{
  for (map<Weights, WeightRecord>::iterator it = _weightmap.begin(); it != _weightmap.end(); it ++)
    {
      printf("%d\n", it -> first);
      printf("%s:\n", weightstitles.at(it -> first).Data());
      it -> second.ls();
    }
}

void WeightMap::Do()
{
  printf("Hi! I am a WeightMap\n");
}
