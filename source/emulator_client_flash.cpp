#include "emulator_client_flash.h"

Emulator_client<Request_write, Request_read, Request_erase> Emulator_client_flash::_client("emulator_server_flash");

bool Emulator_client_flash::write(char * from, int plane, int block, int page)
{
    Request_write request;

    request.plane = plane;
    request.block = block;
    request.page = page;
    memcpy(request.data, from, 2048);

    _client.send(request);

    auto response = _client.receive<Response_write>();

    return response.result;
}

bool Emulator_client_flash::read(char * to, int plane, int block, int page)
{
    Request_read request;

    request.plane = plane;
    request.block = block;
    request.page = page;

    _client.send(request);

    auto response = _client.receive<Response_read>();

    memcpy(to, response.data, 2048);

    return response.data[0] != 0xFF ? true : false;
}

bool Emulator_client_flash::erase(int plane, int block)
{
    Request_erase request;

    request.plane = plane;
    request.block = block;

    _client.send(request);

    auto response = _client.receive<Response_erase>();

    return response.result;
}