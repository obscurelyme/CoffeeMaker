#ifndef _echelon_hpp
#define _echelon_hpp

#include <SDL2/SDL.h>

#include <array>
#include <string>

#include "Color.hpp"
#include "Event.hpp"
#include "Math.hpp"
#include "Renderer.hpp"

class Echelon;

class EchelonItem {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  enum class EchelonState { Solo, Synced };
  void AddToEchelon(Echelon *);
  void RemoveFromEchelon();
  void SyncToEchelon();
  void DesyncFromEchelon();
  bool IsInEchelon() const;
  bool IsSynced() const;

  virtual Vec2 GetEchelonPosition() = 0;
  virtual void SetEchelonPosition(const Vec2 &pos) = 0;
  /**
   * @brief This will be the amount of space (width)
   * that this object will take up in the Echelon
   */
  virtual float GetEchelonSpace() = 0;

  protected:
  EchelonItem();
  ~EchelonItem() = default;

  bool _isInEchelon;
  std::string _echelonId;
  Echelon *_echelon;
  EchelonState _echelonState;
  unsigned int _echelonIndex;
  Vec2 _echelonPosition;
};

/**
 * @brief Formation for Enemy Sprites to travel on screen
 */
class Echelon : public CoffeeMaker::IUserEventListener {
  enum class MovementState { ShiftingLeft, ShiftingRight };

  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  friend class EchelonItem;

  Echelon(float width, float height, int renderOutputWidth, float spacing = 0.0f, float speed = 325.0f,
          const std::string &name = "Unknown Echelon",
          float scale = CoffeeMaker::Renderer::DynamicResolutionDownScale());
  ~Echelon();

  void Add(EchelonItem *);
  void RemoveAtIndex(unsigned int index);

  std::string GetId() const { return _id; }

  float GetHeight();
  float GetSpacing();
  float GetWidth();
  void SetPosition(const Vec2 &newPosition);
  Vec2 GetPosition();

  void Update(float);
  void OnSDLUserEvent(const SDL_UserEvent &);

  void Render() {
    SDL_Color yellow = CoffeeMaker::Colors::Yellow;
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), yellow.r, yellow.g, yellow.b, yellow.a);
    SDL_RenderDrawRectF(CoffeeMaker::Renderer::Instance(), &_debugRect);
  }

  private:
  static float _rightBoundary;
  static float _leftBoundary;
  static unsigned int _uid;
  static const unsigned int ECHELON_SIZE = 6;

  bool HitRightBoundary() const;
  bool HitLeftBoundary() const;

  float _height;
  float _width;
  float _spacing;
  Vec2 _position;
  float _speed;
  std::array<EchelonItem *, ECHELON_SIZE> _enemies;
  MovementState _movementState;
  std::string _id;
  std::string _name;
  unsigned int _currentIndex;
  SDL_FRect _debugRect;
};

#endif
