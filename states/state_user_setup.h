#ifndef __STATE_USER_SETUP_H__
#define __STATE_USER_SETUP_H__

#include "../libsmachine/smachine.h"
#include "states_definitions.h"

static const char * const userSetupName = "user_setup";

int userSetupBegin(StateData_t *data);
int userSetupLoop(StateData_t *data);
int userSetupEnd(StateData_t *data);

#endif /* __STATE_USER_SETUP_H__ */
