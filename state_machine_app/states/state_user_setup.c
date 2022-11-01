#include "state_user_setup.h"
#include <stdio.h>
#include <unistd.h>

#include "state_idle.h"

int userSetupBegin(StateCtrlStateData_t *data)
{
    StateCtrlStateProperties_t *currStateProps = NULL;
    stateCtrlGetCurrentStateProperties(&currStateProps);
    printf("Begin state: <%s>.\n", (currStateProps ? currStateProps->stateName : "unknown"));
    
    StateCtrlStateProperties_t *nextProps = NULL;
    stateCtrlGetStatePropertiesByName(idleName, &nextProps);
    data->nextState = nextProps ? nextProps->handle : STATE_CTRL_NO_STATE;
    
    stateCtrlSetNextState(&data->nextState);
}

int userSetupLoop(StateCtrlStateData_t *data)
{
    data->someData++;
    printf("%02d... ", data->someData);
    fflush(stdout);

    usleep(200 * 1000);
    if (data->someData >= 5) {
        printf("\n");
        stateCtrlGoToNextState();
    }
    return 0;    
}

int userSetupEnd(StateCtrlStateData_t *data)
{
    StateCtrlStateProperties_t *currStateProps = NULL;
    stateCtrlGetCurrentStateProperties(&currStateProps);
    printf("End state: <%s>.\n\n", (currStateProps ? currStateProps->stateName : "unknown"));
    data->someData = 0;
}
