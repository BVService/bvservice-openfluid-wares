/**
  \file TotalVolumeContribSUSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.totalvolumecontrib-su")

DECLARE_NAME("water.surf.totalvolumecontrib-su");
DECLARE_DESCRIPTION("Compute the total contributory volume for SU connected to RS");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");

// Variables
DECLARE_REQUIRED_VAR("water.surf.Q.downstream-rs","RS","outflow at the outlet of the RS","m3/s");
DECLARE_REQUIRED_VAR("water.surf.Q.downstream-su","SU","outflow at the outlet of the SU","m3/s");
DECLARE_PRODUCED_VAR("water.surf.V.contribDownstream-su","SU","total contributory volume of the SU","m3")




// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class TotalVolumeContribSUSimulator : public openfluid::ware::PluggableSimulator
{
  private:
    openfluid::core::IDDoubleMap m_VolumeValue;

  public:


    TotalVolumeContribSUSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~TotalVolumeContribSUSimulator()
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
        OPENFLUID_InitializeVariable(SU,"water.surf.V.contribDownstream-su",0.0);
        ID=SU->getID();
        m_VolumeValue[ID]=0.0;
      }

      return DefaultDeltaT();

    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {
      openfluid::core::Unit* RS;

      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS )
      computeRecursive("SU",RS);


      if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
      {
        openfluid::core::Unit* SU;
        int ID;
        OPENFLUID_UNITS_ORDERED_LOOP("SU",SU )
        {
          ID=SU->getID();
          OPENFLUID_AppendVariable(SU,"water.surf.V.contribDownstream-su",m_VolumeValue[ID]);
        }
      }
      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    void finalizeRun()
    {


    }


    // =====================================================================
    // =====================================================================


    void computeRecursive(const openfluid::core::UnitClass_t& UnitsClass,
                          openfluid::core::Unit* U	)
    {
      // postfixed depth-first search to process leafs first and go back to root

      openfluid::core::UnitsPtrList_t* UpperUnits = U->getFromUnits(UnitsClass);

      openfluid::core::DoubleValue FlowSU=0.0;

      if (U->getClass()=="SU")
        OPENFLUID_GetVariable(U,"water.surf.Q.downstream-su",FlowSU);


      openfluid::core::Unit* UU = NULL;
      if (UpperUnits != NULL)
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU)
				{
          openfluid::core::DoubleValue FlowUnitFrom=0.0;
          OPENFLUID_GetVariable(UU,"water.surf.Q.downstream-su",FlowUnitFrom);
          FlowSU=FlowSU-FlowUnitFrom;

          computeRecursive("SU",UU);
				}
      }
      if (U->getClass()=="SU")
      {
        int ID;
        ID=U->getID();
        m_VolumeValue[ID]=m_VolumeValue[ID]+FlowSU;
      }

    }


};


// =====================================================================
// =====================================================================


DEFINE_SIMULATOR_CLASS(TotalVolumeContribSUSimulator);

