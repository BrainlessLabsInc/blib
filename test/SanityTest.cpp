#ifndef __BLIB_ODRA_INCLUDED__
#include <blib/odra.hpp>
#endif

void sanity()
{
   blib::odra::operands::Operand<blib::odra::operands::operand_details::OpRegType, 
      blib::odra::operands::x86_64_operands_details::OperandTypeTraits> t;
   ::blib::odra::operands::x86_64_operands_details::GPReg gp;
}