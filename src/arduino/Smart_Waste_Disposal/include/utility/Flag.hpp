#ifndef __FLAG__
#define __FLAG__

typedef enum containerAllarm {NO_ALLARM, TEMPERATURE_ALLARM, FULL_ALLARM, TEMPERATURE_AND_FULL_ALLARM} containerAllarm;
typedef enum containerInstruction {NO_INSTRUCTION, EMPTY_INSTRUCTION, RESTORE_INSTRUCTION, EMPTY_AND_RESTORE_INSTRUCTION} containerInstruction;

class Flag {
private:
    containerAllarm allarm;
    containerInstruction instruction;
public:
    Flag();
    containerAllarm getAllarm();
    containerInstruction getInstruction();
    void setAllarm(containerAllarm allarm);
    void setInstruction(containerInstruction instruction);
};

#endif