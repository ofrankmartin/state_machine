#ifndef __SMACHINE_H__
#define __SMACHINE_H__

#include <stddef.h>
#include <stdint.h>

#define NO_STATE 0
#define STATE_NAME_LEN 64

typedef struct StateData_s StateData_t;

typedef int StateHandle;

typedef int(StateCallback)(StateData_t *data);

// Properties
typedef struct StateProperties_s StateProperties_t;
struct StateProperties_s {
    StateHandle handle;
    char stateName[STATE_NAME_LEN];
    StateData_t *stateDataPtr;
    StateCallback *beginStateCallback;
    StateCallback *loopStateCallback;
    StateCallback *endStateCallback;
};

// Factory
/**
 * @brief Initializes a state and returns a handle
 *
 * @param handle [out] The newly created state handle
 * @param stateDataPtr [in] Pointer to a data structure used by this state
 * @return int Error code: 0 if success, otherwise error code
 */
int initState(StateHandle *handle, const char *const stateName,
              StateData_t *stateDataPtr, StateCallback *beginStateCallback,
              StateCallback *loopStateCallback,
              StateCallback *endStateCallback);
/**
 * @brief Deinitializes and free memory related to a given state
 *
 * @param handle [in] A handle to a state to be destroyed
 * @return int Error code: 0 if success, otherwise error code
 */
int deinitState(StateHandle *handle);

// State functions
int loopCurrentState(void);

// State change control
int setNextState(StateHandle *nextState);
int goToNextState(void);
int goToState(StateHandle *nextState);

// Read functions
int getCurrentStateProperties(StateProperties_t **stateProperties);
int getNextStateProperties(StateProperties_t **stateProperties);
int getPrevStateProperties(StateProperties_t **stateProperties);

int getStatePropertiesByName(const char * const stateName, StateProperties_t **stateProperties);

#endif /* __SMACHINE_H__ */
