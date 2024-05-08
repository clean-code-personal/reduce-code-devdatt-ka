#include <iostream>
#include "brightener.h"

int main() {
	auto image = std::make_shared<Image>(512, 512);
	std::cout << "Brightening a 512 x 512 image\n";
	ImageBrightener brightener(image);
	int attenuatedCount;
	brightener.BrightenWholeImage(attenuatedCount);
	std::cout << "Attenuated " << attenuatedCount << " pixels\n";
}
