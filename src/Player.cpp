#include <Player.hpp>

namespace chants
{

    Player::Player(string name, int health, int fightCoefficient) : Combatant(name, health, fightCoefficient)
    {
    }

    vector<Asset> Player::GetAssets()
    {
        return _assets;
    }
    void Player::AddAsset(Asset asset)
    {
        _assets.push_back(asset);
    }

     void Player::RemoveAsset(const Asset& asset) {
        // Find the asset in the vector and remove it
        auto it = std::find(_assets.begin(), _assets.end(), asset);
        if (it != _assets.end()) {
            _assets.erase(it);  // Remove the asset from the vector
        }
    }

    Asset* Player::RemoveAssetByName(const string& assetName) {
    for (auto it = _assets.begin(); it != _assets.end(); ++it) {
        if (it->GetName() == assetName) {
            Asset* removedAsset = new Asset(*it);
            _assets.erase(it);
            return removedAsset;
        }
    }
    return nullptr;
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

    vector<Asset> Player::GetOffensiveAssets()
    {
        vector<Asset> offensive;
        for (auto &asset : _assets)
        {
            if (asset.isOffensive() && !asset.hasBeenUsed)
            {
                offensive.push_back(asset);
            }
        }
        return offensive;
    }
}
