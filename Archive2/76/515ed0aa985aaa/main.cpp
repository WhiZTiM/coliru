#define SPEEDUP_IO

#include <climits>

#ifdef SPEEDUP_IO
  #include <stdio.h>
  #define GET_NEXT_INPUT(var) do {scanf ("%u", &var);} while (false)
  #define PUT_OUT(var)        do {printf("%u",  var);} while (false)
  #define INIT_IO()           /* do nothing */
#else
  #include <iostream>
  #define GET_NEXT_INPUT(var) do {std::cin  >> var;} while (false)
  #define PUT_OUT(var)        do {std::cout << var;} while (false)
  #define INIT_IO()           do {std::ios::sync_with_stdio(false);} while (false) /* disable syncing of iostream with stdio for performance boost */
#endif

typedef unsigned int u32;

enum { NR_OF_TICKET_CATEGORIES = 3u };

struct Ticket
{
  u32 m_coveredDistance;
  u32 m_price;
};

struct Station
{
  u32 m_distanceToSource;
  u32 m_travelCost;
  Station(u32 _distance = 0, u32 _travelCost = (u32)INT_MAX) : m_distanceToSource(_distance), m_travelCost(_travelCost) {}
};

static u32 getCostByDistance(u32 _distance, Ticket const * _tickets)
{
  u32 v_ret = (u32)INT_MAX;
  for (u32 v_i = 0; v_i < (u32)NR_OF_TICKET_CATEGORIES; v_i++)
  {
    if (_distance <= _tickets[v_i].m_coveredDistance)
    {
      v_ret = _tickets[v_i].m_price;
      break;
    }
  }
  return v_ret;
}

int main()
{
  INIT_IO();
  Ticket v_aTicketTypes[NR_OF_TICKET_CATEGORIES];
  u32 v_sourceStationIndex, v_destStationIndex, v_distanceSourceToRoot = 0, v_maxDistance = 0;
  for (u32 v_i = 0; v_i < (u32)NR_OF_TICKET_CATEGORIES; v_i++)
  {
    GET_NEXT_INPUT(v_aTicketTypes[v_i].m_coveredDistance);
    v_maxDistance =  (v_maxDistance < v_aTicketTypes[v_i].m_coveredDistance) ? v_aTicketTypes[v_i].m_coveredDistance : v_maxDistance;
  }
  for (u32 v_i = 0; v_i < (u32)NR_OF_TICKET_CATEGORIES; v_i++)
  {
    GET_NEXT_INPUT(v_aTicketTypes[v_i].m_price);
  }

  GET_NEXT_INPUT(v_sourceStationIndex); //extract and forfeit number of stations, because we don't care.
  GET_NEXT_INPUT(v_sourceStationIndex);
  v_sourceStationIndex--; /* decrement by 1 (input index range is [1..nrOfStations]) */
  GET_NEXT_INPUT(v_destStationIndex);
  v_destStationIndex--; /* decrement by 1 (input index range is [1..nrOfStations]) */

  for (u32 v_i = 0; v_i < v_sourceStationIndex; v_i++) // pop all distances up until source-station (including)
  {
    GET_NEXT_INPUT(v_distanceSourceToRoot);
  }
  Station v_aStationRingBuffer[v_maxDistance +1u]; /* allocate array for use as ring buffer */
  v_aStationRingBuffer[0] = Station(0, 0); /* init source station */
  u32 v_ringBufferIndex = 0;

  for (u32 v_i = v_sourceStationIndex; v_i < v_destStationIndex; v_i++)
  {
    v_ringBufferIndex = (v_ringBufferIndex + 1u) % (v_maxDistance + 1u);

    u32 v_distanceToRoot;
    GET_NEXT_INPUT(v_distanceToRoot);
    v_aStationRingBuffer[v_ringBufferIndex].m_distanceToSource = (v_distanceToRoot - v_distanceSourceToRoot); /* set distance */
    v_aStationRingBuffer[v_ringBufferIndex].m_travelCost = (u32)INT_MAX; /* reset cost */

    for (u32 v_seekIndex = (v_ringBufferIndex + v_maxDistance) % (v_maxDistance + 1u); v_seekIndex != v_ringBufferIndex; v_seekIndex = (v_seekIndex + v_maxDistance) % (v_maxDistance + 1u))
    {
      u32 const c_distanceToPriorStation     = v_aStationRingBuffer[v_ringBufferIndex].m_distanceToSource - v_aStationRingBuffer[v_seekIndex].m_distanceToSource;
      u32 const c_travelCostFromPriorStation = v_aStationRingBuffer[v_seekIndex].m_travelCost + getCostByDistance(c_distanceToPriorStation, v_aTicketTypes);
      if (c_travelCostFromPriorStation < v_aStationRingBuffer[v_ringBufferIndex].m_travelCost)
      {
        v_aStationRingBuffer[v_ringBufferIndex].m_travelCost = c_travelCostFromPriorStation;
      }
      else
      {
        if (c_travelCostFromPriorStation >= (u32)INT_MAX)
        {
          break;
        }
      }
    }
  }
  PUT_OUT(v_aStationRingBuffer[v_ringBufferIndex].m_travelCost);
  return 0;
}
