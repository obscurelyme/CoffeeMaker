
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestWithMocking.hpp"

#define CREATE_CALL_COUNT_SPY(function)  \
  public:                 \
    mutable int _##function##CallCount; \
    int function##CallCount() { return _##function##CallCount; }


/**
 * MockPerson class contains noop methods from the IPerson interface.
 */
class MockPerson : public IPerson
{
  CREATE_CALL_COUNT_SPY(talkTo)
  CREATE_CALL_COUNT_SPY(acknowledge)
  CREATE_CALL_COUNT_SPY(getName)

  public:
    void talkTo(const IPerson&) const {
      _talkToCallCount++;
    }

    void acknowledge(const IPerson&) const {
      _acknowledgeCallCount++;
    }

    std::string getName() const {
      _getNameCallCount++;
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

  CPPUNIT_ASSERT(person2.acknowledgeCallCount() == 1);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestWithMocking);

