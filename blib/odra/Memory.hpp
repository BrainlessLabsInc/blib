#ifndef __BLIB_MEMORY_INCLUDED__
#define __BLIB_MEMORY_INCLUDED__

#ifndef __STD_STRING_INCLUDED__
#define __STD_STRING_INCLUDED__
#include <string>
#endif
#ifndef BOOST_TYPE_TRAITS_HPP
#include <boost/type_traits.hpp>
#endif
#ifndef BOOST_POOL_ALLOC_HPP
#include <boost/pool/pool_alloc.hpp>
#endif
#ifndef __BLIB_SYSTEM_INFO_INCLUDED__
#include <blib/sys/system_info.hpp>
#endif
#ifndef __BLIB_CONFIG_INCLUDED__
#include <blib/config.hpp>
#endif
#ifndef BOOST_CONTAINER_FLAT_MAP_HPP
#include <boost/container/flat_map.hpp>
#endif

namespace blib{namespace odra{namespace memory{

   struct ExeMemAllocator
   {
      typedef char RetType;
      typedef RetType* RetTypePtr;
      typedef std::size_t size_type;
      typedef std::ptrdiff_t difference_type;

      typedef boost::container::flat_map<RetTypePtr
         ,size_type, std::less<RetTypePtr>
         ,boost::fast_pool_allocator<std::pair<RetTypePtr, size_type> > > MemSizeMapType;
      static MemSizeMapType _memSizeMap;
      static RetTypePtr malloc(const size_type aSize)
      {
         RetTypePtr retType = nullptr;
#if defined(BOOST_WINDOWS)
         retType = (RetTypePtr)VirtualAlloc(NULL,aSize,MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);
#elif defined(__BLIB_POSIX__)
         // http://man7.org/linux/man-pages/man2/mmap.2.html
         retType = mmap(NULL,aSize,PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
#endif
         _memSizeMap[retType] = aSize;
         return (RetTypePtr)retType;
      }
      static void free(RetTypePtr aMem)
      {
         MemSizeMapType::const_iterator it = _memSizeMap.find(aMem);
         if(_memSizeMap.end() != it)
         {
#if defined(BOOST_WINDOWS)
            VirtualFree((LPVOID)aMem,0,MEM_RELEASE);
#elif defined(__BLIB_POSIX__)
            munmap(aMem, it->second);
#endif
            _memSizeMap.erase(it);
         }
      }
   };// struct ExeMemAllocator
   ExeMemAllocator::MemSizeMapType ExeMemAllocator::_memSizeMap;

   typedef boost::uint8_t ExeAllocUnitType;

   typedef std::basic_string<ExeAllocUnitType
      ,std::char_traits<ExeAllocUnitType>
      ,boost::pool_allocator<ExeAllocUnitType, ExeMemAllocator > > ExeBuffer;

}// namespace utils
}// namespace odra
}// namespace blib

#endif// __BLIB_MEMORY_INCLUDED__
