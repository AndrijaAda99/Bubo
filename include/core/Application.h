#ifndef BUBO_APPLICATION_H
#define BUBO_APPLICATION_H


namespace bubo {

    class Application {

    public:
        Application();
        ~Application();

        void run();
    private:
        static Application* s_appInstance;
    };

}

#endif //BUBO_APPLICATION_H
