//
// Created by Juan Diego on 10/6/24.
//

#include <MainWindow.h>


//==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
MainWindow::MainWindow (juce::String name, juce::ValueTree tree, SPCommandManager& manager, juce::AudioDeviceManager& deviceManager, MainComponent* mainComponent)
            : DocumentWindow (name, juce::Desktop::getInstance().getDefaultLookAndFeel().findColour
                           (ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (mainComponent, true);

    setResizable (true, true);
    centreWithSize (getWidth(), getHeight());
    setFullScreen(true);

    MainWindow::setVisible (true);

    //MELATONIN WINDOW
    // open the inspector window
    inspector.setVisible(this);

    // enable the inspector
    inspector.toggle(this);
}

void MainWindow::closeButtonPressed()
{
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

