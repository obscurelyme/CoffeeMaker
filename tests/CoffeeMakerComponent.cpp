
#include "CoffeeMakerComponent.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

#include "Widgets/UIComponent.hpp"

using namespace CoffeeMaker;
using namespace CoffeeMaker::UIProperties;

void CoffeeMakerComponent::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerComponent::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerComponent::testComponentCreation() {
  // UIComponent* parent = new UIComponent();
  // UIComponent* child = new UIComponent();
  std::shared_ptr<UIComponent> greatGrandChild(new UIComponent());

  {
    std::shared_ptr<UIComponent> greatGrandChild2 = greatGrandChild;
    std::unique_ptr<UIComponent> grandchild(new UIComponent());

    grandchild->clientRect.x = 0;
    grandchild->clientRect.y = 0;
  }

  // parent->AppendChild(child);

  // delete parent;

  CPPUNIT_ASSERT_EQUAL(true, true);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerComponent);
