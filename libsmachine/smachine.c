#include "smachine.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct StatesListItem_s {
    StateProperties_t *properties;
    struct StatesListItem_s *next;
    struct StatesListItem_s *prev;
} StatesListItem_t;

static StatesListItem_t *_statesList = NULL;
static StatesListItem_t *_lastState = NULL;
static StatesListItem_t *_currentState = NULL;
static StatesListItem_t *_nextState = NULL;
static StatesListItem_t *_prevState = NULL;

// Private Prototypes
StatesListItem_t *findStateItem(StateHandle *handle);
int executeStateCallback(StateCallback *callback, StateData_t *data);

// Factory implementation
int initState(StateHandle *handle, const char *const stateName,
              StateData_t *stateDataPtr, StateCallback *beginStateCallback,
              StateCallback *loopStateCallback, StateCallback *endStateCallback)
{
    *handle = NO_STATE;
    StatesListItem_t *newState = calloc(1, sizeof(*newState));
    if (newState == NULL)
        return -1;

    newState->properties = calloc(1, sizeof(*(_statesList->properties)));
    if (newState->properties == NULL)
        return -1;

    newState->properties->stateDataPtr = stateDataPtr;
    newState->properties->beginStateCallback = beginStateCallback;
    newState->properties->loopStateCallback = loopStateCallback;
    newState->properties->endStateCallback = endStateCallback;
    snprintf(newState->properties->stateName, STATE_NAME_LEN, "%s", stateName);

    if (_statesList) {
        *handle = _lastState->properties->handle + 1;
        newState->prev = _lastState;
        _lastState->next = newState;
        _lastState = newState;
    } else {
        *handle = 1;
        _statesList = newState;
        _lastState = _statesList;
        _nextState = _statesList;
    }
    newState->properties->handle = *handle;
}

int deinitState(StateHandle *handle)
{
    StatesListItem_t *state = findStateItem(handle);
    if (state) {
        if (state->prev)
            state->prev->next = state->next;
        if (state->next)
            state->next->prev = state->prev;
    }
    free(state->properties);
    free(state);
}

int loopCurrentState(void)
{
    if (_currentState) {
        return executeStateCallback(
            _currentState->properties->loopStateCallback,
            _currentState->properties->stateDataPtr);
    }

    return 0;
}

int setNextState(StateHandle *nextState)
{
    // TODO check if the state exists
    _nextState = findStateItem(nextState);
    return 0;
}

int goToNextState(void)
{
    // End current state
    if (_currentState) {
        // TODO Handle errors
        executeStateCallback(_currentState->properties->endStateCallback,
                             _currentState->properties->stateDataPtr);
    }

    _prevState = _currentState;
    _currentState = _nextState;
    _nextState = NULL;

    // Begin new state
    if (_currentState) {
        // TODO Handle errors
        executeStateCallback(_currentState->properties->beginStateCallback,
                             _currentState->properties->stateDataPtr);
    }
}

int goToState(StateHandle *nextState)
{
    // TODO Handle errors
    setNextState(nextState);
    return goToNextState();
}

int getCurrentStateProperties(StateProperties_t **stateProperties)
{
    StatesListItem_t *item = _currentState;
    *stateProperties = item ? item->properties : NULL;
    return 0;
}

int getNextStateProperties(StateProperties_t **stateProperties)
{
    StatesListItem_t *item = _nextState;
    *stateProperties = item ? item->properties : NULL;
    return 0;
}

int getPrevStateProperties(StateProperties_t **stateProperties)
{
    StatesListItem_t *item = _prevState;
    *stateProperties = item ? item->properties : NULL;
    return 0;
}

int getStatePropertiesByName(const char * const stateName, StateProperties_t **stateProperties)
{
    StatesListItem_t *currItem = _statesList;
    while (currItem != NULL) {
        if (strcmp(stateName, currItem->properties->stateName) == 0) {
            *stateProperties = currItem->properties;
            break;
        }
        currItem = currItem->next;
    }
    
    return 0;
}

// Private implementation
StatesListItem_t *findStateItem(StateHandle *handle)
{
    StatesListItem_t *currItem = _statesList;
    while (currItem != NULL) {
        if (currItem->properties->handle == *handle) {
            break;
        }
        currItem = currItem->next;
    }

    return currItem;
}

int executeStateCallback(StateCallback *callback, StateData_t *data)
{
    if (callback)
        return callback(data);
    return 0;
}
