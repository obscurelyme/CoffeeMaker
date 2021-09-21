
#ifndef _coffeemaker_coffeemakertexturetest_hpp
#define _coffeemaker_coffeemakertexturetest_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestBed.hpp"

class CoffeeMakerTextureTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoffeeMakerTextureTest);
  CPPUNIT_TEST(testCreateTexture);
  CPPUNIT_TEST(testLoadTexture);
  CPPUNIT_TEST(testRender);
  CPPUNIT_TEST(testCreateTextureColor);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testCreateTexture();
  void testLoadTexture();
  void testRender();
  void testCreateTextureColor();

private:
  CoffeeMaker::Test::TestBed *_testBed;
  // CoffeeMaker::Renderer *_renderer;
  // CoffeeMaker::IWindow *_window;
};

#endif
