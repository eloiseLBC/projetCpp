#include <iostream>
#include <string>
#include "Tests.h"
#include "TestReview.h"
#include "models/Review.h"

using namespace TAssert;

void TestReview::runAllTests() {
    std::cout << "=== RUNNING REVIEW TESTS ===\n";
    std::cout << "\n- Default Constructor -\n";
    {
        Review r;
        assert_equal(std::string("Unknown"), r.getTitle(), "Default title");
        assert_equal(std::string("Unknown"), r.getAuthor(), "Default author");
        assert_equal(0, r.getYearPublished(), "Default year published");
        assert_equal(0, r.getNumberPages(), "Default number pages");
        assert_equal(std::string("Unknown"), r.getCollection(), "Default collection");
        assert_equal(std::string("No summary available."), r.getSummary(), "Default summary");
        assert_equal(std::string("Unknown"), r.getEditor(), "Default editor");
        assert_equal(0, r.getNumberArticles(), "Default number articles");
        is_true(!r.getBorrowed(), "Default borrowed status");
    }

    std::cout << "\n- Parameterized Constructor -\n";
    {
        Review r("Tech Review", "Jane Doe", true, 2023, 150, "Technology", "A review of the latest in tech.", "Tech Publishers", 10);
        assert_equal(std::string("Tech Review"), r.getTitle(), "Parameterized title");
        assert_equal(std::string("Jane Doe"), r.getAuthor(), "Parameterized author");
        assert_equal(2023, r.getYearPublished(), "Year published");
        assert_equal(150, r.getNumberPages(), "Number pages");
        assert_equal(std::string("Technology"), r.getCollection(), "Collection");
        assert_equal(std::string("A review of the latest in tech."), r.getSummary(), "Summary");
        assert_equal(std::string("Tech Publishers"), r.getEditor(), "Editor");
        assert_equal(10, r.getNumberArticles(), "Number articles");
        is_true(r.getBorrowed(), "Borrowed status");
    }

    std::cout << "\n- Setters -\n";
    {
        Review r;
        r.setTitle("New Title");
        assert_equal(std::string("New Title"), r.getTitle(), "Set title");
        r.setAuthor("New Author");
        assert_equal(std::string("New Author"), r.getAuthor(), "Set author");
        r.setYearPublished(2023);
        assert_equal(2023, r.getYearPublished(), "Set year published");
        r.setNumberPages(150);
        assert_equal(150, r.getNumberPages(), "Set number pages");
        r.setCollection("New Collection");
        assert_equal(std::string("New Collection"), r.getCollection(), "Set collection");
        r.setSummary("New Summary");
        assert_equal(std::string("New Summary"), r.getSummary(), "Set summary");
        r.setEditor("New Editor");
        assert_equal(std::string("New Editor"), r.getEditor(), "Set editor");
        r.setNumberArticles(15);
        assert_equal(15, r.getNumberArticles(), "Set number articles");
        r.setBorrowed(true);
        is_true(r.getBorrowed(), "Set borrowed");
    }

    std::cout << "\n- Search -\n";
    {
        Review r("Tech Review", "Jane Doe", true, 2023, 150, "Technology", "A review of the latest in tech.", "Tech Publishers", 10);
        is_true(r.contains("Tech Review"),   "Search by title");
        is_true(r.contains("Jane"),          "Search by author");
        is_true(r.contains("Tech"),          "Search by collection");
        is_true(r.contains("latest"),        "Search by summary");
        is_true(r.contains("Tech Publishers"), "Search by editor");
        is_true(!r.contains("xyz"),          "Search non-existent");
    }

    std::cout << "\n- Setters -\n";
    {
        Review r;
        r.setTitle("New Title");
        assert_equal(std::string("New Title"), r.getTitle(), "Set title");
        r.setAuthor("New Author");
        assert_equal(std::string("New Author"), r.getAuthor(), "Set author");
        r.setYearPublished(2023);
        assert_equal(2023, r.getYearPublished(), "Set year published");
    }
}

// Auto-enregistrement de la suite :
REGISTER_TEST_SUITE(TestReview)