#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#include "libsmachine/smachine.h"
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

    StateData_t stateData = {.someData = 0, .nextState = NO_STATE};

    StateHandle userSetupState = NO_STATE;
    INIT_STATE(userSetup, &stateData);

    StateHandle idleState = NO_STATE;
    INIT_STATE(idle, &stateData);

    goToState(&userSetupState);

    while (!_doExit) {
        loopCurrentState();
        StateProperties_t *currStateProperties = NULL;
        getCurrentStateProperties(&currStateProperties);
        if (currStateProperties == NULL) {
            _doExit = true;
        }
    }

    // Cleaning up state
    deinitState(&userSetupState);

    printf("\nExiting...\n");

    return EXIT_SUCCESS;
}
