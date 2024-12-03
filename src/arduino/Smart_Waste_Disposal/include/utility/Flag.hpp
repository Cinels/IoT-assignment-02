#ifndef __FLAG__
#define __FLAG__

/// @brief Enumeration to track allarms.
typedef enum containerAllarm {NO_ALLARM, FULL_ALLARM, TEMPERATURE_ALLARM, TEMPERATURE_AND_FULL_ALLARM} containerAllarm;

/// @brief Enumeration to track instruction.
typedef enum containerInstruction {NO_INSTRUCTION, EMPTY_INSTRUCTION, RESTORE_INSTRUCTION, EMPTY_AND_RESTORE_INSTRUCTION} containerInstruction;

/// @brief Class to signal data.
class Flag {
private:
    containerAllarm allarm;
    containerInstruction instruction;
public:
    /// @brief Flag constructor, creates a flag with no allarm and no instruction.
    Flag();

    /// @brief Returns if there is any allarm signaled.
    /// @return the allarm.
    containerAllarm getAllarm();
    
    /// @brief Returns if there is any instruction to be execute.
    /// @return the instruction.
    containerInstruction getInstruction();
    
    /// @brief Sets an allarm.
    /// @param allarm value of the allarm.
    void setAllarm(containerAllarm allarm);

    /// @brief Sets an instructon.
    /// @param instruction value of the instruction.
    void setInstruction(containerInstruction instruction);
};

#endif
