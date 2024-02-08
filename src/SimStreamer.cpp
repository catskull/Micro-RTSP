#include "SimStreamer.h"
#include "JPEGSamples.h"
#include "jpeg-compressor/jpge.h"
#include <fstream> // Include for file I/O
#include <vector>

// Add a static member variable to hold the current instance
static SimStreamer* currentInstance = nullptr;

#ifdef INCLUDE_SIMDATA
SimStreamer::SimStreamer(bool showBig) : CStreamer(400, 240), m_showBig(showBig)
{
    currentInstance = this; // Set the current instance
    image = new unsigned char[width * height * bytesPerPixel];
}

void SimStreamer::streamImage(uint32_t curMsec)
{
    const auto width  = 400;
    const auto height = 240;
    const auto bytesPerPixel = 3;

    // Reuse the image buffer if possible
    if (!image)
        image = new unsigned char[width * height * bytesPerPixel];

    // Pre-calculate values that can be constant in the loop
    const unsigned char colorOffset = colorState % 3;
    const unsigned char colorOffset1 = (colorState + 1) % 3;
    const unsigned char colorOffset2 = (colorState + 2) % 3;

    for (int y = 0; y < height; ++y)
    {
        int yHeight = 255 * y / height;
        for (int x = 0; x < width; ++x)
        {
            int offset = (y * width + x) * bytesPerPixel;
            image[offset + colorOffset] = 255 * x / width;
            image[offset + colorOffset1] = yHeight;
            image[offset + colorOffset2] = 127;
        }
    }

    // Update colorState for the next call
    colorState++;


    jpge::params params;
    params.m_quality = 100;
    params.m_subsampling = jpge::H2V1;

    std::vector<unsigned char> jpegData;
    jpegData.resize(width * height * bytesPerPixel);

    int jpegSize = static_cast<int>(jpegData.size());

    if (jpge::compress_image_to_jpeg_file_in_memory(
        jpegData.data(), jpegSize, width, height, bytesPerPixel, image, params))
    {
        jpegData.resize(jpegSize);
        // Stream the frame
        streamFrame(jpegData.data(), jpegSize, curMsec);

        // // Write JPEG data to file
        // std::ofstream outFile("output.jpg", std::ios::out | std::ios::binary);
        // if (outFile.is_open())
        // {
        //     outFile.write(reinterpret_cast<const char*>(jpegData.data()), jpegSize);
        //     outFile.close();
        // }
    }

    // Clean up
    m_bytes.clear(); // Clear the buffer after streaming
}

void SimStreamer::bufferResult(unsigned char byte)
{
    m_bytes.push_back(byte); // Append the byte to the buffer
}

// Static function that delegates to the instance method
void SimStreamer::staticBufferResult(unsigned char byte)
{
    if (currentInstance)
    {
        currentInstance->bufferResult(byte);
    }
}

#endif
