#include <iostream>
#include <string>
#include "TestArticle.h"
#include "Tests.h"
#include "models/Article.h"

using namespace TAssert;

void TestArticle::runAllTests() {
    std::cout << "=== RUNNING ARTICLE TESTS ===\n";
    std::cout << "\n- Default Constructor -\n";
    {
        Article a;
        assert_equal(std::string("Unknown"), a.getTitle(), "Default title");
        assert_equal(std::string("Unknown"), a.getAuthor(), "Default author");
        assert_equal(0, a.getYearPublished(), "Default year published");
        assert_equal(0, a.getNumberPages(), "Default number pages");
        assert_equal(std::string("Unknown"), a.getName(), "Default name");
        assert_equal(std::string("Unknown"), a.getEditor(), "Default editor");
        is_true(!a.getBorrowed(), "Default borrowed status");
    }

    std::cout << "\n- Parameterized Constructor -\n";
    {
        Article a("Science Today", "Various Authors", true, 2023, 120, "Science", "A monthly science magazine.", "SciMag Publishers", 5, "The Future of AI");
        assert_equal(std::string("Science Today"), a.getTitle(), "Parameterized title");
        assert_equal(std::string("Various Authors"), a.getAuthor(), "Parameterized author");
        assert_equal(2023, a.getYearPublished(), "Year published");
        assert_equal(120, a.getNumberPages(), "Number pages");
        assert_equal(std::string("The Future of AI"), a.getName(), "Article name");
        assert_equal(std::string("SciMag Publishers"), a.getEditor(), "Editor");
        is_true(a.getBorrowed(), "Borrowed status");
    }

    std::cout << "\n- Setters -\n";
    {
        Article a;
        a.setTitle("New Title");
        assert_equal(std::string("New Title"), a.getTitle(), "Set title");
        a.setAuthor("New Author");
        assert_equal(std::string("New Author"), a.getAuthor(), "Set author");
        a.setYearPublished(2023);
        assert_equal(2023, a.getYearPublished(), "Set year published");
        a.setNumberPages(150);
        assert_equal(150, a.getNumberPages(), "Set number pages");
        a.setName("New Article Name");
        assert_equal(std::string("New Article Name"), a.getName(), "Set article name");
        a.setEditor("New Editor");
        assert_equal(std::string("New Editor"), a.getEditor(), "Set editor");
        a.setBorrowed(true);
        is_true(a.getBorrowed(), "Set borrowed");
    }
    std::cout << "\n- Search -\n";
    {
        Article a("Science Today", "Various Authors", true, 2023, 120, "Collection Mag", "A monthly science magazine.", "SciMag Publishers", 5, "The Future of AI");
        is_true(a.contains("Science Today"),   "Search by title");
        is_true(a.contains("Various"),         "Search by author");
        is_true(a.contains("Future"),          "Search by article name");
        is_true(a.contains("SciMag"),         "Search by editor");
        is_true(a.contains("Collection Mag"), "Search by collection");
        is_true(!a.contains("xyz"),            "Search non-existent");
    }
}

// Auto-enregistrement de la suite :
REGISTER_TEST_SUITE(TestArticle)