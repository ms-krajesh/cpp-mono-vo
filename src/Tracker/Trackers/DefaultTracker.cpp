#include "Tracker/Trackers/DefaultTracker.hpp"

// Create a params object with defaults for given detector.
// Parameters are changed after creation.

DefaultTrackerParams::DefaultTrackerParams()
{
  config_();
}

void DefaultTrackerParams::config_()
{
  win_size_ = cv::Size(21,21);
  term_criteria_ = 
    cv::TermCriteria(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,
        30,
        0.01);
  flags_ = cv::OPTFLOW_LK_GET_MIN_EIGENVALS ;
  min_eig_threshold_ = 0.0001;
}

/*
 * This is the default (reference) implementation of a feature tracker.
 * It uses sparse optical flow to track features into the next frame.
 */

DefaultTracker::DefaultTracker() 
{
  params_ = DefaultTrackerParams();
}

DefaultTracker::DefaultTracker(DefaultTrackerParams params) 
{
  params_ = params;
}

std::vector<Feature> DefaultTracker::track_features(
    const std::vector<Feature> previous_features,
    const cv::Mat previous_image,
    const cv::Mat next_image)
{
  // Use PyrLK optical flow to propagate features

  // 1. Unroll features into array
  std::vector<cv::Point2f> previous_points = unpack_feature_vector_(previous_features);

  // 2. Track
  // TODO: Use subpixel optimization
  std::vector<cv::Point2f> next_points;
  std::vector<uint8_t> status;
  cv::Mat err;

  cv::calcOpticalFlowPyrLK(previous_image,
      next_image,
      previous_points,
      next_points,
      status, 
      err,
      params_.win_size_,
      params_.max_level_,
      params_.term_criteria_,
      params_.flags_,
      params_.min_eig_threshold_);

  // 3. Create new feature vector of features that tracked successfully
  // TODO: TEST THAT THIS PRODUCES THE CORRECT ANSWERS
  std::vector<Feature> out_features;

  for (int i = 0; i < next_points.size(); i++) {
    // If this point passses (check err/status), connect to feature in 
    // previous image
    if (status.at(i) != 0) {
      // This point succeeded
      // TODO: Check that point hasn't left frame (because apparently 
      // that's a thing?
      Feature previous_feature = previous_features.at(i);
      cv::Point2f next_point = next_points.at(i);

      Feature temp_feature(next_point);
      temp_feature.id = previous_feature.id;
      out_features.push_back(temp_feature);
    }
  }

  return out_features;

}

std::vector<cv::Point2f> DefaultTracker::unpack_feature_vector_(std::vector<Feature> features) 
{
  std::vector<cv::Point2f> out_vec;

  for (Feature f : features) {
    // Get pixel coords
    cv::Point2f temp_point = f.raw_coords;

    // Add pixel to back of vector (maintains order)
    out_vec.push_back(temp_point);

  }

  return out_vec;

}