//
// Created by Juan Diego on 12/30/24.
//
#pragma once
#include <DeckGUI.h>

/*TODO:
 *use Viewport to implement scrolling on these components
 *
 *
 */


class MixDeckTrack final : public juce::Component,
                           public DeckGUI,
                           public juce::SliderListener<juce::Slider>
{
public:
    MixDeckTrack(int width, int height, juce::ValueTree& n): DeckGUI(width, height, juce::Colour::fromRGB(144, 144, 144)), node(n)
    {
        setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        slider.setBounds(getLocalBounds().reduced(5));
        slider.setRange(0.0, 2.0, 0.1);
        slider.setValue(initialGain);
        slider.addListener(this);

        setUpValueTree();
    }

    ~MixDeckTrack()
    {
    }

    void setUpValueTree()
    {
        node.setProperty(SP_ID::track_gain, initialGain, nullptr);
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(BACKGROUND_COLOUR);
        g.drawRect(this->getLocalBounds(), BORDER_WIDTH - 1);
    }

    void resized() override
    {
        slider.setBounds(getLocalBounds().reduced(5));
    }

    //Slider Listener

    void sliderValueChanged(juce::Slider* slider) override
    {
        node.setProperty(SP_ID::track_gain, slider->getValue(), nullptr);
    }

private:
    float initialGain = 1;

    juce::Slider slider;

    juce::ValueTree node;
};

class MixDeckGUI final : public juce::Component,
                         public DeckGUI
{
public:
    explicit MixDeckGUI(const juce::ValueTree& v)
        : DeckGUI(200, 200, juce::Colour::fromRGB(60, 60, 60)), valueTree(v)
    {
        setSize(WINDOW_WIDTH, WINDOW_WIDTH);
        //addAndMakeVisible(resizableEdge);
        //resizableEdge.setAlwaysOnTop(true);
        setUpGrid(TRACK_WIDTH);
    }

    ~MixDeckGUI()
    {
    }

    void addTrack(juce::ValueTree& newNode)
    {
        auto* track = new MixDeckTrack(TRACK_WIDTH, TRACK_WIDTH, newNode);
        grid.items.add(track);
        addAndMakeVisible(track);
    }

    void setUpGrid(const int width)
    {
        using Track = juce::Grid::TrackInfo;
        grid.rowGap = juce::Grid::Px(0);
        grid.columnGap = juce::Grid::Px(0);

        grid.templateRows = {Track(juce::Grid::Px(TRACK_HEIGHT))};

        grid.templateColumns = {Track(juce::Grid::Px(width))};

        grid.autoColumns = Track(juce::Grid::Px(TRACK_WIDTH));
        grid.autoRows = Track(juce::Grid::Px(TRACK_HEIGHT));

        //grid.justifyContent = juce::Grid::JustifyContent::stretch; //technically not necessary?
        grid.autoFlow = juce::Grid::AutoFlow::row;
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(BACKGROUND_COLOUR);
        g.drawRect(this->getLocalBounds(), BORDER_WIDTH);
        if (getNumChildComponents() != 0)
            grid.performLayout(getLocalBounds());
    }

    void resized() override
    {
        const auto rect = getLocalBounds();
        //resizableEdge.setBounds(rect.getX() + rect.getWidth() - RESIZABLE_EDGE, rect.getY(), RESIZABLE_EDGE,rect.getHeight());

        setUpGrid(rect.getWidth());
    }

private:
    juce::Grid grid;

    //juce::ResizableEdgeComponent resizableEdge{this, nullptr, juce::ResizableEdgeComponent::Edge::rightEdge};

    //juce::OwnedArray<MixDeckTrack> mixDeckTracks;

    juce::ValueTree valueTree;

    int TRACK_WIDTH = 200;
    int TRACK_HEIGHT = 100;
};



