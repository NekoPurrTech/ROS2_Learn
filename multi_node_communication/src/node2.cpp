#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <memory>

class Node2 : public rclcpp::Node {
public:
    Node2() : Node("node2") {
        // 创建发布者
        publisher_to_node1_ = this->create_publisher<std_msgs::msg::String>("node2_to_node1", 10);
        publisher_to_node3_ = this->create_publisher<std_msgs::msg::String>("node2_to_node3", 10);

        // 创建订阅者
        subscription_from_node1_ = this->create_subscription<std_msgs::msg::String>(
            "node1_to_node2", 10, std::bind(&Node2::callback_from_node1, this, std::placeholders::_1));
        subscription_from_node3_ = this->create_subscription<std_msgs::msg::String>(
            "node3_to_node2", 10, std::bind(&Node2::callback_from_node3, this, std::placeholders::_1));

        // 创建定时器
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&Node2::timer_callback, this));
    }

private:
    void timer_callback() {
        std_msgs::msg::String msg;
        msg.data = "Hello from Node2";
        publisher_to_node1_->publish(msg);
        publisher_to_node3_->publish(msg);
    }

    void callback_from_node1(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received from Node1: '%s'", msg->data.c_str());
    }

    void callback_from_node3(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received from Node3: '%s'", msg->data.c_str());
    }

    // 发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_to_node1_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_to_node3_;

    // 订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_from_node1_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_from_node3_;

    // 定时器
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Node2>());
    rclcpp::shutdown();
    return 0;
}