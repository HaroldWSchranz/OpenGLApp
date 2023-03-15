// OpenGLApp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Application3D.h" 

const float fraction = 0.95;
const int windowWidth = 1920 * fraction;  //= 1280;
const int windowHeight = 1080 * fraction; // = 720;


int main() {

    //harry::Application* theApp = new harry::Application("Title", windowWidth, windowHeight);

    auto theApp = new Application3D("OpenGLApp: RenderingModels", windowWidth, windowHeight);
    if (theApp->startup() == true) {
        while (theApp->update(0.0) == true)
            theApp->draw();
        theApp->shutdown();
    }

    delete theApp;
    return 0;
}


