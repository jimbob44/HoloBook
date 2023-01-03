/*
 *  HoloBook.h
 *
 *  Copyright 2023 James Smith All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "main.h"

using namespace std;
using namespace zxing;
using namespace zxing::qrcode;
using namespace cv;

// a sample exported function
extern "C" int QRCodeScan(unsigned int maxSize, char *retBuf)
{
    int deviceId = 0;
    int captureWidth = 640;
    int captureHeight = 480;
    bool multi = false;
    int retInt;
    std::string errString;
    std::string resString;
    //errString =  "Capturing from device " + deviceId + "..." + "\n";


    VideoCapture videoCapture(deviceId);

    if (!videoCapture.isOpened()) {

        // Log
        errString = "Open video capture failed on device id: " + std::to_string(deviceId) + "\n";
        return -1;

    }

    if (!videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, captureWidth)) {

        // Log
        errString = "Failed to set frame width: " + std::to_string(captureWidth) + "\n";
    }

    if (!videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, captureHeight)) {

        // Log
        errString = "Failed to set frame height: " + std::to_string(captureHeight) + "\n";
    }

    // The captured image and its grey conversion
    Mat image, grey;

    // Open output window
  //  namedWindow("Qermit(TheFrog)", cv::WINDOW_AUTOSIZE);

    // Stopped flag will be set to -1 from subsequent wayKey() if no key was pressed
    int stopped = -1;




    while (resString.empty() && stopped == -1) {

        // Capture image
        bool result = videoCapture.read(image);

        if (result) {

            // Convert to grayscale
            cvtColor(image, grey, cv::COLOR_BGR2GRAY);

            try {

                // Create luminance  source
                Ref<LuminanceSource> source = MatSource::create(grey);

                // Search for QR code
                Ref<Reader> reader;

                if (multi) {
                    reader.reset(new MultiFormatReader);
                } else {
                    reader.reset(new QRCodeReader);
                }

                Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(source));
                Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
                Ref<Result> result(reader->decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));

                resString = result->getText()->getText();


            } catch (const ReaderException& e) {
             //   cerr << e.what() << " Reader Exception (ignoring)" << endl;
            } catch (const zxing::IllegalArgumentException& e) {
             //   cerr << e.what() << " Illegal Argument Exception (ignoring)" << endl;
            } catch (const zxing::Exception& e) {
             //   cerr << e.what() << " Exception (ignoring)" << endl;
            } catch (const std::exception& e) {
             //   cerr << e.what() << " std exception (ignoring)" << endl;
            }

            // Show captured image
    //        imshow("Qermit(TheFrog)", image);

            // Wait a key for 1 millis
            stopped = waitKey(1);

        } else {

            // Log
            errString = std::string("video capture failed") + "/n";

        }

    }

    if (!errString.empty()){
      //  destroyWindow("Qermit(TheFrog)");
        videoCapture.release();
        return 1;
}
    else{


        if(sizeof(resString.c_str()) < maxSize){
        for(unsigned int b = 0; b < strlen(resString.c_str());b++){
            retBuf[b] = resString.at(b);
        }
            retInt = strlen(resString.c_str());

        }
        else
            retInt = 0;
    //  destroyWindow("Qermit(TheFrog)");
      videoCapture.release();

	return retInt;



    }
}



/* commented out as apart of original windows code. Removed as not necessary for nix based library.

extern "C" __stdcall DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}

*/
