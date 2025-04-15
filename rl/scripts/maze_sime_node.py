#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import torch
import torch.nn as nn
import numpy as np
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from ament_index_python.packages import get_package_share_directory
import os

class DQN(nn.Module):
    def __init__(self, input_dim, output_dim):
        super(DQN, self).__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, 64),
            nn.ReLU(),
            nn.Linear(64, output_dim)
        )

    def forward(self, x):
        return self.net(x)

class MazeSimNode(Node):
    def __init__(self):
        super().__init__('maze_sim_node')
        self.maze_height, self.maze_width = 8, 15
        self.action_to_delta = {0: (-1, 0), 1: (1, 0), 2: (0, -1), 3: (0, 1)}
        self.maze = np.array([
            [2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0],
            [0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0],
            [0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1],
            [0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0],
            [0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0],
            [0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3],
        ])
        # Load DQN model
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.policy_net = DQN(6, 4).to(self.device)
        model_path = os.path.join(
            get_package_share_directory('rl_maze_sim'), 'trained_dqn_model.pth'
        )
        self.policy_net.load_state_dict(torch.load(model_path, map_location=self.device))
        self.policy_net.eval()
        # Publishers
        self.maze_pub = self.create_publisher(MarkerArray, '/maze', 10)
        self.path_pub = self.create_publisher(Marker, '/path', 10)
        # Timer to run simulation
        self.timer = self.create_timer(0.1, self.run_simulation)
        # Initialize simulation
        self.pos = tuple(np.argwhere(self.maze == 2)[0])
        self.path = [self.pos]
        self.step_count = 0
        self.max_steps = 200
        self.publish_maze()

    def lidar_reading(self, pos):
        x, y = pos
        lidar_dict = {'up': 0, 'down': 0, 'left': 0, 'right': 0}
        for i in range(1, self.maze_height):
            if x - i < 0 or self.maze[x - i, y] == 1:
                lidar_dict['up'] = i - 1
                break
            lidar_dict['up'] = i
        for i in range(1, self.maze_height):
            if x + i >= self.maze_height or self.maze[x + i, y] == 1:
                lidar_dict['down'] = i - 1
                break
            lidar_dict['down'] = i
        for i in range(1, self.maze_width):
            if y - i < 0 or self.maze[x, y - i] == 1:
                lidar_dict['left'] = i - 1
                break
            lidar_dict['left'] = i
        for i in range(1, self.maze_width):
            if y + i >= self.maze_width or self.maze[x, y + i] == 1:
                lidar_dict['right'] = i - 1
                break
            lidar_dict['right'] = i
        return lidar_dict

    def state_from_lidar(self, pos, lidar_dict):
        goal_pos = np.argwhere(self.maze == 3)[0]
        rel_goal_x = (goal_pos[0] - pos[0]) / self.maze_height
        rel_goal_y = (goal_pos[1] - pos[1]) / self.maze_width
        return np.array([
            lidar_dict['up']/self.maze_height,
            lidar_dict['down']/self.maze_height,
            lidar_dict['left']/self.maze_width,
            lidar_dict['right']/self.maze_width,
            rel_goal_x,
            rel_goal_y
        ], dtype=np.float32)

    def step(self, pos, action):
        dx, dy = self.action_to_delta[action]
        new_x, new_y = pos[0] + dx, pos[1] + dy
        if 0 <= new_x < self.maze_height and 0 <= new_y < self.maze_width and self.maze[new_x, new_y] != 1:
            new_pos = (new_x, new_y)
        else:
            new_pos = pos
        done = self.maze[new_pos[0], new_pos[1]] == 3
        return new_pos, done

    def publish_maze(self):
        marker_array = MarkerArray()
        for i in range(self.maze_height):
            for j in range(self.maze_width):
                marker = Marker()
                marker.header.frame_id = "map"
                marker.header.stamp = self.get_clock().now().to_msg()
                marker.ns = "maze"
                marker.id = i * self.maze_width + j
                marker.type = Marker.CUBE
                marker.action = Marker.ADD
                marker.pose.position.x = float(j)
                marker.pose.position.y = float(self.maze_height - i - 1)
                marker.pose.position.z = 0.0
                marker.pose.orientation.w = 1.0
                marker.scale.x = 1.0
                marker.scale.y = 1.0
                marker.scale.z = 0.1
                if self.maze[i, j] == 1:
                    marker.color.r, marker.color.g, marker.color.b = 0.5, 0.5, 0.5
                    marker.color.a = 1.0
                elif self.maze[i, j] == 2:
                    marker.color.r, marker.color.g, marker.color.b = 0.0, 1.0, 0.0
                    marker.color.a = 1.0
                elif self.maze[i, j] == 3:
                    marker.color.r, marker.color.g, marker.color.b = 1.0, 0.0, 0.0
                    marker.color.a = 1.0
                else:
                    marker.color.r, marker.color.g, marker.color.b = 0.0, 0.0, 0.0
                    marker.color.a = 0.2
                marker_array.markers.append(marker)
        self.maze_pub.publish(marker_array)

    def publish_path(self):
        marker = Marker()
        marker.header.frame_id = "map"
        marker.header.stamp = self.get_clock().now().to_msg()
        marker.ns = "path"
        marker.id = 0
        marker.type = Marker.LINE_STRIP
        marker.action = Marker.ADD
        marker.scale.x = 0.1
        marker.color.r, marker.color.g, marker.color.b = 0.0, 0.0, 1.0
        marker.color.a = 1.0
        for pos in self.path:
            point = Point()
            point.x = float(pos[1])
            point.y = float(self.maze_height - pos[0] - 1)
            point.z = 0.1
            marker.points.append(point)
        self.path_pub.publish(marker)

    def run_simulation(self):
        if self.step_count >= self.max_steps or self.maze[self.pos[0], self.pos[1]] == 3:
            self.get_logger().info("Simulation finished")
            self.timer.cancel()
            return
        lidar = self.lidar_reading(self.pos)
        state = self.state_from_lidar(self.pos, lidar)
        state_tensor = torch.tensor(state, dtype=torch.float32).unsqueeze(0).to(self.device)
        with torch.no_grad():
            q_vals = self.policy_net(state_tensor)
            action = torch.argmax(q_vals).item()
        next_pos, done = self.step(self.pos, action)
        self.path.append(next_pos)
        self.pos = next_pos
        self.step_count += 1
        self.publish_path()
        self.get_logger().info(f"Step {self.step_count}: Position {self.pos}")

def main(args=None):
    rclpy.init(args=args)
    node = MazeSimNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()