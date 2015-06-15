
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Degrees;
class Radians;

class AngleVisitor
{
    public:
        virtual void visit(Degrees const &r_degrees) = 0;
        virtual void visit(Radians const &r_radians) = 0;
};

class Angle : public AngleVisitor
{
    public:
        Angle(double value = 0) : value_(value) { }
        virtual void accept(AngleVisitor * const p_visitor) const = 0;
        void convertTo(Angle * const p_angle) const { accept(p_angle); }
        double value() const { return value_; }
        
    protected:
        virtual ~Angle() { }
        double value_;
};

class Degrees : public Angle
{
    public:
        Degrees(double value = 0) : Angle(value) { }
        Degrees(Angle const &r_angle);
        void accept(AngleVisitor * const p_visitor) const;
        void convertTo(Angle * const p_angle) const;
        void visit(Degrees const &r_degrees);
        void visit(Radians const &r_radians);
};

class Radians : public Angle
{
    public:
        Radians(double value = 0) : Angle(value) { }
        Radians(Angle const &r_angle);
        void accept(AngleVisitor * const p_visitor) const;
        void convertTo(Angle * const p_angle) const;
        void visit(Degrees const &r_degrees);
        void visit(Radians const &r_radians);
};

class SignalReadingValue : public AngleVisitor
{
    public:
        string print(Angle const &r_angle)
        {
            r_angle.accept(this);
            return text_;
        }
        void visit(Degrees const &r_degrees) { text_ = to_string(r_degrees.value()) + " degs"; }
        void visit(Radians const &r_radians) { text_ = to_string(r_radians.value()) + " rads"; }
    
    private:
        string text_;
};

int main()
{ 
    SignalReadingValue signal_reading_value;
    
    Degrees degrees(180);
    Radians radians(degrees);
    cout << "Converted " << signal_reading_value.print(degrees) << " to " << signal_reading_value.print(radians) << "." << endl;
    
    Angle *p_angle = new Radians(1.5 * M_PI);
    Angle *p_angle_2 = new Degrees();
    p_angle->convertTo(p_angle_2);
    cout << "Converted " << signal_reading_value.print(*p_angle) << " to " << signal_reading_value.print(*p_angle_2) << "." << endl;
}

Degrees::Degrees(Angle const &r_angle) { r_angle.accept(this); }
void Degrees::accept(AngleVisitor * const p_visitor) const { p_visitor->visit(*this); }
void Degrees::visit(Degrees const &r_degrees) { value_ = r_degrees.value(); }
void Degrees::visit(Radians const &r_radians) { value_ = (180.0 / M_PI) * r_radians.value(); }

Radians::Radians(Angle const &r_angle) { r_angle.accept(this); }
void Radians::accept(AngleVisitor * const p_visitor) const { p_visitor->visit(*this); }
void Radians::visit(Degrees const &r_degrees) { value_ = (M_PI / 180.0) * r_degrees.value(); }
void Radians::visit(Radians const &r_radians) { value_ = r_radians.value(); }
