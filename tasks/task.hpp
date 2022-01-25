#ifndef TASK_MODULE_HPP
#define TASK_MODULE_HPP

#include <vector>

class Task;

class TaskManager
{
    public:
    void addTask(Task*); // tache supprimée si retourne 1
    void executeTasks();
    void erase(Task*);

    protected:
    std::vector<Task*> active_tasks;
};

TaskManager tasks;

#define uint32_t long

class Task
{
    public:
    Task(bool (*function)(void)); // tache supprimée si retourne 1
    Task(bool (*function)(void), uint32_t time); // tache executée dans time ms temps et supprimée ensuite
    Task(bool (*function)(void), uint32_t frequency, uint16_t priority); // tache supprimée si retourne 1, priority: 0=dès que possible 1=toutes les secondes, 2=toutes les minutes, 3=toutes les heures
    ~Task();
    
    void execute();

    private:
    bool (*function)(void) = nullptr;
    uint32_t counter = 0;
    uint32_t time = 0;
    uint32_t frequency = 0;
    uint16_t priority = 0;
};

#include "task.cpp"

#endif