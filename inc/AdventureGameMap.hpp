#pragma once

#include <string>
#include <vector>
#include <Node.hpp>

using namespace std;

namespace chants
{
    class AdventureGameMap
    {
    private:
        vector<Node> locations;

        void buildMapNodes();

    public:
        AdventureGameMap();
        vector<Node> GetLocations();
    };
}