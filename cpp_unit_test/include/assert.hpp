#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <string>
#include <iostream>

class CPP_UNIT_ASSERT {
    private: 
        int total_tests;
        int failed_tests;
        std::string log_messages;

        // ANSI Colors
        const std::string RESET   = "\033[0m";
        const std::string RED     = "\033[31m";
        const std::string GREEN   = "\033[32m";
        const std::string YELLOW  = "\033[33m";
        const std::string CYAN    = "\033[36m";
        const std::string WHITE   = "\033[37m";
        const std::string BOLD    = "\033[1m";

        void printHeader() const;
        void printSummary() const;

    public:
        CPP_UNIT_ASSERT();
        ~CPP_UNIT_ASSERT();
        
        void assert_equals(const std::string& act, const std::string& exp);
        void assert_equals(int act, int exp);
        void assert_equals(bool act, bool exp);
};

#endif