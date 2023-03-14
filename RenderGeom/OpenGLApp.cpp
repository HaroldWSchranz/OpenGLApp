// OpenGLApp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Application.h" 

const int windowWidth = 1280;
const int windowHeight = 720;

int main() {

    Application* theApp = new Application("Title", windowWidth, windowHeight);
    if (theApp->startup() == true) {
        while (theApp->update() == true)
            theApp->draw();
        theApp->shutdown();
    }

    delete theApp;
    return 0;
}


