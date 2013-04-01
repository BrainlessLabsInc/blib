#ifndef __BLIB_OPERANDS_INCLUDED__
#define __BLIB_OPERANDS_INCLUDED__

#ifndef __BLIB_PLATFORM_TRAITS__
#include <blib/odra/PlatformTraits.hpp>
#endif
#ifndef __BLIB_UTILS_INCLUDED__
#include <blib/utils/Utils.hpp>
#endif
#ifndef BOOST_MPL_INT_HPP_INCLUDED
#include <boost/mpl/int.hpp>
#endif
#ifndef BOOST_MPL_MAP_HPP_INCLUDED
#include <boost/mpl/map.hpp>
#endif
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#include <boost/mpl/empty_base.hpp>
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
         kOpBin = 0x11,
         kOpInvalid = 666
      };
      typedef boost::mpl::int_<kOpNone> NoOpType;
      typedef boost::mpl::int_<kOpReg> OpRegType;
      typedef boost::mpl::int_<kOpMem> OpMemType;
      typedef boost::mpl::int_<kOpImm> OpImmType;
      typedef boost::mpl::int_<kOpLabel> OpLabelType;
      typedef boost::mpl::int_<kOpVar> OpVarType;
      typedef boost::mpl::int_<kOpBin> OpBinType;
      typedef boost::mpl::int_<kOpInvalid> OpInvalidType;
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
         return kOpIDValueInvalid;
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
   public:
      typedef blib::odra::operands::operand_details::EOperandType OperandTypeEnum;
      typedef blib::odra::operands::operand_details::EOperandIDMask OperandIDMaskType;
      typedef std::size_t SizeType;
   private:
      OperandTypeEnum _operandType;
      OperandIDMaskType _operandId;
      SizeType _regSize;
   public:
      // --------------------------------------------------------------------------
      // [Identification]
      // --------------------------------------------------------------------------
      OperandBase(const OperandTypeEnum aOperandType,
         const OperandIDMaskType aOperandId,const SizeType aSize)
         :_operandType(aOperandType),_operandId(aOperandId),_regSize(aSize)
      {
      }
      OperandBase()
         :_operandType(operand_details::kOpNone)
         ,_regSize(0)
         ,_operandId(operand_details::invalid_value<OperandIDMaskType>())
      {
      }
      OperandBase(const OperandBase& aRhs)
         :_operandType(aRhs._operandType)
         ,_regSize(aRhs._regSize)
         ,_operandId(aRhs._operandId)
      {
      }
      OperandBase& operator=(const OperandBase& aRhs)
      {
         _operandType = aRhs._operandType;
         _regSize = aRhs._regSize;
         _operandId = aRhs._operandId;
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
         _regSize = aSize;
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
         _operandId = aId;
      }
   };
}// namespace operands
}// namespace odra
}// namespace blib

namespace blib{namespace odra{namespace operands{namespace x86_64_operands_details{

   typedef blib::odra::operands::operand_details::EOperandType OperandTypeEnum;
   typedef blib::odra::operands::operand_details::EOperandIDMask OperandIDMaskType;
   typedef std::size_t SizeType;

   // ============================================================================
   // [AsmJit::SCALE]
   // ============================================================================

   //! @brief Scale, can be used for addressing.
   //!
   //! See @c Op and addressing methods like @c byte_ptr(), @c word_ptr(),
   //! @c dword_ptr(), etc...
   enum EScale
   {
      //! @brief Scale 1 times (no scale).
      kTimes1 = 0,
      //! @brief Scale 2 times (same as shifting to left by 1).
      kTimes2 = 1,
      //! @brief Scale 4 times (same as shifting to left by 2).
      kTimes3 = 2,
      //! @brief Scale 8 times (same as shifting to left by 3).
      kTimes4 = 3
   };

   // ============================================================================
   // [AsmJit::SEGMENT_PREFIX]
   // ============================================================================

   //! @brief Segment override prefixes.
   enum ESegmentPrefix
   {
      // DO NOT MODIFY INDEX CODES - They are used by _emitSegmentPrefix() and
      // by logger in the following order:
      //! @brief Use 'es' segment override prefix.
      kES = 0,
      //! @brief Use 'cs' segment override prefix.
      kCS = 1,
      //! @brief Use 'ss' segment override prefix.
      kSS = 2,
      //! @brief Use 'ds' segment override prefix.
      kDS = 3,
      //! @brief Use 'fs' segment override prefix.
      kFS = 4,
      //! @brief Use 'gs' segment override prefix.
      kGS = 5,
      //! @brief No segment override prefix.
      kSegmentNone = 0xF,
      //! @brief End of prefix codes
      kSegmentCount = 6
   };

   // ============================================================================
   // [AsmJit::VARIABLE_TYPE]
   // ============================================================================

   //! @brief Variable type.
   enum EVariableType
   {
      // --------------------------------------------------------------------------
      // [Platform Dependent]
      // --------------------------------------------------------------------------
      //! @brief Variable is 32-bit general purpose register.
      kVarTypeGPD = 0,
      //! @brief Variable is 64-bit general purpose register.
      kVarTypeGPQ = 1,
      //! @var VARIABLE_TYPE_GPN
      //! @brief Variable is system wide general purpose register (32-bit or 64-bit).
#if defined(ASMJIT_X86)
      kVarTypeGPN = kVarTypeGPD,
#else
      kVarTypeGPN = kVarTypeGPQ,
#endif
      //! @brief Variable is X87 (FPU).
      VARIABLE_TYPE_X87 = 2,
      //! @brief Variable is X87 (FPU) SP-FP number (float).
      kVarTypeX87_1F = 3,
      //! @brief Variable is X87 (FPU) DP-FP number (double).
      kVarTypeX87_1D = 4,
      //! @brief Variable is MM register / memory location.
      kVarTypeMM = 5,
      //! @brief Variable is XMM register / memory location.
      kVarTypeXMM = 6,
      //! @brief Variable is SSE scalar SP-FP number.
      kVarTypeXMM_1F = 7,
      //! @brief Variable is SSE packed SP-FP number (4 floats).
      kVarTypeXMM_4F = 8,
      //! @brief Variable is SSE2 scalar DP-FP number.
      kVarTypeXMM_1D = 9,
      //! @brief Variable is SSE2 packed DP-FP number (2 doubles).
      kVarTypeXMM_2D = 10,
      //! @brief Count of variable types.
      kVarTypeCOUNT = 11,

      // --------------------------------------------------------------------------
      // [Platform Independent]
      // --------------------------------------------------------------------------
      //! @brief Variable is 32-bit integer.
      kVarTypeINT32 = kVarTypeGPD,
      //! @brief Variable is 64-bit integer.
      kVarTypeINT64 = kVarTypeGPQ,
      //! @brief Variable is system dependent integer / pointer.
      kVarTypeINTPTR = kVarTypeGPN,
#if defined(__BLIB_PLATFORM64__)
      kVarTypeFLOAT = kVarTypeX87_1F,
      kVarTypeDOUBLE = kVarTypeX87_1D
#else
      kVarTypeFLOAT = kVarTypeXMM_1F,
      kVarTypeDOUBLE = kVarTypeXMM_1D
#endif
   };

   namespace od = ::blib::odra::operands::operand_details;
   //! @internal
   //! 
   //! @brief Register data.
   struct RegData
   {
      typedef boost::mpl::int_<od::kOpReg> OperandType;
      //! @brief Not used.
      boost::uint8_t _reserved[2];
      //! @brief Register code or variable, see @c REG and @c INVALID_VALUE.
      boost::uint32_t _code;
   };

   //! @internal
   //! 
   //! @brief Memory address data.
   struct MemData
   {
      typedef boost::mpl::int_<od::kOpMem> OperandType;
      //! @brief Memory operand type, see @c OPERAND_MEM_TYPE.
      od::EOperandMemType _type;
      //! @brief Segment override prefix, see @c SEGMENT_PREFIX.
      ESegmentPrefix _segmentPrefix;
      //! @brief Emit MOV/LEA instruction using 16-bit form of base/index registers.
      bool _sizePrefix;
      //! @brief Index register shift/scale (0 to 3 inclusive, see @c SCALE).
      boost::uint8_t _shift;
      //! @brief Base register index, variable or label id.
      boost::uint32_t _base;
      //! @brief Index register index or variable id.
      boost::uint32_t _index;
      //! @brief Target (for 32-bit, absolute address).
      void* _target;
      //! @brief Displacement.
      boost::int32_t _displacement;
   };

   //! @internal
   //! 
   //! @brief Immediate value data.
   struct ImmData
   {
      typedef boost::mpl::int_<od::kOpImm> OperandType;
      //! @brief @c true if immediate is unsigned.
      bool _isUnsigned;
      //! @brief Not used.
      boost::uint8_t _reserved;
      //! @brief Immediate value.
      boost::int32_t _value;
   };

   //! @internal
   //! 
   //! @brief Label data.
   struct LblData
   {
      typedef boost::mpl::int_<od::kOpLabel> OperandType;
   };

   //! @internal
   //! 
   //! @brief Variable data.
   struct VarData
   {
      typedef boost::mpl::int_<od::kOpVar> OperandType;
      //! @brief Not used.
      //! @brief Type (and later also code) of register, see @c REG_TYPE, @c REG_CODE.
      //!
      //! @note Register code and variable code are two different things. In most
      //! cases registerCode is very related to variableType, but general purpose
      //! registers are divided to 64-bit, 32-bit, 16-bit and 8-bit entities so
      //! the registerCode can be used to access these, variableType remains
      //! unchanged from the initialization state. Variable type describes mainly
      //! variable type and home memory size.
      boost::uint32_t _registerCode;
      //! @brief Type of variable. See @c VARIABLE_TYPE enum.
      EVariableType _variableType;
   };

   //! @brief Binary data.
   struct BinData
   {
      typedef boost::mpl::int_<od::kOpNone> OperandType;
      //! @brief First four 32-bit integers.
      boost::uint32_t _u32[4];
      //! @brief Second two 32 or 64-bit integers.
      boost::int32_t _s[2];
   };

   struct OperandTypeTraits
   {
      typedef boost::mpl::map<
         boost::mpl::pair<od::NoOpType, boost::mpl::empty_base>,
         boost::mpl::pair<od::OpRegType, RegData>,
         boost::mpl::pair<od::OpMemType, MemData>,
         boost::mpl::pair<od::OpImmType, ImmData>,
         boost::mpl::pair<od::OpLabelType, LblData>,
         boost::mpl::pair<od::OpVarType, VarData>,
         boost::mpl::pair<od::OpBinType, BinData>
      > OperandTypeMaps;
      typedef ::blib::odra::operands::OperandBase OperandBaseType;
   };
}// namespace x86_64_operands_details
}// namespace operands
}// namespace odra
}// namespace blib

namespace blib{namespace odra{namespace operands{

   template<typename OperandType, typename OperandTraits>
   struct Operand 
      : public OperandTraits::OperandBaseType,
      boost::mpl::at<typename OperandTraits::OperandTypeMaps, OperandType>::type
   {
      typedef typename OperandTraits::OperandBaseType OperandBaseType;
      typedef typename OperandBase::OperandTypeEnum OperandTypeEnum;
      typedef typename OperandBase::OperandIDMaskType OperandIDMaskType;
      typedef typename OperandBase::SizeType SizeType;
      Operand()
      {
      }
      Operand(const OperandTypeEnum aOperandType,
         const OperandIDMaskType aOperandId,const SizeType aSize)
         :OperandBase(aOperandType, aOperandId, aSize)
      {
      }
   };
}// namespace operand
}// namespace odra
}// namespace blib

namespace blib{namespace odra{namespace operands{namespace x86_64_operands_details{
      
   namespace od = ::blib::odra::operands::operand_details;
   class X86_64BaseRegType 
      :public Operand<od::OpRegType, OperandTypeTraits>
   {
 /*     X86_64BaseRegType()
         :_code(0)
      {
      }

      X86_64BaseRegType(const OperandTypeEnum aOperandType,
         const OperandIDMaskType aOperandId,
         const SizeType aSize,
         const boost::uint32_t aCode)
         :OperandBase(aOperandType, aOperandType, aSize),
         _code(aCode)
      {
      }*/
   };

   class GPReg : public X86_64BaseRegType
   {
   };
}// namespace x86_64_operands_details
}// namespace operands
}// namespace odra
}// namespace blib

#endif// __BLIB_OPERANDS_INCLUDED__