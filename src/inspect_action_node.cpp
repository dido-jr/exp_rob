#include <memory>

#include "geometry_msgs/msg/twist.hpp"

#include "plansys2_executor/ActionExecutorClient.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "lifecycle_msgs/msg/state.hpp"

using namespace std::chrono_literals;

class Inspect : public plansys2::ActionExecutorClient
{
public:
  Inspect()
  : plansys2::ActionExecutorClient("patrol", 1s)
  {
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State & previous_state)
  {
    progress_ = 0.0;

    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    cmd_vel_pub_->on_activate();

    return ActionExecutorClient::on_activate(previous_state);
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State & previous_state)
  {
    cmd_vel_pub_->on_deactivate();

    return ActionExecutorClient::on_deactivate(previous_state);
  }

private:
  void do_work()
  {
    if (progress_ < 1.0) {
      progress_ += 0.1;

      send_feedback(progress_, "Patrol running");

      geometry_msgs::msg::Twist cmd;
      cmd.linear.x = 0.0;
      cmd.linear.y = 0.0;
      cmd.linear.z = 0.0;
      cmd.angular.x = 0.0;
      cmd.angular.y = 0.0;
      cmd.angular.z = 0.5;

      cmd_vel_pub_->publish(cmd);
    } else {
      geometry_msgs::msg::Twist cmd;
      cmd.linear.x = 0.0;
      cmd.linear.y = 0.0;
      cmd.linear.z = 0.0;
      cmd.angular.x = 0.0;
      cmd.angular.y = 0.0;
      cmd.angular.z = 0.0;

      cmd_vel_pub_->publish(cmd);

      finish(true, 1.0, "Patrol completed");
    }
  }

  float progress_;

  rclcpp_lifecycle::LifecyclePublisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Inspect>();

  node->set_parameter(rclcpp::Parameter("action_name", "patrol"));
  node->trigger_transition(lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE);

  rclcpp::spin(node->get_node_base_interface());

  rclcpp::shutdown();

  return 0;
}
