/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: Managging the link table of task_oder.
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#include "os_task.h"
#include "os_tasklink.h"

task_order_link_t t_order_link=
{
    .head_node = OS_NULL,
    .count_node    = 0,
};

void os_order_link_init(by_task_t * _task)
{
    if (OS_NULL != _task)
    {
        t_order_link.head_node = _task;
        t_order_link.head_node->last_node = _task;
        t_order_link.head_node->next_node = _task;
    }
}

int os_input_link(by_task_t * _task)
{
    OS_NULL_CHECK(_task);
    OS_NULL_CHECK(t_order_link.head_node);

    by_task_t *p_next_node = t_order_link.head_node->next_node;
    by_task_t *p_head_node = t_order_link.head_node;

    p_head_node->next_node = _task;
    p_next_node->last_node = _task;

    _task->next_node = p_next_node;
    _task->last_node = p_head_node;

    t_order_link.count_node++;

    return 0;
}

int os_output_link(by_task_t * _task)
{
    OS_NULL_CHECK(_task);
    OS_NULL_CHECK(t_order_link.head_node);

    by_task_t *p_last_node = _task->last_node;
    by_task_t *p_next_node = _task->next_node;

    p_next_node->last_node = p_last_node;
    p_last_node->next_node = p_next_node;

    _task->last_node = _task->next_node = _task;

    t_order_link.count_node--;

    return 0;
}

