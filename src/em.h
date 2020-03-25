    #pragma once
    /*
        -EM-
            Master class for EM-Project, containing many useful and reusable methods.
            Static class.
    */


    #include <string>


    class em {

    protected:
        em();

        // TCOD Console
        static int tcodConsoleWidth;
        static int tcodConsoleHeight;

        //Private Constants
        static const int MAX_TCOD_CONS_WIDTH = 400;
        static const int MAX_TCOD_CONS_HEIGHT = 256;
        static const int MIN_TCOD_CONS_WIDTH = 10;
        static const int MIN_TCOD_CONS_HEIGHT = 10;

        // Etc.
        static std::string returnDescription(int returnVal);

    public:
        // Public Constants
        static const int RETURN_CONTRADICTION = -42;

        // Terminal
        static void exitError(std::string fileName, std::string methodName, std::string description, int returnVal);
        static void notice(std::string message);

        // Getters/Setters
        static void setTcodConsoleWidth(int width);
        static int getTcodConsoleWidth() {return tcodConsoleWidth;}

        static void setTcodConsoleHeight(int height);
        static int getTcodConsoleHeight() {return tcodConsoleHeight;}

    };
