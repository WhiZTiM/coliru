#include <valarray>
#include <cmath>
#include <tuple>

// ell = { x | (x - xc)' * P^-1 * (x - xc) <= 1 }
class ell
{
private:
    using Vec = std::valarray<double>;
    // using Mat = std::valarray<Vec>;

    class Mat : public std::valarray<Vec> 
    {
    public:
        Mat(Vec v, size_t n) : std::valarray<Vec>(v, n) {}
        Vec operator*(const Vec& g) const {
            size_t n = g.size();
            Vec gt(n);
            for (size_t i=0; i<n; ++i) {
                gt[i] = ((*this)[i] * g).sum();
            }
            return gt;        
        }
    };
    
	size_t n;
    Mat    _P;
    Vec    _xc;
    double _c1;

protected:
    void update_P(double sig, double delta, const Vec& gt) {
    	for (size_t i=0; i<n; ++i) {
      		double temp = sig*gt[i]; 
      		for (size_t j=i; j<n; ++j) {
        		_P[i][j] -= temp * gt[j];
        		_P[i][j] *= delta;
      		}
    	}
    
    	// Make symmetric
    	for (size_t i=0; i<n-1; ++i) {
      		for (size_t j=i+1; j<n; ++j) {
        		_P[j][i] = _P[i][j];
      		}
    	}
    }

public:
    ell(double val, const Vec& x) :
        n{x.size()},
        _P(Mat(Vec(0.0,n),n)),
        _xc{x},
        _c1{n*n/(n*n-1.0)} 
    {
    	for (size_t i = 0; i < n; ++i) {
    		_P[i][i] = val;
    	}
    }

    ell(const Vec& r, const Vec& x) :
        n{x.size()},
        _P(Mat(Vec(0.0,n),n)),
        _xc{x},
        _c1{n*n/(n*n-1.0)} 
    {
        for (size_t i = 0; i < n; ++i) {
    		_P[i][i] = r[i];
    	}
    }

	Vec& xc() { return _xc; }
	
    double update(const Vec& g) { //  central cut
        auto Pg = _P * g;
        double tsq = (g*Pg).sum();
        double rho = 1.0/(n+1);
        double tau = sqrt(tsq);
        _xc -= (rho/tau)*Pg;
        update_P(2*rho/tsq, _c1, Pg);
        return tau;
    }

    std::tuple<int, double>
    update(const Vec& g, double beta) { //  deep cut
        auto Pg = _P * g;
        double tsq = (g*Pg).sum();
        double tau = sqrt(tsq);

        if (beta > tau) // no sol'n
        	return std::make_tuple(1, tau); 
        if (n*beta < -tau) // no effect
        	return std::make_tuple(3, tau); 

        double alpha = beta/tau;
        double rho = (1+n*alpha)/(n+1);
        double sigma = 2*rho/(1+alpha);
        double delta = _c1*(1-alpha*alpha);
        _xc -= (rho/tau)*Pg;
        update_P(sigma/tsq, delta, Pg);
        return std::make_tuple(0, tau);
    }
        
        
    auto
    update(const Vec& g, const Vec& beta) { // parallel or deep cut
        auto Pg = _P * g;
        double tsq = (g*Pg).sum();
        double tau = sqrt(tsq);
       	auto alpha = beta/tau;

        if (alpha[0] > 1) // no sol'n
        	return std::make_tuple(1, tau); 

        double rho, sigma, delta;

        if (alpha.size() == 1 || alpha[1] >= 1.0) { // deep cut
        	double a0 = alpha[0];
            if (n*a0 < -1.0) // no effect
            	return std::make_tuple(3, tau); 
            rho = (1+n*a0)/(n+1);
            sigma = 2*rho/(1+a0);
            delta = _c1*(1-a0*a0);
        } else { // parallel cut
            double aprod = alpha[0] * alpha[1];
            if (n*aprod < -1.0) // no effect
            	return std::make_tuple(3, tau); 
            auto asq = alpha * alpha;
            double asum = alpha[0] + alpha[1];
            double asqdiff = asq[1] - asq[0];
            double xi = sqrt(4*(1-asq[0])*(1-asq[1]) + (n*n)*asqdiff*asqdiff);
            sigma = (n + (2*(1 + aprod - xi/2)/(asum*asum)))/(n+1);
            rho = asum * sigma/2;
            delta = _c1*(1 - (asq[0] + asq[1] - xi/n)/2);
        }
        _xc = _xc - (rho/tau)*Pg;
        update_P(sigma/tsq, delta, Pg);
        return std::make_tuple(0, tau);
    }
}; // } ell



// -- Ellipsoid method for solving convex optimization problem
//
// input   
//         oracle        perform assessment on x0
//          E(P,xc)       ellipsoid containing x*
//         t             best-so-far optimal sol'n
//         max_it        maximum number of iterations
//         tol           error tolerance                  
//
// output  
//         x             solution vector
//         iter          number of iterations performed
template <class F>
auto ellipsoid_dc(F& access, ell& E, double t, int max_it, double tol) {
    using Vec = std::valarray<double>;
    Vec x_best = E.xc();
	double t1;
	int iter, flag=0, status;

	for (iter = 1; iter < max_it; ++iter) {
		double tau; 
    	auto info = access(E.xc(), t);
        Vec g = std::get<0>(info);
        auto h = std::get<1>(info);
        t1 = std::get<2>(info);
    	if (t != t1) { // best t obtained
        	flag = 1;
	    	t = t1;
        	x_best = E.xc();
    	}  
    	std::tie(status, tau) = E.update(g,h);
    	if (status == 1) break; 
    	if (tau < tol) { status = 2; break; }; // no more,
    }
    return std::make_tuple(x_best, t1, iter, flag, status);
} // END of ellipsoid_dc



template <class F>
auto ellipsoid_q(F& access, ell& E, double t, int max_it, double tol) {
    using Vec = std::valarray<double>;
    auto norm = [](const Vec& v) -> double {
        return sqrt((v*v).sum());
    };
    Vec x_last = E.xc();
    Vec x_best = E.xc();
    double t1;
	int iter=1, flag=0, status;
    int count = 20;
    
	for (; iter < max_it; ++iter) {
		double tau; 
    	auto info = access(E.xc(), t);
        Vec g = std::get<0>(info);
        auto h = std::get<1>(info);
        t1 = std::get<2>(info);
        Vec x = std::get<3>(info);
        auto loop = std::get<4>(info);
        if (loop == 1) {
            h += (g*(x - E.xc())).sum();
        }

    	if (t != t1) { // best t obtained
        	flag = 1;
	    	t = t1;
        	x_best = E.xc();
    	}  
    	std::tie(status, tau) = E.update(g,h);
        
        if (status == 1) break; 
        else {
            if (status == 3) { // retry 20 times
                --count;
                if (count == 0) {
                    if (flag == 0) x_best = x;	  
	                break; 
                }
                continue;
            }
        }
    	if (tau < tol) { status = 2; break; } // no more,
        if (norm(x_last - E.xc()) < 1e-8) { 
            status = 4; 
            break; 
        }
        
        x_last = E.xc();  
        count = 20; // restart the count
    }
    
    return std::make_tuple(x_best, t1, iter, flag, status);
} // END of ellipsoid_q


/*---------------------------------------------------------------------*/
class profit_oracle
{
private:
    using Vec = std::valarray<double>;

	double _log_pA;
	double _log_k;
	Vec _v;
    Vec _a;

public:
	profit_oracle(double p, double A, double alpha, double beta, 
                        double v1, double v2, double k) :
		_log_pA{log(p*A)},
		_log_k{log(k)},
		_v{v1, v2},
		_a{alpha, beta}
	{}
		
	//std::tuple<Vec, double, double>
	auto operator()(const Vec& y, double t) const {
		double fj = y[0] - _log_k; // constraint
		if (fj > 0) {
			return std::make_tuple(Vec{1, 0}, fj, t);
		}
			
		double log_Cobb = _log_pA + (_a*y).sum();
		Vec x = exp(y);
		double te = t + (_v*x).sum();
		fj = log(te) - log_Cobb;
		if (fj < 0) {
			t = exp(log_Cobb) - (_v*x).sum();
			te = t + (_v*x).sum();
			fj = 0;
		}
		Vec g = (_v * x)/te - _a;		
		return std::make_tuple(g, fj, t);	
	}
};

class profit_q_oracle : public profit_oracle
{
    using Vec = std::valarray<double>;

public:
    profit_q_oracle(double p, double A, double alpha, double beta, 
                    double v1, double v2, double k) :
		profit_oracle(p, A, alpha, beta, v1, v2, k) {}
		
	//function [g, fj, t, y, discr] = 
    auto operator()(Vec y, double t) {
        Vec g;
        double fj;
            
		Vec x = y.apply( [](double n)->double {
                    return round(exp(n));} );
		y = log(x);
		int discr = 1;
		std::tie(g, fj, t) = profit_oracle::operator()(y, t);
        return std::make_tuple(g, fj, t, y, discr);
    }
};

/*---------------------------------------------------------------------*/
#include <iostream>
int main()
{
    using Vec = std::valarray<double>;
    
    double p = 20;
    double A = 40;
    double alpha = 0.1;
    double beta = 0.4;
    double v1 = 10;
    double v2 = 35;
    double k = 30.5;

    Vec y0 = {0, 0}; // initial x0
    double Ae = 100; // initial ellipsoid (sphere)

    ell E(Ae, y0);
    profit_oracle P(p, A, alpha, beta, v1, v2, k);
    
    Vec yb1;
    double fb;
    int iter, flag, status;
    std::tie(yb1, fb, iter, flag, status) = ellipsoid_dc(P, E, 0, 200, 1e-4);
    std::cout << fb << ", " << iter << "\n";

    ell E2(Ae, y0);
    profit_q_oracle P2(p, A, alpha, beta, v1, v2, k);
    std::tie(yb1, fb, iter, flag, status) = ellipsoid_q(P2, E2, 0, 200, 1e-4);
    std::cout << fb << ", " << iter << "\n";
    
}