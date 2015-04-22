#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define XMIN 0.0
#define YMIN 0.0
#define XMAX 1.0
#define YMAX 1.0

int a;
int npart = a;          /* Number of particles   */
float dt = 1e-4;        /* Time step (1e-4)           */
float eps_lj = 1;       /* Strength for L-J (1)       */
float sig_lj = 1e-2;    /* Radius for L-J   (1e-2)    */
float T0 = 1;           /* Initial temperature (1)    */
float G = 1;            /* Gravitational strength (1) */

int init_particles(float* x, float* v)
{
    const int MAX_INIT_TIMES = 1000;
    
    float min_sig_r2 = sig_lj*sig_lj;
    
    for (int i = 0; i < npart; ++i) {
        float r2 = 0;

        /* Choose velocity components randomly from Normal distribution (0,T0) */
        double R = T0 * sqrt(-2*log(drand48()));
        double T = 2*M_PI*drand48();
        v[2*i+0] = (float) (R * cos(T));
        v[2*i+1] = (float) (R * sin(T));

        /* Choose new points through rejection sampling */
        for (int trial = 0; r2 < min_sig_r2 && trial < MAX_INIT_TIMES; ++trial) {
            x[2*i+0] = (float) drand48();
            x[2*i+1] = (float) drand48();
            for (int j = 0; j < i; ++j) {
                float dx = x[2*i+0]-x[2*j+0];
                float dy = x[2*i+1]-x[2*j+1];
                r2 = dx*dx + dy*dy;
                if (r2 < min_sig_r2)
                    break;
            }
        }

        /* If it reaches the limit of trails, return the current located number of particles */
        if (i > 0 && r2 < min_sig_r2) 
            return i;
    }
    return npart;
}

float compute_LJ_scalar(float r2, float eps, float sig2)
{
    if (r2 < 6.25*sig2) { /* r_cutoff = 2.5 sigma */
        float z = sig2/r2;
        float u = z*z*z;
        return 24*eps/r2 * u*(1-2*u);
    }
    return 0;
}

void leapfrog1(int n, float* x, float* v, float* a)
{
    for (int i = 0; i < n; ++i, x += 2, v += 2, a += 2) {
        v[0] += a[0]*dt/2;
        v[1] += a[1]*dt/2;
        x[0] += v[0]*dt;
        x[1] += v[1]*dt;
    }
}

void leapfrog2(int n, float* v, float* a)
{
    for (int i = 0; i < n; ++i, v += 2, a += 2) {
        v[0] += a[0]*dt/2;
        v[1] += a[1]*dt/2;
    }
}

static void reflect(float wall, float* x, float* v, float* a)
{
    *x = (2*wall-(*x));
    *v = -(*v);
    *a = -(*a);
}

void apply_reflect(int n, float* x, 
                   float* v, float* a)
{
    for (int i = 0; i < n; ++i, x += 2, v += 2, a += 2) {
        if (x[0] < XMIN) reflect(XMIN, x+0, v+0, a+0);
        if (x[0] > XMAX) reflect(XMAX, x+0, v+0, a+0);
        if (x[1] < YMIN) reflect(YMIN, x+1, v+1, a+1);
        if (x[1] > YMAX) reflect(YMAX, x+1, v+1, a+1);
    }
}

void force(int n, float* x, float* F)
{
    float g = G;
    float eps  = eps_lj;
    float sig  = sig_lj;
    float sig2 = sig*sig;
    
    /*  Gravity*/
    for (int i = 0; i < n; ++i) {
        F[2*i+0] = 0;
        F[2*i+1] = -g;
    }
    
    /* Interactions between particle (Lennard-Jones) */
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            float dx = x[2*j+0]-x[2*i+0];
            float dy = x[2*j+1]-x[2*i+1];
            float C_LJ = compute_LJ_scalar(dx*dx+dy*dy, eps, sig2);
            F[2*i+0] += (C_LJ*dx);
            F[2*i+1] += (C_LJ*dy);
            F[2*j+0] -= (C_LJ*dx);
            F[2*j+1] -= (C_LJ*dy);
        }
    }
}

void print_parts(float* x, float* v)
{
    for(int i=0;i<npart;i++){
        printf("%d. position:(%f, %f); velocity: (%f, %f)\n",i,x[2*i+0], x[2*i+1], v[2*i+0], v[2*i+1] );
    }
}

void run(int nrun, float* x, float* v)
{
    int n = npart;
    float* a = (float*) malloc(2*n*sizeof(float));
    memset(a, 0, 2*n*sizeof(float));
    
    force(n, x, a);
    for(int i=0;i<nrun;i++){    
        printf("%d run:\n",(i+1));
        leapfrog1(n, x, v, a);
        apply_reflect(n, x, v, a);
        force(n, x, a);
        leapfrog2(n, v, a);
        print_parts(x, v);
        printf("\n");
    }
    free(a);
}

int main(int argc, char *argv[])
{    
    int opt;
  while ((opt = getopt (argc, argv,"n:")) != -1)
  {
    switch (opt)
    {
      case 'n':
                a=atoi(optarg) ;
                break;
      
      default:
                a=2;
                break;
                
                
    }
  }

    int nrun = 100;
    
    float* x; //positions of the particles
    float* v; //velocities of the particles
    int init_npart;
    
    x = (float*)malloc(2*npart*sizeof(float));
    v = (float*)malloc(2*npart*sizeof(float));
    
    init_npart = init_particles(x, v);
    if (init_npart < npart){
        printf("Could not generate %d particles; trying %d\n",
        npart, init_npart);
        npart = init_npart;
    }
    
    run(nrun, x, v);
    print_parts(x, v);
    

    free(v);
    free(x);
    return 0;
}

