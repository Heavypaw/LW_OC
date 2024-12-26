#include "Node.h"
#include <cstdlib>  // Для rand()
#include <iostream> // Для вывода в консоль (если нужно для отладки)

// Конструктор
Node::Node(int id) : id(id), pid(rand()), alive(true), timer_running(false), time(0) {
    // Здесь мы генерируем случайный pid для узла и инициализируем другие поля
    std::cout << "Node created with ID: " << id << " and PID: " << pid << std::endl;
}

// Геттер для ID
int Node::get_id() const {
    return id;
}

// Геттер для PID
int Node::get_pid() const {
    return pid;
}

// Проверка, жив ли узел
bool Node::is_alive() const {
    return alive;
}

// Получение времени таймера
long long Node::get_time() const {
    return time;
}

// Начало работы таймера
void Node::start_timer() {
    if (!timer_running) {
        timer_running = true;
        time = 0;  // Инициализируем время на 0 при запуске таймера
        std::cout << "Timer started for Node " << id << std::endl;
    }
}

// Остановка таймера
void Node::stop_timer() {
    if (timer_running) {
        timer_running = false;
        std::cout << "Timer stopped for Node " << id << ". Time: " << time << " seconds." << std::endl;
    }
}

// Для примера, можно обновить время, если таймер работает
void Node::update_time(long long delta_time) {
    if (timer_running) {
        time += delta_time;  // Увеличиваем время на delta_time (например, в секундах)
    }
}
