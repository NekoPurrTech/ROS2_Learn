#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <memory>

class Node1 : public rclcpp::Node {
public:
    Node1() : Node("node1") {
        // 创建发布者，向node2和node3发送消息
        publisher_to_node2_ = this->create_publisher<std_msgs::msg::String>("node1_to_node2", 10);
        publisher_to_node3_ = this->create_publisher<std_msgs::msg::String>("node1_to_node3", 10);

        // 创建订阅者，接收来自node2和node3的消息
        subscription_from_node2_ = this->create_subscription<std_msgs::msg::String>(
            "node2_to_node1", 10, std::bind(&Node1::callback_from_node2, this, std::placeholders::_1));
        subscription_from_node3_ = this->create_subscription<std_msgs::msg::String>(
            "node3_to_node1", 10, std::bind(&Node1::callback_from_node3, this, std::placeholders::_1));

        // 创建定时器，每秒发送一次消息
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&Node1::timer_callback, this));
    }

private:
    void timer_callback() {
        std_msgs::msg::String msg;
        msg.data = "Hello from Node1";
        publisher_to_node2_->publish(msg);
        publisher_to_node3_->publish(msg);
    }

    void callback_from_node2(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received from Node2: '%s'", msg->data.c_str());
    }

    void callback_from_node3(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received from Node3: '%s'", msg->data.c_str());
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_to_node2_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_to_node3_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_from_node2_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_from_node3_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Node1>());
    rclcpp::shutdown();
    return 0;
}