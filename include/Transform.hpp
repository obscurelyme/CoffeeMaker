#ifndef _transform_hpp
#define _transform_hpp

#include <glm/glm.hpp>

class Transform {
  public:
    Transform(int x = 0, int y = 0);
    ~Transform();

    const glm::vec2& Position() const;

  private:
    glm::vec2 vec2;
};

#endif
