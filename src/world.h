    /*
        -WORLD-
            ...
    */
    #pragma once

    //
    #include <vector>


    class WorldTile;

    class World {
    protected:

    public:
        World(); //Constructor

        std::vector< WorldTile* > worldTiles;

    };
