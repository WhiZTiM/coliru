#include <utility>

struct Script { };

class ScriptThread {
public:
    ScriptThread(): mParent() {}

private:
    ScriptThread(ScriptThread *parent): mParent(parent) {}

public:
    ScriptThread(ScriptThread &&rhs);
    ScriptThread &operator = (ScriptThread &&rhs);
    // copy constructor/assignment deleted implicitly

    ScriptThread& execute(const Script& script)&;
    ScriptThread execute(const Script& script)&&;
    ScriptThread spawn();
    ScriptThread spawn(const Script &script);

private:
    ScriptThread *mParent;
};

ScriptThread &ScriptThread::execute(const Script &script)& {
    // start executing the given script
    return *this;
}

ScriptThread ScriptThread::execute(const Script &script)&& {
    // start executing the given script
    return std::move(*this);
}

ScriptThread ScriptThread::spawn() {
    // create a ScriptThread with "this" as its parent
    return ScriptThread(this);
}

ScriptThread ScriptThread::spawn(const Script &script) {
    // convenience method to spawn and execute at the same time
    return spawn().execute(script); // OK, calling execute() on an rvalue returns an rvalue
}