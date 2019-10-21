#include "Estimator.hpp"

Estimator::Estimator()
{
  float t0[3] = {0, 0, 0};
  tvec_ = cv::Mat(3,1,CV_32F, t0);
  float r0[3] = {0,0,0};
  rvec_ = cv::Mat(3,1,CV_32F, r0);
}

Estimator::Estimator(std::shared_ptr<Camera> camera,
    std::shared_ptr<Map> map)
{
  camera_ = camera;
  map_ = map;

  // Set starting location to origin of nav frame
  float t0[3] = {0, 0, 0};
  tvec_ = cv::Mat(3, 1, CV_32F, t0);

  float r0[3] = {0, 0, 0};
  rvec_ = cv::Mat(3, 1, CV_32F, r0);
}

// Deprecated
Estimator::Estimator(Camera camera, Map map)
{
  camera_ = std::make_shared<Camera>(camera.get_intrinsic_params(),
      camera.get_distortion_coeffs(),
      camera.get_size());

  // Set starting location to origin of nav frame
  float t0[3] = {0, 0, 0};
  tvec_ = cv::Mat(3, 1, CV_32F, t0);

  float r0[3] = {0, 0, 0};
  rvec_ = cv::Mat(3, 1, CV_32F, r0);
}
