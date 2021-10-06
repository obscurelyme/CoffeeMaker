#include <cppunit/Test.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

#include <iostream>

class CustomProgressListener : public CppUnit::TextTestProgressListener {
  public:
  CustomProgressListener() {}
  ~CustomProgressListener() = default;

  void startTest(CppUnit::Test *test) override { std::cout << "Running test: " << test->getName() << std::endl; };

  // void addFailure(const CppUnit::TestFailure &failure) override{
  //   TODO(obscurelyme): do some stuff on failure
  // };

  // void endTestRun(CppUnit::Test *test, CppUnit::TestResult *eventManager) override{
  //    TODO(obscurelyme): do some stuff on end
  // };
};

int main(int argc, char **argv) {
  CustomProgressListener progress;
  CppUnit::TextTestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

  runner.addTest(registry.makeTest());
  runner.eventManager().addListener(&progress);

  if (argc > 1) {
    /**
     * Test name format is [className]::[methodName]
     * ie: MyTestSuite::testCasec
     */
    std::cout << "Running isolated test: " << argv[1] << std::endl;

    bool wasSuccessful = runner.run(argv[1], false);

    return wasSuccessful ? 0 : 1;
  }

  bool wasSuccessful = runner.run("", false);

  return wasSuccessful ? 0 : 1;
}
