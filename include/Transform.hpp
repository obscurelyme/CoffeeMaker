#ifndef _transform_hpp
#define _transform_hpp

#include <glm/glm.hpp>

class Transform {
 public:
  Transform(float x = 0.0f, float y = 0.0f);
  ~Transform();

  const glm::vec2& Position() const;

 private:
  glm::vec2 vec2;
};

#endif
