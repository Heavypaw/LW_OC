#ifndef NODE_H
#define NODE_H

class Node {
public:
    // Конструктор по умолчанию
    Node() : id(0), pid(0), alive(true), timer_running(false), time(0) {}

    // Конструктор с параметром
    Node(int id);

    // Геттеры
    int get_id() const;
    int get_pid() const;

    // Статус
    bool is_alive() const;
    long long get_time() const;

    // Методы для работы с таймером
    void start_timer();
    void stop_timer();

    // Обновление времени
    void update_time(long long delta_time);  // Объявление метода

private:
    int id;              // ID узла
    int pid;             // PID узла
    bool alive;          // Статус жизни узла
    bool timer_running;  // Статус работы таймера
    long long time;      // Время таймера (например, в секундах)
};

#endif // NODE_H
