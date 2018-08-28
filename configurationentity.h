#ifndef CONFIGURATIONENTITY_H
#define CONFIGURATIONENTITY_H

#define PIPE_SIZE_MIN 5
#define PIPE_SIZE_MAX 20

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
