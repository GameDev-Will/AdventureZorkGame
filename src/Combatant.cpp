#include <Combatant.hpp>
#include <time.h>
using namespace std;

namespace chants
{
    Combatant::Combatant(string name, int health, int fightCoefficient)
    {
        _name = name;
        _health = health;
        _fightCoefficient = fightCoefficient;
    }

    string Combatant::GetName()
    {
        return _name;
    }

    int Combatant::GetHealth()
    {
        return _health;
    }

     void Combatant::ReduceHealth(int damage)
    {
        _health -= damage;
        if (_health < 0)
        {
            _health = 0;     //ensuring health does not go below zero
        }
    }

    /// @brief Average fight value over several interations
    /// @return
    int Combatant::Fight()
    {
        int baseDamage = 100;  //Base damage ensures each attack has a minimum impact
        int variableDamage = rand() % (_fightCoefficient + 1); //adds up to fightCoefficient
        return baseDamage + variableDamage;
    }

    
}
