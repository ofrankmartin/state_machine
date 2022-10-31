#include "state_user_setup.h"
#include <stdio.h>
#include <unistd.h>

#include "state_idle.h"

int userSetupBegin(StateData_t *data)
{
    StateProperties_t *currStateProps = NULL;
    getCurrentStateProperties(&currStateProps);
    printf("Begin state: <%s>.\n", (currStateProps ? currStateProps->stateName : "unknown"));
    
    StateProperties_t *nextProps = NULL;
    getStatePropertiesByName(idleName, &nextProps);
    data->nextState = nextProps ? nextProps->handle : NO_STATE;
    
    setNextState(&data->nextState);
}

int userSetupLoop(StateData_t *data)
{
    data->someData++;
    printf("%02d... ", data->someData);
    fflush(stdout);

    usleep(200 * 1000);
    if (data->someData >= 5) {
        printf("\n");
        goToNextState();
    }
    return 0;    
}

int userSetupEnd(StateData_t *data)
{
    StateProperties_t *currStateProps = NULL;
    getCurrentStateProperties(&currStateProps);
    printf("End state: <%s>.\n\n", (currStateProps ? currStateProps->stateName : "unknown"));
    data->someData = 0;
}
