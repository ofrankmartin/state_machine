#include "state_idle.h"
#include <stdio.h>
#include <unistd.h>

#include "state_user_setup.h"

int idleBegin(StateData_t *data)
{
    StateProperties_t *currStateProps = NULL;
    getCurrentStateProperties(&currStateProps);
    printf("Begin state: <%s>.\n", (currStateProps ? currStateProps->stateName : "unknown"));
    
    StateProperties_t *nextProps = NULL;
    getStatePropertiesByName(userSetupName, &nextProps);
    data->nextState = nextProps ? nextProps->handle : NO_STATE;
    
    setNextState(&data->nextState);
}

int idleLoop(StateData_t *data)
{
    data->someData += 2;
    printf("%02d... ", data->someData);
    fflush(stdout);

    usleep(200 * 1000);
    if (data->someData >= 10) {
        printf("\n");
        goToNextState();
    }
    return 0;    
}

int idleEnd(StateData_t *data)
{
    StateProperties_t *currStateProps = NULL;
    getCurrentStateProperties(&currStateProps);
    printf("End state: <%s>.\n\n", (currStateProps ? currStateProps->stateName : "unknown"));
    data->someData = 0;
}
