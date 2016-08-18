#include "TLorentzVector.h"
class Plane
{
  TVector3 v3_left_;
  TVector3 v3_right_;
public:
  Plane(const TLorentzVector &, const TLorentzVector &);
  Plane(const TVector3 &, const TVector3 &);
  void ls() const;
  double DefAngle() const;
  double angle_right(const TVector3 &) const;
  double angle_left(const TVector3 &) const;
  bool ProjectsInside(const TVector3 &) const;
  void SwitchDef();
  TVector3 Project(const TVector3 &) const;
  TVector3 Normal() const;
};
