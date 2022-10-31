#ifndef __STATES_DEFINITIONS_H__
#define __STATES_DEFINITIONS_H__

#define INIT_STATE(NAME, stateData) \
    initState(&NAME ## State, NAME ## Name, stateData, &NAME ## Begin, &NAME ## Loop, &NAME ## End)

/// @brief Definition of the state data structure
typedef struct StateData_s {
    int someData;
    StateHandle nextState;
} StateData_t;

#endif /* __STATES_DEFINITIONS_H__ */
