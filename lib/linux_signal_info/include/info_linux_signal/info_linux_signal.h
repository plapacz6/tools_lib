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

#ifndef INFO_LINUX_SIGNAL_H
#define INFO_LINUX_SIGNAL_H
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
#endif // INFO_LINUX_SIGNAL_H