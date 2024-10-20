#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
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
    int h[2] = {46, 255}, s[2] = {0, 255}, v[2] = {0, 42};
    namedWindow("Control");

    createTrackbar("Hmin", "Control", &h[0], 255);
    createTrackbar("Smin", "Control", &s[0], 255);
    createTrackbar("Vmin", "Control", &v[0], 255);

    createTrackbar("Hmax", "Control", &h[1], 255);
    createTrackbar("Smax", "Control", &s[1], 255);
    createTrackbar("Vmax", "Control", &v[1], 255);

    while (true)
    {
        cap >> frame;

        // Convert BGR to HSV
        Mat frame_hsv;
        cvtColor(frame, frame_hsv, COLOR_BGR2HSV);

        Mat frame_thres;
        inRange(frame, Scalar(h[0], s[0], v[0]), Scalar(h[1], s[1], v[1]), frame_thres);

        vector<vector<Point>> contours;
        findContours(frame_thres, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++)
        {
            double area = contourArea(contours[i]);

            // Ini tergantung ukuran bendanya ges,
            if (area < 500)
                continue;

            Moments m = moments(contours[i]);
            double mArea = m.m00;
            double mX = m.m10;
            double mY = m.m01;

            Point2f centroid(mX / mArea, mY / mArea);

            Point2f circleLine;
            float radius;

            // Hitung min enclosing circle
            minEnclosingCircle(contours[i], circleLine, radius);

            float distance = (200 * 22) / radius;
            cout << radius << endl;

            // gambar enclosing circle
            circle(frame, circleLine, (int)radius, Scalar(0, 255, 255), 2);

            // show info
            string distanceText = "Distance: " + to_string(int(distance)) + " cm";
            string areaText = "Area: " + to_string(int(area));
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