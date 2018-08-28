#include "configurationentity.h"

ConfigurationEntity::ConfigurationEntity(int _size, int _input1, int _input2, int _output1, int _output2, int _output3)
    :size(_size),input1Pos(_input1),input2Pos(_input2),output1Pos(_output1),output2Pos(_output2),output3Pos(_output3)
{
}

int ConfigurationEntity::getSize() const
{
    return size;
}

int ConfigurationEntity::getInput1Pos() const
{
    return input1Pos;
}

int ConfigurationEntity::getInput2Pos() const
{
    return input2Pos;
}

int ConfigurationEntity::getOutput1Pos() const
{
    return output1Pos;
}

int ConfigurationEntity::getOutput2Pos() const
{
    return output2Pos;
}

int ConfigurationEntity::getOutput3Pos() const
{
    return output3Pos;
}

bool ConfigurationEntity::checkValidity() const {
    if (size < PIPE_SIZE_MIN || size > PIPE_SIZE_MAX ){
        return false;
    } else if (input1Pos == input2Pos) {
        return false;
    } else if (input1Pos < 0 || input1Pos >= size || input2Pos < 0 || input2Pos >= size){
        return false;
    } else if (output1Pos == output2Pos || output2Pos == output3Pos || output1Pos == output3Pos){
        return false;
    } else if (output1Pos < 0 || output1Pos >= size || output2Pos < 0 || output2Pos >= size || output3Pos < 0 || output3Pos >= size){
        return false;
    }

    return true;
}
