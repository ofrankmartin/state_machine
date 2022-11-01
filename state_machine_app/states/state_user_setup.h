#ifndef __STATE_USER_SETUP_H__
#define __STATE_USER_SETUP_H__

#include <state_ctrl.h>
#include "states_definitions.h"

static const char * const userSetupName = "user_setup";

int userSetupBegin(StateCtrlStateData_t *data);
int userSetupLoop(StateCtrlStateData_t *data);
int userSetupEnd(StateCtrlStateData_t *data);

#endif /* __STATE_USER_SETUP_H__ */
