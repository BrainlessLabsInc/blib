#ifndef __BLIB_OPERANDS_INCLUDED__
#define __BLIB_OPERANDS_INCLUDED__

#ifndef __BLIB_PLATFORM_TRAITS__
#include <blib/odra/PlatformTraits.hpp>
#endif
#ifndef __BLIB_UTILS_INCLUDED__
#include <blib/utils/Utils.hpp>
#endif

namespace blib{namespace odra{namespace operands{
   namespace operand_details{
      using namespace blib::utils;
      template<typename T>
      T invalid_value();

      // ============================================================================
      // [EOperandType]
      // ============================================================================
      //! @brief Operand types that can be encoded in @c Op operand.
      enum EOperandType
      {
         //! @brief Operand is none, used only internally (not initialized Operand).
         //!
         //! This operand is not valid.
         kOpNone = 0x00,

         //! @brief Operand is register.
         kOpReg = 0x01,
         //! @brief Operand is memory.
         kOpMem = 0x02,
         //! @brief Operand is immediate.
         kOpImm = 0x04,
         //! @brief Operand is label.
         kOpLabel = 0x08,
         //! @brief Operand is variable.
         kOpVar = 0x10,
         kOpInvalid = 666
      };
      template<>
      EOperandType invalid_value<EOperandType>()
      {
         return kOpInvalid;
      }

      // ============================================================================
      // [EOperandMemType]
      // ============================================================================
      //! @brief Type of memory operand.
      enum EOperandMemType
      {
         //! @brief Operand is combination of register(s) and displacement (native).
         kOpMemNative = 0,
         //! @brief Operand is label.
         kOpMemLabel = 1,
         //! @brief Operand is absolute memory location (supported mainly in 32-bit 
         //! mode)
         kOpMemAbsolute = 2,
         kOpMemTypeInvalid = 666
      };
      template<>
      EOperandMemType invalid_value<EOperandMemType>()
      {
         return kOpMemTypeInvalid;
      }

      // ============================================================================
      // [EOperandIDMask]
      // ============================================================================
      //! @brief Operand ID masks used to determine the operand type.
      enum EOperandIDMask
      {
         //! @brief Operand id value mask (part used for IDs).
         kOpIDValueMask = 0x3FFFFFFF,
         //! @brief Operand id type mask (part used for operand type).
         kOpIDTypeMask  = 0xC0000000,
         //! @brief Label operand mark id.
         kOpIDTypeLabel = 0x40000000,
         //! @brief Variable operand mark id.
         kOpIDTypeVar   = 0x80000000,
         kOpIDValueInvalid = 0xFFFFFFFF
      };
      template<>
      EOperandIDMask invalid_value<EOperandIDMask>()
      {
         return kOpMemTypeInvalid;
      }

      // ============================================================================
      // [ECompilerProperty]
      // ============================================================================

      //! @brief @c Assembler/Compiler properties.
      enum ECompilerProperty
      {
         //! @brief Optimize align for current processor.
         //!
         //! Default: @c true.
         kCompPropertyOptimizeAlign = 0,

         //! @brief Emit hints added to jcc() instructions.
         //!
         //! Default: @c true.
         //!
         //! @note This is X86/X64 property only.
         kCompPropertyJumpHints = 1,
         kCompPropertyInvalid = 666
      };
      template<>
      ECompilerProperty invalid_value<ECompilerProperty>()
      {
         return kCompPropertyInvalid;
      }
   }//namespace operand_details

   class OperandBase
   {
      using namespace ;
   private:
      OperandTypeEnum _operandType;
      OperandIDMaskType _operandId;
      SizeType _regSize;
   public:
      typedef blib::odra::operand_details::EOperandType OperandTypeEnum;
      typedef blib::odra::operand_details::EOperandIDMask OperandIDMaskType;
      typedef std::size_t SizeType;
   public:
      // --------------------------------------------------------------------------
      // [Identification]
      // --------------------------------------------------------------------------
      OperandBase()
         :_operandType(OperandTypeEnum::kOpNone)
         ,_regSize(0)
         ,_operandId(invalid_value<OperandIDMaskType>())
      {
      }
      OperandBase(const OperandBase& aRhs)
         :_operandType(aRhs._operandType)
         ,_regSize(aRhs._regSize)
         ,_operandId(aRhs._operandId)
      {
      }
      OperandBase& operator=(const OperandBase& aRhs)
         :_operandType(aRhs._operandType)
         ,_regSize(aRhs._regSize)
         ,_operandId(aRhs._operandId)
      {
      }
      OperandTypeEnum operandTypeEnum()const
      {
         return _operandType;
      }
      OperandTypeEnum operandTypeEnum(const OperandTypeEnum aOpType)
      {
         _operandType = aOpType;
      }
      bool isOperandType(const OperandTypeEnum aOpType)const
      {
         return (aOpType == _operandType);
      }

      // --------------------------------------------------------------------------
      // [Operand Size]
      // --------------------------------------------------------------------------
      //! @brief Return size of operand in bytes.
      SizeType size()const
      {
         return _regSize;
      }
      void size(const SizeType aSize)
      {
         _regSize = aSize._regSize;
      }

      // --------------------------------------------------------------------------
      // [Operand Id]
      // --------------------------------------------------------------------------

      //! @brief Return operand Id (Operand Id's are used internally by 
      //! @c Assembler and @c Compiler classes).
      //!
      //! @note There is no way how to change or remove operand id. If you don't
      //! need the operand just assign different operand to this one.
      OperandIDMaskType id()const
      { 
         return _operandId; 
      }
      void id(const OperandIDMaskType aId)
      {
         _operandId = aId._operandId;
      }
   };
}// namespace operands
}// namespace odra
}// namespace blib
#endif// __BLIB_OPERANDS_INCLUDED__