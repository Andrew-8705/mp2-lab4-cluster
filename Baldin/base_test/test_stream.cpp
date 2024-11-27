#include "Stream.h"
#include "Stream.cpp"
#include <gtest.h>

TEST(stream, can_create_stream_with_valid_intensity) {
    ASSERT_NO_THROW(Stream stream(0.5));
}

TEST(stream, generates_tasks_based_on_intensity) {
    Stream stream(1.0); 
    int generatedTasks = 0;
    for (int i = 0; i < 100; ++i) {
        if (stream.GenerateTask()) {
            ++generatedTasks;
        }
    }

    EXPECT_GT(generatedTasks, 90); 
}

TEST(stream, task_ids_are_unique_and_sequential) {
    Stream stream(1.0);
    Task task1 = stream.GetNextTask();
    Task task2 = stream.GetNextTask();

    EXPECT_EQ(task1.id + 1, task2.id);
}