#include "Cluster.h"
#include "Cluster.cpp"
#include <gtest.h>

TEST(cluster, throws_when_queue_size_is_zero_or_negative) {
    EXPECT_ANY_THROW(Cluster cluster(0, 0.5)); 
    EXPECT_ANY_THROW(Cluster cluster(-5, 0.5));
}

TEST(cluster, throws_when_task_intensity_is_out_of_range) {
    ASSERT_THROW(Cluster cluster(10, -0.1), invalid_argument);
    ASSERT_THROW(Cluster cluster(10, 1.1), invalid_argument);
}

TEST(cluster, throws_when_running_simulation_with_non_positive_ticks) {
    Cluster cluster(10, 0.5);
    ASSERT_THROW(cluster.RunSimulation(0), invalid_argument);
    ASSERT_THROW(cluster.RunSimulation(-5), invalid_argument);
}

TEST(cluster, can_create_cluster_with_valid_parameters) {
    ASSERT_NO_THROW(Cluster cluster(10, 0.5));
}

TEST(cluster, simulation_runs_and_updates_statistics) {
    Cluster cluster(10, 0.5);
    cluster.RunSimulation(100);
    SimulationStatistics stats = cluster.GetStatistics();

    EXPECT_GT(stats.total_tasks, 0); // предполагаетс€ что какие-то задани€ будут сгенерированы
    EXPECT_EQ(stats.total_ticks, 100); // симул€ци€ пройдЄт все 100 тактов
}

TEST(cluster, task_refusals_when_queue_is_full) {
    Cluster cluster(1, 1.0); // макс эффективность дл€ быстрого заполнени€ очереди и мин размер очереди
    cluster.RunSimulation(100);
    SimulationStatistics stats = cluster.GetStatistics();

    EXPECT_GT(stats.task_refusals, 0); // предполагаетс€ что хот€ бы одно задание будет отклонено
}

TEST(cluster, downtime_ticks_when_no_tasks) {
    Cluster cluster(10, 0.0); // задани€ не будут сгенерированы
    cluster.RunSimulation(100);
    SimulationStatistics stats = cluster.GetStatistics();

    EXPECT_EQ(stats.downtime_ticks, 100); // все такты должны уйти в простой
}
