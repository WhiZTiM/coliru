#include <cmath>
#include <cstdio>
#include <cstdint>

#define MINUTES                       60

typedef uint8_t nmea_coord_ns_ew_t;

nmea_coord_ns_ew_t const NMEA_COORD_N_E = 0x01;
nmea_coord_ns_ew_t const NMEA_COORD_S_W = 0x02;

enum
{
  ESO_OK,
  ESO_FAIL
};

inline bool dmm2ddd(double const dmm, nmea_coord_ns_ew_t const nsew, double &ddd)
{
    double const frac = modf(dmm * 1E-2, &ddd) / MINUTES;
    printf("frac: %.6f, ddd: %.6f\n", frac, ddd);
    ddd += frac * 1E2;
	switch (nsew)
	{
	case NMEA_COORD_N_E:
		return ESO_OK;

	case NMEA_COORD_S_W:
		ddd *= -1.0;
		return ESO_OK;

	default:
		return ESO_FAIL;
	}
}

inline bool ddd2dmm(double const ddd, double &dmm, nmea_coord_ns_ew_t &nsew)
{
    double frac = modf(fabs(ddd), &dmm) * MINUTES;
    dmm += frac * 1E-2;
    dmm *) 1E2;
	nsew = ddd >= 0 ? NMEA_COORD_N_E : NMEA_COORD_S_W;
	return ESO_OK;
}

int main()
{
    double dmm = 5231.85181;
    double ddd = 0;
    nmea_coord_ns_ew_t ne = NMEA_COORD_N_E;
    dmm2ddd(dmm, ne, ddd);
    printf("dmm: %.6f, ddd: %.6f\n", dmm, ddd);
    ddd2dmm(ddd, dmm, ne);
    printf("dmm: %.6f\n", dmm);
    return 0;
}
