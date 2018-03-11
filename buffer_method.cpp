#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	// cap.open("http://192.168.0.112/cam_pic_new.php?x.mjpeg");
	cap.open(0);
	if (!cap.isOpened())
    {
        cout << "Error Opening Stream" << endl;
        return -1;
    }
    while (1)
    {
		Mat frame;
        cap.read(frame);
		cvNamedWindow("Output", CV_WINDOW_NORMAL);
        // imshow("Output",frame);
        
        if (waitKey(30) == 27) 
            break;
    }
    return 0;
}