/**
  \file totalstream-rs.cpp
*/


/*
<sim2doc>

</sim2doc>
*/


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("totalstream-rs")

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("","");

    
  
  
// Variables
  DECLARE_REQUIRED_VAR("water.surf.V.downstream-totalrs","RS","","m3")

  
  
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class totalstreamrssimulator : public openfluid::ware::PluggableSimulator
{
  private:

  
  public:

  
    totalstreamrssimulator(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~totalstreamrssimulator()
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


DEFINE_SIMULATOR_CLASS(totalstreamrssimulator);

