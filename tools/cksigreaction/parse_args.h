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

int parse_args(int argc, char** argv, int** signals_type, int* signals_number);

#ifdef __cplusplus
}
#endif
#endif // PARSE_ARGS_H



