//----------------------------------------------------------------------
// file: application_window.cpp
// description: Class for initializing an OpenGL window with the SDL
//              used by the OpenGL tutorials at www.tomprogs.at
//----------------------------------------------------------------------
// Copyright (c) 2008, Thomas Geymayer
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------

#include "application_window.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

  //--------------------------------------------------------------------
  ApplicationWindow::ApplicationWindow(
                       int width,
                       int height, int bpp ):
                         width_  ( width                  ),
                         height_ ( height                 ),
                         bpp_    ( bpp                    ),
                         caption_( "64k Intro Test" ),
                         state_  ( 0                      )
  {

  }

  //--------------------------------------------------------------------
  ApplicationWindow::~ApplicationWindow()
  {
    destroy();
  }

  //--------------------------------------------------------------------
  bool ApplicationWindow::create()
  {
    // check if allready opened a window
    if( state_ & OPENED_WINDOW ) destroy();

    if(    !SDL_WasInit( SDL_INIT_VIDEO ) )
      SDL_InitSubSystem( SDL_INIT_VIDEO );

    SDL_WM_SetCaption(   caption_.c_str(), NULL );

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);

    surface_ =
      SDL_SetVideoMode(
        width_, height_, bpp_,
        SDL_OPENGL | ( (state_ & FULL_SCREEN) ? SDL_FULLSCREEN : 0 ) );

    if( !surface_ ) return false;

    // disable cursor
    SDL_ShowCursor( 0 );

    state_ |= OPENED_WINDOW;

    return true;
  }

  //--------------------------------------------------------------------
  bool ApplicationWindow::destroy()
  {
    // return if no window is opened
    if( !(state_ & OPENED_WINDOW) ) return true;

    SDL_FreeSurface( surface_ );

    state_ &= ~OPENED_WINDOW;

    return true;
  }

  //--------------------------------------------------------------------
  void ApplicationWindow::setResolution( int width, int height )
  {
    width_  = width;
    height_ = height;
  }

  //--------------------------------------------------------------------
  void ApplicationWindow::setColorDepth( int bpp )
  {
    bpp_ = bpp;
  }

  //--------------------------------------------------------------------
  void ApplicationWindow::setCaption( const std::string& caption )
  {
    caption_ = caption;
  }

  //--------------------------------------------------------------------
  void ApplicationWindow::setFullscreen( bool enable )
  {
    if( enable )
    {
      state_ |= FULL_SCREEN;
    }
    else
    {
      state_ &= ~FULL_SCREEN;
    }
  }

  //--------------------------------------------------------------------
  SDL_Surface* ApplicationWindow::getSurface()
  {
    return surface_;
  }

