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
