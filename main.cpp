//
// Created by afterburner on 18-12-2.
//
#include <opencv2/core/cvstd.hpp>    // for String
#include <opencv2/core/mat.hpp>      // for Mat
#include <opencv2/core/mat.inl.hpp>  // for Mat::Mat, Mat::~Mat, _InputArray...
#include <opencv2/core/types.hpp>    // for Point2i, Scalar
#include <opencv2/core/utility.hpp>  // for CommandLineParser
#include <opencv2/highgui.hpp>       // for imshow, namedWindow, setMouseCal...
#include <opencv2/imgcodecs.hpp>     // for imread, IMREAD_ANYCOLOR
#include <opencv2/imgproc.hpp>       // for circle


int main(int argc, const char *argv[]) {
    constexpr const char *keys = "{help h usage ? |        | Please specify an input image}"
                                 "{@image         |<none>  | the image to be processed}";
    cv::CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        parser.printMessage();
    }
    cv::Mat input_image = cv::imread(parser.get<cv::String>("@image"), cv::IMREAD_ANYCOLOR);
    if (!parser.check()) {
        parser.printErrors();
    }

    cv::String Lena{"Lena"};
    cv::namedWindow(Lena, cv::WINDOW_GUI_EXPANDED);
    const auto mouse_callback = [](const int event, const int x, const int y, const int flags, void *userdata) {
        if (event != cv::EVENT_LBUTTONDOWN) { return; }
        else {
            cv::Mat &img_ = *static_cast<cv::Mat *>(userdata);
            cv::circle(img_, cv::Point2i(x, y), 8, cv::Scalar(155, 100, 30), 2);
        }
    };
    cv::setMouseCallback(Lena, mouse_callback, static_cast<void *>(&input_image));
    while (cv::waitKey(30) != 27) {
        cv::imshow(Lena, input_image);
    }
}
