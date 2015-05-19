    
    // this is nested in WizardFactory....
    template <typename WIZARD>
    class Registrant : public Wizard
    {
        static const bool staticRegistration; ///< Static init of this adds WIZARD to the factory map

        template<typename T, T> class ForceInstantiation{ }; ///< T will be explicitly instantiated for each Registrant
        typedef ForceInstantiation<const bool&, staticRegistration> AutoRegistrationHook;

    protected:
        Registrant() = default; ///< You cannot create an instance of this type, only inheritance is allowed
    };
    
    // Simply adds {wizardType, generator} to m_wizardRegistry
    inline bool WizardFactory::registerWizard(const std::string &wizardType, WizardBuilder &&builder)
    {
        return m_registry.insert( std::make_pair(wizardType,std::forward<WizardBuilder>(builder)) ).second;
    }

    
    // THis is the static initializer for Registrants staticRegistration bool
    // Wizard implementors must inherit from Registrant, which will embed this static bool in their class's compilation unit
    // the c++ standard has a quirk that causes the compiler to strip the staticRegistration variable since its in a template
    // (it thinks its unused even tho its static initialization has a side effect) so the ForceInstantiation metatype
    // prevents the variable from being blown away. Thus when the program loads, the templatized initializer below
    // will add WIZARD to the factory
    //
    // At compile time, generates the initializer for this variable whose side effect is to add a string -> instance
    // returning function at .so load time
    template<class WIZARD>
    const bool WizardFactory::Registrant<WIZARD>::staticRegistration(
        get().registerWizard(getDemangledNameFor<WIZARD>(),std::make_shared<WIZARD>)
    );