#ifndef TASK_CPP
#define TASK_CPP

void TaskManager::addTask(Task* newTask)
{
    active_tasks.push_back(newTask);
}

void TaskManager::executeTasks()
{
    for (int i = 0; i < active_tasks.size(); i++)
    {
        active_tasks[i]->execute();
    }
}

void TaskManager::erase(Task* task)
{
    for (int i = 0; active_tasks.size(); i++)
    {
        if (active_tasks[i] == task)
            active_tasks.erase(active_tasks.begin() + i);
    }
}

//---------------------------//

Task::Task(bool (*function)(void))
{
    tasks.addTask(this);
    counter=millis();
}

Task::Task(bool (*function)(void), uint32_t time)
{
    tasks.addTask(this);
    this->time = time + millis();
    counter=millis();
}

Task::Task(bool (*function)(void), uint32_t frequency, uint16_t priority)
{
    tasks.addTask(this);
    this->frequency= frequency;
    this->priority= priority;
    counter=millis();
}

Task::~Task()
{
    tasks.erase(this);
}

void Task::execute()
{
    if (time != 0 && counter + time < millis()) // si time est actif
    {
        function();
        this->~Task();
        return;
    }

    if (frequency != 0 && counter + frequency < millis()) // si frequency est actif
    {
        if (function())
        {
            this->~Task();
            return;
        }
        counter=millis() + frequency;
    }
}

#endif /* TASK_HPP */