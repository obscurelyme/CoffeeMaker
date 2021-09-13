
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestWithMocking.hpp"

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

  /**
   * MockPerson class contains noop methods from the IPerson interface.
   */
  class MockPerson : public IPerson
  {
    public:
      void talkTo(const IPerson&) const {
        // noop
      }
      void acknowledge(const IPerson&) const {
        // noop
      }
      std::string getName() const {
        return "";
      }

      std::string name;
      int age;
  };

  MockPerson person2;
  // Person person2;
  person2.name = "Jane";
  CPPUNIT_ASSERT_NO_THROW(person1.talkTo(person2));
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestWithMocking);

