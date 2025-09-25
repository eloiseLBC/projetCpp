#include <iostream>
#include <string>
#include "Tests.h"
#include "TestBook.h"
#include "models/Book.h"   // grâce à CMake include_dirs

using namespace TAssert;

void TestBook::runAllTests() {
    std::cout << "=== RUNNING BOOK TESTS ===\n";

    std::cout << "\n- Default Constructor -\n";
    {
        Book b;
        assert_equal(std::string("Unknown"), b.getTitle(), "Default title");
        assert_equal(std::string("Unknown"), b.getAuthor(), "Default author");
        assert_equal(0, b.getYearPublished(), "Default year");
        assert_equal(0, b.getNumberPages(), "Default pages");
        is_true(!b.getBorrowed(), "Default borrowed status");
    }

    std::cout << "\n- Parameterized Constructor -\n";
    {
        Book b("1984", "George Orwell", false, 1949, 328, "Dystopian", "A classic");
        assert_equal(std::string("1984"), b.getTitle(), "Parameterized title");
        assert_equal(std::string("George Orwell"), b.getAuthor(), "Parameterized author");
        assert_equal(1949, b.getYearPublished(), "Year");
        assert_equal(328, b.getNumberPages(), "Pages");
        is_true(!b.getBorrowed(), "Borrowed status");
    }

    std::cout << "\n- Setters -\n";
    {
        Book b;
        b.setTitle("New Title");
        assert_equal(std::string("New Title"), b.getTitle(), "Set title");
        b.setAuthor("New Author");
        assert_equal(std::string("New Author"), b.getAuthor(), "Set author");
        b.setYearPublished(2023);
        assert_equal(2023, b.getYearPublished(), "Set year");
        b.setNumberPages(500);
        assert_equal(500, b.getNumberPages(), "Set pages");
        b.setBorrowed(true);
        is_true(b.getBorrowed(), "Set borrowed");
    }

    std::cout << "\n- Search -\n";
    {
        Book b("1984", "George Orwell", false, 1949, 328, "Dystopian", "A classic");
        is_true(b.contains("1984"),   "Search by title");
        is_true(b.contains("George"), "Search by author");
        is_true(b.contains("Dystopian"), "Search by collection");
        is_true(!b.contains("xyz"),   "Search non-existent");
    }
}

// Auto-enregistrement de la suite :
REGISTER_TEST_SUITE(TestBook)
