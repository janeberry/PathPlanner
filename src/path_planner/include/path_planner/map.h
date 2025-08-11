#ifndef PATH_PLANNER_MAP_H
#define PATH_PLANNER_MAP_H

//ros
#include <rclcpp/rclcpp.hpp>

class Map : public rclcpp::Node {
public :
    Map();
    ~Map();

private :
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr map_publisher_;
    
};

#endif // PATH_PLANNER_MAP_H