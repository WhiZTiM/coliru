struct Actor;
struct Button;

class InputComponent
{
public:
    InputComponent();
    ~InputComponent();

    void handleinput(Actor& actor);
    bool isPressed(Button button);
};