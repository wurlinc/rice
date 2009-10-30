#include "method_data.hpp"

// TODO: This is silly, autoconf...
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include "../config.hpp"


#if defined(HAVE_NODE_H)
/* pre-YARV */
#include <node.h>
#elif defined(REALLY_HAVE_RUBY_NODE_H)
/* YARV */
#include <ruby/node.h>
#else
/* YARV without node.h */
#include "mininode.hpp"
using namespace Rice::detail::Mininode;
#endif

#include "env.hpp"

#ifdef RUBY_VM
/* YARV */
#include "cfp.hpp"
#endif

namespace
{

#ifdef RUBY_VM

/* YARV */

/* On YARV, we store the method data on the stack.  We don't have to pop
 * it off the stack, because the stack pointer will be reset to the
 * previous frame's stack pointer when the function returns.
 */
static void fix_frame()
{
#if 0
  VALUE * cfp = Rice::detail::cfp();
  VALUE & memo_node = Rice::detail::cfp_data_memo_node_and_pc(cfp);
  VALUE & method_class = Rice::detail::cfp_method_class(cfp);

  memo_node = RBASIC(method_class)->klass;

  if(rb_type(memo_node) != T_NODE)
  {
    /* This can happen for module functions that are created after
     * the stub function */
    rb_raise(
        rb_eRuntimeError,
        "Cannot find method data for module function");
  }
  else
  {
    method_class = RCLASS_SUPER(method_class);
  }
#endif
}

#define FIX_FRAME() \
  fix_frame()

static NODE * data_memo_node()
{
/*
  VALUE * cfp = Rice::detail::cfp();
  VALUE & memo_node = Rice::detail::cfp_data_memo_node_and_pc(cfp);
  return (NODE *)memo_node;
*/
  ID id;
  VALUE klass;
  if (!rb_frame_method_id_and_class(&id, &klass))
  {
    rb_raise(
        rb_eRuntimeError,
        "Cannot get method id and class for function");
  }

  VALUE memo_node = RBASIC(klass)->klass;

  if(rb_type(memo_node) != T_NODE)
  {
    /* This can happen for module functions that are created after
     * the stub function */
    rb_raise(
        rb_eRuntimeError,
        "Cannot find method data for module function");
  }

  return (NODE *)memo_node;
}

#else

/* pre-YARV */

/* Okay to not pop this temporary frame, since it will be popped by the
 * caller
 */
#define FIX_FRAME() \
  struct FRAME _frame = *ruby_frame; \
  _frame.last_class = RCLASS(ruby_frame->last_class)->super; \
  _frame.prev = ruby_frame; \
  ruby_frame = &_frame; \

static NODE * data_memo_node()
{
  return (NODE *)(RBASIC(ruby_frame->prev->last_class)->klass);
}

#endif

typedef VALUE (*Method_Func)(ANYARGS);

static Method_Func actual_cfunc()
{
  return data_memo_node()->nd_cfnc;
}

static VALUE data_wrapper_m1(int argc, VALUE * argv, VALUE self)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(argc, argv, self);
  return result;
}

static VALUE data_wrapper_0(VALUE self)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self);
  return result;
}

static VALUE data_wrapper_1(VALUE self, VALUE arg1)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1);
  return result;
}
static VALUE data_wrapper_2(VALUE self, VALUE arg1, VALUE arg2)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2);
  return result;
}
static VALUE data_wrapper_3(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3);
  return result;
}
static VALUE data_wrapper_4(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4);
  return result;
}
static VALUE data_wrapper_5(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5);
  return result;
}
static VALUE data_wrapper_6(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6);
  return result;
}
static VALUE data_wrapper_7(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return result;
}
static VALUE data_wrapper_8(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
  return result;
}
static VALUE data_wrapper_9(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
  return result;
}
static VALUE data_wrapper_10(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9, VALUE arg10)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
  return result;
}
static VALUE data_wrapper_11(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9, VALUE arg10, VALUE arg11)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
  return result;
}
static VALUE data_wrapper_12(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9, VALUE arg10, VALUE arg11, VALUE arg12)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
  return result;
}
static VALUE data_wrapper_13(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9, VALUE arg10, VALUE arg11, VALUE arg12, VALUE arg13)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
  return result;
}
static VALUE data_wrapper_14(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9, VALUE arg10, VALUE arg11, VALUE arg12, VALUE arg13, VALUE arg14)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14);
  return result;
}
static VALUE data_wrapper_15(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9, VALUE arg10, VALUE arg11, VALUE arg12, VALUE arg13, VALUE arg14, VALUE arg15)
{
  VALUE result;
  FIX_FRAME();
  result = (*actual_cfunc())(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15);
  return result;
}

} // namespace

/* Define a method and attach data to it.
 *
 * The method looks to ruby like a normal aliased CFUNC, with a modified
 * origin class:
 *
 * NODE_FBODY
 *   |- (u1) orig - origin class
 *   |  |- basic
 *   |  |  |- flags - origin class flags + FL_SINGLETON
 *   |  |  +- klass - NODE_MEMO
 *   |  |     |- (u1) cfnc - actual C function to call
 *   |  |     |- (u2) rval - stored data
 *   |  |     +- (u3) 0
 *   |  |- iv_tbl - 0
 *   |  |- m_tbl - 0
 *   |  +- super - actual origin class
 *   |- (u2) mid - name of the method
 *   +- (u3) head - NODE_CFUNC
 *      |- (u1) cfnc - wrapper function to call
 *      +- (u2) argc - function arity
 *
 * Or, on YARV:
 *
 * NODE_FBODY
 *   |- (u1) oid - name of the method
 *   +- (u2) body - NODE_METHOD
 *      |- (u1) clss - origin class
 *      |  |- basic
 *      |  |  |- flags - origin class flags + FL_SINGLETON
 *      |  |  +- klass - NODE_MEMO
 *      |  |     |- (u1) cfnc - actual C function to call
 *      |  |     |- (u2) rval - stored data
 *      |  |     +- (u3) 0
 *      |  |- ptr - rb_classext_t
 *      |  |  |- super - actual origin class
 *      |  |  +- iv_tbl - 0
 *      |  |- m_tbl - 0
 *      |  +- iv_index_tbl - 0?
 *      |- (u2) body - NODE_CFUNC
 *      |  |- (u1) cfnc - wrapper function to call
 *      |  |- (u2) argc - function arity
 *      +- (u3) noex - NOEX_PUBLIC
 *
 * When the wrapper function is called, last_class is set to the origin
 * class found in the FBODY node.  So that the method data will be
 * accessible, and so last_class will point to klass and not to our MEMO
 * node, it is necessary to "fix" the current frame.
 *
 * Pre-YARV, this means we duplicate the current frame and set last_class:
 *
 * ruby_frame
 *   |- last_class - klass
 *   |- prev
 *   |  |- last_class - NODE_MEMO
 *   |  |  |- (u1) cfnc - actual C function to call
 *   |  |  |- (u2) rval - stored data
 *   |  |  +- (u3) 0
 *   |  |- prev - the real previous frame
 *   |  +- ...
 *   +- ...
 *
 * The method data is then accessible via
 * ruby_frame->prev->last_class->rval.
 *
 * On YARV, the current frame is not duplicated; rather, the method data
 * is placed on the stack and is referenced by one of the unused members
 * of the control frame (the program counter):
 *
 * ruby_current_thread->cfp
 *   |- pc - NODE_MEMO
 *   |  |- (u1) cfnc - actual C function to call
 *   |  |- (u2) rval - stored data
 *   |  +- (u3) 0
 *   |- method_class - klass
 *   +- ...
 *
 */
VALUE
Rice::detail::
define_method_with_data(
    VALUE klass, ID id, VALUE (*cfunc)(ANYARGS), int arity, VALUE data)
{
  /* TODO: origin should have #to_s and #inspect methods defined */
#ifdef HAVE_RB_CLASS_BOOT
  VALUE origin = rb_class_boot(klass);
#else
  VALUE origin = rb_class_new(klass);
#endif
  NODE * node;

  VALUE (*data_wrapper)(ANYARGS);
  switch(arity)
  {
    case 0: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_0); break;
    case 1: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_1); break;
    case 2: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_2); break;
    case 3: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_3); break;
    case 4: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_4); break;
    case 5: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_5); break;
    case 6: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_6); break;
    case 7: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_7); break;
    case 8: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_8); break;
    case 9: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_9); break;
    case 10: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_10); break;
    case 11: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_11); break;
    case 12: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_12); break;
    case 13: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_13); break;
    case 14: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_14); break;
    case 15: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_15); break;
    case -1: data_wrapper = RUBY_METHOD_FUNC(data_wrapper_m1); break;
    default: rb_raise(rb_eArgError, "unsupported arity %d", arity);
  }

  FL_SET(origin, FL_SINGLETON);
  rb_singleton_class_attached(origin, klass);
  rb_name_class(origin, SYM2ID(rb_class_name(klass)));

  RBASIC(origin)->klass = (VALUE)NEW_NODE(NODE_MEMO, cfunc, data, 0);

#ifdef RUBY_VM
  /* YARV */
  rb_define_method(
      origin,
      rb_id2name(id),
      data_wrapper,
      arity);
  rb_alias(
      origin,
      rb_intern("dummy"),
      id);
  st_lookup(RCLASS_M_TBL(origin), rb_intern("dummy"), (st_data_t *)&node);
  st_insert(RCLASS_M_TBL(klass), id, (st_data_t)node);

  // Clear the table so we don't try to double-free the method entry
  RCLASS_M_TBL(origin) = st_init_numtable();
#else
  /* pre-YARV */
  node = NEW_FBODY(
      NEW_CFUNC(data_wrapper, arity),
      id,
      origin);
  rb_add_method(klass, id, node, NOEX_PUBLIC);
#endif

  return Qnil;
}

VALUE
Rice::detail::
method_data()
{
  return data_memo_node()->nd_rval;
}

