#ifndef _coffeemaker_math_hpp
#define _coffeemaker_math_hpp

#include <fmt/core.h>

#include <chrono>
#include <random>

using RNG = std::mt19937;
namespace Chrono = std::chrono;

namespace CoffeeMaker {
  /**
   * @brief Math functions for CoffeeMaker
   * @see https://en.wikipedia.org/wiki/Smoothstep
   * @see https://www.youtube.com/watch?v=aVwxzDHniEw
   * @see
   * http://codetuto.com/2017/02/7-lerping-tricks-need-know-game-developer/#:~:text=7%20Lerping%20tricks%20you%20need%20to%20know%20as,weight.%20...%207%20Lerp%20inside%20tween%20updates.%20
   */
  namespace Math {

    class RandomEngine {
      public:
      static void Init() {
        auto now = Chrono::system_clock::now();
        auto msSinceEpoch = Chrono::duration_cast<Chrono::milliseconds>(now.time_since_epoch()).count();
        engine.seed(static_cast<unsigned int>(msSinceEpoch));
      }

      static RNG engine;
    };

    /**
     * @brief Returns a random float between the given min and max values.
     * default logic will return a number between 0 and 1.
     *
     * @param min
     * @param max
     * @return float
     */
    float Random(float min = 0, float max = 1);

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

    float InverseLerp(float f1, float f2, float value);
    Vector2D InverseLerp(Vector2D f1, Vector2D f2, Vector2D value);

    float Remap(float inputMin, float inputMax, float outputMin, float outputMax, float value);
    Vector2D Remap(const Vector2D& inputMin, const Vector2D& inputMax, const Vector2D& outputMin,
                   const Vector2D& outputMax, const Vector2D& value);

    Vector2D Normalize(const Vector2D& v1);

    float rad2deg(float rad);

    float deg2rad(float degrees);

    Vector2D QuadraticBezierCurve(const Vector2D& startPos, const Vector2D&, const Vector2D& endPos, float t);
    Vector2D CubicBezierCurve(const Vector2D& startPos, const Vector2D&, const Vector2D&, const Vector2D& endPos,
                              float t);

    struct Point2D {
      float x;
      float y;
    };

    class PolarRotate {
      public:
      static float QUARTER;
      static float PI;
      static float TAU;
    };

    class Vector2D {
      public:
      Vector2D(float xx = 0.0f, float yy = 0.0f);
      Vector2D(const Vector2D& rhs);

      float x;
      float y;

      float Dot(const Vector2D& rhs) const;

      float AngleBetween(const Vector2D& rhs) const;

      Vector2D Rotate(float degrees) const;

      /**
       * @brief Returns the angle, in radians, of the direction the
       * lhs vector is facing rhs vector.
       *
       * @param rhs Vector2D that lhs should be facing.
       * @return radian value of the angle
       */
      float Direction(const Vector2D& rhs);

      /**
       * @brief Leverages Polar Coordinate system to find the angle of 2 points
       * Returns unit vector that the caller can travel per frame that
       * would result in eventually landing at the rhs postion.
       *
       * @param rhs
       * @return float
       */
      Vector2D HeadTowards(const Vector2D& rhs);

      /**
       * @brief Leverages Polar Coordinate system to find the angle of 2 points
       * Returns an angle that the entity needs to be rotated by in order to
       * be looking at the rhs vector
       *
       * @param rhs
       * @return float
       */
      float LookAt(const Vector2D& rhs);

      /**
       * @brief Returns the magnitude between 2 Vectors
       *
       * @param rhs
       * @return float value of the magnitude
       */
      float Magnitude(const Vector2D& rhs) const;
      /**
       * @brief Returns the magnitude of the Vector using the given end coordinates
       */
      float Magnitude(float endX, float endY) const;
      /**
       * @brief Returns the magnitude of the Vector from origin (0,0)
       */
      float Magnitude(void) const;

      Vector2D& operator+=(const Vector2D& rh);
      friend Vector2D operator+(Vector2D lhs, const Vector2D& rhs) { return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y); }
      Vector2D& operator-=(const Vector2D& rh);
      friend Vector2D operator-(Vector2D lhs, const Vector2D& rhs) { return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y); }
      Vector2D& operator*=(float scalar);
      friend Vector2D operator*(Vector2D lhs, const Vector2D& rhs) { return Vector2D(lhs.x * rhs.x, lhs.y * rhs.y); }
      friend Vector2D operator*(Vector2D lhs, float scalar) { return Vector2D(lhs.x * scalar, lhs.y * scalar); }

      Vector2D& operator=(const Vector2D& vector);
      bool operator==(const Vector2D& rhs);

      std::string ToString() const { return fmt::format(fmt::runtime("({},{})"), x, y); }

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

    class Oscillate {
      public:
      explicit Oscillate(float min, float max, float speed);
      ~Oscillate() = default;

      float Update();
      void Stop();
      void Start();

      private:
      float _min;
      float _max;
      float _speed;
      float _current;
      bool _stopping;
      bool _end;
    };
  }  // namespace Math
}  // namespace CoffeeMaker

#endif
