#include "pf.hh"
 
void pf::Do()
{
  printf("Hello from pf %p\n", this);
}

void pf::ls() const
{
  const TLorentzVector  lv = GetLorentzVector();
  printf("Pt %f Px %f Py %f Pz %f E %f\n", lv.Pt(), lv.Px(), lv.Py(), lv.Pz(), lv.E());
}
