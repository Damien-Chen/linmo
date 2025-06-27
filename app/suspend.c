#include <linmo.h>

void task2(void)
{
    int32_t cnt = 0;

    while (1) {
        printf("[task %d %ld]\n", mo_task_id(), cnt++);
    }
}

void task1(void)
{
    int32_t cnt = 0, val;

    while (1) {
        printf("[task %d %ld]\n", mo_task_id(), cnt++);
        if (cnt == 2000) {
            val = mo_task_resume(2);
            if (val == 0)
                printf("TASK 2 RESUMED!\n");
            else
                printf("FAILED TO RESUME TASK 2\n");
        }
        if (cnt == 6000) {
            val = mo_task_resume(0);
            if (val == 0)
                printf("TASK 0 RESUMED!\n");
            else
                printf("FAILED TO RESUME TASK 0\n");
        }
    }
}

void task0(void)
{
    int32_t cnt = 0, val;

    while (1) {
        printf("[task %d %ld]\n", mo_task_id(), cnt++);
        if (cnt == 1000) {
            val = mo_task_suspend(2);
            if (val == 0)
                printf("TASK 2 SUSPENDED!\n");
            else
                printf("FAILED TO SUSPEND TASK 2\n");
        }
        if (cnt == 5000) {
            printf("TRYING TO SUSPEND SELF...");
            mo_task_suspend(mo_task_id());
        }
    }
}

int32_t app_main(void)
{
    mo_task_spawn(task0, DEFAULT_STACK_SIZE);
    mo_task_spawn(task1, DEFAULT_STACK_SIZE);
    mo_task_spawn(task2, DEFAULT_STACK_SIZE);

    /* preemptive mode */
    return 1;
}
