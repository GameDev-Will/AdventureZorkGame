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
        void RemoveAsset(const Asset& asset);
        Asset* RemoveAssetByName(const string& assetName);
        int GetTotalAssetValue();
        vector<Asset> GetOffensiveAssets();  
        vector<Asset> GetAssets(); 
    };
}
