#include "ParticleFlowTools.hh"

Plane::Plane(const TLorentzVector & lv_left, const TLorentzVector & lv_right)
{
  v3_left_ = lv_left.Vect().Unit();
  v3_right_ = lv_right.Vect().Unit();
 

} 

Plane::Plane(const TVector3 & v3_left, const TVector3 & v3_right)
{
  v3_left_ = v3_left.Unit();
  v3_right_ = v3_right.Unit();
  

}

void Plane::ls() const
{
  printf("Left  x %f y %f z %f\n", v3_left_.Px(), v3_left_.Py(), v3_left_.Pz());
  printf("Right x %f y %f z %f\n", v3_right_.Px(), v3_right_.Py(), v3_right_.Pz());
  
}


double Plane::DefAngle() const
{
  return v3_right_.Angle(v3_left_);
}

double Plane::angle_right(const TVector3 &other) const
{
  const TVector3 proj = Project(other);
  return proj.Angle(v3_right_);
}

double Plane::angle_left(const TVector3 &other) const
{
  const TVector3 proj = Project(other);
  return proj.Angle(v3_left_);
}


void Plane::SwitchDef()
{
  const TVector3 store = v3_left_;
  v3_left_ = v3_right_;
  v3_right_ = store;
}
 
bool Plane::ProjectsInside(const TVector3 & v3) const
{
  const TVector3 projection = Project(v3);
  const double angle_right = projection.Angle(v3_right_);
  const double angle_left = projection.Angle(v3_left_);
  return fabs(angle_right + angle_left - DefAngle()) < 1E-12;
}

TVector3 Plane::Normal() const
{
  return v3_right_.Cross(v3_left_);
}

TVector3 Plane::Project(const TVector3 & v3) const
{
  const TVector3 normal = Normal();
  return normal.Cross(v3.Cross(normal));

}
