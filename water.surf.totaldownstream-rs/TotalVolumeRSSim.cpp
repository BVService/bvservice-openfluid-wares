/**
  \file TotalVolumeRSSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.totalvolume-rs")

DECLARE_NAME("water.surf.totalvolume-rs");
DECLARE_DESCRIPTION("Compute the total volume for RS");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");


// Variables
DECLARE_REQUIRED_VAR("water.surf.Q.downstream-rs","RS","outflow at the outlet of the RS","m3/s");
DECLARE_PRODUCED_VAR("water.surf.V.total-rs","RS","Total volume at the outlet of the RS","m3");

// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class TotalVolumeRSSimulator : public openfluid::ware::PluggableSimulator
{
  private:

    openfluid::core::IDDoubleMap m_TotalValue;

  public:


    TotalVolumeRSSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~TotalVolumeRSSimulator()
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

      int ID;
      openfluid::core::Unit* RS;
      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS )
      {
        OPENFLUID_InitializeVariable(RS,"water.surf.V.total-rs",0.0);
        ID=RS->getID();
        m_TotalValue[ID]=0.0;

      }
      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {
      int ID;
      openfluid::core::Unit* RS;
      openfluid::core::DoubleValue CurrentValue;

      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS)
      {

        OPENFLUID_GetVariable(RS,"water.surf.Q.downstream-rs",CurrentValue);
        ID=RS->getID();

        m_TotalValue[ID]=CurrentValue*OPENFLUID_GetDefaultDeltaT() + m_TotalValue[ID];

        if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
          OPENFLUID_AppendVariable(RS,"water.surf.V.total-rs",m_TotalValue[ID]);

      }

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


DEFINE_SIMULATOR_CLASS(TotalVolumeRSSimulator);

