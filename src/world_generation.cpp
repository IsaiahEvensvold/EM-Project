    #include "world_generation.h"

    #include "world.h"
    #include "world_type.h"


    World* WorldGeneration::generateWorld(std::string name, WorldType worldType) {
        World* newWorld = new World();
        newWorld->setName(name);
    }
