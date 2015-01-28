/**
  \file totaldownstream-rs.cpp
*/


/*
<sim2doc>

</sim2doc>
*/


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("totaldownstream-rs-simulator")

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("JV","v.jonath@live.fr");

    
  // Variables
    DECLARE_REQUIRED_VAR("water.surf.Q.downstream-rs","RS","","m3/s")
    DECLARE_PRODUCED_VAR("water.surf.V.downstream-totalrs","RS","","m3")  // Attention si declare une variable produite il faut ensuite la produire sinon ca bug
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class totaldownstreamrssimulator : public openfluid::ware::PluggableSimulator
{
  private:
	// On declare un attribut privé, il ne sera disponible que pour cette simulation
	openfluid::core::IDDoubleMap m_LastValue; // A noter, c'est un attribut map (tableau deux colonnes)
  
  public:

  
    totaldownstreamrssimulator(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~totaldownstreamrssimulator()
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
    	// ::: On initialise m_LastValue pour chaque pas de temps a venir
    	int ID; // declare ID
    	openfluid::core::Unit* RS; // Doit etre declare ici si utilise, ce qui est le cas.
    	OPENFLUID_UNITS_ORDERED_LOOP("RS",RS ) // Quel type d'entité (1), la valeur dans le pointeur défini plus haut (2)
    	    	{
    	OPENFLUID_InitializeVariable(RS,"water.surf.V.downstream-totalrs",0.0); // La variable produite doit tjr etre initialisee
    	ID=RS->getID(); // cree ID
    	m_LastValue[ID]=0.0; // Chaque valeur de m_LastValue correspondant a l'ID de la map est initialise

    	    	}
    	return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {


		//std::cout << OPENFLUID_GetCurrentTimeIndex() << std::endl;

    	// Pointeur sur une RS
    	int ID;
    	openfluid::core::Unit* RS;
    	openfluid::core::DoubleValue MaxValue;


    	// On fait une boucle sur les RS (for)
    	OPENFLUID_UNITS_ORDERED_LOOP("RS",RS) // Type d'entité (1), Valeur dans le pointeur défini plus haut (2)
    	{
    		// Pour chaque RS on va recuperer la valeur produite par le sim precedent cad water.surf.H.level-rs
    		// Pour recuperer cette variable on utilise la methode getvariable : sur quelle entite (ici le pointeur de RS), la variable a recuperer (water.surf.H.level_rs), dans quoi on met cette valeur (ici dans un double)
    		// POur le faire on a du definir une openfluid::core::DoubleValue,MaxValue)
    		OPENFLUID_GetVariable(RS,"water.surf.Q.downstream-rs",MaxValue); // recquired var
    		ID=RS->getID();

    		m_LastValue[ID]=MaxValue*OPENFLUID_GetDefaultDeltaT() + m_LastValue[ID];
    		//OPENFLUID_Logger.getFile() << OPENFLUID_GetCurrentTimeIndex() << " " << m_LastValue[ID] << "\n";

    		OPENFLUID_AppendVariable(RS,"water.surf.V.downstream-totalrs",m_LastValue[ID]);

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


DEFINE_SIMULATOR_CLASS(totaldownstreamrssimulator);

