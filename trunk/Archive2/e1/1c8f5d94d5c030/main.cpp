
class IAirdropPhaseProcessor 
{ 
    public :
    virtual int getAirdropPhase() = 0;
    virtual bool getChadcsArmed() = 0;
};

class AirdropPhaseProcessor : public IAirdropPhaseProcessor // Interface Implementation
{ 
    public :
    int getAirdropPhase() { return 42; }
    bool getChadcsArmed() { return true ;}
};

// -----------------------------

class IAirdropPhaseInputs 
{
    public :
    virtual bool gotoRedManualEnabled() = 0;
}; 

class AirdropPhaseInputs : public IAirdropPhaseInputs  // Interface Implementation
{
    public :
        bool gotoRedManualEnabled() {  return true ; } ;
}; 

// -----------------------------


class AirdropPhaseFactory
{
 public:
    static IAirdropPhaseProcessor* getAirdropPhaseProcessor( const IAirdropPhaseInputs& inputs )
    {   (void)inputs ; 
        return new AirdropPhaseProcessor ; // 1. Should be decided based on inputs ?

    }
    
};


// Simulink Bus
typedef struct 
{
    int AirdropPhase ;
    bool ChadcsArmed ;
} Simulink_Bus;

Simulink_Bus* AirdropBus = new Simulink_Bus ; // Will be a Externed,  defined just to get rid of seg fault


// 2. Something like following needs to be achieved via LCT ?
void Fill_SimulinkSignals( IAirdropPhaseProcessor* process , Simulink_Bus* SimBus )
{
    SimBus->AirdropPhase = process->getAirdropPhase() ;
    
    SimBus->ChadcsArmed  = process->getChadcsArmed () ;
}


int main()  // Example
{
    // 3. Simulink should instantiate this, needs Strapping as inputs to constructor ?
    IAirdropPhaseInputs *inputs = new AirdropPhaseInputs() ;  
    
   
    IAirdropPhaseProcessor* process 
                           = AirdropPhaseFactory::getAirdropPhaseProcessor( *inputs );
    
    // 4. Now 'process' will be used for updating Simulink Signals for 661/non-661 output ?
    Fill_SimulinkSignals( 
        process,
        AirdropBus
        ) ;
        
   
    /*  Never required
        delete process;
        delete inputs;
    */
}
