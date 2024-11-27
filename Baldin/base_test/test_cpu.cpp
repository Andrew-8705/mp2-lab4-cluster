#include "CPU.h"
#include "CPU.cpp"
#include "queue.h"
#include <gtest.h>

TEST(cpu, can_create_cpu) {
    ASSERT_NO_THROW(CPU cpu);
}

TEST(cpu, cpu_starts_idle) {
    CPU cpu;
    EXPECT_FALSE(cpu.IsBusy());
}

TEST(cpu, cpu_processes_tasks) {
    CPU cpu;
    TQueue<Task> queue(10);
    queue.Push(Task(1, 5));
    queue.Push(Task(2, 3));

    int downtime_ticks = 0;
    for (int i = 0; i < 15; ++i) {
        cpu.process(queue, downtime_ticks);
    }

    EXPECT_EQ(downtime_ticks, 5); 
    EXPECT_EQ(cpu.GetCurrentTaskId(), -1); // так как всё выполнится
}

TEST(cpu, cpu_goes_idle_after_completing_tasks) {
    CPU cpu;
    TQueue<Task> queue(10);
    queue.Push(Task(1, 5));

    int downtime_ticks = 0;
    for (int i = 0; i < 10; ++i) {
        cpu.process(queue, downtime_ticks);
    }

    EXPECT_FALSE(cpu.IsBusy()); 
    EXPECT_EQ(downtime_ticks, 4); 
}