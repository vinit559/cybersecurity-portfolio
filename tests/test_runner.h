#pragma once
#include <iostream>
#include <vector>
#include <string>

class TestRunner {
public:
    struct Failure { std::string test; std::string msg; };

    void expectTrue(bool cond, const std::string& test, const std::string& msg="") {
        if (!cond) failures.push_back({test, msg});
    }

    void expectEq(double a, double b, const std::string& test) {
        if (a != b) {
            failures.push_back({test, "expected: " + std::to_string(b) + ", got: " + std::to_string(a)});
        }
    }

    void expectApprox(double a, double b, double eps, const std::string& test) {
        if (std::fabs(a-b) > eps) {
            failures.push_back({test, "expected approx: " + std::to_string(b) + ", got: " + std::to_string(a)});
        }
    }

    int report() {
        if (failures.empty()) {
            std::cout << "All custom tests passed" << std::endl;
            return 0;
        }
        std::cout << failures.size() << " test(s) failed:\n";
        for (auto &f : failures) {
            std::cout << "- " << f.test << ": " << f.msg << std::endl;
        }
        return 1;
    }
private:
    std::vector<Failure> failures;
};
