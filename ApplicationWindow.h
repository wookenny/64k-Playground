#pragma once

#include <string>
#include <SDL/SDL_video.h>

class ApplicationWindow
  {
    public:

      //----------------------------------------------------------------
      ///
      /// @brief Constructor
      ///

      ApplicationWindow( int width = 0, int height = 0, int bpp = 0);

      //----------------------------------------------------------------
      ///
      /// @brief Destructor
      ///

      virtual ~ApplicationWindow();

      //----------------------------------------------------------------
      ///
      /// @brief Generates a window with the stored parameters
      ///
      /// Generates a new window with the stored parameters.
      /// If fullscreen is enabled, the new displaymode is set before.
      ///
      /// @return Returns true on success

      bool create();

      //----------------------------------------------------------------
      ///
      /// @brief Destroys this window
      ///
      /// Destroys the window an frees his surface
      ///
      /// @return Returns true on success

      bool destroy();

      //----------------------------------------------------------------
      ///
      /// @brief Set the wished window resolution
      ///
      /// Sets the resolution of the window and changes displaymode if
      /// fullscreen is enabled.

      void setResolution( int width, int height );

      //----------------------------------------------------------------
      ///
      /// @brief Set the wished color depth
      ///
      /// Sets the color depth of the window and changes displaymode if
      /// fullscreen is enabled.

      void setColorDepth( int bpp );

      //----------------------------------------------------------------
      ///
      /// @brief Set the caption of the game window
      ///
      /// Sets the text in the titlebar of the window in windowed mode
      /// and the name of the application in the taskbar or taskmanager.

      void setCaption( const std::string& caption );

      //----------------------------------------------------------------
      ///
      /// @brief En-/Disables fullscreen mode
      ///
      /// Depending on the given parameter enables or disables
      /// fullscreen mode.
      ///
      /// @param enable If true fullscreen will be enabled

      void setFullscreen( bool enable = true );

      //----------------------------------------------------------------
      ///
      /// @brief Get surface of this window
      ///
      /// Get the SDL surface of this window
      ///
      /// @return Pointer to SDL_Surface

      SDL_Surface* getSurface();

      enum
      {
        OPENED_WINDOW = 0x0001,
        FULL_SCREEN   = 0x0002
      };

    private:

      //----------------------------------------------------------------

      int           width_;
      int           height_;
      int           bpp_;

      std::string   caption_;

      SDL_Surface  *surface_;
      char          state_;

      /// copy constructor and assign operator set private
      ApplicationWindow(const ApplicationWindow& src);
      ApplicationWindow& operator=(const ApplicationWindow& src);
};


