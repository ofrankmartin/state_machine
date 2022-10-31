#ifndef __STATE_IDLE_H__
#define __STATE_IDLE_H__

#include "../libsmachine/smachine.h"
#include "states_definitions.h"

static const char * const idleName = "idle";

int idleBegin(StateData_t *data);
int idleLoop(StateData_t *data);
int idleEnd(StateData_t *data);

#endif /* __STATE_IDLE_H__ */
