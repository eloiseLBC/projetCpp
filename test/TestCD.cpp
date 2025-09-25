#include <iostream>
#include <string>
#include "TestCD.h"
#include "Tests.h"
#include "models/CD.h"

using namespace TAssert;

void TestCD::runAllTests() {
    std::cout << "=== RUNNING CD TESTS ===\n";
    std::cout << "\n- Default constructor -\n";

    {
        CD c;
        assert_equal(std::string("Unknown"), c.getTitle(), "Default title");
        assert_equal(std::string("Unknown"), c.getAuthor(), "Default author");
        assert_equal(0, c.getSecondesDuration(), "Default duration");
        assert_equal(0, c.getNumberTracks(), "Default number of tracks");
        assert_equal(std::string("Unknown"), c.getProductionCompany(), "Default production company");
        is_true(!c.getBorrowed(), "Default borrowed status");
    }

    std::cout << "\n- Parameterized Constructor -\n";
    {
        CD c("Thriller", "Michael Jackson", true, 2580, 9, "Pop Record");
        assert_equal(std::string("Thriller"), c.getTitle(), "Parameterized title");
        assert_equal(std::string("Michael Jackson"), c.getAuthor(), "Parameterized author");
        assert_equal(2580, c.getSecondesDuration(), "Duration");
        assert_equal(9, c.getNumberTracks(), "Number of tracks");
        assert_equal(std::string("Pop Record"), c.getProductionCompany(), "Production company");
        is_true(c.getBorrowed(), "Borrowed status");
    }

    std::cout << "\n- Setters -\n";
    {
        CD c;
        c.setTitle("New Title");
        assert_equal(std::string("New Title"), c.getTitle(), "Set title");
        c.setAuthor("New Author");
        assert_equal(std::string("New Author"), c.getAuthor(), "Set author");
        c.setSecondesDuration(3000);
        assert_equal(3000, c.getSecondesDuration(), "Set duration");
        c.setNumberTracks(12);
        assert_equal(12, c.getNumberTracks(), "Set number of tracks");
        c.setProductionCompany("New Production Company");
        assert_equal(std::string("New Production Company"), c.getProductionCompany(), "Set production company");
        c.setBorrowed(true);
        is_true(c.getBorrowed(), "Set borrowed");
    }

    std::cout << "\n- Search -\n";
    {
        CD c("Thriller", "Michael Jackson", true, 2580, 9, "Pop Record");
        is_true(c.contains("Thriller"),         "Search by title");
        is_true(c.contains("Michael"),          "Search by author");
        is_true(c.contains("Pop"),              "Search by production company");
        is_true(!c.contains("Nonexistent"),     "Search for nonexistent term");
    }
}

// Auto-enregistrement de la suite :
REGISTER_TEST_SUITE(TestCD)