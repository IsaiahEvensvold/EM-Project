    #pragma once
    /*
        -WORLD-
            ...
    */


    #include <vector>


    class WorldTile;

    class World {

    protected:

    public:
        World();

        std::vector< std::vector< WorldTile*> > worldTiles;

    };
