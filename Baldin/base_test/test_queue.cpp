#include "queue.h"
#include <gtest.h>

TEST(TQueue, can_create_queue_with_positive_length) {
    ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, cant_create_queue_with_zero_length) {
    ASSERT_ANY_THROW(TQueue<int> q(0));
}

TEST(TQueue, cant_create_queue_with_negative_length) {
    ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_create_queue_with_dynamic_size) {
    ASSERT_NO_THROW(TQueue<int> q);
}

TEST(TQueue, can_push_elements_to_queue_with_fixed_size) {
    TQueue<int> q(3);
    ASSERT_NO_THROW(q.Push(1));
    ASSERT_NO_THROW(q.Push(2));
    ASSERT_NO_THROW(q.Push(3));
}

TEST(TQueue, cant_push_to_full_queue_with_fixed_size) {
    TQueue<int> q(3);
    q.Push(1); q.Push(2); q.Push(3);
    ASSERT_ANY_THROW(q.Push(4));
}

TEST(TQueue, can_pop_elements_from_queue) {
    TQueue<int> q(3);
    q.Push(1); q.Push(2); q.Push(3);
    ASSERT_NO_THROW(q.Pop());
    ASSERT_NO_THROW(q.Pop());
    ASSERT_NO_THROW(q.Pop());
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, cant_pop_from_empty_queue) {
    TQueue<int> q(3);
    ASSERT_ANY_THROW(q.Pop());
}

TEST(TQueue, queue_is_empty_after_creation) {
    TQueue<int> q(3);
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, queue_is_full_after_filling) {
    TQueue<int> q(3);
    q.Push(1); q.Push(2); q.Push(3);
    EXPECT_TRUE(q.IsFull());
}

TEST(TQueue, size_is_correct_after_operations) {
    TQueue<int> q(5);
    EXPECT_EQ(q.Size(), 0);
    q.Push(1);
    EXPECT_EQ(q.Size(), 1);
    q.Push(2);
    EXPECT_EQ(q.Size(), 2);
    q.Pop();
    EXPECT_EQ(q.Size(), 1);
    q.Pop();
    EXPECT_EQ(q.Size(), 0);
}

TEST(TQueue, queue_is_not_copy_constructible) {
    static_assert(!std::is_copy_constructible<TQueue<int>>::value,
        "TQueue should not be copy constructible");
}

TEST(TQueue, queue_is_not_copy_assignable) {
    static_assert(!std::is_copy_assignable<TQueue<int>>::value,
        "TQueue should not be copy assignable");
}

TEST(TQueue, can_push_and_pop_multiple_elements) {
    TQueue<int> q(10);
    for (int i = 0; i < 5; i++) {
        q.Push(i);
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(q.Front(), i);
        q.Pop();
    }
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_handle_interleaved_push_and_pop_operations) {
    TQueue<int> q(5);
    q.Push(1);
    q.Push(2);
    EXPECT_EQ(q.Front(), 1);
    q.Pop();
    q.Push(3);
    EXPECT_EQ(q.Front(), 2);
    q.Pop();
    q.Push(4);
    EXPECT_EQ(q.Front(), 3);
    q.Pop();
    EXPECT_EQ(q.Front(), 4);
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_fill_queue_after_some_pops) {
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);
    q.Pop();
    q.Pop();
    q.Push(3);
    q.Push(4);
    q.Push(5);
    EXPECT_TRUE(q.IsFull());
    EXPECT_EQ(q.Front(), 3);
    q.Pop();
    EXPECT_EQ(q.Front(), 4);
    q.Pop();
    EXPECT_EQ(q.Front(), 5);
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, queue_with_strings) {
    TQueue<std::string> q(3);
    q.Push("first");
    q.Push("second");
    q.Push("third");
    EXPECT_EQ(q.Front(), "first");
    q.Pop();
    EXPECT_EQ(q.Front(), "second");
    q.Pop();
    EXPECT_EQ(q.Front(), "third");
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, queue_with_objects) {
    struct TestStruct {
        int x;
        double y;
    };
    TQueue<TestStruct> q(3);
    TestStruct a = { 1, 1.1 };
    TestStruct b = { 2, 2.2 };
    TestStruct c = { 3, 3.3 };
    q.Push(a);
    q.Push(b);
    q.Push(c);
    EXPECT_EQ(q.Front().x, 1);
    q.Pop();
    EXPECT_EQ(q.Front().x, 2);
    q.Pop();
    EXPECT_EQ(q.Front().x, 3);
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, queue_handles_capacity_changes) {
    TQueue<int> q(2);
    q.Push(1);
    q.Push(2);
    EXPECT_EQ(q.Front(), 1);
    q.Pop();
    q.Push(3);
    EXPECT_EQ(q.Front(), 2);
    q.Pop();
    q.Push(4);
    EXPECT_EQ(q.Front(), 3);
    q.Pop();
    EXPECT_EQ(q.Front(), 4);
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, queue_handles_large_number_of_operations) {
    TQueue<int> q(100);
    for (int i = 0; i < 100; ++i) {
        q.Push(i);
    }
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(q.Front(), i);
        q.Pop();
    }
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, front_does_not_remove_element) {
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Front(), 1); // проверяем, что элемент не удаляется
    q.Pop();
    EXPECT_EQ(q.Front(), 2);
    EXPECT_EQ(q.Front(), 2); // проверяем, что элемент не удаляется
}

TEST(TQueue, front_throws_when_queue_is_empty) {
    TQueue<int> q(3);
    ASSERT_ANY_THROW(q.Front());
}

TEST(TQueue, push_pop_and_front_combined_operations) {
    TQueue<int> q(5);
    q.Push(10);
    q.Push(20);
    q.Push(30);
    EXPECT_EQ(q.Front(), 10);
    q.Pop();
    EXPECT_EQ(q.Front(), 20);
    q.Push(40);
    EXPECT_EQ(q.Front(), 20);
    q.Pop();
    EXPECT_EQ(q.Front(), 30);
    q.Pop();
    EXPECT_EQ(q.Front(), 40);
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, handles_resize_when_empty) {
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Pop();
    q.Pop();
    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
    q.Push(4);
    EXPECT_EQ(q.Front(), 4);
    EXPECT_FALSE(q.IsFull());
}

TEST(TQueue, handles_resize_when_partially_filled) {
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);
    q.Pop();
    q.Push(3);
    q.Push(4);
    EXPECT_EQ(q.Front(), 2);
    q.Pop();
    EXPECT_EQ(q.Front(), 3);
    q.Pop();
    EXPECT_EQ(q.Front(), 4);
}

