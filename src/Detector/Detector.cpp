#include "Detector/Detector.hpp"

DetectorParams::DetectorParams()
{
  config_();
}

void DetectorParams::config_()
{

}

Detector::Detector()
{
  params_ = DetectorParams();
}

Detector::Detector(DetectorParams params)
{
  params_ = params;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image)
{
  std::vector<Feature> out;
  return out;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image, 
    const cv::Mat mask)
{
  std::vector<Feature> out;
  return out;

}

DetectorParams Detector::get_params()
{
  return params_;
}
