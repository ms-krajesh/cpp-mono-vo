#ifndef TRACKER_HPP_INCLUDE
#define TRACKER_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"
#include "Tracker/TrackerParams.hpp"

class Tracker {
  public:
    Tracker();
    Tracker(TrackerParams params);

    std::vector<Feature> track_features(
        const std::vector<Feature> previous_features,
        const cv::Mat previous_image,
        const cv::Mat new_image);
  private:
    // This contains the parameters to pass to the tracking/matching method.
    TrackerParams params_;
};

#endif
