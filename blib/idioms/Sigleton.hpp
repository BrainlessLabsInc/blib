#ifndef __BLIB_SINGLETON_INCLUDED__
#define __BLIB_SINGLETON_INCLUDED__

namespace blib{namespace idioms{

   template<typename Type>
   class Singleton
   {
   public:
      static Type& instance()
      {
         static Type retType;
         return retType;
      }
   protected:
      Singleton();
      ~Singleton();
   private:
      Singleton& operator=(const Singleton&);
      Singleton(const Singleton&);
   };
}
}

#endif // __BLIB_SINGLETON_INCLUDED__