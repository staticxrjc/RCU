#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>

namespace RCU {

struct State {
    // Load Assets and Font
    virtual void Init () = 0; 
    virtual void HandleInput () = 0;
    virtual void Update (float dt) = 0;
    virtual void Draw (float dt) = 0;
    virtual void Pause () {};
    virtual void Resume () {};
};

typedef std::unique_ptr<State> StateRef;

class StateMachine {
public:
    StateMachine() {};
    ~StateMachine() {};

public: 
    void AddState(StateRef newState, bool isReplacing=true);
    void RemoveState();
    void ProcessStateChanges();
    StateRef& GetActiveState();

private:
    std::stack<StateRef> _states;
    StateRef _newState;

    bool _isRemoving;
    bool _isAdding;
    bool _isReplacing;
};

}

#endif // STATEMACHINE_H