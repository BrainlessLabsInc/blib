// Modified by: Shakti Misra (2013-)
#ifndef __BLIB_CONFIG_INCLUDED__
#define __BLIB_CONFIG_INCLUDED__
// http://sourceforge.net/p/predef/wiki/Home/
#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_NO_CXX11_NULLPTR
#define nullptr NULL
#endif
#ifndef BLIB_UNUSED
#define BLIB_UNUSED(var) ((void)var)
#endif

#endif// __BLIB_CONFIG_INCLUDED__
