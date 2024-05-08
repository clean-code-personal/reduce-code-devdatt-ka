#include "brightener.h"

ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage): m_inputImage(inputImage) {
}

bool ImageBrightener::BrightenWholeImage(int& attenuatedCount) {
    // For brightening, we add a certain grayscale (25) to every pixel.
    // While brightening, some pixels may cross the max brightness. They are
    // called 'attenuated' pixels
    auto dummyimage = std::make_shared<const Image>(m_inputImage->m_rows, m_inputImage->m_columns);
    for (auto pixel = 0; pixel < m_inputImage->m_rows * m_inputImage->m_columns; ++pixel)
        dummyimage->pixels[pixel] = 25;
    return AddBrighteningImage(dummyimage, attenuatedCount);
   
}

bool ImageBrightener::AddBrighteningImage(std::shared_ptr<const Image> imageToAdd, int& attenuatedCount) {
    if (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns) {
        return false;
    }
    attenuatedCount = 0;
    for (int x = 0; x < m_inputImage->m_rows; x++) {
        for (int y = 0; y < m_inputImage->m_columns; y++) {
            int pixelIndex = x * m_inputImage->m_columns + y;
            if (int(m_inputImage->pixels[pixelIndex]) + imageToAdd->pixels[pixelIndex] > 255) {
                ++attenuatedCount;
                m_inputImage->pixels[pixelIndex] = 255;
            } else {
                 m_inputImage->pixels[pixelIndex] += imageToAdd->pixels[pixelIndex];
            }
        }
    }
    return true;
}
