#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct view_base // polymorphic class (object oriented)
{
    using pointer = std::unique_ptr<view_base> ;

    virtual ~view_base() = default ;
    virtual void render() const = 0 ;
    virtual void say_hello( std::string source ) const = 0 ; // only for exposition
};

struct model
{
    // data management, access and validation

    // number
    static constexpr int min_n = 0 ;
    static constexpr int max_n = 6 ;

    int number() const { return number_ ; }
    void number( int n ) { if( valid_number(n) ) number_ = n ; }
    void increment() { if( number_ < max_n ) { ++number_ ; update_views() ; } }
    void decrement() { if( number_ > min_n ) { --number_ ; update_views() ; } }
    static bool valid_number( int number ) { return number >= min_n && number <= max_n ; }

    // ...

    // TODO: persistence support
    std::istream& read( std::istream& stm ) ;
    std::ostream& write( std::istream& stm ) ;

    // associated views
    void add_view( view_base::pointer&& view )
    { views.push_back( std::move(view) ) ; views.back()->render() ; }

    const std::vector<view_base::pointer>& associated_views() const { return views ; }

    private:

        std::vector<view_base::pointer> views ; // in this variant, the model owns the associated views
        void update_views() { for( auto& p : views ) p->render() ; }

        int number_ = ( min_n + max_n ) / 2 ;

        // ...
};

struct controller
{
    void handle_input( char input )
    {
        if( input == '+' ) model_.increment() ;
        else if( input == '-' ) model_.decrement() ;
    }

    // the controller is typically responsible for creating the view(s) and associating them with the model
    template < typename VIEW, typename... CONSTRUCTOR_ARGS >
    void create_view( CONSTRUCTOR_ARGS&&... args )
    { model_.add_view( std::make_unique<VIEW>( model_, *this, std::forward<CONSTRUCTOR_ARGS>(args)... ) ) ; }

    // note: model_.associated_views() gives (non-mutable) access to the associated views:
    // for instance:
    void say_hello_to_all() const
    { for( const auto& view : model_.associated_views() ) view->say_hello( "controller" ) ; }

    private: model model_ ; // in this variant, holds the DefaultConstructible model by value
};

struct view : view_base
{
    view( model& m, controller& c ) : model_(m), controller_(c)  {}

    // retrieve the information from the model and display it
    virtual void render() const override { std::cout << "view: " << model_.number() << '\n' ; }

    virtual void say_hello( std::string source ) const override
    { std::cout << "view: '" << source << "' says hello\n" ; }


    protected:
        model& model_ ; // and to the model

        controller& controller_ ; // optional: the view holds a reference to its controller
        // this is required if the view directly accepts user input requesting a change
        // in the data and it needs to forward the request to the associated controller
};

int main()
{
    struct text_view : view
    {
        using view::view ;
        text_view( model& m, controller& c, std::string id ) : view(m,c), id(id) {}

        virtual void render() const override
        {
            static const char* const text[] = { "zero", "one", "two", "three", "four", "five", "six" } ;
            static constexpr int MAXN = sizeof(text) / sizeof( text[0] ) - 1 ;
            static_assert( model::min_n == 0 && model::max_n == MAXN, "stale code: model has changed" ) ;

            std::cout << "text_view (" << id << "): '" << text[ model_.number() ] << "'\n\n" ;
        }

        virtual void say_hello( std::string source ) const override
        { std::cout << "text_view (" << id << "): '" << source << "' says hello\n" ; }

        const std::string id = "noname" ;
    };

    controller controller ;
    controller.create_view<view>() ;
    controller.create_view<text_view>("daffy") ;

    for( char c : { '+', '+', '+', '?', '+', '-', '$', '-' } ) controller.handle_input(c) ;

    controller.say_hello_to_all() ;
}
