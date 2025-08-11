/** MAP
 * *A representation of the map (a 2D array, a flatmap, bytes, etc)
 */

#include "path_planner/map.h"
#include <cstdio>

//Constructor
Map::Map() : Node("map")
{
 RCLCPP_INFO(this->get_logger(), "Map node is starting."); 
 
 map_publisher_ = this->create_publisher<std_msgs::msg::String>("map_topic", 10);
}

Map::~Map() = default;





int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Map>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
