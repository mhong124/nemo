/*
 * plummer4.c:  (spherical) plummer potential, derived from plummer.c
 * 		but explicitely written for single precision 
 *		potential interface 
 *			13-sep-01  this test		Peter Teuben
 *		
 *
 */

/*CTEX
 *	{\bf potname=plummer
 *       potpars={\it $\Omega,M,R$}}
 *
 *  Plummer potential (BT, pp.42, eq. 2.47, see also MNRAS 71, 460 (1911))
 *
 * $$
 *    \Phi = -  {  M  \over
 *                    {   {(r_c^2 + r^2)}^{1/2} }  }
 * $$
 */                     
  
#include <stdinc.h>
#include <vectmath.h>	
 
local float omega = 0.0;
local float plummer_mass = 1.0;
local float plummer_radius = 1.0;	/* radius=0 gives point mass */

local float r2;

void inipotential (int *npar, double *par, string name)
{
    int n;

    n = *npar;
    if (n>0) omega = par[0];
    if (n>1) plummer_mass = par[1];
    if (n>2) plummer_radius = par[2];
    if (n>3) warning("plummer: npar=%d only 3 parameters accepted",n);

#if defined(TWODIM)
    dprintf (1,"INIPOTENTIAL Plummer4: [2d opt]\n");
#else
    dprintf (1,"INIPOTENTIAL Plummer4: [3d version]\n");
#endif
    dprintf (1,"  Parameters : Pattern Speed = %f\n",omega);
    dprintf (1,"  mass, radius = %f %f \n",plummer_mass,plummer_radius);
	
    r2 = sqr(plummer_radius);
    par[0] = omega;
}

void potential (int *ndim,float *pos,float *acc,float *pot,float *time)
{
    register float tmp;

#if defined(TWODIM)
    /* TWODIM: Saves two MUL's - hardly making any difference... */
    tmp = 1.0/(r2 + pos[0]*pos[0] + pos[1]*pos[1]);
    *pot = -sqrt(tmp);
    tmp *= (*pot) * plummer_mass;
    *pot *= plummer_mass;
    acc[0] = tmp*pos[0];
    acc[1] = tmp*pos[1];
    acc[2] = 0.0;
#else
    tmp = 1.0/(r2 + pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
    *pot = -sqrt(tmp);
    tmp *= (*pot) * plummer_mass;
    *pot *= plummer_mass;
    acc[0] = tmp*pos[0];
    acc[1] = tmp*pos[1];
    acc[2] = tmp*pos[2];

#endif
}
