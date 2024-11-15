#pragma once

#include <vector>
#include <string>
#include <Asset.hpp>
#include <Monster.hpp>

using namespace std;

namespace chants
{

    class Node
    {
    private:
        int _id;
        string _name;
        vector<Node *> _connections;
        vector<Asset *> _assets;
        vector<Monster *> _monsters;

    public:
        string Description;

        Node(int id, string name);
        int GetId();
        void SetId(int id);
        string GetName();
        void AddConnection(Node *conn);
        vector<Node *> GetConnections();
        Node *GetAConnection(int connId);

        void AddAsset(Asset *asset);
        vector<Asset *> GetAssets();

        void AddMonster(Monster *monster);
        vector<Monster *> GetMonsters();

        bool operator==(const Node &rhs) const;
    };
}