#ifndef _coffeemaker_texture_hpp
#define _coffeemaker_texture_hpp

#include <SDL2/SDL.h>

#include <string>

#include "Color.hpp"

namespace CoffeeMaker {
  SDL_Texture *createRectTextureFromSurface(int height, int width, const SDL_Color &color);

  class Texture {
    public:
    static constexpr SDL_Color COLOR_KEY = {.r = 213, .g = 57, .b = 213, .a = 255};
    Texture();
    explicit Texture(const std::string &filePath);
    explicit Texture(const SDL_Color &color);
    /**
     * Load a texture from the given file path and use the given
     * color key to set transparent pixels.
     */
    Texture(const std::string &filePath, const bool useColorKey);
    ~Texture();

    Texture &operator=(const Texture &rhs);

    void LoadFromFile(const std::string &filePath);
    void CreateFromSurface(int height, int width, const SDL_Color &color);
    void SetColor(SDL_Color color = Color());
    // Get the additional color value multiplied into render copy operations.
    SDL_Color GetColorMod();
    void SetAlpha(Uint8 alpha);
    void SetBlendMode(SDL_BlendMode blend);
    void Render(int top, int left);
    void Render(float top, float left);
    /**
     * For use when the Texture's dimensions are controled by its parent
     */
    void Render(int top, int left, int height, int width);
    void Render(const SDL_Rect &clip, const SDL_Rect &renderRect);
    void Render(const SDL_Rect &clip, const SDL_Rect &renderRect, double rotation);
    void Render(const SDL_Rect &renderRect, double rotation);
    int Height() const;
    int Width() const;
    void SetHeight(int const height);
    void SetWidth(int const width);
    SDL_Texture *Handle() const;

    static void SetTextureDirectory();

    private:
    static std::string _textureDirectory;

    SDL_Texture *_texture;
    SDL_Color _color;
    int _height;
    int _width;
    bool _useColorKey;
    SDL_Surface *_surface;
  };

}  // namespace CoffeeMaker

#endif
