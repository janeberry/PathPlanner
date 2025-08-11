/** MAP
 * *A representation of the map (a 2D array, a flatmap, bytes, etc)
 */

#include "path_planner/map.h"
#include <cstdio>
#include <iostream>

//Constructor
Map::Map() : Node("map")
{

  RCLCPP_INFO(this->get_logger(), "Map Node Running"); 
  
  loadFromFile("/home/parallels/dev/project/PathPlanner/src/path_planner/map.pgm");

  origin_.position.x = 0.0;
  origin_.position.y = 0.0;
  origin_.position.z = 0.0;
  origin_.orientation.w = 1.0;

  map_publisher_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10); 
  publishMap();

}

Map::~Map() = default;


bool Map::loadFromFile(const std::string & path)
{
  cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
  if (img.empty()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load map image from %s", path.c_str());
    return false;
  }

  grid_.resize(img.rows, std::vector<int>(img.cols, 0));

  for (int i = 0; i < img.rows; ++i) {
    for (int j = 0; j < img.cols; ++j) {
      int pixel_value = img.at<uchar>(i, j);
      if (pixel_value == 255) {
        grid_[i][j] = 0; // free space
      } else if (pixel_value == 0) {
        grid_[i][j] = 100; // occupied space
      } else {
        grid_[i][j] = -1; // unknown space
      }
    }
  }

  return true;
}
void Map::publishMap()
{
  nav_msgs::msg::OccupancyGrid map_msg;
  map_msg.header.frame_id = "map";
  map_msg.header.stamp = this->now();
  
  map_msg.info.resolution = resolution_;
  map_msg.info.width = grid_[0].size();
  map_msg.info.height = grid_.size();
  
  map_msg.info.origin = origin_;

  map_msg.data.reserve(map_msg.info.width * map_msg.info.height);
  // Fill the data array
  for (const auto& row : grid_) {
    for (const auto& cell : row) {
      map_msg.data.push_back(cell);
    }
  }

  map_publisher_->publish(map_msg);
}





int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Map>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
