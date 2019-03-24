#ifndef _emulator_flash_client_h
#define _emulator_flash_client_h

#include "emulator.h"

struct Request_write
{
    char data[2048];
    int plane;
    int block;
    int page;
};

struct Response_write
{
    bool result;
};

struct Request_read
{
    int plane; 
    int block;
    int page;
};

struct Response_read
{
    char data[2048];
};

struct Request_erase
{
    int plane;
    int block;
};

struct Response_erase
{
    bool result;
};

class Emulator_client_flash
{
public:

    static bool write(char * from, int plane, int block, int page);
    static bool read(char * to, int plane, int block, int page);
    static bool erase(int plane, int block);

protected:
    

private:
    static Emulator_client<Request_write, Request_read> _client;

};

#endif