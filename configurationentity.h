/**
 * configurationentity.h
 * Copyright (c) 2018 Linus Boyle <linusboyle@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CONFIGURATIONENTITY_H
#define CONFIGURATIONENTITY_H

#define PIPE_SIZE_MIN 3
#define PIPE_SIZE_MAX 10

class ConfigurationEntity
{
public:
    explicit ConfigurationEntity(int _size,int _input1,int _input2,int _output1,int _output2,int _output3);
    int getSize() const;
    int getInput1Pos() const;
    int getInput2Pos() const;
    int getOutput1Pos() const;
    int getOutput2Pos() const;
    int getOutput3Pos() const;

    bool checkValidity() const;
private:
    int size;
    int input1Pos;
    int input2Pos;
    int output1Pos;
    int output2Pos;
    int output3Pos;
};

#endif // CONFIGURATIONENTITY_H
