#ifndef CONTROLNODE_H
#define CONTROLNODE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>
#include "Node.h"

class ControlNode {
public:
    void create_node(int id, int parent);
    void exec_command(int id, const std::string& subcommand);
    void ping(int id);
    void heartbit(int time);
    void process_command();

private:
    std::unordered_map<int, Node> nodes;
    std::atomic<bool> running{true}; // флаг для работы с heartbit
};

#endif // CONTROLNODE_H
