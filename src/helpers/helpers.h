//
// Created by Juan Diego on 10/23/24.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace SP_ID
{
    #define DECLARE_ID(name) const juce::Identifier name (#name);

    //names for branches
    DECLARE_ID (MAIN_BRANCH)
    DECLARE_ID (TRACK_BRANCH)
    DECLARE_ID (METRONOME_BRANCH)
    DECLARE_ID (FREEDECK_BRANCH)

    //Unique IDs for Tracks and Clips
    DECLARE_ID (U_ID)
    DECLARE_ID (TRACK)
    DECLARE_ID (CLIP)

    //values

    //metronome
    DECLARE_ID (metronome_grouping)
    DECLARE_ID (metronome_bpm)
    DECLARE_ID (metronome_gain)

    //track
    DECLARE_ID (track_gain)

    //clips
    DECLARE_ID (clip_start_value)
    DECLARE_ID (clip_end_value)
    DECLARE_ID (clip_length_value)
    DECLARE_ID (clip_filepath)
    DECLARE_ID (clip_ready_to_play)

    #undef DECLARE_ID
}

enum SP_CommandID
{
    print = 1,
    show_audio_device_menu,
    record,
    play,
    startOrStopProcessing,
    createNewTrack,
    createNewDummyClip,
};

// helper function to move child components around, I might not need this
// namespace SP
// {
//     static void moveChildComponent(juce::Component* childComponent, juce::Component* oldParent, juce::Component* newParent)
//     {
//         newParent->addAndMakeVisible(childComponent);
//         oldParent->removeChildComponent(childComponent);
//     }
// }


namespace SP
{
    inline void printVT(juce::ValueTree toPrint)
    {
        static const juce::Identifier printTest("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

        toPrint.setProperty(printTest, "x", nullptr);

        DBG(toPrint.getRoot().toXmlString());

        toPrint.removeProperty(printTest, nullptr);
    }

    inline juce::ValueTree createNewID(juce::ValueTree& tree)
    {
        if (! tree.hasProperty(SP_ID::U_ID))
            tree.setProperty(SP_ID::U_ID, juce::Uuid().toString(), nullptr);

        return tree;
    }
}

