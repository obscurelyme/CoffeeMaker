
#ifndef _coffeemaker_coffeemakerwidgetbutton_hpp
#define _coffeemaker_coffeemakerwidgetbutton_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoffeeMakerWidgetButton : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoffeeMakerWidgetButton);
  CPPUNIT_TEST(testButtonCreation);
  CPPUNIT_TEST(testButtonCreatesTexture);
  CPPUNIT_TEST(testButtonRender);
  CPPUNIT_TEST(testButtonOnMousemotionEvent);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testButtonCreation();
  void testButtonCreatesTexture();
  void testButtonRender();
  void testButtonOnMousemotionEvent();
};

#endif