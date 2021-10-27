#ifndef _coffeemaker_math_hpp
#define _coffeemaker_math_hpp

namespace CoffeeMaker {
  /**
   * @brief Math functions for CoffeeMaker
   * @see https://en.wikipedia.org/wiki/Smoothstep
   * @see https://www.youtube.com/watch?v=aVwxzDHniEw
   * @see
   * http://codetuto.com/2017/02/7-lerping-tricks-need-know-game-developer/#:~:text=7%20Lerping%20tricks%20you%20need%20to%20know%20as,weight.%20...%207%20Lerp%20inside%20tween%20updates.%20
   */
  namespace Math {
    class Vector2D;  // forward declaration

    /**
     * @brief Finds the floating point value in between f1 and f2
     * using the value t, which acts as a percentage
     * between f1 and f2.
     * @param f1 Starting floating point value
     * @param f2 End floating point value
     * @param t The percentage given in terms of decimal values between 0 and 1
     * @return Exact floating point number between f1 and f2
     */
    float Lerp(float f1, float f2, float t);
    Vector2D Lerp(const Vector2D& v1, const Vector2D& v2, float t);

    Vector2D Normalize(const Vector2D& v1);

    float rad2deg(float rad);

    float deg2rad(float degrees);

    Vector2D QuadraticBezierCurve(const Vector2D& startPos, const Vector2D&, const Vector2D& endPos, float t);
    Vector2D CubicBezierCurve(const Vector2D& startPos, const Vector2D&, const Vector2D&, const Vector2D& endPos,
                              float t);

    class Vector2D {
      public:
      Vector2D(float xx = 0.0f, float yy = 0.0f);
      Vector2D(const Vector2D& rhs);

      float x;
      float y;

      /**
       * @brief Returns the angle, in radians, of the direction the
       * lhs vector is facing rhs vector.
       *
       * @param rhs Vector2D that lhs should be facing.
       * @return radian value of the angle
       */
      float Direction(const Vector2D& rhs);

      /**
       * @brief Returns the magnitude between 2 Vectors
       *
       * @param rhs
       * @return float value of the magnitude
       */
      float Magnitude(const Vector2D& rhs);
      /**
       * @brief Returns the magnitude of the Vector using the given end coordinates
       */
      float Magnitude(float endX, float endY);
      /**
       * @brief Returns the magnitude of the Vector from origin (0,0)
       */
      float Magnitude();

      Vector2D& operator+=(const Vector2D& rh);
      friend Vector2D operator+(Vector2D lhs, const Vector2D& rhs) { return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y); }
      Vector2D& operator-=(const Vector2D& rh);
      friend Vector2D operator-(Vector2D lhs, const Vector2D& rhs) { return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y); }
      Vector2D& operator*=(float scalar);
      friend Vector2D operator*(Vector2D lhs, float scalar) { return Vector2D(lhs.x * scalar, lhs.y * scalar); }

      Vector2D& operator=(const Vector2D& vector);
      bool operator==(const Vector2D& rhs);

      /**
       * @brief Directional vector pointing up the y axis
       *
       * @return Vector2D (0.0f, 1.0f)
       */
      static Vector2D Up();
      /**
       * @brief Directional vector pointing down the y axis
       *
       * @return Vector2D (0.0f, -1.0f)
       */
      static Vector2D Down();
      /**
       * @brief Directional vector pointing left on the x axis
       *
       * @return Vector2D (-1.0f, 0.0f)
       */
      static Vector2D Left();
      /**
       * @brief Directional vector pointing right on the x axis
       *
       * @return Vector2D (1.0f, 0.0f)
       */
      static Vector2D Right();
    };
  }  // namespace Math
}  // namespace CoffeeMaker

#endif
