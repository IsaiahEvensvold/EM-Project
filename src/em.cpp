    #include "em.h"

    #include <iostream>


    std::string em::returnDescription(int returnVal) {

        switch (returnVal) {

        case em::RETURN_CONTRADICTION:
            return "Explicit contradiction.";
            break;

        default:
            return "Return description not found.";
            break;
        }

    }


    void em::exitError(std::string fileName, std::string methodName, std::string description, int returnVal) {

        std::cout << "\n**[CRITICAL ERROR] file: " << fileName << ", method: " << methodName << "\n**Error Description: " << description;
        std::cout << "\n**Exiting with return code: " << returnVal << "  - " << em::returnDescription(returnVal) << "\n\n";
        exit( returnVal );

    }


    void em::notice(std::string message) {
        std::cout << "\n**[NOTE] " << message << std::endl;
    }



    // Setters


    int em::tcodConsoleWidth;
    void em::setTcodConsoleWidth(int w) {

        if (w > em::MAX_TCOD_CONS_WIDTH) {
            em::notice("TCod console width exceeded the maximum and was instead set to the maximum.");
            em::tcodConsoleWidth = em::MAX_TCOD_CONS_WIDTH;
        }
        else if (w < em::MIN_TCOD_CONS_WIDTH) {
            em::notice("TCod console width was less than the minimum and was instead set to the minimum.");
            em::tcodConsoleWidth = em::MIN_TCOD_CONS_WIDTH;
        }
        else {
            em::tcodConsoleWidth = w;
        }

    }

    int em::tcodConsoleHeight;
    void em::setTcodConsoleHeight(int h) {

        if (h > em::MAX_TCOD_CONS_HEIGHT) {
            em::notice("TCod console height exceeded the maximum and was instead set to the maximum.");
            em::tcodConsoleHeight = em::MAX_TCOD_CONS_HEIGHT;
        }
        else if (h < em::MIN_TCOD_CONS_HEIGHT) {
            em::notice("TCod console height was less than the minimum and was instead set to the minimum.");
            em::tcodConsoleHeight = em::MIN_TCOD_CONS_HEIGHT;
        }
        else {
            em::tcodConsoleHeight = h;
        }

    }
