/* Process model C form file: vsr_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char vsr_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 45924CC3 45924CC3 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
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

// INCLUDES
#include	<oms_dist_support.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>

#include	"../cdcl/cdcl_biblio.h"
#include	"../cdcl/cdcl_gw_list_management.h"


//----------------------------------------------------------------------
//				     		PARAMETERS		
//----------------------------------------------------------------------

//COMMON
#define		INTERVALL_PERIODIC_FUNCTIONS	1.0
//DEBUG LEVEL
#define		NONE							0
#define		LOW								1
#define		MEDIUM							2
#define		HIGH							3

//----------------------------------------------------------------------
//				     		ROUTES		
//----------------------------------------------------------------------

//RREQ - RREP
#define		MAX_RREQ_PK						100000
#define		MAX_RERR_PK						10000
#define		MAX_NB_RREQ_RETRY				4
#define		MAX_CLUSTER_FIELDS_IN_RREQ_PK	15


//ROUTING
#define		TIMEOUT_ROUTING_TABLE			10.0



//----------------------------------------------------------------------
//				     		DATA		
//----------------------------------------------------------------------

//DATA Generation
#define		MAX_DATA_PK						1000000

//Repair
#define		MAX_NB_REPAIRS_IN_DATA_PK		4
#define		MAX_NB_REPAIRS_PER_NODE			1

//Buffer
#define		TIMEOUT_DATA_PK_BUFFER			2.0

//Stats
#define		DIRECT_NEIGH					1
#define		DIRECT_ROUTING					2
#define		RREQ_ROUTING					3

//To store the route for stats and debug
#define		MAX_ROUTE_LENGTH				100

//----------------------------------------------------------------------
//				     		ACKS	
//----------------------------------------------------------------------


// Acks
#define		MAX_NB_RETRIES_UNICAST_ACKS		2
//#define	ACK_FOR_DATA					1
#define		ACK_FOR_RREP					0
#define		ACK_FOR_RERR					0


//----------------------------------------------------------------------
//				     		TIMEOUTS		
//----------------------------------------------------------------------

#define		TIMEOUT_UNICAST_ACK				0.05			//Acks in Unicast
#define		TIMEOUT_ADDR_PK_ID				10.1
#define		TIMEOUT_RREQ_PK_BUFFER			0.20162461
#define		TIMEOUT_ID						5




//----------------------------------------------------------------------
//						PACKETS			
//----------------------------------------------------------------------
//Streams
#define		STRM_FROM_CDCL	   				0
#define		STRM_TO_CDCL					0



//----------------------------------------------------------------------
//						Interruptions			
//----------------------------------------------------------------------

// Interruption codes
//DATA
#define		PK_DATA_GENERATE_CODE			3
//COMMON
#define		PERIODIC_FUNCTIONS_CODE			10
#define		UNICAST_RETRANSMISSIONS_CODE	11
//RREQ
#define		ROUTE_REQUEST_RETRY_CODE		20
//RREP

// Macro definitions for state
#define		ENDSIM							(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define 	PK_FROM_CDCL					(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_CDCL)
#define 	PK_DATA_GENERATE				(op_intrpt_code() == PK_DATA_GENERATE_CODE)
#define		PERIODIC_FUNCTIONS				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == PERIODIC_FUNCTIONS_CODE)
#define		UNICAST_RETRANSMISSIONS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == UNICAST_RETRANSMISSIONS_CODE)






//----------------------------------------------------------------------
//						Structures
//----------------------------------------------------------------------


//For Addr/Pk_id records
typedef struct {
	int			address;
	int			pk_id;
	double		timeout;
} addr_pk_id_couple;



//Acks table
typedef struct{
	int			dest;
	int			pk_id;
	double 		timeout;
	short		nb_retry;
	short		nb_repairs;
	List*		exceptions;
	packet*		pkptr;	
} ack_couple;




//-------- BUFFER ---------

//Data Pk Buffer
typedef struct{
	Packet	*packet;
	int		dest;
	double	timeout;
} struct_pk_buffer;


//RREQ Buffer
typedef struct{
	int		dest;
	double	timeout;
	short	nb_retry;
	int		stat_id;
	packet*	pkptr;	
} struct_rreq_pk_buffer;


//-------- ROUTING TABLE ---------

//Routing Table
typedef struct{
	int 		dest;
	short		hops;
	double		timeout;
	List		*route;
} struct_routing ;



//----------------------------------------------------------------------
//						Structures For Stats Collect
//----------------------------------------------------------------------


//DATA PK
typedef struct{
	int		source;
	int		dest;
	int		pk_size;
	short	hops;
	int		nb_retry;
	int		nb_repairs;
	double	time_generation;
	double	time_emission;
	double	time_reception;
	short	method;
	double	src_x_pos;
	double	src_y_pos;
	double	dest_x_pos;
	double	dest_y_pos;
	char	route[MAX_ROUTE_LENGTH];
} struct_stats_data;


//RREQ/RREP PK
typedef struct{
	int			source;
	int			dest;
	double		rreq_time_emission;
	double		rreq_time_reception;
	int			rreq_nb_retry;
	double		rrep_time_emission;
	double		rrep_time_reception;
	int			rrep_hops;
	int			rrep_nb_retry;
} struct_stats_rreq;

//RERR PK
typedef struct{
	int			source;
	int			dest;
	double		time_emission;
	double		time_reception;
	int			hops;
	int			nb_retry;
} struct_stats_rerr;


//----------------------------------------------------------------------
//				     		STATS
//----------------------------------------------------------------------
//Common

int			nb_nodes;

//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];




//----------------------------------------------------------------------
//	     		Global Variables for Control		
//----------------------------------------------------------------------

//	Common
int			begin_loc_time 			= 0;

// Nb nodes, special nodes... 
int			nb_loc_aps = 0;
int			nb_loc_nodes = 0;

// Speeds
int			nb_loc_high_speed_nodes = 0;
int			nb_loc_low_speed_nodes 	= 0;

//Actual Number of Communicating Nodes
int			current_nb_connections = 0;


//----------------------------------------------------------------------
//				     		Statistics		
//----------------------------------------------------------------------
//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];




//----------------------------------------------------------------------
//			     		Packet Statistics		
//----------------------------------------------------------------------

//In bits

int			nb_routing_pk_ack_instantaneous 							= 0;
int			nb_routing_pk_ack_total 									= 0;

int			nb_routing_pk_data_instantaneous 							= 0;
int			nb_routing_pk_data_total 									= 0;
int			nb_routing_pk_data_retransmission_instantaneous 			= 0;
int			nb_routing_pk_data_retransmission_total 					= 0;

int			nb_routing_pk_rreq_instantaneous 							= 0;
int			nb_routing_pk_rreq_total 									= 0;

int			nb_routing_pk_rrep_instantaneous 							= 0;
int			nb_routing_pk_rrep_total 									= 0;
int			nb_routing_pk_rrep_retransmission_instantaneous 			= 0;
int			nb_routing_pk_rrep_retransmission_total 					= 0;

int			nb_routing_pk_rerr_instantaneous 							= 0;
int			nb_routing_pk_rerr_total 									= 0;
int			nb_routing_pk_rerr_retransmission_instantaneous 			= 0;
int			nb_routing_pk_rerr_retransmission_total 					= 0;

//In bits

int			nb_routing_bits_ack_instantaneous 							= 0;
int			nb_routing_bits_ack_total 									= 0;

int			nb_routing_bits_data_instantaneous 							= 0;
int			nb_routing_bits_data_total 									= 0;
int			nb_routing_bits_data_retransmission_instantaneous 			= 0;
int			nb_routing_bits_data_retransmission_total 					= 0;

int			nb_routing_bits_rreq_instantaneous 							= 0;
int			nb_routing_bits_rreq_total 									= 0;

int			nb_routing_bits_rrep_instantaneous 							= 0;
int			nb_routing_bits_rrep_total 									= 0;
int			nb_routing_bits_rrep_retransmission_instantaneous 			= 0;
int			nb_routing_bits_rrep_retransmission_total 					= 0;

int			nb_routing_bits_rerr_instantaneous 							= 0;
int			nb_routing_bits_rerr_total 									= 0;
int			nb_routing_bits_rerr_retransmission_instantaneous 			= 0;
int			nb_routing_bits_rerr_retransmission_total 					= 0;


//OVERHEADS in the CDCL layer
//In packets
int			overhead_total_cdcl_cds_pk									= 0;
int			overhead_total_cdcl_cluster_pk								= 0;
int			overhead_total_cdcl_hello_pk								= 0;

//In bits
int			overhead_total_cdcl_cds_bits								= 0;
int			overhead_total_cdcl_cluster_bits							= 0;
int			overhead_total_cdcl_hello_bits								= 0;



//----------------------------------------------------------------------
//						    Data 	Packets		
//----------------------------------------------------------------------
struct_stats_data	stats_data_pk 	[MAX_DATA_PK];

int			stats_nb_data_pk 		= 0;


/*----------------------------------------------------------------------
					    RREQ / RREP 	Packets		
----------------------------------------------------------------------*/
struct_stats_rreq	stats_rreq 	[MAX_RREQ_PK];
struct_stats_rerr	stats_rerr 	[MAX_RERR_PK];

int			stats_nb_rreq 				= 0;
int			stats_nb_rerr 				= 0;








//----------------------------------------------------------------------
//				     		PROTOTYPES		
//----------------------------------------------------------------------



//--------------    DEBUG  --------------

void 	vsr_debug(char*msg);
void 	vsr_data(char*msg);
void 	vsr_rreq(char*msg);
void	vsr_rrep(char*msg);
void	vsr_rerr(char*msg);
void 	vsr_ack(char*msg);
void 	vsr_route(char*msg);
void 	vsr_node(char*msg);

void 	print_rreq_pk_buffer();
void 	print_unicast_ack_table();
char* 	print_route(List* route);
void 	print_routing_table();
void 	print_data_pk_buffer();
void 	print_neigh_table();



//------------    NETWORK  --------------

void 	send_delayed(Packet* pkptr , double delay);
void 	send (Packet* pkptr);
void 	retransmit_delayed(Packet* pkptr , double delay);
void 	retransmit (Packet* pkptr);

Boolean	is_in_list(List* ll , int addr);
void 	add_in_list(List* ll  , int addr);



//------------    ROUTE REQUESTS  --------------

void	send_route_request(int addr);
void 	send_rreq_pk(int addr_searched , int stat_id);
void 	add_my_cluster_in_cluster_relay_fields(Packet* pkptr);



//------------    ROUTE REPLIES  --------------

void 	send_route_reply(Packet* pk_src , int addr_src , int addr_searched , int stat_id);
//int 	get_next_hop_from_cluster_relay_fields(Packet* pkptr , int node_searched);
//int 	search_next_hop_for_cluster(int addr_cluster , int node_searched);


//------------    ROUTE MANAGEMENT  --------------

void 	delete_timeout_in_routing_table (int useless_var , int code);
void 	add_routing_entry (List* route, int dest , short hops);

List* 	create_route_from_pk(Packet* pkptr);
void 	fill_pk_with_route(Packet* pk_src , List* route);

int 	get_relay_to_node_from_routing_table(int address , Packet* pk_src , List* exceptions);
int 	get_relay_to_neighbour_node(int addr , List* exceptions);
int 	get_next_hop_from_cluster_route(List* route , Boolean update , List* exceptions);
int		get_next_hop_from_neigh_table_to(int dest , List* exceptions); 



//------------   DATA  --------------

void 	add_in_data_pk_buffer(Packet *pk_dest);
int 	get_initial_next_hop_for_data_pk(Packet* pk_src , int dest_final , List* exceptions);
int 	get_forward_next_hop_for_data_pk(Packet* pk_src , int dest_final , List *exceptions);
Boolean initiate_local_repair_for_data_pk(Packet* pkptr , List* exceptions);



//------------   ACK  --------------

void 	send_timeouted_in_ack_table(int* arg, int code);
void 	add_unicast_ack(Packet* pkptr);
void 	delete_unicast_ack(int dest , int pk_id);
void 	acknowledges_unicast_packet(int address , int pk_id);

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
	int	                    		is_AP;
	List*	                  		addr_pk_id_list;
	List*	                  		ack_table;
	int	                    		my_ap;
	int	                    		current_id;
	int	                    		my_stat_id;
	int	                    		NB_CONNECTIONS;
	int	                    		DEBUG_DATA;
	int	                    		DEBUG_ROUTE;
	List*	                  		routing_table;
	List*	                  		rreq_pk_buffer;
	clusterhead*	           		my_clusterhead;
	neigh_cell*	            		neighbour_table;
	cds*	                   		my_cds;
	List*	                  		data_pk_buffer;
	int	                    		DEBUG_LOAD;
	int	                    		DATA_PK_SIZE;
	int	                    		DEBUG_ACK;
	double	                 		INTERARRIVAL_DATA_PK;
	int	                    		NB_PK_PER_FLOW;
	int*	                   		overhead_cdcl_cds;
	int*	                   		overhead_cdcl_cluster;
	int*	                   		overhead_cdcl_hello;
	int	                    		ACK_FOR_DATA;
	} vsr_process_state;

#define pr_state_ptr            		((vsr_process_state*) SimI_Mod_State_Ptr)
#define my_address              		pr_state_ptr->my_address
#define is_AP                   		pr_state_ptr->is_AP
#define addr_pk_id_list         		pr_state_ptr->addr_pk_id_list
#define ack_table               		pr_state_ptr->ack_table
#define my_ap                   		pr_state_ptr->my_ap
#define current_id              		pr_state_ptr->current_id
#define my_stat_id              		pr_state_ptr->my_stat_id
#define NB_CONNECTIONS          		pr_state_ptr->NB_CONNECTIONS
#define DEBUG_DATA              		pr_state_ptr->DEBUG_DATA
#define DEBUG_ROUTE             		pr_state_ptr->DEBUG_ROUTE
#define routing_table           		pr_state_ptr->routing_table
#define rreq_pk_buffer          		pr_state_ptr->rreq_pk_buffer
#define my_clusterhead          		pr_state_ptr->my_clusterhead
#define neighbour_table         		pr_state_ptr->neighbour_table
#define my_cds                  		pr_state_ptr->my_cds
#define data_pk_buffer          		pr_state_ptr->data_pk_buffer
#define DEBUG_LOAD              		pr_state_ptr->DEBUG_LOAD
#define DATA_PK_SIZE            		pr_state_ptr->DATA_PK_SIZE
#define DEBUG_ACK               		pr_state_ptr->DEBUG_ACK
#define INTERARRIVAL_DATA_PK    		pr_state_ptr->INTERARRIVAL_DATA_PK
#define NB_PK_PER_FLOW          		pr_state_ptr->NB_PK_PER_FLOW
#define overhead_cdcl_cds       		pr_state_ptr->overhead_cdcl_cds
#define overhead_cdcl_cluster   		pr_state_ptr->overhead_cdcl_cluster
#define overhead_cdcl_hello     		pr_state_ptr->overhead_cdcl_hello
#define ACK_FOR_DATA            		pr_state_ptr->ACK_FOR_DATA

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	vsr_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								PACKETS COMMON
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Deletes all entries that are timeouted
void delete_timeout_in_addr_pk_id_list(){
	int					i = 0;
	addr_pk_id_couple*	entry;
	char				msg[150];
	
	//If the list is empty
	if (op_prg_list_size(addr_pk_id_list)==0)
		return;
	
	//Search if the entry already exists
	while (i< op_prg_list_size(addr_pk_id_list))
		{
			entry = (addr_pk_id_couple*) op_prg_list_access (addr_pk_id_list, i);
			
			//We delete the entry
			if (entry->timeout < op_sim_time())
				{				
					//DEBUG
					if (DEBUG_ROUTE >= HIGH)
						{
							sprintf(msg,"ID-TABLE : deletes the address %d with pk_id %d with timeout %f at %f\n", entry->address , entry->pk_id , entry->timeout , op_sim_time());
							vsr_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( addr_pk_id_list , i);
					free(entry);
				}
			else
				i++;
		}
}

//=1 if that packet was already seen, 0 else
Boolean addr_pk_id_not_seen (int addr , int pk_id) {
	int					i=0;
	addr_pk_id_couple*	couple;
	
	//For each entry of the list ...
	for(i=0; i< op_prg_list_size(addr_pk_id_list);i++)
		{  
			couple = (addr_pk_id_couple*) op_prg_list_access(addr_pk_id_list,i);
			//.....compare it
			if ((couple->address == addr) && (couple->pk_id == pk_id))
				return(OPC_FALSE);
		}
	return (OPC_TRUE);
}

//Adds this packet as already seen
void add_addr_id_couple(int addr , int pk_id){
	addr_pk_id_couple*		couple;
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (addr_pk_id_couple*) op_prg_mem_alloc ( sizeof (addr_pk_id_couple));
	
	//Info
	couple->address 	= addr;
	couple->pk_id		= pk_id;
	couple->timeout		= op_sim_time() + TIMEOUT_ADDR_PK_ID;
	
	//Insert it
	op_prg_list_insert( addr_pk_id_list, couple, OPC_LISTPOS_TAIL);	
}


















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								NETWORK
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void vsr_stats_about_control_pk_flows(Packet* pkptr){
	char	msg[50];
	int		option_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
	
	//Gets the type associated to the option_type
	switch (option_type)
		{
			case ACK_APP_PK_TYPE :
				type = ACK;
			break;
			case DATA_PK_TYPE :
				type = DATA;
			break;
			case RREQ_PK_TYPE :
				type = RREQ;
			break;
			case RREP_PK_TYPE :
				type = RREP;
			break;
			case RERR_PK_TYPE :
				type = RERR;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case ACK :
				nb_routing_pk_ack_instantaneous++;
				nb_routing_bits_ack_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_ack_total++;
						nb_routing_bits_ack_total += op_pk_total_size_get(pkptr);
					}
			break;
			case DATA :
				nb_routing_pk_data_instantaneous++;
				nb_routing_bits_data_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_data_total++;
						nb_routing_bits_data_total += op_pk_total_size_get(pkptr);
					}
			break;
			case RREQ :
				nb_routing_pk_rreq_instantaneous++;
				nb_routing_bits_rreq_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_rreq_total++;
						nb_routing_bits_rreq_total += op_pk_total_size_get(pkptr);
					}
			break;
			case RREP :
				nb_routing_pk_rrep_instantaneous++;
				nb_routing_bits_rrep_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_rrep_total++;
						nb_routing_bits_rrep_total += op_pk_total_size_get(pkptr);
					}
			break;
			case RERR :
				nb_routing_pk_rerr_instantaneous++;
				nb_routing_bits_rerr_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_rerr_total++;
						nb_routing_bits_rerr_total += op_pk_total_size_get(pkptr);
					}
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void vsr_stats_about_control_pk_flows_retransmission(Packet* pkptr){
	char	msg[50];
	int		option_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
	
	//Gets the type associated to the option_type
	switch (option_type)
		{
			case DATA_PK_TYPE :
				type = DATA;
			break;
			case RREP_PK_TYPE :
				type = RREP;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case DATA :
				nb_routing_pk_data_retransmission_instantaneous++;
				nb_routing_bits_data_retransmission_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_data_retransmission_total++;
						nb_routing_bits_data_retransmission_total += op_pk_total_size_get(pkptr);
					}
			break;
			case RREP :
				nb_routing_pk_rrep_retransmission_instantaneous++;
				nb_routing_bits_rrep_retransmission_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_rrep_retransmission_total++;
						nb_routing_bits_rrep_retransmission_total += op_pk_total_size_get(pkptr);
					}
			break;
			case RERR :
				nb_routing_pk_rerr_retransmission_instantaneous++;
				nb_routing_bits_rerr_retransmission_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						nb_routing_pk_rerr_retransmission_total++;
						nb_routing_bits_rerr_retransmission_total += op_pk_total_size_get(pkptr);
					}
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Sends the packet with the specified delay
void send_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	
	//Stats
	vsr_stats_about_control_pk_flows(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", &address_dest);
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &pk_type);
	
	//Transmission
	op_pk_send_delayed(pkptr , STRM_TO_CDCL , delay);
}

//Sends the packet without delay
void send (Packet* pkptr){
	send_delayed(pkptr , 0);
}


//Retransmits the packet with the specified delay
void retransmit_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	
	//Stats
	vsr_stats_about_control_pk_flows_retransmission(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", &address_dest);
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &pk_type);
	
	//Transmission
	op_pk_send_delayed(pkptr , STRM_TO_CDCL , delay);
}

//Retransmits the packet without delay
void retransmit (Packet* pkptr){
	retransmit_delayed(pkptr , 0);
}

//Is addr in the list ?
Boolean	is_in_list(List* ll , int addr){
	int		*elem;
	int		i;
	
	for(i=0; i < op_prg_list_size(ll) ; i++)
		{
			elem = (int*) op_prg_list_access(ll , i);
			if (*elem == addr)
				return(OPC_TRUE);
		}
	return(OPC_FALSE);
}

//Adds an integer in the list "ll"
void add_in_list(List* ll  , int addr){
	int		*elem;
	
	//initalization
	if (ll == NULL)
		{
		printf("ca arrive\n");
			ll =  op_prg_list_create();
			//ll =  op_prg_mem_alloc (sizeof(List));
		}
	
	//Adds the element
	elem = (int*) op_prg_mem_alloc(sizeof(int));
	*elem = addr;
	
	op_prg_list_insert(ll , elem , OPC_LISTPOS_TAIL);
}























//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//						ROUTING TABLE MANIPULATION
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//*****************************
//		ROUTING TABLE
//******************************


//Returns the timeout time associated to one entry (-1 if no entry was found)
double timeout_routing_entry (int address){
	int				i ;
	struct_routing*	entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if (entry->dest == address)
				return (entry->timeout);
		}
	
	//No corresponding entry was found
	return(-1);
}


//Returns the hops associated to an entry (-1 if no entry was found)
short hops_routing_entry(int address){
	struct_routing*		entry;	
	int					i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(-1);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if (entry->dest == address)
				return (entry->hops);
		}

	//Returns the value
	return(-1);
}


//Delete the route associated to address
void delete_route(int address){
	int				i = 0;
	struct_routing*	entry;
	char			msg[150];
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return;
	
	//For each entry
	while (i< op_prg_list_size(routing_table))
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We delete the entry (which is timeouted)
			if (entry->dest == address)
				{				
					//DEBUG
					if (DEBUG_ROUTE >= MEDIUM)
						{
							sprintf(msg,"ROUTING-TABLE : I delete the route toward %d (hops=%d), with timeout %f at %f\n", entry->dest , entry->hops , entry->timeout , op_sim_time());
							vsr_node(msg);
						}

					op_prg_list_remove ( routing_table , i);
					free(entry);
					
					return;
				}
			i++;
		}

}

//Delete all entries in routing table that overcome the timeout
void delete_timeout_in_routing_table (int useless_var , int coda){
	int				i;
	struct_routing*	entry;
	char			msg[150];
	double			older_entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return;
	
	//For each entry
	older_entry = -1;
	for(i = op_prg_list_size(routing_table) - 1 ; i >=0 ; i--)
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout <= op_sim_time())
				{		
					//DEBUG
					if (DEBUG_ROUTE >= MEDIUM)
						{
							sprintf(msg,"ROUTING-TABLE : I delete the route toward %d (hops=%d), with timeout %f at %f\n", entry->dest , entry->hops , entry->timeout , op_sim_time());
							vsr_node(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( routing_table , i);
					free(entry);
				}
			//Older entry
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;
					
		}
	
	//Next Verification
	if (older_entry != -1)
		op_intrpt_schedule_call(older_entry , 0 , delete_timeout_in_routing_table , i);
}


//Verify that a route for a given destination exists or not
/*Boolean	route_for_dest_exists(List* route , int dest){
	int				i = 0;
	struct_routing*	entry;

	//Delete timeouts
	if (op_prg_list_size(routing_table) == 0)
		return(OPC_FALSE);
	
	//Search this entry
	for(i=0; i < op_prg_list_size(routing_table) ; i++)
		{
			entry = op_prg_list_access (routing_table , i);
			if ((dest == entry->dest) && (are_list_equal(route , entry->route)))
				return(OPC_TRUE);
		}

	//Not found
	return(OPC_FALSE);
}
*/

//Adds an entry in the routing table :
void add_routing_entry (List* route, int dest , short hops){
	int				i = 0;
	struct_routing*	entry;
	char			msg[350];
	
	//It exists ?
//	if (route_for_dest_exists(route , dest))
//		return;
	
	//Delete timeouts
	if (op_prg_list_size(routing_table) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_ROUTING_TABLE , 0 , delete_timeout_in_routing_table , i);
		
	
	//We can have several routes per destination 
	//Memory allocation
	entry = (struct_routing*) op_prg_mem_alloc (sizeof(struct_routing));
			
	//Info
	entry->dest			= dest;
	entry->hops			= hops;
	entry->route		= route;
	entry->timeout 		= op_sim_time() + TIMEOUT_ROUTING_TABLE;
	
	//DEBUG
	if (DEBUG_ROUTE >= MEDIUM)
		{
			sprintf(msg,"ROUTING-TABLE : I add the route toward %d (hops=%d), at %f\n", entry->dest , entry->hops , op_sim_time());
			vsr_node(msg);
		}
	
	//I add it in the list
	op_prg_list_insert( routing_table, entry, OPC_LISTPOS_TAIL);	
}


//*****************************
//	ROUTE <-> PK CONVERSION
//******************************

List* inverse_route(List* route_src){
	List*	route_dest;
	int*	elem_src;
	int*	elem_dest;
	int		i;
	
	//Initialization
	route_dest = op_prg_list_create();
	//route_dest = op_prg_mem_alloc (sizeof(List));
	
	//Copy in inversing the route
	for(i=0; i < op_prg_list_size(route_src) ; i++)
		{
			//Takes the src element
			elem_src = (int*) op_prg_list_access(route_src , i);
			
			//Copy it (with memory allocation)
			elem_dest = (int*) op_prg_mem_alloc (sizeof(int));
			*elem_dest = *elem_src;
			
			//Insert it in head of the list -> List inversion
			op_prg_list_insert(route_dest , elem_dest , OPC_LISTPOS_HEAD);
		}
	
	//Result
	return(route_dest);
}

//Create a list of clusters (a route) with the route contained in a packet
List* create_route_from_pk(Packet* pkptr){
	List*	route;
	int		i;
	int		*addr_cluster;
	char	field_name[20];
	
	//List Initialization
	route = op_prg_list_create();
	//route = op_prg_mem_alloc (sizeof(List));
	
	//For each cluster in the route
	i = 1;
	sprintf(field_name , "CLUSTER_%d", i);
	while ((i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK) && (op_pk_nfd_is_set(pkptr , field_name)))
		{
			//Get the info from the packet
			addr_cluster = (int*) op_prg_mem_alloc (sizeof(int));
			op_pk_nfd_get(pkptr , field_name , addr_cluster);
			
			//Insert at the end of the list
			op_prg_list_insert(route , addr_cluster , OPC_LISTPOS_TAIL);
			
			//Next Cluster field
			i++;
			sprintf(field_name , "CLUSTER_%d", i);
		}
	
	//Returns the result
	return(route);
}

//Fill a packet with the route of clusters contained in "route"
void fill_pk_with_route(Packet* pk_src , List* route){
	int		*addr;
	int		i;
	char	field_name[20];
	
	//Size Verification
	if (op_prg_list_size(route) > MAX_CLUSTER_FIELDS_IN_RREQ_PK)
		op_sim_end("We don't have enough place in the pk","to place all our cluster-route","Please increase MAX_CLUSTER_FIELDS_IN_RREQ_PK","");
	
	//Fills the route of clusters of pk_src with the clusters present in the route
	for(i=0 ; i < op_prg_list_size(route) ; i++)
		{
			addr = (int*) op_prg_list_access(route , i);
			sprintf(field_name , "CLUSTER_%d", i+1);
			op_pk_nfd_set(pk_src , field_name , *addr);
		}
	
	//Empty the remaining fields
	for(i = op_prg_list_size(route) ; i <=  MAX_CLUSTER_FIELDS_IN_RREQ_PK-1; i++)
		{
			sprintf(field_name , "CLUSTER_%d", i+1);
			if (op_pk_nfd_is_set(pk_src , field_name))
				op_pk_nfd_strip(pk_src , field_name);
		}
}


//*******************************
//	 ROUTING: SEARCHES ROUTES
//*******************************


//Next hop toward one node in the neighbourhood_table
int get_next_hop_from_neigh_table_to(int dest , List* exceptions){
	neigh_cell	*ptr;
	
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			//If this node is a 1-neighbor and is 1-neighbor of dest, It is a candidate !
			if ((ptr->hops == 1) && (ptr->bidirect) && (is_in_list(ptr->neighbors, dest)) && (!is_in_list(exceptions , ptr->address) ))
				return(ptr->address);
			ptr = ptr->next;
		}
	return(-1);
}


//Next hop toward an entry in the routing table
int get_relay_to_node_from_routing_table(int address , Packet* pk_src , List* exceptions){
	struct_routing*		entry;
	struct_routing*		best_entry;
	int					i ;
	int					next_hop = -1;
	char				msg[350];

//Searches if the destination exists in the routing table (I take the more recent route if several exist)
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search the best existing entry 
	best_entry = NULL;
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if ((entry->dest == address) && ( (best_entry == NULL) || (best_entry->timeout < entry->timeout) ))
				{
					if (DEBUG_ROUTE >= MEDIUM)
						{
							sprintf(msg , "DATA-ROUTE : %s\n", print_route(entry->route));
							vsr_data(msg);
						}					
					
					next_hop = get_next_hop_from_cluster_route(entry->route , OPC_FALSE , exceptions);
					if (next_hop != -1)
						best_entry = entry;
				}				
		}
	
//Sets the route of clusters in the data pk
	if (best_entry != NULL)
		fill_pk_with_route(pk_src , best_entry->route);
	
//Result
	return(next_hop);
}

//Returns the cluster associated to address in the neighbourhood table (-1 if not found)
int get_cluster_associated(int address){
	neigh_cell* ptr;
	
	ptr = neighbour_table;
	while (ptr != NULL)
		{
			if ((ptr->address == address) && (ptr->bidirect))
				return (ptr->clusterhead);
			
			ptr = ptr->next;		
		}	
	return(-1);
}


//Next hop toward one of our k_cds-neighbor
int get_relay_to_neighbour_node(int addr , List* exceptions){
	neigh_cell *ptr;
	
	//Search the relay fields for this entry (this method  is prefered, because it is the most recent information)
	ptr= neighbour_table;
	while ( ptr != NULL)
		{
			//The entry for the dest
			if ((ptr->address == addr) && (ptr->bidirect) && (!is_in_list(exceptions , ptr->relay)) )
			return (ptr->relay);
			
			//next Cell
			ptr = (neigh_cell *)ptr->next;
		 }
	
	//Search if one of its 1-neighbors if known ! 
	ptr= neighbour_table;
	while ( ptr != NULL)
		{
		
			//1-Neighbor of one known node
			if ((ptr->bidirect) && (is_in_list(ptr->neighbors , addr)) && (!is_in_list(exceptions , ptr->relay)) )
				return (ptr->relay);
			
			//next Cell
			ptr = (neigh_cell *)ptr->next;
		 }
	
	return (-1);
}










//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//				ROUTING FROM RELAY FIELDS DIRECTLY IN PACKETS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Returns the gateway toward the cluster add_cluster (-1, if no relay was found)
int search_next_hop_for_cluster(int addr_cluster , int dest , List* exceptions){
	neigh_cell*		ptr;
	int				best_relay;
	short			best_relay_prio;
	Boolean			is_gw_in_different_cluster;
	Boolean			is_cluster_neighbor;
	Boolean			is_gateway_in_my_cluster;
	char			msg[350];
	Boolean			e1 , e2 , e3 , e4 , e5 , e6;
	
	//Default value
	best_relay = -1;
	best_relay_prio = MAX_NETWORK_RADIUS;
	
	//Search if an entry in the neighborhood table has the corresponding clusterhead
	ptr = neighbour_table;
	while(ptr != NULL)
		{
			//Is this node gateway for addr_cluster, 1-neighbor, but not in the same cluster ? 
			is_gw_in_different_cluster 	= (ptr->hops == 1) && (ptr->bidirect) && (cluster_present_in_gw_list(addr_cluster , ptr->gw_list)) && (ptr->clusterhead != my_clusterhead->address);// && (ptr->clusterhead != 0) && (ptr->clusterhead != -1);
			//Is this node in addr_cluster, and 1-neighbor (not in my cluster) ?
			is_cluster_neighbor 		= (ptr->hops == 1) && (ptr->bidirect) && (ptr->clusterhead == addr_cluster) && (ptr->clusterhead != my_clusterhead->address);// && (ptr->clusterhead != 0) && (ptr->clusterhead != -1);
			//Is this node in my cluster and gateway for addr_cluster ?		
			is_gateway_in_my_cluster 	= (cluster_present_in_gw_list(addr_cluster , ptr->gw_list)) && (ptr->bidirect) && (ptr->clusterhead == my_clusterhead->address);
			
			
			if (DEBUG_ROUTE >= HIGH)
				{
					sprintf(msg, "		%d %d %d (prio %d, best %d)\n", is_gw_in_different_cluster , is_cluster_neighbor , is_gateway_in_my_cluster , best_relay_prio , best_relay);
					vsr_data(msg);
				}			
			
			
			//Takes the best candidate (accordint to several criteria)
			if (!is_in_list(exceptions , ptr->relay))
				{
					//Priority according to the number of hops (one node of my cluster, gw from the searched cluster)
					e1 = is_gateway_in_my_cluster && ((best_relay == -1) || (best_relay_prio > ptr->hops + 4));
					if (e1)
						{
							best_relay 		= ptr->relay;
							best_relay_prio	= ptr->hops + 4;							
						}
					//Prio 4  (one node not in my cluster, but gw for the searched cluster)
					e2 = is_gw_in_different_cluster && ((best_relay == -1) || (best_relay_prio > 4));
					if (e2)
						{
							best_relay 		= ptr->relay;
							best_relay_prio	= 4;
						}
					//Prio 3  (one node of my cluster, 1 hop nearer from my CH)
					e3 = (ptr->hops == 1) && (ptr->bidirect) && (ptr->clusterhead == addr_cluster) && (ptr->clusterhead == my_clusterhead->address) && (ptr->clusterhead_hops < my_clusterhead->hops) && ((best_relay == -1) || (best_relay_prio > 3));
					if (e3)
						{
							best_relay 		= ptr->relay;
							best_relay_prio	= 3;
						}
					//Prio 2  (one node not in my cluster, but in the searched cluster)
					e4 = is_cluster_neighbor && ((best_relay == -1) || (best_relay_prio > 2));
					if (e4)
						{
							best_relay 		= ptr->relay;
							best_relay_prio	= 2;
						}
					//Prio 1  (the CH of the searched cluster)
					e5 = (ptr->address == addr_cluster) && (ptr->bidirect) && ((best_relay == -1) || (best_relay_prio > 1));
					if (e5)
						{
							best_relay 		= ptr->relay;
							best_relay_prio	= 1;
						}
					//The destination is in the neighborhood table ! (Max Priority)
					e6 = (ptr->address == dest) && (ptr->bidirect);
					if  (e6)
						{
							best_relay 		= ptr->relay;
							best_relay_prio = 0;
						}
					if (DEBUG_ROUTE >= HIGH)
						{
							sprintf(msg, "			->%d %d %d %d %d %d\n",e1 , e2 , e3 , e4 , e5 , e6);
							vsr_data(msg);
						}			
				}			
			
			
			//Next neighbourhood_table member
			ptr = ptr->next;			
		}

	if (DEBUG_ROUTE >= HIGH)
		{
			print_neigh_table();	
			sprintf(msg , "DATA : %d chooses %d (prio %d) to relay to cluster %d\n",my_address , best_relay , best_relay_prio ,  addr_cluster);
			vsr_data(msg);
		}
	
	//No entry was found
	return(best_relay);
}







//*********************************************
//	NEW GENERATION OF ROUTE MANIPULATION
//*********************************************


//Add the cluster "cluster_to_add" after the cluster "cluster_before", in the route contained in the pk
void add_in_cluster_route_after(List* route , int cluster_before, int cluster_to_add){
	int		i;
	int		*addr_cluster;
	int		*elem;
	char	msg[200];
	List*	old_route;
	
	old_route = op_prg_list_create();
	//old_route = op_prg_mem_alloc (sizeof(List));
	op_prg_list_elems_copy(route , old_route);
	
	
	for(i=0; i < op_prg_list_size(route) ; i++)
		{
			addr_cluster = (int*) op_prg_list_access (route , i);
			
			//Adds the element
			if (*addr_cluster == cluster_before)
				{
					//Creation + Insertion
					elem = (int*) op_prg_mem_alloc (sizeof(int));
					*elem = cluster_to_add;
					op_prg_list_insert(route , elem , i+1);
									
					//End !
					if (DEBUG_ROUTE >= HIGH)
						{
							sprintf(msg , "I add %d after the cluster %d\n", cluster_to_add , cluster_before);
							vsr_debug(msg);
							printf(msg);
			
							sprintf(msg , "I change the route from %s to %s at %f\n", print_route(old_route) , print_route(route) , op_sim_time());
							vsr_debug(msg);
							
							printf("%d changed the route from %s to %s \n", my_address , print_route(old_route) , print_route (route));
						}
					
					//End
					while(op_prg_list_size(old_route)>0)
						{
							addr_cluster = op_prg_list_remove(old_route , 0);
							op_prg_mem_free(addr_cluster);
						}
					op_prg_mem_free(old_route);
					return;
				}
		}
	
	if (DEBUG_ROUTE >= HIGH)
		{
			sprintf(msg, "%d didn't find the cluster %d in the route %s at %f \n", my_address , cluster_before , print_route(route) , op_sim_time());
			printf(msg);
			vsr_debug(msg);
			vsr_node(msg);
		}
}

//Delete all cluster addresses present in the route contained in pkptr, between cluster1 and cluster2
void delete_in_cluster_route_between(List* route , int cluster1 , int cluster2){
	int		i;
	int		*addr_cluster;
	char	msg[200];
	List*	old_route;
	
	//For debug
	old_route = op_prg_list_create();
	//old_route = op_prg_mem_alloc (sizeof(List));
	op_prg_list_elems_copy(route , old_route);
	
	for(i=0; i < op_prg_list_size(route) ; i++)
		{
			addr_cluster = (int*) op_prg_list_access (route , i);
			
			//Cluster1 found
			if (*addr_cluster == cluster1)
				{
					while (op_prg_list_size(route) > i+1)
						{
							addr_cluster = (int*) op_prg_list_access (route , i+1);
							
							//If cluster 2 found, we have finished
							if (*addr_cluster == cluster2)
								{
									if (DEBUG_ROUTE >= MEDIUM)
										{
											sprintf(msg , "%d deletes all clusters between %d and %d \n", my_address , cluster1 , cluster2);
											vsr_debug(msg);
			
											sprintf(msg, "I change the route from %s to %s at %f\n", print_route(old_route) , print_route(route), op_sim_time());
											vsr_debug(msg);
											
											printf("%d changed the route from %s to %s\n", my_address , print_route(old_route), print_route(route));
										}
									
									//Memory Free
									while(op_prg_list_size(old_route)>0)
										{
											addr_cluster = op_prg_list_remove(old_route , 0);
											op_prg_mem_free(addr_cluster);
										}
									op_prg_mem_free(old_route);
									return;
								}
							//We remove all elements after cluster1 while we didn't find cluster2
							else
								{
									op_prg_list_remove(route , i+1);
									free(addr_cluster);
								}
						}
				}
		}
	
	if (DEBUG_ROUTE >= MEDIUM)
		{
			sprintf(msg, "%d didn't find the cluster %d or cluster %d in the route %s at %f \n", my_address , cluster1 , cluster2 , print_route(route) , op_sim_time());
			printf(msg);
			vsr_debug(msg);
			vsr_node(msg);
		}

}

//Returns the next hop (The list of clusters is given with the format : "dest|...|src")
int get_next_hop_from_cluster_route(List* route , Boolean update , List* exceptions){
	//Control
	int		i;
	char	msg[150];
	//Packet info
	int		*addr_cluster;
	int		next_hop;
	int		next_hop_cluster;

	
	//Empty List
	if (op_prg_list_size(route) == 0)
		return(-1);

	//List of intermediary Clusters
	for (i=0; i < op_prg_list_size(route) ; i++)
		{
			addr_cluster = (int*) op_prg_list_access(route, i);

			//My cluster appears in the route 
			//-> If I am the CH, I drop the pk
			//->else I will forward the pk to my CH (perhaps it answered to a RREP for the destination without CH because it has D in its neighbour_table)
			if ((addr_cluster == NULL) || ((*addr_cluster == my_clusterhead->address) && (my_clusterhead->address == my_address)))
				return(-1);
			
			//Is this cluster reachable ? (dest=0 -> we don't want the destination precisely)
			next_hop = search_next_hop_for_cluster(*addr_cluster , 0 , exceptions);
					
			//Valid Result
			if (next_hop != -1)
				{
					//We must update the route to reflect changes according to our routing decision
					if (update)
						{
						sprintf(msg, "route avant : %s\n", print_route(route));
						vsr_rreq(msg);
						
							//Delete useless fields
							if (my_clusterhead->address != get_cluster_associated(next_hop))
								delete_in_cluster_route_between(route , *addr_cluster , my_clusterhead->address);
						
						sprintf(msg, "route inter : %s\n", print_route(route));
						vsr_rreq(msg);
					
							//Must the cluster of next hop be added in the cluster list ?
							next_hop_cluster = get_cluster_associated(next_hop);
							if ((next_hop_cluster != my_clusterhead->address ) && (next_hop_cluster != *addr_cluster))
								add_in_cluster_route_after(route , *addr_cluster , next_hop_cluster);			

						sprintf(msg, "route apres : %s\n", print_route(route));
						vsr_rreq(msg);
						}
					
					if (DEBUG_ROUTE >= HIGH)
						{
							sprintf(msg, "DATA : %d chooses the next hop %d (cl %d) for the cluster %d\n", my_address , next_hop , next_hop_cluster , *addr_cluster );
							vsr_data(msg);
						}
						
					return(next_hop);
				}
			
		}
	
	//No Result
	return(-1);
}





//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                  ROUTE REPLY
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns the next hop to a destination from the neighborhood table or from the route contained in pk_src
int get_relay_from_route_to(List* route , int dest_final , List* exceptions){
	int 	next_hop;
	char	msg[1000];
	
	//Route from The Neighborhood Table
	next_hop = get_relay_to_neighbour_node(dest_final , exceptions);
			  
	//Route present in the packet
	if (next_hop == -1)
		next_hop = get_next_hop_from_cluster_route(route , OPC_FALSE , exceptions);	
	else if (DEBUG_ROUTE > LOW)
		{
			sprintf(msg, "ROUTE : to %d -> via %d from neighborhood table\n", dest_final , next_hop);
			vsr_rrep(msg);
		}
		
	
	return(next_hop);
}

//Adds a cluster in the route
void add_cluster_in_route(List* route , int address , int position){
	int*	elem;
	
	//Creates a new element
	elem = (int*) op_prg_mem_alloc(sizeof (int));
	*elem = address;
	
	//Adds it in the list
	op_prg_list_insert (route, elem , position);	
}

//Sends a route reply
void send_route_reply(Packet* pk_src , int addr_src , int addr_searched , int stat_id){
	//Pk
	Packet* 	pk_dest;	
	//Control
	char 		msg[200];
	//Route
	List*		route;
	int*		addr_cluster;
	int			destination_cluster;
	int			next_hop;
	//Lists of forbidden relay
	List		*exceptions;
	
	//Null Forbidden List
	exceptions = op_prg_list_create();
	
	//send route_reply to the AP	
	pk_dest = op_pk_create_fmt("vsr_pk_route_reply");
	
	//I act as proxy, the apparent "source" is the searched node
	op_pk_nfd_set(pk_dest,"SRC",			my_address);
	op_pk_nfd_set(pk_dest,"SRC_INIT",		addr_searched);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",		addr_src);
	op_pk_nfd_set(pk_dest,"PK_ID",			current_id++);
	op_pk_nfd_set(pk_dest,"STAT_ID",		stat_id);
	op_pk_nfd_set(pk_dest,"TTL",			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",	RREP_PK_TYPE);
	
	
	//Extracts the route
	route = create_route_from_pk(pk_src);
	
	//Extracts the last cluster of the route (If this RREQ comes from a dominatee, the route is empty -> condition else)
	if (op_prg_list_size(route) != 0)
		addr_cluster = (int*) op_prg_list_access (route , OPC_LISTPOS_TAIL);
	else
		addr_cluster = NULL;
	
	//I am already in this route ?
	if ((addr_cluster == NULL) || (*addr_cluster != my_clusterhead->address))
		add_cluster_in_route(route, my_clusterhead->address , OPC_LISTPOS_TAIL);

	//Is the cluster of the destination in this route ?
	destination_cluster = get_cluster_associated(addr_searched);
	if ((my_clusterhead->address != destination_cluster) && (destination_cluster != 0) && (destination_cluster != -1))
		add_cluster_in_route(route , destination_cluster , OPC_LISTPOS_TAIL);
	
	// we search the address of the father
	next_hop = get_relay_from_route_to(route , addr_src , exceptions);	
	op_pk_nfd_set(pk_dest , "DEST", next_hop);
	
	//Updates the route
	fill_pk_with_route(pk_dest , route);
	
	
	if (DEBUG_ROUTE >= LOW)
		{
			sprintf(msg,"RREP : %d sends a RREP for %d to %d toward %d\n" , my_address , addr_searched , next_hop , addr_src );
			vsr_rrep(msg);	
			sprintf(msg,"		route = %s\n",print_route(route));
			vsr_rrep(msg);	
		}
	
	//Transmission of we have a valid route
	if (next_hop != -1)
		{
			//Transmission
			if (ACK_FOR_RREP)
				add_unicast_ack(pk_dest);
			send(pk_dest);
		}
	
	//Stats
	stats_rreq[stat_id].rreq_time_reception	= op_sim_time();
	stats_rreq[stat_id].rrep_time_emission	= op_sim_time();
	stats_rreq[stat_id].rrep_hops			= 0;
	stats_rreq[stat_id].rrep_nb_retry 		= 1;
}

//A node forwards the route reply, according to the route present in the packet
void forward_route_reply(Packet* pk_src){
	Packet	*pk_dest;
	char	msg[150];
	int		ttl;
	int		addr_src;
	int		src_init;
	int		dest;
	int		dest_final;
	List*	route;
	List*	route_data;
	//Lists of forbidden relay
	List	*exceptions;
	
	//Null Forbidden List
	exceptions = op_prg_list_create();

	//The previous hop is forbidden
	op_pk_nfd_get(pk_src, "SRC" , &addr_src);
	add_in_list(exceptions , addr_src);
	
	//Info
	op_pk_nfd_get(pk_src , "DEST_FINAL", 	&dest_final);
	op_pk_nfd_get(pk_src , "SRC_INIT", 		&src_init);
	op_pk_nfd_get(pk_src , "TTL", 			&ttl);
	
	//Extracts the route
	route = create_route_from_pk(pk_src);
	
	//we search the address of the next hop toward dest_final
	dest = get_relay_from_route_to(route , dest_final , exceptions);	

	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	
	//Updates the route	
	fill_pk_with_route(pk_dest , route);
	
	//Updates some fields	
	op_pk_nfd_set(pk_dest , "SRC", 	my_address);
	op_pk_nfd_set(pk_dest , "DEST", dest);
				
	if (DEBUG_ROUTE >= LOW)
		{
			sprintf(msg,"RREP : %d forwards to %d toward %d at %f\n", my_address , dest , dest_final , op_sim_time());
			vsr_rrep(msg);
			sprintf(msg,"		route = %s\n",print_route(route));
			vsr_rrep(msg);	
		}
	
	//We create a routing entry
	route_data = inverse_route(route);
	//add_routing_entry(create_route_from_pk(pk_dest) , src_init, MAX_NETWORK_RADIUS - ttl + 1);
		
	//TTL
	ttl--;
	op_pk_nfd_set(pk_dest ,"TTL", ttl);
	
	//Transmission
	if (dest != -1)
		{
			if (ACK_FOR_RREP)
				add_unicast_ack(pk_dest);
			send(pk_dest);
		}
}





//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   ROUTE ERRORS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//A node forwards the route error, according to the route present in the packet
void forward_route_error(Packet* pk_src){
	Packet	*pk_dest;
	char	msg[150];
	int		ttl;
	int		addr_src;
	int		src_init;
	int		dest;
	int		dest_final;
	List*	route;
//	List*	route_data;
	//Lists of forbidden relay
	List	*exceptions;
	
	//Null Forbidden List
	exceptions = op_prg_list_create();
	
	//The previous hop is forbidden
	op_pk_nfd_get(pk_src, "SRC" , &addr_src);
	add_in_list(exceptions , addr_src);	

	//Info
	op_pk_nfd_get(pk_src , "DEST_FINAL", 	&dest_final);
	op_pk_nfd_get(pk_src , "SRC_INIT", 		&src_init);
	op_pk_nfd_get(pk_src , "TTL", 			&ttl);
	
	//Extracts the route
	route = create_route_from_pk(pk_src);
	
	//we search the address of the next hop toward dest_final
	dest = get_relay_from_route_to(route , dest_final , exceptions);	

	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	
	//Updates the route	
	fill_pk_with_route(pk_dest , route);
	
	//Updates some fields	
	op_pk_nfd_set(pk_dest , "SRC", 	my_address);
	op_pk_nfd_set(pk_dest , "DEST", dest);
				
	if (DEBUG_ROUTE >= LOW)
		{
			sprintf(msg,"RERR : %d relayed to %d toward %d at %f\n", my_address , dest , dest_final , op_sim_time());
			vsr_rerr(msg);
			sprintf(msg, "	Route : %s\n", print_route(route));
			vsr_rerr(msg);
		}
	
	//We create a routing entry
	//route_data = inverse_route(route);
		
	//TTL
	ttl--;
	op_pk_nfd_set(pk_dest ,"TTL", ttl);
	
	//Transmission
	if (dest != -1)
		{
			if (ACK_FOR_RERR)
				add_unicast_ack(pk_dest);
			send(pk_dest);
		}
}


//Sends a route reply
void send_route_error(Packet* pk_src , int addr_src , int addr_dead){
	//Pk
	Packet* 	pk_dest;	
	//Control
	char 		msg[200];
	//Route
	List		*route;
	List		*route_dest;
	int			next_hop;
	//Lists of forbidden relay
	List		*exceptions;
	
	//Null Forbidden List
	exceptions = op_prg_list_create();

	//send route_reply to the AP	
	pk_dest = op_pk_create_fmt("vsr_pk_route_error");
	
	//I act as proxy, the apparent "source" is the searched node
	op_pk_nfd_set(pk_dest,"SRC",			my_address);
	op_pk_nfd_set(pk_dest,"SRC_INIT",		my_address);
	op_pk_nfd_set(pk_dest,"DEST_FINAL",		addr_src);
	op_pk_nfd_set(pk_dest,"NODE_DEAD",		addr_dead);
	op_pk_nfd_set(pk_dest,"PK_ID",			current_id++);
	op_pk_nfd_set(pk_dest,"STAT_ID",		stats_nb_rerr);
	op_pk_nfd_set(pk_dest,"TTL",			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",	RERR_PK_TYPE);
	
	
	//Extracts the route
	route = create_route_from_pk(pk_src);
	route_dest = inverse_route(route);
	
	// we search the address of the father
	next_hop = get_relay_from_route_to(route , addr_src , exceptions);	
	op_pk_nfd_set(pk_dest , "DEST", next_hop);
	
	//Updates the route
	fill_pk_with_route(pk_dest , route_dest);

	//sends it if valid (a valid next hop and a not null route of clusters (else the RERR is useless))
	if ((next_hop != -1) && (op_prg_list_size(route_dest) != 0))
		{
			if (DEBUG_ROUTE >= HIGH)
				{
					sprintf(msg,"!!!! RERR-INIT : %d sends a RERR (%d dead) to %d toward %d !!!!\n" , my_address , addr_dead , next_hop , addr_src);
					vsr_rerr(msg);	
					sprintf(msg, "	Route : %s\n", print_route(route_dest));
					vsr_rerr(msg);
				}

			//Transmission
			if (ACK_FOR_RERR)
				add_unicast_ack(pk_dest);
			send(pk_dest);
	
			//Stats
			stats_rerr[stats_nb_rerr].source		= my_address;
			stats_rerr[stats_nb_rerr].dest			= addr_src;
			stats_rerr[stats_nb_rerr].time_emission	= op_sim_time();
			stats_rerr[stats_nb_rerr].hops			= 0;
			stats_rerr[stats_nb_rerr].nb_retry 		= 1;
			stats_nb_rerr++;
			if (stats_nb_rerr == MAX_RERR_PK)
				op_sim_end("We sent too many route errors", "please increase the value of MAX_RERR_PK", "in the header block","");
		}
	else
		op_pk_destroy(pk_dest);
}








//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   ROUTE REQUESTS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//*****************************
//		ROUTE in RREQ
//*****************************


//Adds my clusterhead If it is different from the last cluster in the list
void add_my_cluster_in_cluster_relay_fields(Packet* pkptr){
	int		i;
	char	field_name[20];
	int		last_cluster = 0;
	char	msg[150];

	//Get the last Cluster in Relay Fields
	i=1;
	sprintf(field_name, "CLUSTER_1");
	while (op_pk_nfd_is_set(pkptr, field_name))
		{
			op_pk_nfd_get(pkptr, field_name , &last_cluster);
			i++;
			sprintf(field_name, "CLUSTER_%d", i);
		}
	
	//Add my cluster in relay fields if I have a different clusterhead
	if ((my_clusterhead->address != last_cluster) && (my_clusterhead->address != 0))
		{
			op_pk_nfd_set(pkptr, field_name , my_clusterhead->address);	
			if (DEBUG_ROUTE >= MEDIUM)
				{
					sprintf(msg, "I added my clusterhead (%d) in cluster list (the last cluster (no %d) was %d)\n" , my_clusterhead->address , i , last_cluster);
					vsr_rreq(msg);
				}
		}
}




//*****************************
//		RREQ BUFFER
//****************************



//delete an entry in the rreq pk buffer
int delete_entry_in_rreq_buffer(int address){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	double					older_entry=-1;
	int						value;
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return(-1);

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);			
			//We delete the entry
			if (entry->dest == address)
				{	
					value = entry->nb_retry;
					op_prg_list_remove ( rreq_pk_buffer , i);
					free(entry);
					return (value);
				}
		}
	
	return(-1);
}	

//When the simulation ends
void delete_all_in_rreq_pk_buffer(){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[150];
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return;

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			
			if (DEBUG_ROUTE >= MEDIUM)
				{
					sprintf(msg,"RREQ-BUFFER : deletes the rreq toward %d with timeout %f at %f (nb_retry=%d)\n", entry->dest , entry->timeout , op_sim_time() , entry->nb_retry);
					vsr_rreq(msg);
				}
			op_prg_list_remove ( rreq_pk_buffer , i);
			free(entry);
		}
}

//Timeout entries in Route Requests pk buffer
void send_timeout_in_rreq_pk_buffer(int* arg , int code){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[150];
	double					older_entry=-1;
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return;

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			
			//We delete the entry
			if (entry->timeout <= op_sim_time())
				{	
					//If we send a new RREQ, are we over our quota of RREQ ? 
				   	if (entry->nb_retry + 1 <= MAX_NB_RREQ_RETRY)
						{
							//DEBUG
							if (DEBUG_ROUTE >= MEDIUM)
								{
									sprintf(msg,"RREQ-BUFFER : %d retransmits the rreq toward %d with timeout %f at %f\n", my_address , entry->dest , entry->timeout , op_sim_time());
									vsr_rreq(msg);
								}

							//Sends a new RREQ
							send_rreq_pk(entry->dest , entry->stat_id);
							
							//Info update
							entry->nb_retry ++;
							
							//We have a bigger timeout in order to have the entry if we receive a RREP with this new retry (anywhere, we won't retransmit the packet)
							//if (entry->nb_retry == MAX_NB_RREQ_RETRY)
							//	entry->timeout = op_sim_time() + TIMEOUT_RREQ_PK_BUFFER*10;
							//else
								{
									entry->timeout = op_sim_time() + TIMEOUT_RREQ_PK_BUFFER*entry->nb_retry;
		
									//The older entry
									if ((entry->timeout < older_entry) || (older_entry == -1))						
										older_entry = entry->timeout;
								}
							
						}
					//deletes the corresponding entry
					else					
						{
							if (DEBUG_ROUTE >= MEDIUM)
								{
									sprintf(msg,"RREQ-BUFFER : deletes the rreq toward %d with timeout %f at %f (nb_retry=%d)\n", entry->dest , entry->timeout , op_sim_time() , entry->nb_retry);
									vsr_rreq(msg);
								}
							op_prg_list_remove ( rreq_pk_buffer , i);
							free(entry);
						}
				}
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;

		}
	
	if (older_entry!=-1)
		op_intrpt_schedule_call(older_entry , ROUTE_REQUEST_RETRY_CODE , send_timeout_in_rreq_pk_buffer , i);
}


//Is the entry already in the table ?
Boolean is_dest_in_rreq_pk_buffer(int dest){
	struct_rreq_pk_buffer*	entry;
	int						i = 1;	
	
	if (op_prg_list_size(rreq_pk_buffer) == 0)
		return(OPC_FALSE);

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			if (entry->dest == dest)
				return(OPC_TRUE);
		}
	
	//Not found
	return(OPC_FALSE);
}


//Add the data packet in the buffered list
void add_in_rreq_pk_buffer(int dest , int stat_id){
	struct_rreq_pk_buffer*	entry;
	int						i = 1;
	
	
	if (op_prg_list_size(rreq_pk_buffer) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RREQ_PK_BUFFER , ROUTE_REQUEST_RETRY_CODE, send_timeout_in_rreq_pk_buffer , &i);
	
	//Memory allocation
	entry = (struct_rreq_pk_buffer*) op_prg_mem_alloc (sizeof(struct_rreq_pk_buffer));
			
	//Info
	entry->dest		= dest;
	entry->timeout	= op_sim_time() + TIMEOUT_RREQ_PK_BUFFER;
	entry->nb_retry	= 0;
	entry->stat_id	= stat_id;
	
	//I add it in the list
	op_prg_list_insert(rreq_pk_buffer, entry , OPC_LISTPOS_TAIL);	
}




//*****************************
//		RREQ PACKETS
//*****************************


//Is the destination in my neighborhood table ? I must act as proxy for the RREQ
Boolean must_rreq_proxy(int addr){
	neigh_cell *ptr;
	
	//If the node 
	ptr= neighbour_table;
	while ( ptr != NULL)
		{
			if ((ptr->address == addr) && (ptr->bidirect))// && (ptr->clusterhead != -1) && (ptr->clusterhead != 0))
				return (OPC_TRUE);
			else
				ptr = (neigh_cell *)ptr->next;
		 }

	return (OPC_FALSE);
}


//Sends a RREQ
void send_route_request(int addr){	
	char	msg[150];
	
	//protection against arrays overflows
	if (stats_nb_rreq >= MAX_RREQ_PK)
		op_sim_end("We have too many RREQ to store all statistics","please increase the value MAX_RREQ_PK","in the header block of the vsr_routing process","");
	
	//Send a rreq if necessary
	if (!is_dest_in_rreq_pk_buffer(addr))
		{
			add_in_rreq_pk_buffer(addr , stats_nb_rreq);
			send_rreq_pk(addr , stats_nb_rreq++);
	
			if (DEBUG_ROUTE >= MEDIUM)
				{
					sprintf(msg,"\n\n !!!  RREQ : %d sends a RREQ toward %d via the backbone at %f  !!!\n", my_address , addr , op_sim_time());
					vsr_rreq(msg);
				}
		}
	else if (DEBUG_ROUTE >= MEDIUM)
		{
			sprintf(msg,"\n\n !!!  RREQ : %d has already sent a RREQ toward %d via the backbone (now : %f)  !!!\n", my_address , addr , op_sim_time());
			vsr_rreq(msg);
		}
}


//Sends the RREQ Packet
void send_rreq_pk(int addr_searched , int stat_id){
	Packet* pk_dest;
	char 	msg[200];
	char	field_name[15];
	int		i;
	int		dest;

	//dest
	if (my_cds->state == DOMINATOR)
		dest = ADDR_MULTICAST_BACKBONE;
	else
		dest = my_cds->relay;
	
	// we create and send the route-request
	pk_dest = op_pk_create_fmt("vsr_pk_route_request");
			
	op_pk_nfd_set(pk_dest,"SRC_INIT",		my_address);
	op_pk_nfd_set(pk_dest,"SRC",			my_address);
	
	op_pk_nfd_set(pk_dest,"DEST",			dest);	
	op_pk_nfd_set(pk_dest,"NODE_SEARCHED",	addr_searched);
	
	op_pk_nfd_set(pk_dest,"PK_ID",			current_id++);
	op_pk_nfd_set(pk_dest,"STAT_ID",		stat_id);
	op_pk_nfd_set(pk_dest,"TTL",			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",	RREQ_PK_TYPE);
	
	//Relay fields
	for(i=1 ; i<= MAX_CLUSTER_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name , "CLUSTER_%d", i);
			op_pk_nfd_strip(pk_dest , field_name);
		}
	
	//My Clusterhead is the first clusterhead
	if (my_cds->state == DOMINATOR)
		op_pk_nfd_set(pk_dest , "CLUSTER_1" , my_clusterhead->address);
	
	//Stats
	stats_rreq [stat_id].source 				= my_address;
	stats_rreq [stat_id].dest 					= addr_searched;
	stats_rreq [stat_id].rreq_nb_retry ++;
	if (stats_rreq [stat_id].rrep_time_reception == 0)
		stats_rreq [stat_id].rreq_time_emission 	= op_sim_time();
	
	if ((my_cds->state == DOMINATEE) || (my_clusterhead->address != 0))
		{	
			//Debug
			if (DEBUG_ROUTE >= MEDIUM)
				{
					sprintf(msg,"\n\n !!!  RREQ : %d sends a RREQ toward %d via the backbone (dest = %d) at %f  !!!\n", my_address , addr_searched , dest , op_sim_time());
					vsr_rreq(msg);
				}
	
			//Transmission
			send(pk_dest);	
		}
	else if (DEBUG_ROUTE >= MEDIUM)
		{
			sprintf(msg,"\n\n !!!  RREQ : %d don't try to send this RREQ to %d, it has a null clusterhead %f  !!!\n", my_address , addr_searched , op_sim_time());
			vsr_rreq(msg);
		}
}


//relay a route_request to all sons and father
//void relay_route_request(Packet* pk,int addr_son){
void forward_route_request(Packet* pk_src){
	Packet	*pk_dest;
	char 	msg[200];
	int		ttl;
	//To gather the last cluster visited
	int		last_cluster = 0;
	List*	route;
	
	//Get some info
	op_pk_nfd_get(pk_src, "TTL", 		&ttl);
	
	//Pk to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest, "SRC",		my_address);
	op_pk_nfd_set(pk_dest, "TTL", 		--ttl);

	if (my_cds->state == DOMINATOR)
		{
			add_my_cluster_in_cluster_relay_fields(pk_dest);
			op_pk_nfd_set(pk_dest, "DEST", ADDR_MULTICAST_BACKBONE);
		}
	else
		op_pk_nfd_set(pk_dest, "DEST", my_cds->relay);

	//Debug
	if(DEBUG_ROUTE>LOW)
		{
			route = create_route_from_pk(pk_dest);	
			sprintf(msg,"RREQ : %d sent to backbone (route : %s)\n" , my_address , print_route(route));
			vsr_rreq(msg);
		}

	//Transmission
	send_delayed(pk_dest , op_dist_uniform(0.005));	
}













//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								Acknowledgements
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//This packet must be further acknowledged
void add_unicast_ack(Packet* pkptr){
	ack_couple*		couple;
	int				pk_id;
	int				dest;
	
	//If the list is empty, we must schedule the must verification of timeouts in ack_table (else it is already scheduled)
	if (op_prg_list_size (ack_table) == 0)
		op_intrpt_schedule_call (op_sim_time() + TIMEOUT_UNICAST_ACK , UNICAST_RETRANSMISSIONS_CODE , send_timeouted_in_ack_table , -1);
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (ack_couple*) op_prg_mem_alloc ( sizeof (ack_couple));
	
	op_pk_nfd_get(pkptr, "PK_ID",	&pk_id);
	op_pk_nfd_get(pkptr, "DEST",	&dest);
	
	//Info
	couple->dest		= dest;
	couple->pk_id		= pk_id;
	couple->nb_retry	= 0;
	couple->nb_repairs	= 0;
	couple->timeout 	= op_sim_time() + TIMEOUT_UNICAST_ACK ;
	couple->pkptr		= op_pk_copy(pkptr);
	
	couple->exceptions	= op_prg_list_create();
	
	//Insert it
	op_prg_list_insert( ack_table , couple , OPC_LISTPOS_TAIL);	
}

//This packet has been acknowledged
void delete_unicast_ack(int dest , int pk_id){
	ack_couple*		couple;
	char			msg[200];
	int				i;
	//Info from packet for debug purpose
	int				pk_type , dest_final;
	int				nb_entry_del = 0;
		
	//If the list is empty -> I exit !
	if (op_prg_list_size(ack_table)==0)
		{
			if (DEBUG_ACK >= MEDIUM)
				{
					sprintf(msg, "ACKS : the entry corresponding to the pk_id %d to destination %d was not found at %f\n", pk_id , dest , op_sim_time());
					vsr_ack (msg);
				}
			return ;
		}
	
	//For each entry
	for (i = op_prg_list_size(ack_table)-1 ; i >=0 ; i--)
		{
			//gets the entry
			couple = (ack_couple*) op_prg_list_access (ack_table, i);
			
			if ((couple->dest == dest) && (couple->pk_id == pk_id))
				{
					if (DEBUG_ACK >= MEDIUM)
						{
							op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
							op_pk_nfd_get(couple->pkptr, "DEST_FINAL", 	&dest_final);
						}
					op_prg_list_remove(ack_table, i);
					free(couple);
					nb_entry_del++;
				}
		}
	
	if (DEBUG_ACK >= LOW)
		{
			sprintf(msg, "ACKS : %d finds %d entries (with pk_id %d to destination %d) at %f\n", my_address , nb_entry_del , pk_id , dest , op_sim_time());
			vsr_ack (msg);
			/*if (pk_type == DATA_PK_TYPE)
				vsr_data (msg);
			else if (pk_type == RREP_PK_TYPE)
				vsr_rrep(msg);*/
		}
	
}

//Sends an unicast ack
void acknowledges_unicast_packet(int address , int pk_id){
	char		msg[150];
	Packet*		pkptr;
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("vsr_pk_ack");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SRC" ,			my_address);
	op_pk_nfd_set (pkptr, "SRC_INIT" ,		my_address);
	op_pk_nfd_set (pkptr, "DEST" ,			address);
	op_pk_nfd_set (pkptr, "TTL" ,			1);
	op_pk_nfd_set (pkptr, "OPTION_TYPE" ,	ACK_APP_PK_TYPE);
	op_pk_nfd_set (pkptr, "PK_ID" ,			pk_id);

	//Sends it
	send_delayed(pkptr , op_dist_uniform(0.005));
	
	if (DEBUG_ACK >= HIGH)
		{
			sprintf(msg,"ACKS : %d sends an active ack to %d (for pk-id %d) at %f\n", my_address , address , pk_id , op_sim_time());
			vsr_ack(msg);
		}
}



//retransmissions of all not acknowledged entries
void send_timeouted_in_ack_table(int* arg, int code){
	ack_couple*		couple;
	//Control
	char			msg [400];
	int				i;
	double			older_entry;
	Boolean			must_be_dropped;
	//Random delay before transmitting
	double			delay;
	//Info for/from the packet
	int				pk_type;
	int				pk_id;
	int				stat_id;
	int				address_final;
	int				address_init;
	int				nb_repairs;
		
	
	//Older entry variable contains the time for which we must schedule an interuption
	older_entry = -1;
	//If the ack table is empty, we don't treat it ....
	if (op_prg_list_size(ack_table)!=0)
		{
			//For each entry
			for (i=op_prg_list_size(ack_table)-1 ; i>=0 ; i--)
				{
					//gets the entry
					couple = (ack_couple*) op_prg_list_access (ack_table, i);

					//Get packet type
					op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
					op_pk_nfd_get(couple->pkptr, "PK_ID", 		&pk_id);
					op_pk_nfd_get(couple->pkptr, "DEST_FINAL",	&address_final);
					op_pk_nfd_get(couple->pkptr, "SRC_INIT",	&address_init);
					op_pk_nfd_get(couple->pkptr, "DEST",		&(couple->dest));
			
					
					//Verifies each entry
					if (couple->timeout <= op_sim_time())
						{
							//Test for max nb retransmissions
							if (couple->nb_retry >= MAX_NB_RETRIES_UNICAST_ACKS)
								{
									//Get Info
									if (pk_type == DATA_PK_TYPE)
										op_pk_nfd_get(couple->pkptr, "NB_REPAIRS", &nb_repairs);
									else
										nb_repairs = MAX_NB_REPAIRS_IN_DATA_PK;
									
									
									//initiates a local repair 
									//the cell is removed: anyway, we add in retransmissions table when we send the repaired data pk
									must_be_dropped = OPC_TRUE;
									if ((nb_repairs < MAX_NB_REPAIRS_IN_DATA_PK ) && (couple->nb_repairs < MAX_NB_REPAIRS_PER_NODE))
										{
											couple->nb_retry 	= 0;
											couple->nb_repairs++;
											add_in_list(couple->exceptions , couple->dest);
											must_be_dropped = !initiate_local_repair_for_data_pk(couple->pkptr , couple->exceptions);
												
										}
									//Remove this cell in the retransmission list	
									if (must_be_dropped)
										{
											//debug
											if ((pk_type == DATA_PK_TYPE) && (DEBUG_DATA>0))
												{
													sprintf(msg, "DROP : %d drops the packet for %d after %d local repairs at %f (pk type%d)\n", my_address , couple->dest , couple->nb_repairs , op_sim_time() , pk_type);
													vsr_data(msg);
												}
											
											//sends a route error
											if (pk_type == DATA_PK_TYPE)
												send_route_error(couple->pkptr , address_init , address_final);
											
											//Remote it from the list of pk to be acked
											op_prg_list_remove (ack_table , i);
											free(couple);
										}

								}
							//if (couple->nb_retry < MAX_NB_RETRIES_UNICAST_ACKS)
							else if (couple->timeout <= op_sim_time())
								{
									op_pk_nfd_get(couple->pkptr, "STAT_ID",&stat_id);
								
									//retransmission
									couple->timeout = op_sim_time() + TIMEOUT_UNICAST_ACK;
									couple->nb_retry++;							
									delay 			= op_dist_uniform(0.005);
									retransmit_delayed (op_pk_copy(couple->pkptr) , delay);			
										
									//Stats of nb of retransmissions
									switch (pk_type)
										{
											case DATA_PK_TYPE :
												stats_data_pk [stat_id].nb_retry++;
												if (DEBUG_DATA >= MEDIUM)
													{
														sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry , op_sim_time()+delay);
														vsr_data (msg);
													}
											break;
											case RREP_PK_TYPE :
												stats_rreq [stat_id].rrep_nb_retry++;
												if (DEBUG_ROUTE >= MEDIUM)
													{
														sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry , op_sim_time()+delay);
														vsr_rrep (msg);
													}
											break;
											case RERR_PK_TYPE :
												stats_rerr [stat_id].nb_retry++;
												if (DEBUG_ROUTE >= MEDIUM)
													{
														sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry , op_sim_time()+delay);
														vsr_rerr (msg);
													}
											break;
											default:
												sprintf(msg, "This packet type (%d) is not destined to be acknowledged\n",pk_type);
												vsr_debug(msg);
												op_sim_end("ERROR !!!!!!",msg,"","");
											break;
										}
											
									
									//DEBUG
									if (DEBUG_ACK >= MEDIUM)
										{
											sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d and currently %d retransmissions at %f\n", my_address , couple->dest , couple->pk_id , couple->nb_retry+1 , op_sim_time()+delay);
											vsr_ack (msg);
										}							
								}
						}
					if ((couple!= NULL) && ((couple->timeout < older_entry) || (older_entry==-1)))
						older_entry = couple->timeout;
				}

			//The next verification
			if (older_entry != -1)
				op_intrpt_schedule_call (older_entry , UNICAST_RETRANSMISSIONS_CODE , send_timeouted_in_ack_table , -1 );
			
		}
}	












//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								DATA
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//***********************************
//			DATA PACKET
//***********************************

//Returns the next hop when I have a data packet to route (When I am source)
int get_initial_next_hop_for_data_pk(Packet* pk_src , int dest_final , List* exceptions){
	int		next_hop;
		
	//I search the if the node is in the neighborhood table
	next_hop = get_relay_to_neighbour_node(dest_final , exceptions);
	if (next_hop == -1)
		{	
			//Not in the neighborhood table, I search directly in the route
			//next_hop = get_next_hop_from_routing_table(route , OPC_TRUE);
			next_hop = get_relay_to_node_from_routing_table(dest_final , pk_src , exceptions);				
		}	
	return(next_hop);
}

//Returns the next hop when I have a data packet to route (When I am a relay)
int get_forward_next_hop_for_data_pk(Packet* pk_src , int dest_final , List *exceptions){
	int		next_hop;
	List*	route;
	char	msg[250];
		
	//I search the if the node is in the neighborhood table
	next_hop = get_relay_to_neighbour_node(dest_final , exceptions);
	if (next_hop == -1)
		{	
			//Not in the neighborhood table, I search directly in the route
			route = create_route_from_pk(pk_src);
			
			if (DEBUG_ROUTE >= HIGH)
				{
					sprintf(msg , "DATA - ROUTE : %s\n",print_route(route));
					vsr_data(msg);
				}

			next_hop = get_next_hop_from_cluster_route(route , OPC_FALSE , exceptions);

		}
	return(next_hop);
}


//Prepare a data packet, search a route...
void schedule_data_pk(int dest_final , int code){
	Packet*		pkptr;
	char		msg[300];
	int			next_hop;
	int			i;
	char		field_name[20];
	//Lists of forbidden relay
	List		*exceptions;
		
	//Null Forbidden List
	exceptions = op_prg_list_create();

	//INCOMING PACKET 
	pkptr = op_pk_create_fmt ("vsr_pk_data");

	//Other Info
	op_pk_nfd_set (pkptr, "SRC_INIT", 	my_address);
	op_pk_nfd_set (pkptr, "SRC", 		my_address);
	op_pk_nfd_set (pkptr, "DEST_FINAL",	dest_final);
	op_pk_nfd_set (pkptr, "PK_ID", 		current_id++);
	op_pk_nfd_set (pkptr, "STAT_ID", 	stats_nb_data_pk);
	op_pk_nfd_set (pkptr, "TTL", 		MAX_NETWORK_RADIUS);
	op_pk_nfd_set (pkptr, "NB_REPAIRS", 0);
	op_pk_nfd_set (pkptr, "OPTION_TYPE",DATA_PK_TYPE);	
	
	//Pk Size
	op_pk_bulk_size_set(pkptr , (int) op_dist_exponential( (double)DATA_PK_SIZE * 8)  );
	
	//Empty useless fields
	for(i=1; i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name , "CLUSTER_%d" , i);
			op_pk_nfd_strip (pkptr, field_name);
		}
	
	//The next hop (in routing table), and fills the packet with this route
	next_hop = get_initial_next_hop_for_data_pk(pkptr , dest_final , exceptions);		
	op_pk_nfd_set (pkptr, "DEST",		next_hop);
	
	//STATS
	if (stats_nb_data_pk >= MAX_DATA_PK)
		op_sim_end("We have too many data packets to store statistics","please increase the value of MAX_DATA_PK","in the header block of the vsr_routing process","");
	stats_data_pk	[stats_nb_data_pk].source			= my_address;
	stats_data_pk	[stats_nb_data_pk].dest				= dest_final;
	stats_data_pk 	[stats_nb_data_pk].time_generation	= op_sim_time();
	stats_data_pk	[stats_nb_data_pk].pk_size			= (int) op_pk_bulk_size_get(pkptr);
	op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stats_nb_data_pk].src_x_pos));	
	op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stats_nb_data_pk].src_y_pos));	
	sprintf(stats_data_pk	[stats_nb_data_pk].route, "%d ", my_address);
	
	//Acks + Transmission
	if (next_hop!=-1)
		{
			//Acks
			if (ACK_FOR_DATA)
				add_unicast_ack(pkptr);
			add_addr_id_couple(my_address , current_id-1);

			//Stats
			stats_data_pk 	[stats_nb_data_pk].time_emission	= op_sim_time();	
			
			//Next hop obtained with the neighborhood_table of with the routing_table
			if (get_relay_to_neighbour_node(dest_final , exceptions) != -1)
				stats_data_pk 	[stats_nb_data_pk].method = DIRECT_NEIGH;	
			else
				stats_data_pk 	[stats_nb_data_pk].method = DIRECT_ROUTING;	
				

			//Emission
			if (DEBUG_DATA >= MEDIUM)
				{
					sprintf(msg , "\n\n!!! DATA-INIT : %d sends directly the packet to %d via %d at %f!!!\n", my_address , dest_final, next_hop , op_sim_time());
					vsr_data(msg);
				}			
			send(pkptr);
		}
	//The node is neither in localization nor in neighborhood table
	else
		{
			//We send a route_request in order to build a road to the destination
			add_in_data_pk_buffer(pkptr);													
			send_route_request(dest_final);

			//Stats
			stats_data_pk 	[stats_nb_data_pk].method = RREQ_ROUTING;	
			
			//Debug
			if (DEBUG_DATA >= MEDIUM)
				{
					sprintf(msg , "DATA : %d buffered the pk to %d at %f (RREQ sent, no current route)\n" , my_address , dest_final , op_sim_time());
					vsr_data(msg);
				}
		}
		
	//Control
	stats_nb_data_pk++;
	if (stats_nb_data_pk == MAX_DATA_PK)
		op_sim_end("We sent too many data pk","please increase the value of MAX_DATA_PK","in the Header block" , "");
}


//Sends a data packet, and call the procedure searching the route / destination
void send_data_pk(Packet* pkptr){
	char 	msg[300];
	int 	dest_final;
	int		next_hop;
	int		stat_id , pk_id;
	//Lists of forbidden relay
	List		*exceptions;
	
	//Null Forbidden List
	exceptions = op_prg_list_create();

	//Common fields
	op_pk_nfd_set(pkptr , "PK_ID",		current_id);
	op_pk_nfd_get(pkptr , "STAT_ID",	&stat_id);
	op_pk_nfd_get(pkptr , "PK_ID",		&pk_id);
	op_pk_nfd_get(pkptr , "DEST_FINAL",	&dest_final);
	
	//STATS
	stats_data_pk 	[stat_id].time_emission	= op_sim_time();

	//Route (if none is known, this function buffers the packet and sends a RREQ), and fills the packet with this route if it exists
	next_hop = get_initial_next_hop_for_data_pk(pkptr , dest_final , exceptions); 
	op_pk_nfd_set(pkptr , "DEST", next_hop);

	//DEBUG
	if (DEBUG_DATA >= MEDIUM)
		{
			sprintf(msg, "\n\n !!!  DATA-INIT : %d sends a data pk to %d at %f (stat_id %d pk_id %d) !!!\n", my_address , dest_final , op_sim_time(),stat_id, pk_id);
			vsr_data(msg);
		}
				
	//Only If we have a valid route
	if (next_hop != -1)
		{
			if (DEBUG_DATA >= MEDIUM)
				{
					sprintf(msg,"DATA : %d sent to %d toward %d\n", my_address , next_hop , dest_final);
					vsr_data(msg);
				}

			//Acks
			if (ACK_FOR_DATA)
				add_unicast_ack(pkptr);

			//Transmission
			current_id++;
			send(pkptr);			
		}
	else if (DEBUG_ROUTE >= LOW)
		{
			sprintf(msg,"DATA : %d doesn't send pk to %d toward %d (no route)\n", my_address , next_hop , dest_final);
			vsr_data(msg);
		}
}

//Forwards the data pk
void forward_data_pk(Packet* pk_src){
	Packet	*pk_dest;
	char	msg[150];
	int		next_hop;
	int		src;
	int		dest_final;
	int		pk_id;
	int		stat_id;
	int		ttl;
	//Lists of forbidden relay
	List		*exceptions;
	
	//Common fields
	op_pk_nfd_get(pk_src , "STAT_ID",		&stat_id);
	op_pk_nfd_get(pk_src , "PK_ID",			&pk_id);
	op_pk_nfd_get(pk_src , "DEST_FINAL",	&dest_final);
	op_pk_nfd_get(pk_src , "SRC",			&src);
	op_pk_nfd_get(pk_src , "TTL",			&ttl);
	
	//I am not allowed to forward the packet to the previous relay (to avoid loops in 2-cliques)
	exceptions = op_prg_list_create();
	add_in_list(exceptions , src);

	//Route (if none is known, this function buffers the packet and sends a RREQ)
	pk_dest = op_pk_copy(pk_src);
	next_hop = get_forward_next_hop_for_data_pk(pk_dest , dest_final , exceptions); 	
	op_pk_nfd_set(pk_dest , "DEST", 	next_hop);
	op_pk_nfd_set(pk_dest , "SRC", 	my_address);
	op_pk_nfd_set(pk_dest , "TTL", 	--ttl);

	//Only If we have a valid route
	if (next_hop != -1)
		{
			if (DEBUG_DATA >= MEDIUM)
				{
					sprintf(msg,"DATA : %d forwards to %d toward %d at %f\n", my_address , next_hop , dest_final , op_sim_time());
					vsr_data(msg);
				}

			//Transmission
			if (ACK_FOR_DATA)
				add_unicast_ack(pk_dest);
			send(pk_dest);			
		}
	else if (DEBUG_DATA >= MEDIUM)
		{
			sprintf(msg,"DATA : %d not sent to %d toward %d (no route)\n", my_address , next_hop , dest_final);
			vsr_data(msg);
		}
}

//Create a local route repair for a data pk: we retransmitted nb_max this packet, but it seems dropped by the radio medium
Boolean initiate_local_repair_for_data_pk(Packet* pkptr , List* exceptions){
	char 	msg[300];
	int 	dest_final;
	int		dest;
	int		next_hop;
	int		stat_id , pk_id;
	int		nb_repairs;
	
	//Common fields
	op_pk_nfd_get(pkptr , "STAT_ID",	&stat_id);
	op_pk_nfd_get(pkptr , "PK_ID",		&pk_id);
	op_pk_nfd_get(pkptr , "DEST_FINAL",	&dest_final);
	op_pk_nfd_get(pkptr , "NB_REPAIRS",	&nb_repairs);
	op_pk_nfd_set(pkptr , "NB_REPAIRS",	++nb_repairs);
	
	//STATS
	stats_data_pk 	[stat_id].nb_repairs++;

	//Route (if none is known, this function buffers the packet and sends a RREQ), and fills the packet with this route if it exists
	op_pk_nfd_get(pkptr , "DEST", &dest);
	next_hop = get_forward_next_hop_for_data_pk(pkptr , dest_final , exceptions); 
	op_pk_nfd_set(pkptr , "DEST", next_hop);
	
	//Only If we have a valid route
	if (next_hop != -1)
		{
			if (DEBUG_DATA >= HIGH)
				{
					sprintf(msg, "%d is in the EXCEPTIONS-LIST : %d\n", next_hop , is_in_list(exceptions ,  next_hop) );
					vsr_data(msg);	
				}
		
			if (DEBUG_DATA > LOW)
				{
					sprintf(msg,"DATA : %d tries a local repair to %d toward %d (data pk for %d)\n", my_address , next_hop , dest_final , dest_final);
					vsr_data(msg);
				}

			//Transmission
			send(op_pk_copy(pkptr));
			return(OPC_TRUE);
		}
	//No possible local repair !
	if (DEBUG_DATA >= MEDIUM)
		{
			sprintf(msg,"DATA : %d drops the packet toward %d (no route, no local repair possible)\n", my_address , dest_final);
			vsr_data(msg);
		}
	return(OPC_FALSE);
}


//***********************************
//			DATA PK BUFFER
//***********************************


//Sends all buffered data packet for the destination (return FALSE if not pk was found in the buffer)
Boolean send_data_pk_buffer(int destination){
	int					i = 0;
	struct_pk_buffer*	entry;
	char				msg[150];
	Boolean				is_found = OPC_FALSE; //at least one entry was found
	int					stat_id , pk_id , src;
	
	
	//If the list is empty
	if (op_prg_list_size(data_pk_buffer)==0)
		return(OPC_FALSE);
	
	if (DEBUG_DATA >= MEDIUM)
		print_data_pk_buffer();
	
	//Search if the entry already exists
	for (i=op_prg_list_size(data_pk_buffer)-1 ; i>=0 ;i--)
		{
			entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
			//We delete the entry
			if ((entry->dest == destination) && (entry->timeout >= op_sim_time()))
				{	
					op_pk_nfd_get(entry->packet, "STAT_ID", &stat_id);
					stats_data_pk 	[stat_id].method = RREQ_ROUTING;	
					
					//DEBUG
					if (DEBUG_DATA >= MEDIUM)
						{
							op_pk_nfd_get(entry->packet, "SRC", 	&src);
							op_pk_nfd_get(entry->packet, "PK_ID", 	&pk_id);
							
							sprintf(msg,"\n\n-------  DATA-PK : data-pk from %d to %d at %f (timeout %f)  (with at least 1 RREQ) (stat_id %d pk_id %d)   -------\n", src , entry->dest , op_sim_time(), entry->timeout, stat_id , pk_id);
							vsr_data(msg);
						}
					
					//Sends the packet
					send_data_pk(entry->packet);
			
					//deletes the corresponding entry
					op_prg_list_remove ( data_pk_buffer , i);
					free(entry);
					is_found = OPC_TRUE;
				}
		}
	
	if ((DEBUG_DATA >= MEDIUM) && (!is_found))
		{
			sprintf(msg,"\n\n-------  DATA-PK : %d doesn't find any data-pk to %d at %f  -------\n", my_address , destination , op_sim_time());
			vsr_data(msg);
		}
	
	return(is_found);

}

//Deletes timeouted entries in data pk buffer
void delete_timeout_in_data_pk_buffer(int code, int unused){
	int					i = 0;
	struct_pk_buffer*	entry;
	double				older_entry = -1;
	char				msg[150];
	
	//If the list is empty
	if (op_prg_list_size(data_pk_buffer)==0)
		return;
	
	//For each entry
	for (i=op_prg_list_size(data_pk_buffer)-1; i >=0; i--)
		{
			entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
			//We delete the entry
			if (entry->timeout <= op_sim_time())
				{				
					//DEBUG
					if (DEBUG_DATA >= MEDIUM)
						{
							sprintf(msg,"DATA-BUFFER : deletes the packet to %d with timeout %f at %f\n", entry->dest , entry->timeout , op_sim_time());
							vsr_debug(msg);
							vsr_data(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove (data_pk_buffer , i);
					free(entry);
				}
			//Older Remaining Entry
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;
		}
	if (older_entry != -1)
		op_intrpt_schedule_call(older_entry , 0 , delete_timeout_in_data_pk_buffer , 0);
}

//Add the data packet in the buffered list
void add_in_data_pk_buffer(Packet *pk_dest){
	struct_pk_buffer*	entry;
	int					dest;
	char				msg[150];
	
	//Delete Timeouted entries Verification
	if (op_prg_list_size (data_pk_buffer) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_DATA_PK_BUFFER , 0 , delete_timeout_in_data_pk_buffer , 0);
	
	op_pk_nfd_get(pk_dest, "DEST_FINAL", &dest);
	
	//Memory allocation
	entry = (struct_pk_buffer*) op_prg_mem_alloc (sizeof(struct_pk_buffer));
			
	//Info
	entry->packet	= op_pk_copy(pk_dest);
	entry->timeout	= op_sim_time() + TIMEOUT_DATA_PK_BUFFER;
	entry->dest		= dest;
	
	//I add it in the list
	op_prg_list_insert(data_pk_buffer, entry , OPC_LISTPOS_TAIL);	
	
	if (DEBUG_DATA >= MEDIUM)
		{
			sprintf(msg, "DATA-PK_BUFFER : %d adds a data pk toward %d at %f\n", my_address , dest, op_sim_time());
			vsr_data(msg);
		}
}










//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								DEBUG
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

char* print_route(List* route){
	int		*addr_cluster;
	int		i;
	char	*result;
	//int		mem_required;
	
	//Initialization
	result = (char*) op_prg_mem_alloc (100000*sizeof(char));
	sprintf(result, "");

	
	for (i=0; i < op_prg_list_size(route) ; i++)
		{
			addr_cluster = (int*) op_prg_list_access(route, i);
			sprintf(result, "%s%d	|	", result , *addr_cluster);
		}	
	//Adds each cluster in the route (If empty -> null string result)
/*	for (i=0; i < op_prg_list_size(route) ; i++)
		{
			addr_cluster = (int*) op_prg_list_access(route, i);
			mem_required = sizeof(char) * (strlen(result) + 3 + ceil ( (int) log10 ((double)*addr_cluster)));
			result = (char*) realloc (result , mem_required );
			sprintf(result, "%s%d	|	", result , *addr_cluster);
			printf("%s\n",result);
		}
*/	
	//Returns the result (after the good memory allocation)
	return(result);
}

//Prints the content of the data pk buffer
void print_data_pk_buffer(){
	int					i = 0;
	struct_pk_buffer*	entry;
	char				msg[250];
	
	//Common Information
	vsr_node ("-------------------------------------------------------------------------\n");
	sprintf (msg,"DATA PK BUFFER  of %d:\n",my_address);
	vsr_node(msg);
	vsr_node ("-------------------------------------------------------------------------\n\n");
	
	vsr_node ("DEST	|	TIMEOUT\n");

	//If the list is empty
	if (op_prg_list_size(data_pk_buffer)==0)
		{
			vsr_node ("\n\n\n");
			return;
		}	
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(data_pk_buffer) ; i++)
		{
			entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
			sprintf(msg, "%d	|	%f\n", entry->dest , entry->timeout);
			vsr_node(msg);
		}
	vsr_node ("\n\n\n");	
}

//Prints the routing table
void print_routing_table(){
	int					i = 0;
	struct_routing*		entry;
	char				msg[350];
	
		
	//Common Information
	vsr_node ("-------------------------------------------------------------------------\n");
	vsr_node ("ROUTING TABLE  :\n");
	vsr_node ("-------------------------------------------------------------------------\n\n");
	
	vsr_node ("DEST	|	HOPS	|	TIMEOUT	|	ROUTE\n");

	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		{
			vsr_node ("\n\n\n");
			return;
		}
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(routing_table) ; i++)
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			sprintf(msg, "%d	|	%d	|	%f	|	%s\n", entry->dest , entry->hops , entry->timeout , print_route(entry->route));
			vsr_node(msg);
		}
	vsr_node ("\n\n\n");	
}

void print_rreq_pk_buffer(){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[150];
	
		
	//Common Information
	vsr_node ("-------------------------------------------------------------------------\n");
	vsr_node ("RREQ PK BUFFER  :\n");
	vsr_node ("-------------------------------------------------------------------------\n\n");
	
	vsr_node ("DEST	|	NB_RETRY	|	STAT_ID	|	TIMEOUT\n");
	
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		{
			vsr_node ("\n\n\n");
			return;
		}

	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(rreq_pk_buffer) ; i++)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			sprintf(msg, "%d		|	%d	|	%d	|	%f\n", entry->dest , entry->nb_retry , entry->stat_id , entry->timeout);
			vsr_node(msg);
		}
	vsr_node ("\n\n\n");
}


//Writes in ack_debug file the list of packets remaining to be acknowledged
void print_unicast_ack_table(){
	ack_couple*		couple;
	char			msg[200];
	int				i;
	
	if (DEBUG_ACK)
		{
			vsr_ack("--------------------------------------------------------\n");
			sprintf(msg,"|                 ACK TABLE FROM %d                   |\n", my_address);
			vsr_ack(msg);
			vsr_ack("--------------------------------------------------------\n");
			vsr_ack("DEST	|	PK_ID	|	NB_RETRY	|	TIMEOUT\n");
	
			//For each entry
			for (i = 0 ; i < op_prg_list_size(ack_table) ; i++)
				{
					//gets the entry
					couple = (ack_couple*) op_prg_list_access (ack_table, i);
			
					sprintf(msg, "%d	|	%d	|	%d		|	%f	\n",couple->dest , couple->pk_id , couple->nb_retry , couple->timeout);
					vsr_ack(msg);			
				}
			vsr_ack("\n");
		}
}


void individual_statistics_generate(){
	char	msg[300];
	
	sprintf(msg,"\n\n------------------ Routing Table of %d ----------------------\n\n",my_address);
	vsr_node(msg);
	print_routing_table();
	sprintf(msg,"\n----------------------------------------------------------------\n\n");				
	vsr_node(msg);		
	sprintf(msg,"\n\n-------------------- Ack Table of %d ------------------------\n\n",my_address);
	vsr_node(msg);
	print_unicast_ack_table();
	sprintf(msg,"\n----------------------------------------------------------------\n\n");				
	vsr_node(msg);		
	sprintf(msg,"\n\n-------------------- RREQ Buffer of %d -----------------------\n\n",my_address);
	vsr_node(msg);
	print_rreq_pk_buffer();
	sprintf(msg,"\n----------------------------------------------------------------\n\n");				
	vsr_node(msg);		
	sprintf(msg,"\n\n------------------- DATA pk Buffer of %d ---------------------\n\n",my_address);
	vsr_node(msg);
	print_data_pk_buffer();
	sprintf(msg,"\n----------------------------------------------------------------\n\n");				
	vsr_node(msg);		
}

void vsr_node(char*msg){
	char	filename[150];
	FILE*	file;
	
	if (my_address<10)
		sprintf(filename,"results_vsr/details_per_node/results_0%d.txt",my_address);
	if (my_address>=10)
		sprintf(filename,"results_vsr/details_per_node/results_%d.txt",my_address);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}

void vsr_debug(char*msg){
	char	filename[60];
	FILE*	file;
	
	sprintf(filename,"results_vsr/%d_vsr_debug_common.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}
void vsr_data(char*msg){
	char	filename[60];
	FILE*	file;

	sprintf(filename,"results_vsr/%d_vsr_debug_data.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}
void vsr_rreq(char*msg){
	char	filename[60];
	FILE*	file;

	sprintf(filename,"results_vsr/%d_vsr_debug_rreq.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}
void vsr_rrep(char*msg){
	char	filename[60];
	FILE*	file;

	sprintf(filename,"results_vsr/%d_vsr_debug_rrep.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}
void vsr_rerr(char*msg){
	char	filename[60];
	FILE*	file;

	sprintf(filename,"results_vsr/%d_vsr_debug_rerr.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}
void vsr_ack(char*msg){
	char	filename[60];
	FILE*	file;

	sprintf(filename,"results_vsr/%d_vsr_DEBUG_ACK.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}
void vsr_route(char*msg){
	char	filename[60];
	FILE*	file;

	sprintf(filename,"results_vsr/%d_vsr_DEBUG_ROUTE.txt",begin_loc_time);
	file = fopen(filename,"a");
	fprintf(file , msg);
	fclose(file);
}

void print_neigh_table(){
		neigh_cell*	ptr;
		char		msg[600];
	
		sprintf(msg,"\n\n----------------- Neighbours of %d ------------------------\n\n",my_address);
		vsr_data(msg);

		ptr = neighbour_table;
		vsr_data("Id	| hops  |  relay	|   weight	| bidirect	|state|   father	|father_hops|	id_ap	|cluster_flag|  CH	|  ch_hops	|	ch_timeout	| timeout\n");
		while(ptr!=NULL)
			{
				sprintf(msg,"%d	|   %d   |	%d	|	%d	|	%d", 	ptr->address , ptr->hops , ptr->relay , ptr->weight , ptr->bidirect);
				//sprintf(msg,"%s	|  %d  |  %d" , 				msg, ptr->mobility , ptr->state);
				sprintf(msg,"%s	|  %d" , 							msg, ptr->state);
				sprintf(msg,"%s  |	%d	|	%d	|	%d" , 			msg, ptr->father , ptr->father_hops , ptr->id_ap);
				sprintf(msg,"%s	|	%d	 |	%d	|	%d	|	%f" , 	msg, ptr->cluster_init_flag , ptr->clusterhead , ptr->clusterhead_hops , ptr->clusterhead_timeout);
				sprintf(msg,"%s	| %f\n" , 							msg, ptr->timeout);
				vsr_data(msg);
				ptr=ptr->next;
			}	
		vsr_data("\n----------------------------------------------------------------\n\n");	

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
	void vsr_process (void);
	Compcode vsr_process_init (void **);
	void vsr_process_diag (void);
	void vsr_process_terminate (void);
	void vsr_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
vsr_process (void)
	{
	int _block_origin = 0;
	FIN (vsr_process ());
	if (1)
		{


		FSM_ENTER (vsr_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "init", "vsr_process () [init enter execs]")
				{
				//Synchronisation with lower levels
				op_intrpt_schedule_self(op_sim_time() + TIME_INIT_MAC , 100);
				
				//Gets the time of simulation beginning
				if (begin_loc_time==0)
					begin_loc_time = time(NULL);
				
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,vsr_process)


			/** state (init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "init", "vsr_process () [init exit execs]")
				{
				}


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (3, state3_enter_exec, ;, "default", "", "init", "init2")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, state1_enter_exec, "idle", "vsr_process () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,vsr_process)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "vsr_process () [idle exit execs]")
				{
				//printf ("%d - %d - %d - %d - %d\n", op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_SELF, OPC_INTRPT_STRM, OPC_INTRPT_ENDSIM);
				
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (PK_DATA_GENERATE)
			FSM_TEST_COND (ENDSIM)
			FSM_TEST_COND (PK_FROM_CDCL)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "PK_DATA_GENERATE", "", "idle", "DATA")
				FSM_CASE_TRANSIT (1, 4, state4_enter_exec, ;, "ENDSIM", "", "idle", "ENDSIM")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "PK_FROM_CDCL", "", "idle", "FROM_LOWER")
				}
				/*---------------------------------------------------------*/



			/** state (DATA) enter executives **/
			FSM_STATE_ENTER_FORCED (2, state2_enter_exec, "DATA", "vsr_process () [DATA enter execs]")
				{
				int		dest_final;
				int		i;
				int		network_id;
				int		node_remote_id;
				int		process_remote_id;
				int		its_address;
				
				
				/*------------------------------------------------------------------------------------------	
												   THE FINAL DESTINATION
				-------------------------------------------------------------------------------------------*/					
				//The final destination is random
				dest_final	= op_dist_uniform (nb_nodes-1)+1;
				if (dest_final == my_address)
					dest_final ++;
				
				//Identificaiton of the remote localization process
				network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
				node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB))    );
				process_remote_id	= op_id_from_name ( node_remote_id, OPC_OBJMTYPE_QPS, ROUTING_PROCESS_NAME);
				
				/*------------------------------------------------------------------------------------------	
											  PACKET GENERATION + TRANSMISSION
				-------------------------------------------------------------------------------------------*/	
				
				for(i=0; i < NB_PK_PER_FLOW ; i++)
					op_intrpt_schedule_call(op_sim_time() + i*INTERARRIVAL_DATA_PK , 0 , schedule_data_pk , dest_final);
				
				
				/*------------------------------------------------------------------------------------------	
															NEXT FLOW
				-------------------------------------------------------------------------------------------*/					
				//I must wake up the next source node
				op_intrpt_schedule_remote(op_sim_time() + op_dist_exponential(INTERARRIVAL_DATA_PK*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE , process_remote_id);
				}


			/** state (DATA) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "DATA", "vsr_process () [DATA exit execs]")
				{
				}


			/** state (DATA) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "DATA", "idle")
				/*---------------------------------------------------------*/



			/** state (init2) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "init2", "vsr_process () [init2 enter execs]")
				{
				int				addr_attribution;
				char			str[200];
				FILE			*file;
				int 			i,j, addr; 
				char			msg[200];
				int				node_id , cdcl_id;
				neigh_cell		**ptr_tmp;
				Packet* 		pkptr;
				
				
				//----------------------------------------------------
				//
				//					My address
				//
				//-----------------------------------------------------
				
				op_ima_obj_attr_get(op_topo_parent(op_id_self()) , "Wireless LAN MAC Address" , &my_address); 
				if (my_address==0)
					op_sim_end("Error : we have a null address","Problem with cdcl layer communications \n","","");
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//	Recuperation of simulation parameters
				//
				//-----------------------------------------------------
				
				//The simulation paramaters
				//For this Node
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_DATA", 			&DEBUG_DATA);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_ROUTE", 			&DEBUG_ROUTE);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_LOAD", 			&DEBUG_LOAD);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_ACK", 			&DEBUG_ACK);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_CONNECTIONS", 		&NB_CONNECTIONS);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"DATA_PK_SIZE", 		&DATA_PK_SIZE);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE,	"INTERARRIVAL_DATA_PK", &INTERARRIVAL_DATA_PK);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_PK_PER_FLOW", 		&NB_PK_PER_FLOW);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"ACK_FOR_DATA", 		&ACK_FOR_DATA);
				
				op_ima_obj_attr_get(op_topo_parent(op_id_self()),	"cds-cluster.is_AP",	&is_AP); 
				
				node_id = op_topo_parent(op_id_self());
				cdcl_id = op_id_from_name(node_id, OPC_OBJTYPE_PROC , "cds-cluster");
				
				my_clusterhead 		= op_ima_obj_svar_get(cdcl_id , "my_clusterhead");
				ptr_tmp				= op_ima_obj_svar_get(cdcl_id , "neighbour_table");
				neighbour_table		= *ptr_tmp;
				my_cds 			 	= op_ima_obj_svar_get(cdcl_id , "my_cds");
				
				
				
				if (is_AP)
					nb_loc_aps++;
				
				
				
				
				
				//----------------------------------------------------
				//
				//				General Infos
				//
				//-----------------------------------------------------
				
				//--------------- Various ---------------
				
				current_id 						= op_dist_uniform(30000);				//the first id of the packet I will send
				
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//		Open the file for out messages
				//
				//-----------------------------------------------------
				
				//----------------------- Stats ---------------------
				my_stat_id = nb_nodes++;							//The first node has id 0
				
				//protection against arrays overflows
				if (my_address >= MAX_ADDRESS)
					op_sim_end("We have too many nodes","please increase the value of MAX_ADDRESS","in the header block of the vsr process","");
				if (nb_nodes >= MAX_NB_NODES)
					op_sim_end("We have too many nodes","please increase the value of MAX_NB_NODES","in the header block of the vsr process","");
				
				address_to_stat_id	[my_address] = my_stat_id;		//Convert an address into an id
				stat_id_to_address	[my_stat_id] = my_address;		//The inverse
				
				
				//--------------------- Per node --------------------
				
				if (my_address<10)
					sprintf(str,"results_vsr/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
					sprintf(str,"results_vsr/details_per_node/results_%d.txt",my_address);
				file = fopen(str,"w");
				fclose(file);
				
				
				
				//--------------- Global periodic stats ------------
				
				if (my_stat_id==1)
					{
						//Stats About Data Packets
						for(i=0; i < MAX_DATA_PK ; i++)
							{
								stats_data_pk [i].source 			= 0;
								stats_data_pk [i].dest 				= 0;
								stats_data_pk [i].pk_size			= 0;
								stats_data_pk [i].hops 				= 0;
								stats_data_pk [i].nb_retry 			= 0;
								stats_data_pk [i].nb_repairs		= 0;
								stats_data_pk [i].time_emission 	= 0;
								stats_data_pk [i].time_reception 	= 0;
								stats_data_pk [i].method		 	= 0;
							}
						//Stats About RREQ/RREP
						for(i=0; i < MAX_RREQ_PK ; i++)
							{
								stats_rreq [i].source 				= 0;
								stats_rreq [i].dest 				= 0;
								stats_rreq [i].rreq_time_emission 	= 0;
								stats_rreq [i].rreq_time_reception 	= 0;
								stats_rreq [i].rreq_nb_retry 		= 0;
								stats_rreq [i].rrep_time_emission 	= 0;
								stats_rreq [i].rrep_time_reception 	= 0;
								stats_rreq [i].rrep_hops			= 0;
								stats_rreq [i].rrep_nb_retry 		= 0;
							}
							
					/*	if  (debug_route)
							{
								sprintf(str,"results_vsr/%d_vsr_network_control.txt",begin_loc_time);
								file = fopen(str,"w");
								fprintf(file , "# Instantaneous Network Control, gathered by packet type\n");
								fprintf(file , "# All flows are in packets per second per node (RET signifies 'Retransmission')\n");
								fprintf(file , "TIME		| 	AP HELLOS	| AP HELLOS RET	| AP REGISTRATIONS| AP REG RET	| 	ACKS		|	HELLO		|	DATA		|	DATA RET	|\n");
								fclose(file);
							}
					*/	
					}
				
				
				
				
				
				//----------------------------------------------------
				//
				//			LISTS INTIALIZATIONS
				//
				//-----------------------------------------------------
				
				
				addr_pk_id_list =  op_prg_list_create();
				routing_table 	=  op_prg_list_create();
				ack_table 		=  op_prg_list_create();
				rreq_pk_buffer 	=  op_prg_list_create();
				data_pk_buffer 	=  op_prg_list_create();
				
				
				
				//----------------------------------------------------
				//
				//				INTERRUPTIONS
				//
				//-----------------------------------------------------
				
				//Periodic Updates
				//op_intrpt_schedule_self (op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS , PERIODIC_FUNCTIONS_CODE);
				
				//For nb_connections nodes, lauch a flow transmission of data packets
				if (NB_CONNECTIONS > current_nb_connections)
					{
						op_intrpt_schedule_self (TIME_BEGIN_DATA + op_dist_uniform(INTERARRIVAL_DATA_PK*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE);
						current_nb_connections++;
					}
				
				
				}


			/** state (init2) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "init2", "vsr_process () [init2 exit execs]")
				{
				}


			/** state (init2) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init2", "idle")
				/*---------------------------------------------------------*/



			/** state (ENDSIM) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "ENDSIM", "vsr_process () [ENDSIM enter execs]")
				{
				//----------------------------------------------------------------
				//				SIMULATION END
				//----------------------------------------------------------------
				
				//Collects some stats when the simulation ends
				//CONTROL
					char	filename[60];
					FILE	*file , *data_file , *rreq_file , *rrep_file , *rerr_file;
					int 	i , j;
					int		node_id , cdcl_id;
					char	msg[150];
				//AP HELLOS
					double	ap_hellos_rcvd_total					= 0; 
				//AP REG
					int		nb_sent_ap_reg							= 0;
					int		nb_received_ap_reg						= 0;
					int		hops_ap_reg								= 0;
					int		nb_retransmissions_ap_reg				= 0;
					double	delay_ap_reg							= 0;
				//DURATION
					double	stats_time_duration;
				//PACKETS
					double	nb_routing_pk_total						= 0;
					double	nb_routing_bits_total					= 0;
				//DATA
					double	delay_data_pk 							= 0;
					int		nb_data_pk								= 0;
					int		nb_data_pk_sent							= 0;
					int		nb_data_pk_received						= 0;
					int		throughput_data_pk						= 0;
					int		hops_data_pk							= 0;
					int		nb_retransmissions_data_pk				= 0;
					double	tmp_distance							= 0;
					int		length_distribution	[MAX_NETWORK_RADIUS];
				//DIRECT NEIGHBOR (dn)
					int		dn_nb_data_pk							= 0;
					double	dn_delay_data_pk 						= 0;
					int		dn_nb_data_pk_received					= 0;
					int		dn_throughput_data_pk					= 0;
					int		dn_hops_data_pk							= 0;
					int		dn_nb_retransmissions_data_pk			= 0;
				//DIRECT ROUTING (dr)
					int		dr_nb_data_pk							= 0;
					double	dr_delay_data_pk 						= 0;
					int		dr_nb_data_pk_received					= 0;
					int		dr_throughput_data_pk					= 0;
					int		dr_hops_data_pk							= 0;
					int		dr_nb_retransmissions_data_pk			= 0;
				//RREQ ROUTING (rr)
					int		rr_nb_data_pk							= 0;
					double	rr_delay_data_pk 						= 0;
					int		rr_nb_data_pk_received					= 0;
					int		rr_throughput_data_pk					= 0;
					int		rr_hops_data_pk							= 0;
					int		rr_nb_retransmissions_data_pk			= 0;
				//SPEED
				   	double	SPEED_HIGH_MIN 							= 0;
				   	double	SPEED_HIGH_MAX 							= 0;
				   	double	SPEED_LOW_MIN 							= 0;
				   	double	SPEED_LOW_MAX 							= 0;
					int		speed_class								= 0;
				//TOPOLOGY
					double	X_MAX									= 0;
					double	Y_MAX									= 0;
				//RREQ
					int		nb_rreq_sent							= 0;
					int		nb_retry_for_rreq						= 0;
					int		nb_retry_for_success_rreq				= 0;
					int		nb_success_rreq_with_non_null_nb_retry	= 0;
				//RREP
					int		nb_rrep_received						= 0;
					int		nb_rrep_transmitted						= 0;
					double	average_delay_for_rrep					= 0;
					double	average_delay_for_rreq_to_final_rrep	= 0;
					int		average_nb_retransmissions_rrep 		= 0;
					int		hops_rrep								= 0;
				//RERR
					int		nb_rerr_sent							= 0;
					int		nb_rerr_received						= 0;
					int		nb_retry_for_rerr						= 0;
					double	average_delay_for_rerr					= 0;
					int		average_nb_retransmissions_rerr 		= 0;
					int		hops_rerr								= 0;
				//OVERHEADS
					int		*overhead_tmp_cdcl_cds_pk				;
					int		*overhead_tmp_cdcl_cluster_pk			;
					int		*overhead_tmp_cdcl_hello_pk				;
					int		*overhead_tmp_cdcl_cds_bits				;
					int		*overhead_tmp_cdcl_cluster_bits			;
					int		*overhead_tmp_cdcl_hello_bits			;
				
				
				//Stats Per node
					individual_statistics_generate();
					
				//Speeds
					if (op_ima_obj_attr_exists(op_topo_parent(op_id_self()), "mobility.Speed_Class") == OPC_TRUE)
						{
							op_ima_obj_attr_get(op_topo_parent(op_id_self()), "mobility.Speed_Class", &speed_class);
							switch(speed_class)		
								{
									case LOW_SPEED :
										nb_loc_low_speed_nodes++;
									break;
									case HIGH_SPEED :
										nb_loc_high_speed_nodes++;
									break;
								}
						}
				
				
					//-----------------------
					//    CDCL OVERHEADS 
					//-----------------------
					node_id = op_topo_parent(op_id_self());
					cdcl_id = op_id_from_name(node_id, OPC_OBJTYPE_PROC , "cds-cluster");
					//In packets
					overhead_tmp_cdcl_cds_pk 			= op_ima_obj_svar_get(cdcl_id , "overhead_cds_pk");
					overhead_tmp_cdcl_cluster_pk 		= op_ima_obj_svar_get(cdcl_id , "overhead_cluster_pk");
					overhead_tmp_cdcl_hello_pk 			= op_ima_obj_svar_get(cdcl_id , "overhead_hello_pk");
					overhead_total_cdcl_cds_pk 			+= *overhead_tmp_cdcl_cds_pk;
					overhead_total_cdcl_cluster_pk 		+= *overhead_tmp_cdcl_cluster_pk;
					overhead_total_cdcl_hello_pk 		+= *overhead_tmp_cdcl_hello_pk;
					//In bits
					overhead_tmp_cdcl_cds_bits 			= op_ima_obj_svar_get(cdcl_id , "overhead_cds_bits");
					overhead_tmp_cdcl_cluster_bits 		= op_ima_obj_svar_get(cdcl_id , "overhead_cluster_bits");
					overhead_tmp_cdcl_hello_bits 		= op_ima_obj_svar_get(cdcl_id , "overhead_hello_bits");
					overhead_total_cdcl_cds_bits 		+= *overhead_tmp_cdcl_cds_bits;
					overhead_total_cdcl_cluster_bits 	+= *overhead_tmp_cdcl_cluster_bits;
					overhead_total_cdcl_hello_bits	 	+= *overhead_tmp_cdcl_hello_bits;
				
				
				
				//Global Stats
					if (my_stat_id+1 == nb_nodes)
						{
							//Initialization
							for (i=0; i< MAX_NETWORK_RADIUS ; i++)
								length_distribution[i] = 0;
				
							//Time Duration for Stats Simualtion
							stats_time_duration = op_sim_time()-TIME_BEGIN_STATS;
							
							//General Parameters
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MIN", 	&SPEED_HIGH_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MAX",	&SPEED_HIGH_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MIN", 	&SPEED_LOW_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MAX",	&SPEED_LOW_MAX); 
				
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "X_MAX",		&X_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Y_MAX",		&Y_MAX); 
							
							
							//-------------------
							//       DATA
							//-------------------
							if (DEBUG_DATA >= LOW)
								{
									sprintf(filename,"results_vsr/%d_vsr_debug_pk_data.txt",begin_loc_time);		
									data_file = fopen(filename , "w");
									fprintf(data_file,"#SRC	|	DEST	|	REPAIRS	|	SENT		|	DELAY		|	METHOD	|	GENERATION	|	DISTANCE	|	ROUTE\n");
								}
							for (i=0 ;  i < stats_nb_data_pk ; i++ )
								{
									//The pk is effective (valid final_dest...)
									if (stats_data_pk [i].time_generation != -1)
										{
											nb_data_pk++;
											
											//Stats according to the routing method
											switch(stats_data_pk [i].method)
												{
													case DIRECT_NEIGH:
														dn_nb_data_pk++;
													break;
													case DIRECT_ROUTING:
														dr_nb_data_pk++;
													break;
													case RREQ_ROUTING:
														rr_nb_data_pk++;
													break;
												}
										}
									
									if (stats_data_pk [i].time_emission != 0)
										nb_data_pk_sent++;						
										
									//The packet was received
									if (stats_data_pk [i].time_reception != 0)
										{
											nb_data_pk_received++;
											throughput_data_pk 			+= stats_data_pk [i].pk_size;
											hops_data_pk 				+= stats_data_pk [i].hops;
											nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
											delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;							
											(length_distribution [stats_data_pk [i].hops]) ++;
											switch(stats_data_pk [i].method)
												{
													case DIRECT_NEIGH:
														dn_nb_data_pk_received++;
														dn_throughput_data_pk 			+= stats_data_pk [i].pk_size;
														dn_hops_data_pk 				+= stats_data_pk [i].hops;
														dn_nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
														dn_delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;							
													break;
													case DIRECT_ROUTING:
														dr_nb_data_pk_received++;
														dr_throughput_data_pk 			+= stats_data_pk [i].pk_size;
														dr_hops_data_pk 				+= stats_data_pk [i].hops;
														dr_nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
														dr_delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;							
													break;
													case RREQ_ROUTING:
														rr_nb_data_pk_received++;
														rr_throughput_data_pk 			+= stats_data_pk [i].pk_size;
														rr_hops_data_pk 				+= stats_data_pk [i].hops;
														rr_nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
														rr_delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;							
													break;
												}
										}
									tmp_distance = sqrt( pow(stats_data_pk [i].src_x_pos - stats_data_pk [i].dest_x_pos , 2) + pow(stats_data_pk [i].src_y_pos - stats_data_pk [i].dest_y_pos , 2));
									if (DEBUG_DATA >= LOW)
										fprintf(data_file,"%d / %d		%d		%f		%f		%d			%f		%f		%s		<-	%d\n", stats_data_pk[i].source , stats_data_pk[i].dest , stats_data_pk[i].nb_repairs , stats_data_pk[i].time_emission , stats_data_pk[i].time_reception - stats_data_pk[i].time_emission , stats_data_pk[i].method , stats_data_pk[i].time_generation , tmp_distance , stats_data_pk[i].route , i);
								}		
							if (DEBUG_DATA>= LOW)
								fclose(data_file);
							
							//-------------------
							//	ROUTE REQUEST
							//-------------------
							if (DEBUG_ROUTE >= LOW)
								{
									sprintf(filename,"results_vsr/%d_vsr_debug_pk_rreq.txt",begin_loc_time);		
									rreq_file = fopen(filename , "w");
									fprintf(rreq_file,"SRC	|	DEST	|	SENT		|	REC		|	RETRY	|	SENT		|	REC		|	HOPS	|	RETRY\n");
								}
				
							nb_rreq_sent = stats_nb_rreq;
							for (i=0 ;  i < stats_nb_rreq ; i++ )
								{
									//Nb of RREQ per route discovering
									nb_retry_for_rreq += stats_rreq [i].rreq_nb_retry;
									
									//Nb of RREQ that create a RREP
									if (stats_rreq [i].rreq_time_reception != 0)
										nb_rrep_transmitted++;							
									
							//-------------------
							//	ROUTE REPLY
							//-------------------
									if (stats_rreq[i].rrep_time_reception != 0)
										{
											nb_rrep_received++;
											hops_rrep	 					+= stats_rreq [i].rrep_hops;
											average_nb_retransmissions_rrep += stats_rreq [i].rrep_nb_retry;							
											
											//Delays for S(RREQ)->S(RREP) & D(RREP)->S(RREP)
											average_delay_for_rrep 					+= stats_rreq [i].rrep_time_reception - stats_rreq [i].rrep_time_emission;
											average_delay_for_rreq_to_final_rrep 	+= stats_rreq [i].rrep_time_reception - stats_rreq [i].rreq_time_emission;
											//Nb RREQ per successfull route discovering
											nb_retry_for_success_rreq				+= stats_rreq [i].rreq_nb_retry;
											nb_success_rreq_with_non_null_nb_retry ++;
										}
									if (DEBUG_ROUTE >= LOW)
										fprintf(rreq_file,"%d	|	%d	|	%f	|	%f	|	%d	|	%f	|	%f	|	%d	|	%d\n", stats_rreq[i].source , stats_rreq[i].dest , stats_rreq[i].rreq_time_emission , stats_rreq[i].rreq_time_reception , stats_rreq[i].rreq_nb_retry , stats_rreq[i].rrep_time_emission , stats_rreq[i].rrep_time_reception , stats_rreq[i].rrep_hops , stats_rreq[i].rrep_nb_retry );
								}
							if (DEBUG_ROUTE >= LOW)
								fclose(rreq_file);
							
							//-------------------
							//	ROUTE ERROR
							//-------------------
							if (DEBUG_ROUTE >= LOW)
								{
									sprintf(filename,"results_vsr/%d_vsr_debug_pk_rerr.txt",begin_loc_time);		
									rerr_file = fopen(filename , "w");
									fprintf(rerr_file,"SRC	|	DEST	|	SENT		|	REC		|	RETRY	|	HOPS\n");
								}
				
							nb_rerr_sent = stats_nb_rerr;
							for (i=0 ;  i < stats_nb_rerr ; i++ )
								{
									if (stats_rerr[i].time_reception != 0)
										{
											nb_rerr_received++;
											hops_rerr	 					+= stats_rerr [i].hops;
											average_nb_retransmissions_rrep += stats_rerr [i].nb_retry;
											average_delay_for_rerr 			+= stats_rerr [i].time_reception - stats_rerr [i].time_emission;
											nb_retry_for_rerr				+= stats_rerr [i].nb_retry;
										}
									if (DEBUG_ROUTE >= LOW)
										fprintf(rerr_file,"%d	|	%d	|	%f	|	%f	|	%d	|	%d\n" , stats_rerr[i].source , stats_rerr[i].dest , stats_rerr[i].time_emission , stats_rerr[i].time_reception , stats_rerr[i].nb_retry , stats_rerr[i].hops );
								}
							if (DEBUG_ROUTE>= LOW)
								fclose(rerr_file);
							
				
							
							//File Initialization	
							sprintf(filename, "results_vsr/%d_vsr_global_stats.txt" , begin_loc_time);
							file = fopen (filename, "w");
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, "|                                 Global Statistics for Routing on CDCL (VSR)                                |\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				   
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                           PARAMETERS                                                       |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Nb AP									:	%d\n", 						nb_loc_aps);
							fprintf(file, "->High Speed \n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_HIGH_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_HIGH_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_loc_high_speed_nodes);
							fprintf(file, "->Low Speed\n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_LOW_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_LOW_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_loc_low_speed_nodes);
							fprintf(file, "X-coordinate max							:	%f\n",						X_MAX);
							fprintf(file, "Y-coordinate max							:	%f\n",						Y_MAX);
							fprintf(file, "Duration (in seconds)						:	%f\n", 					op_sim_time());
							fprintf(file, "Number of Communicating Nodes (i.e. nb of flows)	:	%d\n", 				NB_CONNECTIONS);
							fprintf(file, "Interarrival pk time						:	%f\n", 						INTERARRIVAL_DATA_PK);
							fprintf(file, "Packet Size (in octets)						:	%d\n", 					DATA_PK_SIZE);
							fprintf(file, "Number of packet per flow					:	%d\n", 					NB_PK_PER_FLOW);
							fprintf(file, "\n\n");
				
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                              DATA                                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "\n-------------------------------------------- TOTAL --------------------------------------------------\n");
							fprintf(file, "Nb Packets Generated						:	%d\n",  			nb_data_pk );
							fprintf(file, "Nb Packets Sent							:	%d\n",  			nb_data_pk_sent );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received );
							fprintf(file, "Delivery Ratio (for generated pk)				:	%f\n", 		(double) nb_data_pk_received / (double)nb_data_pk );
							fprintf(file, "Delivery Ratio (for sent pk)					:	%f\n", 			(double) nb_data_pk_received / (double)nb_data_pk_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk / (double)nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk / (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk / nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk / hops_data_pk );
							
							fprintf(file, "\n---------------------------------------- DIRECT NEIGHBOR ------------------------------------------------------\n");
							fprintf(file, "Ratio of data packets						:	%f\n",			(double) dn_nb_data_pk / nb_data_pk);
							fprintf(file, "Nb Packets Sent							:	%d\n",  			dn_nb_data_pk );
							fprintf(file, "Nb Packets Received						:	%d\n",  			dn_nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) dn_nb_data_pk_received / (double)dn_nb_data_pk );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) dn_delay_data_pk / (double)dn_nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) dn_throughput_data_pk / (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) dn_hops_data_pk / dn_nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) dn_nb_retransmissions_data_pk / dn_hops_data_pk );
							fprintf(file, "\n");
							
							fprintf(file, "\n----------------------------------------- DIRECT ROUTING -----------------------------------------------------\n");
							fprintf(file, "Ratio of data packets						:	%f\n",			(double) dr_nb_data_pk / nb_data_pk);
							fprintf(file, "Nb Packets Sent							:	%d\n",  			dr_nb_data_pk );
							fprintf(file, "Nb Packets Received						:	%d\n",  			dr_nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) dr_nb_data_pk_received / (double)dr_nb_data_pk );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) dr_delay_data_pk / (double)dr_nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) dr_throughput_data_pk / (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) dr_hops_data_pk / dr_nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) dr_nb_retransmissions_data_pk / dr_hops_data_pk );
							fprintf(file, "\n");
							
							fprintf(file, "\n------------------------------------------ RREQ ROUTING ----------------------------------------------------\n");
							fprintf(file, "Ratio of data packets						:	%f\n",			(double) rr_nb_data_pk / nb_data_pk);
							fprintf(file, "Nb Packets Sent							:	%d\n",  			rr_nb_data_pk );
							fprintf(file, "Nb Packets Received						:	%d\n",  			rr_nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) rr_nb_data_pk_received / (double)rr_nb_data_pk );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) rr_delay_data_pk / (double)rr_nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) rr_throughput_data_pk / (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) rr_hops_data_pk / rr_nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) rr_nb_retransmissions_data_pk / rr_hops_data_pk );
							fprintf(file, "\n");
							
							fprintf(file, "\n---------------------------------------- ROUTE LENGTH DISTRIBUTION ------------------------------------------------\n");
							for (i=1; i< MAX_NETWORK_RADIUS ; i++)
								if (length_distribution[i] != 0)
									fprintf(file, "%d hops								:	%d\n",		i , 	length_distribution[i]);					
							fprintf(file, "\n\n");
				
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                           ROUTE CONTROL                                                    |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "\n------------------------------------------- ROUTE REQUEST ---------------------------------------------------\n");
							fprintf(file, "Nb RREQ Sent							:	%d\n",  				stats_nb_rreq );
				//			fprintf(file, "Nb packets per RREQ Sent					:	%f\n",  			(double) stats_nb_pk_for_all_rreq / stats_nb_rreq );
							fprintf(file, "Percentage of Successfull RREQ				:	%f\n", 			(double) nb_rrep_transmitted / stats_nb_rreq );
							fprintf(file, "End To End Delay 1 RREQ -> 1 RREP				:	%f\n", 		(double) average_delay_for_rreq_to_final_rrep / nb_rrep_received );
							fprintf(file, "Average nb of RREQ per route discovering			:	%f\n", 		(double) nb_retry_for_rreq / stats_nb_rreq);
							fprintf(file, "Average nb of RREQ per successfull route discovering	:	%f\n", 	(double) nb_retry_for_success_rreq / nb_success_rreq_with_non_null_nb_retry);
							fprintf(file, "\n");
							fprintf(file, "\n--------------------------------------------- ROUTE REPLY -------------------------------------------------\n");
							fprintf(file, "Nb RREP Transmitted						:	%d\n",  			nb_rrep_transmitted );
							fprintf(file, "Nb RREP Received							:	%d\n",  			nb_rrep_received );
							fprintf(file, "Percentage of Successfull RREP (over all RREP)		:	%f\n", 	(double) nb_rrep_received / nb_rrep_transmitted );
							fprintf(file, "Percentage of Successfull RREP (over all RREQ)		:	%f\n", 	(double) nb_rrep_received / stats_nb_rreq );
							fprintf(file, "Average Delay before receiveing the RREP			:	%f\n", 		(double) average_delay_for_rrep / nb_rrep_received );
							fprintf(file, "Average Number of Retransmissions along a RREP		:	%f\n", 	(double) average_nb_retransmissions_rrep / nb_rrep_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rrep / nb_rrep_received  );
							fprintf(file, "\n");
							fprintf(file, "\n--------------------------------------------- ROUTE ERROR -------------------------------------------------\n");
							fprintf(file, "Nb RERR Transmitted						:	%d\n",  			nb_rerr_sent );
							fprintf(file, "Nb RERR Received							:	%d\n",  			nb_rerr_received );
							fprintf(file, "Delivery ratio							:	%f\n", 				(double) nb_rerr_received / nb_rerr_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) average_delay_for_rerr / nb_rerr_received );
							fprintf(file, "Average Number of Retransmissions per hop			:	%f\n", 	(double) average_nb_retransmissions_rerr / nb_rerr_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rerr / nb_rerr_received  );
							fprintf(file, "\n");
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                            NETWORK CONTROL  (in packet per second per node)                                |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				
							nb_routing_pk_total =   ((double)  nb_routing_pk_ack_total + nb_routing_pk_data_retransmission_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							//nb_routing_pk_total += (double) nb_routing_pk_data_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_routing_pk_total +=  ((double) nb_routing_pk_rreq_total + nb_routing_pk_rrep_total + nb_routing_pk_rrep_retransmission_total + nb_routing_pk_rerr_total + nb_routing_pk_rerr_retransmission_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_routing_pk_total +=  ((double) overhead_total_cdcl_cds_pk + overhead_total_cdcl_cluster_pk + overhead_total_cdcl_hello_pk)  / ((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes);
							
							fprintf(file, "--> Average packets per node per second \n");
							fprintf(file , "\n");
							fprintf(file, "CDCL - CDS								:	%f\n", 		(double) overhead_total_cdcl_cds_pk					/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes));
							fprintf(file, "CDCL - Clusters							:	%f\n", 		(double) overhead_total_cdcl_cluster_pk				/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes));
							fprintf(file, "CDCL - Hellos							:	%f\n", 		(double) overhead_total_cdcl_hello_pk				/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes));
							fprintf(file , "\n");
							fprintf(file, "Unicast Acks							:	%f\n", 			(double) nb_routing_pk_ack_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 			(double) nb_routing_pk_data_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 		(double) nb_routing_pk_data_retransmission_total	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREQ									:	%f\n", 			(double) nb_routing_pk_rreq_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREP									:	%f\n", 			(double) nb_routing_pk_rrep_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREP Retransmissions						:	%f\n", 		(double) nb_routing_pk_rrep_retransmission_total	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RERR									:	%f\n", 			(double) nb_routing_pk_rerr_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RERR Retransmissions						:	%f\n", 		(double) nb_routing_pk_rerr_retransmission_total	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 		(double) nb_routing_pk_total);
							fprintf(file, "\n\n");
							
							nb_routing_bits_total 	=  ((double) nb_routing_bits_ack_total+ nb_routing_bits_data_retransmission_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							//nb_routing_bits_total += ((double) nb_routing_bits_data_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_routing_bits_total 	+= ((double) nb_routing_bits_rreq_total + nb_routing_bits_rrep_total + nb_routing_bits_rrep_retransmission_total + nb_routing_bits_rerr_total + nb_routing_bits_rerr_retransmission_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_routing_bits_total 	+= ((double) overhead_total_cdcl_cds_bits + overhead_total_cdcl_cluster_bits + overhead_total_cdcl_hello_bits) / ((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes);
							
							
							fprintf(file, "--> Average bits per node per second \n");
							fprintf(file , "\n");
							fprintf(file, "CDCL - CDS								:	%f\n", 		(double) overhead_total_cdcl_cds_bits				/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes));
							fprintf(file, "CDCL - Clusters							:	%f\n", 		(double) overhead_total_cdcl_cluster_bits			/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes));
							fprintf(file, "CDCL - Hellos							:	%f\n", 		(double) overhead_total_cdcl_hello_bits				/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes));
							fprintf(file , "\n");
							fprintf(file, "Unicast Acks							:	%f\n", 			(double) nb_routing_bits_ack_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 			(double) nb_routing_bits_data_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 		(double) nb_routing_bits_data_retransmission_total	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREQ									:	%f\n", 			(double) nb_routing_bits_rreq_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREP									:	%f\n", 			(double) nb_routing_bits_rrep_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREP Retransmissions						:	%f\n", 		(double) nb_routing_bits_rrep_retransmission_total	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RERR									:	%f\n", 			(double) nb_routing_bits_rerr_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RERR Retransmissions						:	%f\n", 		(double) nb_routing_bits_rerr_retransmission_total	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 		(double) nb_routing_bits_total);
							fprintf(file, "\n\n");
							
							
							fclose(file);
						}
				}


			/** state (ENDSIM) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "ENDSIM", "vsr_process () [ENDSIM exit execs]")
				{
				}


			/** state (ENDSIM) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "ENDSIM", "idle")
				/*---------------------------------------------------------*/



			/** state (FROM_LOWER) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "FROM_LOWER", "vsr_process () [FROM_LOWER enter execs]")
				{
				//PK Fields
				Packet	*pk_src;
				int		packet_type;
				int		dest_final , dest = 0;
				int		src , src_init;
				int		node_searched;
				int		node_dead;
				int		destination_cluster;
				int		ttl;
				int		pk_id;
				int		stat_id;
				//Routes
				List	*route_data;
				List	*route_rreq;
				List	*route_rrep;
				//Control
				char  		msg[2000];
				
				
				
				// Obtain the incoming packet.	
				if (!op_strm_empty(STRM_FROM_CDCL))
					pk_src = op_pk_get (op_intrpt_strm ());
				
				
				
				//Gather information needed
				op_pk_nfd_get(pk_src,"DEST_FINAL", 	&dest_final);
				op_pk_nfd_get(pk_src,"DEST", 		&dest);
				op_pk_nfd_get(pk_src,"SRC",			&src);
				op_pk_nfd_get(pk_src,"SRC_INIT", 	&src_init);
				
				op_pk_nfd_get(pk_src,"OPTION_TYPE",	&packet_type);
				op_pk_nfd_get(pk_src,"TTL", 		&ttl);
				op_pk_nfd_get(pk_src,"PK_ID", 		&pk_id);
				op_pk_nfd_get(pk_src,"STAT_ID", 	&stat_id);
				
				
				
				
				if ((my_cds->state != DOMINATOR) && (packet_type != DATA_PK_TYPE) && (packet_type !=  ACK_APP_PK_TYPE) && (packet_type !=  RREQ_PK_TYPE) && (packet_type !=  RREP_PK_TYPE) && (packet_type !=  RERR_PK_TYPE) )
					{
						printf("!!!! %d is not a dominator and it received a control packet (neither data nor ack) (type=%d) !!!!!!!!!\n",my_address, packet_type);
						return;
					}
				
				switch (packet_type)
					{
					//------------------------------------------	
					//			ACKNOWLEDGEMENTS
					//-------------------------------------------
						case ACK_APP_PK_TYPE :
							//Acknowledges the packet in Retransmissions Buffer
							delete_unicast_ack(src , pk_id);	
						break;
						
						
						
				
					//------------------------------------------	
					//					DATA
					//-------------------------------------------
						
						case DATA_PK_TYPE :
							if (ACK_FOR_DATA)
								acknowledges_unicast_packet(src , pk_id);
						
							//Adds my id as forwarder (3 chars to have a margin before sef fault)
							if (strlen(stats_data_pk [stat_id].route) < MAX_ROUTE_LENGTH - 10)
								sprintf(stats_data_pk [stat_id].route, "%s | %d ", stats_data_pk [stat_id].route , my_address);
						
							if (dest_final == my_address)
								{
									//Stats
									stats_data_pk	[stat_id].hops		 		= MAX_NETWORK_RADIUS - ttl + 1;
									stats_data_pk	[stat_id].time_reception 	= op_sim_time();
									stats_data_pk	[stat_id].pk_size			= (int) op_pk_bulk_size_get(pk_src);
									op_pk_nfd_get(pk_src , "NB_REPAIRS" , &(stats_data_pk[stat_id].nb_repairs));
									op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stat_id].dest_x_pos));	
									op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stat_id].dest_y_pos));	
								
									if (DEBUG_DATA >= MEDIUM)
										{
											sprintf(msg, "!!! DATA - %d received the data pk from %d at %f !!!\n\n", my_address , src_init , op_sim_time());
											vsr_data(msg);
										}
								}
							//I must forward the RREP (juste before forwarding it, I add a routing entry)
							else
								forward_data_pk(pk_src);
					
						break;
						
						
						
						
						
					//------------------------------------------	
					//			ROUTE REQUESTS
					//-------------------------------------------
						
						case RREQ_PK_TYPE :
							//Adds the route contained in the RREQ (if we have to send data further to src_init)
							//route_data = create_route_from_pk (pk_src);
							//add_routing_entry(route_data , src_init, MAX_NETWORK_RADIUS - ttl + 1);
				
							if((dest == ADDR_MULTICAST_BACKBONE) || (dest == my_address))
								{
									route_rreq = create_route_from_pk(pk_src);	
							
									// we get the address of the searched node
									op_pk_nfd_get(pk_src,"NODE_SEARCHED", 	&node_searched);
									
									//Cluster of the destination (I am able to send a RREP for it or not)
									destination_cluster = get_cluster_associated(node_searched);
									
									//I must send a RREP or forward the RREQ ?
									if ((node_searched == my_address) || ((must_rreq_proxy(node_searched)) && (my_clusterhead->address != 0) && (destination_cluster != 0) && (destination_cluster != -1)))
										{
											if (DEBUG_ROUTE >= LOW)
												{
													sprintf(msg, "!! RREQ : %d received a RREQ from %d (src %d) at %f (%d searched), it sends a RREP !!\n", my_address, src , src_init , op_sim_time() , node_searched);
													vsr_rreq(msg);
													vsr_rrep(msg);
												}
											send_route_reply(pk_src , src_init , node_searched , stat_id);
										}	
									else
										{
											if (DEBUG_ROUTE >= LOW)
												{
													sprintf(msg, "RREQ : %d forwards the RREQ from %d via %d at %f (%d searched)\n", my_address, src_init , src , op_sim_time() , node_searched);
													vsr_rreq(msg);
												}
											
											//The destination is different for dominators and for dominatees (Unicast versus Multicast)
											if ((dest == my_address) || (my_clusterhead->address != 0))
												forward_route_request(pk_src);
											else if (DEBUG_ROUTE >= LOW)
												{
													//We discard the RREQ, else we couldn't give a valid route of clusters !
													sprintf(msg, "%d is a dominator with a null clusterhead -> it discards the RREQ at %f\n",  my_address , op_sim_time());
													vsr_rreq(msg);
												}
										}
								}		
						
					
				
					
						break;
						
						
						
						
						
					//------------------------------------------	
					//			ROUTE REPLY
					//-------------------------------------------
						case RREP_PK_TYPE :
							if (ACK_FOR_RREP)
								acknowledges_unicast_packet(src , pk_id);
							//I receive the RREP of one of my RREQ
							if (dest_final == my_address)
								{
									//Saves the route in routing table (source routing)
									//NB : We must inverse the route: the RREP must be sent to source, data must be sent to destination (with the same routing functions)
									route_data = inverse_route(create_route_from_pk(pk_src));
									add_routing_entry(route_data , src_init, MAX_NETWORK_RADIUS - ttl + 1);
				
									//If stat_id == -1, this is a gratuitous RREP -> We d'ont generate any statistic for this packet
									if (stat_id != -1)
										{
											//Stats
											stats_rreq	[stat_id].rreq_nb_retry 		= delete_entry_in_rreq_buffer(src_init) + 1;	//We send 1 + nb_retry RREQ for a route discovering
											
											stats_rreq	[stat_id].rrep_hops		 		= MAX_NETWORK_RADIUS - ttl + 1;
											stats_rreq	[stat_id].rrep_time_reception 	= op_sim_time();
											stats_rreq	[stat_id].rrep_nb_retry			= 0;							
										}									
				
									//data bufferized
									send_data_pk_buffer(src_init);
												
				
									//Debug
									if (DEBUG_ROUTE >= LOW)
										{
											//Extracts the route
											route_rrep = create_route_from_pk(pk_src);
				
											sprintf(msg, "\n\n!!! RREP : %d received a RREP from %d via %d at %f !!!\n", my_address , src_init , src , op_sim_time());
											vsr_rrep(msg);
											sprintf(msg,"		route = %s\n\n",print_route(route_rrep));
											vsr_rrep(msg);	
											
											op_prg_list_free(route_rrep);
											op_prg_mem_free(route_rrep);
										}
								
									//We don't have to send route_request for that node anymore
									delete_entry_in_rreq_buffer(src_init);
								}
							//I must forward the RREP (juste before forwarding it, I add a routing entry)
							else
								forward_route_reply(pk_src);
				
						break;
						
						
						
						
						
					//------------------------------------------	
					//			ROUTE ERROR
					//-------------------------------------------
						case RERR_PK_TYPE :
							if (ACK_FOR_RERR)
								acknowledges_unicast_packet(src , pk_id);
							//I receive the RERR
							if (dest_final == my_address)
								{
									// we get the address of the searched node
									op_pk_nfd_get(pk_src,"NODE_DEAD", 	&node_dead);
									
									//Deletes the route in routing table (source routing)
									delete_route(node_dead);
										
									//Stats
									stats_rerr	[stat_id].hops		 		= MAX_NETWORK_RADIUS - ttl + 1;
									stats_rerr	[stat_id].time_reception 	= op_sim_time();
				
									//Debug
									if (DEBUG_ROUTE >= LOW)
										{
											sprintf(msg, "\n\n!!! RERR : %d received a RERR from %d via %d at %f !!!\n\n", my_address , src_init , src , op_sim_time());
											vsr_rerr(msg);
										}				
								}
							//I must forward the RREP (juste before forwarding it, I add a routing entry)
							else
								forward_route_error(pk_src);
				
						break;
				
						default:
							printf("VSR - Pk_FROM_LOWER => Type de paquet inconnu : %d !!!!!!!!!!!!!!!\n", packet_type);
							op_pk_print(pk_src);
						break;	
				
					}
						
					
				
					
				//The packet was treated, destroys it to free memory 
				op_pk_destroy(pk_src);
				}


			/** state (FROM_LOWER) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "FROM_LOWER", "vsr_process () [FROM_LOWER exit execs]")
				{
				}


			/** state (FROM_LOWER) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "FROM_LOWER", "idle")
				/*---------------------------------------------------------*/



			/** state (OBSOLETE) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (6, "OBSOLETE", "vsr_process () [OBSOLETE enter execs]")
				{
				/*
				
				//*********************************************
				//	OLD GENERATION OF ROUTE MANIPULATION
				//*********************************************
				
				
				
				
				//Add the cluster "cluster_to_add" after the cluster "cluster_before", in the route contained in the pk
				void add_cluster_in_cluster_route(Packet* pkptr, int cluster_before, int cluster_to_add){
					int		i , j;
					char	field_name[20];
					int		addr_cluster;
					char	msg[300];
					Packet*	pk_src;
					
					
					//For debug
					pk_src = op_pk_copy(pkptr);	
					
					//For each cluster fields
					i = 1;
					sprintf(field_name, "CLUSTER_%d", i);
					while ((i<=MAX_CLUSTER_FIELDS_IN_RREQ_PK) && (op_pk_nfd_is_set(pkptr, field_name)))
						{
							op_pk_nfd_get(pkptr, field_name, &addr_cluster);
							
							//Adds the cluster and shift all other elements
							if (addr_cluster == cluster_before)
								{
									//I have enough fields ?
									sprintf(field_name, "CLUSTER_%d", MAX_CLUSTER_FIELDS_IN_RREQ_PK);
									if (op_pk_nfd_is_set(pkptr, field_name))
										op_sim_end("we don't have enough fields to store the route of clusters","in ROUTE REPLY/REQUEST...","please increase the constant MAX_CLUSTER_FIELDS_IN_RREQ_PK","");
				
									//I shift the next elements
									for (j = MAX_CLUSTER_FIELDS_IN_RREQ_PK - 1; j >= i+1 ; j--)
										{							
											sprintf(field_name, "CLUSTER_%d", j);							
											if (op_pk_nfd_is_set(pkptr, field_name))
												{
													op_pk_nfd_get(pkptr, field_name, &addr_cluster);
													sprintf(field_name, "CLUSTER_%d", j+1);
													op_pk_nfd_set(pkptr, field_name, addr_cluster);
												}
										}
								
									//I add "cluster_to_add"
									sprintf(field_name, "CLUSTER_%d", i+1);
									op_pk_nfd_set(pkptr, field_name, cluster_to_add);
									
									//End !
									if (debug_route>0)
										{
											sprintf(msg , "I add %d after the cluster %d\n", cluster_to_add , cluster_before);
											vsr_rrep(msg);
							
											sprintf(msg , "I change the route from %s to %s at %f\n", print_route(create_route_from_pk(pk_src)) , print_route(create_route_from_pk(pkptr)) , op_sim_time());
											vsr_rrep(msg);
										}
									return;
								}
							
							//Next cluster in the route
							i++;
							sprintf(field_name, "CLUSTER_%d", i);		
						}
					
					printf("we didn't find the cluster %d\n",cluster_before);
				}
				
				//Delete all cluster addresses present in the route contained in pkptr, between cluster1 and cluster2
				void delete_clusters_between(Packet* pkptr , int cluster1 , int cluster2){
					int		i = 1;
					int		addr_cluster;
					char	field_name[20];
					short	start, end , shift;
					Packet*	pk_src;
					char	msg[300];
					
					//Debug
					pk_src = op_pk_copy(pkptr);
					
					//Searches the cell to shift between cluster1 and cluster2
					for (i=1; (i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK) && (addr_cluster != cluster2); i++)
						{
							sprintf(field_name, "CLUSTER_%d",i);
							op_pk_nfd_get(pkptr, field_name, &addr_cluster);
							if (addr_cluster == cluster1)
								start = i;
							if (addr_cluster == cluster2)
								end = i;
						}
				
					//The second cluster was not found
					if (addr_cluster != cluster2)
						return;
					
					//Shift the cells
					i = start + 1;
					shift = end - start - 1;
					
					//I shift the next elements
					for (i = start +1 ; i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK - shift ; i ++)
						{							
							sprintf(field_name, "CLUSTER_%d", i + shift);							
							if (op_pk_nfd_is_set(pkptr, field_name))
								{
									op_pk_nfd_get(pkptr, field_name, &addr_cluster);
									sprintf(field_name, "CLUSTER_%d", i);
									op_pk_nfd_set(pkptr, field_name, addr_cluster);
								}
							else
								{
									sprintf(field_name, "CLUSTER_%d", i);
									if (op_pk_nfd_is_set(pkptr, field_name))
										op_pk_nfd_strip(pkptr, field_name);
								}
						}
					
					if (debug_route)
						{
							sprintf(msg , "%d deletes all clusters between %d (%d) and %d (%d) \n", my_address , cluster1, start , cluster2 , end);
							vsr_rrep(msg);
							
							sprintf(msg, "I change the route from %s to %s at %f\n", print_route(create_route_from_pk(pk_src)) , print_route(create_route_from_pk(pkptr)), op_sim_time());
							vsr_rrep(msg);
						}
				}
				
				
				//Returns the next hop toward 
				int get_next_hop_from_cluster_relay_fields(Packet* pkptr , int destination){
					//Control
					int				i;
					char			msg[150];
					//Packet info
					char			field_name[20];
					int				next_hop;
					int				next_hop_cluster;
					int				addr_cluster;
				
					//List of intermediary Clusters
					for(i=1 ; i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK; i++)
						{
							sprintf(field_name , "CLUSTER_%d",i);
							if (op_pk_nfd_is_set(pkptr, field_name))
								{
									//Get the next cluster in the list
									op_pk_nfd_get(pkptr, field_name , &addr_cluster);
									
									//Is this the end of the route ?
									if (addr_cluster == my_clusterhead->address)
										return(-1);
									
									//Is this cluster reachable ?
									next_hop = search_next_hop_for_cluster(addr_cluster , destination);
									
									sprintf(msg, "->relay vers cluster %d : noeud %d\n",addr_cluster , next_hop);
									vsr_rrep(msg);
									
									if (next_hop != -1)
										{
											//Delete useless fields
											if (my_clusterhead->address != get_cluster_associated(next_hop))
												delete_clusters_between(pkptr , addr_cluster , my_clusterhead->address);
									
											//Must the cluster of next hop be added in the cluster list ?
											next_hop_cluster = get_cluster_associated(next_hop);
											if ((next_hop_cluster != my_clusterhead->address ) && (next_hop_cluster != addr_cluster))
												add_cluster_in_cluster_route(pkptr , addr_cluster , next_hop_cluster);
				
									
											return(next_hop);
										}
								}
							//No remaining cluster relay fields -> No route found !
							else
								return(-1);
						}
					
				
					//No relay found !
					return(-1);
				}
				
				*/
				
				
				
				
				/*	
				FUNCTION  : 
				
					//List of intermediary Clusters
					for(i=1 ; i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK; i++)
						{
							sprintf(field_name , "CLUSTER_%d",i);
							if (op_pk_nfd_is_set(pk_src, field_name))
								{
									op_pk_nfd_get(pk_src 	, field_name , &addr_cluster);
									op_pk_nfd_set(pk_dest 	, field_name , addr_cluster);
								}
							//Updates the route of intermediary clusters
							else if (! is_final_clusters_added)
								{
									//My clusterhead
									if (addr_cluster != my_clusterhead->address)
										{
											addr_cluster = my_clusterhead->address;
											op_pk_nfd_set(pk_dest 	, field_name , addr_cluster);
											i++;
											sprintf(field_name , "CLUSTER_%d",i);							
										}
									
									//The clusterhead of the destination
									destination_cluster = get_cluster_associated(addr_searched);
									if (addr_cluster != destination_cluster)
										{	
											addr_cluster = destination_cluster;
											if ((addr_cluster != 0) && (addr_cluster != -1) && (addr_cluster != my_clusterhead->address))
												op_pk_nfd_set(pk_dest 	, field_name , addr_cluster);
											else
												op_pk_nfd_strip(pk_dest, field_name);
										}
									else
										op_pk_nfd_strip(pk_dest, field_name);
									
									is_final_clusters_added = OPC_TRUE;
								}
							else
								op_pk_nfd_strip(pk_dest , field_name);				
						}
					
					// we search the address of the father
					next_hop = get_relay_to(pk_dest , addr_src);	
					op_pk_nfd_set(pk_dest , "DEST", next_hop);
				*/	
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (13,vsr_process)


			/** state (OBSOLETE) exit executives **/
			FSM_STATE_EXIT_UNFORCED (6, "OBSOLETE", "vsr_process () [OBSOLETE exit execs]")
				{
				}


			/** state (OBSOLETE) transition processing **/
			FSM_TRANSIT_MISSING ("OBSOLETE")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,vsr_process)
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
vsr_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (vsr_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (vsr_process)",
			sizeof (vsr_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
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
		((vsr_process_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
vsr_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
vsr_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (vsr_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in vsr_process_svar function. */
#undef my_address
#undef is_AP
#undef addr_pk_id_list
#undef ack_table
#undef my_ap
#undef current_id
#undef my_stat_id
#undef NB_CONNECTIONS
#undef DEBUG_DATA
#undef DEBUG_ROUTE
#undef routing_table
#undef rreq_pk_buffer
#undef my_clusterhead
#undef neighbour_table
#undef my_cds
#undef data_pk_buffer
#undef DEBUG_LOAD
#undef DATA_PK_SIZE
#undef DEBUG_ACK
#undef INTERARRIVAL_DATA_PK
#undef NB_PK_PER_FLOW
#undef overhead_cdcl_cds
#undef overhead_cdcl_cluster
#undef overhead_cdcl_hello
#undef ACK_FOR_DATA



void
vsr_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	vsr_process_state		*prs_ptr;

	FIN (vsr_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (vsr_process_state *)gen_ptr;

	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("addr_pk_id_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->addr_pk_id_list);
		FOUT;
		}
	if (strcmp ("ack_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_table);
		FOUT;
		}
	if (strcmp ("my_ap" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_ap);
		FOUT;
		}
	if (strcmp ("current_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_id);
		FOUT;
		}
	if (strcmp ("my_stat_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_stat_id);
		FOUT;
		}
	if (strcmp ("NB_CONNECTIONS" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_CONNECTIONS);
		FOUT;
		}
	if (strcmp ("DEBUG_DATA" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_DATA);
		FOUT;
		}
	if (strcmp ("DEBUG_ROUTE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_ROUTE);
		FOUT;
		}
	if (strcmp ("routing_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->routing_table);
		FOUT;
		}
	if (strcmp ("rreq_pk_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->rreq_pk_buffer);
		FOUT;
		}
	if (strcmp ("my_clusterhead" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_clusterhead);
		FOUT;
		}
	if (strcmp ("neighbour_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->neighbour_table);
		FOUT;
		}
	if (strcmp ("my_cds" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_cds);
		FOUT;
		}
	if (strcmp ("data_pk_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->data_pk_buffer);
		FOUT;
		}
	if (strcmp ("DEBUG_LOAD" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_LOAD);
		FOUT;
		}
	if (strcmp ("DATA_PK_SIZE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DATA_PK_SIZE);
		FOUT;
		}
	if (strcmp ("DEBUG_ACK" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_ACK);
		FOUT;
		}
	if (strcmp ("INTERARRIVAL_DATA_PK" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->INTERARRIVAL_DATA_PK);
		FOUT;
		}
	if (strcmp ("NB_PK_PER_FLOW" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_PK_PER_FLOW);
		FOUT;
		}
	if (strcmp ("overhead_cdcl_cds" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cdcl_cds);
		FOUT;
		}
	if (strcmp ("overhead_cdcl_cluster" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cdcl_cluster);
		FOUT;
		}
	if (strcmp ("overhead_cdcl_hello" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->overhead_cdcl_hello);
		FOUT;
		}
	if (strcmp ("ACK_FOR_DATA" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ACK_FOR_DATA);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

