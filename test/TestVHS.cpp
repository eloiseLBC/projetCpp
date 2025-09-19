#include <iostream>
#include <string>
#include "Tests.h"
#include "TestVHS.h"
#include "models/VHS.h"

using namespace TAssert;

void TestVHS::runAllTests() {
    std::cout << "=== RUNNING VHS TESTS ===\n";

    std::cout << "\n- Default Constructor -\n";
    {
        VHS v;
        assert_equal(std::string("Unknown"), v.getTitle(), "Default title");
        assert_equal(std::string("Unknown"), v.getAuthor(), "Default author");
        assert_equal(0, v.getSecondesDuration(), "Default duration");
        assert_equal(std::string("Unknown"), v.getProductionCompany(), "Default studio");
        is_true(!v.getBorrowed(), "Default borrowed status");
    }

    std::cout << "\n- Parameterized Constructor -\n";
    {
        VHS v("Inception", "Christopher Nolan", true, 8880, "Warner Bros.");
        assert_equal(std::string("Inception"), v.getTitle(), "Parameterized title");
        assert_equal(std::string("Christopher Nolan"), v.getAuthor(), "Parameterized author");
        assert_equal(8880, v.getSecondesDuration(), "Duration");
        assert_equal(std::string("Warner Bros."), v.getProductionCompany(), "Studio");
        is_true(v.getBorrowed(), "Borrowed status");
    }

    std::cout << "\n- Setters -\n";
    {
        VHS v;
        v.setTitle("New Title");
        assert_equal(std::string("New Title"), v.getTitle(), "Set title");
        v.setAuthor("New Author");
        assert_equal(std::string("New Author"), v.getAuthor(), "Set author");
        v.setSecondesDuration(120);
        assert_equal(120, v.getSecondesDuration(), "Set duration");
        v.setProductionCompany("New Studio");
        assert_equal(std::string("New Studio"), v.getProductionCompany(), "Set studio");
        v.setBorrowed(true);
        is_true(v.getBorrowed(), "Set borrowed");
    }

    std::cout << "\n- Getters -\n";
    {
        VHS v("Inception", "Christopher Nolan", true, 8880, "Warner Bros.");
        assert_equal(std::string("Inception"), v.getTitle(), "Get title");
        assert_equal(std::string("Christopher Nolan"), v.getAuthor(), "Get author");
        assert_equal(8880, v.getSecondesDuration(), "Get duration");
        assert_equal(std::string("Warner Bros."), v.getProductionCompany(), "Get studio");
    }

    std::cout << "\n- Search -\n";
    {
        VHS v("Inception", "Christopher Nolan", true, 8880, "Warner Bros.");
        is_true(v.contains("Inception"),   "Search by title");
        is_true(v.contains("Christopher"), "Search by author");
        is_true(!v.contains("xyz"),        "Search non-existent");
    }
}

// Auto-enregistrement de la suite :
REGISTER_TEST_SUITE(TestVHS)