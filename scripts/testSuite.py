testSuiteHeaderFileName = ""
testSuiteImplFileName = ""
testSuiteName = ""

baseHeaderFile = """
#ifndef _coffeemaker_%s_hpp
#define _coffeemaker_%s_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class %s : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(%s);
  // TODO append your unit tests here
  // ie: CPPUNIT_TEST([TEST_NAME_HERE])
  CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();
};

#endif
"""

baseImplFile = """
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "%s.hpp"

void %s::setUp() {
  // TODO: Implement set up logic...
}

void %s::tearDown() {
  // TODO: Implement tear down logic...
}

CPPUNIT_TEST_SUITE_REGISTRATION(%s);

"""

def interpolateHeaderWithTestSuiteName(str):
  return str % (testSuiteName.lower(),  testSuiteName.lower(), testSuiteName, testSuiteName)

def interpolateImplWithTestSuiteName(str):
  return str % (testSuiteName, testSuiteName, testSuiteName, testSuiteName)

testSuiteRootDir = "tests"
testSuiteIncludeDir = "%s/include" % testSuiteRootDir

testSuiteName = input("Enter the name of this test suite: ")

testSuiteHeaderFileName = "%s.hpp" % testSuiteName
testSuiteImplFileName = "%s.cpp" % testSuiteName

testSuiteHeaderFilePath = "%s/%s" % (testSuiteIncludeDir, testSuiteHeaderFileName)
testSuiteImplFilePath = "%s/%s" % (testSuiteRootDir, testSuiteImplFileName)

headerFile = open(testSuiteHeaderFilePath, "w+")
implFile = open(testSuiteImplFilePath, "w+")

print("Writing new file: %s..." % headerFile.name)
print("Writing new file: %s..." % implFile.name)

headerFile.write(interpolateHeaderWithTestSuiteName(baseHeaderFile))
implFile.write(interpolateImplWithTestSuiteName(baseImplFile))

print("Header and Implementation file written!")

headerFile.close()
implFile.close()
