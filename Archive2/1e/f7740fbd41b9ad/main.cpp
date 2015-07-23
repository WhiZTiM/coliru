#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ControllerTest

#include <boost/test/included/unit_test.hpp>
#include <boost/algorithm/string.hpp>

//#include <nddlgen/Controller.h>
namespace nddlgen {
    struct Controller {
        Controller(std::string*) {}
        bool setFileIdentifier(std::string) { return true; }
        std::string getInitialStateOutputFileName() { return "testmodel-initial-state.nddl"; }
        std::string getModelsOutputFileName() { return "testmodel-model.nddl"; }
    };
}

using namespace std;
using namespace nddlgen;
using namespace boost;
using namespace boost::unit_test;

struct UnitUnderTest
{
    UnitUnderTest()
    {
        c = new Controller(&this->errorText);
    }

    ~UnitUnderTest()
    {
        boost::checked_delete(c);
    }

    Controller* c;
    string errorText;
};

string existingFile = "res/testmodel.sdf";
string corruptedFile = "res/corruptedmodel.sdf";

/**
 * ======================================================
 * Tests for normal operation
 * ======================================================
 */
BOOST_AUTO_TEST_SUITE (ControllerTestNormalBehaviour)

    /**
     * Test if the output file names match the expected behavior.
     */
    BOOST_AUTO_TEST_CASE (testGetOutputFileNames)
    {
        UnitUnderTest uut;
        string actualModelOutputFileName;
        string actualInitialStateOutputFileName;

        // Should work since a file identifier has not been set yet
        BOOST_CHECK_EQUAL(uut.c->setFileIdentifier(existingFile), true);

        actualModelOutputFileName = uut.c->getModelsOutputFileName();
        actualInitialStateOutputFileName = uut.c->getInitialStateOutputFileName();

        BOOST_CHECK_EQUAL(actualModelOutputFileName, "testmodel-model.nddl");
        BOOST_CHECK_EQUAL(actualInitialStateOutputFileName, "testmodel-initial-state.nddl"); // This is line 72
    }

BOOST_AUTO_TEST_SUITE_END()
