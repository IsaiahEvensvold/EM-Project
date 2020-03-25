    #pragma once
    /*
        -EM-
            Master class for EM-Project, containing many useful and reusable methods.
    */


    #include <string>


    class em {

    protected:
        em();

        static std::string returnDescription(int returnVal);

    public:
        static const int RETURN_CONTRADICTION = -42;

        static void exitError(std::string fileName, std::string methodName, std::string description, int returnVal);

    };
