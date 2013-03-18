#ifndef __BLIB_COMPILER_CONFIG_INCLUDED__
#define __BLIB_COMPILER_CONFIG_INCLUDED__

//Mostly credited to Boost Config
#if defined(__GCCXML__)
// GCC-XML emulates other compilers, it has to appear first here!
#define __COMPILER__ 'GXML'
#define __GCCXML
#elif defined __CUDACC__
// NVIDIA CUDA C++ compiler for GPU
#define __COMPILER__ 'CUDA'
#define BLIB_CUDA 
#elif defined __COMO__
// Comeau C++
#define __COMPILER__ 'COMO'
#define BLIB_COMEAU
#elif defined __clang__
// Clang C++ emulates GCC, so it has to appear early.
#define __COMPILER__ 'CLAN'
#define BLIB_CLANG
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
// Intel
#define __COMPILER__ 'INTL'
#define BLIB_INTEL
# elif defined __GNUC__
//  GNU C++:
#define __COMPILER__ 'GCPP'
#define BLIB_GCC
#elif defined _MSC_VER
//  Microsoft Visual C++
#define __COMPILER__ 'MSVC'
#define BLIB_MSVC
#else
#define __COMPILER__ 'UNSP'
#define __COMPILER___UNSUPPORTED
#endif

#endif// __BLIB_COMPILER_CONFIG_INCLUDED__