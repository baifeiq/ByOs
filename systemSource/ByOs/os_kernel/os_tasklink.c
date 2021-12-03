/*******************************************************************************
 * @file     os_tasklink.c
 * @brief    Managging the link table of TaskOder.
 * @version  V1.0.0
 * @date     2021/07/12
 * @author   Baifeiq
 * @note     nothing
 ******************************************************************************/

#include "os_task.h"
#include "os_tasklink.h"

task_order_link_t t_order_link=
{
    .head_node = _NULL,
    .count_node    = 0,
};

void os_order_link_init(tTask * _task)
{
    if (_NULL != _task)
    {
        t_order_link.head_node = _task;
        t_order_link.head_node->last_node = _task;
        t_order_link.head_node->next_node = _task;
    }
}

int os_input_link(tTask * _task)
{
    _NULL_CHECK(_task);
    _NULL_CHECK(t_order_link.head_node);

    tTask *p_next_node = t_order_link.head_node->next_node;
    tTask *p_head_node = t_order_link.head_node;

    p_head_node->next_node = _task;
    p_next_node->last_node = _task;

    _task->next_node = p_next_node;
    _task->last_node = p_head_node;

    t_order_link.count_node++;

    return 0;
}

int os_output_link(tTask * _task)
{
    _NULL_CHECK(_task);
    _NULL_CHECK(t_order_link.head_node);

    tTask *p_last_node = _task->last_node;
    tTask *p_next_node = _task->next_node;

    p_next_node->last_node = p_last_node;
    p_last_node->next_node = p_next_node;

    _task->last_node = _task->next_node = _task;

    t_order_link.count_node--;

    return 0;
}

