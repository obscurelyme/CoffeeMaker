
#ifndef _coffeemaker_uciechelon_hpp
#define _coffeemaker_uciechelon_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Game/Echelon.hpp"

namespace EchelonTester {
  class EchelonImpl : public IEchelonItem {
    using Vec2 = CoffeeMaker::Math::Vector2D;

    public:
    explicit EchelonImpl(float width) : _position(Vec2{0.0f, 0.0f}), _width(width) {}
    ~EchelonImpl() = default;
    virtual void SetEchelonPosition(const Vec2 &echelonPosition) {
      _position.x = echelonPosition.x + (GetEchelonSpace() * static_cast<float>(_echelonIndex)) +
                    (_echelon->GetSpacing() * static_cast<float>(_echelonIndex));
      _position.y = echelonPosition.y;
    }
    virtual float GetEchelonSpace() { return _width; }
    std::string GetEchelonId() { return _echelonId; }
    Vec2 GetPosition() const { return _position; }

    private:
    Vec2 _position;
    float _width;
  };
}  // namespace EchelonTester

class UCIEchelon : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(UCIEchelon);
  CPPUNIT_TEST(testCreateEchelon);
  CPPUNIT_TEST(testCreateIEchelonItem);
  CPPUNIT_TEST(testRemoveIEchelonItem);
  CPPUNIT_TEST(testDesyncedIEchelonItem);
  CPPUNIT_TEST(testResyncedIEchelonItem);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testCreateEchelon();
  void testCreateIEchelonItem();
  void testRemoveIEchelonItem();
  void testDesyncedIEchelonItem();
  void testResyncedIEchelonItem();
};

#endif
