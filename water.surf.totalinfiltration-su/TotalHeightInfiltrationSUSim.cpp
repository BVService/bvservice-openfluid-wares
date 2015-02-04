/**
  \file TotalHeightInfiltrationSUSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.totalinfiltration-su")

DECLARE_NAME("water.surf.totalinfiltration-su");
DECLARE_DESCRIPTION("Compute the total height infiltration for SU");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");



// Variables
DECLARE_REQUIRED_VAR("water.surf.H.infiltration","SU","water infiltration height through the surface of SU","m");
DECLARE_PRODUCED_VAR("water.surf.H.totalinfiltration-su","SU","total water infiltration height through the surface of SU","m");




// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class TotalHInfilSUSimulator : public openfluid::ware::PluggableSimulator
{
  private:
    openfluid::core::IDDoubleMap m_TotalValue;

  public:


    TotalHInfilSUSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~TotalHInfilSUSimulator()
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
        OPENFLUID_InitializeVariable(SU,"water.surf.H.totalinfiltration-su",0.0);

        ID=SU->getID();
        m_TotalValue[ID]=0.0;

      }

      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {
      int ID;
      openfluid::core::Unit* SU;
      openfluid::core::DoubleValue CurrentValue;


      OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
      {
        OPENFLUID_GetVariable(SU,"water.surf.H.infiltration",CurrentValue);
        ID=SU->getID();

        m_TotalValue[ID]= CurrentValue+m_TotalValue[ID];

        if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
          OPENFLUID_AppendVariable(SU,"water.surf.H.totalinfiltration-su",m_TotalValue[ID]);

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


DEFINE_SIMULATOR_CLASS(TotalHInfilSUSimulator);

