/*
Copyright 2024-2024 plapacz6@gmail.com

This file is part of cksigreaction.

cksigreaction is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

cksigreaction is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
 with cksigreaction. If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <cstdarg>

#include "gtest/gtest.h"
#include "../parse_args.h"

using namespace std;
using namespace testing;

TEST(signals_description, konstruct_destruct) {
    signal_description_T *sd = new_signal_description_T(
                                   const_cast<char*>("sIG9"), 9
                               );
    ASSERT_STREQ(sd->name, "sIG9");
    ASSERT_EQ(sd->val, 9);
    delete_signal_description_T(&sd);
    ASSERT_EQ(sd, nullptr);
    delete_signal_description_T(&sd);
    ASSERT_EQ(sd, nullptr);
}

class test_f_parse_args : public testing::Test {
protected:

    struct application_test_conditions_T atc;
    int argc;
    char **argv;

public:

    test_f_parse_args() {
        // argc = 0;
        // argv = nullptr;
        // atc.app_name = nullptr;
        // atc.app_args = nullptr;
        // atc.signals = nullptr;
        // atc.signals_number = 0;
    }

    void SetUp() override {
        argc = 0;
        argv = nullptr;
        atc.app_name = nullptr;
        atc.app_args = nullptr;
        atc.signals = nullptr;
        atc.signals_number = 0;
    }

    void SetUpArgv(int argc, ...) {
        this->argc = argc;
        argv = new char*[argc];
        if(!argv) {
            cerr << "new" << endl;
            exit(1);
        }

        va_list va;
        va_start(va, argc);
        for(size_t i = 0; i < (size_t)argc; ++i) {
            argv[i] = va_arg(va, char*);
        }
        va_end(va);
    }

    void TearDown() override {
        if(argv) {
            delete argv;
            argv = nullptr;
            argc = 0;
        }
        if(atc.app_name) {
            delete atc.app_name;
            atc.app_name = nullptr;
        }
        if(atc.app_args) {
            delete atc.app_args;
            atc.app_args = nullptr;
        }
        if(atc.signals) {
            for(size_t i = 0; i < (size_t)atc.signals_number; ++i) {
                if(atc.signals[i]) {
                    delete_signal_description_T(&atc.signals[i]);
                }
            }
            delete atc.signals;
            atc.signals = nullptr;
            atc.signals_number = 0;
        }
        // optind = 0;  //reset getopt()  //parse_args must do this
    }
};

TEST_F(test_f_parse_args, SetUpArgv) {
    SetUpArgv(4,
              "this_program",
              "--app=app_name",
              "--sigs=SIGALRM:SIGINTR",
              "--appargs=-ax *"
             );
    ASSERT_EQ(argc, 4);
    ASSERT_EQ(argv[0], "this_program");
    ASSERT_EQ(argv[1], "--app=app_name");
    ASSERT_EQ(argv[2], "--sigs=SIGALRM:SIGINTR");
    ASSERT_EQ(argv[3], "--appargs=-ax *");

    ASSERT_EQ(atc.app_name, nullptr);
    ASSERT_EQ(atc.app_args, nullptr);
    ASSERT_EQ(atc.signals, nullptr);
    ASSERT_EQ(atc.signals_number, 0);
}

TEST_F(test_f_parse_args, usage__empty_args_list) {
    SetUpArgv(1,
              "this_program"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(-1, ret);
    ASSERT_EQ(argv[0], "this_program");

    ASSERT_EQ(atc.app_name, nullptr);
    ASSERT_EQ(atc.app_args, nullptr);
    ASSERT_EQ(atc.signals, nullptr);
    ASSERT_EQ(atc.signals_number, 0);
}

TEST_F(test_f_parse_args, usage__only_app_name) {
    SetUpArgv(2,
              "this_program",
              "--app=app_name"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(-1, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_EQ(atc.app_args, nullptr);
    ASSERT_EQ(atc.signals, nullptr);
    ASSERT_EQ(atc.signals_number, 0);
}

TEST_F(test_f_parse_args, correct__app_name_and_1_sigs) {
    SetUpArgv(3,
              "this_program",
              "--app=app_name",
              "--sigs=SIGALRM"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(0, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_EQ(atc.app_args, nullptr);
    ASSERT_STREQ(atc.signals[0]->name, "SIGALRM");
    ASSERT_EQ(atc.signals_number, 1);
}

TEST_F(test_f_parse_args, correct__app_name_and_2_sigs) {
    SetUpArgv(3,
              "this_program",
              "--app=app_name",
              "--sigs=SIGALRM:SIGINTR"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(0, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_EQ(atc.app_args, nullptr);
    ASSERT_STREQ(atc.signals[0]->name, "SIGALRM");
    ASSERT_STREQ(atc.signals[1]->name, "SIGINTR");
    ASSERT_EQ(atc.signals_number, 2);
}

TEST_F(test_f_parse_args, usage__app_name_and_1AND_sigs) {
    SetUpArgv(3,
              "this_program",
              "--app=app_name",
              "--sigs=SIGALRM:"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(-1, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_EQ(atc.app_args, nullptr);
    ASSERT_STREQ(atc.signals[0]->name, "SIGALRM");
    ASSERT_STREQ(atc.signals[1]->name, "");
    ASSERT_EQ(atc.signals_number, 2);
}

TEST_F(test_f_parse_args, correct__app_name_3_sigs_and_app_1_args) {
    SetUpArgv(4,
              "this_program",
              "--app=app_name",
              "--sigs=SIGALRM:SIGINTR:SIGTERM",
              "--appargs=-ax"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(0, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_STREQ(atc.app_args, "-ax");
    ASSERT_STREQ(atc.signals[0]->name, "SIGALRM");
    ASSERT_STREQ(atc.signals[1]->name, "SIGINTR");
    ASSERT_STREQ(atc.signals[2]->name, "SIGTERM");
    ASSERT_EQ(atc.signals_number, 3);
}

TEST_F(test_f_parse_args, correct__app_name_2_sigs_and_app_4_args) {
    SetUpArgv(7,
              "this_program",
              "--app=app_name",
              "--sigs=SIGALRM:SIGINTR",
              "--appargs=-ax",
              "*",
              "-o",
              "N"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(0, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_STREQ(atc.app_args, "-ax * -o N");
    ASSERT_STREQ(atc.signals[0]->name, "SIGALRM");
    ASSERT_STREQ(atc.signals[1]->name, "SIGINTR");
    ASSERT_EQ(atc.signals_number, 2);
}

TEST_F(test_f_parse_args, usage__app_name_0_sigs_and_app_4_args) {
    SetUpArgv(6,
              "this_program",
              "--app=app_name",
              "--appargs=-ax",
              "*",
              "-o",
              "N"
             );
    int ret = parse_args(argc, argv, &atc);
    ASSERT_EQ(-1, ret);

    ASSERT_STREQ(atc.app_name, "app_name");
    ASSERT_STREQ(atc.app_args, "-ax * -o N");
    ASSERT_EQ(atc.signals, nullptr);
    ASSERT_EQ(atc.signals_number, 0);
}
