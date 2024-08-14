#ifndef COMMANDHELP_H
#define COMMANDHELP_H

enum RETURN_CODE
{
    SUCCESS,
    UNKNOWN_COMMAND,
};

struct ReturnData
{
    std::string data;
    RETURN_CODE status;
};

#endif //COMMANDHELP_H
