class SegmentActivityState {
    public:
    enum class ActivityStateType : int
            {
                PreExecution = 0,   /**< Pre-execution state. */
                Execution = 1, /**< Execution state. */
                PostExecution = 2 /**< Post-execution state. */
            };
};
using SegmentActivityType = SegmentActivityState::ActivityStateType;
int main() {
    auto x = SegmentActivityType::PreExecution;
    
}