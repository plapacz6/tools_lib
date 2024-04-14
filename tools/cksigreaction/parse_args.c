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
#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

signal_description_T* new_signal_description_T(char *name, int val) {
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
void delete_signal_description_T(signal_description_T** sd_ptr) {
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

    optind = 0; //reset getopt()

    struct option longopts[] = {
        {"app", required_argument, 0, 'n'},
        {"appargs", required_argument, 0, 'a'},
        {"sigs", required_argument, 0, 's'},
        {0, 0, 0, 0}
    };
    int longindex;
    int c;
    bool important_option_already_readed = false;
    while(!important_option_already_readed) {
        c = getopt_long(argc, argv,
                        "",
                        longopts, &longindex
                       );
        if(-1 == c) {
            break;
        }
        switch (c)
        {
        case 'n':
            size_t appname_length = strlen(optarg);
            atc_ptr->app_name = calloc(appname_length + 1, sizeof(char));
            strncpy(atc_ptr->app_name, optarg, appname_length);
            break;
        case 'a':
            size_t appargs_length = strlen(optarg);

            //calculate all args length (+ 1 space before each)
            int curr_arg_idx = optind;
            while(curr_arg_idx < argc) {
                appargs_length += 1 + strlen(argv[curr_arg_idx]);
                ++curr_arg_idx;
            }
            //allocate place for all args (separated by 1 space)
            atc_ptr->app_args = calloc(appargs_length + 1, sizeof(char));
            if(!atc_ptr->app_args) {
                exit(1);
            }
            curr_arg_idx = optind;
            strcpy(atc_ptr->app_args, optarg); //argv[curr_arg_idx]);
            while(curr_arg_idx < argc) {
                strcat(atc_ptr->app_args, " ");
                strcat(atc_ptr->app_args, argv[curr_arg_idx]);
                ++curr_arg_idx;
            };

            important_option_already_readed = true;
            break;
        case 's':
            size_t signals_list_length = strlen(optarg);
            char *signals_list = calloc(signals_list_length + 1, sizeof(char));
            if(!signals_list) {
                exit(1);
            }
            strncpy(signals_list, optarg, signals_list_length);
            fprintf(stdout, "%s\n", signals_list);

            //counting numer of signals
            char* colon = signals_list;
            while(colon) {
                colon = strchr(colon, ':');
                ++atc_ptr->signals_number;
                if(colon) {
                    //fprintf(stdout, "number: %d: colon: %p char: %c\n", atc_ptr->signals_number, colon, *colon);
                    ++colon;
                }
            }

            //preparing place
            atc_ptr->signals = calloc(atc_ptr->signals_number, sizeof(signal_description_T*));
            if(!atc_ptr->signals) {
                fprintf(stderr, "%s\n", "parse_args: signals: calloc");
                exit(1);
            }

            //writing signals to signal table
            char *sig_begin = signals_list;
            colon = signals_list;
            for(size_t i = 0; i < (size_t)atc_ptr->signals_number; ++i) {
                colon = strchr(colon, ':');
                if(colon) {
                    *colon = '\0';
                }
                atc_ptr->signals[i] = new_signal_description_T(sig_begin, 9);
                printf("%s  %d\n", atc_ptr->signals[i]->name, atc_ptr->signals[i]->val);
                if(colon) {
                    colon++;
                    sig_begin = colon;
                }
            }
            free(signals_list);
            signals_list = NULL;
            break;
        default:
            break;
            //some unknown arguemnts or in wrong orders (app args have to be at the very end)
        }
    }
    if(
        atc_ptr->app_name == NULL ||
        // atc_ptr->app_args == NULL ||
        atc_ptr->signals == NULL ||
        atc_ptr->signals[atc_ptr->signals_number - 1]->name[0] == '\0' ||
        atc_ptr->signals_number == 0
    ) {
        printf("usage:\n%s %s\n",
               argv[0], " --app=name --sigs=SIG1:SIG2:SIG3 [--appargs=-op args]");
        return -1;
    }
    return 0;
}
