#include "../include/assert.hpp"

CPP_UNIT_ASSERT::CPP_UNIT_ASSERT() {
    total_tests = 0;
    failed_tests = 0;
    log_messages = "";
}

CPP_UNIT_ASSERT::~CPP_UNIT_ASSERT() {
    printHeader();

    if (!log_messages.empty() && failed_tests > 0) {
        std::cout << log_messages << "\n";
    }

    printSummary();
}

void CPP_UNIT_ASSERT::assert_equals(const std::string& act, const std::string& exp) {
    total_tests++;

    if (act != exp) {
        failed_tests++;
        log_messages += 
            YELLOW + "[ TEST #" + std::to_string(total_tests) + " FAILED ]" + RESET + "\n"
            "  " + WHITE + "EXP: " + RESET + exp + "\n"
            "  " + WHITE + "ACT: " + RESET + act + "\n\n";
    } else {
        log_messages += GREEN + "[ TEST #" + std::to_string(total_tests) + " PASSED ]" + RESET + "\n\n";
    }
}

void CPP_UNIT_ASSERT::assert_equals(int act, int exp) {
    total_tests++;

    if (act != exp) {
        failed_tests++;
        log_messages += 
            YELLOW + "[ TEST #" + std::to_string(total_tests) + " FAILED ]" + RESET + "\n"
            "  " + WHITE + "EXP: " + RESET + std::to_string(exp) + "\n"
            "  " + WHITE + "ACT: " + RESET + std::to_string(act) + "\n\n";
    } else {
        log_messages += GREEN + "[ TEST #" + std::to_string(total_tests) + " PASSED ]" + RESET + "\n\n";
    }
}

void CPP_UNIT_ASSERT::assert_equals(bool act, bool exp) {
    total_tests++;

    if (act != exp) {
        failed_tests++;
        std::string act_str = act ? "true" : "false";
        std::string exp_str = exp ? "true" : "false";
        log_messages += 
            YELLOW + "[ TEST #" + std::to_string(total_tests) + " FAILED ]" + RESET + "\n"
            "  " + WHITE + "EXP: " + RESET + exp_str + "\n"
            "  " + WHITE + "ACT: " + RESET + act_str + "\n\n";
    } else {
        log_messages += GREEN + "[ TEST #" + std::to_string(total_tests) + " PASSED ]" + RESET + "\n\n";
    }
}

void CPP_UNIT_ASSERT::printHeader() const {
    std::cout << BOLD << CYAN << "========================================" << "\n" << CYAN << "#";
    std::cout << WHITE << "         CPP_UNIT_ASSERT REPORT       " << CYAN << "#" << "\n";
    std::cout << CYAN << "========================================" << RESET << "\n\n";
}

void CPP_UNIT_ASSERT::printSummary() const {
    if (failed_tests == 0) {
        std::cout << GREEN << BOLD << "[ ALL " << total_tests << " TESTS PASSED ]" << RESET << "\n\n";
    } else {
        std::cout << RED << BOLD << "[ FAIL ] " << RESET << BOLD << failed_tests << " / " << total_tests << " TESTS FAILED\n\n";
    }
}