#include <iostream>
#include <string>
#include "Tests.h"
#include "TestDigitalResource.h"
#include "models/DigitalResource.h"

using namespace TAssert;

void TestDigitalResource::runAllTests() {
    std::cout << "=== RUNNING BOOK TESTS ===\n";

    std::cout << "\n- Default Constructor -\n";
    {
        DigitalResource d;
        assert_equal(std::string("Unknown"), d.getTitle(), "Default title");
        assert_equal(std::string("Unknown"), d.getAuthor(), "Default author");
        assert_equal(0, d.getBytes(), "Default bytes");
        assert_equal("Unknown", d.getPath(), "Default path");
        assert_equal("Unknown", d.getTypeDigitalResource(), "Default type");
        is_true(!d.getBorrowed(), "Default borrowed status");
    }

    std::cout << "\n- Parameterized Constructor -\n";
    {
        DigitalResource dr("E-book on C++", "Bjarne Stroustrup", false, "PDF", 2048000, "/ebooks/cpp.pdf");
        assert_equal(std::string("E-book on C++"), dr.getTitle(), "Parameterized title");
        assert_equal(std::string("Bjarne Stroustrup"), dr.getAuthor(), "Parameterized author");
        assert_equal(std::string("PDF"), dr.getTypeDigitalResource(), "Parameterized type");
        assert_equal(2048000, dr.getBytes(), "Parameterized bytes");
        assert_equal("/ebooks/cpp.pdf", dr.getPath(), "Parameterized path");
        is_true(!dr.getBorrowed(), "Borrowed status");
    }

    std::cout << "\n- Setters -\n";
    {
        DigitalResource dr;
        dr.setTitle("New Title");
        assert_equal(std::string("New Title"), dr.getTitle(), "Set title");
        dr.setAuthor("New Author");
        assert_equal(std::string("New Author"), dr.getAuthor(), "Set author");
        dr.setTypeDigitalResource("CSV");
        assert_equal("CSV", dr.getTypeDigitalResource(), "Set type");
        dr.setBytes(500);
        assert_equal(500, dr.getBytes(), "Set bytes");
        dr.setPath("etc/etc/oui");
        assert_equal("etc/etc/oui", dr.getPath(), "Set path");
        dr.setBorrowed(true);
        is_true(dr.getBorrowed(), "Set borrowed");
    }

    std::cout << "\n- Search -\n";
    {
        DigitalResource dr("E-book on C++", "Bjarne Stroustrup", false, "PDF", 2048000, "/ebooks/cpp.pdf");
        is_true(dr.contains("E-book"),   "Search by title");
        is_true(dr.contains("Bjarne"),   "Search by author");
        is_true(dr.contains("PDF"),      "Search by type");
        is_true(dr.contains("cpp.pdf"),  "Search by path");
        is_true(!dr.contains("Nonexistent"), "Search for nonexistent term");
    }
}

// Auto-enregistrement de la suite :
REGISTER_TEST_SUITE(TestDigitalResource)
