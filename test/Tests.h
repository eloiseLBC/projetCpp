#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>

// ========= Compteurs globaux =========
namespace TCore {
    extern int testsRun;
    extern int testsPassed;
}

// ========= Assertions =========
namespace TAssert {
    void assert_equal(const std::string& expected, const std::string& actual, const std::string& testName);
    void assert_equal(int expected, int actual, const std::string& testName);
    void is_true(bool condition, const std::string& testName);
}

// ========= Registre des suites =========
struct TestSuite {
    std::string name;
    std::function<void()> run; // appelle runAllTests() de la suite
};

namespace TRegistry {
    // Renvoie une référence sur le vecteur unique
    std::vector<TestSuite>& all();
    void register_suite(const std::string& name, std::function<void()> runner);
}

// ========= Récap global =========
namespace TSummary {
    void print_global();
}

// ========= Macro pour s’auto-enregistrer =========
// À mettre en bas de chaque fichier de suite de tests (.cpp)
#define REGISTER_TEST_SUITE(SUITE_CLASS)                             \
namespace {                                                       \
struct SUITE_CLASS##_registrar {                              \
SUITE_CLASS##_registrar() {                               \
TRegistry::register_suite(#SUITE_CLASS, [](){         \
SUITE_CLASS suite;                                \
suite.runAllTests();                              \
});                                                   \
}                                                         \
};                                                            \
static SUITE_CLASS##_registrar global_##SUITE_CLASS##_registrar; \
}
