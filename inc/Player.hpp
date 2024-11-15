#pragma once

#include <string>
#include <vector>
#include <Asset.hpp>
#include <Combatant.hpp>

using namespace std;

namespace chants
{
    class Player : public Combatant
    {
    private:
        vector<Asset> _assets;

    public:
        Player(string name, int health, int fightCoefficient);
        void AddAsset(Asset asset);
        int GetTotalAssetValue();
    };
}
