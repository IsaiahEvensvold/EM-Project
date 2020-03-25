    /*
        -CLASS NAME-
            Class description...
    */
    #pragma once

    //
    #include <vector>
    #include <time.h>


    class PerlinNoise {
    protected:
        double surflet(double x, double y, int period, double gridX, double gridY);
        std::vector<int> perm;
        int seed = time(NULL);

        std::vector<double> dirsX;
        std::vector<double> dirsY;

    public:
        PerlinNoise(int maxPeriod);
        double noise(double x,double y,int period);
        double noiseO(double x, double y, int period, int octs);

    };
