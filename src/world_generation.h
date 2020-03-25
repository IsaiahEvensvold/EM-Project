    #pragma once
    /*
        -WORLD GENERATION-
            Static class. Handles generation of worlds, interfacing noise functions.
    */

    #include <vector>
    #include <string>


    class World;
    class WorldType;

    class WorldGeneration {

    protected:
        WorldGeneration();

    public:
        static World* generateWorld(std::string name, WorldType worldType);

    };
