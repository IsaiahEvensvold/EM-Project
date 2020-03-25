    /*  EM-Project
             -Isaiah Evensvold */

    #include <iostream>
    #include <libtcod.hpp>
    #include <cmath>
    #include <vector>

    #include "world.h"
    #include "perlin_noise.h"

    #include <stdlib.h>     /* srand, rand */
    #include <time.h>       /* time */


    void test() {
        int tsize = 30;
        PerlinNoise* pn = new PerlinNoise(256);
        double freq = 0.125;

        for (int i = 0; i < tsize; i++) { //y

            for (int j = 0; j < tsize; j++) { //x
                double tsf = tsize * freq / 2;
                int tsff = tsf;

                double n = pn->noise(j*freq, i*freq, tsff);
                n = floor(n * 100);
                //std::cout << n << " ";
            }
            //std::cout << std::endl;
        }

    }




    /*size, freq, octs, data = 128, 1/32.0, 5, []
    for y in range(size):
        for x in range(size):
            data.append(fBm(x*freq, y*freq, int(size*freq), octs))*/


    std::vector< std::vector< double > > screenTest() {
        int tsize = 256;
        PerlinNoise* pn = new PerlinNoise(256);
        double freq = 1/64.0; //1/64.0
        int octs = 5; //10

        std::vector< std::vector<double> > testVec;
        testVec.resize(tsize);

        for(int i = 0; i < tsize; i++)
            testVec[i].resize(tsize);


        double maxx = 0;
        double minn = 1;
        for (int i = 0; i < tsize; i++) { //y

            for (int j = 0; j < tsize; j++) { //x
                double tsf = tsize * freq;
                int tsff = tsf;

                //double n = pn->noise(j*freq, i*freq, tsff);
                double n = pn->noiseO(j*freq, i*freq, tsff, 5);

                testVec[j][i] = n;

                if (n > maxx)
                    maxx = n;

                if (n < minn)
                    minn = n;

                //std::cout << n << std::endl;
            }
        }

        std::cout << "MAX: " << maxx << std::endl << "MIN" << minn;

        return testVec;
    }


    int main() {

        TCODColor COLORWorldBlue(35,60,100);
        TCODColor COLORWorldGreen(0,100,0);

        TCODColor colWorldBlue = COLORWorldBlue;
        TCODColor colWorldGreen = COLORWorldGreen;

        int testWidth = 256;
        int testHeight = 200;

        test();

        std::vector< std::vector< double > > cVal = screenTest();

        double criticalMagnitude = 0;
        for (int i = 0; i < testHeight; i++) { //y
                for (int j = 0; j < testWidth; j++) { //x

                    if (abs(cVal[j][i]) > criticalMagnitude)
                        criticalMagnitude = abs(cVal[j][i]);

                }
        }

        for (int i = 0; i < testHeight; i++) { //y
                for (int j = 0; j < testWidth; j++) { //x

                    cVal[j][i] += criticalMagnitude;
                    cVal[j][i] /= (2*criticalMagnitude);

                }
        }

        criticalMagnitude *= 2;

        double submergedDepth = 0.35 * criticalMagnitude;
        double landHeight = 0.5 * criticalMagnitude;

        /* initialize random seed: */
        srand (time(NULL));

        /* Initialize the LIBTCOD console */
        TCODConsole::setCustomFont("babyterminal.png");
        TCODConsole::initRoot(testWidth, testHeight, "EM Project", false);


        while ( !TCODConsole::isWindowClosed() ) {
           TCOD_key_t key;
           TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
           switch(key.vk) {
               /*case TCODK_UP : playery--; break;
               case TCODK_DOWN : playery++; break;
               case TCODK_LEFT : playerx--; break;
               case TCODK_RIGHT : playerx++; break;*/
               default:break;
           }

           TCODConsole::root->clear();

           for (int i = 0; i < testWidth; i++) {
            for (int j = 0; j < testHeight; j++) {
                //TCODConsole::root->putChar(i, j, rand() % 40 + 1);

                TCODColor baseColor;

                if (cVal[i][j] < submergedDepth) {
                    baseColor = colWorldBlue;
                }
                else if (cVal[i][j] > landHeight) {
                    baseColor = TCODColor::lerp (colWorldGreen, TCODColor::white, (cVal[i][j]-landHeight)/(criticalMagnitude-landHeight));
                }
                else {
                    baseColor = TCODColor::lerp (colWorldBlue, colWorldGreen, (cVal[i][j]-submergedDepth)/(landHeight-submergedDepth));
                }

                TCODConsole::root->setCharBackground(i, j, baseColor);
            }
           }
           TCODConsole::flush();
        }

        return 0;
    }
