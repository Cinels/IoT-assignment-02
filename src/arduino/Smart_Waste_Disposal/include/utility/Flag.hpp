#ifndef __FLAG__
#define __FLAG__

/// @brief Enumeration to track alarms.
typedef enum containerAlarm {NO_ALARM, FULL_ALARM, TEMPERATURE_ALARM, TEMPERATURE_AND_FULL_ALARM} containerAlarm;

/// @brief Enumeration to track instruction.
typedef enum containerInstruction {NO_INSTRUCTION, EMPTY_INSTRUCTION, RESTORE_INSTRUCTION, EMPTY_AND_RESTORE_INSTRUCTION} containerInstruction;

/// @brief Class to signal data.
class Flag {
private:
    containerAlarm alarm;
    containerInstruction instruction;
public:
    /// @brief Flag constructor, creates a flag with no alarm and no instruction.
    Flag();

    /// @brief Returns if there is any alarm signaled.
    /// @return the alarm.
    containerAlarm getAlarm();
    
    /// @brief Returns if there is any instruction to be execute.
    /// @return the instruction.
    containerInstruction getInstruction();
    
    /// @brief Sets an alarm.
    /// @param alarm value of the alarm.
    void setAlarm(containerAlarm alarm);

    /// @brief Sets an instructon.
    /// @param instruction value of the instruction.
    void setInstruction(containerInstruction instruction);
};

#endif
