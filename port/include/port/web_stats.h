// Web build: frame timing counters for ?stats, kept by vi_frame.cpp and
// web_platform.cpp and printed (then reset) every 300 frames.
#pragma once

struct WebFrameStats
{
    unsigned frames;      // frames presented
    unsigned late;        // presented more than 1.5 periods after the last one
    double maxIntervalMs; // longest gap between presents
    double maxWorkMs;     // longest game frame (present to present, minus the wait)
    double workMs;        // total game time
    unsigned discWaits;   // disc reads that had to wait for the page
    double discWaitMs;
    double audioMs;    // audio mixed while presenting
    double endFrameMs; // aurora_end_frame
    double eventsMs;   // aurora_update (window events)
};

extern WebFrameStats g_webStats;
