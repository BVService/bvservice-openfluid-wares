/**
  \file TotalVolumeSUSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.totalvolume-su")

DECLARE_NAME("water.surf.totalvolume-su");
DECLARE_DESCRIPTION("Compute the total volume for SU");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");


DECLARE_REQUIRED_VAR("water.surf.Q.downstream-su","SU","outflow at the outlet of the SU","m3/s");
DECLARE_PRODUCED_VAR("water.surf.V.total-su","SU","Total volume at the outlet of the SU","m3");

// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class TotalVolumeSUSimulator : public openfluid::ware::PluggableSimulator
{
  private:

    openfluid::core::IDDoubleMap m_TotalValue;

  public:


    TotalVolumeSUSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~TotalVolumeSUSimulator()
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
        OPENFLUID_InitializeVariable(SU,"water.surf.V.total-su",0.0);
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
        OPENFLUID_GetVariable(SU,"water.surf.Q.downstream-su",CurrentValue);
        ID=SU->getID();

        m_TotalValue[ID]=CurrentValue*OPENFLUID_GetDefaultDeltaT() + m_TotalValue[ID];

        if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
          OPENFLUID_AppendVariable(SU,"water.surf.V.total-su",m_TotalValue[ID]);

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


DEFINE_SIMULATOR_CLASS(TotalVolumeSUSimulator);

