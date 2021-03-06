/**
  \file StatUpperRSSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("stat.upper.rs")

DECLARE_NAME("stat.upper.rs");
DECLARE_DESCRIPTION("Compute geometric indicators on RS");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("geometric");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");



// Attributes
DECLARE_REQUIRED_ATTRIBUTE("length","RS","Length of the RS","m")


// Variables
DECLARE_PRODUCED_VAR("stat.upper.length","RS","Total length of upstream RS","m")
DECLARE_PRODUCED_VAR("stat.upper.number","RS","Number of upstream RS","")



// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class StatUpperRSSimulator : public openfluid::ware::PluggableSimulator
{
  private:
    // Map container to store values
    openfluid::core::IDDoubleMap m_SumLength;
    openfluid::core::IDDoubleMap m_NumEntities;

  public:


    StatUpperRSSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~StatUpperRSSimulator()
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
      // Initialize variables for each RS
      openfluid::core::Unit* RS;
      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS )
      {
        OPENFLUID_InitializeVariable(RS,"stat.upper.length",0.0);
        OPENFLUID_InitializeVariable(RS,"stat.upper.number",0.0);

      }

      // Variables are computed here
      OPENFLUID_UNITS_ORDERED_LOOP("RS",RS)
      {

        if (RS->getToUnits("RS") == NULL) // Call the recursive method only for RS leafs
          computeRecursive("RS","length",RS,m_SumLength,m_NumEntities);
      }

      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {
      // test if it is the last step
      if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
      {
        openfluid::core::Unit* RS;
        int ID;
        OPENFLUID_UNITS_ORDERED_LOOP("RS",RS)
        {
          ID=RS->getID();
          OPENFLUID_AppendVariable(RS,"stat.upper.length",m_SumLength[ID]);
          OPENFLUID_AppendVariable(RS,"stat.upper.number",m_NumEntities[ID]);
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
                          const openfluid::core::AttributeName_t& AttrName,
                          openfluid::core::Unit* U,
                          openfluid::core::IDDoubleMap& MapLength,
                          openfluid::core::IDDoubleMap& MapEntities)
    {
      // postfixed depth-first search to process leafs first and go back to root

      openfluid::core::UnitsPtrList_t* UpperUnits = U->getFromUnits(UnitsClass);
      openfluid::core::Unit* UU = NULL;


      // --- go to leafs recursively
      if (UpperUnits != NULL) //if UpperUnits not empty, upstream Units are present
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU) // loop for each upstream unit
        {
          if (!(MapLength.find(UU->getID()) != MapLength.end()))
            computeRecursive(UnitsClass,AttrName,UU,MapLength,MapEntities); // recursive method for upstream unit
        }
      }


      // --- processing of the current unit
      double UpperSum = 0.0;
      double Val;
      double UpperNum=0.0;

      // summ attributes of upper processed units (if exist)
      if (UpperUnits != NULL)
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU)
        {
          UpperSum = UpperSum + MapLength[UU->getID()];
          UpperNum= UpperNum+ MapEntities[UU->getID()];
        }
      }

      // add current unit attribute
      OPENFLUID_GetAttribute(U,AttrName,Val);
      UpperSum = UpperSum + Val;
      MapLength[U->getID()] = UpperSum;
      UpperNum = UpperNum + 1;
      MapEntities[U->getID()] = UpperNum;

    }

};


// =====================================================================
// =====================================================================


DEFINE_SIMULATOR_CLASS(StatUpperRSSimulator);

