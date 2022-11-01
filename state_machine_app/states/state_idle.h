#ifndef __STATE_IDLE_H__
#define __STATE_IDLE_H__

#include <state_ctrl.h>
#include "states_definitions.h"

static const char * const idleName = "idle";

int idleBegin(StateCtrlStateData_t *data);
int idleLoop(StateCtrlStateData_t *data);
int idleEnd(StateCtrlStateData_t *data);

#endif /* __STATE_IDLE_H__ */
