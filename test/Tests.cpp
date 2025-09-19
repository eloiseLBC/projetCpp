#include "Tests.h"

// ========= Compteurs =========
int TCore::testsRun = 0;
int TCore::testsPassed = 0;

// ========= Assertions =========
void TAssert::assert_equal(const std::string& expected, const std::string& actual, const std::string& testName) {
    TCore::testsRun++;
    if (expected == actual) {
        TCore::testsPassed++;
        std::cout << "✓ " << testName << " PASSED\n";
    } else {
        std::cout << "✗ " << testName << " FAILED\n"
                  << "  Expected: " << expected << "\n"
                  << "  Actual: " << actual << "\n";
    }
}

void TAssert::assert_equal(int expected, int actual, const std::string& testName) {
    TCore::testsRun++;
    if (expected == actual) {
        TCore::testsPassed++;
        std::cout << "✓ " << testName << " PASSED\n";
    } else {
        std::cout << "✗ " << testName << " FAILED\n"
                  << "  Expected: " << expected << "\n"
                  << "  Actual: " << actual << "\n";
    }
}

void TAssert::is_true(bool condition, const std::string& testName) {
    TCore::testsRun++;
    if (condition) {
        TCore::testsPassed++;
        std::cout << "✓ " << testName << " PASSED\n";
    } else {
        std::cout << "✗ " << testName << " FAILED\n";
    }
}

// ========= Registre =========
std::vector<TestSuite>& TRegistry::all() {
    static std::vector<TestSuite> suites;
    return suites;
}

void TRegistry::register_suite(const std::string& name, std::function<void()> runner) {
    all().push_back({name, std::move(runner)});
}

// ========= Résumé global =========
void TSummary::print_global() {
    using namespace TCore;
    std::cout << "\n=== GLOBAL TEST RESULTS ===\n"
              << "Tests run: " << testsRun << "\n"
              << "Tests passed: " << testsPassed << "\n"
              << "Tests failed: " << (testsRun - testsPassed) << "\n";
    if (testsPassed == testsRun) std::cout << "ALL TESTS PASSED!\n";
    else std::cout << "SOME TESTS FAILED!\n";
}

// ========= main() =========
int main() {
    std::cout << "=== DISCOVERING & RUNNING TEST SUITES ===\n";
    for (auto& s : TRegistry::all()) {
        std::cout << "\n--- Running suite: " << s.name << " ---\n";
        s.run();
    }
    TSummary::print_global();
    return (TCore::testsRun == TCore::testsPassed) ? 0 : 1;
}
