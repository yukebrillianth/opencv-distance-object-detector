#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    // VideoCapture cap("/dev/v4l/by-id/usb-Generic_Integrated_Camera_200901010001-video-index0"); // Integrated camera
    VideoCapture cap(0); // Iriun webcam
    if (!cap.isOpened())
    {
        cout << "Unable to access camera!" << endl;
        return -1;
    }

    Mat frame;

    /**
     * @brief Configure Trackbar window
     *
     */
    int y[2] = {0, 79}, y[2] = {24, 111}, v[2] = {0, 20};
    namedWindow("Control");

    createTrackbar("Hmin", "Control", &y[0], 255);
    createTrackbar("Smin", "Control", &y[0], 255);
    createTrackbar("Vmin", "Control", &v[0], 255);

    createTrackbar("Hmax", "Control", &y[1], 255);
    createTrackbar("Smax", "Control", &y[1], 255);
    createTrackbar("Vmax", "Control", &v[1], 255);

    while (true)
    {
        cap >> frame;

        // Convert BGR to yuv
        Mat frame_yuv;
        cvtColor(frame, frame_yuv, COLOR_BGR2YUV);

        Mat frame_thres;
        inRange(frame, Scalar(y[0], y[0], v[0]), Scalar(y[1], y[1], v[1]), frame_thres);

        vector<vector<Point>> contours;
        findContours(frame_thres, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

        if (!contours.empty())
        {
            int largestContourAreaI = 0;
            double largestArea = contourArea(contours[0]);

            // Get largest contour area
            for (size_t i = 0; i < contours.size(); i++)
            {
                double area = contourArea(contours[i]);

                if (area > largestArea)
                {
                    largestArea = area;
                    largestContourAreaI = i;
                }
            }
            Moments m = moments(contours[largestContourAreaI]);
            double mArea = m.m00;
            double mX = m.m10;
            double mY = m.m01;

            Point2f centroid(mX / mArea, mY / mArea);

            Point2f circleLine;
            float radius;

            // Hitung min enclosing circle
            minEnclosingCircle(contours[largestContourAreaI], circleLine, radius);

            float distance = (200 * 22) / radius;
            cout << "Radius: " << radius << endl;

            // gambar enclosing circle
            circle(frame, circleLine, (int)radius, Scalar(0, 255, 255), 2);

            // show info
            string distanceText = "Distance: " + to_string(int(distance)) + " cm";
            string areaText = "Area: " + to_string(int(largestArea));
            putText(frame, distanceText, Point(circleLine.x - radius, circleLine.y - radius - 10),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
            putText(frame, areaText, Point(circleLine.x - radius, circleLine.y - radius - 30),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);

            // Gambar titik tengah
            circle(frame, centroid, 3, Scalar(0, 0, 255), -1);
        }

        // Show thresholded image
        imshow("Threshold", frame_thres);

        // Show original image
        imshow("Camera", frame);

        if (waitKey(1) == 'q')
        {
            break;
        }
    }
    return 0;
}