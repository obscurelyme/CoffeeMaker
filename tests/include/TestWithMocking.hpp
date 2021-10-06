
#ifndef _coffeemaker_testwithmocking_hpp
#define _coffeemaker_testwithmocking_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <string>

/**
 * Interface for a person object
 */
class IPerson
{
  public:
    virtual ~IPerson() = default;
    virtual void talkTo(const IPerson& person) const = 0;
    virtual void acknowledge(const IPerson& person) const = 0;
    virtual std::string getName() const = 0;
};

/**
 * Base Person object that implements the IPerson interface
 */
class Person : public IPerson
{
  public:
    Person();

    void talkTo(const IPerson& person) const;
    void acknowledge(const IPerson& person) const;
    std::string getName() const;

    std::string name;
    int age;
};

class TestWithMocking : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestWithMocking);
  CPPUNIT_TEST(testInitializePersonDataMembers);
  CPPUNIT_TEST(testPersonCanTalkToOtherPerson);
  CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void testInitializePersonDataMembers();
    void testPersonCanTalkToOtherPerson();
};

#endif
