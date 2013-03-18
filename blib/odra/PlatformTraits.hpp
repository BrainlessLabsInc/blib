#ifndef __BLIB_PLATFORM_TRAITS__
#define __BLIB_PLATFORM_TRAITS__

#ifndef __BLIB_PLATFORM_CONFIG_INCLUDED__
#include <blib/config/platform_config.hpp>
#endif

namespace blib{namespace odra{namespace platform_traits{
         struct PlatformTraits
      {
         /** \var NUM_OkInsFlagPHYSICAL_REG
         * Number of physical register
         */
         /** \var SIZkEncodeOkInsFlagGP_REG
         * Size of general-purpose register
         */
#ifdef __BLIB_PLATFORM64__
         static const int numOfPhysicalRegs = 16;
         static const int gpRegSize = 8;
         static const int platformSize = 64;
#else
         static const int numOfPhysicalRegs = 8;
         static const int gpRegSize = 4;
         static const int platformSize = 32;
#endif
      };
}// platform_traits
}// namespace odra
}// namespace blib

#endif // __BLIB_PLATFORM_TRAITS__