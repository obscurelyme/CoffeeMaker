#ifndef _echelon_hpp
#define _echelon_hpp

#include <SDL2/SDL.h>

#include <array>
#include <string>

#include "Event.hpp"
#include "Game/Enemy.hpp"
#include "Math.hpp"

class Echelon;

class IEchelonItem {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  enum class EchelonState { Solo, Synced };
  void AddToEchelon(Echelon *);
  void RemoveFromEchelon();
  void SyncToEchelon();
  void DesyncFromEchelon();
  bool IsInEchelon() const;
  bool IsSynced() const;

  virtual void SetEchelonPosition(const Vec2 &pos) = 0;
  /**
   * @brief This will be the amount of space (width)
   * that this object will take up in the Echelon
   */
  virtual float GetEchelonSpace() = 0;

  protected:
  IEchelonItem();
  ~IEchelonItem() = default;

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
  friend class IEchelonItem;

  Echelon(float width, float height, float spacing = 0.0f, float speed = 150.0f,
          const std::string &name = "Unknown Echelon");
  ~Echelon();

  void Add(IEchelonItem *);
  void RemoveAtIndex(unsigned int index);

  std::string GetId() const { return _id; }

  float GetHeight();
  float GetSpacing();
  float GetWidth();
  void SetPosition(const Vec2 &newPosition);

  void Update(float);
  void OnSDLUserEvent(const SDL_UserEvent &);

  private:
  static float _rightBoundary;
  static float _leftBoundary;
  static unsigned int _uid;
  static const unsigned int ECHELON_SIZE = 5;

  bool HitRightBoundary() const;
  bool HitLeftBoundary() const;

  float _height;
  float _width;
  float _spacing;
  Vec2 _position;
  float _speed;
  std::array<IEchelonItem *, ECHELON_SIZE> _enemies;
  MovementState _movementState;
  std::string _id;
  std::string _name;
  unsigned int _currentIndex;
};

#endif
