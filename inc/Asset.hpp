#pragma once

#include <string>

using namespace std;

namespace chants
{
    class Asset
    {
    private:
        string _name;
        string _message;
        int _value;
        bool _isOffensive;

    public:
        bool hasBeenUsed;
        Asset(string name, string message, int value, bool isOffensive);
        string GetName();
        string GetMessage();
        int GetValue();
        bool isOffensive();
    };
}