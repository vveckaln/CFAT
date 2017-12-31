#include "CFAT_Core.hh"
CFAT_Core::pf_iter_core::pf_iter_core(pf * particle ): particle_ptr_(particle)
{
  tracked_vector_ = 255;
}

CFAT_Core::pf_iter_core::~pf_iter_core()
{
}

void CFAT_Core::pf_iter_core::Do()
{
  printf("Hello from CFAT_Core::pf_iter_core %p\n", this);
}

CFAT_Core::pf_iter * CFAT_Core::pf_iter_core::GetIter() const
{
  return iter_ptr_;
}

void CFAT_Core::pf_iter_core::WhoAmI()
{
  printf("I am CFAT_Core::pf_iter_core %p\n", this);
}
