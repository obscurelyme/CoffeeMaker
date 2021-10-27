#ifndef _coffeemaker_math_hpp
#define _coffeemaker_math_hpp

namespace CoffeeMaker {
  namespace Math {
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

    float rad2deg(float rad);

    float deg2rad(float degrees);

    class Vector2D {
      public:
      Vector2D(float xx, float yy);

      float x;
      float y;

      Vector2D& operator+=(const Vector2D& rh);
      friend Vector2D operator+(Vector2D lhs, const Vector2D& rh) {
        lhs.x += rh.x;
        lhs.y += rh.y;

        return lhs;
      }

      float Direction(const Vector2D& rhs);
      float Magnitude(const Vector2D& rhs);

      Vector2D& operator-=(const Vector2D& rh);
      friend Vector2D operator-(Vector2D lhs, const Vector2D& rh) {
        lhs.x -= rh.x;
        lhs.y -= rh.y;

        return lhs;
      }

      Vector2D& operator*=(float scalar);
      friend Vector2D operator*(Vector2D lhs, float scalar) {
        lhs.x *= scalar;
        lhs.y *= scalar;

        return lhs;
      }

      static const Vector2D* Up();
      static const Vector2D* Down();
      static const Vector2D* Left();
      static const Vector2D* Right();

      private:
      static Vector2D* _up;
      static Vector2D* _down;
      static Vector2D* _left;
      static Vector2D* _right;
    };
  }  // namespace Math
}  // namespace CoffeeMaker

#endif
