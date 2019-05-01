#include "CFAT_Core.hh"
CFAT_Core::pf_iter::pf_iter()
{
  iter_core_ptr_ = NULL;
  CanDelete_     = true;
  tracked_vector_code_    = 255;
}



CFAT_Core::pf_iter::pf_iter(pf_iter && other): iter_core_ptr_(other.iter_core_ptr_), CanDelete_(other.CanDelete_)
{
  other.iter_core_ptr_ = NULL;
}

CFAT_Core::pf_iter::pf_iter(const pf_iter & other): iter_core_ptr_(other.iter_core_ptr_), CanDelete_(other.CanDelete_)
{
  core_ptr_ = NULL;
}

CFAT_Core::pf_iter_core * CFAT_Core::pf_iter::GetIterCore() const
{
  return iter_core_ptr_;
}

void CFAT_Core::pf_iter::SetCore(CFAT_Core & other)
{
  core_ptr_ = & other;
}

CFAT_Core * CFAT_Core::pf_iter::GetCore() const
{
  return core_ptr_;
}

 
void CFAT_Core::pf_iter::SetIterCore(pf_iter_core & other)
{
  iter_core_ptr_ = & other;
  other.iter_ptr_ = this;
}

void CFAT_Core::pf_iter::SetDeleteOption(bool option)
{
  CanDelete_ = option;
}

void CFAT_Core::pf_iter::SetTrackedVectorCode(VectorCode_t code)
{
  // set code tracked by the iterator
  tracked_vector_code_ = code;
}

VectorCode_t CFAT_Core::pf_iter::GetTrackedVectorCode() const
{
  // return vector code tracked by the iterator, 255 if tracking all jets
  return tracked_vector_code_;
}

CFAT_Core::pf_iter::~pf_iter()
{
  if (iter_core_ptr_ and CanDelete_)
    {
      delete iter_core_ptr_;
      iter_core_ptr_ = NULL;
    }
}

pf * CFAT_Core::pf_iter::operator -> ()
{
  return iter_core_ptr_ -> particle_ptr_; 
}

bool CFAT_Core::pf_iter::operator != (const pf_iter & other)
{
  
  return iter_core_ptr_ -> compare(other.iter_core_ptr_); 
}


CFAT_Core::pf_iter CFAT_Core::pf_iter::operator ++ (int)
{
  pf_iter ret = *this;
  core_ptr_ -> increment(*this);
  return ret;
}
