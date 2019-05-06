#include <spdlog/spdlog.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/videoio.hpp>

namespace log = spdlog;

int main() {
  log::set_level(log::level::debug);
  log::info("OpenCV Bench starting");

  cv::VideoCapture cap{0};
  if (!cap.isOpened())  // check if succeeded to connect to the camera
    CV_Assert("Cam open failed");

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
  cap.set(cv::CAP_PROP_FPS, 30);

  cv::Mat frame;
  cv::TickMeter tm;

  cap.read(frame);

  for (int i = 0; i < 100; i++) {
    tm.start();
    bool grabbed = cap.read(frame);
    tm.stop();
    if (!grabbed) log::error("frame not grabbed");
  }
  double average_time = tm.getTimeSec() / tm.getCounter();
  log::info("frame size = {} x {}", frame.cols, frame.rows);
  log::info("average time = {}", average_time);
  log::info("Requested FPS = {}", cap.get(cv::CAP_PROP_FPS));
  log::info("Actual FPS = {}", 1.0 / average_time);
}
