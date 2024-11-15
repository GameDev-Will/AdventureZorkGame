#pragma once
#include <string>
using namespace std;

namespace chants
{
    class Combatant
    {
    protected:
        string _name;
        int _health;
        int _fightCoefficient;

    public:
        Combatant(string name, int health, int coefficient);
        int Fight();
        string GetName();
        int GetHealth();
    };
}