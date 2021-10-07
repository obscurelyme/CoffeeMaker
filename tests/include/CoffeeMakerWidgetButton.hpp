
#ifndef _coffeemaker_coffeemakerwidgetbutton_hpp
#define _coffeemaker_coffeemakerwidgetbutton_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestBed.hpp"

class CoffeeMakerWidgetButton : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerWidgetButton);
  CPPUNIT_TEST(testButtonCreation);
  CPPUNIT_TEST(testButtonCreatesTexture);
  CPPUNIT_TEST(testButtonDynamicPosition);
  CPPUNIT_TEST(testButtonRenderTexture);
  CPPUNIT_TEST(testButtonRenderTextureAndText);
  CPPUNIT_TEST(testButtonRenderColor);
  CPPUNIT_TEST(testTextAppendedToDefaultButton);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testButtonCreation();
  void testButtonCreatesTexture();
  void testButtonDynamicPosition();
  void testButtonRenderTexture();
  void testButtonRenderTextureAndText();
  void testButtonRenderColor();
  void testTextAppendedToDefaultButton();

  private:
  CoffeeMaker::Test::TestBed *_testBed;
};

#endif
