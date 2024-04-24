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
#include <string.h>
#include <stdlib.h>

#include "info_linux_signal/info_linux_signal.h"

typedef struct pair_sting_int_T {
    const char *string;
    int integer;
} pair_sting_int_T;

static const pair_sting_int_T signal_name_def[] = {
{"SIGABRT", SIGABRT},
{"SIGALRM", SIGALRM},
{"SIGBUS", SIGBUS},
{"SIGCHLD", SIGCHLD},
{"SIGCLD", SIGCLD},
{"SIGCONT", SIGCONT},
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGEMT", SIGEMT},
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGFPE", SIGFPE},
{"SIGHUP", SIGHUP},
{"SIGILL", SIGILL},
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGINFO", SIGINFO},
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGINT", SIGINT},
{"SIGIO", SIGIO},
{"SIGIOT", SIGIOT},
{"SIGKILL", SIGKILL},
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGLOST", SIGLOST},
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGPIPE", SIGPIPE},
{"SIGPOLL", SIGPOLL},
{"SIGPROF", SIGPROF},
{"SIGPWR", SIGPWR},
{"SIGQUIT", SIGQUIT},
{"SIGSEGV", SIGSEGV},
{"SIGSTKFLT", SIGSTKFLT},
{"SIGSTOP", SIGSTOP},
{"SIGTSTP", SIGTSTP},
{"SIGSYS", SIGSYS},
{"SIGTERM", SIGTERM},
{"SIGTRAP", SIGTRAP},
{"SIGTTIN", SIGTTIN},
{"SIGTTOU", SIGTTOU},
#ifdef OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGUNUSED", SIGUNUSED},
#endif //OTHER_THAN_X86_ARM_ARCHITECTURES
{"SIGURG", SIGURG},
{"SIGUSR1", SIGUSR1},
{"SIGUSR2", SIGUSR2},
{"SIGVTALRM", SIGVTALRM},
{"SIGXCPU", SIGXCPU},
{"SIGXFSZ", SIGXFSZ},
{"SIGWINCH", SIGWINCH},
{NULL, -1},
};

int signal_str2int(const char* sig) {
    if(!sig) {
        return -1;
    }
    if(sig[0] == '\0') {
        return -1;
    }
    #define MAX_SIGNAL_NAME_LENGTH (20)
    size_t i = 0;
    if(!memchr(sig, 0, MAX_SIGNAL_NAME_LENGTH + 1)){
        return -1;
    }
    #undef MAX_SIGNAL_NAME_LENGTH
    while(signal_name_def[i].integer != -1) {
        if(!strcmp(
            signal_name_def[i].string, 
            sig
        )) {
            return signal_name_def[i].integer;
        }
        ++i;
    }
    return -1;
}