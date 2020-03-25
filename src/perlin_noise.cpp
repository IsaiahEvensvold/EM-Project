    #include "perlin_noise.h"

    #include "em.h"

    #define _USE_MATH_DEFINES
    #include <math.h>

    #include <cmath>
    #include <random>
    #include <algorithm>
    #include <numeric>



    PerlinNoise::PerlinNoise(int maxPeriod, int seed, bool periodX, bool periodY) {
        maxPeriod_m = maxPeriod;
        periodX_m = periodX;
        periodY_m = periodY;

        perm.resize(maxPeriod_m);
        std::iota(perm.begin(), perm.end(), 0);
        std::default_random_engine engine(seed);
        std::shuffle(perm.begin(), perm.end(), engine);
        perm.insert(perm.end(), perm.begin(), perm.end());

        dirsX.resize(maxPeriod_m);
        dirsY.resize(maxPeriod_m);

        for (int i = 0; i < maxPeriod_m; i++)
            dirsX[i] = cos(i * 2.0 * M_PI / maxPeriod_m);

        for (int i = 0; i < maxPeriod_m; i++)
            dirsY[i] = sin(i * 2.0 * M_PI / maxPeriod_m);
    }

    double PerlinNoise::surflet(double x, double y, int period, double gridX, double gridY) {

        double distX = abs(x-gridX);
        double distY = abs(y-gridY);

        double polyX = 1 - (6 * pow(distX, 5)) + (15 * pow(distX, 4)) - (10 * pow(distX, 3));
        double polyY = 1 - (6 * pow(distY, 5)) + (15 * pow(distY, 4)) - (10 * pow(distY, 3));


        /* Formatting grid values for optional periodicism --*/
        int updGridX = (int)gridX;
        int updGridY = (int)gridY;

        if (periodX_m)
            updGridX = updGridX%period;
        if (periodY_m)
            updGridY = updGridY%period;
        /* --IE-- */

        int hashed = perm[perm[updGridX] + updGridY];
        double grad = (x-gridX)*dirsX[hashed] + (y-gridY)*dirsY[hashed];
        return polyX * polyY * grad;
    }

    double PerlinNoise::noise(double x, double y, int period) {
        if (period > maxPeriod_m)
            em::exitError("perlin_noise.cpp", "PerlinNoise::noise", "Period inputted is greater than this noise object's maximum period.", em::RETURN_CONTRADICTION);

        int intX = (int)x;
        int intY = (int)y;

        return (PerlinNoise::surflet(x, y, period, intX+0, intY+0) + PerlinNoise::surflet(x, y, period, intX+1, intY+0) +
                PerlinNoise::surflet(x, y, period, intX+0, intY+1) + PerlinNoise::surflet(x, y, period, intX+1, intY+1) );
    }

    double PerlinNoise::aNoise(double x, double y, int period, int octaves) {
        double val = 0;

        for (int i = 0; i < octaves; i++) {
            double scal = pow(2, i);
            val += pow(0.5, i) * noise(x*scal, y*scal, period*scal);
        }

        return val;
    }
