    /************************************************************
    **
    **  EM-Project
    **
    **      designed and programmed by Isaiah Evensvold
    **
    ***********************************************************/


    #include <libtcod.hpp> // LIBTCod Library
    #include "em.h"        // EM master class

    #include <iostream>
    #include <vector>

    #include <cmath>        /* floor */
    #include <stdlib.h>     /* srand, rand */
    #include <time.h>       /* time */

    #include "world.h"
    #include "perlin_noise.h"


    std::vector< std::vector< double > > screenTest() {
        int tsize = 256;
        PerlinNoise* pn = new PerlinNoise(256);
        double freq = 1/64.0; //1/64.0
        int octs = 5; //5

        std::vector< std::vector<double> > testVec;
        testVec.resize(tsize);

        for(int i = 0; i < tsize; i++)
            testVec[i].resize(tsize);

        for (int i = 0; i < tsize; i++) { //y

            for (int j = 0; j < tsize; j++) { //x
                double tsf = tsize * freq;
                int tsff = tsf;

                double n = pn->aNoise(j*freq, i*freq, tsff, octs);

                testVec[j][i] = n;
            }
        }

        return testVec;
    }


    int main() {

        TCODColor COLORWorldBlue(35,60,100);
        TCODColor COLORWorldGreen(0,100,0);

        TCODColor colWorldBlue = COLORWorldBlue;
        TCODColor colWorldGreen = COLORWorldGreen;

        int testWidth = 256;//256
        int testHeight = 200;//200
        em::setTcodConsoleWidth(testWidth);
        em::setTcodConsoleHeight(testHeight);

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

        /* Initialize the LIBTCOD console */
        TCODConsole::setCustomFont("babyterminal.png"); // Set font to smaller tiles, improving the potential map size
        TCODConsole::initRoot(em::getTcodConsoleWidth(), em::getTcodConsoleHeight(), "EM Project", false);


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
