#ifndef Rice__detail__Caster__hpp_
#define Rice__detail__Caster__hpp_

#include "../Module.hpp"
#include <stdexcept>

namespace Rice
{

namespace detail
{

class Abstract_Caster
{
public:
  virtual void * cast_to_base(void * derived, Module type) const = 0;
  virtual ~Abstract_Caster() { }
  virtual bool can_cast_to(Module type) const = 0;
};

/**
 * Caster implementation that supports casting up and
 * down the type heirarchy.
 */
template<typename Derived_T, typename Base_T>
class Caster
  : public Abstract_Caster
{
public:
  Caster(Abstract_Caster * base_caster, Module type)
    : base_caster_(base_caster)
    , type_(type)
  {
  }

  virtual bool can_cast_to(Module type) const
  {
    return type.value() == type_.value();
  }

protected:
  virtual void * cast_to_base(void * derived, Module type) const
  {
    if(can_cast_to(type))
    {
      Derived_T * d(static_cast<Derived_T *>(derived));
      return static_cast<Base_T *>(d);
    }
    else
    {
      if(base_caster_)
      {
        return base_caster_->cast_to_base(derived, type);
      }
      else
      {
        std::string s = "bad cast. No caster found for ";
        s += type_.name().str();
        throw std::runtime_error(s);
      }
    }
  }

private:
  Abstract_Caster * base_caster_;
  Module type_;
};

template<typename T>
class ImplicitCaster
  : public Abstract_Caster
{
  public:
    typedef To_T CastToType;

    ImplicitTypeCaster(Abstract_Caster* base)
      : base_caster_(base)
    {}

    From_T* implicit_cast(void * in, Module type) const
    {
      return new From_T(static_cast<To_T>(base_caster_->cast_to_base(in, type)));
    }

    virtual bool can_cast_to(Module type) const
    {
      return base_caster_->can_cast_to(type);
    }

  protected:
    virtual void * cast_to_base(void * derived, Module type) const
    {
        throw std::runtime_error(std::string("Implicit caster not implemented yet"));
    }

  private:
    Abstract_Caster * base_caster_;
};



} // detail

} // Rice

#endif //Rice__detail__Caster__hpp_
