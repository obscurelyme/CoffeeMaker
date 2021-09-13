
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestWithMocking.hpp"

/**
 * MockPerson class contains noop methods from the IPerson interface.
 */
class MockPerson : public IPerson
{
  public:
    mutable int talkToCallCount;
    mutable int acknowledgeCallCount;
    mutable int getNameCallCount;

    MockPerson(): talkToCallCount(0), acknowledgeCallCount(0), getNameCallCount(0) {}

    void talkTo(const IPerson&) const {
      talkToCallCount++;
    }
    void acknowledge(const IPerson&) const {
      acknowledgeCallCount++;
    }
    std::string getName() const {
      getNameCallCount++;
      return "";
    }

    std::string name;
    int age;
};

Person::Person(): name(""), age(0) {}

std::string Person::getName() const {
  return this->name;
}

void Person::talkTo(const IPerson& p) const {
  p.acknowledge(*this);
}

void Person::acknowledge(const IPerson& p) const {
  std::cout << this->name << " acknowledges " << p.getName() << std::endl;
}

void TestWithMocking::setUp() {
  // TODO: Implement set up logic...
}

void TestWithMocking::tearDown() {
  // TODO: Implement tear down logic...
}

void TestWithMocking::testInitializePersonDataMembers() {
  Person s;
  std::string emptyStr = "";
  CPPUNIT_ASSERT_EQUAL(s.name, emptyStr);
  CPPUNIT_ASSERT_EQUAL(s.age, 0);
}

void TestWithMocking::testPersonCanTalkToOtherPerson() {
  Person person1;
  person1.name = "John";
  MockPerson person2;
  person2.name = "Jane";

  person1.talkTo(person2);

  CPPUNIT_ASSERT(person2.acknowledgeCallCount == 2);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestWithMocking);

