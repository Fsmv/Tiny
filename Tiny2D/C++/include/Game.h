namespace Tiny2D {
class Game {
    public:
        Game(const char *title = "Game", int width = 720, int height = 480);
        ~Game();

        void init();
        void start();
        void stop();
    
    private:
        const char *title;
        int width;
        int height;
        int fps = 60;
        int tps = 60;
        bool printFPS = true;
};
}
