
#ifndef _coffeemaker_coffeemakertexturetest_hpp
#define _coffeemaker_coffeemakertexturetest_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Renderer.hpp"
#include "Window.hpp"

class CoffeeMakerTextureTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoffeeMakerTextureTest);
  CPPUNIT_TEST(testCreateTexture);
  CPPUNIT_TEST(testLoadTexture);
  CPPUNIT_TEST(testRender);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testCreateTexture();
  void testLoadTexture();
  void testRender();

private:
  CoffeeMaker::Renderer *_renderer;
  CoffeeMaker::IWindow *_window;
};

#endif
