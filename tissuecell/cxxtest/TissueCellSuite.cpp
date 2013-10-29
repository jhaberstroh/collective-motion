/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_TissueCellSuite_init = false;
#include "TissueCellSuite.h"

static TissueCellSuite suite_TissueCellSuite;

static CxxTest::List Tests_TissueCellSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TissueCellSuite( "TissueCellSuite.h", 6, "TissueCellSuite", suite_TissueCellSuite, Tests_TissueCellSuite );

static class TestDescription_suite_TissueCellSuite_testCreate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testCreate() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 31, "testCreate" ) {}
 void runTest() { suite_TissueCellSuite.testCreate(); }
} testDescription_suite_TissueCellSuite_testCreate;

static class TestDescription_suite_TissueCellSuite_testCardinalUnit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testCardinalUnit() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 36, "testCardinalUnit" ) {}
 void runTest() { suite_TissueCellSuite.testCardinalUnit(); }
} testDescription_suite_TissueCellSuite_testCardinalUnit;

static class TestDescription_suite_TissueCellSuite_testOneStep : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testOneStep() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 74, "testOneStep" ) {}
 void runTest() { suite_TissueCellSuite.testOneStep(); }
} testDescription_suite_TissueCellSuite_testOneStep;

static class TestDescription_suite_TissueCellSuite_testLRUDMoveReal : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testLRUDMoveReal() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 84, "testLRUDMoveReal" ) {}
 void runTest() { suite_TissueCellSuite.testLRUDMoveReal(); }
} testDescription_suite_TissueCellSuite_testLRUDMoveReal;

static class TestDescription_suite_TissueCellSuite_testLRUDForceReal : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testLRUDForceReal() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 106, "testLRUDForceReal" ) {}
 void runTest() { suite_TissueCellSuite.testLRUDForceReal(); }
} testDescription_suite_TissueCellSuite_testLRUDForceReal;

static class TestDescription_suite_TissueCellSuite_testOneInteract : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testOneInteract() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 137, "testOneInteract" ) {}
 void runTest() { suite_TissueCellSuite.testOneInteract(); }
} testDescription_suite_TissueCellSuite_testOneInteract;

static class TestDescription_suite_TissueCellSuite_testManyBalance : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testManyBalance() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 152, "testManyBalance" ) {}
 void runTest() { suite_TissueCellSuite.testManyBalance(); }
} testDescription_suite_TissueCellSuite_testManyBalance;

static class TestDescription_suite_TissueCellSuite_testGenerateLattice : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testGenerateLattice() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 170, "testGenerateLattice" ) {}
 void runTest() { suite_TissueCellSuite.testGenerateLattice(); }
} testDescription_suite_TissueCellSuite_testGenerateLattice;

static class TestDescription_suite_TissueCellSuite_testTwoStepNoForce : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TissueCellSuite_testTwoStepNoForce() : CxxTest::RealTestDescription( Tests_TissueCellSuite, suiteDescription_TissueCellSuite, 181, "testTwoStepNoForce" ) {}
 void runTest() { suite_TissueCellSuite.testTwoStepNoForce(); }
} testDescription_suite_TissueCellSuite_testTwoStepNoForce;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
