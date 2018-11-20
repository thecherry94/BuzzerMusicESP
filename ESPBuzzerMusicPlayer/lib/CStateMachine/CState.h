#ifndef STATE__H
#define STATE__H

#include <vector>
#include <map>


using StateTransitionCondition_t = 
    std::function<void(const char* targetStateName, std::function<bool()> checkConditions, std::function<void()> transitionAction)>;

class CState
{
    private:
        CState();
        std::map<const char*, std::vector<StateTransitionCondition_t>> _transitions;    // Transition von diesem State zu X State vVrhalten

    protected:
        virtual void process() = 0; // Wird bei jedem loop() Durchgang in der main aufgerufen
        virtual void enter() = 0;   // Wird immer aufgerufen wenn dieser State betreten wird
        virtual void leave() = 0;   // Wird immer aufgerufen wenn dieser State verlassen wird

    public:
        void AddTransition(const char* transitionName, const char* targetStateName, StateTransitionCondition_t);
        //void RemoveTransition(const char* transitionName);

        void CheckTransitionConditions();
        



};




#endif