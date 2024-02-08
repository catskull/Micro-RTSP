#pragma once

#include "JPEGSamples.h"
#include "CStreamer.h"
#include "toojpeg/toojpeg.h"
#include <vector>

#ifdef INCLUDE_SIMDATA
class SimStreamer : public CStreamer
{
    bool m_showBig;
    int colorState;
    std::vector<unsigned char> m_bytes; // Buffer for storing JPEG data

public:
    SimStreamer(bool showBig);
    virtual void streamImage(uint32_t curMsec);
    void bufferResult(unsigned char byte);

    // Static method to handle JPEG output
    static void staticBufferResult(unsigned char byte);
};
#endif
