#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>

int main(int argc, char** argv)
{
	CppUnit::TextUi::TestRunner testRunner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	testRunner.addTest(registry.makeTest());

	if (argc > 1) {
		/**
		 * Test name format is [className]::[methodName]
		 * ie: MyTestSuite::testCase
		 */
		std::cout << "Running isolated test: " << argv[1] << std::endl;

		bool wasSuccessful = testRunner.run(argv[1], false);

		return wasSuccessful ? 0 : 1;
	}

	bool wasSuccessful = testRunner.run("", false);

  return wasSuccessful ? 0 : 1;
}
