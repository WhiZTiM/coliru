namespace tlm
{
   namespace tlm_base_protocol_types
   {
      struct tlm_payload_type;
   }
}

namespace sc_core
{
   struct sc_time;
}

template<typename MOD>
void foo()
{
   typedef void (MOD::*b_transport_cb_type)(tlm::tlm_base_protocol_types::tlm_payload_type&, sc_core::sc_time&) __attribute__((unused));
   return;
}

int main()
{
   return 0;
}