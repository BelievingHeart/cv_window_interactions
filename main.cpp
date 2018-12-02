//
// Created by afterburner on 18-12-2.
//
#include <jmorecfg.h>                    // for boolean
#include <opencv2/core/cvstd.hpp>        // for String
#include <opencv2/core/hal/interface.h>  // for CV_8U
#include <opencv2/core/mat.hpp>          // for Mat
#include <opencv2/core/mat.inl.hpp>      // for Mat::operator=, _InputArray:...
#include <opencv2/core/types.hpp>        // for Point2i, Scalar, Size
#include <opencv2/core/utility.hpp>      // for CommandLineParser
#include <opencv2/highgui.hpp>           // for createButton, imshow, create...
#include <opencv2/imgcodecs.hpp>         // for imread, IMREAD_ANYCOLOR
#include <opencv2/imgproc.hpp>           // for Sobel, blur, circle, cvtColor
#include <vector>                        // for vector


cv::Mat draft;
cv::Mat input_image;
boolean to_color = 1;
boolean to_gray = 0;
boolean clear_points = 0;
boolean sobel_on = 0;
int blur_size = 0;
std::vector<cv::Point2i> pts;
cv::String Lena{"Lena"};


//    overall change function
void apply_changes(){
    if(to_gray != 0){
        cv::cvtColor(input_image, draft, cv::COLOR_BGR2GRAY);
    }else{
        draft = input_image.clone();
    }
    if(blur_size != 0){
        cv::blur(draft, draft, cv::Size(blur_size, blur_size));
    }
    if(sobel_on != 0){
        cv::Sobel(draft, draft, CV_8U, 1, 1);
    }
    if(clear_points != 0){
        pts.clear();
    }else{
        for(auto& pt : pts){
            cv::circle(draft, pt, 8, cv::Scalar(155, 100, 30), 2);
        }
    }
    cv::imshow(Lena, draft);
};

int main(int argc, const char *argv[]) {
    constexpr const char *keys = "{help h usage ? |        | Please specify an input image}"
                                 "{@image         |<none>  | the image to be processed}";
    cv::CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        parser.printMessage();
    }
    input_image = cv::imread(parser.get<cv::String>("@image"), cv::IMREAD_ANYCOLOR);
    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    cv::namedWindow(Lena, cv::WINDOW_GUI_EXPANDED);
    cv::displayOverlay(Lena, "overlay 5 secs", 5000);

// set mouse callback Black
    const auto mouse_callback = [](const int event, const int x, const int y, const int flags, void *userdata) {
        if (event != cv::EVENT_LBUTTONDOWN) { return; }
        pts.emplace_back(x, y);
        apply_changes();
    };
    cv::setMouseCallback(Lena, mouse_callback, static_cast<void *>(&input_image));

//    set trackbar
    const auto on_change = [](const int pos, void *userdata) {
        if (pos != 0) {
            blur_size = pos;
            apply_changes();
        }
    };

    int _ = 3;
    cv::createTrackbar("Blur size", Lena, &_, 11, on_change, static_cast<void *>(&input_image));

//    create buttons
    const auto color_button = [](int state, void *userdata){
        to_color = state;
    };
    cv::createButton("color", color_button, nullptr, cv::QT_RADIOBOX, true);

    const auto gray_button = [](int state, void *userdata){
        to_gray = state;
        apply_changes();
    };
    cv::createButton("gray", gray_button, nullptr, cv::QT_RADIOBOX, false);

   const auto sobel_button = [](int state, void *userdata){
        sobel_on = state;
        apply_changes();
    };
    cv::createButton("sobel", sobel_button, nullptr, cv::QT_CHECKBOX, false);

    const auto clear_button = [](int state, void *userdata){
        clear_points = state;
        apply_changes();
    };
    cv::createButton("clear_points", clear_button, &clear_points, cv::QT_CHECKBOX, false);

    draft = input_image;
    cv::imshow(Lena, draft);
    cv::waitKey(0);
}
