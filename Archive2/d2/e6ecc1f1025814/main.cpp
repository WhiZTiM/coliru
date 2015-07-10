#include <iostream>
#include <vector>
#include <string>

struct target
{
    explicit target ( std::string its_name ) : name( std::move(its_name) ) {}
    std::string name;
	virtual ~target() = default ;
};

struct monster : target 
{
    explicit monster( std::string name ) : target( std::move(name) ) {}
    // ...
};

struct vampire : target
{
    explicit vampire( std::string name ) : target( std::move(name) ) {}
    // ...
};

struct player
{
    target* pick_target( const std::vector<target*>& available_targets ) /* may be const */
    {
        // TODO: pick an appropriate target from among available_targets
        // in this trivialised example, we always pick the first target
        return available_targets.empty() ? nullptr : available_targets.front() ;
    }

    void make_attack( const std::vector<target*>& available_targets )
    {
        // ...
        target* the_target = pick_target( available_targets ) ;
        if( the_target != nullptr ) std::cout << "picked target '" << the_target->name << "'\n" ;
        // ...
    }
};

int main()
{
	vampire orlok( "orlok" );
	monster bigger( "bigger" );
	monster tiny( "tiny" );

    player kyle ;
    kyle.make_attack( { std::addressof(bigger), std::addressof(orlok), std::addressof(tiny) } );
    kyle.make_attack( { std::addressof(orlok), std::addressof(bigger), std::addressof(tiny) } );
}
