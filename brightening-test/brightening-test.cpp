#include "CppUnitTest.h"
#include "../brightener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brighteningtest
{
	TEST_CLASS(BrighteningTest)
	{
	public:
		
		TEST_METHOD(BrightensWholeImage)
		{
			auto image = std::make_shared<Image>(2, 2);
			image->pixels[0] = 45; image->pixels[1] = 55;
			image->pixels[2] = 75; image->pixels[3] = 254;

			ImageBrightener brightener(image);
			int attenuatedCount;
			bool result = brightener.BrightenWholeImage(attenuatedCount);
			Assert::IsTrue(result);
			Assert::AreEqual(1, attenuatedCount);
			Assert::AreEqual(100, int(image->pixels[2]));
		}

		TEST_METHOD(BrightensWithAnotherImage)
		{
			auto image = std::make_shared<Image>(2, 2);
			image->pixels[0] = 45; image->pixels[1] = 55;
			image->pixels[2] = 65; image->pixels[3] = 75;
            ImageBrightener brightener(image);
            
            // Test by brightening only the right part
            auto brighteningImage = std::make_shared<Image>(2, 2);
            brighteningImage->pixels[0] = 0; brighteningImage->pixels[1] = 25;
            brighteningImage->pixels[2] = 0; brighteningImage->pixels[3] = 25;

            int attenuatedCount = 0;
            bool succeeded = brightener.AddBrighteningImage(brighteningImage, attenuatedCount);
            Assert::IsTrue(succeeded);
            Assert::AreEqual(45, int(image->pixels[0])); // left-side pixel is unchanged
            Assert::AreEqual(80, int(image->pixels[1])); // right-side pixel is brightened
            Assert::AreEqual(0, attenuatedCount);
		}
	};
}
