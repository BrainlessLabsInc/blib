#ifndef __BLIB_SYSTEM_INFO_INCLUDED__
#define __BLIB_SYSTEM_INFO_INCLUDED__

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif
#ifndef __BLIB_PLATFORM_CONFIG_INCLUDED__
#include <blib/config/platform_config.hpp>
#endif
#ifndef __BLIB_SINGLETON_INCLUDED__
#include <blib/idioms/Sigleton.hpp>
#endif
#ifndef BOOST_CSTDINT_HPP
#include <boost/cstdint.hpp>
#endif
#ifndef __STD_ALGORITHM_INCLUDED__
#define __STD_ALGORITHM_INCLUDED__
#include <algorithm>
#endif
#ifndef __STD_STRING_INCLUDED__
#define __STD_STRING_INCLUDED__
#include <string>
#endif
#ifndef __STD_BITSET_INCLUDED__
#define __STD_BITSET_INCLUDED__
#include <bitset>
#endif
#ifndef BOOST_LEXICAL_CAST_INCLUDED
#include <boost/lexical_cast.hpp>
#endif
#if defined(BOOST_WINDOWS)
#ifndef _WINDOWS_
#include <windows.h>
#endif
#elif defined(__BLIB_POSIX__)
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#endif
/* Need to do this here because intrin.h has C++ code in it */
/* Visual Studio 2005 has a bug where intrin.h conflicts with winnt.h */
#if defined(_MSC_VER) && (_MSC_VER >= 1500)
#include <intrin.h>
#ifndef _WIN64
#define __MMX__
#define __3dNOW__
#endif
#define __SSE__
#define __SSE2__
#elif defined(__MINGW64_VERSION_MAJOR)
#include <intrin.h>
#else
#ifdef __ALTIVEC__
#if HAVE_ALTIVEC_H && !defined(__APPLE_ALTIVEC__)
#include <altivec.h>
#undef pixel
#endif
#endif
#ifdef __MMX__
#include <mmintrin.h>
#endif
#ifdef __3dNOW__
#include <mm3dnow.h>
#endif
#ifdef __SSE__
#include <xmmintrin.h>
#endif
#ifdef __SSE2__
#include <emmintrin.h>
#endif
#endif
#if defined(__MACOSX__) && (defined(__ppc__) || defined(__ppc64__))
#include <sys/sysctl.h>         /* For AltiVec check */
#elif defined(__OpenBSD__) && defined(__powerpc__)
#include <sys/param.h>
#include <sys/sysctl.h> /* For AltiVec check */
#include <machine/cpu.h>
//#elif SDL_ALTIVEC_BLITTERS && HAVE_SETJMP
//#include <signal.h>
//#include <setjmp.h>
#endif

namespace blib{namespace system_info{

   namespace cpu_info{
      //! @brief X86/X64 CPU features.
      enum FeatureBitIndex
      {
         //! @brief Cpu has RDTSC instruction.
         kFeatureRDTSC = 0,
         //! @brief Cpu has RDTSCP instruction.
         kFeatureRDTSCP = 1,
         //! @brief Cpu has CMOV instruction (conditional move)
         kFeatureCMOV = 2,
         //! @brief Cpu has CMPXCHG8B instruction
         kFeatureCMPXCHG8B = 3,
         //! @brief Cpu has CMPXCHG16B instruction (64 bit processors)
         kFeatureCMPXCHG16B = 4,
         //! @brief Cpu has CLFUSH instruction
         kFeatureCLFLUSH = 5,
         //! @brief Cpu has PREFETCH instruction
         kFeaturekPREFETCH = 6,
         //! @brief Cpu supports LAHF and SAHF instrictions.
         kFeatureLAHFSAHF = 7,
         //! @brief Cpu supports FXSAVE and FXRSTOR instructions.
         kFeatureFXSR = 8,
         //! @brief Cpu supports FXSAVE and FXRSTOR instruction optimizations (FFXSR).
         kFeatureFFXSR = 9,

         //! @brief Cpu has MMX.
         kFeatureMMX = 10,
         //! @brief Cpu has extended MMX.
         kFeatureMMXExt = 11,
         //! @brief Cpu has 3dNow!
         kFeature3dNow = 12,
         //! @brief Cpu has enchanced 3dNow!
         kFeature3dNowExt = 13,
         //! @brief Cpu has SSE.
         kFeatureSSE = 14,
         //! @brief Cpu has Misaligned SSE (MSSE).
         kFeatureMSSE = 15,
         //! @brief Cpu has SSE2.
         kFeatureSSE2 = 16,
         //! @brief Cpu has SSE3.
         kFeatureSSE3 = 17,
         //! @brief Cpu has Supplemental SSE3 (SSSE3).
         kFeatureSSSE3 = 18,
         //! @brief Cpu has SSE4.A.
         kFeatureSSE4_A = 19,
         //! @brief Cpu has SSE4.1.
         kFeatureSSE4_1 = 20,
         //! @brief Cpu has SSE4.2.
         kFeatureSSE4_2 = 21,
         //! @brief Cpu has SSE5.
         kFeatureSSE5 = 22,
         //! @brief Cpu supports MONITOR and MWAIT instructions.
         kFeatureMonitorMWait = 23,
         //! @brief Cpu supports POPCNT instruction.
         kFeaturePOPCNT = 24,
         //! @brief Cpu supports LZCNT instruction.
         kFeatureLZCNT  = 25,
         //! @brief Cpu supports PCLMULDQ set of instructions.
         kX86FeaturePCLMULDQ  = 26,
         //! @brief Cpu supports multithreading.
         kFeatureMultiThreading = 27,
         //! @brief Cpu supports execute disable bit (execute protection).
         kFeatureExecuteDisableBit = 28,
         //! @brief Cpu supports 64 bits.
         kFeature64Bit = 29,
         kFeatureMOVBE = 30,
         kFeatureAVX = 31,
         kFeaturePrefetch = 32,
         kFeatureEnd
      };

      //! @brief X86/X64 CPU bugs.
      enum BugBitIndex
      {
         kBugAmdLockMB = 0,
         kNoBug = 1,
         kBugEnd
      };

      //! @brief Cpu vendor IDs.
      //! Cpu vendor IDs are specific for AsmJit library. Vendor ID is not directly
      //! read from cpuid result, instead it's based on CPU vendor string.
      enum CpuVendorIds
      {
         //! @brief Intel CPU vendor.
         kCpuIntel = 0,
         //! @brief AMD CPU vendor.
         kCpuAmd = 1,
         //! @brief National Semiconductor CPU vendor (applies also to Cyrix processors).
         kCpuNSM = 2,
         //! @brief Transmeta CPU vendor.
         kCpuTransmeta = 3,
         //! @brief VIA CPU vendor.
         kCpuVia = 4,
         //! @brief Unknown CPU vendor.
         kCpuIdEnd,
         kCpuUnknown = 666
      };
   }
}
}

namespace boost{
   template<>
   inline blib::system_info::cpu_info::CpuVendorIds 
      lexical_cast<blib::system_info::cpu_info::CpuVendorIds,std::string>(const std::string& aSource)
   {
      if("GenuineIntel" == aSource)
      {
         return blib::system_info::cpu_info::kCpuIntel;
      }
      else if(("AuthenticAMD" == aSource) || ("AMDisbetter!" == aSource))
      {
         return blib::system_info::cpu_info::kCpuAmd;
      }
      else if(("Geode by NSC" == aSource) || ("CyrixInstead" == aSource))
      {
         return blib::system_info::cpu_info::kCpuNSM;
      }
      else if(("GenuineTMx86" == aSource) || ("TransmetaCPU" == aSource))
      {
         return blib::system_info::cpu_info::kCpuTransmeta;
      }
      else if(("VIA0VIA0VIA0" == aSource) || ("CentaurHauls" == aSource))
      {
         return blib::system_info::cpu_info::kCpuVia;
      }
      else if("Unknown" == aSource)
      {
         blib::system_info::cpu_info::kCpuUnknown;
      }
   }
}

namespace blib{namespace system_info{

   namespace cpu_info{
      /*
      * This is a guess for the cacheline size used for padding.
      * Most x86 processors have a 64 byte cache line.
      * The 64-bit PowerPC processors have a 128 byte cache line.
      * We'll use the larger value to be generally safe.
      * Taken from SDL
      */
      struct CPUInfoTraits
      {
         typedef boost::uint32_t DefIntType;
         typedef FeatureBitIndex FeatureBitIndexType;
         typedef BugBitIndex BugBitIndexType;
         static const DefIntType kDefaultCacheLineSize = 128;
         static const DefIntType kVendorStringMaxSize = 16;
         static const DefIntType kBrandStringMaxSize = 64;
         static const DefIntType kDefaultPageSize = 1024*4;
      };
//http://code.google.com/p/libjingle/source/browse/trunk/talk/session/phone/cpuid.cc?r=144
      struct CPUInfoHelper
      {
         static int numberOfProcessors()
         {
            int retVal = 1; // If we are executing program at least one processor is there :)
#if defined(BOOST_WINDOWS)
            SYSTEM_INFO info = {0};
            GetSystemInfo(&info);
            retVal = info.dwNumberOfProcessors;
#elif defined(__BLIB_POSIX__) && defined(_SC_NPROCESSORS_ONLN)
            // It seems that sysconf returns the number of "logical" processors on both
            // mac and linux.  So we get the number of "online logical" processors.
            const long num = sysconf(_SC_NPROCESSORS_ONLN);
            if (-1 != num)
            {
               retVal = static_cast<UInt32>(num);
            }
#endif
            return retVal;
         }

         static int pageSize()
         {
            int retVal = 1;
#if defined(BOOST_WINDOWS)
            SYSTEM_INFO info = {0};
            GetSystemInfo(&info);
            retVal = info.dwPageSize;
#elif defined(__BLIB_POSIX__)
            const long num = sysconf(_SC_PAGE_SIZE);
            if (-1 != num)
            {
               retVal = static_cast<UInt32>(num);
            }
#endif
            return retVal;
         }


         static bool haveCPUID()
         {
            int retVal = 0;
            /* *INDENT-OFF* */
#if defined(__GNUC__) && defined(i386)
            __asm__ (
               "        pushfl                      # Get original EFLAGS             \n"
               "        popl    %%eax                                                 \n"
               "        movl    %%eax,%%ecx                                           \n"
               "        xorl    $0x200000,%%eax     # Flip ID bit in EFLAGS           \n"
               "        pushl   %%eax               # Save new EFLAGS value on stack  \n"
               "        popfl                       # Replace current EFLAGS value    \n"
               "        pushfl                      # Get new EFLAGS                  \n"
               "        popl    %%eax               # Store new EFLAGS in EAX         \n"
               "        xorl    %%ecx,%%eax         # Can not toggle ID bit,          \n"
               "        jz      1f                  # Processor=80486                 \n"
               "        movl    $1,%0               # We have CPUID support           \n"
               "1:                                                                    \n"
               : "=m" (retVal)
               :
            : "%eax", "%ecx"
               );
#elif defined(__GNUC__) && defined(__x86_64__)
            /* Technically, if this is being compiled under __x86_64__ then it has
            CPUid by definition.  But it's nice to be able to prove it.  :)      */
            __asm__ (
               "        pushfq                      # Get original EFLAGS             \n"
               "        popq    %%rax                                                 \n"
               "        movq    %%rax,%%rcx                                           \n"
               "        xorl    $0x200000,%%eax     # Flip ID bit in EFLAGS           \n"
               "        pushq   %%rax               # Save new EFLAGS value on stack  \n"
               "        popfq                       # Replace current EFLAGS value    \n"
               "        pushfq                      # Get new EFLAGS                  \n"
               "        popq    %%rax               # Store new EFLAGS in EAX         \n"
               "        xorl    %%ecx,%%eax         # Can not toggle ID bit,          \n"
               "        jz      1f                  # Processor=80486                 \n"
               "        movl    $1,%0               # We have CPUID support           \n"
               "1:                                                                    \n"
               : "=m" (retVal)
               :
            : "%rax", "%rcx"
               );
            //#elif (defined(_MSC_VER) && defined(_M_IX86)) || defined(__WATCOMC__)
            //            __asm {
            //               pushfd                      ; Get original EFLAGS
            //                  pop     eax
            //                  mov     ecx, eax
            //                  xor     eax, 200000h        ; Flip ID bit in EFLAGS
            //                  push    eax                 ; Save new EFLAGS value on stack
            //                  popfd                       ; Replace current EFLAGS value
            //                  pushfd                      ; Get new EFLAGS
            //                  pop     eax                 ; Store new EFLAGS in EAX
            //                  xor     eax, ecx            ; Can not toggle ID bit,
            //                  jz      done                ; Processor=80486
            //                  mov     retVal,1         ; We have CPUID support
            //done:
            //            }
#elif defined(__sun) && defined(__i386)
            __asm (
               "       pushfl                 \n"
               "       popl    %eax           \n"
               "       movl    %eax,%ecx      \n"
               "       xorl    $0x200000,%eax \n"
               "       pushl   %eax           \n"
               "       popfl                  \n"
               "       pushfl                 \n"
               "       popl    %eax           \n"
               "       xorl    %ecx,%eax      \n"
               "       jz      1f             \n"
               "       movl    $1,-8(%ebp)    \n"
               "1:                            \n"
               );
#elif defined(__sun) && defined(__amd64)
            __asm (
               "       pushfq                 \n"
               "       popq    %rax           \n"
               "       movq    %rax,%rcx      \n"
               "       xorl    $0x200000,%eax \n"
               "       pushq   %rax           \n"
               "       popfq                  \n"
               "       pushfq                 \n"
               "       popq    %rax           \n"
               "       xorl    %ecx,%eax      \n"
               "       jz      1f             \n"
               "       movl    $1,-8(%rbp)    \n"
               "1:                            \n"
               );
#endif
            return static_cast<bool>(retVal);
         }

         static void cpuid(const int aFeature, int& a, int& b, int& c, int& d)
         {
#if defined(__GNUC__) && defined(i386)
            __asm__ __volatile__(
               "        pushl %%ebx        \n"
               "        cpuid              \n"
               "        movl %%ebx, %%esi  \n"
               "        popl %%ebx         \n" :
            "=a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (aFeature))
#elif defined(__GNUC__) && defined(__x86_64__)
            __asm__ __volatile__(
               "        pushq %%rbx        \n"
               "        cpuid              \n"
               "        movq %%rbx, %%rsi  \n"
               "        popq %%rbx         \n" :
            "=a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (aFeature))
               //#elif (defined(_MSC_VER) && defined(_M_IX86)) || defined(__WATCOMC__)
               //            __asm
               //            {
               //               __asm mov eax, aFeature
               //                  __asm cpuid
               //                  __asm mov a, eax
               //                  __asm mov b, ebx
               //                  __asm mov c, ecx
               //                  __asm mov d, edx
               //            }
#elif defined(__WATCOMC__)
            __asm
            {
               __asm mov eax, aFeature
                  __asm cpuid
                  __asm mov a, eax
                  __asm mov b, ebx
                  __asm mov c, ecx
                  __asm mov d, edx
            }
#elif defined(_MSC_VER) && (_MSC_VER > 1400)
            {
               int CPUInfo[4] = {0};
               __cpuid(CPUInfo,aFeature);
               a = CPUInfo[0];
               b = CPUInfo[1];
               c = CPUInfo[2];
               d = CPUInfo[3];
            }
#else
            a = b = c = d = 0;
#endif
         ;}

         static const std::string& getCPUType()
         {
            static std::string retVal = "Unknown";
            const size_t CPUTypeSize = 13;
            static char CPUType[CPUTypeSize] = {0};
            if (!CPUType[0])
            {
               int i = 0;
               int a, b, c, d;

               if (haveCPUID())
               {
                  cpuid(0x00000000, a, b, c, d);
                  CPUType[i++] = (char)(b & 0xff);
                  b >>= 8;
                  CPUType[i++] = (char)(b & 0xff);
                  b >>= 8;
                  CPUType[i++] = (char)(b & 0xff);
                  b >>= 8;
                  CPUType[i++] = (char)(b & 0xff);
                  b >>= 8;
                  CPUType[i++] = (char)(d & 0xff);
                  d >>= 8;
                  CPUType[i++] = (char)(d & 0xff);
                  d >>= 8;
                  CPUType[i++] = (char)(d & 0xff);
                  d >>= 8;
                  CPUType[i++] = (char)(d & 0xff);
                  d >>= 8;
                  CPUType[i++] = (char)(c & 0xff);
                  c >>= 8;
                  CPUType[i++] = (char)(c & 0xff);
                  c >>= 8;
                  CPUType[i++] = (char)(c & 0xff);
                  c >>= 8;
                  CPUType[i++] = (char)(c & 0xff);
                  c >>= 8;
               }
               if (CPUType[0])
               {
                  retVal = CPUType;
               }
            }
            return retVal;
         }

         static int getCPUIDFeatures()
         {
            int retVal = 0;
            int a = 0, b = 0, c = 0, d = 0;

            cpuid(0, a, b, c, d);
            if (a >= 1)
            {
               cpuid(1, a, b, c, d);
               retVal = d;
            }
            return retVal;
         }

         static int getCPUCacheLineSize()
         {
            int a = 0, b = 0, c = 0, d = 0;
            if(getCPUType() == "GenuineIntel")
            {
               cpuid(0x00000001, a, b, c, d);
               return (((b >> 8) & 0xff) * 8);
            }
            else if((getCPUType() == "AuthenticAMD") || (getCPUType() == "AMDisbetter!"))
            {
               cpuid(0x80000005, a, b, c, d);
               return (c & 0xff);
            }
            else
            {
               /* Just make a guess here... */
               return CPUInfoTraits::kDefaultCacheLineSize;
            }
         }
      };// CPUInfoHelper
   }// namespace cpu_info
   class SystemInfo : public blib::idioms::Singleton<SystemInfo>
   {
   public:
      friend blib::idioms::Singleton<SystemInfo>;
      typedef cpu_info::CPUInfoTraits MyTraits;
      typedef MyTraits::DefIntType IntType;
      typedef std::bitset<cpu_info::kFeatureEnd> FeatureFlagType;
      typedef cpu_info::CpuVendorIds CpuVendorIdsFlagType;
      typedef std::bitset<cpu_info::kCpuIdEnd> BugFlagType;
   private:
      //! @brief Cpu short vendor string.
      char _vendorString[MyTraits::kVendorStringMaxSize];
      //! @brief Cpu long vendor string (brand).
      char _brandString[MyTraits::kBrandStringMaxSize];
      //! @brief Cpu vendor id.
      CpuVendorIdsFlagType _vendorId;
      //! @brief Cpu family ID.
      IntType _family;
      //! @brief Cpu model ID.
      IntType _model;
      //! @brief Cpu stepping.
      IntType _stepping;
      //! @brief Number of processors or cores.
      IntType _numberOfProcessors;
      //! @brief Cpu features bitfield, see @c Feature enum).
      FeatureFlagType _features;
      //! @brief Cpu bugs bitfield, see @c Bug enum).
      BugFlagType _bugs;
      //! @brief Cpu cacheline size.
      IntType _cacheLineSize;
      IntType _processorType;
      IntType _brandIndex;
      IntType _apicPhysicalId;
      IntType _pageSize;
      bool _haveCpuId;
   private:
      SystemInfo()
         :_family(0),_model(0)
         ,_stepping(0),_numberOfProcessors(1)
         ,_cacheLineSize(cpu_info::CPUInfoHelper::getCPUCacheLineSize())
         ,_haveCpuId(cpu_info::CPUInfoHelper::haveCPUID())
         ,_pageSize(cpu_info::CPUInfoHelper::pageSize())
      {
         for(int i = 0;i < MyTraits::kVendorStringMaxSize; ++i)
         {
            _vendorString[i] = '\0';
         }
         for(int i = 0;i < MyTraits::kBrandStringMaxSize; ++i)
         {
            _brandString[i] = '\0';
         }
         if(_haveCpuId)
         {
            initialize();
         }
      }

      void initialize()
      {
         using namespace cpu_info;
         int a = 0,b = 0,c = 0,d = 0;
         _vendorId = boost::lexical_cast<cpu_info::CpuVendorIds>(cpu_info::CPUInfoHelper::getCPUType());
         CPUInfoHelper::cpuid(1,a,b,c,d);
         // Fill family and model information
         _family = (a >> 8) &0x0F;
         _model = (a >> 4) &0x0F;
         _stepping = a & 0x0F;
         // Fill extended family and model
         if(0x0F == _family)
         {
            _family += (a >> 20) & 0xFF;
            _model += ((a >> 16) & 0x0F)<<4;
         }
         _processorType = (a >> 12) & 0x03;
         _brandIndex = b & 0xFF;
         _apicPhysicalId = (b >> 24) & 0xFF;

         if(c & 0x00000001U)
         {
            _features.set(kFeatureSSE3);
         }
         if(c & 0x00000002U)
         {
            _features.set(kX86FeaturePCLMULDQ);
         }
         if(c & 0x00000008U)
         {
            _features.set(kFeatureMonitorMWait);
         }
         if(c & 0x00000200U)
         {
            _features.set(kFeatureSSSE3);
         }
         if(c & 0x00002000U)
         {
            _features.set(kFeatureCMPXCHG16B);
         }
         if(c & 0x00080000U)
         {
            _features.set(kFeatureSSE4_1);
         }
         if(c & 0x00100000U)
         {
            _features.set(kFeatureSSE4_2);
         }
         if(c & 0x00400000U)
         {
            _features.set(kFeatureMOVBE);
         }
         if(c & 0x00800000U)
         {
            _features.set(kFeaturePOPCNT);
         }
         if(c & 0x10000000U)
         {
            _features.set(kFeatureAVX);
         }
         if(c & 0x00000010U)
         {
            _features.set(kFeatureRDTSC);
         }
         if(c & 0x00000100U)
         {
            _features.set(kFeatureCMPXCHG8B);
         }
         if(c & 0x00008000U)
         {
            _features.set(kFeatureCMOV);
         }
         if(c & 0x00800000U)
         {
            _features.set(kFeatureMMX);
         }
         if(c & 0x01000000U)
         {
            _features.set(kFeatureFXSR);
         }
         if(c & 0x02000000U)
         {
            _features.set(kFeatureSSE);
            _features.set(kFeatureMMXExt);
         }
         if(c & 0x04000000U)
         {
            _features.set(kFeatureSSE);
            _features.set(kFeatureSSE2);
         }
         if(c & 0x10000000U)
         {
            _features.set(kFeatureMultiThreading);
         }
         if((kCpuAmd == _vendorId)&& (d & 0x10000000U))
         {
            // AMD sets Multithreading to ON if it has more cores.
            if(_numberOfProcessors == 1)
            {
               _numberOfProcessors = 2;
            }
         }
         // This comment comes from V8 and asmjit:
         //
         // Opteron Rev E has i bug in which on very rare occasions i locked
         // instruction doesn't act as i read-acquire barrier if followed by i
         // non-locked read-modify-write instruction.  Rev F has this bug in
         // pre-release versions, but not in versions released to customers,
         // so we test only for Rev E, which is family 15, model 32..63 inclusive.

         if((kCpuAmd == _vendorId) && (15 == _family) && (_model >= 32) && (_model <= 63))
         {
            _bugs.set(kBugAmdLockMB);
         }
         // Calling cpuid with 0x80000000 as the in argument
         // gets the number of valid extended IDs.
         CPUInfoHelper::cpuid(0x80000000, a,b,c,d);
         boost::uint32_t exIds = a;
         if (exIds > 0x80000004)
         {
            exIds = 0x80000004;
         }
         boost::uint32_t* brand = reinterpret_cast<boost::uint32_t*>(_brandString);
         for(boost::uint32_t i = 0x80000001; i <= exIds; i++)
         {
            CPUInfoHelper::cpuid(i,a,b,c,d);
            switch (i)
            {
            case 0x80000001:
               if(c & 0x00000001U)
                  _features.set(kFeatureLAHFSAHF);
               if(c & 0x00000020U)
                  _features.set(kFeatureLZCNT);
               if(c & 0x00000040U)
                  _features.set(kFeatureSSE4_A);
               if(c & 0x00000080U)
                  _features.set(kFeatureMSSE);
               if(c & 0x00000100U)
                  _features.set(kFeaturePrefetch);

               if(d & 0x00100000U)
                  _features.set(kFeatureExecuteDisableBit);
               if(d & 0x00200000U)
                  _features.set(kFeatureFFXSR);
               if(d & 0x00400000U)
                  _features.set(kFeatureMMXExt);
               if(d & 0x08000000U)
                  _features.set(kFeatureRDTSC);
               if(d & 0x20000000U)
                  _features.set(kFeature64Bit);
               if(d & 0x40000000U)
               {
                  _features.set(kFeature3dNow);
                  _features.set(kFeatureMMXExt);
               }
               if(d & 0x80000000U)
                  _features.set(kFeature3dNow);
               break;

            case 0x80000002:
            case 0x80000003:
            case 0x80000004:
               *brand++ = a;
               *brand++ = b;
               *brand++ = c;
               *brand++ = d;
               break;

            default:
               // Additional features can be detected in the future.
               break;
            }
         }
      }
   public:
      bool isFeatureSupported(const cpu_info::FeatureBitIndex aFlag)const
      {
         return _features.test(aFlag);
      }
      IntType cacheLineSize()const
      {
         return _cacheLineSize;
      }
      CpuVendorIdsFlagType vendorId()const
      {
         return _vendorId;
      }
      IntType numberOfProcessors()const
      {
         return _numberOfProcessors;
      }
      IntType stepping()const
      {
         return _stepping;
      }
      IntType pageSize()const
      {
         return _pageSize;
      }
   };
}
}

#endif //__BLIB_SYSTEM_INFO_INCLUDED__
