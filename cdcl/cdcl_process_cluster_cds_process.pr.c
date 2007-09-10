/* Process model C form file: cdcl_process_cluster_cds_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char cdcl_process_cluster_cds_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 43ED18E5 43ED18E5 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>

#if defined (__cplusplus)
extern "C" {
#endif
FSM_EXT_DECS
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif


/* Header Block */

// Include files.					
#include	<oms_dist_support.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>

#include	"cdcl_biblio.h"
#include	"cdcl_gw_list_management.h"


//----------------------------------------------------------------------
//		     				Parameters		
//----------------------------------------------------------------------

#define		INFINITY					1000

#define		TIME_NETWORK_STABILIZED		60.0

//  Debug    
#define		BB_FLOODING_DEBUG			1			//=1 if the debug message must be printed
#define		TEST_DEBUG					1
#define		NORMAL_DEBUG				1
#define		STATS_DEBUG					1

#define		DEBUG_INSTANTANEOUS			0
#define		DEBUG_NETWORK_CTRL			0
#define		DEBUG_CPLEX					0
#define		DEBUG_CONVERGENCE			0


//Debug level
#define		LOW							0
#define		MEDIUM						1
#define		HIGH						2
#define		MAX							4

//	For automatic attribution of Addresses
#define		ADDR_RANDOM					0
#define		ADDR_WLAN					1
#define		ADDR_CONFIGURED				2
#define		ADDR_MAC_CDCL_FROM_NAME		3


//----------------------------------------------------------------------
//						TIMEOUTS + INTERVALLS
//----------------------------------------------------------------------

//	TIMEOUTS	
//Hello
#define		TIMEOUT_HELLO				3.01
//Cds
#define		TIMEOUT_RELAY_FATHER		2.01
#define		TIMEOUT_AP_HELLO			2.01
//Clusters
#define		TIMEOUT_CLUSTERHEAD			2.1
//Network
#define		TIMEOUT_ID					60
#define		TIMEOUT_ICI					2.0
#define		TIMEOUT_RELAYING			2.1

//	INTERVALLS
#define		INTERVALL_AP_HELLO			2.0
#define		INTERVALL_CLUSTERHEAD_HELLO	2.0
#define		INTERVALL_CDS_WU_LI_COMP	1.0
#define		INTERVALL_HELLO				4.0
#define		INTERVALL_FAST_HELLO		2.0	
#define		INTERVALL_UPDATE_TABLE		1.0

//I generate a figure of cds and clusters every x seconds
#define		INTERVALL_FIGURES			10


//----------------------------------------------------------------------
//						HELLOS
//----------------------------------------------------------------------

#define		HELLO_METHOD_RELAY			1
#define		HELLO_METHOD_KTABLE			2

#define		MAX_FIELDS_IN_HELLO_RELAY	70
#define		MAX_FIELDS_IN_HELLO_KTABLE	40

#define		MAX_AP_NEIGH_IN_HELLO		2
#define		MAX_GW_FIELDS_IN_HELLO		30			//Exact Maximum Number

/*	For Packets	*/
#define		NB_RELAY_FIELDS				8



//----------------------------------------------------------------------
//				     		ENERGY		
//----------------------------------------------------------------------

// Initial Energy and sleeping Time
#define		SLEEPING_TIME				INTERVALL_HELLO*2
#define		NO_ENERGY					0
#define		ENERGY						1
#define		ENERGY_AND_SLEEP			2
	
// Values of energy consumption
#define		IDLE_CONSUMPTION			843000
#define		SENT_SLOPE_CONSUMPTION		454
#define		SENT_COEFF_CONSUMPTION		1.9
#define		RECEIVED_SLOPE_CONSUMPTION	356

//Weakest node energy
#define		WEAKEST_NODE_LIFETIME		0.6


//----------------------------------------------------------------------
//				     		WEIGHT		
//----------------------------------------------------------------------
// Type of metric used to compute our weights
#define		LOWEST_ID					1
#define		HIGHEST_DEGREE				2
#define		MOBILITY					3
#define		THEO_WEIGHT					4
#define		OTHER_DEGREE				5

//	Weight
#define		LOW_WEIGHT					15		//Threshold to define a weak weight
#define		OPTIMAL_K_DENSITY			15		//To compute density_metric for the weight
#define		MAX_WEIGHT					255
#define		MAX_DEGREE					20
#define		RECEIVED_COEFF_CONSUMPTION	0.5

//Sleeping threshold (the highest the threshold is, the lowest the probability of sleeping is)
#define		SLEEPING_DECISION_THRESHOLD	2.0


//  Classes of energy
float		MEDIUM_ENERGY;
float		LOW_ENERGY;
float		HIGH_ENERGY;
#define		HIGH_ENERGY_PERCENTAGE		0.7
#define		MEDIUM_ENERGY_PERCENTAGE	0.4
#define		LOW_ENERGY_PERCENTAGE		0.2




///----------------------------------------------------------------------
//				     		ACKS		
//----------------------------------------------------------------------

//timeouts
#define		MAX_NB_RETRANSMISSIONS		1		//Retransmission for data packets that must be acknowledged
#define		TIMEOUT_RETRANSMISSIONS		0.1
#define		MAX_NB_RETRY_ACK_MULTICAST	1
#define		TIMEOUT_ACK_MULTICAST		0.1


//----------------------------------------------------------------------
//				     		CDS		
//----------------------------------------------------------------------
float		timeout_construct_cds ;

//  Parameters for reconnection
#define		NB_JOIN_MAX					2
#define		NB_MAX_TRY_RECONNECT_CDS	10
#define		TIME_BETWEEN_2_BREAKS		10

// 	CDS Maintenance Type
#define		NONE						0
#define		THEO_OLD					1
#define		THEO_NEW					2
#define		THEO_NEW2					3
#define		WU_LI						4


// ROLE
#define		DEAD						0
#define		AP							1
#define		NORMAL						2




//----------------------------------------------------------------------
//				     		CLUSTER		
//----------------------------------------------------------------------
// Parameters
#define		NB_MAX_TRY_RECONNECT_CLUSTER	5




//----------------------------------------------------------------------
//				   		CDS PERORMANCES		
//----------------------------------------------------------------------

//BB Flooding
#define		MAX_BB_FLOODING				10000
#define		INTERVALL_BB_FLOODING		2.0
//AP unicast
#define		MAX_AP_UNICAST				10000
#define		INTERVALL_AP_UNICAST_PK		2.0	





//----------------------------------------------------------------------
//				     		FIGURE		
//----------------------------------------------------------------------

#define		PHYSIC_NEIGHBOR					1
#define		DOMINANCE						2
#define		DOMINATEE_PARENT				3
#define		DOMINATOR_PARENT				4

#define		THICKNESS_DOMINATEE				2
#define		THICKNESS_DOMINATOR				4
#define		THICKNESS_PHYSIC_NEIGHBOR		1



//----------------------------------------------------------------------
//				     		FAILURE		
//----------------------------------------------------------------------

//A node changes its cds-state
#define		STATE_DOMINATOR					1
#define		STATE_DOMINATEE					2
#define		STATE_ANY						3

//A node changes its position
#define		TOPO_DOMINATOR					4
#define		TOPO_DOMINATEE					5
#define		TOPO_ANY						6


//----------------------------------------------------------------------
//							STREAMS			
//----------------------------------------------------------------------

// Type of Streams
#define		STRM_FROM_WLAN		   		0
#define		STRM_TO_WLAN				0

#define		STRM_FROM_ETH		   		2
#define		STRM_TO_ETH					2

#define		STRM_FROM_HIGHER	   		1
#define		STRM_TO_HIGHER				1



//----------------------------------------------------------------------
//							OTHER			
//----------------------------------------------------------------------

//Interval between topology control packets (used for overhead estimation of a proactive protocol with WU & LI)
#define		TC_INTERVAL					5


//----------------------------------------------------------------------
//						Interruptions			
//----------------------------------------------------------------------

// Interrupt code values
#define		HELLO_GENERATION_CODE		01
//CDS
#define		CONSTRUCT_CDS_CODE			10
#define		WAIT_STATE_CODE				11
#define		CDS_MAINTENANCE_CODE		12
#define		AP_HELLO_CODE				13
// CDS Wu & LI
#define		CDS_WU_LI_COMP_CODE			100
// Clusters
#define		CONSTRUCT_CLUSTER_CODE		20
#define		CLUSTER_HELLO_CODE			21
#define		CLUSTERHEAD_HELLO_CODE		22
#define		CLUSTER_MAINTENANCE_CODE	23
// Utils
#define		STATS_CODE					30
#define		CLUSTER_TOPO_CODE			31
#define		UPDATE_TABLE_CODE			33
#define		AP_UNICAST_GENERATE_CODE	35
// Acknowledgements
#define		RETRANSMISSIONS_CODE		40
#define		MULTI_RETRANSMISSIONS_CODE	41
// Stats about positions
#define		STATS_POSITIONS_CODE		60



// Macro definitions for state		
// transitions.						
#define		ENDSIM					(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define		HELLO_PK_GENERATE		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == HELLO_GENERATION_CODE)
#define 	PK_FROM_WLAN			(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_WLAN)
#define 	PK_FROM_ETH				(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_ETH)
#define 	PK_FROM_HIGHER			(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_HIGHER)
#define		CONSTRUCT_CDS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CONSTRUCT_CDS_CODE)
#define		WAIT_STATE_END			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == WAIT_STATE_CODE)
#define		CDS_MAINTENANCE			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CDS_MAINTENANCE_CODE)
#define		CONSTRUCT_CLUSTER		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CONSTRUCT_CLUSTER_CODE)
#define		CLUSTER_MAINTENANCE		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CLUSTER_MAINTENANCE_CODE)
#define		CLUSTERHEAD_HELLO		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CLUSTERHEAD_HELLO_CODE)
#define		DIE						(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == DIE_CODE)
#define		STATS_POSITIONS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == STATS_POSITIONS_CODE)
#define		AP_UNICAST_GENERATE		(op_intrpt_code() == AP_UNICAST_GENERATE_CODE)





//----------- Global Variables ---------
double	simulation_duration	= 0;
int		nb_total			= 0;
int		nb_aps				= 0;
int		nb_wireless_routers	= 0;
int		nb_nodes_expected 	= 0;
int		nb_aps_expected		= 0;




//----------------------------------------------------------------------
//						Utils	& Parameters	
//----------------------------------------------------------------------


//In order to manipulate name of fields in hello packets like array of strings
struct_hello_field 	hello_fields_names[MAX_FIELDS_IN_HELLO_RELAY+1];
int 				begin_time=0;





//----------------------------------------------------------------------
//						WEIGHT DECISION (MAX, MIN....)	
//----------------------------------------------------------------------
double	MAX_SPEED		= 0;

int		MAX_K_DEGREE	= 0;
int		MIN_K_DEGREE	= INFINITY;








//----------------------------------------------------------------------
//				     		OVERHEADS
//----------------------------------------------------------------------


//--------------------  PACKETS ---------------------------------------

long int	nb_pk_hello_instantaneous						=0;
long int	nb_pk_cds_instantaneous							=0;
long int	nb_pk_ap_hello_instantaneous					=0;
long int	nb_pk_cluster_instantaneous						=0;
long int	nb_pk_other_instantaneous						=0;
long int	nb_pk_data_instantaneous						=0;
long int	nb_pk_bb_multicast_instantaneous				=0;
long int	nb_pk_ack_instantaneous							=0;

long int	nb_pk_hello_total								=0;
long int	nb_pk_cds_total									=0;
long int	nb_pk_ap_hello_total							=0;
long int	nb_pk_cluster_total								=0;
long int	nb_pk_other_total								=0;
long int	nb_pk_data_total								=0;
long int	nb_pk_bb_multicast_total						=0;
long int	nb_pk_ack_total									=0;


long int	nb_pk_hello_dominatee_instantaneous				=0;
long int	nb_pk_cds_dominatee_instantaneous				=0;
long int	nb_pk_ap_hello_dominatee_instantaneous			=0;
long int	nb_pk_cluster_dominatee_instantaneous			=0;
long int	nb_pk_other_dominatee_instantaneous				=0;
long int	nb_pk_data_dominatee_instantaneous				=0;
long int	nb_pk_bb_multicast_dominatee_instantaneous		=0;
long int	nb_pk_ack_dominatee_instantaneous				=0;

long int	nb_pk_hello_dominatee_total						=0;
long int	nb_pk_cds_dominatee_total						=0;
long int	nb_pk_ap_hello_dominatee_total					=0;
long int	nb_pk_cluster_dominatee_total					=0;
long int	nb_pk_other_dominatee_total						=0;
long int	nb_pk_data_dominatee_total						=0;
long int	nb_pk_bb_multicast_dominatee_total				=0;
long int	nb_pk_ack_dominatee_total						=0;


long int	nb_pk_hello_dominator_instantaneous				=0;
long int	nb_pk_cds_dominator_instantaneous				=0;
long int	nb_pk_ap_hello_dominator_instantaneous			=0;
long int	nb_pk_cluster_dominator_instantaneous			=0;
long int	nb_pk_other_dominator_instantaneous				=0;
long int	nb_pk_data_dominator_instantaneous				=0;
long int	nb_pk_bb_multicast_dominator_instantaneous		=0;
long int	nb_pk_ack_dominator_instantaneous				=0;

long int	nb_pk_hello_dominator_total						=0;
long int	nb_pk_cds_dominator_total						=0;
long int	nb_pk_ap_hello_dominator_total					=0;
long int	nb_pk_cluster_dominator_total					=0;
long int	nb_pk_other_dominator_total						=0;
long int	nb_pk_data_dominator_total						=0;
long int	nb_pk_bb_multicast_dominator_total				=0;
long int	nb_pk_ack_dominator_total						=0;



//----------- PACKET RETRANSMISSION FLOWS ---------

long int	nb_pk_ret_bb_multicast_instantaneous			=0;
long int	nb_pk_ret_bb_multicast_total					=0;
long int	nb_pk_ret_bb_multicast_dominatee_instantaneous	=0;
long int	nb_pk_ret_bb_multicast_dominatee_total			=0;
long int	nb_pk_ret_bb_multicast_dominator_instantaneous	=0;
long int	nb_pk_ret_bb_multicast_dominator_total			=0;






//--------------------  BITS ---------------------------------------


long int	nb_bits_hello_instantaneous						=0;
long int	nb_bits_cds_instantaneous						=0;
long int	nb_bits_ap_hello_instantaneous					=0;
long int	nb_bits_cluster_instantaneous					=0;
long int	nb_bits_other_instantaneous						=0;
long int	nb_bits_data_instantaneous						=0;
long int	nb_bits_bb_multicast_instantaneous				=0;
long int	nb_bits_ack_instantaneous						=0;

long int	nb_bits_hello_total								=0;
long int	nb_bits_cds_total								=0;
long int	nb_bits_ap_hello_total							=0;
long int	nb_bits_cluster_total							=0;
long int	nb_bits_other_total								=0;
long int	nb_bits_data_total								=0;
long int	nb_bits_bb_multicast_total						=0;
long int	nb_bits_ack_total								=0;


long int	nb_bits_hello_dominatee_instantaneous			=0;
long int	nb_bits_cds_dominatee_instantaneous				=0;
long int	nb_bits_ap_hello_dominatee_instantaneous		=0;
long int	nb_bits_cluster_dominatee_instantaneous			=0;
long int	nb_bits_other_dominatee_instantaneous			=0;
long int	nb_bits_data_dominatee_instantaneous			=0;
long int	nb_bits_bb_multicast_dominatee_instantaneous	=0;
long int	nb_bits_ack_dominatee_instantaneous				=0;

long int	nb_bits_hello_dominatee_total					=0;
long int	nb_bits_cds_dominatee_total						=0;
long int	nb_bits_ap_hello_dominatee_total				=0;
long int	nb_bits_cluster_dominatee_total					=0;
long int	nb_bits_other_dominatee_total					=0;
long int	nb_bits_data_dominatee_total					=0;
long int	nb_bits_bb_multicast_dominatee_total			=0;
long int	nb_bits_ack_dominatee_total						=0;


long int	nb_bits_hello_dominator_instantaneous			=0;
long int	nb_bits_cds_dominator_instantaneous				=0;
long int	nb_bits_ap_hello_dominator_instantaneous		=0;
long int	nb_bits_cluster_dominator_instantaneous			=0;
long int	nb_bits_other_dominator_instantaneous			=0;
long int	nb_bits_data_dominator_instantaneous			=0;
long int	nb_bits_bb_multicast_dominator_instantaneous	=0;
long int	nb_bits_ack_dominator_instantaneous				=0;

long int	nb_bits_hello_dominator_total					=0;
long int	nb_bits_cds_dominator_total						=0;
long int	nb_bits_ap_hello_dominator_total				=0;
long int	nb_bits_cluster_dominator_total					=0;
long int	nb_bits_other_dominator_total					=0;
long int	nb_bits_data_dominator_total					=0;
long int	nb_bits_bb_multicast_dominator_total			=0;
long int	nb_bits_ack_dominator_total						=0;



//----------- PACKET RETRANSMISSION FLOWS ---------

long int	nb_bits_ret_bb_multicast_instantaneous			=0;
long int	nb_bits_ret_bb_multicast_total					=0;
long int	nb_bits_ret_bb_multicast_dominatee_instantaneous=0;
long int	nb_bits_ret_bb_multicast_dominatee_total		=0;
long int	nb_bits_ret_bb_multicast_dominator_instantaneous=0;
long int	nb_bits_ret_bb_multicast_dominator_total		=0;








//----------------------------------------------------------------------
//				     		Stats and Global Variables
//----------------------------------------------------------------------


//----------- Global Variables ---------


//----------- GLOBAL STATS ---------
//General
int		written_nodes=0;

//Global Stats
int		nb_dead_nodes=0;
char	list_dead_nodes[500];

//Stats about final weights 
char	final_weights_of_all_nodes[6000];

//Topology
//Average
int		nb_high_speed_nodes=0;
int		nb_low_speed_nodes=0;
float	average_degree=0;
//Instantaneous
float	final_weight=0 , final_weight_dom=0 , final_weight_usefull_dom=0;
float	final_degree=0 ;
int		final_max_degree=0;
float	final_k_neighbours=0;


//----------- CDS ---------

//Instantaneous variables (7for control or computing other variables)
int		nb_actual_dominators				= 0;
short 
	
//Average Statistics for Global Simulation
int 	nb_dominators						= 0;
int 	nb_dominatees						= 0;
int 	nb_idles							= 0;
int 	nb_actives							= 0;
int		nb_ap_neigh							= 0;

float	average_nb_secondary_fathers		= 0;
float	average_nb_ap_neigh					= 0;
float	average_nb_cds_connectors			= 0;
int		average_nb_dominators				= 0;
int		average_nb_dominatees				= 0;

//Stats for Stats procedure (instantaneous values stored in stat_files)
int		stats_cds_connection				= 0;
char	stats_list_dominators[500];
char	stats_list_cds_connectors[500];

//Statistics about Final State of the system
int		final_nb_isolated_dominators=0;
char	final_list_isolated_dominators[500];

int 	average_seconds_of_disconnection_for_dominatees	= 0;	//Cumulative seconds of disconnection for one dominatee (for global average statistics)
int 	tmp_seconds_of_disconnection_for_dominatees		= 0;	

int		final_nb_dominators						= 0;
int		final_nb_dominatees						= 0;
int		final_nb_dominatees_max					= -1;
int		final_nb_dominatees_min					= -1;

float	final_dominatees_per_dominator			= 0;
int		final_nb_dominator_without_dominatees	= 0;	
int		final_nb_sons_max						= -1;
float	final_sons_per_dominator				= 0;

//Time connection
double	average_cds_percentage_time_disconnected	= 0;
double	average_cds_connexity_strict				= 0;
double	average_cds_connexity_large					= 0;

double	tmp_cds_percentage_time_disconnected	= 0;
double	tmp_cds_connexity_strict				= 0;
double	tmp_cds_connexity_large					= 0;

//Requests (packets,...)
int 	nb_cds_recon		= 0;
int		nb_cds_recon_req	= 0;
int		nb_cds_recon_pk		= 0;
int 	nb_cds_breaks		= 0;

//Persistence
int 	nb_nodes_impacted_by_cds_breaks				= 0;
int		nb_dominatees_which_change_their_dominator	= 0;
int		nb_nodes_which_change_their_dominator		= 0;
int		nb_changes_of_dominators					= 0;


//----------- CLUSTERS ---------

//Average Stats For Global Simulation					//Computed constantly
int 	nb_clusterheads			= 0;
int		average_nb_clusterheads	= 0;

int		tmp_nb_clusterheads		= 0;

//Stats for Stats procedure (instantaneous values stored in stat_files)
int		stats_clusterhead_connection=0;
char	stats_list_clusterheads[100];

//Stats about final State of The System
int		final_nb_clusterheads=0;			//Computed finally
int		final_nb_nodes_without_clusterhead=0;
char	final_list_clusterheads[500];
char	final_list_nodes_without_clusterhead[500];

//Time connection
double	average_cluster_percentage_time_disconnected	= 0;
double	tmp_cluster_percentage_time_disconnected		= 0;

//Requests (packets,...)
int 	nb_cluster_con		= 0;
int		nb_cluster_con_pk	= 0;
int		nb_cluster_con_req	= 0;

//Persistence
int		nb_dominators_which_change_their_clusterheads	= 0;
int		nb_nodes_which_change_their_clusterheads		= 0;
int		nb_changes_of_clusterheads						= 0;


//Stats about changes in Neighborhood
int		nb_chgts_virtual_topo=0;
int		nb_chgts_real_topo=0;





//----------- ENERGY ---------

//Sleep
double	cumul_sleeping_time				= 0;
double	average_energy_sleeping_nodes	= 0;
double	energy_sleeping_weakest_node	= 0;
double	energy_weakest_node				= -1;
int		nb_sleeps						= 0;
int		stat_id_weakest_node 			= 0;
//Energy
energy_stats_stuct 		stat_conso_dominator;
energy_stats_stuct 		stat_conso_dominatee;
char stat_energy_conso_record[30000];						//To describe energy consumptions, sleeping time...


//----------- BACKBONE FLOODING ---------

struct_bb_flooding	stats_bb_flooding[MAX_BB_FLOODING];
int	current_bb_flooding_id = 0;


//----------- AP UNICAST ---------

struct_ap_unicast	stats_ap_unicast[MAX_AP_UNICAST];
int	current_ap_unicast_id = 0;



//--------------- STATS --------------

//Contains the number of stats which were collected
long int	nb_stats_collections		= 0;


//Contains all x and y coordinates for all nodes
char	prefix_results_file [50];
char	suffix_results_file [50];
int		stats_specificities	[MAX_NB_NODES];   				//the specificity of the node (if special) : AP / DEAD / NORMAL
short	stats_degree		[MAX_NB_NODES];   				//Degree of each node
double	stats_positions		[MAX_NB_NODES][2];   			//0: x-position, 1:y-position
short	stats_links			[MAX_NB_NODES][MAX_NB_NODES];	//1 in Mi,j if there exists a link between node i and j
short	stats_weights		[MAX_NB_NODES];		   			//Weight-Values

short	stats_state			[MAX_NB_NODES];   				//CDS-state (DOMINATOR / DOMINATEE / ACTIVE /IDLE)
short	stats_cluster		[MAX_NB_NODES];   				//Contains the id of our clusterhead

double	stats_overheads_pk	[MAX_NB_NODES];					//Overheads associated to one node (in pps)
double	stats_overheads_bits[MAX_NB_NODES];					//Overheads associated to one node (in bps)

short	stats_addresses_to_id [MAX_ADDRESS];				//The stat_id corresponding to one address
short	stats_id_to_addresses [MAX_NB_NODES];				//The address corresponding to one id (inverse of the precedent)

struct_stats	stats_cds[MAX_NB_NODES];					//To store infos about cds



//-------------- STATE CHANGES ----------------------
int		stats_idle_active_changes				= 0;
int		stats_idle_dominator_changes			= 0;
int		stats_idle_dominatee_changes			= 0;
int		stats_dominatee_idle_changes			= 0;
int		stats_dominator_idle_changes			= 0;
int		stats_active_dominator_changes			= 0;
int		stats_active_dominatee_changes			= 0;
int		stats_dominatee_active_changes			= 0;
int		stats_dominatee_dominator_changes		= 0;
int		stats_dominator_dominatee_changes		= 0;


//-------------- SELF-STABILIZATION ----------------------

int		stab_idle_active_changes				= 0;
int		stab_idle_dominator_changes				= 0;
int		stab_idle_dominatee_changes				= 0;
int		stab_dominatee_idle_changes				= 0;
int		stab_dominator_idle_changes				= 0;
int		stab_active_dominator_changes			= 0;
int		stab_active_dominatee_changes			= 0;
int		stab_dominatee_active_changes			= 0;
int		stab_dominatee_dominator_changes		= 0;
int		stab_dominator_dominatee_changes		= 0;

Boolean	stab_is_idle_end_written					= OPC_FALSE;
Boolean	stab_is_active_end_written					= OPC_FALSE;
Boolean	stab_is_large_connexity_cds_end_written		= OPC_FALSE;
Boolean	stab_is_strict_connexity_cds_end_written	= OPC_FALSE;
Boolean	stab_is_strict_tempo_failure_written		= OPC_FALSE;
Boolean	stab_is_large_tempo_failure_written			= OPC_FALSE;
double	stab_failure_time							= 0;
int	   	stab_failure_type							= 0;


//----------------------------------------------------------------------//
//																		//
//																		//
//								PROTOTYPES								//
//																		//
//																		//
//----------------------------------------------------------------------//



//-------------------  UTILS ---------------------

//No category
int 		get_max(int v1 , int v2);
void 	format_int_to_string(double src, char* dest, int nb_digits);
//List of neighbors
List* 		create_list_from_pk(Packet* pkptr);
//Manipulation of lists of dominatees, sons...
int 		is_my_son(int addr);
int 		is_my_dominatee(int addr);
int 		count_nb_dominatees();
int 		count_nb_sons();
void 		add_son(int addr);
void 		add_dominatee(int addr);
void 		delete_son(int addr);
void 		delete_dominatee(int addr);
//Secondary fathers
int 		delete_double_secondary_fathers(candidate* ptr,int result[]);


//-------------------  NETWORK UTILS ---------------------

//Transmission
void 		pk_retransmit_delayed(Packet* pkptr, double delay);
void 		pk_retransmit(Packet* pkptr);
void 		pk_send_delayed(Packet* pkptr, double delay);
void 		pk_send(Packet* pkptr);
void 		die();
//Network Control
int 		remove_id(int id, int addr);
void 		forward_packet_to_dominator(Packet* pkptr, int type);
void 		add_address_id_couple(int addr,int id);
int			is_unidirectional_link(int addr);
//Ici
void 		delete_timeout_in_ici_list();
Ici* 		add_in_ici_list();



//-------------------  STATS ---------------------


void 	compute_stats_about_graph_cluster_cds();
void 	compute_cds_graph(short g[MAX_NB_NODES][MAX_NB_NODES] , short cds_graph[MAX_NB_NODES][MAX_NB_NODES]);
void 	compute_shortest_routes(List* routes[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , int nb_nodes);
void 	compute_cds_graph_large(short g[MAX_NB_NODES][MAX_NB_NODES] , short cds_graph[MAX_NB_NODES][MAX_NB_NODES]);

void 	route_to_str(List * route, char* msg);
void 	route_empty(List* route);
void 	copy_route(List* source , List * dest);
void 	add_route(List* route , int node);
int 	get_relay(List* route , int pos);

void 	compute_and_write_cplex_files();


//-------------  ACKS --------------

void 		send_timeout_ack_pk(int *arg, int code);
void 		send_timeout_ack_multicast_pk(int* arg, int code);



//-------------------  ENERGY / WEIGHT ---------------------

//Energy
void 		energy_decreases(float	offset);
int			must_sleep();
void 		sleep();
void 		add_sleeping_node(int addr);
void 		die();

//Weight
void 		update_my_weight() ;


//-------------------  HELLOS ---------------------

//K-Neighbourhood
Packet*		hello_packet_generate ();
void 		update_table_neighbours (Packet* pkptr , short ttl_for_pk);
void 		delete_duplicated_entries_in_neigh_table();
int			is_one_valid_neighbour(int addr, short hops_max);
int 		nb_neighbours();
//TABLES
void 		update_tables();
void 		update_tables_periodic(int* arg, int code);



//-------------------  CDS ---------------------

//MIS
void 		update_state_cds(int state);
void 		send_new_state(int state);
void 		update_informations_cds(int address , int father , int clusterhead , int state , int weight);
int 		own_highest_weight();
//CDS
void 		send_join_message();
void		send_join_message_delayed(float delay);
void 		forward_join_message(Packet* pkptr);
void 		send_join_reverse(Packet* pk_src);	
//AP-Hellos
void 		forward_join_reverse(Packet* pk_dest);
void 		update_ap_hellos_table(int src, int id_ap, int id_hello);
void		forward_hello_ap(Packet* pkptr, Stathandle stat_local, Stathandle stat_global);
void 		ap_hello(int* arg, int code);
void 		forward_packet_ap_hello_dominatee(Packet* pkptr, Stathandle stat_local, Stathandle stat_global);
//MAINTENANCE
void 		reply_cds_reconnect(Packet *pk_src);
int			connection_cds_init(Packet *pk_src);
void 		add_relaying(int src, int relay);						//return 0 if the entry already exists in the table
void 		forward_reconnect_reply(Packet* pkptr);
void 		break_all_our_tree();
void 		reinit_cds_infos();	
void		leader_election_init();
int 		add_cds_reconnect_candidate(Packet* pkptr);

//Backbone Interconnection
void		advertise_ap_neigh(pkptr);
void		register_ap_neigh(pkptr);
int 		count_nb_cds_connectors();
int 		count_nb_dominatees_in_list(List* list);
List* 		get_my_unique_cds_connectors();



//-------------------  CLUSTERS ---------------------

//Clusters
void 		clusterhead_hello(int* arg , int code);
void		update_weight(pkptr);
void 		send_hello_cluster();
Boolean 	all_neighbours_cluster_init();
int			own_highest_weight_cluster();
void 		change_clusterhead(int ch, int relay, short hops);
void		update_cluster_table();
//Cluster-Neighbors (GW Management)
void 		fill_hello_pk_with_my_gw_list(Packet* pkptr);
List* 		fill_gw_list_with_hello_pk(Packet* pkptr , List *gw_list);
void 		update_my_gw_list();



//-------------------  DEBUG ---------------------

void 		cluster_message(char* message);
void 		bb_flooding_message(char* message);
void 		test_message(char* message);
void 		ap_unicast_message(char* message);

void 		print_general_infos();
void 		print_neighbour_table();
void 		print_neighbours_of_neighbours_table();
void 		print_cds_candidates();
void 		print_cds_infos();
void 		print_ap_hellos_table();
void 		print_cluster_infos();
void 		print_cluster_table();
void		print_cluster_topo();
void 		print_dominatees();
void 		print_sons();
void 		end_simulation();
void		print_last_short_neighbour_table();
void 		print_absolute_speeds();
void 		print_gw_list_line(List* gw_list);
void 		print_gw_lists_of_neighbour_table();
void 		print_cds_connectors();


//-------------------  CLUSTERS TOPOLOGY ---------------------

//Actual Cluster Topology
int 		refresh_cluster_neigh_global(int addr1 , int addr2);
void 		delete_cluster_neigh_global(int addr1 , int addr2);
int 		is_cluster_neigh_global(int addr1, int addr2);

int			is_cluster_neigh(int addr);
int 		refresh_cluster_neigh(int addr);
void 		delete_cluster_neigh(int addr);
void 		add_cluster_neigh(int addr);

void 		print_global_gateways();




//----------------------  Wu & LI ------------------------

//Main Function
void 		cds_maintenance_wu_li();
int 		get_state_wu_li();
//Debug
void 		print_neighbors_table_wu();
//utils
void 		update_neighbors_table_wu();

/*
//Utils
void		update_the_neighbor_table_associated_to_one_neighbor(Packet* pkptr);
void 		find_node_with_highest_good_degree(int *final_node, int* final_weight);
void 		add_1_neighbors_of_higher_weight(int addr, min_cell** covered_list);		//Adds recursively this 1 neighbor and all its 1-neighbors with higher weight than my own weight
//Covered List
void 		add_node_in_covered_list(int addr , int weight , short hops , min_cell** covered_list);
void		print_covered_list(min_cell** list);
//Print for debuggging
void 		print_neighbors_table_of_table();

*/

/* End of Header Block */


#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(last_line_passed) = __LINE__ - _block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(last_line_passed) = 0; _block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	int	                    		my_address;
	weight	                 		my_weight;
	neigh_cell*	            		neighbour_table;
	int	                    		DEBUG;
	id_cell*	               		id_table;
	int	                    		current_id;
	int	                    		is_AP;
	cds	                    		my_cds;
	List*	                  		temporary_pk_list;
	relay_cell*	            		relay_table;
	short	                  		k_cds;
	ap_hellos*	             		ap_hellos_table;
	int	                    		hello_method;
	clusterhead	            		my_clusterhead;
	short	                  		k_cluster;
	cluster_cell*	          		cluster_table;
	Boolean	                		is_wireless_router;
	old_cl_topo	            		old_cluster_topo;
	energy_struct	          		my_energy;
	dead_struct	            		is_DEAD;
	sleeping_struct	        		is_sleeping;
	short	                  		energy_management;
	short	                  		metric;
	coordinates	            		last_xy;
	double	                 		last_absolute_speeds[NB_STORED_SPEEDS];
	int	                    		nb_chgts_neighbourhood;
	ack_cell*	              		my_acks;
	int	                    		my_stat_id;
	int	                    		cds_algos_type;
	int	                    		cluster_algos_type;
	int	                    		process_higher_layer_id;
	Evhandle	               		last_ev_cluster_hello;
	List*	                  		ici_list;
	List*	                  		my_gw_list;
	int	                    		process_higher_layer_type;
	int	                    		is_cluster_knowledge_required;
	int	                    		last_son_lost;
	List*	                  		ack_multicast_list;
	int	                    		ttl_for_hellos;
	int	                    		overhead_cds_pk;
	int	                    		overhead_cds_bits;
	int	                    		overhead_cluster_pk;
	int	                    		overhead_cluster_bits;
	int	                    		overhead_hello_pk;
	int	                    		overhead_hello_bits;
	int	                    		overhead_route_pk;
	int	                    		overhead_route_bits;
	int	                    		overhead_data_pk;
	int	                    		overhead_data_bits;
	int	                    		overhead_paging_pk;
	int	                    		overhead_paging_bits;
	int	                    		overhead_other_pk;
	int	                    		overhead_other_bits;
	List*	                  		neighbor_table_wu_li;
	int	                    		ACK_FOR_BB_MULTICAST;
	int	                    		ttl_for_hello_mis;
	} cdcl_process_cluster_cds_process_state;

#define pr_state_ptr            		((cdcl_process_cluster_cds_process_state*) SimI_Mod_State_Ptr)
#define my_address              		pr_state_ptr->my_address
#define my_weight               		pr_state_ptr->my_weight
#define neighbour_table         		pr_state_ptr->neighbour_table
#define DEBUG                   		pr_state_ptr->DEBUG
#define id_table                		pr_state_ptr->id_table
#define current_id              		pr_state_ptr->current_id
#define is_AP                   		pr_state_ptr->is_AP
#define my_cds                  		pr_state_ptr->my_cds
#define temporary_pk_list       		pr_state_ptr->temporary_pk_list
#define relay_table             		pr_state_ptr->relay_table
#define k_cds                   		pr_state_ptr->k_cds
#define ap_hellos_table         		pr_state_ptr->ap_hellos_table
#define hello_method            		pr_state_ptr->hello_method
#define my_clusterhead          		pr_state_ptr->my_clusterhead
#define k_cluster               		pr_state_ptr->k_cluster
#define cluster_table           		pr_state_ptr->cluster_table
#define is_wireless_router      		pr_state_ptr->is_wireless_router
#define old_cluster_topo        		pr_state_ptr->old_cluster_topo
#define my_energy               		pr_state_ptr->my_energy
#define is_DEAD                 		pr_state_ptr->is_DEAD
#define is_sleeping             		pr_state_ptr->is_sleeping
#define energy_management       		pr_state_ptr->energy_management
#define metric                  		pr_state_ptr->metric
#define last_xy                 		pr_state_ptr->last_xy
#define last_absolute_speeds    		pr_state_ptr->last_absolute_speeds
#define nb_chgts_neighbourhood  		pr_state_ptr->nb_chgts_neighbourhood
#define my_acks                 		pr_state_ptr->my_acks
#define my_stat_id              		pr_state_ptr->my_stat_id
#define cds_algos_type          		pr_state_ptr->cds_algos_type
#define cluster_algos_type      		pr_state_ptr->cluster_algos_type
#define process_higher_layer_id 		pr_state_ptr->process_higher_layer_id
#define last_ev_cluster_hello   		pr_state_ptr->last_ev_cluster_hello
#define ici_list                		pr_state_ptr->ici_list
#define my_gw_list              		pr_state_ptr->my_gw_list
#define process_higher_layer_type		pr_state_ptr->process_higher_layer_type
#define is_cluster_knowledge_required		pr_state_ptr->is_cluster_knowledge_required
#define last_son_lost           		pr_state_ptr->last_son_lost
#define ack_multicast_list      		pr_state_ptr->ack_multicast_list
#define ttl_for_hellos          		pr_state_ptr->ttl_for_hellos
#define overhead_cds_pk         		pr_state_ptr->overhead_cds_pk
#define overhead_cds_bits       		pr_state_ptr->overhead_cds_bits
#define overhead_cluster_pk     		pr_state_ptr->overhead_cluster_pk
#define overhead_cluster_bits   		pr_state_ptr->overhead_cluster_bits
#define overhead_hello_pk       		pr_state_ptr->overhead_hello_pk
#define overhead_hello_bits     		pr_state_ptr->overhead_hello_bits
#define overhead_route_pk       		pr_state_ptr->overhead_route_pk
#define overhead_route_bits     		pr_state_ptr->overhead_route_bits
#define overhead_data_pk        		pr_state_ptr->overhead_data_pk
#define overhead_data_bits      		pr_state_ptr->overhead_data_bits
#define overhead_paging_pk      		pr_state_ptr->overhead_paging_pk
#define overhead_paging_bits    		pr_state_ptr->overhead_paging_bits
#define overhead_other_pk       		pr_state_ptr->overhead_other_pk
#define overhead_other_bits     		pr_state_ptr->overhead_other_bits
#define neighbor_table_wu_li    		pr_state_ptr->neighbor_table_wu_li
#define ACK_FOR_BB_MULTICAST    		pr_state_ptr->ACK_FOR_BB_MULTICAST
#define ttl_for_hello_mis       		pr_state_ptr->ttl_for_hello_mis

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	cdcl_process_cluster_cds_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
double	stats_overheads_pk	[MAX_NB_NODES];					//Overheads associated to one node (in pps)
double	stats_overheads_bits[MAX_NB_NODES];					//Overheads associated to one node (in bps)





/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//											NEIGHBORS



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/

 
/*-----------------------------------------------------------------------------------------------

									NEIGHBORS MANIPULATION

-----------------------------------------------------------------------------------------------*/

//Empties a list
void empty_list(List* ll){
	void	*elem;
	
	while(op_prg_list_size(ll) > 0)
		{
			elem = op_prg_list_remove(ll , OPC_LISTPOS_TAIL);
			op_prg_mem_free(elem);
		}	
}

//returns the list of neighbors present in pkptr
List * create_neighbors_list(Packet *pkptr){
	List			*neighbors;
	neigh_min		*elem;
	int				addr , weight;
	Boolean			bidirect , is_fields_overflow;
	int				i;
	

	//initialization
	neighbors = op_prg_list_create();
	
	//We store all the 1-neighbors of this node in the cell of the neighbor table of table
	i = 1;
	is_fields_overflow = (i>MAX_FIELDS_IN_HELLO_RELAY) ;
	while (op_pk_nfd_is_set(pkptr , hello_fields_names[i].address) && !is_fields_overflow )
		{
			op_pk_nfd_get(pkptr , hello_fields_names[i].bidirect , &bidirect);
			if (bidirect) 
				{		
					//Gathers address
					op_pk_nfd_get(pkptr , hello_fields_names[i].address ,	&addr);
					op_pk_nfd_get(pkptr , hello_fields_names[i].weight , 	&weight);
	
					//Memory Allocation for a new cell in the list of neighbours
					elem = op_prg_mem_alloc(sizeof(neigh_min));
					if (elem == NULL)
						printf("error in the memory allocation for the creation of a new entry in the list of neighbors in Wu & Li\n");
				
					//Information
					elem->address 	= addr;
					elem->weight 	= weight;
			
					//Insert it !
					op_prg_list_insert(neighbors, elem , OPC_LISTPOS_TAIL);
				}
			i++;
			is_fields_overflow = (i>MAX_FIELDS_IN_HELLO_RELAY) ;
		}
	return(neighbors);
}


/*-----------------------------------------------------------------------------------------------

									HELLO PACKETS

-----------------------------------------------------------------------------------------------*/

void hello_management(int* arg, int code){
	char		msg[250];
	Packet*		pkptr;

	if (!is_sleeping.value)
		{
			//Update variables before sending the hello with these new information
			update_my_weight();
			delete_duplicated_entries_in_neigh_table();

			//Generate one hello packet with the table of neighbours
			pkptr = hello_packet_generate();
			
			// Send the packet
			pk_send_delayed(pkptr , op_dist_uniform(0.005));


			//Will this node sleep during SLEEPING_TIME seconds ?
			if ((energy_management == 2) && (must_sleep()))
				sleep();
		}
	else
		{
			if (is_sleeping.time_sleeping < op_sim_time() - SLEEPING_TIME)
				{
					sprintf(msg,"%d : end sleep at %f!\n",my_address,op_sim_time());
					cluster_message(msg);
					
					//Stats
					cumul_sleeping_time += op_sim_time() - is_sleeping.time_sleeping;
					is_sleeping.cumul_sleeping_time += op_sim_time() - is_sleeping.time_sleeping;

					//Sleeping Temporary Values
					is_sleeping.value = OPC_FALSE;
					is_sleeping.time_sleeping = 0;
				}
			
		}

	op_intrpt_schedule_call (op_sim_time() + INTERVALL_HELLO + op_dist_uniform(0.01) , HELLO_GENERATION_CODE , hello_management , 1);
}

Packet* hello_packet_generate (void){
	Packet*				pkptr;

	//Variables of control (loops, lists of pointers...)
	neigh_cell*			ptr;
	int					i, j;
	int					hops_max; 	//If we forward k times the hellos, we send only our 1-neighbourhood
	char				msg[150];
	
	//--------------------------------------------
	//	Pk Creation + TTL + Initialization
	//--------------------------------------------	

	/* Multiple Cases :
	-forwarding hellos 	-> ttl = k and place in the packet our 1-neighbourhood
	-k-table			-> ttl = 1 and place all our k-neighbourhood in the packet */
	switch(hello_method) {
		case HELLO_METHOD_RELAY :
			pkptr = op_pk_create_fmt ("cdcl_hello_relay");
			
			//TTL
			op_pk_nfd_set(pkptr,"TTL" , ttl_for_hellos);
		
			//We send only us and not our neighbour		
			hops_max = 1;		
		
			//Sets the default value in the fields of neighbours addresses (this value is forbidden)
			for(i=1;i <= MAX_FIELDS_IN_HELLO_RELAY;i++)
				op_pk_nfd_set(pkptr , hello_fields_names[i].address ,-1);

			break;
		
		case HELLO_METHOD_KTABLE :
			pkptr = op_pk_create_fmt ("cdcl_hello_ktable");
			op_pk_nfd_set(pkptr,"TTL",1);
			//If we have k=1, we must send our neighbours to detect unidiretional links
			if (k_cds > 1)
				hops_max = k_cds-1;
			else
				hops_max = 1;
		
			//Sets the default value in the fields of neighbours addresses (this value is forbidden)
			for(i=1;i <= MAX_FIELDS_IN_HELLO_KTABLE;i++)
				{
					op_pk_nfd_set(pkptr , hello_fields_names[i].address , -1);
				}

			break;
		
		default :
			cluster_message("We have encountered an error : the hello method is false !\n");
		
	}	

	if (DEBUG>MAX) 
		{
			sprintf(msg,"I send an hello (id=%d) : %d, a weight of %d, father=%d and a state of %d (at %f)\n",current_id,my_address,my_weight.value,my_cds.father,my_cds.state,op_sim_time());
			cluster_message(msg);
		}
	
	
	//--------------------------------------------
	//	COMMON FIELDS
	//--------------------------------------------	

	op_pk_nfd_set(pkptr,"OPTION_TYPE",HELLO_PK_TYPE);

	op_pk_nfd_set(pkptr,"SRC",				my_address);
	op_pk_nfd_set(pkptr,"DEST",				-1);
	if (hello_method == HELLO_METHOD_RELAY)
		op_pk_nfd_set(pkptr,"RELAY",		my_address);
	op_pk_nfd_set(pkptr,"PK_ID",			current_id++);
	
	op_pk_nfd_set(pkptr,"WEIGHT",			my_weight.value);
	op_pk_nfd_set(pkptr,"MOBILITY",			my_weight.mobility);
	
	op_pk_nfd_set(pkptr,"STATE",			my_cds.state);
	op_pk_nfd_set(pkptr,"ID_AP",			my_cds.id_ap);
	op_pk_nfd_set(pkptr,"FATHER",			my_cds.father);
	if (my_cds.state != DOMINATEE)
		op_pk_nfd_set(pkptr,"FATHER_HOPS",	0);
	else
		op_pk_nfd_set(pkptr,"FATHER_HOPS",	my_cds.father_hops);

	op_pk_nfd_set(pkptr,"CLUSTERHEAD",		my_clusterhead.address);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD_HOPS",	my_clusterhead.hops);
	
	if (my_cds.state == DOMINATOR)
		op_pk_nfd_set(pkptr , "AP_HOPS" , my_cds.ap_hops);
	else
		op_pk_nfd_strip(pkptr , "AP_HOPS");
	
	//To add adjacent ap if I am a gateway
	advertise_ap_neigh(pkptr);

	
	//--------------------------------------------
	//	THE CLUSTER FOR WHICH I AM GW
	//--------------------------------------------	
	fill_hello_pk_with_my_gw_list(pkptr);
	
	
	
	//--------------------------------------------
	//	NEIGHBOURS FILLING
	//--------------------------------------------	

	//Place in the packet the table of neighbourhood
	if (neighbour_table!=NULL) 
		ptr = neighbour_table->next;	//We bypass ourself
	else  //Normally impossible : we are in the table !
		{
			ptr=NULL;
			cluster_message("!!!!!!!!!!! Error : the neighbour_table doesn't contain ourself ! The timeouts has expired ?????\n");
		}

		
	
	//We add all the nodes that are nearer than hops_max 
	i=1;
	//We stop at the end of the chain or when we have not enough place in the packet
	//If Mode=relay, we send only ourself and our 1-neighbors to detect unidirectionnal links (we have also a knowledge of the 2-Neighborhood)
	while(ptr!=NULL) 
		{
			if ((ptr->hops <= hops_max) && (ptr->address != my_address))
				{
					if (i==MAX_FIELDS_IN_HELLO_KTABLE)
						printf("Error : %d can't place all its neighbours in the packet(%d) , it must use partial neighbourhood\n",my_address,i);
					if ((hello_method == HELLO_METHOD_KTABLE) && (i <= MAX_FIELDS_IN_HELLO_KTABLE) && (ptr->address!=0) && ((ptr->bidirect)||(ptr->hops==1)))
						{
							if (ptr->address==0)
								{
									printf("error, null address in a generated hello packet!\n");
								}
							
							//Fields for Neighbors
							op_pk_nfd_set(pkptr , hello_fields_names[i].address 	, ptr->address);
							op_pk_nfd_set(pkptr , hello_fields_names[i].weight 		, ptr->weight);	
							op_pk_nfd_set(pkptr , hello_fields_names[i].hops 		, ptr->hops);
							op_pk_nfd_set(pkptr , hello_fields_names[i].state 		, ptr->state);	
							op_pk_nfd_set(pkptr , hello_fields_names[i].bidirect 	, ptr->bidirect);
							op_pk_nfd_set(pkptr , hello_fields_names[i].clusterhead	, ptr->clusterhead);

							if (ptr->address==0) 
								{
									sprintf(msg,"Creation in %d of a node with id=0 in a hello packet at %f!\n",my_address,op_sim_time());
									cluster_message(msg);
								}		
							
							if (DEBUG>HIGH) 
								{
									sprintf(msg,"I send an hello : %d with %d hops, a weight of %d and a state of %d (at %f)\n",ptr->address,ptr->hops,ptr->weight,ptr->state,op_sim_time());
									cluster_message(msg);
								}
						}
					if ((hello_method == HELLO_METHOD_RELAY) && (i <= MAX_FIELDS_IN_HELLO_RELAY))
						{
							if (ptr->address==0)
								{
									printf("error, null address in a generated hello packet!\n");
								}
							
							//All the neighbours we declare in HELLO_METHOD_RELAY are 1-neighbours
							//Fields for Neighbors
							op_pk_nfd_set(pkptr , hello_fields_names[i].address		, ptr->address);
							op_pk_nfd_set(pkptr , hello_fields_names[i].weight		, ptr->weight);	
							op_pk_nfd_set(pkptr , hello_fields_names[i].state		, ptr->state);	
							op_pk_nfd_set(pkptr , hello_fields_names[i].bidirect	, ptr->bidirect);
							//op_pk_nfd_set(pkptr , hello_fields_names[i].clusterhead	, ptr->clusterhead);
						}
					i++;
				}
			
			ptr=ptr->next;
		}	
	
	//Deletes useless fields (marked as unset)
	switch(hello_method){
		case HELLO_METHOD_KTABLE:
			for (j=i;  (j<=MAX_FIELDS_IN_HELLO_KTABLE) && (op_pk_nfd_is_set(pkptr,hello_fields_names[j].address))  ; j++)
				{
					op_pk_nfd_strip(pkptr , hello_fields_names[j].address);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].weight);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].hops);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].state);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].bidirect);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].clusterhead);
				}
		break;
		case HELLO_METHOD_RELAY:
			for (j=i;  (j<=MAX_FIELDS_IN_HELLO_RELAY) && (op_pk_nfd_is_set(pkptr , hello_fields_names[j].address))  ; j++)
				{
					op_pk_nfd_strip(pkptr , hello_fields_names[j].address);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].weight);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].state);
					op_pk_nfd_strip(pkptr , hello_fields_names[j].bidirect);
					//op_pk_nfd_strip(pkptr , hello_fields_names[j].clusterhead);
				}
		break;
	}
	return(pkptr);
}


void update_table_neighbours (Packet* pkptr , short ttl_for_pk) {
	char 			msg[250];
	neigh_cell 		*ptr, *ptr2;
	int 			i;
	int				src_temp, addr_temp , bidirect_temp , relay_temp;
	int				weight_temp , state_temp , mobility_temp;
	int				father_temp , id_ap_temp , ap_hops_temp , clusterhead_temp , clusterhead_hops_temp , father_hops_temp;
	short 			hops_temp;
	int				ttl;
	Boolean			is_fields_overflow;
	Boolean			is_source_link_bidirect;
	//The initial TTL set by the source
	short			ttl_initial;
	short			distance_max;
	
	
	//--------------------------------------------
	//	COMMON FIELDS
	//--------------------------------------------	

	//Some usefull fields
	op_pk_nfd_get(pkptr,"SRC",				&src_temp);
	op_pk_nfd_get(pkptr,"RELAY",			&relay_temp);
	op_pk_nfd_get(pkptr,"TTL",				&ttl);

	op_pk_nfd_get(pkptr,"FATHER",			&father_temp);
	op_pk_nfd_get(pkptr,"FATHER_HOPS",		&father_hops_temp);
	op_pk_nfd_get(pkptr,"ID_AP",			&id_ap_temp);

	op_pk_nfd_get(pkptr,"WEIGHT",			&weight_temp);
	op_pk_nfd_get(pkptr,"MOBILITY",			&mobility_temp);
	op_pk_nfd_get(pkptr,"STATE",			&state_temp);

	op_pk_nfd_get(pkptr,"CLUSTERHEAD",		&clusterhead_temp);
	op_pk_nfd_get(pkptr,"CLUSTERHEAD_HOPS",	&clusterhead_hops_temp);

	if (weight_temp == DOMINATOR)
		op_pk_nfd_get(pkptr , "AP_HOPS" , &ap_hops_temp);
	else
		ap_hops_temp = -1;
	
	//--------------------------------------------
	//	BIDIRECTION DETECTION
	//--------------------------------------------	
	
	is_source_link_bidirect = 0;
	
	//Special case: the hello was already forwarded-> it comes mandatory from a bidirectional link
	if ((hello_method==HELLO_METHOD_RELAY) && (ttl < k_cds-1) && (!is_unidirectional_link(relay_temp)))
		is_source_link_bidirect = 1;
	
	//General case: I am in its 1-Neighborhood -> bidirectional link
	i=1;
	is_fields_overflow = 0;
	//If this packet was treated, it is because it comes from a bidirectional link
	if (relay_temp!= src_temp)
		is_source_link_bidirect = OPC_TRUE;
			
	//If this packet comes from a 1-Neighbor, We must see if we are one of its 1-Neighbor	
	while (!is_fields_overflow && (op_pk_nfd_is_set(pkptr , hello_fields_names[i].address)) && (!is_source_link_bidirect))
		{
			op_pk_nfd_get(pkptr , hello_fields_names[i].address , &addr_temp);
			if (addr_temp == my_address)
				{
					if (hello_method==HELLO_METHOD_RELAY)
						is_source_link_bidirect = 1;
			
					if (hello_method==HELLO_METHOD_KTABLE)
						{				
							op_pk_nfd_get(pkptr , hello_fields_names[i].hops , &hops_temp);
							if (hops_temp==1)
								is_source_link_bidirect = 1;
						}
				}			
			i++;
			is_fields_overflow = ((i>MAX_FIELDS_IN_HELLO_KTABLE)&&(hello_method==HELLO_METHOD_KTABLE)) || ((hello_method==HELLO_METHOD_RELAY)&&(i>MAX_FIELDS_IN_HELLO_RELAY)) ;
		}
		
	//The maximal distance of one node
	distance_max = ttl_for_pk;//ttl_for_hellos;
	
		
	//--------------------------------------------
	//	UPDATE THE NEIGHBOR TABLE
	//--------------------------------------------	
	
	//KTABLE : all neighbors declared in the packet, according to the number of hops
	//RELAY  : all neighbors from a bidirectional neighbor are our 2-neighbors
	i=0;	
			
	//Conditions to treat this node :
	//	-Valid Neighbor: bidirectional multihop neighbor /OR/ unidirectional single hop neighbor
	//	-The maximum number of fields in packet is reached --> we exit the procedure

	is_fields_overflow = ((i > MAX_FIELDS_IN_HELLO_KTABLE) && (hello_method == HELLO_METHOD_KTABLE))   ||   ((hello_method == HELLO_METHOD_RELAY) && (i > MAX_FIELDS_IN_HELLO_RELAY)) ;
	while( op_pk_nfd_is_set(pkptr , hello_fields_names[i].address) && ((i==0) || (is_source_link_bidirect)) && !is_fields_overflow )
		{
			//Is this link declared as bidirect (both for relay and ktable: relay must contain unidirect links too, else a link couldn't change from unidirect to bidirect) 
			if (i!=0)
				op_pk_nfd_get(pkptr , hello_fields_names[i].bidirect , &bidirect_temp);
			else
				bidirect_temp = is_source_link_bidirect;
				
			//For each node declared in the packet
			if ((op_pk_nfd_get(pkptr , hello_fields_names[i].address , &addr_temp)) && (op_pk_nfd_get(pkptr , hello_fields_names[i].weight , &weight_temp)) &&  ((bidirect_temp) || (i==0)))
				{								
					op_pk_nfd_get(pkptr , hello_fields_names[i].state , &state_temp);
					op_pk_nfd_get(pkptr , hello_fields_names[i].clusterhead , &clusterhead_temp);
					op_pk_nfd_get(pkptr , hello_fields_names[i].father , &father_temp);

					//Gathers the distance between this node and us
					switch (hello_method)
						{
							//We have a field describing for each neighbor the distance from the advertiser
							case HELLO_METHOD_KTABLE :
								if (i!=0) 
									{
										op_pk_nfd_get(pkptr , hello_fields_names [i].hops , &hops_temp);
										hops_temp++;			//The old hops + 1 hop (between us and the sender)
									}
								//The node is the sender of the hello packet
								else
									hops_temp = 1;			
							break;
										
							//We have no fields containing hops count: there are only 2-neighbors	
							case HELLO_METHOD_RELAY :
								//The TTL set by the source
								ttl_initial = ttl_for_pk;//ttl_for_hellos;
								
								//The Source
								if (i==0)
									hops_temp = ttl_initial - ttl + 1;
								//Its 1-Neighbors
								else
									hops_temp = (ttl_initial - ttl + 1) + 1;
								break;
						}
								
					//Search if the address already exists
					ptr = neighbour_table;														
					while ((ptr!=NULL) && (!((ptr->address==addr_temp) && ((ptr->bidirect==bidirect_temp) || ((ptr->hops==hops_temp)&&(hops_temp==1))))))
						{
							ptr2=ptr; 			//in order to keep the previous cell of the list
							ptr=ptr->next;
						}							
							
					//This address doesn't exist, we add an entry
					//If the address=-1, the field has its default value, so the field is not representative
					if ((ptr==NULL) && (addr_temp!=-1))
						{
							//Changes in physical 1-Neighborhood
							if ((hops_temp == 1) && (op_sim_time() > TIME_BEGIN_TOPO_STATS))
								nb_chgts_real_topo++;
							//Changes in physical k-Neighborhood (for mobility metric)
							nb_chgts_neighbourhood++;

							//Memory Allocation for a new cell in the list of neighbours
							ptr = (struct neigh_cell*)op_prg_mem_alloc(sizeof(neigh_cell));
							if (ptr==NULL)
								printf("error in the memory allocation for the creation of a new cell in the list of neighbours");

							
							//Add the correct content
							ptr->address 			= addr_temp;
							ptr->hops 				= hops_temp;
							ptr->timeout 			= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;	//This node timeouts in TIMEOUT_HELLO seconds
							ptr->relay				= relay_temp;
							ptr->bidirect 			= bidirect_temp;
							
							ptr->weight 			= weight_temp;
							ptr->sleep				= 0;
								
							ptr->state 				= state_temp;
							
							//List of neighbors
							if (i==0)
								{
									ptr->neighbors 			= create_neighbors_list(pkptr);//create_list_from_pk(pkptr);
									ptr->neighbors_timeout 	= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
								}
							else
								empty_list(ptr->neighbors);
							
							//If the field corresonds to the packet headers (or if we have a Ktable)
							if ((i==0) || (hello_method==HELLO_METHOD_KTABLE))
								{
									ptr->father 			= father_temp;
									ptr->clusterhead 		= clusterhead_temp;
									ptr->clusterhead_timeout= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
									if (ptr->clusterhead != 0)
										ptr->cluster_init_flag	= 1;
									else
										ptr->cluster_init_flag	= 0;									
											
									if (i==0)
										{
											ptr->father_hops		= father_hops_temp;
											ptr->id_ap				= id_ap_temp;
											ptr->ap_hops			= ap_hops_temp;
											ptr->clusterhead_hops	= clusterhead_hops_temp;
											ptr->mobility			= mobility_temp;												
										}
									else
										{
											ptr->father_hops		= -1;
											ptr->id_ap				= -1;
											ptr->ap_hops			= -1;
											ptr->clusterhead_hops	= -1;
											ptr->mobility			= -1;
										}
								}
							//If the field is in the 1-neighbors table of the packet
							else
								{
									ptr->father 			= -1;
									ptr->father_hops		= -1;
									ptr->id_ap				= -1;	
									ptr->ap_hops			= -1;
									ptr->mobility			= -1;
									ptr->clusterhead 		= -1;
									ptr->clusterhead_hops	= -1;
									ptr->clusterhead_timeout= -1;
									ptr->cluster_init_flag	= 1;
								}
							
							//We create a new list for cluster-neighbors for this entry
							(ptr->gw_list) = op_prg_list_create();

							//We fill this cluster-neighbor List for this node only if it is the originator
							if (i==0)
								{
									fill_gw_list_with_hello_pk(pkptr , ptr->gw_list);
									ptr->gw_timeout = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
								}
							
							//DEBUG Infos
							if (DEBUG>MAX)
								{
									sprintf(msg,"%d added (%f) in NEIGH_TABLE : weight=%d, hops=%d, state=%d, father=%d, father_hops=%d, ch=%d (%d/%d), originator=%d, relay=%d, bidirect=%d, timeout=%f\n", ptr->address , op_sim_time() , ptr->weight , ptr->hops , ptr->state, ptr->father, ptr->father_hops , ptr->clusterhead, ptr->clusterhead_hops, ptr->cluster_init_flag, src_temp , ptr->relay , ptr->bidirect , op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO);
									cluster_message(msg);
								}

							//Error
							if (ptr->address==0)
								{
									printf("null address in a received hello packet\n");
									op_pk_print(pkptr);
								}						

							//Updates the pointers
							ptr->next = NULL;
							ptr2->next = ptr;
						}					
					//The address already exists, we have just to update it if :
					//- It's not my address (we don't update our own address)
					//- The hops declared by the sender are lower that the hops in our table
					//- The timeout is near and we must find another way in order to avoid the deletion of this entry
					//else if ((ptr != NULL) && (((addr_temp != my_address) && (ptr->hops >= hops_temp))  ||  (ptr->timeout < op_sim_time()+INTERVALL_HELLO)))
					else if ((ptr != NULL) && (addr_temp != my_address) &&   ((ptr->hops >= hops_temp) || (ptr->timeout-INTERVALL_HELLO*TIMEOUT_HELLO+INTERVALL_HELLO < op_sim_time() ))  )
					//else if ((ptr != NULL) && (addr_temp != my_address))    // (( && (ptr->hops >= hops_temp))  ||  (ptr->timeout < op_sim_time()+INTERVALL_HELLO)))
						{									
							if (ptr->hops > hops_temp)
								{
									if (((hops_temp == 1) || (hops_temp==1)) && (op_sim_time() > TIME_BEGIN_TOPO_STATS))
										nb_chgts_real_topo++;
									
									nb_chgts_neighbourhood++;
								}
							
							// We change main info on this entry
							if ((ptr->hops >= hops_temp) || (ptr->timeout < op_sim_time()+INTERVALL_HELLO))
								{
									ptr->hops 				= hops_temp;
									ptr->timeout 			= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;	//This node timeouts in TIMEOUT_HELLO seconds
									ptr->relay				= relay_temp;
									ptr->bidirect 			= bidirect_temp;
							
									//List of neighbors
									if (i==0)
										{
											ptr->neighbors 			= create_neighbors_list(pkptr);//create_list_from_pk(pkptr);
											ptr->neighbors_timeout 	= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
										}
									else if (ptr->neighbors_timeout < op_sim_time())
										empty_list(ptr->neighbors);							

									//If the field corresponds to the packet headers (or if we have a Ktable)
									if ((i==0) || (hello_method==HELLO_METHOD_KTABLE))
										{
											ptr->father 			= father_temp;
											ptr->clusterhead		= clusterhead_temp;
											ptr->clusterhead_timeout= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
											if (ptr->clusterhead != 0)
												ptr->cluster_init_flag	= 1;
											
											if (i==0)
												{
													ptr->father_hops		= father_hops_temp;
													ptr->id_ap				= id_ap_temp;
													ptr->ap_hops			= ap_hops_temp;
													ptr->clusterhead_hops	= clusterhead_hops_temp;
													ptr->mobility			= mobility_temp;												
												}
											else
												{
													ptr->father_hops		= -1;
													ptr->id_ap				= -1;
													ptr->ap_hops			= -1;
													ptr->clusterhead_hops	= -1;
													ptr->mobility			= -1;
												}
										}
									else 
										{
											ptr->father 			= -1;
											ptr->father_hops		= -1;
											ptr->id_ap				= -1;
											ptr->ap_hops			= -1;
											ptr->mobility			= -1;
											if (ptr->clusterhead_timeout < op_sim_time())
												ptr->clusterhead	= -1;
											ptr->clusterhead_hops	= -1;
											ptr->cluster_init_flag	= 1;
										}
									}
							
							
							//Other info (potentially obtained via a non-relay node
							ptr->weight 			= weight_temp;
							ptr->sleep				= 0;
								
							ptr->state 				= state_temp;
							
							
							//Fills the Gateway List for this node (Only if it is the originator, else we don't have its cluster-neighbors)
							//The cell already exist -> We don't need to create a NEW list
							if (i==0)
								{
									fill_gw_list_with_hello_pk(pkptr , ptr->gw_list);
									ptr->gw_timeout = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
								}
							else if (ptr->gw_timeout < op_sim_time())
								empty_gw_list(ptr->gw_list);
							
							//DEBUG Infos
							if (DEBUG>MAX)
								{
									sprintf(msg,"%d updated (%f) in NEIGH_TABLE : weight=%d, hops=%d, state=%d, father=%d, father_hops=%d, ch=%d (%d/%d), originator=%d, relay=%d, bidirect=%d, timeout=%f\n", ptr->address , op_sim_time() , ptr->weight , ptr->hops , ptr->state , ptr->father, ptr->father_hops , ptr->clusterhead, ptr->clusterhead_hops, ptr->cluster_init_flag, src_temp , ptr->relay , ptr->bidirect , op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO);
									cluster_message(msg);
								}

						}
				}
			i++;
			is_fields_overflow = ((i>MAX_FIELDS_IN_HELLO_KTABLE)&&(hello_method==HELLO_METHOD_KTABLE)) || ((hello_method==HELLO_METHOD_RELAY)&&(i>MAX_FIELDS_IN_HELLO_RELAY)) ;
		}	
	
	//--------------------------------------------
	//		CDS CONNECTORS
	//--------------------------------------------	
	
	//We adds the node as potential cds-connector if it is a bidirectional (and potential multihops) neighbor 
	if (!is_unidirectional_link(relay_temp))
		register_ap_neigh(pkptr);
	
		
}


//Returns OPC_TRUE if aadr is one of my 1-neighbors
Boolean is_neighbor(int address, short dist){
	neigh_cell	*ptr;
	
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			if ((ptr->address == address) && (ptr->bidirect) && (ptr->hops <= dist))
				return(OPC_TRUE);
			ptr = ptr->next;
		}
	return(OPC_FALSE);
}

//Returns the ratio of the nb of edges to and between my 1-Neighbors and the nb of 1-neighbors
double compute_my_closed_degree(short d){
	neigh_cell	*ptr;
	int			nb_edges 	= 0;
	int			nb_vertices = 0;
	neigh_min	*elem;
	int			i;
	
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			//is the node a d-neighbor and bidirect ?
			if ((ptr->address != my_address) && (is_neighbor(ptr->address , 1)) && (ptr->hops <= d))
				{
					//the node is a d-neighbor
					nb_edges++;
					nb_vertices++;
					
					//Count each edge to one d-neighbor
					for(i=0 ; i<op_prg_list_size(ptr->neighbors); i++)
						{
							elem = op_prg_list_access(ptr->neighbors, i);
							if (is_neighbor(elem->address , d))
								nb_edges++;						
						}
					
				}
			ptr = ptr->next;
		}
	
	//I return the metric
	//NB : I count every edge twice (one for each extremity)
	if (nb_vertices != 0)
		return((double)nb_edges / (2*nb_vertices));
	else
		return(0);
}

/*Update the weight of my node (it depends of many parameters)*/
/*Temporary, My weight=My k-density (the nb of neighbours)*/
void update_my_weight() {
	char		msg[150];
	neigh_cell	*ptr_neigh;
	int			my_degree , i;
	int			mob_average , nb_neigh;
	double		mob_result;
	double		mob_max , mob_min , mob_temp;
	double		my_mob_metric , my_density_metric , my_importance_metric , my_energy_metric;
	double		x , y , distance;		//actual positions and traversed distance 
	double		penalty; 				//Penalty for low_energy nodes
	int			nb_neighbours_k_cds;
	
	
	
	
	//------- Start of computing of Theo Weight -----------
	if ((metric==THEO_WEIGHT)&&(!is_wireless_router))
		{
			//--------------------------------------------
			//	Nb Nodes changed in my neighbourhood
			//--------------------------------------------	
			//We compute the number of changed nodes and store it in an array
			i=0;
			while(my_weight.last_neigh_changements[i][0]!=-1) {i++;}
			my_weight.last_neigh_changements[i][0] = nb_chgts_neighbourhood;
			my_weight.last_neigh_changements[i][1] = nb_neighbours(k_cds);
			nb_chgts_neighbourhood = 0;

			if (i == NB_STORED_SPEEDS-1)
				{
					my_weight.last_neigh_changements[0][0] = -1;
					my_weight.last_neigh_changements[0][1] = -1;
				}
			else
				{
					my_weight.last_neigh_changements[i+1][0] = -1;
					my_weight.last_neigh_changements[i+1][1] = -1;
				}
	
			//Compute the mobility metric
			//NB : mob_max = 2 (all my neighbours are new, and all the precedent were deleted) -> we normalize it in order to have a metric between 0 and 1
			my_mob_metric = 0;
			sprintf(msg,"Chgts : ");
			for (i=0;i < NB_STORED_SPEEDS;i++)
				{
					if ((my_weight.last_neigh_changements[i][0]!=-1)&&(my_weight.last_neigh_changements[i][1]!=0))			//If no neighbours, the mobility metric is not significative
						my_mob_metric += (double)my_weight.last_neigh_changements[i][0] / 20;//(double)my_weight.last_neigh_changements[i][1];
					//sprintf(msg,"%s - %d/%d ",msg,my_weight.last_neigh_changements[i][0],20);//my_weight.last_neigh_changements[i][1]);
				}
			//sprintf(msg,"%s\n",msg);
			//cluster_message(msg);
			
			//We divide by NB_STORED_SPEEDS to eliminate the influence of the nb of values stored to compute the metric	
			//We have a local metric (the changes in neighbourhood, that we will diffuse for our neighbours)
			my_mob_metric = exp(-my_mob_metric / NB_STORED_SPEEDS);
			my_weight.mobility = my_mob_metric * MAX_WEIGHT;

			//We observe our neighbourhood table to have :
			//The max/Min/Average mobility
			mob_average = 0;
			nb_neigh = 0;
			ptr_neigh = neighbour_table;
			mob_max = my_weight.mobility;
			mob_min = my_weight.mobility;
			while(ptr_neigh !=NULL)
				{
					if ((ptr_neigh->hops <= k_cds)&&(ptr_neigh->bidirect)&&(ptr_neigh->mobility>1))
						{
							nb_neigh++;
							mob_average += ptr_neigh->mobility;
							if (mob_max < ptr_neigh->mobility)
								mob_max = ptr_neigh->mobility;
							if (mob_min > ptr_neigh->mobility)
								mob_min = ptr_neigh->mobility;
							
						}
					ptr_neigh = ptr_neigh->next;
				}
			//We will normalize all values and will keeps the final mobility metric between 0 and MAX_WEIGHT(255) (the node with minimal mobliity has 0, and thus whith max, 255)
			if ((nb_neigh!=0)&&(mob_max - mob_min!=0))
				{
					//We normalize values (difference with the average 'mobility')
					mob_min = (float)mob_min - (mob_average/nb_neigh);
					mob_max = (float)mob_max - (mob_average/nb_neigh);
					mob_temp = (float)my_weight.mobility - (mob_average/nb_neigh);
					
					//We scale mob_result between 0 and MAX_WEIGHT
					mob_result = MAX_WEIGHT*(mob_temp - mob_min)/(mob_max - mob_min);
				}
			//If 0 division -> weight = default (not enough data)	
			else
				mob_result = 125;
			//Normalization between 0 and 1
			my_mob_metric = mob_result/MAX_WEIGHT;
			
			//sprintf(msg,"new mob metric =%f (%d / %d) (mob_temp=%f mob_min=%f mob_max=%f)\n",mob_result,mob_average,nb_neigh,mob_temp,mob_min,mob_max);
			//cluster_message(msg);
			
	
			//----------------------------------------------------
			//	Degree + Importance + Stores the last neigh_table
			//----------------------------------------------------
			//We compute our degree and store the actual neighbour table
			my_degree = nb_neighbours(k_cds);
			//To compute density_metric (inverse of the difference between this degree and the optimal degree):			
			my_density_metric = 1 -(float)abs(my_degree - OPTIMAL_K_DENSITY)/20;
			if (my_density_metric < 0.1)
				my_density_metric = 0.1;
			
			
			//sprintf(msg,"metric density : %f | degree=%d\n",my_density_metric,my_degree);
			//cluster_message(msg);

			//The metric of importance of a dominator / clusterhead is the proportion of its neighbours for those it's usefull
			//Temporary desactivated
			my_importance_metric = 0;//my_importance_metric / my_degree;
	
	
	
			//--------------------------------------------
			//	Energy Metric
			//--------------------------------------------
			my_energy_metric = my_energy.value / my_energy.max_capacity;
	
	}
	//------- End of computing of Theo Weight -----------
	
	
	
	
	//--------------------------------------------
	//	Final Metric
	//--------------------------------------------
	switch(metric){
		case OTHER_DEGREE :
				my_weight.value = (int) 50*compute_my_closed_degree(1);
			break;
		case LOWEST_ID:
				//To have a final weight between 0 and MAX_WEIGHT
				my_weight.value = MAX_WEIGHT - my_address*(MAX_WEIGHT/nb_total);
				//my_weight.value = MAX_WEIGHT/my_address;
			break;
		case HIGHEST_DEGREE:
				nb_neighbours_k_cds = nb_neighbours(k_cds);
				if (nb_neighbours_k_cds < MIN_K_DEGREE)
					MIN_K_DEGREE = nb_neighbours_k_cds;
				if (nb_neighbours_k_cds > MAX_K_DEGREE)
					MAX_K_DEGREE = nb_neighbours_k_cds;
				my_weight.value = (int) ((double)((double)nb_neighbours_k_cds - MIN_K_DEGREE) / ((double)MAX_K_DEGREE - MIN_K_DEGREE) * MAX_WEIGHT);
			break;
		case MOBILITY:
				//get new coordinates ("god mode")
				op_ima_obj_attr_get(op_topo_parent (op_id_self()),"x position",&x);
				op_ima_obj_attr_get(op_topo_parent (op_id_self()),"y position",&y);

				//Finds the last modified entry
				i=0;
				while(last_absolute_speeds[i]!=-1) 	
					{
						i++;
					}

				//Computes the new speed and Stores it with other parameters
				distance = sqrt((last_xy.x - x)*(last_xy.x - x) +  (last_xy.y - y)*(last_xy.y - y));
				last_absolute_speeds[i] = distance / (op_sim_time() - my_weight.time_last_computation);
				my_weight.time_last_computation = op_sim_time();
				last_xy.x = x;
				last_xy.y = y;		
				if (last_absolute_speeds[i] < 0.1)
					last_absolute_speeds[i] = 0.1;
				
				//Store the control value to define actual position
				if (i == NB_STORED_SPEEDS-1)
					last_absolute_speeds[0]=-1;
				else
					last_absolute_speeds[i+1]=-1;
				
				//print_absolute_speeds();
				
				//Computes the new weight
				my_weight.value = 1;
				for(i=0;i<NB_STORED_SPEEDS;i++)
					{
						//Max speed
						if (last_absolute_speeds[i] > MAX_SPEED)
							MAX_SPEED = last_absolute_speeds[i];
						
						//New weight
						if (last_absolute_speeds[i]!=-1)
							my_weight.value += (MAX_SPEED - last_absolute_speeds[i]) * MAX_WEIGHT / MAX_SPEED;
					}
				
				//normalization, independance if the nb of stored speeds
				my_weight.value = my_weight.value / NB_STORED_SPEEDS;
		
				
			break;
		case THEO_WEIGHT:
				if ((is_wireless_router) || (is_AP))
					my_energy_metric = 1;

				if (energy_management == NO_ENERGY)
					my_weight.value = 8*( 5*my_density_metric + 20*my_mob_metric );
				else
					{
						penalty = 0.3;
						if (my_energy.value > LOW_ENERGY)
							penalty = 0.5;
						if (my_energy.value > MEDIUM_ENERGY)
							penalty = 0.7;
						if (my_energy.value > HIGH_ENERGY)
							penalty = 1;

						my_weight.value = 5*penalty*( 5*my_density_metric + 20*my_mob_metric);
					}

				//Special Max Weight for AP and Wireless Routers
				if ((is_wireless_router)||(is_AP))
					{
						my_weight.value = MAX_WEIGHT;
						my_weight.mobility = MAX_WEIGHT;
					}
			break;	
	}
	//We have a 8 bits field to store the weight in packets -> Weight_max=MAX_WEIGHT
	if (my_weight.value > MAX_WEIGHT)
		my_weight.value = MAX_WEIGHT;
	if (my_weight.value < 1)
		my_weight.value = 1;
	//the AP weight
	if ((is_AP) || (is_wireless_router))
		my_weight.value = MAX_WEIGHT;
	

	
	//--------------------------------------------
	//	Store it in our table
	//--------------------------------------------
	//We search the entry which corresponds to us (normally useless, because we are the first entry of the neighbour_table)
	ptr_neigh=neighbour_table;
	while ((ptr_neigh!=NULL) && (ptr_neigh->address!=my_address))
		{
			ptr_neigh = ptr_neigh->next;
		}	

	//We update our weight in the neighbour_table
	if ( (ptr_neigh!=NULL) && (ptr_neigh->address==my_address) )
		ptr_neigh->weight = my_weight.value;
	else
		{
			cluster_message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n We have encountered an error : my address is not present in my neighbour_table ! \n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n We (%d) have encountered an error : my address is not present in my neighbour_table ! \n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",my_address);
			
			//Memory Allocation for a new cell in the list of neighbours
			ptr_neigh = (struct neigh_cell*)op_prg_mem_alloc(sizeof(neigh_cell));
			if (ptr_neigh==NULL)
				{
					printf("error in the memory allocation for the creation of a new cell in the list of neighbours");
				}

			//Add the correct content
			ptr_neigh->address 		= my_address;
			ptr_neigh->weight	 	= my_weight.value;
			ptr_neigh->hops 		= 0;
			ptr_neigh->timeout 		= 9999999.0;
			ptr_neigh->state 		= my_cds.state;
			ptr_neigh->bidirect 	= 1;
			ptr_neigh->sleep		= is_sleeping.value;
			ptr_neigh->father 		= my_cds.father;
			ptr_neigh->clusterhead 	= my_clusterhead.address;
			ptr_neigh->clusterhead_hops 	= my_clusterhead.hops;
			
			//Neighbors list
			ptr_neigh->neighbors	= op_prg_list_create();
			
			//Updates the pointers
			ptr_neigh->next 		= neighbour_table;
			neighbour_table 		= ptr_neigh;
			
		}

}

/* We have to delete all the timeout entries in the neighbour_table and id_table*/
void update_tables_periodic(int* arg, int code){
	update_tables();
	delete_timeout_in_ici_list();
	
	op_intrpt_schedule_call(op_sim_time() + INTERVALL_UPDATE_TABLE, UPDATE_TABLE_CODE , update_tables_periodic , -1);
}


//empty one neighbor table
void empty_neighbour_table(neigh_cell **its_ptr_neigh_table, int its_address){
		neigh_cell		*its_neigh_table; 
		neigh_cell		*ptr_neighbour, *ptr_neighbour2; 
		neigh_min		*elem;

		//Ptr copy
		its_neigh_table = *its_ptr_neigh_table;
		
		
		//We delete the timeout entries in neighbour_table
		ptr_neighbour = its_neigh_table;
		while(ptr_neighbour!=NULL)
			{
				if (ptr_neighbour->address != its_address)
					{
						//deletes the list of neighbors
						while(op_prg_list_size(ptr_neighbour->neighbors) != 0)
							{
								elem = op_prg_list_remove(ptr_neighbour->neighbors, OPC_LISTPOS_TAIL);
								free(elem);
							}						
						
						//delete the cell
						if (ptr_neighbour == its_neigh_table) //The particular case of a delete entry in head of the list 
							{
								its_neigh_table = ptr_neighbour->next;
								free(ptr_neighbour);
								ptr_neighbour = its_neigh_table;
							}
						else
							{
								ptr_neighbour2->next = ptr_neighbour->next;
								free(ptr_neighbour);
								ptr_neighbour = ptr_neighbour2;
							}
					}					
				
				ptr_neighbour2 = ptr_neighbour;
				if (ptr_neighbour!=NULL)
					ptr_neighbour =  ptr_neighbour->next;
			}

}

//empty one neighbor table
void delete_in_neighbour_table(neigh_cell **its_ptr_neigh_table, int its_address){
		neigh_cell		*its_neigh_table; 
		neigh_cell		*ptr_neighbour, *ptr_neighbour2; 
		neigh_min		*elem;

		//Ptr copy
		its_neigh_table = *its_ptr_neigh_table;
		
		
		//We delete the timeout entries in neighbour_table
		ptr_neighbour = its_neigh_table;
		while(ptr_neighbour!=NULL)
			{
				if (ptr_neighbour->address == its_address)
					{
						//deletes the list of neighbors
						while(op_prg_list_size(ptr_neighbour->neighbors) != 0)
							{
								elem = op_prg_list_remove(ptr_neighbour->neighbors, OPC_LISTPOS_TAIL);
								free(elem);
							}						
						
						//delete the cell
						if (ptr_neighbour == its_neigh_table) //The particular case of a delete entry in head of the list 
							{
								its_neigh_table = ptr_neighbour->next;
								free(ptr_neighbour);
								ptr_neighbour = its_neigh_table;
							}
						else
							{
								ptr_neighbour2->next = ptr_neighbour->next;
								free(ptr_neighbour);
								ptr_neighbour = ptr_neighbour2;
							}
					}					
				
				ptr_neighbour2 = ptr_neighbour;
				if (ptr_neighbour!=NULL)
					ptr_neighbour =  ptr_neighbour->next;
			}

}

//empty one neighbor table
void clear_in_all_neighbour_table(int its_address){
	int			network_id;
	int			failed_node_remote_id;
	int			failed_process_remote_id;
	int			*failed_node_address_ptr;
	neigh_cell	**failed_neighbour_table;
	int			i;
	
	
	network_id 					= op_id_parent 	(op_id_parent( op_id_self() ) );
	
	for (i=0; i < op_topo_object_count( OPC_OBJTYPE_NDMOB) ; i++)
		{
			failed_node_remote_id		= op_id_from_sysid		(OPC_OBJTYPE_NDMOB , i);
			failed_process_remote_id	= op_id_from_name 		(failed_node_remote_id , OPC_OBJMTYPE_QPS , "cds-cluster");
			failed_neighbour_table		= op_ima_obj_svar_get	(failed_process_remote_id, "neighbour_table");
			failed_node_address_ptr		= op_ima_obj_svar_get	(failed_process_remote_id, "my_address");	
			
			if (its_address != *failed_node_address_ptr)
				delete_in_neighbour_table(failed_neighbour_table , its_address);
		}
}

//Updates periodically the tables
void update_tables(){
		neigh_cell		*ptr_neighbour, *ptr_neighbour2; 
		neigh_min		*elem;
		id_cell			*ptr_id, *ptr_id2;
		relay_cell		*ptr_relay, *ptr_relay2;
		ap_hellos		*ptr_hello, *ptr_hello2;
		double			actual_time;
		char			msg[500];
		
		current_id = op_dist_uniform(64000);	
		actual_time =  op_sim_time();
		
		//We delete the timeout entries in id_table
		ptr_id = id_table;
		while(ptr_id!=NULL)
			{
				if (ptr_id->timeout < actual_time)	//The entry is obsolete
					{
						if (ptr_id == id_table) //The particular case of a delete entry in head of the list (not tested, I believe)
							{
								id_table = ptr_id->next;
								free(ptr_id);
								ptr_id = id_table;
							}
						else
							{
								ptr_id2->next = ptr_id->next;
								free(ptr_id);
								ptr_id = ptr_id2;
							}
					}
				ptr_id2 = ptr_id;
				if (ptr_id!=NULL)
					ptr_id = ptr_id->next;
			}	
		
		//We delete the timeout entries in relay table
		ptr_relay = relay_table;
		while(ptr_relay!=NULL)
			{
				if (ptr_relay->timeout < actual_time)	//The entry is obsolete
					{
						if (ptr_relay == relay_table) //The particular case of a delete entry in head of the list 
							{
								relay_table = ptr_relay->next;
								free(ptr_relay);
								ptr_relay = relay_table;
							}
						else
							{
								ptr_relay2->next = ptr_relay->next;
								free(ptr_relay);
								ptr_relay = ptr_relay2;
							}
					}
				ptr_relay2 = ptr_relay;
				if (ptr_relay!=NULL)
					ptr_relay = ptr_relay->next;
			}	
		
		//We delete the timeout entries in the ap_hellos table
		ptr_hello=ap_hellos_table;
		while(ptr_hello!=NULL)
			{
				if (ptr_hello->last_seen < actual_time - 5*INTERVALL_AP_HELLO)			//I keep on maximum the 5 last ap-hellos
					{
						if (ptr_hello==ap_hellos_table) //The particular case of a delete entry in head of the list 
							{
								ap_hellos_table = ptr_hello->next;
								free(ptr_hello);
								ptr_hello = ap_hellos_table;
							}
						else
							{
								ptr_hello2->next = ptr_hello->next;
								free(ptr_hello);
								ptr_hello = ptr_hello2;
							}
					}			   
				ptr_hello2 = ptr_hello;
				//We can have ptr_hello==NULL because we might have deleted one entry in the list, (and possibly the last entry of the list)
				if (ptr_hello!=NULL)
					ptr_hello =  ptr_hello->next;
			}	
		
		
		//We delete the timeout entries in neighbour_table
		ptr_neighbour=neighbour_table;
		while(ptr_neighbour!=NULL)
			{
				//We don't delete entries corresponding to an AP if we are an AP
				if ((is_AP) && (ptr_neighbour->address <= nb_aps))// && (!my_cds.cluster_init_flag))//&&(ptr_neighbour->timeout < actual_time))
					{
						ptr_neighbour->timeout 				= 9999999.0;

						ptr_neighbour->state 				= DOMINATOR;
						ptr_neighbour->id_ap	 			= ptr_neighbour->address;
						ptr_neighbour->clusterhead 		 	= ptr_neighbour->address;

					}
					
				if ((ptr_neighbour->timeout < actual_time) && (ptr_neighbour->address != my_address))
					{
						if ((ptr_neighbour->hops==1) && (ptr_neighbour->bidirect) && (op_sim_time() > TIME_BEGIN_TOPO_STATS))
							nb_chgts_real_topo++;
						if (ptr_neighbour->bidirect)
							nb_chgts_neighbourhood++;

						if (DEBUG>HIGH)
							{
								sprintf(msg,"%d deleted in NEIGH_TABLE (%f)\n",ptr_neighbour->address,op_sim_time());
								cluster_message(msg);
							}
						
						//deletes the list of neighbors
						while(op_prg_list_size(ptr_neighbour->neighbors) != 0)
							{
								elem = op_prg_list_remove(ptr_neighbour->neighbors, OPC_LISTPOS_TAIL);
								free(elem);
							}						
						
						//delete the cell
						if (ptr_neighbour==neighbour_table) //The particular case of a delete entry in head of the list 
							{
								neighbour_table = ptr_neighbour->next;
								free(ptr_neighbour);
								ptr_neighbour = neighbour_table;
							}
						else
							{
								ptr_neighbour2->next = ptr_neighbour->next;
								free(ptr_neighbour);
								ptr_neighbour = ptr_neighbour2;
							}
					}					
				
				ptr_neighbour2 = ptr_neighbour;
				if (ptr_neighbour!=NULL)
					ptr_neighbour =  ptr_neighbour->next;
			}
}

void delete_duplicated_entries_in_neigh_table(){
	neigh_cell 	*ptr, *ptr3, *ptr4;
	int			hops_temp , bidirect_temp , address_temp; 	
	char		msg[200];

	
	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			//Infos of the current entry
			address_temp = ptr->address;
			hops_temp = ptr->hops;
			bidirect_temp = ptr->bidirect;
			
			//Search in all the table an entry that is redundant (the link is unidirectional or there exists the same entry with more hops)
			ptr3 = neighbour_table;
			if ((bidirect_temp)&&(hops_temp==1))
				{
					while(ptr3!=NULL)
						{
							if ((ptr3->address == address_temp) && ((ptr3->bidirect==0) || (ptr3->hops>hops_temp)))
								{
									if (DEBUG>MEDIUM)
										{
											sprintf(msg,"%d deletes in neighbour_table addr=%d, hops=%d, bidirect=%d (duplicate of addr=%d, hops=%d, bidirect=%d)\n",my_address,ptr3->address,ptr3->hops,ptr3->bidirect,address_temp,hops_temp,bidirect_temp);
											cluster_message(msg);
										}
									if (ptr3==neighbour_table) 
										{
											neighbour_table = ptr3->next;
											free(ptr3);
											ptr3 = neighbour_table;
										}	
									else
										{
											ptr4->next = ptr3->next;
											free(ptr3);
											ptr3 = ptr4;
										}
								}
				
							ptr4 = ptr3;
							if (ptr3!=NULL)
								ptr3 =  ptr3->next;
						}
				}
			if (ptr!=NULL)
				ptr=ptr->next;
		}

}


//Returns:
// 1 if the 1-link between us and addr is unidirectionnal
// 0 if bidirectionnal
// -1 if such a link doesn't exist in our neighbour_table
int is_unidirectional_link(int addr){
	neigh_cell	*ptr;
	
	ptr=neighbour_table;
	while ((ptr!=NULL)&&(!((ptr->address==addr)&&(ptr->hops==1))))
		ptr=ptr->next;

	if (ptr == NULL)
		return(-1);
	else if (ptr->bidirect)
		return(0);
	else if (!ptr->bidirect)
		return(1);		
}

//Returns the number of sons associated to one particular node
int get_nb_sons(int father){
	neigh_cell	*ptr_neigh;
	int			nb_sons = 0;	

	ptr_neigh = neighbour_table;
	while (ptr_neigh != NULL)
		{
			if (ptr_neigh->father == father)
				nb_sons++;
			ptr_neigh	= ptr_neigh->next;
		}	
	return(nb_sons);
}

//Have I a valid parent ?
Boolean is_my_father_alive_for_dominator(){
	neigh_cell	*ptr_neigh;
	Boolean		is_father_alive;
	Boolean		is_father_gone;
	char		msg[200];
	
	ptr_neigh = neighbour_table;
	while (ptr_neigh != NULL)
		{
			if (ptr_neigh->address==my_cds.father)
				{
					//Our father is dead if : the link is unidirecional | it is farther than 1 hop | we have lost 2 hellos | it's not yet dominator		
 					is_father_gone =  ((ptr_neigh->state != DOMINATOR) || (ptr_neigh->hops > 1) || (ptr_neigh->bidirect == 0));
 					
 					//if ((ptr_neigh->address != my_address) && (!is_father_gone) && (my_cds.last_hello_ap_seen > op_sim_time() - INTERVALL_AP_HELLO*TIMEOUT_AP_HELLO))
 					if ((!is_father_gone) && (my_cds.last_hello_ap_seen > op_sim_time() - INTERVALL_AP_HELLO*TIMEOUT_AP_HELLO))
 						is_father_alive = OPC_TRUE;
 					else if (DEBUG>LOW)
 						{
 							sprintf(msg, "PARENT DEAD: state %d, / hops %d / bidirect %d / last_ap_hello %f\n", ptr_neigh->state , ptr_neigh->hops , ptr_neigh->bidirect , my_cds.last_hello_ap_seen);
 							cluster_message(msg);
 						}
				}
			ptr_neigh	= ptr_neigh->next;
		}
	return(is_father_alive);
}

//Return 1 if addr is in one hops_max-neighbourhood(and the entry is not too old)
int	is_one_valid_neighbour(int addr, short hops_max){
	neigh_cell	*ptr;
	
	ptr=neighbour_table;
	while((ptr!=NULL)&&(ptr->address!=addr))
		{
			ptr = ptr->next;
		}
	//I can miss one hello, not 2. 
	return ((ptr != NULL)&&(ptr->hops<=hops_max)&&(ptr->timeout-TIMEOUT_HELLO*INTERVALL_HELLO>op_sim_time()-2.01*INTERVALL_HELLO));
}

//Return 1 if addr is this address corresponds to a father or son that exists (with a valid hello entry)
int	is_one_valid_father_or_son(int addr){
	neigh_cell	*ptr;
	
	//Verify that the node is one son or father
	if ((!is_my_son(addr)) && (addr!=my_cds.father))
		return(0);
		
	//Verify that it is present in the neighbour_table
	ptr=neighbour_table;
	while((ptr!=NULL)&&(ptr->address!=addr))
		{
			ptr = ptr->next;
		}
	//I can miss one hello, not 2. 
	return ((ptr != NULL)&&(ptr->hops==1)&&(ptr->timeout-TIMEOUT_HELLO*INTERVALL_HELLO>op_sim_time()-2.1*INTERVALL_HELLO));
}	
	
	
//returns the number of neighbors	
int nb_neighbours(int hops_max){
	neigh_cell	*ptr_neigh;
	int nb;
	
	ptr_neigh = neighbour_table;
	nb = 0;
	while (ptr_neigh!=NULL)
		{
			if (ptr_neigh->hops <= hops_max)
				nb++;
			ptr_neigh = ptr_neigh->next;
		}
	nb--;		//I am not my own neighbour
	return(nb);
}

	
//Returns :
//-the number of unique secondary_fathers
//-an array of int (result) with all secondary fathers contained in ptr, but whithout doubles
int delete_double_secondary_fathers(candidate* ptr,int result[]){
	int 	nb_fathers=0;		//Nb unique secondary fathers
	int		found;				//The address is a double (already in result array)
	int		i;					//Control variables
	
	//Initialization of the array
	for(i=0 ; i<MAX_NB_NODES ; i++)
		{
			result[i] = 0;
		}

	//Add iteratively each secondary father if not already present in the result array
	nb_fathers = 0;
	while(ptr!=NULL)
		{
			//Is this entry already present in result ?
			found = 0;
			for(i=0;i<nb_fathers;i++)
				{
					if(result[i]==ptr->address)
						found = 1;								
				}
			
			//Ad the entry if not found
			if (!found)
				{
					result[nb_fathers++] = ptr->address;
				}
			
			//Next secondary father
			ptr = ptr->next;
		}
	return(nb_fathers);
}
	
	
/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//											UTILS



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/

//Returns the maximum value (either v1 or v2)
int get_max(int v1 , int v2){
	if (v1 > v2)
		return(v1);
	else
		return(v2);
}

//Is my cds valid (!=-1 and !=0)
Boolean	 is_father_valid(int addr){
	if ((addr != 0) && (addr != -1))
		return(OPC_TRUE);
	else
		return(OPC_FALSE);
}

/*-----------------------------------------------------------------------------------------------

										MOBILITY DEBUG

-----------------------------------------------------------------------------------------------*/	

List* create_list_from_pk(Packet* pkptr){
	//Result
	List* 		list_result;
	//Control
	int			i;
	int			*elem;
	//Pk Info
	int			hops;
	int			address;
	Boolean		bidirect;
	
	//Initialization
	list_result = op_prg_list_create();;
	//list_result = op_prg_mem_alloc (sizeof(List));
	
	//Adds the 1-bidirect-neighbors in the list
	i = 1;
	while((i <= MAX_FIELDS_IN_HELLO_KTABLE) && (op_pk_nfd_is_set(pkptr , hello_fields_names[i].address)))
		{
			//Get Info
			op_pk_nfd_get(pkptr , hello_fields_names[i].address 	, &address);
			op_pk_nfd_get(pkptr , hello_fields_names[i].bidirect 	, &bidirect);
			if (hello_method == HELLO_METHOD_KTABLE)
				op_pk_nfd_get(pkptr , hello_fields_names[i].bidirect , &hops);
			else
				hops = 1;
			
			//If valid 1-bidirect-neighbors, adds it in the list
			if ((bidirect) && (hops == 1))
				{
					elem = (int*) op_prg_mem_alloc(sizeof(int));
					*elem = address;
					op_prg_list_insert(list_result , elem , i);
				}
			i++;
		}
	
	//result
	return(list_result);
}


void print_absolute_speeds(){
	int 	i;
	char	msg[150];

	cluster_message("____________Absolute Speeds_____________\n");
	for(i=0;i<NB_STORED_SPEEDS;i++)
		{
			sprintf(msg,"Speed [%d] = %f\n",i,last_absolute_speeds[i]);
			cluster_message(msg);
		}
	cluster_message("_________________________________________\n");
}

void print_stats_about_mobility(){
		char	msg[150];
		int		i;
			
		for(i=0;i<NB_STORED_SPEEDS;i++)
			{
				sprintf(msg,"nb_chgts[%d]= %d  |  ",i,my_weight.last_neigh_changements[i][0]);
				cluster_message(msg);
			}
		cluster_message("\n");
		for(i=0;i<NB_STORED_SPEEDS;i++)
			{
				sprintf(msg,"nb_nodes[%d]= %d  |  ",i,my_weight.last_neigh_changements[i][1]);
				cluster_message(msg);
			}
		cluster_message("\n");
	}


	
/*-----------------------------------------------------------------------------------------------

										TRANSMISSION

-----------------------------------------------------------------------------------------------*/	


//Set some stats about nerwork control flows only for retransmisted packets
void stats_about_retransmission_control_pk_flows(Packet *pkptr){
	int		pk_type;
	
	//The pk_type
	op_pk_nfd_get(pkptr , "OPTION_TYPE" , &pk_type);	
	
	//According to the pk type, increments the asscociated overhead (classified in several categories)
	switch(pk_type){
		case BACKBONE_PK_TYPE :
		case BACKBONE_WITH_CONNECT_PK_TYPE :
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_other_pk++;
						overhead_other_bits+= op_pk_total_size_get(pkptr);
						
						nb_pk_ret_bb_multicast_total++;
						nb_bits_ret_bb_multicast_total+= op_pk_total_size_get(pkptr);

						if (my_cds.state == DOMINATEE)
							{
								nb_pk_ret_bb_multicast_dominatee_total++;
								nb_bits_ret_bb_multicast_dominatee_total+= op_pk_total_size_get(pkptr);
							}
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_ret_bb_multicast_dominator_total++;						
								nb_bits_ret_bb_multicast_dominator_total+= op_pk_total_size_get(pkptr);				
							}						
					}
		
				nb_pk_ret_bb_multicast_instantaneous++;
				nb_bits_ret_bb_multicast_instantaneous+= op_pk_total_size_get(pkptr);
				
				if (my_cds.state == DOMINATEE)
					{
						nb_pk_ret_bb_multicast_dominatee_instantaneous++;
						nb_bits_ret_bb_multicast_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_ret_bb_multicast_dominator_instantaneous++;
						nb_bits_ret_bb_multicast_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}
			break;
		default :
				op_sim_end("Error : the packet format is unknown for retransmission", "I am not allowed to send a packet which I don't know the role", "please modify the stats_about_control_pk_flows() procedure", "");
			break;	
	}
}


//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void stats_about_control_pk_flows(Packet *pkptr){
	int		pk_type;
	
	//The pk_type
	op_pk_nfd_get(pkptr , "OPTION_TYPE" , &pk_type);	
	
	//According to the pk type, increments the asscociated overhead (classified in several categories)
	switch(pk_type){
		case HELLO_PK_TYPE :
		
				nb_pk_hello_instantaneous++;
				nb_bits_hello_instantaneous+= op_pk_total_size_get(pkptr);
		
				if (my_cds.state == DOMINATEE)
					{
						nb_pk_hello_dominatee_instantaneous++;
						nb_bits_hello_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_hello_dominator_instantaneous++;
						nb_bits_hello_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_hello_pk++;
						overhead_hello_bits+= op_pk_total_size_get(pkptr);						
				
						nb_pk_hello_total++;
						nb_bits_hello_total+= op_pk_total_size_get(pkptr);
						
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_hello_dominatee_total++;
								nb_bits_hello_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_hello_dominator_total++;						
								nb_bits_hello_dominator_total+= op_pk_total_size_get(pkptr);				
							}						
					}
			break;
		case CDS_MIS_PK_TYPE :
		case CDS_JOIN_PK_TYPE :
		case CDS_REVERSE_JOIN_PK_TYPE :
		case CDS_RECONNECT_PK_TYPE :
		case CDS_RECON_REP_PK_TYPE :
		case RECONNECT_INIT_PK_TYPE :
		case BREAK_CDS_PK_TYPE :
		case NOTHING_NEIGH_CDS_PK_TYPE :
		case USELESS_DOMINATOR_PK_TYPE :
				
				nb_pk_cds_instantaneous++;
				nb_bits_cds_instantaneous+= op_pk_total_size_get(pkptr);
			
				if (my_cds.state == DOMINATEE)
					{
						nb_pk_cds_dominatee_instantaneous++;
						nb_bits_cds_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_cds_dominator_instantaneous++;
						nb_bits_cds_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}
				
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_cds_pk++;
						overhead_cds_bits+= op_pk_total_size_get(pkptr);
						
						nb_pk_cds_total++;
						nb_bits_cds_total+= op_pk_total_size_get(pkptr);
						
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_cds_dominatee_total++;
								nb_bits_cds_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_cds_dominator_total++;
								nb_bits_cds_dominator_total+= op_pk_total_size_get(pkptr);
							}						

					}
			break;
		case AP_HELLO_PK_TYPE :
		
				nb_pk_ap_hello_instantaneous++;
				nb_bits_ap_hello_instantaneous+= op_pk_total_size_get(pkptr);
				
				if (my_cds.state == DOMINATEE)
					{
						nb_pk_ap_hello_dominatee_instantaneous++;
						nb_bits_ap_hello_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_ap_hello_dominator_instantaneous++;
						nb_bits_ap_hello_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}
				
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_cds_pk++;
						overhead_cds_bits+= op_pk_total_size_get(pkptr);
				
						nb_pk_ap_hello_total++;
						nb_bits_ap_hello_total+= op_pk_total_size_get(pkptr);
						
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_ap_hello_dominatee_total++;
								nb_bits_ap_hello_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_ap_hello_dominator_total++;
								nb_bits_ap_hello_dominator_total+= op_pk_total_size_get(pkptr);
							}						
					}
			break;
		case HELLO_CLUSTER_PK_TYPE :
		case JOIN_CLUSTER_PK_TYPE :
		case CON_CLUSTER_PK_TYPE :
		case REP_CON_CLUSTER_PK_TYPE :
		case HELLO_CLUSTERHEAD_PK_TYPE :
		
				nb_pk_cluster_instantaneous++;
				nb_bits_cluster_instantaneous+= op_pk_total_size_get(pkptr);

				if (my_cds.state == DOMINATEE)
					{
						nb_pk_cluster_dominatee_instantaneous++;
						nb_bits_cluster_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_cluster_dominator_instantaneous++;
						nb_bits_cluster_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_cluster_pk++;
						overhead_cluster_bits+= op_pk_total_size_get(pkptr);
				
						nb_pk_cluster_total++;
						nb_bits_cluster_total+= op_pk_total_size_get(pkptr);
				
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_cluster_dominatee_total++;
								nb_bits_cluster_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_cluster_dominator_total++;
								nb_bits_cluster_dominator_total+= op_pk_total_size_get(pkptr);
							}						
						
					}
			break;
		case SLEEPING_NODE_PK_TYPE :
		case AP_UNICAST_PK_TYPE :
		
				nb_pk_other_instantaneous++;
				nb_bits_other_instantaneous+= op_pk_total_size_get(pkptr);

				if (my_cds.state == DOMINATEE)
					{
						nb_pk_other_dominatee_instantaneous++;
						nb_bits_other_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_other_dominator_instantaneous++;
						nb_bits_other_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_other_pk++;
						overhead_other_bits+= op_pk_total_size_get(pkptr);
				
						nb_pk_other_total++;
						nb_bits_other_total+= op_pk_total_size_get(pkptr);
				
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_other_dominatee_total++;
								nb_bits_other_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_other_dominator_total++;
								nb_bits_other_dominator_total+= op_pk_total_size_get(pkptr);
							}						
						
					}
			break;
		case PAGING_REQ_PK_TYPE :
		case PAGING_REP_PK_TYPE :
		case PAGING_ACK_PK_TYPE :
		case PAGING_DEL_PK_TYPE :
		case PAGING_REP_GRATUITOUS_PK_TYPE :
		
				nb_pk_data_instantaneous++;
				nb_bits_data_instantaneous+= op_pk_total_size_get(pkptr);
				
				if (my_cds.state == DOMINATEE)
					{
						nb_pk_data_dominatee_instantaneous++;
						nb_bits_data_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_data_dominator_instantaneous++;
						nb_bits_data_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_paging_pk++;
						overhead_paging_bits+= op_pk_total_size_get(pkptr);

						nb_pk_data_total++;
						nb_bits_data_total+= op_pk_total_size_get(pkptr);

						if (my_cds.state == DOMINATEE)
							{
								nb_pk_data_dominatee_total++;
								nb_bits_data_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_data_dominator_total++;
								nb_bits_data_dominator_total+= op_pk_total_size_get(pkptr);
							}						

					}
				
			break;
		case RREQ_PK_TYPE :
		case RREP_PK_TYPE :
		case RERR_PK_TYPE :
		case RUPDATE_PK_TYPE :
		case RDELETE_PK_TYPE :
		
				nb_pk_data_instantaneous++;
				nb_bits_data_instantaneous+= op_pk_total_size_get(pkptr);

				if (my_cds.state == DOMINATEE)
					{
						nb_pk_data_dominatee_instantaneous++;
						nb_bits_data_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_data_dominator_instantaneous++;
						nb_bits_data_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_route_pk++;
						overhead_route_bits+= op_pk_total_size_get(pkptr);

						nb_pk_data_total++;
						nb_bits_data_total+= op_pk_total_size_get(pkptr);
						
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_data_dominatee_total++;
								nb_bits_data_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_data_dominator_total++;
								nb_bits_data_dominator_total+= op_pk_total_size_get(pkptr);
							}						
					}
			break;
		case ACK_APP_PK_TYPE :
		case DATA_PK_TYPE :
		
				nb_pk_data_instantaneous++;
				nb_bits_data_instantaneous+= op_pk_total_size_get(pkptr);

				if (my_cds.state == DOMINATEE)
					{
						nb_pk_data_dominatee_instantaneous++;
						nb_bits_data_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_data_dominator_instantaneous++;
						nb_bits_data_dominator_instantaneous+= op_pk_total_size_get(pkptr);

					}
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_data_pk++;
						overhead_data_bits+= op_pk_total_size_get(pkptr);

						nb_pk_data_total++;
						nb_bits_data_total+= op_pk_total_size_get(pkptr);

						if (my_cds.state == DOMINATEE)
							{
								nb_pk_data_dominatee_total++;
								nb_bits_data_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_data_dominator_total++;
								nb_bits_data_dominator_total+= op_pk_total_size_get(pkptr);
							}						
					}
			break;
		case BACKBONE_PK_TYPE :
		case BACKBONE_WITH_CONNECT_PK_TYPE :
		
				nb_pk_bb_multicast_instantaneous++;
				nb_bits_bb_multicast_instantaneous+= op_pk_total_size_get(pkptr);

				if (my_cds.state == DOMINATEE)
					{
						nb_pk_bb_multicast_dominatee_instantaneous++;
						nb_bits_bb_multicast_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_bb_multicast_dominator_instantaneous++;
						nb_bits_bb_multicast_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_other_pk++;
						overhead_other_bits+= op_pk_total_size_get(pkptr);

						nb_pk_bb_multicast_total++;
						nb_bits_bb_multicast_total+= op_pk_total_size_get(pkptr);

						if (my_cds.state == DOMINATEE)
							{
								nb_pk_bb_multicast_dominatee_total++;
								nb_bits_bb_multicast_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_bb_multicast_dominator_total++;
								nb_bits_bb_multicast_dominator_total+= op_pk_total_size_get(pkptr);
							}						
					}
			break;
		case ACK_UNICAST_PK_TYPE :
		
				nb_pk_ack_instantaneous++;
				nb_bits_ack_instantaneous+= op_pk_total_size_get(pkptr);

				if (my_cds.state == DOMINATEE)
					{
						nb_pk_ack_dominatee_instantaneous++;
						nb_bits_ack_dominatee_instantaneous+= op_pk_total_size_get(pkptr);
					}
				else if (my_cds.state == DOMINATOR)
					{
						nb_pk_ack_dominator_instantaneous++;
						nb_bits_ack_dominator_instantaneous+= op_pk_total_size_get(pkptr);
					}

				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						overhead_other_pk++;
						overhead_other_bits+= op_pk_total_size_get(pkptr);

						nb_pk_ack_total++;
						nb_bits_ack_total+= op_pk_total_size_get(pkptr);
						
						if (my_cds.state == DOMINATEE)
							{
								nb_pk_ack_dominatee_total++;
								nb_bits_ack_dominatee_total+= op_pk_total_size_get(pkptr);
							}						
						else if (my_cds.state == DOMINATOR)
							{
								nb_pk_ack_dominator_total++;
								nb_bits_ack_dominator_total+= op_pk_total_size_get(pkptr);
							}						
					}
			break;
		default :
				op_sim_end("Error : the packet format is unknown", "I am not allowed to send a packet which I don't know the role", "please modify the stats_about_control_pk_flows() procedure", "");
			break;
	}
}

//sends the pk on the ethernet or wlan stream
void pk_send_uniquely(Packet* pkptr, double delay) {
	Ici*	ici_ptr;
	int		pk_type;
	int		dest;
	
	//Fields in the pk
	op_pk_nfd_get(pkptr, "DEST",			&dest);	
	op_pk_nfd_get(pkptr, "OPTION_TYPE", 	&pk_type);	

	//Energy Consumption
	energy_decreases(SENT_COEFF_CONSUMPTION*op_pk_total_size_get(pkptr)/8+SENT_SLOPE_CONSUMPTION);

	//Transmission (without delay if sent via ethernet)
	if ((dest > 0) && (dest <= nb_aps) && (is_AP))
		op_pk_send(pkptr, STRM_TO_ETH);
	else if ( (dest >= LOWER_ADDR_FOR_MULTICAST) && (is_AP) && (nb_aps > 1) )
		{
			//Transmission with the Ethernet link
			op_pk_send(op_pk_copy(pkptr), STRM_TO_ETH);
						
			//Ici Management
			if ((PROMISCUOUS_FOR_UNICAST) || (dest >= LOWER_ADDR_FOR_MULTICAST))
				dest = -1;
			ici_ptr = add_in_ici_list();
			op_ici_attr_set(ici_ptr,"dest_addr", dest);
			op_ici_install(ici_ptr);
	
			//Transmission with the WLAN card
			op_pk_send_delayed(pkptr , STRM_TO_WLAN , delay);		}
	else
		{
			//Ici Management
			if ((PROMISCUOUS_FOR_UNICAST) || (dest >= LOWER_ADDR_FOR_MULTICAST))
				dest = -1;

			//Ici
			ici_ptr = add_in_ici_list();
			op_ici_attr_set(ici_ptr,"dest_addr", dest);
			op_ici_install(ici_ptr);
	
			//Transmission
			op_pk_send_delayed(pkptr, STRM_TO_WLAN , delay);
		}

}

//Retransmit a packet with a certain delay (and set some stats about flows). Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void pk_retransmit_delayed(Packet* pkptr, double delay){
	int		dest;
	int		pk_type;	
		
	
	//Gather destination
	op_pk_nfd_get(pkptr,"DEST",			&dest);
	op_pk_nfd_get(pkptr,"OPTION_TYPE",	&pk_type);
	
	//Set statistics about network control packets
	stats_about_retransmission_control_pk_flows(pkptr);
	
	//sends the packet
	pk_send_uniquely(pkptr , delay);
}

//Retransmit a packet without delay
void pk_retransmit(Packet* pkptr){
	pk_retransmit_delayed(pkptr, 0);
}

//Send a packet with a certain delay (and set some stats about flows)
void pk_send_delayed(Packet* pkptr, double delay){
	int		dest;
	int		pk_type;
	
	//Gather destination
	op_pk_nfd_get(pkptr,"DEST",			&dest);
	op_pk_nfd_get(pkptr,"OPTION_TYPE",	&pk_type);
	
	//debug
	/*if (pk_type == ACK_UNICAST_PK_TYPE)
		{
			sprintf(msg, "%d sends an ack to %d at %f (%f + %f)\n", my_address, dest, op_sim_time()+delay , op_sim_time() , delay);
			test_message(msg);
		}
	*/
	
	//Set statistics about network control packets
	stats_about_control_pk_flows(pkptr);
		
	//sends the packet
	pk_send_uniquely(pkptr , delay);
}

//Send a packet (and set some stats about flows). Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void pk_send(Packet* pkptr){
	pk_send_delayed(pkptr , 0);
}

/*-----------------------------------------------------

						ENERGY

------------------------------------------------------*/
//Decreases the energy by offset
void energy_decreases(float	offset){

	//If energy management is implemented :
	if (energy_management >= 1)
		{
			//Decreases energy, and perhaps die !
			if (my_energy.value > ENERGY)
				my_energy.value -= offset;
			else
				{
					my_energy.value = 0;
					die();
				}
		}
}

//Return 1 if we decide this node must sleep( it depends on degree, weight, battery...)
Boolean must_sleep(){
	neigh_cell*		ptr_neigh;
	int				my_degree=0 , penalty=1;
	short			possible=1;
	float			test;
	char			msg[450];
	int				*is_authorized;

	//Verify that I am not a communicating node (If the higher layer is cdcl_loc)
	if (process_higher_layer_type == LOCALIZATION)
		{
			is_authorized = op_ima_obj_svar_get(process_higher_layer_id , "is_sleeping_authorized");
			if (!*is_authorized)
				return(OPC_FALSE);
		}
	
	
	//I must be a dominatee to sleep
	if (my_cds.state != DOMINATEE)
		return(OPC_FALSE);
	
	
	//We compute our degree and store the actual neighbour table
	ptr_neigh=neighbour_table;	
	my_degree = 0;
	while(ptr_neigh!=NULL)
		{
			//Computes the degree of alive nodes
			if ((ptr_neigh->hops == 1)&&(ptr_neigh->bidirect)&&(!ptr_neigh->sleep))
				++my_degree;
			
			//If I have the highest weight in my neighborhood, I have chances to have much energy
			if ((ptr_neigh->hops == 1)&&(ptr_neigh->bidirect)&&(ptr_neigh->weight < my_weight.value)&&(!ptr_neigh->sleep)&&(ptr_neigh->timeout > op_sim_time()+TIMEOUT_HELLO-INTERVALL_HELLO-0.2))
				penalty++;
			
			//We have a nothing neighbor
			if (ptr_neigh->state == IDLE)
				possible = 0;
				
			ptr_neigh = ptr_neigh->next;
		}	
		
	
	//We estimate that a degree of 8 is sufficient for efficient transmission and paket relays
	if ((my_degree > 4) && (my_cds.state == DOMINATEE) && (!is_wireless_router) && (!is_AP) && (possible))
		{
			//If I have no sufficient energy, I have no penalty
			//if (my_energy.value < 10/100*my_energy.max_capacity)
			//	penalty = 1;
			
			//The probability of sleeping depends from the nb of nodes which have an lower weight than me			
			test = op_dist_uniform(SLEEPING_DECISION_THRESHOLD);
			
			//debug purpose
			if (DEBUG > MAX)
				{
					print_neighbour_table();
					sprintf(msg,"value=%f : threshold=%f penalty=%d\n" , test , (double)1/penalty , penalty);
					cluster_message(msg);
				}
			
			//If I have a penalty = x, I have the probability 1/x to sleep
			if ((double)test < (double)1/penalty)
				return(OPC_TRUE);
		}
	else
		{
			if (DEBUG > LOW)
				{
					sprintf(msg,"sleeping not allowed : degree=%d, state=%d, possible=%d\n",my_degree,my_cds.state,possible);
					cluster_message(msg);
				}		
		}
	
	return(OPC_FALSE);
}


//Initiates the sleeping mode for a node (advertises its neighbours....)
void sleep(){
	Packet*		pkptr;
	char		msg[150];

	//Sleeping Control Variables
	is_sleeping.value = OPC_TRUE;
	is_sleeping.time_sleeping = op_sim_time();
	
	//Messages
	if (DEBUG>=LOW)
		{
			sprintf(msg,"%d : begins to sleep at %f!\n",my_address,op_sim_time());
			cluster_message(msg);
		}

	//Stats
	average_energy_sleeping_nodes += my_energy.value;
	nb_sleeps++;
	
	//Sends an advertisement packet to Neighbors
	pkptr = op_pk_create_fmt("cdcl_cds_sleeping_node");
	op_pk_nfd_set(pkptr,"SRC",		my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT",	my_address);
	op_pk_nfd_set(pkptr,"DEST",		-1);
	op_pk_nfd_set(pkptr,"FATHER",	my_cds.father);
	op_pk_nfd_set(pkptr,"PK_ID",	current_id++);
	op_pk_nfd_set(pkptr,"TTL",		k_cds);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",SLEEPING_NODE_PK_TYPE);
	
	pk_send(pkptr);
}

//Set this node as sleeping node in the neighbourhood table
void add_sleeping_node(int addr){
	neigh_cell*	ptr_neigh;
	char		msg[150];

	if (DEBUG>LOW)
		{
			sprintf(msg,"%d begins sleeping at %f\n",addr,op_sim_time());
			cluster_message(msg);
		}
	
	//Searches the correspondant entry and updates it as sleeping 
	ptr_neigh=neighbour_table;	
	while(ptr_neigh!=NULL)
		{
			if ((ptr_neigh->address == addr)&&(ptr_neigh->address != my_address))
				{
					ptr_neigh->sleep = 1;
					//Special Timeout for sleeping nodes
					ptr_neigh->timeout = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO + SLEEPING_TIME + INTERVALL_HELLO;
				}
			ptr_neigh = ptr_neigh->next;
		}	


}

//This node is dead -> stop all
void die(){
	char	msg[200];

	if (is_DEAD.bool==0)
		{
			nb_dead_nodes++;
			is_DEAD.bool = 1;
			is_DEAD.time = op_sim_time();
			printf("DEAD --- %d --- DEAD\n",my_address);
			if (DEBUG>LOW)
				{
					sprintf(msg,"I die at %f\n",op_sim_time());
					cluster_message(msg);
				}
			op_intrpt_schedule_self(op_sim_time(),DIE_CODE);
			
			//Change state -> updates the Stats about Energy
			//update_state_cds(NOTHING,Stathandle stat_local,Stathandle stat_global);
			
			
			if (my_cds.state == DOMINATOR)
				{
					stat_conso_dominator.time += op_sim_time() - my_cds.previous_state_change_time;
					stat_conso_dominator.energy +=  my_energy.previous_value - my_energy.value;
					my_cds.previous_state_change_time = op_sim_time();
					my_energy.previous_value = my_energy.value;
				}
			if (my_cds.state == DOMINATEE)
				{
					stat_conso_dominatee.time += op_sim_time() - my_cds.previous_state_change_time;
					stat_conso_dominatee.energy +=  my_energy.previous_value - my_energy.value;
					my_cds.previous_state_change_time = op_sim_time();
					my_energy.previous_value = my_energy.value;
				}	
			
			my_cds.state = IDLE;
		}	
	
}	

/*-----------------------------------------------------------------------------------------------

										PACKETS

-----------------------------------------------------------------------------------------------*/

//Gets the first buffered packet in the list (older packets are in head of the list)
Packet* get_next_pk_in_wait_state(){
	
	return(op_prg_list_remove(temporary_pk_list , OPC_LISTPOS_HEAD));
}

//Adds a packet which requires a delay before treatment (I have not a valid state)
//NB: we had packets in tail of the list (FIFO list)
void add_pk_in_wait_state(Packet* pkptr){
	Packet	*pk_to_store;
	
	pk_to_store = op_pk_copy(pkptr);
	op_prg_list_insert(temporary_pk_list , pk_to_store , OPC_LISTPOS_TAIL);
}

//Add a new Ici in the ici_list
Ici* add_in_ici_list(){
	struct_ici*		entry;
	
	//Memory allocation (to have a valid entry outside this function)
	entry = (struct_ici*) op_prg_mem_alloc ( sizeof (struct_ici));
	
	//Info
	entry->ici_ptr		= op_ici_create("mac_dest_indication");
	entry->timeout		= op_sim_time() + TIMEOUT_ICI ;
	
	//Insert it
	op_prg_list_insert( ici_list , entry , OPC_LISTPOS_TAIL);	
	
	//Return the Ici
	return(entry->ici_ptr);
}

//Delete timeouted entries
void delete_timeout_in_ici_list(){
	int				i = 0;
	struct_ici*		entry;
	
	if (ici_list == NULL)
		op_sim_end("We have an error :" , "the ici list is a null list" , "please initialize it","");

	//If the list is empty
	if (op_prg_list_size(ici_list)==0)
		return;
	
	//For each entry
	while (i< op_prg_list_size(ici_list))
		{
			entry = (struct_ici*) op_prg_list_access (ici_list, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout < op_sim_time())
				{
					op_prg_list_remove ( ici_list , i);
					free(entry);
				}
			else
				i++;
		}
}

//=1 if that packet was already seen, 0 else
int pk_not_seen (int id, int addr) {
		id_cell*	ptr;
		
		ptr=id_table;
		while((ptr!=NULL)&&!((id == ptr->id)&&(addr == ptr->source)))
			{
				ptr=ptr->next;
			}	
		return(ptr == NULL); //No packet corresponds to the id if we have the end of list
		
}

void add_address_id_couple(int addr,int id){
	id_cell*	ptr;	

	//Is the node already in the list ?
	if (!pk_not_seen(id , addr))
		return;
		
	//add this reconnection request as already seen
	ptr = (struct id_cell*)op_prg_mem_alloc(sizeof(id_cell));
	if (ptr==NULL)
		{
			printf("error in the memory allocation for the creation of a new cell in the list of packets id");
		}
								
								
	//Add the correct content at the queue of the list
	ptr->id = id;
	ptr->source = addr;
	ptr->timeout =  op_sim_time() + TIMEOUT_ID;
								
								
	ptr->next=id_table;
	id_table = ptr;
}


//To maintain the relaying table (usually for cds-reconection requests): 
//Verify that this request was not previous forwarded
void add_relaying(int src, int relay){
	relay_cell		*ptr;
	Boolean			loop_test;
	char			msg[150];
	
	//IWe search in the table an entry equal to the parameters
	ptr = relay_table;
	loop_test = OPC_FALSE;
	while(ptr!=NULL)
		{
			if ((ptr->src==src) && (ptr->relay==relay)) 
				{				
					ptr->timeout = op_sim_time() + TIMEOUT_RELAYING;
					loop_test = OPC_TRUE;					
				}	
			ptr = ptr->next;
		
		}
	
	//If such an entry doesn't exist, we add it
	if (!loop_test)	
		{
			//Memory Allocation for a new cell in the list of neighbours
			ptr = (struct relay_cell *)op_prg_mem_alloc(sizeof(relay_cell));
			if (ptr==NULL)
				{
					printf("error in the memory allocation for the creation of a new cell in the relay_table");
				}
		
			//Add the correct content
			ptr->src 		= src;
			ptr->relay 		= relay;
			ptr->timeout 	= op_sim_time() + TIMEOUT_RELAYING;

			//Updates the pointers (add in head of list)
			ptr->next = relay_table;
			relay_table = ptr;	
		}	
	
	if (DEBUG>MAX)
		{
			if (loop_test)
				sprintf(msg,"I update the entry src=%d with relay=%d \n",src,relay);
			else
				sprintf(msg,"I add the entry src=%d with relay=%d \n",src,relay);
			cluster_message(msg);
		}

}

//Forwards one packet to my dominator (with ttl-- and SRC changed)
void forward_packet_to_dominator(Packet* pkptr, int type){
	int		ttl;

	//Forward, but in unicast, to my dominator (even if the packet sent is in broadcast)
	op_pk_nfd_set(pkptr,"DEST",my_cds.relay);
	
	if (op_pk_nfd_get(pkptr,"TTL",&ttl) != OPC_COMPCODE_FAILURE)
		op_pk_nfd_set(pkptr,"TTL",--ttl);

	op_pk_nfd_set(pkptr,"SRC",my_address);

	pk_send_delayed(pkptr , op_dist_uniform(0.005));							
}



//Remove a special id from the id_table
//Return 1 if all is okay, else 0
int remove_id(int id, int addr){
	id_cell		*ptr, *ptr2;
	
	
	ptr = id_table;
	while ( (ptr!=NULL) && ((ptr->source!=addr)||(ptr->id!=id)) )
		{
			ptr2 = ptr;
			ptr = ptr->next;
		}

	//The element was not found, there is an error
	if (ptr==NULL)
		return(0);

	//We must delete the first entry of the list of pointers
	if (ptr==id_table)
		{
			id_table = ptr->next;		
		}
	//We bypass the correspondant entry
	else
		{			
			ptr2 = ptr->next;
			free(ptr);
		}	
	return(1);

}


/*-----------------------------------------------------------------------------------------------
							
							MANIPULATION OF SONS, DOMINATEES ...

-----------------------------------------------------------------------------------------------*/




//is addr one of my sons ?
Boolean is_my_son(int addr){
	neigh_cell*	ptr;
	
	ptr = neighbour_table;
	while (ptr != NULL)
		{
			if ((ptr->address == addr) && (ptr->state == DOMINATOR) && (ptr->hops==1) && (ptr->bidirect))
				{
					if (ptr->father == my_address)
						return(OPC_TRUE);
					else
						return(OPC_FALSE);
				}
			ptr = ptr->next;
		}
	return(OPC_FALSE);

}

//Delete all sons which are no more present in the neighborhood table
void delete_timeouted_in_son_list(){
	son			*ptr;
	son			*ptr2;
	
	ptr 	= my_cds.sons;
	ptr2 	= my_cds.sons;
	while (ptr != NULL)
		{
			if (!is_my_son(ptr->address))
				{
					//Head of the list
					if (ptr == my_cds.sons)
						{
							my_cds.sons = ptr->next;
							free(ptr);
							ptr = my_cds.sons;
						}
					else
						{
							ptr2->next = ptr->next;
							free(ptr);
							ptr = ptr2;
						}
				}
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr = ptr->next;
		}	
}

//IS this node in my son  list ?
Boolean is_in_son_list(int address){
	son	*ptr;
	
	ptr = my_cds.sons;
	while (ptr != NULL)
		{
			if (ptr->address == address)
				return(OPC_TRUE);
			
			ptr = ptr->next;
		}	
	return(OPC_FALSE);		
}

//Adds a son in the son list
void add_son(int addr){
	son			*ptr_son;
	neigh_cell	*ptr_neigh;
	Boolean		is_found;
	char		msg[150];	
	
	//Update the list of my sons
	if(!is_in_son_list(addr))		
		{
			ptr_son = (struct son*)op_prg_mem_alloc(sizeof(son));
			if (ptr_son==NULL)
				{
					printf("error in the memory allocation for the creation of a new son in the list");
				}
			ptr_son->address	= addr;
			ptr_son->next 		= my_cds.sons;
			my_cds.sons			= ptr_son;		
		}
	
	//Update the neighborhood table (more precisely, the field 'father')
	ptr_neigh = neighbour_table;
	is_found= OPC_FALSE;
	while ((ptr_neigh != NULL) && (!is_found))
		{
			if (ptr_neigh->address == addr)
				{
					ptr_neigh->father = my_address;
					is_found = OPC_TRUE;
				}
			
			ptr_neigh = ptr_neigh->next;
		}
	//Debug
	if (DEBUG>LOW)
		{
			sprintf(msg , "%d adds its son %d at %f\n",my_address , addr , op_sim_time());
			cluster_message(msg);
		}
	
	//If this node change from dominatee to dominator
	if (is_my_dominatee(addr))
		delete_dominatee(addr);
}

void delete_son(int addr){
	son		*ptr_son , *ptr_son2;
	char	msg[200];
	
	ptr_son = my_cds.sons;
	//Searches the entry
	while(ptr_son!=NULL)
		{
			if (ptr_son->address == addr)
				{
					if (ptr_son == my_cds.sons) //The particular case of a delete entry in head of the list (not tested, I believe)
							{
								my_cds.sons = ptr_son->next;
								free(ptr_son);
								ptr_son = my_cds.sons;
							}
						else
							{
								ptr_son2->next = ptr_son->next;
								free(ptr_son);
								ptr_son = ptr_son2;
							}
					}
			
				ptr_son2 = ptr_son;
				if (ptr_son!=NULL)
					ptr_son = ptr_son->next;
		}
	//DEBUG
	if (DEBUG>2)
		{
			sprintf(msg, "%d deletes its son %d at %f\n", my_address , addr, op_sim_time());
			cluster_message(msg);
		}
}

int	count_nb_sons(){
	int		nb;
	son		*ptr_son;
	
	ptr_son = my_cds.sons;
	nb = 0;
	while(ptr_son!=NULL)
		{
			nb++;
			ptr_son = ptr_son->next;
		}
	return(nb);
}


//is addr one of my dominatees ?
int is_my_dominatee(int addr){
	dominatee*	ptr_dominatee;
	
	ptr_dominatee = my_cds.dominatees;
	while(ptr_dominatee!=NULL)
		{
			if (ptr_dominatee->address==addr)
				return(1);
			ptr_dominatee = ptr_dominatee->next;
		}
	 return(0);
}


void add_dominatee(int addr){
	dominatee*	ptr_dominatee;
	
	if(!is_my_dominatee(addr))		
		{
			ptr_dominatee = (struct dominatee*)op_prg_mem_alloc(sizeof(dominatee));
			if (ptr_dominatee==NULL)
				{
					printf("error in the memory allocation for the creation of a new dominatee in the list");
				}
			ptr_dominatee->address = addr;
			ptr_dominatee->next = my_cds.dominatees;
			my_cds.dominatees = ptr_dominatee;		
		}
}

void delete_dominatee(int addr){
	dominatee		*ptr_dominatee , *ptr_dominatee2;

	
	ptr_dominatee = my_cds.dominatees;
	while(ptr_dominatee!=NULL)
		{
			if (ptr_dominatee->address == addr)
				{
					if (ptr_dominatee == my_cds.dominatees) //The particular case of a delete entry in head of the list (not tested, I believe)
							{
								my_cds.dominatees = ptr_dominatee->next;
								free(ptr_dominatee);
								ptr_dominatee = my_cds.dominatees;
							}
						else
							{
								ptr_dominatee2->next = ptr_dominatee->next;
								free(ptr_dominatee);
								ptr_dominatee = ptr_dominatee2;
							}
				}
			
			ptr_dominatee2 = ptr_dominatee;
			if (ptr_dominatee!=NULL)
					ptr_dominatee = ptr_dominatee->next;
		}
}

int	count_nb_dominatees(){
	int		nb;
	dominatee		*ptr_dominatee;
	
	ptr_dominatee = my_cds.dominatees;
	nb = 0;
	while(ptr_dominatee!=NULL)
		{
			nb++;
			ptr_dominatee = ptr_dominatee->next;
		}
	return(nb);
}


/*-------------------------------------------------------------

						VARIOUS

------------------------------------------------------------*/

//With a float value, returns a string representing the rounded float, with dd decimals, with space between thousands and millions or not (option_space)
void round(char* result, float value, int dd, int option_space){
	char	str[100];
	char	*int_part;
	char	int_part2[100];
	char	rounded_dd_part[100];
	int		curseur;
	int		i,j;
	int		lg_int;
	
	sprintf(str,"%f",value);
	if (strchr(str,'.')==NULL)
		{
			strcpy(result,str);
		}
	else
		{
			int_part = strtok(str,".");
			//For the decimal part, we take the dd characters behing the '.'
			strncpy(rounded_dd_part , strtok(NULL,".") , dd);
			rounded_dd_part[dd]='\0';
			
			//To add spaces between units, thousands, millions.... (groups of 3 digits like : "1 234 567")
			lg_int = strlen(int_part);
			//destination size -> initial_size + goups of 3 digits - 1
			if (option_space)
				curseur = lg_int+(lg_int+2)/3-1;
			else
				curseur = lg_int;
			
			//We treat the number from the end to the begining of the string -> we decrement curseur (character in treatment in the destination string)
			int_part2[curseur--] = '\0';
			for(i=0;i<(lg_int+2)/3 ;i++)
				{
					if (i==(lg_int+2)/3-1)
						{
							//The first group of digits (not necessary multiple of 3 (we treat it at the end)
							for(j=0;j< lg_int - ((lg_int+2)/3-1)*3 ;j++)
								{
									int_part2[curseur--] = int_part[lg_int-j-3*i-1];	
								}
						}
					else
						{
							//All complete groups of 3 digits
							for(j=0;j< 3;j++)
								{
									int_part2[curseur--] = int_part[lg_int-j-3*i-1];	
								}
							//It is not the first group of digits -->adds a space
							if (option_space)
								int_part2[curseur--] = ' ';
						}
				}
			if (dd>0)
				sprintf(result,"%s.%s",int_part2 , rounded_dd_part);
			else
				sprintf(result,"%s",int_part2);			//If no decimal required
		}
}

/*-------------------------------------------------------------

			TREATMENTS OF RELAY FIELDS IN PACKETS

------------------------------------------------------------*/


//Return True if addr_to_find constitutes a relay in the "RELAYxx" fields of the packet pkptr
int is_a_relay(Packet* pkptr, int addr_to_find){
	int 	i, addr_tempo;
	char	chaine[150];

	addr_tempo = my_address;
	i = 0;
	while((addr_tempo!=0)&&(i<=NB_RELAY_FIELDS))
		{
			sprintf(chaine,"RELAY%d",i++);
			op_pk_nfd_get(pkptr,chaine,&addr_tempo);
			if (addr_tempo == addr_to_find)
				return(1);
		}
	//If we have a null addr_tempo or i=NB_RELAy_FIELDS, we have no more RELAY_FIELDS
	return(0);
}


//Returns the address of the last relay contained in pkptr
int get_last_relay(Packet* pkptr){
	int 	i, addr_tempo;
	char	chaine[150];

	i = NB_RELAY_FIELDS;
	addr_tempo = 0;
	while((addr_tempo==0)&&(i>=1))
		{
			sprintf(chaine,"RELAY%d",i--);
			op_pk_nfd_get(pkptr,chaine,&addr_tempo);
		}
	return(addr_tempo);
}

//Returns the address of the before-last relay contained in pkptr
int get_before_last_relay(Packet* pkptr){
	int 	i, addr_tempo;
	char	chaine[150];

	i = NB_RELAY_FIELDS;
	addr_tempo = 0;
	while((addr_tempo==0)&&(i>=1))
		{
			sprintf(chaine,"RELAY%d",i--);
			op_pk_nfd_get(pkptr,chaine,&addr_tempo);
		}
	sprintf(chaine,"RELAY%d",i--);
	op_pk_nfd_get(pkptr,chaine,&addr_tempo);
	return(addr_tempo);
}

/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//											CDS



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/










/*-----------------------------------------------------------------------------------------------

									CONSTRUCTION  OF  THE  MIS

-----------------------------------------------------------------------------------------------*/

//Get a better relay to father (nearer than the current relay) if it exists
void optimize_relay_to_father(){
	neigh_cell*	ptr;
	int			best_relay;
	short		best_relay_hops;
	char		msg[150];
	
	//Actual Values
	best_relay		= my_cds.relay;
	best_relay_hops	= my_cds.father_hops;
	
	//Searches all potential relay to cds
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			//Better relay
			if ((ptr->father == my_cds.father) && (ptr->father_hops < best_relay_hops) && (ptr->hops == 1) && (ptr->bidirect) && (ptr->father_hops != -1) && (ptr->father_hops != 0))
				{
					best_relay		= ptr->address;
					best_relay_hops = ptr->father_hops + 1;
				}
			//The father is 1-Neighbor
			if ((ptr->address == my_cds.father) && (ptr->state == DOMINATOR) && (ptr->hops == 1) && (ptr->bidirect))
				{
					best_relay		= ptr->address;
					best_relay_hops = 1;
				}
			
			ptr = ptr->next;
		}
	
	//If we have better values, we change it
	if (best_relay_hops < my_cds.father_hops)
		{
			if (DEBUG>LOW)
				{
					sprintf(msg,"I update my relay %d (%d hops) -> %d (%d hops) for my father %d at %f\n", my_cds.relay , my_cds.father_hops , best_relay , best_relay_hops , my_cds.father , op_sim_time());
					cluster_message(msg);
					print_neighbour_table();
				}
		
			my_cds.relay		= best_relay;
			my_cds.father_hops 	= best_relay_hops;			
		}
}

//Change father
void change_father(int father, int relay , short hops){
	char	msg[200];

	if (DEBUG>LOW)
		{
			sprintf(msg,"FATHER: I changed my father from %d to %d (father_hops = %d)\n", my_cds.father , father , hops);
			cluster_message(msg);
		}

	//First father change not comptabilized (father=0 is not a "real" father) + deletes the effect of construction (only maintenance)
	if ((my_cds.father != father) && (my_cds.father != 0) && (op_sim_time() > TIME_BEGIN_STATS))
		{
			nb_nodes_which_change_their_dominator++;
			if (my_cds.state==DOMINATEE)
				nb_dominatees_which_change_their_dominator++;
		}
	
	my_cds.father 		= father;
	my_cds.father_hops 	= hops;
	my_cds.relay 		= relay;
		
	//The configuration has perhaps changed -> we delete our father from the list of dominatees/sons
	if (is_my_son(father))
		delete_son(father);
	if (is_my_dominatee(father))
		delete_dominatee(father);		
}

//Advertise our neighbour of our new state (with a cds_packet)
void send_new_state(int state){
	Packet* 		pkptr;
	
	pkptr = hello_packet_generate();
	op_pk_nfd_set(pkptr,"OPTION_TYPE",	CDS_MIS_PK_TYPE);
	op_pk_nfd_set(pkptr,"TTL",			ttl_for_hello_mis);
	
	
	pk_send_delayed(pkptr , op_dist_uniform(0.005));
}

//Change my state in the cds table
void update_state_cds(int state){	
	char	msg[150];
	
	if (DEBUG>LOW)
		{
			sprintf(msg,"STATE: changed to %d with Weight=%d at %f (cds construct %d)\n" , state , my_weight.value , op_sim_time() , my_cds.cds_intrpt_end);
			cluster_message(msg);
		}
	
	
	//Stats about CDS-state changes
	if ((my_cds.state == IDLE) && (state == ACTIVE))
		stats_idle_active_changes++;
	else if ((my_cds.state == IDLE) && (state == DOMINATOR))
		stats_idle_dominator_changes++;
	else if ((my_cds.state == IDLE) && (state == DOMINATEE))
		stats_idle_dominatee_changes++;
	else if ((my_cds.state == DOMINATEE) && (state == IDLE))
		stats_dominatee_idle_changes++;
	else if ((my_cds.state == DOMINATOR) && (state == IDLE))
		stats_dominator_idle_changes++;
	else if ((my_cds.state == ACTIVE) && (state == DOMINATOR))
		stats_active_dominator_changes++;
	else if ((my_cds.state == ACTIVE) && (state == DOMINATEE))
		stats_active_dominatee_changes++;
	else if ((my_cds.state == DOMINATEE) && (state == ACTIVE))
		stats_dominatee_active_changes++;
	else if ((my_cds.state == DOMINATEE) && (state == DOMINATOR))
		stats_dominatee_dominator_changes++;
	else if ((my_cds.state == DOMINATOR) && (state == DOMINATEE))
		stats_dominator_dominatee_changes++;
	else
		{
			sprintf(msg, "error : a node (%d) changed its cds-state from %d to %d\n", my_address , my_cds.state , state);
			op_sim_end(msg, "" , "" , "");
		}
	
	//Stats about Energy
	if ((state != DOMINATOR) && (my_cds.state == DOMINATOR))
		{
			stat_conso_dominator.time 			+= op_sim_time() - my_cds.previous_state_change_time;
			stat_conso_dominator.energy			+=  my_energy.previous_value - my_energy.value;
			my_cds.previous_state_change_time 	= op_sim_time();
			my_energy.previous_value 			= my_energy.value;
			nb_changes_of_dominators++;
			
			change_clusterhead (ZERO, -1, -1);
		}
	if ((state != DOMINATEE) && (my_cds.state == DOMINATEE))
		{
			stat_conso_dominatee.time 			+= op_sim_time() - my_cds.previous_state_change_time;
			stat_conso_dominatee.energy 		+=  my_energy.previous_value - my_energy.value;
			my_cds.previous_state_change_time 	= op_sim_time();
			my_energy.previous_value 			= my_energy.value;
		}	
	
	//Maintenance for cluster (when state change after initialization)
	my_cds.time_cds_reinit=-1;	
	
	//I become dominator
	if ((state==DOMINATOR) && (my_cds.state!=DOMINATOR))
		{
			//Infos about cds for dominators
			my_cds.time_dominator_usefull 		= op_sim_time();		
			my_cds.time_last_cds_reconstruct 	= op_sim_time();

			switch (cluster_algos_type)
				{
					case THEO_OLD :
					case THEO_NEW :
					case THEO_NEW2 :
						my_clusterhead.last_time_usefull 	= op_sim_time();
						change_clusterhead (ZERO, -1, -1);
			
						//test if the cluster election is already ended for neighbours
						if (all_neighbours_cluster_init())
							{
								if (DEBUG>LOW)
									{
										sprintf(msg,"%d becomes dominator and intiates the cluster-maintenance process at %f (all neighbours have already initiated a cluster-construction before I become dominator)\n",my_address,op_sim_time());
										cluster_message(msg);
									}
								my_clusterhead.construct_cluster = 5;
								op_intrpt_schedule_self(op_sim_time(),CLUSTER_MAINTENANCE_CODE);	
							}
						else
							{
								my_clusterhead.construct_cluster = 1;
								op_intrpt_schedule_self(op_sim_time(),CONSTRUCT_CLUSTER_CODE);
							}
						break;
					case NONE :
							my_clusterhead.address				= my_address;
							my_clusterhead.relay				= my_address;
							my_clusterhead.relay_last_seen		= op_sim_time();
							my_clusterhead.construct_cluster	= 2;
						break;
				}
		}

	//A dominator loses its role of dominator
	if ((my_cds.state==DOMINATOR) && (state!=DOMINATOR))
		{			
			switch (cluster_algos_type)
				{
					case THEO_OLD :
							//Cluster Maintenance Procedure
							if (my_clusterhead.construct_cluster >= 4)
								op_intrpt_disable(OPC_INTRPT_SELF,CLUSTER_MAINTENANCE_CODE,OPC_TRUE);
							my_clusterhead.construct_cluster = 0;
						break;
					case THEO_NEW :
					case THEO_NEW2 :
							//Cluster Maintenance Procedure
							if (my_clusterhead.construct_cluster >= 4)
								op_intrpt_disable(OPC_INTRPT_SELF,CLUSTER_MAINTENANCE_CODE,OPC_TRUE);
							my_clusterhead.construct_cluster = 0;
						break;
					case NONE :
							my_clusterhead.address	= my_cds.father;
						break;
				}
						
			if (process_higher_layer_type == LOCALIZATION)
				op_intrpt_schedule_remote(op_sim_time(),STATE_CHANGE_CODE,process_higher_layer_id);
		}
	
	
	//OUR NEW STATE
	my_cds.state = state;

	//We must advertise our neighbours of our new state
	if (cds_algos_type != WU_LI)
		send_new_state(state);
	
	//Update the entry of the cds_table
	update_informations_cds(my_address , my_cds.father , my_clusterhead.address , state , my_weight.value);
	
	//We have no verification of highest weight that is scheduled
	if ((state == DOMINATOR) || (state==DOMINATEE))
		my_cds.cds_intrpt_end = 0;
	
	//schedule the next verification of "I am the node with the hisghest weight" (->DOMINATOR)						
	if ((!my_cds.cds_intrpt_end) && (state==ACTIVE))
		{
			op_intrpt_schedule_self(op_sim_time() + timeout_construct_cds , CONSTRUCT_CDS_CODE); 
			my_cds.cds_intrpt_end = 1;
		}	
	
	
	//We schedule the maintenance : our integration in the cds will finish when the principal dominator will have sent a join message and the other dominators will have answsered
	if	((!my_cds.is_maintenance_scheduled) && (cds_algos_type != WU_LI))
		{
			//It I am dominatee, the cds-maintenance process is not hurried
			if (my_cds.state==DOMINATEE)
				{
					my_cds.is_maintenance_scheduled = 1;
					op_intrpt_schedule_self(op_sim_time()+ (2*k_cds+1)* 2 * (0.4) + INTERVALL_HELLO ,CDS_MAINTENANCE_CODE);
				}
			//If I am a dominator, I schedule the next cds_maintenance to choose a father (and eventually send a join-reverse) --> must be quick
			else if (my_cds.state==DOMINATOR)
				{
					my_cds.is_maintenance_scheduled = 1;
					op_intrpt_schedule_self(op_sim_time()+ 0.5*(2*k_cds+1)*(0.1) ,CDS_MAINTENANCE_CODE);
				}				
		}
}



//I update the cds-information in my neighbour_table (One hello_cds_packet just came)
void update_informations_cds(int address, int father , int clusterhead , int state, int weight){
	neigh_cell	*ptr;
	char		msg[150];
	
	//Look for the correspodant entry
	ptr = neighbour_table;
	while ((ptr!=NULL)&&(ptr->address!=address))
		{
			ptr = ptr->next;
		}

		
	//We must update the cds-information of our neighbourhood
	if (ptr!=NULL){
			ptr->state 			= state;	
			ptr->weight 		= weight;
			ptr->father			= father;
			ptr->clusterhead	= clusterhead;
			
			
			if (DEBUG>HIGH)
				{
					sprintf(msg,"%d updates the state %d of node %d in my table at %f\n",my_address,ptr->state,ptr->address,op_sim_time());
					cluster_message(msg);
				}
		}
	
	//We must add an entry -> abnormal (except if the source is a dominatee k_cds+1 hops far (possible because ttl of dominatee-messages are set to k_cds+1))
	if ((ptr==NULL) && (state!=DOMINATEE) && (DEBUG>MEDIUM)) 
		{
			sprintf(msg,"%d must updates a cds entry but the correspondant entry doesn't exist in the neighbour table, and such a case is not regular\n",my_address);
			cluster_message(msg);
			print_neighbour_table();
			sprintf(msg,"%d-%d\n",address,state);
			cluster_message(msg);
		}
	
}


//Have I the highest weight of all my active neighbours ?
int own_highest_weight(){
	neigh_cell		*neigh_ptr;
	int				id_highest_weight, highest_weight;
	char			msg[150];
	
	id_highest_weight=0;
	highest_weight=0;

	
	//I must have the highest weight of my active neighbours
	neigh_ptr = neighbour_table;
	while(neigh_ptr!=NULL)
		{
			if ((neigh_ptr->state==ACTIVE) && (neigh_ptr->hops <= k_cds))	//We search the weight only for the nodes which are active only for the nodes which are active
				{
					//We have a conflict (2 weights equals) -->resolution with the id
					if ( (neigh_ptr->weight == highest_weight) && (neigh_ptr->address > id_highest_weight) )
						{
							id_highest_weight = neigh_ptr->address;
							highest_weight = neigh_ptr->weight;
						}
					//This weight is the best
					if (neigh_ptr->weight > highest_weight)
						{
							id_highest_weight = neigh_ptr->address;
							highest_weight = neigh_ptr->weight;
						}
				}
			neigh_ptr = neigh_ptr->next;
		}	
	
	if (DEBUG > LOW)
		{
			sprintf(msg, "In my active-neighborhood, %d has the highest weight (%d)\n", id_highest_weight , highest_weight);
			cluster_message(msg);
		}
	
	if (id_highest_weight==my_address)
		return(1);
	else
		return(0);
 }





/*-----------------------------------------------------------------------------------------------

								INTERCONNECTION  OF  THE  MIS

-----------------------------------------------------------------------------------------------*/

//Each dominator must advertise its presence to the other dominator (nearer than 2k-1 hops) 
void send_join_message()	{
	Packet* pkptr;
	int		i;
	char	chaine[12], msg[150];

	if (my_cds.last_join_message_sent < op_sim_time()-INTERVALL_HELLO)
		{
			if (DEBUG>LOW)
				{
					sprintf(msg,"CDS-MIS: %d send a join indication message (id=%d) for the interconnection of MIS at %f\n",my_address,current_id,(float)op_sim_time());
					cluster_message(msg);		
				}

			//Creation and Initialization of the join message
			pkptr = op_pk_create_fmt("cdcl_cds_reconnect_init");
	
			for(i=2;i<=NB_RELAY_FIELDS;i++)
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_set(pkptr,chaine,0);
				}
			op_pk_nfd_set(pkptr,"RELAY1",my_address);
			op_pk_nfd_set(pkptr,"PK_ID",(int)current_id++);
			op_pk_nfd_set(pkptr,"TTL",k_cds*2+1);
			op_pk_nfd_set(pkptr,"SRC",my_address);
			op_pk_nfd_set(pkptr,"DEST",-1);
			op_pk_nfd_set(pkptr,"SRC_INIT",my_address);
			op_pk_nfd_set(pkptr,"OPTION_TYPE",CDS_JOIN_PK_TYPE);

			pk_send_delayed(pkptr , op_dist_uniform(0.005));	
			my_cds.last_join_message_sent = op_sim_time();
		}
}	
   

void send_join_message_delayed(float delay){
	Packet* pkptr;
	int		i;
	char	chaine[12], msg[150];

	if (my_cds.last_join_message_sent < op_sim_time()-INTERVALL_HELLO)
		{
	
			if (DEBUG>LOW)
				{
					sprintf(msg,"%d send a join indication message (id=%d) for the interconnection of MIS at %f\n",my_address,current_id,(float)op_sim_time());
					cluster_message(msg);		
				}

			//Creation and Initialization of the join message
			pkptr = op_pk_create_fmt("cdcl_cds_reconnect_init");
	
			for(i=2;i<=NB_RELAY_FIELDS;i++)
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_set(pkptr,chaine,0);
				}
			op_pk_nfd_set(pkptr,"RELAY1",my_address);
			op_pk_nfd_set(pkptr,"PK_ID",(int)current_id++);
			op_pk_nfd_set(pkptr,"TTL",k_cds*2+1);
			op_pk_nfd_set(pkptr,"SRC",my_address);
			op_pk_nfd_set(pkptr,"DEST",-1);
			op_pk_nfd_set(pkptr,"SRC_INIT",my_address);
			op_pk_nfd_set(pkptr,"OPTION_TYPE",CDS_JOIN_PK_TYPE);

			pk_send_delayed(pkptr , delay);
		}
}

//One dominatee must forward a join indication in order to contact the neighbours which are dominators and that have no father
void forward_join_message(Packet* pk_src)	{
	Packet	*pk_dest;
	int		i, ttl, src_addr , priority ,type , previous_hop;
	int		test = -1;
	char	chaine[20];
	char	msg[150];
	
	//Add our address in the relay fields
	i=1;
	while ((test != 0) && (i<=NB_RELAY_FIELDS))
		{
			sprintf(chaine,"RELAY%d",i);
			op_pk_nfd_get(pk_src , chaine , &test);
			i++;
		}	
	
	//Info from source pk
	op_pk_nfd_get(pk_src , "TTL",			&ttl);
	op_pk_nfd_get(pk_src , "OPTION_TYPE",	&type);
	op_pk_nfd_get(pk_src , "PRIORITY",		&priority);
	op_pk_nfd_get(pk_src , "SRC",			&previous_hop);
	
	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest , chaine,		my_address);
	op_pk_nfd_set(pk_dest , "SRC",		my_address);
	op_pk_nfd_set(pk_dest , "TTL",		--ttl);
	op_pk_nfd_set(pk_dest , "PRIORITY",	priority + my_weight.value);
	
	if (DEBUG>LOW)
		{
			op_pk_nfd_get(pk_src , "SRC_INIT" , &src_addr);
			sprintf(msg,"%d forwarded the join indication from %d (via %d), with ttl=%d and id=%d at %f\n" , my_address , src_addr , previous_hop ,  ttl , current_id-1 , op_sim_time());
			cluster_message(msg);
		}
	
	//Send the packet
	if (my_weight.value > LOW_WEIGHT )
		pk_send_delayed(pk_dest , (double)(15/(my_weight.value)) + op_dist_uniform(0.005));
	else
		pk_send_delayed(pk_dest , 5 + op_dist_uniform(0.005));		
}


//We answers to a join indication : we advertise that :
//-the dominator which is source that he was our father
//-the relay-dominatee that he was choosen to become a dominator (in order to connect 2 dominators)
void send_join_reverse(Packet* pk_src){
	Packet	*pk_dest;
	int		i , dest, dest_final, addr;
	char	chaine[12], msg[150];
	
	op_pk_nfd_get(pk_src,"SRC",&dest);
	op_pk_nfd_get(pk_src,"SRC_INIT",&dest_final);	
	
	//Sets my father
	change_father(dest,dest,1);	
		
	//Creation of the packet
	pk_dest = op_pk_create_fmt("cdcl_cds_reconnect_rep");
	
	//Sets the relay destinations
	for(i=1;i<=NB_RELAY_FIELDS;i++)
		{
			sprintf(chaine,"RELAY%d",i);
			op_pk_nfd_get(pk_src,chaine,&addr);
			
			if (addr!=dest)						
				op_pk_nfd_set(pk_dest,chaine,addr);
			else
				op_pk_nfd_set(pk_dest,chaine,0);
		}
	
	//sets different fields
	op_pk_nfd_set(pk_dest,"PK_ID",(int)current_id++);
	op_pk_nfd_set(pk_dest,"TTL",2*k_cds+1);
	op_pk_nfd_set(pk_dest,"SRC",my_address);
	op_pk_nfd_set(pk_dest,"DEST",dest);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",dest_final);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",CDS_REVERSE_JOIN_PK_TYPE);

	//Sends it
	pk_send_delayed(pk_dest , op_dist_uniform(0.005));	

	
	//For debugging
	if (DEBUG>LOW)
		{
			sprintf(msg,"%d sends a reverse-join to %d with id=%d and relayed by %d (new father) at %f\n",my_address,dest_final,current_id-1,dest,op_sim_time());
			cluster_message(msg);
		}
	
	//Secondly, we must send a join indication for other dominators in the network (we delay it in order to desynchronize it with the establishment of the MIS
	send_join_message_delayed(1.0 + op_dist_uniform(0.005));	
}

//Forwards a reply of join message
void forward_join_reverse(Packet *pk_src){
	packet	*pk_dest;
	int		addr, src_addr, id, dest_final, ttl;
	char	chaine[15];
	char	msg[150];
	int		i;
	
	//Info from source pk
	op_pk_nfd_get(pk_src , "SRC",&src_addr);
	op_pk_nfd_get(pk_src , "PK_ID",&id);
	op_pk_nfd_get(pk_src , "DEST_FINAL",&dest_final);
	op_pk_nfd_get(pk_src , "TTL",&ttl);
	
	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest , "TTL",--ttl);

	//if (dest_final != my_address)
	if((my_cds.father==0) || (my_cds.state==DOMINATEE))
		{		
			//Sets the relay destination
			i = NB_RELAY_FIELDS;
			addr = 0;
			while((addr==0)&&(i-->1))
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_get(pk_dest,chaine,&addr);
				}

			add_son(src_addr);
			if (my_cds.state!=DOMINATEE)
				update_state_cds(DOMINATOR);

			//We are not the final destination
			if (addr!=0)
				{
					op_pk_nfd_set(pk_dest,"DEST",addr);
					op_pk_nfd_set(pk_dest,chaine,0);
					op_pk_nfd_set(pk_dest,"SRC",my_address);			

					//Sets my father, my sons ...
					change_father(addr,addr,1);
					
					//I consider that I didn't receive the last ap_hello, but I don't consider myself disconnected
					my_cds.last_hello_ap_seen = op_sim_time() - 1.1*INTERVALL_AP_HELLO;
			
					//Sends the packet
					pk_send_delayed(pk_dest , op_dist_uniform(0.001));

					if (DEBUG>LOW)
						{
							sprintf(msg,"%d forwards a join-reverse from %d, with ttl=%d and id=%d to %d (new father) at %f\n",my_address,src_addr,ttl,current_id-1,addr,op_sim_time());
							cluster_message(msg);
						}
				}
		}
	else
		{
			if (DEBUG>LOW)
				{
					sprintf(msg,"%d, a dominator, has a new son : %d, He adds it at %f\n",my_address,src_addr,op_sim_time());					
					cluster_message(msg);
				}
			//Sets my my sons ...
			add_son(src_addr);
		}
}


/*-----------------------------------------------------------------------------------------------

										AP HELLOS

-----------------------------------------------------------------------------------------------*/

void ap_hello(int* arg, int code){
	Packet*	pkptr;
	
	//I create the hello-ap packet
	pkptr = op_pk_create_fmt("cdcl_cds_ap_hello");
	op_pk_nfd_set(pkptr,"SRC"			,my_address);
	op_pk_nfd_set(pkptr,"DEST"			,-1);
	op_pk_nfd_set(pkptr,"RELAY"			,my_address);

	op_pk_nfd_set(pkptr,"PK_ID"			,my_cds.current_id_ap_hello++);
	op_pk_nfd_set(pkptr,"ID_AP"			,my_address);
	op_pk_nfd_set(pkptr,"OPTION_TYPE"	,AP_HELLO_PK_TYPE);
	op_pk_nfd_set(pkptr,"TTL"			,MAX_NETWORK_RADIUS);

	op_pk_nfd_set(pkptr,"FATHER"		,my_cds.father);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD"	,my_clusterhead.address);
	op_pk_nfd_set(pkptr,"WEIGHT"		,my_weight.value);

	pk_send_delayed(pkptr , op_dist_uniform(0.05));

	
	//To be sure that the id isn't out of limits
	if (my_cds.current_id_ap_hello >  65535)
		my_cds.current_id_ap_hello = 0;
	my_cds.id_last_hello_ap_seen = my_cds.current_id_ap_hello;

	//We schedule the newt ap-advertisement
	op_intrpt_schedule_call(op_sim_time() + INTERVALL_AP_HELLO , AP_HELLO_CODE , ap_hello , -1);	
}

//Forwards an ap-hello (for dominators)
void forward_ap_hello(Packet* pk_src){
	packet	*pk_dest;
	int		addr , id_ap , id_pk , ttl;
	char	msg[150];
	
	//Info from pk source
	op_pk_nfd_get(pk_src , "SRC",	&addr);
	op_pk_nfd_get(pk_src , "ID_AP",	&id_ap);
	op_pk_nfd_get(pk_src , "PK_ID",	&id_pk);
	op_pk_nfd_get(pk_src , "TTL",	&ttl);
	
	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	
	//Info
	op_pk_nfd_set(pk_dest , "RELAY" 	, my_address);
	op_pk_nfd_set(pk_dest , "SRC"		, my_address);
	op_pk_nfd_set(pk_dest , "FATHER"	, my_cds.father);
	op_pk_nfd_set(pk_dest , "CLUSTERHEAD",my_clusterhead.address);
	op_pk_nfd_set(pk_dest , "WEIGHT"	, my_weight.value);
	op_pk_nfd_set(pk_dest , "TTL"		, --ttl);
	
	if (ttl>0)
		{
			pk_send_delayed(pk_dest , op_dist_uniform(0.1));
			
	
			if(DEBUG>LOW)
				{
					sprintf(msg,"AP-HELLO: forwarding at %f (id_ap=%d and id_pk=%d)\n" , op_sim_time() , id_ap , id_pk);
					cluster_message(msg);
				}
		}
}

//updates the informations associated with the last ap_hello
void update_ap_hellos_table(int src, int id_ap, int id_hello){
	ap_hellos		*ptr, *ptr2;
	short			is_found;
	
	ptr = ap_hellos_table;
	is_found = 0;

	while (ptr!=NULL)
		{
			//We have found it, we modify its "last_seen" time
			if (ptr->address == src)
				{
					is_found 		= 1;
					ptr->last_seen 	= op_sim_time();
					ptr->id_ap 	= id_ap;
					ptr->id_hello	= id_hello;
				}
			
			ptr=ptr->next;
		}

	//We didn't find it, we must add it
	if (!is_found)
		{
			//Memory Allocation for a new cell in the list of neighbours
			ptr2 = (struct ap_hellos*)op_prg_mem_alloc(sizeof(ap_hellos));
			if (ptr2==NULL)
				{
					printf("error in the memory allocation for the creation of a new cell in the list of neighbours");
				}

			//Add the correct content
			ptr2->address 	= src;
			ptr2->last_seen = op_sim_time();
			ptr2->id_ap 	= id_ap;
			ptr2->id_hello	= id_hello;

			//Updates the pointers
			ptr2->next = ap_hellos_table;
			ap_hellos_table = ptr2;			
		}
}

void forward_packet_ap_hello_dominatee(Packet* pkptr, Stathandle stat_local, Stathandle stat_global){
	int		dest_addr, ttl, id;

	op_pk_nfd_get(pkptr,"DEST",&dest_addr);
	op_pk_nfd_get(pkptr,"PK_ID",&id);

	op_pk_nfd_set(pkptr,"RELAY",my_address);
	
	if (op_pk_nfd_get(pkptr,"TTL",&ttl) != OPC_COMPCODE_FAILURE)
		op_pk_nfd_set(pkptr,"TTL",--ttl);
	
	//Transmission
	pk_send_delayed(pkptr , op_dist_uniform(0.005)); 	
}



/*-----------------------------------------------------------------------------------------------

								MAINTENANCE OF CDS

-----------------------------------------------------------------------------------------------*/

//Update the infos about cds from the hello packets
void update_cds(Packet *pkptr){
	int			addr_src , state , ttl , its_id , its_dominator , its_weight;
	short 		is_loop_entered;
	neigh_cell	*ptr_neigh;
	char		msg[250];

	//Pick up the source of packet
	op_pk_nfd_get(pkptr,"SRC"		,&addr_src);	
	op_pk_nfd_get(pkptr,"STATE"		,&state);
	op_pk_nfd_get(pkptr,"FATHER"	,&its_dominator);
	op_pk_nfd_get(pkptr,"PK_ID"		,&its_id);
	op_pk_nfd_get(pkptr,"WEIGHT"	,&its_weight);
	op_pk_nfd_get(pkptr,"TTL"		,&ttl);
	is_loop_entered = 0;
	
	//Update the cds table
	ptr_neigh = neighbour_table;
	while ((ptr_neigh != NULL)&&(!is_loop_entered))
		{
			if (ptr_neigh->address == addr_src)
				{
					if (DEBUG>MAX)
						{
							sprintf(msg,"(id=%d) (CDS)-Hello, updated : addr=%d, state=%d, father=%d, weight=%d \n",its_id,addr_src,state,its_dominator,its_weight);
							cluster_message(msg);
						}	

					is_loop_entered				= 1;
					ptr_neigh->state 			= state;
					ptr_neigh->father			= its_dominator;
					ptr_neigh->weight			= its_weight;
				}
			ptr_neigh = ptr_neigh->next;
		}

	//Add this node in my sons if I am its father and that it's not already present in my list
	if ((my_cds.state==DOMINATOR) && (state==DOMINATOR) && (its_dominator==my_address))		
		add_son(addr_src);
	

	//Add this node in my dominatees if I am its dominator and that it's not already present in my list
	if ((my_cds.state==DOMINATOR) && (state==DOMINATEE) && (its_dominator==my_address))		
		add_dominatee(addr_src);

	//Delete that node of my dominatee if it is inscribed in my list but it declares another father
	if ((is_my_dominatee(addr_src)) && ((its_dominator!=my_address) || (state != DOMINATEE)) )
		{
			if (DEBUG>MEDIUM)
				{
					sprintf(msg,"%d deletes its dominatee %d\n",my_address,addr_src);
					cluster_message(msg);				
				}
			delete_dominatee(addr_src);
		}
	
	//Delete that node of my sons if it is inscribed in my list but it declares another father
	if ((is_in_son_list(addr_src)) && ((its_dominator != my_address) || (state != DOMINATOR) || (is_unidirectional_link(addr_src))))
		{
			if (DEBUG>MEDIUM)
				{
					sprintf(msg,"%d deletes its son %d (its current dominator %d)\n" , my_address , addr_src , its_dominator);
					cluster_message(msg);				
				}
			delete_son(addr_src);
			
			//I warn the upper layer process that I lost a son (it will pick up the address in my state variable if it wants it)
			last_son_lost = addr_src;
			if ((my_cds.state==DOMINATOR) && (process_higher_layer_type == LOCALIZATION))
				op_intrpt_schedule_remote(op_sim_time() , SON_LOST_CODE , process_higher_layer_id);
		}
}

/*------------------------- Utils for Reconnection ---------------------------*/
void advertise_our_dominator_of_nothing_neighbour(){
	Packet*	pkptr;
	
	pkptr = op_pk_create_fmt("cdcl_minimal");
	op_pk_nfd_set(pkptr,"SRC",my_address);
	op_pk_nfd_set(pkptr,"DEST",my_cds.relay);
	op_pk_nfd_set(pkptr,"PK_ID",current_id++);
	op_pk_nfd_set(pkptr,"TTL",k_cds);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",NOTHING_NEIGH_CDS_PK_TYPE);
	pk_send(pkptr);	
}

//Forwards one packet to my dominator (with ttl-- and SRC changed)
void forward_packet_to_dominator_cds(Packet* pk_src){
	int		ttl;
	Packet	*pk_dest;

	//Pk creation
	pk_dest = op_pk_copy(pk_src);
	
	//Forward, but in unicast, to my dominator (even if the packet sent is in broadcast)
	op_pk_nfd_set(pk_dest,"DEST",my_cds.relay);
	
	//Common Info
	if (op_pk_nfd_get(pk_src , "TTL" , &ttl) != OPC_COMPCODE_FAILURE)
		op_pk_nfd_set(pk_dest, "TTL" , --ttl);
	op_pk_nfd_set(pk_dest,"SRC",my_address);

	//Tranmission
	nb_cds_recon_pk++;
	if (my_weight.value > LOW_WEIGHT )
		pk_send_delayed(pk_dest , (double)(15/(my_weight.value)) + op_dist_uniform(0.005));		
	else
		pk_send_delayed(pk_dest , 5);	
}

//Forwards one packet (with ttl-- and SRC changed)
void forward_packet_cds(Packet* pk_src){
	int		ttl;
	Packet	*pk_dest;

	//Pk to send preparation
	pk_dest = op_pk_copy(pk_src);
	if (op_pk_nfd_get(pk_src , "TTL" , &ttl) != OPC_COMPCODE_FAILURE)
		op_pk_nfd_set(pk_dest , "TTL" , --ttl);
	op_pk_nfd_set(pk_dest , "SRC" , my_address);

	//Transmission
	nb_cds_recon_pk++;
	if (my_weight.value > LOW_WEIGHT )
		pk_send_delayed(pk_dest , (double)(15/(my_weight.value)) + op_dist_uniform(0.005));				
	else
		pk_send_delayed(pk_dest , 5);	
}



/*--------------------------- Reconnection ----------------------------------*/
//Sends a reconnection-request
void send_reconnect_request(int id_last_ap_hello, int ttl){
	Packet*	pkptr;
	char	msg[200];

	//Send a packet of reconnection request
	pkptr = op_pk_create_fmt("cdcl_cds_reconnect");
	op_pk_nfd_set(pkptr,"SRC"			,my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT"		,my_address);
	op_pk_nfd_set(pkptr,"DEST"			,-1);
	op_pk_nfd_set(pkptr,"PK_ID"			,current_id++);
	op_pk_nfd_set(pkptr,"ID_AP_HELLO"	,++id_last_ap_hello);			//We want that only nodes, that have more recent informations, reply
	op_pk_nfd_set(pkptr,"OPTION_TYPE"	,CDS_RECONNECT_PK_TYPE);
	op_pk_nfd_set(pkptr,"TTL"			,ttl);					//One dominator at least, at 2k+1 hops, is connected
					
	add_address_id_couple(my_address,current_id-1);
	pk_send_delayed(pkptr , op_dist_uniform(0.005));	

	//Stats
	if (my_cds.nb_retry_reconnect_cds==0)
		nb_cds_recon++;
	nb_cds_recon_req++;						
	nb_cds_recon_pk++;
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "%d sends a reconnect-req at %f\n", my_address, op_sim_time());
			cluster_message(msg);
		}
}

//Reply to a tree-reconnect request
void reply_cds_reconnect(Packet *pk_src){
	Packet		*pk_dest;
	char		chaine[12], msg[100];
	int			dest , dest_final , i , id_last_ap_hello , id_ap_hello_in_pk;
	ap_hellos	*ptr;
	
	
	//Search the id of the last ap_hello seen (from our father)
	ptr = ap_hellos_table;
	id_last_ap_hello = 0;
	while(ptr!=NULL)
		{
			if ((ptr->address==my_cds.father) && (ptr->id_hello > id_last_ap_hello))
				id_last_ap_hello = ptr->id_hello;
			
			ptr=ptr->next;
		}	
	
	
	//If the id of the last seen ap-hello is greater than the id in the packet, we answer, else we do nothing
	op_pk_nfd_get(pk_src,"ID_AP_HELLO",&id_ap_hello_in_pk);
	if ((id_ap_hello_in_pk <= id_last_ap_hello)||(is_AP))
		{
			pk_dest = op_pk_create_fmt("cdcl_cds_reconnect_rep");
	
			for(i=2;i<=NB_RELAY_FIELDS;i++)
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_set(pk_dest,chaine,0);
				}
	
			op_pk_nfd_get(pk_src,"SRC",			&dest);
			op_pk_nfd_get(pk_src,"SRC_INIT",	&dest_final);	

			op_pk_nfd_set(pk_dest,"OPTION_TYPE",CDS_RECON_REP_PK_TYPE);
			op_pk_nfd_set(pk_dest,"PK_ID",		(int)current_id++);
			op_pk_nfd_set(pk_dest,"ID_AP_HELLO",(int)current_id++);
			op_pk_nfd_set(pk_dest,"TTL",		2*k_cds);
			
			op_pk_nfd_set(pk_dest,"SRC",		my_address);
			op_pk_nfd_set(pk_dest,"RELAY1",		my_address);
			op_pk_nfd_set(pk_dest,"DEST",		dest);
			op_pk_nfd_set(pk_dest,"DEST_FINAL",	dest_final);
			
			op_pk_nfd_set(pk_dest,"PRIORITY",	my_weight.value);


			nb_cds_recon_pk ++;
			pk_send_delayed(pk_dest , op_dist_uniform(0.005));
			
			if (DEBUG>LOW)
				{
					sprintf(msg,"%d answers to %d via %d for a reconnection of the cds (last_ap_hello=%f) at %f\n",my_address,dest_final,dest,my_cds.last_hello_ap_seen,op_sim_time());
					cluster_message(msg);					
				}
		}
	else
		{
			if (DEBUG>LOW)
				{
					sprintf(msg,"I can't answer, I have obsolete informations (actual time =%f, actual father=%d, last_ap_hello=%f/%d, asked=%d)\n",op_sim_time(),my_cds.father,my_cds.last_hello_ap_seen,id_last_ap_hello,id_ap_hello_in_pk);
					cluster_message(msg);
				}
		}	
}

//Forwards the reconnection init reply (and stop it if we are the final destination)
void forward_reconnect_reply(Packet* pk_src){
	Packet			*pk_dest;
	int 			src , dest, id, ttl, test , i , priority;
	relay_cell*		ptr;
	short			loop_test;
	char			msg[150],chaine[12];

	//Info from pk source
	op_pk_nfd_get(pk_src ,"SRC",			&src);
	op_pk_nfd_get(pk_src , "DEST_FINAL",	&dest);
	op_pk_nfd_get(pk_src , "PK_ID",			&id);
	op_pk_nfd_get(pk_src , "TTL",			&ttl);
	op_pk_nfd_get(pk_src , "PRIORITY",		&priority);

	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest , "TTL",			--ttl);
	op_pk_nfd_set(pk_dest , "PRIORITY",		priority + my_weight.value);

	loop_test=0;
	ptr = relay_table;
	while(ptr!=NULL)
		{
			if (ptr->src==dest)
				{
					op_pk_nfd_set(pk_dest , "DEST" , ptr->relay);
					loop_test = 1;
				}
			
			ptr=ptr->next;
		}
	if (loop_test)
		{
			//Add our address in the relay fields
			i=1;
			test = 1;
			while ((test != 0) && (i<9))
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_get(pk_src , chaine , &test);
					i++;
				}
			
			op_pk_nfd_set(pk_dest , chaine , my_address);
			op_pk_nfd_set(pk_dest , "SRC" , my_address);
					
			//Send the packet
			nb_cds_recon_pk++;
			pk_send_delayed(pk_dest , op_dist_uniform(0.005));
		}
	else
		{
			sprintf(msg,"!!!!!!!!! errror !!!!!!!! %d has not found the id %d, the packet is discarded (possibly a timeout)\n",my_address,id);
			cluster_message(msg);
		}
}


//Send a message to advertise the dominatees between us and the dominator which answer us
//returns 1 if all required informations are present, else 0 (for example when the packet is unknown)
int connection_cds_init(Packet *pk_src){
	char	msg[150],chaine[15];
	Packet*	pk_dest;
	int		addr, dest, i, dest_final;
	
	//We had a reply !
	//my_cds.nb_retry_reconnect_cds = 0;
	//I consider that I didn't receive the last ap_hello, but I don't consider myself disconnected
	//my_cds.last_hello_ap_seen = op_sim_time() - 1.01*INTERVALL_AP_HELLO;

	
	//Change its father
	op_pk_nfd_get(pk_src,"SRC",&dest);
	change_father(dest,dest,1);
	
	
	//Extracts the type of the original packet
   	op_pk_format(pk_src,msg);
	//The original packet was a reconnect-reply
	if (strcmp(msg,"cdcl_cds_reconnect_rep")==0)
		{
			pk_dest = op_pk_copy(pk_src);
	
			op_pk_nfd_set(pk_dest,"OPTION_TYPE",RECONNECT_INIT_PK_TYPE);
			op_pk_nfd_set(pk_dest,"PK_ID",		current_id++);
			op_pk_nfd_set(pk_dest,"SRC",		my_address);
			op_pk_nfd_set(pk_dest,"TTL",		2*k_cds);
			op_pk_nfd_set(pk_dest,"STATE",		my_cds.state);
			op_pk_nfd_set(pk_dest,"FATHER",		my_cds.father);
			op_pk_nfd_set(pk_dest,"CLUSTERHEAD",my_clusterhead.address);
	
			op_pk_nfd_get(pk_dest,"RELAY1",&dest_final);
			op_pk_nfd_set(pk_dest,"DEST_FINAL",dest_final);
	
			i = NB_RELAY_FIELDS;
			addr = 0;
			while((addr==0)&&(i-->1)&&(addr!=dest_final))
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_get(pk_dest,chaine,&addr);
				}
			op_pk_nfd_set(pk_dest,"DEST",addr);
			op_pk_nfd_set(pk_dest,chaine,0);
		}
	//The original packet was a ap-hello
	else if (strcmp(msg,"cdcl_cds_ap_hello")==0)
		{
			pk_dest = op_pk_create_fmt("cdcl_cds_reconnect_rep");
			op_pk_nfd_set(pk_dest,"OPTION_TYPE",RECONNECT_INIT_PK_TYPE);
			op_pk_nfd_set(pk_dest,"PK_ID",(int)current_id++);
			op_pk_nfd_set(pk_dest,"SRC",my_address);
			op_pk_nfd_set(pk_dest,"TTL",1);
			op_pk_nfd_set(pk_dest,"STATE",		my_cds.state);
			op_pk_nfd_set(pk_dest,"FATHER",		my_cds.father);
			op_pk_nfd_set(pk_dest,"CLUSTERHEAD",my_clusterhead.address);
			
			op_pk_nfd_get(pk_src,"SRC",&dest_final);
			op_pk_nfd_set(pk_dest,"DEST",dest_final);
			op_pk_nfd_set(pk_dest,"DEST_FINAL",dest_final);
		}
	else
		{
			printf("error : format %s unknown in function connection_cds_init()\n",msg);
			return(0);
		}

	
	if (DEBUG>LOW)
		{
			sprintf(msg,"%d (new father=%d) sends a message of reconnection to %d at %f\n",my_address,my_cds.father,dest_final,op_sim_time());
			cluster_message(msg);
		}
	
	
	//I consider that I didn't receive the last ap_hello, but I don't consider myself disconnected
	//my_cds.last_hello_ap_seen = op_sim_time() - 1.1*INTERVALL_AP_HELLO;
	//nb_cds_recon_pk += my_cds.nb_retry_reconnect_cds;
	pk_send_delayed(pk_dest , op_dist_uniform(0.005));
	return(1);
}


//Forwards a message to advertise other intermediaries
void forward_reconnect_init(Packet *pk_src){
	Packet	*pk_dest;
	int		id, dest_final, ttl, src, dest,i;
	char	chaine[15],msg[150];
	
	//Info from source pk
	op_pk_nfd_get(pk_src , "SRC",			&src);
	op_pk_nfd_get(pk_src , "PK_ID",			&id);
	op_pk_nfd_get(pk_src , "DEST_FINAL",	&dest_final);
	op_pk_nfd_get(pk_src , "TTL",			&ttl);
	
	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest,"TTL",--ttl);

	
	//I am not a valid dominator
	if ( (dest_final != my_address) && ((my_cds.state!=DOMINATOR)||(my_cds.father==0)||(my_cds.last_hello_ap_seen < op_sim_time()-INTERVALL_AP_HELLO)) )
		{
			//If not dominator --> become it
			if (my_cds.state!=DOMINATOR)
				update_state_cds(DOMINATOR);
						
			//Update my son
			add_son(src);
						
			//Sets the relay destination
			i = NB_RELAY_FIELDS;
			dest=0;
			while((dest==0)&&(i-->0))
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_get(pk_src , chaine , &dest);
				}
			op_pk_nfd_set(pk_dest,"DEST",dest);
			op_pk_nfd_set(pk_dest,chaine,0);
			op_pk_nfd_set(pk_dest,"SRC",my_address);		
	
			
			//Sets my father
			change_father(dest,dest,1);
			
			//Transmission
			nb_cds_recon_pk++;
			pk_send_delayed(pk_dest , op_dist_uniform(0.005));
			
			if (DEBUG>LOW)
				{
					sprintf(msg,"CDS-RECONNECT: %d is an intermediary to reconnect the CDS -> becomes dominator and sets its father to %d and sons to %d at %f\n",my_address,my_cds.father,src,op_sim_time());
					cluster_message(msg);		
				}
		}
	else
		{
			//Update my son
			add_son(src);		
			if (DEBUG>LOW)
				{
					sprintf(msg,"CDS-RECONNECT: %d is the end to reconnect the CDS (father %d not changed) -> sets its son to %d at %f\n",my_address,my_cds.father,src,op_sim_time());
					cluster_message(msg);		
				}
		}
	
	
}

void advertise_useless_dominator(){
	Packet*	pkptr;
	
	pkptr = op_pk_create_fmt("cdcl_cds_useless_dominator");
	op_pk_nfd_set(pkptr,"SRC",		my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT",	my_address);
	op_pk_nfd_set(pkptr,"FATHER",	my_cds.father);
	op_pk_nfd_set(pkptr,"DEST",		-1);
	op_pk_nfd_set(pkptr,"PK_ID",	current_id++);
	op_pk_nfd_set(pkptr,"TTL",		k_cds);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",USELESS_DOMINATOR_PK_TYPE);
	
	pk_send(pkptr);	
}

void break_all_our_tree(){
	Packet	*pkptr;
	
	
	pkptr = op_pk_create_fmt("cdcl_minimal");
	op_pk_nfd_set(pkptr,"SRC",my_address);
	op_pk_nfd_set(pkptr,"DEST",-1);
	op_pk_nfd_set(pkptr,"PK_ID",current_id++);
	op_pk_nfd_set(pkptr,"TTL",k_cds);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",BREAK_CDS_PK_TYPE);
	

	//Transmission
	pk_send(pkptr);
	reinit_cds_infos();
}

void reinit_cds_infos(){
	int 	i;
	char	msg[150];
	Packet*	pkptr;
	
	//Stats
	nb_nodes_impacted_by_cds_breaks++;	
	
	//CDS Infos
	change_father(ZERO , ZERO , ZERO);
	update_state_cds(IDLE);
	for(i=0;i<KCDS_MAX;i++) {my_cds.join_already_forwarded[i] = 0;}
	my_cds.sons 		= NULL;
	my_cds.dominatees 	= NULL;
	my_cds.id_ap 		= 0;
	//my_cds.time_cds_reinit = op_sim_time();
	
	//Clusters infos
	change_clusterhead(ZERO , ZERO , ZERO);
	my_clusterhead.time_last_break = -1;
	
	if (DEBUG > 1)
		{
			sprintf(msg,"%d reinitalizes its cds-informations and father at %f. It received a break_cds message\n",my_address,op_sim_time());
			cluster_message(msg);
		}	
	
	//Generates an hello with the new info and sends it
	pkptr = hello_packet_generate();
	pk_send_delayed(pkptr , op_dist_uniform(0.005));

	
	
	//my_cds.is_maintenance_scheduled = 0;
	//op_intrpt_disable(OPC_INTRPT_SELF,CDS_MAINTENANCE_CODE,OPC_TRUE);		
}

//Adds a new candidate for a potential father (reconnection, breaks...)
//Returns 1 if the packet contains all required informations, else 0
Boolean add_cds_reconnect_candidate(Packet* pkptr){
	int			addr, weight , father , priority , ttl;
	candidate*	ptr;
	char		msg[20] , chaine[10];
	int			i;
	

	//Memory Allocation for a new cell in the list of neighbours
	ptr = (struct candidate*)op_prg_mem_alloc(sizeof(candidate));
	if (ptr==NULL)
		{
			printf("error in the memory allocation for the creation of a new cell in the list of cds candidates");
		}

	
	//------- To have the father of the candidate ------------//
	//Extracts the type of the original packet
   	op_pk_format(pkptr , msg);
	//The original packet was a reconnect-reply
	if (strcmp(msg,"cdcl_cds_reconnect_rep")==0)
		{
			op_pk_nfd_get(pkptr , "SRC",		&addr);
			op_pk_nfd_get(pkptr , "TTL",		&ttl);
			op_pk_nfd_get(pkptr , "PRIORITY",	&priority);		//Weight = sum of the weight of all intermediaries that are dominatees
			weight = priority / (2*k_cds - ttl + 1);

			i = NB_RELAY_FIELDS;
			father = 0;
			while((father==0)&&(i>=1))
				{
					sprintf(chaine , "RELAY%d" , i--);
					op_pk_nfd_get(pkptr , chaine , &father);
				}
			sprintf(chaine , "RELAY%d" , i);
			op_pk_nfd_get(pkptr,chaine,&father);
		}
	//The original packet was a ap-hello
	else if (strcmp(msg,"cdcl_cds_ap_hello")==0)
		{
			op_pk_nfd_get(pkptr , "FATHER",	&father);	
			op_pk_nfd_get(pkptr , "SRC"	,	&addr);
			op_pk_nfd_get(pkptr , "WEIGHT",	&weight);
		}
	else
		{
			printf("error : format %s unknown in function add_cds_reconnect_candidate()\n",msg);
			return(OPC_FALSE);
		}
			
	ptr->address 	= addr;
	ptr->parent 	= father;
	ptr->weight 	= weight;
	ptr->last_seen 	= op_sim_time();
	ptr->pk 		= op_pk_copy(pkptr);	
	ptr->next 		= my_cds.secondary_fathers;
	my_cds.secondary_fathers = ptr;
	
	return(OPC_TRUE);
}



void delete_timeout_cds_candidates(double timeout_max){
	candidate	*ptr , *ptr2;
	
	//We delete the timeout entries in cds_candidates
	ptr = my_cds.secondary_fathers;
	ptr2 = NULL;
	while(ptr!=NULL)
		{
			if ((ptr->last_seen <= op_sim_time() - timeout_max)||(ptr->address == my_address))	
				{
					if (ptr == my_cds.secondary_fathers) //The particular case of a delete entry in head of the list
						{
							my_cds.secondary_fathers = ptr->next;
							free(ptr);
							ptr = my_cds.secondary_fathers;
						}
					else
						{
							ptr2->next = ptr->next;
							free(ptr);
							ptr = ptr2;
						}
				}
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr = ptr->next;
		}	
}



/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//											CLUSTERS



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/







/*-----------------------------------------------------------------------------------------------

								CONSTRUCTION OF CLUSTERS

-----------------------------------------------------------------------------------------------*/







void update_cluster_infos(Packet* pkptr){
	int				address , weight , clusterhead , ttl;
	cluster_cell	*ptr , *ptr2;
	char			msg[200];
	

	op_pk_nfd_get(pkptr,"SRC_INIT",&address);
	op_pk_nfd_get(pkptr,"WEIGHT",&weight);
	op_pk_nfd_get(pkptr,"CLUSTERHEAD",&clusterhead);
	op_pk_nfd_get(pkptr,"TTL",&ttl);

	//Search if the address already exists
	ptr = cluster_table;														
	while ((ptr!=NULL) && (ptr->address!=address))
		{
			ptr2=ptr; 			//in order to keep the previous cell of the list
			ptr=ptr->next;
		}							
	//This address doesn't exist, we add an entry
	if (ptr==NULL)
		{
			if (DEBUG>MEDIUM)
				{
					sprintf(msg,"Cluster - %d adds the node %d with the weight %d , clusterhead=%d , hops %d at %f\n",my_address,address,weight,clusterhead,(k_cluster-k_cds)-ttl+1,op_sim_time());
					cluster_message(msg);
				}
				
			//Memory Allocation for a new cell in the list of neighbours
			ptr = (struct cluster_cell*)op_prg_mem_alloc(sizeof(cluster_cell));
			if (ptr==NULL)
				{
					printf("error in the memory allocation for the creation of a new cell in the list of clusters");
				}

			//Add the correct content
			ptr->address 		= address;
			ptr->weight 		= weight;
			ptr->hops 			=  (k_cluster-k_cds)-ttl+1;							
			ptr->timeout 		= op_sim_time() + 2.1*INTERVALL_FAST_HELLO;					
			ptr->clusterhead 	= clusterhead;		
			
			//Updates the pointers
			ptr->next 	= NULL;
			ptr2->next 	= ptr;
		}
						
	if ((ptr!=NULL)&&(address!=my_address))
		{
			if (DEBUG>MEDIUM)
				{
					sprintf(msg,"Cluster - %d updates the node %d with weight=%d at %f\n",my_address,address,weight,op_sim_time(),op_sim_time());
					cluster_message(msg);
				}
			ptr->weight			= weight;
			ptr->clusterhead 	= clusterhead;		
			ptr->hops 			=  (k_cluster-k_cds)-ttl+1;	
			ptr->timeout 		=  op_sim_time() + 2.1*INTERVALL_FAST_HELLO;
		}
}

// --------------------------  Packets ------------------------------

void send_hello_cluster(){
	Packet	*pkptr;
	char	msg[150];	
	
	if (DEBUG>HIGH)
		{
			sprintf(msg,"%d sends an hello cluster at %f\n",my_address,op_sim_time());
			cluster_message(msg);
		}
	
	pkptr = op_pk_create_fmt ("cdcl_cluster_hello");
	op_pk_nfd_set(pkptr,"TTL",k_cluster-k_cds);


	// Set some general fields of the packet
	op_pk_nfd_set(pkptr,"OPTION_TYPE",HELLO_CLUSTER_PK_TYPE);
	op_pk_nfd_set(pkptr,"SRC",my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT",my_address);
	op_pk_nfd_set(pkptr,"WEIGHT",my_weight.value);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD",my_clusterhead.address);
	op_pk_nfd_set(pkptr,"DEST",-1);
	op_pk_nfd_set(pkptr,"PK_ID",current_id++);
	
	//transmission
	pk_send_delayed(pkptr, op_dist_uniform(0.005));
	
	//In order to avoid to modify myself, I add this packet as already seen
	add_address_id_couple(my_address,current_id-1);
}


//Infos + messages for a new clusterhead
void become_clusterhead(){
	Packet			*pkptr;
	char			msg[150];	
	int				ctrl;
		
	if (DEBUG>LOW)
		{
			sprintf(msg,"%d has got the highest weight, it becomes clusterhead at %f\n",my_address,op_sim_time());
			cluster_message(msg);
		}
	
	change_clusterhead(my_address,my_address,0);
	my_clusterhead.last_time_usefull 	= op_sim_time();
	
	//Sends an advertisement
	pkptr = op_pk_create_fmt ("cdcl_cluster_hello");
	op_pk_nfd_set(pkptr,"TTL",k_cluster-k_cds);
	
	// Set some general fields of the packet
	op_pk_nfd_set(pkptr,"OPTION_TYPE",JOIN_CLUSTER_PK_TYPE);
	op_pk_nfd_set(pkptr,"SRC",my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT",my_address);
	op_pk_nfd_set(pkptr,"DEST",-1);
	op_pk_nfd_set(pkptr,"WEIGHT",my_weight.value);
	op_pk_nfd_set(pkptr,"PK_ID",current_id++);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD",my_clusterhead.address);	

	//Send it !
	pk_send_delayed(pkptr , op_dist_uniform(0.005));

	//If we have old maintenance, we must send clusterhead hellos
	switch (cluster_algos_type)
		{
			case THEO_OLD :
					op_intrpt_schedule_call(op_sim_time() + INTERVALL_CLUSTERHEAD_HELLO , CLUSTERHEAD_HELLO_CODE , clusterhead_hello , ctrl);
				break;
		}
	add_address_id_couple(my_address,current_id-1);
}


void send_decision_cluster(){
	Packet	*pkptr;
	char	msg[150];	
	
	if (DEBUG>HIGH)
		{
			sprintf(msg,"%d sends an decision-cluster at %f\n",my_address,op_sim_time());
			cluster_message(msg);
		}
	
	pkptr = op_pk_create_fmt ("cdcl_cluster_hello");
	op_pk_nfd_set(pkptr,"TTL",k_cluster-k_cds);


	// Set some general fields of the packet
	op_pk_nfd_set(pkptr,"OPTION_TYPE",JOIN_CLUSTER_PK_TYPE);
	op_pk_nfd_set(pkptr,"SRC",my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT",my_address);
	op_pk_nfd_set(pkptr,"WEIGHT",my_weight.value);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD",my_clusterhead.address);
	op_pk_nfd_set(pkptr,"DEST",-1);
	op_pk_nfd_set(pkptr,"PK_ID",current_id++);
	
	//op_stat_write(cluster_sent_handle,op_pk_total_size_get(pkptr));
	//op_stat_write(total_cluster_sent_handle,op_pk_total_size_get(pkptr));
	pk_send_delayed(pkptr , op_dist_uniform(0.005));
	add_address_id_couple(my_address,current_id-1);
}


// --------------------------  Utils ------------------------------


//Change the infos after a clusterhead changement
void change_clusterhead(int ch, int relay, short hops){
	cluster_cell 	*ptr;
	char			msg[150];
	
	if (DEBUG>LOW)
		{
			sprintf(msg,"%d changes its clusterhead from %d to %d at %f\n",my_address,my_clusterhead.address,ch,op_sim_time());
			cluster_message(msg);
		}
	old_cluster_topo.old_clusterhead = my_clusterhead.address;
			
	//Stats about cluster changes	
	//Clusterhead=0 is not a "real" clusterhead (first clusterhead change not comptabilized)
	if (my_clusterhead.address == my_address)
		nb_changes_of_clusterheads++;
	else if ((my_clusterhead.address != 0) && (ch != my_address))
		{
			nb_nodes_which_change_their_clusterheads++;
			if (my_cds.state == DOMINATOR)
				nb_dominators_which_change_their_clusterheads++;
		}		

	
	my_clusterhead.address 			= ch;
	my_clusterhead.nb_recon_try		= 0;
	my_clusterhead.relay_last_seen 	= op_sim_time();
	my_clusterhead.last_seen 		= op_sim_time();
	my_clusterhead.relay			= relay;
	my_clusterhead.hops 			= hops;
	
	//Sets our clusterhead in the table
	ptr = cluster_table;
	while((ptr!=NULL)&&(ptr->address!=my_address))
		ptr=ptr->next;
	if (ptr!=NULL)
		ptr->clusterhead = ch;		
	
	my_clusterhead.construct_cluster = 4;
}

//Send periodic cluster-hellos
void cluster_hello(int* arg, int code){
	if(my_cds.state==DOMINATOR)
		{
			if (!is_sleeping.value)
				send_hello_cluster();

			last_ev_cluster_hello = op_intrpt_schedule_call(op_sim_time() + INTERVALL_FAST_HELLO , CLUSTER_HELLO_CODE , cluster_hello , -1);	
		}
}

//Verify if I don't have the highest weight
int own_highest_weight_cluster(){
	cluster_cell	*ptr;
	int				id_highest_weight , highest_weight;
	
	id_highest_weight	= 0;
	highest_weight		= 0;
	//I must have the highest weight of my neighbours (Dominators-CDS Neigbors)
	ptr = cluster_table;
	while (ptr!=NULL)
		{
			//Updates our weight
			if (ptr->address == my_address)
				ptr->weight = my_weight.value;
		
			//Verify the highest weight // id
			if ((ptr->clusterhead == 0) && (ptr->hops <= k_cluster-k_cds))
				{
					//We have a conflict (2 weights equals) -->resolution with the id
					if ( (ptr->weight == highest_weight) && (ptr->address > id_highest_weight) )
						{
							id_highest_weight = ptr->address;
							highest_weight = ptr->weight;
						}
					//This weight is the best
					if (ptr->weight > highest_weight)
						{
							id_highest_weight = ptr->address;
							highest_weight = ptr->weight;
						}
				}
			ptr = ptr->next;
		}	
	
	return(id_highest_weight==my_address);
}

//returns 1 if addr has no clusterhead in neighbour table
int has_no_clusterhead(int addr){
	neigh_cell	*ptr;
	
	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			if (ptr->address==addr)
				{
					if (ptr->clusterhead!=0)
						return(0);
					else
						return(1);
				}
			ptr = ptr->next;
		}
	return(1);
}

//Returns 1 if all the k(cluster) neighbours have initiated the construction of a cluster
Boolean all_neighbours_cluster_init(){
	neigh_cell	*ptr;
	
	if (my_cds.state!=DOMINATOR)
		return(OPC_FALSE);
	
	ptr = neighbour_table;
	while (ptr!=NULL)
		{
			//If one dominator didn't intiate the cluster-construction
			if ((!ptr->cluster_init_flag) && (ptr->state==DOMINATOR) && (ptr->bidirect) && ((is_my_son(ptr->address))||(my_cds.father==ptr->address)))
				return(OPC_FALSE);
			
			//If one node is not determined (active or nothing)
			if (((ptr->state==ACTIVE) || (ptr->state==IDLE)) && (ptr->bidirect) && (ptr->hops<=k_cluster-k_cds))
				return(OPC_FALSE);
			
			ptr = ptr->next;
		}
	return(OPC_TRUE);
}

void add_cluster_init_neighbour(int addr){
		neigh_cell	*neigh_ptr;
		
		neigh_ptr = neighbour_table;
		while((neigh_ptr!=NULL)&&(neigh_ptr->address!=addr))
			{
				neigh_ptr = neigh_ptr->next;
			}
		if (neigh_ptr!=NULL)
			neigh_ptr->cluster_init_flag = 1;	
}

void delete_cluster_init_neighbour(int addr){
		neigh_cell	*neigh_ptr;
		
		neigh_ptr = neighbour_table;
		while((neigh_ptr!=NULL)&&(neigh_ptr->address!=addr))
			{
				neigh_ptr = neigh_ptr->next;
			}
		if (neigh_ptr!=NULL)
			neigh_ptr->cluster_init_flag = 0;	
}

//Deletes the timeout entries
void update_cluster_table(){
	cluster_cell	*ptr, *ptr2;
	double			actual_time;
	
	actual_time =  op_sim_time();

	//We delete the timeout entries in cluster_table
	ptr = cluster_table;
	while(ptr!=NULL)
		{
			if (ptr->address==my_address)
				ptr->weight = my_weight.value;
			if (ptr->timeout < actual_time)	//The entry is obsolete
				{
					if (ptr == cluster_table) //The particular case of a delete entry in head of the list (not tested, I believe)
						{
							cluster_table = ptr->next;
							free(ptr);
							ptr = cluster_table;
						}
					else
						{
							ptr2->next = ptr->next;
							free(ptr);
							ptr = ptr2;
						}
				}
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr = ptr->next;
		}
}



void add_cluster_reconnect_candidate(Packet* pkptr){
	int			addr, weight;
	candidate*	ptr;
	char		msg[150];
	
	op_pk_nfd_get(pkptr,"CLUSTERHEAD",	&addr);	
	op_pk_nfd_get(pkptr,"WEIGHT",		&weight);
	
	//Memory Allocation for a new cell in the list of neighbours
	ptr = (struct candidate*)op_prg_mem_alloc(sizeof(candidate));
	if (ptr==NULL)
		{
			printf("error in the memory allocation for the creation of a new cell in the list of cluster candidates");
		}

	ptr->address = 		addr;
	ptr->parent = 		-1;
	ptr->weight = 		weight;
	ptr->last_seen = 	op_sim_time();
	ptr->pk = 			op_pk_copy(pkptr);	
	ptr->next = my_clusterhead.reconnect_candidates;
	my_clusterhead.reconnect_candidates = ptr;
	
	if (DEBUG>LOW)
		{
			sprintf(msg,"I add a new cluster candidate : %d with weight=%d\n",addr,weight);
			cluster_message(msg);
		}
}


void delete_timeout_cluster_candidates(){
	candidate	*ptr , *ptr2;
	float		timeout_time;
	
	//We have a verification of candidates every INTERVALL_HELLO/2 (both for clusters and cds)
	timeout_time = op_sim_time() - INTERVALL_HELLO/2 - 0.2;
	
	//We delete the timeout entries in cluster_candidates
	ptr = my_clusterhead.reconnect_candidates;
	ptr2 = NULL;
	while(ptr!=NULL)
		{
			if (ptr->last_seen < timeout_time)	
				{
					if (ptr == my_clusterhead.reconnect_candidates) //The particular case of a delete entry in head of the list
						{
							my_clusterhead.reconnect_candidates = ptr->next;
							op_pk_destroy(ptr->pk);
							free(ptr);
							ptr = my_clusterhead.reconnect_candidates;
						}
					else
						{
							ptr2->next = ptr->next;
							op_pk_destroy(ptr->pk);
							free(ptr);
							ptr = ptr2;
						}
				}
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr = ptr->next;
		}	
}


/*-----------------------------------------------------------------------------------------------

								MATINTENANCE OF CLUSTERS

-----------------------------------------------------------------------------------------------*/

/*------------------------------
	Clusterhead Hellos
-------------------------------*/

void clusterhead_hello(int* arg , int code){
	Packet	*pkptr;
	char	msg[150];
	int		ctrl;
	
		
	if (DEBUG>MAX)
		{
			sprintf(msg,"%d sends an hello clusterhead at %f\n",my_address,op_sim_time());
			cluster_message(msg);
		}
	if (my_cds.state==DOMINATEE)
		return;
	
	pkptr = op_pk_create_fmt ("cdcl_cluster_clusterhead_hello");
	op_pk_nfd_set(pkptr,"TTL",(k_cluster-k_cds));


	// Set some general fields of the packet
	op_pk_nfd_set(pkptr,"OPTION_TYPE",HELLO_CLUSTERHEAD_PK_TYPE);
	op_pk_nfd_set(pkptr,"SRC",my_address);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD",my_address);
	op_pk_nfd_set(pkptr,"WEIGHT",my_weight.value);
	op_pk_nfd_set(pkptr,"DEST",-1);
	op_pk_nfd_set(pkptr,"PK_ID",current_id++);
	
	pk_send_delayed(pkptr , op_dist_uniform(0.005));
	
	//In order to avoid to receive this packet, I add it as already seen
	add_address_id_couple(my_address,current_id-1);
	
	//If I am clusterhead -> I must perhaps send clusterhead-hellos
	switch (cluster_algos_type)
		{
			case THEO_OLD :
				if ((my_cds.state==DOMINATOR) && (my_clusterhead.address==my_address))
					op_intrpt_schedule_call(op_sim_time() + INTERVALL_CLUSTERHEAD_HELLO , CLUSTERHEAD_HELLO_CODE , clusterhead_hello , ctrl);
				break;
		}
	
	//In the last-seen field of the clusterhead, we had the time at which we send our clusterhead hello
	my_clusterhead.last_seen = op_sim_time();
	my_clusterhead.last_id = current_id-1;
}


/*------------------------------
	Clusterhead Reconnection
-------------------------------*/
//Sends a cluster-reconnection (or connection)
void send_connect_ch(){
	Packet		*pkptr;
	char		msg[150] , str[20];	
	int			i;
		
	if (DEBUG>LOW)
		{
			sprintf(msg,"%d sends a clusterhead request at %f\n",my_address,op_sim_time());
			cluster_message(msg);
		}


	pkptr = op_pk_create_fmt ("cdcl_cluster_reconnect");
	for(i=2;i<=NB_RELAY_FIELDS;i++)
		{
			sprintf(str,"RELAY%d",i);
			op_pk_nfd_set(pkptr,str,0);
		}
	// Set some general fields of the packet
	op_pk_nfd_set(pkptr,"OPTION_TYPE",	CON_CLUSTER_PK_TYPE);
	op_pk_nfd_set(pkptr,"TTL",			k_cluster-k_cds);
	op_pk_nfd_set(pkptr,"PK_ID",		current_id++);

	op_pk_nfd_set(pkptr,"SRC",			my_address);
	op_pk_nfd_set(pkptr,"SRC_INIT",		my_address);
	op_pk_nfd_set(pkptr,"RELAY1",		my_address);
	op_pk_nfd_set(pkptr,"DEST",			-1);
	
	op_pk_nfd_set(pkptr,"CLUSTERHEAD",	my_clusterhead.address);
	op_pk_nfd_set(pkptr,"LAST_CLUSTERHEAD_ID",my_clusterhead.last_id+1);

	pk_send_delayed(pkptr , op_dist_uniform(0.001));
	nb_cluster_con_pk++;
	add_address_id_couple(my_address,current_id-1);
}

//Forwards a cluster-reconnection request (changes src and ttl only)
void forward_connect_ch(Packet* pk_src){
	Packet		*pk_dest;
	char		msg[150] , str[20];	
	int			ttl , ch , i , dest , test=-1;
	int			address_src, address_relay;	
	
	//Get some infos
	op_pk_nfd_get(pk_src,"SRC_INIT",&address_src);
	op_pk_nfd_get(pk_src,"SRC",&address_relay);
	
	//Set some infos in dest packet	
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_get(pk_src,"TTL",		&ttl);
	op_pk_nfd_set(pk_dest,"TTL",	--ttl);	
	op_pk_nfd_set(pk_dest,"SRC",	my_address);
	op_pk_nfd_get(pk_dest,"DEST",	&dest);
	
	//Add our address in the relay fields
	i=1;
	while ((test != 0) && (i<=NB_RELAY_FIELDS))
		{
			sprintf(str,"RELAY%d",i);
			op_pk_nfd_get(pk_dest,str,&test);
			i++;
		}			
	op_pk_nfd_set(pk_dest,str,my_address);	

	
	//Destination : broadcasts if same clusterhead, else forwards towards my clusterhead
	op_pk_nfd_get(pk_src,"CLUSTERHEAD",&ch);
	if (my_clusterhead.address != ch)
		{
			op_pk_nfd_set(pk_dest,"DEST",my_clusterhead.relay);
		}
	
	//I forward the packet if : 
	//-It's the first hop
	//-It comes from one member of our cluster and hops>1 (obligatory in unicast, because we forward torwards the relay to ch))
	//-It comes in broadcast from a member of our cluster (=cluster of the source which requested a reconnection)
	if ((my_clusterhead.address == ch)||(i==3)||(dest!=-1))
		{
			add_relaying(address_src,address_relay);
	
			pk_send_delayed(pk_dest , op_dist_uniform(0.005));		
			nb_cluster_con_pk ++;
	
			if (DEBUG>MEDIUM)
				{
					sprintf(msg,"%d forwards one clusterhead request to %d (from %d via %d) at %f\n",my_address,dest,address_src,address_relay,op_sim_time());
					cluster_message(msg);
				}
		}
}


//Replies to a cluster-reconnection (change destination,...)
void reply_connect_ch(Packet* pk_src){
	Packet		*pk_dest;
	char		msg[150] , str[20];	
	int			addr_src , addr_src_init , addr , ttl , i;	
	
		
	//Pick up some infos
	op_pk_nfd_get(pk_src,"SRC",&addr_src);
	op_pk_nfd_get(pk_src,"RELAY1",&addr_src_init);
	op_pk_nfd_get(pk_src,"TTL",&ttl);
	
	pk_dest = op_pk_create_fmt ("cdcl_cluster_reconnect_rep");
	//Sets the relay destinations
	for(i=1;i<=NB_RELAY_FIELDS;i++)
		{
			sprintf(str,"RELAY%d",i);
			op_pk_nfd_get(pk_src,str,&addr);
			
			if (addr!=addr_src)						
				op_pk_nfd_set(pk_dest,str,addr);
			else
				op_pk_nfd_set(pk_dest,str,0);
		}

	//Sets some fields
	op_pk_nfd_set(pk_dest,"DEST",			addr_src);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",		addr_src_init);
	op_pk_nfd_set(pk_dest,"TTL",			k_cluster-k_cds);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",	REP_CON_CLUSTER_PK_TYPE);
	op_pk_nfd_set(pk_dest,"PK_ID",			(int)current_id++);

	op_pk_nfd_set(pk_dest,"CLUSTERHEAD",	my_clusterhead.address);
	op_pk_nfd_set(pk_dest,"SRC",			my_address);
	op_pk_nfd_set(pk_dest,"WEIGHT",			my_weight.value);
	
	//Sends the packet
	pk_send_delayed(pk_dest , op_dist_uniform(0.001));
	nb_cluster_con_pk ++;
		
	if (DEBUG>LOW)
		{
			sprintf(msg,"%d sends a clusterhead reply to %d via %d at %f\n",my_address,addr_src_init,addr_src,op_sim_time());
			cluster_message(msg);
		}
}


//Forwards a cluster-reconnection reply (change ttl, src and dest (thanks to temporary infos in the relay table))
void forward_rep_connect_ch(Packet* pk_src){
	char		msg[150] , chaine[20];	
	Packet		*pk_dest;
	int			src , ttl , dest , dest_final , id;
	int			i , test;
	Boolean 	loop_test;
	relay_cell	*ptr;

	//Info from source pk
	op_pk_nfd_get(pk_src , "SRC",			&src);
	op_pk_nfd_get(pk_src , "DEST_FINAL",	&dest_final);	
	op_pk_nfd_get(pk_src , "PK_ID",			&id);
	op_pk_nfd_get(pk_src , "TTL",			&ttl);
	
	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest , "TTL",			--ttl);

	//Destination
	dest = dest_final;
	
	//Searches the next relay (from the relay table)
	loop_test = OPC_FALSE;
	ptr = relay_table;
	while(ptr!=NULL)
		{
			if (ptr->src==dest)
				{
					op_pk_nfd_set(pk_dest , "DEST" , ptr->relay);
					dest = ptr->relay;
					loop_test = OPC_TRUE;
				}			
			ptr = ptr->next;
		}
	
	//If a relay was found, prepares the packet and sends it
	if (loop_test)
		{
			//Add our address in the relay fields
			i=1;
			test = 1;
			while ((test != 0) && (i<9))
				{
					sprintf(chaine,"RELAY%d",i);
					op_pk_nfd_get(pk_dest , chaine , &test);
					i++;
				}
			
			op_pk_nfd_set(pk_dest , chaine , my_address);
			op_pk_nfd_set(pk_dest , "SRC" , my_address);
			
			//Send the packet
			nb_cluster_con_pk ++;
			pk_send_delayed(pk_dest , op_dist_uniform(0.005));
		
			if (DEBUG>MEDIUM)
				{
					sprintf(msg,"%d forwards a clusterhead reply to %d via %d at %f\n",my_address,dest_final,dest,op_sim_time());
					cluster_message(msg);
				}	
		}
	else
		{
			sprintf(msg,"!!!!!!!!! errror !!!!!!!! I didn't find a relay toward %d (id=%d), the packet is discarded (possibly a timeout)\n",dest_final,id);
			cluster_message(msg);
		}
	
}








/*---------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//										ROUTES MANAGEMENT



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/



//gets the i° node of the route
int get_relay(List* route , int pos){
	int*	elem;
	
	elem = op_prg_list_access(route, pos);
	return(*elem);
}

//Returns the empty list (remove all elements)
void route_empty(List* route){
	int	*elem;

	while (op_prg_list_size(route) > 0)
		{
			elem = op_prg_list_remove(route, OPC_LISTPOS_HEAD);
			op_prg_mem_free(elem);
		}
}

//converts a route to a string
void route_to_str_of_stat_id(List * route , char* msg){
	int		i;
	int		*elem;
	
	//initialization
	sprintf(msg, "");
	
	//print the content
	for (i=0 ; i < op_prg_list_size(route) ; i++)
		{	
			elem = op_prg_list_access(route , i);
			sprintf(msg, "%s %d", msg , stats_addresses_to_id[*elem]);
		}
}

//converts a route to a string
void route_to_str(List * route , char* msg){
	int		i;
	int		*elem;
	
	//initialization
	sprintf(msg, "");
	
	//print the content
	for (i=0 ; i < op_prg_list_size(route) ; i++)
		{	
			elem = op_prg_list_access(route , i);
			sprintf(msg, "%s %d", msg , *elem);
		}
}

//Copy one route to another
void copy_route(List* source , List * dest){
	int		i;
	int		*elem;
	
	//empty the dest list
	route_empty(dest);
	
	//copies the source
	for(i=0 ; i<op_prg_list_size(source) ; i++)
		{
			elem = op_prg_list_access(source, i);
			op_prg_list_insert(dest , elem, OPC_LISTPOS_TAIL);
		}
}

//add one route
void add_route(List* route , int node){
	int		*elem;
	
	elem = malloc(sizeof(int));
	*elem = node;
	op_prg_list_insert(route , elem , OPC_LISTPOS_TAIL);
}

//Length of the route
int	route_length(List* route){
	return(op_prg_list_size(route));
}


//computes shortest routes on the graph with the matrix G
void compute_shortest_routes(List* routes[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , int nb_nodes){
	//Control
	int		i , j , s , u , v ;
	//Route length
	int 	length[MAX_NB_NODES][MAX_NB_NODES];	
	//Condition to stop to search new routes in the graph for a particular source
	Boolean	was_one_route_modified_or_added;
	
	//intialization
	for (i=0; i < nb_nodes ; i++)
		for(j=0 ; j < nb_nodes ; j++)
			{
				if (i == j)
					length[i][j] = 0;
				else
					length[i][j] = INFINITY;
				
				route_empty(routes[i][j]);
				if (i == j)
					add_route(routes[i][j] , stats_id_to_addresses[i]);
			}
	
	//For each source
	for (s=0 ; s < nb_nodes ; s++)
		{
			do
				{
					was_one_route_modified_or_added = OPC_FALSE;
					//For each edge in the graph
					for (u=0 ; u < nb_nodes ; u++)
						for (v=0 ; v < nb_nodes ; v++)
							{
								// if the route i->u->v is better than the current i->v route, changes it
								if ((g[u][v] != 0) && (1 + length[s][u] < length[s][v]))
									{
										length[s][v] = length[s][u] + 1;										
										copy_route(routes[s][u] , routes[s][v]);
										add_route(routes[s][v] , stats_id_to_addresses[v]);

										was_one_route_modified_or_added = OPC_TRUE;
									}							
							}		
				}
			while(was_one_route_modified_or_added);
		}
}

//Returns OPC_TRUE if cluster 1 & 2 are radio neighbors 
Boolean are_cluster_neighbors(int cluster1 , int cluster2 , short g[MAX_NB_NODES][MAX_NB_NODES]){
	int		u , v;
		
	for(u=0 ; u < nb_total ; u++)
		for (v=0 ; v<nb_total ; v++)
			{
				if ((g[u][v] >= 1) && (stats_cluster[u] == cluster1) && (stats_cluster[v] == cluster2))
				 	return(OPC_TRUE);
			}
	return(OPC_FALSE);
}

//returns the id of a cluster, dist_max hops at most from dest
int get_cluster_id_neighbor(short g[MAX_NB_NODES][MAX_NB_NODES] , List* shortest_routes_id[MAX_NB_NODES][MAX_NB_NODES] , int dest , short dist_max , int nb_total){
	int		i , j;
	
	for(i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			{
				if ((g[i][j] >= 1) && (stats_cluster[i] != stats_cluster[j]) && (stats_cluster[i] == stats_cluster[dest]))
					if ((op_prg_list_size(shortest_routes_id[dest][i]) <= k_cluster+1) && (stats_state[i] == DOMINATOR))
						return(stats_cluster[j]);
			}
	return(-1);
	
}


//Otimizes the route of clusters -> bypass several cluster if 2 clusters are connected directly
void optimize_cluster_route(List *cluster_routes[MAX_NB_NODES][MAX_NB_NODES] , short cluster_graph[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , short nb_total){
	int		u , v;
	int		a , b;
	int		i;
	Boolean	is_optimized;

	//for each source and destination pair
	for(u=0 ; u < nb_total ; u++)
		for (v=0 ; v<nb_total ; v++)
			{			
				for (a=0 ; a < op_prg_list_size(cluster_routes[u][v]); a++)
					{
						is_optimized = OPC_FALSE;
						for (b=op_prg_list_size(cluster_routes[u][v])-1 ; (b > a+1) && (!is_optimized) ; b--)
							{
						  		//It the next cluster can be directly joined, optimizes the route
						  		if (are_cluster_neighbors(stats_addresses_to_id[get_relay(cluster_routes[u][v] , a)] , stats_addresses_to_id[get_relay(cluster_routes[u][v] , b)] , g ))
									{
										is_optimized = OPC_TRUE;

										//deletes all useless intermediary clusters
										for (i=a+1 ; i < b ; i++)
											op_prg_list_remove(cluster_routes[u][v] , a+1);
									}
							}
					}
			}
}

//adds the node id route from a source_id to a cluster (returns the dest_id)
int add_id_for_intra_route(List* id_route , int source_id, int cl_after , List* shortest_routes_id[MAX_NB_NODES][MAX_NB_NODES] ,  short g[MAX_NB_NODES][MAX_NB_NODES] , int nb_total){
	int		i , j;
	int		*e1 , *e2;
	int		min_length = INFINITY;
	int		dest_id , gw_id;
	
	//init
	dest_id = 0;
	gw_id 	= 0;
	
	//Find the nearest gateway to the corresponding cluster
	for (i=0 ; i < nb_total ; i++)
		{
			//I am directly connected to the after_clusterhead
			if ((stats_cluster[i] == stats_addresses_to_id[cl_after]) && (stats_cluster[i]==i) && (g[i][source_id] >= 1))
				{
					dest_id 	= source_id;
					gw_id 		= i;
					min_length 	= -1;
				}
			
			//I am directly connected to the after_cluster
			if ((stats_cluster[i] == stats_addresses_to_id[cl_after]) && (g[i][source_id] >= 1))
				{
					dest_id 	= source_id;
					gw_id 		= i;
					min_length 	= 0;
				}
				
			//for each node of my cluster (nearest from the current gateway)
			if ((stats_cluster[i] == stats_cluster[source_id]) && (op_prg_list_size(shortest_routes_id[source_id][i]) < min_length))
				{
					//For each of its neighbors
					for (j=0 ; j < nb_total ; j++)
						{
							if ((g[i][j] >= 1) && (stats_cluster[j] == stats_addresses_to_id[cl_after]))
								{
									min_length 	= op_prg_list_size(shortest_routes_id[source_id][i]);
									dest_id 	= i;
									gw_id 		= j;
								}
						}				
				}			
		}
				 
	//copy the corresponding intra route (from the shortest routes)
	if (source_id != dest_id)
		{
			for(i=1 ; i<op_prg_list_size(shortest_routes_id[source_id][dest_id]) ; i++)
				{
					e1 = op_prg_list_access(shortest_routes_id[source_id][dest_id] , i);
					e2 = (int*)malloc(sizeof(int));
					*e2 = *e1;
					op_prg_list_insert(id_route , e2, OPC_LISTPOS_TAIL);
				}
			
			//Adds the next gateway
			if (dest_id != gw_id)
				add_route(id_route , stats_id_to_addresses[gw_id]);
		}
	//Adds the next gateway (if the source is not the gateway, of course !)
	else if (source_id != gw_id)
		add_route(id_route , stats_id_to_addresses[gw_id]);

	//dest reached
	return(gw_id);

}

//adds the node id route from a source_id directly to a dest_id
void add_id_to_dest(List* id_route , int source_id, int dest_id , List* shortest_routes_id[MAX_NB_NODES][MAX_NB_NODES] ){
	int		i ;
	int		*e1 , *e2;

	//copy the corresponding intra route (from the shortest routes)
	for(i=1 ; i<op_prg_list_size(shortest_routes_id[source_id][dest_id]) ; i++)
		{
			e1 = op_prg_list_access(shortest_routes_id[source_id][dest_id] , i);
			e2 = (int*)malloc(sizeof(int));
			*e2 = *e1;
			op_prg_list_insert(id_route , e2, OPC_LISTPOS_TAIL);
		}
}

//Computes the routes of nodes-id according to the cluster_id route 
void compute_intra_cluster_routes(List *total_cluster_routes[MAX_NB_NODES][MAX_NB_NODES] , List *cluster_routes[MAX_NB_NODES][MAX_NB_NODES] , short cluster_graph[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , List* shortest_routes_id[MAX_NB_NODES][MAX_NB_NODES] , int nb_total){
	//routes
	List	*cl_route;
	//Pair source/dest
	int		s , d;
	int		cl;
	int		source;
	//Cluster hops
	int		*cl_after;
	//clusters
	int		cluster_dest;
	
	//initalization
	cl_route 	= op_prg_list_create();
	
	//For each source/dest pair
	for(s=0 ; s<nb_total ; s++)
		for(d=0 ; d<nb_total ; d++)
			if (s != d)
				{
					//the destination is in my neighborhood -> direct routing
					if (op_prg_list_size(shortest_routes_id[s][d]) <= k_cluster+1)
						{
							copy_route(shortest_routes_id[s][d] , total_cluster_routes[s][d]);
						}
					//Else -> cluster routing
					else
						{				
							//the route of cluster to follow
							copy_route (cluster_routes[stats_cluster[s]][stats_cluster[d]] , cl_route);
				
							
							//If the cluster route is not valid, search a cluster neighbor of d which could be valid
							if (op_prg_list_size (cl_route) == 0)
								{
									cluster_dest = get_cluster_id_neighbor(g , shortest_routes_id , d , k_cluster , nb_total);
									if (cluster_dest != -1)
										{
											//printf("%d -> %d : route vers le cluster %d avant d'atteindre le cluster %d de la dest %d\n", stats_id_to_addresses[s] , stats_id_to_addresses[d] , cluster_dest , stats_id_to_addresses[stats_cluster[d]] , stats_id_to_addresses[d]);
											copy_route(total_cluster_routes[stats_cluster[s]][cluster_dest] , cl_route);
											add_route(cl_route , stats_id_to_addresses[stats_cluster[d]]);
										}								
								}
							
							//If the cluster route is valid (else, source & destination are not connected via the backbone)
							if (op_prg_list_size (cl_route) != 0)
								{
									//Adds the source in the route
									add_route(total_cluster_routes[s][d] , stats_id_to_addresses[s]);
												
									//the temporary source (the route is not computed in one shot)	
									source = s;
									for(cl=1 ; cl < op_prg_list_size(cl_route) ; cl++)
										{
											cl_after 	= op_prg_list_access(cl_route , cl);								
											
											source = add_id_for_intra_route(total_cluster_routes[s][d] , source , *cl_after , shortest_routes_id , g , nb_total);
											
										}
									if (source != d)
										{
											//I am in the correct cluster, I must join directly the destination
											add_id_to_dest(total_cluster_routes[s][d] , source, d , shortest_routes_id);
										}
								}
						}
				}				
}



























/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//							GRAPH (CLUSTER_g, CDS_g, exact MCDS computation)



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/


//computes the hypergraph of clusters, with edges from a cluster to another
void compute_cluster_graph(short g[MAX_NB_NODES][MAX_NB_NODES] , short clusters[MAX_NB_NODES] , short cl_g[MAX_NB_NODES][MAX_NB_NODES] , int nb_nodes){
	int		s , n;
	
	//initialization
	for(s=0 ; s<nb_nodes ; s++)
		for(n=0 ; n<nb_nodes ; n++)
			cl_g[s][n] = 0;
	
	//For each node
	for(s=0 ; s<nb_nodes ; s++)
		//For each neighbor of s
		for(n=0 ; n<nb_nodes ; n++)
			{	
				//If the clusters of s and n are different and the edge s-n is a CDS-dominator edge -> adds an edge in the cluster graph
				if ((clusters[s] != clusters[n]) && (g[s][n] == DOMINATOR))
					{
						cl_g[clusters[s]][clusters[n]] = 1;
						cl_g[clusters[n]][clusters[s]] = 1;
					}
			}
}

//Returns the graph of cds links
void compute_cds_graph(short g[MAX_NB_NODES][MAX_NB_NODES] , short cds_graph[MAX_NB_NODES][MAX_NB_NODES]){
	int		i , j;
	
	for(i=0 ; i<nb_total ; i++)
		for(j=0 ; j<nb_total ; j++)
			{
				//DOMINATOR -> DOMINATOR (parent)
				if ((stats_state[i] == DOMINATOR) && (stats_state[j] == DOMINATOR) && (g[i][j] == DOMINATOR_PARENT))
					cds_graph[i][j] = OPC_TRUE;				
				//DOMINATEE -> DOMINATOR (relay or parent)
				else if ((stats_state[i] == DOMINATEE) && (g[i][j] == DOMINATEE_PARENT))
					cds_graph[i][j] = OPC_TRUE;
				//No link
				else
					cds_graph[i][j] = OPC_FALSE;
				
				//symetric matrix
				if (cds_graph[i][j])
					cds_graph[j][i] = OPC_TRUE;
			}
}

//Returns the graph of cds links (dominator-dominator or dominatee-father)
void compute_cds_graph_large(short g[MAX_NB_NODES][MAX_NB_NODES] , short cds_graph[MAX_NB_NODES][MAX_NB_NODES]){
	int		i , j;
	
	for(i=0 ; i<nb_total ; i++)
		for(j=0 ; j<nb_total ; j++)
			{
				//DOMINATOR -> DOMINATOR (whatever radio link)
				if ((stats_state[i] == DOMINATOR) && (stats_state[j] == DOMINATOR) && (g[i][j] >= PHYSIC_NEIGHBOR))
					cds_graph[i][j] = 1;				
				//DOMINATEE -> DOMINATOR (parent)
				else if ((stats_state[i] == DOMINATEE) && (stats_state[j] == DOMINATOR) && (g[i][j] == DOMINATEE_PARENT))
					cds_graph[i][j] = 1;				
				//DOMINATEE -> DOMINATEE (same dominating zone)
				else if ((stats_state[i] == DOMINATEE) && (stats_state[j] == DOMINATEE) && (g[i][j] >= DOMINANCE))
					cds_graph[i][j] = 1;
				else
					cds_graph[i][j] = 0;
				
				//symetric matrix
				if (cds_graph[i][j])
					cds_graph[j][i] = OPC_TRUE;
			}
}

//Returns a text-formatted number with non significative zeros (i.e. 2 becomes 002)
void format_int_to_string(double src, char* dest, int nb_digits){
	int i;

	//We initialize dest 
	sprintf(dest,"");
	
	//We add non significative zeros (nb digits of src : round( log10(src)+1) ) 
	for(i=0 ; i < nb_digits - ((int)log10(src)+1) ;i++)
		sprintf(dest,"%s%d",dest,0);
	
	//We add the original string 
	sprintf(dest , "%s%f" , dest , src);	
}




//returns TRUE if 'set' is a CDS of g
Boolean is_a_cds(short g[MAX_NB_NODES][MAX_NB_NODES], short mcds_set[MAX_NB_NODES]){
	char	msg[200];
	//Covering
	short 	covering[MAX_NB_NODES];
	//CDS
	short 	cds[MAX_NB_NODES][MAX_NB_NODES];
	List*	routes[MAX_NB_NODES][MAX_NB_NODES];
	//Control
	int		i , j;
	Boolean	is_cds_connected;
	int		nb_ap_in_mcds = 0;
	
	
//-------  Verification   -------
	
	//Are the AP members of the MCDS ?
	for (i=0 ; i<nb_total ; i++)
		{
			//if (stats_specificities[i] == AP)
			//	printf("%d est AP\n", stats_id_to_addresses[i]);
			if ((stats_specificities[i] == AP)  &&  (!mcds_set[i]))
				return(OPC_FALSE);
		}
	
	
//-------  Is 'set' a covering ?   -------
	
	//Initialization
	for (i=0 ; i<nb_total ; i++)
		covering[i] = mcds_set[i];
		
		
	//Constructs the covering
	for (i=0 ; i<nb_total ; i++)
		if (mcds_set[i])
			for (j=0 ; j < nb_total ; j++)
				if (g[i][j])
					covering[j] = OPC_TRUE;

	//Is the Covering total ?
	for(i=0 ; i < nb_total ; i++)
	if (!covering[i])
		return(OPC_FALSE);
	

//-------  Is 'set' connected ?   -------
	
	//Copies the graph
	for (i=0 ; i<nb_total ; i++)
		for (j=0 ; j < nb_total ; j++)
			cds[i][j] = g[i][j];
	
	
	//Keeps only intersting information (improves the shortest routes computing speed)
	for(i=0; i<nb_total ; i++)
		if (!mcds_set[i])
			for(j=0; j<nb_total ; j++)
				{
					cds[i][j] = OPC_FALSE;
					cds[j][i] = OPC_FALSE;
				}
	
	//Routes intialization
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			routes[i][j] 	= op_prg_list_create();
	
	//computes the shortest routes
	compute_shortest_routes(routes , cds , nb_total);

	//are all routes present ? (i.e. is the cds connected ?)
	is_cds_connected = OPC_TRUE;
	cluster_message("ROUTES:\n");
	for (i=0 ; (i<nb_total) && (is_cds_connected) ; i++)
		for(j=0 ; (j<nb_total) && (is_cds_connected)  ; j++)
			{			
				route_to_str(routes[i][j] , msg);
				sprintf(msg , "%\n", msg);
				cluster_message(msg);
				if (  (mcds_set[i])   &&   (mcds_set[j])   &&   (op_prg_list_size(routes[i][j])==0)  )
					is_cds_connected = OPC_FALSE;
			}
		
	//Routes Destruction
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			{
				route_empty(routes[i][j]);
				op_prg_mem_free(routes[i][j]);
			}			
	
	if (is_cds_connected)
		{
			cluster_message("SET : ");
			for(i=0; i < nb_total; i++)
				if (mcds_set[i])
					{
						sprintf(msg, "%d ", stats_id_to_addresses[i]);
						cluster_message(msg);
					}
			cluster_message("\n");		
		}
	
	//return the final result
	return(is_cds_connected);
	
	
}




//Computes all possible set 'set' adding nb_doms_to_add to 'set', and returns if 'set' is a MCDS ?
Boolean compute_mcds(short g[MAX_NB_NODES][MAX_NB_NODES] , short mcds_set[MAX_NB_NODES], short start  , short nb_doms_to_add){
//	int		i;

	//The set is chosen
	if (nb_doms_to_add == 0)
		{		
			//Is 'set' a CDS ?
			if (is_a_cds(g , mcds_set))
				return(OPC_TRUE);	
			else
				return(OPC_FALSE);
		}
	//The set is not complete -> computes all possible sets
	else
		{
			/*			for(i=1; i < nb_total; i++)
				{
					printf("%d ", set[i]);					
				}
			printf("\n");
			*/
		

			//We take this node in the set
			mcds_set[start] = OPC_TRUE;
			if (nb_doms_to_add-1 <= (nb_total - (start+1) + 1))
				if (    compute_mcds(g , mcds_set , start+1 , nb_doms_to_add-1)   )
					return(OPC_TRUE);
			
			//We don't take this node in the set (except if the node is an AP)
			mcds_set[start] = OPC_FALSE;
			if (stats_specificities[start] != AP)
				if (  (nb_doms_to_add-1) <= nb_total - (start+1) + 1) 
					if ( compute_mcds(g , mcds_set , start+1 , nb_doms_to_add)   )
						return(OPC_TRUE); 
			
			//No possible set with this 'set'
			return(OPC_FALSE);			
		}
	
}



//Returns the cardinality of the exact MCDS (and a MCDS : MCDS[i]=1 if the ith node is member of the MCDS)
int compute_mcds_graph(short g[MAX_NB_NODES][MAX_NB_NODES], short mcds_set[MAX_NB_NODES]){
	short	i;
	short	card_min;
	
	//Initialization
	card_min = INFINITY;
	for(i=0 ; i<nb_total ; i++)
		mcds_set[i] = OPC_FALSE;
	
	
	//For a cardinality 1 -> nb_total-1   (a MCDS contains at most n-1 nodes, and at least one node)
	for(i=1 ; (i<nb_total) && (card_min==INFINITY) ; i++)
		{
			if (compute_mcds(g, mcds_set, 0 , i))
				card_min = i;
		}
	
	return(card_min);	
}








/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//											STATISTICS



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/


//Returns the color associated with a special cds-state
int get_color_with_state(short state){
	switch(state)
		{
			case DOMINATOR :
					return(1);
				break;
			case DOMINATEE :
					return(6);
				break;
			case ACTIVE :
					return(4);
				break;
			case IDLE :
					return(7);
				break;
			default :
					return(5);
				break;
		}
}


//Instantaneous stats
void periodic_stats_generate(int* arg, int code){
Boolean					is_global_stats_collect_required;
Boolean					is_quick_stats_collect_required;
//Control variables
char					msg[1500];
char					filename[150];
int						i , j;
int						int_value;
double					stats_per_sec;			//Nb of generated stats per second (to have instantaneous values like pkts/sec)
//Temp values for stats
double					tmp_average_degree;
double					tmp_average_nb_fathers;
//Tempv values for cds-connectors
int						tmp_average_nb_cds_connectors;
List*					cds_connectors_list_tmp;
struct_cds_connector	*entry;
//Files
FILE* 					fichier;
neigh_cell*				ptr;
Boolean					is_father_alive;
//Secondary Fathers
int						second_fathers_temp[MAX_NB_NODES];
//CDS
int						nb_cds_connected_nodes_strict;
int						nb_cds_connected_nodes_large;
List*					cds_routes	[MAX_NB_NODES][MAX_NB_NODES];
short					cds_graph	[MAX_NB_NODES][MAX_NB_NODES];
//short					mcds_set	[MAX_NB_NODES];
short					g			[MAX_NB_NODES][MAX_NB_NODES];
Boolean					is_node_connected_to_ap;
//Simulation of a node failure
int						network_id;
int						failed_node_address;
int						*failed_node_address_ptr;
int						failed_node_remote_id;
int						failed_process_remote_id;
int						*failed_node_is_AP_ptr;
cds						*failed_cds;
char					stab_failure_type_str[30];
double					x_pos , y_pos , XMAX , YMAX;
neigh_cell				**failed_neighbour_table;

	//---------------------------------------------
	//  Global infos on Nodes (position, state...)
	//---------------------------------------------
	compute_stats_about_graph_cluster_cds();



	//---------------------------------------------
	//  Global average stats are required ?
	//---------------------------------------------
	is_global_stats_collect_required 	= (op_sim_time() >= TIME_BEGIN_STATS);
	is_quick_stats_collect_required 	= (op_sim_time() <= 90.0) && (stab_failure_type != NONE);
	is_quick_stats_collect_required 	= is_quick_stats_collect_required || (op_sim_time() < TIME_BEGIN_STATS);



	//---------------------------------------------
	//		Time of disconnection (CDS)
	//---------------------------------------------
	//Verify that my father is already alive
	if (my_cds.state==DOMINATEE)
		{
			is_father_alive = 0;
			ptr = neighbour_table;
			while (ptr != NULL)
				{
					//My father already exists
					if ((ptr->address == my_cds.father) && (ptr->state == DOMINATOR) && (ptr->hops <= k_cds) && (ptr->bidirect==1))
						is_father_alive = 1;
					ptr	= ptr->next;
				}
			if (is_sleeping.value)
				is_father_alive = 1;
		}

	if ((my_cds.last_hello_ap_seen > op_sim_time()- INTERVALL_AP_HELLO*TIMEOUT_AP_HELLO) || (is_AP) || ((is_father_alive)&&(my_cds.state == DOMINATEE)) || (is_sleeping.value))
		{
			if (my_cds.time_last_break!=-1)
				tmp_cds_percentage_time_disconnected += (op_sim_time() - my_cds.time_last_break);
			my_cds.time_last_break = -1;
			stats_cds_connection++;
		}
	else
		{
			if (my_cds.time_last_break==-1)
				my_cds.time_last_break = op_sim_time();
			if (my_cds.state == DOMINATEE)
				tmp_seconds_of_disconnection_for_dominatees++;
		}

	
	//---------------------------------------------
	//		Time of disconnection (Cluster)
	//---------------------------------------------
	if (my_cds.state==DOMINATOR)
		{
			if ((my_clusterhead.relay_last_seen > op_sim_time()- 2.1*INTERVALL_HELLO) || (my_clusterhead.address==my_address) || (is_AP) || (cluster_algos_type==NONE))
				{
					if (my_clusterhead.time_last_break != -1)
						tmp_cluster_percentage_time_disconnected += (op_sim_time() - my_clusterhead.time_last_break);
					my_clusterhead.time_last_break = -1;
					stats_clusterhead_connection++;
				}
			else
				{
					if (my_clusterhead.time_last_break==-1)
						my_clusterhead.time_last_break = op_sim_time();
				}
		}
	//When we are dominatee, we estimate that our dominator is responsable of the cluster-maintenant. If we have a dominator, we have a clusterhead!
	if (my_cds.state == DOMINATEE)
		{
			if ((is_father_alive) || (is_sleeping.value))
				{
					stats_clusterhead_connection++;
					if (my_clusterhead.time_last_break!=-1)
						{
							tmp_cluster_percentage_time_disconnected += (op_sim_time() - my_clusterhead.time_last_break);
							my_clusterhead.time_last_break = -1;
						}
				}
			else
				{
					if ((my_clusterhead.time_last_break==-1) && (is_global_stats_collect_required))
						my_clusterhead.time_last_break = op_sim_time();
				}
		}
	if ((my_cds.state == ACTIVE)||(my_cds.state == IDLE))
		{
			if ((my_clusterhead.time_last_break==-1) && (is_global_stats_collect_required))
				my_clusterhead.time_last_break = op_sim_time();
		}	
	
	
	//---------------------------------------------
	//		List of clusterheads/Dominators
	//---------------------------------------------	
	if (my_address == my_clusterhead.address)
			sprintf(stats_list_clusterheads,"%s|%d",stats_list_clusterheads,my_address);
	if (my_cds.state == DOMINATOR)
			sprintf(stats_list_dominators,"%s|%d",stats_list_dominators,my_address);

	
	
	
	//---------------------------------------------
	//				Energy
	//---------------------------------------------
	if ((!is_sleeping.value) && (energy_management>=ENERGY))
		energy_decreases(IDLE_CONSUMPTION);
		
		
	
	//----------------------------------------------------------
	//	Cardinality (Dominators/Clusterheads/Dominatees)
	//---------------------------------------------------------
	if (my_stat_id < MAX_NB_NODES)
		{
			if (my_cds.state==DOMINATOR)
				{
					//The gateways to other APs are chosen if I am not an AP (else I use the wired network) 
					if (!is_AP)
						{
							//Nb of cds_connectors
							cds_connectors_list_tmp = get_my_unique_cds_connectors();
							stats_cds[my_stat_id].nb_cds_connectors = count_nb_dominatees_in_list(cds_connectors_list_tmp);							
							
							//List of cds-connectors
							for(i = op_prg_list_size(cds_connectors_list_tmp)-1 ; i>=0 ; i--)
								{
									entry = op_prg_list_remove(cds_connectors_list_tmp , i);
									if (entry->state == DOMINATEE)
										sprintf(stats_list_cds_connectors , "%s | %d(%d)" , stats_list_cds_connectors , entry->address , entry->id_ap);
									free(entry);
								}
							op_prg_mem_free(cds_connectors_list_tmp);
						}
					else
						stats_cds[my_stat_id].nb_cds_connectors = 0;
					

				}
			else
				stats_cds[my_stat_id].nb_cds_connectors = 0;
		}
	else
		{
			sprintf(msg,"You must increase MAX_NB_NODES (%d), my_address (%d) is too high\n" , MAX_NB_NODES , my_address);
			printf(msg);
			op_sim_end(msg,"","","");
		}
	
	
	
	//---------------------------------------
	//		Actual Density
	//---------------------------------------
	if (my_stat_id < MAX_NB_NODES)
		{
			///  AEIOU
			int_value=0;
			ptr=neighbour_table;
			while(ptr!=NULL)
				{
					if ((ptr->hops==1) && (ptr->bidirect))
						int_value++;
					ptr=ptr->next;
				}
			stats_degree[my_stat_id] = int_value;
   		}
	else
		{
			sprintf(msg,"You must increase MAX_NB_NODES (%d), my_address (%d) is too high\n" , MAX_NB_NODES , my_address);
			printf(msg);
			op_sim_end(msg,"","","");
		}
		
	//---------------------------------------
	//		NB of Fathers (for Dominators)
	//---------------------------------------	
	if((my_cds.state == DOMINATOR) && (!is_AP) && (my_stat_id < MAX_NB_NODES))
		{
			switch (cds_algos_type)
				{
					case THEO_NEW :
					case THEO_NEW2 :
						delete_timeout_cds_candidates(TIMEOUT_AP_HELLO*INTERVALL_AP_HELLO);
						//print_secondary_fathers();
						stats_cds [my_stat_id].nb_parents = delete_double_secondary_fathers(my_cds.secondary_fathers,second_fathers_temp);
					break;
					case THEO_OLD :
					case WU_LI:
						stats_cds[my_stat_id].nb_parents = 0;
					break;
				}
					
		}
	else
		stats_cds[my_stat_id].nb_parents = 0;
	
	
	//---------------------------------------------
	//	   		Stats about Cluster/CDS
	//---------------------------------------------	
	if (my_stat_id == nb_total-1)
		{		
			/*-------------------------------------
						STATS NB
			-------------------------------------*/
		 	if (is_global_stats_collect_required)
				nb_stats_collections++;
			
			/*-------------------------------------
						PRE-TREATMENTS
			-------------------------------------*/
			//Symetrical matrix for the graph matrix transitions
			for(i=0 ; i<MAX_NB_NODES ; i++)
				for (j=0 ; j<MAX_NB_NODES ; j++)
					{
						g[i][j] = stats_links[i][j];
						if (stats_links[i][j] > stats_links[j][i])
							g[j][i] = stats_links[i][j];
					}

			/*-------------------------------------
				CDS-EXACT CONNEXITY (Strict CDS)
			-------------------------------------*/
			//Computes the cds graph
			compute_cds_graph(g , cds_graph);
	
			//Routes intialization
			for (i=0 ; i < nb_total ; i++)
				for(j=0 ; j < nb_total ; j++)
					cds_routes[i][j] 	= op_prg_list_create();
	
			//List of CDS Shortest Routes
			compute_shortest_routes(cds_routes , cds_graph , nb_total);
	
			//For each source/destination pair :
			for(i=0;i<nb_total;i++)
				for(j=0;j<nb_total;j++)
					{
						//only routes to the AP
						if ((op_prg_list_size((cds_routes[i][j]))!=0) && (stats_specificities[i]==NORMAL) && (stats_specificities[j]==AP))
							nb_cds_connected_nodes_strict++;
					}
			
			//average value during the whole simulation
			tmp_cds_connexity_strict += (double)nb_cds_connected_nodes_strict / (nb_total - nb_aps - nb_dead_nodes);			

			//Routes Destruction
			for (i=0 ; i < nb_total ; i++)
				for(j=0 ; j < nb_total ; j++)
					{
						route_empty(cds_routes[i][j]);
						op_prg_mem_free(cds_routes[i][j]);
					}	
						
			/*-------------------------------------
				CDS-EXACT CONNEXITY (Large CDS)
			-------------------------------------*/
		
			//Computes the cds graph
			compute_cds_graph_large(g , cds_graph);

			//Routes intialization
			for (i=0 ; i < nb_total ; i++)
				for(j=0 ; j < nb_total ; j++)
					cds_routes[i][j] 	= op_prg_list_create();
	
			//List of CDS Shortest Routes
			compute_shortest_routes(cds_routes , cds_graph , nb_total);
				
			//For each source/destination pair :
			nb_cds_connected_nodes_large = 0;
			for(i=0;i<nb_total;i++)
				{
					is_node_connected_to_ap = OPC_FALSE;
					for(j=0;j<nb_total;j++)
						{
							//only routes to the AP (I can have several routes (one per AP) when dominators from different backbone are neighbors)
							if ((op_prg_list_size((cds_routes[i][j]))!=0) && (stats_specificities[i]==NORMAL) && (stats_specificities[j]==AP))
								is_node_connected_to_ap = OPC_TRUE;
						}
					if (is_node_connected_to_ap)
						nb_cds_connected_nodes_large++;
				}
			
			//average value during the whole simulation
			tmp_cds_connexity_large += (double)nb_cds_connected_nodes_large / (nb_total - nb_aps - nb_dead_nodes);			
			
			//Routes Destruction
			for (i=0 ; i < nb_total ; i++)
				for(j=0 ; j < nb_total ; j++)
					{
						route_empty(cds_routes[i][j]);
						op_prg_mem_free(cds_routes[i][j]);
					}

			/*-------------------------------------
					CDS-CLUSTERS PERFS
			-------------------------------------*/
			//Computes stats
			nb_idles	 					= 0;
			nb_actives	 					= 0;
			nb_dominatees	 				= 0;
			nb_dominators	 				= 0;
			nb_clusterheads					= 0;
			tmp_average_degree 				= 0;
			tmp_average_nb_fathers			= 0;
			tmp_average_nb_cds_connectors	= 0;
			
			
			//0th -> (nb_total-1)th (=nb_total nodes)
			for(i=0 ; i < nb_total ; i++) 
				{	
					nb_idles	 					+= (stats_state[i] == IDLE);
					nb_actives	 					+= (stats_state[i] == ACTIVE);
					nb_dominators 					+= (stats_state[i] == DOMINATOR);
					nb_dominatees 					+= (stats_state[i] == DOMINATEE);
					nb_clusterheads 				+= (stats_cluster[i] == i);
					tmp_average_nb_cds_connectors	+= stats_cds[i].nb_cds_connectors;
					tmp_average_degree 				+= stats_degree[i];
					tmp_average_nb_fathers 			+= stats_cds[i].nb_parents;			
				}
			
			//Global Variables
			nb_actual_dominators = nb_dominators;
			
			//Writes stats in a temporary variable
			sprintf(msg,"%.2lf" , op_sim_time());
				
		//CDS
			sprintf(msg,"%s		%d", 		msg , 	nb_dominators);						
			//if (nb_dominators > 0)
			//	sprintf(msg,"%s		%d", 	msg , 	compute_mcds_graph(g, mcds_set));
			//else
			//	sprintf(msg,"%s		%d", 	msg , 	0);
			sprintf(msg,"%s		%.1lf", 	msg , 	100 * tmp_cds_connexity_strict);
			sprintf(msg,"%s		%.1lf", 	msg , 	100 * tmp_cds_connexity_large);
		
			
			
		//Clusters
			//Nb clusterheads
			sprintf(msg,"%s		%d",		msg , 	nb_clusterheads);					
			sprintf(msg,"%s		%.1lf", 	msg , 	100*stats_clusterhead_connection/(float)(nb_total-nb_dead_nodes) );
					
		//General	
			sprintf(msg,"%s			%.2lf", msg , 	tmp_average_degree 		/ (float)(nb_total-nb_dead_nodes));
			sprintf(msg,"%s		%.2lf", 	msg , 	tmp_average_nb_fathers  / (float)(nb_dominators-nb_aps));
			sprintf(msg,"%s			%d",	msg ,	tmp_average_nb_cds_connectors);
			sprintf(msg,"%s			%s",	msg ,	stats_list_clusterheads);
			sprintf(msg,"%s			%s",	msg ,	stats_list_dominators);
			sprintf(msg,"%s			%s\n",	msg,	stats_list_cds_connectors);
			
			//Purge the lists
			sprintf(stats_list_clusterheads		,"");
			sprintf(stats_list_dominators		,"");
			sprintf(stats_list_cds_connectors	,"");
			stats_clusterhead_connection	= 0;
			stats_cds_connection			= 0;
			
			//Writes stats (if some are relevant)
			if ((DEBUG_INSTANTANEOUS) && (nb_idles != nb_total))
				{
					sprintf(filename,"results/%sperfs_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier,msg);
					fclose(fichier);
				}
			
			/*---------------------------------------------
						STATS ABOUT STABILIZATION
			---------------------------------------------*/
			
			sprintf(msg,"%.2lf"  , op_sim_time());
			sprintf(msg,"%s		%d", 	msg , 	nb_idles);						
			sprintf(msg,"%s	%d", 		msg , 	nb_actives);						
			sprintf(msg,"%s	%d", 		msg , 	nb_dominators);						
			sprintf(msg,"%s	%d", 		msg , 	nb_dominatees);						
			sprintf(msg,"%s	%.1lf",		msg , 	100 * tmp_cds_connexity_strict);
			sprintf(msg,"%s		%.1lf",	msg , 	100 * tmp_cds_connexity_large);
			sprintf(msg,"%s		%d",	msg,	stats_idle_active_changes);
			sprintf(msg,"%s	%d",		msg,	stats_idle_dominator_changes);
			sprintf(msg,"%s	%d",		msg,	stats_idle_dominatee_changes);
			sprintf(msg,"%s	%d",		msg,	stats_dominatee_idle_changes);
			sprintf(msg,"%s	%d",		msg,	stats_dominator_idle_changes);
			sprintf(msg,"%s	%d",		msg,	stats_active_dominator_changes);
			sprintf(msg,"%s	%d",		msg,	stats_active_dominatee_changes);
			sprintf(msg,"%s	%d",		msg,	stats_dominatee_active_changes);
			sprintf(msg,"%s	%d",		msg,	stats_dominatee_dominator_changes);
			sprintf(msg,"%s	%d",		msg,	stats_dominator_dominatee_changes);			
			sprintf(msg,"%s\n",			msg);			
			
			//Writes stats
			if ((DEBUG_CONVERGENCE) && (nb_idles != nb_total))
				{
					sprintf(filename,"results/%sstabilization_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier,msg);
					fclose(fichier);
				}
			
			/*---------------------------------------------
					STATS ABOUT TIME OF STABILIZATION
			---------------------------------------------*/
			if ((nb_idles == 0) && (!stab_is_idle_end_written))
				{
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "---------------------------------------------------------------\n");
					fprintf(fichier , "---------------------------   GENERAL   -----------------------\n");
					fprintf(fichier , "---------------------------------------------------------------\n\n");

					fprintf(fichier , "\n-----------------------  Prameters ------------------------\n");
					fprintf(fichier , "Number of nodes					:	%d\n", nb_total);
					fprintf(fichier , "\n\n");
					
					
					fprintf(fichier , "\n\n---------------------------------------------------------------\n");
					fprintf(fichier , "--------------------   INITIAL  CONVERGENCE   -----------------\n");
					fprintf(fichier , "---------------------------------------------------------------\n\n");
					
					
					fprintf(fichier , "\n-----------------------  IDLE CONVERGENCE TIME ------------------------\n");
					fprintf(fichier , "Time before no idle node			:	%f\n", op_sim_time() - TIME_NETWORK_INIT - TIME_INIT_MAC);
					fprintf(fichier , "\n\n");
					fclose(fichier);
					stab_is_idle_end_written = OPC_TRUE;
				}
			if ((stab_is_idle_end_written) && (nb_actives == 0) && (!stab_is_active_end_written))
				{
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "\n-------------------------   ACTIVE CONVERGENCE  ----------------------------------\n");
					fprintf(fichier , "Time before no active node			:	%f\n", op_sim_time() - TIME_NETWORK_INIT - TIME_INIT_MAC);
					fprintf(fichier , "IDLE -> ACTIVE					:	%d\n", 		stats_idle_active_changes);
					fprintf(fichier , "IDLE -> DOMINATOR					:	%d\n", 	stats_idle_dominator_changes);
					fprintf(fichier , "IDLE -> DOMINATEE					:	%d\n", 	stats_idle_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> IDLE					:	%d\n", 	stats_dominatee_idle_changes);
					fprintf(fichier , "DOMINATOR -> IDLE					:	%d\n", 	stats_dominator_idle_changes);
					fprintf(fichier , "ACTIVE -> DOMINATOR				:	%d\n", 		stats_active_dominator_changes);
					fprintf(fichier , "ACTIVE -> DOMINATEE				:	%d\n", 		stats_active_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> ACTIVE				:	%d\n",		stats_dominatee_active_changes);
					fprintf(fichier , "DOMINATEE -> DOMINATOR				:	%d\n", 	stats_dominatee_dominator_changes);
					fprintf(fichier , "DOMINATOR -> DOMINATEE				:	%d\n", 	stats_dominator_dominatee_changes);
					fprintf(fichier , "\n\n");
					fclose(fichier);				
					stab_is_active_end_written = OPC_TRUE;
				}
			if ((100 * tmp_cds_connexity_large == 100) && (!stab_is_large_connexity_cds_end_written))
				{
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "\n-------------------------   CDS LARGE CONVERGENCE  ----------------------------------\n");
					fprintf(fichier , "Time before a large-connected CDS		:	%f\n", op_sim_time() - TIME_NETWORK_INIT - TIME_INIT_MAC);
					fprintf(fichier , "IDLE -> ACTIVE					:	%d\n", 		stats_idle_active_changes);
					fprintf(fichier , "IDLE -> DOMINATOR					:	%d\n", 	stats_idle_dominator_changes);
					fprintf(fichier , "IDLE -> DOMINATEE					:	%d\n", 	stats_idle_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> IDLE					:	%d\n", 	stats_dominatee_idle_changes);
					fprintf(fichier , "DOMINATOR -> IDLE					:	%d\n", 	stats_dominator_idle_changes);
					fprintf(fichier , "ACTIVE -> DOMINATOR				:	%d\n", 		stats_active_dominator_changes);
					fprintf(fichier , "ACTIVE -> DOMINATEE				:	%d\n", 		stats_active_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> ACTIVE				:	%d\n", 		stats_dominatee_active_changes);
					fprintf(fichier , "DOMINATEE -> DOMINATOR				:	%d\n", 	stats_dominatee_dominator_changes);
					fprintf(fichier , "DOMINATOR -> DOMINATEE				:	%d\n", 	stats_dominator_dominatee_changes);
					fprintf(fichier , "\n\n");
					fclose(fichier);
					stab_is_large_connexity_cds_end_written = OPC_TRUE;
				}
			if ((100 * tmp_cds_connexity_strict == 100) && (!stab_is_strict_connexity_cds_end_written))
				{
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "\n-------------------------   CDS STRICT CONVERGENCE  ----------------------------------\n");
					fprintf(fichier , "Time before a strict-connected CDS		:	%f\n", op_sim_time() - TIME_NETWORK_INIT - TIME_INIT_MAC);
					fprintf(fichier , "IDLE -> ACTIVE					:	%d\n",		stats_idle_active_changes);
					fprintf(fichier , "IDLE -> DOMINATOR					:	%d\n", 	stats_idle_dominator_changes);
					fprintf(fichier , "IDLE -> DOMINATEE					:	%d\n", 	stats_idle_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> IDLE					:	%d\n", 	stats_dominatee_idle_changes);
					fprintf(fichier , "DOMINATOR -> IDLE					:	%d\n", 	stats_dominator_idle_changes);
					fprintf(fichier , "ACTIVE -> DOMINATOR				:	%d\n", 		stats_active_dominator_changes);
					fprintf(fichier , "ACTIVE -> DOMINATEE				:	%d\n", 		stats_active_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> ACTIVE				:	%d\n", 		stats_dominatee_active_changes);
					fprintf(fichier , "DOMINATEE -> DOMINATOR				:	%d\n", 	stats_dominatee_dominator_changes);
					fprintf(fichier , "DOMINATOR -> DOMINATEE				:	%d\n", 	stats_dominator_dominatee_changes);
					fprintf(fichier , "\n\n");
					fclose(fichier);
					stab_is_strict_connexity_cds_end_written = OPC_TRUE;
				
					//Is this stat useless ?
					if (!DEBUG_CONVERGENCE)
						remove(filename);
				}
			
			
		
			/*---------------------------------------------
    			SOME AVERAGE STATS FOR GLOBAL SIMULATION
			---------------------------------------------*/
			if (is_global_stats_collect_required)
				{
					//CDS STATES
					average_nb_dominators 		+= nb_dominators;
					average_nb_dominatees 		+= nb_dominatees;
					
					average_cds_percentage_time_disconnected 	+= tmp_cds_percentage_time_disconnected;
					average_cds_connexity_strict				+= tmp_cds_connexity_strict;
					average_cds_connexity_large					+= tmp_cds_connexity_large;
					
					average_nb_cds_connectors	+=	tmp_average_nb_cds_connectors;
					
					
					//CLUSTER
					average_nb_clusterheads 	+= nb_clusterheads;
					average_cluster_percentage_time_disconnected += tmp_cluster_percentage_time_disconnected;
					
					//ENVIRONMENT
					average_nb_ap_neigh			+= nb_ap_neigh;
					average_degree				+= tmp_average_degree;
					
					//Computes number of secondary fathers
					if (nb_dominators - nb_aps != 0)
						average_nb_secondary_fathers += (float)tmp_average_nb_fathers / (nb_dominators-nb_aps);
					
					
				}
		
	

			/*-------------------------------------
					NETWORK CONTROL STATS
			-------------------------------------*/		
			
			//We compute network flows every INTERVALL_STATS --> coeff to have pk/s
			if (op_sim_time() < TIME_BEGIN_STATS)
				stats_per_sec = 1 / INTERVALL_QUICK_STATS_COLLECTING;
			else
				stats_per_sec = 1 / INTERVALL_STATS_COLLECTING;
			
			//Writes network control stats
			sprintf(msg,"%.2lf" , op_sim_time());
			sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_hello_instantaneous/nb_total);
			sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * (nb_pk_cds_instantaneous+nb_pk_ap_hello_instantaneous)/nb_total);
			sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_cluster_instantaneous/nb_total);
			sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_data_instantaneous/nb_total);
			sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * (nb_pk_bb_multicast_instantaneous + nb_pk_ret_bb_multicast_instantaneous)/nb_total);
			sprintf(msg,"%s		%.2lf	|"	, msg , (float) stats_per_sec * nb_pk_other_instantaneous/nb_total);
			if (nb_dominators!=0)
				{
					sprintf(msg,"%s	%.2lf"			, msg , (float) stats_per_sec * nb_pk_hello_dominator_instantaneous/nb_dominators);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * (nb_pk_cds_dominator_instantaneous+nb_pk_ap_hello_dominator_instantaneous)/nb_dominators);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_cluster_dominator_instantaneous/nb_dominators);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_data_dominator_instantaneous/nb_dominators);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * (nb_pk_bb_multicast_dominator_instantaneous + nb_pk_ret_bb_multicast_dominator_instantaneous)/nb_dominators);
					sprintf(msg,"%s		%.2lf	|"	, msg , (float) stats_per_sec * nb_pk_other_dominator_instantaneous/nb_dominators);
				}	
			else
				{
					sprintf(msg,"%s 	0		0		0		0		0		0	|",msg);
				}
			if (nb_dominatees!=0)
				{
					sprintf(msg,"%s	%.2lf"			, msg , (float) stats_per_sec * nb_pk_hello_dominatee_instantaneous/nb_dominatees);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * (nb_pk_cds_dominatee_instantaneous+nb_pk_ap_hello_dominatee_instantaneous)/nb_dominatees);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_cluster_dominatee_instantaneous/nb_dominatees);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_data_dominatee_instantaneous/nb_dominatees);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * (nb_pk_bb_multicast_dominatee_instantaneous + nb_pk_bb_multicast_dominatee_instantaneous)/nb_dominatees);
					sprintf(msg,"%s		%.2lf"		, msg , (float) stats_per_sec * nb_pk_other_dominatee_instantaneous/nb_dominatees);
				}
			else
				{
					sprintf(msg,"%s 	0		0		0		0		0		0	|",msg);
				}
			sprintf(msg,"%s \n",msg);				

			
			//------------------------------------
			//	 TEMPORARY FAILURE SIMULATION
			//------------------------------------
			
		//A temporary failure was simulated, is the cds reconnected ?
			if ((100 * tmp_cds_connexity_large == 100) && (!stab_is_large_tempo_failure_written) && (stab_failure_time != 0) && (stab_failure_time < op_sim_time()))
				{
				printf("fin large\n");
				
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "\n-------------------------   CDS LARGE RECONNECTION  ----------------------------------\n");
					fprintf(fichier , "TIME_CDS_LARGE_RECONNECTION			:	%f\n", 	op_sim_time() - stab_failure_time);
					fprintf(fichier , "IDLE -> ACTIVE					:	%d\n", 		stats_idle_active_changes - stab_idle_active_changes);
					fprintf(fichier , "IDLE -> DOMINATOR					:	%d\n", 	stats_idle_dominator_changes - stab_idle_dominator_changes);
					fprintf(fichier , "IDLE -> DOMINATEE					:	%d\n", 	stats_idle_dominatee_changes - stab_idle_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> IDLE					:	%d\n", 	stats_dominatee_idle_changes - stab_dominatee_idle_changes);
					fprintf(fichier , "DOMINATOR -> IDLE					:	%d\n", 	stats_dominator_idle_changes - stab_dominator_idle_changes);
					fprintf(fichier , "ACTIVE -> DOMINATOR				:	%d\n", 		stats_active_dominator_changes - stab_active_dominator_changes);
					fprintf(fichier , "ACTIVE -> DOMINATEE				:	%d\n", 		stats_active_dominatee_changes - stab_active_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> ACTIVE				:	%d\n", 		stats_dominatee_active_changes - stab_dominatee_active_changes);
					fprintf(fichier , "DOMINATEE -> DOMINATOR				:	%d\n", 	stats_dominatee_dominator_changes - stab_dominatee_dominator_changes);
					fprintf(fichier , "DOMINATOR -> DOMINATEE				:	%d\n", 	stats_dominator_dominatee_changes - stab_dominator_dominatee_changes);
					fprintf(fichier , "\n\n");
					fclose(fichier);
					stab_is_large_tempo_failure_written = OPC_TRUE;
				}			

			if ((100 * tmp_cds_connexity_strict == 100) && (!stab_is_strict_tempo_failure_written) && (stab_failure_time != 0) && (stab_failure_time < op_sim_time()))
				{
				printf("fin stricte\n");
				
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "\n-------------------------   CDS STRICT RECONNECTION  ----------------------------------\n");
					fprintf(fichier , "TIME_CDS_STRICT_RECONNECTION			:	%f\n", 	op_sim_time() - stab_failure_time);
					fprintf(fichier , "IDLE -> ACTIVE					:	%d\n", 		stats_idle_active_changes - stab_idle_active_changes);
					fprintf(fichier , "IDLE -> DOMINATOR					:	%d\n", 	stats_idle_dominator_changes - stab_idle_dominator_changes);
					fprintf(fichier , "IDLE -> DOMINATEE					:	%d\n", 	stats_idle_dominatee_changes - stab_idle_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> IDLE					:	%d\n", 	stats_dominatee_idle_changes - stab_dominatee_idle_changes);
					fprintf(fichier , "DOMINATOR -> IDLE					:	%d\n", 	stats_dominator_idle_changes - stab_dominator_idle_changes);
					fprintf(fichier , "ACTIVE -> DOMINATOR				:	%d\n", 		stats_active_dominator_changes - stab_active_dominator_changes);
					fprintf(fichier , "ACTIVE -> DOMINATEE				:	%d\n", 		stats_active_dominatee_changes - stab_active_dominatee_changes);
					fprintf(fichier , "DOMINATEE -> ACTIVE				:	%d\n", 		stats_dominatee_active_changes - stab_dominatee_active_changes);
					fprintf(fichier , "DOMINATEE -> DOMINATOR				:	%d\n", 	stats_dominatee_dominator_changes - stab_dominatee_dominator_changes);
					fprintf(fichier , "DOMINATOR -> DOMINATEE				:	%d\n", 	stats_dominator_dominatee_changes - stab_dominator_dominatee_changes);
					fprintf(fichier , "\n\n");
					fclose(fichier);
					stab_is_strict_tempo_failure_written = OPC_TRUE;
				
					//Is this stat useless ?
					if (!DEBUG_CONVERGENCE)
						remove(filename);
				}			

		 //Simulates a temporary failure
			if ((op_sim_time() >= 60.0) && (100 * tmp_cds_connexity_strict == 100) && (stab_failure_time == 0) && (stab_failure_type != NONE))
				{
				printf("failure!!!\n");
				
				
					//chooses a random node for the failure
					network_id 					= op_id_parent 			(op_id_parent( op_id_self() ) );
					failed_node_address			= op_dist_uniform		(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB));
					failed_node_remote_id		= op_id_from_sysid		(OPC_OBJTYPE_NDMOB , failed_node_address);
					failed_process_remote_id	= op_id_from_name 		(failed_node_remote_id , OPC_OBJMTYPE_QPS , "cds-cluster");
					failed_cds 					= op_ima_obj_svar_get	(failed_process_remote_id, "my_cds");
					failed_neighbour_table		= op_ima_obj_svar_get	(failed_process_remote_id, "neighbour_table");
					failed_node_address_ptr		= op_ima_obj_svar_get	(failed_process_remote_id, "my_address");	
					failed_node_is_AP_ptr		= op_ima_obj_svar_get	(failed_process_remote_id, "is_AP");	
							
					//This is not the searched type, choose another node
					//-FAILURE_ANY -> type of the node for the position_failure
				   	while ((*failed_node_is_AP_ptr) ||  ((failed_cds->state != stab_failure_type) && (failed_cds->state != stab_failure_type - STATE_ANY) && (stab_failure_type != TOPO_ANY) && (stab_failure_type != STATE_ANY)))
						{
							failed_node_address			= op_dist_uniform		(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB));
							failed_node_remote_id		= op_id_from_sysid		(OPC_OBJTYPE_NDMOB , failed_node_address );
							failed_process_remote_id	= op_id_from_name 		(failed_node_remote_id , OPC_OBJMTYPE_QPS , "cds-cluster");
							failed_cds 					= op_ima_obj_svar_get	(failed_process_remote_id, "my_cds");
							failed_neighbour_table		= op_ima_obj_svar_get	(failed_process_remote_id, "neighbour_table");
							failed_node_address_ptr		= op_ima_obj_svar_get	(failed_process_remote_id, "my_address");	
							failed_node_is_AP_ptr		= op_ima_obj_svar_get	(failed_process_remote_id, "is_AP");	
						}
					
					switch (stab_failure_type)
						{
							// FAILURE_TYPE : A NODE CHANGES ITS CDS-STATE
							case STATE_DOMINATOR :
							case STATE_DOMINATEE :
							case STATE_ANY :
				
						printf("state\n");
								//Changes its state
								if (failed_cds->state == DOMINATOR)
									failed_cds->state = DOMINATEE;
								else if (failed_cds->state == DOMINATEE)
									failed_cds->state = DOMINATOR;						
							break;
								
								
							// FAILURE_TYPE : A NODE CHANGES ITS GEOGRAPHIC POSITION
							case TOPO_DOMINATOR :
							case TOPO_DOMINATEE :
							case TOPO_ANY :
							
								empty_neighbour_table(failed_neighbour_table , *failed_node_address_ptr);
								clear_in_all_neighbour_table(*failed_node_address_ptr);
								//(*failed_neighbour_table) = NULL;
							
							
								//Parameters
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"X_MAX"      		, &XMAX);
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"Y_MAX"      		, &YMAX);

								//New random position
								x_pos = op_dist_uniform (XMAX);
								y_pos = op_dist_uniform (YMAX);

								// Set the current position of the node
								op_ima_obj_attr_set(failed_node_remote_id , "x position" , x_pos);
								op_ima_obj_attr_set(failed_node_remote_id , "y position" , y_pos);

							break;
							default :
								op_sim_end("Error, the failure type is unknown","the parameters constants are inconsistent","","");
							break;
						}
					
					
					
					
					//Time of the temporary failure
					stab_failure_time = op_sim_time();
					
					//Nb of changes already done since initialization
					stab_idle_active_changes			= stats_idle_active_changes;
					stab_idle_dominator_changes			= stats_idle_dominator_changes;
					stab_idle_dominatee_changes			= stats_idle_dominatee_changes;
					stab_dominatee_idle_changes			= stats_dominatee_idle_changes;
					stab_dominator_idle_changes			= stats_dominator_idle_changes;
					stab_active_dominator_changes		= stats_active_dominator_changes;
					stab_active_dominatee_changes		= stats_active_dominatee_changes;
					stab_dominatee_active_changes		= stats_dominatee_active_changes;
					stab_dominatee_dominator_changes	= stats_dominatee_dominator_changes;
					stab_dominator_dominatee_changes	= stats_dominator_dominatee_changes;
		
				
					//Type of the failed node
					switch(stab_failure_type){
						case STATE_DOMINATOR:
							strcpy(stab_failure_type_str, "STATE-DOMINATOR");
						break;
						case STATE_DOMINATEE:
							strcpy(stab_failure_type_str, "STATE-DOMINATEE");
						break;
						case STATE_ANY:
							strcpy(stab_failure_type_str, "STATE-ANY");
						break;
						case TOPO_DOMINATOR:
							strcpy(stab_failure_type_str, "TOPOLOGY-DOMINATOR");
						break;
						case TOPO_DOMINATEE:
							strcpy(stab_failure_type_str, "TOPOLOGY-DOMINATEE");
						break;
						case TOPO_ANY:
							strcpy(stab_failure_type_str, "TOPOLOGY-ANY");
						break;
						default:
							strcpy(stab_failure_type_str, "ERROR");
						break;
						}					
					
					sprintf(filename,"results/%sstabilization_time_stats%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier , "\n\n---------------------------------------------------------------\n");
					fprintf(fichier , "----------------------   TEMPORARY FAILURE   ------------------\n");
					fprintf(fichier , "---------------------------------------------------------------\n\n");
					
					
					fprintf(fichier , "\n-------------------------   PARAMETERS  ----------------------------------\n");					
					fprintf(fichier , "Type of the node 					:	%s\n" , 		stab_failure_type_str);
					fprintf(fichier , "Failed node (time of failure)			:	%d (%f)\n", *failed_node_address_ptr , op_sim_time());
					fprintf(fichier , "Distance to parent				:	%d\n", 				failed_cds->father_hops );
					fprintf(fichier , "Distance to the AP				:	%d\n", 				failed_cds->ap_hops );
					fprintf(fichier , "Dominator with at least one son		:	%d\n", 			(failed_cds->sons) != NULL );
					fprintf(fichier , "\n\n");
				}
				
			//------------------------------------
			//	 REINIT TEMPORARY VARIABLES
			//------------------------------------
			
			//PACKETS
			nb_pk_hello_instantaneous 					= 0;
			nb_pk_cds_instantaneous 					= 0;
			nb_pk_ap_hello_instantaneous 				= 0;
			nb_pk_cluster_instantaneous 				= 0;
			nb_pk_other_instantaneous					= 0;
			nb_pk_data_instantaneous					= 0;
			nb_pk_bb_multicast_instantaneous			= 0;
			
			nb_pk_hello_dominator_instantaneous 		= 0;
			nb_pk_cds_dominator_instantaneous 			= 0;
			nb_pk_ap_hello_dominator_instantaneous 		= 0;
			nb_pk_cluster_dominator_instantaneous 		= 0;
			nb_pk_other_dominator_instantaneous			= 0;
			nb_pk_data_dominator_instantaneous			= 0;
			nb_pk_bb_multicast_dominator_instantaneous	= 0;
			
			nb_pk_hello_dominatee_instantaneous 		= 0;
			nb_pk_cds_dominatee_instantaneous 			= 0;
			nb_pk_ap_hello_dominatee_instantaneous 		= 0;
			nb_pk_cluster_dominatee_instantaneous 		= 0;
			nb_pk_other_dominatee_instantaneous			= 0;
			nb_pk_data_dominatee_instantaneous			= 0;
			nb_pk_bb_multicast_dominatee_instantaneous	= 0;

			
			//CDS CONNEXITY
			nb_cds_connected_nodes_strict 				= 0;
			nb_cds_connected_nodes_large				= 0;
			
			//CDS
			tmp_cds_percentage_time_disconnected		= 0;
			tmp_cds_connexity_strict					= 0;
			tmp_cds_connexity_large						= 0;
			tmp_seconds_of_disconnection_for_dominatees	= 0;
			
			//CLUSTER
			tmp_cluster_percentage_time_disconnected	 = 0;
			
			
			//Writes it
			if(DEBUG_NETWORK_CTRL)
				{
					sprintf(filename,"results/%snetwork_control%s.txt", prefix_results_file , suffix_results_file);
					fichier = fopen(filename,"a");
					fprintf(fichier,msg);
					fclose(fichier);
				}

		}


	if (is_quick_stats_collect_required)
		op_intrpt_schedule_call(op_sim_time() + INTERVALL_QUICK_STATS_COLLECTING 	, STATS_CODE , periodic_stats_generate , -1);
	else
		op_intrpt_schedule_call(op_sim_time() + INTERVALL_STATS_COLLECTING 			, STATS_CODE , periodic_stats_generate , -1);
}


//Initializes all stat variables in order to store infos and generate figure of the current network
void stats_network_figure_initalization(){
	int		i;

	for(i=0;i<nb_total;i++)
		stats_id_to_addresses[i] = -1;
	for(i=0;i<MAX_ADDRESS;i++)
		stats_addresses_to_id[i] = -1;
}


//Writes all files necessary for cplex
int write_cplex_files(){
	//Control
	int			i , j;	
	char		msg[1000];
	int			nb_cds_connected=0;
	//Intermediary variables
	List*		routes				[MAX_NB_NODES][MAX_NB_NODES];
	List*		cds_routes			[MAX_NB_NODES][MAX_NB_NODES];
	List*		cluster_routes		[MAX_NB_NODES][MAX_NB_NODES];
	List*		total_cluster_routes[MAX_NB_NODES][MAX_NB_NODES];
	short		cluster_graph		[MAX_NB_NODES][MAX_NB_NODES];
	short		cds_graph			[MAX_NB_NODES][MAX_NB_NODES];
	short		g					[MAX_NB_NODES][MAX_NB_NODES];
	double		length_average		=0;
	Boolean		is_empty;
	//Files
	char		filename[150];
	FILE		*cplex_file;
	FILE		*cplex_file_2;

//--------------------------------------------------
//		Pre-Treatments on the matrix transition
//--------------------------------------------------

	//Copy the topology in a temporary graph matrix
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			g[i][j] = stats_links[i][j];
	
	//Symetrical matrix
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			if (g[i][j] > g[j][i])
				g[j][i] = g[i][j];
	
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			if (g[i][j] < g[j][i])
				g[i][j] = g[j][i];


//--------------------------------------------------
//	CPLEX Format  (overheads in bits per second)
//--------------------------------------------------

	//Opens the associated file
	format_int_to_string( op_sim_time() , msg , 4);
	sprintf(filename,"results/%scplex_graph_radio_bps_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		printf("Error : we cannot create the file %s\n",filename);
	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_total);						
	
	//--------------------
	//Radio Graph Matrix
	//--------------------
	for(i=0 ; i<nb_total ; i++)
		{		
			//If Wu&Li -> adds the overhead for "virtual" topology packets (size of an tc_pk = header(32 bits) + addresses for neighbors
			if (cds_algos_type == WU_LI)
				fprintf(cplex_file , "%f ", stats_overheads_bits[i] +  (stats_degree[i] * 32 + 32)* ((nb_total-1) * 1/TC_INTERVAL * (stats_cluster[i] == i) + 1/TC_INTERVAL));
			else
			//Else, I simulate the higher level -> I take its effective overhead
				fprintf(cplex_file , "%f ", stats_overheads_bits[i]);
				
			for(j=0;j<nb_total;j++)
				{
					switch (g[i][j]){
						case NULL :
							fprintf(cplex_file,"%d ",  0);
						break;
						case PHYSIC_NEIGHBOR :
						case DOMINANCE :
							fprintf(cplex_file,"%d ",  1);
						break;
						case DOMINATOR_PARENT :
						case DOMINATEE_PARENT :
							fprintf(cplex_file,"%d ",  2);
						break;
						default:
							sprintf(msg, "type=%d" , g[i][j]);
							op_sim_end("this type of link is unknown", msg,"","");
						break;
						}
				}
			fprintf(cplex_file,"\n");							
		}			
	fclose(cplex_file);
	
//--------------------------------------------------
//	CPLEX Format  (overheads in packets per second)
//--------------------------------------------------

	//Opens the associated file 
	format_int_to_string( op_sim_time() , msg , 4);
	sprintf(filename,"results/%scplex_graph_radio_pps_%s%S.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		printf("Error : we cannot create the file %s\n",filename);
	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_total);						
	
	//--------------------
	//Radio Graph Matrix
	//--------------------
	for(i=0 ; i<nb_total ; i++)
		{
			//If Wu&Li -> adds the overhead for "virtual" topology packets
			if (cds_algos_type == WU_LI)
				fprintf(cplex_file , "%f ", stats_overheads_pk[i] + (nb_total-1) * 1/TC_INTERVAL * (stats_cluster[i] == i) + 1/TC_INTERVAL);
			else
			//Else, I simulate the higher level -> I take its effective overhead
				fprintf(cplex_file , "%f ", stats_overheads_pk[i]);

			for(j=0;j<nb_total;j++)
				{
					switch (g[i][j]){
						case NULL :
							fprintf(cplex_file,"%d ",  0);
						break;
						case PHYSIC_NEIGHBOR :
						case DOMINANCE :
							fprintf(cplex_file,"%d ",  1);
						break;
						case DOMINATOR_PARENT :
						case DOMINATEE_PARENT :
							fprintf(cplex_file,"%d ",  2);
						break;
						default:
							sprintf(msg, "type=%d" , g[i][j]);
							op_sim_end("this type of link is unknown", msg,"","");
						break;
						}
				}
			fprintf(cplex_file,"\n");							
		}			
	fclose(cplex_file);
	
	
//--------------------------------------------------
//				CPLEX Shortest Routes
//--------------------------------------------------

	//Opens the associated file 
	format_int_to_string( op_sim_time() , msg , 4);
	
	//All ad hoc and direct routes
	if (cds_algos_type != WU_LI)
		sprintf(filename,"results/%scplex_radio_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	else
		sprintf(filename,"results/%scplex_wu_li_direct_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		{
			printf("Error : we cannot create the file %s\n",filename);
		}
	
	//All hybrid routes not necessary through the CDS (using WU & LI)
	if (cds_algos_type == WU_LI)
	 	{
			sprintf(filename,"results/%scplex_wu_li_direct_hybrid_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			cplex_file_2 = fopen(filename,"w");
			if (cplex_file_2 == NULL)
				printf("Error : we cannot create the file %s\n",filename);
		}
	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_total * (nb_total-1));						
	if (cds_algos_type == WU_LI)
		fprintf(cplex_file_2,"%d\n", nb_total-1);						
	
	//---------------------
	//Routes intialization
	//---------------------
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			routes[i][j] = op_prg_list_create();

	//-------------------------
	//List of Shortest Routes
	//-------------------------
	//For each source/destination pair :
	compute_shortest_routes(routes , g , nb_total);
	for(i=0;i<nb_total;i++)
		for(j=0;j<nb_total;j++)
			{
				if (i != j)
					{
						length_average += op_prg_list_size(routes[i][j]) - 1;
						route_to_str_of_stat_id(routes[i][j] , msg);
						fprintf(cplex_file , "%s -1\n", msg);
					}
				
				//All hybrid routes not through the CDS (Wu & LI only)
				if (cds_algos_type == WU_LI)
					{
						if ((op_prg_list_size(routes[i][j]) != 0) && (stats_specificities[i]==NORMAL) && (stats_specificities[j]==AP))
							{
								length_average += op_prg_list_size(routes[i][j]) - 1;
								route_to_str_of_stat_id(routes[i][j] , msg);
								fprintf(cplex_file_2 , "%s -1\n", msg);
							}					
					}
			}
	fprintf(cplex_file,"-1\n");							
	fclose(cplex_file);

	//I delete this file : it is useless
	if ((!DEBUG_CPLEX) && (cds_algos_type != WU_LI))
		remove(filename);

	if (cds_algos_type == WU_LI)
	 	{
			fprintf(cplex_file_2,"-1\n");							
			fclose(cplex_file_2);
		}
	

//--------------------------------------------------
//				CPLEX Clusters
//--------------------------------------------------
	if ((cluster_algos_type != NONE) && (cds_algos_type != WU_LI))
		{

			//Opens the associated file 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results/%scplex_graph_cluster_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			cplex_file = fopen(filename,"w");
			if (cplex_file==NULL)
				printf("Error : we cannot create the file %s\n",filename);
	
			//--------
			//Headers
			//--------
	
			//--------------------
			//Cluster Membership
			//--------------------
			for(i=0;i<nb_total;i++)
				{
					is_empty = OPC_TRUE;
					for(j=0;j<nb_total;j++)
						{	
							if (stats_cluster[j] == i)
								{
									fprintf(cplex_file , "%d ", stats_id_to_addresses[j]);
									is_empty = OPC_FALSE;
								}
						}
					if (!is_empty)
						fprintf(cplex_file,"-1\n");							
				}			
			fprintf(cplex_file,"-1\n");							
			fclose(cplex_file);
			
			//I delete this file : it is useless
			if (!DEBUG_CPLEX)
				remove(filename);

		}
	
	
//--------------------------------------------------
//		  	CPLEX Cluster Shortest Routes
//--------------------------------------------------


	if (cds_algos_type != WU_LI)
		{
			//Opens the associated file 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results/%scplex_routes_cluster_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			cplex_file = fopen(filename,"w");
			if (cplex_file==NULL)
				printf("Error : we cannot create the file %s\n",filename);
	
			//--------
			//Headers
			//--------
			//fprintf(cplex_file,"%d\n",nb_total-1);						
	
			//---------------------
			//Routes intialization
			//---------------------
			for (i=0 ; i < nb_total ; i++)
				for(j=0 ; j < nb_total ; j++)
					cluster_routes[i][j] 		= op_prg_list_create();
	
			//----------------------------------
			//List of Cluster Shortest Routes
			//----------------------------------

			//Hypergrap of clusters
			compute_cluster_graph(g, stats_cluster , cluster_graph , nb_total);

			//The sortest routes in the cluster hypergraph
			compute_shortest_routes(cluster_routes , cluster_graph , nb_total);

			//Optimize the cluster route length
			optimize_cluster_route(cluster_routes , cluster_graph , g , nb_total);
	
			//For each source/destination pair :
			for(i=0;i<nb_total;i++)
				for(j=0;j<nb_total;j++)
					if ((i != j) && (op_prg_list_size((cluster_routes[i][j])) != 0))
						{
							route_to_str_of_stat_id(cluster_routes[i][j] , msg);
							fprintf(cplex_file , "%s -1\n", msg);
						}
			fprintf(cplex_file, "-1\n");
			fclose(cplex_file);
			
			//I delete this file : it is useless
			if (!DEBUG_CPLEX)
				remove(filename);
		}	


	
//--------------------------------------------------
//		  	CPLEX VSR Shortest Routes
//--------------------------------------------------

	if (cds_algos_type != WU_LI)
		{
			//Opens the associated file 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results/%scplex_vsr_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			cplex_file = fopen(filename,"w");
			if (cplex_file==NULL)
				printf("Error : we cannot create the file %s\n",filename);
	
			//--------
			//Headers
			//--------
			fprintf(cplex_file,"%d\n",nb_total * (nb_total-1));						
	
			//---------------------
			//Routes intialization
			//---------------------
			for (i=0 ; i < nb_total ; i++)
				for(j=0 ; j < nb_total ; j++)
					total_cluster_routes[i][j] 	= op_prg_list_create();
	
			//----------------------------------
			//List of Cluster Shortest Routes
			//----------------------------------

			//computes routes according to inter-cluster_routes, with intra-cluster_routes
			compute_intra_cluster_routes(total_cluster_routes , cluster_routes , cluster_graph , g , routes , nb_total);
	
			//For each source/destination pair :
			for(i=0;i<nb_total;i++)
				for(j=0;j<nb_total;j++)
					if ((i != j) && (op_prg_list_size((total_cluster_routes[i][j])) != 0))
						{
							route_to_str_of_stat_id(total_cluster_routes[i][j] , msg);
							fprintf(cplex_file , "%s -1\n", msg);
						}
			fprintf(cplex_file, "-1\n");
			fclose(cplex_file);
		}

//--------------------------------------------------
//		  	CPLEX CDS GRAPH
//--------------------------------------------------

	//Opens the associated file 
	format_int_to_string( op_sim_time() , msg , 4);
	sprintf(filename,"results/%scplex_graph_cds_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		printf("Error : we cannot create the file %s\n",filename);
	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_total);						
		
	//----------------------------------
	// CDS Graph
	//----------------------------------

	//Computes the cds graph
	compute_cds_graph_large(g , cds_graph);
	
	//For each source/destination pair :
	for(i=0;i<nb_total;i++)
		{
			for(j=0;j<nb_total;j++)
				{
					if (cds_graph[i][j] > cds_graph[j][i])
						cds_graph[j][i] = cds_graph[i][j];
				
					fprintf(cplex_file , "%d ", cds_graph[i][j]);
				}
			fprintf(cplex_file, "\n");
		}
	fclose(cplex_file);

   	if (!DEBUG_CPLEX)
		remove(filename);

//--------------------------------------------------
//		  	CPLEX CDS Shortest Routes
//--------------------------------------------------


	//Opens the associated file 
	format_int_to_string( op_sim_time() , msg , 4);
	
	//For hybrid routes via the CDS
	if (cds_algos_type != WU_LI)
		sprintf(filename,"results/%scplex_vsr_hybrid_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	else
		sprintf(filename,"results/%scplex_wu_li_via_cds_hybrid_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file == NULL)
		printf("Error : we cannot create the file %s\n",filename);
	
	//For ad hoc routes via the CDS (wu&li only)
	if (cds_algos_type == WU_LI)
		{
			sprintf(filename,"results/%scplex_wu_li_via_cds_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			cplex_file_2 = fopen(filename,"w");
			if (cplex_file_2 == NULL)
				printf("Error : we cannot create the file %s\n",filename);
		}

	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_total-1);						
	
	if (cds_algos_type == WU_LI)
		fprintf(cplex_file_2,"%d\n",nb_total * (nb_total-1));
	
	//---------------------
	//Routes intialization
	//---------------------
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			cds_routes[i][j] 	= op_prg_list_create();

	//----------------------------------
	//List of CDS Shortest Routes
	//----------------------------------
	
	//computes routes according to inter-cluster_routes, with intra-cluster_routes
	compute_shortest_routes(cds_routes , cds_graph , nb_total);

	//For each source/destination pair :
	for(i=0;i<nb_total;i++)
		for(j=0;j<nb_total;j++)
			{
				//only routes to the AP (via CDS only)
				if ((op_prg_list_size(cds_routes[i][j]) > 1) && (stats_specificities[i]==NORMAL) && (stats_specificities[j]==AP))
				//if ((op_prg_list_size(cds_routes[i][j]) > 1) && (stats_specificities[i]==NORMAL) && (stats_state[j]==DOMINATOR))
					{
						route_to_str_of_stat_id(cds_routes[i][j] , msg);
						fprintf(cplex_file , "%s -1\n", msg);
						if (stats_specificities[j]==AP)
							nb_cds_connected++;
					}
				//All routes (via CDS only)
				if (cds_algos_type == WU_LI)
					{
						//All routes
						if ((op_prg_list_size(cds_routes[i][j]) != 0) && (i != j))
							{
								route_to_str_of_stat_id(cds_routes[i][j] , msg);
								fprintf(cplex_file_2 , "%s -1\n", msg);
							}
					}
			}
		
	fprintf(cplex_file, "-1\n");
	fclose(cplex_file);
	
	if (cds_algos_type == WU_LI)
		{
			fprintf(cplex_file_2, "-1\n");
			fclose(cplex_file_2);
		}
	
	
//--------------------------------------------------
//		  MEMORY DESALLOCATION
//--------------------------------------------------
	//---------------------
	//Routes Destruction
	//---------------------
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			{
				route_empty(routes[i][j]);
				op_prg_mem_free(routes[i][j]);
			}

	//-----------------------
	//VSR Routes Destruction
	//-----------------------
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			{
				route_empty(total_cluster_routes[i][j]);
				op_prg_mem_free (total_cluster_routes[i][j]);
			}

	//---------------------------
	//Cluster Routes Destruction
	//---------------------------
	if (cds_algos_type != WU_LI)
		for (i=0 ; i < nb_total ; i++)
			for(j=0 ; j < nb_total ; j++)
				{
					route_empty(cluster_routes[i][j]);
					op_prg_mem_free (cluster_routes[i][j]);
				}
	//-----------------------
	//CDS Routes Destruction
	//-----------------------
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			{
				route_empty(cds_routes[i][j]);
				op_prg_mem_free (cds_routes[i][j]);
			}
	
//--------------------------------------------------
//		  NEXT CPLEX WRITING REQUIRED ?
//--------------------------------------------------

	//CDS not connected -> delete useless files
	if (nb_total-nb_aps-nb_dead_nodes != nb_cds_connected)
		{
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results/%scplex_graph_radio_bps_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			remove(filename);
			sprintf(filename,"results/%scplex_graph_radio_pps_%s%S.txt" , prefix_results_file , msg , suffix_results_file);
			remove(filename);
			if (!DEBUG_CPLEX)
				{
					sprintf(filename,"results/%scplex_graph_cds_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
				}
			if (cds_algos_type == WU_LI)
				{
					sprintf(filename,"results/%scplex_wu_li_direct_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
					sprintf(filename,"results/%scplex_wu_li_direct_hybrid_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
					sprintf(filename,"results/%scplex_wu_li_via_cds_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
					sprintf(filename,"results/%scplex_wu_li_via_cds_hybrid_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
				}
			else
				{				
					if (!DEBUG_CPLEX)
						{
							sprintf(filename,"results/%scplex_graph_cluster_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
							remove(filename);
							sprintf(filename,"results/%scplex_routes_cluster_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
							remove(filename);
							sprintf(filename,"results/%scplex_radio_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);					
							remove(filename);
						}
					sprintf(filename,"results/%scplex_vsr_ad_hoc_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
					sprintf(filename,"results/%scplex_vsr_hybrid_shortest_routes_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
					remove(filename);
				}
		}
	//All the CDS is connected ?
	return (nb_total-nb_aps-nb_dead_nodes == nb_cds_connected);
}


//Compute all stats necessary for cplex-files, and launch the cplex writting
void compute_and_write_cplex_files(){
	compute_stats_about_graph_cluster_cds();
	if (my_stat_id == nb_total - 1)
		{
			if (write_cplex_files())
				op_sim_end("We have computed valid cplex files", "all was connected", "we have a representative topology","");
		}
	op_intrpt_schedule_call (op_sim_time()+1.0 , STATS_POSITIONS_CODE , compute_and_write_cplex_files , -1);
}


//Links stats, node positions....
void compute_stats_about_graph_cluster_cds(){
	//x and y coordinates
	double		x , y ; 
	//To verify link connectivity
	neigh_cell	*ptr;
	//Control
	char		msg[1000];
	int			i;

	
	//---------------------------------------
	//			GPS Position
	//---------------------------------------	
	if (my_stat_id < MAX_NB_NODES)
		{
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"x position",&x);
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"y position",&y);
			stats_positions	[my_stat_id][0]	= x;
			stats_positions	[my_stat_id][1]	= y;
			stats_weights	[my_stat_id]	= my_weight.value;
			stats_overheads_bits[my_stat_id]	= (overhead_cds_bits + overhead_cluster_bits + overhead_hello_bits + overhead_route_bits +  overhead_paging_bits +  overhead_other_bits) / (op_sim_time() - TIME_BEGIN_STATS);
			stats_overheads_pk	[my_stat_id]	= (overhead_cds_pk + overhead_cluster_pk + overhead_hello_pk + overhead_route_pk +  overhead_paging_pk +  overhead_other_pk) / (op_sim_time() - TIME_BEGIN_STATS);
			if (is_AP)
				stats_specificities	[my_stat_id]	= AP;
			else if (is_DEAD.bool)
				stats_specificities	[my_stat_id]	= DEAD;
			else
				stats_specificities	[my_stat_id]	= NORMAL;
			
			//---------------------------------------
			//			    CDS
			//---------------------------------------	
			stats_state		[my_stat_id]	= my_cds.state;
	
			//---------------------------------------
			//			    Clusters
			//---------------------------------------	
			stats_cluster [my_stat_id] = stats_addresses_to_id[my_clusterhead.address];
			
	   	}
	else
		{
			sprintf(msg,"You must increase MAX_NB_NODES (%d), my_address (%d) is too high\n" , MAX_NB_NODES , my_address);
			printf(msg);
			op_sim_end(msg,"","","");
		}
		
	//---------------------------------------
	//			    Links
	//---------------------------------------	
	for(i=0 ; i<nb_total ; i++)
		stats_links[my_stat_id][i] = ZERO;	
	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			if ((ptr->hops==1) && (ptr->bidirect))
				{
					//DOMINATOR -> DOMINATOR (parent)
					if ( (ptr->address == my_cds.father)  &&  (my_cds.state==DOMINATOR) )
						stats_links[my_stat_id][stats_addresses_to_id[ptr->address]] = DOMINATOR_PARENT;
					//DOMINATEE -> DOMINAT* (relay to parent)
					else if ( ((my_cds.relay == ptr->address) || (my_cds.father == ptr->address))  &&  (my_cds.state==DOMINATEE))
						stats_links[my_stat_id][stats_addresses_to_id[ptr->address]] = DOMINATEE_PARENT;
					//DOMINATOR -> DOMINATOR (WU & LI)
					else if ((my_cds.state == DOMINATOR) && (ptr->state == DOMINATOR) && (cds_algos_type == WU_LI))
						stats_links[my_stat_id][stats_addresses_to_id[ptr->address]] = DOMINATOR_PARENT;				
					//DOMINATEE -> DOMINATEE (dominating zone)
					else if ((my_cds.state == DOMINATEE) && (ptr->state == DOMINATEE) && (ptr->father == my_cds.father))
						stats_links[my_stat_id][stats_addresses_to_id[ptr->address]] = DOMINANCE;				
					else
						stats_links[my_stat_id][stats_addresses_to_id[ptr->address]] = PHYSIC_NEIGHBOR;				
				}
			ptr = ptr->next;
		}
	
	
}


//Collect infos about Position of nodes and links between nodes, and store all that in a stat file
void collect_stat_about_nodes_and_links(int* arg, int code){
	double		x_max , y_max;
	int			x1 , y1 , x2 , y2;
	//Stats Filename
	char		str[150];	
	FILE*		pfile;
	//Control
	int			i , j;
	char		msg[1000];
	//Stats
	int			GRAPHIC_MAX = 12000;
	int			GRAPHIC_XMAX , GRAPHIC_YMAX;
	//Figure : colors,...
	short		color_state;
	short		radius_clusterhead , color_cluster;
	
	
	//---------------------------------------
	// 	Gathers stats about topology
	//---------------------------------------	
	
	compute_stats_about_graph_cluster_cds();
	
	
	//---------------------------------------
	//			Writes Figures
	//---------------------------------------	
		
	//Writes stats if I'm the last node
	if (my_stat_id == nb_total-1)
		{
		
		//---------------------------------------
		//			Pre Treatments
		//---------------------------------------	
			
			//Symetrical matrix
			for(i=0 ; i<MAX_NB_NODES ; i++)
				for (j=0 ; j<MAX_NB_NODES ; j++)
					{
						if ((stats_links[i][j] > stats_links[j][i]) && (stats_links[j][i] == ZERO))
							stats_links[j][i] = stats_links[i][j];
					}
			
		//---------------------------------------
		//			CDS
		//---------------------------------------	
		
			//Opens the associated file and 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(str,"results/%stopology_cds_%s%s.fig" , prefix_results_file , msg , suffix_results_file);
			pfile = fopen(str,"w");
			if (pfile==NULL)
				{
					printf("Error : we cannot create the file %s\n",str);
				}
		
			op_ima_sim_attr_get(OPC_IMA_DOUBLE , "X_MAX" , &x_max);
			op_ima_sim_attr_get(OPC_IMA_DOUBLE , "Y_MAX" , &y_max); 
			
			
			//Horizontal & vertical Scaling
			if (x_max > y_max)
				{
					GRAPHIC_XMAX = GRAPHIC_MAX;
					GRAPHIC_YMAX = y_max * GRAPHIC_MAX / x_max;
				}
			else
				{
					GRAPHIC_YMAX = GRAPHIC_MAX;
					GRAPHIC_XMAX = x_max * GRAPHIC_MAX / y_max;
				}
			
			
			//--------
			//Headers
			//--------
			fprintf(pfile,"#FIG 3.2 \n#Snapshot of The Network Topology (CDS) with CDS-CLUSTER \nLandscape \nCenter \nInches \nA4 \n100.00 \nSingle \n-2 \n1200 2 \n");						
			fprintf(pfile,"1 3 0 1 0 0 50 -1 15 0.000 1 0.000 0 0 1 1 0 0 0 0\n");
			
			//---------------
			//Nodes Position
			//---------------
			fprintf(pfile,"#NODE POSITIONS AND ADDRESSES\n");
			for(i=0;i<nb_total;i++)
				{	
					//Circle with color associated to the clusterhead id
					color_state = get_color_with_state(stats_state[i]);
					sprintf(msg,"1 3 0 1 0 %d 50 -1 15 0.000 1 0.000 %d %d 100 100 0 0 0 0\n",color_state,(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),(int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX)));
					fprintf(pfile,msg);
					
					//Address associated to this node
					sprintf(msg,"4 0 0 50 -1 0 15 0.0000 4 135 135 %d %d %d\\001\n",80+(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),-20+(int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX)),stats_id_to_addresses[i]);
					fprintf(pfile,msg);
					
					//Weight associated to this node
					//sprintf(msg,"4 0 0 50 -1 0 10 0.0000 4 135 135 %d %d (%d)\\001\n",80+(int)(250+stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),-20+(int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX)),stats_weights[i]);
					//fprintf(pfile,msg);
				}
			
			//------
			//Links
			//------
			fprintf(pfile,"#LINKS\n");
			for(i=0;i<nb_total;i++)
				{
					for(j=0;j<nb_total;j++)
						{
							if (stats_links[i][j]!=0)
								{
									//Coordinates of the source and destination of link
									x1 = (int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX));
									y1 = (int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX));
									
									x2 = (int)(stats_positions[j][0]/(x_max/GRAPHIC_XMAX));
									y2 = (int)(stats_positions[j][1]/(y_max/GRAPHIC_YMAX));
									
									//The figure is not represented in the same way according to the cds algorithm used in the simulation
									//if (cds_algos_type == WU_LI)
									//	{	
									
									
									switch(stats_links[i][j])
										{
											case DOMINATOR_PARENT :
												if (cds_algos_type != WU_LI)
													sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 1 0 2\n			1 1 %f 120.00 240.00\n			%d %d %d %d\n			0.000 0.000\n", THICKNESS_DOMINATOR , (double)stats_links[i][j]/2 , x1,y1,x2,y2);
												else
													sprintf(msg,"3 0 2 %d 0 7 50 -1 -1 0.000 0 0 0 2\n			%d %d %d %d\n			0.000 0.000\n", THICKNESS_DOMINATOR , x1,y1,x2,y2);
											break;
											case DOMINATEE_PARENT :
												sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 1 0 2\n			1 1 %f 120.00 240.00\n			%d %d %d %d\n			0.000 0.000\n", THICKNESS_DOMINATEE , (double)stats_links[i][j]/2 , x1,y1,x2,y2);
											break;
											default :
												sprintf(msg,"3 2 2 1 0 7 50 -1 -1 7.000 0 0 0 2\n			%d %d %d %d\n			0.000 0.000\n", x1,y1,x2,y2);
											break;
										}
									
									fprintf(pfile,msg);
								}
						}
				}
			
			//--------
			//Footers
			//--------
			fprintf(pfile,"#END OF FIGURE\n");
			fclose(pfile);
			
			
		//---------------------------------------
		//			CLUSTERS
		//---------------------------------------	
		if (cluster_algos_type!=NONE)
			{			
			
			//Opens the associated file and 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(str,"results/%stopology_cluster_%s%s.fig" , prefix_results_file , msg , suffix_results_file);
			pfile = fopen(str,"w");
			if (pfile==NULL)
				{
					printf("Error : we cannot create the file %s\n",str);
				}
			
			//--------
			//Headers
			//--------
			fprintf(pfile,"#FIG 3.2 \n#Snapshot of The Network Topology (CLUSTER) with CDS-CLUSTER \nLandscape \nCenter \nInches \nA4 \n100.00 \nSingle \n-2 \n1200 2 \n");						
			fprintf(pfile,"1 3 0 1 0 0 50 -1 15 0.000 1 0.000 0 0 1 1 0 0 0 0\n");

			//---------------
			//Nodes Position
			//---------------
			fprintf(pfile,"#NODE POSITIONS AND ADDRESSES\n");
			for(i=0;i<nb_total;i++)
				{	
					//Circle with color associated to the clusterhead id
					color_cluster = stats_cluster[i];
					radius_clusterhead = (i == stats_cluster[i]) * 50 + 100;		
					sprintf(msg,"1 3 0 1 0 %d 50 -1 15 0.000 1 0.000 %d %d %d %d 0 0 0 0\n",color_cluster,(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),(int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX)),radius_clusterhead,radius_clusterhead);
					fprintf(pfile,msg);
					
					//Address associated to this node
					sprintf(msg,"4 0 0 50 -1 0 15 0.0000 4 135 135 %d %d %d\\001\n",80+(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),-20+(int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX)),stats_id_to_addresses[i]);
					fprintf(pfile,msg);
					
					//Weight associated to this node
					//sprintf(msg,"4 0 0 50 -1 0 10 0.0000 4 135 135 %d %d (%d)\\001\n",80+(int)(250+stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),-20+(int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX)),stats_weights[i]);
					//fprintf(pfile,msg);
				}
			
			//------
			//Links
			//------
			fprintf(pfile,"#LINKS\n");
			for(i=0;i<nb_total;i++)
				{
					for(j=0;j<nb_total;j++)
						{
							if (stats_links[i][j]!=0)
								{
									//Coordinates of the source and destination of link
									x1 = (int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX));
									y1 = (int)(stats_positions[i][1]/(y_max/GRAPHIC_YMAX));
									
									x2 = (int)(stats_positions[j][0]/(x_max/GRAPHIC_XMAX));
									y2 = (int)(stats_positions[j][1]/(y_max/GRAPHIC_YMAX));
											
									switch(stats_links[i][j])
										{
											case DOMINATOR_PARENT :
												if (cds_algos_type != WU_LI)
													sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 1 0 2\n			1 1 %f 120.00 240.00\n			%d %d %d %d\n			0.000 0.000\n", THICKNESS_DOMINATOR , (double)stats_links[i][j]/2 , x1,y1,x2,y2);
												else
													sprintf(msg,"3 0 2 %d 0 7 50 -1 -1 0.000 0 0 0 2\n			%d %d %d %d\n			0.000 0.000\n", THICKNESS_DOMINATOR , x1,y1,x2,y2);
											break;
											case DOMINATEE_PARENT :
												sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 1 0 2\n			1 1 %f 120.00 240.00\n			%d %d %d %d\n			0.000 0.000\n", THICKNESS_DOMINATEE , (double)stats_links[i][j]/2 , x1,y1,x2,y2);
											break;
											default :
												sprintf(msg,"3 2 2 1 0 7 50 -1 -1 7.000 0 0 0 2\n			%d %d %d %d\n			0.000 0.000\n", x1,y1,x2,y2);
											break;
										}
									
									fprintf(pfile,msg);
								}								
						}
				}
			
			
			
			//--------
			//Footers
			//--------
			fprintf(pfile,"#END OF FIGURE\n");
			fclose(pfile);
			
			}			
		//---------------------------------------
		//			END
		//---------------------------------------	
			
		}
		  
	op_intrpt_schedule_call(op_sim_time() + INTERVALL_FIGURES , STATS_POSITIONS_CODE , collect_stat_about_nodes_and_links , x1);
}











/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//											Cluster Topo



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------

					Gateways and Clusters (Structures to store old infos) .....

----------------------------------------------------------------------------------------------*/



//Clusters neighbours
int	is_cluster_neigh(int addr){
	list*	cl2;
	
	cl2 = old_cluster_topo.clusters;
	while(cl2!=NULL)
		{
			if (cl2->addr==addr)
				return(1);
			cl2 = cl2->next;
		}

	return(0);
}

void add_cluster_neigh(int addr){
	list*	ptr;
	char	msg[150];

	if (DEBUG>HIGH)
		{
			sprintf(msg,"%d added cl_neigh : %d\n",my_address,addr);
			cluster_message(msg);
		}
	
	//Memory Allocation for a new cell in the list of neighbours
	ptr = (struct list*)op_prg_mem_alloc(sizeof(list));
	if (ptr==NULL)
		{
			printf("error in the memory allocation for the creation of a new cell in the list of clusters neighbours/gateway");
		}
	ptr->addr = addr;
	ptr->last = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
	ptr->next = old_cluster_topo.clusters;
	old_cluster_topo.clusters = ptr;
}

//Refresh the last time this cluster_neigh was seen. If not found, returns 0
int refresh_cluster_neigh(int addr){
	list*	ptr;
	
	ptr = old_cluster_topo.clusters;
	while(ptr!=NULL)
		{
			if (ptr->addr==addr)
				{
					ptr->last = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
					return(1);
				}
			ptr = ptr->next;
		}
	return(0);
}

void delete_cluster_neigh(int addr){
	list	*ptr , *ptr2;
	char	msg[150];

	if (DEBUG>HIGH)
		{
			sprintf(msg,"%d deleted cl_neigh : %d\n",my_address,addr);
			cluster_message(msg);
		}
	
	ptr = old_cluster_topo.clusters;
	ptr2 = NULL;
	while(ptr!=NULL)
		{
			if (ptr->addr==addr)
				{
					if (ptr2==NULL)
						{
							old_cluster_topo.clusters = ptr->next;
							free(ptr);
							ptr = old_cluster_topo.clusters;
						}
					else
						{
							ptr2->next = ptr->next;
							free(ptr);
							ptr = ptr2;
						}				
				}
			ptr2 = ptr;
		 	if (ptr!=NULL)
				ptr=ptr->next;
		}
}



/*-----------------------------------------------------------------------------------------------

								Cluster actual topology

----------------------------------------------------------------------------------------------*/


void add_cluster_neigh_global(int addr1 , int addr2){
	cl_neigh_global*	ptr;
	int 				addr;
	char				msg[150];

	if (!refresh_cluster_neigh_global(addr1,addr2))
		{
			//Permutation if not classed
			if (addr1>addr2)
				{
					addr = addr1;
					addr1 = addr2;
					addr2 = addr;
				}
			if (DEBUG>HIGH)
				{
					sprintf(msg,"%d adds cluster_neigh_global : %d - %d\n",my_address,addr1,addr2);
					cluster_message(msg);
				}

			//Memory Allocation for a new cell in the list of neighbours
			ptr = (struct cl_neigh_global*)op_prg_mem_alloc(sizeof(cl_neigh_global));
			if (ptr==NULL)
				{
					printf("error in the memory allocation for the creation of a new cell in the list of global gateways");
				}
			ptr->cluster1 = addr1;
			ptr->cluster2 = addr2;
			ptr->last = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
			ptr->next = cluster_topo;
			cluster_topo = ptr;
		}
}

void delete_cluster_neigh_global(int addr1 , int addr2){
	cl_neigh_global	*ptr , *ptr2;
	char			msg[150];
	int		 		addr;

	//Permutation if not classed
	if (addr1>addr2)
		{
			addr = addr1;
			addr1 = addr2;
			addr2 = addr;
		}
	
	if (DEBUG>HIGH)
		{		
			sprintf(msg,"deleted global cluster_neigh_global : %d - %d\n",addr1,addr2);
			cluster_message(msg);
		}

	ptr = cluster_topo;
	ptr2 = NULL;
	while(ptr!=NULL)
		{
			if ((ptr->cluster1==addr1)&&(ptr->cluster2==addr2))
				{
					if (ptr2==NULL)
						{
							cluster_topo = ptr->next;
							free(ptr);
							ptr = cluster_topo;
						}
					else
						{
							ptr2->next = ptr->next;
							free(ptr);
							ptr = ptr2;
						}				
				}
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr=ptr->next;
		}
}

int refresh_cluster_neigh_global(int addr1 , int addr2){
	cl_neigh_global*	ptr;
	int 				addr;
	char				msg[150];

	//Permutation if not classed
	if (addr1>addr2)
		{
			addr = addr1;
			addr1 = addr2;
			addr2 = addr;
		}
	
	ptr = cluster_topo;
	while(ptr!=NULL)
		{
			if ((ptr->cluster1==addr1)&&(ptr->cluster2==addr2))
				{
					ptr->last = op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
					return(1);
				}
			ptr = ptr->next;
		}
	if (DEBUG>HIGH)
		{
			sprintf(msg,"%d refreshes cluster_neigh_global : %d - %d\n",my_address,addr1,addr2);
			cluster_message(msg);
		}
			
	return(0);
}

int is_cluster_neigh_global(int addr1, int addr2){
	cl_neigh_global*	ptr;
	int 				addr;

	//Permutation if not classed
	if (addr1>addr2)
		{
			addr = addr1;
			addr1 = addr2;
			addr2 = addr;
		}
	
	ptr = cluster_topo;
	while(ptr!=NULL)
		{
			if ((ptr->cluster1==addr1)&&(ptr->cluster2==addr2))
				{
					return(1);
				}
			ptr = ptr->next;
		}
	return(0);		
}


void periodic_cluster_topo_stats_generate(int* arg, int code){
	cl_neigh_global		*cl_global , *cl_global2;
	list				*cl_local, *cl_local2;
	char				msg[150];

	if (my_clusterhead.address!=0)
	{

		if (my_address==1)
			{
				//Deletes timeouted gateways
				cl_global = cluster_topo;
				cl_global2 = NULL;
				while(cl_global!=NULL)
					{
						if (cl_global->last < op_sim_time())
							{
								if (cl_global2==NULL)
									{
										cluster_topo = cl_global->next;
										free(cl_global);
										cl_global = cluster_topo;
									}
								else
									{
										cl_global2->next = cl_global->next;
										free(cl_global);
										cl_global = cl_global2;
									}				
							}
						cl_global2 = cl_global;
						if (cl_global!=NULL)
							cl_global=cl_global->next;
					}
			}

		if (my_clusterhead.address!=0)
			{
				//Update the differences between our old infos and actual infos
				//A global cluster is not present in the local cluster list
				cl_global = cluster_topo;
				while (cl_global!=NULL)
					{
						if (cl_global->cluster1==my_clusterhead.address)
							{
								if (!is_cluster_neigh(cl_global->cluster2))
									{
										if (op_sim_time() > TIME_BEGIN_TOPO_STATS)
											nb_chgts_virtual_topo++;
										add_cluster_neigh(cl_global->cluster2);
									}				
							}
						if (cl_global->cluster2==my_clusterhead.address)
							{
								if (!is_cluster_neigh(cl_global->cluster1))
									{
										if (op_sim_time() > TIME_BEGIN_TOPO_STATS)
											nb_chgts_virtual_topo++;
										add_cluster_neigh(cl_global->cluster1);
									}				
							}		
						cl_global = cl_global->next;
					}
		
		
				//A local cluster is not present in the global cluster list
				cl_local = old_cluster_topo.clusters;
				cl_local2 = NULL;
				while(cl_local!=NULL)
					{
						if (!is_cluster_neigh_global(my_clusterhead.address,cl_local->addr))
							{
								if (DEBUG>HIGH)
									{
										sprintf(msg,"%d deletes in its table the clusters_neigh %d-%d\n",my_address,my_clusterhead.address,cl_local->addr);
										cluster_message(msg);
									}
								
								if (op_sim_time() > TIME_BEGIN_TOPO_STATS)
									nb_chgts_virtual_topo++;
								if (cl_local2==NULL)
									{
										old_cluster_topo.clusters = cl_local->next;
										free(cl_local);
										cl_local = old_cluster_topo.clusters;
									}
								else
									{
										cl_local2->next = cl_local->next;
										free(cl_local);
										cl_local = cl_local2;
									}				
							}
					
						cl_local2 = cl_local;
						if (cl_local!=NULL)
							cl_local=cl_local->next;
					}
			}

		}

	op_intrpt_schedule_call(op_sim_time()+2.0 , CLUSTER_TOPO_CODE , periodic_cluster_topo_stats_generate , -1);		
}





/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//								DATA and BACKBONE MULTICAST PACKETS



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------

				   Mini Local Routing Table (relay field in neighborhood table)

----------------------------------------------------------------------------------------------*/

int get_relay_to_near_destination(int addr){
	neigh_cell	*ptr;

	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			if ((ptr->address==addr)&&(ptr->bidirect))
				return(ptr->relay);
			ptr = ptr->next;
		}
	 return(-1);
}


//I must contact addr -> I return the next intermediary node to join it
int get_relay_to_general_destination(int addr){

	//If the destination is my AP
	if (addr == ADDR_MULTICAST_AP)
		{
			//If I am dominatee, forward to my relay to dominator / or my dominator
			if (my_cds.state==DOMINATEE)
				return(my_cds.relay);
			//If I am dominator, forwards to my father
			else if (my_cds.state==DOMINATOR)
				return(my_cds.father);
		}
	//If I must contact my _dominator
	else if ((addr==my_cds.father) && (my_cds.state==DOMINATEE))
		return(my_cds.relay);
	//If I must contact a node in my neighborhood table
	else
		get_relay_to_near_destination(addr);
}



/*-----------------------------------------------------------------------------------------------

						Acknowledgments of Unicast Data Packets

----------------------------------------------------------------------------------------------*/

//Delete a packet to aknowledge
void delete_ack_pk(Packet* pk_ack){
	ack_cell	*ptr , *ptr2;
	int			id_pk , id_pk2 , addr , addr2;
	Boolean		is_present;
	char		msg[250];
	
	is_present = OPC_FALSE;
	op_pk_nfd_get(pk_ack,"SRC",&addr);
	op_pk_nfd_get(pk_ack,"PK_ID",&id_pk);

	ptr = my_acks;
	ptr2 = NULL;
	while(ptr!=NULL)
		{
			//op_pk_nfd_get(ptr->pk,"DEST",&addr2);
			addr2 = ptr->dest;
			op_pk_nfd_get(ptr->pk,"PK_ID",&id_pk2);
			
			if ((id_pk==id_pk2) && (addr==addr2))
				{
					is_present = OPC_TRUE;
					if (ptr2==NULL)
						{
							my_acks = ptr->next;
							free(ptr);
							ptr = my_acks;
						}
					else
						{
							ptr2->next = ptr->next;
							free(ptr);
							ptr = ptr2;
						}
					if (DEBUG>LOW)
						{
							sprintf(msg, "%d acked the pk_id %d at %f\n", addr , id_pk, op_sim_time());
							cluster_message(msg);
						}
				}
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr=ptr->next;
		}
	
	if (is_present)
		sprintf(msg ,"ACK : %d records the ack from %d with id %d\n",my_address,addr,id_pk);			
	else
		sprintf(msg, "ACK : not present ! %d didn't record the ack from %d with id %d\n",my_address,addr,id_pk);			
	cluster_message(msg);
}

//Adds a packet to acknowledge
void add_ack_pk(Packet* pkptr){
	ack_cell*	ptr;
	int 		dest;
	int			pk_id;
	char		msg[250];
	
	//Schedule the interruption for verification of the ack reception
	if (op_prg_list_size(my_acks) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RETRANSMISSIONS , RETRANSMISSIONS_CODE , send_timeout_ack_pk , -1);

	//Gathers destination
	op_pk_nfd_get(pkptr,"DEST",	&dest);
	op_pk_nfd_get(pkptr,"PK_ID",&pk_id);

	//Memory Allocation for a new cell in the list of neighbours
	ptr = (struct ack_cell*) op_prg_mem_alloc (sizeof(ack_cell));
	if (ptr==NULL)
		printf("error in the memory allocation for the creation of a new cell in the list of packets to ack");

	ptr->time_sent 		= op_sim_time();
	ptr->dest			= dest;
	ptr->pk				= op_pk_copy(pkptr);
	ptr->nb_retransmits	= 0;
	ptr->next 			= my_acks;
	my_acks 			= ptr;
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "ACK : %d must ack the pk_id %d sent at %f\n", dest , pk_id , op_sim_time());
			cluster_message(msg);
		}
}

//Adds a unicast gws-interconnect-packet to acknowledge
void add_ack_pk_gws(Packet* pkptr, int gw){
	ack_cell*	ptr;
	int			pk_id;
	char		msg[250];

	//Gathers destination
	op_pk_nfd_get(pkptr,"PK_ID",&pk_id);

	//Schedule the interruption for verification of the ack reception
	if (op_prg_list_size(my_acks) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RETRANSMISSIONS , RETRANSMISSIONS_CODE , send_timeout_ack_pk , -1);
	
	//Memory Allocation for a new cell in the list of neighbours
	ptr = (struct ack_cell*) op_prg_mem_alloc (sizeof(ack_cell));
	if (ptr==NULL)
		{
			printf("error in the memory allocation for the creation of a new cell in the list of packets to ack");
		}
	ptr->time_sent 		= op_sim_time();
	ptr->dest			= gw;
	ptr->pk				= op_pk_copy(pkptr);
	ptr->nb_retransmits	= 0;
	ptr->next 			= my_acks;
	my_acks 			= ptr;
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "ACK : %d must ack the pk_id %d sent at %f\n", gw , pk_id , op_sim_time());
			cluster_message(msg);
		}
}

//Acknowledges the packet pk_src
void ack_packet(Packet* pk_src, int type){
	Packet*	pk_dest;
	int		id, src;
	char	msg[200];
	double	delay;
	
	//delay before sending the ack in order to avoid collisions
	delay =  op_dist_uniform(0.005);

	//Gathers information of source
	if (type != BACKBONE_MULTICAST)
		op_pk_nfd_get(pk_src,"SRC",&src);
	else if (type == BACKBONE_MULTICAST)
		op_pk_nfd_get(pk_src,"RELAY",&src);
	
	op_pk_nfd_get(pk_src,"PK_ID",&id);

	if (DEBUG>LOW)
		{
			sprintf(msg ,"ACK : %d sends an ack to %d at %f\n", my_address , src , op_sim_time() + delay);
			cluster_message(msg);
		}
	
	//Create an ack apcket
	pk_dest = op_pk_create_fmt("cdcl_data_ack");
	op_pk_nfd_set(pk_dest,"SRC",		my_address);
	op_pk_nfd_set(pk_dest,"DEST",		src);
	op_pk_nfd_set(pk_dest,"PK_ID",		id);
	op_pk_nfd_set(pk_dest,"TTL",		1);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",ACK_UNICAST_PK_TYPE);
	
	//Sends it
	pk_send_delayed(pk_dest , delay);
}

//Retransmit a packet after timeout
void send_timeout_ack_pk(int *arg, int code){
	ack_cell	*ptr , *ptr2;
	int			dest , dest_final;
	int			next_intrpt_needed = 0;		//An Interruption is needed 
	char		msg[250];
	
	//Searches if an entry must be retransmited
	ptr = my_acks;
	while(ptr!=NULL)
		{
			if (ptr->time_sent <= op_sim_time() - TIMEOUT_RETRANSMISSIONS)
				{
					if (ptr->nb_retransmits < 2)
						{
							op_pk_nfd_get(ptr->pk,"DEST_FINAL",&dest_final);

							//If not multicast address, search a new relay
							if (dest_final != ADDR_MULTICAST_BACKBONE)
								{
									dest = get_relay_to_general_destination(dest_final);
									op_pk_nfd_set(ptr->pk,"DEST",dest);
									pk_retransmit(op_pk_copy(ptr->pk));
								}

							else
								{
									dest = dest_final;
									op_pk_nfd_set(ptr->pk,"DEST",dest);
									pk_retransmit(op_pk_copy(ptr->pk));
								}
							
							if (DEBUG>LOW)
								{
									sprintf(msg,"RETRANSMISSION : %d forwards the packet to %d to join %d at %f\n" , my_address , dest , dest_final , op_sim_time());							
									printf(msg);							
									cluster_message(msg);
								}
							
							ptr->time_sent = op_sim_time();
							ptr->nb_retransmits++;

							if (ptr->nb_retransmits < 2)
								next_intrpt_needed = 1;
						}
				}
			ptr=ptr->next;
		}
	
	//Deletes entries with too many retries
	ptr = my_acks;
	ptr2 = NULL;
	while(ptr!=NULL)
		{
			//Deletes entries with too many retransmissions
			if (ptr->nb_retransmits >= MAX_NB_RETRANSMISSIONS)
				{
					if (ptr2==NULL)
						{
							my_acks = ptr->next;
							op_pk_destroy(ptr->pk);
							free(ptr);
							ptr = my_acks;
						}
					else
						{
							ptr2->next = ptr->next;
							op_pk_destroy(ptr->pk);
							free(ptr);
							ptr = ptr2;
						}				
				}
		
			//Next entry
			ptr2 = ptr;
			if (ptr!=NULL)
				ptr=ptr->next;
		}
	
	if (next_intrpt_needed)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RETRANSMISSIONS , RETRANSMISSIONS_CODE , send_timeout_ack_pk , -1);
	
}





















/*-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



//													WU AND LI



-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/





/*-----------------------------------------------------------------------------------------------

								CDS of WU and LI (based on k-Neighborhood knowledge)

----------------------------------------------------------------------------------------------*/
/*



//Empties a list
void empty_list(List* ll){
	void	*elem;
	
	while(op_prg_list_size(ll) > 0)
		{
			elem = op_prg_list_remove(ll , OPC_LISTPOS_TAIL);
			op_prg_mem_free(elem);
		}	
}


//deletes timeouted entries
void update_neighbors_table_wu(){
	int			i;
	neigh_wu	*neigh;
	
	for(i=0 ; i<op_prg_list_size(neighbor_table_wu_li) ; i++)
		{
			neigh = op_prg_list_access(neighbor_table_wu_li , i);
			if (neigh->timeout < op_sim_time())
				{
					empty_list(neigh->neighbors);
					op_prg_mem_free(neigh->neighbors);
					op_prg_list_remove(neighbor_table_wu_li , i);
					op_prg_mem_free(neigh);
					i--;				
				}
		}	
}


//update the neighbor_table
void update_neighbor_wu(int addr , int weight , int hops , Boolean bidirect , List *neighbors){
	//Neighbor Table
	neigh_wu	*neigh;
	int			i;
	char		msg[500];
	
	//init
	neigh = NULL;

	
	//I search in the table the entry corresponding to the actual source
	for(i=0 ; i < op_prg_list_size(neighbor_table_wu_li); i++)
		{
			neigh = op_prg_list_access(neighbor_table_wu_li , i);
			if ((neigh->address == addr) && ((neigh->bidirect == bidirect) || ((neigh->hops == hops) && (hops ==1))))
				{
					neigh->weight 	= weight;
					neigh->hops 	= hops;
					neigh->bidirect = bidirect;
					neigh->timeout 	= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
					
					empty_list(neigh->neighbors);
					op_prg_mem_free(neigh->neighbors);
					neigh->neighbors = neighbors;

					if (DEBUG>MAX)
						{
							sprintf(msg, "%d updates its neighbor table : addr %d, weight %d, hops %d, bidirect %d at %f\n", my_address , neigh->address , neigh->weight , neigh->hops , neigh->bidirect , neigh->timeout);
							cluster_message(msg);
						}
					return;
				}
		}
	
	//No entry -> we add one (empty by default)
	if ((neigh == NULL) || (neigh->address != addr))
		{
			neigh = malloc(sizeof(neigh_wu));
			if (neigh == NULL)
				printf("Error in the creation of a new neighbors in the neighbors table of WU & Li\n");
					
			neigh->address 	= addr;
			neigh->weight 	= weight;
			neigh->hops 	= hops;
			neigh->bidirect = bidirect;
			neigh->timeout 	= op_sim_time() + TIMEOUT_HELLO*INTERVALL_HELLO;
					
			neigh->neighbors = neighbors;
		
			op_prg_list_insert(neighbor_table_wu_li , neigh , OPC_LISTPOS_TAIL);
			
			if (DEBUG>MAX)
				{
					sprintf(msg, "%d adds in its neighbor table a new entry : addr %d, weight %d, hops %d, bidirect %d at %f\n", my_address , neigh->address , neigh->weight , neigh->hops , neigh->bidirect , neigh->timeout);
					cluster_message(msg);
				}
		}
}


//Is a bidirect neighbor ?
Boolean	is_neighbor_bidirect(Packet *pkptr){
	Boolean		bidirect;
	Boolean		is_fields_overflow;
	int			addr;
	int			i;
	
	i = 1;
	is_fields_overflow = (i > MAX_FIELDS_IN_HELLO_RELAY) ;
	while (op_pk_nfd_is_set(pkptr , hello_fields_names[i].address) && !is_fields_overflow )
		{
			op_pk_nfd_get(pkptr , hello_fields_names[i].bidirect , &bidirect);
			if (bidirect) 
				{		
					op_pk_nfd_get(pkptr , hello_fields_names[i].address ,	&addr);
					if (addr == my_address)
						return(OPC_TRUE);
				}
		
			i++;
			is_fields_overflow = (i > MAX_FIELDS_IN_HELLO_RELAY) ;
		}
	return(OPC_FALSE);
}


//I received one hello packet -> I add/update the neighbor_table associated to the source
void update_the_neighbor_table_associated_to_one_neighbor(Packet* pkptr){
	//infos
	int				src_addr , src_weight , ttl;
	Boolean			bidirect;
	List			*neighbors;
	//Control
	char			msg[150];
	
	//Gathers info from the packet
	op_pk_nfd_get(pkptr, "SRC"		, &src_addr);
	op_pk_nfd_get(pkptr, "WEIGHT"	, &src_weight);
	op_pk_nfd_get(pkptr, "TTL"		, &ttl);

	//creates the neighbor_list* associated to the packet
	neighbors = create_neighbors_list(pkptr);
	//neighbors = op_prg_list_create();
	
	//Does the hello come from a bidirectionnal link ?
	if (ttl_for_hellos == ttl)
		bidirect = is_neighbor_bidirect(pkptr);
	else
		bidirect = OPC_TRUE;

	//Updates the entry (information only for the =k_cds-neighborhood)
	if ((ttl_for_hellos - ttl) + 1 <= k_cds)
		update_neighbor_wu(src_addr , src_weight , (ttl_for_hellos - ttl) + 1 , bidirect , neighbors);

	if (DEBUG>MAX)
		{
			sprintf(msg,"I received an hello packet from %d -> I add/update its neighbor_table that I stored\n" , src_addr);
			cluster_message(msg);
		}
	

}




/*-----------------------------------------------------------------------------------------------

								Manipulation of Lists

----------------------------------------------------------------------------------------------*/

//comate to pointers of int
int compare_values(int *el1 , int *el2){
	int	a , b;
	
	a = (int)(*el1);
	b = (int)(*el2);

	if (a > b)
		return(1);
	else if (a == b)
		return(0);
	else
		return(-1);
}

//returns a list in str
char* int_list_to_str(List* ll){
	int		i;
	int		*elem;
	char*	result;
	
	result = malloc(op_prg_list_size(ll)*sizeof(char)*5);
	sprintf(result, "");
	for(i=0 ; i<op_prg_list_size(ll); i++)
		{
			elem = op_prg_list_access(ll, i);
			sprintf(result, "%s %d", result, *elem);		
		}
	return(result);
}


//are the list different ?
Boolean	are_different_int_lists(List* l1 , List* l2){
	int		i ;
	int		*el1 , *el2;
	char	msg[200];
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "lists (cds,higher) : %s and %s\n", int_list_to_str(l1) ,  int_list_to_str(l2));
			cluster_message(msg);
		}
	
	//Different cardinality
	if (op_prg_list_size(l1) != op_prg_list_size(l2))
	 	return(OPC_TRUE);

	//Sorts the lists
	op_prg_list_sort(l1 , compare_values);
	op_prg_list_sort(l2 , compare_values);

	//Compare both lists
	for(i=0 ; i<op_prg_list_size(l1) ; i++)
		{
			el1 = op_prg_list_access(l1,i);
			el2 = op_prg_list_access(l2,i);
			if (*el1 != *el2)
				return(OPC_TRUE);
		}

	return(OPC_FALSE);
}


//IS the int already in the list ?
Boolean is_int_in_list(List* ll , int addr){
	int		i;
	int		*elem;
	
	for(i=0 ; i<op_prg_list_size(ll) ; i++)
		{
			elem = op_prg_list_access(ll , i);
			if (addr == *elem)
				return(OPC_TRUE);
		}
	return(OPC_FALSE);
}

//Adds an int in the list (if it is not already in that list)
void add_int_in_list(int addr , List* ll){
	int		*elem;

	if (!is_int_in_list(ll, addr))
		{
			elem = malloc(sizeof(int));
			*elem = addr;
			op_prg_list_insert(ll , elem , OPC_LISTPOS_TAIL);
		}
}







/*-----------------------------------------------------------------------------------------------

								CDS of WU and LI (State Determination)

----------------------------------------------------------------------------------------------*/



//returns the list of higher weight nodes
List* get_list_of_higher_weight_nodes(){
	List		*higher_nodes;
	neigh_cell	*ptr;
	
	//initialisation
	higher_nodes = op_prg_list_create();
	
	//Neighbor table
	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			if (  ((ptr->weight>my_weight.value) && (ptr->address != my_address)) || ((ptr->weight == my_weight.value) && (ptr->address>my_address))  )
				if ((ptr->bidirect) && (ptr->hops <= k_cds))
					add_int_in_list(ptr->address , higher_nodes);
		
			ptr = ptr->next;
		}	
	
	//End
	return(higher_nodes);
}

//returns the address of a 1-neighbor with an higher weight
int get_1_neighbor_with_highest_weight(){
	neigh_cell	*ptr;
	int			highest_weight = 0;
	int			addr;
	
	//initialization
	addr = my_address;
	highest_weight = my_weight.value;
	
	//Search the root
	ptr = neighbour_table;
 	while (ptr!=NULL)
		{
			if ((ptr->weight > highest_weight) || ((ptr->weight == highest_weight) && (ptr->address > addr)) )
				if ((ptr->hops <=k_cds) && (ptr->bidirect))
						{
							addr 			= ptr->address;
							highest_weight 	= ptr->weight;
						}
			ptr = ptr->next;
		}
	
	//Result
	if (addr != my_address)
		return(addr);
	else
		return(-1);
}


//Is neigh a bidirect neighbor of addr ?
Boolean is_a_declared_bidirect_neighbor(int addr , int addr_neigh){
	int			i;
	//neigh_wu	*neigh;
	neigh_cell	*ptr;
	neigh_min	*neigh_list;

	//Search addr
	ptr = neighbour_table;
	while ((ptr!=NULL) && !((ptr->address == addr) && (ptr->bidirect)) )
		ptr = ptr->next;
	
	//is add_neigh one of its neighbors ?
	if (ptr != NULL)
		{
			//Looks up its neighbors list
			for(i=0 ; i < op_prg_list_size(ptr->neighbors) ; i++)
				{
					//gets the j° neighbor and regards if it is the neigh I am searching....
					neigh_list = op_prg_list_access(ptr->neighbors, i);
					if (neigh_list->address == addr_neigh)
						return(OPC_TRUE);
				}
		}
	
	//The bidirect link was not found
	return(OPC_TRUE);

}

//adds addr and its dist-neighbors as covered
void construct_covering(int addr, List* covering, short dist){
	neigh_cell	*ptr;
	neigh_min	*neigh_list;
	int			i;
	
	//Adds the firt node
	add_int_in_list(addr , covering);
	
	//adds its (dist-1)-neighbors
	if (dist > 0)
		{
			//Search the node
			ptr = neighbour_table;
			while ((ptr!=NULL) && !((ptr->address == addr) && (ptr->bidirect)) )
				ptr = ptr->next;
	
			//adds the (dist-1)-neighbors of addr
			if (ptr != NULL)
				for (i=0 ; i<op_prg_list_size(ptr->neighbors) ; i++)
					{
						neigh_list = op_prg_list_access(ptr->neighbors , i);
						construct_covering(neigh_list->address , covering , dist-1);
					}
		}
	
}

//returns a CDS of higher weight nodes, rooted at 'root' (table -> contains only k_cds-neighbors)
void construct_cds_from(List* cds , List* covering , int root){
	int			root_pos=-1;
	int			i;
	//neigh_wu	*neigh;
	neigh_cell	*ptr;
	neigh_min	*neigh_list;
	char		msg[1000];
	
	//Search the root
	ptr = neighbour_table;
	while ((ptr!=NULL) && !((ptr->address == root) && (ptr->bidirect) && (ptr->hops <= k_cds)) )
		ptr = ptr->next;
	
	//adds the root and create the CDS starting from it
	if (ptr != NULL)
		{
			//I add the node in the CDS, and only this node in the covering set 
			//(not its k_cds-neighbors, because I use the same code to expand the CDS and to add its 1-neighbors to optimize the algo speed....)
			add_int_in_list(ptr->address 	, cds);
			construct_covering(ptr->address , covering , 0);
			
			if (DEBUG>MEDIUM)
				{
					sprintf(msg, "%d is added to the CDS (CDS=%s)\n", ptr->address , int_list_to_str(cds));
					cluster_message(msg);
				}			
			
			//Looks up its neighbors list
			for(i=0 ; i < op_prg_list_size(ptr->neighbors) ; i++)
				{
					//gets the node
					neigh_list = op_prg_list_access(ptr->neighbors, i);
					
					//Adds the node as covered
					construct_covering(neigh_list->address , covering , k_cds-1);
					
					//And if higher weight -> adds it to the CDS
					if (  ((neigh_list->weight > my_weight.value) && (neigh_list->address != my_address))   ||     ((neigh_list->weight == my_weight.value) && (neigh_list->address > my_address))  )
						{				  
							if (!is_int_in_list(cds, neigh_list->address))
								//verification that this node declares ourself as a bidirect neighbor (perhaps, the information is changing)
								if (is_a_declared_bidirect_neighbor(neigh_list->address , root))
									construct_cds_from(cds, covering , neigh_list->address);
						}
				}			
		}
}


//Is covering a complete covering of all my neighbors ?
Boolean is_a_complete_covering(List* covering){
	char		msg[200];
	neigh_cell	*ptr;
	
	ptr= neighbour_table;
	while(ptr != NULL)
		{
			if ((ptr->bidirect) && (ptr->hops<=k_cds) && (!is_int_in_list(covering, ptr->address)))
				{
					if (DEBUG>LOW)
						{
							sprintf(msg, "%d not covered\n", ptr->address);
							cluster_message(msg);
						}
					return(OPC_FALSE);
				}
			ptr = ptr->next;
		}
	return(OPC_TRUE);
}

//Return my state : dominator or dominatee
int get_state_wu_li(){
	List	*cds;
	List	*covering;
//	List	*higher_weight_nodes;
	int		root;
	char	msg[200];
	
	if (DEBUG>HIGH)
		print_neighbour_table();
	
	//initialization
	cds = op_prg_list_create();
	covering = op_prg_list_create();
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "CDS -> computes the new state at %f (my weight = %d)\n", op_sim_time() , my_weight.value);
			cluster_message(msg);
		}
	
	//Constructs a cds from the root + covering of this cds
	root = get_1_neighbor_with_highest_weight();	
	if (root == -1)
		return(DOMINATOR);
	construct_cds_from(cds , covering , root);	
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "CDS obtained (root %d): %s\n", root , int_list_to_str(cds));
			cluster_message(msg);
			sprintf(msg, "Covering obtained : %s\n", int_list_to_str(covering));	
			cluster_message(msg);
		}	
	
	//Is the CDS a complete covering ?
	if (!is_a_complete_covering(covering))
		{
			if (DEBUG>LOW)
				{
					sprintf(msg, "not a complete covering\n\n\n");
					cluster_message(msg);
				}
			//Lists destruction
			empty_list(cds);
			op_prg_mem_free(cds);
			empty_list(covering);
			op_prg_mem_free(covering);
			return(DOMINATOR);		
		}

	if (DEBUG >LOW)
		{
			sprintf(msg, "total covering\n");
			cluster_message(msg);
		}
			   
	//The list of higher weight nodes = computed cds ?	(The original rule of WU & LI)
	/*if (1)//k_cds > 1)
		{
			higher_weight_nodes = get_list_of_higher_weight_nodes();
			if (are_different_int_lists(cds , higher_weight_nodes))
				{
					if (DEBUG>LOW)
						{
							sprintf(msg, "CDS computed != set of higher weight nodes\n");
							cluster_message(msg);
						}
					empty_list(cds);
					op_prg_mem_free(cds);
					empty_list(covering);
					op_prg_mem_free(covering);
					empty_list(higher_weight_nodes);
					op_prg_mem_free(higher_weight_nodes);
					return(DOMINATOR);
				}
		}
	*/
	
	//Lists destruction + final result
	empty_list(cds);
	op_prg_mem_free(cds);
	empty_list(covering);
	op_prg_mem_free(covering);
	return(DOMINATEE);		
}














/*

//Constructs the set of higher_weight nodes + its covering
void construct_higher_weight_nodes(List* higher_nodes , short mcds_set[MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES], List* covering){
	neigh_cell	*ptr;
	neigh_min	*neigh_list;
	int			i;
	//char		msg[1000];
	
	//Search the root
	ptr = neighbour_table;
	while (ptr!=NULL)
		{
			//adds the links in the graph
			g[  stats_addresses_to_id[ptr->address]  ]  [ my_stat_id  ] = OPC_TRUE;
			
			if ((ptr->hops <= k_cds) && (ptr->bidirect) && (ptr->weight > my_weight.value))
				{
					//I add the node in the CDS, and only this node in the covering set 
					add_int_in_list(ptr->address 	, higher_nodes);
					mcds_set[ stats_addresses_to_id[ptr->address]] = OPC_TRUE;
					construct_covering(ptr->address , covering , k_cds);
					
					//Constructs the associated graph
					for (i=0 ; i<op_prg_list_size(ptr->neighbors) ; i++)
						{
							neigh_list = op_prg_list_access(ptr->neighbors , i);
							g[  stats_addresses_to_id[ptr->address]  ]  [  stats_addresses_to_id[neigh_list->address]  ] = OPC_TRUE;
						}
					
				}
			ptr = ptr->next;
		}
}

//Is covering a complete covering of all my neighbors ?
Boolean is_a_complete_covering(List* covering){
	char		msg[200];
	neigh_cell	*ptr;
	
	ptr= neighbour_table;
	while(ptr != NULL)
		{
			if ((ptr->bidirect) && (ptr->hops<=k_cds) && (!is_int_in_list(covering, ptr->address)))
				{
					if (DEBUG>LOW)
						{
							sprintf(msg, "%d not covered\n", ptr->address);
							cluster_message(msg);
						}
					return(OPC_FALSE);
				}
			ptr = ptr->next;
		}
	return(OPC_TRUE);
}



//Is a connected set ?
Boolean is_a_connected_set(List* set, short g[MAX_NB_NODES][MAX_NB_NODES]){
	List	*routes[MAX_NB_NODES][MAX_NB_NODES];
	int		i , j;
	char	msg[200];
		
	//Routes intialization
	for (i=0 ; i < nb_total ; i++)
		for(j=0 ; j < nb_total ; j++)
			routes[i][j] 	= op_prg_list_create();
	
	//List of CDS Shortest Routes
	compute_shortest_routes(routes , g , nb_total);

	if (DEBUG>LOW)
		for(i=0; i<nb_total; i++)
			{
				for(j=0; j<nb_total; j++)
					{
						route_to_str(routes[i][j] , msg);
						cluster_message(msg);
					}
				cluster_message("\n");
			}			
	
	//Is all the routes present ?
	for(i=0; i<nb_total; i++)
		for(j=0; j<nb_total; j++)
			if ((i!=j) && (is_int_in_list(set , i)) && (is_int_in_list(set , j)) && (route_length(routes[i][j]) == 0))
				return(OPC_FALSE);
		
	//All the routes are present
	return(OPC_TRUE);
}



//Return my state : dominator or dominatee
int get_state_wu_li2(){
	List	*higher_weight_nodes;
	List	*covering;
	int		root;
	char	msg[200];
	short	g[MAX_NB_NODES][MAX_NB_NODES];
	short	mcds_set[MAX_NB_NODES];
	int		i , j;
	
	if (DEBUG>HIGH)
		print_neighbour_table();
	
	//initialization
	higher_weight_nodes = op_prg_list_create();
	covering 			= op_prg_list_create();
	for(i=0; i<nb_total; i++)
		{
			for(j=0; j<nb_total; j++)
				g[i][j] = OPC_FALSE;
			mcds_set[i] = OPC_FALSE;
		}
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "CDS -> computes the new state at %f (my weight = %d)\n", op_sim_time() , my_weight.value);
			cluster_message(msg);
		}
	
	//Constructs the list of 1-neighborhood of higher weight + their covering
	construct_higher_weight_nodes(higher_weight_nodes , mcds_set , g ,covering);
	
	
	//Gets a symetric graph
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			if (g[i][j] > g[j][i])
				g[j][i] = g[i][j];
	
	//debug
	if (DEBUG>LOW)
		{
			sprintf(msg, "CDS obtained (root %d): %s\n", root , int_list_to_str(higher_weight_nodes));
			cluster_message(msg);
			sprintf(msg, "Covering obtained : %s\n", int_list_to_str(covering));	
			cluster_message(msg);
		}		
	
	//The nodes are not a complete covering -> End
	if (!is_a_complete_covering(covering))
		{
			if (DEBUG>LOW)
				{
					sprintf(msg, "not a complete covering\n\n\n");
					cluster_message(msg);
				}
			//Lists destruction
			empty_list(higher_weight_nodes);
			op_prg_mem_free(higher_weight_nodes);
			empty_list(covering);
			op_prg_mem_free(covering);
			return(DOMINATOR);		
		}
	
	//The nodes are not a complete covering -> End
	//if (!is_a_connected_set(higher_weight_nodes , g))
	if (is_a_cds( g, mcds_set))
		{
			if (DEBUG>LOW)
				{
					sprintf(msg, "not a connected set\n\n\n");
					cluster_message(msg);
				}
			
			//Lists destruction
			empty_list(higher_weight_nodes);
			op_prg_mem_free(higher_weight_nodes);
			empty_list(covering);
			op_prg_mem_free(covering);
			return(DOMINATOR);		
		}

	if (DEBUG >LOW)
		{
			sprintf(msg, "whole covering and connected\n");
			cluster_message(msg);
		}
			   	
	//The nodes are a complete covering -> End
	empty_list(higher_weight_nodes);
	op_prg_mem_free(higher_weight_nodes);
	empty_list(covering);
	op_prg_mem_free(covering);
	return(DOMINATEE);		
}






*/











//Returns the address of a father (knowing the address of the old father)
int get_new_father(int old_father , int *father_result , int *relay_result , int *hops_result){
	neigh_cell	*ptr;
	int			new_father = -1;
	int			new_relay = -1;
	int			new_hops = -1;
	int			highest_weight=0;
	
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			//I can keep the same father
			if ((ptr->address == old_father) && (ptr->state == DOMINATOR) && (ptr->hops <= k_cds) && (ptr->bidirect))
				{
					new_father 		= old_father;
					new_relay 		= ptr->relay;
					new_hops		= ptr->hops;
					highest_weight 	= MAX_WEIGHT + 1;					
				}
			//It's a candidate
			if ((ptr->hops <= k_cds) && (ptr->state == DOMINATOR) && (ptr->bidirect) && (ptr->weight > highest_weight))
				{
					new_father 		= ptr->address;
					new_relay 		= ptr->relay;
					highest_weight 	= ptr->weight;					
					new_hops		= ptr->hops;
				}			
			ptr = ptr->next;
		}
	
	//result
	*father_result 	= new_father;
	*relay_result 	= new_relay;
	*hops_result	= new_hops;
}


//I update my cds-state according to my k-neighborhood table
void cds_maintenance_wu_li(int* arg, int code){
	int		new_state , new_father , new_relay , new_hops;
	
	//My new computed state
	new_state 	= get_state_wu_li();
	if (new_state != my_cds.state)
		update_state_cds(new_state);

	//My new father (Important if I am dominatee) 
	//NB : maximum persistence : I try to keep my father, or else I take the highest weight dominator
	get_new_father(my_cds.father , &new_father , &new_relay , &new_hops);
	if (my_cds.state == DOMINATOR)
		my_cds.father 	= my_address;	
	else if (my_cds.state == DOMINATEE)
		change_father(new_father , new_relay , new_hops);
			
	if (DEBUG>LOW)
		{
			//print_neighbours_of_neighbours_table();
			//print_neighbour_table();
		}
	
	//Next CDS Computing
	op_intrpt_schedule_call (op_sim_time() + INTERVALL_CDS_WU_LI_COMP, CDS_WU_LI_COMP_CODE , cds_maintenance_wu_li , -1);
}



































//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//
//
//
//									GATEWAY MANAGEMENT (INTER CLUSTER)
//
//
//
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------


//Debug Purpose
void print_my_gw_list(){
	char		msg[300];
	int			i;
	struct_gw	*entry;
	
	//Last Version
	//update_my_gw_list();

	//Print
	sprintf(msg,"\n\n------------------ List of gateways of %d -----------------\n\n",my_address);
	cluster_message(msg);
	
	if (my_gw_list == NULL)
		op_sim_end("Error :" , "my_gw_list is a null list" , "please initialize it" ,"");
	
	//verification
	for(i=0; i < op_prg_list_size(my_gw_list); i++ )
		{
			entry = (struct_gw*) op_prg_list_access (my_gw_list , i);
			sprintf(msg, "	Cluster %d :	%d\n", i , entry->cluster);		
			cluster_message(msg);
		}
	cluster_message("\n----------------------------------------------------------------\n\n");
}


//Prints the gw lists for each neighbor in neighbourhood table
void print_gw_lists_of_neighbour_table(){
	char		msg[300];
	neigh_cell	*ptr;
	
	//Print
	sprintf(msg,"\n\n------------- List of clusters of my neighbors of %d -----------------\n\n",my_address);
	cluster_message(msg);

	//GW Lists
	ptr = neighbour_table;
	while(ptr != NULL)
		{	
			if (ptr->gw_list == NULL)
				op_sim_end("Error :" , "my_gw_list is a null list" , "please initialize it" ,"");
	
			if (op_prg_list_size(ptr->gw_list) != 0)
				{
					sprintf(msg,"%d	(%f) :	" , ptr->address , ptr->gw_timeout);
					cluster_message(msg);
				}
			print_gw_list(ptr->gw_list);
			if (op_prg_list_size(ptr->gw_list) != 0)
				cluster_message("\n");
			
			ptr = ptr->next;
		}
	
	//Footer
	cluster_message("\n----------------------------------------------------------------\n\n");
}

//Update the list of the clusters for which I am gateway
void update_my_gw_list(){
	neigh_cell*		ptr_neigh;
	
	//Empty the old list
	empty_gw_list(my_gw_list);
	
	//Fills with the new cluster-neighbors
	ptr_neigh = neighbour_table;
	while (ptr_neigh != NULL)
		{
			if ((ptr_neigh->hops == 1) && (ptr_neigh->bidirect) && (ptr_neigh->clusterhead != my_clusterhead.address) && (ptr_neigh->clusterhead != 0) && (my_clusterhead.address != 0))
				 add_in_gw_list (ptr_neigh->clusterhead , my_gw_list);
			ptr_neigh = ptr_neigh->next;
		}
}


void fill_hello_pk_with_my_gw_list(Packet* pkptr){
	struct_gw*	entry;
	int			i;
	char		field_name[30];
	char		msg[100];
	
	//Update my current list
	update_my_gw_list();
	
	if (my_gw_list == NULL)
		op_sim_end("Error : ", "The my_gw_list is a null list" , "please correct the pb" , "");
	
	//Verification (If cluster_ago == NONE, we consider that not essential...)
	if ((op_prg_list_size(my_gw_list) > MAX_GW_FIELDS_IN_HELLO) && (cluster_algos_type != NONE))
		{
			sprintf(msg, "at least to %d\n", op_prg_list_size(my_gw_list));
			op_sim_end("We don't have enough fields to place all our Cluster-Neighbors" , "for which we are Gateways","You must increase MAX_GW_FIELDS_IN_HELLO" , msg);
		}
	
	//Fills the packet
	for(i=0; (i< op_prg_list_size(my_gw_list)) && (i<=MAX_GW_FIELDS_IN_HELLO) ; i++)
		{
			entry = (struct_gw*) op_prg_list_access(my_gw_list , i);
			sprintf(field_name , "GATEWAY_%d" , i+1);
			op_pk_nfd_set(pkptr , field_name , entry->cluster);			
		}
	//Delete unused fields the field numbered "MAX_GATEWAY_FIELDS_IN_HELLO_RELAY" is including deleted 
	for (i = op_prg_list_size(my_gw_list) ; i < MAX_GW_FIELDS_IN_HELLO ;  i++)
		{
			sprintf(field_name , "GATEWAY_%d" , i+1);
			op_pk_nfd_strip(pkptr, field_name);
		}	
}


//Fills a gw_list with an hello_packet (fields "gateway_%d")
List* fill_gw_list_with_hello_pk(Packet* pkptr , List *gw_list){
	char	field_name[30];
	int		i;
	int		cluster;

	//Empty the old list
	empty_gw_list(gw_list);
	
	//Fills it
	sprintf(field_name, "GATEWAY_1");
	i=1;
	while ((i <= MAX_GW_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr , field_name)))
		{
			op_pk_nfd_get(pkptr , field_name , &cluster);
			add_in_gw_list(cluster , gw_list);
			
			i++;
			sprintf(field_name, "GATEWAY_%d", i);
		}
	
	//Returns the result
	return(gw_list);
}

































//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//
//
//
//											STATS + DEBUG
//
//
//
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------
//
//								STATISTICS, INFOS .....
//
//---------------------------------------------------------------------------------------------


/////////////////////////////////////////////
//
//					DEBUG
//
/////////////////////////////////////////////

void cluster_message(char* message)
	{
		FILE* 	fichier;
		char	str[200];

		if (NORMAL_DEBUG)
			{
				if (my_address<10)
					sprintf(str,"results/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
					sprintf(str,"results/details_per_node/results_%d.txt",my_address);
				fichier = fopen(str,"a");
				fprintf(fichier,message);
				fclose(fichier);
			}
	}
void test_message(char* message)
	{
		FILE* 	fichier;
		char	str[200];
		if (TEST_DEBUG)
			{
				sprintf(str,"results/%sdebug_test%s.txt", prefix_results_file , suffix_results_file);			
				fichier = fopen(str,"a");
				fprintf(fichier,message);
				fclose(fichier);
			}
	}
void bb_flooding_message(char* message)
	{
		FILE* 	fichier;
		char	str[200];

		sprintf(str,"results/%sdebug_backbone_flooding%s.txt", prefix_results_file , suffix_results_file);			
				if (BB_FLOODING_DEBUG)
			{
				fichier = fopen(str,"a");
				fprintf(fichier,message);
				fclose(fichier);
			}
	}
void ap_unicast_message(char* message)
	{
		FILE* 	fichier;
		char	str[200];

		sprintf(str,"results/%sdebug_ap_unicast%s.txt", prefix_results_file , suffix_results_file);			
				if (BB_FLOODING_DEBUG)
			{
				fichier = fopen(str,"a");
				fprintf(fichier,message);
				fclose(fichier);
			}
	}
void print_general_infos()
	{
		char	msg[200];

		sprintf(msg,"\n\n----------------- General Infos of %d ---------------------\n\n",my_address);
		cluster_message(msg);
		
		//Energy (Energy Initial/Final, Sleeping Time...)
		sprintf(msg,"Initial energy : %f \n",my_energy.initial_value);
		cluster_message(msg);
		if (is_DEAD.bool)
			sprintf(msg,"is DEAD at %f \n",is_DEAD.time);
		else
			sprintf(msg,"already alive, energy left : %f\n",my_energy.value);
		cluster_message(msg);
		sprintf(msg,"Sleeping Time : %f \n",is_sleeping.cumul_sleeping_time);
		cluster_message(msg);
		
		//Mobility Metric
		sprintf(msg,"mobility=%d\n",my_weight.mobility);
		cluster_message(msg);		
		
		cluster_message("\n----------------------------------------------------------------\n\n");		

	}


/////////////////////////////////////////////
//
//					NEIGHBORS
//
/////////////////////////////////////////////




void print_neighbour_table()
	{
		neigh_cell*	ptr;
		char		msg[600];
	
		sprintf(msg,"\n\n----------------- Neighbours of %d ------------------------\n\n",my_address);
		cluster_message(msg);

		ptr = neighbour_table;
		cluster_message("Id	| hops  |  relay	|   weight	| bidirect	|state|   father	|father_hops|	id_ap	|ap_hops	|cluster_flag|  CH	|  ch_hops	|	ch_timeout	| timeout\n");
		while(ptr!=NULL)
			{
				sprintf(msg,"%d	|   %d   |	%d	|	%d	|	%d", 	ptr->address , ptr->hops , ptr->relay , ptr->weight , ptr->bidirect);
				sprintf(msg,"%s	|  %d" , 							msg, ptr->state);
				sprintf(msg,"%s  |	%d	|	%d	|	%d	|	%d" , 			msg, ptr->father , ptr->father_hops , ptr->id_ap , ptr->ap_hops);
				sprintf(msg,"%s	|	%d	 |	%d	|	%d	|	%f" , 	msg, ptr->cluster_init_flag , ptr->clusterhead , ptr->clusterhead_hops , ptr->clusterhead_timeout);
				sprintf(msg,"%s	| %f\n" , 							msg, ptr->timeout);
				cluster_message(msg);
				ptr=ptr->next;
			}	
		cluster_message("\n----------------------------------------------------------------\n\n");	
		
	}

void print_neighbours_of_neighbours_table(){
	int			i;
	neigh_cell*	ptr;
	neigh_min	*neigh_list;
	char		msg[600];
	
	sprintf(msg,"\n\n------------- Neighbours of Neighbours of %d --------------------\n\n",my_address);
	cluster_message(msg);

	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			sprintf(msg, "%d (d=%d, w=%d, b=%d, t=%f):", ptr->address, ptr->hops, ptr->weight , ptr->bidirect , ptr->timeout);
			cluster_message(msg);
			for(i=0 ; i < op_prg_list_size(ptr->neighbors) ; i++)
				{
					neigh_list = op_prg_list_access(ptr->neighbors , i);
					sprintf(msg , " | %d (w=%d)", neigh_list->address , neigh_list->weight);
					cluster_message(msg);
				}
			cluster_message("\n");
			ptr = ptr->next;
		}	
	cluster_message("\n----------------------------------------------------------------\n\n");	
		
}

/////////////////////////////////////////////
//
//					CDS
//
/////////////////////////////////////////////


void print_cds_candidates()
	{
		candidate*	ptr;
		char		msg[300];
	
		ptr = my_cds.secondary_fathers;
		cluster_message("Id | weight | last_seen | parent\n");
		while(ptr!=NULL)
			{
				sprintf(msg,"%d  |  %d  |  %f  |  %d\n",ptr->address,ptr->weight,ptr->last_seen,ptr->parent);
				cluster_message(msg);
				ptr=ptr->next;
			}	
	}

int print_secondary_fathers()
	{
		char		msg[600];
		int			i;
		int			second_fathers_temp[MAX_NB_NODES];

		//delete older entries (potentially invalid)
		switch (cds_algos_type)
			{
				case THEO_NEW :
				case THEO_NEW2 :
					delete_timeout_cds_candidates(TIMEOUT_AP_HELLO*INTERVALL_AP_HELLO);
				break;
				case THEO_OLD :
					return(0);
				break;
				case WU_LI :
				break;
			}
		
		//print_cds_candidates();
		delete_double_secondary_fathers(my_cds.secondary_fathers,second_fathers_temp);
 		
		//Print secondary fathers
		cluster_message("\nSecondary Fathers :\n");
		sprintf(msg,"");
		i = 0;
		while(second_fathers_temp[i]!=0)
			{
				if (i==0)
					sprintf(msg,"[%d] %d",i+1,second_fathers_temp[i++]);
				else
					sprintf(msg,"%s  |  [%d] %d",msg,i+1,second_fathers_temp[i++]);
			}
		cluster_message(msg);
		cluster_message("\n");

	}

void print_cds_connectors()
	{
		char				msg[200];
		struct_cds_connector *entry;
		int					i;

		//Print CDS - Gateways (timeouts are automatically deleted)
		cluster_message("\nPotential CDS -  Connectors (it must be MY dominatee to be chosen):\n");
		cluster_message("Address	|	Last_Seen		|	ID_AP\n");

		//Prints the content
		for (i=0 ; i < op_prg_list_size(my_cds.cds_connectors_list) ; i++)
			{
				entry = op_prg_list_access(my_cds.cds_connectors_list , i);
			
				sprintf(msg,"%d		|	%f		|	%d\n" , entry->address , entry->timeout , entry->id_ap);
				cluster_message(msg);
			}
		
		cluster_message("\n\n");
		//sprintf(msg,"Nb of Dominatees-cds-connectors : %d\n\n" , count_nb_cds_connectors());
		//cluster_message(msg);
	}

void print_sons(){
		char		msg[1550];
		int			i;
		son			*ptr_son;

		ptr_son = my_cds.sons;
		i=0;
		cluster_message("List of Sons :\n");
		while(ptr_son!=NULL)
			{
				sprintf(msg,"%d   |   ",ptr_son->address);i++;
				cluster_message(msg);
				ptr_son = ptr_son->next;
			}
		cluster_message("\n");
		sprintf(msg,"(%d sons)\n\n",i);
		cluster_message(msg);

}

void print_dominatees(){
		char		msg[1550];
		dominatee	*ptr_dominatee;
		int			i;
		
		ptr_dominatee = my_cds.dominatees;
		i=0;
		cluster_message("List of Dominatees : \n");
		while(ptr_dominatee!=NULL)
			{
				sprintf(msg,"%d   |   ",ptr_dominatee->address);
				cluster_message(msg);
				ptr_dominatee = ptr_dominatee->next;i++;
			}
		cluster_message("\n");
		sprintf(msg,"(%d Dominatees)\n\n",i);
		cluster_message(msg);

}

void print_ap_hellos_table()
	{
		ap_hellos*	ptr;
		char		msg[150];
			
		sprintf(msg,"\n\n-------------------- AP Hellos of %d -------------------\n\n",my_address);
		cluster_message(msg);

		sprintf(msg,"last \"official\" ap-hello=%f\n",my_cds.last_hello_ap_seen);
		cluster_message(msg);
		
		ptr=ap_hellos_table;
		cluster_message("   address	|  last_seen  |   id_ap	|  id_hello\n");
		while(ptr!=NULL)
			{
				sprintf(msg,"	%d	|  %f  |	%d	|  %d\n",ptr->address,ptr->last_seen,ptr->id_ap,ptr->id_hello);
				cluster_message(msg);
				ptr=ptr->next;
			}	
		
		cluster_message("\n----------------------------------------------------------------\n\n");		
}

void print_cds_infos()
	{
		char		msg[550];
		
		
		sprintf(msg,"\n\n----------------------- CDS of %d -------------------------\n\n",my_address);
		cluster_message(msg);

		
		//Our father
		cluster_message("Infos about Father :\n");
		sprintf(msg,"father = %d (%d hops)	|	id_ap = %d (%d hops)   |   relay = %d (timeout : %f)	|   state = %d	|	last_dom_usefull = %f\n\n",my_cds.father , my_cds.father_hops , my_cds.id_ap , my_cds.ap_hops , my_cds.relay , my_cds.relay_timeout , my_cds.state , my_cds.time_dominator_usefull);
		cluster_message(msg);
		
		//Our secondary fathers :
		if (my_cds.state==DOMINATOR)
			print_secondary_fathers();

		//Our CDS-Gateways
		print_cds_connectors();
		
		//Our sons and Dominatees
		print_sons();
		print_dominatees();	
		
		cluster_message("\n----------------------------------------------------------------\n\n");		
	}

/////////////////////////////////////////////
//
//					CLUSTER
//
/////////////////////////////////////////////

void print_cluster_infos()
	{
		char		msg[150];

		sprintf(msg,"\n\n------------------ Cluster infos of %d -----------------\n\n",my_address);
		cluster_message(msg);

		//our infos about clustering
		cluster_message("\n");
		sprintf(msg,"clusterhead=%d  | relay=%d  |  relay_last_seen=%f  |  hops=%d  |  my_clusterhead.construct_cluster=%d	| last_useful=%f\n\n", my_clusterhead.address , my_clusterhead.relay , my_clusterhead.relay_last_seen , my_clusterhead.hops , my_clusterhead.construct_cluster , my_clusterhead.last_time_usefull);
		cluster_message(msg);
		
		cluster_message("\n----------------------------------------------------------------\n\n");		
}



//Global list of clusters
void print_cluster_table()
	{
		cluster_cell*	ptr;
		char		msg[300];	

		sprintf(msg,"\n\n------------------ Cluster Table of %d -----------------\n\n",my_address);
		cluster_message(msg);

		ptr=cluster_table;
		cluster_message("Used uniquely for Cluster Construction :\nId	|hops	|  weight	|   clusterhead	|  timeout\n");
		while(ptr!=NULL)
			{
				sprintf(msg,"%d	| %d	|	%d	|		%d	|  %f\n",ptr->address,ptr->hops,ptr->weight,ptr->clusterhead,ptr->timeout);
				cluster_message(msg);
				ptr=ptr->next;
			}	
		cluster_message("\n");
		
		cluster_message("\n----------------------------------------------------------------\n\n");		
	}

//Prints the global list of cluster adjacency
void print_global_gateways()	{
	cl_neigh_global	*ptr;
	char			msg[300];
	int				i;
		
	sprintf(msg,"\n\n----------------- Cluster Adjacency of %d ------------------------\n\n",my_address);
	cluster_message(msg);

	ptr = cluster_topo;i=0;
	while(ptr!=NULL){	i++;ptr = ptr->next;	}
	sprintf(msg,"Global List of all Cluster Topology (%d) :\n",i);
	cluster_message(msg);
		
	cluster_message("  Cluster1	|  Cluster2	|  Timeout\n");
	ptr = cluster_topo;
	while(ptr!=NULL)
		{
			sprintf(msg,"	%d	|	%d	| %f\n",ptr->cluster1,ptr->cluster2,ptr->last);
			cluster_message(msg);
			ptr = ptr->next;
		}
	cluster_message("\n");
	
	cluster_message("\n----------------------------------------------------------------\n\n");		
}


//List of MY Cluster-Neighbors
void print_cluster_topo()
	{
		list*	ptr;
		char	msg[300];
		int		i;
	
		
		sprintf(msg,"\n\n----------------- Cluster Topo of %d ------------------------\n\n",my_address);
		cluster_message(msg);

		//To know the number of adjacent clusters
		i=0;
		ptr=old_cluster_topo.clusters;
		while(ptr!=NULL)
			{ ptr = ptr->next; i++;	}
		sprintf(msg,"List of local adjacent Clusters (%d):\n",i);
		cluster_message(msg);
		cluster_message("Address	|	Last Seen\n");
		ptr=old_cluster_topo.clusters;
		while(ptr!=NULL)
			{
				sprintf(msg,"  %d		|	%f\n",ptr->addr,ptr->last);
				cluster_message(msg);
				ptr = ptr->next;
			}
		cluster_message("\n");
		
		
		cluster_message("\n----------------------------------------------------------------\n\n");		
}	


/////////////////////////////////////////////
//
//					ACKS
//
/////////////////////////////////////////////


//Prints the table containing all packets that must be acknowledged and eventually retransmitted
void print_acks_pk_table(){
		ack_cell	*ptr;
		int			dest , dest_final , id;
		char		msg[200];
		
		sprintf(msg,"\n\n-------------------- Acks Packets of %d -----------------\n\n",my_address);
		cluster_message(msg);

		cluster_message("RELAY	|	DESTINATION	|	PK_ID	|	Nb Retransmission	|	Time Sent\n");
		ptr = my_acks;
		while(ptr!=NULL)
			{
				//Gathers info from packet
				op_pk_nfd_get(ptr->pk,"DEST_FINAL",&dest_final);
				op_pk_nfd_get(ptr->pk,"DEST",&dest);
				op_pk_nfd_get(ptr->pk,"PK_ID",&id);
				
				//Prints it
				sprintf(msg,"%d	|	%d		|	%d	|		%d		|	%f\n", dest , dest_final , id , ptr->nb_retransmits , ptr->time_sent);
				cluster_message(msg);
				
				//Next Packet to ack
				ptr=ptr->next;				
			}

		cluster_message("\n----------------------------------------------------------------\n\n");		
	}



































//-----------------------------------------------------------------------------------------------
//
//								ACKS     IN      MULTICAST
//
//----------------------------------------------------------------------------------------------

//prints the content of multicast_ack_list
void print_ack_multicast(){
	struct_ack_multicast	*entry;
	int		*node;
	int		i , j;
	char	msg[600];

	sprintf(msg , "\n---------------- ACK MULTICAST LIST at %f --------------\n\n", op_sim_time());
	cluster_message(msg);
	cluster_message("	PK_ID	|	NB_RETRY	|	TIMEOUT	|	DESTINATIONS\n\n");
	
	for (i=0; i < op_prg_list_size(ack_multicast_list) ; i++)
		{
			entry = op_prg_list_access(ack_multicast_list , i);
			sprintf(msg , "	%d	|		%d	|	%f" , entry->pk_id , entry->nb_retry , entry->timeout);
						
			for (j= 0; j < op_prg_list_size(entry->dest_list) ; j++)
				{
					node = op_prg_list_access(entry->dest_list , j);
					sprintf(msg , "%s	|	%d" , msg , *node);
				}
			sprintf(msg , "%s\n" , msg);
			cluster_message(msg);
		}
	cluster_message("\n--------------------------------------------------------------\n\n");
}

//src retransmits the pk pk_id, it received the pk, no retransmission is required
void delete_ack_multicast(int src , int pk_id){
	struct_ack_multicast	*entry;
	int		*node;
	int		i , j;
	char	msg[300];
	
	if (DEBUG>LOW)
		{
			sprintf(msg, "		MULTI-DEL: %d tries to delete ack toward %d pk_id %d\n", my_address , src , pk_id);
			bb_flooding_message(msg);
		}
	
	
	for(i=0 ; i < op_prg_list_size(ack_multicast_list) ; i++)
		{
			entry = op_prg_list_access (ack_multicast_list , i);

			//Entry for this pk_id
			if (entry->pk_id == pk_id)
				{
					for (j=0; j < op_prg_list_size(entry->dest_list) ; j++)
						{						
							node = op_prg_list_access(entry->dest_list , j);
							
							//Entry for this pk_id + special dest
							if (*node == src)
								{
									if (DEBUG>LOW)
										{
											sprintf(msg , "		MULTI-DEL: %d registers an ack from %d at %f\n", my_address , src , op_sim_time());
											bb_flooding_message(msg);
											cluster_message(msg);
										}
									//Removes this dest
									op_prg_list_remove(entry->dest_list , j);
									free(node);
									
									//No more destinations for this pk_id -> remove the whole entry
									if (op_prg_list_size(entry->dest_list) == 0)
										{
											op_prg_mem_free(entry->dest_list);
											op_prg_list_remove(ack_multicast_list , i);
											free(entry);
										}
									
									//No more thing todo
									return;
								}						
						}				
				}
		}
}

//Deletes/Retransmits all entries with a too low timeout in multicast_ack_table
void delete_timeouted_in_ack_multicast(int arg, int code){
	struct_ack_multicast	*entry;
	double		older_entry = -1;
	int			*node;
	int			i , j;
	char		msg[150];
	Boolean		is_pk_retransmitted;

	if (DEBUG>LOW)
		{
			sprintf(msg , "RET: multicast_ack verification in %d at %f\n", my_address , op_sim_time()); 
			cluster_message(msg);
		}
	
	for (i=op_prg_list_size(ack_multicast_list)-1 ; i >=0 ; i--)
		{
			entry = op_prg_list_access(ack_multicast_list , i);
			
			//This entry is timeouted
			if ((entry->timeout <= op_sim_time()) && (entry->nb_retry < MAX_NB_RETRY_ACK_MULTICAST))
				{
					//Still a valid father / son in the dest_list ?
					is_pk_retransmitted = OPC_FALSE;
					for (j=op_prg_list_size(entry->dest_list)-1 ; (j>=0) && (!is_pk_retransmitted) ; j--)
						{
							node = op_prg_list_access(entry->dest_list , j);
							
							//Is this node still a valid father or son ?
							//-> I delete this particular destination
							if (!is_my_son(*node) && (my_cds.father != *node) && (my_cds.father != my_address))
								{
									if (DEBUG>LOW)
										{
											sprintf(msg , "MULTI-RET: %d is no more the son or father of %d at %f, it is deleted in multicast_ack_list\n",*node , my_address , op_sim_time());
											bb_flooding_message(msg);
											cluster_message(msg);
										}
									op_prg_list_remove(entry->dest_list , j);
									free(node);
								}
							//->Or I retransmit the corresponding packet
							else
								{
									if (DEBUG>LOW)
										{
											sprintf(msg , "MULTI-RET: %d retransmits a bb pk at %f at least for %d (nb retry = %d)\n", my_address , op_sim_time() , *node , entry->nb_retry);
											bb_flooding_message(msg);
											cluster_message(msg);
										}									
								
									entry->nb_retry++;
									entry->timeout = op_sim_time() + TIMEOUT_ACK_MULTICAST;
									pk_retransmit_delayed(op_pk_copy(entry->pk) , op_dist_uniform(0.005));
									is_pk_retransmitted = OPC_TRUE;
								}
						}
				}
			//Too many retransmissions -> Cell deletion
			if ((entry->nb_retry >= MAX_NB_RETRY_ACK_MULTICAST) || (op_prg_list_size(entry->dest_list) ==0))
				{
					//Still a valid father / son in the dest_list ?
					for (j=op_prg_list_size(entry->dest_list)-1 ; j>=0 ; j--)
						{
							node = op_prg_list_remove(entry->dest_list , j);
							free(node);
						}
					op_pk_destroy(entry->pk);					
					op_prg_list_remove(ack_multicast_list, i);
					free(entry);	
				}
			//Next verification
			else if ((older_entry >= entry->timeout) || (older_entry == -1))
				older_entry = entry->timeout;
		}
	
	if (older_entry != -1)
		op_intrpt_schedule_call(older_entry , -1 , delete_timeouted_in_ack_multicast , -1);
}



//Adds all sons and father to ack this packet
void add_ack_multicast(Packet* pkptr){
	//Control
	struct_ack_multicast	*entry;
	int		pk_id;
	char	msg[500];
	//address to ack
	int		*node;
	//Sons
	son		*ptr;
	//Cds-connectors
//	char	field_name[30];
	
	//Empty dest_list -> Nothing to do
	if ((my_cds.father == 0) || (my_cds.father == -1) || (my_cds.sons == NULL))
		return;
	
	if (op_prg_list_size(ack_multicast_list) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_ACK_MULTICAST , -1 , delete_timeouted_in_ack_multicast , -1);
	
	//Info
	op_pk_nfd_get(pkptr , "PK_ID", &pk_id);
	
	if (DEBUG>LOW)
		sprintf(msg , "		MULTI-ACK: %d adds a pk (pk_id %d) to ack by ", my_address , pk_id);
	
	//New cell
	entry = op_prg_mem_alloc(sizeof(struct_ack_multicast));
	entry->pk_id	= pk_id;
	entry->nb_retry	= 0;
	entry->timeout	= op_sim_time() + TIMEOUT_ACK_MULTICAST;
	entry->pk		= op_pk_copy(pkptr);
	
	//List initalization
	entry->dest_list = op_prg_list_create();
	
	//----------------------
	//	The sons to add
	//----------------------
	ptr = my_cds.sons;
	while (ptr != NULL)
		{
			node = op_prg_mem_alloc(sizeof(int));
			*node = ptr->address;
			op_prg_list_insert(entry->dest_list , node, OPC_LISTPOS_TAIL);
			if (DEBUG>LOW)
				sprintf(msg , "%s %d(SON)", msg , *node);
			
			ptr = ptr->next;
		}
	//----------------------
	//	The father to add
	//----------------------
	if ((my_cds.father != 0) && (my_cds.father != -1) && (my_cds.father != my_address))
		{
			node = op_prg_mem_alloc(sizeof(int));
			*node = my_cds.father;
			op_prg_list_insert(entry->dest_list , node, OPC_LISTPOS_TAIL);
			if (DEBUG>LOW)
				sprintf(msg , "%s %d(FATHER)", msg , *node , op_sim_time());
		}
	//----------------------
	//	The cds-connectors
	//----------------------
/*	for (i=1; i < nb_aps ; i++)
		{
			sprintf(field_name , "DEST%d" , i);
			if (op_pk_nfd_is_set(pkptr , field_name))
				{
					node = op_prg_mem_alloc(sizeof(int));
					op_pk_nfd_get(pkptr , field_name, node);
					op_prg_list_insert(entry->dest_list , node, OPC_LISTPOS_TAIL);
					if (DEBUG>LOW)
						sprintf(msg , "%s %d(CDS-CONNECTOR)", msg , *node , op_sim_time());				
				}	
		}	
*/	
	//DEBUG
	if (DEBUG>LOW)
		{
			sprintf(msg , "%s at %f\n", msg , op_sim_time());
			bb_flooding_message(msg);
			cluster_message(msg);
		}
	
	op_prg_list_insert(ack_multicast_list , entry, OPC_LISTPOS_TAIL);
}









//-----------------------------------------------------------------------------------------------
//
//								CDS   CONNECTORS   MANAGEMENT
//
//----------------------------------------------------------------------------------------------
//---------------  LIST MANAGEMENTS ------------

//Is this elem already present in a list of int ?
Boolean is_present_in_list(List* ll , int value){
	int		i;
	int		*el;
	
	for(i=0 ; i < op_prg_list_size(ll) ; i++)
		{
			el = op_prg_list_access(ll , i);
			if (*el == value)
				return(OPC_TRUE);
		}
	return(OPC_FALSE);
}

//Get the list of my ap_neigh
List *get_ap_neigh(){
	neigh_cell	*ptr;
	List		*ap_neigh_list;
	int			*elem;
	Boolean		is_valid_ap;
	
	//Initialization
	ap_neigh_list = op_prg_list_create();
	//ap_neigh_list = op_prg_mem_alloc (sizeof(List));

	//Adds all unique ap_neigh
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			is_valid_ap = (ptr->id_ap != -1) && (ptr->id_ap != 0) && (my_cds.id_ap != 0) && (my_cds.id_ap != -1);
			if (is_valid_ap && (ptr->id_ap != my_cds.id_ap) && (ptr->hops == 1) && (ptr->bidirect) && (!is_present_in_list(ap_neigh_list , ptr->id_ap)))
				{
					elem = (int*) op_prg_mem_alloc(sizeof(int));
					*elem = ptr->id_ap;
					op_prg_list_insert(ap_neigh_list , elem , OPC_LISTPOS_TAIL);
				}
			ptr = ptr->next;
		}

	//Result
	return(ap_neigh_list);
}

//Delete a node in the list
void delete_cds_connector(int address){
	int						i;
	struct_cds_connector	*elem;
	
	for(i = op_prg_list_size(my_cds.cds_connectors_list)-1 ; i>=0 ; i--)
		{
			elem = op_prg_list_access(my_cds.cds_connectors_list , i);
			if (elem->address == address)
				{
					op_prg_list_remove(my_cds.cds_connectors_list , i);
					free(elem);
				}
		}
}

//Delete all timeouts in cds_connectors_list
void delete_timeouted_cds_connectors(int arg , int code){
	int						i;
	struct_cds_connector	*elem;
	double					older_entry = -1;
	
	for(i = op_prg_list_size(my_cds.cds_connectors_list)-1 ; i>=0 ; i--)
		{
			elem = op_prg_list_access(my_cds.cds_connectors_list , i);
			if (elem->timeout >= op_sim_time())
				{
					op_prg_list_remove(my_cds.cds_connectors_list , i);
					free(elem);
				}
			else if ((older_entry >= elem->timeout) || (older_entry == -1))
				older_entry = elem->timeout;				
		}
	
	//Next Verification
	if(older_entry != -1)
		op_intrpt_schedule_call(older_entry , -1 , delete_timeouted_cds_connectors , -1);
}

//Deletes all cds-connectors associated to a particular node
void delete_all_cds_connectors_for(int addr){
	int						i;
	struct_cds_connector	*elem;
	
	for(i = op_prg_list_size(my_cds.cds_connectors_list)-1 ; i>=0 ; i--)
		{
			elem = op_prg_list_access(my_cds.cds_connectors_list , i);
			if (elem->address == addr)
				{
					op_prg_list_remove(my_cds.cds_connectors_list , i);
					free(elem);
				}
		}	
}

//Adds a cds-connector (it is necessary dominatee, else we didn't inscribe the node in this list, extracted from hellos)
void add_cds_connector (int addr, int id_ap){
	struct_cds_connector	*entry;
	char					msg[150];
	
	//Next Timeout verification
	if (op_prg_list_size(my_cds.cds_connectors_list) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_HELLO * INTERVALL_HELLO , -1 , delete_timeouted_cds_connectors , -1);
	
	//Entry not found, must add it
	entry = (struct struct_cds_connector*) op_prg_mem_alloc (sizeof(struct_cds_connector));
	
	entry->address 	= addr;
	entry->id_ap	= id_ap;
	entry->state	= DOMINATEE;
	entry->timeout	= op_sim_time() + TIMEOUT_HELLO * INTERVALL_HELLO;

	op_prg_list_insert(my_cds.cds_connectors_list , entry , OPC_LISTPOS_TAIL);

	if (DEBUG>MAX)
		{
			sprintf(msg , "CDS-CONNECTOR : I add the connector %d to ap %d at %f\n", entry->address , entry->id_ap , entry->timeout);
			cluster_message(msg);
		}
}

//Is id_ap already in the list of cds-connectors ?
Boolean is_this_ap_in_cds_connector_list(List* list , int id_ap){
	struct_cds_connector	*entry;
	int						i;
	
	//For each registered ap-dominatee-neigh
	for(i=0; i < op_prg_list_size(list) ; i++)
		{
			entry = op_prg_list_access(list , i);
			if (entry->id_ap == id_ap)
				return(OPC_TRUE);
		}
	
	return(OPC_FALSE);
}

//Adds a cds-connector in the list
void copy_entry_in_unique_cds_connectors_list(List *list , struct_cds_connector *entry){
	struct_cds_connector	*entry_to_add;

	//Memory allocation
	entry_to_add = op_prg_mem_alloc(sizeof(struct_cds_connector));
	
	//Data
	entry_to_add->address	= entry->address;
	entry_to_add->id_ap		= entry->id_ap;
	entry_to_add->timeout	= entry->timeout;
	entry_to_add->state		= entry->state;
	
	//Inserts it
	op_prg_list_insert(list , entry_to_add , OPC_LISTPOS_TAIL);
}

//Adds a cds-connector in the list
void add_entry_in_unique_cds_connectors_list(List *list , int address , int state , int id_ap , double timeout){
	struct_cds_connector	*entry_to_add;

	//Memory allocation
	entry_to_add = op_prg_mem_alloc(sizeof(struct_cds_connector));
	
	//Data
	entry_to_add->address	= address;
	entry_to_add->id_ap		= id_ap;
	entry_to_add->timeout	= timeout;
	entry_to_add->state		= state;
	
	//Inserts it
	op_prg_list_insert(list , entry_to_add , OPC_LISTPOS_TAIL);
}

//Returns the list of my cds-connectors: they are connectors for DIFFERENT backbones (no doubles)
List* get_my_unique_cds_connectors(){
	struct_cds_connector	*entry;
	int						i;
	List					*unique_cds_connectors_list;
	neigh_cell				*ptr;
	Boolean					is_valid_ap;
	
	//List initialization
	unique_cds_connectors_list = op_prg_list_create();
	//unique_cds_connectors_list = op_prg_mem_alloc (sizeof(List));
	
	//All dominators, 1-Neighbors
	ptr = neighbour_table;
	while(ptr != NULL)		
		{
			is_valid_ap = (ptr->id_ap != 0) && (ptr->id_ap != -1) && (my_cds.id_ap != 0) && (my_cds.id_ap != -1);
			if (is_valid_ap && (ptr->state == DOMINATOR) && (ptr->hops == 1) && (ptr->bidirect) && (ptr->id_ap != my_cds.id_ap) && (!is_this_ap_in_cds_connector_list(unique_cds_connectors_list , ptr->id_ap)))
				add_entry_in_unique_cds_connectors_list(unique_cds_connectors_list , ptr->address , ptr->state , ptr->id_ap , ptr->timeout);				
			ptr = ptr->next;
		}
	
	//For each registered dominatee which has a not null ap-neigh
	for(i=0 ; i < op_prg_list_size(my_cds.cds_connectors_list) ; i++)
		{
			entry = op_prg_list_access(my_cds.cds_connectors_list , i);
			if ((is_my_dominatee(entry->address)) && (!is_this_ap_in_cds_connector_list(unique_cds_connectors_list , entry->id_ap)) && (entry->timeout > op_sim_time()))
				copy_entry_in_unique_cds_connectors_list(unique_cds_connectors_list , entry);			
		}
	
	//All dominatees, 1-neighbors, which are connected to a different AP
	ptr = neighbour_table;
	while(ptr != NULL)		
		{
			is_valid_ap = (ptr->id_ap != 0) && (ptr->id_ap != -1) && (my_cds.id_ap != 0) && (my_cds.id_ap != -1);
			if (is_valid_ap && (ptr->state == DOMINATEE) && (ptr->hops == 1) && (ptr->bidirect) && (ptr->id_ap != my_cds.id_ap) && (!is_this_ap_in_cds_connector_list(unique_cds_connectors_list , ptr->id_ap)))
				add_entry_in_unique_cds_connectors_list(unique_cds_connectors_list , ptr->address , ptr->state , ptr->id_ap , ptr->timeout);				
			ptr = ptr->next;
		}
	
	
	
	
	return(unique_cds_connectors_list);
}


//Deletes a list of unique_cds_connectors_list
void delete_unique_cds_connectors_list(List*  list){
	struct_cds_connector	*entry;
	int						i;
	
	for(i=op_prg_list_size(list)-1 ; i>=0 ; i--)
		{
			entry = op_prg_list_remove(list , i);
			free(entry);
		}
}

//Returns the nb of unique cds-connectors (for me)
int count_nb_cds_connectors(){
	struct_cds_connector	*entry;
	List* 	unique_cds_connectors_list;
	int		nb = 0;
	int		i;
	
	//Format the list and computes the result
	unique_cds_connectors_list = get_my_unique_cds_connectors();
	
	//Empty the list
	for(i=op_prg_list_size(unique_cds_connectors_list)-1 ; i>=0 ; i--)
		{
			entry = op_prg_list_remove(unique_cds_connectors_list , i);
			if (entry->state == DOMINATEE)
				nb++;
			free(entry);
		}
	op_prg_mem_free(unique_cds_connectors_list);
	
	//Result
	return(nb);
}


//Returns the nb of dominatees in "list"
int count_nb_dominatees_in_list(List* list){
	struct_cds_connector	*entry;
	int		nb = 0;
	int		i;
	
	//Empty the list
	for(i=op_prg_list_size(list)-1 ; i>=0 ; i--)
		{
			entry = op_prg_list_access(list , i);
			if (entry->state == DOMINATEE)
				nb++;
			free(entry);
		}
	
	//Result
	return(nb);
}



//------------------  HELLOS -------------------


//Fills an hello pk with the ap_neigh
void advertise_ap_neigh(Packet* pkptr){
	List*	ap_neigh_list;
	char	field_name[20];
	int*	elem;
	int		i , j;
	char	msg[200];

	//Gets the list of ap I can hear in my 1-neighborhood
	if (my_cds.state == DOMINATEE)
		ap_neigh_list = get_ap_neigh();	
	//I am not dominatee, my ap_neigh don't interess anyone
	else
		{
			ap_neigh_list = op_prg_list_create();
			//ap_neigh_list = op_prg_mem_alloc (sizeof(List));
		}
	//Fills the pk
	if (op_prg_list_size(ap_neigh_list) > MAX_AP_NEIGH_IN_HELLO)
		op_sim_end("We don't have enough fields in helo packets" , "to place all the ap which are 1-neighbors", "Please increase MAX_AP_NEIGH_IN_HELLO" , "");
	
	if (DEBUG>MAX)
		{
			sprintf(msg , "HELLO: I set the ap_neigh fields in my hello packet at %f\n", op_sim_time());
			cluster_message(msg);
		}
	for (i=0; i < op_prg_list_size(ap_neigh_list) ; i++)
		{
			elem = op_prg_list_access(ap_neigh_list , i);

			if (DEBUG>MAX)
				{
					sprintf(msg, "	->Ap_neigh_%d: %d\n", i , *elem);
					cluster_message(msg);
				}
			
			sprintf(field_name, "AP_NEIGH_%d" , i+1);
			op_pk_nfd_set(pkptr , field_name , *elem);
		}
	
	//Delete useless fields
	for(j=i ; j <= MAX_AP_NEIGH_IN_HELLO-1 ; j++)
		{
			sprintf(field_name, "AP_NEIGH_%d" , i+1);
			if (op_pk_nfd_is_set(pkptr , field_name))
				op_pk_nfd_strip(pkptr , field_name);
		}
	
	//End (free memory)
	for (i= op_prg_list_size(ap_neigh_list)-1 ; i>=0 ; i--)
		{	
			elem = op_prg_list_access(ap_neigh_list , i);
			op_prg_list_remove(ap_neigh_list , i);
			free(elem);
		}
	op_prg_mem_free(ap_neigh_list);
}

//Extracts the ap neigh from an hello pk for a neighbor
void register_ap_neigh(Packet* pkptr){
	char	field_name[20];
	int		id_ap;
	int		address_src;
	int		state;
	int		i;

	//Info
	op_pk_nfd_get(pkptr , "SRC" , &address_src);
	op_pk_nfd_get(pkptr , "STATE" , &state);
	
	
	if (state == DOMINATEE)
		{
			sprintf(field_name,"AP_NEIGH_1");
			
			//Empty obsolete list (we recieved newer information
			delete_cds_connector(address_src);
			
			//For each ap_neigh declared
			for(i=1 ; (i <= MAX_AP_NEIGH_IN_HELLO) && (op_pk_nfd_is_set(pkptr,field_name)) ; i++)
				{
					//Gets the ap for which it is neighbor
					op_pk_nfd_get(pkptr , field_name , &id_ap);

					//Adds the source as connector for ap_neigh
					add_cds_connector (address_src , id_ap);
			
					//Next field
					sprintf(field_name , "AP_NEIGH_%d" , i);
				}
		}
	//delete all cds-connectors associated to a particular node
	else
		delete_all_cds_connectors_for(address_src);
}






//-----------------------------------------------------------------------------------------------
//
//								Backbone Multicasts
//
//------------------------------------------------------------------------------------------------

//Relays a packet toward the dest_final (a cds-connector)
void relay_to_cds_connector(Packet* pk_src , int dest , int dest_final , int id_ap){
	Packet*	pk_dest;
	int		i;
	char	str[20];
	char	msg[300];
	
	pk_dest = op_pk_copy(pk_src);
	
	//Searches the relay towards the cds-connector (=dest_final)
	dest = get_relay_to_general_destination(dest_final);
	
	//Set some fields
	op_pk_nfd_set(pk_dest,"RELAY",		my_address);
	op_pk_nfd_set(pk_dest,"DEST",		dest);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",	dest_final);
	op_pk_nfd_set(pk_dest,"ID_AP",		id_ap);

	//resets unused fields
	for (i=1 ; i<= MAX_NB_APS ; i++)
		{
			sprintf(str,"DEST%d",i);
			if (op_pk_nfd_is_set(pk_dest,str))
				{
					op_pk_nfd_strip(pk_dest,str);
					sprintf(str,"DEST_FINAL%d",i);
					op_pk_nfd_strip(pk_dest,str);
					sprintf(str,"ID_AP%d",i);
					op_pk_nfd_strip(pk_dest,str);
				}
		}	
	if (DEBUG>LOW)
		{
			sprintf(msg , "	BB (gw) : %d relays to %d via %d (relay to gateway)\n", my_address , dest_final , dest);
			bb_flooding_message(msg);
		}
	
	//Send it
	if (ACK_FOR_BB_MULTICAST)
		add_ack_pk(pk_dest);
	pk_send_delayed(pk_dest , op_dist_uniform(0.005));
}

//returns the address of a neighbor toward the AP id_ap
int get_neighbor_with_id_ap(int id_ap){
	neigh_cell*	ptr;
	
	ptr = neighbour_table;
	while(ptr!=NULL)
		{
			if (ptr->id_ap == id_ap)
				return(ptr->address);		
			ptr = ptr->next;
		}
	
	return(-1);
}

//Relays a packet to a neighbor which has the required id_ap
void relay_to_ap_neighbor(Packet* pk_src , int dest , int dest_final , int id_ap){
	Packet*	pk_dest;
	int		i;
	char	str[20];
	char	msg[300];

	pk_dest = op_pk_copy(pk_src);
	
	//Searches the relay towards the id_ap
	dest 		= get_neighbor_with_id_ap(id_ap);
	dest_final 	= dest;
	
	//Set some fields
	op_pk_nfd_set(pk_dest,"RELAY",		my_address);
	op_pk_nfd_set(pk_dest,"DEST",		dest);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",	dest_final);
	op_pk_nfd_set(pk_dest,"ID_AP",		id_ap);

	//resets unused fields
	for (i=1;i<=MAX_NB_APS;i++)
		{
			sprintf(str,"DEST%d",i);
			if (op_pk_nfd_is_set(pk_dest,str))
				{
					op_pk_nfd_strip(pk_dest , str);
					sprintf(str,"DEST_FINAL%d",i);
					op_pk_nfd_strip(pk_dest , str);
					sprintf(str,"ID_AP%d",i);
					op_pk_nfd_strip(pk_dest , str);
				}
		}	

	if (DEBUG>LOW)
		{
			sprintf(msg , "	BB (ap-neigh) : %d relays to %d via %d (relay to ap neighbor)\n" , my_address , dest_final , dest);
			bb_flooding_message(msg);
		}
	
	//Send it
	if (ACK_FOR_BB_MULTICAST)
		add_ack_pk(pk_dest);
	pk_send(pk_dest);
}

//Relays the packet toward my ap, i.e. toward my dominator
void relay_to_my_ap(Packet* pk_src , int dest , int dest_final , int id_ap){
	Packet*	pk_dest;
	int		i;
	char	str[20];
	char	msg[300];

	pk_dest = op_pk_copy(pk_src);
	
	//Searches the relay towards the id_ap
	dest_final	= my_cds.father;
	dest 		= my_cds.relay;
	
	//Set some fields
	op_pk_nfd_set(pk_dest,"RELAY",		my_address);
	op_pk_nfd_set(pk_dest,"DEST",		dest);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",	my_cds.father);
	op_pk_nfd_set(pk_dest,"ID_AP",		id_ap);

	//resets unused fields
	for (i=1;i<=MAX_NB_APS;i++)
		{
			sprintf(str,"DEST%d",i);
			if (op_pk_nfd_is_set(pk_dest,str))
				{
					op_pk_nfd_strip(pk_dest,str);
					sprintf(str,"DEST_FINAL%d",i);
					op_pk_nfd_strip(pk_dest,str);
					sprintf(str,"ID_AP%d",i);
					op_pk_nfd_strip(pk_dest,str);
				}
		}	
	if (DEBUG>LOW)
		{
			sprintf(msg , "	BB (dom) : %d relays to %d via %d (relay to dominator)\n", my_address , dest_final , dest);
			bb_flooding_message(msg);
		}
	
	//Send it
	if (ACK_FOR_BB_MULTICAST)
		add_ack_pk(pk_dest);
	pk_send(pk_dest);
}


//Sends a pk to other backbone neighbors + gateways to other backbone with different AP
void send_pk_to_bb_and_gws(Packet* pk_src){
	//control
	int					i;
	char				field_name[20];
	char				msg[300];
	//pkts
	int					pk_id;
	int					pk_type;
	Packet*				pk_dest;
	//addresses info
	int					address_relay;
	int					dest;
	//cds connectors
	int					field_nb;
	List*				unique_cds_connectors_list;
	struct_cds_connector *entry;
	
	//Pk to forward
	op_pk_nfd_get(pk_src , "PK_ID", 		&pk_id);
	op_pk_nfd_get(pk_src , "RELAY", 		&address_relay);
	op_pk_nfd_get(pk_src , "OPTION_TYPE",	&pk_type);
	pk_dest = op_pk_copy(pk_src);
	
	//First Destination : my cds-neighbors
	op_pk_nfd_set(pk_dest,"RELAY",		my_address);
	op_pk_nfd_set(pk_dest,"ID_AP",		my_cds.id_ap);
		
	//DEBUG
	if (DEBUG>LOW)
		{
			sprintf(msg , "	BB (DOM) : %d forwards the pk\n", my_address);
			bb_flooding_message(msg);
		}
	
	//If me must send pk through cds-connectors
	if (pk_type == BACKBONE_PK_TYPE)
		{
			//Dests
			op_pk_nfd_set(pk_dest,"DEST",		ADDR_MULTICAST_BACKBONE);
			op_pk_nfd_set(pk_dest,"DEST_FINAL",	ADDR_MULTICAST_BACKBONE);
		}
	else if (pk_type == BACKBONE_WITH_CONNECT_PK_TYPE)
		{
			//Dests
			op_pk_nfd_set(pk_dest,"DEST",		ADDR_MULTICAST_BACKBONE_WITH_CONNECT);
			op_pk_nfd_set(pk_dest,"DEST_FINAL",	ADDR_MULTICAST_BACKBONE_WITH_CONNECT);

			
			//All my cds-connectors (toward other different backbone
			unique_cds_connectors_list = get_my_unique_cds_connectors ();

			if (count_nb_dominatees_in_list(unique_cds_connectors_list) > MAX_NB_APS)
				op_sim_end("In the 'function send_pk_to_bb_and_gws',"," we don't have enough place to set all our cds-connectors" , "Please increase the number of fields in the pk" , "and the associated constant in the process");
			
			//For each cds-connector
			field_nb = 1;
			for(i=0 ; i < op_prg_list_size(unique_cds_connectors_list) ; i++)
				{
					entry = op_prg_list_access(unique_cds_connectors_list , i);
								
					//We only send explicit packets for dominatees
					if (entry->state == DOMINATEE)
						{
							//The dominatee-gateway
							sprintf(field_name , "DEST_FINAL%d" , field_nb);
							op_pk_nfd_set(pk_dest , field_name , entry->address);
					
							//The associated id_ap
							sprintf(field_name , "ID_AP%d" , field_nb);
							op_pk_nfd_set(pk_dest , field_name , entry->id_ap);
					
							//The relay toward my dominatee-gateway
							sprintf(field_name , "DEST%d" , field_nb);
							dest = get_relay_to_general_destination(entry->address);
							op_pk_nfd_set(pk_dest , field_name , dest);
					
							if (DEBUG>LOW)
								{
									sprintf(msg , "		BB (BB) : gw %d (ap=%d) via %d\n", entry->address , entry->id_ap ,dest);
									bb_flooding_message(msg);
								}
							
							//active ack for cds-connectors
							if (ACK_FOR_BB_MULTICAST)
								add_ack_pk_gws(pk_dest , dest);

							//nb efficient cds-connectors
							field_nb++;
						}
				}
			
			//erases all infos in original packet
			for (i = field_nb ; i < MAX_NB_APS ; i++)
				{		
					sprintf(field_name , "DEST%d" , i+1);
					if (op_pk_nfd_is_set(pk_dest , field_name))
						{
							op_pk_nfd_strip(pk_dest , field_name);
							sprintf(field_name , "DEST_FINAL%d" , i+1);
							op_pk_nfd_strip(pk_dest , field_name);
							sprintf(field_name , "ID_AP%d" , i+1);
							op_pk_nfd_strip(pk_dest , field_name);
						}
				}
			
			//Free memory
			delete_unique_cds_connectors_list(unique_cds_connectors_list);		
		}
	
	//Sends it
	add_ack_multicast(pk_dest);
	delete_ack_multicast(address_relay , pk_id);	
	pk_send_delayed (pk_dest , op_dist_uniform(0.005));
}




//Creates a backbone multicast packet
void bb_multicast_generate(int arg , int code){
	Packet	*pkptr;
	int		i;
	char	str[20];
	char	msg[200];
	int		address_dest;
	
	//----------------------------------------
	// TYPE OF FLOODING w/o interconnections
	//----------------------------------------
	//address_dest = ADDR_MULTICAST_BACKBONE;
	address_dest = ADDR_MULTICAST_BACKBONE_WITH_CONNECT;
	
	//Sets this packet as already seen (I sent it)
	add_address_id_couple(my_address , current_id);
	
	//The list of actual dominators : the nodes which must receive this packet
	if (current_bb_flooding_id >= MAX_BB_FLOODING)
		op_sim_end("We have too many bb floodings to treat the statistics", "please increase the value of MAX_BB_FLOODING","in the header-block of the cdcl process","");
	for(i=0; i<nb_total ; i++)
		stats_bb_flooding[current_bb_flooding_id].is_dominator[i] = (stats_state[i] == DOMINATOR);
	stats_bb_flooding [current_bb_flooding_id].is_dominator [my_stat_id] 	= (my_cds.state == DOMINATOR);
	stats_bb_flooding [current_bb_flooding_id].is_rcvd		[my_stat_id] 	= OPC_TRUE;
	stats_bb_flooding [current_bb_flooding_id].time_emission = op_sim_time();
	
	//Debug Infos
	if (DEBUG>LOW)
		{
			sprintf(msg,"\n\n\n\nBB (BEGIN) : %d sends a bb flooding with stat_id %d at %f\n" , my_address , current_bb_flooding_id , op_sim_time());
			bb_flooding_message(msg);
			printf(msg);
		}

	//Prepare the packet
	pkptr = op_pk_create_fmt("cdcl_bb_multicast");
	op_pk_nfd_set(pkptr,"SRC",			my_address);
	op_pk_nfd_set(pkptr,"RELAY",		my_address);
	op_pk_nfd_set(pkptr,"ID_AP",		my_cds.id_ap);
	op_pk_nfd_set(pkptr,"PK_ID",		current_id++);
	op_pk_nfd_set(pkptr,"STAT_ID",		current_bb_flooding_id++);
	op_pk_nfd_set(pkptr,"TTL",			1);
	if (address_dest == ADDR_MULTICAST_BACKBONE)
		op_pk_nfd_set(pkptr,"OPTION_TYPE",	BACKBONE_PK_TYPE);
	else
		op_pk_nfd_set(pkptr,"OPTION_TYPE",	BACKBONE_WITH_CONNECT_PK_TYPE);
	
	//erases all infos in original packet
	for (i=1;i <= MAX_NB_APS;i++)
		{
			sprintf(str,"DEST%d",i);
			if (op_pk_nfd_is_set(pkptr,str))
				{
					op_pk_nfd_strip(pkptr,str);
					sprintf(str,"DEST_FINAL%d",i);
					op_pk_nfd_strip(pkptr,str);
					sprintf(str,"ID_AP%d",i);
					op_pk_nfd_strip(pkptr,str);
				}
		}

	//DMOINATOR -> BB + CDS-CONNECTORS (dest & dest_final determined further)
	if (my_cds.state == DOMINATOR)
		send_pk_to_bb_and_gws(pkptr);
	//DOMINATEE -> toward BB
	else
		{
			op_pk_nfd_set(pkptr,"DEST",	my_cds.relay);		
			relay_to_my_ap(pkptr , my_cds.relay , my_cds.father , my_cds.id_ap);
		}	
	
	//Destroys the pk because the previous function, copies the packet before forwarding it
	op_pk_destroy(pkptr);
		
	//For the next BB Flooding
	op_intrpt_schedule_call(op_sim_time() + INTERVALL_BB_FLOODING , -1 , bb_multicast_generate , -1);
}





//Creates an ap-unicast packet
void ap_unicast_generate(){
	Packet	*pkptr;
	char	msg[200];
	int		network_id;
	int		node_remote_id;
	int		process_remote_id;
				
	if (DEBUG>LOW)
		{
			sprintf(msg , "!!!!!!!!!!%d sent a ap_unicast pk to %d toward its ap %d at %f !!!!!!!!!!!!!!!\n", my_address , my_cds.relay , my_cds.id_ap , op_sim_time());
			ap_unicast_message(msg);
		}
	
	//Prepare the packet
	pkptr = op_pk_create_fmt("cdcl_ap_unicast");
	op_pk_nfd_set(pkptr,"SRC",			my_address);
	op_pk_nfd_set(pkptr,"RELAY",		my_address);
	op_pk_nfd_set(pkptr,"DEST",			my_cds.relay);
	op_pk_nfd_set(pkptr,"DEST_FINAL",	ADDR_MULTICAST_AP);
	op_pk_nfd_set(pkptr,"PK_ID",		current_id++);
	op_pk_nfd_set(pkptr,"STAT_ID",		current_ap_unicast_id);
	op_pk_nfd_set(pkptr,"TTL",			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",	AP_UNICAST_PK_TYPE);
	
	//Stats
	if (current_ap_unicast_id >= MAX_AP_UNICAST)
		op_sim_end("We have too many max_ap_unicast pk","to handle the statistics","Please increase the value of MAX_AP_UNICAST","in the header block of the cdcl process");
	stats_ap_unicast[current_ap_unicast_id].time_emission	= op_sim_time();
	stats_ap_unicast[current_ap_unicast_id].source			= my_address;
		
	//Final Control variables
	current_ap_unicast_id++;
	
	//Transmission
	pk_send (pkptr);	
		
	//Identificaiton of the remote localization process
	network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
	node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(  op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB)  - nb_aps)) + nb_aps;
	process_remote_id	= op_id_from_name (node_remote_id, OPC_OBJMTYPE_QPS, "cds-cluster");

	op_intrpt_schedule_remote(op_sim_time() + INTERVALL_AP_UNICAST_PK , AP_UNICAST_GENERATE_CODE , process_remote_id);
}









int factoriel(int a){
	if ((a == 0) || (a==1))
		return(1);
	else
		return(a * factoriel(a-1));
}

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void cdcl_process_cluster_cds_process (void);
	Compcode cdcl_process_cluster_cds_process_init (void **);
	void cdcl_process_cluster_cds_process_diag (void);
	void cdcl_process_cluster_cds_process_terminate (void);
	void cdcl_process_cluster_cds_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
cdcl_process_cluster_cds_process (void)
	{
	int _block_origin = 0;
	FIN (cdcl_process_cluster_cds_process ());
	if (1)
		{
		/* Variables used in state transitions.		*/
		int			intrpt_code;
		


		FSM_ENTER (cdcl_process_cluster_cds_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (Init2) enter executives **/
			FSM_STATE_ENTER_FORCED (0, state0_enter_exec, "Init2", "cdcl_process_cluster_cds_process () [Init2 enter execs]")
				{
				//CONTROL
				char		str[150];
				char		var_name[200];
				neigh_cell	*ptr;
				FILE		*fichier;
				int 		i , j , addr; 
				char		msg[150];
				//Constants
				Boolean		IS_BB_FLOODING_ACTIVATED;
				Boolean		IS_AP_UNICAST_ACTIVATED;
				Boolean		TOPOLOGY_DEBUG;
				//ENERGY
				double		MIN_ENERGY;
				double		MAX_ENERGY;
				//CPLEX
				double		cplex_time;
				//SPEEDS
				double		low_mob_max , low_mob_min , high_mob_max , high_mob_min;
				//TOPOLOGY
				int			nb_fixed_nodes , nb_mobile_nodes , is_node_AP;
				//AP Position
				int			process_id , node_id;
				double		XMAX , YMAX;
				int			MOBILITY_MODEL;
				
				
				//Initialize the constant about Energy
				if (nb_total == 0)
					{
						
						//NB :   AP / normal nodes
						nb_fixed_nodes 		= op_topo_object_count(OPC_OBJTYPE_NDFIX);
						for(i=0 ; i<nb_fixed_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDFIX , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
				
						nb_mobile_nodes 	= op_topo_object_count(OPC_OBJTYPE_NDMOB);
						for(i=0 ; i<nb_mobile_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDMOB , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
						
						
						//NB : the AP (@=1) isforbidden as weakest node (@ : 2->max)
						stat_id_weakest_node 	= op_dist_uniform (nb_nodes_expected-1) + 2; 
					
						//Initialization of stats about energy consumption
						stat_conso_dominator.energy 	= 0;
						stat_conso_dominator.time 		= 0;
						stat_conso_dominatee.energy 	= 0;
						stat_conso_dominatee.time 		= 0;
						
						//definition of thresholds to define high/medium/low energy
						// max energy   --->   high_energy  --->  medium_energy   ---->   low_energy  ---> null
						HIGH_ENERGY 	= simulation_duration*IDLE_CONSUMPTION * HIGH_ENERGY_PERCENTAGE;  	//We can durate still x% of our battery life (x = HIGH_ENERGY_PERCENTAGE)
						MEDIUM_ENERGY 	= simulation_duration*IDLE_CONSUMPTION * MEDIUM_ENERGY_PERCENTAGE;
						LOW_ENERGY 		= simulation_duration*IDLE_CONSUMPTION * LOW_ENERGY_PERCENTAGE;
				
						//Get the forecasted simulation duration
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"duration",				&simulation_duration);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_LOW_MAX",			&low_mob_max);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_LOW_MIN",			&low_mob_min);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_HIGH_MAX",			&high_mob_max);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_HIGH_MIN",			&high_mob_min);
						op_ima_sim_attr_get(OPC_IMA_INTEGER,"cds_algo",				&cds_algos_type);
						op_ima_sim_attr_get(OPC_IMA_INTEGER,"FAILURE_TYPE",			&stab_failure_type);
						
						//The prefix for all file containing results/debug
						if (cds_algos_type != WU_LI)
							sprintf(prefix_results_file, "vsr_%d_(%.0lf_%.0lf)_(%.0lf_%.0lf)-%d_", 		nb_nodes_expected + nb_aps_expected , low_mob_min , low_mob_max , high_mob_min , high_mob_max , begin_time);
						else
							sprintf(prefix_results_file, "wu_li_%d_(%.0lf_%.0lf)_(%.0lf_%.0lf)-%d_", 	nb_nodes_expected + nb_aps_expected , low_mob_min , low_mob_max , high_mob_min , high_mob_max , begin_time);
						
						sprintf(suffix_results_file, "");
					}
				
				
				//printf("%d >+ %d (%d)\n",nb_total, MAX_NB_NODES , nb_total >= MAX_NB_NODES);
				//The number of nodes has a maximum value (else, we have a buffer overflow for our arrays)
				if (nb_total >= MAX_NB_NODES)
					{
						sprintf(msg, "currently, MAX_NB_NODES=%d\n",MAX_NB_NODES);
						op_sim_end("We have too many nodes", "You must increase the MAX_NB_NODES value","in the HB of the cds-cluster process",msg);
					}
				
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//						Stats ID
				//
				//-----------------------------------------------------
				
				//protection against arrays overflows
				if (my_address >= MAX_ADDRESS)
					op_sim_end("We have too many nodes","please increase the value of MAX_ADDRESS","in the header block of the cdcl_routing process","");
				if (nb_total >= MAX_NB_NODES)
					op_sim_end("We have too many nodes","please increase the value of MAX_NB_NODES","in the header block of the cdcl_routing process","");
				
				my_stat_id = nb_total++;	//The first node has id 0
				stats_addresses_to_id[my_address] = my_stat_id;		//Convert an address into an id
				stats_id_to_addresses[my_stat_id] = my_address;		//The inverse
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//Initialisation of name of fields in the hello packet
				//
				//-----------------------------------------------------
				
				sprintf(hello_fields_names[0].address		, "SRC");
				sprintf(hello_fields_names[0].weight		, "WEIGHT");
				sprintf(hello_fields_names[0].hops 			, "NO_FIELD");
				sprintf(hello_fields_names[0].state			, "STATE");
				sprintf(hello_fields_names[0].bidirect		, "NO_FIELD");
				sprintf(hello_fields_names[0].clusterhead	, "CLUSTERHEAD");
				
				for(i=1 ; i <= MAX_FIELDS_IN_HELLO_RELAY ; i++)
					{
						sprintf(msg,"ADDRESS%d",i);
						sprintf(hello_fields_names[i].address, msg);
						sprintf(msg,"WEIGHT%d",i);
						sprintf(hello_fields_names[i].weight, msg);
						sprintf(msg,"HOPS%d",i);
						sprintf(hello_fields_names[i].hops, msg);
						sprintf(msg,"STATE%d",i);
						sprintf(hello_fields_names[i].state, msg);
						sprintf(msg,"BIDIRECT%d",i);
						sprintf(hello_fields_names[i].bidirect, msg);
						sprintf(msg,"FATHER%d",i);
						sprintf(hello_fields_names[i].father, msg);
						sprintf(msg,"CLUSTERHEAD%d",i);
						sprintf(hello_fields_names[i].clusterhead, msg);
					}
				
				
				
				
				//----------------------------------------------------
				//
				//	Recuperation of simulation parameters
				//
				//-----------------------------------------------------
				
				//The simulation paramaters
				//For this Node
				op_ima_obj_attr_get(op_id_self(),	"is_AP",				&is_AP); 
				op_ima_obj_attr_get(op_id_self(),	"is_Wireless_Router",	&is_wireless_router); 
				
				
				//Whole simulation
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"hello_method",					&hello_method); 
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"k_cds",						&k_cds);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"k_cluster",					&k_cluster);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"energy_management",			&energy_management);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"METRIC",						&metric);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"cds_algo",						&cds_algos_type);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"cluster_algo",					&cluster_algos_type);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"is_cluster_knowledge_required",&is_cluster_knowledge_required);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"is_bb_flooding_activated",		&IS_BB_FLOODING_ACTIVATED);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"is_ap_unicast_activated",		&IS_AP_UNICAST_ACTIVATED);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"topology_debug",				&TOPOLOGY_DEBUG);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"DEBUG_CDCL",					&DEBUG);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"ACK_FOR_BB_MULTICAST",			&ACK_FOR_BB_MULTICAST);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, "MIN_ENERGY",					&MIN_ENERGY);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, "MAX_ENERGY",					&MAX_ENERGY);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, "CPLEX_TIME",					&cplex_time);
				
				
				//Verifications for cluster agorithms, and limits on the value of k_cluster / k_cds
				if (k_cds == k_cluster)
					cluster_algos_type = NONE;
				if (k_cds == k_cluster)
					is_cluster_knowledge_required = OPC_FALSE;
				
				//verifications for Wu&LI
				if ((hello_method != HELLO_METHOD_RELAY) && (cds_algos_type == WU_LI))
					op_sim_end("We don't support the KTABLE HELLOS", "for the CDS WU&Li construction", "please change it", "and reload the simulation");
				
				
				if (is_AP)
					nb_aps++;
				if (is_wireless_router)
					nb_wireless_routers++;
				
				
				
				
				//----------------------------------------------------
				//
				//				POSITION OF THE AP
				//
				//-----------------------------------------------------
				
				
				
				//The AP is central only if it exists one single AP
				if ((is_AP) && (nb_aps_expected == 1))
					{
						process_id = op_id_self();
						node_id = op_topo_parent (process_id);
						op_ima_sim_attr_get(OPC_IMA_INTEGER, 	"SP_LOW_MOBILITY_MODEL"	, &MOBILITY_MODEL);
						
						//NB : NEITHER_POSITION_NOR_MOBILITY = 5
						if (MOBILITY_MODEL != 5)
							{
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, "X_MAX"  , &XMAX);
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Y_MAX"  , &YMAX);
								op_ima_obj_attr_set(node_id, "x position", XMAX/2);
								op_ima_obj_attr_set(node_id, "y position", YMAX/2);
							}
					}
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//				General Infos
				//
				//-----------------------------------------------------
				
				//--------------- Various ---------------
				
				my_weight.value 				= 1;						//For initialization, my weight is the unity
				my_weight.time_last_computation = 0;						//Last time we computed our weight (initially -> 0 (not yet computed))
				current_id 						= op_dist_uniform(64000);	//the first id of the packet I will send
				
				
				//--------------- Weight ---------------
				for(i=0;i<NB_STORED_SPEEDS;i++)
					{
						last_absolute_speeds[i] = -1;
					}
				op_ima_obj_attr_get(op_topo_parent (op_id_self()),"x position",&(last_xy.x));
				op_ima_obj_attr_get(op_topo_parent (op_id_self()),"y position",&(last_xy.y));
				
				
				//------- Overheads specific for this node -----------
				overhead_cluster_pk 	= 0;
				overhead_cluster_bits 	= 0;
				overhead_cds_pk	 		= 0;
				overhead_cds_bits	 	= 0;
				overhead_hello_pk	 	= 0;
				overhead_hello_bits	 	= 0;
				overhead_route_pk	 	= 0;
				overhead_route_bits	 	= 0;
				overhead_data_pk	 	= 0;
				overhead_data_bits	 	= 0;
				overhead_paging_pk	 	= 0;
				overhead_paging_bits	= 0;
				
				
				//----------------------------------------------------
				//
				//				Energy
				//
				//-----------------------------------------------------
				
				//---------- Energy Limits for all nodes -------------
				
				//Min energy = energy necessary with no sleeping and no transmission/reception consumption - 15% time of sleeping mode
				my_energy.min_capacity = simulation_duration*IDLE_CONSUMPTION * MIN_ENERGY ;
				//Max Energy = energy necessary with no sleeping and transmission/reception consumption + 50% of extra
				my_energy.max_capacity = simulation_duration*IDLE_CONSUMPTION * MAX_ENERGY ;
				
				if ((is_wireless_router) || (is_AP))
					my_energy.value = 10 * my_energy.max_capacity;
				else
					my_energy.value = op_dist_uniform(my_energy.max_capacity - my_energy.min_capacity) + my_energy.min_capacity;
				
				
				
				
				//----- To test the longevity of a weak node ---------
				if (my_stat_id == stat_id_weakest_node)
					{
						if ((is_AP) || (is_wireless_router))
							stat_id_weakest_node++;
						else
							my_energy.value = simulation_duration * IDLE_CONSUMPTION* WEAKEST_NODE_LIFETIME;
					}
				
				//------------- Common for stats -----------------
				is_DEAD.bool = 0;
				my_energy.previous_value 	= my_energy.value;
				my_energy.initial_value 	= my_energy.value;
				
				
				
				
				
				//----------------------------------------------------
				//
				//				CDS
				//
				//-----------------------------------------------------
				
				//--------------- CDS Infos ---------------
				
				change_father(ZERO , ZERO , ZERO);
				if (is_AP)
					my_cds.id_ap			= my_address;
				else
					my_cds.id_ap			= 0;
				my_cds.cds_intrpt_end 		= 0;								//The CDS is sure not finished !!
				my_cds.last_hello_ap_seen 	= 0;							//We have not yet seen a ap-hello		
				my_cds.time_last_break 		= -1;
				my_cds.state 				= IDLE;
				my_cds.sons					= NULL;
				my_cds.dominatees 			= NULL;
				
				for (i=0;i<NB_STORED_SPEEDS;i++)	{my_weight.last_neigh_changements[i][0]=-1;my_weight.last_neigh_changements[i][1]=-1;}
				
				
				//--------------- Timers ---------------
				
				my_cds.is_maintenance_scheduled = 0;
				
				
				//--------------- Other ---------------
				for(i=0;i<2*KCLUSTER_MAX-KCDS_MAX+1;i++) {my_cds.join_already_forwarded[i] = 0;}	//The node as already fowarded a join message (for the cds construction)
				my_cds.time_cds_reinit 			= -1;												//-1 --> No reconstruction must be scheduled
				my_cds.nb_retry_reconnect_cds 	= 0;
				my_cds.current_id_ap_hello 		= op_dist_uniform(64000);
				my_cds.time_last_break 			= -1;
				my_cds.previous_state_change_time 	= 0;
				my_cds.time_last_cds_reconstruct 	= 0;
				
				//------------- AP Hellos Table -------------
				ap_hellos_table = NULL;
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//				Clusters
				//
				//-----------------------------------------------------
				
				//--------------- General ---------------
				
				my_clusterhead.address 				= 0;
				my_clusterhead.relay 				= 0;
				my_clusterhead.time_last_break 		= -1;
				my_clusterhead.last_id 				= 0;
				my_clusterhead.nb_recon_try 		= 0;
				my_clusterhead.last_inscription 	= 0;
				my_clusterhead.last_time_usefull 	= 0;
				my_clusterhead.construct_cluster 	= 0;
				
				
				
				//--------------- Cluster Table ---------------
				
				cluster_table = (struct cluster_cell*) op_prg_mem_alloc(sizeof(cluster_cell));
				if (cluster_table==NULL)
					{
						printf("Error in the memory allocation for my cluster table\n");
					}
				
				//I add myself in the table
				cluster_table->next			= NULL;
				cluster_table->address 		= my_address;
				cluster_table->weight 		= my_weight.value ;
				cluster_table->hops 		= (short)0;
				cluster_table->timeout 		= (double) 99999999.0;
				cluster_table->clusterhead 	= 0;					
				
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//				Neighbors and Others
				//
				//-----------------------------------------------------
				
				if (is_cluster_knowledge_required)
					{
						ttl_for_hellos = k_cluster;
						ttl_for_hello_mis = k_cds + 1;
							
					}
				else if (cds_algos_type == WU_LI)
					ttl_for_hellos = k_cds;
				else
					{
						ttl_for_hellos 		= k_cds;
						ttl_for_hello_mis 	= k_cds + 1;
					}
				
				
				
				//---------------- ID Table -----------------
				id_table = NULL;
				
				//-------------- Relaying Table -------------
				relay_table = NULL;
				
				//--------------- Neighborhood --------------
				
				neighbour_table = (struct neigh_cell*) op_prg_mem_alloc (sizeof(neigh_cell));
				if (neighbour_table==NULL)
					{
						printf("Error in the memory allocation for my neighbourhood table\n");
					}
				
				//I add myself in the table
				neighbour_table->next				= NULL;
				
				neighbour_table->address 			= my_address;
				neighbour_table->hops 				= (short)0;
				neighbour_table->relay 				= -1;
				neighbour_table->bidirect 			= 1;
				neighbour_table->timeout 			= (double) 9999999.0;
				
				neighbour_table->weight 			= my_weight.value ;
				neighbour_table->mobility 			= -1 ;
				neighbour_table->sleep				= 0;
				
				neighbour_table->state 				= 0;
				neighbour_table->father 			= 0;
				neighbour_table->father_hops		= 0;
				neighbour_table->id_ap	 			= 0;//my_cds.id_ap;
				neighbour_table->cluster_init_flag 	= 1;					//This flag must not be restrictive to verify that all our neighbours initiated the construction of a cluster (if we verify, we try to construct one)
				neighbour_table->clusterhead 		= 0;
				neighbour_table->clusterhead_hops	= 0;
				nb_chgts_neighbourhood 				= 0;
				
				neighbour_table->gw_list			= op_prg_list_create();
				//neighbour_table->gw_list			= op_prg_mem_alloc (sizeof(List));
				
				neighbor_table_wu_li				= op_prg_list_create();
				
				neighbour_table->neighbors			= op_prg_list_create();
				//neighbour_table->neighbors			= op_prg_mem_alloc (sizeof(List));
				neighbour_table->neighbors_timeout	= 0;
				
				
				//--------------- Acks Table ---------------
				my_acks = NULL;
				
				
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//		Initiialization of Lists
				//
				//-----------------------------------------------------
				
				//Ici Initialization
				ici_list					= op_prg_list_create();
				//ici_list					= op_prg_mem_alloc (sizeof(List));
								
				//Buffered Pk List Initialization
				temporary_pk_list			= op_prg_list_create();
				//temporary_pk_list			= op_prg_mem_alloc (sizeof(List));
				
				//My gw list Initialization
				my_gw_list					= op_prg_list_create();
				//my_gw_list					= op_prg_mem_alloc (sizeof(List));
				
				//The list of the cds-connectors in my _neighborhood
				my_cds.cds_connectors_list	= op_prg_list_create();
				//my_cds.cds_connectors_list	= op_prg_mem_alloc (sizeof(List));
				
				//My gw list Initialization
				ack_multicast_list			= op_prg_list_create();
				//ack_multicast_list			= op_prg_mem_alloc (sizeof(List));
				
				
				
				//----------------------------------------------------
				//
				//		Open the file for out messages
				//
				//-----------------------------------------------------
				//----------------------- Stats ---------------------
				//I'am the first node : I reinitialize my infos about correspondence id<->address
				if(nb_total==0)
					stats_network_figure_initalization();
				if (my_stat_id == 0)
					{
						for(i=0;i<MAX_BB_FLOODING;i++)
							{	
								stats_bb_flooding[i].time_emission	= 0;
								stats_bb_flooding[i].time_reception	= 0;
								for (j=0; j< MAX_NB_NODES ; j++)
									{
										stats_bb_flooding [i].is_rcvd 		[j] = 0;
										stats_bb_flooding [i].is_dominator  [j] = 0;
									}
							}
					}
				
				
				
				
				//--------------------- Per node --------------------
				
				if (my_address<10)
					sprintf(str,"results/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
					sprintf(str,"results/details_per_node/results_%d.txt",my_address);
				fichier = fopen(str,"w");
				fclose(fichier);
				
				
				
				//--------------- Global periodic stats ------------
				
				if (my_stat_id == 1)
					{
						for(i=0 ; i < MAX_NB_NODES ; i++)
							{
								stats_degree[i]					= 0;
								stats_cds[i].nb_parents			= 0;
								stats_cds[i].nb_cds_connectors	= 0;
							}
					//Instantaneous Performances
						if (DEBUG_INSTANTANEOUS)
							{
								sprintf(str,"results/%sperfs_stats%s.txt", prefix_results_file , suffix_results_file);		
								fichier = fopen(str,"w");
								fprintf(fichier,"#Instantaneous Performances Statistics of our constuctions\n");
								fprintf(fichier,"#NB : CH=clusterhead - DOM=Dominator - dom=Dominatee\n");
								fprintf(fichier,"#time		Nb DOM	CDS_strict	CDS_large	Nb CH		CH Connexity	Degree	2nd Parents		Connectors		List CH			List DOM\n");
								fclose(fichier);
							}
				
					//Number of changes of nodes states
						if (DEBUG_CONVERGENCE)
							{
								sprintf(str,"results/%sstabilization_stats%s.txt", prefix_results_file , suffix_results_file);		
								fichier = fopen(str,"w");
								fprintf(fichier,"#Number of nodes which change their state from the start of the simulation\n");
								fprintf(fichier,"#NB : i=idle, D=dominator, d=dominatee, a=active\n");
								fprintf(fichier,"#time		NB_i	NB_a	NB_D	NB_d	CDS_Strict	CDS_Large	i->a	i->D	i->d	d->i	D->i	a->D	a->d	d->a	d->D	D->d\n");
								fclose(fichier);
							}
				
					//Instantaneous Overhead
						if (DEBUG_NETWORK_CTRL)
							{
								sprintf(str,"results/%snetwork_control%s.txt", prefix_results_file , suffix_results_file);
								fichier = fopen(str,"w");
								fprintf(fichier,"#Flows in packets per second : rows 1->5(general), rows 6->10(dominators), rows 11->15(dominatees)\n");		
								fprintf(fichier,"#time		HELLOS	CDS		CLUSTERS	DATA		BB		OTHER	|	HELLOS	CDS		CLUSTERS	DATA		BB		OTHER	|	HELLOS	CDS		CLUSTERS	DATA		BB		OTHER\n");		
								fclose(fichier);
							}
						
					}
				
				
				
				
				//--------------- Cluster Topology ------------
				if (my_stat_id == 1)
						cluster_topo = NULL;
				old_cluster_topo.gw = NULL;
				old_cluster_topo.clusters =NULL;
				old_cluster_topo.old_clusterhead = ZERO;
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//			INTERRUPTIONS AFTER INITIALIZATION
				//
				//-----------------------------------------------------
				
				
				
				//Collecting periodic statistics
				op_intrpt_schedule_call (TIME_BEGIN_PERFS_STATS   	, STATS_CODE 		, periodic_stats_generate 		, -1);
				if (cds_algos_type != WU_LI)
					op_intrpt_schedule_call (op_sim_time() + 5.0 + TIME_NETWORK_INIT	, CLUSTER_TOPO_CODE , periodic_cluster_topo_stats_generate 	, -1);		
				
				
				
				//Schedule the next hello_generation (uniformly distributed in the intervall [0..INTERVALL_HELLO])
				op_intrpt_schedule_call (op_sim_time() + (INTERVALL_HELLO * op_dist_uniform(1.0)) , HELLO_GENERATION_CODE 	, hello_management 		, -1);
				op_intrpt_schedule_call (op_sim_time() + INTERVALL_UPDATE_TABLE, 					UPDATE_TABLE_CODE 		, update_tables_periodic, -1);
				
				
				//All nodes will determine that their are active after k_cds hops (each during max 0.4 seconds). It advertises us with its new state and weight (k_cds hops). 
				//We have max k_cds nodes that retrieve the transmitting (arbitrary)
				timeout_construct_cds = 2*k_cds*0.4;
				
				
				//We must know our k_cds-neighbourhood in order to intiate the construction of the k-cds. 
				switch (cds_algos_type) {
				//CDS Construction & Maintenance proposed by Theo
					case THEO_OLD :
					case THEO_NEW :
					case THEO_NEW2 :
						if (is_AP)
							{
								my_cds.cds_intrpt_end = 1;
								op_intrpt_schedule_self(op_sim_time()+ TIME_NETWORK_INIT	, CONSTRUCT_CDS_CODE);
								op_intrpt_schedule_call(op_sim_time()+ TIME_NETWORK_INIT	, AP_HELLO_CODE , ap_hello, -1);		
							}
					break;
				//CDS Proposition of Wu & Li 	
					case WU_LI :
								op_intrpt_schedule_call (op_sim_time()	, CDS_WU_LI_COMP_CODE , cds_maintenance_wu_li , -1);	
							break;
					default :
						op_sim_end("Bad Maintenance/Construction CDS type Selected\n", "","","");
				}
				
				
				//Topology Figure generation : TIME_BEGIN_STATS
				if (TOPOLOGY_DEBUG)
					op_intrpt_schedule_call (20 , STATS_POSITIONS_CODE , collect_stat_about_nodes_and_links , -1);
				//Cplex Files
				if (cplex_time > 0)
					op_intrpt_schedule_call (cplex_time , STATS_POSITIONS_CODE , compute_and_write_cplex_files , -1);
				
				
				//Backbone flooding
				if ((my_address == 2) && (IS_BB_FLOODING_ACTIVATED))
					op_intrpt_schedule_call(TIME_NETWORK_STABILIZED  , -1 , bb_multicast_generate , -1);
				
				
				//Toward Ap Transmission
				if ((my_address == 5) && (IS_AP_UNICAST_ACTIVATED))
					op_intrpt_schedule_self(TIME_NETWORK_STABILIZED , AP_UNICAST_GENERATE_CODE);
				
				
				
				
				}


			/** state (Init2) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "Init2", "cdcl_process_cluster_cds_process () [Init2 exit execs]")
				{
				
				}


			/** state (Init2) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Init2", "Idle")
				/*---------------------------------------------------------*/



			/** state (Idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, state1_enter_exec, "Idle", "cdcl_process_cluster_cds_process () [Idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,cdcl_process_cluster_cds_process)


			/** state (Idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "Idle", "cdcl_process_cluster_cds_process () [Idle exit execs]")
				{
				/*char msg[200];
				
				
				sprintf (msg ,"%d - %d - %d - %d - %d\n", op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_SELF, OPC_INTRPT_STRM, OPC_INTRPT_ENDSIM);
				test_message(msg);
				
				*/
				}


			/** state (Idle) transition processing **/
			FSM_INIT_COND (PK_FROM_WLAN||PK_FROM_ETH||WAIT_STATE_END)
			FSM_TEST_COND (PK_FROM_HIGHER)
			FSM_TEST_COND (CLUSTER_MAINTENANCE)
			FSM_TEST_COND (CONSTRUCT_CLUSTER)
			FSM_TEST_COND (CONSTRUCT_CDS)
			FSM_TEST_COND (ENDSIM)
			FSM_TEST_COND (DIE)
			FSM_TEST_COND (AP_UNICAST_GENERATE)
			FSM_TEST_COND (CDS_MAINTENANCE)
			FSM_TEST_LOGIC ("Idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 4, state4_enter_exec, ;, "PK_FROM_WLAN||PK_FROM_ETH||WAIT_STATE_END", "", "Idle", "PK From LOWER")
				FSM_CASE_TRANSIT (1, 5, state5_enter_exec, ;, "PK_FROM_HIGHER", "", "Idle", "PK From HIGHER")
				FSM_CASE_TRANSIT (2, 6, state6_enter_exec, ;, "CLUSTER_MAINTENANCE", "", "Idle", "CLUSTER Maintenance")
				FSM_CASE_TRANSIT (3, 7, state7_enter_exec, ;, "CONSTRUCT_CLUSTER", "", "Idle", "CLUSTER")
				FSM_CASE_TRANSIT (4, 8, state8_enter_exec, ;, "CONSTRUCT_CDS", "", "Idle", "CDS")
				FSM_CASE_TRANSIT (5, 9, state9_enter_exec, ;, "ENDSIM", "", "Idle", "END_SIM")
				FSM_CASE_TRANSIT (6, 10, state10_enter_exec, ;, "DIE", "", "Idle", "DEAD")
				FSM_CASE_TRANSIT (7, 1, state1_enter_exec, ap_unicast_generate();, "AP_UNICAST_GENERATE", "ap_unicast_generate()", "Idle", "Idle")
				FSM_CASE_TRANSIT (8, 11, state11_enter_exec, ;, "CDS_MAINTENANCE", "", "Idle", "CDS Maintenance")
				}
				/*---------------------------------------------------------*/



			/** state (Init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (2, "Init", "cdcl_process_cluster_cds_process () [Init enter execs]")
				{
				//Addresses
				int			addr_attribution;
				char		str[500];
				
				
				//Synchronisation with lower levels
				op_intrpt_schedule_self(op_sim_time() + TIME_INIT_MAC,0);
				
				//Gets the time of simulation beginning
				if (begin_time==0)
					begin_time = time(NULL);
				
				//Communication with Higher Layer
				/*				
				//We have as attribute a pointer on the neighbour_table (communication with localization level)
				op_ima_obj_attr_set(op_id_self() ,"neigh_ptr",&neighbour_table);
								
				//We have as attribute a pointer on the cds structure (communication with localization level)
				op_ima_obj_attr_set(op_id_self() ,"my_cds",&my_cds);
				*/
				
				
				//Id of the process for The Higher Layer
				op_ima_obj_attr_get(op_id_self(),	"process_higher_layer",	&process_higher_layer_type); 
				switch(process_higher_layer_type)
					{
						case LOCALIZATION :
							process_higher_layer_id  = op_id_from_name ( op_id_parent (op_id_self()), OPC_OBJMTYPE_QPS, LOCALIZATION_PROCESS_NAME );
						break;
						case ROUTING :
							process_higher_layer_id  = op_id_from_name ( op_id_parent (op_id_self()), OPC_OBJMTYPE_QPS, ROUTING_PROCESS_NAME);
						break;
						case NULL :
							process_higher_layer_id  = 0;
						break;
						default:
							op_sim_end("You didn't select a valid upper layer" , "The process name and type must be moreover present" , "in the biblio.h file" , "");
						break;
					}
				
				
				
				
				
				//----------------------------------------------------
				//
				//					My address
				//
				//-----------------------------------------------------
				
				op_ima_obj_attr_get(op_id_self(),"Address_Attribution",&addr_attribution); 
				switch(addr_attribution){
						case ADDR_RANDOM :
							//I pick-up my wlan mac address
							op_ima_obj_attr_get(op_topo_parent(op_id_self()),"Wireless LAN MAC Address",&my_address);
							my_address = nb_aps + 1 + op_dist_uniform(LOWER_ADDR_FOR_MULTICAST - nb_aps);
							op_ima_obj_attr_set(op_id_self(),"My_Address",my_address); 	
						break;
						
						case ADDR_WLAN :
							op_ima_obj_attr_get(op_topo_parent(op_id_self()),"Wireless LAN MAC Address",&my_address);
							op_ima_obj_attr_set(op_id_self(),"My_Address",my_address); 	
						break;
						
						case ADDR_CONFIGURED :
							op_ima_obj_attr_get(op_id_self(),"My_Address",&my_address); 	
						break;
						
						case ADDR_MAC_CDCL_FROM_NAME :
							op_ima_obj_attr_get(op_topo_parent(op_id_self()) , "name" , str);
							my_address = atoi(str);
							op_ima_obj_attr_set(op_topo_parent(op_id_self()),"Wireless LAN MAC Address", my_address);
							op_ima_obj_attr_set(op_id_self() , "My_Address" , my_address); 	
						break;
						
						default :
							op_sim_end("The address auto-configuration is not well-configured" , "", "", "");
						break;
					}
				if (my_address==0)
					op_sim_end("Error : we have a null address","Probable Problem with random address and/or with Mac and Ad-hoc Addresses cohabitation) \n","","");
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,cdcl_process_cluster_cds_process)


			/** state (Init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "Init", "cdcl_process_cluster_cds_process () [Init exit execs]")
				{
				}


			/** state (Init) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "Init", "Init2")
				/*---------------------------------------------------------*/



			/** state (OBSOLETE) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (3, "OBSOLETE", "cdcl_process_cluster_cds_process () [OBSOLETE enter execs]")
				{
				
				/*
				
				//----------------------------------------------------------------------------------------------------------------------------------
				//------------------------------------------------------------------------------------------------------------------------------------
				//
				//														DATA PACKETS
				//
				//------------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				
				if ( is_unicast_for_me && is_ttl_enough && is_pk_data_or_ack )
					{
				
						//Adds this packet as already seen
						add_address_id_couple(address_src,id);
					
						switch(type_packet)
							{
								//------------------------------------------	
								//					DATA 
								//-------------------------------------------
								case DATA_PK_TYPE : 
									op_stat_write(data_rcvd_handle,op_pk_total_size_get(pkptr));			
									op_stat_write(total_data_rcvd_handle,op_pk_total_size_get(pkptr));			
									
									if (is_pk_not_seen)
										{
											//A node of state nothing is neighbour of our cds-zone -> the dominator must send a join message
											op_pk_nfd_get(pkptr,"DEST_FINAL",&dest_final);
											
											//Acknowledges actively the packet to the source (only if I won't forward it (I am the final destination)
											if ((my_address==dest_final) || ((dest_final==ADDR_MULTICAST_AP)&&(is_AP)))
												{
													ack_packet(pkptr, DATA);
													printf("!!  AP Reception  !!\n\n",my_address);
												}
						
											//I am just a relay, I forward to the next relay !
											if ((dest_final != my_address)&&!((is_AP)&&(dest_final==ADDR_MULTICAST_AP))&&(is_pk_not_seen))
												{
													dest = get_relay_to_general_destination(dest_final);
													if (dest!=-1)
														{
															op_pk_nfd_set(pkptr,"SRC",my_address);
															op_pk_nfd_set(pkptr,"DEST",dest);
															//op_pk_nfd_set(pkptr,"ID_PK",current_id++);
															op_pk_nfd_set(pkptr,"TTL",--ttl);
												
															if (DEBUG>1)
																{
																	printf("RELAY : %d forwards to %d with final destination %d\n",my_address,dest,dest_final);
																	sprintf(msg,"RELAY : %d forwards to %d with final destination %d\n",my_address,dest,dest_final);
																	cluster_message(msg);
																}
													
															//This apcket must be acknowledged and sent
															add_ack_pk(pkptr);	
															pk_send(pkptr , DATA);
														}
													else
														{
															if (DEBUG>1)
																{
																	sprintf(msg,"pb : no relay for destination %d\n", dest_final);
																	cluster_message(msg);
																}
														}
												}
											//I forward directly the packet to higher level
											else
												{
													op_pk_nfd_set(pkptr,"TTL",--ttl);
													op_pk_send(pkptr, STRM_TO_HIGHER);
												}
										}
									else
										//We have already received this packet, but the source has not received our acknowledgement
										ack_packet(pkptr, DATA);
				
								break;
									
									
								//------------------------------------------	
								//					ACKS
								//-------------------------------------------
									
								case ACK_UNICAST_PK_TYPE :
									op_stat_write(ack_rcvd_handle,op_pk_total_size_get(pkptr));			
									op_stat_write(total_ack_rcvd_handle,op_pk_total_size_get(pkptr));			
				
									printf("ACK : reception at %d\n",my_address);
									//Set the original packet as acknowledged
									delete_ack_pk(pkptr);
								break;
							}
									
					}
				
									
				//------------------------------------------	
				//		PASSIVE ACKNOWLEDGEMENTS
				//-------------------------------------------
									
				//When we receive a data-packet from one of our son/dominatee
				if ( (!is_unicast_for_me)  && is_ttl_enough && (type_packet == DATA_PK_TYPE) )
					{
						//This node has forwarded our packet -> all is ok, it's like an ack
						delete_ack_pk(pkptr);	
					}
				
				
				//---------------------------------------------------------------------------------------------------------------------------------
				//------------------------------------------------------------------------------------------------------------------------------------
				//
				//														BACKBONE MULTICAST
				//
				//------------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				
				
				//Searches in all DEST_i fields If I am a unicast destination
				my_dest_field_nb = -1;
				if ((is_pk_bb_multicast)&&(my_cds.state==DOMINATEE)&&(my_dest_field_nb==-1))
						{
							//Destination in DEST_i packets -> searches if I am one of these destinations
							i = 0;
							sprintf(str,"DEST");
							while((i<=MAX_NB_APS) && (op_pk_nfd_is_set(pkptr,str)) )
								{
									op_pk_nfd_get(pkptr,str,&dest);					
									if (dest==my_address)
										my_dest_field_nb = i;
									i++;
									sprintf(str,"DEST%d",i);
								}
							//This packet is a unicast for me If I am one of these destinations
							is_unicast_for_me = (my_dest_field_nb != -1);
						}
				
				if (is_ttl_enough && is_pk_bb_multicast && (is_pk_not_seen || is_unicast_for_me))
					{
						//Adds this packet as already seen
						add_address_id_couple(address_src,id);
						op_pk_nfd_get(pkptr,"RELAY",&relay);					
				
						//print_cds_infos();
						switch(type_packet)
							{
								
								//------------------------------------------	
								//			BACKBONE MULTICAST PK
								//-------------------------------------------
									
								case BACKBONE_PK_TYPE :
									op_stat_write(bb_multicast_rcvd_handle,op_pk_total_size_get(pkptr));
									op_stat_write(total_bb_multicast_rcvd_handle,op_pk_total_size_get(pkptr));
								
								//DOMINATORS : standard retransmission
									//I received this packet from one interconnection
									if ((my_cds.state==DOMINATOR)&&(is_unicast_for_me))
										ack_packet(pkptr , BACKBONE_MULTICAST);
									
									if ((my_cds.state==DOMINATOR)&&(is_pk_not_seen))
										{
											//I received the packet + I must receives that							
											stats_backbone_flooding [my_stat_id][id] 			= 1;
											stats_backbone_flooding_receivers [my_stat_id][id] 	= 1;
											
											//Forwards packet
											if(DEBUG>1)
												{
													printf("BB (BB) : %d -> relay dom from %d with id %d\n",my_address,relay,id);
													sprintf(msg,"BB (BB) : %d -> relay dom from %d with id %d\n",my_address,relay,id);
													cluster_message(msg);
												}
											send_pk_to_bb_and_gws(pkptr);
										}
									
								
								//INTERCONNECTIONS
									if (is_unicast_for_me && (my_cds.state==DOMINATEE) && !pk_not_seen(id,relay))
										ack_packet(pkptr , BACKBONE_MULTICAST);
				
									if (is_unicast_for_me && (my_cds.state==DOMINATEE) && pk_not_seen(id,relay))
										{
											//Adds this packet as already relayed (a unicast retransmission is possible if the ack is lost)
											add_address_id_couple(relay,id);
											ack_packet(pkptr , BACKBONE_MULTICAST);
											
											//Gathers Destination informations (necessary for a good relaying)
											if (my_dest_field_nb!=0)
												{
													sprintf(str,"DEST%d",my_dest_field_nb);
													op_pk_nfd_get(pkptr,str,&dest);
													sprintf(str,"DEST_FINAL%d",my_dest_field_nb);
													op_pk_nfd_get(pkptr,str,&dest_final);
													sprintf(str,"ID_AP%d",my_dest_field_nb);
													op_pk_nfd_get(pkptr,str,&id_ap);
												}
											else
												{
													op_pk_nfd_get(pkptr,"DEST",&dest);
													op_pk_nfd_get(pkptr,"DEST_FINAL",&dest_final);
													op_pk_nfd_get(pkptr,"ID_AP",&id_ap);
												}
											
											if(DEBUG>1)
												{
													printf("BB (INTER) : %d is a secondary relay for a packet from %d\n",my_address,relay);
													sprintf(msg,"BB (INTER) : %d is a secondary relay for a packet from %d\n",my_address,relay);
													cluster_message(msg);
												}
				
											//If It's not the same id_ap, I relay to the gateway registered in packet
											if (id_ap != my_cds.id_ap)
												{
													//If I am just a relay to the gateway
													if (dest_final!=my_address)
														relay_to_gateway(pkptr , dest , dest_final , id_ap);
													//If I am the gateway
													else
														relay_to_ap_neighbor(pkptr , dest , dest_final , id_ap);
												}
											//I relay the packet to my dominator (with the same id_ap)
											else
												relay_to_my_ap(pkptr , dest , dest_final , id_ap);
										}		
									
								break;		
							}
							
									
					}
					
				//For Multicast acknowledgements (If I am dominator, else I mustn't participe to backbone flooding)
				if ((is_pk_bb_multicast) && (my_cds.state == DOMINATOR))
					delete_ack_multicast_pk(pkptr);
					
				}
				*/
				
				/*
				
				
				
				
				
				//----------------------------------------------------------------------
				//				     		Parameters		
				//---------------------------------------------------------------------
				// Special attribute values
#define		TIME_INIT_MAC				5.0		//Time to wait before initialization
#define		TIME_NETWORK_INIT			25.0	//All cumulated timers for initialization = 30 seconds
#define		TIME_BEGIN_STATS			50.0	//Time to wait before collecting stats
#define		TIME_BEGIN_TOPO_STATS		80.0
#define		INTERVALL_STATS_COLLECTING	1.0
				
				// General parameters
#define		NB_MAX_NODES				60
#define		MAX_ADDRESS					300
#define		MAX_NB_APS					1
				
				// Debug
#define		BB_FLOODING_DEBUG			1			//=1 if the debug message must be printed
#define		TEST_DEBUG					1
#define		NORMAL_DEBUG				1
#define		STATS_DEBUG					1
#define		NETWORK_CTRL_DEBUG			1
#define		MAX_BB_FLOODING				1000
				
				
				// Special Addresses (Multicast for APs...
#define		ADDR_MULTICAST_AP			255
#define		ADDR_MULTICAST_BACKBONE		256
#define		LOWER_ADDR_FOR_MULTICAST	255			
				//NB : we have the variable "nb_aps" to define dynamically the numbre of APs in the simulation
				
				// To distinguish different modules and functions for Stats
#define		HELLO						1
#define		CDS							2
#define		CLUSTER						3
#define		OTHER						4		//For sleeping control for example
#define		AP_HELLOS					5
#define		DATA						6
#define		BACKBONE_MULTICAST			7
#define		ACK							8
				
				// For automatic attribution of Addresses 
#define		ADDR_RANDOM					0
#define		ADDR_WLAN					1
#define		ADDR_CONFIGURED				2
					
				// Timeouts
#define		MAX_RETRY					1		//We send "important" packets MAX_RETRY
#define		MAX_NB_RETRANSMISSIONS		2		//Retransmission for data packets that must be acknowledged
#define		TIMEOUT_RETRANSMISSIONS		0.1
#define		TIMEOUT_AP_HELLO			2.1
#define		TIMEOUT_RELAYING			4.1
#define		TIMEOUT_CLUSTERHEAD			2.1
#define		TIMEOUT_RETRIEVE			0.1
#define		TIMEOUT_HELLO				3.01
#define		TIMEOUT_ID					60
				
				// Hellos
#define		INTERVALL_AP_HELLO			2.0
#define		INTERVALL_CLUSTERHEAD_HELLO	2.0
				
#define		INTERVALL_HELLO				4.0
#define		INTERVALL_FAST_HELLO		1.0	
				
#define		INTERVALL_BB_FLOODING		5.0
				
#define		INTERVALL_UPDATE_TABLE		1.0
#define		INTERVALL_CDS_WU_LI_COMP	1.0
#define		HELLO_METHOD_RELAY			1
#define		HELLO_METHOD_KTABLE			2
#define		MAX_FIELDS_IN_HELLO_RELAY	39
#define		MAX_FIELDS_IN_HELLO_KTABLE	40
#define		MAX_AP_NEIGH_IN_HELLO		9
				
				
				
				// For Packets
#define		NB_RELAY_FIELDS				8
				
				//----------------------------------------------------------------------
				//				     		ENERGY		
				//----------------------------------------------------------------------
#define		SLEEP_THRESHOLD				0.25
				
				//	Initial Energy and sleeping Time	
#define		SLEEPING_TIME				11.99
#define		NO_ENERGY					0
#define		ENERGY						1
#define		ENERGY_AND_SLEEP			2
					
				//	Values of energy consumption	
#define		IDLE_CONSUMPTION			843000
#define		SENT_SLOPE_CONSUMPTION		454
#define		SENT_COEFF_CONSUMPTION		1.9
#define		RECEIVED_SLOPE_CONSUMPTION	356
#define		RECEIVED_COEFF_CONSUMPTION	0.5
				
				//  Classes of energy  
				float		MEDIUM_ENERGY;
				float		LOW_ENERGY;
				float		HIGH_ENERGY;
#define		HIGH_ENERGY_PERCENTAGE		0.7
#define		MEDIUM_ENERGY_PERCENTAGE	0.4
#define		LOW_ENERGY_PERCENTAGE		0.2
				
				
				//----------------------------------------------------------------------
				//				     		WEIGHT		
				//----------------------------------------------------------------------
				// Type of metric used to compute our weights 
#define		LOWEST_ID					1
#define		HIGHEST_DEGREE				2
#define		MOBILITY					3
#define		THEO_WEIGHT					4
				
				//	Weight	
#define		LOW_WEIGHT					15		//Threshold to define a weak weight
#define		OPTIMAL_K_DENSITY			8		//To compute density_metric for the weight
				
				
				//----------------------------------------------------------------------
				//				     		CDS		
				//----------------------------------------------------------------------
				float		timeout_construct_cds ;
				
				// States of CDS Creation 
#define		DOMINATOR					1
#define		DOMINATEE					2
#define		ACTIVE						3
#define		NOTHING						0
				
				//  Parameters for reconnection   
#define		NB_JOIN_MAX					2
#define		NB_MAX_TRY_RECONNECT_CDS	8
#define		TIME_BETWEEN_2_BREAKS		15
				
				// 	CDS Maintenance Type	
#define		NONE						0
#define		THEO_OLD					1
#define		THEO_NEW					2
#define		WU_LI						3
				
				//----------------------------------------------------------------------
				//				     		CLUSTER		
				//----------------------------------------------------------------------
				// Parameters 
#define		NB_MAX_TRY_RECONNECT_CLUSTER	5
				
				//----------------------------------------------------------------------
				//				     		FIGURE		
				//----------------------------------------------------------------------
				
#define		THICKNESS_DOMINATEE			2
#define		THICKNESS_DOMINATOR			5
#define		THICKNESS_PHYSIC_NEIGHBOR	1
				
				//----------------------------------------------------------------------
				//								Packets			
				//----------------------------------------------------------------------
				
				
				//Type of Streams 
#define		STRM_FROM_WLAN		   		0
#define		STRM_TO_WLAN				0
				
#define		STRM_FROM_ETH		   		2
#define		STRM_TO_ETH					2
				
#define		STRM_FROM_HIGHER	   		1
#define		STRM_TO_HIGHER				1
				
				
				
				//Type of packets 
#define		HELLO_PK_TYPE				01
				//Data
#define		DATA_PK_TYPE				10
#define		ACK_UNICAST_PK_TYPE			11
				//CDS Construction
#define		CDS_MIS_PK_TYPE				20
#define		CDS_JOIN_PK_TYPE			21
#define		CDS_REVERSE_JOIN_PK_TYPE	22
				//CDS Maintenance
#define		AP_HELLO_PK_TYPE			30
#define		CDS_RECONNECT_PK_TYPE		31
#define		CDS_RECON_REP_PK_TYPE		32
#define		RECONNECT_INIT_PK_TYPE		33					
#define		BREAK_CDS_PK_TYPE			34
#define		NOTHING_NEIGH_CDS_PK_TYPE	35
#define		USELESS_DOMINATOR_PK_TYPE	36					//To prevent our father that we have an idle neighbor (state=0)
				//Cluster Construction
#define		HELLO_CLUSTER_PK_TYPE		40
#define		JOIN_CLUSTER_PK_TYPE		41					//To declare That I am clusterhead
				//Cluster Maintenance
#define		CON_CLUSTER_PK_TYPE			50
#define		REP_CON_CLUSTER_PK_TYPE		51
#define		HELLO_CLUSTERHEAD_PK_TYPE	52
				//Sleeping
#define		SLEEPING_NODE_PK_TYPE		60
				//Control over backbone
#define		BACKBONE_PK_TYPE			70
				
				
				
				
				//----------------------------------------------------------------------
				//						Interruptions			
				//----------------------------------------------------------------------
				
				// Interrupt code values.			
#define		HELLO_GENERATION_CODE		01
				//CDS
#define		CONSTRUCT_CDS_CODE			10
#define		WAIT_STATE_CODE				11
#define		CDS_MAINTENANCE_CODE		12
#define		AP_HELLO_CODE				13
				//CDS Wu & LI
#define		CDS_WU_LI_COMP_CODE			100
				//Clusters
#define		CONSTRUCT_CLUSTER_CODE		20
#define		CLUSTER_HELLO_CODE			21
#define		CLUSTERHEAD_HELLO_CODE		22
#define		CLUSTER_MAINTENANCE_CODE	23
				//Utils
#define		STATS_CODE					30
#define		CLUSTER_TOPO_CODE			31
#define		DIE_CODE					32
#define		UPDATE_TABLE_CODE			33
				//Acknowledgements
#define		RETRANSMISSIONS_CODE		40
#define		MULTI_RETRANSMISSIONS_CODE	41
				//BB Flooding
#define		BB_FLOODING_CODE			50
				//Stats about positions
#define		STATS_POSITIONS_CODE		60
				
				
				
				// Macro definitions for state
				// transitions.	
#define		ENDSIM					(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define		HELLO_PK_GENERATE		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == HELLO_GENERATION_CODE)
#define 	PK_FROM_WLAN			(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_WLAN)
#define 	PK_FROM_ETH				(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_ETH)
#define 	PK_FROM_HIGHER			(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_HIGHER)
#define		CONSTRUCT_CDS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CONSTRUCT_CDS_CODE)
#define		WAIT_STATE_END			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == WAIT_STATE_CODE)
#define		CDS_MAINTENANCE		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CDS_MAINTENANCE_CODE)
#define		CONSTRUCT_CLUSTER		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CONSTRUCT_CLUSTER_CODE)
#define		CLUSTER_MAINTENANCE		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CLUSTER_MAINTENANCE_CODE)
#define		CLUSTERHEAD_HELLO		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == CLUSTERHEAD_HELLO_CODE)
#define		DIE						(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == DIE_CODE)
#define		STATS_POSITIONS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == STATS_POSITIONS_CODE)
				//RET - MULTI RET - STATS - CLUSTER TOPO - AP HELLO - CLUSTER HELLO
#define		PERIODIC_PROC			(op_intrpt_type() == OPC_INTRPT_SELF  ) && ((op_intrpt_code() == RETRANSMISSIONS_CODE) || (op_intrpt_code() == MULTI_RETRANSMISSIONS_CODE) || (op_intrpt_code() == STATS_CODE) || (op_intrpt_code() == CLUSTER_TOPO_CODE) || (op_intrpt_code() == CLUSTER_HELLO_CODE) || (op_intrpt_code() == AP_HELLO_CODE) || (op_intrpt_code() == BB_FLOODING_CODE) || (op_intrpt_code() == UPDATE_TABLE_CODE) || (op_intrpt_code() == CDS_WU_LI_COMP_CODE))
				
				
				
				
				*/
				
				
				/*
				void send_hello_cluster(){
					Packet	*pkptr;
					char	msg[150];	
					
					if (DEBUG>4)
						{
							sprintf(msg,"%d sends an hello cluster at %f\n",my_address,op_sim_time());
							cluster_message(msg);
						}
					
					pkptr = op_pk_create_fmt ("cdcl_cluster_hello");
					op_pk_nfd_set(pkptr,"TTL",k_cluster-k_cds);
				
				
					// Set some general fields of the packet
					op_pk_nfd_set(pkptr,"Option_Type",HELLO_CLUSTER_PK_TYPE);
					op_pk_nfd_set(pkptr,"SRC",my_address);
					op_pk_nfd_set(pkptr,"SRC_INIT",my_address);
					op_pk_nfd_set(pkptr,"WEIGHT",my_weight.value);
					op_pk_nfd_set(pkptr,"CLUSTERHEAD",my_clusterhead.address);
					op_pk_nfd_set(pkptr,"DEST",-1);
					op_pk_nfd_set(pkptr,"ID_PK",current_id++);
					
					//op_stat_write(cluster_sent_handle,op_pk_total_size_get(pkptr));
					//op_stat_write(total_cluster_sent_handle,op_pk_total_size_get(pkptr));	
					pk_send_delayed(pkptr,(float)rand()/32000, CLUSTER);
					
					//In order to avoid to modify myself, I add this packet as already seen
					add_address_id_couple(my_address,current_id-1);
				}
				
				*/
				
				
				
				
				
				
				/*-----------------------------------------------------------------------------------------------
				
										Acknowledgments of Multicast Packets
				
				----------------------------------------------------------------------------------------------*/
				/*
				//Delete a packet to aknowledge
				void delete_ack_multicast_pk(Packet* pk_ack){
					ack_multicast_cell	*ptr , *ptr2;
					int					id_pk , relay;
					char				msg[200];
				
					
					op_pk_nfd_get(pk_ack,"RELAY",&relay);
					op_pk_nfd_get(pk_ack,"PK_ID",&id_pk);
				
					if (DEBUG>3)
						{
							//printf("		MULTI ACK (%d) : acked pk from %d with id %d\n",my_address,relay,id_pk);
							sprintf(msg,"MULTI ACK (%d) : acked pk from %d with id %d\n",my_address,relay,id_pk);
							cluster_message(msg);
						}
					
					ptr = my_multicast_acks;
					ptr2 = NULL;
					while(ptr!=NULL)
						{
							if ((id_pk == ptr->id) && (relay == ptr->dest))
								{
									if (ptr2==NULL)
										{
											my_multicast_acks = ptr->next;
											free(ptr);
											ptr = my_multicast_acks;
										}
									else
										{
											ptr2->next = ptr->next;
											free(ptr);
											ptr = ptr2;
										}				
								}
							ptr2 = ptr;
							if (ptr!=NULL)
								ptr=ptr->next;
						}
				}
				
				//Adds a packet to acknowledge
				void add_ack_multicast_pk(Packet* pkptr){
					ack_multicast_cell*	ptr;
					son*				ptr_son;
					int					id , src;
				
					//Gathers id_packet
					op_pk_nfd_get(pkptr,"SRC",&src);
					op_pk_nfd_get(pkptr,"PK_ID",&id);
					
					//For each son
					ptr_son = my_cds.sons;
					while(ptr_son!=NULL)
						{
							ptr = (struct ack_cell*)op_prg_mem_alloc(sizeof(ack_cell));
							if (ptr==NULL)
								printf("error in the memory allocation for the creation of a new cell in the list of packets to ack");
							
							
							ptr->src			= src;
							ptr->dest			= ptr_son->address;
							ptr->id				= id;
							ptr->timeout 		= op_sim_time() + TIMEOUT_RETRANSMISSIONS;
							ptr->pk				= op_pk_copy(pkptr);
							ptr->nb_retransmits	= 0;
							ptr->next 			= my_multicast_acks;
							my_multicast_acks 	= ptr;	
							
							ptr_son = ptr_son->next;
						}
					
					
					//For the father
					if ((my_address != my_cds.father) && (my_cds.father!=0) && (my_cds.father!=-1))
						{
							ptr = (struct ack_cell*)op_prg_mem_alloc(sizeof(ack_cell));
							if (ptr==NULL)
								printf("error in the memory allocation for the creation of a new cell in the list of packets to ack");
				
							ptr->src			= src;
							ptr->dest			= my_cds.father;
							ptr->id				= id;	
							ptr->timeout 		= op_sim_time() + TIMEOUT_RETRANSMISSIONS;
							ptr->pk				= op_pk_copy(pkptr);
							ptr->nb_retransmits	= 0;
							ptr->next 			= my_multicast_acks;
							my_multicast_acks 	= ptr;
						}
				
					//Schedule the interruption for verification of the ack reception
					op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RETRANSMISSIONS , MULTI_RETRANSMISSIONS_CODE , send_timeout_ack_multicast_pk , -1);
				}
				
				//NB : acknowledgements are transcient : each neighbor retransmits this packet
				//Retransmit a packet after timeout
				void send_timeout_ack_multicast_pk(int* arg, int code){
					ack_multicast_cell	*ptr , *ptr2;
					char				msg[200];
					int					dest , dest_final;
					int					next_intrpt_needed = 0;		//An Interruption is needed 
					
				
					//Searches if an entry must be retransmited
					ptr = my_multicast_acks;
					while(ptr!=NULL)
						{
							if (ptr->timeout <= op_sim_time())
								{
									if (ptr->nb_retransmits < 2)
										{
											//Get and Set final and intermediary Destinations
											op_pk_nfd_get(ptr->pk,"DEST_FINAL",&dest_final);
											if (dest_final!=ADDR_MULTICAST_BACKBONE)
												dest = get_relay_to_general_destination(dest_final);
											else
												dest = dest_final;
											op_pk_nfd_set(ptr->pk,"DEST",dest);
				
											//Updates infos in Multicast Table
											ptr->timeout	= op_sim_time() + TIMEOUT_RETRANSMISSIONS;
											ptr->nb_retransmits++;
											if (ptr->nb_retransmits < 2)
												next_intrpt_needed = 1;
											
											//I send the packet only if it is destined to my son or my father
											if (( (is_my_son(ptr->dest)) || (my_cds.father==ptr->dest) ))
												{								
													if (DEBUG>1)
														{
															printf("MULTI-RET : %d forwards to %d to join %d\n",my_address,dest,dest_final);							
															sprintf(msg,"MULTI-RET : %d forwards to %d to join %d\n",my_address,dest,dest_final);	
															cluster_message(msg);
														}
													pk_send(op_pk_copy(ptr->pk),BACKBONE_MULTICAST);
													
													//I send it only if I didn't even transmit the same packet to one of my son or father in this round ...
													//I change for all other packet to sons and father with same id
													ptr2 = my_multicast_acks;
													while(ptr2!=NULL)
														{
															if ((ptr->src==ptr2->src) && (ptr->id == ptr2->src))
																{
																	ptr2->timeout = op_sim_time() + TIMEOUT_RETRANSMISSIONS;
																	ptr2->nb_retransmits++;
																}
															ptr2 = ptr2->next;							
														}
											
												}
											else
												printf("son %d - father %d\n",is_my_son(ptr->dest),my_cds.father==ptr->dest);
											
										}
								}
							ptr=ptr->next;
						}
					
					//Deletes entries with too many retries
					ptr = my_multicast_acks;
					ptr2 = NULL;
					while(ptr!=NULL)
						{
							//Deletes entries with too many retransmissions
							if (ptr->nb_retransmits >= 2)
								{
									if (ptr2==NULL)
										{
											my_multicast_acks = ptr->next;
											free(ptr);
											ptr = my_multicast_acks;
										}
									else
										{
											ptr2->next = ptr->next;
											free(ptr);
											ptr = ptr2;
										}				
								}
						
							//Next entry
							ptr2 = ptr;
							if (ptr!=NULL)
								ptr=ptr->next;
						}
				
					if (next_intrpt_needed)
						op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RETRANSMISSIONS , MULTI_RETRANSMISSIONS_CODE , send_timeout_ack_multicast_pk , -1);
				}
				*/
				
				
				
				/*-------------------------------------------------------------
				
				   MANIPULATION OF CDS-GATEWAYS (BACKBONE INTERCONNECTION)
				
				------------------------------------------------------------*/
				/*
				//Returns an unique array with id of adjacent APs (extracted from the neighborhood table: list of 1-neighbors with different AP
				int get_ap_neigh(int ap_list[], int max){
					int 		pos = 0;
					neigh_cell	*ptr;
					int			i;
				
					for(i=0;i<max;i++)
						ap_list[i] = 0;
					
					//Searches a 1-Neighbor which owns a different AP
					ptr = neighbour_table;
					while((ptr!=NULL)&&(pos<max))
						{
							if ((ptr->id_ap!=my_cds.id_ap) && (ptr->bidirect) && (ptr->hops==1) && (ptr->id_ap!=0) && (ptr->id_ap!=-1) && (my_cds.id_ap!=0) && (my_cds.id_ap!=-1))
								{
									//Search if This AP is nos already in gw[]
									i = 0;
									while((i < pos) && (ap_list[i] != ptr->id_ap))
										i++;
									
									//Adds it in gw[] if not 
									if (ap_list[i] != ptr->id_ap)
										{
											ap_list[pos] = ptr->id_ap;
											pos++;
										}
								}		
							ptr = ptr->next;
						}
					return(pos);
				}
				
				
				//Adds adjacent AP in hello packets
				void advertise_ap_neigh(Packet* pkptr){
					char		field_name[20];
					int			i , pos;
					int			ap_neigh_list [MAX_AP_NEIGH_IN_HELLO];
					
				   	
					//Get an array with gateways (pos contains the number of effective gateways)
					pos = get_ap_neigh(ap_neigh_list , MAX_AP_NEIGH_IN_HELLO);
					for (i=1 ; i < pos+1 ; i++)
						{
							sprintf(field_name,"AP_NEIGH_%d" , i);
							op_pk_nfd_set(pkptr , field_name , ap_neigh_list[i-1]);
						}
					for(i = pos+1 ; i <= MAX_AP_NEIGH_IN_HELLO ; i++)
						{
							sprintf(field_name , "AP_NEIGH_%d",i);
							op_pk_nfd_strip(pkptr , field_name);
						}
				}
				
				//Returns the number of dominatees which are gateways towards an adjacent AP
				int count_nb_ap_neigh_to_different_ap(){
					struct_cds_ap_neigh		*entry;
					int 					nb_ap_neigh = 0;
					int						ap_list[MAX_NB_APS];
					int						i , pos = 0;
					
					//Initializes the temporary of connected APs via dominatees which are gateways 
					for (i=0 ; i<MAX_NB_APS ; i++)
						ap_list [i] = 0;
					
					//For every gateway
					for(i=0; i < op_prg_list_size(my_cds.ap_neigh_list) ; i++)
						{
							entry = op_prg_list_access(my_cds.ap_neigh_list , i);
				
							//If this gateway is one of our dominatees
							if (is_my_dominatee(entry->address))
								{
									//If this ap isn't yet referenced
									i=0;
									while((ap_list[i] != entry->id_ap) && (i < pos) && (ap_list[i] != 0))
										i++;
									if ((ap_list[i] != entry->id_ap) && (entry->id_ap != my_cds.id_ap))
										{
											nb_ap_neigh++;
											ap_list[pos++] = entry->id_ap;
										}
								}
						}
					
					//Returns the result
					return(nb_ap_neigh);
				}
				
				//Returns the  dominatees which are gateways towards an adjacent AP (and the associated id_ap)
				int get_ap_neigh_to_different_ap(struct_ap_dominatee  ap_dominatee_list[MAX_NB_APS] , int max){
					struct_cds_ap_neigh		*entry;
					int 					nb_ap_dominatee;
					int						i , pos = 0;
					
					//Initializes the temporary of connected APs via dominatees which are gateways 
					for (i=0 ; i<MAX_NB_APS ; i++)
						{
							ap_dominatee_list[i].ap 		= 0;
							ap_dominatee_list[i].dominatee 	= 0;
						}
					
					//For every gateway
					nb_ap_dominatee = 0;	
					for(i=0; i < op_prg_list_size(my_cds.ap_neigh_list) ; i++)
						{
							entry = op_prg_list_access (my_cds.ap_neigh_list , i);
							
							//If this gateway is one of our dominatees (NB : one AP don't use dominatees-gateways)
							if ((is_my_dominatee(entry->address))&&(!is_AP))
								{
									//If this ap isn't yet referenced
									i=0;
									while((ap_dominatee_list[i].ap != entry->id_ap ) && (i < pos) && (ap_dominatee_list [i].ap != 0))
										i++;
									
									//Ad this ap and the associated dominatee-gateway
									if ((ap_dominatee_list[i].ap != entry->id_ap) && (entry->id_ap != my_cds.id_ap))
										{
											nb_ap_dominatee++;
											if (nb_ap_dominatee <= max)
												{
													ap_dominatee_list[pos].dominatee 	= entry->address;
													ap_dominatee_list[pos].ap 			= entry->id_ap;
													pos++;
												}
										}
								}
						}
					return(nb_ap_dominatee);
				}
				
				//Returns the number of dominatees which are gateways towards an adjacent AP
				int count_nb_ap_neigh(){
					struct_cds_ap_neigh		*entry;
					int 					nb_ap_dominatee=0;
					int						i;
					
					for (i=0; i < op_prg_list_size(my_cds.ap_neigh_list) ; i++ )
						{
							entry = op_prg_list_access(my_cds.ap_neigh_list , i);
							
							if (is_my_dominatee(entry->address))
								nb_ap_dominatee++;
						}
				
					return(nb_ap_dominatee);
				}
				
				//Returns :
				//-TRUE if the gateway already exists
				//-FALSE else
				Boolean is_a_ap_neigh(int addr){
					struct_cds_ap_neigh	*entry;
					int					i;
						
					for (i=0; i < op_prg_list_size(my_cds.ap_neigh_list) ; i++ )
						{
							entry = op_prg_list_access(my_cds.ap_neigh_list , i);
							
							if (entry->address == addr)
								return(OPC_TRUE);
						}
				
					//Not found
					return(OPC_FALSE);
				}
				
				//Adds a gateway in the list (my_cds.gw) or refresh it
				void add_or_refresh_ap_neigh(int addr, int id_ap){
					struct_cds_ap_neigh		*entry;
					int						i;
					
					//For each registered ap-dominatee-neigh
					for(i=0; i < op_prg_list_size(my_cds.ap_neigh_list) ; i++)
						{
							entry = op_prg_list_access (my_cds.ap_neigh_list , i);
							
							//Entry found, we update it
							if (entry->address == addr)
								{
									entry->timeout 	= op_sim_time() + TIMEOUT_HELLO * INTERVALL_HELLO;
									entry->id_ap		= id_ap;
								}
						}
				
					
					//Entry not found, must add it
					entry = (struct struct_cds_ap_neigh*) op_prg_mem_alloc (sizeof(struct_cds_ap_neigh));
							
					entry->address 	= addr;
					entry->id_ap	= id_ap;
					entry->timeout	= op_sim_time() + TIMEOUT_HELLO * INTERVALL_HELLO;
				
					op_prg_list_insert(my_cds.ap_neigh_list , entry , OPC_LISTPOS_TAIL);
				}
				
				//Register nodes which act as gateways
				void register_ap_neigh(Packet* pkptr){
					char			field_name[20];
					int				id_ap;
					int				address_src;
					int				i;
					
					//First Fields
					op_pk_nfd_get(pkptr , "SRC" , &address_src);
					sprintf(field_name,"AP_NEIGH_1");
					
					//For each ap_neigh declared
					for(i=1 ; (i < MAX_AP_NEIGH_IN_HELLO) && (op_pk_nfd_is_set(pkptr,field_name)) ; i++)
						{
							//Gets the ap for which it is neighbor
							op_pk_nfd_get(pkptr , field_name , &id_ap);
				
							//Adds the source as connector for ap_neigh
							add_or_refresh_ap_neigh(address_src , id_ap);
							
							//Next field
							sprintf(field_name , "AP_NEIGH_%d" , i);
						}
				}
				
				
				//Delete all gateways that have an obsolete timeout
				void delete_timeouted_ap_neigh(){
					struct_cds_ap_neigh		*entry;
					int						i;
				
					for (i= op_prg_list_size(my_cds.ap_neigh_list)-1 ; i >= 0 ; i--)
						{
							entry = op_prg_list_access(my_cds.ap_neigh_list , i);
							
							if (entry->timeout <= op_sim_time())
								{
									free(entry);
									op_prg_list_remove(my_cds.ap_neigh_list , i);
								}
						}
				}
				
				*/
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				/*
				
				-----------------------------------------------------------------------------------------------
				
												CDS of WU and LI
				
				----------------------------------------------------------------------------------------------
				
				
				//I update my cds-state according to my k-neighborhood table
				void cds_maintenance_wu_li(int* arg, int code){
					//min_cell** 	covered_list;
					//int			highest_node;
					//int			highest_weight;
				
				//Initialization
					//covered_list = NULL;
					
				//Build our list of covered nodes in k-neighborhood
					//We must find the 1-neighbors which have the highest number of nodes with an higher weight than me
					//find_node_with_highest_good_degree(&highest_node, &highest_weight);
				
					//sprintf(msg,"HIGHEST NODE=%d with HIGHEST WEIGHT=%d (my weight = %d)\n",highest_node,highest_weight,my_weight.value);
					//cluster_message(msg);
					
					//Initliazes all flags "done" to null in in NNT
					//neigh_neigh_table_done_flag_init();
					
					//Add the cds of higher weight, rooted at high_node
					//covered_list = (min_cell**) op_prg_mem_alloc (sizeof(min_cell*));
					//*covered_list = NULL;
					//add_node_in_covered_list(highest_node , highest_weight , 1 , covered_list); 
					//add_1_neighbors_of_higher_weight(highest_node , covered_list);
					
					//Debug
					//print_covered_list(covered_list);
					
					//Computes my new state -> either dominatee or dominator
					//my_cds.state 	= get_state_wu_li(covered_list);
					
					//sprintf(msg,"My state = %d\n",my_cds.state);
					//cluster_message(msg);
					
				}
				
				
				//I received one hello packet -> I add/update the neighbor_table associated to the source
				void update_the_neighbor_table_associated_to_one_neighbor(Packet* pkptr){
					neigh_table		*table_tmp ;
					min_cell		*cell_tmp ;
					int				src_addr , src_weight , addr_temp , weight_temp , hops_temp , bidirect_temp, ttl;
					int				i;
					Boolean			is_fields_overflow;
					char			msg[150];
				
					//Gathers info from the packet
					op_pk_nfd_get(pkptr, "SRC"		, &src_addr);
					op_pk_nfd_get(pkptr, "WEIGHT"	, &src_weight);
					op_pk_nfd_get(pkptr, "TTL"		, &ttl);
				
					
					if (DEBUG>0)
						{
							sprintf(msg,"I received an hello packet from %d -> I add/update its neighbor_table that I stored\n",src_addr);
							cluster_message(msg);
						}
					
					//I search in the table the entry corresponding to the actual source (It can be not present (It's the first hello I recieved from it))
					table_tmp = neighbor_table_of_table;
					while ((table_tmp != NULL) && (table_tmp->address != src_addr))
						{
							table_tmp = table_tmp->next;
						}
					
					//There exists an entry -> We delete the whole neighbors_table of this entry)
					if ((table_tmp != NULL) && (table_tmp->address == src_addr))
						{
							table_tmp->weight	= src_weight;
							table_tmp->hops		= ((k-1) - ttl) + 1;
							table_tmp->timeout	= op_sim_time();
				
							if (DEBUG>0)
								cluster_message("Added Entry :\nExisting cell, We delete its neighbors table\n");
							
							while( (table_tmp->table) != NULL)
								{
									//For each cell, I store this cell in a temporary variable, I bypass this cell in the chained list, and I delete it
									cell_tmp 			= (table_tmp->table);
									table_tmp->table	= (table_tmp->table)->next;
									free(cell_tmp);					
								}
						}
					//No entry -> we add one (empty by default)
					else if (table_tmp == NULL)
						{
							//Allocation of a new cell
							table_tmp = (struct neigh_table*) op_prg_mem_alloc (sizeof (neigh_table));
							if (table_tmp==NULL)
								printf("error in the memory allocation for the creation of a new entry in the neighborhood tables of tables");			
				
							//Default Assignments
							table_tmp->table 	= NULL;
							table_tmp->address 	= src_addr;
							table_tmp->weight	= src_weight;
							table_tmp->timeout	= op_sim_time();
							table_tmp->hops		= ((k-1) - ttl) + 1;
							
							if (DEBUG>0)
								{
									cluster_message("Added Entry :\n");
									sprintf(msg,"New cell : addr=%d, weight=%d, hops=%d\n",table_tmp->address, table_tmp->weight, table_tmp->hops);
									cluster_message(msg);
								}			
								
							//Updates pointers in chained list
							table_tmp->next = neighbor_table_of_table;
							neighbor_table_of_table = table_tmp;
						}
					else
						printf("Error : the loop is terminated but We have not the good entry -> Impossible!\n");
					
					
					//We store all the 1-neighbors of this node in the cell of the neighbor table of table
					i = 1;
					is_fields_overflow = ((i>MAX_FIELDS_IN_HELLO_KTABLE)&&(hello_method==HELLO_METHOD_KTABLE)) || ((hello_method==HELLO_METHOD_RELAY)&&(i>MAX_FIELDS_IN_HELLO_RELAY)) ;
					while (op_pk_nfd_is_set(pkptr , hello_fields_names[i].address) && !is_fields_overflow )
						{
							op_pk_nfd_get(pkptr , hello_fields_names[i].bidirect , &bidirect_temp);
							if (bidirect_temp) 
								{
									//Memory Allocation for a new cell in the list of neighbours
									cell_tmp = (struct min_cell*)op_prg_mem_alloc(sizeof(min_cell));
									if (cell_tmp==NULL)
										printf("error in the memory allocation for the creation of a new cell in the table of table of neighbors");
						
									//Gathers address
									op_pk_nfd_get(pkptr , hello_fields_names[i].address , &addr_temp);
									op_pk_nfd_get(pkptr , hello_fields_names[i].weight , &weight_temp);
							
									//Hops
									if (hello_method == HELLO_METHOD_RELAY)
										hops_temp = 1;										//Relay : I declare only 1-neighbors
									else if (hello_method == HELLO_METHOD_KTABLE);
									op_pk_nfd_get(pkptr , hello_fields_names[i].hops , &hops_temp);	//Ktable : inscribed in special fields
								
									//Information
									cell_tmp->address 	= addr_temp;
									cell_tmp->weight 	= weight_temp;
									cell_tmp->hops		= hops_temp;
							
									if (DEBUG>0)
										{
											sprintf(msg,"	-> addr=%d, weight=%d, hops=%d\n" , cell_tmp->address , cell_tmp->weight , cell_tmp->hops);
											cluster_message(msg);
										}
				
									//Updates ordering in chained list
									cell_tmp->next		= table_tmp->table;
									table_tmp->table	= cell_tmp;
									i++;
								}
						}	
				}
				
				//adds a node in covered list
				void add_node_in_covered_list(int addr , int weight , short hops , min_cell** covered_list){
					min_cell 	*list_ptr , *cell_tmp;
					char		msg[150];
					
					//We search if the entry already exists
					list_ptr = *covered_list;
					while ((list_ptr != NULL) && (list_ptr->address != addr))
						{
							list_ptr = list_ptr->next;
						}
					
					//The node is not present -> We add it (else we do nothing)
					if (list_ptr == NULL)
						{
							//Memory Allocation for a new cell in the list
							cell_tmp = (struct min_cell*)op_prg_mem_alloc(sizeof(min_cell));
							if (cell_tmp==NULL)
								printf("error in the memory allocation for the creation of a new cell in the list of covered nodes ");
							
							//Real Information Assignment
							cell_tmp->address 	= addr;
							cell_tmp->weight	= weight;		//Set but useless ....
							cell_tmp->hops		= hops;
				
							sprintf(msg,"	->ajout du noeud %d hops=%d, weight=%d\n",addr,hops,weight);
							cluster_message(msg);
							
							//Pointers Update
							cell_tmp->next	= *covered_list;
							*covered_list	= cell_tmp;		
						}
				}
				
				//Add all the 1-Neighbors with higher weight and recursively all the 1-neighbors of these 1-neighbors of higher weight
				void add_1_neighbors_of_higher_weight(int addr, min_cell** covered_list){
					neigh_table		*table_tmp ;
					min_cell		*cell_tmp ;
					char			msg[250];
				
					table_tmp = neighbor_table_of_table;
					while ((table_tmp != NULL) && (table_tmp->address != addr))
						{
							//Next Neighbor
							table_tmp = table_tmp->next;
						}
				
					//If We have The good entry -> We observe each of its 1-Neighbors
					if ((table_tmp != NULL) && (table_tmp->address == addr) && (table_tmp->done == OPC_FALSE))
						{
							sprintf(msg,"On ajoute les 1-voisins de %d\n",addr);
							cluster_message(msg);
							
							//Set the flag "done" for this node
							table_tmp->done		= OPC_TRUE;
							
							//For each 1-neighbor
							cell_tmp = table_tmp->table;
							while (cell_tmp!=NULL)
								{
									//If The weight is higher than my own weight 
									//	-> I add its own 1-neighbors in my covered list
									//	-> I observe recursively if its 1-Neighbors have an higher weight than me
									if ( (cell_tmp->weight > my_weight.value))// && (cell_tmp->hops == 1) )
										{
											add_1_neighbors_of_higher_weight( cell_tmp->address, covered_list);
											add_node_in_covered_list(cell_tmp->address , cell_tmp->weight , cell_tmp->hops , covered_list); 
										}
									//Not higher weight -> I add this list as covered, but not relay
									else //if (cell_tmp->hops == 1)
										add_node_in_covered_list(cell_tmp->address , cell_tmp->weight , cell_tmp->hops , covered_list); 
									
									//nect Cell
									cell_tmp = cell_tmp->next;
								}
						}
					else if (table_tmp == NULL)
						{
							sprintf(msg,"We dind't find %d in table of table of neighbors\n",addr);
							//cluster_message(msg);
						}
					//Else : we have already handled this node !
				}
				
				
				//Print the content of the covered list "list"
				void print_covered_list(min_cell** list){
					min_cell*	ptr;
					char		msg[150];
					
					sprintf(msg,"\n-------------\nCovered List of %d (weight=%d)\n------------------\n",my_address,my_weight.value);
					cluster_message(msg);
					ptr = *list;
					while(ptr!=NULL)
						{
							sprintf(msg,"-> %d | hops=%d | weight=%d\n",ptr->address,ptr->hops,ptr->weight);
							cluster_message(msg);
							ptr = ptr->next;
						}
					sprintf(msg,"\n-------------------\n FIN COVERED \n---------------------------\n");
					cluster_message(msg);
					sprintf(msg,"\n---------------\nNeighbor Table of Table\n------------------\n");
					cluster_message(msg);
					print_neighbors_table_of_table();
					sprintf(msg,"\n-------------------\n FIN NEIGH \n---------------------------\n");
					cluster_message(msg);
				}
				
				//Find our 1-Neighbor which have the higher degree of nodes with a weight superior than my own weight
				//We must recompute this weight : I can change my weight -> it changes these degrees
				//Returns 1 if no 1-neighbor was found
				void find_node_with_highest_good_degree(int *final_node, int* final_weight){
					neigh_table		*table ;
					min_cell		*cell;
					int 			highest_node , highest_degree , highest_weight;
					int				degree_temp;
					
					//Default value for the highest node
					highest_node 	= -1;
					highest_weight	= -1;
					highest_degree 	= -1;
					
					//We search in the neighbor of neighbor table
					table = neighbor_table_of_table;
					while(table!=NULL)
						{
							if ((table->hops==1)&&(table->weight > my_weight.value))
								{				
									degree_temp = 0;
									cell = table->table;
									while (cell!=NULL)
										{
											if (cell->weight > my_weight.value)
												degree_temp++;
											cell = cell->next;
										}
									if (degree_temp > highest_degree)
										{
											highest_node 	= table->address;
											highest_degree 	= degree_temp;
											highest_weight	= table->weight;
										}
								}
						
							table = table->next;
						}
					
					//Updates final returned values
					*final_node		= highest_node;
					*final_weight	= highest_weight;
				}
				
				//Initliazes all flags "done" to null in in Neighbor of Neighbor Table (NNT)
				void neigh_neigh_table_done_flag_init(){
					neigh_table		*table;
					
					table = neighbor_table_of_table;
					while(table != NULL)
						{
							table->done		= OPC_FALSE;
							table			= table->next;
						}
				}
				
				//Return my state : dominator or dominatee
				int get_state_wu_li(min_cell** covered_list){
					char		msg[250];
					neigh_cell	*neigh;
					min_cell	*cell;
					Boolean		covered;
					
					//Initialization*
					covered = OPC_TRUE;
					
					//For each node in neighbor table -> search if it is covered
					neigh = neighbour_table;
					while ((neigh!=NULL))// && (covered))
						{
							if (neigh->hops == 1)
								{
									//Search if an entry exists in covered_list
									cell = *covered_list;
									while ((cell!=NULL) && (cell->address != neigh->address))
										{
											cell = cell->next;
										}
									//If not --> not all my neighbors are covered
									if (cell==NULL)
										{
											covered = OPC_FALSE;		
											sprintf(msg,"!!-> Node not covered : %d\n",neigh->address);
											cluster_message(msg);
										}
								}
							neigh = neigh->next;
						}
					
					//Return value
					if (covered)
						return (DOMINATEE);
					else
						return (DOMINATOR);
				}
				
				*/
				
				
				
				
				
				/*
				
				
				//Returns the address of one 1-neighbor with an higher weight
				int get_one_higher_1_neighbor(){
					int			i;
					neigh_wu*	neigh;
					
					for(i=0; i<op_prg_list_size(neighbor_table_wu_li) ; i++)
						{
							neigh = op_prg_list_access(neighbor_table_wu_li , i);
							if (neigh->weight > my_weight.value)
								return(neigh->address);
							if ((neigh->weight == my_weight.value) && (neigh->address > my_address))
								return(neigh->address);
						}
					return(-1);
				}
				
				//returns the list of higher weight nodes
				List* get_list_of_higher_weight_nodes(){
					List		*higher_nodes;
					neigh_cell	*ptr;
					
					//initialisation
					higher_nodes = op_prg_list_create();
					
					//Neighbor table
					ptr = neighbour_table;
					while(ptr!=NULL)
						{
							if (  ((ptr->weight>my_weight.value) && (ptr->address != my_address)) || ((ptr->weight == my_weight.value) && (ptr->address>my_address))  )
								if ((ptr->bidirect) && (ptr->hops <= k_cds-1))
									add_int_in_list(higher_nodes , ptr->address);
						
							ptr = ptr->next;
						}	
					
					//End
					return(higher_nodes);
				}
				
				//returns the address of a 1-neighbor with an higher weight
				int get_1_neighbor_with_higher_weight(){
					neigh_wu	*neigh;
					int			i;
					
					//Search the root
					for(i=0; i<op_prg_list_size(neighbor_table_wu_li) ; i++)
						{
							neigh = op_prg_list_access(neighbor_table_wu_li , i);
							
							if ( ((neigh->weight > my_weight.value) && (neigh->address != my_address)) || ((neigh->weight == my_weight.value) && (neigh->address > my_address)) )
								if (neigh->bidirect)
									return(neigh->address);
						}
					return(-1);
				}
				
				
				//Is neigh a bidirect neighbor of addr ?
				Boolean is_a_declared_bidirect_neighbor(int addr , int addr_neigh){
					int			i , j;
					neigh_wu	*neigh;
					neigh_min	*neigh_list;
					int			addr_pos = -1;
				
					//Search addr
					for(i=0; (i<op_prg_list_size(neighbor_table_wu_li)) && (addr_pos==-1) ; i++)
						{
							neigh = op_prg_list_access(neighbor_table_wu_li , i);
							if ((neigh->address == addr) && (neigh->bidirect))
								addr_pos = i;
						}
					
					//adds the root and create the CDS starting from it
					if (addr_pos != -1)
						{
							neigh = op_prg_list_access(neighbor_table_wu_li , addr_pos);
				
							//Looks up its neighbors list
							for(j=0 ; j < op_prg_list_size(neigh->neighbors) ; j++)
								{
									//gets the j° neighbor and regards if it is the neigh I am searching....
									neigh_list = op_prg_list_access(neigh->neighbors, j);
									if (neigh_list->address == addr_neigh)
										return(OPC_TRUE);
								}
						}
					
					//The bidirect link was not found
					return(OPC_TRUE);
				
				}
				
				//returns a CDS of higher weight nodes, rooted at 'root' (table -> contains only k_cds-neighbors)
				void construct_cds_from(List* cds , List* covering , int root){
					int			root_pos=-1;
					int			i , j;
					neigh_wu	*neigh;
					neigh_min	*neigh_list;
					char		msg[1000];
					
					//Search the root
					for(i=0; (i<op_prg_list_size(neighbor_table_wu_li)) && (root_pos==-1) ; i++)
						{
							neigh = op_prg_list_access(neighbor_table_wu_li , i);
							if ((neigh->address == root) && (neigh->bidirect))
								root_pos = i;
						}
					
					//adds the root and create the CDS starting from it
					if (root_pos != -1)
						{
							neigh = op_prg_list_access(neighbor_table_wu_li , root_pos);
							add_int_in_list(cds, 		neigh->address);
							add_int_in_list(covering, 	neigh->address);
							
							if (DEBUG>LOW)
								{
									sprintf(msg, "%d is added to the CDS (CDS=%s)\n", neigh->address , int_list_to_str(cds));
									cluster_message(msg);
								}			
							
							//Looks up its neighbors list
							for(j=0 ; j < op_prg_list_size(neigh->neighbors) ; j++)
								{
									//gets the node
									neigh_list = op_prg_list_access(neigh->neighbors, j);
									
									//Adds the node as covered
									add_int_in_list(covering, neigh_list->address);
									
									//And if higher weight -> adds it to the CDS
									if (  ((neigh_list->weight > my_weight.value) && (neigh_list->address != my_address))   ||     ((neigh_list->weight == my_weight.value) && (neigh_list->address > my_address))  )
										{						  
											if (!is_int_in_list(cds, neigh_list->address))
												//verification that this node declares ourself as a bidirect neighbor (perhaps, the information is changing)
												if (is_a_declared_bidirect_neighbor(neigh_list->address , root))
													{
														//printf("ouap\n");
														construct_cds_from(cds, covering , neigh_list->address);
													}
										}
								}
						}
				}
				
				
				//Is covering a complete covering of all my neighbors ?
				Boolean is_a_complete_covering(List* covering){
					char		msg[200];
					neigh_cell	*ptr;
					
					ptr= neighbour_table;
					while(ptr != NULL)
						{
							if ((ptr->bidirect) && (ptr->hops<=k_cds) && (!is_int_in_list(covering, ptr->address)))
								{
									if (DEBUG>LOW)
										{
											sprintf(msg, "%d not covered\n", ptr->address);
											cluster_message(msg);
										}
									return(OPC_FALSE);
								}
							ptr = ptr->next;
						}
					return(OPC_TRUE);
				}
				
				//Return my state : dominator or dominatee
				int get_state_wu_li(){
					List	*cds;
					List	*covering;
				//	List	*higher_weight_nodes;
					int		root;
					char	msg[200];
						
					if (DEBUG>LOW)
						print_neighbour_table();
					
					//initialization
					cds = op_prg_list_create();
					covering = op_prg_list_create();
					
					if (DEBUG>LOW)
						{
							sprintf(msg, "CDS -> computes the new state at %f (my weight = %d)\n", op_sim_time() , my_weight.value);
							cluster_message(msg);
						}
					
					//Constructs a cds from the root + covering of this cds
					root = get_1_neighbor_with_higher_weight();	
					if (root == -1)
						return(DOMINATOR);
					construct_cds_from(cds , covering , root);	
					
					if (DEBUG>LOW)
						{
							sprintf(msg, "CDS obtained (root %d): %s\n", root , int_list_to_str(cds));
							cluster_message(msg);
							sprintf(msg, "Covering obtained : %s\n", int_list_to_str(covering));	
							cluster_message(msg);
						}	
					
					//Is the CDS a complete covering ?
					if (!is_a_complete_covering(covering))
						{
							if (DEBUG>LOW)
								{
									sprintf(msg, "not a complete covering\n\n\n");
									cluster_message(msg);
								}
							//Lists destruction
							op_prg_mem_free(cds);
							return(DOMINATOR);		
						}
					if (DEBUG >LOW)
						{
							sprintf(msg, "covering total\n");
							cluster_message(msg);
						}
							   
					//The list of higher weight nodes = computed cds ?	
					if (DEBUG>LOW)
						cluster_message("ok, I am useless -> dominatee\n\n\n");
					
					//Lists destruction + final result
					op_prg_mem_free(cds);
					return(DOMINATEE);		
				}
				*/
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (7,cdcl_process_cluster_cds_process)


			/** state (OBSOLETE) exit executives **/
			FSM_STATE_EXIT_UNFORCED (3, "OBSOLETE", "cdcl_process_cluster_cds_process () [OBSOLETE exit execs]")
				{
				}


			/** state (OBSOLETE) transition processing **/
			FSM_TRANSIT_MISSING ("OBSOLETE")
				/*---------------------------------------------------------*/



			/** state (PK From LOWER) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "PK From LOWER", "cdcl_process_cluster_cds_process () [PK From LOWER enter execs]")
				{
				// ------- Common Temporary Variables ------
				id_cell		*ptr,*ptr2;
				Packet		*pk_dest , *pkptr ;
				int			i;
				char		msg[200];
				char		str[20];								//For variable name fields
				
				// ---------- Neighbourhood --------------
				int 		address_src , address_dest, address_relay =0, address_src_init , address_dest_final , dest ;
				int			type_packet , ttl , id;
				int			state ;	  
				Boolean		is_relay_hello_required;
				
				// ---------------- Acks -----------------
				int			is_changed;								//Test of loop
				ret_cell*	ptr_ret;
				
				// ---------------- CDS -----------------
				short		not_id_add;								//to prevent to add the couple id/address i the id_table
				int			state_src , weight_src;					//MIS
				int			dest_id;	
				int			addr_father , father_hops;
					
				// ------------ Hellos AP -------------
				int			id_ap , old_weight, new_weight , id_last_ap_hello;
				ap_hellos*	ptr_ap_hello;
				
				// --------- CDS Reconnection---------
				int 		src_init;								//The initiator of the cds reconnect packet
				int 		dest_final;								//The final destination of the cds reconnect packet reply
				neigh_cell	*ptr_neigh;
				short		is_father_alive, is_father_gone;
				int			id_ap_hello_in_pk;
				ap_hellos	*ptr_ap;
				
				// -------------- Cluster --------------
				int			address_ch , id_asked , ch_hops;
				Boolean		valid_clusterhead;						//Our clusterhead is valid or not (it depends on the cluster maintenance process)
				
				// ---------- BB Multicast ------------
				int			stat_id = 0;
				char		field_name[20];
				
				// --------   HiGHER LAYER -------------
				Boolean		is_pk_from_son_or_father;
				Boolean		is_pk_from_bb;
				
				
				// -- The conditions to treat a packet  --
				Boolean		is_broadcast;
				Boolean 	is_unicast_for_me;
				Boolean		is_ttl_enough;
				Boolean		is_a_retry;
				Boolean		is_pk_not_seen;
				Boolean		is_pk_from_bidirectional;
				Boolean		is_unidirect_authorized;
				Boolean		is_pk_from_cds;
				Boolean		is_pk_type_for_cluster;
				Boolean		is_pk_type_for_cds;
				Boolean		is_pk_type_for_bb_flooding;
				Boolean		is_pk_type_for_ap_unicast;
				Boolean		is_pk_type_for_higher;
				Boolean		is_pk_type_for_paging;
				Boolean		is_pk_data_or_ack;
				Boolean		is_pk_bb_multicast;
				Boolean		is_wireless;
				Boolean		must_relay_hello;
				
				
				/*------------------------------------------------------------------------------------------	
													   INCOMING PACKET 
				-------------------------------------------------------------------------------------------*/					
				if (op_intrpt_code() != WAIT_STATE_CODE)
					pkptr = op_pk_get (op_intrpt_strm ());
				else
					pkptr = get_next_pk_in_wait_state();				//When I bufferize a packet for cds construction (my state was not yet determined)
				
				
				//Gathers some infos
				op_pk_nfd_get(pkptr,"SRC",			&address_src);
				op_pk_nfd_get(pkptr,"RELAY",		&address_relay);
				op_pk_nfd_get(pkptr,"DEST",			&address_dest);
				op_pk_nfd_get(pkptr,"DEST_FINAL",	&address_dest_final);
				op_pk_nfd_get(pkptr,"PK_ID",		&id);
				op_pk_nfd_get(pkptr,"STAT_ID",		&stat_id);
				op_pk_nfd_get(pkptr,"TTL",			&ttl);
				op_pk_nfd_get(pkptr,"OPTION_TYPE",	&type_packet);
				not_id_add = OPC_FALSE;
				
				
				
				
				/*------------------------------------------------------------------------------------------	
													   NOT SLEEPING -> I treat the packet 
				-------------------------------------------------------------------------------------------*/					
				
				if (!is_sleeping.value)
				{
				
				
				//Computes the energy consumtion
				energy_decreases(RECEIVED_COEFF_CONSUMPTION*op_pk_total_size_get(pkptr)/8+RECEIVED_SLOPE_CONSUMPTION);
				
				
				
				/*------------------------------------------------------------------------------------------	
													   CONDITIONS FOR PKS 
				-------------------------------------------------------------------------------------------*/					
				//Determination of different conditions to handle the packet
				is_broadcast 				=	((address_dest == -1)&&(address_src != my_address));
				is_unidirect_authorized 	=	(((type_packet == HELLO_PK_TYPE) && ((address_relay == address_src)||(!is_unidirectional_link(address_relay)))) || ((type_packet == CDS_MIS_PK_TYPE)&&(ttl < k_cds))  );	//hello packet (normal or cds) : for an hello -> discovering of new bidirect links, and for hello+cds -> relay of packets (without changing source)
				is_pk_from_bidirectional	=	(!is_unidirectional_link(address_src) || is_unidirect_authorized); 						//The packet comes from a birdirectional link or it is a special packet
				
				is_unicast_for_me 			=	(address_dest == my_address);
				is_ttl_enough 				=	(ttl>0);
				is_a_retry 					=	(op_intrpt_code() == WAIT_STATE_CODE);
				is_pk_not_seen 				=	((pk_not_seen(id,address_src)) || is_a_retry );
				is_pk_data_or_ack 			=	(type_packet == DATA_PK_TYPE) || (type_packet == ACK_UNICAST_PK_TYPE); 
				is_pk_bb_multicast 			=	(type_packet == BACKBONE_PK_TYPE); 
				
				is_pk_from_cds 				=	((my_cds.state == DOMINATOR)&&((address_src == my_cds.father)||(is_my_son(address_src))));
				is_pk_type_for_cluster 		=	((type_packet == HELLO_CLUSTER_PK_TYPE) || (type_packet == HELLO_CLUSTERHEAD_PK_TYPE) || (type_packet == JOIN_CLUSTER_PK_TYPE) || (type_packet == CON_CLUSTER_PK_TYPE) || (type_packet == REP_CON_CLUSTER_PK_TYPE));
				is_pk_type_for_cds			=	((type_packet == BREAK_CDS_PK_TYPE) || (type_packet == USELESS_DOMINATOR_PK_TYPE) || (type_packet == HELLO_PK_TYPE) || (type_packet == SLEEPING_NODE_PK_TYPE));
				is_pk_type_for_cds			=	(is_pk_type_for_cds || (type_packet == CDS_MIS_PK_TYPE) || (type_packet == CDS_JOIN_PK_TYPE) || (type_packet==CDS_REVERSE_JOIN_PK_TYPE));
				is_pk_type_for_cds			=	(is_pk_type_for_cds || (type_packet == AP_HELLO_PK_TYPE) || (type_packet == CDS_RECONNECT_PK_TYPE) || (type_packet == CDS_RECON_REP_PK_TYPE) || (type_packet == RECONNECT_INIT_PK_TYPE) || (type_packet == NOTHING_NEIGH_CDS_PK_TYPE));
				is_pk_type_for_bb_flooding	=	(type_packet == BACKBONE_PK_TYPE) || (type_packet == BACKBONE_WITH_CONNECT_PK_TYPE);
				is_pk_type_for_ap_unicast	=	(type_packet == AP_UNICAST_PK_TYPE);
				is_pk_type_for_higher		=	((type_packet >= DATA_PK_TYPE) && (type_packet <= RDELETE_PK_TYPE));
				is_pk_type_for_paging		=	(type_packet >= PAGING_REQ_PK_TYPE) && (type_packet <= 10+PAGING_REQ_PK_TYPE);
				is_wireless					=	1;
				
				//DEBUG
				if (type_packet == RREQ_PK_TYPE)
					{
						//sprintf(msg,  "%f : %d (%d) -> %d (I %d, state %d) (is_not_seen %d) (pk_type %d) (id %d) (stream %d)\n", op_sim_time() , address_relay , address_src , address_dest , my_address , my_cds.state ,  is_pk_not_seen , type_packet , id , op_intrpt_strm ());
						//test_message(msg);
					}
				
				
				/*----------------------------------------------------------------------------------------------------------------------------------
				------------------------------------------------------------------------------------------------------------------------------------
				
																			CLUSTERING
				
				------------------------------------------------------------------------------------------------------------------------------------
				----------------------------------------------------------------------------------------------------------------------------------*/
						
				if ( (is_broadcast || is_unicast_for_me) && is_wireless && is_ttl_enough && is_pk_not_seen && is_pk_from_cds && is_pk_type_for_cluster)
					{
						if (my_cds.state!=DOMINATOR)
							{
								printf("!!! error !!!! A not dominator treats a cluster pk (%d)\n",my_address);
								op_pk_print(pkptr);
							}
				
						//Lookup up the type of packet
						switch(type_packet)
							{
								//------------------------------------------	
								//		(NEIGHBOURHOOD KNOWLEDGE)
								//-------------------------------------------
								case HELLO_CLUSTER_PK_TYPE:
										op_pk_nfd_get(pkptr,"SRC_INIT",&src_init);
										op_pk_nfd_get(pkptr,"CLUSTERHEAD",&address_ch);
				
										add_cluster_init_neighbour(src_init);
								
										if (pk_not_seen(id,src_init))
											{
												add_address_id_couple(src_init,id);
												update_cluster_infos(pkptr);
				
												//Procedure specific to clustering
												switch (cluster_algos_type)
													{
														case THEO_OLD :
														case THEO_NEW :
														case THEO_NEW2 :
															//If the normal-hello was lost, we even initiate the sending of cluster-hellos, and the construction of one cluster
															if (my_clusterhead.construct_cluster==0)
																{
																	my_clusterhead.construct_cluster = 1;
																	op_intrpt_schedule_self (op_sim_time() , CONSTRUCT_CLUSTER_CODE);
																	op_intrpt_schedule_call (op_sim_time() , CLUSTER_HELLO_CODE , cluster_hello , -1);
																}
									
															//Change clusterhead if we have a clusterhead in our neighbourhood
															if ((src_init==address_ch) && (my_clusterhead.address==0) && (is_wireless))
																{
																	if (DEBUG>LOW)
																	   {
																	   		sprintf(msg,"I had no clusterhead and one of my neighbor is clusterhead I choose one\n");
																			cluster_message(msg);
																		}
																	change_clusterhead(src_init,address_src,(k_cluster-k_cds)-ttl+1);		
																	op_intrpt_schedule_self(op_sim_time()+INTERVALL_HELLO,CLUSTER_MAINTENANCE_CODE);
																	send_decision_cluster();									
																}
															break;
														case NONE :
																//nothing to do
															break;
													}
												
												//I relay the packet if it comes from one of my son or my father (I use the tree-structure of the CDS)
												if ((ttl>1)&&(is_wireless))
													{
														op_pk_nfd_set(pkptr,"TTL",--ttl);
														op_pk_nfd_set(pkptr,"SRC",my_address);
														pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
													}
				
											}
									break;
									
								//------------------------------------------	
								//		CLUSTERHEAD DECISION DECLARATION 
								//-------------------------------------------
								case JOIN_CLUSTER_PK_TYPE:
										op_pk_nfd_get(pkptr,"SRC_INIT",&src_init);
										op_pk_nfd_get(pkptr,"CLUSTERHEAD",&address_ch);
										if ((pk_not_seen(id,src_init))&&(address_ch==src_init))							
											{
												add_address_id_couple(src_init,id);
								
												//Updates the associated infos
												update_cluster_infos(pkptr);
										
												//The message is from a clusterhead
												if (my_clusterhead.address==0)
													{
														if (DEBUG > LOW)
															{
																cluster_message("I had no clusterhead and I received a clusterhead decision, I choose one\n");
																change_clusterhead(src_init,address_src,(k_cluster-k_cds)-ttl+1);		
															}
														op_intrpt_schedule_self(op_sim_time()+INTERVALL_HELLO,CLUSTER_MAINTENANCE_CODE);
														send_decision_cluster();
													}
									
												//I relay the packet if it comes from one of my son or my father (I use the tree-structure of the CDS)
												if (ttl>1)
													{
														ttl--;
														op_pk_nfd_set(pkptr,"TTL",ttl);
														op_pk_nfd_set(pkptr,"SRC",my_address);
														pk_send(op_pk_copy(pkptr));
													}					
											}
									
									
									
									break;				
								//------------------------------------------	
								//		CLUSTERHEAD HELLOS 
								//-------------------------------------------
								//Old Maintenance
								case HELLO_CLUSTERHEAD_PK_TYPE:				
										op_pk_nfd_get(pkptr,"CLUSTERHEAD",&address_ch);
										if (pk_not_seen(id,address_ch))
											{
												add_address_id_couple(address_ch,id);
												if (my_clusterhead.address==address_ch)
													{
														my_clusterhead.relay = 		address_src;
														my_clusterhead.hops = 		(k_cluster-k_cds)-ttl+1;
														my_clusterhead.last_seen = 	op_sim_time();
														my_clusterhead.last_id = 	id;
														my_clusterhead.nb_recon_try = 0;
													}
								
												//I schedule the maintenance process : I found a clusterhead !
												if (my_clusterhead.address==0)
													op_intrpt_schedule_self(op_sim_time()+INTERVALL_HELLO,CLUSTER_MAINTENANCE_CODE);
														
												//I have no clusterhead or my old clusterhead is perhaps dead, I choose it as my new clusterhead
												if ((my_clusterhead.address != my_address) && ((my_clusterhead.address==0)||(my_clusterhead.last_seen < op_sim_time()-2.1*INTERVALL_CLUSTERHEAD_HELLO)))
													{
														change_clusterhead(address_ch,address_src,(k_cluster-k_cds)-ttl+1);
														cluster_message("I change my clusterhead (the precedent is perhaps dead : I don't saw it for a long time)!\n");
													}
								
												//I am useless, i choose the source as clusterhead
												if ((my_clusterhead.last_time_usefull < op_sim_time() - 2.1*INTERVALL_HELLO)&&(my_clusterhead.address==my_address))
																	{
												//Stats about ch changes
												if ((my_clusterhead.address!=my_address)&&(my_clusterhead.address!=address_ch))
													nb_changes_of_clusterheads++;
																													
												//Change my clusterhead, and stop to send "clusterhead-hellos"
												if ((my_clusterhead.last_time_usefull < op_sim_time()- .1*INTERVALL_HELLO) && (my_clusterhead.address==my_address))
													{
														change_clusterhead(address_ch,address_src,(k_cluster-k_cds)-ttl+1);
														op_intrpt_disable(OPC_INTRPT_SELF,CLUSTERHEAD_HELLO_CODE,OPC_TRUE);
														if (DEBUG>LOW)
															{
																sprintf(msg,"%d is a useless clusterhead at %f (since %f), it chooses %d\n",my_address,op_sim_time(),my_clusterhead.last_time_usefull,address_ch);
																cluster_message(msg);
															}
													}
											}
								
									if ((ttl>1)&&(my_clusterhead.address==address_ch))
										{
											ttl--;
											op_pk_nfd_set(pkptr,"TTL",ttl);
											op_pk_nfd_set(pkptr,"SRC",my_address);
											pk_send(op_pk_copy(pkptr));
										}					
									}
									break;
									
								//------------------------------------------	
								//		FORWARD CLUSTERHEAD CONNECT 
								//-------------------------------------------
								case CON_CLUSTER_PK_TYPE:
								
										//op_pk_nfd_get(pkptr,"RELAY1",&src_init);
										op_pk_nfd_get(pkptr,"SRC_INIT",&src_init);
									
										if (pk_not_seen(id,src_init))
											{
												op_pk_nfd_get(pkptr,"CLUSTERHEAD",&address_ch);
				
												//Condition to have a valid clusterhead (it depends on our cluster maintenance process)
												switch (cluster_algos_type)
													{
														case THEO_NEW :
														case THEO_NEW2 :
															valid_clusterhead = (my_clusterhead.relay != address_src);
														break;
														case THEO_OLD :
															op_pk_nfd_get(pkptr,"LAST_CLUSTERHEAD_ID",&id_asked);
															valid_clusterhead = (my_clusterhead.last_id >= id_asked);
														break;
													}
												
												//Condition to reply
												if ((my_clusterhead.hops<k_cluster-k_cds)&&((my_clusterhead.address==my_address) || ((my_clusterhead.address!=address_ch)&&(my_clusterhead.address!=0)&&(valid_clusterhead)) ) )
													{
														reply_connect_ch(pkptr);
														add_address_id_couple(src_init,id);
													}
												//We forward the request only with the old cluster_maintenance
												else
													{
														if (cluster_algos_type == THEO_OLD)											
															{
																//Forwards the reconnection packet												
																forward_connect_ch (pkptr);
															}
														add_address_id_couple(src_init,id);
													}
											}
									break;
									
									
									
								//------------------------------------------	
								//		FORWARD REPLIES
								//-------------------------------------------
								case REP_CON_CLUSTER_PK_TYPE:	
									
										op_pk_nfd_get(pkptr,"CLUSTERHEAD",&address_ch);
										op_pk_nfd_get(pkptr,"RELAY1",&src_init);
									
										//We directly add candidate if we have a proactive maintenance approach
										//If we have THEO_NEW2 maintenance, reconnection pkts are useless
										if (cluster_algos_type == THEO_NEW)
											add_cluster_reconnect_candidate(pkptr);
				
										//We change our clusterhead with a reconnect-reply if we have a reactive cluster maintenance approach
										if ((cluster_algos_type == THEO_OLD) && ((my_clusterhead.construct_cluster==5)||(my_clusterhead.last_seen < op_sim_time() - TIMEOUT_CLUSTERHEAD * INTERVALL_CLUSTERHEAD_HELLO)))
											{
												if (DEBUG>LOW)
													cluster_message("I change my clusterhead after a reconnection reply (I was disconnected)\n");
												change_clusterhead(address_ch,address_src,k_cluster-k_cds-ttl);								
											}
									
										//We treat this packet only if not seen (identified by id-packet) -> we can't also treat a packet we have already forwarded and also have a bad clusterhead-relay
										if (address_ch == my_clusterhead.address)
											{
												my_clusterhead.relay 			= address_src;
												my_clusterhead.hops 			= (k_cluster-k_cds)-ttl+1;
												my_clusterhead.relay_last_seen 	= op_sim_time();
												my_clusterhead.last_id 			= id;
												my_clusterhead.nb_recon_try		= 0;
												my_clusterhead.construct_cluster= 4;	//I have a valid clusterhead
											}
									
										
										if (src_init != 0)
												forward_rep_connect_ch(pkptr);
								
									break;
									
									
							}
						if (!not_id_add)
							add_address_id_couple(address_src,id);
					}
				
				
				
				
				
				
				
				
				/*----------------------------------------------------------------------------------------------------------------------------------
				------------------------------------------------------------------------------------------------------------------------------------
				
																			BACKBONE 
				
																CONSTRUCTION   and   MAINTENANCE
				
				------------------------------------------------------------------------------------------------------------------------------------
				----------------------------------------------------------------------------------------------------------------------------------*/
				
				
				if ( (is_broadcast || is_unicast_for_me) && is_ttl_enough && is_pk_not_seen && is_pk_from_bidirectional && is_pk_type_for_cds && ((type_packet == HELLO_PK_TYPE)||is_wireless))
					{
						//Lookup up the type of packet
						switch(type_packet)
							{
								/*------------------------------------------	
										Discovering of k-Neighbourhood 
								-------------------------------------------*/
								case HELLO_PK_TYPE:
									op_pk_nfd_get(pkptr,"CLUSTERHEAD",		&address_ch);				
									op_pk_nfd_get(pkptr,"CLUSTERHEAD_HOPS",	&ch_hops);				
									op_pk_nfd_get(pkptr,"FATHER",			&addr_father);
									op_pk_nfd_get(pkptr,"FATHER_HOPS", 		&father_hops);
									op_pk_nfd_get(pkptr,"STATE",			&state);
									op_pk_nfd_get(pkptr,"ID_AP",			&id_ap);
								
													
									//If the packet comes from Ethernet interface (for an AP), we consider this packet only if it was not just relayed by the source AP
									if (is_wireless)
										{	
											//Update the Neighborhood tables
											switch (cds_algos_type){
												case THEO_OLD:
												case THEO_NEW:
												case THEO_NEW2:
													//if ((address_relay == address_src) || (!is_unidirectional_link(address_relay)))
													update_table_neighbours(pkptr, ttl_for_hellos);
													update_cds(pkptr);
												break;
												case WU_LI :
													//Necessary to maintain compatbility with statistics collect, with topology figure generation... (additional information is stored in this variable)
													update_table_neighbours(pkptr , ttl_for_hellos);
												break;
											}
										}
												
										
									//I will perhaps receive the same packet from a bidirectional link further
									if (is_unidirectional_link(address_relay))
										not_id_add	= OPC_TRUE;
					
									//We treat this packet if it don't come from one AP via the Ethernet Network (wired)
									if ((is_wireless) && (!is_unidirectional_link(address_relay)))
										{
										
											////////////////////////////////////////////
											//
											//  ID_AP  +  RELAY CHANGE (same father)
											//
											////////////////////////////////////////////
										
											//Pick up the id_ap and relay to/of my_dominator
											if ((addr_father == my_cds.father) && (address_src == address_relay) && (!is_unidirectional_link(address_src)) && (my_cds.state == DOMINATEE) && (state == DOMINATEE))
												{
													if ((father_hops < my_cds.father_hops) && (father_hops <= k_cds - 1))
														{
															if(DEBUG>LOW)
																{
																	sprintf(msg, "I change my relay %d (hops %d) -> %d (hops %d) to father %d at %f\n", my_cds.relay , my_cds.father_hops , address_relay , father_hops , my_cds.father , op_sim_time());
																	cluster_message(msg);
																}
				
															my_cds.id_ap			= id_ap;
															my_cds.relay			= address_relay;
															my_cds.relay_timeout 	= op_sim_time() + INTERVALL_HELLO * TIMEOUT_RELAY_FATHER;
															my_cds.father_hops 		= father_hops + 1;											
														}
												}		
					
											
											///////////////////////////////////////
											//
											//	RELAY FATHER TIMEOUT (dominatees)
											//
											///////////////////////////////////////
											
											
											//Refreshes the timeout for relay toward father
											if ((address_src == address_relay) && (my_cds.relay == address_src) && !is_unidirectional_link(address_src) && (my_cds.state == DOMINATEE))
												{
													if ((address_src == my_cds.father) || ((addr_father == my_cds.father) && (father_hops <= k_cds - 1) && (state == DOMINATEE)))
														{
															my_cds.relay_timeout 	= op_sim_time() + INTERVALL_HELLO * TIMEOUT_RELAY_FATHER;
															my_cds.father_hops 		= father_hops + 1;
															my_cds.id_ap			= id_ap;
															
															if (DEBUG>HIGH)
																{
																	sprintf(msg, "RELAY refreshed at %f (father hops %d, id_ap %d)\n",op_sim_time() , father_hops+1 , id_ap);
																	cluster_message(msg);
																}
														}
													//Dead Relay to father (invalid)
													else
														{
															my_cds.relay_timeout 	= op_sim_time() - 0.01;
															my_cds.father_hops 		= k_cds + 1;
															
															if (DEBUG>LOW)
																{
																	sprintf(msg, "RELAY %d invalid : father %d=%d, hops %d<=%d, state %d at %f\n" , my_cds.relay , addr_father, my_cds.father , father_hops , k_cds-1 , state , op_sim_time());
																	cluster_message(msg);
																}
														}										
												}
											
											///////////////////////////////////////
											//
											//	  INFO FROM FATHER (dominators)
											//
											///////////////////////////////////////
											
											
											//Refreshes the timeout for relay toward father
											if ((address_src == address_relay) && (my_cds.relay == address_src) && !is_unidirectional_link(address_src) && (my_cds.state == DOMINATOR))
												my_cds.id_ap = id_ap;
											
											
											
											//////////////////////////////
											//
											//	  CLUSTERHEAD
											//
											//////////////////////////////
				
											
											//I have the same clusterhead as my dominator
											if((address_src == my_cds.father) && (my_cds.state == DOMINATEE))
												{								
													if ((address_ch!=my_clusterhead.address) && (address_ch!=0))
														{
															change_clusterhead(address_ch,-1,-1);
															if (DEBUG>LOW)
																{
																	sprintf(msg,"I update my clusterhead (I pick up the clusterhead of my dominator) at %f\n",op_sim_time());
																	cluster_message(msg);
																}
														}
												}
				
											//I have the same clusterhead as my relay to dominator
											if ((my_cds.state == DOMINATEE) && (my_cds.relay == address_src))
												{
													if (addr_father == my_cds.father)
														{
															if ((address_ch != my_clusterhead.address)&&(address_ch != 0))
																{
																	change_clusterhead(address_ch,address_src,-1);
																	if (DEBUG>LOW)
																		{
																			sprintf(msg,"I update my clusterhead (I am dominatee and I take the same dominator as my relay to cds %d) at %f\n", my_cds.relay , op_sim_time());
																			cluster_message(msg);
																		}
																}
														}
												}
											
											
											//I verify that my gateway to clusterhead is already alive -> THEO_NEW Maintenance
											if (((cluster_algos_type == THEO_NEW)||(cluster_algos_type == THEO_NEW2)) && (my_cds.state == DOMINATOR) && ( (my_clusterhead.relay == address_src) || (my_clusterhead.address==address_src) )  &&  ((my_cds.father==address_src)||(is_my_son(address_src))))
												{
													if (DEBUG>LOW)
														{
															sprintf(msg,"CH Verification with hello pk -> relay %d, ch %d, hops %d\n",address_src , address_ch , ch_hops+1);
															cluster_message(msg);
														}
													if (state != DOMINATOR)
														{											
															my_clusterhead.relay_last_seen = -2;
															change_clusterhead(0, 0 , 0);
														}
													//My Relay has changed its clusterhead, I choose its new clusterhead if it's valid
													else if (address_ch != my_clusterhead.address)
														{
															if (ch_hops+1 <= k_cluster-k_cds)
																{
																	if (DEBUG>LOW)
																		{
																			sprintf(msg, "I update my clusterhead (I pick up the same clusterhead as my relay) at %f\n", op_sim_time());
																			cluster_message(msg);
																		}			
																	change_clusterhead(address_ch , address_src , ch_hops+1);
																	my_clusterhead.relay_last_seen 	= op_sim_time();
																}
															else
																my_clusterhead.relay_last_seen = -2;
														}
													else
														{
															if (ch_hops+1 <= k_cluster-k_cds)
																{
																	if (DEBUG>HIGH)
																		{
																			sprintf(msg,"%d refresh the last seen time for its relay node to clusterhead (clusterhead=%d,relay=%d,clusterhead_hops=%d)\n",my_address,address_ch,address_src,ch_hops);
																			cluster_message(msg);
																		}
																	my_clusterhead.relay			= address_src;
																	my_clusterhead.hops 			= ch_hops+1;
																	my_clusterhead.relay_last_seen 	= op_sim_time();
																}
															else
																my_clusterhead.relay_last_seen = -2;
														}
														
												}
				
											//I pick up a sniffed clusterhead sent by a 1-Neighbor -> THEO_NEW Maintenance		
											if (  ((cluster_algos_type==THEO_NEW)||(cluster_algos_type==THEO_NEW2))  &&  ((hello_method == HELLO_METHOD_KTABLE) || (ttl = k_cds-1))   && (my_clusterhead.address == 0) && (address_ch !=0) && (ch_hops+1 < k_cluster-k_cds) && (my_cds.state==DOMINATOR) && ((my_cds.father==address_src)||(is_my_son(address_src))))
												{
													change_clusterhead(address_ch , address_relay , ch_hops+1);
													if (DEBUG>LOW)
														{
															sprintf(msg,"I update my clusterhead (I haven't yet) at %f\n",op_sim_time());
															cluster_message(msg);
														}
													my_clusterhead.relay_last_seen 	= op_sim_time();
													op_intrpt_schedule_self(op_sim_time(),CLUSTER_MAINTENANCE_CODE);
													op_intrpt_disable(OPC_INTRPT_SELF , CONSTRUCT_CLUSTER_CODE , OPC_TRUE);
												}
											
											//////////////////////////////
											//
											//	 CLUSTER   TOPOLOGY
											//
											//////////////////////////////
				
											
											//Add 2 adjacent clusters (I am a gateway)
											if ((address_ch != my_clusterhead.address)&&(address_ch != 0)&&(my_clusterhead.address != 0)&&(is_wireless)&&((ttl == k_cds-1)||(hello_method==HELLO_METHOD_KTABLE)))
												{
													//If refresh=0, the entry doesn't already exist
													if (!refresh_cluster_neigh_global(my_clusterhead.address,address_ch))
														add_cluster_neigh_global(my_clusterhead.address,address_ch);
				
												}
											
											
											//////////////////////////////
											//
											//	 CDS    CONSTRUCTION 
											//
											//////////////////////////////
				
				
											if ((my_cds.state==IDLE) || (my_cds.state == ACTIVE))
												{
													switch (state)
														{
															case DOMINATEE :
																if ((father_hops < k_cds) && (father_hops >= 1) && (addr_father != 0) && (addr_father != -1))
																	{
																		change_father(addr_father , address_src , father_hops+1);
																		update_state_cds(DOMINATEE);
																		if (DEBUG>LOW)
																			{
																				sprintf(msg,"FROM HELLO : %d has a new dominator/father : %d, connected via %d, at %f\n", my_address , my_cds.father , my_cds.relay , op_sim_time());
																				cluster_message(msg);
																			}
																	}
															break;
															case ACTIVE :
																if (my_cds.state == IDLE)
																	update_state_cds(ACTIVE);
															break;
															case DOMINATOR: 
																//If I am dominatee, my father in the tree is my dominator
																if (hello_method == HELLO_METHOD_KTABLE)
																	change_father(address_src , address_relay , 1);
																else
																	change_father(address_src , address_relay , k_cds-ttl+1);
																update_state_cds(DOMINATEE);
																if (DEBUG>LOW)
																	{
																		sprintf(msg,"FROM HELLO : %d has a new dominator/father : %d, connected via %d, at %f\n",my_address,my_cds.father,my_cds.relay,op_sim_time());
																		cluster_message(msg);
																	}									
															break;
														}
												}
											
											
										
											//////////////////////////////
											//
											//			FORWARD 
											//
											//////////////////////////////
				
				
											//We must relay the hello packet if the TTL is not null (equal to 1 on the reception) and if the link is not unidirectional
											op_pk_nfd_get(pkptr,"TTL",&ttl);
											
											//Relaying
											//is_relay_hello_required = (!is_cluster_knowledge_required) || ((address_ch != 0) && (address_ch == my_clusterhead.address));
											if (is_cluster_knowledge_required)
												{
													//k_cds MUST be equal to 2
													if ((ttl>1) && (!is_unidirectional_link(address_relay)) && (address_ch != 0) && (address_ch == my_clusterhead.address))								
														{
															ttl--;
															op_pk_nfd_set(pkptr,"TTL",ttl);
															op_pk_nfd_set(pkptr,"RELAY" , my_address);
															pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
														}								
												}
											else
												{
													//No proactive knowledge of the cluster
													//-> k_cds normal neighbors known with the hello-neighbor-table of k_cds-1 neighbors (partial info)
													//-> A father must know its dominatees
													must_relay_hello = (addr_father == my_cds.father) && is_father_valid(my_cds.father) && (father_hops == k_cds) && (my_cds.father_hops == 1);
													if (!is_unidirectional_link(address_relay) &&    ((ttl>2)  ||  ((ttl>1) && (must_relay_hello)) ))
														{
															if (DEBUG >MAX)
																{
																	sprintf(msg,"%d relays the hello-pk from %d (src=%d its_father=%d my_father=%d)\n",my_address , address_src , addr_father , my_cds.father);
																	cluster_message(msg);
																}
															ttl--;
															op_pk_nfd_set(pkptr , "TTL" , ttl);
															op_pk_nfd_set(pkptr,"RELAY" , my_address);
															pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
														}								
												}
											
										}					
									
								break;
													
				
									
									
									
									
									
								/*----------------------------------------------	
											Sleeping Nodes
								-----------------------------------------------*/					
								 case SLEEPING_NODE_PK_TYPE:
								
									//Adds the source as a Sleeping Node
								 	//op_pk_nfd_get(pkptr,"SRC_INIT",&src_init);					
								 	add_sleeping_node(address_src);
									
									//Relays the packet
									if (ttl>1)
										{						
											op_pk_nfd_get(pkptr,"TTL",&ttl);
											op_pk_nfd_set(pkptr,"TTL",--ttl);
											pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
											ttl++;
										}
									break;
									
									
									
								/*----------------------------------------------					
									Creation of an CDS  - Method of Butenko
								-----------------------------------------------*/
								/*----------------------------------------------	
									First Step : Creation of an MIS
								-----------------------------------------------*/					
								 case CDS_MIS_PK_TYPE:
				
									//Extract some information in the packet
								 	op_pk_nfd_get(pkptr,"STATE",		&state_src);
									op_pk_nfd_get(pkptr,"TTL",			&ttl);
									op_pk_nfd_get(pkptr,"CLUSTERHEAD",	&address_ch);				
									op_pk_nfd_get(pkptr,"FATHER",		&addr_father);
									op_pk_nfd_get(pkptr,"WEIGHT",		&weight_src);
				
									//If we are in "break mode", I do nothing
									if (my_cds.time_cds_reinit != -1)
										{						
											state_src = -1;
											sprintf(msg,"%d is blocked at %f\n",my_address,op_sim_time());
											cluster_message(msg);
										}
									else
										{
											//Update the informations in neighbour_table and cds table
											update_cds(pkptr);
										}
				
									//Update the state informations associated to the source
									switch (cds_algos_type){
										case THEO_OLD:
										case THEO_NEW:
										case THEO_NEW2:
											update_table_neighbours(pkptr , ttl_for_hello_mis);
											update_cds(pkptr);
										break;
										case WU_LI :
											//Necessary to maintain compatbility with statistics collect, with topology figure generation...
											update_table_neighbours(pkptr , ttl_for_hello_mis);
				
											//The effective information we use
											//I update/add the neighbor table associated to the source
											//update_the_neighbor_table_associated_to_one_neighbor(pkptr);
												
											//if (!is_unidirectional_link(address_src) || (ttl != k))
											//	cds_maintenance_wu_li(pkptr);
										break;
									}
									
									//Update the neighborhood table with this new cds information
									//NB : I don't need to store the nodes farther than k_cds hops -> It is only a trigger to change my cds_state
									update_informations_cds(address_src , addr_father , address_ch , state_src , weight_src);
				
									switch(state_src){
										//We have received a dominator-message => We become dominatee
										case DOMINATOR :
										
											//Change my state
											if ((my_cds.state==ACTIVE)||(my_cds.state==IDLE)) 
												{
													//If I am dominatee, my father in the tree is my dominator
													if (hello_method == HELLO_METHOD_KTABLE)
														change_father(address_src , address_relay , 1);
													else
														change_father(address_src , address_relay , k_cds-ttl+1);
													update_state_cds(DOMINATEE);
													if (DEBUG>LOW)
														{
															sprintf(msg,"%d has a new dominator/father : %d, connected via %d, at %f\n",my_address,my_cds.father,my_cds.relay,op_sim_time());
															cluster_message(msg);
														}									
												}
										break;
										
										//We have received a dominator-message => We become active
										case DOMINATEE :
													
											if (my_cds.state==IDLE)
												update_state_cds(ACTIVE);
											break;
														
														
														
										//We update the information about the neighbours which are actives
										case ACTIVE :						
												//Nothing to do, If we are active, we wait for an election and no particular case act
											break;
									}
							
									//Relays the packet
									//pk_dest= op_pk_copy(pkptr);
									if (ttl>1)
										{						
											op_pk_nfd_set(pkptr,"TTL",--ttl);
											op_pk_nfd_set(pkptr,"RELAY",my_address);
											pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
										}			
										
								 break;
									
									
									
									
								/*----------------------------------------------	
									Second Step : Interconnection of the MIS
								-----------------------------------------------*/					
								 case CDS_JOIN_PK_TYPE:
									
								 	//I must have a state, else, I wait
								 	if ((my_cds.state!=DOMINATOR) && (my_cds.state!=DOMINATEE))
										{
											//I must determine myself after a join_message (reconstruction or packet loss....)
											if (my_cds.state==IDLE)   //&&(my_cds.time_cds_reinit!=-1))
												{
													my_cds.time_cds_reinit = -1;
													my_cds.time_last_cds_reconstruct = op_sim_time();
													//forward_join_message(op_pk_copy(pkptr));
													forward_join_message(pkptr);
													update_state_cds(ACTIVE);
													add_address_id_couple(src_init,id);
													
													if (DEBUG>LOW)
														{
															sprintf(msg,"CDS-BREAK: reconstructs the cds thanks to %d at %f\n", address_src , op_sim_time());
															cluster_message(msg);
														}
												}
											
											//I wait 5 seconds and try again to deal with this packet (I hope that my state is determined in 5 seconds)
											//NB : I must store this packet and remove the packet-id from my id_table (else, I will simply ignore the packet when I will "wake" me)
											add_pk_in_wait_state(pkptr);
											not_id_add 		= OPC_TRUE;
											op_intrpt_schedule_self(op_sim_time() + timeout_construct_cds/2 , WAIT_STATE_CODE);
										}
									else
										{
											op_pk_nfd_get(pkptr,"SRC_INIT",&src_init);
											op_pk_nfd_get(pkptr,"TTL",&ttl);
											if (pk_not_seen(id,src_init))
												{
													//I must set my	parent to the dominatee which relay the join indication and send a join-request
													if ((my_cds.state==DOMINATOR)&&(my_cds.father==0)&&(src_init!=my_address))
														{
															send_join_reverse(pkptr);
															add_address_id_couple(src_init,id);													
														}
													//We must forward the join indication message to our neighbours (it exists perhaps a dominator which is not yet connected)					
													if (my_cds.state==DOMINATEE)
														{
															if (my_cds.join_already_forwarded[ttl-1]<=NB_JOIN_MAX)
																{		
																	forward_join_message(pkptr);
																	add_address_id_couple(src_init,id);
																	for (i=0;i<ttl;i++) {my_cds.join_already_forwarded[i]++;}
																}
														}
													}
											}
									
								 	break;
				
								case CDS_REVERSE_JOIN_PK_TYPE:
									
								 	//I must have a state, else, I wait
								 	if ((my_cds.state!=DOMINATOR)&&(my_cds.state!=DOMINATEE))
										{
											//I must determine myself after a join_message (reconstruction or packet loss....)
											if ((my_cds.state==IDLE)&&(my_cds.time_cds_reinit!=-1))
												{
													my_cds.time_cds_reinit = -1;
													my_cds.time_last_cds_reconstruct = op_sim_time();
													forward_join_message(pkptr);
													update_state_cds(ACTIVE);
													add_address_id_couple(src_init,id);
													
													if (DEBUG>LOW)
														{
															sprintf(msg,"CDS-BREAK: reconstructs the cds thanks to %d at %f\n", address_src , op_sim_time());
															cluster_message(msg);
														}
												}
											
											//I wait 5 seconds and try again to deal with this packet (I hope that my state is determined in 5 seconds)
											//NB : I must store this packet and remove the packet-id from my id_table (else, I will simply ignore the packet when I will "wake" me)
											add_pk_in_wait_state(pkptr);
											not_id_add 		= OPC_TRUE;
											op_intrpt_schedule_self(op_sim_time() + timeout_construct_cds/2 , WAIT_STATE_CODE);
										}
									else
										{
											//This a join-reverse (it is a unicast message)
											op_pk_nfd_get(pkptr , "DEST_FINAL" , &dest_final);
											if (pk_not_seen(id,dest_final))
								 					{
								 						//I must forward the packet, change my_cds.state, and add the corresponding son (or destroy the packet if I am the destination)
								 						forward_join_reverse(pkptr);	
								 						add_address_id_couple(dest_final,id);
													}
										}
									break;	
				
									
									
									
									
								
									
									
								/*------------------------------------------	
										USELESS DOMINATOR (our father) 
								-------------------------------------------*/
								//My father is useless -> we take its own father as new father
								case USELESS_DOMINATOR_PK_TYPE:			
				/*						op_pk_nfd_get(pkptr , "SRC_INIT" , &src_init);
										if ((my_cds.state==DOMINATEE) && (my_cds.father==src_init))	
											{
												op_pk_nfd_get(pkptr , "FATHER" , &addr_father);
												if (DEBUG>1)
													{
														sprintf(msg,"My father (%d) was useless, I changed it at %f\n",my_cds.father,op_sim_time());
														cluster_message(msg);
													}	
												if (hello_method == HELLO_METHOD_KTABLE)
													change_father(addr_father,address_src,1);
												else
													change_father(addr_father,address_src,k_cds-ttl+1);
												if (ttl>1)
													{
														op_pk_nfd_get(pkptr,"TTL",&ttl);
														ttl--;
														op_pk_nfd_set(pkptr,"TTL",ttl);
														op_pk_nfd_set(pkptr,"SRC",my_address);
														pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
													}
											}					
				*/					break;
									
									
									
									
									
									
								/*------------------------------------------	
											AP HELLOS 
								-------------------------------------------*/					
								case AP_HELLO_PK_TYPE:
				
									//Extract the id of the AP
									op_pk_nfd_get(pkptr,"ID_AP", &id_ap);
									op_pk_nfd_get(pkptr,"PK_ID", &id);				
									
									//Search the id of the last ap_hello seen (from our father)
									ptr_ap_hello = ap_hellos_table;
									id_last_ap_hello = 0;
									while(ptr_ap_hello!=NULL)
										{
											//ap-hellos coming from my father -> I take the last ap-hello received (the higher id)
											if ((ptr_ap_hello->address == my_cds.father) && (ptr_ap_hello->id_hello > id_last_ap_hello))
												{
													id_last_ap_hello = ptr_ap_hello->id_hello;
													my_cds.id_ap = id_ap;
												}
											
											ptr_ap_hello = ptr_ap_hello->next;
										}	
								
									//Maintain the list of last ap-hellos seen and their direct transmitters
									update_ap_hellos_table(address_src,id_ap,id);					
							
									
									//all dominators retransmit the advertisement to maintain backbone connectivity
									if (my_cds.state==DOMINATOR) 
										{
											//Retransmit the advertisement if not already seen														
											if (my_cds.father == address_src)
												{
													my_cds.last_hello_ap_seen 		= op_sim_time();
													my_cds.id_last_hello_ap_seen 	= id;
													my_cds.id_ap					= id_ap;
													my_cds.ap_hops 					= MAX_NETWORK_RADIUS - ttl + 1;
													forward_ap_hello(pkptr);									
												}
											//Adds the sender as a candidate for a connection/reconnection
											//f the id is superior than the last I received, the source can't be a son (or descendant)
											else if ((my_cds.is_maintenance_scheduled) && (id > my_cds.id_last_hello_ap_seen))
												{	
													if (DEBUG>MEDIUM)
														{
															sprintf(msg,"FATHER: a new father (%d) is candidate (automatic detection of ap_hellos) at %f\n", address_src , op_sim_time());
															cluster_message(msg);
														}
													add_cds_reconnect_candidate(pkptr);
												}						
										}
									
									//Optimizes 'Number of leaves' / 'Distance to the AP' / 'Load balacing of the sons number'  of the CDS
									//if ((my_cds.state == DOMINATOR) && ( get_nb_sons(address_relay)+1 > get_nb_sons(my_cds.father) ) && (id_last_ap_hello < id) && (cds_algos_type == THEO_NEW2))
									//if ((my_cds.state == DOMINATOR) && (MAX_NETWORK_RADIUS - ttl + 1 > my_cds.ap_hops) && (id_last_ap_hello < id) && (cds_algos_type == THEO_NEW2))
									if ((my_cds.state == DOMINATOR) && (MAX_NETWORK_RADIUS - ttl + 1 < my_cds.ap_hops) && (id_last_ap_hello < id) && (cds_algos_type == THEO_NEW2))
										{
											change_father(address_relay , address_relay , 1);
											
											if (DEBUG>LOW)
												{
													sprintf(msg,"FATHER: %d changes its father (better distance to ap old=%d, new=%d) and retransmits an hello-ap (id_ap=%d with id=%d) from %d at %f\n" , my_address , my_cds.ap_hops , MAX_NETWORK_RADIUS - ttl + 1 , id_ap,id , address_src , op_sim_time());
													cluster_message(msg);
												}
											
											my_cds.last_hello_ap_seen 		= op_sim_time();
											my_cds.id_last_hello_ap_seen 	= id;
											my_cds.id_ap					= id_ap;
											my_cds.ap_hops 					= MAX_NETWORK_RADIUS - ttl + 1;
											forward_ap_hello(pkptr);									
										}
								
									break;
									
									
									
									
									
									
									
								/*------------------------------------------	
											CDS RECONNECTION REQUEST
								-------------------------------------------*/					
								case CDS_RECONNECT_PK_TYPE:				
				
										op_pk_nfd_get(pkptr,"SRC_INIT",&src_init);
										
										//I answer if I am connected to the ap
										op_pk_nfd_get(pkptr,"ID_AP_HELLO",&id_ap_hello_in_pk);						
										//if ((pk_not_seen(id,src_init)) && (my_cds.state==DOMINATOR) && (my_cds.nb_retry_reconnect_cds==0) && (address_src!=my_cds.father) && ((my_cds.last_hello_ap_seen > op_sim_time() - 1.1*INTERVALL_AP_HELLO) || (is_AP))&&(id_ap_hello_in_pk <= my_cds.id_last_hello_ap_seen))
										if ((pk_not_seen(id,src_init)) && (my_cds.state==DOMINATOR) && (address_src!=my_cds.father) && ((my_cds.last_hello_ap_seen > op_sim_time() - 1.1*INTERVALL_AP_HELLO) || (is_AP))&&(id_ap_hello_in_pk <= my_cds.id_last_hello_ap_seen))
											{	
												reply_cds_reconnect(pkptr);
												add_address_id_couple(src_init,id);
											}
										//else, I forward
										else if (my_cds.state==DOMINATEE)
											{
												if (pk_not_seen(id,src_init))
													{										
														if (DEBUG>MEDIUM)
															{
																sprintf(msg,"CDS-RECONNECTION: forwards a request of cds reconnection from %d (initial dominator =%d) at %f\n", address_src , src_init , op_sim_time());
																cluster_message(msg);					
															}
																							
													   	add_relaying(src_init,address_src);										
														if ((src_init==my_cds.father)||(my_cds.father==0)||(my_cds.relay==0)||(my_cds.relay==my_address))
															{
																forward_packet_cds(pkptr);
																//We will know that we have already relayed the request from src_init with this id, even with this reconnect-req arrives via other intermediaries
																add_address_id_couple(src_init,id);
															}
														else
															{
																forward_packet_to_dominator_cds(pkptr);
																add_address_id_couple(src_init,id);
															}
														
													}
											}
									break;
									
								/*------------------------------------------	
											CDS RECONNECTION REPLY 
								-------------------------------------------*/					
								case CDS_RECON_REP_PK_TYPE:				
									
										op_pk_nfd_get(pkptr,"RELAY1",&src_init);				
										op_pk_nfd_get(pkptr,"DEST_FINAL",&dest_final);
									
										//This comes from our father -> We act as if we received an ap-hello from it
										if (src_init == my_cds.father)
											{
												my_cds.last_hello_ap_seen = op_sim_time();
												my_cds.id_last_hello_ap_seen = id;
											}
											
										//I am not the final destination
										if (dest_final != my_address)
											{
												if ((my_cds.father==0) && (!is_a_relay(pkptr , my_address)))
													add_cds_reconnect_candidate(pkptr);
												if (DEBUG>MEDIUM)
													{
														sprintf(msg,"CDS-RECONNECTION: %d forwards a reply of cds reconnection from %d (actual father=%d) at %f\n", address_src , my_cds.father , op_sim_time());
														cluster_message(msg);
													}
												forward_reconnect_reply(pkptr);
											}
										else
											{								
												if (DEBUG>LOW)
													{
														sprintf(msg,"CDS-RECONNECTION: %d receives a reply of cds reconnection from %d (actually my_cds.father=%d) at %f\n", my_address , src_init , my_cds.father , op_sim_time());
														cluster_message(msg);
													}
				
												//Depends from the maintenance type
												switch (cds_algos_type)
													{
														case THEO_OLD :
															connection_cds_init(pkptr);
															my_cds.nb_retry_reconnect_cds = 0;
															my_cds.last_hello_ap_seen = op_sim_time();
														break;
														case THEO_NEW :
														case THEO_NEW2 :
															//The source is a candidate for reconnection (examined in cds maintenance in order to have multiple candidates)
															add_cds_reconnect_candidate(pkptr);
														break;
													}								
											}
								
									break;
									
								/*------------------------------------------	
											CDS RECONNECTION INIT 
								-------------------------------------------*/					
								case RECONNECT_INIT_PK_TYPE:						
								
										op_pk_nfd_get(pkptr,"DEST_FINAL",&dest_final);	
										update_cds(pkptr);
									
										if (dest_final != my_address)
											{
												if (DEBUG>LOW)
													{
														sprintf(msg,"CDS-RECONNECTION: intermediary for the reconstruction of the cds at %f\n", op_sim_time());
														cluster_message(msg);
													}
												forward_reconnect_init(pkptr);							
											}
										else
											{	
												if (DEBUG>LOW)
													{
														sprintf(msg,"CDS-RECONNECTION: finalizes the reconnection of the CDS with one new son : %d at %f\n", address_src , op_sim_time());
														cluster_message(msg);
													}
												forward_reconnect_init(pkptr);
											}						
								
								
									break;
									
				
									
									
									
									
									
									
									
									
									
									
								/*------------------------------------------	
											CDS RECONSTRUCT 
								-------------------------------------------*/
								//Such a message means that all dominatees and sons must reinitialize theirself, in order to reconstruct entirely this aprt of the cds (reconnection impossible)
								case BREAK_CDS_PK_TYPE:				
									
										if ((address_src==my_cds.father)&&(my_cds.state==DOMINATEE))
											{								
												if (my_cds.state==DOMINATOR)
													break_all_our_tree();
												
												if (my_cds.state==DOMINATEE)
													{
														reinit_cds_infos();
													
														if (ttl>1)
															{
																op_pk_nfd_get(pkptr,"TTL",&ttl);
																ttl--;
																op_pk_nfd_set(pkptr,"TTL",ttl);
																pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
															}
													}	
												my_cds.time_cds_reinit = op_sim_time();								
											}
								
									break;
									
									
									
								/*------------------------------------------	
											CDS ADVERTISING 
								-------------------------------------------*/
								//A node of state nothing is neighbour of our cds-zone -> the dominator must send a join message
								case NOTHING_NEIGH_CDS_PK_TYPE:				
								
										if ((my_address==my_cds.father)&&((is_AP) || ((my_cds.state==DOMINATOR) && (my_cds.last_hello_ap_seen > op_sim_time() - 1.2*INTERVALL_AP_HELLO))))
											send_join_message();							
										else
											{
												if (ttl>1)
													{
														op_pk_nfd_get(pkptr,"TTL",&ttl);
														ttl--;
														op_pk_nfd_set(pkptr,"TTL",ttl);
														op_pk_nfd_set(pkptr,"DEST",my_cds.relay);
														pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
													}
											}					
									break;
								}
				
						if (!not_id_add)
							add_address_id_couple(address_src,id);
					}
				
				
				
				
				//----------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				//				
				//												BACKBONE      MULTICAST
				//				
				//----------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				
				//Active ack for cds-connectors
				if (type_packet == ACK_UNICAST_PK_TYPE)
					delete_ack_pk(pkptr);
				
				//Passive acknowledgement
				if (is_pk_type_for_bb_flooding && !pk_not_seen(id , address_src) )
					delete_ack_multicast(address_relay , id);
				
				//Normal procedure
				//if (is_pk_type_for_bb_flooding && pk_not_seen(id , address_src) && is_ttl_enough)
				if (is_pk_type_for_bb_flooding && is_ttl_enough)
					{
						//STATS
						op_pk_nfd_get(pkptr , "STAT_ID", &stat_id);
						stats_bb_flooding [stat_id].is_rcvd [my_stat_id]	= OPC_TRUE;
						stats_bb_flooding [stat_id].time_reception 			= op_sim_time();
				
						
						//FOR DOMINATORS
						if (my_cds.state == DOMINATOR)
							{
								//Active ack for cds-connectors
								if ((address_dest == my_address) && (ACK_FOR_BB_MULTICAST))
									ack_packet(pkptr , BACKBONE_MULTICAST);
								
								if (pk_not_seen(id , address_src))
									 {
									 	//Adds Pk as seen
									 	add_address_id_couple(address_src , id);
							
								
										//Forwards the packet toward other backbone members, and through its cds-connectors toward other backbones
										send_pk_to_bb_and_gws(pkptr);
									}
							}
						
						//FOR DOMINATEES
						if (my_cds.state == DOMINATEE)
							for(i=1 ; i < MAX_NB_APS ; i++)
								{
									//The first fields (in common headers)
									if (address_dest == my_address)
										{
											if (ACK_FOR_BB_MULTICAST)
												ack_packet(pkptr , BACKBONE_MULTICAST);
											
											if (pk_not_seen(id , address_src))
												{
													op_pk_nfd_get(pkptr,"ID_AP" ,	&id_ap);
											
													//Adds Pk as seen
													add_address_id_couple(address_src , id);
											
													//Relay to cds-connector
													if ((my_address != address_dest_final) && (id_ap != my_cds.id_ap))
														relay_to_cds_connector(pkptr , address_dest , address_dest_final , id_ap);							
													//I am the cds-connector, relay to ap-neighbor
													else if ((my_address == address_dest_final) && (id_ap != my_cds.id_ap))									
														relay_to_ap_neighbor(pkptr , address_dest , address_dest_final , id_ap);									
													//Relay to backbone (to my father)
													else if (id_ap == my_cds.id_ap)								
														relay_to_my_ap(pkptr , address_dest , address_dest_final , id_ap);
													else
														{
															sprintf(msg, "BB-ERROR : no role was found, whereas %d is a dominatee-destination for this bb-flooding pk\n", my_address);
															cluster_message(msg);
														}
												}
										}
				
									
									//The following fields (in extension headers)
									sprintf(field_name , "DEST%d", i);
									if (op_pk_nfd_is_set(pkptr , field_name))
										{
											
											op_pk_nfd_get(pkptr, field_name ,	&dest);
											sprintf(field_name , "DEST_FINAL%d", i);
											op_pk_nfd_get(pkptr, field_name ,	&dest_final);
											sprintf(field_name , "ID_AP%d", i);
											op_pk_nfd_get(pkptr, field_name ,	&id_ap);
											
											if (dest == my_address)
												{
													//active ack
													if (ACK_FOR_BB_MULTICAST)
														ack_packet(pkptr , BACKBONE_MULTICAST);
													
													//and forward if not seen
													if (pk_not_seen(id , address_src))
														{
															//Adds Pk as seen
															add_address_id_couple(address_src , id);
											
															//Relay to cds-connector
															if ((my_address != dest_final) && (id_ap != my_cds.id_ap))
																relay_to_cds_connector(pkptr , dest , dest_final , id_ap);								
															//I am the cds-connector, relay to ap-neighbor
															else if ((my_address == dest_final) && (id_ap != my_cds.id_ap))									
																relay_to_ap_neighbor(pkptr , dest , dest_final , id_ap);									
															//Relay to backbone (to my father)
															else if (id_ap == my_cds.id_ap)								
																relay_to_my_ap(pkptr , dest , dest_final , id_ap);
															else
																{
																	printf("BB-ERROR : no role was found, whereas %d is a dominatee-destination for this bb-flooding pk\n", my_address);
																	cluster_message(msg);
																}
														}
												}
												
										}				
							}
					
					
					
					
					
					}
				
				
				
				//----------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				//				
				//										AP DATA     -    AP CONNECTIVITY TEST   (CDS-CLUSTER LEVEL PERFS)
				//				
				//----------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				if (is_pk_type_for_ap_unicast && is_ttl_enough && pk_not_seen(id , address_relay))
					{
						//I am the ap (final_dest = MULTICAST_AP)
						if ((address_dest == my_address) && (is_AP))
							{
								//Stats
								op_pk_nfd_get(pkptr , "STAT_ID" , &stat_id);
								stats_ap_unicast[stat_id].time_reception 	= op_sim_time();
								stats_ap_unicast[stat_id].dest 				= my_address;
								stats_ap_unicast[stat_id].hops 				= MAX_NETWORK_RADIUS - ttl + 1;
								
								if (DEBUG>LOW)
									{
										sprintf(msg , "!!!!!!!!!!%d received the pk from %d at %f !!!!!!!!!!!!!!!\n\n\n", my_address , address_src , op_sim_time());
										ap_unicast_message(msg);
									}
								
							}
						//I forward the pk toward my ap
						else if ((address_dest == my_address) && (ttl >1))
							{
								if (DEBUG>LOW)
									{
										sprintf(msg , "	%d relayed a pk from %d to %d toward its ap at %f\n", my_address , address_relay , my_cds.relay , op_sim_time());
										ap_unicast_message(msg);
									}
								op_pk_nfd_set(pkptr , "TTL" , --ttl);
								op_pk_nfd_set(pkptr , "RELAY", my_address);
								op_pk_nfd_set(pkptr , "DEST" , my_cds.relay);
								pk_send_delayed(op_pk_copy(pkptr) , op_dist_uniform(0.001));
							}
					}
				
				
				
				
				
				//----------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				//				
				//												HIGHER LEVEL PACKETS
				//				
				//----------------------------------------------------------------------------------------------------------------------------------
				//----------------------------------------------------------------------------------------------------------------------------------
				
				// DATA Paging for all AP -> direct to the higher layer (without control), else try to inspect all required conditions
				if (is_pk_type_for_paging)
					op_pk_send(op_pk_copy(pkptr), STRM_TO_HIGHER);
				else if (is_pk_type_for_higher && is_ttl_enough){
						if (process_higher_layer_id == ZERO)
							{
								op_pk_print(pkptr);
								op_sim_end("We must forward and pk to the upper layer" , "and this upper layer doesn't exist for us" , "please set a valid attribute model" , "");
							}
						
						//Special Info Field
						op_pk_nfd_get(pkptr, "SRC_INIT", &address_src_init);
						
						//Already seen ? (Acks have the same id as data pk -> they are already seen, and the phenomena is reversible for data pk)
						is_pk_not_seen = pk_not_seen(id , address_src_init) || (type_packet == ACK_APP_PK_TYPE);// || (type_packet == DATA_PK_TYPE);				
							
						is_pk_from_son_or_father 	= (address_src == my_cds.father || is_my_son(address_src)) && (my_cds.state == DOMINATOR);
						is_pk_from_bb				= (my_cds.state == DOMINATOR) && (!is_unidirectional_link(address_src));
						is_pk_from_bb 				= is_pk_from_son_or_father || (is_pk_from_bb && process_higher_layer_type == ROUTING);
								
						//Forward to the higher layer if it is not seen and for it
						if ((type_packet >= DATA_PK_TYPE) && (is_pk_not_seen)){
								//Forwards to the localization level if the packet is for me
								if ( ((address_dest == ADDR_MULTICAST_BACKBONE) && (is_pk_from_bb)) || (address_dest == my_address))
									{
										//Broadcast or Multicast
										add_address_id_couple(address_src_init , id);
										
										op_pk_send(op_pk_copy(pkptr), STRM_TO_HIGHER);
									}	
							}	
					}
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				if (!is_pk_type_for_higher && !is_pk_type_for_cds && !is_pk_type_for_cluster && !is_pk_type_for_bb_flooding && !is_pk_type_for_ap_unicast && !is_pk_type_for_paging && type_packet!=ACK_UNICAST_PK_TYPE)
					op_sim_end("We received an invalid pk_type", "Please modify the Option Type in the packet", "or modify the pk_from_lower in the cdcl process", "");
				
				
				//The pk was treated, we must destroy the packet to free memory
				op_pk_destroy(pkptr);
				
				
				}
				//else
				//	-> Nothing (We sleep, we do as we didn't receive any packet)
				
				
				}


			/** state (PK From LOWER) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "PK From LOWER", "cdcl_process_cluster_cds_process () [PK From LOWER exit execs]")
				{
				}


			/** state (PK From LOWER) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "PK From LOWER", "Idle")
				/*---------------------------------------------------------*/



			/** state (PK From HIGHER) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "PK From HIGHER", "cdcl_process_cluster_cds_process () [PK From HIGHER enter execs]")
				{
				Packet	*pk_src; 
				int		dest , dest_final;
				int		src , src_init;
				int 	packet_type;
				int		id_pk , stat_id = 0;
				char	msg[200];
								
								
				// Obtain the incoming packet.	
				if ((op_intrpt_code()!=WAIT_STATE_CODE) && (!op_strm_empty(STRM_FROM_HIGHER)) )
					pk_src = op_pk_get (op_intrpt_strm ());
					
				
				//Gathers some info in different Fields
				op_pk_nfd_get(pk_src,"OPTION_TYPE", &packet_type);
				
				//The packet is a control pk for APs (via the ethernet network) or not
				if ((packet_type >= PAGING_REQ_PK_TYPE) && (packet_type < 10+PAGING_REQ_PK_TYPE))
					{
						//Transmission with the Ethernet link
						op_pk_send(op_pk_copy(pk_src), STRM_TO_ETH);						
					}
				else
					{
				
						op_pk_nfd_get(pk_src,"SRC",			&src);
						op_pk_nfd_get(pk_src,"DEST",		&dest);
						op_pk_nfd_get(pk_src,"DEST_FINAL",	&dest_final);
						op_pk_nfd_get(pk_src,"PK_ID",		&id_pk);
						op_pk_nfd_get(pk_src,"STAT_ID",		&stat_id);
								
						//Adds this packet as seen
						add_address_id_couple(src , id_pk);
				
						//DEBUG
						/*if (packet_type >= RERR_PK_TYPE)
							{
								sprintf(msg, "| %f :  (%d) -> %d (I %d, state %d) (pk_type %d) (id %d)\n", op_sim_time() , src , dest , my_address , my_cds.state ,  packet_type , id_pk);
								test_message(msg);		
								printf("%f ------ %f\n", op_sim_time() , op_pk_id(pk_src));
							}
						*/
						
						//Sends it
						if (dest != -1)
							pk_send(pk_src);		
						else
							{
								//printf("pb : no relay to destination %d\n", dest_final);
								//op_pk_print(pk_src);
							}
					}
				}


			/** state (PK From HIGHER) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "PK From HIGHER", "cdcl_process_cluster_cds_process () [PK From HIGHER exit execs]")
				{
				}


			/** state (PK From HIGHER) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "PK From HIGHER", "Idle")
				/*---------------------------------------------------------*/



			/** state (CLUSTER Maintenance) enter executives **/
			FSM_STATE_ENTER_FORCED (6, state6_enter_exec, "CLUSTER Maintenance", "cdcl_process_cluster_cds_process () [CLUSTER Maintenance enter execs]")
				{
				//Control
				int				i;
				char			msg[500];
				Packet*			pkptr;
				//For case separation
				Boolean			necessary;
				Boolean			is_useless_clusterhead;
				Boolean			is_cluster_neighbour;
				Boolean			is_valid_clusterhead;
				//Info
				int				address_ch , address_src;
				short 			ttl;
				//Structures
				cluster_cell	*ptr;
				neigh_cell		*ptr_neigh , *ptr_neigh_candidate ;
				candidate		*ptr_cand , *ptr_cand2;
				
				if (DEBUG>MAX)
					{
						sprintf(msg,"cluster maintenance  - %f\n",op_sim_time());
						cluster_message(msg);
					}	
				
				
				//Deletes the timeout entries
				update_cluster_table();
				
				/*--------------------------------------
						Cluster Hello required
				--------------------------------------*/
				//Verify that a periodic cluster-hello is necessary (deschedule it if not)
				ptr = cluster_table;
				necessary = OPC_FALSE;
				while((ptr!=NULL)&&(!necessary))
					{
						if ((ptr->clusterhead == 0) && (ptr->hops == 1) && (ptr->address != my_address))
							{
								necessary = OPC_TRUE;
								if (DEBUG>HIGH)
									{
										sprintf(msg,"I keep on sending cluster-hello, it is necessary for %d at %f\n", ptr->address , op_sim_time());
										cluster_message(msg);
									}
							}
						ptr = ptr->next;
					}
				if ( (!necessary || (my_cds.state != DOMINATOR)) && (op_ev_valid(last_ev_cluster_hello)) )
					{
						op_ev_cancel(last_ev_cluster_hello);
						if (DEBUG>HIGH)
							{
								sprintf(msg,"I delete the next scheduling for cluster_hello generation, the construction is finished\n");
								cluster_message(msg);
							}
					}
				
				
				/*--------------------------------------
						Verification of Connection
				--------------------------------------*/
				//Verify that we are connected to our clusterhead
				//If my clusterhead is one of my parent, I must wait that the cds-maintenance change it ! Else, I will change my parenty and nothing will work !
				//if (!is_AP && (my_cds.state==DOMINATOR) && (my_address!=my_clusterhead.address) && ((my_clusterhead.last_seen < op_sim_time() - (max_retry+0.01)*INTERVALL_CLUSTERHEAD_HELLO)||(my_clusterhead.address==0))) //||!is_one_valid_father_or_son(my_clusterhead.address)
				
				if (cluster_algos_type == THEO_OLD)
					{
						if (!is_AP && (my_cds.state==DOMINATOR) && (my_address!=my_clusterhead.address) && ((my_clusterhead.last_seen < op_sim_time() - 1.1*INTERVALL_CLUSTERHEAD_HELLO)||(my_clusterhead.address==0)))
							my_clusterhead.construct_cluster = 5;	
						else
							my_clusterhead.construct_cluster = 4;
					}
				
				
				if ((cluster_algos_type == THEO_NEW) || (cluster_algos_type == THEO_NEW2))
					{
						if (!is_AP && (my_cds.state==DOMINATOR) && (my_address!=my_clusterhead.address) && ((my_clusterhead.relay_last_seen < op_sim_time() - 1.1*INTERVALL_HELLO)||(my_clusterhead.address==0))) 
							my_clusterhead.construct_cluster = 5;	
						else
							my_clusterhead.construct_cluster = 4;
					}
				
				
				
				/*--------------------------------------
						Useless Clusterhead ?
				--------------------------------------*/
				//If we are clusterhead and that no 1-neighbour declare ourself as clusterhead, we are useless (a cluster is connected)
				//If we can find another clusterhead, we will choose it (when we will receive a clusterhead-hello)
				if (my_clusterhead.address == my_address)
					{
						//Useless ?
						ptr_neigh = neighbour_table; 
						is_useless_clusterhead = 1;
						while((ptr_neigh!=NULL)&&(is_useless_clusterhead))
							{
								if ((ptr_neigh->hops==1)&&(ptr_neigh->clusterhead==my_address)&&(ptr_neigh->state==DOMINATOR))
									is_useless_clusterhead = 0;
								ptr_neigh = ptr_neigh->next;			
							}
						//If I am useless -> Reconnexion
						if ((!is_useless_clusterhead)||(is_wireless_router)||(is_AP))
							my_clusterhead.last_time_usefull = op_sim_time();		
					}
					
							
				
				
				//----------------------------------------------------------------
				//
				//					 THEO_NEW2 Maintenance
				//
				// -> If no one exists, I search in the neigborhood table
				// -> Else, I will probably become directly clusterhead
				//
				//-----------------------------------------------------------------
				
				//Search a candidate for reconnection in the neighborhood table
				if ((cluster_algos_type == THEO_NEW2) && ((my_clusterhead.construct_cluster==5) || ((my_clusterhead.last_time_usefull < op_sim_time() - 3.1*INTERVALL_HELLO) && (my_clusterhead.address==my_address))))
					{
						i=0;
						//Searches one candidate
						ptr_neigh = neighbour_table;
						ptr_neigh_candidate = NULL;
						while(ptr_neigh!=NULL)
							{
								//If the node is one of our son or father and its clusterhead is valid, we choose it !
								is_cluster_neighbour = (is_my_son(ptr_neigh->address)) || (my_cds.father==ptr_neigh->address) ;
									
								//CH valid -> not too far, highest weight, clusterhead different (restrictive to avoid loops)
								is_valid_clusterhead = (ptr_neigh->clusterhead > 0) && (ptr_neigh->clusterhead_hops+1 <= k_cluster-k_cds) && ((ptr_neigh->clusterhead != my_clusterhead.address) || (ptr_neigh->clusterhead_hops < my_clusterhead.hops));    // && ((ptr_neigh_candidate==NULL)||(ptr_neigh_candidate->weight < ptr_neigh->weight));
								
								if ((is_cluster_neighbour) && (is_valid_clusterhead) && ((ptr_neigh_candidate==NULL) || (ptr_neigh_candidate->weight < ptr_neigh->weight)))
										{
											ptr_neigh_candidate = ptr_neigh;
											i++;
										}
								ptr_neigh = ptr_neigh->next;
							}
				
						//Set the new clusterhead if it exists 
						if (ptr_neigh_candidate != NULL)
							{
								//DEBUG
								if (DEBUG>LOW)
									{
										if ((my_clusterhead.address==my_address) && (DEBUG>LOW))
											{
												sprintf(msg,"!! %d is a useless clusterhead since %f (at %f)\n", my_address , my_clusterhead.last_time_usefull , op_sim_time());
												cluster_message(msg);
											}
										sprintf(msg,"%d chooses %d as new clusterhead (old_ch=%d) (%d candidate)(neighbourhood table) at %f\n" , my_address , ptr_neigh_candidate->clusterhead , my_clusterhead.address , i , op_sim_time());
										cluster_message(msg);
									}				
								//Set Infos
								change_clusterhead(ptr_neigh_candidate->clusterhead , ptr_neigh_candidate->address , ptr_neigh_candidate->clusterhead_hops+1);
								pkptr = hello_packet_generate();					
								pk_send_delayed(pkptr , op_dist_uniform(0.001));
							}
					}
				
					
				//----------------------------------------------------------------
				//
				//					 THEO_NEW Maintenance
				//
				// -> I search a clusterhead candidate
				// -> If no one exists, I search in the neigborhood table
				// -> Else, I will probably send a reconnection request
				//
				//-----------------------------------------------------------------
					
				//Search if a candidate already declared itself to the reconnection
				if ((cluster_algos_type == THEO_NEW) && ((my_clusterhead.construct_cluster==5) || ((my_clusterhead.last_time_usefull < op_sim_time() - 3.1*INTERVALL_HELLO) && (my_clusterhead.address==my_address))))
					{
						//We eliminate dead entries
						delete_timeout_cluster_candidates();			
						
						//We search the best candidate
						ptr_cand = my_clusterhead.reconnect_candidates;
						ptr_cand2 = NULL;
						i=0;
						while(ptr_cand!=NULL)
							{
								if ((ptr_cand->address!=0) && (ptr_cand->address!=my_address) && ((ptr_cand2 == NULL) || (ptr_cand->weight > ptr_cand2->weight)))
									ptr_cand2 = ptr_cand;
								ptr_cand = ptr_cand->next;
								i++;
							}
									
						//We have one candidate (the best)
						if (ptr_cand2!=NULL)
							{	
								//We change our clusterhead
								if (ptr_cand2->address != my_clusterhead.address)
									{
										if (DEBUG>LOW)
											{
												if (my_clusterhead.address==my_address)
													{
														sprintf(msg,"%d useless clusterhead since %f (at %f)\n",my_address,my_clusterhead.last_time_usefull,op_sim_time());
														cluster_message(msg);
													}
												sprintf(msg,"%d chooses %d as new clusterhead (%d candidate) at %f\n",my_address,ptr_cand2->address,i,op_sim_time());
												cluster_message(msg);
											}
								
										//Set the new clusterhead
										op_pk_nfd_get(ptr_cand2->pk,"SRC",&address_src);
										op_pk_nfd_get(ptr_cand2->pk,"TTL",&ttl);
				
										change_clusterhead(ptr_cand2->address,address_src,k_cluster-k_cds-ttl+1);
										pkptr = hello_packet_generate();
										pk_send_delayed(pkptr , op_dist_uniform(0.001));						
									}
								//The candidate is our old clusterhead -> nothing to do
								else
									{
										if (DEBUG>LOW)
											{
												sprintf(msg,"%d : our clusterhead (%d) is already the best -> we keep it at %f\n",my_address,ptr_cand2->address,op_sim_time());
												cluster_message(msg);
											}
										change_clusterhead(ptr_cand2->address,address_src,k_cluster-k_cds-ttl+1);
									}
							}	
						//Searches a potential candidate in the neighbourhood table (restricted conditions to avoid loops, and normal candidates must already answer to a cluster-reconnect)
						else
							{
								i=0;
								//Searches one candidate
								ptr_neigh = neighbour_table;
								ptr_neigh_candidate = NULL;
								while(ptr_neigh!=NULL)
									{
										//If the node is one of our son or father and its clusterhead is valid, we choose it !
										is_cluster_neighbour = (is_my_son(ptr_neigh->address)) || (my_cds.father==ptr_neigh->address) ;
										
										//CH valid -> not too far, highest weight, clusterhead different (restrictive to avoid loops)
										is_valid_clusterhead = (ptr_neigh->clusterhead > 0) && (ptr_neigh->clusterhead_hops+1 <= k_cluster-k_cds) && ((ptr_neigh->clusterhead != my_clusterhead.address) || (ptr_neigh->clusterhead_hops < my_clusterhead.hops));    // && ((ptr_neigh_candidate==NULL)||(ptr_neigh_candidate->weight < ptr_neigh->weight));
										
										if ((is_cluster_neighbour) && (is_valid_clusterhead) && ((ptr_neigh_candidate==NULL) || (ptr_neigh_candidate->weight < ptr_neigh->weight)))
												{
													ptr_neigh_candidate = ptr_neigh;
													i++;
												}
										ptr_neigh = ptr_neigh->next;
									}
				
								//Set the new clusterhead if it exists 
								if (ptr_neigh_candidate != NULL)
									{
										//DEBUG
										if (DEBUG>LOW)
											{
												if ((my_clusterhead.address==my_address) && (DEBUG>LOW))
													{
														sprintf(msg,"!! %d is a useless clusterhead since %f (at %f)\n", my_address , my_clusterhead.last_time_usefull , op_sim_time());
														cluster_message(msg);
													}
												sprintf(msg,"%d chooses %d as new clusterhead (old_ch=%d) (%d candidate)(neighbourhood table) at %f\n" , my_address , ptr_neigh_candidate->clusterhead , my_clusterhead.address , i , op_sim_time());
												cluster_message(msg);
											}				
										//Set Infos
										change_clusterhead(ptr_neigh_candidate->clusterhead , ptr_neigh_candidate->address , ptr_neigh_candidate->clusterhead_hops+1);
										pkptr = hello_packet_generate();					
										pk_send_delayed(pkptr , op_dist_uniform(0.001));
									}
							}
					}
				
				
				/*----------------------------------------------
					Cluster Connection request - Useless Dom
				-----------------------------------------------*/
				//For Useless Dominators which didn't find a new Clusterhead
				if ((my_clusterhead.last_time_usefull < op_sim_time() - 3.1*INTERVALL_HELLO) && (my_clusterhead.address==my_address) && (cluster_algos_type != THEO_NEW2))
					{
						send_connect_ch();
						if(DEBUG>MEDIUM)
							{
								sprintf(msg,"%d tries to find a new clusterhead (I am a useless clusterhead, with father=%d) at %f\n" , my_address ,  my_cds.father , op_sim_time());
								cluster_message(msg);
							}
					}
				
				/*--------------------------------------
						Cluster Connection request
				--------------------------------------*/
				//Try to find a new clusterhead (sends a request packet) if we are disconnected
				//THEO_NEW2 Maintenance -> I become directly a clusterhead if I have no candidate (It's useless to send a pk, the potential candidates are only my 1-neighbors)
				if (my_clusterhead.construct_cluster==5)
					{
						if ((cluster_algos_type != THEO_NEW2) && (my_clusterhead.nb_recon_try < NB_MAX_TRY_RECONNECT_CLUSTER) && (my_cds.father != 0))
							{
								//Stats of nb pkts, reconnections...
								if (my_clusterhead.nb_recon_try == 0)
									nb_cluster_con++;
								nb_cluster_con_req++;
								my_clusterhead.nb_recon_try++;
						
								//Request Packet
								send_connect_ch();
								if(DEBUG>LOW)
									{
										sprintf(msg,"%d tries to find a new clusterhead (old clusterhead=%d and father=%d) at %f\n",my_address,my_clusterhead.address,my_cds.father,op_sim_time());
										cluster_message(msg);
									}
							}
						else if (my_cds.father!=0)
							{				
								//Reinitializes its clusterhead infos
								if(DEBUG>LOW)
									{
										sprintf(msg,"%d becomes clusterhead (old ch=%d and old father=%d), it fails to reconnect to one cluster (after %d attempts) at %f\n",my_address,my_clusterhead.address,my_cds.father,my_clusterhead.nb_recon_try,op_sim_time());
										cluster_message(msg);
									}
								become_clusterhead();
								my_clusterhead.nb_recon_try = 0;
							}
					}
				
				
				
				//Reschedule the next interruption
				//Normal maintenance
				if ((my_cds.state==DOMINATOR) && (my_clusterhead.construct_cluster==4))
					op_intrpt_schedule_self(op_sim_time() + INTERVALL_HELLO , CLUSTER_MAINTENANCE_CODE);
				//Quick maintenance
				else if ((my_cds.state==DOMINATOR) && (my_clusterhead.construct_cluster==5))
					op_intrpt_schedule_self(op_sim_time() + 1.0 , CLUSTER_MAINTENANCE_CODE);
				}


			/** state (CLUSTER Maintenance) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "CLUSTER Maintenance", "cdcl_process_cluster_cds_process () [CLUSTER Maintenance exit execs]")
				{
				}


			/** state (CLUSTER Maintenance) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "CLUSTER Maintenance", "Idle")
				/*---------------------------------------------------------*/



			/** state (CLUSTER) enter executives **/
			FSM_STATE_ENTER_FORCED (7, state7_enter_exec, "CLUSTER", "cdcl_process_cluster_cds_process () [CLUSTER enter execs]")
				{
				char			msg[150];
				neigh_cell		*neigh_ptr;
				cluster_cell	*clus_ptr;
				short			alone;
				
				if ((is_AP)&&(my_clusterhead.construct_cluster == 0))
					my_clusterhead.construct_cluster = 1;
				
				if (DEBUG>MAX)
					{
						sprintf(msg,"cluster - step(%d) - %f\n",my_clusterhead.construct_cluster,op_sim_time());
						cluster_message(msg);
					}
				
				//Deletes the timeout entries
				update_cluster_table();
				
				
				switch(my_clusterhead.construct_cluster){
					case 1 :
						switch(my_cds.state){
							case DOMINATOR :
								//Generates cluster-hello and enters in the election process
								op_intrpt_schedule_call (op_sim_time() , CLUSTER_HELLO_CODE , cluster_hello , -1);
								op_intrpt_schedule_self (op_sim_time() + INTERVALL_FAST_HELLO , CONSTRUCT_CLUSTER_CODE);	//I wait fast-hellos to be certain that I will have no more cds-neighbours
								my_clusterhead.construct_cluster = 2;
								break;
							case DOMINATEE:
								//Ends the construction (my clusterhead is the clusterhead of my dominator)
								my_clusterhead.construct_cluster = 3;
								break;
							case IDLE :
							case ACTIVE :
								//Waits
								op_intrpt_schedule_self(op_sim_time()+INTERVALL_FAST_HELLO,CONSTRUCT_CLUSTER_CODE);
								break;
						}
						
						//Sets our cluster init flag
						neigh_ptr = neighbour_table;
						while((neigh_ptr!=NULL)&&(neigh_ptr->address!=my_address))
							{
								neigh_ptr = neigh_ptr->next;
							}
						if (neigh_ptr!=NULL)
							neigh_ptr->cluster_init_flag = 1;	
				
						break;
					case 2 :
						//I have at least one father/son, or I must start the maintenance process
						clus_ptr = cluster_table;
						alone = OPC_TRUE;
						while((clus_ptr!=NULL)&&(alone))
							{
								if ((clus_ptr->address != my_address) && (has_no_clusterhead(clus_ptr->address)) && ((clus_ptr->address==my_cds.father) || (is_my_son(clus_ptr->address))))
									alone = OPC_FALSE;
								clus_ptr = clus_ptr->next;
							}
						if (DEBUG>LOW)
							{
								sprintf(msg,"var maintenance : alone=%d - clus_init =%d - highest weight=%d\n" , alone , all_neighbours_cluster_init() , own_highest_weight_cluster());
								cluster_message(msg);
							}
				
						if (all_neighbours_cluster_init() || is_AP)
							{
						
								if (alone && !is_AP)
									{
										my_clusterhead.construct_cluster = 5;
										op_intrpt_schedule_self(op_sim_time(),CLUSTER_MAINTENANCE_CODE);
									}
								//Else, I verify if I must elect my self
								else
									{
										if ((own_highest_weight_cluster())&&(my_clusterhead.address==0)&& ((my_cds.last_hello_ap_seen > op_sim_time() - 1.5*INTERVALL_AP_HELLO*TIMEOUT_AP_HELLO) || (is_AP)))
											{
												become_clusterhead();	
												op_intrpt_schedule_self(op_sim_time(),CLUSTER_MAINTENANCE_CODE);
											}
										else
											{
												if (my_clusterhead.address==0)
													op_intrpt_schedule_self(op_sim_time()+INTERVALL_FAST_HELLO,CONSTRUCT_CLUSTER_CODE);
											}
									}
							}
						else
							{
								//If I am dominatee, I don't need to participate in the cluster election, else I wait ...
								if ((my_clusterhead.address==0)&&(my_cds.state == DOMINATOR))//&&(!alone))
									op_intrpt_schedule_self(op_sim_time() + INTERVALL_FAST_HELLO, CONSTRUCT_CLUSTER_CODE);
							}
						break;
					case 4 :
					case 5 :
						//I delete the buffer for this interruption
						op_intrpt_disable(OPC_INTRPT_SELF , CLUSTER_MAINTENANCE_CODE , OPC_TRUE);
						//I create a new interruption
						op_intrpt_schedule_self(op_sim_time(),CLUSTER_MAINTENANCE_CODE);
						
						if (DEBUG>LOW)
							cluster_message("I must schedule a cluster maintenance, whereas I have already a cluster code reserved to maintenance\n");
					break;
				}
				
				
				}


			/** state (CLUSTER) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "CLUSTER", "cdcl_process_cluster_cds_process () [CLUSTER exit execs]")
				{
				}


			/** state (CLUSTER) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "CLUSTER", "Idle")
				/*---------------------------------------------------------*/



			/** state (CDS) enter executives **/
			FSM_STATE_ENTER_FORCED (8, state8_enter_exec, "CDS", "cdcl_process_cluster_cds_process () [CDS enter execs]")
				{
				char	msg[150];
				
				my_cds.cds_intrpt_end = 0;
				
				//The leader (or elected leader) intializes the interconnection of the MCDS
				if ((is_AP==1) && (my_cds.state==DOMINATOR))
					{
						//Send a join message in order to interconnect the MIS 
						send_join_message();
					}
				
				
				//The leader intializes the construction of the MCDS
				if ((is_AP==1) && (my_cds.state!=DOMINATOR))
					{
						//I become dominator (and do all that is required)
						update_state_cds(DOMINATOR);
				
						change_father(my_address,my_address,0);
						my_cds.id_ap = my_address;
						send_join_message();
					}
				
				//I am not the leader, but I must verify that I have not the hisghest weight of my neighbours
				if (my_cds.state==ACTIVE) 
					{
						if (own_highest_weight())
							{
								update_state_cds(DOMINATOR);
								my_cds.cds_intrpt_end = 0;
							}
						else
							{
								//If all goes well, we don't need such a schedule (but if we have collisions or else ....)
								op_intrpt_schedule_self(op_sim_time()+timeout_construct_cds,CONSTRUCT_CDS_CODE); //schedule the next verification 
								my_cds.cds_intrpt_end = 1;
							}
					}
				
				
				//All the other steps are on the reception of a message, so there are described in "From_Lower"
				}


			/** state (CDS) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "CDS", "cdcl_process_cluster_cds_process () [CDS exit execs]")
				{
				}


			/** state (CDS) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "CDS", "Idle")
				/*---------------------------------------------------------*/



			/** state (END_SIM) enter executives **/
			FSM_STATE_ENTER_FORCED (9, state9_enter_exec, "END_SIM", "cdcl_process_cluster_cds_process () [END_SIM enter execs]")
				{
				neigh_cell	*ptr;
				Boolean		is_dominatee_isolated;
				//Control
				FILE 		*stat_file;
				FILE		*ap_unicast_file;
				int			int_value;		//For temporary tests
				int			i;
				int			j;
				double		duration_nb_stats;
				//Speeds	
				int			speed_class;	//Defines the speed class
				double		SPEED_LOW_MIN;
				double		SPEED_LOW_MAX;
				double		SPEED_HIGH_MIN;
				double		SPEED_HIGH_MAX ;
				double		x_max , y_max;
				//Parameters	
				char		filename	[100];
				char		en_model_tmp[100];
				char		metric_tmp	[100];
				int			nb_connections;
				//Strings
				char		msg	[1000];
				char		msg2[20];
				char		msg3[5];
				//BB Flooding
				double		bb_flooding_delivery_ratio;
				double		bb_flooding_delivery_ratio_for_one_flooding;
				double		bb_flooding_average_delay;
				int			nb_receivers_for_one_flooding;
				char		bb_flooding_receivers  [MAX_NB_NODES*sizeof(char)*5];
				char		bb_flooding_error_nodes[MAX_NB_NODES*sizeof(char)*5];
				//AP Unicast
				int			ap_unicast_nb_pk_rcvd			= 0;
				double		ap_unicast_average_delay		= 0;
				double		ap_unicast_average_hops			= 0;
				//Length of routes
				double		average_length = 0;
				
				//----------------------------------------------------------------
				//
				//						STATS PER NODE
				//
				//----------------------------------------------------------------
				
				
				if (DEBUG > 0)
					{
						//In order to keep good statistics 
						update_tables();
				
						//Info per node
						print_general_infos();
						print_neighbour_table();
						print_neighbours_of_neighbours_table();
						print_cds_infos();
						print_ap_hellos_table();
						print_cluster_table();
						print_cluster_infos();
				
						print_acks_pk_table();
						//print_cluster_topo();
						//print_global_gateways();
				
						print_my_gw_list();
						print_gw_lists_of_neighbour_table();
					}
						
				
				
				
				
				//----------------------------------------------------------------
				//
				//						GLOBAL STATS
				//
				//----------------------------------------------------------------
				
				
				
				//-----------------------------
				// Cplex
				//-----------------------------
				//compute_stats_about_graph_cluster_cds();
				//average_length = write_cplex_files();
				
				
				//---------------------------------------------------------------------------
				// DURATION OF SIMULATION FROM THE START COLLECTING
				//---------------------------------------------------------------------------
				duration_nb_stats = (op_sim_time() - TIME_BEGIN_STATS);
				//duration_nb_stats = nb_stats_collections;//(op_sim_time() - TIME_BEGIN_STATS) * (1 / INTERVALL_STATS_COLLECTING);
				
				//--------------------------------
				//Stats about Mobility + Position
				//--------------------------------
				if (op_ima_obj_attr_exists(op_topo_parent(op_id_self()), "mobility.Speed_Class") == OPC_TRUE)
					{
						op_ima_obj_attr_get(op_topo_parent(op_id_self()), "mobility.Speed_Class", &speed_class);
						if (is_AP)
							nb_low_speed_nodes++;
						switch(speed_class)		
							{
								case LOW_SPEED :
									nb_low_speed_nodes++;
								break;
								case HIGH_SPEED :
									nb_high_speed_nodes++;
								break;
							}
					}
				
				op_ima_sim_attr_get(OPC_IMA_DOUBLE , "X_MAX" , &x_max);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE , "Y_MAX" , &y_max); 
				
				
				//-----------------------------
				//Stats about upper layer
				//-----------------------------
				
				switch(process_higher_layer_type){
						case LOCALIZATION :
						case ROUTING :
							op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_CONNECTIONS", 	&nb_connections);	
						break;
						default:
							nb_connections = 0;
						break;
					}
				
				
				
				
				
				//-----------------------------
				//Stats about Energy
				//-----------------------------
				round(msg  , my_energy.value/1000 , 0 , OPC_TRUE);
				round(msg2 , (my_energy.initial_value - my_energy.value)/1000 , 0 , OPC_TRUE);
				round(msg3 , is_sleeping.cumul_sleeping_time , 0 , OPC_TRUE);
				
				if (strcmp(stat_energy_conso_record,"")==0)
					sprintf(stat_energy_conso_record,"Address	Final Energy	Energy Consumption	Sleeping Time	initial_energy/necessary_energy	Dead Time	Weakest Node\n");
				sprintf(stat_energy_conso_record,"%s->%d : 	%s		%s				%s			%f					%f		%d\n" , stat_energy_conso_record , my_address , msg , msg2 , msg3 , my_energy.initial_value/(op_sim_time()*IDLE_CONSUMPTION) , is_DEAD.time , my_stat_id == stat_id_weakest_node);
				
				sprintf(final_weights_of_all_nodes,"%s%d : %d\n", final_weights_of_all_nodes , my_address , my_weight.value);
				
				if (my_cds.state == DOMINATOR)
					{
						stat_conso_dominator.time += op_sim_time() - my_cds.previous_state_change_time;
						stat_conso_dominator.energy += my_energy.previous_value - my_energy.value;
						my_cds.previous_state_change_time = op_sim_time();
						my_energy.previous_value = my_energy.value;
					}
				if (my_cds.state == DOMINATEE)
					{
						stat_conso_dominatee.time += op_sim_time() - my_cds.previous_state_change_time;
						stat_conso_dominatee.energy +=  my_energy.previous_value - my_energy.value;
						my_cds.previous_state_change_time = op_sim_time();
						my_energy.previous_value = my_energy.value;
					}	
				//Energy for the weakest node (Minima comparison)
				if ((my_energy.initial_value < energy_weakest_node) || (energy_weakest_node == -1))
					{
						energy_weakest_node 			= my_energy.initial_value;
						energy_sleeping_weakest_node 	= is_sleeping.cumul_sleeping_time;
					}
				
				
				
				//---------------------------------------------------------------------
				//Sons, Dominatees, Weight of dominators, Dominators usefull/useless
				//---------------------------------------------------------------------
				if (my_cds.state==DOMINATOR)
					{
						final_nb_dominators++;
				
						//Nb of dominatees
						int_value = count_nb_dominatees();
						final_dominatees_per_dominator += int_value;				
						//Min and max dominatees per dominator
						if (((final_nb_dominatees_min > int_value)&&(int_value!=0))||(final_nb_dominatees_min==-1))
							final_nb_dominatees_min = int_value;
						if (final_nb_dominatees_max < int_value)
							final_nb_dominatees_max = int_value;
						//Nb dominator without dominatees (interconnection only)
						if (int_value==0)
							final_nb_dominator_without_dominatees++;
						
						//Nb of sons
						int_value = count_nb_sons();
						final_sons_per_dominator = final_sons_per_dominator + int_value;
						if (final_nb_sons_max < int_value)
							final_nb_sons_max = int_value;	
					
						//Weight of dominators (all / only those with dominatees)
						if (!is_wireless_router)
							final_weight_dom += my_weight.value;
						if (((count_nb_dominatees() != 0) || (count_nb_sons() != 0))  &&(!is_wireless_router))
								final_weight_usefull_dom += my_weight.value;
						
						
					}
				//-----------------------------
				//Weight, Isolated Nodes
				//-----------------------------
				if (!is_wireless_router)
					final_weight += my_weight.value;	
				int_value=0;
				ptr=neighbour_table;
				while(ptr!=NULL)
					{
						if (ptr->hops==1)
							int_value++;
						ptr=ptr->next;
					}
				if (final_max_degree<int_value)
					final_max_degree = int_value;
				final_degree += int_value;
				final_k_neighbours += nb_neighbours(k_cds);
				
				//For dominatees : verify that my father already exists
				ptr = neighbour_table;
				is_dominatee_isolated = 1;
				while (ptr != NULL)
					{			
						if ((ptr->address == my_cds.father)&&(ptr->state == DOMINATOR)&&(ptr->hops <= k_cds)&&(ptr->bidirect==1))
							is_dominatee_isolated = 0;
						ptr	= ptr->next;
					}
				//-----------------------------
				//For dead nodes
				//-----------------------------
				if (is_DEAD.bool)
					{
						if (strcmp(list_dead_nodes,"")==0)
							sprintf(list_dead_nodes,"%d",my_address);
						else
							sprintf(list_dead_nodes,"%s  |  %d",list_dead_nodes,my_address);		
					}
				
				//-----------------------------
				//For isolated dominators
				//-----------------------------
				if ((my_cds.state==DOMINATOR)&&(my_cds.last_hello_ap_seen < op_sim_time() - INTERVALL_AP_HELLO*TIMEOUT_AP_HELLO)&&(!is_AP))
					{
						final_nb_isolated_dominators++;
						if (strcmp(final_list_isolated_dominators,"")==0)
							sprintf(final_list_isolated_dominators,"%d",my_address);
						else
							sprintf(final_list_isolated_dominators,"%s  |  %d",final_list_isolated_dominators,my_address);
					}
				
				//Update the disconnection time if I am not actually connected (my_cds.time_last_break!=-1)
				if ((my_cds.time_last_break!=-1) && (!is_AP))
					average_cds_percentage_time_disconnected = average_cds_percentage_time_disconnected + (op_sim_time() - my_cds.time_last_break);
				
				
				//-----------------------------
				//			 Clusters 
				//-----------------------------
				//The dominatees don't have infos of presence of their clusterhead (only dominators are involved)
				if (((my_clusterhead.address==0)||(my_clusterhead.relay_last_seen < 1.1*INTERVALL_HELLO))&&(my_cds.state==DOMINATOR))
					{
						if (strcmp(final_list_nodes_without_clusterhead,"")==0)
							sprintf(final_list_nodes_without_clusterhead,"%d",my_address);
						else
							sprintf(final_list_nodes_without_clusterhead,"%s  |  %d",final_list_nodes_without_clusterhead,my_address);
						final_nb_nodes_without_clusterhead++;
					}
				if (my_clusterhead.address==my_address)
					{
						if (strcmp(final_list_clusterheads,"")==0)
							sprintf(final_list_clusterheads,"%d",my_address);
						else
							sprintf(final_list_clusterheads,"%s  |  %d",final_list_clusterheads,my_address);
						final_nb_clusterheads++;
					}
				
				//-----------------------------
				//		Writes stats
				//-----------------------------
				
				written_nodes++;	
				if (written_nodes == nb_total)
					{
						//-----------------------------------
						//  BACKBONE FLOODING
						//-----------------------------------
						bb_flooding_delivery_ratio = 0;
						for(i=0 ; i < current_bb_flooding_id ; i++)
							{
								//Results
								sprintf(msg,"For Pk %d\n",i);
								bb_flooding_message(msg);
								sprintf(bb_flooding_error_nodes,"		");
								sprintf(bb_flooding_receivers,"		");
								
								//Delays
								if (stats_bb_flooding [i].time_reception != 0)
									bb_flooding_average_delay += stats_bb_flooding [i].time_reception - stats_bb_flooding [i].time_emission;				
								
								//Reinitliazes the delivery rate for this pk
								bb_flooding_delivery_ratio_for_one_flooding	= 0;
								nb_receivers_for_one_flooding 				= 0;
								
								//Foreach node
								for(j=0 ; j < nb_total ; j++)						
									{
										//Counts the number of node which received this packet
										if (stats_bb_flooding [i].is_dominator[j])
											{
												bb_flooding_delivery_ratio_for_one_flooding 	+= stats_bb_flooding [i].is_rcvd[j];
												nb_receivers_for_one_flooding 					+= stats_bb_flooding [i].is_dominator[j];
										
												if (stats_bb_flooding[i].is_rcvd [j])
													sprintf(bb_flooding_receivers ,"%s|%d" , bb_flooding_receivers , stats_id_to_addresses[j]);
												else
													sprintf(bb_flooding_error_nodes ,"%s|%d" , bb_flooding_error_nodes , stats_id_to_addresses[j]);
											}
									}
								
								//Results
								sprintf(msg," Receivers:	%s\n Not receivers : %s\n Delivery ratio for this pk : %f\n" , bb_flooding_receivers , bb_flooding_error_nodes , bb_flooding_delivery_ratio_for_one_flooding / nb_receivers_for_one_flooding);
								bb_flooding_message(msg);
				
								//Computes the final delivery rate of this packet and adds it to the delivery rate for all pks
								bb_flooding_delivery_ratio += bb_flooding_delivery_ratio_for_one_flooding / nb_receivers_for_one_flooding;
							}
						//Average delivey rate
						if (current_bb_flooding_id != 0)
							bb_flooding_delivery_ratio = bb_flooding_delivery_ratio / current_bb_flooding_id;
						else
							bb_flooding_delivery_ratio = 0;
						
				
						//-----------------------------------
						//  UNICAST AP - BB CONNECTIVITY
						//-----------------------------------
						if (current_ap_unicast_id != 0)
							{
								sprintf(filename,"results/%sdebug_pk_ap_unicast%s.txt", prefix_results_file , suffix_results_file);
								ap_unicast_file = fopen(filename,"w");
								fprintf(ap_unicast_file , "	SRC	|	DEST	|	HOPS	|	EMISSION	|	RECEPTION\n");
						
								for(i=0 ; i < current_ap_unicast_id ; i++)
									{
										if (stats_ap_unicast[i].time_reception != 0)
											{
												ap_unicast_nb_pk_rcvd++;
												ap_unicast_average_delay	+= stats_ap_unicast[i].time_reception - stats_ap_unicast[i].time_emission;
												ap_unicast_average_hops		+= stats_ap_unicast[i].hops;
											}
										fprintf(ap_unicast_file , "	%d	|	%d	|	%d	|	%f	|	%f\n", stats_ap_unicast[i].source , stats_ap_unicast[i].dest , stats_ap_unicast[i].hops , stats_ap_unicast[i].time_emission , stats_ap_unicast[i].time_reception);
									}
								fclose(ap_unicast_file);
							}
						
						
						//-----------------------------------
						//FILE Opening
						//-----------------------------------
				
						sprintf(filename,"results/%sglobal_stats%s.txt",  prefix_results_file , suffix_results_file);
						stat_file=fopen(filename,"w");
						if (stat_file==NULL) 
							printf("I cannot create/open the file for statistics results\n");
						
						//-----------------------------------
						//Gathers some parameters
						//-----------------------------------
						
						op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MIN", 	&SPEED_HIGH_MIN); 
						op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MAX",	&SPEED_HIGH_MAX); 
						op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MIN", 	&SPEED_LOW_MIN); 
						op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MAX",	&SPEED_LOW_MAX); 
						
						//To get the energy model used
						switch (energy_management){
							case 0:
									sprintf(en_model_tmp,"Without energy Management");
								break;
							case 1:
									sprintf(en_model_tmp,"With standard Energy Management");
								break;
							case 2:
									sprintf(en_model_tmp,"With standard Energy Management and Sleeping Mode");
								break;
							default:
									op_sim_end("Unknown Energy Model" , "to generate files for statistics" , "in  write_global_statistics()" , "");
								break;
						}
						switch (metric){
							case LOWEST_ID:
									sprintf(metric_tmp,"Lowest Id");
								break;
							case HIGHEST_DEGREE:
									sprintf(metric_tmp,"Highest Degre (=nb neighbours)");
								break;
							case MOBILITY:
									sprintf(metric_tmp,"Mobility");
								break;
							case THEO_WEIGHT:
									sprintf(metric_tmp,"Theo Weight (combination)");
								break;
							case OTHER_DEGREE:
									sprintf(metric_tmp,"Optimized Degree");
								break;
							default:
									op_sim_end("Unknown Metric" , "to generate files for statistics" , "in  write_global_statistics()" , "");
								break;
						}			
					
						//-----------------------------------
						//Writes Values
						//-----------------------------------
				
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"----------------------------- General -------------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"---------------------------- Parameters -----------------------\n");
						fprintf(stat_file, "Nb AP								:	%d\n",					nb_aps);
						fprintf(stat_file, "Nb Wireless Routers					:	%d\n",					nb_wireless_routers);
						fprintf(stat_file, "Nb Nodes							:	%d\n",					nb_total);
						fprintf(stat_file, "Energy Model						:	%s\n",					en_model_tmp);
						fprintf(stat_file, "Metric							:	%s\n",						metric_tmp);
						fprintf(stat_file, "->High Speed \n");
						fprintf(stat_file, "Speed Min							:	%f\n",					SPEED_HIGH_MIN);
						fprintf(stat_file, "Speed Max							:	%f\n",					SPEED_HIGH_MAX);
						fprintf(stat_file, "Nb Nodes							:	%d\n",					nb_high_speed_nodes);
						fprintf(stat_file, "->Low Speed\n");
						fprintf(stat_file, "Speed Min							:	%f\n",					SPEED_LOW_MIN);
						fprintf(stat_file, "Speed Max							:	%f\n",					SPEED_LOW_MAX);
						fprintf(stat_file, "Nb Nodes							:	%d\n",					nb_low_speed_nodes);
						fprintf(stat_file, "X_MAX								:	%f\n",					x_max);
						fprintf(stat_file, "Y_MAX								:	%f\n",					y_max);
						fprintf(stat_file, "Duration (seconds)					:	%f\n",					op_sim_time());
						fprintf(stat_file, "Number of Communicating Nodes				:	%d\n", 			nb_connections);
						fprintf(stat_file, "CDS Radius							:	%d\n",					k_cds);
						fprintf(stat_file, "Cluster Radius						:	%d\n",					k_cluster);
						fprintf(stat_file, "CDS Maintenance Type					:	%d\n",					cds_algos_type);
						fprintf(stat_file, "Clusters Maintenance Type				:	%d\n",				cluster_algos_type);
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"------------- Environment : Average Statistics ----------------\n");
						fprintf(stat_file,"Nb Total of nodes						:	%d\n",			nb_total);
						fprintf(stat_file,"Average Degree 				 		:	%f\n",				average_degree / (nb_total * nb_stats_collections));
						fprintf(stat_file, "Average Distance						:	%f\n", 			average_length / ((nb_total-1)*(nb_total-1)));
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"-------------------- Final Environment ------------------------\n");
						fprintf(stat_file,"Average Weight 				 		:	%f	(except wireless routers)\n",			final_weight				/(nb_total-nb_aps-nb_wireless_routers));
						fprintf(stat_file,"Average weight of dominators 				:	%f	(except wireless routers)\n",	final_weight_dom			/(final_nb_dominators-nb_aps-nb_wireless_routers));			
						fprintf(stat_file,"Average weight of dominators with dominatees	:	%f	(except wireless routers)\n",	final_weight_usefull_dom	/(final_nb_dominators-final_nb_dominator_without_dominatees-nb_aps-nb_wireless_routers));	
						fprintf(stat_file,"Average Degree 				 		:	%f\n",				final_degree/nb_total);
						fprintf(stat_file,"Maximal Degree 		 				:	%d\n",				final_max_degree);
						fprintf(stat_file,"Average %d-Neighbours 					:	%f\n",			k_cds,final_k_neighbours/nb_total);			
						fprintf(stat_file,"\n\n");
				
						
				
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"-------------------------------- Cds -------------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"\n\n");
						
						
						fprintf(stat_file,"---------------------- Cds - Average Informations ----------------\n");
						fprintf(stat_file,"Average Nb of Dominatees		 		:	%f\n", 				(float)average_nb_dominatees		/ nb_stats_collections);
						fprintf(stat_file,"Average Nb of Dominators		 		:	%f\n", 				(float)average_nb_dominators		/ nb_stats_collections);
						fprintf(stat_file,"Average Nb of Secondary Parents 			:	%f\n", 			(float)average_nb_secondary_fathers	/ nb_stats_collections);
						fprintf(stat_file,"Average Nb of Backbone Interconnections 		:	%f\n", 		(float)average_nb_cds_connectors	/ nb_stats_collections);
						fprintf(stat_file,"Average Disconnection Time for A Dominatee	:	%f\n",		average_seconds_of_disconnection_for_dominatees/((float)average_nb_dominatees/(nb_stats_collections)));
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"--------------------- Cds - Final State Informations -------------\n");
						fprintf(stat_file,"-- About dominators --\n");
						fprintf(stat_file,"Nb Dominators of the Cds		 		:	%d\n",				final_nb_dominators);	
						fprintf(stat_file,"Nb Isolated Dominators					:	%d\n",			final_nb_isolated_dominators);
						fprintf(stat_file,"List of Isolated Dominators 				:	%s\n",			final_list_isolated_dominators);
						fprintf(stat_file,"\n");
						fprintf(stat_file,"-- About dominatees and sons --\n");
						fprintf(stat_file,"Nb Dominatees per dominator		 		:	%f\n", 			final_dominatees_per_dominator/(final_nb_dominators-final_nb_dominator_without_dominatees));
						fprintf(stat_file,"Nb Dominator without dominatee	 		:	%d\n",			final_nb_dominator_without_dominatees);
						fprintf(stat_file,"Nb Max Dominatees 			 		:	%d\n",				final_nb_dominatees_max);
						fprintf(stat_file,"Nb Min Dominatees 			 		:	%d\n",				final_nb_dominatees_min);
						fprintf(stat_file,"Nb Sons per dominator			 		:	%f\n",			final_sons_per_dominator/final_nb_dominators);
						fprintf(stat_file,"Nb Max Sons		 			 		:	%d\n",				final_nb_sons_max);
						fprintf(stat_file,"\n\n");
				
						
						fprintf(stat_file,"----------------------------- Connection -------------------------\n");
						fprintf(stat_file,"Connexity Percentage (estimation)			:	%f\n",		1-average_cds_percentage_time_disconnected / ((nb_total - nb_dead_nodes - nb_aps)*(nb_stats_collections)));
						fprintf(stat_file,"Connexity Percentage (exact, strict CDS)		:	%f\n",		average_cds_connexity_strict  / nb_stats_collections);
						fprintf(stat_file,"Connexity Percentage (exact, large CDS)		:	%f\n",		average_cds_connexity_large   / nb_stats_collections);
						fprintf(stat_file,"\n\n");
						
						
						fprintf(stat_file,"----------------------------- Maintenance ------------------------\n");
						fprintf(stat_file,"Nb CDS-Reconnections					:	%d\n",				nb_cds_recon);
						fprintf(stat_file,"Nb reconnection-requests per reconnection		:	%f\n",	(float)nb_cds_recon_req / (float)nb_cds_recon);
						fprintf(stat_file,"Nb packet per reconnection-requests 		:	%f\n",			(float)nb_cds_recon_pk  / (float)nb_cds_recon_req);
						fprintf(stat_file,"Nb Breaks of the Cds			 		:	%d\n",				nb_cds_breaks);
						fprintf(stat_file,"Nb Nodes impacted by Cds-Break		 	:	%f\n",			nb_nodes_impacted_by_cds_breaks / (float)nb_cds_breaks);
						fprintf(stat_file,"Nb changes of dominators 				:	%d\n",			nb_changes_of_dominators);
						fprintf(stat_file,"Nb Dominatees which changed their dominator	:	%d\n",		nb_dominatees_which_change_their_dominator);
						fprintf(stat_file,"Nb Nodes which changed their parent			:	%d\n",		nb_nodes_which_change_their_dominator);
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"------------------------------ Clusters -----------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");			
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"------------------ Clusters - Average Informations ------------\n");
						fprintf(stat_file,"Average Nb of clusterheads 				:	%f\n",			(float) average_nb_clusterheads / nb_stats_collections);
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"-------------- Clusters - Final State Informations -----------\n");
						fprintf(stat_file,"Nb clusterheads 						:	%d\n",				final_nb_clusterheads);
						fprintf(stat_file,"List of Clusterheads	 				:	%s\n",				final_list_clusterheads);
						fprintf(stat_file,"Nb Nodes without Clusterhead 				:	%d\n",		final_nb_nodes_without_clusterhead);
						fprintf(stat_file,"List of Nodes without clusterhead			:	%s\n",		final_list_nodes_without_clusterhead);			
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"----------------------------- Connection -----------------------\n");
						fprintf(stat_file,"Percentage time Connection/dominator		:	%f\n",			1-average_cluster_percentage_time_disconnected/((nb_total-nb_dead_nodes)*(op_sim_time()-TIME_BEGIN_STATS)));
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"----------------------------- Maintenance ----------------------\n");
						fprintf(stat_file,"Nb Reconnections to a Cluster			 	:	%d\n",		nb_cluster_con);					
						fprintf(stat_file,"Nb reconnection-requests per reconnection		:	%f\n",	(float)nb_cluster_con_req/(float)nb_cluster_con);					
						fprintf(stat_file,"Nb packets per reconnection-requests 		:	%f\n",		(float)nb_cluster_con_pk/(float)nb_cluster_con_req);					
						fprintf(stat_file,"Nb changes of clusterhead				:	%d\n",			nb_changes_of_clusterheads);
						fprintf(stat_file,"Nb Dominators which changed their clusterhead 	:	%d\n",	nb_dominators_which_change_their_clusterheads);
						fprintf(stat_file,"Nb Nodes which changed their clusterhead 		:	%d\n",	nb_nodes_which_change_their_clusterheads);
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"------------------------ Virtual topology ----------------------\n");
						fprintf(stat_file,"Nb changes of virtual topology			:	%d\n",			nb_chgts_virtual_topo);
						fprintf(stat_file,"Nb changes of virtual topology . (node.s)^-1	:	%f\n",		nb_chgts_virtual_topo/(nb_total*op_sim_time()));
						fprintf(stat_file,"Nb changes of real topology				:	%d\n",			nb_chgts_real_topo);
						fprintf(stat_file,"Nb changes of real topology . (node.s)^-1		:	%f\n",	nb_chgts_real_topo/(nb_total*op_sim_time()));
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"------------------------- Network control ---------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"---------- General Average Flows in pk/(node.s) -----------\n");
						fprintf(stat_file,"Hellos							:	%f\n",			(float) nb_pk_hello_total				/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Cds								:	%f\n",			(float) nb_pk_cds_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Ap Hellos							:	%f\n",		(float) nb_pk_ap_hello_total			/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Clusters							:	%f\n",			(float) nb_pk_cluster_total				/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Other								:	%f\n",		(float) nb_pk_other_total				/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Data								:	%f\n",			(float) nb_pk_data_total				/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Acks								:	%f\n",			(float) nb_pk_ack_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Backbone Multicast					:	%f\n",		(float) nb_pk_bb_multicast_total		/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Backbone Multicast Retransmissions			:	%f\n",(float) nb_pk_ret_bb_multicast_total	/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Total 							:	%f\n",			(float) (nb_pk_hello_total + nb_pk_cds_total + nb_pk_ap_hello_total + nb_pk_cluster_total + nb_pk_other_total + nb_pk_data_total + nb_pk_ack_total + nb_pk_bb_multicast_total + nb_pk_ret_bb_multicast_total) / (duration_nb_stats * nb_total));
						fprintf(stat_file,"\n\n");
						
						//dom_average = dom_average / duration
						fprintf(stat_file,"--- Average Flows For Dominators/Dominatees in pk/(node.s) ---\n");
						fprintf(stat_file,"hello - Dominator						:	%f\n",		(float) nb_pk_hello_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"hello - Dominatee						:	%f\n",		(float) nb_pk_hello_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"cds - Dominator						:	%f\n",			(float) nb_pk_cds_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"cds - Dominatee						:	%f\n",			(float) nb_pk_cds_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"ap_hellos - Dominator					:	%f\n",		(float) nb_pk_ap_hello_dominator_total			/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"ap_hellos - Dominatee					:	%f\n",		(float) nb_pk_ap_hello_dominatee_total			/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"cluster - Dominator					:	%f\n",			(float) nb_pk_cluster_dominator_total			/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"cluster - Dominatee					:	%f\n",			(float) nb_pk_cluster_dominatee_total			/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"other - Dominator						:	%f\n",		(float) nb_pk_other_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"other - Dominatee						:	%f\n",		(float) nb_pk_other_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"data - Dominator						:	%f\n",			(float) nb_pk_data_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"data - Dominatee						:	%f\n",			(float) nb_pk_data_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"acks - Dominator						:	%f\n",			(float) nb_pk_ack_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"acks - Dominatee						:	%f\n",			(float) nb_pk_ack_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"bb multicast - Dominator				:	%f\n",			(float) nb_pk_bb_multicast_dominator_total		/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"bb multicast - Dominatee				:	%f\n",			(float) nb_pk_bb_multicast_dominatee_total		/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"bb multicast retransmissions - Dominator		:	%f\n",	(float) nb_pk_ret_bb_multicast_dominator_total	/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"bb multicast retransmissions - Dominatee		:	%f\n",	(float) nb_pk_ret_bb_multicast_dominatee_total	/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"total - Dominator						:	%f\n",		(float) (nb_pk_hello_dominator_total + nb_pk_cds_dominator_total + nb_pk_ap_hello_dominator_total + nb_pk_cluster_dominator_total + nb_pk_other_dominator_total + nb_pk_data_dominator_total + nb_pk_bb_multicast_dominator_total + nb_pk_ret_bb_multicast_dominator_total) / (duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"Total - Dominatee						:	%f\n",		(float) (nb_pk_hello_dominatee_total + nb_pk_cds_dominatee_total + nb_pk_ap_hello_dominatee_total + nb_pk_cluster_dominatee_total + nb_pk_other_dominatee_total + nb_pk_data_dominatee_total + nb_pk_bb_multicast_dominatee_total + nb_pk_ret_bb_multicast_dominatee_total) / (duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"---------- General Average Flows in bits/(node.s) -----------\n");
						fprintf(stat_file,"Hellos							:	%f\n",			(float) nb_bits_hello_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Cds								:	%f\n",			(float) nb_bits_cds_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Ap Hellos							:	%f\n",		(float) nb_bits_ap_hello_total				/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Clusters							:	%f\n",			(float) nb_bits_cluster_total				/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Other								:	%f\n",		(float) nb_bits_other_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Data								:	%f\n",			(float) nb_bits_data_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Acks								:	%f\n",			(float) nb_bits_ack_total					/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Backbone Multicast					:	%f\n",		(float) nb_bits_bb_multicast_total			/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Backbone Multicast Retransmissions			:	%f\n",(float) nb_bits_ret_bb_multicast_total	/(duration_nb_stats * nb_total));
						fprintf(stat_file,"Total 							:	%f\n",			(float) (nb_bits_hello_total + nb_bits_cds_total + nb_bits_ap_hello_total + nb_bits_cluster_total + nb_bits_other_total + nb_bits_data_total + nb_bits_ack_total + nb_bits_bb_multicast_total + nb_bits_ret_bb_multicast_total) / (duration_nb_stats * nb_total));
						fprintf(stat_file,"\n\n");
						
						//dom_average = dom_average / duration
						fprintf(stat_file,"--- Average Flows For Dominators/Dominatees in bits/(node.s) ---\n");
						fprintf(stat_file,"hello - Dominator						:	%f\n",		(float) nb_bits_hello_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"hello - Dominatee						:	%f\n",		(float) nb_bits_hello_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"cds - Dominator						:	%f\n",			(float) nb_bits_cds_dominator_total					/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"cds - Dominatee						:	%f\n",			(float) nb_bits_cds_dominatee_total					/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"ap_hellos - Dominator					:	%f\n",		(float) nb_bits_ap_hello_dominator_total			/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"ap_hellos - Dominatee					:	%f\n",		(float) nb_bits_ap_hello_dominatee_total			/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"cluster - Dominator					:	%f\n",			(float) nb_bits_cluster_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"cluster - Dominatee					:	%f\n",			(float) nb_bits_cluster_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"other - Dominator						:	%f\n",		(float) nb_bits_other_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"other - Dominatee						:	%f\n",		(float) nb_bits_other_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"data - Dominator						:	%f\n",			(float) nb_bits_data_dominator_total				/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"data - Dominatee						:	%f\n",			(float) nb_bits_data_dominatee_total				/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"acks - Dominator						:	%f\n",			(float) nb_bits_ack_dominator_total					/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"acks - Dominatee						:	%f\n",			(float) nb_bits_ack_dominatee_total					/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"bb multicast - Dominator				:	%f\n",			(float) nb_bits_bb_multicast_dominator_total		/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"bb multicast - Dominatee				:	%f\n",			(float) nb_bits_bb_multicast_dominatee_total		/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"bb multicast retransmissions - Dominator		:	%f\n",	(float) nb_bits_ret_bb_multicast_dominator_total	/(duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"bb multicast retransmissions - Dominatee		:	%f\n",	(float) nb_bits_ret_bb_multicast_dominatee_total	/(duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"total - Dominator						:	%f\n",		(float) (nb_bits_hello_dominator_total + nb_bits_cds_dominator_total + nb_bits_ap_hello_dominator_total + nb_bits_cluster_dominator_total + nb_bits_other_dominator_total + nb_bits_data_dominator_total + nb_bits_bb_multicast_dominator_total + nb_bits_ret_bb_multicast_dominator_total) / (duration_nb_stats * average_nb_dominators / nb_stats_collections));
						fprintf(stat_file,"Total - Dominatee						:	%f\n",		(float) (nb_bits_hello_dominatee_total + nb_bits_cds_dominatee_total + nb_bits_ap_hello_dominatee_total + nb_bits_cluster_dominatee_total + nb_bits_other_dominatee_total + nb_bits_data_dominatee_total + nb_bits_bb_multicast_dominatee_total + nb_bits_ret_bb_multicast_dominatee_total) / (duration_nb_stats * average_nb_dominatees / nb_stats_collections));
						fprintf(stat_file,"\n\n");
						
				
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"--------------------- Backbone Floooding ----------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"----------------- Transmissions (per flooding) --------------------\n");
						fprintf(stat_file,"Nb bakbone floodings initiated			:	%d\n",	current_bb_flooding_id);
						fprintf(stat_file,"backbone multicast - Dominator			:	%f\n",	(float)nb_pk_bb_multicast_dominator_total / current_bb_flooding_id);
						fprintf(stat_file,"backbone multicast - Dominatee			:	%f\n",	(float)nb_pk_bb_multicast_dominatee_total / current_bb_flooding_id);
						fprintf(stat_file,"acks - Dominator						:	%f\n",		(float)nb_pk_ack_dominator_total / current_bb_flooding_id);
						fprintf(stat_file,"acks - Dominatee						:	%f\n",		(float)nb_pk_ack_dominatee_total / current_bb_flooding_id);
						fprintf(stat_file,"backbone multicast - Total				:	%f\n",	((float)nb_pk_bb_multicast_dominatee_total + nb_pk_bb_multicast_dominator_total + nb_pk_ack_dominator_total + nb_pk_ack_dominatee_total)  / current_bb_flooding_id);
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"--------------- Retransmissions (per flooding) ------------------\n");
						fprintf(stat_file,"backbone multicast - Dominator			:	%f\n",	(float)nb_pk_ret_bb_multicast_dominator_total / current_bb_flooding_id);
						fprintf(stat_file,"backbone multicast - Dominatee			:	%f\n",	(float)nb_pk_ret_bb_multicast_dominatee_total / current_bb_flooding_id);
						fprintf(stat_file,"backbone multicast - Total				:	%f\n",	((float)nb_pk_ret_bb_multicast_dominatee_total + nb_pk_ret_bb_multicast_dominator_total)  / current_bb_flooding_id);
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"------------------------ Performances ---------------------------\n");
						fprintf(stat_file,"Average delay before last reception			:	%f\n",	(float)bb_flooding_average_delay / current_bb_flooding_id);
						fprintf(stat_file,"Delivery ratio						:	%f\n",			(float)bb_flooding_delivery_ratio);
						fprintf(stat_file,"\n\n");
						
						
				
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"----------------------- AP Transmission -----------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"\n\n");
						
						
						fprintf(stat_file,"Number of pk sent to the AP				:	%d\n",	current_ap_unicast_id);
						fprintf(stat_file,"Delivery Ratio						:	%f\n",		(double)ap_unicast_nb_pk_rcvd / current_ap_unicast_id);
						fprintf(stat_file,"Average Delay						:	%f\n",		(double)ap_unicast_average_delay / current_ap_unicast_id);
						fprintf(stat_file,"Average Length						:	%f\n",		(double)ap_unicast_average_hops / current_ap_unicast_id);
						fprintf(stat_file,"\n\n");
						
						
						
						fprintf(stat_file,"\n\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"----------------------------- Energy --------------------------\n");
						fprintf(stat_file,"---------------------------------------------------------------\n");
						fprintf(stat_file,"\n\n");
				
						fprintf(stat_file,"---------------------------- Dead Nodes -----------------------\n");
						fprintf(stat_file,"Dead Nodes							:	%d\n",					nb_dead_nodes);			
						fprintf(stat_file,"List od Dead Nodes					:	%s\n",					list_dead_nodes);			
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"---------------------------- Sleep ----------------------------\n");
						fprintf(stat_file,"Sleeping Time per Node in seconds			:	%f\n",			cumul_sleeping_time/nb_total);
						fprintf(stat_file,"Avg. Energy of sleeping Nodes (mW)			:	%f\n",			average_energy_sleeping_nodes / (1000*nb_sleeps));
						fprintf(stat_file,"Sleeping time of the weakest node			:	%f\n",			energy_sleeping_weakest_node);
						fprintf(stat_file,"Energy of the Weakest Node (mW)			:	%f\n",				energy_weakest_node/1000);
						fprintf(stat_file,"\n\n");
				
				
						fprintf(stat_file,"---------------------------- Sleep ----------------------------\n");
						fprintf(stat_file,"Avg. Energy consumtion (mW) per sec (dominator)	:	%f\n",		stat_conso_dominator.energy/(stat_conso_dominator.time*1000));
						fprintf(stat_file,"Avg. Energy consumtion (mW) per sec (dominatee)	:	%f\n",		stat_conso_dominatee.energy/(stat_conso_dominatee.time*1000));
						fprintf(stat_file,"\n\n");
						
						fprintf(stat_file,"------------------ Energy Consumption ------------------------\n");
						fprintf(stat_file,"%s\n",stat_energy_conso_record);
						fprintf(stat_file,"\n\n");
				
				
						
						//Closes the file
						fclose(stat_file);
					}
				
				
				
				
				
				}


			/** state (END_SIM) exit executives **/
			FSM_STATE_EXIT_FORCED (9, "END_SIM", "cdcl_process_cluster_cds_process () [END_SIM exit execs]")
				{
				}


			/** state (END_SIM) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "END_SIM", "Idle")
				/*---------------------------------------------------------*/



			/** state (DEAD) enter executives **/
			FSM_STATE_ENTER_UNFORCED (10, state10_enter_exec, "DEAD", "cdcl_process_cluster_cds_process () [DEAD enter execs]")
				{
				//if (my_address==2)
				//	op_sim_end("2 is dead","","","");
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (21,cdcl_process_cluster_cds_process)


			/** state (DEAD) exit executives **/
			FSM_STATE_EXIT_UNFORCED (10, "DEAD", "cdcl_process_cluster_cds_process () [DEAD exit execs]")
				{
				}


			/** state (DEAD) transition processing **/
			FSM_INIT_COND (ENDSIM)
			FSM_TEST_COND (!ENDSIM)
			FSM_TEST_LOGIC ("DEAD")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 9, state9_enter_exec, ;, "ENDSIM", "", "DEAD", "END_SIM")
				FSM_CASE_TRANSIT (1, 10, state10_enter_exec, ;, "!ENDSIM", "", "DEAD", "DEAD")
				}
				/*---------------------------------------------------------*/



			/** state (CDS Maintenance) enter executives **/
			FSM_STATE_ENTER_FORCED (11, state11_enter_exec, "CDS Maintenance", "cdcl_process_cluster_cds_process () [CDS Maintenance enter execs]")
				{
				//Conditions for each type of maintenance
				Boolean			is_father_alive;
				Boolean			is_loop_entered;
				Boolean			is_father_gone;
				Boolean			is_reconstruct_required;
				Boolean			is_reconstruct_from_dominatee_required;
				Boolean			is_useless_dominator;
				//Time between 2 cds-maintenance
				double			next_maintenance_scheduled =1.0 ;
				//To discover a new father
				Boolean			is_new_candidate_found = OPC_FALSE;
				int				old_father;
				int				new_father , new_father_weight , new_father_relay , new_father_hops , new_father_ap_hops;
				//The best relay toward our father (for dominatees)
				int				best_relay_father_hops  = 0;
				neigh_cell		*best_relay;
				//Neighorhood table manipulation
				neigh_cell		*ptr_neigh, *ptr_neigh2;
				son				*ptr_son;
				dominatee		*ptr_dominatee;
				//Maintenance for dominators (connectivity to the backbone)
				int				id_last_ap_hello;
				ap_hellos		*ptr_hello,*ptr_hello2;
				int				id_hello, id_ap;
				//New father for dominators
				candidate		*ptr_cand , *ptr_cand2;
				//For reconnection requests
				int				ttl_cds_reconnect_req;
				//Control
				int				i , j;
				char			msg[250];
				
				
				if (DEBUG>MAX)
					{
						sprintf(msg,"cds maintenance  - %f\n",op_sim_time());
						cluster_message(msg);
					}	
				
						
					//---------------------------------------------
					//	Elimination of dead entries in CDS Table
					//----------------------------------------------
					update_tables();
					
					
					//---------------------------------------------
					//		Elimination of useless dominators
					//----------------------------------------------
					//The dominators which have no sons or dominatees are useless. The father must be different from 0 (in initialization or pb mode)
					//My father remains unchanged
					if ((my_cds.state==DOMINATOR)&&(my_cds.father!=0))
						{
							ptr_neigh = neighbour_table;
							is_useless_dominator = 1;
							while(ptr_neigh!=NULL)
								{
									if (is_my_son(ptr_neigh->address) && (ptr_neigh->hops == 1))
										is_useless_dominator = OPC_FALSE;
									if (is_my_dominatee(ptr_neigh->address) && (ptr_neigh->hops == k_cds))
										is_useless_dominator = OPC_FALSE;
									ptr_neigh = ptr_neigh->next;
								}
				
							//Old Maintenance: a dominator-clusterhead is useless only if it is a useless-clusterhead too
							if ((cds_algos_type == THEO_OLD) || (cds_algos_type == THEO_NEW))
								is_useless_dominator = (is_useless_dominator && ((my_clusterhead.address!=my_address)||(my_clusterhead.last_time_usefull < op_sim_time() - TIMEOUT_HELLO*INTERVALL_HELLO)));
							
							//New Maintenance2: The useless dominators lose their role of clusterhead, other dominators must become clusterhead -> minimizes the number of dominators (BB independent from clusters)			
							if ((!is_AP) && is_useless_dominator)
								{
									if ((my_cds.time_dominator_usefull < op_sim_time() - TIMEOUT_HELLO*INTERVALL_HELLO) || ((!is_my_father_alive_for_dominator() && (my_cds.time_dominator_usefull < op_sim_time() - INTERVALL_HELLO) && (cds_algos_type == THEO_NEW2))))
										{
											//Change my clusterhead, and stop to send "clusterhead-hellos"
											if (cluster_algos_type == THEO_OLD)
												op_intrpt_disable(OPC_INTRPT_SELF,CLUSTERHEAD_HELLO_CODE,OPC_TRUE);
											if (DEBUG>LOW)
												{
													sprintf(msg,"%d is a useless dominator-clusterhead at %f\n",my_address,op_sim_time());
													cluster_message(msg);
												}
										
											//Useless dominator
											if (DEBUG>LOW)
												{
													sprintf(msg,"%d is a useless dominator at %f (useless since %f)\n", my_address,op_sim_time(),my_cds.time_dominator_usefull);
													cluster_message(msg);
													print_sons();
													print_dominatees();
												}							
											advertise_useless_dominator();
											update_state_cds(DOMINATEE);
										}
								}
							else
								my_cds.time_dominator_usefull = op_sim_time();
				
						}
						
					//---------------------------------------------
					//	Dominators with too low energy (<10%)
					//----------------------------------------------
					if ((my_cds.state==DOMINATOR) && (my_energy.value < my_energy.max_capacity/10))
						{		
							update_state_cds(DOMINATEE);
						
							if (DEBUG>LOW)
								{
									sprintf(msg,"%d is a weak dominator (energy) at %f\n", my_address,op_sim_time());
									cluster_message(msg);
								}							
						
						}
					
					//--------------------------------------------------------------------------
					//	Does it exist one idle neighbor ? -> For reconstruction sollicitation
					//--------------------------------------------------------------------------
					is_father_alive = 0;
					is_reconstruct_required = 0;
				
					ptr_neigh = neighbour_table;
					while (ptr_neigh != NULL)
						{		
							//My father already exists
							if ((ptr_neigh->address != my_address) && (ptr_neigh->address == my_cds.father) && (ptr_neigh->state == DOMINATOR) && (ptr_neigh->hops <= k_cds) && (ptr_neigh->bidirect==1))
								is_father_alive = 1;
							
							//I am dominator or I am dominatee and my dominator (1-neighbour) can't see this node 
							is_reconstruct_from_dominatee_required = ((my_cds.state==DOMINATEE)&&(my_cds.relay==my_cds.father)&&(ptr_neigh->hops==k_cds));
							if ((ptr_neigh->state == IDLE) && ((my_cds.state == DOMINATOR) || (is_reconstruct_from_dominatee_required)))
								is_reconstruct_required =1;
							
							ptr_neigh	= ptr_neigh->next;
						}
					is_father_alive = is_father_alive && (my_cds.relay_timeout >= op_sim_time());
				
					//---------------------------------------------
					//	Verification / optimization of my father
					//----------------------------------------------
					
					//Optimizes in number of hops the relay to father
					if (is_father_alive)
						optimize_relay_to_father();
					
					
					//Initialization of some control variables
					new_father = my_cds.father;
					new_father_weight	= -1;
					new_father_hops		= k_cds+1;
					new_father			= -1;
					
					
					//We verify that our father exists + We optimize our father if necessary
					if ((is_father_alive == 0) && (!is_sleeping.value) && (my_cds.state == DOMINATEE) && (my_cds.time_cds_reinit==-1))
					if ((my_cds.state == DOMINATEE) && (my_cds.time_cds_reinit==-1) && (!is_sleeping.value))
						{
							ptr_neigh = neighbour_table;
							while ((ptr_neigh != NULL) && (new_father != my_cds.father))
								{
									if ( (ptr_neigh->state == DOMINATOR) && (ptr_neigh->address != my_address) && (ptr_neigh->hops<=k_cds) && (ptr_neigh->bidirect))
										{
										//The dominator is 1-Neighbor
											if ((ptr_neigh->hops == 1) && (ptr_neigh->weight > new_father_weight))
												{
													new_father_weight		= ptr_neigh->weight;
													new_father		 		= ptr_neigh->address;
													new_father_relay 		= ptr_neigh->address;
													new_father_hops	 		= 1;
													new_father_ap_hops		= ptr_neigh->ap_hops;
													is_new_candidate_found 	= OPC_TRUE;
												}
											
										//The dominator is not a 1-Neighbor
											if (ptr_neigh->hops != 1)
												{
													best_relay = NULL;									
													
													//Verify that one of my neighbors has this father (forces the connexity of CDS dominatees areas)
													best_relay_father_hops = 0;
													ptr_neigh2 = neighbour_table;
													while (ptr_neigh2 != NULL) 
														{
															if ( ((best_relay_father_hops == 0) || (best_relay_father_hops > ptr_neigh2->father_hops)) && (ptr_neigh2->father == ptr_neigh->address) && (ptr_neigh2->hops == 1) && (ptr_neigh2->father_hops < k_cds) && (ptr_neigh2->address != my_address) && (ptr_neigh2->state == DOMINATEE) && (ptr_neigh2->bidirect))
																{
																	best_relay = ptr_neigh2;
																	best_relay_father_hops = ptr_neigh2->father_hops + 1 ;
																}											
															ptr_neigh2 = ptr_neigh2->next;
														}				
													
													//When we have more than one candidate, we choose firstly:
													//1- Our old father 
													//2- The nearest of the AP
													//3- The nearest
													//4- The higher weight
													if ((best_relay != NULL) && (ptr_neigh->ap_hops >= new_father_hops) && (new_father_hops >= best_relay->father_hops + 1) && (ptr_neigh->weight > new_father_weight))
														{
															is_new_candidate_found 	= OPC_TRUE;
															new_father_weight		= ptr_neigh->weight;
															new_father		 		= ptr_neigh->address;
															new_father_relay 		= best_relay->address;
															new_father_hops	 		= best_relay->father_hops + 1;
															new_father_ap_hops		= ptr_neigh->ap_hops;
														}								
												}
										}	
									ptr_neigh = ptr_neigh->next;
								}
				
							//Verify that such a dominator exists in our neighbourhood
							if (!is_new_candidate_found)
								{
								
									if (DEBUG>LOW)
										{
											sprintf(msg,"%d becomes active at %f (father->0), it has no more dominator in its neighbourhood\n",my_address,op_sim_time());
											cluster_message(msg);
										}
				
									//We become active
									//If I am further disconnected from AP, I will act in consequence (it's a full procedure of maintenance to reconnect the tree)
									update_state_cds(ACTIVE);
									change_father(ZERO , ZERO , ZERO);
									//print_neighbour_table();
								}
							else
								{
								
									if (DEBUG>LOW)
										{
											sprintf(msg,"%d has changed its father from %d to %d, relay %d, father_hops %d at %f (I'm dominatee, timeout_father_relay %d)\n",my_address , my_cds.father , new_father , new_father_relay ,  new_father_hops , op_sim_time() , my_cds.relay , my_cds.relay_timeout >= op_sim_time() );
											cluster_message(msg);
										}				
									if (my_cds.state!=DOMINATEE)
										update_state_cds(DOMINATEE);					
									change_father(new_father,new_father_relay,new_father_hops);
									my_cds.relay_timeout = op_sim_time() + INTERVALL_HELLO * TIMEOUT_RELAY_FATHER;
								}
					
						}
					
					
					//---------------------------------------------
					//			Elimination of dead sons
					//----------------------------------------------
					//We test the presence of each son in the neighbourhood table
					delete_timeouted_in_son_list();
					
				
					//---------------------------------------------
					//			Elimination of dead dominatees
					//----------------------------------------------
					//We test the presence of each dominatee in the neighbour table
					ptr_dominatee = my_cds.dominatees;
					while(ptr_dominatee!=NULL)
						{
							is_loop_entered  = 0;
							ptr_neigh = neighbour_table;
							while (ptr_neigh != NULL)
								{
									if ( (ptr_neigh->address == ptr_dominatee->address) && (ptr_neigh->state==DOMINATEE) )
											is_loop_entered  = 1;
									ptr_neigh = ptr_neigh->next;
								}	
							if ((is_loop_entered ==0) && (ptr_dominatee->address!=0))
								{
									delete_dominatee(ptr_dominatee->address);
									ptr_dominatee = my_cds.dominatees;
								}
				
							if (ptr_dominatee!=NULL)
								ptr_dominatee = ptr_dominatee->next;
						}
					
				   
					
					//--------------------------------------------
					//	Detection of disconnected parts
					//--------------------------------------------
					//To be sure to be a connected dominator
					if ((is_reconstruct_required) && ((is_AP) || ((my_cds.state==DOMINATOR) && (my_cds.last_hello_ap_seen > op_sim_time() - 1.2*INTERVALL_AP_HELLO))))
						{
							if (DEBUG>HIGH)
								cluster_message("I detect a neighbour which has state=nothing\n");
							
							send_join_message();		
							for (i=0;i<2*KCLUSTER_MAX-KCDS_MAX+1;i++) {my_cds.join_already_forwarded[i]=0;}
						}
					
					
					//I must prevent my father
					if ((is_reconstruct_required)&&(my_cds.state==DOMINATEE))
						{			
							if (DEBUG>HIGH)
								cluster_message("I detectect a neighbour which has state=nothing\n");
							
							advertise_our_dominator_of_nothing_neighbour();
							for (i=0;i<2*KCLUSTER_MAX-KCDS_MAX+1;i++) {my_cds.join_already_forwarded[i]=0;}
						}
					
					
					
				
					//--------------------------------------------
					//	Try to reconnect to the tree and AP
					//--------------------------------------------
					if ((!is_AP) && (my_cds.state==DOMINATOR) && (my_cds.time_cds_reinit==-1))
						{			
							//to test if father is alive
							is_father_alive = is_my_father_alive_for_dominator();
							
							//-------------------------------------------------------
							//	If no valid father, choose a candidate if it exists
							//-------------------------------------------------------
							if (!is_father_alive)
								{
									//We eliminate dead entries if proactive maintenance, all entries if reactive maintenance
									if (my_cds.nb_retry_reconnect_cds == 0)
										switch (cds_algos_type)
											{
												case THEO_OLD :
													delete_timeout_cds_candidates(0);
												break;
												case THEO_NEW :
												case THEO_NEW2 :
													delete_timeout_cds_candidates(INTERVALL_AP_HELLO/2);
												break;
											}
				
									
									//We search the best candidate
									ptr_cand = my_cds.secondary_fathers;
									ptr_cand2 = NULL;
									i=0;
									while(ptr_cand!=NULL)
										{
											if (((ptr_cand2 == NULL) || (ptr_cand->weight > ptr_cand2->weight))&&(!is_my_son(ptr_cand->address)))//&&(ptr_cand->parent!=0))//&&(ptr_cand2->address != my_address))
												ptr_cand2 = ptr_cand;
											ptr_cand = ptr_cand->next;
											i++;
										}
				
									//We don't change our father
									if ((ptr_cand2!=NULL) && (ptr_cand2->address==my_cds.father))
										{
											my_cds.nb_retry_reconnect_cds = 0;
											my_cds.last_hello_ap_seen = op_sim_time();
											if (DEBUG>LOW)
												{
													sprintf(msg,"%d : our father (%d) is already the best -> we keep it at %f\n",my_address,ptr_cand2->address,op_sim_time());
													cluster_message(msg);
												}
										}
									
									//We have one candidate (the best)
									if ((ptr_cand2!=NULL) && (ptr_cand2->address!=my_cds.father))
										{
											if (DEBUG>LOW)
												{
													sprintf(msg,"%d chooses %d as new father at %f (its father=%d) (my_old_father=%d) (%d candidates)\n" , my_address , ptr_cand2->address , op_sim_time() , ptr_cand2->parent , my_cds.father,i);
													cluster_message(msg);
												}
											connection_cds_init(op_pk_copy(ptr_cand2->pk));
											my_cds.nb_retry_reconnect_cds = 0;
											my_cds.last_hello_ap_seen = op_sim_time();//ptr_cand2->last_seen;
										}	
								}
								
								
							//--------------------------------------------
							//	Try to reconnect to the tree and AP
							//--------------------------------------------
							if ((!is_father_alive) && (ptr_cand2==NULL))
								{				
									if ((my_cds.nb_retry_reconnect_cds >= NB_MAX_TRY_RECONNECT_CDS) && (my_cds.time_last_cds_reconstruct < op_sim_time()-TIME_BETWEEN_2_BREAKS) && (my_clusterhead.address!=my_address)) //&&(count_nb_sons()==0)
										{
											//1 chance sur 10 de casser la branche (pour éviter les synchros) 
											if (op_dist_uniform(10) <= 1)
												{
													break_all_our_tree();
													if (DEBUG>LOW)
														{
															sprintf(msg,"%d initiates (last time reconstruction=%f) the breaking of its tree at %f (after %d atempts/%d)\n",my_address,my_cds.time_last_cds_reconstruct,op_sim_time(),my_cds.nb_retry_reconnect_cds,NB_MAX_TRY_RECONNECT_CDS);
															cluster_message(msg);
														}
													my_cds.time_cds_reinit = op_sim_time();
													my_cds.nb_retry_reconnect_cds=0;
													nb_cds_breaks++;
												}
				
										}
									else
										{
				
										//printf("%d (%d): nelle reconnexion\n", my_address , my_cds.nb_retry_reconnect_cds);
											if (DEBUG>LOW)
												{
													sprintf(msg,"CDS-RECONNECT: %d tries to reconnect itself to the cds (old_father=%d) at %f (last ap-hello=%f)\n" , my_address , my_cds.father , op_sim_time() , my_cds.last_hello_ap_seen);
													cluster_message(msg);
												}							
				
											//my_cds.father = 0;
											//Search the id of the last ap_hello seen (from our father)
											ptr_hello=ap_hellos_table;
											id_last_ap_hello = 0;
											while(ptr_hello!=NULL)
												{
													if ((ptr_hello->address==my_cds.father)&&(ptr_hello->id_hello>id_last_ap_hello))
														id_last_ap_hello = ptr_hello->id_hello;
													ptr_hello=ptr_hello->next;
												}
											
											//Set the TTL of the cds-reconneciton-request
											//ttl_cds_reconnect_req = (int) ((2*k_cds+1) * NB_MAX_TRY_RECONNECT_CDS / (my_cds.nb_retry_reconnect_cds + 1) );
											//if (ttl_cds_reconnect_req < k_cds)
											//	ttl_cds_reconnect_req = k_cds;
											//if (ttl_cds_reconnect_req > 2*k_cds+1)
											//	ttl_cds_reconnect_req = 2*k_cds+1;
											
											//sends the reconnecion-request
											send_reconnect_request(id_last_ap_hello , 2*k_cds+1);
																		
											//If we have no result further with n retries, we break our part of tree and reconstruct it 
											my_cds.nb_retry_reconnect_cds++;							
											
											//Schedule a quick maintenance for CDS-reconnection (will handle potential CDS-Replies)
											if (my_cds.nb_retry_reconnect_cds < NB_MAX_TRY_RECONNECT_CDS)
												next_maintenance_scheduled = 0.4;
											else
												next_maintenance_scheduled = 2;
										}
										
								}
						}
				
					
					
				
					
				current_id = op_dist_uniform(64000);
				
				
				
				//schedule the next interruption
				op_intrpt_schedule_self(op_sim_time() + next_maintenance_scheduled + op_dist_uniform(0.005)	, 	CDS_MAINTENANCE_CODE);
				
				}


			/** state (CDS Maintenance) exit executives **/
			FSM_STATE_EXIT_FORCED (11, "CDS Maintenance", "cdcl_process_cluster_cds_process () [CDS Maintenance exit execs]")
				{
				}


			/** state (CDS Maintenance) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "CDS Maintenance", "Idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (2,cdcl_process_cluster_cds_process)
		}
	}

#if defined (__cplusplus)
	extern "C" { 
#endif
	extern VosT_Fun_Status Vos_Catmem_Register (const char * , int , VosT_Void_Null_Proc, VosT_Address *);
	extern VosT_Address Vos_Catmem_Alloc (VosT_Address, size_t);
	extern VosT_Fun_Status Vos_Catmem_Dealloc (VosT_Address);
#if defined (__cplusplus)
	}
#endif


Compcode
cdcl_process_cluster_cds_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (cdcl_process_cluster_cds_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (cdcl_process_cluster_cds_process)",
			sizeof (cdcl_process_cluster_cds_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
			{
			FRET (OPC_COMPCODE_FAILURE)
			}
		}

	*gen_state_pptr = Vos_Catmem_Alloc (obtype, 1);
	if (*gen_state_pptr == OPC_NIL)
		{
		FRET (OPC_COMPCODE_FAILURE)
		}
	else
		{
		/* Initialize FSM handling */
		((cdcl_process_cluster_cds_process_state *)(*gen_state_pptr))->current_block = 4;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
cdcl_process_cluster_cds_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
cdcl_process_cluster_cds_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (cdcl_process_cluster_cds_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in cdcl_process_cluster_cds_process_svar function. */
#undef my_address
#undef my_weight
#undef neighbour_table
#undef DEBUG
#undef id_table
#undef current_id
#undef is_AP
#undef my_cds
#undef temporary_pk_list
#undef relay_table
#undef k_cds
#undef ap_hellos_table
#undef hello_method
#undef my_clusterhead
#undef k_cluster
#undef cluster_table
#undef is_wireless_router
#undef old_cluster_topo
#undef my_energy
#undef is_DEAD
#undef is_sleeping
#undef energy_management
#undef metric
#undef last_xy
#undef last_absolute_speeds
#undef nb_chgts_neighbourhood
#undef my_acks
#undef my_stat_id
#undef cds_algos_type
#undef cluster_algos_type
#undef process_higher_layer_id
#undef last_ev_cluster_hello
#undef ici_list
#undef my_gw_list
#undef process_higher_layer_type
#undef is_cluster_knowledge_required
#undef last_son_lost
#undef ack_multicast_list
#undef ttl_for_hellos
#undef overhead_cds_pk
#undef overhead_cds_bits
#undef overhead_cluster_pk
#undef overhead_cluster_bits
#undef overhead_hello_pk
#undef overhead_hello_bits
#undef overhead_route_pk
#undef overhead_route_bits
#undef overhead_data_pk
#undef overhead_data_bits
#undef overhead_paging_pk
#undef overhead_paging_bits
#undef overhead_other_pk
#undef overhead_other_bits
#undef neighbor_table_wu_li
#undef ACK_FOR_BB_MULTICAST
#undef ttl_for_hello_mis



void
cdcl_process_cluster_cds_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	cdcl_process_cluster_cds_process_state		*prs_ptr;

	FIN (cdcl_process_cluster_cds_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (cdcl_process_cluster_cds_process_state *)gen_ptr;

	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
		FOUT;
		}
	if (strcmp ("my_weight" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_weight);
		FOUT;
		}
	if (strcmp ("neighbour_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->neighbour_table);
		FOUT;
		}
	if (strcmp ("DEBUG" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG);
		FOUT;
		}
	if (strcmp ("id_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->id_table);
		FOUT;
		}
	if (strcmp ("current_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_id);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("my_cds" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_cds);
		FOUT;
		}
	if (strcmp ("temporary_pk_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->temporary_pk_list);
		FOUT;
		}
	if (strcmp ("relay_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->relay_table);
		FOUT;
		}
	if (strcmp ("k_cds" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->k_cds);
		FOUT;
		}
	if (strcmp ("ap_hellos_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ap_hellos_table);
		FOUT;
		}
	if (strcmp ("hello_method" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->hello_method);
		FOUT;
		}
	if (strcmp ("my_clusterhead" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_clusterhead);
		FOUT;
		}
	if (strcmp ("k_cluster" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->k_cluster);
		FOUT;
		}
	if (strcmp ("cluster_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->cluster_table);
		FOUT;
		}
	if (strcmp ("is_wireless_router" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_wireless_router);
		FOUT;
		}
	if (strcmp ("old_cluster_topo" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->old_cluster_topo);
		FOUT;
		}
	if (strcmp ("my_energy" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_energy);
		FOUT;
		}
	if (strcmp ("is_DEAD" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_DEAD);
		FOUT;
		}
	if (strcmp ("is_sleeping" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_sleeping);
		FOUT;
		}
	if (strcmp ("energy_management" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->energy_management);
		FOUT;
		}
	if (strcmp ("metric" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->metric);
		FOUT;
		}
	if (strcmp ("last_xy" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->last_xy);
		FOUT;
		}
	if (strcmp ("last_absolute_speeds" , var_name) == 0)
		{
		*var_p_ptr = (char *) (prs_ptr->last_absolute_speeds);
		FOUT;
		}
	if (strcmp ("nb_chgts_neighbourhood" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->nb_chgts_neighbourhood);
		FOUT;
		}
	if (strcmp ("my_acks" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_acks);
		FOUT;
		}
	if (strcmp ("my_stat_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_stat_id);
		FOUT;
		}
	if (strcmp ("cds_algos_type" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->cds_algos_type);
		FOUT;
		}
	if (strcmp ("cluster_algos_type" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->cluster_algos_type);
		FOUT;
		}
	if (strcmp ("process_higher_layer_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->process_higher_layer_id);
		FOUT;
		}
	if (strcmp ("last_ev_cluster_hello" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->last_ev_cluster_hello);
		FOUT;
		}
	if (strcmp ("ici_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ici_list);
		FOUT;
		}
	if (strcmp ("my_gw_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_gw_list);
		FOUT;
		}
	if (strcmp ("process_higher_layer_type" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->process_higher_layer_type);
		FOUT;
		}
	if (strcmp ("is_cluster_knowledge_required" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_cluster_knowledge_required);
		FOUT;
		}
	if (strcmp ("last_son_lost" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->last_son_lost);
		FOUT;
		}
	if (strcmp ("ack_multicast_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_multicast_list);
		FOUT;
		}
	if (strcmp ("ttl_for_hellos" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ttl_for_hellos);
		FOUT;
		}
	if (strcmp ("overhead_cds_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cds_pk);
		FOUT;
		}
	if (strcmp ("overhead_cds_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cds_bits);
		FOUT;
		}
	if (strcmp ("overhead_cluster_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cluster_pk);
		FOUT;
		}
	if (strcmp ("overhead_cluster_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cluster_bits);
		FOUT;
		}
	if (strcmp ("overhead_hello_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_hello_pk);
		FOUT;
		}
	if (strcmp ("overhead_hello_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_hello_bits);
		FOUT;
		}
	if (strcmp ("overhead_route_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_route_pk);
		FOUT;
		}
	if (strcmp ("overhead_route_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_route_bits);
		FOUT;
		}
	if (strcmp ("overhead_data_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_data_pk);
		FOUT;
		}
	if (strcmp ("overhead_data_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_data_bits);
		FOUT;
		}
	if (strcmp ("overhead_paging_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_paging_pk);
		FOUT;
		}
	if (strcmp ("overhead_paging_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_paging_bits);
		FOUT;
		}
	if (strcmp ("overhead_other_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_other_pk);
		FOUT;
		}
	if (strcmp ("overhead_other_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_other_bits);
		FOUT;
		}
	if (strcmp ("neighbor_table_wu_li" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->neighbor_table_wu_li);
		FOUT;
		}
	if (strcmp ("ACK_FOR_BB_MULTICAST" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ACK_FOR_BB_MULTICAST);
		FOUT;
		}
	if (strcmp ("ttl_for_hello_mis" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ttl_for_hello_mis);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

