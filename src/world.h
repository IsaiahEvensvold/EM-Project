    #pragma once
    /*
        -WORLD-
            ...
    */


    #include <vector>
    #include <string>


    class WorldTile;

    class World {

    protected:
        std::string name;

    public:
        World();

        std::vector< std::vector< WorldTile*> > worldTiles;

        void setName(std::string name);
        std::string getName() {return name;}

    };
