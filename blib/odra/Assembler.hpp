#ifndef __BLIB_ASSEMBLER_INCLUDED__
#define __BLIB_ASSEMBLER_INCLUDED__

#ifndef __BLIB_INSTRUCTIONDETAILS_INCLUDED__
#include <blib/odra/InstructionDetails.hpp>
#endif
#ifndef __BLIB_SYSTEM_INFO_INCLUDED__
#include <blib/sys/system_info.hpp>
#endif
#ifndef __BLIB_MEMORY_INCLUDED__
#include <blib/odra/Memory.hpp>
#endif
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#include <boost/mpl/empty_base.hpp>
#endif

namespace blib{namespace odra{namespace assembler{
   typedef boost::mpl::empty_base NullDebugger;

   template<class ExecutableBuffer = blib::odra::memory::ExeBuffer>
   class AssemblerBuffer
   {
   public:
      typedef typename ExecutableBuffer::value_type value_type;
      typedef typename ExecutableBuffer::pointer pointer;
      typedef typename ExecutableBuffer::const_pointer const_pointer;
      typedef typename ExecutableBuffer::size_type size_type;
      typedef ExecutableBuffer BufferType;
   private:
      ExecutableBuffer _codeBuffer;
   public:
      ~AssemblerBuffer()
      {
      }
      const_pointer* code()const
      {
         return _codeBuffer.data();
      }
      size_type codeSize()const
      {
         _codeBuffer.size();
      }
      void clearCodeBuffer()
      {
         _codeBuffer.clear();
      }
      void pushBackCode(const value_type aByte)
      {
         _codeBuffer.push_back(aByte);
      }
      template<typename Size>
      void pushBackCode(const Size aWord)
      {
         _codeBuffer += (pointer)&aWord;
      }
   };

   template<class PlatformTraits = blib::system_info::SystemInfo
         ,class InstructionTraits = blib::odra::instruction_details::InstructionTraits
         ,class ExecutableBuffer = blib::odra::memory::ExeBuffer
         ,class DebuggerTraits = NullDebugger>
   class Assembler
   {
   private:
      //ExecutableBuffer _codeBuffer;
   public:
      //! @brief Emit single @a opCode without operands.
      //void pushBackOpCode(const boost::uint32_t aOpCode)
      //{
      //   // instruction prefix
      //   if (aOpCode & 0xFF000000)
      //   {
      //      pushBackCode((boost::uint8_t)((aOpCode & 0xFF000000) >> 24));
      //   }
      //   // instruction opcodes
      //   if (aOpCode & 0x00FF0000)
      //   {
      //      pushBackCode((boost::uint8_t)((aOpCode & 0x00FF0000) >> 16));
      //   }
      //   if (aOpCode & 0x0000FF00)
      //   {
      //      pushBackCode((boost::uint8_t)((aOpCode & 0x0000FF00) >>  8));
      //   }
      //   // last opcode is always emitted (can be also 0x00)
      //   pushBackCode((boost::uint8_t)(aOpCode & 0x000000FF));
      //}
      //! @brief Emit CS (code segmend) prefix. TODO
      //!
      //! Behavior of this function is to emit code prefix only if memory operand
      //! address uses code segment. Code segment is used through memory operand
      //! with attached @c AsmJit::Label.
      // void _emitSegmentPrefix(const Operand& rm)

      //! @brief Emit MODR/M byte.
      //void pushBackMod(const boost::uint8_t m, const boost::uint8_t o, const boost::uint8_t r)
      //{ 
      //   pushBackCode(((m & 0x03) << 6) | ((o & 0x07) << 3) | (r & 0x07));
      //}

      //! @brief Emit SIB byte.
      //void pushBackSib(const boost::uint8_t s, const boost::uint8_t i, const boost::uint8_t b)
      //{ 
      //   pushBackCode(((s & 0x03) << 6) | ((i & 0x07) << 3) | (b & 0x07));
      //}

//      //! @brief Emit REX prefix (64-bit mode only).
//      void pushBackRexR(const boost::uint8_t w, const boost::uint8_t opReg, const boost::uint8_t regCode, const bool forceRexPrefix)
//      {
//#if defined(__BLIB_PLATFORM64__)
//         const boost::uint8_t r = (opReg & 0x8) != 0;
//         const boost::uint8_t b = (regCode & 0x8) != 0;
//
//         // w Default operand size(0=Default, 1=64-bit).
//         // r Register field (1=high bit extension of the ModR/M REG field).
//         // x Index field not used in RexR
//         // b Base field (1=high bit extension of the ModR/M or SIB Base field).
//         if (w || r || b || forceRexPrefix)
//         {
//            pushBackCode(0x40 | (w << 3) | (r << 2) | b);
//         }
//#else
//         BLIB_UNUSED(w);
//         BLIB_UNUSED(opReg);
//         BLIB_UNUSED(regCode);
//         BLIB_UNUSED(forceRexPrefix);
//#endif // __BLIB_PLATFORM64__
//      }
/*TODO
      //! @brief Emit REX prefix (64-bit mode only).
      void pushBackRexRM(uint8_t w, uint8_t opReg, const Operand& rm, bool forceRexPrefix) ASMJIT_NOTHROW
      {
#if defined(__BLIB_PLATFORM64__)
         uint8_t r = (opReg & 0x8) != 0;
         uint8_t x = 0;
         uint8_t b = 0;

         if (rm.isReg())
         {
            b = (reinterpret_cast<const BaseReg&>(rm).getRegCode() & 0x8) != 0;
         }
         else if (rm.isMem())
         {
            x = ((reinterpret_cast<const Mem&>(rm).getIndex() & 0x8) != 0) & (reinterpret_cast<const Mem&>(rm).getIndex() != INVALID_VALUE);
            b = ((reinterpret_cast<const Mem&>(rm).getBase() & 0x8) != 0) & (reinterpret_cast<const Mem&>(rm).getBase() != INVALID_VALUE);
         }

         // w Default operand size(0=Default, 1=64-bit).
         // r Register field (1=high bit extension of the ModR/M REG field).
         // x Index field (1=high bit extension of the SIB Index field).
         // b Base field (1=high bit extension of the ModR/M or SIB Base field).
         if (w || r || x || b || forceRexPrefix)
         {
            _emitByte(0x40 | (w << 3) | (r << 2) | (x << 1) | b);
         }
#else
         BLIB_UNUSED(w);
         BLIB_UNUSED(opReg);
         BLIB_UNUSED(rm);
#endif // 
      }
      */
   };// class Assembler

}// namespace assembler
}// namespace odra
}// namespace blib
#endif// __BLIB_ASSEMBLER_INCLUDED__
