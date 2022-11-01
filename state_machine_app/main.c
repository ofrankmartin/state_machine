#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#include <state_ctrl.h>
#include "states/state_user_setup.h"
#include "states/state_idle.h"

static bool _doExit = false;

void sigHandler(int sig);
void sigHandler(int sig) { _doExit = true; }

int main(int argc, char **argv)
{
    struct sigaction signal_handler;

    signal_handler.sa_handler = sigHandler;
    sigemptyset(&signal_handler.sa_mask);
    signal_handler.sa_flags = 0;

    sigaction(SIGINT, &signal_handler, NULL);

    StateCtrlStateData_t stateData = {.someData = 0, .nextState = STATE_CTRL_NO_STATE};

    StateCtrlStateHandle userSetupState = STATE_CTRL_NO_STATE;
    INIT_STATE(userSetup, &stateData);

    StateCtrlStateHandle idleState = STATE_CTRL_NO_STATE;
    INIT_STATE(idle, &stateData);

    stateCtrlGoToState(&userSetupState);

    while (!_doExit) {
        stateCtrlLoopCurrentState();
        StateCtrlStateProperties_t *currStateProperties = NULL;
        stateCtrlGetCurrentStateProperties(&currStateProperties);
        if (currStateProperties == NULL) {
            _doExit = true;
        }
    }

    // Cleaning up state
    stateCtrlDeinitState(&userSetupState);

    printf("\nExiting...\n");

    return EXIT_SUCCESS;
}
