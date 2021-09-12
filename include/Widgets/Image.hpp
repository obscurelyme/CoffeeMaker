#ifndef _coffeemaker_image_hpp
#define _coffeemaker_image_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Window.hpp"
#include "Utilities.hpp"

namespace CoffeeMaker
{
  namespace Widgets
  {
    SDL_Surface *loadImageSurface(std::string filePath)
    {
      SDL_Surface *surface = nullptr;
      std::string resolvedPath = CoffeeMaker::Utilities::WithinImagesDirectory(filePath);
      SDL_Surface *loaded = IMG_Load(resolvedPath.c_str());
      if (loaded == NULL)
      {
        return nullptr;
      }

      surface = SDL_ConvertSurface(loaded, CoffeeMaker::GLOBAL_SCREEN_SURFACE->format, 0);
      SDL_FreeSurface(loaded);

      return surface;
    }

    class Image
    {
    public:
      Image(std::string filePath) : filePath(CoffeeMaker::Utilities::WithinImagesDirectory(filePath)) {}

      void *LoadImage()
      {
        SDL_Surface *loaded = IMG_Load(filePath.c_str());

        if (loaded == NULL)
        {
          return nullptr;
        }

        // surface = SDL_ConvertSurface(loaded, CoffeeMaker::GLOBAL_SCREEN_SURFACE->format, 0);

        _texture = SDL_CreateTextureFromSurface(renderer, loaded);
        clientRect.w = loaded->w;
        clientRect.h = loaded->h;
        clientRect.x = loaded->clip_rect.x;
        clientRect.y = loaded->clip_rect.y;
        SDL_FreeSurface(loaded);
      }

      void AssignToRenderer(SDL_Renderer *sdlRenderer)
      {
        renderer = sdlRenderer;
      }

      void Render()
      {
        SDL_RenderCopy(renderer, _texture, NULL, &clientRect);
      }

      std::string filePath;
      SDL_Rect clientRect;
      SDL_Renderer *renderer;

    private:
      SDL_Texture *_texture;
    };
  }
}

#endif