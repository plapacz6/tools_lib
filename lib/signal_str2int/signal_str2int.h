/*
Copyright 2024-2024 plapacz6@gmail.com

This file is part of signal_str2int.

signal_str2int is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

signal_str2int is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
 with signal_str2int. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SIGNAL_STR2INT
#define SIGNAL_STR2INT
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @brief gives int value of signal from passed string with his name
 * 
 * @param sig string with name of signal
 * @return int val of signal or -1 when error occured (wrong signal name)
 */
int signal_str2int(const char* sig);

#ifdef __cplusplus
}
#endif
#endif //SIGNAL_STR2INT