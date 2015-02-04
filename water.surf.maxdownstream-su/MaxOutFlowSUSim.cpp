/**
  \file MaxOutFlowSUSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.max-outflow-su")

DECLARE_NAME("water.surf.max-outflow-su");
DECLARE_DESCRIPTION("Compute the maximum output flow for SU");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");



// Variables
DECLARE_REQUIRED_VAR("water.surf.Q.downstream-su","SU","Output flow at the outlet of the SU","m3/s");
DECLARE_PRODUCED_VAR("water.surf.Q.maxdownstream-su","SU","Maximum output flow at the outlet of the SU","m3/s")



// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class MaxOutFlowSUSimulator : public openfluid::ware::PluggableSimulator
{
  private:
    openfluid::core::IDDoubleMap m_MaxValue;

  public:


    MaxOutFlowSUSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~MaxOutFlowSUSimulator()
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
      openfluid::core::Unit* SU;
      OPENFLUID_UNITS_ORDERED_LOOP("SU",SU )
      {
        OPENFLUID_InitializeVariable(SU,"water.surf.Q.maxdownstream-su",0.0);
        ID=SU->getID();
        m_MaxValue[ID]=0.0;

      }

      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {
      int ID;
      openfluid::core::Unit* SU;
      openfluid::core::DoubleValue LevelValue;

      OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
      {
        OPENFLUID_GetVariable(SU,"water.surf.Q.downstream-su",LevelValue);
        ID=SU->getID();

        if (LevelValue > m_MaxValue[ID])
          m_MaxValue[ID]=LevelValue;

        if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
          OPENFLUID_AppendVariable(SU,"water.surf.Q.maxdownstream-su",m_MaxValue[ID]);

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


DEFINE_SIMULATOR_CLASS(MaxOutFlowSUSimulator);

