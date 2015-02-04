/**
  \file MaxHeightOverRSSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.overflow-rs")

DECLARE_NAME("water.surf.overflow-rs");
DECLARE_DESCRIPTION("Compute the maximum height overflow for RS");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");

DECLARE_REQUIRED_ATTRIBUTE("height","RS","height of the RS","m")


DECLARE_REQUIRED_VAR("water.surf.H.level-rs","RS","water height at the outlet of the RS","m")
DECLARE_PRODUCED_VAR("water.surf.H.overflow-rs","RS","maximum water height overflow at the outlet of the RS","m")


// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class MaxHeightOverRSSimulator : public openfluid::ware::PluggableSimulator
{
  private:

    openfluid::core::IDDoubleMap m_MaxValue;

  public:


    MaxHeightOverRSSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~MaxHeightOverRSSimulator()
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
        OPENFLUID_InitializeVariable(RS,"water.surf.H.overflow-rs",0.0);
        ID=RS->getID();
        m_MaxValue[ID]=0.0;

      }

      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {

      int ID;
      openfluid::core::Unit* RS;
      openfluid::core::DoubleValue LevelValue;
      openfluid::core::DoubleValue Height;


      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS )
      {
        OPENFLUID_GetVariable(RS,"water.surf.H.level-rs",LevelValue);
        ID=RS->getID();

        if (LevelValue > m_MaxValue[ID])
          m_MaxValue[ID]=LevelValue;


        if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
        {

          OPENFLUID_GetAttribute(RS,"height",Height);

          openfluid::core::DoubleValue DiffValue = 0.0;
          if (m_MaxValue[ID]>Height)
            DiffValue=m_MaxValue[ID]-Height;

          OPENFLUID_AppendVariable(RS,"water.surf.H.overflow-rs",DiffValue);
        }
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


DEFINE_SIMULATOR_CLASS(MaxHeightOverRSSimulator);

