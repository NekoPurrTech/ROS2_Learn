#include <cinttypes>
#include <memory>
#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using AddTwoInts = example_interfaces::srv::AddTwoInts;

void handle_service(const std::shared_ptr<rmw_request_id_t> request_header,
                    const std::shared_ptr<AddTwoInts::Request> request,
                    const std::shared_ptr<AddTwoInts::Response> response)
{
    (void)request_header;
    RCLCPP_INFO(rclcpp::get_logger("minimal_service"), "request: %" PRId64 " + %" PRId64, request->a, request->b);
    response->sum = request->a + request->b;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("minimal_service");
    auto server = node->create_service<AddTwoInts>("add_two_ints", handle_service);
    RCLCPP_INFO(rclcpp::get_logger("minimal_service"), "Service server ready");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}