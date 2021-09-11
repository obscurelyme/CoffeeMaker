#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestCase.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/XmlOutputter.h>
#include <iostream>

class BasicMath
{
public:
  int Addition(int x, int y)
  {
    return x + y;
  }

  int Subtraction(int x, int y)
  {
    return x - y;
  }
};

class TestBasicMathFixture : CppUnit::TestFixture
{
private:
  BasicMath *bm;

public:
  void setUp()
  {
    bm = new BasicMath();
  }

  void tearDown()
  {
    delete bm;
  }

  void testAddition()
  {
    CPPUNIT_ASSERT_EQUAL(bm->Addition(5, 5), 11);
  }

  void testSubtraction()
  {
    CPPUNIT_ASSERT_EQUAL(bm->Subtraction(5, 5), 0);
  }
};

// CPPUNIT_TEST_SUITE_REGISTRATION(TestBasicMathFixture);

int main()
{
  CppUnit::TestCaller<TestBasicMathFixture> test("Test Basic Math Functions", &TestBasicMathFixture::testAddition);
  CppUnit::TestResultCollector collectedResults;
  CppUnit::BriefTestProgressListener progress;
  CppUnit::TestResult result;

  result.addListener(&progress);
  result.addListener(&collectedResults);

  test.run(&result);

  CppUnit::CompilerOutputter compilerOutputter(&collectedResults, std::cerr);
  compilerOutputter.write();

  std::ofstream xmlFileOut("cppTestBasicMathFunction.xml");
  CppUnit::XmlOutputter xmlOut(&collectedResults, xmlFileOut);
  xmlOut.write();

  return collectedResults.wasSuccessful() ? 0 : 1;
}