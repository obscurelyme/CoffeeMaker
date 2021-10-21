#ifndef _game_entity_hpp
#define _game_entity_hpp

enum class EnemyAnimationState { Idle, Moving };

class Entity {
  public:
  virtual void Init() = 0;
  virtual void Update(float deltaTime = 0.0f) = 0;
  virtual void Render() = 0;

  virtual ~Entity() = 0;
};

#endif
