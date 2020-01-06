#ifndef WINDOW_H
#define WINDOW_H

namespace Render{
    
    class Window{
    public:

        virtual ~Window(){};

        inline int getWidth(){return screenWidth;}
        inline int getHeight(){return screenHeight;}
        inline void setWidth(int width){ screenWidth = width; }
        inline void setHeight(int height){ screenHeight = height; }

        virtual void makeContextCurrent()   = 0;
        virtual bool shouldClose()          = 0;
        virtual void swapBuffers()          = 0;
        virtual void pollEvents()           = 0;
        virtual void close()                = 0;

        virtual void setFrameBufferSizeCallback(void(*)(void*, int, int))     = 0;
        virtual void setMouseCallback(void(*)(void*, double, double))         = 0;
        virtual void setMouseButtonCallback(void(*)(void*, int, int, int))    = 0;
        virtual void setScrollCallback(void(*)(void*, double, double))        = 0;
        virtual void setKeyboardCallback(void (*)(void*, int, int, int, int)) = 0;
        virtual int getKey(int)                                               = 0;

        virtual void terminate() = 0;
        
        static Window *create(void *engine, int width, int height);
    protected:

        int screenWidth;
        int screenHeight;

        void *engine;
    };

}
#endif