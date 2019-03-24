#include "emulator_client_flash.h"

constexpr int number_plane = 2;
constexpr int number_block = 64;
constexpr int number_page = 64;
constexpr int size_page = 2048;

char memory[number_plane][number_block][number_plane][size_page];

void handler_write(Request_write * request, Response_write * response)
{
    if (request->plane < number_plane && request->block < number_block && request->page < number_page)
    {
        _d("Writting page @ [%d][%d][%d], data starting with 0x%02X", request->plane, request->block, request->page, request->data[0]);

        memcpy(&memory[request->plane][request->block][request->page][0], request->data, 2048);

        response->result = true;
    }
    else
    {
        _d("Invalid request, make request within Server boundary");
        _d("Plane: 0~%d", number_plane - 1);
        _d("Block: 0~%d", number_block - 1);
        _d("Page: 0~%d", number_page - 1);

        response->result = false;
    }
}

void handler_read(Request_read * request, Response_read * response)
{
    if (request->plane < number_plane && request->block < number_block && request->page < number_page)
    {
        _d("Reading page @ [%d][%d][%d], data starting with 0x%02X", request->plane, request->block, request->page, memory[request->plane][request->block][request->page][0]);

        memcpy(response->data, &memory[request->plane][request->block][request->page][0], 2048);
    }
    else
    {
        _d("Invalid request, make request within Server boundary");
        _d("Plane: 0~%d", number_plane - 1);
        _d("Block: 0~%d", number_block - 1);
        _d("Page: 0~%d", number_page - 1);

        memset(response->data, 0xFF, 2048);
    }
}

void handler_erase(Request_erase * request, Response_erase * response)
{
    if (request->plane < number_plane && request->block < number_block)
    {
        _d("Erasing block @ [%d][%d]", request->plane, request->block);

        for (int i = 0; i < number_page; i++)
        {
            memset(&memory[request->plane][request->block][i][0], 0, 2048);
        }
    }
    else
    {
        _d("Invalid request, make request within current build Server boundary");
        _d("Plane: 0~%d", number_plane - 1);
        _d("Block: 0~%d", number_block - 1);
        _d("Page: 0~%d", number_page - 1);

        response->result = false;
    }
}

int main()
{
    Emulator_server server("emulator_server_flash", handler_write, handler_read, handler_erase);

    server.start();
}