    #include "perlin_noise.h"

    #define _USE_MATH_DEFINES
    #include <math.h>
    #include <cmath>
    #include <random>
    #include <algorithm>
    #include <numeric>

    #include <iostream>



    PerlinNoise::PerlinNoise(int maxPeriod) {
        perm.resize(maxPeriod);
        std::iota(perm.begin(), perm.end(), 0);
        std::default_random_engine engine(seed);
        std::shuffle(perm.begin(), perm.end(), engine);
        perm.insert(perm.end(), perm.begin(), perm.end());

        dirsX.resize(maxPeriod);
        dirsY.resize(maxPeriod);

        for (int i = 0; i < maxPeriod; i++)
            dirsX[i] = cos(i * 2.0 * M_PI / maxPeriod);

        for (int i = 0; i < maxPeriod; i++)
            dirsY[i] = sin(i * 2.0 * M_PI / maxPeriod);
    }

    double PerlinNoise::surflet(double x, double y, int per, double gridX, double gridY) {

        double distX = abs(x-gridX);
        double distY = abs(y-gridY);

        double polyX = 1 - (6 * pow(distX, 5)) + (15 * pow(distX, 4)) - (10 * pow(distX, 3));
        double polyY = 1 - (6 * pow(distY, 5)) + (15 * pow(distY, 4)) - (10 * pow(distY, 3));

        int hashed = perm[perm[(int)gridX%per] + (int)gridY/*%per*/];
        double grad = (x-gridX)*dirsX[hashed] + (y-gridY)*dirsY[hashed];
        return polyX * polyY * grad;
    }

    double PerlinNoise::noise(double x, double y, int per) {
        int intX = (int)x;
        int intY = (int)y;

        return (PerlinNoise::surflet(x, y, per, intX+0, intY+0) + PerlinNoise::surflet(x, y, per, intX+1, intY+0) +
                PerlinNoise::surflet(x, y, per, intX+0, intY+1) + PerlinNoise::surflet(x, y, per, intX+1, intY+1) );
    }

    double PerlinNoise::noiseO(double x, double y, int per, int octs) {
        double val = 0;

        for (int i = 0; i < octs; i++) {
            double scal = pow(2, i);
            val += pow(0.5, i) * noise(x*scal, y*scal, per*scal);
        }

        return val;
    }


    /*def fBm(x, y, per, octs):
    val = 0
    for o in range(octs):
        val += 0.5**o * noise(x*2**o, y*2**o, per*2**o)
    return val*/

    /*
    import random
    import math
    from PIL import Image

    perm = range(256)
    random.shuffle(perm)
    perm += perm
    dirs = [(math.cos(a * 2.0 * math.pi / 256),
             math.sin(a * 2.0 * math.pi / 256))
             for a in range(256)]

    def noise(x, y, per):
        def surflet(gridX, gridY):
            distX, distY = abs(x-gridX), abs(y-gridY)
            polyX = 1 - 6*distX**5 + 15*distX**4 - 10*distX**3
            polyY = 1 - 6*distY**5 + 15*distY**4 - 10*distY**3
            hashed = perm[perm[int(gridX)%per] + int(gridY)%per]
            grad = (x-gridX)*dirs[hashed][0] + (y-gridY)*dirs[hashed][1]
            return polyX * polyY * grad
        intX, intY = int(x), int(y)
        return (surflet(intX+0, intY+0) + surflet(intX+1, intY+0) +
                surflet(intX+0, intY+1) + surflet(intX+1, intY+1))*/
