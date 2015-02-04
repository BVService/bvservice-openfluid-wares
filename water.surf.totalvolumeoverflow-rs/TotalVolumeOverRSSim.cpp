/**
  \file TotalVolumeOverRSSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.totalvolumeoverflow-rs")

DECLARE_NAME("water.surf.totalvolumeoverflow-rs");
DECLARE_DESCRIPTION("Compute the total volume overflow for RS");

DECLARE_VERSION("15.02");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("water");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");



// Attributes
DECLARE_REQUIRED_ATTRIBUTE("height","RS","height of the RS","m")
DECLARE_REQUIRED_ATTRIBUTE("width","RS","width of the RS","m")
DECLARE_REQUIRED_ATTRIBUTE("length","RS","length of the RS","m")


// Variables
DECLARE_REQUIRED_VAR("water.surf.H.level-rs","RS","water height at the outlet of the RS","m");
DECLARE_PRODUCED_VAR("water.surf.V.overflow-rs","RS","total volume overflow at the outlet of the RS","m3")




// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class VolOverFlowRSSimulator : public openfluid::ware::PluggableSimulator
{
  private:
    openfluid::core::IDDoubleMap m_VolumeValue;

  public:


    VolOverFlowRSSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~VolOverFlowRSSimulator()
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
        OPENFLUID_InitializeVariable(RS,"water.surf.V.overflow-rs",0.0);
        ID=RS->getID();
        m_VolumeValue[ID]=0.0;

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
      openfluid::core::DoubleValue Width;
      openfluid::core::DoubleValue Length;


      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS )
      {
        OPENFLUID_GetVariable(RS,"water.surf.H.level-rs",LevelValue);
        OPENFLUID_GetAttribute(RS,"height",Height);
        OPENFLUID_GetAttribute(RS,"width",Width);
        OPENFLUID_GetAttribute(RS,"length",Length);
        ID=RS->getID();

        if (LevelValue > Height)
        {
          openfluid::core::DoubleValue Volume;
          Volume=(LevelValue-Height) *Length * Width;
          m_VolumeValue[ID]=m_VolumeValue[ID]+Volume;
        }

        if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
          OPENFLUID_AppendVariable(RS,"water.surf.V.overflow-rs",m_VolumeValue[ID]);

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


DEFINE_SIMULATOR_CLASS(VolOverFlowRSSimulator);

