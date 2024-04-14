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
#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdlib.h>

typedef struct signal_description_T {
    char *name;
    int val;
} signal_description_T;
signal_description_T* new_signal_description_T(char *name, int val);
void delete_signal_description_T(signal_description_T** sd_ptr);

typedef struct application_test_conditions_T {
    char *app_name;
    char *app_args;
    int signals_number;
    signal_description_T **signals;
} application_test_conditions_T;
void construct_application_test_conditions_T(
    application_test_conditions_T* atc_ptr);
void destruct_application_test_conditions_T(
    application_test_conditions_T *atc_ptr);

int parse_args(int argc, char** argv, application_test_conditions_T *atc_ptr);

#ifdef __cplusplus
}
#endif
#endif // PARSE_ARGS_H



