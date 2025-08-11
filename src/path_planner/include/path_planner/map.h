#ifndef PATH_PLANNER_MAP_H
#define PATH_PLANNER_MAP_H

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <opencv2/opencv.hpp>

class Map : public rclcpp::Node {
public :
    Map();
    ~Map();

    bool loadFromFile(const std::string & path);
    void publishMap();

private :
    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_publisher_;
    std::vector<std::vector<int>> grid_;
    double resolution_ = 0.05;          // meters/cell
    geometry_msgs::msg::Pose origin_;   // map origin in world
};

#endif // PATH_PLANNER_MAP_H