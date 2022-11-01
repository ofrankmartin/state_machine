#ifndef __STATE_CTRL_H__
#define __STATE_CTRL_H__

#include <stddef.h>
#include <stdint.h>

/// The default value for an unset state handle
#define STATE_CTRL_NO_STATE 0
/// Maximum lenght of the state name
#define STATE_CTRL_STATE_NAME_LEN 64

/**
 * @brief Forward declaration for a state data structure
 * 
 * State data struct can contain the data shared with the state callback 
 * functions. The final definition of this structure is up to the application
 * side.
 */
typedef struct StateCtrlStateData_s StateCtrlStateData_t;

/**
 * @brief The type of the handles used to manipulate a state
 */
typedef int StateCtrlStateHandle;

/**
 * @brief The state callbacks function definition
 */
typedef int(StateCtrlStateCallback)(StateCtrlStateData_t *data);

// Properties
/**
 * @brief The state properties
 */
typedef struct StateCtrlStateProperties_s StateCtrlStateProperties_t;
struct StateCtrlStateProperties_s {
    /// @brief State handle property
    StateCtrlStateHandle handle;
    /// @brief State name property
    char stateName[STATE_CTRL_STATE_NAME_LEN];
    /// @brief State data pointer
    StateCtrlStateData_t *stateDataPtr;
    /// @brief Callback for the state begin
    StateCtrlStateCallback *beginStateCallback;
    /// @brief Callback for the state loop
    StateCtrlStateCallback *loopStateCallback;
    /// @brief Callback for the state end
    StateCtrlStateCallback *endStateCallback;
};

// Factory
/**
 * @brief Initializes a state and returns a handle
 * 
 * @param handle [out] The newly created state handle
 * @param stateName [in] The name of this state
 * @param stateDataPtr [in] Pointer to a data structure used by this state
 * @param beginStateCallback [in] The callback function to be called when state begins
 * @param loopStateCallback [in] The callback function to be called when the state loop happens
 * @param endStateCallback [in] The callback function to be called when the state ends
 * @return int int Error code: 0 if success, otherwise error code
 */
int stateCtrlInitState(StateCtrlStateHandle *handle, const char *const stateName,
              StateCtrlStateData_t *stateDataPtr, StateCtrlStateCallback *beginStateCallback,
              StateCtrlStateCallback *loopStateCallback,
              StateCtrlStateCallback *endStateCallback);
/**
 * @brief Deinitializes and free memory related to a given state
 *
 * @param handle [in] A handle to a state to be destroyed
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlDeinitState(StateCtrlStateHandle *handle);

// State functions
/**
 * @brief The current state loop
 * 
 * This function must be called in the application main loop or auxiliary loop
 * in order to periodically call the current state loop callback.
 * 
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlLoopCurrentState(void);

// State change control
/**
 * @brief Sets the next state
 * 
 * @param nextState [in] A StateHandle pointer to the next event
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlSetNextState(StateCtrlStateHandle *nextState);
/**
 * @brief Ends the current and begins the next state
 * 
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlGoToNextState(void);
/**
 * @brief Sets the next state, ends the current state and begin the next state
 * 
 * @param nextState A StateHandle pointer to the next event
 * @return int Error code: 0 if success, otherwise error code
 * 
 * @remarks This is equivalent to call @ref stateCtrlSetNextState then stateCtrlGoToNextState
 */
int stateCtrlGoToState(StateCtrlStateHandle *nextState);

// Read functions
/**
 * @brief Get the current state properties
 * 
 * @param stateProperties [out] a pointer to a pointer to a StateProperties struct
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlGetCurrentStateProperties(StateCtrlStateProperties_t **stateProperties);
/**
 * @brief Get the next state properties
 * 
 * @param stateProperties [out] a pointer to a pointer to a StateProperties struct
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlGetNextStateProperties(StateCtrlStateProperties_t **stateProperties);
/**
 * @brief Get the previous state properties
 * 
 * @param stateProperties [out] a pointer to a pointer to a StateProperties struct
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlGetPrevStateProperties(StateCtrlStateProperties_t **stateProperties);

/**
 * @brief Get the state properties from a named state
 * 
 * @param stateName [in] A string containing the a state name
 * @param stateProperties [out] a pointer to a pointer to a StateProperties struct
 * @return int Error code: 0 if success, otherwise error code
 */
int stateCtrlGetStatePropertiesByName(const char * const stateName, StateCtrlStateProperties_t **stateProperties);

#endif /* __STATE_CTRL_H__ */
