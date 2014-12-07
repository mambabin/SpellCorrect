#include "RedisClient.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    RedisClient client("localhost", 6379);
    string key;
    string value;
    while(cin >> key >> value)
    {
        client.setKeyValue(key, value);
    }

    cin.clear();

    while(cin >> key)
    {
        pair<string, bool> ret = client.getValueByKey(key);
        if(ret.second)
        {
            cout << "key : " << key << " value: " << ret.first << endl;
        }
        else
        {
            cout << "key: " << key << " value not exists" << endl;
        }
    }
    return 0;
}