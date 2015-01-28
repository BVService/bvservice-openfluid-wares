/**
  \file OverSim.cpp
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

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");

    
  
// Attributes : Un attribut est fixe
  DECLARE_REQUIRED_ATTRIBUTE("height","RS","","m")

  
// Variables : Une variable, comme son nom l'indique, est variable
  DECLARE_REQUIRED_VAR("water.surf.H.level-rs","RS","","m")
  DECLARE_PRODUCED_VAR("water.surf.H.overflow-rs","RS","","m")

  
  
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class OverSimulator : public openfluid::ware::PluggableSimulator
{
  private:
	// On declare un attribut privé, il ne sera disponible que pour cette simulation
	openfluid::core::IDDoubleMap m_MaxValue; // A noter, c'est un attribut map (tableau deux colonnes)
  
  public:

  
    OverSimulator(): PluggableSimulator()
    {


    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~OverSimulator()
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
  
    // InitializeRun s'execute a chaque pas de temps
    openfluid::base::SchedulingRequest initializeRun()
    {  
    	int ID; // declare ID
    	openfluid::core::Unit* RS; // Doit etre declare ici si utilise, ce qui est le cas.
    	OPENFLUID_UNITS_ORDERED_LOOP("RS",RS ) // Quel type d'entité (1), la valeur dans le pointeur défini plus haut (2)
    	{
    		OPENFLUID_InitializeVariable(RS,"water.surf.H.overflow-rs",0.0); // La variable produite doit tjr etre initialisee
    		ID=RS->getID(); // cree ID
    		m_MaxValue[ID]=0.0; // Chaque valeur de m_LastValue correspondant a l'ID de la map est initialise

    	}

      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {
    	// Pointeur sur une RS
    	int ID;
    	openfluid::core::Unit* RS;
    	openfluid::core::DoubleValue LevelValue;
    	openfluid::core::DoubleValue Height;

    	// On fait une boucle sur les RS (for)
    	OPENFLUID_UNITS_ORDERED_LOOP("RS",RS ) // Type d'entité (1), Valeur dans le pointeur défini plus haut (2)
    	{
    		// Pour chaque RS on va recuperer la valeur produite par le sim precedent cad water.surf.H.level-rs
    		// Pour recuperer cette variable on utilise la methode getvariable : sur quelle entite (ici le pointeur de RS), la variable a recuperer (water.surf.H.level_rs), dans quoi on met cette valeur (ici dans un double)
    		// POur le faire on a du definir une openfluid::core::DoubleValue,LevelValue)
    		OPENFLUID_GetVariable(RS,"water.surf.H.level-rs",LevelValue);
    		ID=RS->getID();


    		if (LevelValue > m_MaxValue[ID]) // Si la derniere valeur est superieur a la valeur actuelle on actualise m_LastValue
    			m_MaxValue[ID]=LevelValue;


    		if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
    		{

    		  OPENFLUID_GetAttribute(RS,"height",Height); // On recupere sur l'entite height, et on met ça dans l'entite Height

    		  openfluid::core::DoubleValue DiffValue = 0.0; // Declare
    		  if (m_MaxValue[ID]>Height) // Si m_LastValue est superieure a la hauteur on cree DiffValue qui est la difference entre ces deux valeurs
    			  DiffValue=m_MaxValue[ID]-Height; // Fait la difference

    	       OPENFLUID_AppendVariable(RS,"water.surf.H.overflow-rs",DiffValue); // Cree
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


DEFINE_SIMULATOR_CLASS(OverSimulator);

