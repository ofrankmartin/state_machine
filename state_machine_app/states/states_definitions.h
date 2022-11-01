#ifndef __STATES_DEFINITIONS_H__
#define __STATES_DEFINITIONS_H__

#define INIT_STATE(NAME, stateData) \
    stateCtrlInitState(&NAME ## State, NAME ## Name, stateData, &NAME ## Begin, &NAME ## Loop, &NAME ## End)

/// @brief Definition of the state data structure
typedef struct StateCtrlStateData_s {
    int someData;
    StateCtrlStateHandle nextState;
} StateCtrlStateData_t;

#endif /* __STATES_DEFINITIONS_H__ */
