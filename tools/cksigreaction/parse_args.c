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

#include "parse_args.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

signal_description_T* construct_signal_description_T(char *name, int val) {
    struct signal_description_T* sd = calloc(1, sizeof(signal_description_T));
    if(!sd) {
        return NULL;
    }
    size_t name_length = strlen(name);
    sd->name = calloc(name_length + 1, sizeof(char));
    if(!sd->name) {
        free(sd);
        return NULL;
    }
    strncpy(sd->name, name, name_length);
    sd->val = val;
    return sd;
}
void destruct_signal_description_T(signal_description_T** sd_ptr) {
    if(*sd_ptr) {
        if((*sd_ptr)->name) {
            free((*sd_ptr)->name);
            (*sd_ptr)->name = NULL;
        }
        free(*sd_ptr);
        *sd_ptr = NULL;
    }
}

extern char *optarg;
extern int optind, opterr, optopt;

int parse_args(int argc, char** argv, application_test_conditions_T *atc_ptr) {
    return 0;
}
