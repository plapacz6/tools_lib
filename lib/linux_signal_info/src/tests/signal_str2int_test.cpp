/*
Copyright 2024-2024 plapacz6@gmail.com

This file is part of info_linux_signal.

info_linux_signal is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

info_linux_signal is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
 with info_linux_signal. If not, see <https://www.gnu.org/licenses/>.
*/

#include <signal.h>

#define PAIR_SIGNAL_NAME_VAL(X) {#X, X},
struct signal_name_val_T {
    const char *name;
    int val;
};
static const signal_name_val_T signal_name_val[] = {
PAIR_SIGNAL_NAME_VAL(SIGABRT)
PAIR_SIGNAL_NAME_VAL(SIGALRM)
PAIR_SIGNAL_NAME_VAL(SIGBUS)
PAIR_SIGNAL_NAME_VAL(SIGCHLD)
PAIR_SIGNAL_NAME_VAL(SIGCLD)
PAIR_SIGNAL_NAME_VAL(SIGCONT)
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGEMT)
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGFPE)
PAIR_SIGNAL_NAME_VAL(SIGHUP)
PAIR_SIGNAL_NAME_VAL(SIGILL)
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGINFO)
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGINT)
PAIR_SIGNAL_NAME_VAL(SIGIO)
PAIR_SIGNAL_NAME_VAL(SIGIOT)
PAIR_SIGNAL_NAME_VAL(SIGKILL)
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGLOST)
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGPIPE)
PAIR_SIGNAL_NAME_VAL(SIGPOLL)
PAIR_SIGNAL_NAME_VAL(SIGPROF)
PAIR_SIGNAL_NAME_VAL(SIGPWR)
PAIR_SIGNAL_NAME_VAL(SIGQUIT)
PAIR_SIGNAL_NAME_VAL(SIGSEGV)
PAIR_SIGNAL_NAME_VAL(SIGSTKFLT)
PAIR_SIGNAL_NAME_VAL(SIGSTOP)
PAIR_SIGNAL_NAME_VAL(SIGTSTP)
PAIR_SIGNAL_NAME_VAL(SIGSYS)
PAIR_SIGNAL_NAME_VAL(SIGTERM)
PAIR_SIGNAL_NAME_VAL(SIGTRAP)
PAIR_SIGNAL_NAME_VAL(SIGTTIN)
PAIR_SIGNAL_NAME_VAL(SIGTTOU)
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGUNUSED)
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
PAIR_SIGNAL_NAME_VAL(SIGURG)
PAIR_SIGNAL_NAME_VAL(SIGUSR1)
PAIR_SIGNAL_NAME_VAL(SIGUSR2)
PAIR_SIGNAL_NAME_VAL(SIGVTALRM)
PAIR_SIGNAL_NAME_VAL(SIGXCPU)
PAIR_SIGNAL_NAME_VAL(SIGXFSZ)
PAIR_SIGNAL_NAME_VAL(SIGWINCH)
{nullptr, -1},
};
#undef PAIR_SIGNAL_NAME_VAL //(X) {"#X", X},

#include <iostream>
#include <string>
#include <cstdarg>

#include "gtest/gtest.h"
#include "info_linux_signal/info_linux_signal.h"

TEST(signal_str2int, check_all_posix_signal) {
    size_t i = 0;
    while(signal_name_val[i].val != -1) {
        printf("%zu : %s\n", i, strsignal(i));
        ASSERT_EQ(signal_name_val[i].val, signal_str2int(signal_name_val[i].name));
        ++i;
    }
}
TEST(signal_str2int, wrong_name) {
    ASSERT_EQ(-1, signal_str2int(nullptr));
    ASSERT_EQ(-1, signal_str2int(""));
    ASSERT_EQ(-1, signal_str2int("AAA"));
    ASSERT_EQ(-1, signal_str2int(std::string(100, 'A').c_str()));
}