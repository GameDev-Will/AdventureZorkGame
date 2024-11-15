#include <Player.hpp>

namespace chants
{

    Player::Player(string name, int health, int fightCoefficient) : Combatant(name, health, fightCoefficient)
    {
    }

    void Player::AddAsset(Asset asset)
    {
        _assets.push_back(asset);
    }

    int Player::GetTotalAssetValue()
    {
        int val = 0;
        for (Asset asset : _assets)
        {
            val += asset.GetValue();
        }
        return val;
    }
}