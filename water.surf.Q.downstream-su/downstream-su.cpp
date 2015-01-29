/**
  \file downstream-su.cpp
*/


/*
<sim2doc>

</sim2doc>
*/


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.Q.downstream-su")

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("JV","");

    
  
  
// Variables
  DECLARE_REQUIRED_VAR("water.surf.Q.downstream-su","SU","","m3")

  
  
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class downstreamsu : public openfluid::ware::PluggableSimulator
{
  private:

  
  public:

  
    downstreamsu(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~downstreamsu()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    void initParams(const openfluid::ware::WareParams_t& /*Params*/)
    {


    }


    // =====================================================================
    // =====================================================================
  
  
    void prepareData()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    void checkConsistency()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest initializeRun()
    {  
    
      
      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {


      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    void finalizeRun()
    {
  
  
    }

};


// =====================================================================
// =====================================================================


DEFINE_SIMULATOR_CLASS(downstreamsu);

