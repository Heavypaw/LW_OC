#include "ControlNode.h"
#include "Node.h"
#include <unordered_map>

void ControlNode::create_node(int id, int other_param) {
    // Создаем новый узел с использованием конструктора Node(int id)
    Node new_node(id);

    // Присваиваем созданный узел в map. Здесь важно, чтобы у Node был корректно реализован оператор копирования
    nodes[id] = new_node;
}

void ControlNode::exec_command(int id, const std::string& subcommand) {
    if (nodes.find(id) == nodes.end()) {
        std::cout << "Error:" << id << ": Not found" << std::endl;
        return;
    }

    Node& node = nodes[id];
    
    if (subcommand == "start") {
        node.start_timer();
        std::cout << "Ok:" << id << std::endl;
    } else if (subcommand == "stop") {
        node.stop_timer();
        std::cout << "Ok:" << id << std::endl;
    } else if (subcommand == "time") {
        std::cout << "Ok:" << id << ": " << node.get_time() << std::endl;
    } else {
        std::cout << "Error:" << id << ": [Custom error]" << std::endl;
    }
}

void ControlNode::ping(int id) {
    if (nodes.find(id) != nodes.end()) {
        std::cout << "Ok: 1" << std::endl; // Узел доступен
    } else {
        std::cout << "Ok: 0" << std::endl; // Узел недоступен
    }
}

void ControlNode::heartbit(int time) {
    std::thread([this, time]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(time));

            for (auto& pair : nodes) {
                Node& node = pair.second;
                if (!node.is_alive()) {
                    std::cout << "Heartbit: node " << node.get_id() << " is unavailable now" << std::endl;
                }
            }
        }
    }).detach();

    std::cout << "Ok" << std::endl;
}

void ControlNode::process_command() {
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::istringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "create") {
            int id, parent;
            ss >> id >> parent;
            create_node(id, parent);
        } else if (command == "exec") {
            int id;
            std::string subcommand;
            ss >> id >> subcommand;
            exec_command(id, subcommand);
        } else if (command == "ping") {
            int id;
            ss >> id;
            ping(id);
        } else if (command == "heartbit") {
            int time;
            ss >> time;
            heartbit(time);
        } else if (command == "exit") {
            std::cout << "Exiting program." << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}
