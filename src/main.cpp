#include "QueryServer.h"
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
using namespace muduo;
using namespace muduo::net;

int main(int argc, char const *argv[])
{
    EventLoop loop;
    InetAddress addr("localhost", 9981);
    QueryServer server("../dict/en.dict", 
                       "../dict/zh.dict",
                       "localhost", 6379,
                       &loop,
                       addr);

    server.start();
    loop.loop();

    return 0;
}