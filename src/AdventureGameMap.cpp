#include <AdventureGameMap.hpp>

namespace chants
{
    AdventureGameMap::AdventureGameMap()
    {
        buildMapNodes();

        // Possible assets:
        // Flashlight
        // Atomic Map
        // Compass
        // Screwdriver
        // Hammer
        // Polyglot (translator)
        // Treasure
        // Hobgoblin Shield
        // Garden Hose
        // Chest
        // Sign
        // Rabbit Cage
        // Paper Bag
        // Captain’s Chair
        // Purple Haze
        // Drinking Glass
        // Rusty Nail

        // Possible monsters:
        //
    }

    void AdventureGameMap::buildMapNodes()
    {
        // build all nodes
        Node home(0, "Home");
        home.Description = "You are standing in the front yard of a warm and comfortable home that exudes charm and\ntranquility, inviting visitors to feel welcome even before they step inside.\n";

        Node mountain(1, "Mountain");
        mountain.Description = "A majestic mountain rises grandly from the landscape, its towering\npeak piercing the sky and exuding a sense of awe and reverence.\n";

        Node city(2, "City");
        city.Description = "A typical city is a bustling hub of activity, blending diverse elements of\narchitecture, culture, and human interaction. It features a variety of neighborhoods,\neach with its own character, from high-rise apartment buildings and business\ndistricts to residential areas and parks.\n";

        Node ocean(3, "Ocean");
        ocean.Description = "The sea appears restless and chaotic, with surging swells that seem to roil\nand churn, as if the ocean itself is furious, thrashing in a wild, unpredictable rhythm.\n";

        Node island(4, "Island");
        island.Description = "In the midst of an angry sea, the island appears as a defiant outpost,\nbattered but unyielding against the surrounding chaos. Jagged cliffs rise abruptly\nfrom the churning waters, their rugged faces streaked with dark, wet stone, dripping\nwith the constant assault of waves.\n";

        Node hut(5, "Hut");
        hut.Description = "A hut stands as a weathered refuge, small and sturdy against the backdrop of\nthe raging sea. Its wooden walls, gray and splintered from years of exposure to\nsalt and wind, are patched together with whatever materials the island could provide—driftwood,\npalm fronds, and rough-hewn stone.\nThe roof is thatched with dried leaves, lashed tightly\nto withstand the powerful gusts that whip across the island.\n";

        Node quicksand(6, "Quick Sand");
        quicksand.Description = "A patch of treacherous quicksand lurks, deceptively blending into the surrounding\nterrain. It lies at the edge of a narrow clearing, where the ground transitions\nfrom rocky soil to a stretch of damp, silty earth.\n";

        Node cave(7, "Cave");
        cave.Description = "Here is a cave nestled into the rocky cliffs that rise above the angry sea, is a cave that\nseems carved by nature's fury over centuries. Its entrance is half-hidden by\nthick vines and jagged boulders, giving it an air of mystery and shelter.\nThe mouth of the cave is wide and low, just tall enough\nfor a person to crouch and enter, and it faces away from\nthe wind, offering some protection from the relentless storm.\n";

        Node beach(8, "Beach");
        beach.Description = "A beautiful beach stretches out in a graceful curve, bordered by soft, powdery sand that\ngleams white under the sunlight. Each grain feels fine and smooth beneath bare\nfeet, as though sculpted by the gentle hands of time and tide. The shoreline\nis kissed by the crystal-clear waters of the ocean,\nwhere the surf laps quietly and rhythmically, creating a soft,\nsoothing sound with each wave.\n";

        // connect nodes paths
        home.AddConnection(&mountain);
        home.AddConnection(&city);

        mountain.AddConnection(&home);
        mountain.AddConnection(&ocean);
        mountain.AddConnection(&city);

        ocean.AddConnection(&mountain);
        ocean.AddConnection(&city);
        ocean.AddConnection(&island);

        city.AddConnection(&home);
        city.AddConnection(&mountain);
        city.AddConnection(&ocean);

        island.AddConnection(&ocean);
        island.AddConnection(&cave);
        island.AddConnection(&beach);
        island.AddConnection(&quicksand);
        island.AddConnection(&hut);

        cave.AddConnection(&home); // one way connection
        cave.AddConnection(&beach);
        cave.AddConnection(&island);

        beach.AddConnection(&cave);
        beach.AddConnection(&island);

        hut.AddConnection(&island);
        hut.AddConnection(&quicksand);

        quicksand.AddConnection(&hut);
        quicksand.AddConnection(&island);

        // build map in same order as Node Ids above.
        // The index of each node in the vector must match it's id.
        locations.push_back(home);
        locations.push_back(mountain);
        locations.push_back(city);
        locations.push_back(ocean);
        locations.push_back(island);
        locations.push_back(hut);
        locations.push_back(quicksand);
        locations.push_back(cave);
        locations.push_back(beach);
        }

    vector<Node> AdventureGameMap::GetLocations()
    {
        return locations;
    }

}