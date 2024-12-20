#include <iostream>
#include <Node.hpp>
#include <Asset.hpp>
#include <Player.hpp>
#include <Monster.hpp>
#include <AdventureGameMap.hpp>
#include <Combatant.hpp>


using namespace std;
using namespace chants;

bool isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

int getValidIntegerInput(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear the buffer
            return value;
        }
        else
        {
            cout << "Invalid input. Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void AtNode(Node &viewPort)
{
    cout << "\033[2J\033[1;1H"; // clear screen

    // Output contents of this Node
    cout << "Location: " << viewPort.GetName() + "\n\n";
    cout << viewPort.Description << endl
         << "There are paths here ..." << endl;
    for (Node *node : viewPort.GetConnections())
    {
        cout << node->GetId() << " " << node->GetName() << endl;
    }

    // Show all assets in Node
    for (Asset *asset : viewPort.GetAssets())
    {
        cout << "Asset at this node: " << asset->GetName() << " " << asset->GetMessage() << " " << asset->GetValue() << endl;
    }

    // Show any monsters at this Node
    for (Monster *monster : viewPort.GetMonsters())
    {
        cout << "Monster at this node: " << monster->GetName() << " " << monster->GetHealth() << endl;
    }

    cout << "\n";
}

int FindNode(string loc, vector<Node> *gameMap)
{
    int intLoc = -1;
    if (isNumber(loc))
    {
        intLoc = stoi(loc);
    }
    for (Node node : *gameMap)
    {
        if (node.GetName() == loc || node.GetId() == intLoc)
            return node.GetId();
    }
    return -1;
}

int Battle(Player &player, Monster &monster, vector<Asset> &offensiveAssets)
{
    cout << "You've encountered " << monster.GetName() << "!\n";
    char useAsset = 'n';
    int playerDamage = 0;
    int monsterDamage = 0;

    while (player.GetHealth() > 0 && monster.GetHealth() > 0)
    {
        cout << "Player Health: " << player.GetHealth() << ", Monster Health: " << monster.GetHealth() << "\n";
        playerDamage = player.Fight();  //base damage calculation

        cout << "Do you want to use an offensive asset? (y/n): ";
        cin >> useAsset;
        //player attack phase
        if (tolower(useAsset) == 'y')
        {
            if (!offensiveAssets.empty())
            {
                cout << "You can use one of the following offensive assets:\n";
                for (size_t i = 0; i < offensiveAssets.size(); i++)
                {
                    cout << i + 1 << ": " << offensiveAssets[i].GetName() << "(Damage: " << offensiveAssets[i].GetValue() << ")\n";
                }

                int choice = getValidIntegerInput("Select an offensive asset to use (or 0 to skip): ") - 1;
                if (choice > 0 && choice <= offensiveAssets.size())
                {
                    playerDamage += offensiveAssets[choice].GetValue();
                    cout << "Using " << offensiveAssets[choice].GetName() << " for extra damage.\n";
                    //remove asset (single use)
                    offensiveAssets.erase(offensiveAssets.begin() + choice);
                }
            }
            else
            {
                cout << "No offensive assets available.\n";
            }
        }
         
        monster.ReduceHealth(playerDamage);
        cout << "You attack " << monster.GetName() << " dealing " << playerDamage << " damage.\n" << endl;

        if (monster.GetHealth() <= 0)
        {
            cout << monster.GetName() << " is defeated!\n";
            return 1;  //player wins
        }

        //monster counter-attack phase
        monsterDamage = monster.Fight();
        player.ReduceHealth(monsterDamage);
        cout << monster.GetName() << " hits back, dealing " << monsterDamage << " damage.\n";

        if (player.GetHealth() <= 0)
        {
            cout << "You have been defeated by " << monster.GetName() << "!\n";
            return -1;  //monster wins
        }
    }

    return player.GetHealth();
}

std::string getLastWord(const std::string &str)
{
    // Trim trailing spaces
    std::string trimmed = str;
    trimmed.erase(trimmed.find_last_not_of(' ') + 1);

    // Find the position of the last space
    size_t pos = trimmed.find_last_of(' ');

    // Extract the last word
    if (pos == std::string::npos)
    {
        return trimmed; // No spaces found, return the whole string
    }
    else
    {
        return trimmed.substr(pos + 1);
    }
}

//
// All this game setup will be moved to gamemap and out of the main function
//
int main()
{
    //AdventureGameMap _gameMap;

    //vector<AdventureGameMap> gameMap;

    srand(time(nullptr)); //seed random number generator once
    vector<Node> gameMap;

    // //     // build all nodes

        Node home(0, "Home");
        home.Description = "You are standing in the front yard of a warm and comfortable home that exudes charm and\ntranquility, inviting visitors to feel welcome even before they step inside.\n-------------------";

        Node southCarolina(1, "South Carolina");
        southCarolina.Description = "From the sun-drenched Atlantic beaches to the rolling hills and Blue Ridge foothills, South Carolina blends natural beauty with rich history. Its lush forests, serene lakes, and historic cities like Charleston offer a timeless Southern charm.\n-------------------";

        Node california(2, "California");
        california.Description = "A vibrant state stretches along the Pacific coast, its diverse landscape\nfeaturing everything from sandy beaches to towering redwood forests and bustling cities.\n-------------------";

        Node northCarolina(3, "North Carolina");
        northCarolina.Description = "Rolling hills meet coastal plains in this diverse state, where historic\ncharm blends seamlessly with modern innovation and natural beauty.\n-------------------";

        Node disneyLand(4, "Disneyland");
        disneyLand.Description = "A magical kingdom springs to life with whimsical castles and themed\nlands, where imagination and adventure create an enchanting atmosphere.\n-------------------";

        Node goldenGateBridge(5, "Golden Gate Bridge");
        goldenGateBridge.Description = "An iconic orange bridge spans majestically across the bay, its\ntowers rising through the rolling fog to connect two vibrant shores.\n-------------------";

        Node brooksStadium(6, "Brooks Stadium");
        brooksStadium.Description = "A spirited sports arena rises from the campus grounds, its stands\nechoing with cheers and team pride as athletes compete beneath open skies.\n-------------------";

        Node skyWheel(7, "SkyWheel");
        skyWheel.Description = "A majestic observation wheel turns slowly against the coastal horizon,\nits gleaming pods offering breathtaking views of ocean and cityscape below.\n-------------------";

        Node biltmoreEstate(8, "Biltmore Estate");
        biltmoreEstate.Description = "A grand château nestles in the Blue Ridge Mountains, its gilded\narchitecture and sprawling gardens telling tales of America's Gilded Age.\n-------------------";

        Node wrightBrothersNationalMemorial(9, "Wright Brothers National Memorial");
        wrightBrothersNationalMemorial.Description = "Historic dunes and monuments mark the birthplace of flight, where\nthe spirit of innovation and determination still soars through the air.\n-------------------";

        Node newYork(10, "New York");
        newYork.Description = "A dynamic metropolis pulses with energy, its towering skyscrapers and\ndiverse neighborhoods creating a unique tapestry of urban life.\n-------------------";

        Node statueOfLiberty(11, "Statue of Liberty");
        statueOfLiberty.Description = "A copper-clad sentinel stands proudly in the harbor, torch raised\nhigh as a beacon of freedom and hope for all who approach.\n-------------------";

        Node pennsylvania(12, "Pennsylvania");
        pennsylvania.Description = "Historic streets and rolling countryside paint a picture of American\nheritage, where colonial charm meets modern industry.\n-------------------";

        Node libertyBell(13, "Liberty Bell");
        libertyBell.Description = "An enduring symbol of independence sits silently yet powerful,\nits famous crack a testament to the endurance of liberty.\n-------------------";

        Node hersheysChocolateWorld(14, "Hershey's Chocolate World");
        hersheysChocolateWorld.Description = "A sweet wonderland welcomes visitors with the rich aroma of chocolate,\nits interactive exhibits and tours celebrating the magic of candy-making.\n-------------------";

        Node georgia(15, "Georgia");
        georgia.Description = "Southern hospitality flows through tree-lined streets and modern\ncities, where peach blossoms and historic squares create a welcoming atmosphere.\n-------------------";

        Node centennialOlympicPark(16, "Centennial Olympic Park");
        centennialOlympicPark.Description = "A vibrant urban oasis commemorates Olympic spirit, with dancing\nfountains and gathering spaces bringing the community together.\n-------------------";

        Node worldOfCocaCola(17, "World of Coca-Cola");
        worldOfCocaCola.Description = "A modern tribute to an iconic beverage stands proudly, offering\nvisitors a fascinating journey through the history of refreshment.\n-------------------";

        Node nevada(18, "Nevada");
        nevada.Description = "Desert landscapes stretch endlessly beneath bright stars, while\nglittering cities rise like oases from the sandy expanse.\n-------------------";

        Node hooverDam(19, "Hoover Dam");
        hooverDam.Description = "A monumental feat of engineering curves gracefully between canyon\nwalls, its massive concrete face holding back the mighty Colorado River.\n-------------------";

        Node lasvegasSphere(20, "Las Vegas Sphere");
        lasvegasSphere.Description = "A gleaming orb of light and technology rises from the desert,\nits massive LED surface transforming the nighttime skyline.\n-------------------";

        Node empireStateBuilding(21, "Empire State Building");
        empireStateBuilding.Description = "An iconic skyscraper towers over the city, a symbol of urban ambition and engineering marvel, offering breathtaking views of the skyline.\n-------------------";

        // connect nodes paths
        home.AddConnection(&southCarolina);
        home.AddConnection(&california);

        southCarolina.AddConnection(&home);
        southCarolina.AddConnection(&skyWheel);
        southCarolina.AddConnection(&brooksStadium);
        southCarolina.AddConnection(&northCarolina);
        southCarolina.AddConnection(&california);

        skyWheel.AddConnection(&southCarolina);
        skyWheel.AddConnection(&brooksStadium);

        brooksStadium.AddConnection(&southCarolina);
        brooksStadium.AddConnection(&skyWheel);

        northCarolina.AddConnection(&southCarolina);
        northCarolina.AddConnection(&biltmoreEstate);
        northCarolina.AddConnection(&wrightBrothersNationalMemorial);
        northCarolina.AddConnection(&nevada);
        northCarolina.AddConnection(&newYork);
        northCarolina.AddConnection(&california);

        biltmoreEstate.AddConnection(&northCarolina);
        biltmoreEstate.AddConnection(&wrightBrothersNationalMemorial);

        wrightBrothersNationalMemorial.AddConnection(&biltmoreEstate);
        wrightBrothersNationalMemorial.AddConnection(&northCarolina);

        california.AddConnection(&home);
        california.AddConnection(&southCarolina);
        california.AddConnection(&disneyLand);
        california.AddConnection(&goldenGateBridge);
        california.AddConnection(&northCarolina);

        nevada.AddConnection(&northCarolina);
        nevada.AddConnection(&hooverDam);
        nevada.AddConnection(&lasvegasSphere);
        nevada.AddConnection(&newYork);

        hooverDam.AddConnection(&nevada);
        hooverDam.AddConnection(&lasvegasSphere);

        lasvegasSphere.AddConnection(&nevada);
        lasvegasSphere.AddConnection(&hooverDam);

        newYork.AddConnection(&northCarolina);
        newYork.AddConnection(&statueOfLiberty);
        newYork.AddConnection(&empireStateBuilding);
        newYork.AddConnection(&pennsylvania);
        newYork.AddConnection(&nevada);

        statueOfLiberty.AddConnection(&newYork);
        statueOfLiberty.AddConnection(&empireStateBuilding);

        empireStateBuilding.AddConnection(&newYork);
        empireStateBuilding.AddConnection(&statueOfLiberty);

        pennsylvania.AddConnection(&newYork);
        pennsylvania.AddConnection(&libertyBell);
        pennsylvania.AddConnection(&hersheysChocolateWorld);
        pennsylvania.AddConnection(&georgia);

        libertyBell.AddConnection(&pennsylvania);
        libertyBell.AddConnection(&hersheysChocolateWorld);

        hersheysChocolateWorld.AddConnection(&pennsylvania);
        hersheysChocolateWorld.AddConnection(&libertyBell);

        disneyLand.AddConnection(&california);
        disneyLand.AddConnection(&goldenGateBridge);

        goldenGateBridge.AddConnection(&california);
        goldenGateBridge.AddConnection(&disneyLand);

        georgia.AddConnection(&centennialOlympicPark);
        georgia.AddConnection(&worldOfCocaCola);
        georgia.AddConnection(&pennsylvania);
        georgia.AddConnection(&home); // one way connection to home

        centennialOlympicPark.AddConnection(&georgia);
        centennialOlympicPark.AddConnection(&worldOfCocaCola);

        worldOfCocaCola.AddConnection(&georgia);
        worldOfCocaCola.AddConnection(&centennialOlympicPark);

     // build map in same order as Node Ids above
        gameMap.push_back(home);                           // 0
        gameMap.push_back(southCarolina);                  // 1
        gameMap.push_back(california);                     // 2
        gameMap.push_back(northCarolina);                  // 3
        gameMap.push_back(disneyLand);                     // 4
        gameMap.push_back(goldenGateBridge);               // 5
        gameMap.push_back(brooksStadium);                  // 6
        gameMap.push_back(skyWheel);                       // 7
        gameMap.push_back(biltmoreEstate);                 // 8
        gameMap.push_back(wrightBrothersNationalMemorial); // 9
        gameMap.push_back(newYork);                        // 10
        gameMap.push_back(statueOfLiberty);                // 11
        gameMap.push_back(pennsylvania);                   // 12
        gameMap.push_back(libertyBell);                    // 13
        gameMap.push_back(hersheysChocolateWorld);         // 14
        gameMap.push_back(georgia);                        // 15
        gameMap.push_back(centennialOlympicPark);          // 16
        gameMap.push_back(worldOfCocaCola);                // 17
        gameMap.push_back(nevada);                         // 18
        gameMap.push_back(hooverDam);                      // 19
        gameMap.push_back(lasvegasSphere);                 // 20
        gameMap.push_back(empireStateBuilding);            // 21
    

    // // build assets
    // //
    // These assets are in the form of souvenirs that the player can buy with their points
    Asset magnet("Magnet", "A nice souvenir to put on the fridge at home.", 20, false);
    Asset mug("Mug", "A nice souvenir, you can use it to hold your coffee/tea.", 25, false);
    Asset keychain("Keychain", "A cool souvenir, you can carry a reminder of your trip with you.", 8, false);
    Asset scarf("Scarf", "Nice find! This souvenir is one you can wear for years.", 50, false);
    Asset drinkingwater("Drinking water", "This may keep you from going thirsty.", 80, false);
    Asset picture("Picture", "A great picture to remember this by", 20, false);
    Asset snack("Snack", "A snake is great for when you get hungry", 100, false);
    Asset hammer("Hammer", "this is a good weapon to have when faced with monsters.", 500, true);
    Asset gun("Gun", "Weapon for battling monsters.", 1000, true);
    Asset knife("Knife", "Great for taking down opponents.", 500, true);
    Asset bat("Bat", "Weapon for monsters looking for a beating", 300, true);

    // randomly add assets to nodes
    int numOfNodes = gameMap.size();

    int randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&magnet);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&mug);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&keychain);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&scarf);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&drinkingwater);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&picture);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&snack);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&hammer);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&gun);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&knife);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddAsset(&bat);

    // build monsters
    // randomly add monsters to nodes
    Monster ness("Loch Ness", 5000, 100);
    Monster altie("Altie Sea Monster", 6000, 100);
    Monster whitelady("The Lady in White", 7000, 100);
    Monster squonk("Squonk", 5000, 100);
    Monster lizardman("Lizard Man", 4000, 100);
    Monster wampuscat("Wampus Cat", 5000, 100);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddMonster(&ness);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddMonster(&altie);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddMonster(&whitelady);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddMonster(&squonk);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddMonster(&lizardman);

    randNode = rand() % numOfNodes;
    gameMap[randNode].AddMonster(&wampuscat);

    // get ready to play game below
    Player player("Player", 12500, 100);
    int nodePointer = 0; // start at home
    string input;

    // +++++++++ game loop ++++++++++
    while (true)
    {
        // show current node info
        AtNode(gameMap[nodePointer]);

        cout << "Enter command ('t' to take, 'd' to drop, 'i' to inspect assets; 'a' to attack monsters; or go to node? e(x)it: ";
        getline(cin, input);

        // exit app?
        if (input == "x")
            break;

        int nodeAddr = -1;
        if (isNumber(input))
        {
            nodeAddr = stoi(input);
        }

        bool validConnection = false;
        for (Node *node : gameMap[nodePointer].GetConnections())
        {
            if (node->GetId() == nodeAddr)
            {
                validConnection = true;
            }
        }

        int dir = -1;
        if (validConnection)
        {
            dir = FindNode(input, &gameMap);
        }

        // if player wants to take an asset (t hammer)
        if (input.length() > 1)
        {
            string lastWord = getLastWord(input.substr(2));
            if (input[0] == 't')
            {
                for (auto &asset : gameMap[nodePointer].GetAssets())
                {
                    if (asset->GetName() == lastWord)
                    {
                        player.AddAsset(*asset);
                        gameMap[nodePointer].RemoveAsset(asset);
                        cout << "Taken" << lastWord << "." << endl;
                        break;
                    }
                }
            }
            else if (input[0] == 'a')
            {
                vector<Asset> offensiveAssets = player.GetOffensiveAssets();
                for (auto &asset : player.GetAssets())
                {
                    if (asset.isOffensive())
                    {
                        offensiveAssets.push_back(asset);
                    }
                }
                for (auto &monster : gameMap[nodePointer].GetMonsters())
                {
                    if (monster->GetName() == lastWord)
                    {
                        int result = Battle(player, *monster, offensiveAssets);
                        break;
                    }
                }
            }
            else if (input[0] == 'd')
            {
                Asset* asset = player.RemoveAssetByName(lastWord);
                if (asset)
                {
                    gameMap[nodePointer].AddAsset(asset);
                    cout << "Dropped " << lastWord << "." << endl;
                }
            }
            else if (input[0] == 'i')
            {
                for (auto &asset : gameMap[nodePointer].GetAssets())
                {
                    if (asset->GetName() == lastWord)
                    {
                        cout << "Inspecting " << asset->GetMessage() << endl;
                        break;
                    }
                }
            }

            
        }
        else
        {
            cout << "Dir: " << dir << endl;
            if (dir >= 0)
                nodePointer = dir;
            else
                cout << "Not a valid node address\n";

            cout << endl;

        }


        
    }
    return 0;
}
