#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

float calculateDistance(float radius)
{
    // const double a = 2.0868157930708398, b = -4.3881898257058580, c = 3.7050037050199380, d = -1.0918760918813372;

    // return ((a * pow(10, 2)) * radius) + ((b * pow(10, 0)) * radius) + ((c * pow(10, -2)) * radius) + ((d * pow(10, -4)) * radius);

    // Langsung copy dari calc arachnoid nyah
    float terms[] = {
        1.4179837576930566e+002,
        -2.0652213774139256e+000,
        1.1648757199107242e-002,
        -2.1895026422167324e-005};

    float t = 1;
    float r = 0;
    for (float c : terms)
    {
        r += c * t;
        t *= radius;
    }
    return r;
}

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
    int y[2] = {15, 165}, u[2] = {59, 168}, v[2] = {0, 50};
    namedWindow("Control");

    createTrackbar("Ymin", "Control", &y[0], 255);
    createTrackbar("Umin", "Control", &u[0], 255);
    createTrackbar("Vmin", "Control", &v[0], 255);

    createTrackbar("Ymax", "Control", &y[1], 255);
    createTrackbar("Umax", "Control", &u[1], 255);
    createTrackbar("Vmax", "Control", &v[1], 255);

    while (true)
    {
        cap >> frame;

        // Convert BGR to yuv
        Mat frame_yuv;
        cvtColor(frame, frame_yuv, COLOR_BGR2YUV);

        Mat frame_thres;
        inRange(frame, Scalar(y[0], u[0], v[0]), Scalar(y[1], u[1], v[1]), frame_thres);

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

            // Avoid devide by 0
            if (m.m00 != 0)
            {
                double mArea = m.m00;
                double mX = m.m10;
                double mY = m.m01;

                Point2f centroid(mX / mArea, mY / mArea);

                Point2f circleLine;
                float radius;

                // Hitung min enclosing circle
                minEnclosingCircle(contours[largestContourAreaI], circleLine, radius);

                // float distance = (200 * 22) / radius;
                float distance = calculateDistance(radius);
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