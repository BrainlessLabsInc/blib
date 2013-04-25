#ifndef __BLIB_GLFW_ENABLE_INCLUDED__
#define __BLIB_GLFW_ENABLE_INCLUDED__

//************************************************************************
//****                  GLFW internal functions                       ****
//************************************************************************

//========================================================================
// Enable (show) mouse cursor
//========================================================================
namespace blib{namespace glfw{

   void enableMouseCursor( void )
   {
      int centerPosX, centerPosY;

      if( !_glfwWin.opened || !_glfwWin.mouseLock )
      {
         return;
      }

      // Show mouse cursor
      _glfwPlatformShowMouseCursor();

      centerPosX = _glfwWin.width / 2;
      centerPosY = _glfwWin.height / 2;

      if( centerPosX != _glfwInput.MousePosX || centerPosY != _glfwInput.MousePosY )
      {
         _glfwPlatformSetMouseCursorPos( centerPosX, centerPosY );

         _glfwInput.MousePosX = centerPosX;
         _glfwInput.MousePosY = centerPosY;

         if( _glfwWin.mousePosCallback )
         {
            _glfwWin.mousePosCallback( _glfwInput.MousePosX,
               _glfwInput.MousePosY );
         }
      }

      // From now on the mouse is unlocked
      _glfwWin.mouseLock = GL_FALSE;
   }

   //========================================================================
   // Disable (hide) mouse cursor
   //========================================================================

   void disableMouseCursor( void )
   {
      if( !_glfwWin.opened || _glfwWin.mouseLock )
      {
         return;
      }

      // Hide mouse cursor
      _glfwPlatformHideMouseCursor();

      // From now on the mouse is locked
      _glfwWin.mouseLock = GL_TRUE;
   }


   //========================================================================
   // Enable sticky keys
   //========================================================================

   void enableStickyKeys( void )
   {
      _glfwInput.StickyKeys = 1;
   }

   //========================================================================
   // Disable sticky keys
   //========================================================================

   void disableStickyKeys( void )
   {
      int i;

      _glfwInput.StickyKeys = 0;

      // Release all sticky keys
      for( i = 0; i <= GLFW_KEY_LAST; i++ )
      {
         if( _glfwInput.Key[ i ] == 2 )
         {
            _glfwInput.Key[ i ] = 0;
         }
      }
   }


   //========================================================================
   // Enable sticky mouse buttons
   //========================================================================

   void enableStickyMouseButtons( void )
   {
      _glfwInput.StickyMouseButtons = 1;
   }

   //========================================================================
   // Disable sticky mouse buttons
   //========================================================================

   void disableStickyMouseButtons( void )
   {
      int i;

      _glfwInput.StickyMouseButtons = 0;

      // Release all sticky mouse buttons
      for( i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++ )
      {
         if( _glfwInput.MouseButton[ i ] == 2 )
         {
            _glfwInput.MouseButton[ i ] = 0;
         }
      }
   }


   //========================================================================
   // Enable system keys
   //========================================================================

   void enableSystemKeys( void )
   {
      if( !_glfwWin.sysKeysDisabled )
      {
         return;
      }

      _glfwPlatformEnableSystemKeys();

      // Indicate that system keys are no longer disabled
      _glfwWin.sysKeysDisabled = GL_FALSE;
   }

   //========================================================================
   // Disable system keys
   //========================================================================

   void disableSystemKeys( void )
   {
      if( _glfwWin.sysKeysDisabled )
      {
         return;
      }

      _glfwPlatformDisableSystemKeys();

      // Indicate that system keys are now disabled
      _glfwWin.sysKeysDisabled = GL_TRUE;
   }


   //========================================================================
   // Enable key repeat
   //========================================================================

   void enableKeyRepeat( void )
   {
      _glfwInput.KeyRepeat = 1;
   }

   //========================================================================
   // Disable key repeat
   //========================================================================

   void disableKeyRepeat( void )
   {
      _glfwInput.KeyRepeat = 0;
   }


   //========================================================================
   // Enable automatic event polling
   //========================================================================

   void enableAutoPollEvents( void )
   {
      _glfwWin.autoPollEvents = 1;
   }

   //========================================================================
   // Disable automatic event polling
   //========================================================================

   void disableAutoPollEvents( void )
   {
      _glfwWin.autoPollEvents = 0;
   }



   //************************************************************************
   //****                    GLFW user functions                         ****
   //************************************************************************

   //========================================================================
   // Enable certain GLFW/window/system functions.
   //========================================================================

   void glfwEnable( int token )
   {
      // Is GLFW initialized?
      if( !_glfwInitialized )
      {
         return;
      }

      switch( token )
      {
      case GLFW_MOUSE_CURSOR:
         enableMouseCursor();
         break;
      case GLFW_STICKY_KEYS:
         enableStickyKeys();
         break;
      case GLFW_STICKY_MOUSE_BUTTONS:
         enableStickyMouseButtons();
         break;
      case GLFW_SYSTEM_KEYS:
         enableSystemKeys();
         break;
      case GLFW_KEY_REPEAT:
         enableKeyRepeat();
         break;
      case GLFW_AUTO_POLL_EVENTS:
         enableAutoPollEvents();
         break;
      default:
         break;
      }
   }


   //========================================================================
   // Disable certain GLFW/window/system functions.
   //========================================================================

   void glfwDisable( int token )
   {
      // Is GLFW initialized?
      if( !_glfwInitialized )
      {
         return;
      }

      switch( token )
      {
      case GLFW_MOUSE_CURSOR:
         disableMouseCursor();
         break;
      case GLFW_STICKY_KEYS:
         disableStickyKeys();
         break;
      case GLFW_STICKY_MOUSE_BUTTONS:
         disableStickyMouseButtons();
         break;
      case GLFW_SYSTEM_KEYS:
         disableSystemKeys();
         break;
      case GLFW_KEY_REPEAT:
         disableKeyRepeat();
         break;
      case GLFW_AUTO_POLL_EVENTS:
         disableAutoPollEvents();
         break;
      default:
         break;
      }
   }

} // namespace glfw
} // namespace blib

#endif // __BLIB_GLFW_ENABLE_INCLUDED__