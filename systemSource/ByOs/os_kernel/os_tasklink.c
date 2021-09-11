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

Task_Order_Link_t _taskOrderLink=
{
    .head_node = _NULL,
    .count_node    = 0,
};

void _taskOrderLink_Init(tTask * _task)
{
    if (_NULL != _task)
    {
        _taskOrderLink.head_node = _task;
        _taskOrderLink.head_node->last_node = _task;
        _taskOrderLink.head_node->next_node = _task;
    }
}

int _tInputLink(tTask * _task)
{
    _NULL_CHECK(_task);
    _NULL_CHECK(_taskOrderLink.head_node);

    tTask *p_next_node = _taskOrderLink.head_node->next_node;
    tTask *p_head_node = _taskOrderLink.head_node;

    p_head_node->next_node = _task;
    p_next_node->last_node = _task;

    _task->next_node = p_next_node;
    _task->last_node = p_head_node;

    _taskOrderLink.count_node++;

    return 0;
}

int _tOutputLink(tTask * _task)
{
    _NULL_CHECK(_task);
    _NULL_CHECK(_taskOrderLink.head_node);

    tTask *p_last_node = _task->last_node;
    tTask *p_next_node = _task->next_node;

    p_next_node->last_node = p_last_node;
    p_last_node->next_node = p_next_node;

    _task->last_node = _task->next_node = _task;

    _taskOrderLink.count_node--;

    return 0;
}

