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

    /// @brief Average fight value over several interations
    /// @return
    int Combatant::Fight()
    {
        int subTotal = 0;
        srand(time(nullptr));
        for (int i = 0; i < _fightCoefficient; i++)
        {
            subTotal += rand() % _fightCoefficient;
        }
        float Total = subTotal / _fightCoefficient;
        return (int)Total;
    }
}
