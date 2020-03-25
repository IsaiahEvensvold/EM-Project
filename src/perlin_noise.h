    #pragma once
    /*
        -PERLIN NOISE-
            Contains functions for generating advanced perlin noise.
    */


    #include <vector>
    #include <time.h>


    class PerlinNoise {

    protected:
        std::vector<int> perm;
        double surflet(double x, double y, int period, double gridX, double gridY);

        std::vector<double> dirsX;
        std::vector<double> dirsY;

        int maxPeriod_m;
        bool periodX_m; // Toggles whether or not x,y will be repeated using a period. Note that they will use the SAME period value.
        bool periodY_m; // These values default to X period->true, and Y period->false.
                        // @FEATURE -- Possible implementation of separate periods for X and Y, might come in handy if I end up using a lot of noise.

    public:
        PerlinNoise(int maxPeriod, int seed = time(NULL), bool periodX = true, bool periodY = false);
        double noise(double x, double y, int period);
        double aNoise(double x, double y, int period, int octaves); // Advanced noise, using octaves and "persistence" (?)

    };
